/******************************************************************************
*  Filename:       hw_icache.h
*
*  Description:    Defines and prototypes for the ICACHE peripheral.
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
#ifndef __HW_ICACHE_H__
#define __HW_ICACHE_H__
/*-------------------------------------------------------------------------------

This section defines the register offsets of the ICACHE component

--------------------------------------------------------------------------------- */

//The Module and Version Register identifies the module identifier and revision of the icache module
#define ICACHE_O_MOD_VERSION                                         0x00000000U

//The control register defines the size of the remote cache data storage memory to use and whether the icache controller is enabled
#define ICACHE_O_CTRL                                                0x00000004U

//The Status register displays the state of the icache controller
#define ICACHE_O_STATUS                                              0x00000008U

// The Cache Address Low Register defines start of the cacheable space
#define ICACHE_O_CACHE_ADDRESS_LOW                                   0x00000010U

// The L1 Cache Address High Register defines end of the L1 cacheable space
#define ICACHE_O_CACHE_ADDRESS_HIGH                                  0x00000018U

// The RAM Address register defines the upper 17 bits of address for the RAM when renable is set
#define ICACHE_O_REGISTER_ADDRESS                                    0x00000020U

// The HIT Counter register holds the number of cache Hits to the internal cache
#define ICACHE_O_HIT_COUNTER                                         0x00000040U

//The MISS Counter register holds the number of cache misses to the internal cache
#define ICACHE_O_MISS_COUNTER                                        0x00000044U

// The Interrupt Raw Status Register holds the raw status of the icache error interrupts
#define ICACHE_O_IRQ_STATUS_RAW                                      0x00000080U

//The Interrupt Masked Status Register holds the masked status for the icache error interrupts
#define ICACHE_O_IRQ_STATUS_MASK                                     0x00000084U

//The Interrupt Enable Set Register holds the interrupt enable status of the icache error interrupts
#define ICACHE_O_IRQ_ENABLE_SET                                      0x00000088U

//The Interrupt Enable Clear Register holds the interrupt enable status of the icache error interrupts
#define ICACHE_O_IRQ_ENABLE_CLR                                      0x0000008CU



/*-----------------------------------REGISTER------------------------------------
    Register name:       MOD_VERSION
    Offset name:         ICACHE_O_MOD_VERSION
    Relative address:    0x0
    Description:         The Module and Version Register identifies the module identifier and revision of the icache module.
    Default Value:       0x00000000

        Field:           MINOR_REVISION
        From..to bits:   0...5
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Minor revision

*/
#define ICACHE_MOD_VERSION_MINOR_REVISION_W                          6U
#define ICACHE_MOD_VERSION_MINOR_REVISION_M                          0x0000003FU
#define ICACHE_MOD_VERSION_MINOR_REVISION_S                          0U
/*

        Field:           CUSTOM_REVISION
        From..to bits:   6...7
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Custom Revision

*/
#define ICACHE_MOD_VERSION_CUSTOM_REVISION_W                         2U
#define ICACHE_MOD_VERSION_CUSTOM_REVISION_M                         0x000000C0U
#define ICACHE_MOD_VERSION_CUSTOM_REVISION_S                         6U
/*

        Field:           MAJOR_REVISION
        From..to bits:   8...10
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Major Revision

*/
#define ICACHE_MOD_VERSION_MAJOR_REVISION_W                          3U
#define ICACHE_MOD_VERSION_MAJOR_REVISION_M                          0x00000700U
#define ICACHE_MOD_VERSION_MAJOR_REVISION_S                          8U
/*

        Field:           RTL_VERSION
        From..to bits:   11...15
        DefaultValue:    0x0
        Access type:     read-only
        Description:      RTL version

*/
#define ICACHE_MOD_VERSION_RTL_VERSION_W                             5U
#define ICACHE_MOD_VERSION_RTL_VERSION_M                             0x0000F800U
#define ICACHE_MOD_VERSION_RTL_VERSION_S                             11U
/*

        Field:           MODULE_ID
        From..to bits:   16...27
        DefaultValue:    0x0
        Access type:     read-only
        Description:      Module ID

*/
#define ICACHE_MOD_VERSION_MODULE_ID_W                               12U
#define ICACHE_MOD_VERSION_MODULE_ID_M                               0x0FFF0000U
#define ICACHE_MOD_VERSION_MODULE_ID_S                               16U
/*

        Field:           BU
        From..to bits:   28...29
        DefaultValue:    0x0
        Access type:     read-only
        Description:      Module Business Unit

*/
#define ICACHE_MOD_VERSION_BU_W                                      2U
#define ICACHE_MOD_VERSION_BU_M                                      0x30000000U
#define ICACHE_MOD_VERSION_BU_S                                      28U
/*

        Field:           SCHEME
        From..to bits:   30...31
        DefaultValue:    0x0
        Access type:     read-only
        Description:      Module Scheme

*/
#define ICACHE_MOD_VERSION_SCHEME_W                                  2U
#define ICACHE_MOD_VERSION_SCHEME_M                                  0xC0000000U
#define ICACHE_MOD_VERSION_SCHEME_S                                  30U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CTRL
    Offset name:         ICACHE_O_CTRL
    Relative address:    0x4
    Description:         The control register defines the size of the remote cache data storage memory to use and whether the icache controller is enabled.
    Default Value:       NA

        Field:           MEM_RENABLE
        From..to bits:   30...30
        DefaultValue:    NA
        Access type:     read-write
        Description:     .

*/
#define ICACHE_CTRL_MEM_RENABLE                                      0x40000000U
#define ICACHE_CTRL_MEM_RENABLE_M                                    0x40000000U
#define ICACHE_CTRL_MEM_RENABLE_S                                    30U
/*

        Field:           MEM_CENABLE
        From..to bits:   31...31
        DefaultValue:    NA
        Access type:     read-write
        Description:     .

*/
#define ICACHE_CTRL_MEM_CENABLE                                      0x80000000U
#define ICACHE_CTRL_MEM_CENABLE_M                                    0x80000000U
#define ICACHE_CTRL_MEM_CENABLE_S                                    31U


/*-----------------------------------REGISTER------------------------------------
    Register name:       STATUS
    Offset name:         ICACHE_O_STATUS
    Relative address:    0x8
    Description:         The Status register displays the state of the icache controller.
    Default Value:       NA

        Field:           OK_TO_GO
        From..to bits:   31...31
        DefaultValue:    NA
        Access type:     read-only
        Description:     The ok_to_go status bit indicates the Tag/LRU Ram has been initialized and the cache is in an operable state.

*/
#define ICACHE_STATUS_OK_TO_GO                                       0x80000000U
#define ICACHE_STATUS_OK_TO_GO_M                                     0x80000000U
#define ICACHE_STATUS_OK_TO_GO_S                                     31U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CACHE_ADDRESS_LOW
    Offset name:         ICACHE_O_CACHE_ADDRESS_LOW
    Relative address:    0x10
    Description:          The Cache Address Low Register defines start of the cacheable space. The icache controller can cache up to a range of 8MB of of the target Flash as defined by CAL gt= CachedRange lt= CAH. This register is write protected when cenable is set.
    Default Value:       NA

        Field:           MEM_ADDR_LOW
        From..to bits:   12...31
        DefaultValue:    NA
        Access type:     read-write
        Description:      The addr_lo defines the cache low address[31:12] for the icache controller to cache. The remaining bits 10:0 are assumed to be zero

*/
#define ICACHE_CACHE_ADDRESS_LOW_MEM_ADDR_LOW_W                      20U
#define ICACHE_CACHE_ADDRESS_LOW_MEM_ADDR_LOW_M                      0xFFFFF000U
#define ICACHE_CACHE_ADDRESS_LOW_MEM_ADDR_LOW_S                      12U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CACHE_ADDRESS_HIGH
    Offset name:         ICACHE_O_CACHE_ADDRESS_HIGH
    Relative address:    0x18
    Description:          The L1 Cache Address High Register defines end of the L1 cacheable space. The L1 cache can cache up to a range of 8MB of of the target Flash as defined by CAL >= CachedRange <= CAH. This register is write protected when cenable is set.
    Default Value:       NA

        Field:           MEM_ADDR_HIGH
        From..to bits:   12...31
        DefaultValue:    NA
        Access type:     read-write
        Description:      The addr_hi defines the L1 high address[31:12] for the L1 to cache. The remaining bits 10:0 are assumed to be ones.

*/
#define ICACHE_CACHE_ADDRESS_HIGH_MEM_ADDR_HIGH_W                    20U
#define ICACHE_CACHE_ADDRESS_HIGH_MEM_ADDR_HIGH_M                    0xFFFFF000U
#define ICACHE_CACHE_ADDRESS_HIGH_MEM_ADDR_HIGH_S                    12U


/*-----------------------------------REGISTER------------------------------------
    Register name:       REGISTER_ADDRESS
    Offset name:         ICACHE_O_REGISTER_ADDRESS
    Relative address:    0x20
    Description:          The RAM Address register defines the upper 17 bits of address for the RAM when renable is set. This register is write protected when renable is set
    Default Value:       NA

        Field:           MEM_SEG_ADDR
        From..to bits:   15...31
        DefaultValue:    NA
        Access type:     read-write
        Description:     The seg_addr defines RAM address[31:15] value for RAM access .

*/
#define ICACHE_REGISTER_ADDRESS_MEM_SEG_ADDR_W                       17U
#define ICACHE_REGISTER_ADDRESS_MEM_SEG_ADDR_M                       0xFFFF8000U
#define ICACHE_REGISTER_ADDRESS_MEM_SEG_ADDR_S                       15U


/*-----------------------------------REGISTER------------------------------------
    Register name:       HIT_COUNTER
    Offset name:         ICACHE_O_HIT_COUNTER
    Relative address:    0x40
    Description:          The HIT Counter register holds the number of cache Hits to the internal cache
    Default Value:       NA

        Field:           MEM_HIT_COUNTER
        From..to bits:   0...31
        DefaultValue:    NA
        Access type:     read-write
        Description:      The hit Counts the number of hits to the L1 cache. Writing zero to this register will clear its contents.

*/
#define ICACHE_HIT_COUNTER_MEM_HIT_COUNTER_W                         32U
#define ICACHE_HIT_COUNTER_MEM_HIT_COUNTER_M                         0xFFFFFFFFU
#define ICACHE_HIT_COUNTER_MEM_HIT_COUNTER_S                         0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       MISS_COUNTER
    Offset name:         ICACHE_O_MISS_COUNTER
    Relative address:    0x44
    Description:         The MISS Counter register holds the number of cache misses to the internal cache  .
    Default Value:       NA

        Field:           MEM_MISS_COUNTER
        From..to bits:   0...31
        DefaultValue:    NA
        Access type:     read-write
        Description:      The miss Counts the number of misses to the L1 cache. Writing zero to this register will clear its contents.

*/
#define ICACHE_MISS_COUNTER_MEM_MISS_COUNTER_W                       32U
#define ICACHE_MISS_COUNTER_MEM_MISS_COUNTER_M                       0xFFFFFFFFU
#define ICACHE_MISS_COUNTER_MEM_MISS_COUNTER_S                       0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       IRQ_STATUS_RAW
    Offset name:         ICACHE_O_IRQ_STATUS_RAW
    Relative address:    0x80
    Description:          The Interrupt Raw Status Register holds the raw status of the icache error interrupts .
    Default Value:       NA

        Field:           WR_ERR
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     read-write
        Description:      The wr_err bit indicates a write error has occured to the remote cache data storage memory and the L1 is logically disabled while this bit is a '1'. Write 1 to set the wr_err status for diagnostic purposes. Writing a 0 has no effect.

*/
#define ICACHE_IRQ_STATUS_RAW_WR_ERR                                 0x00000001U
#define ICACHE_IRQ_STATUS_RAW_WR_ERR_M                               0x00000001U
#define ICACHE_IRQ_STATUS_RAW_WR_ERR_S                               0U
/*

        Field:           WR_HIT
        From..to bits:   1...1
        DefaultValue:    NA
        Access type:     read-write
        Description:       The wr_hit bit indicates a write to the cacheable range has occured potentially causing a coherency issue and the L1 is logically disabled while this bit is a '1'. Write 1 to set the wr_hit status for diagnostic purposes. Writing a 0 has no effect.

*/
#define ICACHE_IRQ_STATUS_RAW_WR_HIT                                 0x00000002U
#define ICACHE_IRQ_STATUS_RAW_WR_HIT_M                               0x00000002U
#define ICACHE_IRQ_STATUS_RAW_WR_HIT_S                               1U


/*-----------------------------------REGISTER------------------------------------
    Register name:       IRQ_STATUS_MASK
    Offset name:         ICACHE_O_IRQ_STATUS_MASK
    Relative address:    0x84
    Description:         The Interrupt Masked Status Register holds the masked status for the icache error interrupts. Writing to this register will EOI the interrupt, that is if another interrupt is pending, a new pulse interrupt will be generated  .
    Default Value:       NA

        Field:           MEM_ERR
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     read-write
        Description:      The wr_err bit indicates a write error has occured to the remote cache data storage memory and the L1 is logically disabled while this bit is a '1'. Write 1 to clear the wr_err status after interrupt has been serviced (raw status gets cleared, i.e. even if not enabled). Writing a 0 has no effect to this field.

*/
#define ICACHE_IRQ_STATUS_MASK_MEM_ERR                               0x00000001U
#define ICACHE_IRQ_STATUS_MASK_MEM_ERR_M                             0x00000001U
#define ICACHE_IRQ_STATUS_MASK_MEM_ERR_S                             0U
/*

        Field:           MEM_HIT
        From..to bits:   1...1
        DefaultValue:    NA
        Access type:     read-write
        Description:      The wr_hit bit indicates a write to the cacheable range has occured potentially causing a coherency issue and the L1 is logically disabled while this bit is a '1'. Write 1 to clear the wr_hit status after interrupt has been serviced (raw status gets cleared, i.e. even if not enabled). Writing a 0 has no effect to this field.

*/
#define ICACHE_IRQ_STATUS_MASK_MEM_HIT                               0x00000002U
#define ICACHE_IRQ_STATUS_MASK_MEM_HIT_M                             0x00000002U
#define ICACHE_IRQ_STATUS_MASK_MEM_HIT_S                             1U


/*-----------------------------------REGISTER------------------------------------
    Register name:       IRQ_ENABLE_SET
    Offset name:         ICACHE_O_IRQ_ENABLE_SET
    Relative address:    0x88
    Description:         The Interrupt Enable Set Register holds the interrupt enable status of the icache error interrupts  .
    Default Value:       NA

        Field:           EN_WR_ERR
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     read-write
        Description:      Interrupt Enable Set for wr_err error bit. Writing a 1 will enable the interrupt, and set this bit as well as the corresponding Interrupt Enable Clear Register. Writing a 0 has no effect.

*/
#define ICACHE_IRQ_ENABLE_SET_EN_WR_ERR                              0x00000001U
#define ICACHE_IRQ_ENABLE_SET_EN_WR_ERR_M                            0x00000001U
#define ICACHE_IRQ_ENABLE_SET_EN_WR_ERR_S                            0U
/*

        Field:           EN_WR_HIT
        From..to bits:   1...1
        DefaultValue:    NA
        Access type:     read-write
        Description:     Interrupt Enable Set for wr_hit error bit. Writing a 1 will enable the interrupt, and set this bit as well as the corresponding Interrupt Enable Clear Register. Writing a 0 has no effect.

*/
#define ICACHE_IRQ_ENABLE_SET_EN_WR_HIT                              0x00000002U
#define ICACHE_IRQ_ENABLE_SET_EN_WR_HIT_M                            0x00000002U
#define ICACHE_IRQ_ENABLE_SET_EN_WR_HIT_S                            1U


/*-----------------------------------REGISTER------------------------------------
    Register name:       IRQ_ENABLE_CLR
    Offset name:         ICACHE_O_IRQ_ENABLE_CLR
    Relative address:    0x8C
    Description:         The Interrupt Enable Clear Register holds the interrupt enable status of the icache error interrupts.
    Default Value:       NA

        Field:           EN_WR_ERR
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     read-write
        Description:      Interrupt Enable Clear for wr_err error bit. Writing a 1 will disable the interrupt, and clear this bit as well as the corresponding Interrupt Enable Set Register. Writing a 0 has no effect.

*/
#define ICACHE_IRQ_ENABLE_CLR_EN_WR_ERR                              0x00000001U
#define ICACHE_IRQ_ENABLE_CLR_EN_WR_ERR_M                            0x00000001U
#define ICACHE_IRQ_ENABLE_CLR_EN_WR_ERR_S                            0U
/*

        Field:           EN_WR_HIT
        From..to bits:   1...1
        DefaultValue:    NA
        Access type:     read-write
        Description:      Interrupt Enable Clear for wr_hit error bit. Writing a 1 will disable the interrupt, and clear this bit as well as the corresponding Interrupt Enable Set Register. Writing a 0 has no effect

*/
#define ICACHE_IRQ_ENABLE_CLR_EN_WR_HIT                              0x00000002U
#define ICACHE_IRQ_ENABLE_CLR_EN_WR_HIT_M                            0x00000002U
#define ICACHE_IRQ_ENABLE_CLR_EN_WR_HIT_S                            1U

#endif /* __HW_ICACHE_H__*/
