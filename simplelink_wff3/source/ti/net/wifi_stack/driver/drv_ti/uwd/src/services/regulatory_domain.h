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
/** \file regulatoryDomain.h
 *  \brief regulatoryDomain module internal header file
 *
 *  \see regulatoryDomain.c
 */

/***************************************************************************/
/*                                                                         */
/*    MODULE:   regulatory_domain.h                                        */
/*    PURPOSE:  regulatoryDomain module internal header file               */
/*                                                                         */
/***************************************************************************/


#ifndef __REGULATORY_DOMAIN_H__
#define __REGULATORY_DOMAIN_H__

#include "init_table_types.h"
#include "paramOut.h"
#include "802_11defs.h"
#include "regulatory_domain_api.h"

//#define REG_DOMAIN_LOG_REPORT
#ifdef REG_DOMAIN_LOG_REPORT
#define REG_DOMAIN_PRINT_REPORT Report
#define REG_DOMAIN_PRINT_REPORT_ERROR Report
#else
#define REG_DOMAIN_PRINT_REPORT(...)
#define REG_DOMAIN_PRINT_REPORT_ERROR Report
#endif


#define BG_24G_BAND_CHANNEL_HOPS    1
#define BG_24G_BAND_MIN_CHANNEL     1

#define A_5G_BAND_CHANNEL_HOPS      4

#define REG_DOMAIN_MAX_ROWS_IN_COUNTRY	7

#define REG_DOMAIN_MAX_CUSTOM_ENTRIES   7

extern uint8_t gCountryDomainStr[DOT11_COUNTRY_STRING_LEN];

/* Added for the 802.11k support  - Start*/
typedef enum
{
    REGULATORY_ZONE_USA = 0,
    REGULATORY_ZONE_JAPAN,
    REGULATORY_ZONE_RST, /* Europe + Rest of the world */
    REGULATORY_ZONE_NONE,
    REGULATORY_ZONE_MAX
} RegulatoryZone_e;

typedef struct
{
    uint8_t    MinClass;
    uint8_t    MaxClass;
    uint8_t    NumChan;
    uint8_t    TxPower;
    uint8_t/*RadioBand_e*/  band;
    uint16_t   Freq;
    uint8_t    Channel[REG_DOMAIN_MAX_CHAN_NUM];
}RegDomainChanPerClass_t;

typedef struct
{
    RegulatoryZone_e            CountryZone;
    RegDomainChanPerClass_t     DomainReg[REG_DOMAIN_MAX_REG_CLASS_NUM];
}RegDomainCalssesInfo_t;

/* Added for the 802.11k support  - End*/

typedef struct
{
	char             countryStr[DOT11_COUNTRY_STRING_LEN];
    RegDomainChan_t  domainReg[REG_DOMAIN_MAX_ROWS_IN_COUNTRY];
}RegDomainCountryInfo_t;

typedef struct 
{
    uint32_t chBitMap1;
    uint32_t chBitMap2;
} RegDomainChannelConfigBitField_t;

typedef struct
{
    /* Variables read from registry */
    /********************************/   
	Bool32                            	japanChannelsEnabled;

    RegulatoryZone_e                    countryZone;
    uint8_t                             countryDomain;

	RegDomainCountryInfo_t				*pRegDomainTable;
	uint32_t							uNumOfCountriesInTable;
    
    /* Internal reg domain variables */
    /*********************************/

	uint32_t							uDontOverride; /* Not in use currently, should be set to zero */
	Bool32								bFwUpdateRequired;
    dot11_COUNTRY_t                		country24;   /* Detected County IE for 2.4 Ghz */
    dot11_COUNTRY_t                		country5;    /* Detected County IE for 5 Ghz */
    channelCapability_t             	supportedChannels_band_5[A_5G_BAND_NUM_CHANNELS];
    channelCapability_t             	supportedChannels_band_2_4[NUM_OF_CHANNELS_24];

    /* set the size of the array to max of B_G & A, so that the array doesnt overflow. +3 for word alignment */
	uint8_t                        	    pDefaultChannels[A_5G_BAND_NUM_CHANNELS+3];
    
	RegDomainChannelConfigBitField_t	fwRegDomainChannelBitField;

    uint8_t                             is2_4GHzBandSupported;
    uint8_t                             is5GHzBandSupported;

} RegulatoryDomain_t;



#endif /* __REGULATORY_DOMAIN_H__*/

