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
#ifndef ti_drivers_rcl_lrf_LRFLPF3_Interface__include
#define ti_drivers_rcl_lrf_LRFLPF3_Interface__include

#include <stdint.h>

#include <ti/devices/DeviceFamily.h>
#include DeviceFamily_constructPath(inc/hw_types.h)
#include DeviceFamily_constructPath(inc/hw_lrfddbell.h)
#include DeviceFamily_constructPath(inc/hw_lrfdmdm.h)
#include DeviceFamily_constructPath(inc/hw_lrfdpbe.h)
#include DeviceFamily_constructPath(inc/hw_lrfdpbe32.h)
#include DeviceFamily_constructPath(inc/hw_memmap.h)
#include DeviceFamily_constructPath(inc/pbe_common_ram_regs.h)
#include DeviceFamily_constructPath(inc/pbe_generic_regdef_regs.h)

#if (DeviceFamily_PARENT != DeviceFamily_PARENT_CC23X0) && (DeviceFamily_PARENT != DeviceFamily_PARENT_CC27XX)
    #error "This LRFLPF3_Interface.h header file is only for CC23X0 and CC27XX devices!"
#endif

/* ============================================================================
 * Macros
 * ============================================================================
 */
#define LRF_INTERFACE_ENDCAUSE_STAT_ENDOK         (uint16_t)(PBE_COMMON_RAM_ENDCAUSE_STAT_ENDOK)
#define LRF_INTERFACE_ENDCAUSE_STAT_RXTIMEOUT     (uint16_t)(PBE_COMMON_RAM_ENDCAUSE_STAT_RXTIMEOUT)
#define LRF_INTERFACE_ENDCAUSE_STAT_NOSYNC        (uint16_t)(PBE_COMMON_RAM_ENDCAUSE_STAT_NOSYNC)
#define LRF_INTERFACE_ENDCAUSE_STAT_RXERR         (uint16_t)(PBE_COMMON_RAM_ENDCAUSE_STAT_RXERR)
#define LRF_INTERFACE_ENDCAUSE_STAT_CONNECT       (uint16_t)(PBE_COMMON_RAM_ENDCAUSE_STAT_CONNECT)
#define LRF_INTERFACE_ENDCAUSE_STAT_MAXNAK        (uint16_t)(PBE_COMMON_RAM_ENDCAUSE_STAT_MAXNAK)
#define LRF_INTERFACE_ENDCAUSE_STAT_SCANRSP       (uint16_t)(PBE_COMMON_RAM_ENDCAUSE_STAT_SCANRSP)
#define LRF_INTERFACE_ENDCAUSE_STAT_EOPSTOP       (uint16_t)(PBE_COMMON_RAM_ENDCAUSE_STAT_EOPSTOP)
#define LRF_INTERFACE_ENDCAUSE_STAT_ERR_RXF       (uint16_t)(PBE_COMMON_RAM_ENDCAUSE_STAT_ERR_RXF)
#define LRF_INTERFACE_ENDCAUSE_STAT_ERR_TXF       (uint16_t)(PBE_COMMON_RAM_ENDCAUSE_STAT_ERR_TXF)
#define LRF_INTERFACE_ENDCAUSE_STAT_ERR_SYNTH     (uint16_t)(PBE_COMMON_RAM_ENDCAUSE_STAT_ERR_SYNTH)
#define LRF_INTERFACE_ENDCAUSE_STAT_ERR_STOP      (uint16_t)(PBE_COMMON_RAM_ENDCAUSE_STAT_ERR_STOP)
#define LRF_INTERFACE_ENDCAUSE_STAT_ERR_PAR       (uint16_t)(PBE_COMMON_RAM_ENDCAUSE_STAT_ERR_PAR)
#define LRF_INTERFACE_ENDCAUSE_STAT_ERR_BADOP     (uint16_t)(PBE_COMMON_RAM_ENDCAUSE_STAT_ERR_BADOP)
#define LRF_INTERFACE_ENDCAUSE_STAT_ERR_INTERNAL  (uint16_t)(PBE_COMMON_RAM_ENDCAUSE_STAT_ERR_INTERNAL)

/* =========================================================================
 *  Inline APIs
 * =========================================================================
 */
static inline void LRF_Interface_sendOp(uint16_t op)
{
    HWREGH_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_API) = op;
}

static inline void LRF_Interface_programSyncWordA(uint32_t syncWord)
{
    HWREG_WRITE_LRF(LRFDPBE32_BASE + LRFDPBE32_O_MDMSYNCA) = syncWord;
}

static inline void LRF_Interface_programSyncWordB(uint32_t syncWord)
{
    HWREG_WRITE_LRF(LRFDPBE32_BASE + LRFDPBE32_O_MDMSYNCB) = syncWord;
}

static inline uint16_t LRF_Interface_getCmdEndCause(void)
{
    return HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_COMMON_RAM_O_ENDCAUSE);
}

static inline bool LRF_Interface_isCmdEndCauseEopStop(void)
{
    return (LRF_Interface_getCmdEndCause() == PBE_COMMON_RAM_ENDCAUSE_STAT_EOPSTOP);
}

static inline bool LRF_Interface_isCmdEndCauseEndOk(uint16_t endCause)
{
    return (endCause == PBE_COMMON_RAM_ENDCAUSE_STAT_ENDOK);
}

static inline bool LRF_Interface_isCmdEndCauseEndedWithoutSync(uint16_t endCause)
{
    return (endCause == PBE_COMMON_RAM_ENDCAUSE_STAT_NOSYNC);
}

#endif /* ti_drivers_rcl_lrf_LRFLPF3_Interface__include */
