/*
 * Copyright (c) 2025-2026, Texas Instruments Incorporated
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
#ifndef ti_drivers_rcl_lrf_LRFLPF3_Interface_Generic__include
#define ti_drivers_rcl_lrf_LRFLPF3_Interface_Generic__include

#include <stdint.h>

#include <ti/drivers/rcl/LRF.h>
#include <ti/drivers/rcl/lrf/LRFLPF3_Interface.h>

#include <ti/devices/DeviceFamily.h>
#include DeviceFamily_constructPath(inc/hw_types.h)
#include DeviceFamily_constructPath(inc/hw_lrfdrfe.h)
#include DeviceFamily_constructPath(inc/hw_memmap.h)
#include DeviceFamily_constructPath(inc/pbe_generic_ram_regs.h)
#include DeviceFamily_constructPath(inc/pbe_generic_regdef_regs.h)

#if (DeviceFamily_PARENT != DeviceFamily_PARENT_CC23X0) && (DeviceFamily_PARENT != DeviceFamily_PARENT_CC27XX)
    #error "This LRFLPF3_Interface_Generic.h header file is only for CC23X0 and CC27XX devices!"
#endif

/* ============================================================================
 * Forward Declarations
 * ============================================================================
 */
typedef struct RCL_CONFIG_ADDRESS_t RCL_ConfigAddress; /*! NOTE: RCL_ConfigAddress is defined in 'rcl/commands/generic.h' */
typedef struct LRF_SYNC_SEARCH_CTRL_t LRF_SyncSearchCtrl;
typedef struct LRF_MODULATION_CTRL_t LRF_ModulationCtrl;

void LRF_Interface_Generic_configOpNesbPrx(uint16_t lrfOpCfg, uint8_t addrLen, const RCL_ConfigAddress* syncWordCfg);
void LRF_Interface_Generic_setModulationMode(uint32_t sendCw, uint32_t whitenMode, LRF_ModulationCtrl* modulationCtrl);
void LRF_Interface_Generic_disableSyncSearch(bool disableSyncWordA, bool disableSyncWordB, LRF_SyncSearchCtrl* syncSearchCtrl);
void LRF_Interface_Generic_updateSyncWordCfg(RCL_ConfigAddress* syncWordCfg);

/* ============================================================================
 * Type Definitions
 * ============================================================================
 */
struct LRF_SYNC_SEARCH_CTRL_t
{
    uint16_t        demc1be1;
    uint16_t        demc1be2;
#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX)
    uint16_t        demc1be12;
#endif
    uint16_t        restoreThresh : 1; /*! 1: Restore thresholds. 0: Do not restore thresholds. */
};

struct LRF_MODULATION_CTRL_t
{
    uint16_t        restoreOpt;
    uint16_t        storedWhitenInit;
    uint32_t        storedWhitenPoly;
};

/* ============================================================================
 * Macros
 * ============================================================================
 */
#define LRF_INTERFACE_GENERIC_API_OP_PING                            ((uint16_t)(PBE_GENERIC_REGDEF_API_OP_PING))
#define LRF_INTERFACE_GENERIC_API_OP_STOP                            ((uint16_t)(PBE_GENERIC_REGDEF_API_OP_STOP))
#define LRF_INTERFACE_GENERIC_API_OP_EOP_STOP                        ((uint16_t)(PBE_GENERIC_REGDEF_API_OP_EOPSTOP))
#define LRF_INTERFACE_GENERIC_API_OP_TX                              ((uint16_t)(PBE_GENERIC_REGDEF_API_OP_TX))
#define LRF_INTERFACE_GENERIC_API_OP_RX                              ((uint16_t)(PBE_GENERIC_REGDEF_API_OP_RX))
#define LRF_INTERFACE_GENERIC_API_OP_FS                              ((uint16_t)(PBE_GENERIC_REGDEF_API_OP_FS))
#define LRF_INTERFACE_GENERIC_API_OP_STOP_FS                         ((uint16_t)(PBE_GENERIC_REGDEF_API_OP_STOPFS))

#define LRFDRFE_SPARE4_SYNTHLOCK_M                                   (0x00000001U)
#define LRFDRFE_SPARE4_SYNTHLOCK_NOT_LOCKED                          (0x00000000U)

/* Polynomial to use for PRBS15 data */
#define LRF_INTERFACE_GENERIC_PRBS15_POLY                            (0x80020000U)
/* Polynomial to use for PRBS32 data */
#define LRF_INTERFACE_GENERIC_PRBS32_POLY                            (0x00400007U)
#define LRF_INTERFACE_GENERIC_PRBS_INIT                              (0x00005555U)
#define LRF_INTERFACE_GENERIC_PRBS_SYNC                              (0xAB05FA1CU)
#define LRF_INTERFACE_GENERIC_MODULATION_RESTORE_NONE                (0x0000U)
#define LRF_INTERFACE_GENERIC_MODULATION_RESTORE_MODCTRL             (0x0001U)
#define LRF_INTERFACE_GENERIC_MODULATION_RESTORE_WHITEN_INIT         (0x0002U)
#define LRF_INTERFACE_GENERIC_MODULATION_RESTORE_WHITEN_POLY         (0x0004U)

/* =========================================================================
 *  Inline APIs
 * =========================================================================
 */
static inline void LRF_Interface_Generic_sendOpFs(void)
{
    LRF_Interface_sendOp(PBE_GENERIC_REGDEF_API_OP_FS);
}

static inline void LRF_Interface_Generic_sendOpTx(void)
{
    LRF_Interface_sendOp(PBE_GENERIC_REGDEF_API_OP_TX);
}

static inline void LRF_Interface_Generic_sendOpRx(void)
{
    LRF_Interface_sendOp(PBE_GENERIC_REGDEF_API_OP_RX);
}

static inline void LRF_Interface_Generic_sendOpFsOff(void)
{
    LRF_Interface_sendOp(PBE_GENERIC_REGDEF_API_OP_STOPFS);
}

static inline void LRF_Interface_Generic_sendOpStop(void)
{
    LRF_Interface_sendOp(PBE_GENERIC_REGDEF_API_OP_STOP);
}

static inline void LRF_Interface_Generic_sendOpEopStop(void)
{
    LRF_Interface_sendOp(PBE_GENERIC_REGDEF_API_OP_EOPSTOP);
}

static inline void LRF_Interface_Generic_skipFreqProgramming(void)
{
    /* Turn off the FS calibration by writing 1 to the FS_NOCAL bit */
    uint16_t opCfg = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_OPCFG);
    opCfg |= PBE_GENERIC_RAM_OPCFG_FS_NOCAL_M;
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_OPCFG) = opCfg;
}

static inline uint32_t LRF_Interface_Generic_getLastPacketTimestamp(void)
{
    return HWREG_READ_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_LASTTIMESTAMPL);
}

static inline void LRF_Interface_Generic_setLastPacketTimestamp(uint32_t timestamp)
{
    HWREG_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_LASTTIMESTAMPL) = timestamp;
}

static inline int8_t LRF_Interface_Generic_getLastPacketRssi(void)
{
    return (int8_t) HWREGB_READ_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_LASTRSSI);
}

static inline uint16_t LRF_Interface_Generic_getNumOfRxOkPackets(void)
{
    return HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_NRXOK);
}

static inline void LRF_Interface_Generic_setNumOfRxOkPackets(uint16_t numOfRxOkPackets)
{
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_NRXOK) = numOfRxOkPackets;
}

static inline uint16_t LRF_Interface_Generic_getNumOfNotRxOkPackets(void)
{
    return HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_NRXNOK);
}

static inline void LRF_Interface_Generic_setNumOfNotRxOkPackets(uint16_t numOfNotRxOkPackets)
{
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_NRXNOK) = numOfNotRxOkPackets;
}

static inline uint16_t LRF_Interface_Generic_getNumOfTxPackets(void)
{
    return HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_NTX);
}

static inline void LRF_Interface_Generic_setNumOfTxPackets(uint16_t numOfTxPackets)
{
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_NTX) = numOfTxPackets;
}

static inline uint16_t LRF_Interface_Generic_getNumOfIgnoredRxPackets(void)
{
    return HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_NRXIGNORED);
}

static inline void LRF_Interface_Generic_setNumOfIgnoredRxPackets(uint16_t numOfIgnoredRxPackets)
{
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_NRXIGNORED) = numOfIgnoredRxPackets;
}

static inline uint16_t LRF_Interface_Generic_getRxFifoFullCount(void)
{
    return HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_NRXFIFOFULL);
}

static inline void LRF_Interface_Generic_setRxFifoFullCount(uint16_t rxBufferFullCount)
{
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_NRXFIFOFULL) = rxBufferFullCount;
}

static inline bool LRF_Interface_Generic_shouldNesbListenForAck(uint8_t mode)
{
    return (mode != PBE_GENERIC_RAM_SEQSTAT0_STOPAUTO_ALWAYS);
}

static inline uint16_t LRF_Interface_Generic_getFifoCfg(void)
{
    return HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_FIFOCFG);
}

static inline void LRF_Interface_Generic_configOpFs()
{
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_OPCFG) = (0U << PBE_GENERIC_RAM_OPCFG_START_S);
}

static inline void LRF_Interface_Generic_configOpFsOff()
{
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_OPCFG) = 0U;
}

static inline bool LRF_Interface_Generic_isFreqSynthLocked(void)
{
    return (HWREG_READ_LRF(LRFDRFE_BASE + LRFDRFE_O_SPARE4) & LRFDRFE_SPARE4_SYNTHLOCK_M) != LRFDRFE_SPARE4_SYNTHLOCK_NOT_LOCKED;
}

static inline void LRF_Interface_Generic_configOpTx(uint8_t fsOff, uint32_t freqInHz)
{
    uint16_t opCfgVal = (0U << PBE_GENERIC_RAM_OPCFG_TXINFINITE_S)  |
                        (0U << PBE_GENERIC_RAM_OPCFG_TXPATTERN_S)   |
                        (2U << PBE_GENERIC_RAM_OPCFG_TXFCMD_S)      |
                        (0U << PBE_GENERIC_RAM_OPCFG_START_S)       |
                        (1U << PBE_GENERIC_RAM_OPCFG_FS_NOCAL_S)    |
                        (1U << PBE_GENERIC_RAM_OPCFG_FS_KEEPON_S)   |
                        (0U << PBE_GENERIC_RAM_OPCFG_RXREPEATOK_S)  |
                        (0U << PBE_GENERIC_RAM_OPCFG_RXREPEATNOK_S) |
                        (0U << PBE_GENERIC_RAM_OPCFG_NEXTOP_S)      |
                        (1U << PBE_GENERIC_RAM_OPCFG_SINGLE_S)      |
                        (0U << PBE_GENERIC_RAM_OPCFG_IFSPERIOD_S)   |
                        (0U << PBE_GENERIC_RAM_OPCFG_RFINTERVAL_S);
    if (fsOff != 0U)
    {
        opCfgVal &= ~PBE_GENERIC_RAM_OPCFG_FS_KEEPON_M;
    }
    if (freqInHz != 0U)
    {
        opCfgVal &= ~PBE_GENERIC_RAM_OPCFG_FS_NOCAL_M;
    }
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_OPCFG) = opCfgVal;
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_NESB) = PBE_GENERIC_RAM_NESB_NESBMODE_OFF;
}

static inline void LRF_Interface_Generic_configOpTxRepeat(uint32_t freqInHz, uint8_t fsRecal)
{
    /* Handle FS off in the end, so disable it in PBE */
    uint16_t opCfgVal = (0U << PBE_GENERIC_RAM_OPCFG_TXINFINITE_S) |
                        (0U << PBE_GENERIC_RAM_OPCFG_TXPATTERN_S)  |
                        (1U << PBE_GENERIC_RAM_OPCFG_TXFCMD_S)     |
                        (0U << PBE_GENERIC_RAM_OPCFG_START_S)      |
                        (1U << PBE_GENERIC_RAM_OPCFG_FS_NOCAL_S)   |
                        (1U << PBE_GENERIC_RAM_OPCFG_FS_KEEPON_S)  |
                        (0U << PBE_GENERIC_RAM_OPCFG_NEXTOP_S)     |
                        (0U << PBE_GENERIC_RAM_OPCFG_RXREPEATOK_S) |
                        (1U << PBE_GENERIC_RAM_OPCFG_SINGLE_S)     |
                        (0U << PBE_GENERIC_RAM_OPCFG_IFSPERIOD_S)  |
                        (0U << PBE_GENERIC_RAM_OPCFG_RFINTERVAL_S);
    if (freqInHz != 0U)
    {
        opCfgVal &= ~PBE_GENERIC_RAM_OPCFG_FS_NOCAL_M;
    }
    if (fsRecal != 0U)
    {
        opCfgVal &= ~PBE_GENERIC_RAM_OPCFG_FS_KEEPON_M;
    }
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_OPCFG) = opCfgVal;
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_NESB) = PBE_GENERIC_RAM_NESB_NESBMODE_OFF;
}

static inline void LRF_Interface_Generic_configOpTxTest(uint8_t fsOff, uint32_t freqInHz, uint16_t txWord)
{
    uint16_t opCfgVal = (1U << PBE_GENERIC_RAM_OPCFG_TXINFINITE_S) |
                        (1U << PBE_GENERIC_RAM_OPCFG_TXPATTERN_S)  |
                        (0U << PBE_GENERIC_RAM_OPCFG_TXFCMD_S)     |
                        (0U << PBE_GENERIC_RAM_OPCFG_START_S)      |
                        (1U << PBE_GENERIC_RAM_OPCFG_FS_NOCAL_S)   |
                        (1U << PBE_GENERIC_RAM_OPCFG_FS_KEEPON_S)  |
                        (0U << PBE_GENERIC_RAM_OPCFG_RXREPEATOK_S) |
                        (0U << PBE_GENERIC_RAM_OPCFG_NEXTOP_S)     |
                        (1U << PBE_GENERIC_RAM_OPCFG_SINGLE_S)     |
                        (0U << PBE_GENERIC_RAM_OPCFG_IFSPERIOD_S)  |
                        (0U << PBE_GENERIC_RAM_OPCFG_RFINTERVAL_S);
    if (fsOff != 0U)
    {
        opCfgVal &= ~PBE_GENERIC_RAM_OPCFG_FS_KEEPON_M;
    }
    if (freqInHz != 0U)
    {
        opCfgVal &= ~PBE_GENERIC_RAM_OPCFG_FS_NOCAL_M;
    }
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_OPCFG) = opCfgVal;
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_NESB) = PBE_GENERIC_RAM_NESB_NESBMODE_OFF;
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_PATTERN) = txWord;
}

static inline void LRF_Interface_Generic_configOpRx(uint8_t fsOff, uint32_t freqInHz, uint8_t repeated, uint16_t maxPktLen)
{
    uint16_t opCfgVal = (0U << PBE_GENERIC_RAM_OPCFG_RXFILTEROP_S)   |
                        (1U << PBE_GENERIC_RAM_OPCFG_RXINCLUDEHDR_S) |
                        (1U << PBE_GENERIC_RAM_OPCFG_RXREPEATNOK_S)  |
                        (0U << PBE_GENERIC_RAM_OPCFG_START_S)        |
                        (1U << PBE_GENERIC_RAM_OPCFG_FS_NOCAL_S)     |
                        (1U << PBE_GENERIC_RAM_OPCFG_FS_KEEPON_S)    |
                        (1U << PBE_GENERIC_RAM_OPCFG_NEXTOP_S)       |
                        (0U << PBE_GENERIC_RAM_OPCFG_SINGLE_S)       |
                        (0U << PBE_GENERIC_RAM_OPCFG_IFSPERIOD_S)    |
                        (0U << PBE_GENERIC_RAM_OPCFG_RXREPEATOK_S)   |
                        (0U << PBE_GENERIC_RAM_OPCFG_RFINTERVAL_S);
    if (fsOff != 0U)
    {
        opCfgVal &= ~PBE_GENERIC_RAM_OPCFG_FS_KEEPON_M;
    }
    if (freqInHz != 0U)
    {
        opCfgVal &= ~PBE_GENERIC_RAM_OPCFG_FS_NOCAL_M;
    }
    if (repeated != 0U)
    {
        opCfgVal |= PBE_GENERIC_RAM_OPCFG_RFINTERVAL_M;
    }
    else
    {
        opCfgVal |= PBE_GENERIC_RAM_OPCFG_SINGLE_M;
    }
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_OPCFG) = opCfgVal;
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_NESB) = PBE_GENERIC_RAM_NESB_NESBMODE_OFF;
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_MAXLEN) = maxPktLen;
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_RXTIMEOUT) = 0U; /* No timeout except from SYSTIM */
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_FIRSTRXTIMEOUT) = 0U; /* No timeout except from SYSTIM */
}

static inline void LRF_Interface_Generic_configOpNesbPtx(uint8_t fsOff, uint32_t freqInHz, uint8_t autoRetransmitMode)
{
    uint16_t opCfgVal = (PBE_GENERIC_RAM_OPCFG_NEXTOP_SWITCH)   |
                        (PBE_GENERIC_RAM_OPCFG_TXFCMD_NONE)     |
                        (PBE_GENERIC_RAM_OPCFG_FS_NOCAL_NOCAL)  |
                        (PBE_GENERIC_RAM_OPCFG_FS_KEEPON_YES)   |
                        (PBE_GENERIC_RAM_OPCFG_IFSPERIOD_EN)    |
                        (PBE_GENERIC_RAM_OPCFG_RXREPEATNOK_YES) |
                        (PBE_GENERIC_RAM_OPCFG_RXREPEATOK_YES)  |
                        (PBE_GENERIC_RAM_OPCFG_RFINTERVAL_DIS)  |
                        (PBE_GENERIC_RAM_OPCFG_SINGLE_DIS)      |
                        (PBE_GENERIC_RAM_OPCFG_RXINCLUDEHDR_YES);
    if (fsOff != 0U)
    {
        opCfgVal &= ~PBE_GENERIC_RAM_OPCFG_FS_KEEPON_M;
    }
    if (freqInHz != 0U)
    {
        opCfgVal &= ~PBE_GENERIC_RAM_OPCFG_FS_NOCAL_M;
    }
    if (autoRetransmitMode != 0U)
    {
        opCfgVal |= PBE_GENERIC_RAM_OPCFG_TXFCMD_RETRY;
    }
    else
    {
        opCfgVal |= PBE_GENERIC_RAM_OPCFG_TXFCMD_DEALLOC;
    }
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_FIRSTRXTIMEOUT) = 2500U;
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_RXTIMEOUT) = 800U;
    /* PBE currently only supports ACKs with a payload equal to the used address. Maximum 4 bytes. */
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_MAXLEN) = 4U;
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_OPCFG) = opCfgVal;
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_NESB) = PBE_GENERIC_RAM_NESB_NESBMODE_ON;
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_SEQSTAT0) = (uint16_t)((autoRetransmitMode << PBE_GENERIC_RAM_SEQSTAT0_STOPAUTO_S) & PBE_GENERIC_RAM_SEQSTAT0_STOPAUTO_M);
}

static inline uint16_t LRF_Interface_Generic_getOpCfgNesbPrx(uint8_t fsOff, uint32_t freqInHz, uint8_t repeatNok, uint8_t repeatOk)
{
    uint16_t opCfg = (PBE_GENERIC_RAM_OPCFG_NEXTOP_SWITCH)   |
                     (PBE_GENERIC_RAM_OPCFG_TXFCMD_RETRY)    |
                     (PBE_GENERIC_RAM_OPCFG_FS_NOCAL_NOCAL)  |
                     (PBE_GENERIC_RAM_OPCFG_FS_KEEPON_YES)   |
                     (PBE_GENERIC_RAM_OPCFG_IFSPERIOD_EN)    |
                     (PBE_GENERIC_RAM_OPCFG_RXREPEATNOK_NO)  |
                     (PBE_GENERIC_RAM_OPCFG_RXREPEATOK_NO)   |
                     (PBE_GENERIC_RAM_OPCFG_RFINTERVAL_DIS)  |
                     (PBE_GENERIC_RAM_OPCFG_SINGLE_DIS)      |
                     (PBE_GENERIC_RAM_OPCFG_RXINCLUDEHDR_YES);
    if (fsOff != 0U)
    {
        opCfg &= ~PBE_GENERIC_RAM_OPCFG_FS_KEEPON_M;
    }
    if (freqInHz != 0U)
    {
        opCfg &= ~PBE_GENERIC_RAM_OPCFG_FS_NOCAL_M;
    }
    if (repeatNok != 0U)
    {
        opCfg |= PBE_GENERIC_RAM_OPCFG_RXREPEATNOK_M;
    }
    if (repeatOk != 0U)
    {
        opCfg &= ~PBE_GENERIC_RAM_OPCFG_RXREPEATOK_M;
    }

    return opCfg;
}

static inline void LRF_Interface_Generic_configNextOpTx(void)
{
    HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_INIT) = (1U << LRFDPBE_INIT_TOPSM_S);
}

static inline uint32_t LRF_Interface_Generic_updateSyncWord(uint32_t syncWord)
{
    uint32_t syncWordOut;
    /* Check bit ordering of header and follow that */
    if ((HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_PKTCFG) & PBE_GENERIC_RAM_PKTCFG_HDRORDER_M) != 0U)
    {
        /* MSb first configured - bit reverse sync word */
        HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_PHAOUT0) = syncWord & 0x0000FFFFU;
        syncWordOut = HWREG_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_PHAOUT0BR) << 16U;
        HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_PHAOUT0) = syncWord >> 16U;
        syncWordOut |= HWREG_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_PHAOUT0BR);
        /* Check sync word length to see ensure that sync word ends up in least significant bits */
        uint32_t syncWordLen =(uint32_t) (HWREG_READ_LRF(LRFDMDM_BASE + LRFDMDM_O_DEMSWQU0) & LRFDMDM_DEMSWQU0_REFLEN_M) + 1U;
        syncWordOut >>= (32U - syncWordLen);
    }
    else
    {
        syncWordOut = syncWord;
    }

    return syncWordOut;
}

static inline void LRF_Interface_Generic_programSyncWordA(uint32_t syncWord)
{
    /* Convert sync word bit order to match packet header configuration (MSB-first becomes LSB-first) */
    uint32_t syncWordUpdated = LRF_Interface_Generic_updateSyncWord(syncWord);
    LRF_Interface_programSyncWordA(syncWordUpdated);
}

static inline void LRF_Interface_Generic_programSyncWordB(uint32_t syncWord)
{
    /* Convert sync word bit order to match packet header configuration (MSB-first becomes LSB-first) */
    uint32_t syncWordUpdated = LRF_Interface_Generic_updateSyncWord(syncWord);
    LRF_Interface_programSyncWordB(syncWordUpdated);
}

static inline uint32_t LRF_Interface_Generic_maskEventsByFifoConf(uint32_t mask, uint16_t fifoCfg, bool activeUpdate)
{
    /* Remove events that will not give an entry in the RX FIFO, based on FIFOCFG, unless active update is used
       Note: never remove the CRC error event, as it is needed to update the long CRC error counter */
    if (activeUpdate == false)
    {
        mask &= ~(((fifoCfg & PBE_GENERIC_RAM_FIFOCFG_AUTOFLUSHIGN_M) != 0U ?
                   (uint32_t)LRF_EventRxIgnored.value : 0U) | (uint32_t)LRF_EventRxBufFull.value);
    }
    return mask;
}

static inline void LRF_Interface_Generic_restoreSyncSearch(const LRF_SyncSearchCtrl* syncSearchCtrl)
{
    if (syncSearchCtrl->restoreThresh == 1U)
    {
        HWREGH_WRITE_LRF(LRFDMDM_BASE + LRFDMDM_O_DEMC1BE1) = syncSearchCtrl->demc1be1;
        HWREGH_WRITE_LRF(LRFDMDM_BASE + LRFDMDM_O_DEMC1BE2) = syncSearchCtrl->demc1be2;
#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX)
        HWREGH_WRITE_LRF(LRFDMDM_BASE + LRFDMDM_O_DEMC1BE12) = syncSearchCtrl->demc1be12;
#endif
    }
}

static inline void LRF_Interface_Generic_restoreModulationMode(const LRF_ModulationCtrl* modulationCtrl)
{
    if ((modulationCtrl->restoreOpt & LRF_INTERFACE_GENERIC_MODULATION_RESTORE_MODCTRL) != 0U)
    {
        HWREG_WRITE_LRF(LRFDMDM_BASE + LRFDMDM_O_MODCTRL) = HWREG_READ_LRF(LRFDMDM_BASE + LRFDMDM_O_MODCTRL) & (~LRFDMDM_MODCTRL_TONEINSERT_M);
    }
    if ((modulationCtrl->restoreOpt & LRF_INTERFACE_GENERIC_MODULATION_RESTORE_WHITEN_INIT) != 0U)
    {
        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_WHITEINIT) = (modulationCtrl->storedWhitenInit);
    }
    if ((modulationCtrl->restoreOpt & LRF_INTERFACE_GENERIC_MODULATION_RESTORE_WHITEN_POLY) != 0U)
    {
        HWREG_WRITE_LRF(LRFDPBE32_BASE + LRFDPBE32_O_POLY0) = (modulationCtrl->storedWhitenPoly);
    }
}

#endif /* ti_drivers_rcl_lrf_LRFLPF3_Interface_Generic__include */
