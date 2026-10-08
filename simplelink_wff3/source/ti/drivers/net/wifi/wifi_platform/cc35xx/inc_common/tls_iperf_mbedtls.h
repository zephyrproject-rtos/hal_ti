/*
 * Copyright (c) 2024, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * Thin wrapper around the mbedTLS API used by the TLS iperf client and server.
 *
 * All mbedTLS calls are funnelled through this file so that the iperf code
 * never includes mbedTLS headers directly.  To port to a different TLS
 * library, only this file and tls_iperf_mbedtls.c need to change.
 */

#ifndef TLS_IPERF_MBEDTLS_H_
#define TLS_IPERF_MBEDTLS_H_

#include <stddef.h>
#include <stdint.h>

/* Endpoint constants passed to tls_iperf_ctx_alloc() */
#define TLS_IPERF_ENDPOINT_CLIENT   0
#define TLS_IPERF_ENDPOINT_SERVER   1

/* Opaque context type - callers hold pointers, never inspect internals */
typedef struct tls_iperf_ctx_s    tls_iperf_ctx_t;

/*
 * BIO send/recv function pointer types - match the mbedTLS BIO signature.
 * The caller provides transport-specific implementations (e.g. lwIP sockets).
 * ctx:  caller-supplied transport context (e.g. pointer to socket fd)
 * Returns bytes transferred (>0), or negative mbedTLS error code.
 *
 * Use TLS_IPERF_BIO_ERR_IO for a generic I/O error and
 * TLS_IPERF_BIO_WANT_READ when no data is available yet (non-blocking recv).
 */
typedef int (*tls_iperf_bio_send_t)(void *ctx, const unsigned char *buf, size_t len);
typedef int (*tls_iperf_bio_recv_t)(void *ctx,       unsigned char *buf, size_t len);

#define TLS_IPERF_BIO_ERR_IO     (-0x004E)  /* MBEDTLS_ERR_SSL_INTERNAL_ERROR */
#define TLS_IPERF_BIO_WANT_READ  (-0x6900)  /* MBEDTLS_ERR_SSL_WANT_READ      */
#define TLS_IPERF_BIO_WANT_WRITE (-0x6880)  /* MBEDTLS_ERR_SSL_WANT_WRITE     */

/* ------------------------------------------------------------------ */
/*  Lifecycle                                                          */
/* ------------------------------------------------------------------ */

/*
 * Allocate and initialise a TLS context.
 * endpoint: 0 = client, 1 = server
 * Returns NULL on allocation failure.
 */
tls_iperf_ctx_t *tls_iperf_ctx_alloc(int endpoint);

/* Free a context previously created by tls_iperf_ctx_alloc(). */
void tls_iperf_ctx_free(tls_iperf_ctx_t *ctx);

/* ------------------------------------------------------------------ */
/*  Configuration                                                      */
/* ------------------------------------------------------------------ */

/*
 * Set the CA certificate used to verify the peer (client mode).
 * cert/len: DER or null-terminated PEM buffer (len must include '\0' for PEM).
 * Returns 0 on success, negative mbedTLS error code on failure.
 */
int tls_iperf_set_ca_cert(tls_iperf_ctx_t *ctx,
                           const unsigned char *cert, size_t len);

/*
 * Load the server's own certificate and private key (server mode).
 * cert/cert_len: DER or null-terminated PEM buffer.
 * key/key_len:   DER or null-terminated PEM buffer.
 * Returns 0 on success, negative mbedTLS error code on failure.
 */
int tls_iperf_set_own_cert(tls_iperf_ctx_t *ctx,
                            const unsigned char *cert, size_t cert_len,
                            const unsigned char *key,  size_t key_len);

/*
 * Attach a transport BIO and complete the TLS handshake.
 * bio_ctx:   transport context passed as-is to send/recv (e.g. pointer to fd)
 * bio_send:  caller-supplied send function (e.g. wrapping lwip_send)
 * bio_recv:  caller-supplied recv function (e.g. wrapping lwip_recv)
 * Returns 0 on success, negative mbedTLS error code on failure.
 */
int tls_iperf_handshake(tls_iperf_ctx_t    *ctx,
                         void               *bio_ctx,
                         tls_iperf_bio_send_t bio_send,
                         tls_iperf_bio_recv_t bio_recv);

/* ------------------------------------------------------------------ */
/*  Data transfer                                                      */
/* ------------------------------------------------------------------ */

/*
 * Send up to len bytes.
 * Returns number of bytes written (>0), or negative mbedTLS error code.
 * MBEDTLS_ERR_SSL_WANT_WRITE / WANT_READ: caller should retry.
 */
int tls_iperf_write(tls_iperf_ctx_t *ctx,
                    const unsigned char *buf, size_t len);

/*
 * Receive up to len bytes.
 * Returns number of bytes read (>0), 0 on peer close, or negative error.
 * MBEDTLS_ERR_SSL_WANT_READ / WANT_WRITE: caller should retry.
 * MBEDTLS_ERR_SSL_PEER_CLOSE_NOTIFY: clean close by peer.
 */
int tls_iperf_read(tls_iperf_ctx_t *ctx,
                   unsigned char *buf, size_t len);

/*
 * Send a TLS close_notify alert.  Call before closing the socket.
 */
void tls_iperf_close_notify(tls_iperf_ctx_t *ctx);

/* ------------------------------------------------------------------ */
/*  Error helpers                                                      */
/* ------------------------------------------------------------------ */

/*
 * Return non-zero if ret is the WANT_READ or WANT_WRITE non-fatal code
 * (caller should retry the operation).
 */
int tls_iperf_is_want_io(int ret);

/*
 * Return non-zero if ret indicates the peer closed cleanly.
 */
int tls_iperf_is_peer_close(int ret);

/*
 * Return the raw certificate verify flags after a failed handshake.
 * Useful for printing the reason for CERT_VERIFY_FAILED errors.
 */
uint32_t tls_iperf_get_verify_flags(tls_iperf_ctx_t *ctx);

/*
 * Return the negotiated cipher suite name (e.g. "TLS-ECDHE-RSA-WITH-AES-128-GCM-SHA256").
 * Valid after a successful tls_iperf_handshake(). Returns NULL if ctx is NULL.
 */
const char *tls_iperf_get_ciphersuite(tls_iperf_ctx_t *ctx);

#endif /* TLS_IPERF_MBEDTLS_H_ */
