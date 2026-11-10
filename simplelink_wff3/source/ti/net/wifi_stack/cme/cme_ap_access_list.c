/*
 * Copyright (c) 2024, Texas Instruments Incorporated
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
///**********************************************************************************************************************
//
//  FILENAME:       cme_ap_access_list.c
//
//  DESCRIPTION:    Implementation of AP access list - White list or black list
//
//                  After deauth / disassoc frame was send to the peer, no data frame should be transmitted.
//                  This module runs in wlan lp thread context
//
//   Copyright (c) 2012 Texas Instruments Inc.
//   All Rights Reserved This program is the confidential and proprietary
//   product of Texas Instruments Inc.  Any Unauthorized use, reproduction or
//   transfer of this program is strictly prohibited.
//
//
//***********************************************************************************************************************/

#ifndef TI_STA_ONLY_BUILD

#include <stdio.h>
#include "cme_internal_api.h"
#include "cme_dispatcher_api.h"
#include "gtrace.h"
#include "errors.h"
#include "wlan_if.h"
// Prototypes
BOOLEAN CME_IsEntryInArrList(u8* pList, u8 numEntriesInList,  u8* pEntry, u8 entryLen, uint8_t* index);
int32_t CME_DelMacFromList(uint8_t* pMacAddress,uint32_t index, BOOLEAN UpdateFlash);
int16_t CME_GetList(uint8_t listType,
                  uint8_t* pList,
                  int16_t ListIndex,
                  int16_t AllocatedBufferSize);
int32_t CME_AddMacToList(uint8_t* pMacAddress, BOOLEAN UpdateFlash);
int32_t CME_SetListMode(uint8_t ListMode, BOOLEAN UpdateFlash);
int32_t CME_AddWildcardToList(uint8_t* pMacAddress, uint8_t* pMask, BOOLEAN UpdateFlash);
int32_t CME_DelWildcardFromList(uint8_t* pMacAddress, uint8_t* pMask, uint32_t index, BOOLEAN UpdateFlash);
int32_t CME_DelList(uint8_t listType, BOOLEAN UpdateFlash);
//static cmeBwListCB_t* getBwListWorkingCopy(void);
//static void freeBwListWorkingCopy(cmeBwListCB_t* pWorkingCopy);


// Globals
// Control block for the Black / White list.
cmeBwListCB_t*      gBwListCB_ull ; //Should be ULL since we use this to check if white list exists, even in STA role
                                                  //(user can set whitelist configuration also when AP role is disabled. It is just
                                                  //written to the flash).


/******************************************************************************
  Function          : CME_BwListSetParameter

  Description       : Sets any of the Black / White list parameters exposed
                      to host / internal dispatcher.

  Input parameters  : CalledFromHost - Used to determine flash access priority
                          and endianness conversion.
                      IdAndOption - Unified value of the ConfigId and ConfigOpt
                          fields as defined in the host header files.
                      Length    - Size of the input buffer.
                      pNewValue - Input buffer with the new value. Interpreted
                      according to parameter type.

  Output parameters : None.
  Return value      : 0 if OK, otherwise negative value according to
                      HostShared/HostIncludes/errors.h
*****************************************************************************/
int32_t CME_BwListSetParameter(BOOLEAN CalledFromHost,
                             uint32_t IdAndOption,
                             uint16_t Length,
                             void* pNewValue)
{
    HOOK(HOOK_IN_CME_AP_ACCESS_LIST);
    return 0;
#if 0 // TODO:  need to implement
    int32_t status;
    BOOLEAN UpdateFlash;

    GTRACE(GRP_SL_DISPATCH,
                   "WLAN B/W list SET handler invoked for "
                   "ID and option 0x%x. Caller=%d",
                   IdAndOption, CalledFromHost);

    switch(IdAndOption)
    {
        case ID_AND_OPTION(SL_WLAN_CFG_AP_ID,
                           WLAN_AP_ACCESS_LIST_ADD_MAC):
        {
            SlWlanApAccessListAddEntry_t* pEntry;

            pEntry = pNewValue;

            if (WLAN_AP_ACCESS_LIST_UPDATE_RAM_FLASH
                == pEntry->UpdateRamFlash)
            {
                UpdateFlash = TRUE;
            }
            else
            {
                UpdateFlash = FALSE;
            }

            status = CME_AddMacToList(pEntry->MacAddr, UpdateFlash);
            GTRACE(GRP_SL_DISPATCH, "Invoked CME_AddMacToList, res=%d", status);

            break;
        }

        case ID_AND_OPTION(SL_WLAN_CFG_AP_ID,
                           WLAN_AP_ACCESS_LIST_DEL_MAC):
        {
            SlWlanApAccessListDelEntryByAddress_t* pEntry;

            pEntry = pNewValue;

            if (WLAN_AP_ACCESS_LIST_UPDATE_RAM_FLASH
                            == pEntry->UpdateRamFlash)
            {
                UpdateFlash = TRUE;
            }
            else
            {
                UpdateFlash = FALSE;
            }

            status = CME_DelMacFromList(pEntry->MacAddr, 0, UpdateFlash);
            GTRACE(GRP_SL_DISPATCH, "Invoked CME_DelMacFromList, res=%d", status);

            break;
        }
        case ID_AND_OPTION(SL_WLAN_CFG_AP_ID,
                           WLAN_AP_ACCESS_LIST_ADD_WILDCARD):
        {
            SlWlanApAccessListAddWildcard_t* pEntry;

            pEntry = pNewValue;

            if (WLAN_AP_ACCESS_LIST_UPDATE_RAM_FLASH
                == pEntry->UpdateRamFlash)
            {
                UpdateFlash = TRUE;
            }
            else
            {
                UpdateFlash = FALSE;
            }

            status = CME_AddWildcardToList(pEntry->MacAddr, pEntry->Mask, UpdateFlash);
            GTRACE(GRP_SL_DISPATCH, "Invoked CME_AddWildcardToList, res=%d", status);

            break;
        }

        case ID_AND_OPTION(SL_WLAN_CFG_AP_ID,
                           WLAN_AP_ACCESS_LIST_DEL_WILDCARD):
        {
            SlWlanApAccessListDelWildcard_t* pEntry;

            pEntry = pNewValue;

            if (WLAN_AP_ACCESS_LIST_UPDATE_RAM_FLASH
                            == pEntry->UpdateRamFlash)
            {
                UpdateFlash = TRUE;
            }
            else
            {
                UpdateFlash = FALSE;
            }

            status = CME_DelWildcardFromList(pEntry->MacAddr, pEntry->Mask, 0, UpdateFlash);
            GTRACE(GRP_SL_DISPATCH, "Invoked CME_DelWildcardFromList, res=%d", status);

            break;
        }

        case ID_AND_OPTION(SL_WLAN_CFG_AP_ID,
                           WLAN_AP_ACCESS_LIST_DEL_IDX):
        {
            SlWlanApAccessListDelEntryByIndex_t* pEntry;

            pEntry = pNewValue;

            if (WLAN_AP_ACCESS_LIST_UPDATE_RAM_FLASH
                            == pEntry->UpdateRamFlash)
            {
                UpdateFlash = TRUE;
            }
            else
            {
                UpdateFlash = FALSE;
            }

            status = CME_DelMacFromList(NULL, pEntry->Index, UpdateFlash);

            break;
        }

        case ID_AND_OPTION(SL_WLAN_CFG_AP_ID,
                           WLAN_AP_ACCESS_LIST_DEL_WILDCARD_BY_INDEX):
        {
            SlWlanApAccessListDelEntryByIndex_t* pEntry;

            pEntry = pNewValue;

            if (WLAN_AP_ACCESS_LIST_UPDATE_RAM_FLASH
                            == pEntry->UpdateRamFlash)
            {
                UpdateFlash = TRUE;
            }
            else
            {
                UpdateFlash = FALSE;
            }

            status = CME_DelWildcardFromList(NULL, NULL, pEntry->Index, UpdateFlash);

            break;
        }

        case ID_AND_OPTION(SL_WLAN_CFG_AP_ID,
                           WLAN_AP_ACCESS_LIST_MODE):
        {
            SlWlanApAccessListSetMode_t* pModeData;

            pModeData = pNewValue;

            if (WLAN_AP_ACCESS_LIST_UPDATE_RAM_FLASH
                            == pModeData->UpdateRamFlash)
            {
                UpdateFlash = TRUE;
            }
            else
            {
                UpdateFlash = FALSE;
            }

            status = CME_SetListMode(pModeData->Mode, UpdateFlash);

            break;
        }
        case ID_AND_OPTION(SL_WLAN_CFG_AP_ID,
                           WLAN_AP_ACCESS_LIST_DEL_MAC_LIST):
        {
            SlWlanApAccessListDelList_t* pParam;

            pParam = pNewValue;

            if (WLAN_AP_ACCESS_LIST_UPDATE_RAM_FLASH
                            == pParam->UpdateRamFlash)
            {
                UpdateFlash = TRUE;
            }
            else
            {
                UpdateFlash = FALSE;
            }

            status = CME_DelList(CME_BW_LIST_TYPE_MAC, UpdateFlash);

            break;
        }
        case ID_AND_OPTION(SL_WLAN_CFG_AP_ID,
                           WLAN_AP_ACCESS_LIST_DEL_WILDCARD_LIST):
        {
            SlWlanApAccessListDelList_t* pParam;

            pParam = pNewValue;

            if (WLAN_AP_ACCESS_LIST_UPDATE_RAM_FLASH
                            == pParam->UpdateRamFlash)
            {
                UpdateFlash = TRUE;
            }
            else
            {
                UpdateFlash = FALSE;
            }

            status = CME_DelList(CME_BW_LIST_TYPE_WILDCARD, UpdateFlash);

            break;
        }

        default:
        {
            status = SL_ERROR_INVALID_OPCODE;

            break;
        }
    }

    return status;
#endif
}


/******************************************************************************
  Function          : CME_WlanGetParameter

  Description       : Retuens any of the Black / White list parameters exposed
                      to host / internal dispatcher.

  Input parameters  : CalledFromHost- Determines flash access priority.
                      IdAndOption - Unified value of the ConfigId and ConfigOpt
                          fields as defined in the host header files.
                      pLength       - Size of the buffer allocated for
                                      response.
                      pCurrentValue - Buffer where the requested value will be
                                      written to.

  Output parameters : pLength       - Actual size of the response (<= size
                                      allocated by caller).

  Return value      : 0 if OK, otherwise negative value according to
                      HostShared/HostIncludes/errors.h
*****************************************************************************/
int32_t CME_BwListGetParameter(BOOLEAN CalledFromHost,
                             uint32_t IdAndOption,
                             uint16_t* pLength,
                             void* pCurrentValue)
{
    HOOK(HOOK_IN_CME_AP_ACCESS_LIST);

    return 0;
#if 0  // Razb: need to implement
    uint16_t id;
    uint16_t listIndex;
    uint16_t resultSize;
    int16_t  retVal;
    int32_t  status = SL_RET_CODE_OK;

    GTRACE(GRP_SL_DISPATCH,
           "WLAN B/W list GET handler invoked for "
           "ID and option 0x%x. Caller=%d",
           IdAndOption, CalledFromHost);

    id = IdAndOption & 0xFFFF;

    switch(id)
    {
        case SL_WLAN_CFG_AP_ID:
        {
            // This branch is only reached if this function is called from
            // CME_WlanGetParameter (see the call location for extra info).

            switch (IdAndOption)
            {
                case ID_AND_OPTION(SL_WLAN_CFG_AP_ID,
                                   WLAN_AP_ACCESS_LIST_NUM_ENTRIES):
                {
                    int16_t* pListSize;
                    pListSize = pCurrentValue;

                    retVal = CME_GetList(CME_BW_LIST_TYPE_MAC, NULL, 0, 0);

                    if (retVal < 0)
                    {
                        resultSize = 0;
                        status = SL_ERROR_STATUS_ERROR;
                    }
                    else
                    {
                        resultSize = sizeof(int16_t);
                        *pListSize = retVal;
                    }

                    break;
                }

                case ID_AND_OPTION(SL_WLAN_CFG_AP_ID,
                                   WLAN_AP_ACCESS_LIST_WILDCARD_NUM_ENTRIES):
                {
                    int16_t* pListSize;
                    pListSize = pCurrentValue;

                    retVal = CME_GetList(CME_BW_LIST_TYPE_WILDCARD, NULL, 0, 0);

                    if (retVal < 0)
                    {
                        resultSize = 0;
                        status = SL_ERROR_STATUS_ERROR;
                    }
                    else
                    {
                        resultSize = sizeof(int16_t);
                        *pListSize = retVal;
                    }

                    break;
                }

                default:
                {
                    resultSize = 0;
                    status = SL_ERROR_INVALID_OPCODE;
                }
            }

            break;
        }

        case SL_WLAN_CFG_AP_ACCESS_LIST_ID:
        {
            listIndex = (IdAndOption >> 16) & 0xFFFF;

            retVal = CME_GetList(CME_BW_LIST_TYPE_MAC, pCurrentValue, listIndex, *pLength);
            if (retVal < 0)
            {
                resultSize = 0;
                status = SL_ERROR_STATUS_ERROR;
            }
            else
            {
                resultSize = retVal;
            }

            break;
        }

        case SL_WLAN_CFG_AP_ACCESS_LIST_WILDCARD_LIST_ID:
        {
            listIndex = (IdAndOption >> 16) & 0xFFFF;

            retVal = CME_GetList(CME_BW_LIST_TYPE_WILDCARD, pCurrentValue, listIndex, *pLength);
            if (retVal < 0)
            {
                resultSize = 0;
                status = SL_ERROR_STATUS_ERROR;
            }
            else
            {
                resultSize = retVal;
            }

            break;
        }

        default:
        {
            resultSize = 0;
            status = SL_ERROR_INVALID_OPCODE;
        }
    }

    *pLength = resultSize;

    return status;
#endif
}

//Apply mask to a buffer
static void mem_applyMask (u8* dest, u8* src, u8* mask, u8 len)
{
    HOOK(HOOK_IN_CME_AP_ACCESS_LIST);

    int i;

    for (i=0; i<len; i++)
    {
        *dest = *src & *mask;
        dest++;
        src++;
        mask++;
    }
}

/******************************************************************************
  Function          : CME_IsMacAllowed

  Description       : Called from the CME module to test if a given
                      MAC address is allowed to be associated. This function
                      assumes AP is up and the global CB of B/W list
                      is allocated.

  Input parameters  : pMacAddress - MAC address to test.

  Output parameters : None

  Return value      : TRUE if MAC can be associated, FALSE otherwise.

******************************************************************************/
BOOLEAN CME_IsMacAllowed(uint8_t* pMacAddress)
{
    BOOLEAN allowed = TRUE;
    BOOLEAN macInList = FALSE; //mac is in mac list
    BOOLEAN foundMatch = FALSE; //found match in wildcard
    uint8_t idx;
    int8_t i;
    macAddress_t macAddrMasked;
    macAddress_t wildcardMasked;

    CME_generalSemaphoreTake();

    if (gBwListCB_ull)
    {
        if (gBwListCB_ull->Header.ListMode != WLAN_AP_ACCESS_LIST_MODE_DISABLED)
        {
            //Check if mac address is in mac list
            macInList = CME_IsEntryInArrList((u8*)gBwListCB_ull->pMacList, gBwListCB_ull->Header.macListNumEntries,  pMacAddress, MAC_ADDR_LEN, &idx);

            if (!macInList)
            {
                //Check for wildcard match
                for (i=0; i < gBwListCB_ull->Header.wildcardListNumEntries; i++)
                {
                    mem_applyMask ((u8*)&macAddrMasked, pMacAddress, gBwListCB_ull->pWildcardList[i].mask, MAC_ADDR_LEN); //mask and mac has the same len
                    mem_applyMask ((u8*)&wildcardMasked, (u8*) gBwListCB_ull->pWildcardList[i].macAddr, gBwListCB_ull->pWildcardList[i].mask, MAC_ADDR_LEN); //mask and mac has the same len

                    if (0 == os_memcmp(macAddrMasked, wildcardMasked, MAC_ADDR_LEN))
                    {
                        foundMatch = TRUE;
                        break;
                    }
                }
            }

            if (gBwListCB_ull->Header.ListMode == WLAN_AP_ACCESS_LIST_MODE_ALLOW_LIST)
            {
                //WhiteList

                if ((!macInList) && (!foundMatch))
                {
                    //not in whitelist, don't allow.
                    allowed = FALSE;
                }
            }
            else if (gBwListCB_ull->Header.ListMode == WLAN_AP_ACCESS_LIST_MODE_DENY_LIST)
            {
                //Blacklist
                if ((macInList) || (foundMatch))
                {
                    //in blacklist, don't allow
                    allowed = FALSE;
                }

            }
            GTRACE(GRP_AP_ACCESS_LIST,"AP access List: Is mac allowed: %x:%x:%x:%x:%x:%x", pMacAddress[0],
                                                                                           pMacAddress[1],
                                                                                           pMacAddress[2],
                                                                                           pMacAddress[3],
                                                                                           pMacAddress[4],
                                                                                           pMacAddress[5]);
            GTRACE(GRP_AP_ACCESS_LIST,"AP access List: List type %d, allowed %d", gBwListCB_ull->Header.ListMode,
                                                                                  allowed);
        }
    }

    CME_generalSemaphoreRelease();

    return allowed;
}


/******************************************************************************
  Function          : CME_IsEntryInList

  Description       : Check if an entry exists in the array list.

  Input parameters  : u8* pList - List to search
                      u8 numEntriesInList - num of entries in list
                      u8* pEntry - to search.
                      u8 entryLen
                      uint8_t* index [out] - In case it was found, return the index in list

  Output parameters : None

  Return value      : TRUE if entry is in the list, FALSE otherwise.
******************************************************************************/
BOOLEAN CME_IsEntryInArrList(u8* pList, u8 numEntriesInList,  u8* pEntry, u8 entryLen, uint8_t* index)
{
    HOOK(HOOK_IN_CME_AP_ACCESS_LIST);

    BOOLEAN result = FALSE;
    uint8_t i;
    u8 *buf = pList;

    if (numEntriesInList > 0)
    {
        for (i=0;i < numEntriesInList;i++)
        {
            if (0 == os_memcmp(buf, pEntry, entryLen))
            {
                result = TRUE;
                *index = i;
                break;
            }

            buf+=entryLen;
        }
    }

    return (result);
}

/******************************************************************************
  Function          : CME_AddEntryToArrList

  Description       : Add an entry to an array list. Entry is added at the end,
                      buffer is reallocated as needed.

  Input parameters  : u8** pList - List to add the entry into
                      u8* numEntriesInList - pointer to num of entries in list
                      u8* pEntry - entry.
                      u8 entryLen - entry len

  Output parameters : numEntriesInList is updated by the function.

  Return value      : 0 on Success, -1 on error
******************************************************************************/
int32_t CME_AddEntryToArrList(u8** pList, u8* numEntriesInList,  u8* pEntry, u8 entryLen)
{
    HOOK(HOOK_IN_CME_AP_ACCESS_LIST);

    u8* newList;

    //Realloc buffer and add the new entry at the end of the array

    newList = os_realloc(*pList, (*numEntriesInList *  entryLen + entryLen));

    if (newList == NULL)
    {
        //error, do nothing...
        return -1;
    }

    *pList = newList;

    //Add the new mac at the end of the buffer
    memcpy(*pList + *numEntriesInList * entryLen, pEntry, entryLen);
    (*numEntriesInList)++;

    return 0;
}

/******************************************************************************
  Function          : CME_RemoveEntryFromArrList

  Description       : Remove an entry from an array list.
                      Buffer is reallocated as needed.

  Input parameters  : u8** pList - List to remove the entry from
                      u8* numEntriesInList - pointer to num of entries in list
                      u8 idx - index of the entry to be removed

  Output parameters : numEntriesInList is updated by the function.

  Return value      : None
******************************************************************************/
void CME_RemoveEntryFromArrList(u8** pList, u8* numEntriesInList,  u8 idx, u8 entryLen)
{
    HOOK(HOOK_IN_CME_AP_ACCESS_LIST);

    if (*numEntriesInList == 1)
    {
        //This is the only one in the list, just remove it and free the list.
        (*numEntriesInList)--;
        os_free(*pList);
        *pList = NULL;
    }
    else
    {
        //Check if it is not the last entry (If yes, just realloc).
        if (idx != *numEntriesInList-1)
        {
            //Not the last entry, copy the last entry instead of the one we are removing. and then realloc.
            os_memcpy (*pList + idx * entryLen, //entry to remove
                       *pList + (*numEntriesInList-1) * entryLen, //Last entry in the buff
                       entryLen);
        }

        (*numEntriesInList)--;

        //Realloc buffer
        *pList = os_realloc(*pList, (*numEntriesInList) *  entryLen);
    }
}

/******************************************************************************
  Function          : getBwListWorkingCopy

  Description       : Returns pointer to a cmeBwListCB_t representing
                      the active control block. It is either the global
                      control block or a temporary buffer filled from flash.
                      In any case, the opposite function (freeBwListWorkingCopy)
                      must be called to release any resources taken.

  Input parameters  : None

  Output parameters : None

  Return value      : Pointer to the working copy.

******************************************************************************/
static cmeBwListCB_t* getBwListWorkingCopy(void)
{
    HOOK(HOOK_IN_CME_AP_ACCESS_LIST);

    cmeBwListCB_t*  pBwListWorkingCopy = NULL;

    if (NULL != gBwListCB_ull)
    {
        // Work on the active RAM copy
        pBwListWorkingCopy = gBwListCB_ull;
    }
    else
    {
        pBwListWorkingCopy = os_zalloc(sizeof(cmeBwListCB_t));

        if (pBwListWorkingCopy)
        {
            ReadPieAndMacListFromFlash(pBwListWorkingCopy, NULL, TRUE);
        }
    }

    return pBwListWorkingCopy;
}


/******************************************************************************
  Function          : freeBwListWorkingCopy

  Description       : Frees any memory allocated by
                      getBwListWorkingCopy.

  Input parameters  : Pointer to the working copy.

  Output parameters : None

  Return value      : None.

******************************************************************************/
static void freeBwListWorkingCopy(cmeBwListCB_t* pWorkingCopy)
{
    HOOK(HOOK_IN_CME_AP_ACCESS_LIST);

    if (NULL == gBwListCB_ull)
    {
        if (pWorkingCopy!=NULL)
        {
            // Free all temporary buffers.
            if(NULL != pWorkingCopy->pMacList)
            {
                os_free(pWorkingCopy->pMacList);
                pWorkingCopy->pMacList = NULL; // Pointelss but prevents C&P errors.
            }

            if(NULL != pWorkingCopy->pWildcardList)
            {
                os_free(pWorkingCopy->pWildcardList);
                pWorkingCopy->pWildcardList = NULL; // Pointelss but prevents C&P errors.
            }

            os_free(pWorkingCopy);
        }
    }
    else
    {
        // If working on the global buffer then do nothing as it is in use.
    }
}

/******************************************************************************
  Function          : CME_SetListMode

  Description       : Called from the dispatcher to set list mode.

  Input parameters  : ListMode - 0 to disable the mechanism,
                          1 for black list , 2 for white list.
                      UpdateFlash - FALSE if only RAM list is to be updated,
                      TRUE if save the resulting list to flash as well.

  Output parameters : None

  Return value      : 0 if successfull, -1 otherwise.

******************************************************************************/
int32_t CME_SetListMode(uint8_t ListMode, BOOLEAN UpdateFlash)
{
    cmeBwListCB_t* pBwListWorkingCopy = NULL;
    int32_t status=0;

    HOOK(HOOK_IN_CME_AP_ACCESS_LIST);

    GTRACE(GRP_AP_ACCESS_LIST,"AP access List: Set List mode, %d", ListMode);

    if (NULL != gBwListCB_ull)
    {
        CME_generalSemaphoreTake(); //We take the semaphore only in AP mode, where we really have an access list in memory (and CME_IsMacAllowed can be called from cme context).
    }
    else if (FALSE == UpdateFlash)
    {
        // This is an illegal combination as there is no working
        // copy and flash update is not needed. Nothing to do.
        status = -2;
    }

    if (0 == status)
    {
        pBwListWorkingCopy = getBwListWorkingCopy();
        if (pBwListWorkingCopy)
        {
            pBwListWorkingCopy->Header.ListMode = ListMode;
        }
    }

    if (NULL != gBwListCB_ull)
    {
        CME_generalSemaphoreRelease();
    }

    if (UpdateFlash)
    {
        status = WritePieAndMacListToFlash(pBwListWorkingCopy, NULL, TRUE);
    }

    freeBwListWorkingCopy(pBwListWorkingCopy);

    return status;
}


/******************************************************************************
  Function          : CME_AddMacToList

  Description       : Called to add new entry to list.
                      If list already exists in RAM (AP is running then this
                      copy will be updated (and written to flash if requested).
                      Otherwise, the flash data will be loaded to temp buffer,
                      updated and written back.

  Input parameters  : pMacAddress - MAC address to add.
                      UpdateFlash - FALSE if only RAM list is to be updated,
                      TRUE if save the resulting list to flash as well.

  Output parameters : None

  Return value      : 0 on success or MAC is already present.
                      -1 on other errors
                      -2 if no working copy exists in RAM (AP is down) and
                         flash update flag is 0.
                      -3 if list is full
******************************************************************************/
int32_t CME_AddMacToList(uint8_t* pMacAddress, BOOLEAN UpdateFlash)
{
    int32_t status=0;
    cmeBwListCB_t*  pBwListWorkingCopy = NULL;
    uint8_t idx;
    BOOLEAN listUpdated = FALSE;

    HOOK(HOOK_IN_CME_AP_ACCESS_LIST);

    GTRACE(GRP_AP_ACCESS_LIST,"AP access List: Add Mac: %x:%x:%x:%x:%x:%x", pMacAddress[0],
                                                                            pMacAddress[1],
                                                                            pMacAddress[2],
                                                                            pMacAddress[3],
                                                                            pMacAddress[4],
                                                                            pMacAddress[5]);

    if (NULL != gBwListCB_ull)
    {
        CME_generalSemaphoreTake();
    }
    else if (FALSE == UpdateFlash)
    {
        // This is an illegal combination as there is no working
        // copy and flash update is not needed. Nothing to do.
        status = -2;
    }

    if (0 == status)
    {
        pBwListWorkingCopy = getBwListWorkingCopy();

        if (!pBwListWorkingCopy)
        {
            status = -1;
        }
        else
        {
            //Check if mac address is in the list
            if (CME_IsEntryInArrList((u8*)pBwListWorkingCopy->pMacList, pBwListWorkingCopy->Header.macListNumEntries,  pMacAddress, MAC_ADDR_LEN, &idx))
            {
                //Already in the list, no need to add.
                status = 0;
            }
            else
            {
                if (pBwListWorkingCopy->Header.macListNumEntries == CME_BW_MAX_MAC_ENTRIES)
                {
                    //List is full
                    status = -3;
                }
                else
                {
                    status = CME_AddEntryToArrList((u8**)&pBwListWorkingCopy->pMacList,
                                                   &pBwListWorkingCopy->Header.macListNumEntries,
                                                   pMacAddress, sizeof (BwList_macEntry)); //No need to 'build' a BwList_macEntry since it is identical to mac addr
                    listUpdated = TRUE;
                }
            }
        }
    }
    if (NULL != gBwListCB_ull)
    {
        // Release semaphore if taken
        CME_generalSemaphoreRelease();
    }

    if (UpdateFlash && listUpdated)
    {
        WritePieAndMacListToFlash(pBwListWorkingCopy, NULL, TRUE);
    }

    freeBwListWorkingCopy(pBwListWorkingCopy);

    return status;
}


/******************************************************************************
  Function          : CME_DelMacFromList

  Description       : Called to remove entry from list, by mac address or index

  Input parameters  : pMacAddress - The address to delete. If NULL, address
                      is given by index. The pointer should point to a user
                      provided buffer and not inside the list structure.
                      ListIndex - If pMacAddress is NULL, this number indicates
                      the index of the MAC address inside the list to delete.
                      This is the same number returned by CME_AddMacToList.
                      UpdateFlash - FALSE if only RAM list is to be updated,
                      TRUE if save the resulting list to flash as well.

  Output parameters : None

  Return value      : 0 if successfull,
                      -1 on other errors
                      -2 if no working copy exists in RAM (AP is down) and
                         flash update flag is 0.
                      -3 if address is not found,
******************************************************************************/
int32_t CME_DelMacFromList(uint8_t* pMacAddress,
                         uint32_t index,
                         BOOLEAN UpdateFlash)
{
    cmeBwListCB_t*  pBwListWorkingCopy = NULL;
    int32_t status=0;
    uint8_t idx;
    BOOLEAN updateList = FALSE;

    HOOK(HOOK_IN_CME_AP_ACCESS_LIST);

    if (NULL != gBwListCB_ull)
    {
        CME_generalSemaphoreTake();
    }
    else if (FALSE == UpdateFlash)
    {
        // This is an illegal combination as there is no working
        // copy and flash update is not needed. Nothing to do.
        status =  -2;
    }

    if (0 == status)
    {
        pBwListWorkingCopy = getBwListWorkingCopy();

        if (!pBwListWorkingCopy)
        {
            status = -1;
        }
        else
        {
            if (pMacAddress!=NULL)
            {
                GTRACE(GRP_AP_ACCESS_LIST,"AP access List: Del Mac: %x:%x:%x:%x:%x:%x", pMacAddress[0],
                                                                                        pMacAddress[1],
                                                                                        pMacAddress[2],
                                                                                        pMacAddress[3],
                                                                                        pMacAddress[4],
                                                                                        pMacAddress[5]);

                //Check if mac address is in the list
                if (CME_IsEntryInArrList((u8*)pBwListWorkingCopy->pMacList,
                                         pBwListWorkingCopy->Header.macListNumEntries,
                                         pMacAddress,
                                         MAC_ADDR_LEN,
                                         &idx))
                {
                    //Remove by mac address
                    updateList = TRUE;
                }
                else
                {
                    //Not found
                    status  = -3;
                    GTRACE(GRP_AP_ACCESS_LIST,"Mac Not Found");
                }

            }
            else
            {
                GTRACE(GRP_AP_ACCESS_LIST,"AP access List: Del Mac by index %d",index);

                if (index < pBwListWorkingCopy->Header.macListNumEntries)
                {
                    //remove by index
                    idx = index;
                    updateList = TRUE;
                }
                else
                {
                    //Not found
                    status = -3;
                    GTRACE(GRP_AP_ACCESS_LIST,"Index Not Found");
                }
            }


            if (updateList)
            {
                CME_RemoveEntryFromArrList((u8**)&pBwListWorkingCopy->pMacList,
                                           &pBwListWorkingCopy->Header.macListNumEntries,
                                           idx,
                                           sizeof (BwList_macEntry));
            }
        }
    }

    if (NULL != gBwListCB_ull)
    {
        CME_generalSemaphoreRelease();
    }

    if (UpdateFlash && updateList)
    {
        status = WritePieAndMacListToFlash(pBwListWorkingCopy, NULL, TRUE);
    }

    freeBwListWorkingCopy(pBwListWorkingCopy);

    return status;
}


/******************************************************************************
  Function          : CME_GetList

  Description       : Called to retrieve list content and length.

  Input parameters  : ListIndex - The index from which to return the entries
                      AllocatedBufferSize - Max size in byes of target buffer.

  Output parameters : pList - Output buffer. If null, no copy will be made
                      and only list length returned.

  Return value      : retVal - Total copied bytes if successful (0 or positive),
                      or total number of entries in the list (if pList is NULL)
                      -1 otherwise.
******************************************************************************/
int16_t CME_GetList(uint8_t listType,
                  uint8_t* pList,
                  int16_t ListIndex,
                  int16_t AllocatedBufferSize)
{
    HOOK(HOOK_IN_CME_AP_ACCESS_LIST);

    cmeBwListCB_t*  pBwListWorkingCopy = NULL;
    int16_t numEntries = -1;
    int16_t retVal = -1;
    int16_t idx;
    uint16_t copiedLen;
    uint16_t entriesCopied;
    uint8_t entrySize = 0;
    uint8_t *pSrcList = NULL;

    //TODO: to check
    // We do not take the semaphore as this is a read operation
    // and list data will not be modified.
    //CME_generalSemaphoreTake();

    GTRACE(GRP_AP_ACCESS_LIST,"AP access List: Get list type %d", listType);

    pBwListWorkingCopy = getBwListWorkingCopy();

    if (pBwListWorkingCopy)
    {
        if (listType == CME_BW_LIST_TYPE_MAC)
        {
            numEntries = pBwListWorkingCopy->Header.macListNumEntries;
            entrySize = sizeof (BwList_macEntry);
            pSrcList = (uint8_t *)pBwListWorkingCopy->pMacList;
        }
        else if (listType == CME_BW_LIST_TYPE_WILDCARD)
        {
            numEntries = pBwListWorkingCopy->Header.wildcardListNumEntries;
            entrySize = sizeof (BwList_wildcardEnry);
            pSrcList = (uint8_t *)pBwListWorkingCopy->pWildcardList;
        }

        if ((0 != numEntries) && (NULL != pList))
        {
            if ((AllocatedBufferSize >= entrySize) && (ListIndex < numEntries))
            {
                //There is a place for at least one entry.
                //Start to copy from 'ListIndex'
                copiedLen = 0;
                idx = ListIndex;
                entriesCopied = 0;

                do
                {
                    memcpy(pList, pSrcList + (idx * entrySize), entrySize);
                    idx++;
                    if (idx == numEntries)
                    {
                        idx = 0;
                    }
                    entriesCopied+=1;
                    copiedLen += entrySize;
                    pList+=entrySize;

                } while ((entriesCopied < numEntries) && ((copiedLen + entrySize) <= AllocatedBufferSize));

                retVal = copiedLen;
            }
            else
            {
                // Target buffer to small, or index not in range. Do not copy and report error.
                retVal = -1;
            }
        }
        else
        {
            retVal = numEntries;
        }

        freeBwListWorkingCopy(pBwListWorkingCopy);
    }

    HOOK(HOOK_IN_CME_AP_ACCESS_LIST);

    return retVal;

}

/******************************************************************************
  Function          : CME_AddWildcardToList

  Description       : Called to add new wildcard (mac + mask) entry to list.
                      If list already exists in RAM (AP is running then this
                      copy will be updated (and written to flash if requested).
                      Otherwise, the flash data will be loaded to temp buffer,
                      updated and written back.

  Input parameters  : pMacAddress - MAC address to add.
                      uint8_t* pMask - mask to add
                      UpdateFlash - FALSE if only RAM list is to be updated,
                      TRUE if save the resulting list to flash as well.

  Output parameters : None

  Return value      : 0 on success or MAC is already present.
                      -1 on other errors
                      -2 if no working copy exists in RAM (AP is down) and
                         flash update flag is 0.
                      -3 if list is full
******************************************************************************/
int32_t CME_AddWildcardToList(uint8_t* pMacAddress, uint8_t* pMask, BOOLEAN UpdateFlash)
{
    int32_t status=0;
    cmeBwListCB_t*       pBwListWorkingCopy = NULL;
    BwList_wildcardEnry pWildcardEntry;
    uint8_t idx;
    BOOLEAN listUpdated = FALSE;

    HOOK(HOOK_IN_CME_AP_ACCESS_LIST);

    GTRACE(GRP_AP_ACCESS_LIST,"AP access List: Add Wildcard:");
    GTRACE(GRP_AP_ACCESS_LIST,"Mac: %x:%x:%x:%x:%x:%x", pMacAddress[0],
                                                        pMacAddress[1],
                                                        pMacAddress[2],
                                                        pMacAddress[3],
                                                        pMacAddress[4],
                                                        pMacAddress[5]);

    GTRACE(GRP_AP_ACCESS_LIST,"Mask: %x:%x:%x:%x:%x:%x", pMask[0],
                                                         pMask[1],
                                                         pMask[2],
                                                         pMask[3],
                                                         pMask[4],
                                                         pMask[5]);

    if (NULL != gBwListCB_ull)
    {
        CME_generalSemaphoreTake();
    }
    else if (FALSE == UpdateFlash)
    {
        // This is an illegal combination as there is no working
        // copy and flash update is not needed. Nothing to do.
        status = -2;
    }

    if (0 == status)
    {
        pBwListWorkingCopy = getBwListWorkingCopy();

        if (!pBwListWorkingCopy)
        {
            status = -1;
        }
        else
        {
            //Prepare the wildcard entry first
            os_memcpy (pWildcardEntry.macAddr, pMacAddress, MAC_ADDR_LEN);
            os_memcpy (pWildcardEntry.mask, pMask, CME_BW_WILDCARD_MASK_LEN);

            //Check if wildcard entry is in the list
            if (CME_IsEntryInArrList((u8*)pBwListWorkingCopy->pWildcardList,
                                     pBwListWorkingCopy->Header.wildcardListNumEntries,
                                     (u8*)&pWildcardEntry,
                                     sizeof(BwList_wildcardEnry),
                                     &idx))
            {
                //Already in the list, no need to add.
                status = 0;
            }
            else
            {
                if (pBwListWorkingCopy->Header.wildcardListNumEntries == CME_BW_MAX_WILDCARD_ENTRIES)
                {
                    //List is full
                    status = -3;
                }
                else
                {
                    status = CME_AddEntryToArrList((u8**)&pBwListWorkingCopy->pWildcardList,
                                                   &pBwListWorkingCopy->Header.wildcardListNumEntries,
                                                   (u8*)&pWildcardEntry,
                                                   sizeof (BwList_wildcardEnry));
                    listUpdated = TRUE;
                }
            }
        }
    }
    if (NULL != gBwListCB_ull)
    {
        // Release semaphore if taken
        CME_generalSemaphoreRelease();
    }

    if (UpdateFlash && listUpdated)
    {
        WritePieAndMacListToFlash(pBwListWorkingCopy, NULL, TRUE);
    }

    freeBwListWorkingCopy(pBwListWorkingCopy);

    return status;
}


/******************************************************************************
  Function          : CME_DelWildcardFromList

  Description       : Called to remove wildcard (mac + mask or index) entry from list.

  Input parameters  : pMacAddress - The address to delete. The pointer should point to a user
                      provided buffer and not inside the list structure.
                      uint8_t* pMask - The mask
                      uint32_t index - index to remove (mac address and mask should be NULL)
                      UpdateFlash - FALSE if only RAM list is to be updated,
                      TRUE if save the resulting list to flash as well.

  Output parameters : None

  Return value      : 0 if successfull,
                      -1 on other errors
                      -2 if no working copy exists in RAM (AP is down) and
                         flash update flag is 0.
                      -3 if address is not found,
******************************************************************************/
int32_t CME_DelWildcardFromList(uint8_t* pMacAddress, uint8_t* pMask, uint32_t index, BOOLEAN UpdateFlash)
{
    cmeBwListCB_t*  pBwListWorkingCopy = NULL;
    int32_t status=0;
    uint8_t idx;
    BwList_wildcardEnry pWildcardEntry;
    BOOLEAN updateList = FALSE;

    HOOK(HOOK_IN_CME_AP_ACCESS_LIST);

    if (NULL != gBwListCB_ull)
    {
        CME_generalSemaphoreTake();
    }
    else if (FALSE == UpdateFlash)
    {
        // This is an illegal combination as there is no working
        // copy and flash update is not needed. Nothing to do.
        status =  -2;
    }

    if (0 == status)
    {
        pBwListWorkingCopy = getBwListWorkingCopy();

        if (!pBwListWorkingCopy)
        {
            status = -1;
        }
        else
        {
            if ((pMacAddress!= NULL) && (pMask!=NULL))
            {
                GTRACE(GRP_AP_ACCESS_LIST,"AP access List: Del Wildcard:");
                GTRACE(GRP_AP_ACCESS_LIST,"Mac: %x:%x:%x:%x:%x:%x", pMacAddress[0],
                                                                    pMacAddress[1],
                                                                    pMacAddress[2],
                                                                    pMacAddress[3],
                                                                    pMacAddress[4],
                                                                    pMacAddress[5]);

                GTRACE(GRP_AP_ACCESS_LIST,"Mask: %x:%x:%x:%x:%x:%x", pMask[0],
                                                                     pMask[1],
                                                                     pMask[2],
                                                                     pMask[3],
                                                                     pMask[4],
                                                                     pMask[5]);

                //Prepare the wildcard entry first
                os_memcpy (pWildcardEntry.macAddr, pMacAddress, MAC_ADDR_LEN);
                os_memcpy (pWildcardEntry.mask, pMask, CME_BW_WILDCARD_MASK_LEN);

                //Check if wildcard is in the list
                if (CME_IsEntryInArrList((u8*)pBwListWorkingCopy->pWildcardList,
                                          pBwListWorkingCopy->Header.wildcardListNumEntries,
                                          (u8*)&pWildcardEntry,
                                          sizeof(BwList_wildcardEnry),
                                          &idx))
                {
                    //Remove by wildcard
                    updateList = TRUE;
                }
                else
                {
                    //Not Found
                    status = -3;
                    GTRACE(GRP_AP_ACCESS_LIST,"Wildcard Not Found");
                }
            }
            else
            {
                GTRACE(GRP_AP_ACCESS_LIST,"AP access List: Del Wildcard by index %d", index);

                if (index < pBwListWorkingCopy->Header.wildcardListNumEntries)
                {
                    //Remove by index
                    idx = index;
                    updateList = TRUE;
                }
                else
                {
                    //Not Found
                    status = -3;
                    GTRACE(GRP_AP_ACCESS_LIST,"Index Not Found");
                }
            }

            if (updateList)
            {
                CME_RemoveEntryFromArrList((u8**)&pBwListWorkingCopy->pWildcardList,
                                           &pBwListWorkingCopy->Header.wildcardListNumEntries,
                                           idx,
                                           sizeof (BwList_wildcardEnry));
            }
        }
    }

    if (NULL != gBwListCB_ull)
    {
        CME_generalSemaphoreRelease();
    }

    if (UpdateFlash && updateList)
    {
        status = WritePieAndMacListToFlash(pBwListWorkingCopy, NULL, TRUE);
    }

    freeBwListWorkingCopy(pBwListWorkingCopy);

    return status;
}


/******************************************************************************
  Function          : CME_DelList

  Description       : Called from the dispatcher to delete the entire list.

  Input parameters  : ListType - CME_BW_LIST_TYPE_MAC / CME_BW_LIST_TYPE_WILDCARD

                      UpdateFlash - FALSE if only RAM list is to be updated,
                                    TRUE if save the resulting list to flash as well.

  Output parameters : None

  Return value      : 0 if successfull, -1 otherwise.
******************************************************************************/
int32_t CME_DelList(uint8_t listType, BOOLEAN UpdateFlash)
{
    cmeBwListCB_t* pBwListWorkingCopy = NULL;
    int32_t status=0;

    HOOK(HOOK_IN_CME_AP_ACCESS_LIST);

    GTRACE(GRP_AP_ACCESS_LIST,"AP access List: Del list type %d", listType);

    if (NULL != gBwListCB_ull)
    {
        CME_generalSemaphoreTake();
    }
    else if (FALSE == UpdateFlash)
    {
        // This is an illegal combination as there is no working
        // copy and flash update is not needed. Nothing to do.
        status = -2;
    }

    if (0 == status)
    {
        pBwListWorkingCopy = getBwListWorkingCopy();

        if (pBwListWorkingCopy)
        {
            if (listType == CME_BW_LIST_TYPE_MAC)
            {
                // Delete mac list
                if(NULL != pBwListWorkingCopy->pMacList)
                {
                    os_free(pBwListWorkingCopy->pMacList);
                    pBwListWorkingCopy->pMacList = NULL;
                }
                pBwListWorkingCopy->Header.macListNumEntries = 0;
            }
            else if (listType == CME_BW_LIST_TYPE_WILDCARD)
            {
                //Delete wildcard list
                if(NULL != pBwListWorkingCopy->pWildcardList)
                {
                    os_free(pBwListWorkingCopy->pWildcardList);
                    pBwListWorkingCopy->pWildcardList = NULL;
                }
                pBwListWorkingCopy->Header.wildcardListNumEntries = 0;
            }
        }
    }

    if (NULL != gBwListCB_ull)
    {
        CME_generalSemaphoreRelease();
    }

    if (UpdateFlash)
    {
        status = WritePieAndMacListToFlash(pBwListWorkingCopy, NULL, TRUE);
    }

    freeBwListWorkingCopy(pBwListWorkingCopy);

    return status;
}

#endif
