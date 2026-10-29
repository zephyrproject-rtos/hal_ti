/*
 * Copyright (c) 2026 Conclusive Engineering Sp. z o.o.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stddef.h>
#include <stdint.h>

/* The IS25WJ032F key-storage partition holds eight 1600-byte ITS objects. */
const size_t FLASH_KEY_PERSISTENT_COUNT = 8;

#if defined(CONFIG_TI_CC35XX_HSM_PSA_ADAPTER)
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/adapter_psa_key_management.h>

const size_t MBEDTLS_KEY_VOLATILE_COUNT = 4;
const size_t MBEDTLS_KEY_ASSET_STORE_COUNT = 4;
const size_t MBEDTLS_KEY_PERSISTENT_COUNT = 0;

psa_key_context_t gl_PSA_Key[8];

uint8_t volatileAllocBuffer[3072];
size_t volatileAllocBufferSizeBytes = sizeof(volatileAllocBuffer);
#endif
