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
/*-----------------------------------------------------------------------------
  FILENAME:       cme_role_activation.c

  DESCRIPTION:    Handle full role activation process for any role type.
                  requesters can be one of the following:
                  1. CME provisioning pre-configuration stage (AP activation request)
                  2. CME provisioning configuration to confirmation stage (STA activation request)
                  3. CME Init (activate user configuration roles)
                  4. CME new role settings (add or remove)
  ----------------------------------------------------------------------------- */

#include "cme_defs.h"
#include <public_types.h>
#include "cme_internal_api.h"
#include "cme_dispatcher_api.h"
#include "gtrace.h"
#include "wlan_if.h"
#include "osi_kernel.h"
#include "cme_defs.h"

#define CME_ACTIVATABLE_ROLES (BIT_x(ROLE_STA) | BIT_x(ROLE_AP) | BIT_x(ROLE_TRANSCEIVER) | BIT_x(ROLE_DEVICE)) // ethernet ...

#define CME_ACTIVATABLE_MASKED_ROLE_BITMAP(role_bitmap) (role_bitmap & CME_ACTIVATABLE_ROLES)

extern Cme_STA_states_e gCmeDeviceFlowState_ull;
extern int CmeDeviceFlowIsSMIdle();
extern void set_finish_wlan_sta_roleup();


typedef enum
{
    CME_ROLE_DEACTIVATED = 0,
    CME_ROLE_DEACTIVATING,
    CME_ROLE_ACTIVATING,
    CME_ROLE_ACTIVATED

} Cme_Role_states_e;

uint32_t cme_active_role_bitmap_ull = 0;
uint32_t cme_started_role_bitmap_ull = 0;
Cme_Role_states_e cme_current_ap_like_role_state_ull = CME_ROLE_DEACTIVATED;
Cme_Role_states_e cme_current_sta_like_role_state_ull = CME_ROLE_DEACTIVATED;
Cme_Role_states_e cme_current_device_role_state_ull = CME_ROLE_DEACTIVATED;
Cme_Role_states_e cme_current_transceiver_like_role_state_ull = CME_ROLE_DEACTIVATED;

extern signal_role_change_state_done_t g_signal_role_change_state_done;
//
// cme_role_switch_manager
//
// role switch sm manager
//
// input: user
//
// - manager is responsible for satisfying requested active roles compared to the currently active roles.
//  activation:
//   for each role, check if activation requested, and if not already activated start activation process
//   in case activation is not immediate, manage states of the activation untill fully activated.
//  de-activation:
//  for each role, check if de-activation requested, and if not already de-activated start de-activation process
//  in case de-activation is not immediate, manage states of the de-activation untill fully de-activated.
//
// return:
// 0  - role switch done - CME is idle
// 1  - role switch is still ongoing, manager waiting for activing/deactivting event
//
int cme_role_switch_manager(Cme_Users_e _deactivating_user, uint32_t deactivation_action_role_bitmap, uint8_t signal_event_when_done)
{
    HOOK(HOOK_IN_CME_ROLE_ACTIVATION);

    int rc = 0;
    uint32_t requested_active_role = CME_GetStartedRoleBitmap();
    uint32_t needed_activation_roles = CME_ACTIVATABLE_MASKED_ROLE_BITMAP(requested_active_role) & ~(CME_ACTIVATABLE_MASKED_ROLE_BITMAP(cme_active_role_bitmap_ull));
    uint32_t needed_deactivation_roles = ~(CME_ACTIVATABLE_MASKED_ROLE_BITMAP(requested_active_role)) & CME_ACTIVATABLE_MASKED_ROLE_BITMAP(cme_active_role_bitmap_ull);
    GTRACE(GRP_CME, "Requested roles 0x%x active roles 0x%x need activation 0x%x need deactivation 0x%x",
                         requested_active_role, cme_active_role_bitmap_ull,
                         needed_activation_roles, needed_deactivation_roles);

    g_signal_role_change_state_done.cme_signalWhenRoleStateChanged = 0;

    if (CME_ACTIVATABLE_MASKED_ROLE_BITMAP(cme_active_role_bitmap_ull) == CME_ACTIVATABLE_MASKED_ROLE_BITMAP(requested_active_role))
    {
        // release CME manager (during role switch)
        gCmeRoleSwitchActive = FALSE;
        if (signal_event_when_done)
        {
            g_signal_role_change_state_done.cme_signalWhenRoleStateChanged_status = CME_SIGNAL_ROLE_CHNGE_STATUS_OK;
            CME_PRINT_REPORT("\n\rCME_WlanSetMode : signal role is up nothing to active \r\n");

            if (OSI_OK != osi_SyncObjSignal(&gCmeCommandBlockingSyncObject))
            {
                ASSERT_GENERAL(0);
            }
            GTRACE(GRP_SL_DISPATCH, "cme_role_switch_manager : CME role switch acked back to host if");
        }
        return rc;
    }

    //
    // DE-ACTIVATION! ~requsted bitmap & active bitmap will give us bitmap of the needed de-activation role bitmap
    //
    // handle for each role seperatly
    if ((needed_deactivation_roles & BIT_x(ROLE_STA)) && (deactivation_action_role_bitmap & BIT_x(ROLE_STA)))
    {
        // STA DEACTIVATION
        if (cme_current_sta_like_role_state_ull == CME_ROLE_ACTIVATED)
        {
            if (cme_deactivate_sta_role(_deactivating_user) > 0) // ongoing deactivation - wait for completion before finishing deacitvation
            {
                rc = 1;
                return rc;
            }
        }
        else if (cme_current_sta_like_role_state_ull == CME_ROLE_DEACTIVATING)
        {
            cme_deactivate_sta_role_complete(_deactivating_user);
        }
        else
        {
            ASSERT_GENERAL(0);
        }
    }

    // handle for each role seperatly
    if ((needed_deactivation_roles & BIT_x(ROLE_AP)) && (deactivation_action_role_bitmap & BIT_x(ROLE_AP)))
    {
        // AP DEACTIVATION
        if (cme_current_ap_like_role_state_ull == CME_ROLE_ACTIVATED) // TODO: need to check CME_ROLE_DEACTIVATING as well?
        {
            cme_deactivate_ap_role();
        }
        else
        {
            ASSERT_GENERAL(0);
        }
    }

    // handle for each role seperatly
    if ((needed_deactivation_roles & BIT_x(ROLE_TRANSCEIVER)) && (deactivation_action_role_bitmap & BIT_x(ROLE_TRANSCEIVER)))
    {
        // AP DEACTIVATION
        if (cme_current_transceiver_like_role_state_ull == CME_ROLE_ACTIVATED) // TODO: need to check CME_ROLE_DEACTIVATING as well?
        {
            cme_deactivate_transceiver_role();
        }
        else
        {
            ASSERT_GENERAL(0);
        }
    }


    //handle for each role seperatly
    if ( (needed_deactivation_roles & BIT_x(ROLE_DEVICE)) && (deactivation_action_role_bitmap & BIT_x(ROLE_DEVICE)) )
    {
        if (cme_current_device_role_state_ull == CME_ROLE_ACTIVATED) // TODO: need to check CME_ROLE_DEACTIVATING as well?
        {
            cme_deactivate_device_role(_deactivating_user);
        }
        else
        {
            CME_PRINT_REPORT("CME: needed_deactivation_roles:0x%x deactivation_action_role_bitmap:0x%x", needed_deactivation_roles,deactivation_action_role_bitmap);
            ASSERT_GENERAL(0);
        }
    }
    // END of DE-ACTIVATION procedure

    //
    // ACTIVATION! requsted bitmap & ~active bitmap will give us bitmap of the needed activation role bitmap
    //
    if (needed_activation_roles & BIT_x(ROLE_STA))
    {
        ASSERT_GENERAL(cme_current_sta_like_role_state_ull == CME_ROLE_DEACTIVATED);
        cme_activate_sta_role();
    }

    if (needed_activation_roles & BIT_x(ROLE_AP))
    {
        ASSERT_GENERAL(cme_current_ap_like_role_state_ull == CME_ROLE_DEACTIVATED);

        if (signal_event_when_done)
        {
            // AP role up is up when the supplicant finish to configure the uAP
            // so the Sync object will be signaled only when the uAP is up
            g_signal_role_change_state_done.cme_signalWhenRoleStateChanged = signal_event_when_done;

            signal_event_when_done = FALSE;
        }

        cme_activate_ap_role();

        if (g_signal_role_change_state_done.cme_signalWhenRoleStateChanged_status != CME_SIGNAL_ROLE_CHNGE_STATUS_OK)
        {
            signal_event_when_done = TRUE;
            g_signal_role_change_state_done.cme_signalWhenRoleStateChanged = 0;
        }

    }

    if (needed_activation_roles & BIT_x(ROLE_DEVICE))
    {
        // AP role activation is done in one step (there is no "Activating")
        ASSERT_GENERAL(cme_current_device_role_state_ull == CME_ROLE_DEACTIVATED);
        cme_activate_device_role();
    }

#if 0  // remove P2P
    if ( needed_activation_roles & BIT_x(ROLE_P2P))
    {//role station
 //AP P2P not supported yet
        ASSERT_GENERAL(cme_current_sta_like_role_state_ull == CME_ROLE_DEACTIVATED);
        cme_activate_p2p_role();

    }
#endif
    if (needed_activation_roles & BIT_x(ROLE_TRANSCEIVER))
    {
        ASSERT_GENERAL(cme_current_transceiver_like_role_state_ull == CME_ROLE_DEACTIVATED);
        cme_activate_transceiver_role();
    }

    // END of ACTIVATION procedure

    // If got here, potentially all activations should have been already done
    if ((CME_ACTIVATABLE_MASKED_ROLE_BITMAP(cme_active_role_bitmap_ull) == CME_ACTIVATABLE_MASKED_ROLE_BITMAP(requested_active_role)) ||
        (g_signal_role_change_state_done.cme_signalWhenRoleStateChanged_status != CME_SIGNAL_ROLE_CHNGE_STATUS_OK))
    {
        // release CME manager (during role switch)
        gCmeRoleSwitchActive = FALSE;
        if (signal_event_when_done)
        {
            CME_PRINT_REPORT("\n\rCME_WlanSetMode: signal role status change done, status :%d\r\n",
                             g_signal_role_change_state_done.cme_signalWhenRoleStateChanged_status);
            if (needed_activation_roles & BIT_x(ROLE_STA))
            {
                set_finish_wlan_sta_roleup();
            }        
            if (OSI_OK != osi_SyncObjSignal(&gCmeCommandBlockingSyncObject))
            {
                ASSERT_GENERAL(0);
            }
            GTRACE(GRP_SL_DISPATCH, "cme_role_switch_manager: CME role switch acked back to host if");
        }
    }

    HOOK(HOOK_IN_CME_ROLE_ACTIVATION);

    return rc;
}

//
//  cme_is_activated_role_from_type
//  according to input role type- return if role type is initialized or not
//      STA role - bit is set if connected to AP
//      AP role - bit is set if role is started
//
uint8_t cme_is_activated_role_from_type(uint8_t role_type)
{
    HOOK(HOOK_IN_CME_ROLE_ACTIVATION);

    return (((cme_active_role_bitmap_ull & BIT_x(role_type)) != 0) ? 1 : 0);
}
//
//  cme_is_started_role_from_type
//  according to input role type- return if role type is started or not
//
uint8_t cme_is_started_role_from_type(uint8_t role_type)
{
    HOOK(HOOK_IN_CME_ROLE_ACTIVATION);

    return (((cme_started_role_bitmap_ull & BIT_x(role_type)) != 0) ? 1 : 0);
}

//
// cme_activate_sta_role
//
// role deactivtion request
//
// activation request, relevant in case role is in DEACTIVATED state
// send INIT request to station flow SM
//
int cme_activate_sta_role()
{
    HOOK(HOOK_IN_CME_ROLE_ACTIVATION);

    int rc = 0;

    GTRACE(GRP_CME,"CME: handle cme_activate_sta_role, cme_current_sta_like_role_state_ull=%d", cme_current_sta_like_role_state_ull);
    if (cme_current_sta_like_role_state_ull == CME_ROLE_ACTIVATED)
    {
        // already activated
        CME_PRINT_REPORT("\r\nSTA role already active");
        return rc;
    }

    // must not be in action (deactivating or activating in progress)
    ASSERT_GENERAL(cme_current_sta_like_role_state_ull == CME_ROLE_DEACTIVATED);

    cme_current_sta_like_role_state_ull = CME_ROLE_ACTIVATING;

    CME_PRINT_STATE_CHNGE_REPORT("\r\nCME: cme_activate_sta_role, change state to :CME_STA_INIT_EVENT !!");

    // call STA role supplicant init
    rc = CmeStationFlowSM(CME_STA_INIT_EVENT, CME_STA_NONE_USER);
    if ((rc == 0) && (g_signal_role_change_state_done.cme_signalWhenRoleStateChanged_status == CME_SIGNAL_ROLE_CHNGE_STATUS_OK))
    {
#ifdef CC33XX_CME_DEBUG
        ++gCmeDebugInfo.numSTAInterfaceUp;

        GTRACE(GRP_CME, "cme_activate_sta_role: successful activated STA role (num so far %d)", gCmeDebugInfo.numSTAInterfaceUp);
#else
        GTRACE(GRP_CME, "cme_activate_sta_role: successful activated STA role");
#endif

        // in station - activation is immediate - go to complete state

        cme_current_sta_like_role_state_ull = CME_ROLE_ACTIVATED;

        cme_active_role_bitmap_ull |= BIT_x(ROLE_STA);
    }
    else
    {
        GTRACE(GRP_CME, "cme_activate_sta_role: STA activation ERROR! invalid event state ");
        CME_PRINT_REPORT_ERROR("\r\ncme_activate_sta_role: STA activation ERROR! invalid event state ");
        rc = -1;
    }

    HOOK(HOOK_IN_CME_ROLE_ACTIVATION);

    return rc;
}


int cme_activate_device_role()
{
    HOOK(HOOK_IN_CME_ROLE_ACTIVATION);

    int rc = 0;

    GTRACE(GRP_CME,"CME: handle cme_activate_device_role, cme_current_device_role_state_ull=%d", cme_current_device_role_state_ull);
    if (cme_current_device_role_state_ull == CME_ROLE_ACTIVATED)
    {
        CME_PRINT_REPORT("\n\rDevice role already active");
        // already activated
        return rc;
    }

    // must not be in action (deactivating or activating in progress)
    ASSERT_GENERAL(cme_current_device_role_state_ull == CME_ROLE_DEACTIVATED);

    rc = CmeDeviceFlowSM(CME_DEVICE_INIT_EVENT, CME_STA_NONE_USER);
    if (rc == 0)
    {
        GTRACE(GRP_CME, "cme_activate_device_role: successful activated DEVICE role");
        // in station - activation is immediate - go to complete state

        cme_current_device_role_state_ull = CME_ROLE_ACTIVATED;
        cme_active_role_bitmap_ull |= BIT_x(ROLE_DEVICE);
    }
    else
    {
        GTRACE(GRP_CME, "cme_activate_device_role: DEVICE activation ERROR! invalid event state ");
        rc = -1;
        ASSERT_GENERAL(0);
    }



    return rc;
}

int cme_deactivate_device_role(Cme_Users_e _deactivating_user)
{
    int rc = 0;

    if (cme_current_device_role_state_ull == CME_ROLE_DEACTIVATED)
    {
        // already de-activated
        return rc;
    }

    // must not be in activation process (all other states are valid)
    ASSERT_GENERAL((cme_current_device_role_state_ull == CME_ROLE_ACTIVATED));

    cme_current_device_role_state_ull = CME_ROLE_DEACTIVATING;

    // Stop all DEVICE related process / API timers that may have been previusly started:

    //
    // in case DEVICE not in idle state - we should first stop scans / disconnect active connections
    //
    if (!CmeDeviceFlowIsSMIdle())
    {
        //
        // DEVICE is on ROC - or during ROC, stop ROC
        rc = CmeDeviceFlowSM(CME_DEVICE_CROC, _deactivating_user);
        return -1;

    }

    if (CmeDeviceFlowIsSMIdle())
    {
        // DEVICE flow SM should be in Idle now, send de-init request
        rc = CmeDeviceFlowSM(CME_DEVICE_DEINIT_EVENT, _deactivating_user);

        if (rc == 0)
        {
            cme_current_device_role_state_ull = CME_ROLE_DEACTIVATED;
            cme_active_role_bitmap_ull &= ~(BIT_x(ROLE_DEVICE));
            GTRACE(GRP_CME, "CME :cme_deactivate_device_role: successful DEVICE role de-activation request");
            CME_PRINT_REPORT("\r\nCME :cme_deactivate_device_role: successful DEVICE role de-activation request");
            rc = 0;
        }
        else
        {
            GTRACE(GRP_CME, "CME :cme_deactivate_device_role: DEVICE de-activation request ERROR! invalid event state ");
            CME_PRINT_REPORT("\r\nCME :cme_deactivate_device_role: DEVICE de-activation request ERROR! invalid event state ");

            rc = -1;
            ASSERT_GENERAL(0);
        }
    }
    else
    {
        rc = 1;
    }

    return rc;
}

//
// cme_set_unset_started_role
//
// set or unset role up / down indication bit in role bitmap
// set > 0 - set role type bit in bitmap
// set = 0 - unset role type bit in bitmap
//
void cme_set_unset_started_role(uint8_t set, uint8_t role_type)
{
    HOOK(HOOK_IN_CME_ROLE_ACTIVATION);

    if (set)
    {
        cme_started_role_bitmap_ull |= BIT_x(role_type);
    }
    else // unset
    {
        cme_started_role_bitmap_ull &= ~BIT_x(role_type);
    }
}

//
// cme_deactivate_sta_role
//
// role deactivtion request
//
// input: user
//
// - in case STA flow SM is idle, issue deinit supplicant request and once done
//   mark sta as de-activated
// - in case STA flow SM is connected, we should start disconnection sequence before deinit
//   first, make sure de-activing user is the user holding the station flow SM
//   second, issue disconnection request, and now we wait for WPA disconnected notificaiton in
//   station flow SM, that will bring us back to idle state
//   at this stage, this API should be called again to deinit the supplicant completely
//
// return:
// 0  - if role is successfully deactivated
// 1  - if role deactivation in progress
// -1 - if deactivation failed due to illegal states or user transitions
//
int cme_deactivate_sta_role(Cme_Users_e _deactivating_user)
{
    HOOK(HOOK_IN_CME_ROLE_ACTIVATION);

    int rc = 0;

    if (cme_current_sta_like_role_state_ull == CME_ROLE_DEACTIVATED)
    {
        // already de-activated
        return rc;
    }

    // must not be in activation process (all other states are valid)
    ASSERT_GENERAL((cme_current_sta_like_role_state_ull == CME_ROLE_ACTIVATED));

    cme_current_sta_like_role_state_ull = CME_ROLE_DEACTIVATING;

    // Stop all STA related process / API timers that may have been previusly started:

    //
    // in case STA not in idle state - we should first stop scans / disconnect active connections
    //
    if (!CmeStationFlowIsSMIdle())
    {
        //
        // STA is connected - should disconnect gracefully before de-activating
        //
    	CME_PRINT_STATE_CHNGE_REPORT("\n\rCME: cme_deactivate_sta_role, change state to :CME_STA_WLAN_DISCONNECT_REQ_EVENT !!");

        rc = CmeStationFlowSM(CME_STA_WLAN_DISCONNECT_REQ_EVENT, _deactivating_user);

        if (rc == 0)
        {
            GTRACE(GRP_CME, "cme_deactivate_sta_role: STA disconnect request sent ");
        }
        else
        {
            GTRACE(GRP_CME, "cme_deactivate_sta_role: STA disconnect request ERROR! invalid event state ");
            rc = -1;
            ASSERT_GENERAL(0);
            return rc;
        }
    }

    if (CmeStationFlowIsSMIdle())
    {
    	CME_PRINT_STATE_CHNGE_REPORT("\n\rCME: cme_deactivate_sta_role , change state to : CME_STA_DEINIT_EVENT !!");

        // STA flow SM should be in Idle now, send de-init request
        rc = CmeStationFlowSM(CME_STA_DEINIT_EVENT, _deactivating_user);

        if (rc == 0)
        {
            cme_current_sta_like_role_state_ull = CME_ROLE_DEACTIVATED;
            cme_active_role_bitmap_ull &= ~(BIT_x(ROLE_STA));
#ifdef CC33XX_CME_DEBUG
            ++gCmeDebugInfo.numSTAInterfaceDown;
            GTRACE(GRP_CME, "cme_deactivate_sta_role: successful STA role de-activation request (num so far %d)", gCmeDebugInfo.numSTAInterfaceDown);
#else
            GTRACE(GRP_CME, "cme_deactivate_sta_role: successful STA role de-activation request");
#endif
            rc = 0;
        }
        else
        {
            GTRACE(GRP_CME, "cme_deactivate_sta_role: STA de-activation request ERROR! invalid event state ");
            rc = -1;
            ASSERT_GENERAL(0);
        }
    }
    else
    {
        rc = 1;
    }

    HOOK(HOOK_IN_CME_ROLE_ACTIVATION);

    return rc;
}

//
// upon disconnection notifications check if role activation has any in-progress operations
//

int cme_deactivate_sta_role_complete(Cme_Users_e _deactivating_user)
{
    HOOK(HOOK_IN_CME_ROLE_ACTIVATION);

    int rc = 0;
    //    if (cme_current_sta_like_role_state_ull == CME_ROLE_DEACTIVATING)
    {
        // deactivation notifier must be called after state machine is in idle state
        ASSERT_GENERAL(CmeStationFlowIsSMIdle() != FALSE);

    	CME_PRINT_STATE_CHNGE_REPORT("\n\rCME: cme_deactivate_sta_role_complete , change state to : CME_STA_DEINIT_EVENT !!");

        rc = CmeStationFlowSM(CME_STA_DEINIT_EVENT, _deactivating_user);

        if (rc == 0)
        {
            cme_current_sta_like_role_state_ull = CME_ROLE_DEACTIVATED;
            cme_active_role_bitmap_ull &= ~(BIT_x(ROLE_STA));
#ifdef CC33XX_CME_DEBUG
            ++gCmeDebugInfo.numSTAInterfaceDown;
            GTRACE(GRP_CME, "cme_deactivate_sta_role (cme_sta_role_deactivation_disconnect_notifier): successful STA role de-activation (num so far %d)",
                   gCmeDebugInfo.numSTAInterfaceDown);
#else
            GTRACE(GRP_CME, "cme_deactivate_sta_role (cme_sta_role_deactivation_disconnect_notifier): successful STA role de-activation");

#endif
        }
        else
        {
            GTRACE(GRP_CME, "cme_deactivate_sta_role (cme_sta_role_deactivation_disconnect_notifier): STA de-activation ERROR! invalid event state ");
            rc = -1;
            ASSERT_GENERAL(0);
        }
    }

    HOOK(HOOK_IN_CME_ROLE_ACTIVATION);

    return rc;
}


//
// verify if sta like role is already active
//
int cme_is_sta_role_like_activated()
{
    HOOK(HOOK_IN_CME_ROLE_ACTIVATION);
    GTRACE(GRP_CME, "cme_current_sta_like_role_state_ull = %d", cme_current_sta_like_role_state_ull);
    return ((cme_current_sta_like_role_state_ull == CME_ROLE_ACTIVATED) ? 1 : 0);
}

//
// verify if ap like role is already active
//
int cme_is_ap_role_like_activated()
{
    HOOK(HOOK_IN_CME_ROLE_ACTIVATION);
    GTRACE(GRP_CME, "cme_current_ap_like_role_state_ull = %d", cme_current_ap_like_role_state_ull);
    return ((cme_current_ap_like_role_state_ull == CME_ROLE_ACTIVATED) ? 1 : 0);
}

//
// is p2p role configured (no role mix is allowed with p2p)
//
/* Removed P2P
 *
 */
//
// verify if device role is already active (enabled)
//
int cme_is_device_role_like_activated()
{
    HOOK(HOOK_IN_CME_ROLE_ACTIVATION);
    GTRACE(GRP_CME, "cme_current_device_role_state_ull = %d", cme_current_device_role_state_ull);
    return ((cme_current_device_role_state_ull == CME_ROLE_ACTIVATED) ? 1 : 0);
}

#if 0
int cme_is_p2p_role_configured()
{
    uint32_t host_configured_roles_bitmap = CME_GetStartedRoleBitmap();

    return ( ((host_configured_roles_bitmap & BIT_x(ROLE_P2P)) != 0) ? 1 : 0);

}
#endif

int cme_activate_ap_role()
{
    HOOK(HOOK_IN_CME_ROLE_ACTIVATION);

    int rc;
    cme_current_ap_like_role_state_ull = CME_ROLE_ACTIVATING;

    // ensure that while AP is started, the PHY is always awake.

    // Remove power
#if 0
    pwrmgt_addResourceRequirement ( PWRMGT_CLIENT_AP_ROLE, PWRMGT_RESOURCE_PHY_FULL_BIT ) ;
#endif

#ifdef CONFIG_AP
    // hostapd init
    rc = CmeAPFlowSM(CME_AP_INIT_EVENT);
    if ((rc == 0) &&
        (g_signal_role_change_state_done.cme_signalWhenRoleStateChanged_status == CME_SIGNAL_ROLE_CHNGE_STATUS_OK))
    {
        cme_current_ap_like_role_state_ull = CME_ROLE_ACTIVATED;
        cme_active_role_bitmap_ull |= BIT_x(ROLE_AP);
#ifdef CC33XX_CME_DEBUG
        ++gCmeDebugInfo.numAPInterfaceUp;
#endif

        cme_started_role_bitmap_ull |= BIT_x(ROLE_AP);

#ifdef CC33XX_CME_DEBUG
        GTRACE(GRP_CME, "cme_activate_ap_role: successful AP role activation request (num so far %d)", gCmeDebugInfo.numAPInterfaceUp);
#else
        GTRACE(GRP_CME, "cme_activate_ap_role: successful AP role activation request");
#endif

        if(g_signal_role_change_state_done.cme_signalWhenRoleStateChanged)
        {
            //let the application know that role up was done successfully
            CME_PRINT_REPORT("\n\rti_driver_set_ap: signal to application that uAP role is up\r\n");
            g_signal_role_change_state_done.cme_signalWhenRoleStateChanged_status = CME_SIGNAL_ROLE_CHNGE_STATUS_OK;
            if (OSI_OK != osi_SyncObjSignal(&gCmeCommandBlockingSyncObject))
            {
                ASSERT_GENERAL(0);
            }
            osi_uSleep(1000); // Temp WA !!!!!
        }
    }
    else
    {
        GTRACE(GRP_CME, "cme_activate_ap_role: AP activation ERROR!");
        CME_PRINT_REPORT_ERROR("\r\ncme_activate_ap_role: AP activation ERROR!");

        cme_current_ap_like_role_state_ull = CME_ROLE_DEACTIVATED;
        rc = -1;
    }
#endif // CONFIG_AP

    HOOK(HOOK_IN_CME_ROLE_ACTIVATION);

    return rc;
}

//
// cme_deactivate_ap_role
//
// role  AP deactivtion request
//
// input: user
//
// - AP deactivation request sent, waiting for AP stop role indication to finalize the de-activation request
//
// return:
// 0  - if role is deactivated request successfully sent
// -1 - if deactivation failed due to illegal states or user transitions
//

int cme_deactivate_ap_role()
{
    HOOK(HOOK_IN_CME_ROLE_ACTIVATION);

    int rc = 0;

    if (cme_current_ap_like_role_state_ull == CME_ROLE_DEACTIVATED)
    {
        // already de-activated
        return rc;
    }

    // must be in activation process (all other states are valid)
    ASSERT_GENERAL((cme_current_ap_like_role_state_ull == CME_ROLE_ACTIVATED));

    GTRACE(GRP_CME, "cme_deactivate_ap_role: starting deactivation");

    cme_current_ap_like_role_state_ull = CME_ROLE_DEACTIVATING;

    // set AP Role applications
    //  TODO - Need to implement ? - host
    // deInitAPApps(TRUE);

    // unset started role
    cme_started_role_bitmap_ull &= ~(BIT_x(ROLE_AP));

    //
    // AP deactivation complete -notify AP flow SM
    //
#ifdef CONFIG_AP
    rc = CmeAPFlowSM(CME_AP_STOP_ROLE_EVENT);

    if (rc == 0)
    {
        CME_PRINT_REPORT("\n\rcme_deactive_ap_role succeed");
        cme_current_ap_like_role_state_ull = CME_ROLE_DEACTIVATED;
        cme_active_role_bitmap_ull &= ~(BIT_x(ROLE_AP));
#ifdef CC33XX_CME_DEBUG
        ++gCmeDebugInfo.numAPInterfaceDown;
        GTRACE(GRP_CME, "cme_deactivate_ap_role: AP disconnect sent (num so far %d)", gCmeDebugInfo.numAPInterfaceDown);
#else
        GTRACE(GRP_CME, "cme_deactivate_ap_role: AP disconnect sent");
#endif
    }
    else
    {
        GTRACE(GRP_CME, "cme_deactivate_ap_role: AP disconnect  ERROR! invalid event state ");
        CME_PRINT_REPORT_ERROR("\n\rcme_deactivate_ap_role: AP disconnect  ERROR! invalid event state ");
        rc = -1;
        ASSERT_GENERAL(0);
    }
#endif
    // AP is stopped - therefore remove the request to stay awake
    // Remove power
#if 0
    pwrmgt_removeResourceRequirement ( PWRMGT_CLIENT_AP_ROLE, PWRMGT_RESOURCE_PHY_FULL_BIT ) ;
#endif

    HOOK(HOOK_IN_CME_ROLE_ACTIVATION);

    return rc;
}

//
// cme_activate_transceiver_role
//
// role Transceiver activation request
//
// activation request, relevant in case role is in DEACTIVATED state
int cme_activate_transceiver_role()
{
    HOOK(HOOK_IN_CME_ROLE_ACTIVATION);

    return 0;
#if 0
    HOOK(HOOK_IN_NWPM_GROUP_3_CME_0);
    int rc=0;
    if ((cme_current_transceiver_like_role_state_ull == CME_ROLE_ACTIVATED ) )
    {
        //already activated
        return rc;
    }

    //ensure that while Transceiver is started, the PHY is always awake. (use AP client to save client
    //as they are not working simultaneously)
    pwrmgt_addResourceRequirement ( PWRMGT_CLIENT_AP_ROLE, PWRMGT_RESOURCE_PHY_FULL_BIT ) ;
    //must not be in action (deactivating or activating in progress)
    ASSERT_GENERAL(cme_current_transceiver_like_role_state_ull == CME_ROLE_DEACTIVATED);

    cme_current_transceiver_like_role_state_ull = CME_ROLE_ACTIVATING;

    /*enable role*/
    Command_t cmd;
    RoleEnableParameters_t cmdParams;
    RoleType_e aRoleType = ROLE_TRANSCEIVER;

    cmd.cmdID = CMD_ROLE_ENABLE;
    cmd.pCmdParams = (void *)&cmdParams;

    GTRACE(GRP_CME, "Enable role ENUM(RoleType_e, %d) ", aRoleType);

    cmdParams.roleID = INVALID_ROLE_ID;
    cmdParams.roleType = aRoleType;
    // Clear MAC address, this indicates the roles module address needs to be allocated.
    // TODO - may be removed if we always allocate address for a new role.
    IRQ_UtilZeroMacAddress(cmdParams.macAddress);

    // Send the command and wait for response
    CME_SendCmd2WlanServices(&cmd);

    /************/
    /*start role*/
    RoleStartParameters_t cmdStartParams;
    cmd.cmdID = CMD_ROLE_START;
    cmd.pCmdParams = (void *)&cmdStartParams;

    cmdStartParams.roleID = cmdParams.roleID;
    /*Configuration start role - default parameters*/
    cmdStartParams.channelNumber = 6;
    cmdStartParams.band = RADIO_BAND_2_4GHZ;
    cmdStartParams.bandwidth = NLCP_CHAN_NO_HT;

    CME_SendCmd2WlanServices(&cmd);
    /************/
    GTRACE(GRP_CME,"cme_activate_transceiver_role: successful activated TRANSCEIVER role");

    cme_current_transceiver_like_role_state_ull = CME_ROLE_ACTIVATED;
    cme_active_role_bitmap_ull |= BIT_x(ROLE_TRANSCEIVER);

    return rc;
#endif
}

//
// cme_deactivate_ap_role
//
// role Transceiver deactivation request
//
// input: user
//
// - TRANSCEIVER deactivation request sent
//
// return:
// 0  - if role is deactivated request successfully sent
// -1 - if deactivation failed due to illegal states or user transitions
//
int cme_deactivate_transceiver_role()
{
    HOOK(HOOK_IN_CME_ROLE_ACTIVATION);

    return 0;
#if 0
    HOOK(HOOK_IN_NWPM_GROUP_3_CME_1);
    int rc = 0;
    Command_t cmd;
    if (cme_current_transceiver_like_role_state_ull == CME_ROLE_DEACTIVATED )
    {
        //already de-activated
        return rc;
    }

    //must be in activation process (all other states are valid)
    ASSERT_GENERAL((cme_current_transceiver_like_role_state_ull == CME_ROLE_ACTIVATED) );

    GTRACE(GRP_CME,"cme_deactivate_transceiver_role: starting deactivation");

    cme_current_transceiver_like_role_state_ull = CME_ROLE_DEACTIVATING;

    /*Stop role*/
    RoleStopParameters_t cmdStopParams;
    memset(&cmd, 0, sizeof(cmd));
    // Fill command parameters
    cmd.cmdID = CMD_ROLE_STOP;
    cmd.pCmdParams = (void *)&cmdStopParams;
    cmdStopParams.roleID = Roles_GetRoleIdFromRoleType(ROLE_TRANSCEIVER);

    GTRACE(GRP_CME,"cme_deactivate_transceiver_role: Stop role transceiver command role id = %d", cmdStopParams.roleID);
    // Wait blocking until role is stopped
    CME_SendCmd2WlanServices(&cmd);

    /*Disable role*/
    RoleDisableParameters_t cmdDisableParams;
    memset(&cmd, 0, sizeof(cmd));
    // Fill command parameters
    cmd.cmdID = CMD_ROLE_DISABLE;
    cmd.pCmdParams = (void *)&cmdDisableParams;
    cmdDisableParams.roleID = cmdStopParams.roleID;

    GTRACE(GRP_CME,"cme_deactivate_transceiver_role: starting deactivation role id = %d",cmdDisableParams.roleID);
    // Command blocks until WLAN services completes the disable operation
    CME_SendCmd2WlanServices(&cmd);

    //Unsent active role
    cme_active_role_bitmap_ull &= ~(BIT_x(ROLE_TRANSCEIVER));

    GTRACE(GRP_CME,"cme_deactivate_transceiver_role: successful TRANSCEIVER role de-activation request");

    cme_current_transceiver_like_role_state_ull = CME_ROLE_DEACTIVATED;

    /*Remove resource requirement - use AP client to save client as they are not working simultaneously */
    pwrmgt_removeResourceRequirement( PWRMGT_CLIENT_AP_ROLE, PWRMGT_RESOURCE_PHY_FULL_BIT ) ;

    return rc;
#endif
}
