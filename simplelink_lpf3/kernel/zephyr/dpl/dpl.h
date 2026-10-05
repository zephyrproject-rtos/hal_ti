/*
 * Copyright (c) 2024, Texas Instruments Incorporated
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <errno.h>
#define MEM_ALIGN (sizeof(uint32_t))
#define DPL_NO_WAIT (0)
#define DPL_WAIT_FOREVER (~0)

k_timeout_t dpl_to_zephyr_timeout(uint32_t timeout);
