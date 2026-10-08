/*
 *  Copyright The Mbed TLS Contributors
 *  Copyright (c) 2024, Texas Instruments Incorporated
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

/* For size_t */
#include <stddef.h>

#if !defined(MBEDTLS_MEMORY_ALIGN_MULTIPLE)
#define MBEDTLS_MEMORY_ALIGN_MULTIPLE       4 /**< Align on multiples of this value */
#endif

/** \} name SECTION: Module settings */

#define MBEDTLS_MEMORY_VERIFY_NONE         0
#define MBEDTLS_MEMORY_VERIFY_ALLOC        (1 << 0)
#define MBEDTLS_MEMORY_VERIFY_FREE         (1 << 1)
#define MBEDTLS_MEMORY_VERIFY_ALWAYS       (MBEDTLS_MEMORY_VERIFY_ALLOC | \
                                            MBEDTLS_MEMORY_VERIFY_FREE)

void *psaInt_mbedtls_calloc(size_t n, size_t size);

void psaInt_mbedtls_free(void *ptr);

/**
 * @brief   Initialize use of stack-based memory allocator.
 *          The stack-based allocator does memory management inside the
 *          presented buffer and does not call calloc() and free().
 *          It sets the global psaInt_mbedtls_calloc() and psaInt_mbedtls_free() pointers
 *          to its own functions.
 *          (Provided psaInt_mbedtls_calloc() and psaInt_mbedtls_free() are thread-safe if
 *           MBEDTLS_THREADING_C is defined)
 *
 * @note    This code is not optimized and provides a straight-forward
 *          implementation of a stack-based memory allocator.
 *
 * @param buf   buffer to use as heap
 * @param len   size of the buffer
 */
void psaInt_mbedtls_memory_buffer_alloc_init(unsigned char *buf, size_t len);

/**
 * @brief   Clears all memory allocator metadata (first node, pointer to buffer, etc).
 *          Allows use of a new buffer if psaInt_mbedtls_memory_buffer_alloc_init()
 *          is subsequently called. The provided buffer is not modified in this
 *          function.
 */
void psaInt_mbedtls_memory_buffer_alloc_free(void);
