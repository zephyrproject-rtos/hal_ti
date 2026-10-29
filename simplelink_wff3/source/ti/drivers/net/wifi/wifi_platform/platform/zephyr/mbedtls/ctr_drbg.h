/* SPDX-License-Identifier: Apache-2.0 */

#ifndef TI_WIFI_PLATFORM_MBEDTLS_CTR_DRBG_H
#define TI_WIFI_PLATFORM_MBEDTLS_CTR_DRBG_H

#include <stddef.h>

typedef struct {
	unsigned int unused;
} mbedtls_ctr_drbg_context;

static inline void mbedtls_ctr_drbg_free(mbedtls_ctr_drbg_context *ctx)
{
	(void)ctx;
}

static inline int mbedtls_ctr_drbg_random(void *ctx, unsigned char *buf,
					  size_t len)
{
	(void)ctx;
	(void)buf;
	(void)len;

	return -1;
}

#endif /* TI_WIFI_PLATFORM_MBEDTLS_CTR_DRBG_H */
