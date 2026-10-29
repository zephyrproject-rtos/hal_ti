/******************************************************************************
*  Filename:       hw_dcache.h
*
*  Description:    Defines and prototypes for the DCACHE peripheral.
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
#ifndef __HW_DCACHE_H__
#define __HW_DCACHE_H__
/*-------------------------------------------------------------------------------

This section defines the register offsets of the DCACHE component

--------------------------------------------------------------------------------- */

//
#define DCACHE_O_MOD_VER                                             0x00000000U

//
#define DCACHE_O_CTRL                                                0x00000004U

//
#define DCACHE_O_STS                                                 0x00000008U

//
#define DCACHE_O_CAL                                                 0x00000010U

//
#define DCACHE_O_CAH                                                 0x00000018U

//
#define DCACHE_O_READ_COUNTER                                        0x00000040U

//
#define DCACHE_O_WRITE_COUNTER                                       0x00000044U

//When having OTFDE AHB error, Latch the address accessed by D-cache
#define DCACHE_O_ADDRESS_LATCH                                       0x00000048U

//CACHE_FSM_STATE
#define DCACHE_O_CACHE_FSM_STATE                                     0x0000004CU

//
#define DCACHE_O_IRQSTATUS_RAW                                       0x00000080U

//
#define DCACHE_O_IRQSTATUS_MSK                                       0x00000084U

//
#define DCACHE_O_IRQENABLE_SET                                       0x00000088U

//
#define DCACHE_O_IRQENABLE_CLR                                       0x0000008CU

//Flush and invalidates requests
#define DCACHE_O_CTRL1                                               0x000000C0U

//Flush and invalidates status
#define DCACHE_O_STATUS1                                             0x000000C4U



/*-----------------------------------REGISTER------------------------------------
    Register name:       MOD_VER
    Offset name:         DCACHE_O_MOD_VER
    Relative address:    0x0
    Description:
                        The Module and Version Register identifies the module identifier and revision of the L1 module.

    Default Value:       0x68800800

        Field:           MINOR_REVISION
        From..to bits:   0...5
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Minor Revision.

*/
#define DCACHE_MOD_VER_MINOR_REVISION_W                              6U
#define DCACHE_MOD_VER_MINOR_REVISION_M                              0x0000003FU
#define DCACHE_MOD_VER_MINOR_REVISION_S                              0U
/*

        Field:           CUSTOM_REVISION
        From..to bits:   6...7
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Custom Revision.

*/
#define DCACHE_MOD_VER_CUSTOM_REVISION_W                             2U
#define DCACHE_MOD_VER_CUSTOM_REVISION_M                             0x000000C0U
#define DCACHE_MOD_VER_CUSTOM_REVISION_S                             6U
/*

        Field:           MAJOR_REVISION
        From..to bits:   8...10
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Major Revision.

*/
#define DCACHE_MOD_VER_MAJOR_REVISION_W                              3U
#define DCACHE_MOD_VER_MAJOR_REVISION_M                              0x00000700U
#define DCACHE_MOD_VER_MAJOR_REVISION_S                              8U
/*

        Field:           RTL_VERSION
        From..to bits:   11...15
        DefaultValue:    0x1
        Access type:     read-only
        Description:     RTL Version.

*/
#define DCACHE_MOD_VER_RTL_VERSION_W                                 5U
#define DCACHE_MOD_VER_RTL_VERSION_M                                 0x0000F800U
#define DCACHE_MOD_VER_RTL_VERSION_S                                 11U
/*

        Field:           MODULE_ID
        From..to bits:   16...27
        DefaultValue:    0x880
        Access type:     read-only
        Description:     L1 module ID.

*/
#define DCACHE_MOD_VER_MODULE_ID_W                                   12U
#define DCACHE_MOD_VER_MODULE_ID_M                                   0x0FFF0000U
#define DCACHE_MOD_VER_MODULE_ID_S                                   16U
/*

        Field:           BU
        From..to bits:   28...29
        DefaultValue:    0x2
        Access type:     read-only
        Description:     Module Business Unit

*/
#define DCACHE_MOD_VER_BU_W                                          2U
#define DCACHE_MOD_VER_BU_M                                          0x30000000U
#define DCACHE_MOD_VER_BU_S                                          28U
/*

        Field:           SCHEME
        From..to bits:   30...31
        DefaultValue:    0x1
        Access type:     read-only
        Description:     Module Scheme

*/
#define DCACHE_MOD_VER_SCHEME_W                                      2U
#define DCACHE_MOD_VER_SCHEME_M                                      0xC0000000U
#define DCACHE_MOD_VER_SCHEME_S                                      30U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CTRL
    Offset name:         DCACHE_O_CTRL
    Relative address:    0x4
    Description:
                        The control register defines the size of the remote cache data storage memory to use and whether the L1 is enabled.

    Default Value:       0x40000000

        Field:           RENABLE
        From..to bits:   30...30
        DefaultValue:    0x1
        Access type:     read-write
        Description:     The ~irenable field determines if half the cache space is RAM or cache. #br# 0: No RAM 64K of cache#br# 1: RAM 32K of cache, 32K of RAM. This field is write protected when ~icenable is set or the t_cfg_lock_ipcfg input is high.

*/
#define DCACHE_CTRL_RENABLE                                          0x40000000U
#define DCACHE_CTRL_RENABLE_M                                        0x40000000U
#define DCACHE_CTRL_RENABLE_S                                        30U
/*

        Field:           CENABLE
        From..to bits:   31...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     The ~icenable field determines whether the L1 configuration is enabled or not.#br# 0: Disabled#br# 1: Enabled #br# This field is write protected when the t_cfg_lock_ipcfg input is high.

*/
#define DCACHE_CTRL_CENABLE                                          0x80000000U
#define DCACHE_CTRL_CENABLE_M                                        0x80000000U
#define DCACHE_CTRL_CENABLE_S                                        31U


/*-----------------------------------REGISTER------------------------------------
    Register name:       STS
    Offset name:         DCACHE_O_STS
    Relative address:    0x8
    Description:
                        The Status register displays the state of the L1 module

    Default Value:       0x00000000

        Field:           OK_TO_GO
        From..to bits:   31...31
        DefaultValue:    0x0
        Access type:     read-only
        Description:     The ~iok_to_go status bit indicates the Tag/LRU Ram has been initialized and the cache is in an operable state.

*/
#define DCACHE_STS_OK_TO_GO                                          0x80000000U
#define DCACHE_STS_OK_TO_GO_M                                        0x80000000U
#define DCACHE_STS_OK_TO_GO_S                                        31U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CAL
    Offset name:         DCACHE_O_CAL
    Relative address:    0x10
    Description:
                        The L1 Cache Address Low Register defines start of the L1 cacheable space. The L1 cache can cache up to a range of 8MB of of the target Flash as defined by CAL&gt;=CachedRange&lt;=CAH. This register is write protected when ~icenable is set or the t_cfg_lock_ipcfg input is high.

    Default Value:       0x00000000

        Field:           ADDR_LO
        From..to bits:   12...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     The ~iaddr_lo defines the L1 low address[31:12] for the L1 to cache. The remaining bits 10:0 are assumed to be zero.

*/
#define DCACHE_CAL_ADDR_LO_W                                         20U
#define DCACHE_CAL_ADDR_LO_M                                         0xFFFFF000U
#define DCACHE_CAL_ADDR_LO_S                                         12U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CAH
    Offset name:         DCACHE_O_CAH
    Relative address:    0x18
    Description:
                        The L1 Cache Address High Register defines end of the L1 cacheable space. The L1 cache can cache up to a range of 8MB of of the target Flash as defined by CAL&gt;=CachedRange&lt;=CAH. This register is write protected when ~icenable is set or the t_cfg_lock_ipcfg input is high.

    Default Value:       0x00000000

        Field:           ADDR_HI
        From..to bits:   12...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     The ~iaddr_hi defines the L1 high address[31:12] for the L1 to cache. The remaining bits 10:0 are assumed to be ones.

*/
#define DCACHE_CAH_ADDR_HI_W                                         20U
#define DCACHE_CAH_ADDR_HI_M                                         0xFFFFF000U
#define DCACHE_CAH_ADDR_HI_S                                         12U


/*-----------------------------------REGISTER------------------------------------
    Register name:       READ_COUNTER
    Offset name:         DCACHE_O_READ_COUNTER
    Relative address:    0x40
    Description:
                        The L1 HIT Counter register holds the number of L1 Hits to the internal cache.

    Default Value:       0x00000000

        Field:           READ_MISS_COUNTER
        From..to bits:   0...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     The miss Counts the number of misses to the L1 cache.
                         Writing zero to this register will clear its contents.

                         When one reach the max, the rest of the counters are halted too.

*/
#define DCACHE_READ_COUNTER_READ_MISS_COUNTER_W                      12U
#define DCACHE_READ_COUNTER_READ_MISS_COUNTER_M                      0x00000FFFU
#define DCACHE_READ_COUNTER_READ_MISS_COUNTER_S                      0U
/*

        Field:           READ_HIT_COUNTER
        From..to bits:   12...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     The hit Counts the number of hits to the L1 cache.
                         Writing zero to this register will clear its contents

                         When one reach the max, the rest of the counters are halted too.

*/
#define DCACHE_READ_COUNTER_READ_HIT_COUNTER_W                       20U
#define DCACHE_READ_COUNTER_READ_HIT_COUNTER_M                       0xFFFFF000U
#define DCACHE_READ_COUNTER_READ_HIT_COUNTER_S                       12U


/*-----------------------------------REGISTER------------------------------------
    Register name:       WRITE_COUNTER
    Offset name:         DCACHE_O_WRITE_COUNTER
    Relative address:    0x44
    Description:
                        The L1 MISS Counter register holds the number of L1 Misses to the internal cache.

    Default Value:       0x00000000

        Field:           WRITE_MISS_COUNTER
        From..to bits:   0...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     The miss Counts the number of misses to the L1 cache.
                         Writing zero to this register will clear its contents.

                         When one reach the max, the rest of the counters are halted too

*/
#define DCACHE_WRITE_COUNTER_WRITE_MISS_COUNTER_W                    12U
#define DCACHE_WRITE_COUNTER_WRITE_MISS_COUNTER_M                    0x00000FFFU
#define DCACHE_WRITE_COUNTER_WRITE_MISS_COUNTER_S                    0U
/*

        Field:           WRITE_HIT_COUNTER
        From..to bits:   12...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     The hit Counts the number of hits to the L1 cache.
                         Writing zero to this register will clear its contents.

                         When one reach the max, the rest of the counters are halted too.

*/
#define DCACHE_WRITE_COUNTER_WRITE_HIT_COUNTER_W                     20U
#define DCACHE_WRITE_COUNTER_WRITE_HIT_COUNTER_M                     0xFFFFF000U
#define DCACHE_WRITE_COUNTER_WRITE_HIT_COUNTER_S                     12U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ADDRESS_LATCH
    Offset name:         DCACHE_O_ADDRESS_LATCH
    Relative address:    0x48
    Description:         When having OTFDE AHB error, Latch the address accessed by D-cache
    Default Value:       0x00000000

        Field:           ADDRESS_LATCH
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     When D-cache receive AHB error from the OTFDE it should latch the address accessed by D-cache.
                         (OTFDE generates an error for write only)

                         Writing zero to this register will clear its contents.

*/
#define DCACHE_ADDRESS_LATCH_ADDRESS_LATCH_W                         32U
#define DCACHE_ADDRESS_LATCH_ADDRESS_LATCH_M                         0xFFFFFFFFU
#define DCACHE_ADDRESS_LATCH_ADDRESS_LATCH_S                         0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CACHE_FSM_STATE
    Offset name:         DCACHE_O_CACHE_FSM_STATE
    Relative address:    0x4C
    Description:
    Default Value:       NA

        Field:           FSM_STATE
        From..to bits:   0...4
        DefaultValue:    NA
        Access type:     read-only
        Description:     Dcache current FSM state

                         WIDLE    = 5'd0; - No access to D-cache
                         WRAMWR   = 5'd1; - Data RAM Write
                         WRAMRD   = 5'd2; - Data RAM Read
                         WCREADT  = 5'd4; - Read Hit
                         WCREADC  = 5'd5; - Read Miss
                         WCWRITET = 5'd6; - Write Hit
                         EVICT    = 5'd7; -Write back to PSRAM
                         WR_ALLOC = 5'd8; - Write Allocate in write miss
                         RD_WA = 5'd9; - Word aligned read for a byte aligned read
                         WD = 5'd10; - Writing data to PSRAM
                         RDATA_CACHE = 5'd3; Reading data RAM for eviction
                         DEC_DIR = 5'd11; - Deciding direction
                         RDATA_CACHE_FLUSH = 5'd12; Reading data from data RAM for flush
                         RD_SET     = 5'd13; Reading TAG & MRU
                         DET_GRANT  = 5'd14;  Detecting the granted way to evict
                         EVICT_FLUSH = 5'd15; Eviction during Flush
                         WD_DEBUG = 5'd16; Writing data to PSRAM during a debugger access

*/
#define DCACHE_CACHE_FSM_STATE_FSM_STATE_W                           5U
#define DCACHE_CACHE_FSM_STATE_FSM_STATE_M                           0x0000001FU
#define DCACHE_CACHE_FSM_STATE_FSM_STATE_S                           0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       IRQSTATUS_RAW
    Offset name:         DCACHE_O_IRQSTATUS_RAW
    Relative address:    0x80
    Description:
                        The Interrupt Raw Status Register holds the raw status of the L1 error interrupts.
                        Note: Read to the field of this register gives raw status of corresponding interrupt. S/W can set corresponding interrupt field for diagnostic purposes.

    Default Value:       0x00000000

        Field:           LOCK_CFG_WR
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     The ~ilock_cfg_wr bit indicates a write to a locked configuration register has occured. Write 1 to set the ~ilock_cfg_wr status for diagnostic purposes. Writing a 0 has no effect.

*/
#define DCACHE_IRQSTATUS_RAW_LOCK_CFG_WR                             0x00000002U
#define DCACHE_IRQSTATUS_RAW_LOCK_CFG_WR_M                           0x00000002U
#define DCACHE_IRQSTATUS_RAW_LOCK_CFG_WR_S                           1U


/*-----------------------------------REGISTER------------------------------------
    Register name:       IRQSTATUS_MSK
    Offset name:         DCACHE_O_IRQSTATUS_MSK
    Relative address:    0x84
    Description:
                        The Interrupt Masked Status Register holds the masked status for the L1 error interrupts. Writing to this register will EOI the interrupt, that is if another interrupt is pending, a new pulse interrupt will be generated.
                        Note: Read to the field of this register gives masked status of corresponding interrupt. Writing 1 to the field of this register clears corresponding interrupt.

    Default Value:       0x00000000

        Field:           LOCK_CFG_WR
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     The ~ilock_cfg_wr bit indicates a write to a locked configuration register has occured. Write 1 to clear the ~ilock_cfg_wr status after interrupt has been serviced (raw status gets cleared, i.e. even if not enabled). Writing a 0 has no effect to this field.

*/
#define DCACHE_IRQSTATUS_MSK_LOCK_CFG_WR                             0x00000002U
#define DCACHE_IRQSTATUS_MSK_LOCK_CFG_WR_M                           0x00000002U
#define DCACHE_IRQSTATUS_MSK_LOCK_CFG_WR_S                           1U


/*-----------------------------------REGISTER------------------------------------
    Register name:       IRQENABLE_SET
    Offset name:         DCACHE_O_IRQENABLE_SET
    Relative address:    0x88
    Description:
                        The Interrupt Enable Set Register holds the interrupt enable status of the L1 error interrupts.
                        Note:Writing 1 to field of this register will not mask the corresponding interrupt. IRQSTATUS_RAW and IRQSTATUS_MSK status field gives the same status.

    Default Value:       0x00000000

        Field:           EN_LOCK_CFG_WR
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Interrupt Enable Set for ~ilock_cfg_wr error bit. Writing a 1 will enable the interrupt, and set this bit as well as the corresponding Interrupt Enable Clear Register. Writing a 0 has no effect.

*/
#define DCACHE_IRQENABLE_SET_EN_LOCK_CFG_WR                          0x00000002U
#define DCACHE_IRQENABLE_SET_EN_LOCK_CFG_WR_M                        0x00000002U
#define DCACHE_IRQENABLE_SET_EN_LOCK_CFG_WR_S                        1U


/*-----------------------------------REGISTER------------------------------------
    Register name:       IRQENABLE_CLR
    Offset name:         DCACHE_O_IRQENABLE_CLR
    Relative address:    0x8C
    Description:
                        The Interrupt Enable Clear Register holds the interrupt enable status of the L1 error interrupts.
                        Note:Writing 1 to field of this register masks the corresponding interrupt. IRQSTATUS_RAW and IRQSTATUS_MSK status field gives the raw status and masked status respectively

    Default Value:       0x00000000

        Field:           EN_LOCK_CFG_WR
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Interrupt Enable Clear for ~ilock_cfg_wr error bit. Writing a 1 will disable the interrupt, and clear this bit as well as the corresponding Interrupt Enable Set Register. Writing a 0 has no effect.

*/
#define DCACHE_IRQENABLE_CLR_EN_LOCK_CFG_WR                          0x00000002U
#define DCACHE_IRQENABLE_CLR_EN_LOCK_CFG_WR_M                        0x00000002U
#define DCACHE_IRQENABLE_CLR_EN_LOCK_CFG_WR_S                        1U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CTRL1
    Offset name:         DCACHE_O_CTRL1
    Relative address:    0xC0
    Description:         Flush and invalidates requests
    Default Value:       0x00000000

        Field:           INVALIDATE
        From..to bits:   30...30
        DefaultValue:    0x0
        Access type:     read-write
        Description:     0x0 - Do nothing
                         0x1 - Invalidate
                         This bit is self cleared when invalidate completed


*/
#define DCACHE_CTRL1_INVALIDATE                                      0x40000000U
#define DCACHE_CTRL1_INVALIDATE_M                                    0x40000000U
#define DCACHE_CTRL1_INVALIDATE_S                                    30U
/*

        Field:           FLUSH
        From..to bits:   31...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     0x0 - Do nothing
                         0x1 - Flush
                         The bit is self cleared when flush completed

*/
#define DCACHE_CTRL1_FLUSH                                           0x80000000U
#define DCACHE_CTRL1_FLUSH_M                                         0x80000000U
#define DCACHE_CTRL1_FLUSH_S                                         31U


/*-----------------------------------REGISTER------------------------------------
    Register name:       STATUS1
    Offset name:         DCACHE_O_STATUS1
    Relative address:    0xC4
    Description:         Flush and invalidates status

    Default Value:       0x00000000

        Field:           FLUSH_FAIL
        From..to bits:   29...29
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This bit indicates that Flush has failed
                         ( Bit is cleared when Flush request bit is asserted )


*/
#define DCACHE_STATUS1_FLUSH_FAIL                                    0x20000000U
#define DCACHE_STATUS1_FLUSH_FAIL_M                                  0x20000000U
#define DCACHE_STATUS1_FLUSH_FAIL_S                                  29U
/*

        Field:           INVALIDATE_STATUS
        From..to bits:   30...30
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This bit indicates that invalidate has been completed
                         ( Bit is cleared when flush request bit is asserted )

*/
#define DCACHE_STATUS1_INVALIDATE_STATUS                             0x40000000U
#define DCACHE_STATUS1_INVALIDATE_STATUS_M                           0x40000000U
#define DCACHE_STATUS1_INVALIDATE_STATUS_S                           30U
/*

        Field:           FLUSH_STATUS
        From..to bits:   31...31
        DefaultValue:    0x0
        Access type:     read-only
        Description:     This bit indicates that Flush as been completed
                         ( Bit is cleared when Flush request bit is asserted )

*/
#define DCACHE_STATUS1_FLUSH_STATUS                                  0x80000000U
#define DCACHE_STATUS1_FLUSH_STATUS_M                                0x80000000U
#define DCACHE_STATUS1_FLUSH_STATUS_S                                31U

#endif /* __HW_DCACHE_H__*/
