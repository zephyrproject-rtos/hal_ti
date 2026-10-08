/******************************************************************************
*  Filename:       hw_sysresources.h
*
*  Description:    Defines and prototypes for the SYSRESOURCES peripheral.
*
*  Copyright (c) 2023, Texas Instruments Incorporated
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
#ifndef __HW_SYSRESOURCES_H__
#define __HW_SYSRESOURCES_H__
/*-------------------------------------------------------------------------------

This section defines the register offsets of the SYSRESOURCES component

--------------------------------------------------------------------------------- */

//SYSTIM_CTRL
#define SYSRESOURCES_O_SYSTIM_CTRL                                   0x00000008U

//MEMSS_GENERAL
#define SYSRESOURCES_O_MEMSS_GENERAL                                 0x00000400U

//MEMSS_BUS_FAULT_RAW_STATUS
#define SYSRESOURCES_O_MEMSS_BUS_FAULT_RAW_STATUS                    0x00000404U



/*-----------------------------------REGISTER------------------------------------
    Register name:       SYSTIM_CTRL
    Offset name:         SYSRESOURCES_O_SYSTIM_CTRL
    Relative address:    0x8
    Description:
    Default Value:       0x00000000

        Field:           MEM_SYSTIM_ENCLK
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     '1' - enable the reqeusets for the systim clk

*/
#define SYSRESOURCES_SYSTIM_CTRL_MEM_SYSTIM_ENCLK                    0x00000001U
#define SYSRESOURCES_SYSTIM_CTRL_MEM_SYSTIM_ENCLK_M                  0x00000001U
#define SYSRESOURCES_SYSTIM_CTRL_MEM_SYSTIM_ENCLK_S                  0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       MEMSS_GENERAL
    Offset name:         SYSRESOURCES_O_MEMSS_GENERAL
    Relative address:    0x400
    Description:
    Default Value:       0x00000000

        Field:           MEM_STRV_CNTR_VAL
        From..to bits:   0...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     HOST to config how long writing to mailbox can be delayed

*/
#define SYSRESOURCES_MEMSS_GENERAL_MEM_STRV_CNTR_VAL_W               3U
#define SYSRESOURCES_MEMSS_GENERAL_MEM_STRV_CNTR_VAL_M               0x00000007U
#define SYSRESOURCES_MEMSS_GENERAL_MEM_STRV_CNTR_VAL_S               0U
/*

        Field:           MEM_MEMSS_BUS_FAULT_MASK
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     '1' - Mask
                         '0' - Do not mask

*/
#define SYSRESOURCES_MEMSS_GENERAL_MEM_MEMSS_BUS_FAULT_MASK          0x00000008U
#define SYSRESOURCES_MEMSS_GENERAL_MEM_MEMSS_BUS_FAULT_MASK_M        0x00000008U
#define SYSRESOURCES_MEMSS_GENERAL_MEM_MEMSS_BUS_FAULT_MASK_S        3U
/*

        Field:           MEMSS_BUS_FAULT_STATUS_MASKED
        From..to bits:   4...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     '1' - Mask
                         '0' - Do not mask

*/
#define SYSRESOURCES_MEMSS_GENERAL_MEMSS_BUS_FAULT_STATUS_MASKED_W   3U
#define SYSRESOURCES_MEMSS_GENERAL_MEMSS_BUS_FAULT_STATUS_MASKED_M   0x00000070U
#define SYSRESOURCES_MEMSS_GENERAL_MEMSS_BUS_FAULT_STATUS_MASKED_S   4U


/*-----------------------------------REGISTER------------------------------------
    Register name:       MEMSS_BUS_FAULT_RAW_STATUS
    Offset name:         SYSRESOURCES_O_MEMSS_BUS_FAULT_RAW_STATUS
    Relative address:    0x404
    Description:
    Default Value:       0x00000000

        Field:           MEMSS_BUS_FAULT_STATUS_RAW_RDCL
        From..to bits:   0...2
        DefaultValue:    0x0
        Access type:     read-only
        Description:     HOST to config how long writing to mailbox can be delayed

*/
#define SYSRESOURCES_MEMSS_BUS_FAULT_RAW_STATUS_MEMSS_BUS_FAULT_STATUS_RAW_RDCL_W 3U
#define SYSRESOURCES_MEMSS_BUS_FAULT_RAW_STATUS_MEMSS_BUS_FAULT_STATUS_RAW_RDCL_M 0x00000007U
#define SYSRESOURCES_MEMSS_BUS_FAULT_RAW_STATUS_MEMSS_BUS_FAULT_STATUS_RAW_RDCL_S 0U

#endif /* __HW_SYSRESOURCES_H__*/
