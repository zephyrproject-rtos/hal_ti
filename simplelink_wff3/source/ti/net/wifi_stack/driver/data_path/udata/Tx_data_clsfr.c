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
/** \file   txDataClsfr.c 
 *  \brief  The Tx Data Classifier sub-module (under txDataQueue module).
 *  
 *  \see    txDataQueue.h (the classifier uses the same object as txDataQueue)
 */

#define __FILE_ID__  FILE_ID_34
#include "osi_kernel.h"
#include <trnspt_thread.h>
#include <data_path/ethernet.h>
#include "paramOut.h"
#include "tw_driver.h"
#include "tx_data_queue.h"

extern TTxDataQ *gTxDataQCB;

/** 
 * \fn     txDataClsfr_Config 
 * \brief  Configure the classifier paramters
 * 
 * Configure the classifier parameters according to the init parameters.
 * Called from the txDataQueue configuration function.
 * 
 * \note   
 * \param  pTxDataQ     - The object handle                                         
 * \param  pClsfrInitParams - Pointer to the classifier init params
 * \return OK on success or NOK on failure 
 * \sa     
 */ 
uint32_t txDataClsfr_Config(TClsfrInitParams *pClsfrInitParams)
{
    TTxDataQ     *pTxDataQ = gTxDataQCB;
    TClsfrParams *pParams  = &pTxDataQ->tClsfrParams; /* where to save the new params */
    uint32_t     uActualEntryCount;
    uint32_t     i, j;
    Bool_e       bConflictFound;
    
    /* Active classification algorithm */
    pParams->eClsfrType = pClsfrInitParams->eClsfrType;

    /* the number of active entries */
    if (pClsfrInitParams->uNumActiveEntries <= NUM_OF_CLSFR_TABLE_ENTRIES)
        pParams->uNumActiveEntries = pClsfrInitParams->uNumActiveEntries;
    else 
        pParams->uNumActiveEntries = NUM_OF_CLSFR_TABLE_ENTRIES;

    /* Initialization of the classification table */
    switch (pParams->eClsfrType)
    {
        case D_TAG_CLSFR:
            pParams->uNumActiveEntries = 0;
        break;
        
        case DSCP_CLSFR:
            uActualEntryCount = 0;
            for (i = 0; i < pParams->uNumActiveEntries; i++)
            {
                bConflictFound = FALSE;
                /* check conflict */
                for (j = 0; j < i; j++)
                {
                   /* Detect both duplicate and conflicting entries */
                    if (pParams->ClsfrTable[j].Dscp.CodePoint == pClsfrInitParams->ClsfrTable[i].Dscp.CodePoint)
                    {
                        //Report(REPORT_SEVERITY_ERROR , "txDataClsfr_Config(): duplicate/conflicting classifier DSCP entries, indexes = %d, %d\r\n", j, i);
                        bConflictFound = TRUE;
                    }
                }
                if (bConflictFound == FALSE)
                {
                  pParams->ClsfrTable[uActualEntryCount].Dscp.CodePoint = pClsfrInitParams->ClsfrTable[i].Dscp.CodePoint;
                  pParams->ClsfrTable[uActualEntryCount].DTag = pClsfrInitParams->ClsfrTable[i].Dscp.DTag;
                  uActualEntryCount++;
                }
            }
            pParams->uNumActiveEntries = uActualEntryCount;
        break;

        case PORT_CLSFR:
            uActualEntryCount = 0;
            for (i = 0; i < pParams->uNumActiveEntries ; i++)
            {
                bConflictFound = FALSE;
                /* check conflict */
                for (j = 0; j < i; j++)
                {
                    /* Detect both duplicate and conflicting entries */
                    if (pParams->ClsfrTable[j].Dscp.DstPortNum == pClsfrInitParams->ClsfrTable[i].Port.DstPortNum)
                    {
                        //Report(REPORT_SEVERITY_ERROR , "txDataClsfr_Config(): duplicate/conflicting classifier Port entries, indexes = %d, %d\r\n", j, i);
                        bConflictFound = TRUE;
                    }
                }
                if (bConflictFound == FALSE)
                {
                  pParams->ClsfrTable[uActualEntryCount].Dscp.DstPortNum = pClsfrInitParams->ClsfrTable[i].Port.DstPortNum;
                  pParams->ClsfrTable[uActualEntryCount].DTag = pClsfrInitParams->ClsfrTable[i].Port.DTag;
                  uActualEntryCount++;
                }
            }
            pParams->uNumActiveEntries = uActualEntryCount;
        break;  

        case IPPORT_CLSFR:
            uActualEntryCount = 0;
            for (i=0; (i < pParams->uNumActiveEntries ) ; i++)
            {
                bConflictFound = FALSE;
                /* check conflict */
                for (j = 0; j < i; j++)
                {
                   /* Detect both duplicate and conflicting entries */
                    if ((pParams->ClsfrTable[j].Dscp.DstIPPort.DstIPAddress == pClsfrInitParams->ClsfrTable[i].IpPort.DstIPAddress) && 
                        (pParams->ClsfrTable[j].Dscp.DstIPPort.DstPortNum   == pClsfrInitParams->ClsfrTable[i].IpPort.DstPortNum))
                    {
                        //Report(REPORT_SEVERITY_ERROR , "txDataClsfr_Config(): duplicate/conflicting classifier IP&Port entries, indexes = %d, %d\r\n", j, i);
                        bConflictFound = TRUE;
                    }
                }
                if (bConflictFound == FALSE)
                {
                  pParams->ClsfrTable[uActualEntryCount].Dscp.DstIPPort.DstIPAddress = pClsfrInitParams->ClsfrTable[i].IpPort.DstIPAddress;
                  pParams->ClsfrTable[uActualEntryCount].Dscp.DstIPPort.DstPortNum = pClsfrInitParams->ClsfrTable[i].IpPort.DstPortNum;
                  pParams->ClsfrTable[uActualEntryCount].DTag = pClsfrInitParams->ClsfrTable[i].IpPort.DTag;
                  uActualEntryCount++;
                }
            }
            pParams->uNumActiveEntries = uActualEntryCount;
        break;  

        default:
            //Report(REPORT_SEVERITY_ERROR , "txDataClsfr_Config(): Classifier type -- unknown --> set to D-Tag\r\n");
            pParams->eClsfrType = D_TAG_CLSFR;
            pParams->uNumActiveEntries = 0;
        break;  
    }
    
    return OK;
}


/** 
 * \fn     getIpAndUdpHeader 
 * \brief  Get IP & UDP headers addresses if exist
 * 
 * This function gets the addresses of the IP and UDP headers
 *
 * \note   A local inline function!
 * \param  pTxDataQ    - The object handle                                         
 * \param  pPktCtrlBlk - Pointer to the packet
 * \param  pIpHeader   - Pointer to pointer to IP header
 * \param  pUdpHeader  - Pointer to pointer to UDP header 
 * \return OK on success, NOK if it's not an IP packet
 * \sa     
 */ 
static INLINE uint32_t getIpAndUdpHeader( TTxCtrlBlk *pPktCtrlBlk,
                                          uint8_t  **pIpHeader, 
                                          uint8_t  **pUdpHeader)
{
    uint8_t *pEthHead = pPktCtrlBlk->tTxnStruct.aBuf[0];
    uint8_t  ipHeaderLen = 0;
  
    /* check if frame is IP according to ether type */
    if( ( HTOWLANS(((TEthernetHeader *)pEthHead)->type) ) != ETHERTYPE_IP && ( HTOWLANS(((TEthernetHeader *)pEthHead)->type) ) != ETHERTYPE_ARP)
    {
        //Report(REPORT_SEVERITY_INFORMATION, " getIpAndUdpHeader: EthTypeLength is not 0x0800  0x%x\r\n", (int)HTOWLANS(((TEthernetHeader *)pEthHead)->type));
        return NOK;
    }

    /* set the pointer to the beginning of the IP header and calculate it's size */
    *pIpHeader  = pPktCtrlBlk->tTxnStruct.aBuf[1];
    ipHeaderLen = ((*(unsigned char*)(*pIpHeader) & 0x0f) * 4);

    /* Set the pointer to the beggining of the TCP/UDP header */
    if (ipHeaderLen == pPktCtrlBlk->tTxnStruct.aLen[1])
    {
        *pUdpHeader = pPktCtrlBlk->tTxnStruct.aBuf[2];  
    }
    else 
    {
        *pUdpHeader = *pIpHeader + ipHeaderLen;  
    }

    return OK;
}


/** 
 * \fn     txDataClsfr_ClassifyTxPacket 
 * \brief  Configure the classifier paramters
 * 
 * This function classifies the given Tx packet according to the classifier parameters. 
 * It sets the TID field with the classification result.
 * The classification is according to one of the following methods:
 * - D-Tag  - Transparent (TID = Dtag)
 * - DSCP   - According to the DSCP field in the IP header - the default method!
 * - Dest UDP-Port   
 * - Dest IP-Addr & UDP-Port
 *
 * \note   
 * \param  pTxDataQ    - The object handle                                         
 * \param  pPktCtrlBlk - Pointer to the classified packet
 * \param  uPacketDtag - The packet priority optionaly set by the OAL
 * \return OK on success, PARAM_VALUE_NOT_VALID in case of input parameters problems.
 * \sa     
 */ 
uint32_t txDataClsfr_ClassifyTxPacket (TTxCtrlBlk *pPktCtrlBlk, uint8_t uPacketDtag)
{
    TTxDataQ     *pTxDataQ = gTxDataQCB;
    TClsfrParams *pClsfrParams = &pTxDataQ->tClsfrParams;
    uint8_t     *pUdpHeader = NULL;
    uint8_t     *pIpHeader = NULL;
    uint8_t   uDscp;
    uint16_t  uDstUdpPort;
    uint32_t  uDstIpAdd;
    uint32_t  i;

    pPktCtrlBlk->tTxDescriptor.tid = 0;

    switch(pClsfrParams->eClsfrType)
    {
            /* Trivial mapping D-tag to D-tag */
        case D_TAG_CLSFR:
            if (uPacketDtag > MAX_NUM_OF_802_1d_TAGS)
            {
                //Report(REPORT_SEVERITY_ERROR , "txDataClsfr_ClassifyTxPacket(): uPacketDtag error\r\n");
                return PARAM_VALUE_NOT_VALID;
            }
            pPktCtrlBlk->tTxDescriptor.tid = uPacketDtag;
            //Report(REPORT_SEVERITY_INFORMATION , "Classifier D_TAG_CLSFR. uPacketDtag = %d\r\n", uPacketDtag);
        break;

        case DSCP_CLSFR:
            if( (getIpAndUdpHeader(pPktCtrlBlk, &pIpHeader, &pUdpHeader) != OK) 
                || (pIpHeader == NULL) )
            {
                //Report(REPORT_SEVERITY_INFORMATION , "txDataClsfr_ClassifyTxPacket(): DSCP clsfr, getIpAndUdpHeader mismatch\r\n");
                return PARAM_VALUE_NOT_VALID; 
            }

            /* DSCP to D-tag mapping */
            uDscp =  *((uint8_t *)(pIpHeader + 1)); /* Fetching the DSCP from the header */
            uDscp = (uDscp >> 2);
            
            /* looking for the specific DSCP, if found, its corresponding D-tag is set to the TID */
            for(i = 0; i < pClsfrParams->uNumActiveEntries; i++)
            {
                if (pClsfrParams->ClsfrTable[i].Dscp.CodePoint == uDscp)
                {
                    pPktCtrlBlk->tTxDescriptor.tid = pClsfrParams->ClsfrTable[i].DTag;
                    //Report(REPORT_SEVERITY_INFORMATION , "Classifier DSCP_CLSFR found match - entry %d - Tid = %d\r\n",i,pPktCtrlBlk->tTxDescriptor.tid);
                    break;
                }
            }
        break;

        case PORT_CLSFR:
            if( (getIpAndUdpHeader(pPktCtrlBlk, &pIpHeader, &pUdpHeader) != OK) ||
                (pUdpHeader == NULL) )
            {
                //Report(REPORT_SEVERITY_INFORMATION, " txDataClsfr_ClassifyTxPacket() : DstPort clsfr, getIpAndUdpHeader error\r\n");
                return PARAM_VALUE_NOT_VALID; 
            }

            COPY_WLAN_WORD(&uDstUdpPort,(pUdpHeader + 2));
            uDstUdpPort = HTOWLANS(uDstUdpPort);
            
            /* Looking for the specific port number. If found, its corresponding D-tag is set to the TID. */
            for(i = 0; i < pClsfrParams->uNumActiveEntries; i++)
            {
                if (pClsfrParams->ClsfrTable[i].Dscp.DstPortNum == uDstUdpPort)
                {
                    pPktCtrlBlk->tTxDescriptor.tid = pClsfrParams->ClsfrTable[i].DTag;
                    //Report(REPORT_SEVERITY_INFORMATION , "Classifier PORT_CLSFR found match - entry %d - Tid = %d\r\n", i, pPktCtrlBlk->tTxDescriptor.tid);
                    break;
                }
            }
        break;

        case IPPORT_CLSFR: 
            if ( (getIpAndUdpHeader(pPktCtrlBlk, &pIpHeader, &pUdpHeader) != OK) 
                 || (pIpHeader == NULL) || (pUdpHeader == NULL) )
            {
                //Report(REPORT_SEVERITY_INFORMATION, "txDataClsfr_ClassifyTxPacket(): Dst IP&Port clsfr, getIpAndUdpHeader error\r\n");
                return PARAM_VALUE_NOT_VALID; 
            }

            COPY_WLAN_WORD(&uDstUdpPort,(pUdpHeader + 2));
            uDstUdpPort = HTOWLANS(uDstUdpPort);
            COPY_WLAN_32BIT(&uDstIpAdd,(pIpHeader + 16));

            
            /* 
             * Looking for the specific pair of dst IP address and dst port number.
             * If found, its corresponding D-tag is set to the TID.                                                         
             */
            for(i = 0; i < pClsfrParams->uNumActiveEntries; i++)
            {
                if ((pClsfrParams->ClsfrTable[i].Dscp.DstIPPort.DstIPAddress == uDstIpAdd) &&
                    (pClsfrParams->ClsfrTable[i].Dscp.DstIPPort.DstPortNum == uDstUdpPort))
                {
                    pPktCtrlBlk->tTxDescriptor.tid = pClsfrParams->ClsfrTable[i].DTag;
                    //Report(REPORT_SEVERITY_INFORMATION , "Classifier IPPORT_CLSFR found match - entry %d - Tid = %d\r\n", i, pPktCtrlBlk->tTxDescriptor.tid);
                    break;
                }
            }
        break;
        
        default:
            break;
            //Report(REPORT_SEVERITY_ERROR, "txDataClsfr_ClassifyTxPacket(): eClsfrType error\r\n");
    }

    return OK;
}


/** 
 * \fn     txDataClsfr_InsertClsfrEntry 
 * \brief  Insert a new entry to classifier table
 * 
 * Add a new entry to the classification table.
 * If the new entry is invalid or conflicts with existing entries, the operation is canceled.
 *
 * \note   
 * \param  pTxDataQ - The object handle                                         
 * \param  pNewEntry    - Pointer to the new entry to insert
 * \return OK on success, PARAM_VALUE_NOT_VALID in case of input parameters problems.
 * \sa     txDataClsfr_RemoveClsfrEntry
 */ 
uint32_t txDataClsfr_InsertClsfrEntry (TClsfrTableEntry *pNewEntry)
{
    TTxDataQ      *pTxDataQ = gTxDataQCB;
    TClsfrParams  *pClsfrParams = &pTxDataQ->tClsfrParams;
    uint32_t      i;

    if(pNewEntry == NULL)
    {
        //Report(REPORT_SEVERITY_ERROR, "Classifier_InsertClsfrEntry(): NULL ConfigBuffer pointer Error - Aborting\r\n");
        return PARAM_VALUE_NOT_VALID;
    }
    
    /* If no available entries, exit */
    if (pClsfrParams->uNumActiveEntries == NUM_OF_CLSFR_TABLE_ENTRIES)
    {
        //Report(REPORT_SEVERITY_ERROR, "Classifier_InsertClsfrEntry(): Bad Number Of Entries - Aborting\r\n");
        return PARAM_VALUE_NOT_VALID;
    }
    
    if (pClsfrParams->eClsfrType == D_TAG_CLSFR)
    {
        //Report(REPORT_SEVERITY_ERROR, "Classifier_InsertClsfrEntry(): D-Tag classifier - Aborting\r\n");
        return PARAM_VALUE_NOT_VALID;
    }

    /* Check new entry and conflict with existing entries and if OK, insert to classifier table */
    switch (pClsfrParams->eClsfrType)
    {
        case DSCP_CLSFR:
    
            /* Check entry */
            if ( (pNewEntry->Dscp.CodePoint > CLASSIFIER_CODE_POINT_MAX) || 
                 (pNewEntry->DTag > CLASSIFIER_DTAG_MAX) ) 
            {
                //Report(REPORT_SEVERITY_ERROR, "Classifier_InsertClsfrEntry(): bad parameter - Aborting\r\n");
                return PARAM_VALUE_NOT_VALID;
            }
            
            /* Check conflict*/
            for (i = 0; i < pClsfrParams->uNumActiveEntries; i++)
            {
               /* Detect both duplicate and conflicting entries */
                if (pClsfrParams->ClsfrTable[i].Dscp.CodePoint == pNewEntry->Dscp.CodePoint)
                {
                    //Report(REPORT_SEVERITY_ERROR, "Classifier_InsertClsfrEntry(): classifier entries conflict - Aborting\r\n");
                    return PARAM_VALUE_NOT_VALID;
                }
            } 

            /* Insert new entry to classifier table. */
            /* Note: Protect from txDataClsfr_ClassifyTxPacket context preemption. */
            trnspt_EnterCriticalSection ();
            pClsfrParams->ClsfrTable[pClsfrParams->uNumActiveEntries].Dscp.CodePoint = pNewEntry->Dscp.CodePoint;
            pClsfrParams->ClsfrTable[pClsfrParams->uNumActiveEntries].DTag = pNewEntry->DTag;
            trnspt_LeaveCriticalSection ();
            
        break;
        
        case PORT_CLSFR:

            /* Check entry */
            if ((pNewEntry->DTag > CLASSIFIER_DTAG_MAX) || 
                (pNewEntry->Dscp.DstPortNum > CLASSIFIER_PORT_MAX-1) || 
                (pNewEntry->Dscp.DstPortNum < CLASSIFIER_PORT_MIN) )
            {
                //Report(REPORT_SEVERITY_ERROR, "Classifier_InsertClsfrEntry(): bad parameter - Aborting\r\n");
                return PARAM_VALUE_NOT_VALID;
            }
            
            /* Check conflict*/
            for (i = 0; i < pClsfrParams->uNumActiveEntries; i++)
            {
               /* Detect both duplicate and conflicting entries */
                if (pClsfrParams->ClsfrTable[i].Dscp.DstPortNum == pNewEntry->Dscp.DstPortNum)
                {
                    //Report(REPORT_SEVERITY_ERROR, "Classifier_InsertClsfrEntry(): classifier entries conflict - Aborting\r\n");
                     return PARAM_VALUE_NOT_VALID;
                }
            }     

            /* Insert new entry to classifier table. */            
            /* Note: Protect from txDataClsfr_ClassifyTxPacket context preemption. */
            trnspt_EnterCriticalSection ();
            pClsfrParams->ClsfrTable[pClsfrParams->uNumActiveEntries].Dscp.DstPortNum = pNewEntry->Dscp.DstPortNum;
            pClsfrParams->ClsfrTable[pClsfrParams->uNumActiveEntries].DTag = pNewEntry->DTag;
            trnspt_LeaveCriticalSection ();
                                
        break;
        
        case IPPORT_CLSFR:

            /* Check entry */
            if ( (pNewEntry->DTag > CLASSIFIER_DTAG_MAX) || 
                 (pNewEntry->Dscp.DstIPPort.DstPortNum > CLASSIFIER_PORT_MAX-1) || 
                 (pNewEntry->Dscp.DstIPPort.DstPortNum < CLASSIFIER_PORT_MIN) || 
                 (pNewEntry->Dscp.DstIPPort.DstIPAddress > CLASSIFIER_IPADDRESS_MAX-1) || 
                 (pNewEntry->Dscp.DstIPPort.DstIPAddress < CLASSIFIER_IPADDRESS_MIN+1) )
            {
                //Report(REPORT_SEVERITY_ERROR, "Classifier_InsertClsfrEntry(): bad parameter - Aborting\r\n");
                return PARAM_VALUE_NOT_VALID;
            }

            /* Check conflict*/
            for (i = 0; i < pClsfrParams->uNumActiveEntries; i++)
            {
               /* Detect both duplicate and conflicting entries */
                if ( (pClsfrParams->ClsfrTable[i].Dscp.DstIPPort.DstIPAddress == pNewEntry->Dscp.DstIPPort.DstIPAddress) && 
                     (pClsfrParams->ClsfrTable[i].Dscp.DstIPPort.DstPortNum == pNewEntry->Dscp.DstIPPort.DstPortNum))
                {
                    //Report(REPORT_SEVERITY_ERROR, "Classifier_InsertClsfrEntry(): classifier entries conflict - Aborting\r\n");
                     return PARAM_VALUE_NOT_VALID;
                }
            }  

            /* Insert new entry to classifier table */            
            /* Note: Protect from txDataClsfr_ClassifyTxPacket context preemption. */
            trnspt_EnterCriticalSection ();
            pClsfrParams->ClsfrTable[pClsfrParams->uNumActiveEntries].Dscp.DstIPPort.DstIPAddress = pNewEntry->Dscp.DstIPPort.DstIPAddress;
            pClsfrParams->ClsfrTable[pClsfrParams->uNumActiveEntries].Dscp.DstIPPort.DstPortNum = pNewEntry->Dscp.DstIPPort.DstPortNum;
            pClsfrParams->ClsfrTable[pClsfrParams->uNumActiveEntries].DTag = pNewEntry->DTag;
            trnspt_LeaveCriticalSection ();

        break;

        default:
            break;
//Report(REPORT_SEVERITY_ERROR, "Classifier_InsertClsfrEntry(): Classifier type -- unknown - Aborting\r\n");
            
    } 
    
    /* Increment the number of classifier active entries */
    pClsfrParams->uNumActiveEntries++;

    return OK;
}


/** 
 * \fn     txDataClsfr_RemoveClsfrEntry 
 * \brief  Remove an entry from classifier table
 * 
 * Remove an entry from classifier table.
 *
 * \note   
 * \param  pTxDataQ - The object handle                                         
 * \param  pRemEntry    - Pointer to the entry to remove
 * \return OK on success, PARAM_VALUE_NOT_VALID in case of input parameters problems.
 * \sa     txDataClsfr_InsertClsfrEntry
 */ 
uint32_t txDataClsfr_RemoveClsfrEntry (TClsfrTableEntry *pRemEntry)
{
    TTxDataQ      *pTxDataQ     = gTxDataQCB;
    TClsfrParams  *pClsfrParams = &pTxDataQ->tClsfrParams;
    uint32_t      i, j;

    if(pRemEntry == NULL)
    {
        //Report(REPORT_SEVERITY_ERROR, "classifier_RemoveClsfrEntry(): NULL ConfigBuffer pointer Error - Aborting\r\n");
        return PARAM_VALUE_NOT_VALID;
    }
    
    if (pClsfrParams->uNumActiveEntries == 0)
    {
        //Report(REPORT_SEVERITY_ERROR, "classifier_RemoveClsfrEntry(): Classifier table is empty - Aborting\r\n");
        return PARAM_VALUE_NOT_VALID;
    }
   
    if (pClsfrParams->eClsfrType == D_TAG_CLSFR)
    {
        //Report(REPORT_SEVERITY_ERROR, "classifier_RemoveClsfrEntry(): D-Tag classifier - Aborting\r\n");
        return PARAM_VALUE_NOT_VALID;
    }

    /* Check conflicts with classifier table entries */
    /* check all conflicts, if all entries are OK --> insert to classifier table*/
 
    switch (pClsfrParams->eClsfrType)
    {
        case DSCP_CLSFR:

           /* Find the classifier entry */
           i = 0;
            while ((i < pClsfrParams->uNumActiveEntries) &&
                  ((pClsfrParams->ClsfrTable[i].Dscp.CodePoint != pRemEntry->Dscp.CodePoint) ||
                  (pClsfrParams->ClsfrTable[i].DTag != pRemEntry->DTag)))
            {   
              i++;
            }

           /* If we have reached the number of active entries, it means we couldn't find the requested entry */
            if (i == pClsfrParams->uNumActiveEntries)
           {
                //Report(REPORT_SEVERITY_ERROR, "classifier_RemoveClsfrEntry(): Entry not found - Aborting\r\n");
               return PARAM_VALUE_NOT_VALID;
           }

            /* Shift all entries above the removed one downward */
            /* Note: Protect from txDataClsfr_ClassifyTxPacket context preemption. */
            trnspt_EnterCriticalSection ();
            for (j = i; j < pClsfrParams->uNumActiveEntries - 1; j++)
                {
                   /* Move entries */
                pClsfrParams->ClsfrTable[j].Dscp.CodePoint = pClsfrParams->ClsfrTable[j+1].Dscp.CodePoint;
                pClsfrParams->ClsfrTable[j].DTag = pClsfrParams->ClsfrTable[j+1].DTag;
                } 
            trnspt_LeaveCriticalSection ();
          
        break;
        
        case PORT_CLSFR:

           /* Find the classifier entry */
           i = 0;
            while ((i < pClsfrParams->uNumActiveEntries) &&
                  ((pClsfrParams->ClsfrTable[i].Dscp.DstPortNum != pRemEntry->Dscp.DstPortNum) ||
                  (pClsfrParams->ClsfrTable[i].DTag != pRemEntry->DTag)))
            {   
              i++;
            }

           /* If we have reached the number of active entries, it means we couldn't find the requested entry */
            if (i == pClsfrParams->uNumActiveEntries)
           {
                //Report(REPORT_SEVERITY_ERROR, "classifier_RemoveClsfrEntry(): Entry not found - Aborting\r\n");
               return PARAM_VALUE_NOT_VALID;
           }

            /* Shift all entries above the removed one downward */
            /* Note: Protect from txDataClsfr_ClassifyTxPacket context preemption. */
            trnspt_EnterCriticalSection ();
            for (j = i; j < pClsfrParams->uNumActiveEntries - 1; j++)
                {
                pClsfrParams->ClsfrTable[j].Dscp.DstPortNum = pClsfrParams->ClsfrTable[j+1].Dscp.DstPortNum;
                pClsfrParams->ClsfrTable[j].DTag = pClsfrParams->ClsfrTable[j+1].DTag;
            } 
            trnspt_LeaveCriticalSection ();
                                
        break;
        
        case IPPORT_CLSFR:

            /* Find the classifier entry */
            i = 0;
            while ((i < pClsfrParams->uNumActiveEntries) &&
                  ((pClsfrParams->ClsfrTable[i].Dscp.DstIPPort.DstIPAddress != pRemEntry->Dscp.DstIPPort.DstIPAddress) ||
                  (pClsfrParams->ClsfrTable[i].Dscp.DstIPPort.DstPortNum != pRemEntry->Dscp.DstIPPort.DstPortNum) ||
                  (pClsfrParams->ClsfrTable[i].DTag != pRemEntry->DTag)))
            {   
                i++;
            }

            /* If we have reached the number of active entries, it means we couldn't find the requested entry */
            if (i == pClsfrParams->uNumActiveEntries)
            {
                //Report(REPORT_SEVERITY_ERROR, "classifier_RemoveClsfrEntry(): Entry not found - Aborting\r\n");
                return PARAM_VALUE_NOT_VALID;
            }

            /* Shift all entries above the removed one downward. */
            /* Note: Protect from txDataClsfr_ClassifyTxPacket context preemption. */
            trnspt_EnterCriticalSection ();
            for (j = i; j < pClsfrParams->uNumActiveEntries - 1; j++)
            {
                pClsfrParams->ClsfrTable[j].Dscp.DstIPPort.DstIPAddress = pClsfrParams->ClsfrTable[j+1].Dscp.DstIPPort.DstIPAddress;
                pClsfrParams->ClsfrTable[j].Dscp.DstIPPort.DstPortNum = pClsfrParams->ClsfrTable[j+1].Dscp.DstIPPort.DstPortNum;
                pClsfrParams->ClsfrTable[j].DTag = pClsfrParams->ClsfrTable[j+1].DTag;
            } 
            trnspt_LeaveCriticalSection ();

        break;

        default:
            break;
//Report(REPORT_SEVERITY_ERROR, "classifier_RemoveClsfrEntry(): Classifier type -- unknown - Aborting\r\n");
    } 
    
    /* Decrement the number of classifier active entries */
    pClsfrParams->uNumActiveEntries--;

    return OK;
}


/** 
 * \fn     txDataClsfr_SetClsfrType & txDataClsfr_GetClsfrType 
 * \brief  Set / Get classifier type
 * 
 * Set / Get classifier type.
 * When setting type, the table is emptied!
 *
 * \note   
 * \param  pTxDataQ  - The object handle                                         
 * \param  eNewClsfrType - New type
 * \return OK on success, PARAM_VALUE_NOT_VALID in case of input parameters problems.
 * \sa     
 */ 
uint32_t txDataClsfr_SetClsfrType (EClsfrType eNewClsfrType)
{
    TTxDataQ *pTxDataQ = gTxDataQCB;

    if (eNewClsfrType > CLSFR_TYPE_MAX)
    {
//Report(REPORT_SEVERITY_ERROR, "Classifier_setClsfrType(): classifier type exceed its MAX \r\n");
        return PARAM_VALUE_NOT_VALID;
    }
    
    if (pTxDataQ->tClsfrParams.eClsfrType == eNewClsfrType)
    {
//Report(REPORT_SEVERITY_WARNING, "Classifier_setClsfrType(): equal classifier type --> will empty classifier table \r\n");
    }
    
    /* Update type and empty table. */
    /* Note: Protect from txDataClsfr_ClassifyTxPacket context preemption. */
    trnspt_EnterCriticalSection ();
    pTxDataQ->tClsfrParams.eClsfrType = eNewClsfrType;
    pTxDataQ->tClsfrParams.uNumActiveEntries = 0;
    trnspt_LeaveCriticalSection ();

    return OK;
}

uint32_t txDataClsfr_GetClsfrType (EClsfrType *pClsfrType)
{
    TTxDataQ *pTxDataQ = gTxDataQCB;

    *pClsfrType = pTxDataQ->tClsfrParams.eClsfrType;
    return OK;
}



#ifdef TI_DBG

/** 
 * \fn     txDataClsfr_PrintClsfrTable 
 * \brief  Print classifier table
 * 
 * Print the classifier table for debug
 *
 * \note   
 * \param  pTxDataQ  - The object handle                                         
 * \return void
 * \sa     
 */ 
void txDataClsfr_PrintClsfrTable (TTxDataQ *hTxDataQ)
{
    TTxDataQ      *pTxDataQ     = hTxDataQ;
    TClsfrParams  *pClsfrParams = &pTxDataQ->tClsfrParams;
    uint32_t      uIpAddr, i;

    if (pClsfrParams->eClsfrType == D_TAG_CLSFR)
    {
       //Report (("D_TAG classifier type selected...Nothing to print...\r\n"));
        return;
    }

   //Report (("Number of active entries in classifier table : %d\r\n",pClsfrParams->uNumActiveEntries));

    switch (pClsfrParams->eClsfrType)
    {
        case DSCP_CLSFR:
           //Report (("+------+-------+\r\n"));
           //Report (("| Code | D-Tag |\r\n"));
           //Report (("+------+-------+\r\n"));

            for (i = 0; i < pClsfrParams->uNumActiveEntries; i++)  
            {
               //Report (("| %5d | %5d |\r\n",
                    pClsfrParams->ClsfrTable[i].Dscp.CodePoint,pClsfrParams->ClsfrTable[i].DTag));
            }

           //Report (("+-------+-------+\r\n"));
            break;

        case PORT_CLSFR:
           //Report (("+-------+-------+\r\n"));
           //Report (("| Port  | D-Tag |\r\n"));
           //Report (("+-------+-------+\r\n"));

            for (i = 0; i < pClsfrParams->uNumActiveEntries; i++)  
            {
               //Report (("| %5d | %5d |\r\n",
                    pClsfrParams->ClsfrTable[i].Dscp.DstPortNum,pClsfrParams->ClsfrTable[i].DTag));
            }

           //Report (("+-------+-------+\r\n"));
            break;

        case IPPORT_CLSFR:

           //Report (("+-------------+-------+-------+\r\n"));
           //Report (("| IP Address  | Port  | D-Tag |\r\n"));
           //Report (("+-------------+-------+-------+\r\n"));

            for (i = 0; i < pClsfrParams->uNumActiveEntries; i++)  
            {
                uIpAddr = pClsfrParams->ClsfrTable[i].Dscp.DstIPPort.DstIPAddress;
               //Report (("| %02x.%02x.%02x.%02x | %5d | %5d |\r\n",
                    (uIpAddr & 0xFF),((uIpAddr >> 8) & (0xFF)),((uIpAddr >> 16) & (0xFF)),((uIpAddr >> 24) & (0xFF)),
                    pClsfrParams->ClsfrTable[i].Dscp.DstIPPort.DstPortNum, pClsfrParams->ClsfrTable[i].DTag));
            }

           //Report (("+-------------+-------+-------+\r\n"));
            break;

        default:
//Report(REPORT_SEVERITY_ERROR, "Classifier_InsertClsfrEntry(): Classifier type -- unknown - Aborting\r\n");
            break;
    }
}

#endif  /* TI_DBG */



