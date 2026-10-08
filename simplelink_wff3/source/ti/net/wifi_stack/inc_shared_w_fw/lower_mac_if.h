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
#ifndef _LOWER_MAC_IF_H
#define _LOWER_MAC_IF_H


#include "public_types.h"
#include <stdarg.h>
#include "l2_cfg.h"

// ============================================================================
//		UPPER MAC VERSION
// ============================================================================
#define version_upper_mac       "upper_mac_rev_1.1.1.0"

// ============================================================================
//		LOWER MAC STUB FUNCTION INTERFACE
// ============================================================================

// upper mac function pointer 
struct um_stub_func {

    /* ================ malloc/free  ================= */
#ifdef MALLOC_FREE_DEBUG_ENABLE
    void* (*Malloc)(const char *pFunc, int line, uint32 Size);
    void* (*Zalloc)(const char *pFunc, int line, size_t Size);
    void* (*Realloc)(const char *pFunc, int line, void *oldptr, uint32 Size);
    void  (*Free)(const char *pFunc, int line, void* pMem);
#else
    void* (*Malloc)( uint32 Size);
    void* (*Zalloc)(uint32 Size);
    void* (*Realloc)(void *oldptr, uint32 Size);
    void  (*Free)(void* pMem);
#endif //MALLOC_FREE_DEBUG_ENABLE

    /* ================ OS ================= */
    size_t  (*os_strlcpy)       (char *dest, const char *src, size_t size);
    char *  (*os_strdup)        (const char *s);
    void *  (*os_memdup)        (const void *src, size_t len);
    int     (*os_strcasecmp)    (const char *s1, const char *s2);
    int     (*os_strncasecmp)   (const char *s1, const char *s2, size_t n);
    char *  (*os_strchr)        (const char *s, int c);
    int     (*os_memcmp_const)  (const void *a, const void *b, size_t len);
    void *  (*os_calloc)        (size_t nmemb, size_t size);
    void *  (*os_realloc_array) (void *ptr, size_t nmemb, size_t size);
    void    (*os_sleep)         (os_time_t sec, os_time_t usec);
    int     (*os_get_time)      (struct os_time *t);
    int     (*os_get_reltime)   (struct os_reltime *t);
    int     (*os_gmtime)        (os_time_t t, struct os_tm *tm);
    int     (*os_daemonize)     (const char *pid_file);
    int     (*os_get_random)    (unsigned char *buf, size_t len);
    char *  (*os_readfile)      (const char *name, size_t *len);
    char *  (*os_strtok_r)      (char *s, const char *delim, char **last);
    void    (*os_daemonize_terminate)(const char *pid_file);
    unsigned long (*os_random)  (void);


    int     (*vprintf)          (const char *_format, va_list _ap);
    int     (*printf)           (const char *_format, ...);
    int     (*rand)             (void);
    char *  (*fgets)            (char *_ptr, register int _size, register FILE *_fp);

    /*                   SingalObject                  */
    OsiReturnVal_e (*SyncObjCreate)(OsiSyncObj_t* pSyncObj);
    OsiReturnVal_e (*SyncObjDelete)(OsiSyncObj_t* pSyncObj);
    OsiReturnVal_e (*SyncObjSignal)(OsiSyncObj_t* pSyncObj);
    OsiReturnVal_e (*SyncObjWait)(OsiSyncObj_t* pSyncObj , OsiTime_t Timeout);
    OsiReturnVal_e (*SyncObjClear)(OsiSyncObj_t* pSyncObj);

    /*                    MsgQueue                     */
    OsiReturnVal_e (*MsgQCreate)(OsiMsgQ_t* pMsgQ ,char* pMsgQName, uint32 MsgSize, uint32 MaxMsgs, uint8 *pQueue);
    OsiReturnVal_e (*MsgQDelete)(OsiMsgQ_t* pMsgQ);
    OsiReturnVal_e (*MsgQWrite)(OsiMsgQ_t* pMsgQ, void* pMsg , OsiTime_t Timeout);
    OsiReturnVal_e (*MsgQRead)(OsiMsgQ_t* pMsgQ, void* pMsg , OsiTime_t Timeout);
    uint32         (*MsgQCount)(OsiMsgQ_t* pMsgQ);
    uint8          (*MsgQIsEmpty)(OsiMsgQ_t* pMsgQ);

    /*                    Time                         */
    uint32         (*GetTimeMS)();
    OsiReturnVal_e (*TimerStart)    (OsiTimer_t* pTimer ,OsiTime_t DurationMiliSec,unsigned char Periodic);
    OsiReturnVal_e (*TimerStop)     (OsiTimer_t* pTimer);
    OsiReturnVal_e (*TimerCreate)   (OsiTimer_t* pTimer,char* pTimerName, P_TIMER_EXPIRY_LEGACY_FUNCTION pExpiryFunc,void* pParam);
    OsiReturnVal_e (*TimerDelete)   (OsiTimer_t* pTimer);
    OsiReturnVal_e (*Sleep)         (OsiTime_t sec);

    /*                    Thread                      */
    OsiReturnVal_e (*CmeThreadInit)(void* pFunc, uint32_t cmeMsgQuqueSize);
    OsiReturnVal_e (*CmeThreadDeinit)(OsiThread_t* pThread);

    /*                    CME OS Objects              */
    void *(*CmeMsgQ);
    void *(*CmeThreadCB);
    void *(*CmeSyncObjStop);
    void *(*CmeSyncObjCommand);
    void *(*CmeFastConnectTimer);

    /*  
                        Dispatcher                      
    */
    uint16 (*CommandDispatch)(void *pCmd, void *pCmdComplete);       

    /*  
                        MAC ADDRESS                      
    */
    void *(*staRole); 
    void *(*apRole);                 

    /* ========== Managment packet related =========== */
    void (*ConfigMngPackForRetransmition)(void *apDescriptor, void *apSendReq);
    int32 (*AllocAndConfigMngPack)(uint32 aRoleId, uint32 aPayloadSize, uint32 aType, uint8 aKeepAfterTx, uint8 *apDescId, void **apMngPack, void **apDescriptor, void *apSendReq);
    int32 (*TranslateTxDesc)(uint8 descId, void **addr, uint32_t *pPayloadSize, uint32_t *pHdrSize, uint32_t *linkId);

    void (*ForwardToLtxp)(void *apSendReq);
    void (*ReleaseDeallocDescriptorByDescId)(uint8 descId);
    void (*ReleaseDeallocDescriptor)(void *desc);

    /* ================== L2 Config ==================== */
	uint32 		    (*l2_cfg_isStaHeEnabled)(void);
	uint32 		    (*l2_cfgIs11nEnabled)();
	void 		    (*l2_cfgGetRates)(uint32 aRoleType, uint32 *apBasicRatesBM, uint32 *apSupportedRatesBM);
	uint32 		    (*l2_cfgGetWmmParameters)(const void **pAcCfg);
	uint32 		    (*l2_cfgGetHtCapabilities)(const void **apHtCapabilities);
	uint32 	    	(*l2_cfgBuildHtCapabilitiesIe)(uint32 aRoleId, uint8 *apHtCapsIE);
#ifndef DISABLE_WIFI6
	uint32 		    (*l2_cfgBuildHeCapabilitiesIe)(uint32 aRoleId, uint8 *apHeCapsIE);
#endif
	uint8 		    (*l2_cfgGetApMaxNumStations )(void);
	void 	    	(*l2_cfgSetApMaxNumStations)(uint8 apMaxNumStations);
	uint32_t 	    (*l2_cfgGetSupportedBands)();
	uint32 		    (*l2_cfgIsStaWmeEnabled)();
	uint32 		    (*l2_cfgIsApWmeEnabled)();
	uint32 		    (*l2_cfgIsApPmfEnabled)();
	uint32 		    (*l2_cfgIsStaPmfEnabled)();
	uint32 		    (*l2_cfgIsStaShortPreambleEnabled)();
	uint8           (*l2_cfgGetStadot11Mode)();
	uint32 		    (*l2_cfgIsStaShortSlotEnabled)();
	const void *    (*l2_cfgGetApCfg)();
    uint8           (*l2_cfgGetAcPsMode) (uint8 psIdx);
    uint8           (*l2_cfgGetMaxSpLen)();
    uint8           (*l2_cfgGetHeMoreDataBit)();


    /* ================== IE PARSER ==================== */
    uint32  (*IEParser_FindIe)(uint8* payloadStart, uint16  payloadLength, uint8  ieId, uint8**   pIe);
    uint8   (*IEParser_FindVendorSpecificIe)(uint8* payloadStart, uint16  payloadLength, uint8* pInputOui, uint8**   pIe);


    /* ================== FW UTILS ==================== */
    uint32 	(*FWUtils_convertBitmapToRatesIe)(uint32 aSupportedRatesBM, uint32 aBasicRatesBM, uint8 *apRatesBuff);
    uint32  (*FWUtils_convertBitmapToSupplicantRates)(uint32 aSupportedRatesBM, int    *apRatesBuff);
    uint32  (*FWUtils_convertNetRatesToBitmap)(const uint8 *apRatesIe, uint32 aNumRates);
    void 	(*FWUtils_getPeerRates)(void *apCandidateDesc, void *apLinkRates);

};

//extern const struct um_stub_func  g_stub_func;

#endif //_LOWER_MAC_IF_H
