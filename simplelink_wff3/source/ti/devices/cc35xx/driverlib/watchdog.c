/******************************************************************************
 *  Filename:       watchdog.c
 *
 *  Description:    Driver for the Watchdog capabilities of the ELPTMR
 *                  peripheral.
 *
 *  Copyright (c) 2025 Texas Instruments Incorporated
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *
 *  1) Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *
 *  2) Redistributions in binary form must reproduce the above copyright notice,
 *     this list of conditions and the following disclaimer in the documentation
 *     and/or other materials provided with the distribution.
 *
 *  3) Neither the name of the copyright holder nor the names of its
 *     contributors may be used to endorse or promote products derived from this
 *     software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 *  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************/

#include "watchdog.h"

//*****************************************************************************
//
// Sequence to start the timer
//
//*****************************************************************************
void WatchdogStartSequence(void)
{
    /* The stop bit (RST) has higher priority than the start bit (SET).
     * Therefore, it is necessary to clear the stop bit before setting the start
     * bit.
     */
    HWREG(HOSTMCU_AON_BASE + HOSTMCU_AON_O_ELPTMREN) &= ~HOSTMCU_AON_ELPTMREN_ELPTMRRST;

    /* Set the timer back to 0 */
    WatchdogReset();

    /* Start the timer and wait until the timer is counting. Waiting is needed
     * to ensure synchronization between domains.
     */
    HWREG(HOSTMCU_AON_BASE + HOSTMCU_AON_O_ELPTMREN) |= HOSTMCU_AON_ELPTMREN_ELPTMRSET;
    WatchdogWaitUntilEnabled();

    /* Clear the start bit to prepare it for the next sequence because this bit
     * is not a pulse (doesn't reset automatically).
     */
    HWREG(HOSTMCU_AON_BASE + HOSTMCU_AON_O_ELPTMREN) &= ~HOSTMCU_AON_ELPTMREN_ELPTMRSET;
}

//*****************************************************************************
//
// Sequence to stop the timer
//
//*****************************************************************************
void WatchdogStopSequence(void)
{
    /* Stop the timer and wait until it is halted. Waiting is needed to ensure
     * synchronization between domains.
     */
    HWREG(HOSTMCU_AON_BASE + HOSTMCU_AON_O_ELPTMREN) |= HOSTMCU_AON_ELPTMREN_ELPTMRRST;
    WatchdogWaitUntilDisabled();
}
