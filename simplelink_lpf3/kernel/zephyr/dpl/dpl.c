/*
 * Copyright (c) 2024, Texas Instruments Incorporated
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <zephyr/kernel.h>

#include <ti/drivers/dpl/ClockP.h>

#include "dpl.h"

/*
 * Generic function to convert from DPL defines to Zephyr defines and types.
 * DPL timeouts are given in ClockP ticks, which are not Zephyr kernel ticks.
 */
k_timeout_t dpl_to_zephyr_timeout(uint32_t timeout)
{
    switch (timeout)
    {
        case DPL_NO_WAIT:
            return K_NO_WAIT;
        case DPL_WAIT_FOREVER:
            return K_FOREVER;
        default:
            return K_USEC((uint64_t)timeout * ClockP_getSystemTickPeriod());
    }
}
