/*
 * Copyright (c) 2024, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 */

#include <ti/drivers/power/PowerCC26X2.h>
#include <ti/drivers/power/PowerCC26XX.h>

/* Default PowerCC26X2 Configuration */
const PowerCC26X2_Config PowerCC26X2_config = {
    .policyInitFxn = NULL,
    .policyFxn = PowerCC26XX_doWFI,
    .calibrateFxn = PowerCC26XX_noCalibrate,
    .enablePolicy = false,
    .calibrateRCOSC_LF = false,
    .calibrateRCOSC_HF = false,
    .enableTCXOFxn = NULL,
};

/* Stub implementations for scheduler functions (no-op for Zephyr) */
void PowerCC26XX_schedulerDisable(void)
{
    /* Zephyr handles scheduling, this is a no-op */
}

void PowerCC26XX_schedulerRestore(void)
{
    /* Zephyr handles scheduling, this is a no-op */
}
