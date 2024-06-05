/*
 * Copyright (c) 2021-2023, Texas Instruments Incorporated
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
 *  ======== LRF.c ========
 */

#include <stdint.h>
#include <stdlib.h>

#include <ti/drivers/rcl/RCL_Command.h>
#include <ti/drivers/rcl/RCL_Debug.h>
#include <ti/drivers/rcl/LRF.h>
#include <ti/log/Log.h>

// #define LRF_DEBUG_TRACE

LRF_SetupResult LRF_loadImage(const LRF_TOPsmImage *image, uint32_t destinationAddress)
{
    LRF_SetupResult result;

    if (image == NULL)
    {
        /* OK, don't load image */
        result = SetupResult_Ok;
    }
    else
    {
        const uint32_t *topsmSourcePointer = image->image;
        uint32_t *ram = (uint32_t *) destinationAddress;
        uint32_t length = image->imageLen;

        if (length > (TOPSM_RAM_SZ / sizeof(uint32_t)))
        {
            /* Image too long */
            result = SetupResult_ErrorImageLen;
        }
        else
        {
            uint32_t i = 0;
            /* Check if the image is 128-bit aligned, and if not, read out 32-bit word(s) */
            while ((((uintptr_t) topsmSourcePointer) & 0x0F) != 0)
            {
                *ram++ = *topsmSourcePointer++;
                i++;
            }
            /* Load most of the image using aligned 128-bit reads */
#ifdef DeviceFamily_CC27XX
            /* We don't need to use HWREG_READ_LRF every time, as the loop only writes to RAM without registers inbetween, but we should protect the first write */
            ASM_4_NOPS();
#endif //DeviceFamily_CC27XX
            while (i < length - 3)
            {
#ifdef NO_INLINE_ASM
                struct quadword {
                    uint32_t word[4];
                };
                *((struct quadword *) ram) = *((const struct quadword *) topsmSourcePointer);
                topsmSourcePointer += 4;
                ram += 4;
#else
                __asm(
                    "LDMIA %0!, {r4, r5, r6, r7} \n"
                    "STMIA %1!, {r4, r5, r6, r7} \n"
                    : "+r" (topsmSourcePointer),
                      "+r" (ram) :
                    : "r4", "r5", "r6", "r7"
                );
#endif
                i += 4;
            }

            /* If one or more 32-bit word is left, read it here */
            while (i < length)
            {
                *ram++ = *topsmSourcePointer++;
                i++;
            }
            result = SetupResult_Ok;
        }
    }
    return result;
}

void LRF_initSettingsState(LRF_ApplySettingsState *state,
                           LRF_ApplySettingsBase   includeBase,
                           uint16_t                phyFeatures)
{
    LRF_resetSettingsState(state);
    state->includeBase = includeBase;
    state->phyFeatures = phyFeatures;
}

LRF_SetupResult LRF_applySettings(LRF_ConfigWord         *config,
                                  LRF_ApplySettingsState *state,
                                  int32_t                 bufferAvailWords)
{
#ifdef BUFFER_SPLIT_SUPPORT
    uint32_t totalLength = state->totalLength;
#else
    (void)bufferAvailWords;
#endif
    uint32_t segmentLength;
    uint32_t regionLength;
    LRF_RegionOperation operation = LRF_RegionOperation_Invalid;
    uintptr_t address = 0;

    /* If settings is NULL, ignore the entry */
    if (config == NULL)
    {
        return SetupResult_Ok;
    }

    /* Use 32-bit pointer to read entries to ensure compailer doesn't insert
       16-bit reads toward (possible) flash */
    uint32_t *curEntry = &config->value32;

    /* Initialize state if starting fresh */
#ifdef BUFFER_SPLIT_SUPPORT
    if (totalLength == 0)
    {
        if (bufferAvailWords < 2)
        {
            return SetupResult_ErrorElemLen;
        }
        LRF_ConfigWord curWord;
        curWord.value32 = *curEntry;
        totalLength = curWord.segment.length;    /* Total length is at least segment */

        segmentLength = 0; /* Expect region header next */
        regionLength = 0;  /* Read segment next */
        if (curWord.segment.compoundSegment != 0)
        {
            if (totalLength > MAX_REG_CONFIG_LEN || totalLength == 0)
            {
                /* Too long or non-existent entry */
                return SetupResult_ErrorConfigLen;

            }

#ifdef LRF_DEBUG_TRACE
            Log_printf(RclCoreShort, Log_INFO, "New compound configration, length is %d", totalLength);
#endif

            /* Get subsegment length from next word */
            curEntry++;
            bufferAvailWords--; /* Decrement available words */
        }
        else
        {
            totalLength += 1; /* Simulate a compound header */
#ifdef LRF_DEBUG_TRACE
            Log_printf(RclCoreShort, Log_INFO, "New configration, length is %d", totalLength);
#endif
        }

        address = 0;
        operation = LRF_RegionOperation_Invalid;

    }
    else
    {
        segmentLength = state->segmentLength;
        regionLength  = state->regionLength;
        operation     = state->operation;
        address       = state->address;

        totalLength -= segmentLength;
        /* Check if we have words left to skip from last round */
        if (operation == LRF_RegionOperation_Skip)
        {
            bufferAvailWords -= regionLength;
            curEntry += regionLength;
            if (bufferAvailWords < 0)
            {
                /* Still more words to skip */
                segmentLength = -bufferAvailWords;       /* Number of words left of segment */
                /* Add unprocessed part of segment back */
                totalLength += segmentLength;
                state->regionLength = -bufferAvailWords; /* Signal number of words to skip */
                state->segmentLength = segmentLength;
                state->totalLength = totalLength;
                return SetupResult_Ok_Partial;
            }
            else
            {
                /* Start new segment */
                segmentLength = 0;
                operation = LRF_RegionOperation_Invalid;
            }
        }
#ifdef LRF_DEBUG_TRACE
        Log_printf(RclCoreShort, Log_INFO, "Resuming, totalLength:%d, segmentLength:%d address:0x%04X", totalLength, segmentLength, address & 0xffff);
#endif
    }
#endif

    /* While entire segment not parsed, go on. Can abort in the middle if error or
     * out of data */
#ifdef BUFFER_SPLIT_SUPPORT
    while (totalLength + segmentLength > 0)
#endif
    {
#ifdef BUFFER_SPLIT_SUPPORT
        if (segmentLength == 0)
#endif
        {
            /* If segment length is 0, process new segment  */
            LRF_ConfigWord curWord;
            curWord.value32 = *curEntry++;
            uint16_t featureMask = curWord.segment.featureMask;
            if ((curWord.segment.invertedFeatureMask == 0 &&
                ((featureMask != 0 && (featureMask & state->phyFeatures) == 0) ||
                    (featureMask == 0 && !state->includeBase))) ||
                (curWord.segment.invertedFeatureMask != 0 && (featureMask != (featureMask & ~state->phyFeatures))))
            {
                /* We skip it */
#ifdef LRF_DEBUG_TRACE
                Log_printf(RclCoreShort, Log_INFO, "Skipping segment length %1d because invertedFeatureMask = %1d, phyFeatures is 0x%04X and segment's featureMask is 0x%04X", curWord.segment.length, curWord.segment.invertedFeatureMask, state->phyFeatures, featureMask);
#endif
#ifdef BUFFER_SPLIT_SUPPORT
                uint32_t skipSegmentLength = curWord.segment.length;
                bufferAvailWords -= skipSegmentLength + 1;
                totalLength -= skipSegmentLength + 1;

                if (bufferAvailWords < 0)
                {
                    segmentLength = -bufferAvailWords; /* Signal number of words to skip */
                    regionLength = segmentLength;
                    operation = LRF_RegionOperation_Skip; /* Skip when resuming */
                    bufferAvailWords = 0;
                }
                else
                {
                    curEntry += skipSegmentLength;
                    segmentLength = 0;
                }
#else
                segmentLength = 0;
                return SetupResult_Ok;
#endif
            }
            else
            {
                segmentLength = curWord.segment.length;
#ifdef LRF_DEBUG_TRACE
                Log_printf(RclCoreShort, Log_INFO, "New segment, segmentLength:%d", segmentLength);
#endif

#ifdef BUFFER_SPLIT_SUPPORT
                if (segmentLength == 0 || segmentLength >= totalLength)
                {
                    return SetupResult_ErrorConfigLen;
                }
                bufferAvailWords--;
                totalLength -= segmentLength + 1;
#else
                if (segmentLength == 0 || segmentLength >= MAX_REG_CONFIG_LEN)
                {
                    return SetupResult_ErrorConfigLen;
                }
#endif
                regionLength = 0;  /* Read segment next */
            }
        }
        while (segmentLength > 0)
        {
#ifdef BUFFER_SPLIT_SUPPORT
            if (bufferAvailWords == 0)
            {
                /* Add unprocessed part of segment back */
                totalLength += segmentLength;
                state->totalLength = totalLength;
                state->segmentLength = segmentLength;
                state->regionLength = regionLength;
                state->operation = operation;
                state->address = address;

                return SetupResult_Ok_Partial;
            }
#endif
            /* If regionLength is 0 we are expecting a region header */
            if (regionLength == 0)
            {
                LRF_ConfigWord curWord;
                curWord.value32 = *curEntry++;
                regionLength = curWord.region.lengthMinus1 + 1;
                operation    = (LRF_RegionOperation) curWord.region.type;
                uint32_t regionStart  = curWord.region.startAddress;

                /* Accounting. Parsed a region header, so consume+increment word and
                 * parsed count */
                segmentLength--;
#ifdef BUFFER_SPLIT_SUPPORT
                bufferAvailWords--;
#endif
                /* Find correct region base address */
                if (operation >= SW_Region_Clear && operation != HW_Write_16bit_masked)
                {
                    if (operation >= Par_Region_Clear)
                    {
                        address = ((uintptr_t) &swParamList) + regionStart;
                        uint32_t regionActualLength = (operation == Par_Reference_32bit) ? 1 : regionLength;
                        if ((regionStart + (regionActualLength * sizeof(uint32_t))) > swParamListSz)
                        {
                            return SetupResult_ErrorParRange;
                        }
                    }
                    else
                    {
                        address = PBE_RAM_BASE_ADDR + regionStart;
                    }
                }
                else
                {
                    address  = LRF_BASE_ADDR + regionStart;
                }
#ifdef LRF_DEBUG_TRACE
                Log_printf(RclCoreShort, Log_INFO, "New region, regionLength:%d address:0x%04X, operation:%d", regionLength, address & 0xffff, operation);
#endif
            }

            /* Shuffle the data as requested */
            uint32_t numWords;
            switch (operation)
            {
                case HW_Region_Clear:
                case Par_Region_Clear:
                    {
                        if ((address & 0x03) != 0)
                        {
                            return SetupResult_ErrorElemAddrAlign;
                        }
                        volatile uint32_t *clear32 = (uint32_t *) address;
                        for (uint32_t i = 0; i < regionLength; i++)
                        {
#ifdef DeviceFamily_CC27XX
                            HWREG_WRITE_LRF(clear32++) = 0;
#else
                            *clear32++ = 0;
#endif //DeviceFamily_CC27XX
                        }
                        regionLength = 0;
                        numWords = 0;
                    }
                    break;

                case SW_Region_Clear:
                    {
                        if ((address & 0x01) != 0)
                        {
                            return SetupResult_ErrorElemAddrAlign;
                        }
                        volatile uint16_t *clear16 = (uint16_t *) address;
                        for (uint32_t i = 0; i < regionLength; i++)
                        {
#ifdef DeviceFamily_CC27XX
                            HWREGH_WRITE_LRF(clear16++) = 0;
#else
                            *clear16++ = 0;
#endif //DeviceFamily_CC27XX
                        }
                        regionLength = 0;
                        numWords = 0;
                    }
                    break;

                case HW_Write_16bit:
                case SW_Write_16bit:
                    /* Two output words per input words. If number of input
                        word is odd, last half-word is taken separately */
                    if ((address & 0x01) != 0)
                    {
                        return SetupResult_ErrorElemAddrAlign;
                    }
                    numWords = regionLength / 2;
                    break;

                case HW_Write_16bit_masked:
                    if ((address & 0x01) != 0)
                    {
                        return SetupResult_ErrorElemAddrAlign;
                    }
                    numWords = regionLength;
                    break;

                case Par_Reference_32bit:
                case HW_Write_32bit:
                case SW_Write_32bit:
                case Par_Write_32bit:
                case HW_Write_16bit_sparse:
                case SW_Write_16bit_sparse:
                    if ((address & 0x03) != 0)
                    {
                        return SetupResult_ErrorElemAddrAlign;
                    }
                    numWords = regionLength;
                    break;

                 default:
                    return SetupResult_ErrorElemType;
            }
            if (numWords > segmentLength)
            {
                return SetupResult_ErrorElemLen;
            }
#ifdef BUFFER_SPLIT_SUPPORT
            if ((int32_t)numWords > bufferAvailWords)
            {
                numWords = bufferAvailWords;
            }
#endif
            if (numWords > 0)
            {
                /* Write as much as we can */
                switch (operation)
                {
                    case HW_Write_16bit:
                        {
                            volatile uint32_t *dst32 = (volatile uint32_t *) address;
                            for (uint32_t i = 0; i < numWords; i++)
                            {
                                LRF_ConfigWord curWord;
                                curWord.value32 = *curEntry++;
#ifdef LRF_DEBUG_TRACE
                                Log_printf(RclCore, Log_INFO1, "HW_Write_16bit: %04X = %08X, ", dst32&0xFFFF, curWord.value32);
#endif

#ifdef DeviceFamily_CC27XX
                                HWREG_WRITE_LRF(dst32++) = curWord.value16[0];
                                HWREG_WRITE_LRF(dst32++) = curWord.value16[1];
#else
                                *dst32++ = curWord.value16[0];
                                *dst32++ = curWord.value16[1];
#endif //DeviceFamily_CC27XX
                            }
                            regionLength -= 2 * numWords;
                            address = (uintptr_t) dst32;
                        }
                        break;

                    case HW_Write_16bit_masked:
                        {
                            volatile uint32_t *dst32 = (volatile uint32_t *) address;
                            for (uint32_t i = 0; i < numWords; i++)
                            {
                                LRF_ConfigWord curWord;                  
                                curWord.value32 = *curEntry++;
#ifdef LRF_DEBUG_TRACE
                                Log_printf(RclCoreShort, Log_INFO1, "HW_Write_16bit_Masked: %04X: mask %04X value %04X, ",
                                    dst32&0xFFFF, curWord.masked.mask16, curWord.masked.value16);
#endif
                                /* On full setup, do not apply mask, as the register is assumed to start at 0 */
                                if (state->includeBase)
                                {
#ifdef DeviceFamily_CC27XX
                                    HWREG_WRITE_LRF(dst32++) = curWord.masked.value16;
#else
                                    *dst32++ = curWord.masked.value16;
#endif //DeviceFamily_CC27XX
                                }
                                else
                                {
                                    /* The type is intended for 16-bit registers with 32-bit aperture */
                                    /* If used on a true 32-bit register, the 16 most significant bits will not be changed */
#ifdef DeviceFamily_CC27XX
                                    uint32_t oldValue = HWREG_READ_LRF(dst32);
                                    HWREG_WRITE_LRF(dst32++) = (oldValue & ~curWord.masked.mask16) | curWord.masked.value16;
#else
                                    uint32_t oldValue = *dst32;
                                    *dst32++ = (oldValue & ~curWord.masked.mask16) | curWord.masked.value16;
#endif //DeviceFamily_CC27XX
                                }
                            }
                            regionLength -= numWords;
                            address = (uintptr_t) dst32;
                        }
                        break;

                    case SW_Write_16bit:
                        {
                            volatile uint16_t *dst16 = (volatile uint16_t *) address;
                            for (uint32_t i = 0; i < numWords; i++)
                            {
                                LRF_ConfigWord curWord;
                                curWord.value32 = *curEntry++;
#ifdef LRF_DEBUG_TRACE
                                Log_printf(RclCore, Log_INFO1, "SW_Write_16bit: %04X = %08X, ", dst16&0xFFFF, curWord.value32);
#endif

#ifdef DeviceFamily_CC27XX
                                HWREGH_WRITE_LRF(dst16++) = curWord.value16[0];
                                HWREGH_WRITE_LRF(dst16++) = curWord.value16[1];
#else
                                *dst16++ = curWord.value16[0];
                                *dst16++ = curWord.value16[1];
#endif //DeviceFamily_CC27XX
                            }
                            regionLength -= 2 * numWords;
                            address = (uintptr_t) dst16;
                        }
                        break;

                    case HW_Write_32bit:
                    case SW_Write_32bit:
                    case Par_Write_32bit:
                        {
                            volatile uint32_t *dst32 = (volatile uint32_t *) address;
                            for (uint32_t i = 0; i < numWords; i++)
                            {
#ifdef LRF_DEBUG_TRACE
                                switch(operation)
                                {
                                    case HW_Write_32bit:
                                        Log_printf(RclCore, Log_INFO1, "HW_Write_32bit: %04X = %08X", dst32&0xffff, *curEntry);
                                        break;
                                    case SW_Write_32bit:
                                        Log_printf(RclCore, Log_INFO1, "SW_Write_32bit: %04X = %08X", dst32&0xffff, *curEntry);
                                        break;
                                    case Par_Write_32bit:
                                        Log_printf(RclCore, Log_INFO1, "Par_Write_32bit: %04X = %08X", dst32&0xffff, *curEntry);
                                        break;
                                    default:
                                        break;
                                }
#endif
#ifdef DeviceFamily_CC27XX
                                HWREG_WRITE_LRF(dst32++) = *curEntry++;
#else
                                *dst32++ = *curEntry++;
#endif //DeviceFamily_CC27XX
                            }
                            regionLength -= numWords;
                            address = (uintptr_t) dst32;
                        }
                        break;

                    case Par_Reference_32bit:
                        {
#ifdef BUFFER_SPLIT_SUPPORT
                            /* Embedded constants must be contiguous */
                            if ((int32_t)regionLength > bufferAvailWords)
                            {
                                return SetupResult_ErrorParRange;
                            }
#endif
                            volatile uint32_t **dst32 = (volatile uint32_t **) address;
                            *dst32 = curEntry;
                            regionLength -= numWords;
                            curEntry += numWords;
#ifdef LRF_DEBUG_TRACE
                            Log_printf(RclCore, Log_INFO1, "Par_Reference_32bit: %04X = %08X", address, *dst32);
#endif
                        }
                        break;

                    case HW_Write_16bit_sparse:
                        for (uint32_t i = 0; i < numWords; i++)
                        {
                            LRF_ConfigWord curWord;
                            curWord.value32 = *curEntry++;
                            uint32_t curAddress = curWord.sparse.address;
                            if ((curAddress & 3) == 0)
                            {
                                /* Word aligned access to hardware */
                                uint32_t *dst32 = (uint32_t *)(address + curAddress);
#ifdef DeviceFamily_CC27XX
                                HWREG_WRITE_LRF(dst32) = curWord.sparse.value16;
#else
                                *dst32          = curWord.sparse.value16;
#endif //DeviceFamily_CC27XX
                            }
                            else if ((curAddress & 1) == 0)
                            {
                                /* Halfword aligned */
                                uint16_t *dst16 = (uint16_t *)(address + curAddress);
#ifdef DeviceFamily_CC27XX
                                HWREGH_WRITE_LRF(dst16) = curWord.sparse.value16;
#else
                                *dst16          = curWord.sparse.value16;
#endif //DeviceFamily_CC27XX
                            }
                            else
                            {
                                return SetupResult_ErrorElemAddrAlign;
                            }
#ifdef LRF_DEBUG_TRACE
                            Log_printf(RclCoreShort, Log_INFO, "HW_Write_16bit_sparse: 0x%04X = 0x%04X", curAddress, curWord.sparse.value16);
#endif
                        }
                        regionLength -= numWords;
                        break;

                    case SW_Write_16bit_sparse:
                        for (uint32_t i = 0; i < numWords; i++)
                        {
                            LRF_ConfigWord curWord;
                            curWord.value32 = *curEntry++;
                            if ((curWord.sparse.address & 1) == 0)
                            {
                                /* Word aligned 16 bit access  */
                                uint16_t *dst16 = (uint16_t *)(address + curWord.sparse.address);
#ifdef DeviceFamily_CC27XX
                                HWREGH_WRITE_LRF(dst16) = curWord.sparse.value16;
#else
                                *dst16          = curWord.sparse.value16;
#endif
                            }
                            else
                            {
                                return SetupResult_ErrorElemAddrAlign;
                            }
#ifdef LRF_DEBUG_TRACE
                            Log_printf(RclCoreShort, Log_INFO, "SW_Write_16bit_sparse: 0x%04X = 0x%04X", curWord.sparse.address, curWord.sparse.value16);
#endif
                        }
                        regionLength -= numWords;
                        break;

                    default:
                        break;
                }
#ifdef BUFFER_SPLIT_SUPPORT
                bufferAvailWords -= numWords;
#endif
                segmentLength -= numWords;
            }
            /* Write straggler for 16-bit */
            if (regionLength == 1 &&
#ifdef BUFFER_SPLIT_SUPPORT
                bufferAvailWords > 0 &&
#endif
                (operation == HW_Write_16bit || operation == SW_Write_16bit))
            {
                if (segmentLength < 1)
                {
                    return SetupResult_ErrorElemLen;
                }
                if (operation == SW_Write_16bit)
                {
                    volatile uint16_t *dst16 = (volatile uint16_t *) address;
                    LRF_ConfigWord curWord;
                    curWord.value32 = *curEntry++;
#ifdef DeviceFamily_CC27XX
                    HWREGH_WRITE_LRF(dst16) = curWord.value16[0];
#else
                    *dst16 = curWord.value16[0];
#endif //DeviceFamily_CC27XX
#ifdef LRF_DEBUG_TRACE
                    Log_printf(RclCoreShort, Log_INFO, "SW_Write_16bit: 0x%04X = 0x%04X, ", dst16&0xFFFF, curWord.value16[0]);
#endif
                }
                else
                {
                    volatile uint32_t *dst32 = (volatile uint32_t *) address;
                    LRF_ConfigWord curWord;
                    curWord.value32 = *curEntry++;
#ifdef DeviceFamily_CC27XX
                    HWREG_WRITE_LRF(dst32) = curWord.value16[0];
#else
                    *dst32 = curWord.value16[0];
#endif //DeviceFamily_CC27XX
#ifdef LRF_DEBUG_TRACE
                    Log_printf(RclCoreShort, Log_INFO, "HW_Write_16bit: 0x%04X = 0x%04X, ", dst32&0xFFFF, curWord.value16[0]);
#endif
                }
                regionLength -= 1;
#ifdef BUFFER_SPLIT_SUPPORT
                bufferAvailWords--;
#endif
                segmentLength--;
            }
        }
        /* Done with this segment and its header */
#ifdef BUFFER_SPLIT_SUPPORT
        if (bufferAvailWords == 0 && totalLength > 0)
        {
            state->totalLength = totalLength;
            state->segmentLength = 0;
            state->regionLength = 0;
            state->operation = operation;

            return SetupResult_Ok_Partial;
        }
#endif
    }

#ifdef BUFFER_SPLIT_SUPPORT
    RCL_Debug_assert(totalLength == 0);

    state->totalLength = 0;
#endif

    return SetupResult_Ok;
}

LRF_TxPowerTable_Entry LRF_TxPowerTable_findValue(const LRF_TxPowerTable *table, LRF_TxPowerTable_Index powerLevel)
{
    if (powerLevel.rawValue == LRF_TxPower_Use_Raw.rawValue)
    {
        /* Handle special input argument - return raw tx power setting if supported,
           invalid value otherwise. */
        return LRF_getRawTxPower();
    }
    else if (table != NULL && table->numEntries > 0 && powerLevel.rawValue <= LRF_TxPower_Use_Max.rawValue)
    {
        if (powerLevel.rawValue == LRF_TxPower_Use_Min.rawValue)
        {
            /* Handle special input argument - return lowest possible tx power. */
            Log_printf(RclCore, Log_INFO, "Tx table search: lowest possible");
            return table->powerTable[0];
        }
        else if (powerLevel.rawValue == LRF_TxPower_Use_Max.rawValue)
        {
            /* Handle special input argument - return highest possible tx power. */
            Log_printf(RclCore, Log_INFO, "Tx table search: highest possible");
            return table->powerTable[table->numEntries - 1];
        }
        else if (table->powerTable[0].power.rawValue > powerLevel.rawValue)
        {
            /* If the first entry is already larger, then the requested
            power level is invalid. */
            Log_printf(RclCore, Log_INFO, "Tx table search: %d too low", powerLevel.rawValue);
            return LRF_TxPowerEntry_INVALID_VALUE;
        }
        else
        {
            for (size_t i = 1; i < table->numEntries; i++)
            {
                /* Search for the first entry higher than target power level. */
                if (table->powerTable[i].power.rawValue > powerLevel.rawValue)
                {
                    /* Return last entry that was not larger than target power level. */
                    return table->powerTable[i - 1];
                }
            }
            if (table->powerTable[table->numEntries - 1].power.rawValue == powerLevel.rawValue)
            {
                /* Return highest value if it matches the requested power level. */
                return table->powerTable[table->numEntries - 1];
            }
            else
            {
                /* If no entries are larger than target power level, then the requested
                power level is invalid. */
                Log_printf(RclCore, Log_INFO, "Tx table search: %d too high", powerLevel.rawValue);
                return LRF_TxPowerEntry_INVALID_VALUE;
            }
        }
    }
    else
    {
        /* Return invalid value. This covers LRF_TxPower_Use_None. */
        return LRF_TxPowerEntry_INVALID_VALUE;
    }
}
