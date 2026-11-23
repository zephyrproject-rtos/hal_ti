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
/** \file regulatory_domain_api.h
 *  \brief regulatoryDomain module interface header file
 *
 *  \see regulatory_domain.c & regulatory_domain.h
 */

/***************************************************************************/
/*                                                                         */
/*    MODULE:   regulatory_domain_api.h                                    */
/*    PURPOSE:  regulatoryDomain module interface header file              */
/*                                                                         */
/***************************************************************************/
#ifndef __REGULATORY_DOMAIN_API_H__
#define __REGULATORY_DOMAIN_API_H__


#include "802_11defs.h"
#include "paramOut.h"
#include "drv_ti_internal.h"

#include <public_types.h>//temporary for ERadioBand

#define CHANNEL_VALIDITY_TS_THRESHOLD   10000   /*10 seconds*/

#define TIW_REG_DOMAIN_DFS 0x00000001
#define TIW_REG_DOMAIN_HT40PLUS 0x00000002
#define TIW_REG_DOMAIN_HT40MINUS 0x00000004

typedef struct
{
    Bool32    channelValidityPassive; /*TI_TRUE-valid, TI_FALSE-invalid */
    Bool32    channelValidityActive; /*TI_TRUE-valid, TI_FALSE-invalid */
    uint32_t  uFlags;
    int8_t    uMaxTxPowerDomain;     /*
									  * Holds ONLY the default limitation (Application) 
									  * or according to 11d country code IE	
									  * Updated on init phase or upon receiving new country code IE				  
									  */ 
	uint32_t  timestamp;
} channelCapability_t;

typedef struct
{
	uint16_t 		channelNum;
	Bool32			channelValidity;
//	ERadioBand		band;
} channelValidity_t;

typedef struct
{
    uint8_t       minTxPower;
    uint8_t       maxTxPower;
} powerCapability_t;


int32_t regulatoryDomain_Init(WlanRole_e roleType, uint8_t *pCountryCode, uint8_t channel);
void    regulatoryDomain_SetChannels();
void 	regulatoryDomain_UpdateChannelValidity(uint8_t uChannel, Bool32 updateFw);
int32_t	regulatoryDomain_IsChannelSupported(uint8_t uChannel, Bool32 *isDfsChannel);
int32_t regulatoryDomain_GetCapability(RadioBand_e band, uint16_t channel, channelCapability_t *ChannelCapability);
void 	regulatoryDomain_GetCahnnelOnBand(RadioBand_e band,supportedChannels_t *supportedChannels);
void 	regulatoryDomain_GetPowerCapability(powerCapability_t *pPowerCapability,
										 	uint8_t channel);
int32_t regulatoryDomain_setSupportedChannelsAccording2CountryIe(dot11_COUNTRY_t *pCountry,
																 Bool32 band_2_4,
																 Bool32 updateFw);
int32_t regulatoryDomain_SetCountry(uint8_t *pCountryStr);
Bool_e  regulatoryDomain_getChMaxPower(uint16_t channel, int8_t *max_tx_power);
void 	regulatoryDomain_setFwMaxTxPower(int8_t maxTxPower);
void	regulatoryDomain_setRoleMaxTxPower(ti_driver_ifData_t *pDrv,
										   int8_t maxTxPower);
uint8_t regulatoryDomain_isBandSupported(RadioBand_e band);
void 	regulatoryDomain_handlePowerConstraint(ti_driver_ifData_t *pDrv,
     	                          			   uint16_t apCapabilities,
     	                          			   dot11_COUNTRY_t *countryIE,
     	                          			   dot11_POWER_CONSTRAINT_t *powerConstraintIE,
     	                          			   dot11_CELL_TP_t *ciscoDtpcIE);
int32_t regulatoryDomain_getCountryString(uint8_t *pCountryStr);
int32_t regulatoryDomain_SetCustomDomainEntry(WlanSetRegDomainCustomEntry_t *entryParams);
int32_t regulatoryDomain_GetCustomDomainEntry(WlanSetRegDomainCustomEntry_t *entryParams);
uint8_t regulatoryDomain_GetCustomDomainEntriesCount(void);

#endif /* __REGULATORY_DOMAIN_API_H__*/
