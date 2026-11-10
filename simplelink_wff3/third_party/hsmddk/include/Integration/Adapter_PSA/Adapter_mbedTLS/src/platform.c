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

/* TI Modification: This file was brought from mbedTLS but had memory
 * backtrace and memory debug functionality stripped out, because
 * neither was used in any TI configuration of mbedTLS anyways.
 * Occurrences of mbedTLS_exit(), which invoked C's exit(), were replaced
 * with simple early returns. Also adjusted comments to follow TI coding style.
 */
#include <stdlib.h>
#include <string.h>

#include <third_party/hsmddk/include/Integration/Adapter_PSA/Adapter_mbedTLS/incl/platform.h>

#define MAGIC1       0xFF00AA55
#define MAGIC2       0xEE119966

typedef struct _memory_header memory_header;
struct _memory_header {
    size_t          magic1;
    size_t          size;
    size_t          alloc;
    memory_header   *prev;
    memory_header   *next;
    memory_header   *prev_free;
    memory_header   *next_free;
    size_t          magic2;
};

typedef struct {
    unsigned char   *buf;
    size_t          len;
    memory_header   *first;
    memory_header   *first_free;
    int             verify;
}
buffer_alloc_ctx;

static buffer_alloc_ctx heap;

static int verify_header(memory_header *hdr)
{
    if (hdr->magic1 != MAGIC1) {
        return 1;
    }

    if (hdr->magic2 != MAGIC2) {
        return 1;
    }

    if (hdr->alloc > 1) {
        return 1;
    }

    if (hdr->prev != NULL && hdr->prev == hdr->next) {
        return 1;
    }

    if (hdr->prev_free != NULL && hdr->prev_free == hdr->next_free) {
        return 1;
    }

    return 0;
}

static int verify_chain(void)
{
    memory_header *prv = heap.first, *cur;

    if (prv == NULL || verify_header(prv) != 0) {
        return 1;
    }

    if (heap.first->prev != NULL) {
        return 1;
    }

    cur = heap.first->next;

    while (cur != NULL) {
        if (verify_header(cur) != 0) {
            return 1;
        }

        if (cur->prev != prv) {
            return 1;
        }

        prv = cur;
        cur = cur->next;
    }

    return 0;
}

static void *buffer_alloc_calloc(size_t n, size_t size)
{
    memory_header *new, *cur = heap.first_free;
    unsigned char *p;
    void *ret;
    size_t original_len, len;

    if (heap.buf == NULL || heap.first == NULL) {
        return NULL;
    }

    original_len = len = n * size;

    if (n == 0 || size == 0 || len / n != size) {
        return NULL;
    } else if (len > (size_t) -MBEDTLS_MEMORY_ALIGN_MULTIPLE) {
        return NULL;
    }

    if (len % MBEDTLS_MEMORY_ALIGN_MULTIPLE) {
        len -= len % MBEDTLS_MEMORY_ALIGN_MULTIPLE;
        len += MBEDTLS_MEMORY_ALIGN_MULTIPLE;
    }

    /* Find block that fits */
    while (cur != NULL) {
        if (cur->size >= len) {
            break;
        }

        cur = cur->next_free;
    }

    if (cur == NULL) {
        return NULL;
    }

    if (cur->alloc != 0) {
        return NULL; /* Error condition - mbedTLS invokes exit() */
    }

    /* Found location, split block if > memory_header + 4 room left */
    if (cur->size - len < sizeof(memory_header) +
        MBEDTLS_MEMORY_ALIGN_MULTIPLE) {
        cur->alloc = 1;

        /* Remove from free_list */
        if (cur->prev_free != NULL) {
            cur->prev_free->next_free = cur->next_free;
        } else {
            heap.first_free = cur->next_free;
        }

        if (cur->next_free != NULL) {
            cur->next_free->prev_free = cur->prev_free;
        }

        cur->prev_free = NULL;
        cur->next_free = NULL;

        if ((heap.verify & MBEDTLS_MEMORY_VERIFY_ALLOC) && verify_chain() != 0) {
            return NULL; /* Error condition - mbedTLS invokes exit() */
        }

        ret = (unsigned char *) cur + sizeof(memory_header);
        memset(ret, 0, original_len);

        return ret;
    }

    p = ((unsigned char *) cur) + sizeof(memory_header) + len;
    new = (memory_header *) p;

    new->size = cur->size - len - sizeof(memory_header);
    new->alloc = 0;
    new->prev = cur;
    new->next = cur->next;
    new->magic1 = MAGIC1;
    new->magic2 = MAGIC2;

    if (new->next != NULL) {
        new->next->prev = new;
    }

    /* Replace cur with new in free_list */
    new->prev_free = cur->prev_free;
    new->next_free = cur->next_free;
    if (new->prev_free != NULL) {
        new->prev_free->next_free = new;
    } else {
        heap.first_free = new;
    }

    if (new->next_free != NULL) {
        new->next_free->prev_free = new;
    }

    cur->alloc = 1;
    cur->size = len;
    cur->next = new;
    cur->prev_free = NULL;
    cur->next_free = NULL;

    if ((heap.verify & MBEDTLS_MEMORY_VERIFY_ALLOC) && verify_chain() != 0) {
        return NULL; /* Error condition - mbedTLS invokes exit() */
    }

    ret = (unsigned char *) cur + sizeof(memory_header);
    memset(ret, 0, original_len);

    return ret;
}

static void buffer_alloc_free(void *ptr)
{
    memory_header *hdr, *old = NULL;
    unsigned char *p = (unsigned char *) ptr;

    if (ptr == NULL || heap.buf == NULL || heap.first == NULL) {
        return;
    }

    if (p < heap.buf || p >= heap.buf + heap.len) {
        return; /* Error condition - mbedTLS invokes exit() */
    }

    p -= sizeof(memory_header);
    hdr = (memory_header *) p;

    if (verify_header(hdr) != 0) {
        return; /* Error condition - mbedTLS invokes exit() */
    }

    if (hdr->alloc != 1) {
        return; /* Error condition - mbedTLS invokes exit() */
    }

    hdr->alloc = 0;

    /* Regroup with block before */
    if (hdr->prev != NULL && hdr->prev->alloc == 0) {
        hdr->prev->size += sizeof(memory_header) + hdr->size;
        hdr->prev->next = hdr->next;
        old = hdr;
        hdr = hdr->prev;

        if (hdr->next != NULL) {
            hdr->next->prev = hdr;
        }

        memset(old, 0, sizeof(memory_header));
    }

    /* Regroup with block after */
    if (hdr->next != NULL && hdr->next->alloc == 0) {
        hdr->size += sizeof(memory_header) + hdr->next->size;
        old = hdr->next;
        hdr->next = hdr->next->next;

        if (hdr->prev_free != NULL || hdr->next_free != NULL) {
            if (hdr->prev_free != NULL) {
                hdr->prev_free->next_free = hdr->next_free;
            } else {
                heap.first_free = hdr->next_free;
            }

            if (hdr->next_free != NULL) {
                hdr->next_free->prev_free = hdr->prev_free;
            }
        }

        hdr->prev_free = old->prev_free;
        hdr->next_free = old->next_free;

        if (hdr->prev_free != NULL) {
            hdr->prev_free->next_free = hdr;
        } else {
            heap.first_free = hdr;
        }

        if (hdr->next_free != NULL) {
            hdr->next_free->prev_free = hdr;
        }

        if (hdr->next != NULL) {
            hdr->next->prev = hdr;
        }

        memset(old, 0, sizeof(memory_header));
    }

    /* Prepend to free_list if we have not merged. Does not
     * have to stay in same order as prev / next list.
     */
    if (old == NULL) {
        hdr->next_free = heap.first_free;
        if (heap.first_free != NULL) {
            heap.first_free->prev_free = hdr;
        }
        heap.first_free = hdr;
    }

    if ((heap.verify & MBEDTLS_MEMORY_VERIFY_FREE) && verify_chain() != 0) {
        return; /* Error condition - mbedTLS invokes exit() */
    }
}

void *psaInt_mbedtls_calloc(size_t nmemb, size_t size)
{
    return buffer_alloc_calloc(nmemb, size);
}

void psaInt_mbedtls_free(void *ptr)
{
    buffer_alloc_free(ptr);
}

void psaInt_mbedtls_memory_buffer_alloc_init(unsigned char *buf, size_t len)
{
    /* Sets heap.verify to 0, so no verification of header/metadata chains occurs */
    memset(&heap, 0, sizeof(buffer_alloc_ctx));

    if (len < sizeof(memory_header) + MBEDTLS_MEMORY_ALIGN_MULTIPLE) {
        return;
    } else if ((size_t) buf % MBEDTLS_MEMORY_ALIGN_MULTIPLE) {
        /* Adjust len first since buf is used in the computation */
        len -= MBEDTLS_MEMORY_ALIGN_MULTIPLE
               - (size_t) buf % MBEDTLS_MEMORY_ALIGN_MULTIPLE;
        buf += MBEDTLS_MEMORY_ALIGN_MULTIPLE
               - (size_t) buf % MBEDTLS_MEMORY_ALIGN_MULTIPLE;
    }

    memset(buf, 0, len);

    heap.buf = buf;
    heap.len = len;

    heap.first = (memory_header *) buf;
    heap.first->size = len - sizeof(memory_header);
    heap.first->magic1 = MAGIC1;
    heap.first->magic2 = MAGIC2;
    heap.first_free = heap.first;
}

void psaInt_mbedtls_memory_buffer_alloc_free(void)
{
    memset(&heap, 0, sizeof(buffer_alloc_ctx));
}
