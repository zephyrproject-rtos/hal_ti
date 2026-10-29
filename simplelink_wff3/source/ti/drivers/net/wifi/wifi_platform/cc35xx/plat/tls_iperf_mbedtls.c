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
 * mbedTLS backend for tls_iperf_mbedtls.h.
 *
 * All direct mbedTLS API calls for the TLS iperf client/server are
 * centralised here.  The iperf code only sees the opaque tls_iperf_ctx_t
 * type and the wrapper functions declared in tls_iperf_mbedtls.h.
 */

#include <string.h>

#include <mbedtls/ssl.h>
#include <mbedtls/x509_crt.h>
#include <mbedtls/pk.h>
#include <mbedtls/error.h>
#include <mbedtls/platform.h>
#include <psa/crypto.h>

#include "osi_kernel.h"
#include "tls_iperf_mbedtls.h"

extern int cc35xxCiphers[];

/* ------------------------------------------------------------------ */
/*  Internal context struct                                            */
/* ------------------------------------------------------------------ */

struct tls_iperf_ctx_s {
    mbedtls_ssl_context ssl;
    mbedtls_ssl_config  conf;
    mbedtls_x509_crt    ca_cert;
    mbedtls_x509_crt    own_cert;
    mbedtls_pk_context  own_key;
};

/* ------------------------------------------------------------------ */
/*  PSA RNG callback (hardware-backed on CC35xx)                      */
/* ------------------------------------------------------------------ */

static int tls_psa_rng(void *ctx, unsigned char *buf, size_t len)
{
    (void)ctx;
    return (psa_generate_random(buf, len) == PSA_SUCCESS) ? 0 : -1;
}

/* ------------------------------------------------------------------ */
/*  Lifecycle                                                          */
/* ------------------------------------------------------------------ */

tls_iperf_ctx_t *tls_iperf_ctx_alloc(int endpoint)
{
    tls_iperf_ctx_t *ctx = (tls_iperf_ctx_t *)os_malloc(sizeof(tls_iperf_ctx_t));
    if (!ctx)
    {
        return NULL;
    }

    mbedtls_platform_set_calloc_free(os_calloc, os_free);
    mbedtls_ssl_init(&ctx->ssl);
    mbedtls_ssl_config_init(&ctx->conf);
    mbedtls_x509_crt_init(&ctx->ca_cert);
    mbedtls_x509_crt_init(&ctx->own_cert);
    mbedtls_pk_init(&ctx->own_key);

    psa_crypto_init();

    int ret = mbedtls_ssl_config_defaults(&ctx->conf,
                                          endpoint,
                                          MBEDTLS_SSL_TRANSPORT_STREAM,
                                          MBEDTLS_SSL_PRESET_DEFAULT);
    if (ret != 0)
    {
        tls_iperf_ctx_free(ctx);
        return NULL;
    }

    mbedtls_ssl_conf_rng(&ctx->conf, tls_psa_rng, NULL);
    mbedtls_ssl_conf_ciphersuites(&ctx->conf, cc35xxCiphers);
    /* Pin to TLS 1.2 - cc35xxCiphers are TLS 1.2 suites and the RSA cert does
     * not support the RSA-PSS signatures required by TLS 1.3 CertificateVerify */
    mbedtls_ssl_conf_min_tls_version(&ctx->conf, MBEDTLS_SSL_VERSION_TLS1_2);
    mbedtls_ssl_conf_max_tls_version(&ctx->conf, MBEDTLS_SSL_VERSION_TLS1_2);
    /* Advertise MFL=4096 to peer - matches MBEDTLS_SSL_IN_CONTENT_LEN=6144 budget */
    mbedtls_ssl_conf_max_frag_len(&ctx->conf, MBEDTLS_SSL_MAX_FRAG_LEN_4096);

    return ctx;
}

void tls_iperf_ctx_free(tls_iperf_ctx_t *ctx)
{
    if (!ctx)
    {
        return;
    }
    mbedtls_ssl_free(&ctx->ssl);
    mbedtls_ssl_config_free(&ctx->conf);
    mbedtls_x509_crt_free(&ctx->ca_cert);
    mbedtls_x509_crt_free(&ctx->own_cert);
    mbedtls_pk_free(&ctx->own_key);
    os_free(ctx);
}

/* ------------------------------------------------------------------ */
/*  Configuration                                                      */
/* ------------------------------------------------------------------ */

int tls_iperf_set_ca_cert(tls_iperf_ctx_t *ctx,
                           const unsigned char *cert, size_t len)
{
    int ret = mbedtls_x509_crt_parse(&ctx->ca_cert, cert, len);
    if (ret != 0)
    {
        return ret;
    }
    mbedtls_ssl_conf_ca_chain(&ctx->conf, &ctx->ca_cert, NULL);
    mbedtls_ssl_conf_authmode(&ctx->conf, MBEDTLS_SSL_VERIFY_REQUIRED);
    return 0;
}

int tls_iperf_set_own_cert(tls_iperf_ctx_t *ctx,
                            const unsigned char *cert, size_t cert_len,
                            const unsigned char *key,  size_t key_len)
{
    int ret = mbedtls_x509_crt_parse(&ctx->own_cert, cert, cert_len);
    if (ret != 0)
    {
        return ret;
    }

    ret = mbedtls_pk_parse_key(&ctx->own_key, key, key_len,
                                NULL, 0, tls_psa_rng, NULL);
    if (ret != 0)
    {
        return ret;
    }

    ret = mbedtls_ssl_conf_own_cert(&ctx->conf, &ctx->own_cert, &ctx->own_key);
    return ret;
}

int tls_iperf_handshake(tls_iperf_ctx_t     *ctx,
                         void                *bio_ctx,
                         tls_iperf_bio_send_t bio_send,
                         tls_iperf_bio_recv_t bio_recv)
{
    int ret = mbedtls_ssl_setup(&ctx->ssl, &ctx->conf);
    if (ret != 0)
    {
        return ret;
    }

    mbedtls_ssl_set_bio(&ctx->ssl, bio_ctx, bio_send, bio_recv, NULL);

    while ((ret = mbedtls_ssl_handshake(&ctx->ssl)) != 0)
    {
        if (ret != MBEDTLS_ERR_SSL_WANT_READ && ret != MBEDTLS_ERR_SSL_WANT_WRITE)
        {
            return ret;
        }
    }
    return 0;
}

/* ------------------------------------------------------------------ */
/*  Data transfer                                                      */
/* ------------------------------------------------------------------ */

int tls_iperf_write(tls_iperf_ctx_t *ctx,
                    const unsigned char *buf, size_t len)
{
    return mbedtls_ssl_write(&ctx->ssl, buf, len);
}

int tls_iperf_read(tls_iperf_ctx_t *ctx,
                   unsigned char *buf, size_t len)
{
    return mbedtls_ssl_read(&ctx->ssl, buf, len);
}

void tls_iperf_close_notify(tls_iperf_ctx_t *ctx)
{
    mbedtls_ssl_close_notify(&ctx->ssl);
}

/* ------------------------------------------------------------------ */
/*  Error helpers                                                      */
/* ------------------------------------------------------------------ */

int tls_iperf_is_want_io(int ret)
{
    return (ret == MBEDTLS_ERR_SSL_WANT_READ  ||
            ret == MBEDTLS_ERR_SSL_WANT_WRITE ||
            ret == MBEDTLS_ERR_SSL_ALLOC_FAILED);
}

int tls_iperf_is_peer_close(int ret)
{
    /* clean TLS close_notify, EOF, or TCP reset (client killed without close_notify) */
    return (ret == MBEDTLS_ERR_SSL_PEER_CLOSE_NOTIFY ||
            ret == 0 ||
            ret == TLS_IPERF_BIO_ERR_IO);
}

uint32_t tls_iperf_get_verify_flags(tls_iperf_ctx_t *ctx)
{
    return mbedtls_ssl_get_verify_result(&ctx->ssl);
}

const char *tls_iperf_get_ciphersuite(tls_iperf_ctx_t *ctx)
{
    if (!ctx) return NULL;
    return mbedtls_ssl_get_ciphersuite(&ctx->ssl);
}
