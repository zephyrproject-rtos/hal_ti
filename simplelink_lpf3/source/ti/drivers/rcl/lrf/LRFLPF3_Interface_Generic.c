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
#include <stdint.h>

#include <ti/drivers/rcl/lrf/LRFLPF3_Interface_Generic.h>
#include <ti/drivers/rcl/commands/generic.h> /* For definition of RCL_ConfigAddress */

#include <ti/devices/DeviceFamily.h>
#include DeviceFamily_constructPath(inc/hw_types.h)
#include DeviceFamily_constructPath(inc/hw_memmap.h)
#include DeviceFamily_constructPath(inc/hw_lrfdmdm.h)
#include DeviceFamily_constructPath(inc/hw_lrfdpbe32.h)
#include DeviceFamily_constructPath(inc/pbe_generic_ram_regs.h)

/* ============================================================================
 * Implementations
 * ============================================================================
 */

/*
 * ======== LRF_Interface_Generic_configOpNesbPrx ========
 */
void LRF_Interface_Generic_configOpNesbPrx(uint16_t lrfOpCfg, uint8_t addrLen, const RCL_ConfigAddress* syncWordCfg)
{
    /* Enable NESB mode */
    uint16_t nesbVal = (PBE_GENERIC_RAM_NESB_NESBMODE_ON);
    nesbVal |= ((uint16_t) addrLen << PBE_GENERIC_RAM_NESB_PEERADRLEN_S) & PBE_GENERIC_RAM_NESB_PEERADRLEN_M;

    /* Configure AutoACK and Seq Status for syncword 0 */
    uint32_t seqStat0Val = (syncWordCfg[0].seqValid << PBE_GENERIC_RAM_SEQSTAT0_VALID_S) & PBE_GENERIC_RAM_SEQSTAT0_VALID_M;
    seqStat0Val |= (syncWordCfg[0].autoAckMode << PBE_GENERIC_RAM_SEQSTAT0_STOPAUTO_S) & PBE_GENERIC_RAM_SEQSTAT0_STOPAUTO_M;

    /* Configure AutoACK and Seq Status for syncword 1 */
    uint32_t seqStat1Val = (syncWordCfg[1].seqValid << PBE_GENERIC_RAM_SEQSTAT1_VALID_S) & PBE_GENERIC_RAM_SEQSTAT1_VALID_M;
    seqStat1Val |= (syncWordCfg[1].autoAckMode << PBE_GENERIC_RAM_SEQSTAT1_STOPAUTO_S) & PBE_GENERIC_RAM_SEQSTAT1_STOPAUTO_M;

    /* Set the addresses that will be used for address filtering */
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_PEERADR0AL) = (uint16_t) (syncWordCfg[0].address & PBE_GENERIC_RAM_PEERADR0AL_VAL_M);
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_PEERADR0AH) = (uint16_t) (syncWordCfg[0].address >> 0x10) & PBE_GENERIC_RAM_PEERADR0AH_VAL_M;
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_PEERADR0BL) = (uint16_t) (syncWordCfg[1].address & PBE_GENERIC_RAM_PEERADR0BL_VAL_M);
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_PEERADR0BH) = (uint16_t) (syncWordCfg[1].address >> 0x10) & PBE_GENERIC_RAM_PEERADR0BH_VAL_M;

    /* Initialize PEERADR1 and NRXTIMEOUT even if not in use */
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_PEERADR1AL) = 0U;
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_PEERADR1AH) = 0U;
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_PEERADR1BL) = 0U;
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_PEERADR1BH) = 0U;
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_NRXTIMEOUT) = 0U;

    /* Set timeouts for the Rx operation */
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_FIRSTRXTIMEOUT) = 0U; /* No timeout except from SYSTIM */
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_RXTIMEOUT) = 0U; /* No timeout except from SYSTIM */

    /* Set remaining configuration registers */
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_OPCFG) = lrfOpCfg;
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_NESB) = nesbVal;
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_SEQSTAT0) = (uint16_t)seqStat0Val;
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_SEQSTAT1) = (uint16_t)seqStat1Val;
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_MAXLEN) = 255U;
}

/*
 * ======== LRF_Interface_Generic_updateSyncWordCfg ========
 */
void LRF_Interface_Generic_updateSyncWordCfg(RCL_ConfigAddress* syncWordCfg)
{
    /* Update the sequence number to the one from to the last successfully received packet */
    syncWordCfg[0].seq = (uint8_t) ((HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_SEQSTAT0) & PBE_GENERIC_RAM_SEQSTAT0_PID_M) >> PBE_GENERIC_RAM_SEQSTAT0_PID_S);
    syncWordCfg[1].seq = (uint8_t) ((HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_SEQSTAT1) & PBE_GENERIC_RAM_SEQSTAT1_PID_M) >> PBE_GENERIC_RAM_SEQSTAT1_PID_S);

    /* Update the CRC value to the one from the last successfully received packet */
    syncWordCfg[0].crcVal = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_CRCVAL0);
    syncWordCfg[1].crcVal = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_CRCVAL1);
}

/*
 * ======== LRF_Interface_Generic_setModulationMode ========
 */
void LRF_Interface_Generic_setModulationMode(uint32_t sendCw, uint32_t whitenMode, LRF_ModulationCtrl* modulationCtrl)
{
    if (sendCw != 0U)
    {
        modulationCtrl->restoreOpt = (LRF_INTERFACE_GENERIC_MODULATION_RESTORE_MODCTRL);
        HWREG_WRITE_LRF(LRFDMDM_BASE + LRFDMDM_O_MODCTRL) = HWREG_READ_LRF(LRFDMDM_BASE + LRFDMDM_O_MODCTRL) | (LRFDMDM_MODCTRL_TONEINSERT_M);
    }
    else
    {
        if (whitenMode == RCL_CMD_GENERIC_WH_MODE_NONE)
        {
            modulationCtrl->restoreOpt = (LRF_INTERFACE_GENERIC_MODULATION_RESTORE_WHITEN_INIT);
            modulationCtrl->storedWhitenInit = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_WHITEINIT);
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_WHITEINIT) = 0U;
        }
        else
        {
            if (whitenMode >= RCL_CMD_GENERIC_WH_MODE_PRBS15)
            {
                modulationCtrl->restoreOpt = (LRF_INTERFACE_GENERIC_MODULATION_RESTORE_WHITEN_POLY | LRF_INTERFACE_GENERIC_MODULATION_RESTORE_WHITEN_INIT);
                modulationCtrl->storedWhitenPoly = HWREG_READ_LRF(LRFDPBE32_BASE + LRFDPBE32_O_POLY0);
                modulationCtrl->storedWhitenInit = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_WHITEINIT);
                if (whitenMode > RCL_CMD_GENERIC_WH_MODE_PRBS15)
                {
                    HWREG_WRITE_LRF(LRFDPBE32_BASE + LRFDPBE32_O_POLY0) = (LRF_INTERFACE_GENERIC_PRBS15_POLY);
                }
                else
                {
                    HWREG_WRITE_LRF(LRFDPBE32_BASE + LRFDPBE32_O_POLY0) = (LRF_INTERFACE_GENERIC_PRBS32_POLY);
                }
                HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_GENERIC_RAM_O_WHITEINIT) = (LRF_INTERFACE_GENERIC_PRBS_INIT);
            }
        }
    }
}

/*
 * ======== LRF_Interface_Generic_disableSyncSearch ========
 */
void LRF_Interface_Generic_disableSyncSearch(bool disableSyncWordA, bool disableSyncWordB, LRF_SyncSearchCtrl* syncSearchCtrl)
{
    uint16_t demc1be1 = HWREGH_READ_LRF(LRFDMDM_BASE + LRFDMDM_O_DEMC1BE1);
    uint16_t demc1be2 = HWREGH_READ_LRF(LRFDMDM_BASE + LRFDMDM_O_DEMC1BE2);
#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX)
    uint16_t demc1be12 = HWREGH_READ_LRF(LRFDMDM_BASE + LRFDMDM_O_DEMC1BE12);
#endif
    syncSearchCtrl->restoreThresh = 1U;
    syncSearchCtrl->demc1be1 = demc1be1;
    syncSearchCtrl->demc1be2 = demc1be2;
#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX)
    syncSearchCtrl->demc1be12 = demc1be12;
#endif
    if (disableSyncWordA == true)
    {
        demc1be1 = (uint16_t) ((demc1be1 & ~LRFDMDM_DEMC1BE1_THRESHOLDA_M) | (0x7FU << LRFDMDM_DEMC1BE1_THRESHOLDA_S));
        demc1be2 = (uint16_t) ((demc1be2 & ~LRFDMDM_DEMC1BE2_THRESHOLDC_M) | (0x7FU << LRFDMDM_DEMC1BE2_THRESHOLDC_S));
#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX)
        demc1be12 = (uint16_t) ((demc1be12 & ~LRFDMDM_DEMC1BE12_THRESHOLDG_M) | (0x7FU << LRFDMDM_DEMC1BE12_THRESHOLDG_S));
#endif
    }
    if (disableSyncWordB == true)
    {
        demc1be1 = (uint16_t) ((demc1be1 & ~LRFDMDM_DEMC1BE1_THRESHOLDB_M) | (0x7FU << LRFDMDM_DEMC1BE1_THRESHOLDB_S));
    }
    HWREGH_WRITE_LRF(LRFDMDM_BASE + LRFDMDM_O_DEMC1BE1) = demc1be1;
    HWREGH_WRITE_LRF(LRFDMDM_BASE + LRFDMDM_O_DEMC1BE2) = demc1be2;
#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX)
    HWREGH_WRITE_LRF(LRFDMDM_BASE + LRFDMDM_O_DEMC1BE12) = demc1be12;
#endif
}
