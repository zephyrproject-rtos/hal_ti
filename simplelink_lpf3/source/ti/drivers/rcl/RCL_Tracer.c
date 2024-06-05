/*
 * Copyright (c) 2022-2023, Texas Instruments Incorporated
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
 *  ======== RCL_Tracer.c ========
 */


/*
 *  ======== RCL_Tracer_enable ========
 */
void __attribute__((weak)) RCL_Tracer_enable(void)
{
    /* Internal TI use: Enables RF Tracer */
}

/*
 *  ======== RCL_Tracer_disable ========
 */
void __attribute__((weak)) RCL_Tracer_disable(void)
{
    /* Internal TI use: Disables RF Tracer */
}

/*
 *  ======== RCL_Tracer_wakeup ========
 */
void __attribute__((weak)) RCL_Tracer_wakeup(void)
{
    /* Internal TI use: Re-enables RF Tracer after wakeup from standby*/
}

/*
 *  ======== RCL_Tracer_standby ========
 */
void __attribute__((weak)) RCL_Tracer_standby(void)
{
    /* Internal TI use: Prepares RF Tracer for standby */
}

/*
 *  ======== RCL_GPIO_enable ========
 */
void __attribute__((weak)) RCL_GPIO_enable(void)
{
    /* Internal TI use: Enables RCL GPIOs */
}

/*
 *  ======== RCL_GPIO_disable ========
 */
void __attribute__((weak)) RCL_GPIO_disable(void)
{
    /* Internal TI use: Disables RCL GPIOs */
}
