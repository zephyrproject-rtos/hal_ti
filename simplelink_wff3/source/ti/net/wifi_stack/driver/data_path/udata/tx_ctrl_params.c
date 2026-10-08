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
/*******************************************************************************/
/*                                                                             */
/*      MODULE: txCtrlParams.c                                                 */
/*    PURPOSE:  The txCtrl module parameters handling.                         */
/*              This is a part of the txCtrl module (using the same object).   */
/*                                                                             */
/*******************************************************************************/

#define __FILE_ID__  FILE_ID_32

#include "osi_kernel.h"
#include <trnspt_thread.h>
#include "public_share.h"
#include "paramOut.h"
#include "timer.h"
#include "tx_ctrl_api.h"
#include "tx_ctrl.h"

#define USEC_PER_SEC  1000000


extern txCtrl_t *gTxCtrlCB;


/***************************************************************************
*                       txCtrlParams_resetCounters
****************************************************************************
* DESCRIPTION:  Set stack counters
*
* INPUTS:
*
* OUTPUT:
*
* RETURNS:
***************************************************************************/
void txCtrlParams_SetStackCounters(uint32_t uHlid, uint32_t buflen)
{
#ifdef ENABLE_TRAFFIC_STATITIC
    txCtrl_t *pTxCtrl = gTxCtrlCB;
    if(uHlid != INVALID_LINK)
    {
        if(pTxCtrl->dbgLinkCounters.dbgStartCollectCntrStackEntr[uHlid])
        {
            pTxCtrl->dbgLinkCounters.dbgStartCollectCntrStackEntr[uHlid] = 0;
            pTxCtrl->dbgLinkCounters.dbgStackEntrTimeFirstPacket_Ms[uHlid] = osi_GetTimeMS();
            pTxCtrl->dbgLinkCounters.dbgStackEntrNumByteSent[uHlid] = 0;
            pTxCtrl->dbgLinkCounters.link_tx_dbgStackEntNumPktsXfered[uHlid] = 0;
        }
        pTxCtrl->dbgLinkCounters.dbgStackEntrTimeLastPacket_Ms[uHlid] = osi_GetTimeMS();
        pTxCtrl->dbgLinkCounters.dbgStackEntrNumByteSent[uHlid] += buflen;//including ETHERNET_HDR_LEN
        pTxCtrl->dbgLinkCounters.link_tx_dbgStackEntNumPktsXfered[uHlid]++;
    }
#endif
}
/***************************************************************************
*                       txCtrlParams_resetCounters
****************************************************************************
* DESCRIPTION:  Reset the tx data module counters
*
* INPUTS:       hTxCtrl - the object
*
* OUTPUT:
*
* RETURNS:
***************************************************************************/
void txCtrlParams_ResetCounters(void)
{
    txCtrl_t *pTxCtrl = gTxCtrlCB;

    os_memset(&pTxCtrl->txDataCounters, 0, sizeof(TTxDataCounters) * MAX_NUM_OF_AC);
    os_memset(&pTxCtrl->SumTotalDelayUs, 0, sizeof(pTxCtrl->SumTotalDelayUs));
}


/***********************************************************************
 *                        txCtrlParams_SetAdmissionCtrlParams
 ***********************************************************************
DESCRIPTION:    This function is called for add/delete a tspec in order
                to update parameters.

INPUT:          hTxCtrl - handale to the ts data object
                acId - the AC of the tspec
                mediumTime  - tha alocated medium time for this UP
                minimumPHYRate - the min phy rate to send a packet of this UP
                admFlag - indicate if the its addition or deletion of tspec

OUTPUT:     None

RETURN:     void
************************************************************************/
uint32_t txCtrlParams_SetAdmissionCtrlParams(uint32_t uHlid, uint8_t acId, uint16_t mediumTime, Bool_e admFlag)
{
    txCtrl_t *pTxCtrl = gTxCtrlCB;
    if(admFlag == TRUE)
    {
        /* tspec added */
        pTxCtrl->aAdmissionState[uHlid][acId] = AC_ADMITTED;
    }
    else
    {
        /* tspaec deleted */
        pTxCtrl->aAdmissionState[uHlid][acId] = AC_NOT_ADMITTED;
    }

    /* Update the Tx queues mapping after admission change. */
    txCtrl_UpdateQueuesMapping();

    return OK;
}


/* \brief   Get the Tx statistics counters
 */
void txCtrlParams_GetTxCtrlCounters(TTxDataCounters *pCounters)
{
    txCtrl_t *pTxCtrl = gTxCtrlCB;

    os_memcpy((uint8_t *)pCounters, &(pTxCtrl->txDataCounters[0]), 
                       sizeof(TTxDataCounters) * MAX_NUM_OF_AC);
}


/***********************************************************************
 *                        txCtrlParams_setCurrentPrivacyInvokedMode
 ***********************************************************************
DESCRIPTION:    Update the current privacy invoked mode.
************************************************************************/
void txCtrlParams_SetDataEncryptMode(uint32_t uHlid, Bool_e bEncryptMode)
{
    txCtrl_t *pTxCtrl = gTxCtrlCB;

    pTxCtrl->aEncryptData[uHlid] = bEncryptMode;
}

/***********************************************************************
DESCRIPTION:    Update the current pmf encryption.
************************************************************************/
void txCtrlParams_SetMgmtEncryptMode(uint32_t uHlid, Bool_e bPMFEncrypt)
{
   txCtrl_t *pTxCtrl = gTxCtrlCB;

   pTxCtrl->aEncryptMgmt[uHlid] = bPMFEncrypt;
}

/***********************************************************************
DESCRIPTION:    Return if current link is pmf encrypted
************************************************************************/
Bool_e txCtrlParams_GetMgmtEncryptMode(uint32_t uHlid)
{
   txCtrl_t *pTxCtrl = gTxCtrlCB;

   return pTxCtrl->aEncryptMgmt[uHlid];
}

/***********************************************************************
 *                        txCtrlParams_SetEapolEncryptionStatus
 ***********************************************************************
DESCRIPTION:    Update the Eapol Encryption Status.
************************************************************************/
void txCtrlParams_SetEapolEncryptionStatus (uint32_t uHlid, Bool_e bEapolEncryptionStatus)
{
    txCtrl_t *pTxCtrl = gTxCtrlCB;
    pTxCtrl->aEncryptEapol[uHlid] = bEapolEncryptionStatus;
}


/***********************************************************************
 *                        txCtrlParams_GetTxRate
 ***********************************************************************
DESCRIPTION:    Provide the last successfull data packet Tx rate.
************************************************************************/
tiwdrv_rate_e txCtrlParams_GetTxRate (uint32_t uHlid)
{
    txCtrl_t *pTxCtrl = gTxCtrlCB;

    return pTxCtrl->eCurrentTxRate[uHlid];
}


/***********************************************************************
 *                        txCtrlParams_SetAcAdmissionStatus
 ***********************************************************************
DESCRIPTION:    Update the link AC's admission status - required or not and admitted or not.
                Update also the queues mapping in case it should change.
************************************************************************/
void txCtrlParams_SetAcAdmissionStatus(uint32_t uHlid,
                                        uint8_t ac,
                                       EAdmissionState eAdmissionRequired,
                                       ETrafficAdmState eAdmissionState)
{
    txCtrl_t *pTxCtrl = gTxCtrlCB;

    pTxCtrl->aAdmissionRequired[uHlid][ac] = eAdmissionRequired;
    pTxCtrl->aAdmissionState[uHlid][ac]    = eAdmissionState;

    /* Update the Tx queues mapping after admission change. */
    txCtrl_UpdateQueuesMapping ();
}


/***********************************************************************
 *                        txCtrlParams_setAcMsduLifeTime
 ***********************************************************************
DESCRIPTION:    Update the AC MSDU lifetime. The units are TUs (1024 usec).
************************************************************************/
void txCtrlParams_setAcMsduLifeTime(RoleID_t eLmacRoleId, uint8_t ac, uint32_t uMsduLifeTimeTu)
{
    txCtrl_t *pTxCtrl = gTxCtrlCB;

    pTxCtrl->aMsduLifeTimeTu[eLmacRoleId][ac] = (uint16_t)uMsduLifeTimeTu;
}


/***********************************************************************
 *                        txCtrlParams_setAcAckPolicy
 ***********************************************************************
DESCRIPTION:    Update the AC Ack policy.
************************************************************************/
void txCtrlParams_setAcAckPolicy(uint32_t uHlid, uint8_t ac, AckPolicy_e ackPolicy)
{
    txCtrl_t *pTxCtrl = gTxCtrlCB;

    pTxCtrl->aAckPolicy[uHlid][ac] = ackPolicy;
}

void txCtrlParams_GetTsStatistics(reportTsStatisticsReq_t *pTsStatisticsReq)
{
    txCtrl_t *pTxCtrl = gTxCtrlCB;

    os_memcpy(pTsStatisticsReq->pTxDataCounters,
              &(pTxCtrl->txDataCounters[pTsStatisticsReq->acID]),
              sizeof(TTxDataCounters));
    os_memset(&(pTxCtrl->txDataCounters[pTsStatisticsReq->acID]), 0, sizeof(TTxDataCounters));
}

void txCtrlParams_GetDataLinkCounter(uint32_t link, TLinkDataCounters *pLinksDataCounters)
{
    txCtrl_t *pTxCtrl = gTxCtrlCB;

    pLinksDataCounters->sentPkts = pTxCtrl->dbgLinkCounters.dbgNumPktsSent[link];
    pLinksDataCounters->sentBytes = pTxCtrl->dbgLinkCounters.dbgNumBytesSent[link];
    pLinksDataCounters->sentPktsError = pTxCtrl->dbgLinkCounters.dbgNumPktsError[link];
}



/********************************************************************************
*                                                                               *
*                       DEBUG  FUNCTIONS  IMPLEMENTATION                        *
*                                                                               *
*********************************************************************************/

#ifdef TI_DBG

/***********************************************************************
 *                     txCtrlParams_printInfo
 ***********************************************************************
DESCRIPTION:    Print module internal information.
************************************************************************/
void txCtrlParams_printInfo(void)
{
#ifdef REPORT_LOG
    txCtrl_t *pTxCtrl = gTxCtrlCB;
    uint32_t i;

   //Report(("-------------- Tx-Ctrl Module Information --------------\r\n"));
   //Report(("========================================================\r\n"));
   //GTRACE(1, "PktsPendCompleteCounter     = %d\r\n",   pTxCtrl->uPktsPendCompleteCounter));
   //GTRACE(1, "AcBusyBitmap                = 0x%x\r\n", pTxCtrl->tBackpressure.uAcBusyBitmap));
   //GTRACE(1, "LinkBusyBitmap              = 0x%x\r\n", pTxCtrl->tBackpressure.uLinkBusyBitmap));
   //GTRACE(1, "LinkPriorityBitmap          = 0x%x\r\n", pTxCtrl->tBackpressure.uLinkPriorityBitmap));
   //GTRACE(1, "UpDowngradedLink (none=255) = %d\r\n",   pTxCtrl->uUpDowngradedLink));
   //GTRACE(1, "UpDowngradedLinkAcMapping[3,2,1,0]   =  %d,   %d,   %d,   %d\r\n",
                    pTxCtrl->aUpDowngradedLinkAcMapping[3], pTxCtrl->aUpDowngradedLinkAcMapping[2],
                    pTxCtrl->aUpDowngradedLinkAcMapping[1], pTxCtrl->aUpDowngradedLinkAcMapping[0]));
   //Report(("--------------------------------------------------------\r\n"));
   //GTRACE(1, "Per Link Tx Attributes:\r\n"));
   //Report(("-----------------------\r\n"));
    for (i = 0; i < WLANLINKS_MAX_LINKS; i++) 
    {
       //Report(("\nHlid %d:\r\n", i));
       //GTRACE(1, "WmeEnabled            = %d\r\n", pTxCtrl->pUdata->aWmeEnabled[i]));
       //GTRACE(1, "EncryptEapol          = %d\r\n", pTxCtrl->aEncryptEapol[i]));
       //GTRACE(1, "EncryptData           = %d\r\n", pTxCtrl->aEncryptData[i]));
       //GTRACE(1, "aAdmissionRequired[3,2,1,0]   =  %d,   %d,   %d,   %d\r\n",
            pTxCtrl->aAdmissionRequired[i][3], pTxCtrl->aAdmissionRequired[i][2],
            pTxCtrl->aAdmissionRequired[i][1], pTxCtrl->aAdmissionRequired[i][0]));
       //GTRACE(1, "aAdmissionState[3,2,1,0]      =  %d,   %d,   %d,   %d\r\n",
            pTxCtrl->aAdmissionState[i][3], pTxCtrl->aAdmissionState[i][2],
            pTxCtrl->aAdmissionState[i][1], pTxCtrl->aAdmissionState[i][0]));
    }
   //Report(("========================================================\n\r\n"));
#endif
}


/***********************************************************************
 *                     txCtrlParams_printDebugCounters
 ***********************************************************************
DESCRIPTION:    Print Tx statistics debug counters.
************************************************************************/
void txCtrlParams_printDebugCounters(void)
{
#ifdef REPORT_LOG
    txCtrl_t *pTxCtrl = gTxCtrlCB;
    txDataDbgCounters_t *pDbg = &pTxCtrl->dbgCounters;    /* debug counters */
    txDataDbgLinkCounters_t *pLinkDbg = &pTxCtrl->dbgLinkCounters;    /* debug counters */
    uint32_t uHlid;

   //Report(("-------------- Tx-Ctrl Statistics Per AC ---------------\r\n"));
   //Report(("========================================================\r\n"));

   //GTRACE(1, "dbgNumPktsSent:         %8d %8d %8d %8d\r\n", pDbg->dbgNumPktsSent[0], pDbg->dbgNumPktsSent[1], pDbg->dbgNumPktsSent[2], pDbg->dbgNumPktsSent[3]));
   //GTRACE(1, "dbgNumPktsBusy:         %8d %8d %8d %8d\r\n", pDbg->dbgNumPktsBusy[0], pDbg->dbgNumPktsBusy[1], pDbg->dbgNumPktsBusy[2], pDbg->dbgNumPktsBusy[3]));
   //GTRACE(1, "dbgNumPktsLinkBusy:     %8d %8d %8d %8d\r\n", pDbg->dbgNumPktsLinkBusy[0], pDbg->dbgNumPktsLinkBusy[1], pDbg->dbgNumPktsLinkBusy[2], pDbg->dbgNumPktsLinkBusy[3]));
   //GTRACE(1, "dbgNumPktsXfered:       %8d %8d %8d %8d\r\n", pDbg->dbgNumPktsXfered[0], pDbg->dbgNumPktsXfered[1], pDbg->dbgNumPktsXfered[2], pDbg->dbgNumPktsXfered[3]));
   //GTRACE(1, "dbgNumPktsSuccess:      %8d %8d %8d %8d\r\n", pDbg->dbgNumPktsSuccess[0], pDbg->dbgNumPktsSuccess[1], pDbg->dbgNumPktsSuccess[2], pDbg->dbgNumPktsSuccess[3]));
   //GTRACE(1, "dbgNumPktsError:        %8d %8d %8d %8d\r\n", pDbg->dbgNumPktsError[0], pDbg->dbgNumPktsError[1], pDbg->dbgNumPktsError[2], pDbg->dbgNumPktsError[3]));
   //GTRACE(1, "dbgNumTxCmplt:          %8d %8d %8d %8d\r\n", pDbg->dbgNumTxCmplt[0], pDbg->dbgNumTxCmplt[1], pDbg->dbgNumTxCmplt[2], pDbg->dbgNumTxCmplt[3]));
   //GTRACE(1, "dbgNumTxCmpltOk:        %8d %8d %8d %8d\r\n", pDbg->dbgNumTxCmpltOk[0], pDbg->dbgNumTxCmpltOk[1], pDbg->dbgNumTxCmpltOk[2], pDbg->dbgNumTxCmpltOk[3]));
   //GTRACE(1, "dbgNumTxCmpltError:     %8d %8d %8d %8d\r\n", pDbg->dbgNumTxCmpltError[0], pDbg->dbgNumTxCmpltError[1], pDbg->dbgNumTxCmpltError[2], pDbg->dbgNumTxCmpltError[3]));
   //GTRACE(1, "dbgNumTxCmpltOkBytes:   %8d %8d %8d %8d\r\n", pDbg->dbgNumTxCmpltOkBytes[0], pDbg->dbgNumTxCmpltOkBytes[1], pDbg->dbgNumTxCmpltOkBytes[2], pDbg->dbgNumTxCmpltOkBytes[3]));

   //Report(("-------------- Tx-Ctrl Statistics Per LINK ---------------\r\n"));
    for(uHlid = 0; uHlid < WLANLINKS_MAX_LINKS; uHlid++)
    {
       //Report(("====    Link %d    ===================================\r\n", uHlid));
       //GTRACE(1, "dbgNumPktsSent:         %8d\r\n", pLinkDbg->dbgNumPktsSent[uHlid]));
       //GTRACE(1, "dbgNumBytesSent:        %8d\r\n", pLinkDbg->dbgNumBytesSent[uHlid]));
       //GTRACE(1, "dbgNumPktsXfered:       %8d\r\n", pLinkDbg->dbgNumPktsXfered[uHlid]));
       //GTRACE(1, "dbgNumPktsSuccess:      %8d, dbgNumPktsError:      %8d\r\n", pLinkDbg->dbgNumPktsSuccess[uHlid], pLinkDbg->dbgNumPktsError[uHlid]));
       //GTRACE(1, "dbgNumTxCmplt:          %8d\r\n", pLinkDbg->dbgNumTxCmplt[uHlid]));
       //GTRACE(1, "dbgNumTxCmpltOk:        %8d, dbgNumTxCmpltError:   %8d, dbgNumTxCmpltOkBytes: %8d\r\n", pLinkDbg->dbgNumTxCmpltOk[uHlid], pLinkDbg->dbgNumTxCmpltError[uHlid], pLinkDbg->dbgNumTxCmpltOkBytes[uHlid]));
    }

   //Report(("========================================================\n\r\n"));
#endif
}

#endif   /* TI_DBG */


/***************************************************************************
*                       txCtrlParams_resetDbgCounters
****************************************************************************
* DESCRIPTION:  Reset the tx data module debug counters
***************************************************************************/
void txCtrlParams_resetDbgCounters(void)
{
    txCtrl_t *pTxCtrl = gTxCtrlCB;

    os_memset(&pTxCtrl->dbgCounters, 0, sizeof(txDataDbgCounters_t));
    os_memset(&pTxCtrl->dbgLinkCounters, 0, sizeof(txDataDbgLinkCounters_t));
}

/***************************************************************************
*                       txCtrlParams_resetLinkCounters
****************************************************************************
* DESCRIPTION:  Reset the tx data module Link counters
***************************************************************************/
void txCtrlParams_GetLinkCounters(uint32_t link, dbg_cntr_trnspt_t *counters)
{
    txCtrl_t *pTxCtrl = gTxCtrlCB;

    counters->link_tx_dbgNumPktsSent       = pTxCtrl->dbgLinkCounters.dbgNumPktsSent      [link] ;
    counters->link_tx_dbgNumBytesSent      = pTxCtrl->dbgLinkCounters.dbgNumBytesSent     [link] ;
    counters->link_tx_dbgNumPktsBusy       = pTxCtrl->dbgLinkCounters.dbgNumPktsBusy      [link] ;
    counters->link_tx_dbgNumPktsAcBusy     = pTxCtrl->dbgLinkCounters.dbgNumPktsAcBusy    [link] ;
    counters->link_tx_dbgNumPktsXfered     = pTxCtrl->dbgLinkCounters.dbgNumPktsXfered    [link] ;
    counters->link_tx_dbgNumPktsSuccess    = pTxCtrl->dbgLinkCounters.dbgNumPktsSuccess   [link] ;
    counters->link_tx_dbgNumPktsError      = pTxCtrl->dbgLinkCounters.dbgNumPktsError     [link] ;
    counters->link_tx_dbgNumTxCmplt        = pTxCtrl->dbgLinkCounters.dbgNumTxCmplt       [link] ;
    counters->link_tx_dbgNumTxCmpltOk      = pTxCtrl->dbgLinkCounters.dbgNumTxCmpltOk     [link] ;
    counters->link_tx_dbgNumTxCmpltError   = pTxCtrl->dbgLinkCounters.dbgNumTxCmpltError  [link] ;
    counters->link_tx_dbgNumTxCmpltOkBytes = pTxCtrl->dbgLinkCounters.dbgNumTxCmpltOkBytes[link] ;
    counters->link_tx_dbgNumTxCmpltFailBytes = pTxCtrl->dbgLinkCounters.dbgNumTxCmpltFailBytes[link] ;

    counters->link_tx_dbgTimeFirstPacket_Ms  = pTxCtrl->dbgLinkCounters.dbgTimeFirstPacket_Ms[link] ;
    counters->link_tx_dbgTimeLastPacket_Ms   = pTxCtrl->dbgLinkCounters.dbgTimeLastPacket_Ms[link] ;

    counters->link_tx_dbgStackTimeFirstPacket_Ms  = pTxCtrl->dbgLinkCounters.dbgStackEntrTimeFirstPacket_Ms[link] ;
    counters->link_tx_dbgStackTimeLastPacket_Ms   = pTxCtrl->dbgLinkCounters.dbgStackEntrTimeLastPacket_Ms[link] ;
    counters->link_tx_dbgStackEntrNumByteSent     = pTxCtrl->dbgLinkCounters.dbgStackEntrNumByteSent[link] ;
    counters->link_tx_dbgStackEntNumPktsXfered    = pTxCtrl->dbgLinkCounters.link_tx_dbgStackEntNumPktsXfered[link] ;
}

void txCtrlParams_resetLinkCounters(uint32_t uHlid)
{
    txCtrl_t *pTxCtrl = gTxCtrlCB;

    if (uHlid < WLANLINKS_MAX_LINKS)
    {
        pTxCtrl->dbgLinkCounters.dbgStartCollectCntrStackEntr[uHlid] = 1;
        pTxCtrl->dbgLinkCounters.dbgStartCollectCntr[uHlid] = 1;

        pTxCtrl->dbgLinkCounters.dbgNumPktsSent[uHlid] = 0;
        pTxCtrl->dbgLinkCounters.dbgNumBytesSent[uHlid] = 0;
        pTxCtrl->dbgLinkCounters.dbgNumPktsBusy[uHlid] = 0;
        pTxCtrl->dbgLinkCounters.dbgNumPktsAcBusy[uHlid] = 0;
        pTxCtrl->dbgLinkCounters.dbgNumPktsXfered[uHlid] = 0;
        pTxCtrl->dbgLinkCounters.dbgNumPktsSuccess[uHlid] = 0;
        pTxCtrl->dbgLinkCounters.dbgNumPktsError[uHlid] = 0;
        pTxCtrl->dbgLinkCounters.dbgNumTxCmplt[uHlid] = 0;
        pTxCtrl->dbgLinkCounters.dbgNumTxCmpltOk[uHlid] = 0;
        pTxCtrl->dbgLinkCounters.dbgNumTxCmpltError[uHlid] = 0;
        pTxCtrl->dbgLinkCounters.dbgNumTxCmpltOkBytes[uHlid] = 0;
        pTxCtrl->dbgLinkCounters.dbgNumTxCmpltFailBytes[uHlid] = 0;
    }
}

