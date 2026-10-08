/* SPDX-License-Identifier: Apache-2.0 */

#ifndef TI_WIFI_PLATFORM_MBEDTLS_ENTROPY_H
#define TI_WIFI_PLATFORM_MBEDTLS_ENTROPY_H

typedef struct {
	unsigned int unused;
} mbedtls_entropy_context;

static inline void mbedtls_entropy_free(mbedtls_entropy_context *ctx)
{
	(void)ctx;
}

#endif /* TI_WIFI_PLATFORM_MBEDTLS_ENTROPY_H */
