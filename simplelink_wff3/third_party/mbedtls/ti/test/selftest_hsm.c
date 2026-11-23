/*
 *  Self-test demonstration program
 *
 *  Copyright The Mbed TLS Contributors
 *  SPDX-License-Identifier: Apache-2.0
 *
 *  Licensed under the Apache License, Version 2.0 (the "License"); you may
 *  not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 *  WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/mbedtls_config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#define MBEDTLS_ALLOW_PRIVATE_ACCESS

#include "mbedtls/build_info.h"

#include "mbedtls/base64.h"
#include "mbedtls/bignum.h"
#include "mbedtls/x509.h"
#include "mbedtls/timing.h"
#include "mbedtls/nist_kw.h"
#include "mbedtls/threading.h"

#include "mbedtls/net_sockets.h"
#include "mbedtls/ssl.h"
#include "mbedtls/entropy.h"
#include "mbedtls/ctr_drbg.h"
#include "mbedtls/error.h"
#include "mbedtls/psa_util.h"
#include "test/certs.h"

#include <string.h>

#if defined(MBEDTLS_PLATFORM_C)
#include "mbedtls/platform.h"
#endif

#if defined(MBEDTLS_MEMORY_BUFFER_ALLOC_C)
#include "mbedtls/memory_buffer_alloc.h"
#endif

#define SERVER_PORT "4433"
#define SERVER_NAME "localhost"
#define GET_REQUEST "GET / HTTP/1.0\r\n\r\n"

#if defined MBEDTLS_SELF_TEST
/* Sanity check for malloc. This is not expected to fail, and is rather
 * intended to display potentially useful information about the platform,
 * in particular the behavior of malloc(0). */
static int calloc_self_test(int verbose)
{
    int failures  = 0;
    void *empty1  = mbedtls_calloc(0, 1);
    void *empty2  = mbedtls_calloc(0, 1);
    void *buffer1 = mbedtls_calloc(1, 1);
    void *buffer2 = mbedtls_calloc(1, 1);
    uintptr_t old_buffer1;

    if (empty1 == NULL && empty2 == NULL)
    {
        if (verbose)
            mbedtls_printf("  CALLOC(0): passed (NULL)\n");
    }
    else if (empty1 == NULL || empty2 == NULL)
    {
        if (verbose)
            mbedtls_printf("  CALLOC(0): failed (mix of NULL and non-NULL)\n");
        ++failures;
    }
    else if (empty1 == empty2)
    {
        if (verbose)
            mbedtls_printf("  CALLOC(0): passed (same non-null)\n");
    }
    else
    {
        if (verbose)
            mbedtls_printf("  CALLOC(0): passed (distinct non-null)\n");
    }

    if (buffer1 == NULL || buffer2 == NULL)
    {
        if (verbose)
            mbedtls_printf("  CALLOC(1): failed (NULL)\n");
        ++failures;
    }
    else if (buffer1 == buffer2)
    {
        if (verbose)
            mbedtls_printf("  CALLOC(1): failed (same buffer twice)\n");
        ++failures;
    }
    else
    {
        if (verbose)
            mbedtls_printf("  CALLOC(1): passed\n");
    }

    old_buffer1 = (uintptr_t)buffer1;
    mbedtls_free(buffer1);
    buffer1 = mbedtls_calloc(1, 1);
    if (buffer1 == NULL)
    {
        if (verbose)
            mbedtls_printf("  CALLOC(1 again): failed (NULL)\n");
        ++failures;
    }
    else
    {
        if (verbose)
            mbedtls_printf("  CALLOC(1 again): passed (%s address)\n",
                           (uintptr_t)old_buffer1 == (uintptr_t)buffer1 ? "same" : "different");
    }

    if (verbose)
        mbedtls_printf("\n");
    mbedtls_free(empty1);
    mbedtls_free(empty2);
    mbedtls_free(buffer1);
    mbedtls_free(buffer2);
    return (failures);
}
#endif /* MBEDTLS_SELF_TEST */

static int test_snprintf(size_t n, const char *ref_buf, int ref_ret)
{
    int ret;
    char buf[10]       = "xxxxxxxxx";
    const char ref[10] = "xxxxxxxxx";

    ret = mbedtls_snprintf(buf, n, "%s", "123");
    if (ret < 0 || (size_t)ret >= n)
        ret = -1;

    if (strncmp(ref_buf, buf, sizeof(buf)) != 0 || ref_ret != ret || memcmp(buf + n, ref + n, sizeof(buf) - n) != 0)
    {
        return (1);
    }

    return (0);
}

static int run_test_snprintf(void)
{
    return (test_snprintf(0, "xxxxxxxxx", -1) != 0 || test_snprintf(1, "", -1) != 0 || test_snprintf(2, "1", -1) != 0 ||
            test_snprintf(3, "12", -1) != 0 || test_snprintf(4, "123", 3) != 0 || test_snprintf(5, "123", 3) != 0);
}


#if defined(MBEDTLS_SELF_TEST)
#if defined(MBEDTLS_MEMORY_BUFFER_ALLOC_C)
int mbedtls_memory_buffer_alloc_free_and_self_test(int verbose)
{
    if (verbose != 0)
    {
        #if defined(MBEDTLS_MEMORY_DEBUG)
        mbedtls_memory_buffer_alloc_status();
        #endif
    }
    mbedtls_memory_buffer_alloc_free();
    return (mbedtls_memory_buffer_alloc_self_test(verbose));
}
#endif

int psa_can_do_hash(psa_algorithm_t hash_alg)
{
    (void)hash_alg;
    return 1;
}

int psa_can_do_cipher(psa_key_type_t key_type, psa_algorithm_t cipher_alg)
{
    (void)key_type;
    (void)cipher_alg;
    return 1;
}

// #if defined (MBEDTLS_PSA_CRYPTO_C)
// int mbedtls_tls_self_test(int verbose)
// {
//     int ret = 1, len;
//     int exit_code = MBEDTLS_EXIT_FAILURE;
//     mbedtls_net_context server_fd;
//     uint32_t flags;
//     unsigned char buf[1024];
//     const char *pers = "ssl_client1";

//     mbedtls_entropy_context entropy;
//     mbedtls_ctr_drbg_context ctr_drbg;
//     mbedtls_ssl_context ssl;
//     mbedtls_ssl_config conf;
//     mbedtls_x509_crt cacert;

//     /*
//      * 0. Initialize the RNG and the session data
//      */

//     /* Enabling mbedtls_net_init() would require MBEDTLS_NET_C to be enabled, which requires a unix define to be present. */
//     // mbedtls_net_init(&server_fd);

//     mbedtls_ssl_init(&ssl);
//     mbedtls_ssl_config_init(&conf);
//     mbedtls_x509_crt_init(&cacert);


//     /* These initializations should not be necessary when psa_generate_random() is present, as specified in psa-transition.md */
//     // Note: It should be confirmed that any ctrdrbg/entropy APIs are using psa_get_random as we would expect
//     // mbedtls_ctr_drbg_init(&ctr_drbg);
//     // mbedtls_entropy_init(&entropy);

//     psa_status_t status = psa_crypto_init();
//     if (status != PSA_SUCCESS) {
//         mbedtls_fprintf(stderr, "Failed to initialize PSA Crypto implementation: %d\n",
//                         (int) status);
//         goto exit;
//     }

//     /*
//      * 0. Initialize certificates
//      */
//     mbedtls_printf("  . Loading the CA root certificate ...");
//     fflush(stdout);

//     ret = mbedtls_x509_crt_parse(&cacert, (const unsigned char *) mbedtls_test_cas_pem,
//                                  mbedtls_test_cas_pem_len);
//     if (ret < 0) {
//         mbedtls_printf(" failed\n  !  mbedtls_x509_crt_parse returned -0x%x\n\n",
//                        (unsigned int) -ret);
//         goto exit;
//     }


//     /*
//      * 1. Start the connection - can't, without MBEDTLS_NET_C
//      */
//     // mbedtls_printf("  . Connecting to tcp/%s/%s...", SERVER_NAME, SERVER_PORT);
//     // fflush(stdout);

//     // if ((ret = mbedtls_net_connect(&server_fd, SERVER_NAME,
//     //                                SERVER_PORT, MBEDTLS_NET_PROTO_TCP)) != 0) {
//     //     mbedtls_printf(" failed\n  ! mbedtls_net_connect returned %d\n\n", ret);
//     //     goto exit;
//     // }

//     // mbedtls_printf(" ok\n");


//     /*
//      * 2. Setup stuff
//      */
//     mbedtls_printf("  . Setting up the SSL/TLS structure...");
//     fflush(stdout);

//     if ((ret = mbedtls_ssl_config_defaults(&conf,
//                                            MBEDTLS_SSL_IS_CLIENT,
//                                            MBEDTLS_SSL_TRANSPORT_STREAM,
//                                            MBEDTLS_SSL_PRESET_DEFAULT)) != 0) {
//         mbedtls_printf(" failed\n  ! mbedtls_ssl_config_defaults returned %d\n\n", ret);
//         goto exit;
//     }

//     mbedtls_printf(" ok\n");

//     /* OPTIONAL is not optimal for security,
//      * but makes interop easier in this simplified example */
//     mbedtls_ssl_conf_authmode(&conf, MBEDTLS_SSL_VERIFY_OPTIONAL);
//     mbedtls_ssl_conf_ca_chain(&conf, &cacert, NULL);
//     mbedtls_ssl_conf_rng(&conf, mbedtls_psa_get_random, MBEDTLS_PSA_RANDOM_STATE);
//     // mbedtls_ssl_conf_dbg(&conf, my_debug, stdout);

//     // if ((ret = mbedtls_ssl_setup(&ssl, &conf)) != 0) {
//     //     mbedtls_printf(" failed\n  ! mbedtls_ssl_setup returned %d\n\n", ret);
//     //     goto exit;
//     // }

//     // if ((ret = mbedtls_ssl_set_hostname(&ssl, SERVER_NAME)) != 0) {
//     //     mbedtls_printf(" failed\n  ! mbedtls_ssl_set_hostname returned %d\n\n", ret);
//     //     goto exit;
//     // }

//     // mbedtls_ssl_set_bio(&ssl, &server_fd, mbedtls_net_send, mbedtls_net_recv, NULL);


//     /*
//      * 3. Handshake
//      */
//     // mbedtls_printf("  . Performing the SSL/TLS handshake...");
//     // fflush(stdout);

//     // while ((ret = mbedtls_ssl_handshake(&ssl)) != 0) {
//     //     if (ret != MBEDTLS_ERR_SSL_WANT_READ && ret != MBEDTLS_ERR_SSL_WANT_WRITE) {
//     //         mbedtls_printf(" failed\n  ! mbedtls_ssl_handshake returned -0x%x\n\n",
//     //                        (unsigned int) -ret);
//     //         goto exit;
//     //     }
//     // }

//     // mbedtls_printf(" ok\n");


//     /* Test an API that uses PSA Crypto before any error checks, to verify proper linking */
//     mbedtls_ssl_reset_checksum(&ssl);
//     exit:
//         mbedtls_x509_crt_free(&cacert);
//         mbedtls_ssl_free(&ssl);
//         mbedtls_ssl_config_free(&conf);
//         /* Nothing to free in our case, we do not provide this API */
//         // // mbedtls_psa_crypto_free();
//         mbedtls_exit(exit_code);
// }
// #endif /* MBEDTLS_PSA_CRYPTO_C */

typedef struct
{
    const char *name;
    int (*function)(int);
} selftest_t;

const selftest_t selftests[] = {{"calloc", calloc_self_test},
    // #if defined(MBEDTLS_NIST_KW_C) && defined(MBEDTLS_AES_C)
    //                             {"nist_kw", mbedtls_nist_kw_self_test},
    // #endif
    // #if defined(MBEDTLS_BASE64_C)
    //                             {"base64", mbedtls_base64_self_test},
    // #endif
    // #if defined(MBEDTLS_BIGNUM_C)
    //                             {"mpi", mbedtls_mpi_self_test},
    // #endif
    #if defined (MBEDTLS_PSA_CRYPTO_C)
                                {"tls_with_psa_crypto", mbedtls_tls_self_test},
    #endif
    /* Heap test comes last */
    #if defined(MBEDTLS_MEMORY_BUFFER_ALLOC_C)
                                {"memory_buffer_alloc", mbedtls_memory_buffer_alloc_free_and_self_test},
    #endif
                                {NULL, NULL}};
#endif /* MBEDTLS_SELF_TEST */

/* mainThread must be called by kernel-specific main, for example, from main_tirtos.c */
void *mainThread(void *arg0)
{
#if defined(MBEDTLS_SELF_TEST)
    const selftest_t *test;
#endif                     /* MBEDTLS_SELF_TEST */
    int v             = 1; /* v=1 for verbose mode */
    int suites_tested = 0, suites_failed = 0;
    void *pointer;
#if defined(MBEDTLS_MEMORY_BUFFER_ALLOC_C) && defined(MBEDTLS_SELF_TEST)
    unsigned char buf[1000];
#endif

    /* Set alternate threading implementations - must be done in the application */
    mbedtls_threading_set_alt(threading_mutex_init_pthread,
                              threading_mutex_free_pthread,
                              threading_mutex_lock_pthread,
                              threading_mutex_unlock_pthread);

    /*
     * The C standard doesn't guarantee that all-bits-0 is the representation
     * of a NULL pointer. We do however use that in our code for initializing
     * structures, which should work on every modern platform. Let's be sure.
     */
    memset(&pointer, 0, sizeof(void *));
    if (pointer != NULL)
    {
        mbedtls_printf("all-bits-zero is not a NULL pointer\n");
        mbedtls_exit(MBEDTLS_EXIT_FAILURE);
    }

    /*
     * Make sure we have a snprintf that correctly zero-terminates
     */
    if (run_test_snprintf() != 0)
    {
        mbedtls_printf("the snprintf implementation is broken\n");
        mbedtls_exit(MBEDTLS_EXIT_FAILURE);
    }

#if defined(MBEDTLS_SELF_TEST)

    #if defined(MBEDTLS_MEMORY_BUFFER_ALLOC_C)
    mbedtls_memory_buffer_alloc_init(buf, sizeof(buf));
    #endif

    /* Run all the tests */
    for (test = selftests; test->name != NULL; test++)
    {
        if (test->function(v) != 0)
        {
            suites_failed++;
        }
        suites_tested++;
    }
#else
    mbedtls_printf(" MBEDTLS_SELF_TEST not defined.\n");
#endif

    if (v != 0)
    {
        mbedtls_printf("  Executed %d test suites\n\n", suites_tested);

        if (suites_failed > 0)
        {
            mbedtls_printf("  [ %d tests FAIL ]\n\n", suites_failed);
        }
        else
        {
            mbedtls_printf("  [ All tests PASS ]\n\n");
        }
#if defined(_WIN32)
        mbedtls_printf("  Press Enter to exit this program.\n");
        fflush(stdout);
        getchar();
#endif
    }

    if (suites_failed > 0)
        mbedtls_exit(MBEDTLS_EXIT_FAILURE);

    mbedtls_threading_free_alt();
    mbedtls_exit(MBEDTLS_EXIT_SUCCESS);
}