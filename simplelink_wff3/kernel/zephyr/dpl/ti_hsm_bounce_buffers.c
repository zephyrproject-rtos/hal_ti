/*
 * Copyright (c) 2026 Conclusive Engineering Sp. z o.o.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <ti/devices/DeviceFamily.h>
#include <ti/drivers/cryptoutils/hsm/HSMXXF3.h>

#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC35XX)
__attribute__((weak)) HSMXXF3_BounceBuffer HSMXXF3_inputBounce = {
    .size = 0,
    .buffer = NULL,
};

__attribute__((weak)) HSMXXF3_BounceBuffer HSMXXF3_outputBounce = {
    .size = 0,
    .buffer = NULL,
};

__attribute__((weak)) HSMXXF3_BounceBuffer HSMXXF3_auxBounce = {
    .size = 0,
    .buffer = NULL,
};
#endif
