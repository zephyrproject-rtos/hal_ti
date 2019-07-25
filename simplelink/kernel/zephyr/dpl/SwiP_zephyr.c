/*
 * Copyright (c) 2019, Texas Instruments Incorporated
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>

#include <ti/drivers/dpl/SwiP.h>


/*
 *  ======== SwiP_disable ========
 */
uintptr_t SwiP_disable(void)
{
    k_sched_lock();

    return 0;
}

/*
 *  ======== SwiP_restore ========
 */
void SwiP_restore(uintptr_t key)
{
    ARG_UNUSED(key);
    k_sched_unlock();
}
