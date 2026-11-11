/*
 * Copyright (c) 2024, Texas Instruments Incorporated
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <zephyr/kernel.h>

#include "dpl.h"

/* Generic function to convert from DPL defines to Zephyr defines and types */
k_timeout_t dpl_to_zephyr_timeout(uint32_t timeout)
{
    switch (timeout)
    {
        case DPL_NO_WAIT:
            return K_NO_WAIT;
        case DPL_WAIT_FOREVER:
            return K_FOREVER;
        default:
            return K_TICKS(timeout);
    }
}
