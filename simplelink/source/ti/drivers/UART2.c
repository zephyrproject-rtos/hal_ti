/*
 * Copyright (c) 2019, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/*
 *  ======== UART2.c ========
 */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include <ti/drivers/dpl/HwiP.h>
#include <ti/drivers/UART2.h>

extern const UART2_Config UART2_config[];
extern const uint_least8_t UART2_count;

/* Default UART parameters structure */
const UART2_Params UART2_defaultParams = {
    UART2_Mode_BLOCKING,     /* readMode */
    UART2_Mode_BLOCKING,     /* writeMode */
    NULL,                    /* readCallback */
    NULL,                    /* writeCallback */
    UART2_ReadReturnMode_FULL, /* readReturnMode */
    115200,                  /* baudRate */
    UART2_DataLen_8,         /* dataLength */
    UART2_StopBits_1,        /* stopBits */
    UART2_Parity_NONE,       /* parityType */
    NULL                     /* userArg */
};

/*
 *  ======== UART2_close ========
 */

void __attribute__((weak)) UART2_close(UART2_Handle handle)
{
    handle->fxnTablePtr->closeFxn(handle);
}

/*
 *  ======== UART2_flushRx ========
 */
void __attribute__((weak)) UART2_flushRx(UART2_Handle handle)
{
    handle->fxnTablePtr->flushRxFxn(handle);
}

/*
 *  ======== UART2_open ========
 */
UART2_Handle __attribute__((weak)) UART2_open(uint_least8_t index,
        UART2_Params *params)
{
    UART2_Handle handle = NULL;

    if (index < UART2_count) {
        /* If params are NULL use defaults */
        if (params == NULL) {
            params = (UART2_Params *) &UART2_defaultParams;
        }

        /* Get handle for this driver instance */
        handle = UART2_config[index].fxnTablePtr->openFxn(index, params);
    }

    return (handle);
}

/*
 *  ======== UART2_Params_init ========
 */
void UART2_Params_init(UART2_Params *params)
{
    *params = UART2_defaultParams;
}

/*
 *  ======== UART2_read ========
 */
int_fast16_t __attribute__((weak)) UART2_read(UART2_Handle handle, void *buffer,
        size_t size, size_t *bytesRead)
{
    return (handle->fxnTablePtr->readFxn(handle, buffer, size,
            bytesRead, UART2_WAIT_FOREVER));
}

/*
 *  ======== UART2_readTimeout ========
 */
int_fast16_t __attribute__((weak)) UART2_readTimeout(UART2_Handle handle,
        void *buffer, size_t size, size_t *bytesRead, uint32_t timeout)
{
    return (handle->fxnTablePtr->readFxn(handle, buffer, size,
            bytesRead, timeout));
}

/*
 *  ======== UART2_readCancel ========
 */
void __attribute__((weak)) UART2_readCancel(UART2_Handle handle)
{
    handle->fxnTablePtr->readCancelFxn(handle);
}

/*
 *  ======== UART2_write ========
 */
int_fast16_t __attribute__((weak)) UART2_write(UART2_Handle handle,
        const void *buffer, size_t size, size_t *bytesWritten)
{
    return (handle->fxnTablePtr->writeFxn(handle, buffer, size,
                    bytesWritten, UART2_WAIT_FOREVER));
}

/*
 *  ======== UART2_write ========
 */
int_fast16_t __attribute__((weak)) UART2_writeTimeout(UART2_Handle handle,
        const void *buffer, size_t size, size_t *bytesWritten,
        uint32_t timeout)
{
    return (handle->fxnTablePtr->writeFxn(handle, buffer, size,
                    bytesWritten, timeout));
}

/*
 *  ======== UART2_writeCancel ========
 */
void __attribute__((weak)) UART2_writeCancel(UART2_Handle handle)
{
    handle->fxnTablePtr->writeCancelFxn(handle);
}
