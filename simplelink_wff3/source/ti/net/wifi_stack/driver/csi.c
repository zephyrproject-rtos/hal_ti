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
#include "osi_kernel.h"
#include "wlan_if.h"
#include "csi.h"
#include "errors.h"


CSICB_t gCSICB = {0};


int CSI_GetQueueSize();
Bool_e CSI_GetEnable();


int CSI_Init(WlanSetCSIParams_t *csiParams)
{
    int ret = WLAN_RET_CODE_OK;
    if(NULL != gCSICB.pMsgQ)
    {
        ret = WlanError(WLAN_ERROR_SEVERITY__MID, WLAN_ERROR_MODULE__COMMANDS, WLAN_ERROR_TYPE__CSI_ALREADY_STARTED);
        return ret;
    }

    gCSICB.pMsgQ = os_malloc(sizeof(OsiMsgQ_t));
    gCSICB.pLockObj = os_malloc(sizeof(OsiLockObj_t));

    if((NULL == gCSICB.pMsgQ) || (NULL == gCSICB.pLockObj))
    {
        ret = WlanError(WLAN_ERROR_SEVERITY__MID, WLAN_ERROR_MODULE__COMMANDS, WLAN_ERROR_TYPE__MALLOC);
        goto fail;
    }

    if(csiParams->blocking == WLAN_CSI_MSG_Q_BLOCKING)
    {
        gCSICB.msgQueueTO = OSI_WAIT_FOREVER;
    }
    else if(csiParams->blocking == WLAN_CSI_MSG_Q_NONBLOCKING)
    {
        gCSICB.msgQueueTO = 0;
    }
    else
    {
        //ret = WLAN_RET_CODE_INVALID_INPUT;
        ret = WlanError(WLAN_ERROR_SEVERITY__LOW, WLAN_ERROR_MODULE__COMMANDS, WLAN_ERROR_TYPE__INVALID_PARAM_SET_TYPE);

        goto fail;
    }

    gCSICB.queueSize = csiParams->queueSize;

    // Create the message queue
    ret = osi_MsgQCreate(gCSICB.pMsgQ, "CsiMsgQ", sizeof(WlanGetCSIData_t),
                      gCSICB.queueSize);

    if (ret != OSI_OK)
    {
        goto fail;
    }

    return ret;

fail:
    if(NULL != gCSICB.pMsgQ)
    {
        os_free(gCSICB.pMsgQ);
    }
    if(NULL != gCSICB.pLockObj)
    {
        os_free(gCSICB.pLockObj);
    }
    os_memset(&gCSICB,0,sizeof(CSICB_t));

    return ret;
}




void CSI_Deinit()
{
    if(NULL != gCSICB.pMsgQ)
    {
        os_free(gCSICB.pMsgQ);
    }
    if(NULL != gCSICB.pLockObj)
    {
        os_free(gCSICB.pLockObj);
    }
    os_memset(&gCSICB,0,sizeof(CSICB_t));
}


int CSI_PushMessage(WlanGetCSIData_t *pCsiData)
{
    OsiReturnVal_e rc;
    int ret = WLAN_RET_CODE_OK;


    if(NULL != gCSICB.pMsgQ)
    {
        int queueDepth = osi_MsgQCount(gCSICB.pMsgQ);
        if (queueDepth >= gCSICB.queueSize-1)
        {
            return ret;
        }
        // CSI is enabled
       // Start pushing the info into the message queue
        ret = osi_MsgQWrite(gCSICB.pMsgQ, pCsiData, OSI_NO_WAIT, OSI_FLAG_NOT_FROM_INTR);
    }

    return ret;
}


int CSI_GetMessage(WlanGetCSIData_t *pCsiData)
{
    int ret = WLAN_RET_CODE_OK;

    if(NULL != gCSICB.pMsgQ)
    {
        // CSI is enabled
        // copy the CSI data to memory allocated by the caller
        ret = osi_MsgQRead(gCSICB.pMsgQ, (void *)pCsiData, gCSICB.msgQueueTO);
    }
    return (ret);
}



int CSI_GetQueueSize()
{
    return gCSICB.queueSize;
}

Bool_e CSI_GetEnable()
{
    if(NULL == gCSICB.pMsgQ)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}


