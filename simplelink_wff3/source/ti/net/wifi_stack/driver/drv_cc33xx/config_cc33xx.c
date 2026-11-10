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
#include "includes.h"

#include "common.h"
#include "l2_cfg.h"
#include "wpa_supplicant/config.h"
#include "base64.h"
#include "cme_supplicant_api.h"

#define MAX_DOMAIN_NAME_LEN 128
void cfgBuildWmmParameters_sta (struct wpa_config *conf);

// Copy WPS parameters to specified buffer
// Set them to NULL if they aren't set
void cfgBuildWpsParameters(struct wpa_config *conf)
{
    wpsParameters_t *pWpsParameters;
	uint8_t deviceTypeZeros[WPS_DEV_TYPE_LEN] = {0};
	uint8_t uuidZeros[WPS_UUID_LEN] = {0};
	uint8_t osVersionZeros[WPS_OS_VERSION_LEN] = {0};

    // Make sure buffers are clean
	if (conf->device_name)
	{
		os_free(conf->device_name);
	}

	if (conf->manufacturer)
	{
	    os_free(conf->manufacturer);		
	}

	if (conf->model_name)
	{
	    os_free(conf->model_name);		
	}

	if (conf->model_number)
	{
	    os_free(conf->model_number);		
	}
	
	if (conf->serial_number)
	{
	    os_free(conf->serial_number);		
	}

	if (conf->config_methods)
	{
	    os_free(conf->config_methods);
	}

    conf->device_name = NULL;
    conf->manufacturer = NULL;
    conf->model_name = NULL;
    conf->model_number = NULL;
    conf->serial_number = NULL;
    conf->config_methods = NULL;

	// Allocate conf members to pointers using os_strdup()
	// Memory is set free in wpa_config_free() by WPA Supplicant
    if (cfgGetWpsParameters(&pWpsParameters))
    {
		if (pWpsParameters->device_name)
		{
			if (os_strlen(pWpsParameters->device_name) <= WPS_DEV_NAME_MAX_LEN)
			{
				conf->device_name = os_strdup(pWpsParameters->device_name);
			}
			else
			{
				wpa_printf(MSG_DEBUG, "WPS input device_name length %d exceeds max length %d, "
									  "setting failed",
									  os_strlen(pWpsParameters->device_name),
									  WPS_DEV_NAME_MAX_LEN);
			}
		}

		if (pWpsParameters->manufacturer)
		{
			if (os_strlen(pWpsParameters->manufacturer) <= WPS_MANUFACTURER_MAX_LEN)
			{
				conf->manufacturer = os_strdup(pWpsParameters->manufacturer);
			}
			else
			{
				wpa_printf(MSG_DEBUG, "WPS input manufacturer length %d exceeds max length %d, "
									  "setting failed",
									  os_strlen(pWpsParameters->manufacturer),
									  WPS_MANUFACTURER_MAX_LEN);
			}		
		}
		
		if (pWpsParameters->model_name)
		{
			if (os_strlen(pWpsParameters->model_name) <= WPS_MODEL_NAME_MAX_LEN)
			{
				conf->model_name = os_strdup(pWpsParameters->model_name);
			}
			else
			{
				wpa_printf(MSG_DEBUG, "WPS input model_name length %d exceeds max length %d, "
									  "setting failed",
									  os_strlen(pWpsParameters->model_name),
									  WPS_MODEL_NAME_MAX_LEN);
			}
		}
        
		if (pWpsParameters->model_number)
		{
			if (os_strlen(pWpsParameters->model_number) <= WPS_MODEL_NUMBER_MAX_LEN)
			{
				conf->model_number = os_strdup(pWpsParameters->model_number);
			}
			else
			{
				wpa_printf(MSG_DEBUG, "WPS input model_number length %d exceeds max length %d, "
									  "setting failed",
									  os_strlen(pWpsParameters->model_number),
									  WPS_MODEL_NUMBER_MAX_LEN);
			}
		}

		if (pWpsParameters->serial_number)
		{
			if (os_strlen(pWpsParameters->serial_number) <= WPS_SERIAL_NUMBER_MAX_LEN)
			{
				conf->serial_number = os_strdup(pWpsParameters->serial_number);
			}
			else
			{
				wpa_printf(MSG_DEBUG, "WPS input serial_number length %d exceeds max length %d, "
									  "setting failed",
									  os_strlen(pWpsParameters->serial_number),
									  WPS_SERIAL_NUMBER_MAX_LEN);
			}
		}

		if (pWpsParameters->config_methods)
		{
			conf->config_methods = os_strdup(pWpsParameters->config_methods);
		}

		if (0 != os_memcmp(pWpsParameters->device_type, deviceTypeZeros, WPS_DEV_TYPE_LEN))
		{
			os_memcpy(conf->device_type, pWpsParameters->device_type, WPS_DEV_TYPE_LEN);
		}
        
		if (0 != os_memcmp(pWpsParameters->uuid, uuidZeros, WPS_UUID_LEN))
		{
			os_memcpy(conf->uuid, pWpsParameters->uuid, WPS_UUID_LEN);
		}
        
		if (0 != os_memcmp(pWpsParameters->os_version, osVersionZeros, WPS_OS_VERSION_LEN))
		{
			os_memcpy(conf->os_version, pWpsParameters->os_version, WPS_OS_VERSION_LEN);
		}
    }
}

//P2P config params build
void cfgBuildP2pParameters(struct wpa_config *conf)
{
    const P2pParameters_t *pP2pParameters;

    if (cfgGetP2pParameters(&pP2pParameters))
    {
        conf->p2p_listen_reg_class = pP2pParameters->p2pListenRegClass;

        conf->p2p_listen_channel = pP2pParameters->p2pListenChannel;

        conf->p2p_oper_reg_class = pP2pParameters->p2pOperRegClass;

        conf->p2p_oper_channel = pP2pParameters->p2pOperChannel;

        conf->p2p_go_intent = pP2pParameters->p2pGoIntent;

    }
    conf->p2p_6ghz_disable = 1;

}


struct wpa_config * wpa_config_read(const char *name, struct wpa_config *cfgp)
{

	struct wpa_config *config;
	int use_ull_mem = 0;

	if (name == NULL)
		return NULL;

	if (0 == strcmp (name, NETIF_CONF_NAME(TIWLAN_DEV_NAME_STA)))
	{
	    use_ull_mem = 1;
	}

	if (cfgp)
	{
		config = cfgp;
	}
	else
	{
		config = wpa_config_alloc_empty(NULL, NULL);
	}

	if (config == NULL)
	{
		return NULL;
	}

	/* TODO: fill in configuration data */

	wpa_printf(MSG_DEBUG, "Loading cc33xx supplicant configuration - %s", name);

	// Common configuration for both STA and AP
	//Currently none...

	if (0 == strcmp (name, NETIF_CONF_NAME(TIWLAN_DEV_NAME_STA)))
	{
	    //STA specific configuration

	    // Process received credentials in WPS internally and pass them over to external program(s) (via the notify.c)
	    config->wps_cred_processing = 2;
	    // TODO: need to implement
#if 0
	    //Update WPS parameters - Needed only in station (TODO: validate this...)
	    cfgBuildWpsParameters_sta (config);
#endif

	    // Config default scheduled scan plans
	    os_free(config->sched_scan_plans);
	    config->sched_scan_plans = os_strdup(cfgGetStaDefaultSchedScanPlans());

	    if (TRUE == cfgIsStaPmfEnabled())
	    {
	        config->pmf = MGMT_FRAME_PROTECTION_OPTIONAL;
	    }
	    else
	    {
            config->pmf = NO_MGMT_FRAME_PROTECTION;
	    }
		
		cfgBuildWpsParameters(config);

        if (TRUE == cfgGetP2pDeviceEnable())
        {
    		config->p2p_disabled = 0;
        }
        else
        {
            config->p2p_disabled = 1;
        }
		
		// Add support for WPA3 RSNXE using hash-to-element (h2e) and HP loop.
		config->sae_pwe = 2;

		// For SAE PMK caching we must include PMKID in association requests
		config->sae_pmkid_in_assoc = 1;

        config->rsn_overriding = RSN_OVERRIDING_ENABLED;
	}

    //AP specific configuration
	else if (0 == strcmp (name, NETIF_CONF_NAME(TIWLAN_DEV_NAME_SAP)))
	{
	    // Enable WMM
	    // supplicant creates a default configuration when AP interface is added.
	    // By default WMM is disabled. So we may change it now, before activating
	    // wpa_supplicant_create_ap.

	    if (cfgIsApWmeEnabled())
	    {
			config->wmm_enable = TRUE;
	        wpa_printf(MSG_DEBUG, "AP config cc333xx: wmm is enabled. Setting AC parameters");

            //build AC parameters from l2cfg, will be set later on the AP beacon
            cfgBuildWmmParameters_sta(config);
	    }

	    // Set maximal number of STAs supported by cc33xx AP; this is derived from
	    // HW capabilities (number of links the device supports in AP mode).

	    config->max_num_sta = cfgGetApMaxNumStations();
	    config->p2p_intra_bss = 0;

	    wpa_printf(MSG_DEBUG, "AP: max number of stations - %d p2p_intra_bss:%d", config->max_num_sta,  config->p2p_intra_bss);

	    // Disassociate stations with low ack or that reached max TX retries
	    // TODO: config via l2cfg?
	    config->disassoc_low_ack = TRUE;

        config->pmf = cfgIsApPmfEnabled();

		config->p2p_no_group_iface = 1;

		if (TRUE == cfgGetWpsMode())
		{
			cfgBuildWpsParameters(config);
		}
	}
    else if (0 == strcmp (name, NETIF_CONF_NAME(TIWLAN_DEV_NAME_P2PDEV)))
    {
        //Device specific configuration
        cfgBuildP2pParameters(config);
        
        //Set device WPS related params
        cfgBuildWpsParameters(config);

    }
	else if (0 == strcmp (name, NETIF_CONF_NAME(TIWLAN_DEV_NAME_P2P_CL)))
	{
        //Device specific configuration
        cfgBuildP2pParameters(config);
        
        //Set device WPS related params
        cfgBuildWpsParameters(config);
	}
	else if (0 == strcmp (name, NETIF_CONF_NAME(TIWLAN_DEV_NAME_P2P_GO)))
	{
	    // Enable WMM
	    // supplicant creates a default configuration when AP interface is added.
	    // By default WMM is disabled. So we may change it now, before activating
	    // wpa_supplicant_create_ap.

	    if (cfgIsApWmeEnabled())
	    {
			config->wmm_enable = TRUE;
	        wpa_printf(MSG_DEBUG, "AP config cc333xx: wmm is enabled. Setting AC parameters");

            //build AC parameters from l2cfg, will be set later on the AP beacon
            cfgBuildWmmParameters_sta(config);
	    }

	    // Set maximal number of STAs supported by cc33xx AP; this is derived from
	    // HW capabilities (number of links the device supports in AP mode).

	    config->max_num_sta = cfgGetApMaxNumStations();

	    wpa_printf(MSG_DEBUG, "AP: max number of stations - %d", config->max_num_sta);

	    // Disassociate stations with low ack or that reached max TX retries
	    // TODO: config via l2cfg?
	    config->disassoc_low_ack = TRUE;

        config->pmf = cfgIsApPmfEnabled();

		if (TRUE == cfgGetWpsMode())
		{
			cfgBuildWpsParameters(config);
		}
	}
	else
	{
	    wpa_printf(MSG_ERROR, "Unknown supplicant configuration - %s", name);
	    ASSERT_GENERAL(FALSE); //For Debug.
	}

	return config;
}


int wpa_config_write(const char *name, struct wpa_config *config)
{
	struct wpa_ssid *ssid;
	struct wpa_config_blob *blob;

	wpa_printf(MSG_DEBUG, "Writing configuration file '%s'", name);

	/* TODO: write global config parameters */


	for (ssid = config->ssid; ssid; ssid = ssid->next) {
		/* TODO: write networks */
	}

	for (blob = config->blobs; blob; blob = blob->next) {
		/* TODO: write blobs */
	}

	return 0;
}

/******************************************************************************
  Function          : cfgBuildWmmParameters_sta

  Description       : setting AC parmeters for AP's beacon, based on the paramteres set in l2cfg.c
                      qosCfgSta_t gL2StaQosCfg.

  Input parameters  : wpa_config *conf                -   interface configuration parameter, will be filled with the relavent parameters.
******************************************************************************/
void cfgBuildWmmParameters_sta (struct wpa_config *conf)
{

    const AcCfg_t *acCfgparams;
    int i;

    if(cfgGetWmmParameters(&acCfgparams))
    {
        for (i=0; i < NUM_ACCESS_CATEGORIES; i++)
        {
            conf->wmm_ac_params[i].admission_control_mandatory = acCfgparams[i].acm;
            conf->wmm_ac_params[i].aifs = acCfgparams[i].aifsn;
            conf->wmm_ac_params[i].cwmax = acCfgparams[i].cwMax;
            conf->wmm_ac_params[i].cwmin = acCfgparams[i].cwMin;
            conf->wmm_ac_params[i].txop_limit = acCfgparams[i].txopLimit;

            wpa_printf(MSG_DEBUG, "cfgBuildWmmParameters_sta:wmm_ac_params[%d].txop_limit:%d",i,conf->wmm_ac_params[i].txop_limit);
        }
    }
}

