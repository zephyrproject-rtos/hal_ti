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
#include <bus_if.h>
#include <data_path/udata/export_inc/udata_api.h>
#include <fw_event_handle.h>
#include <fw_event_if.h>
#include <init_host_if.h>
#include <trnspt_if.h>
#include <trnspt_if.h>
#include <trnspt_thread.h>
#include "osi_kernel.h"
#include "commands.h"
#include "timer.h"

#include "wlan_links.h"
#include "errors.h"
#include <wlan_irq_adapt.h>
#include "fw_status.h"
#include "control_cmd_fw.h"
#include "rx.h"
#include "tx.h"
#include "tx_ctrl_blk_api.h"
#include "tx_hw_queue_api.h"
#include "tx_xfer_api.h"
#include "tx_result_api.h"
#include "drv_ti_internal.h"
#include "rx_api.h"
#include "tx_ctrl_api.h"
#include "tw_driver.h"
#include "init_host.h"
#include "l2_cfg.h"
#include <stdbool.h>
#include <stdio.h>
/******************************************************************************
                                    EXTERN
******************************************************************************/

/******************************************************************************
                                    DEFINE 
******************************************************************************/

/******************************************************************************
                                    Global 
******************************************************************************/


// MAC address from fuse
extern TMacAddr g_fuse_mac_addr[];
extern OsiLockObj_t driverLock;//TODO verify if this can be removed

extern int32_t init_device(uint32_t commandsEventsSizeBTL,uint32_t commandsEventsSize);
extern int32_t Deinit_device(void);
extern int32_t HwInit(void);
extern int32_t DeHwInit(void);


/******************************************************************************
                                    FUNCTION 
******************************************************************************/
static void SetMacAddress(uint32_t mac1, uint32_t mac2);
void UploadFW(FILE *DeviceFileHandle);
extern int32_t cc3xxx_set_defaults();
extern uint32_t drv_getDriverLink(uint32_t uNetIfId, uint8_t* dst);
extern OsiLockObj_t extAppLockObj;
extern bool open_at_cc35xx_debug(const char *text);

static void init_host_debug(const char *text)
{
    (void)open_at_cc35xx_debug(text);
}

static void init_host_debug_ret(const char *tag, int32_t ret)
{
    char buf[88];

    (void)snprintf(buf, sizeof(buf), "\r\nDBG_INIT:%s ret=%d\r\n", tag, ret);
    init_host_debug(buf);
}


/******************************************************************************

    NAME:           InitHostDriver

    PROTOTYPE:      init

    DESCRIPTION:    First Init

    CALLER:         ChipWakeUp

    RETURNS:        NONE
******************************************************************************/
int32_t InitHostDriver(void)
{
    uint32_t config;
    int32_t ret;
    FwStatus_t stat;
    const TPartition aPartition[] = {{0,0xF0000},{0,0},{0,0},{0,0}};
    uint32_t TrnsptThrdPrior;

    init_host_debug("\r\nDBG_INIT:enter\r\n");

    init_host_debug("\r\nDBG_INIT:wlan_IRQDeinit enter\r\n");
    wlan_IRQDeinit();
    init_host_debug("\r\nDBG_INIT:wlan_IRQDeinit done\r\n");

    osi_LockObjCreate(&driverLock);

    ret = osi_LockObjCreate(&extAppLockObj);
    init_host_debug_ret("extAppLockObj", ret);
    if (ret != OSI_OK)
    {
        ASSERT_GENERAL(0);
        return(ret);
    }


    init_host_debug("\r\nDBG_INIT:ctrlCmdFw_CreateMsgQueue enter\r\n");
    ctrlCmdFw_CreateMsgQueue();
    init_host_debug("\r\nDBG_INIT:ctrlCmdFw_CreateMsgQueue done\r\n");

    /* Transport init */
    TrnsptThrdPrior = TRANSPORT_THREAD_PRIORITY;
    init_host_debug("\r\nDBG_INIT:trnspt_Init enter\r\n");
    ret = trnspt_Init(TrnsptThrdPrior);
    init_host_debug_ret("trnspt_Init", ret);
    if(ret < 0)
    {
        ASSERT_GENERAL(0);
        return(ret);
    }

    init_host_debug("\r\nDBG_INIT:twIf_Init enter\r\n");
    twIf_Init();
    init_host_debug("\r\nDBG_INIT:twIf_Init done\r\n");
    twIf_SetPartition(aPartition);
    init_host_debug("\r\nDBG_INIT:twIf_SetPartition done\r\n");
    tmr_Init();
    init_host_debug("\r\nDBG_INIT:tmr_Init done\r\n");

    init_host_debug("\r\nDBG_INIT:fwEvent_Init enter\r\n");
    ret |= fwEvent_Init(RX_TX_BUFFER,CONTROL_BUFFER_READ_SIZE);
    init_host_debug_ret("fwEvent_Init cumulative", ret);
    init_host_debug("\r\nDBG_INIT:ctrlCmdFw_CreateEventThread enter\r\n");
    ctrlCmdFw_CreateEventThread();
    init_host_debug("\r\nDBG_INIT:ctrlCmdFw_CreateEventThread done\r\n");
    init_host_debug("\r\nDBG_INIT:wlan_IRQInitBeforeHwInit enter\r\n");
    wlan_IRQInitBeforeHwInit(FwEvent_irq_handler);
    init_host_debug("\r\nDBG_INIT:wlan_IRQInitBeforeHwInit done\r\n");
    init_host_debug("\r\nDBG_INIT:cmd_Init enter\r\n");
    ret |= cmd_Init();
    init_host_debug_ret("cmd_Init cumulative", ret);

    init_host_debug("\r\nDBG_INIT:rx_Init enter\r\n");
    ret |= rx_Init();
    init_host_debug_ret("rx_Init cumulative", ret);

    init_host_debug("\r\nDBG_INIT:udata_Create enter\r\n");
    TUdata *pUdata = udata_Create();
    init_host_debug(pUdata ? "\r\nDBG_INIT:udata_Create ok\r\n" :
                             "\r\nDBG_INIT:udata_Create fail\r\n");
    if (pUdata == NULL)
    {
        return NOK;
    }
#ifdef REMOVE_TX_CODE
    ret |= rxXfer_Init(); //TODO to remove
#endif
    init_host_debug("\r\nDBG_INIT:txXferAggr_Init enter\r\n");
    ret |= txXferAggr_Init();
    init_host_debug_ret("txXferAggr_Init cumulative", ret);
    init_host_debug("\r\nDBG_INIT:txXfer_Init enter\r\n");
    ret |= txXfer_Init();
    init_host_debug_ret("txXfer_Init cumulative", ret);
    init_host_debug("\r\nDBG_INIT:txResult_Init enter\r\n");
    ret |= txResult_Init();
    init_host_debug_ret("txResult_Init cumulative", ret);
    init_host_debug("\r\nDBG_INIT:txCtrlBlk_Init enter\r\n");
    ret |= txCtrlBlk_Init();
    init_host_debug_ret("txCtrlBlk_Init cumulative", ret);
    init_host_debug("\r\nDBG_INIT:txHwQueue_Init enter\r\n");
    ret |= txHwQueue_Init();
    init_host_debug_ret("txHwQueue_Init cumulative", ret);
    // for lx ret |= tx_Init();

    init_host_debug("\r\nDBG_INIT:udata_Init enter\r\n");
    ret |= udata_Init(pUdata);//must be performed after rx_Init()
    init_host_debug_ret("udata_Init cumulative", ret);
    if(ret)
    {
        Report("\r\nERROR !udata_Init failed");
        ASSERT_GENERAL(0);
        return(ret);
    }

    if(ret)
    {
        ASSERT_GENERAL(0);
    }


    init_host_debug("\r\nDBG_INIT:wlanLinks_Init enter\r\n");
    wlanLinks_Init();
    init_host_debug("\r\nDBG_INIT:wlanLinks_Init done\r\n");


    /* Set HW init */
    init_host_debug("\r\nDBG_INIT:HwInit enter\r\n");
    ret = HwInit();
    init_host_debug_ret("HwInit", ret);

    if(ret < 0)
    {
        Report("\r\nERROR !HwInit failed \n\r");
        ASSERT_GENERAL(0);
    }

    Report("Hardware init DONE! \n\r");


    //OSPREY_MX-123 ,TODO , bus send init command should be called before fwEvent_Init
    // because on FwEvent init the bus interrupt is enabled,
    //SPI init also send data to the FW,
    //so need to separate  the init into two init function
    init_host_debug("\r\nDBG_INIT:bus_sendInitCommand enter\r\n");
    bus_sendInitCommand(0/*not used*/, 0);
    init_host_debug("\r\nDBG_INIT:bus_sendInitCommand done\r\n");

    /* enable the IRQ interrupt */
    init_host_debug("\r\nDBG_INIT:wlan_IRQEnableInt enter\r\n");
    wlan_IRQEnableInt();
    init_host_debug("\r\nDBG_INIT:wlan_IRQEnableInt done\r\n");

    init_host_debug("\r\nDBG_INIT:cc3xxx_set_defaults enter\r\n");
    ret = cc3xxx_set_defaults();
    init_host_debug_ret("cc3xxx_set_defaults", ret);

    if(ret < 0)
    {
        Report("\r\nERROR !set defults failed");
        ASSERT_GENERAL(0);
    }
    init_host_debug("\r\nDBG_INIT:init_device enter\r\n");
    ret = init_device((uint32_t)CONTROL_BUFFER_READ_SIZE_BTL,(uint32_t)CONTROL_BUFFER_READ_SIZE);
    init_host_debug_ret("init_device", ret);

    if(ret < 0)
    {
        Report("\r\nERROR !Init device FAILED");
        ASSERT_GENERAL(0);
    }

    return ret;
}

/******************************************************************************

    NAME:           DeInitHostDriverInternal

    PROTOTYPE:      deinitialization

    DESCRIPTION:    This function call from transport thread context and destroy
                    the relevant module before destroy transport thread

    CALLER:         DeinitFW

    RETURNS:        NONE
******************************************************************************/
void DeInitHostDriverInternal(void * hCbHndl)
{
    int32_t ret = 0;

    ret = udata_Destroy();
    if (ret)
    {
        goto fail;
    }

    /* Data path */
    ret = txXferAggr_Destroy();

    if (ret)
    {
        goto fail;
    }

    /* Data path */
    ret = txXfer_Destroy();

    if (ret)
    {
        goto fail;
    }


    ret = txResult_Destroy();
    if (ret)
    {
        goto fail;
    }
#ifdef REMOVE_TX_CODE
    rxXfer_Destroy();
#endif
    ret = txCtrlBlk_Destroy();
    if (ret)
    {
        goto fail;
    }

    ret = txHwQueue_Destroy();
    if (ret)
    {
        goto fail;
    }

    ret = wlanLinks_Destroy();
    if (ret)
    {
        goto fail;
    }

    tmr_Destroy();
    bus_sendDeInitCommand();
    DeHwInit();
    fwEvent_Destroy();
    rx_Deinit();
    // lx tx_Deinit();
    cmd_Deinit();

    Report("\n\rDeinit modules DONE!");

    return;

fail:

    Report("Hardware deinit FAILED!!!!!! ret = %d \n\r", ret);
    ASSERT_GENERAL(0);
    return;
}

/******************************************************************************

    NAME:           DeInitHostDriver

    PROTOTYPE:      deinit

    DESCRIPTION:    deinit - Turn off WL chip and

    CALLER:

    RETURNS:        NONE
******************************************************************************/
int32_t DeInitHostDriver(void)
{
    uint32_t ret = 0;
    uint32_t uDestroyClientId;
    uDestroyClientId = trnspt_RegisterClient((TTransportCbFunc)DeInitHostDriverInternal, TRUE);
    TRANSPORT_PRINT_INIT("\n\rRegister Client:DeInitHostDriverInternal uDestroyClientId :%d",uDestroyClientId);


    if(0 == uDestroyClientId)
    {
        /* max number of clients is exceeded, report error and exit. */
        ASSERT_GENERAL(0);
        return WlanError(WLAN_ERROR_SEVERITY__HIGH, WLAN_ERROR_MODULE__DEVICE, WLAN_ERROR_TYPE__REACHED_MAX_CLIENTS);
    }

    /* Transport deinit */
    ret = trnspt_Destroy(uDestroyClientId);
    if(OSI_OK != ret)
    {
        ASSERT_GENERAL(0);
        return ret;
    }

    ctrlCmdFw_DeleteEventThread();
    ctrlCmdFw_DeleteMsgQueue();


    ret = twIf_Destroy();
    if(OSI_OK != ret)
    {
        ASSERT_GENERAL(0);
        return ret;
    }
    osi_LockObjDelete(&driverLock);

    ret = osi_LockObjDelete(&extAppLockObj);
    if (ret != OSI_OK)
    {
        ASSERT_GENERAL(0);
        return ret;
    }


    return 0;

}

/******************************************************************************

    NAME:           ReadChipID

    PROTOTYPE:      init

    DESCRIPTION:    Read chip ID from FW chip

    CALLER:        InitHostDriver

    RETURNS:        NONE
******************************************************************************/
//TODO, ReadChipID , when it needs to be called
void ReadChipID()
{
#ifdef REMOVE_UNUSED_CODE
    uint32_t chip_id;

    SET_BOOT_PARTITION(aPartition);
    ioSetPartition();

    Read32();
   Report("chip id is 0x%x", chip_id);
#endif
}
/******************************************************************************

    NAME:           SetMacAddress

    PROTOTYPE:      init

    DESCRIPTION:    Set MAC address from fuse

    RETURNS:        NONE
******************************************************************************/
#if 0
//TODO, SetMacAddress , when it needs to be called

static void SetMacAddress(uint32_t mac1, uint32_t mac2)
{
    uint32_t oui_addr;
    uint32_t nic_addr;
    uint8_t *addr = g_fuse_mac_addr;

    oui_addr = ((mac2 & 0xffff) << 8) + ((mac1 & 0xff000000) >> 24);
    nic_addr = mac1 & 0xffffff;

    addr[0] = oui_addr >> 16;
    addr[1] = oui_addr >> 8;
    addr[2] = oui_addr;
    addr[3] = nic_addr >> 16;
    addr[4] = nic_addr >> 8;
    addr[5] = nic_addr;
}
#endif


void host_resetCounters(WlanRole_e roleType,dbg_cntr_trnspt_t *counters)
{
    uint32_t link,uNetIfId;

    memset(counters, 0 , sizeof(dbg_cntr_trnspt_t));

    if(WLAN_ROLE_STA == (uint32_t)roleType)
    {
        uNetIfId = (uint32_t)TIWDRV_NETIF_ID_STA;
    }
    else // AP
    {
        uNetIfId = (uint32_t)TIWDRV_NETIF_ID_SAP;
    }

    link = drv_getDriverLink(uNetIfId,NULL);

    udata_ResetGlobalRxStats();
    rxData_ResetLinkCounters(link);
    txCtrlParams_resetLinkCounters(link);


    counters->counters_timeLastReset_Ms = osi_GetTimeMS();
}
void host_getCounters(WlanRole_e roleType, dbg_cntr_trnspt_t *counters)
{
    uint32_t link,uNetIfId;
    ti_driver_ifData_t *pDrv;

    if(WLAN_ROLE_STA == (uint32_t)roleType)
    {
        uNetIfId = TIWDRV_NETIF_ID_STA;
    }
    else // AP
    {
        uNetIfId = TIWDRV_NETIF_ID_SAP;
    }

    counters->counters_timeLastUpdate_Ms = osi_GetTimeMS();

    link = drv_getDriverLink(uNetIfId, NULL);\

    udata_GetGlobalRxStats(counters);
    rxData_GetLinkCounters(link,counters);
    txCtrlParams_GetLinkCounters(link, counters);

    counters->rxRate = (uint32_t)udata_GetRxRate(link);
    counters->txRate =  (uint32_t)udata_GetTxRate(link);

}

/******************************************************************************

    NAME:           InitIniParamsHost

    PROTOTYPE:      init

    DESCRIPTION:    Read ini params value to initate globals on wlan_start 

    CALLER:         ctrlCmdFw_DownloadIniParams

    RETURNS:        NONE
******************************************************************************/
void InitIniParamsHost(cmd_ini_params_download_t *cmd)
{
    struct cc33xx_conf_file *conf = (struct cc33xx_conf_file *)(cmd->payload);

    // Set ps_scheme according to PowerSaveScheme
    uint8_t ps_scheme = conf->mac.ps_scheme; 
    AcPsMode_t acPsMode =
    {
        .wmeAcPsMode[AC_BE] = ps_scheme,
        .wmeAcPsMode[AC_BK] = ps_scheme,
        .wmeAcPsMode[AC_VI] = ps_scheme,
        .wmeAcPsMode[AC_VO] = ps_scheme
    };
    l2_cfg_Dynamic_set(L2_AC_PS_MODE, (uint8_t *)&acPsMode);

    // Update the l2CfgCommon_t parameters based on the INI file configuration
    if (gpL2CommonCfg != NULL)
    {
        // Set the he support value
        gpL2CommonCfg->heSupport = conf->mac.he_enable;

        gpL2CommonCfg->iniIs5GHzEnabled = conf->core.enable_5ghz;

        gpL2CommonCfg->iniMixedModeEnabled = conf->core.mixed_mode_support;
    }

    //SetAP max number of stations
    CME_PRINT_REPORT("\n\rMax num of STA for AP:%d\n\r",conf->mac.ApMaxNumStations );
    cfgSetApMaxNumStations(conf->mac.ApMaxNumStations);//this can be overwrite by ap role up
    cfgSetApMaxNumStationsFromConfIni(conf->mac.ApMaxNumStations);

    // CMD is freed in caller function
}
