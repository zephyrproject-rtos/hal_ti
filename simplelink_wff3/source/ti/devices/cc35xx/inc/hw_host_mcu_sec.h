/******************************************************************************
*  Filename:       hw_host_mcu_sec.h
*
*  Description:    Defines and prototypes for the HOST_MCU_SEC peripheral.
*
*  Copyright (c) 2023-2025, Texas Instruments Incorporated
*  All rights reserved.
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
*  3) Neither the name of the ORGANIZATION nor the names of its contributors may
*     be used to endorse or promote products derived from this software without
*     specific prior written permission.
*
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
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
#ifndef __HW_HOST_MCU_SEC_H__
#define __HW_HOST_MCU_SEC_H__
/*-------------------------------------------------------------------------------

This section defines the register offsets of the HOST_MCU_SEC component

--------------------------------------------------------------------------------- */

//Secure Software Interrupt
#define HOST_MCU_SEC_O_SSWIRQ2NS                                     0x00000000U

//Software Interrupt to CM3
#define HOST_MCU_SEC_O_SWIRQ2CM3                                     0x00000004U

//Software Interrupt to CM3
#define HOST_MCU_SEC_O_LCKUP                                         0x00000008U



/*-----------------------------------REGISTER------------------------------------
    Register name:       SSWIRQ2NS
    Offset name:         HOST_MCU_SEC_O_SSWIRQ2NS
    Relative address:    0x0
    Description:         Secure Software Interrupt
    Default Value:       0x00000000

        Field:           EN
        From..to bits:   0...7
        DefaultValue:    0x0
        Access type:     read-write
        Description:      Secure context of CM33 can use this register to interrupt non secure context of CM33.


*/
#define HOST_MCU_SEC_SSWIRQ2NS_EN_W                                  8U
#define HOST_MCU_SEC_SSWIRQ2NS_EN_M                                  0x000000FFU
#define HOST_MCU_SEC_SSWIRQ2NS_EN_S                                  0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       SWIRQ2CM3
    Offset name:         HOST_MCU_SEC_O_SWIRQ2CM3
    Relative address:    0x4
    Description:         Software Interrupt to CM3
    Default Value:       0x00000000

        Field:           EN
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:      Secure context of CM33 can use this register to interrupt CM3.


*/
#define HOST_MCU_SEC_SWIRQ2CM3_EN                                    0x00000001U
#define HOST_MCU_SEC_SWIRQ2CM3_EN_M                                  0x00000001U
#define HOST_MCU_SEC_SWIRQ2CM3_EN_S                                  0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       LCKUP
    Offset name:         HOST_MCU_SEC_O_LCKUP
    Relative address:    0x8
    Description:         Software Interrupt to CM3
    Default Value:       0x00000000

        Field:           VAL
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     The processor enters a lockup state if a fault occurs when it cannot be serviced or escalated. When
                         the processor is in lockup state, it does not execute any instructions.
                         The processor remains in lockup state until either:
                         * It is reset.
                         * Preemption by a higher priority exception occurs.
                         * It is halted by a debugger.

*/
#define HOST_MCU_SEC_LCKUP_VAL                                       0x00000001U
#define HOST_MCU_SEC_LCKUP_VAL_M                                     0x00000001U
#define HOST_MCU_SEC_LCKUP_VAL_S                                     0U

#endif /* __HW_HOST_MCU_SEC_H__*/
