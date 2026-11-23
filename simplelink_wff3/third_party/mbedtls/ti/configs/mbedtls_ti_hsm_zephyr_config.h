/*
 * Copyright (c) 2026 Conclusive Engineering Sp. z o.o.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef MBEDTLS_TI_HSM_ZEPHYR_CONFIG_H
#define MBEDTLS_TI_HSM_ZEPHYR_CONFIG_H

#include "mbedtls_ti_config.h"

/*
 * The TI HSM PSA adapter provides its own persistent key storage glue over
 * ITS. Do not also enable the generic mbedTLS PSA storage backend: the two
 * implementations export the same symbols with different internal contracts.
 */
#undef MBEDTLS_PSA_CRYPTO_STORAGE_C

#endif /* MBEDTLS_TI_HSM_ZEPHYR_CONFIG_H */
