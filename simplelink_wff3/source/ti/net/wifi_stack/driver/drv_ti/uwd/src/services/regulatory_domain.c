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
/** \file regulatoryDomain.c
 *  \brief regulatoryDomain module interface
 *
 *  \see regulatoryDomain.h
 */

/************************************************************************************************/
/*  												                                            */
/*		MODULE:		regulatory_domain.c					                                        */
/*		PURPOSE:	regulatoryDomain module interface.			                                */
/*                  This module calculated the channel that should be scanned and that are      */
/*                   supported. Moreover, he set the transmit power level according to the      */
/*                   regulatory domain requirements and the supported channel.                  */
/*								 			                                                    */
/************************************************************************************************/
//#define __FILE_ID__  FILE_ID_3
#include "paramOut.h"
#include "regulatory_domain.h"
#include "regulatory_domain_api.h"

#include <public_types.h>
#include "gtrace.h"
#include "string.h"
#include "osi_kernel.h"
#include "802_11defs.h"
#include "80211_utils.h"
#include "control_cmd_fw.h"

#include "macro_utils.h"
#include "errors.h"

#define CHANNEL_VALIDITY_TS_THRESHOLD   10000 /* 10 sec */

#define WORLD_WIDE_ACTIVE_2_4_CHANNEL   11
#define WORLD_WIDE_2_4_CHANNEL_HT40_MIN 3
#define WORLD_WIDE_2_4_CHANNEL_HT40_MAX 7

#define FW_REG_DOMAIN_CHANNEL_BITMASK_2_4G		(0x3FFF)
#define FW_REG_DOMAIN_CHANNEL_LOW_BITMASK_5G	(0x3FFC0000)
#define FW_REG_DOMAIN_CHANNEL_HIGH_BITMASK_5G	(0x7FFFFFFF)

#define REG_DOMAIN_TIMEOUT_MSEC 5000 /* 5 sec*/

#define BASIC_RULES_COUNT 12
#define CUSTOM_RULES_COUNT 7

/* Custom entries starting from number 12 in "rom_gConfigChanPatternsTable" */
#define REG_DOMAIN_CUSTOM_ENTRY_BASE (BASIC_RULES_COUNT)


#define REG_DOMAIN_FCC_REGION		0
#define REG_DOMAIN_TELEC_REGION		1
#define REG_DOMAIN_WORLDWIDE_REGION	2
#define REG_DOMAIN_ETSI_REGION		3
#define REG_DOMAIN_CUSTOM_REGION	4

#define REG_DOMAIN_NUM_OF_REGIONS	5

typedef struct
{
    uint8_t  band;
	uint8_t  txPowerPerRegion[REG_DOMAIN_NUM_OF_REGIONS];
    uint8_t  dfsChannel;
    uint16_t minChannel;
    uint16_t maxChannel;
    uint8_t  numOfChannels;
    uint32_t chanBitmap;
} ConfigChanPattern_t;

typedef struct
{
    uint8_t chanAmount;
    uint8_t chanPatternsList[REG_DOMAIN_MAX_ROWS_IN_COUNTRY];
} ConfigGroupChanPatterns_t;

typedef struct
{
    uint8_t countryStr[REG_DOMAIN_COUNTRY_STR_LEN];
    uint8_t region;
} ConfigCountryCompressed_t;

ConfigChanPattern_t rom_gConfigChanPatternsTable[BASIC_RULES_COUNT + CUSTOM_RULES_COUNT] = {
   //Bnd Tx(US  JP  WW  EU  XZ) Dfs minCh MaxCh NumCh chanBitmap 		 Index Count   Bnd Tx   Dfs Num Channels:
    { 0,  { 30, 0 , 20, 20, 0}, 0,   1,    11,    11, 0x000007ff }, //   0,    20 	 { 0,  20,  0,  11, 1,   2,   3,   4,   5,   6,   7,   8,   9,   10,  11,  0,  0,  0,  0,   },
    { 0,  { 0 , 20, 20, 20, 0}, 1,   12,   13,    2,  0x00001800 }, //   1,     1 	 { 0,  20,  1,  2,  12,  13,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  0,  0,  0,   },
    { 0,  { 0 , 20, 20,  0, 0}, 1,   14,   14,    1,  0x00002000 }, //   2,     1 	 { 0,  20,  1,  1,  14,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  0,  0,  0,   },
    { 1,  { 23, 20, 20, 23, 0}, 1,   36,   48,    4,  0x0000000f }, //   3,     1 	 { 1,  20,  1,  4,  36,  40,  44,  48,  0,   0,   0,   0,   0,   0,   0,   0,  0,  0,  0,   },
    { 1,  { 23, 20, 20, 23, 0}, 1,   52,   64,    4,  0x000000f0 }, //   4,   160 	 { 1,  20,  1,  4,  52,  56,  60,  64,  0,   0,   0,   0,   0,   0,   0,   0,  0,  0,  0,   },
    { 1,  { 23, 23, 20, 30, 0}, 1,   100,  144,   12, 0x000fff00 }, //   5,   127 	 { 1,  20,  1,  11, 100, 104, 108, 112, 116, 120, 124, 128, 132, 136, 140, 144,0,  0,  0,   },
    { 1,  { 30, 23, 20,  0, 0}, 1,   149,  161,   4,  0x00f00000 }, //   6,     1 	 { 1,  20,  1,  4,  149, 153, 157, 161, 0,   0,   0,   0,   0,   0,   0,   0,  0,  0,  0,   },
    { 0,  { 0 , 20, 20, 20, 0}, 0,   1,    13,    13, 0x00001fff }, //   7,   156 	 { 0,  20,  0,  13, 1,   2,   3,   4,   5,   6,   7,   8,   9,   10,  11,  12, 13, 0,  0,   },
    { 1,  { 23, 20, 20, 23, 0}, 0,   36,   48,    4,  0x0000000f }, //   8,   160 	 { 1,  20,  0,  4,  36,  40,  44,  48,  0,   0,   0,   0,   0,   0,   0,   0,  0,  0,  0,   },
    { 1,  { 30, 0 , 20,  0, 0}, 0,   149,  161,   4,  0x00f00000 }, //   9,    85 	 { 1,  20,  0,  4,  149, 153, 157, 161, 0,   0,   0,   0,   0,   0,   0,   0,  0,  0,  0,   },
    { 1,  { 30, 20, 20,  0, 0}, 0,   165,  165,   1,  0x01000000 }, //  10,     1 	 { 1,  20,  0,  1,  165, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  0,  0,  0,   },
    { 2,  { 23, 20, 20,  0, 0}, 0,   184,  196,   4,  0x3c000000 }, //  11,     1 	 { 2,  20,  0,  4,  184, 188, 192, 196, 0,   0,   0,   0,   0,   0,   0,   0,  0,  0,  0,   },
	{ 0,  { 0 , 0 , 0 ,  0, 0}, 0,   0,    0,     0,  0x00000000 }, //  12,     0    { ************************************** CUSTOM *****************************************  },
    { 0,  { 0 , 0 , 0 ,  0, 0}, 0,   0,    0,     0,  0x00000000 }, //  13,     0    { ************************************** CUSTOM *****************************************  },
    { 0,  { 0 , 0 , 0 ,  0, 0}, 0,   0,    0,     0,  0x00000000 }, //  14,     0    { ************************************** CUSTOM *****************************************  },
    { 0,  { 0 , 0 , 0 ,  0, 0}, 0,   0,    0,     0,  0x00000000 }, //  15,     0    { ************************************** CUSTOM *****************************************  },
    { 0,  { 0 , 0 , 0 ,  0, 0}, 0,   0,    0,     0,  0x00000000 }, //  16,     0    { ************************************** CUSTOM *****************************************  },
    { 0,  { 0 , 0 , 0 ,  0, 0}, 0,   0,    0,     0,  0x00000000 }, //  17,     0    { ************************************** CUSTOM *****************************************  },
    { 0,  { 0 , 0 , 0 ,  0, 0}, 0,   0,    0,     0,  0x00000000 }, //  18,     0    { ************************************** CUSTOM *****************************************  },
};

const ConfigGroupChanPatterns_t rom_gConfigGroupChanPatternsTable[] = {
    /*    Index Count     Num of channels 	  Channels: */
    /*    0,    6 */    { 6, 				  {  0,  8,  4,  5,  9,  10 } },
    /*    1,    6 */    { 4, 				  {  7,  8,  4,  5 } },
    /*    2,    6 */    { 6, 				  {  0,  8,  4,  5,  6,  10 } },
	/*    3,    4 */    { 6, 				  {  7,  8,  4,  5,  9,  10 } },
	/*    4,    7 */    { CUSTOM_RULES_COUNT, {  12, 13, 14, 15, 16, 17, 18} },
};

ConfigCountryCompressed_t rom_gConfigCountryCompressedTable[REG_DOMAIN_NUM_OF_REGIONS] = {
      /*       		Country   Rgn: */
    { /* US */ 		'U', 'S', REG_DOMAIN_FCC_REGION }, 		 // FCC - min of FCC/IC/Taiwan
    { /* JP */ 		'J', 'P', REG_DOMAIN_TELEC_REGION }, 	 // ROW (rest of the world) - Min of JP/EU
    { /* WW_SAFE */ '0', '0', REG_DOMAIN_WORLDWIDE_REGION }, // WWS (worldwide safe) - Min of FCC&ROW
	{ /* EU */ 		'E', 'U', REG_DOMAIN_ETSI_REGION },		 // EU
	{ /* XZ */ 		'X', 'Z', REG_DOMAIN_CUSTOM_REGION }, 	 // XZ - Custom regulatory domain, set by API
};

int                        gNumCompressedCountries       = sizeof(rom_gConfigCountryCompressedTable)/sizeof(ConfigCountryCompressed_t);
ConfigChanPattern_t       *gConfigChanPatternsTable      = (ConfigChanPattern_t *)rom_gConfigChanPatternsTable;
ConfigGroupChanPatterns_t *gConfigGroupChanPatternsTable = (ConfigGroupChanPatterns_t *)rom_gConfigGroupChanPatternsTable;
ConfigCountryCompressed_t *gConfigCountryCompressedTable = (ConfigCountryCompressed_t *)rom_gConfigCountryCompressedTable;

uint8_t gCountryDomainStr[DOT11_COUNTRY_STRING_LEN] = {0};

const char rom_dot11g_channels[NUM_OF_CHANNELS_24] = { 1, 2, 3, 4, 5, 6,
													   7, 8, 9, 10, 11, 12, 13, 14 };
const char rom_dot11a_channels[A_BAND_CHANNEL_COUNT] = { 36, 40, 44, 48, 52, 56, 60, 64, 100, 104, 108,
														 112, 116, 120, 124, 128, 132, 136, 140, 144, 149,
														 153, 157, 161, 165, 169 }; //, 184, 188, 192, 196, 254, 255 };


const uint8_t DefaultGBandChannels[NUM_OF_CHANNELS_24] = {1,1,1,1,1,1,1,1,1,1,1,1,1,0};//removed ch14 not supported
const uint8_t DefaultABandChannels[A_5G_BAND_NUM_CHANNELS] = {0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,
	0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; // channel 144,165 are now supported
const uint16_t JapanABandChannels[] = {34, 38, 42, 46, 0};
const uint8_t p2pSocialChannels[] = { 1, 6, 11 };

uint8_t gCustomRegDomainEntriesCount = 0;

//
///*************************** Static Table for Regulatory Class **********************/
//
// This table is for fast roaming which is not supported and therefore no need to enable it
//
//RegDomainCalssesInfo_t RegClassTbl[REGULATORY_ZONE_MAX] = {
//                                  {REGULATORY_ZONE_USA, /* Country*/
//                                  {{1,1,4,30,BAND_TYPE_5_GHZ,5000,{36,40,44,48,0,0,0,0,0,0,0,0,0,0,0}}, /* min class, max class, num of channel,to power, base freq, channel list*/
//                                  {2,2,4,23,BAND_TYPE_5_GHZ,5000,{52,56,60,64,0,0,0,0,0,0,0,0,0,0,0}},
//                                  {3,3,4,29,BAND_TYPE_5_GHZ,5000,{149,153,157,161,0,0,0,0,0,0,0,0,0,0,0}},
//                                  {4,4,11,23,BAND_TYPE_5_GHZ,5000,{100,104,108,112,116,120,132,136,140,0,0,0,0,0,0}},
//                                  {5,5,5,30,BAND_TYPE_5_GHZ,5000,{149,153,157,161,165,0,0,0,0,0,0,0,0,0,0}},
//                                  {10,10,2,20,BAND_TYPE_4_9GHZ,4850,{20,25,0,0,0,0,0,0,0,0,0,0,0,0,0}},
//                                  {11,11,2,33,BAND_TYPE_4_9GHZ,4850,{20,25,0,0,0,0,0,0,0,0,0,0,0,0,0}},
//                                  {12,12,11,30,BAND_TYPE_2_4GHZ,2407,{1,2,3,4,5,6,7,8,9,10,11,0,0,0,0}},
//                                  {0,0,0,0,BAND_TYPE_NONE,0,{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
//                                  {0,0,0,0,BAND_TYPE_NONE,0,{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}}}},
//                                  {REGULATORY_ZONE_JAPAN,
//                                  {{1,1,4,13,BAND_TYPE_5_GHZ,5000,{34,38,42,46,0,0,0,0,0,0,0,0,0,0,0}},
//                                  {2,6,3,13,BAND_TYPE_5_GHZ,5000,{8,12,16,0,0,0,0,0,0,0,0,0,0,0,0}},
//                                  {7,11,4,13,BAND_TYPE_4_9GHZ,4000,{184,188,192,196,0,0,0,0,0,0,0,0,0,0,0}},
//                                  {30,30,13,13,BAND_TYPE_2_4GHZ,2407,{1,2,3,4,5,6,7,8,9,10,11,12,13,0,0}},
//                                  {31,31,1,13,BAND_TYPE_2_4GHZ,2414,{14,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
//                                  {32,32,4,13,BAND_TYPE_5_GHZ,5000,{52,56,60,64,0,0,0,0,0,0,0,0,0,0,0}},
//                                  {0,0,0,0,BAND_TYPE_NONE,0,{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
//                                  {0,0,0,0,BAND_TYPE_NONE,0,{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
//                                  {0,0,0,0,BAND_TYPE_NONE,0,{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
//                                  {0,0,0,0,BAND_TYPE_NONE,0,{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}}}},
//                                  {REGULATORY_ZONE_RST, /* Europe + Rest of the world */
//                                  {{1,1,4,23,BAND_TYPE_5_GHZ,5000,{36,40,44,48,0,0,0,0,0,0,0,0,0,0,0}},
//                                  {2,2,4,23,BAND_TYPE_5_GHZ,5000,{52,56,60,64,0,0,0,0,0,0,0,0,0,0,0}},
//                                  {3,3,11,30,BAND_TYPE_5_GHZ,5000,{100,104,108,112,116,120,124,128,132,136,140,0,0,0,0}},
//                                  {4,4,13,20,BAND_TYPE_2_4GHZ,2407,{1,2,3,4,5,6,7,8,9,10,11,12,13,0,0}},
//                                  {0,0,0,0,BAND_TYPE_NONE,0,{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
//                                  {0,0,0,0,BAND_TYPE_NONE,0,{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
//                                  {0,0,0,0,BAND_TYPE_NONE,0,{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
//                                  {0,0,0,0,BAND_TYPE_NONE,0,{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
//                                  {0,0,0,0,BAND_TYPE_NONE,0,{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
//                                  {0,0,0,0,BAND_TYPE_NONE,0,{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}}}},
//                                  {REGULATORY_ZONE_NONE,
//                                  {{100,100,11,13,BAND_TYPE_2_4GHZ,2407,{1,2,3,4,5,6,7,8,9,10,11,12,13,0,0}},
//                                  {0,0,0,0,BAND_TYPE_NONE,0,{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
//                                  {0,0,0,0,BAND_TYPE_NONE,0,{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
//                                  {0,0,0,0,BAND_TYPE_NONE,0,{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
//                                  {0,0,0,0,BAND_TYPE_NONE,0,{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
//                                  {0,0,0,0,BAND_TYPE_NONE,0,{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
//                                  {0,0,0,0,BAND_TYPE_NONE,0,{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
//                                  {0,0,0,0,BAND_TYPE_NONE,0,{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
//                                  {0,0,0,0,BAND_TYPE_NONE,0,{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
//                                  {0,0,0,0,BAND_TYPE_NONE,0,{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}}}}
//                                  };
//


RegulatoryDomain_t RegulatoryDomain;


///********************************************************************************/
///*						Internal functions prototypes.							*/
///********************************************************************************/
static void setWorldWideDomainSupportedChannels();
static void sendRegDomainCmdToFw();
static void verifyDfsChannelValidity(channelCapability_t *pSupportedChannels, uint8_t channelIndex);
static int32_t getCountryIdInTable(uint8_t *pCountryStr, uint32_t *pCountryID);
static Bool32 isDfsChannelInCountry(uint32_t cntrId, uint32_t uChannel);
static Bool32 setChannelAsFwBitmap(uint16_t channelNumber, Bool32 band_2_4, Bool32 shouldSet);
static int8_t getChannelIndexTranslation(uint16_t chNumber, Bool32 band_2_4);
static int8_t setSupportedChannelsAccording2Domain(void);
static uint8_t isCountryCodeValid(uint8_t *pCountryStr);


///********************************************************************************/
///*						Interface functions Implementation.					  */
///********************************************************************************/

///************************************************************************
// *                     areSocialChannelsSupported						  *
// ************************************************************************
//DESCRIPTION:  Check if social channels for P2P are currently supported
//				by reg domain.
//
//INPUT:
//
//OUTPUT:
//
//RETURN:       TRUE if supported, FALSE otherwise
//************************************************************************/
Bool_e areSocialChannelsSupported()
{
	uint8_t i = 0;

	for (i = 0; i < sizeof(p2pSocialChannels); i++)
	{
		if (!regulatoryDomain_IsChannelSupported(p2pSocialChannels[i], NULL))
		{
			return FALSE;
		}
	}

	return TRUE;
}

///************************************************************************
// *                        regulatoryDomain_Init						  *
// ************************************************************************
//DESCRIPTION:  Module init function.
//
//INPUT:        pCountryCode - Role country code
//				roleType 	 - Role type
//				channel 	 - Necessary only for AP/DEVICE role
//							   (use 0 for STA)
//
//OUTPUT:
//
//RETURN:       void
//************************************************************************/
int32_t regulatoryDomain_Init(WlanRole_e roleType, uint8_t *pCountryCode, uint8_t channel)
{
	int32_t ret = 0;
	Bool32 isDfsChannel = FALSE;

    HOOK(HOOK_IN_REGULATORY_DOMAIN);

	os_memset(&RegulatoryDomain, 0x00, sizeof(RegulatoryDomain_t));

	if (pCountryCode[0] == '\0')
	{
		CME_PRINT_REPORT_ERROR("\r\nregulatoryDomain_Init: Input country code "
							   "is NULL, using WW country code (00)");
		pCountryCode[0] = '0';
		pCountryCode[1] = '0';
		pCountryCode[2] = 0x20;
	}

	ret = regulatoryDomain_SetCountry(pCountryCode);
	if (ret < 0)
	{
		return ret;
	}

	regulatoryDomain_SetChannels();

	if (ROLE_IS_TYPE_AP_BASED(roleType))
	{
		ret = regulatoryDomain_IsChannelSupported(channel, &isDfsChannel);
		if (ret == 0)
		{
			ret = WlanError(WLAN_ERROR_SEVERITY__LOW,
							WLAN_ERROR_MODULE__COMMANDS,
							WLAN_ERROR_TYPE__INVALID_PARAM_CHANNEL);
			return ret;
		}

		if (isDfsChannel)
		{
			CME_PRINT_REPORT_ERROR("\r\nAP in DFS channels isn't supported");
			ret = WlanError(WLAN_ERROR_SEVERITY__LOW,
							WLAN_ERROR_MODULE__COMMANDS,
							WLAN_ERROR_TYPE__INVALID_PARAM_CHANNEL);
			return ret;
		}
	}
	else if (ROLE_IS_TYPE_DEVICE(roleType))
	{
		/* Device role must support social channels */
		if (!areSocialChannelsSupported())
		{
			CME_PRINT_REPORT_ERROR("\r\nP2P device role up failed: "
								   "device must support all social "
								   "channels, regulatory-wise");
			return WlanError(WLAN_ERROR_SEVERITY__LOW,
							 WLAN_ERROR_MODULE__COMMANDS,
							 WLAN_ERROR_TYPE__INVALID_PARAM_CHANNEL);
		}

		/* channel 0 for P2P operating channel means auto-selection by 
		 * supplicant. The channels that supplicant is aware of that we
		 * support are set by the current reg domain.
		 */
		if (channel != 0)
		{
			ret = regulatoryDomain_IsChannelSupported(channel, &isDfsChannel);
			if (ret == 0)
			{
				CME_PRINT_REPORT_ERROR("\r\nP2P device role up failed: "
									   "operating channel not "
									   "supported");
				return WlanError(WLAN_ERROR_SEVERITY__LOW,
								 WLAN_ERROR_MODULE__COMMANDS,
								 WLAN_ERROR_TYPE__INVALID_PARAM_CHANNEL);
			}
	
			if (isDfsChannel)
			{
				CME_PRINT_REPORT_ERROR("\r\nP2P device role up failed: "
									   "Operating channel must "
									   "not be a DFS channel");
				return WlanError(WLAN_ERROR_SEVERITY__LOW,
								 WLAN_ERROR_MODULE__COMMANDS,
								 WLAN_ERROR_TYPE__INVALID_PARAM_CHANNEL);
			}
		}
	}

	return ret;
}


///************************************************************************
// *                        regulatoryDomain_SetChannels				  *
// ************************************************************************
//DESCRIPTION:  regulatoryDomain module configuration function,
//  			called by the config mgr in configuration phase
//				performs the following:
//				-	Reset & initializes local variables
//				-	Init the handles to be used by the module
//
//INPUT:     
//
//OUTPUT:
//
//RETURN:     OK on success,-1 otherwise
//
//************************************************************************/
void regulatoryDomain_SetChannels()
{
    RegulatoryDomain_t *pRegulatoryDomain = &RegulatoryDomain;

    HOOK(HOOK_IN_REGULATORY_DOMAIN);

	setSupportedChannelsAccording2Domain();

	pRegulatoryDomain->uNumOfCountriesInTable = REG_DOMAIN_NUM_OF_REGIONS;
}

void regulatoryDomain_UpdateChannelValidity(uint8_t uChannel, Bool32 updateFw)
{
	uint8_t	             channelIndex;
	channelCapability_t *pSupportedChannels;
	RegulatoryDomain_t  *pRegulatoryDomain = &RegulatoryDomain;

    HOOK(HOOK_IN_REGULATORY_DOMAIN);

	if (pRegulatoryDomain==NULL)
		return;

    if (uChannel>=A_5G_BAND_MIN_CHANNEL && uChannel<A_5G_BAND_MAX_CHANNEL)
	{
		channelIndex = (uChannel-A_5G_BAND_MIN_CHANNEL);
		pSupportedChannels = pRegulatoryDomain->supportedChannels_band_5;
	}
	else
		return;

    /* Update validity only if channel is a DFS channel in the current country*/
	if (pSupportedChannels[channelIndex].uFlags & TIW_REG_DOMAIN_DFS)
	{
		pSupportedChannels[channelIndex].timestamp = osi_GetTimeMS();//   os_timeStampMs(pRegulatoryDomain->hOs);
        pSupportedChannels[channelIndex].channelValidityActive = TRUE;

        if (setChannelAsFwBitmap(uChannel, FALSE, TRUE))
		{
			if (updateFw)
				sendRegDomainCmdToFw();
			else
				pRegulatoryDomain->bFwUpdateRequired = TRUE;
		}
	}
}

void regulatoryDomain_GetPowerCapability(powerCapability_t *pPowerCapability,
										 uint8_t channel)
{
    int8_t maxTxPower = 0;

	pPowerCapability->minTxPower = WLAN_MIN_TX_POWER_DBM;

	if (TRUE == regulatoryDomain_getChMaxPower(channel, &maxTxPower))
	{
		pPowerCapability->maxTxPower = maxTxPower;
	}
	else
	{
		pPowerCapability->maxTxPower = WLAN_MAX_TX_POWER_DBM;
	}
}

/***********************************************************************
 *                 regulatoryDomain_isChannelSupprted		   		   *
 ***********************************************************************
DESCRIPTION: The function checks if the input channel is supported.

INPUT:       isDfsChannel		-	Optional. Get DFS info.
			 channel			-	Channel number.

OUTPUT:

RETURN:      Value higher than zero if channel is supported, zero
			 if not supported, negative value on error.

************************************************************************/
int32_t regulatoryDomain_IsChannelSupported(uint8_t channel, Bool32 *isDfsChannel)
{
	uint8_t	            channelIndex = 0;
	channelCapability_t *pSupportedChannels;
    RegulatoryDomain_t  *pRegulatoryDomain = &RegulatoryDomain;
	uint8_t				arrayLen = 0;

    HOOK(HOOK_IN_REGULATORY_DOMAIN);

	if (pRegulatoryDomain == NULL)
	{
		GTRACE(GRP_GENERAL_ERROR, "ERROR: Regulatory Domain DB is NULL");
		return -1;
	}

    if ((channel < BG_24G_BAND_MIN_CHANNEL) ||
		(channel > A_5G_BAND_MAX_CHANNEL))
	{
		GTRACE(GRP_GENERAL_ERROR, "ERROR: channel #%u is invalid", channel);
		return -1;
	}

	if (channel >= A_5G_BAND_MIN_CHANNEL)
	{
		channelIndex = (channel - A_5G_BAND_MIN_CHANNEL);
		pSupportedChannels = pRegulatoryDomain->supportedChannels_band_5;
		arrayLen = sizeof(pRegulatoryDomain->supportedChannels_band_5) /
					sizeof(pRegulatoryDomain->supportedChannels_band_5[0]);
	}
	else if (channel <= NUM_OF_CHANNELS_24)
	{
		channelIndex = (channel - BG_24G_BAND_MIN_CHANNEL);
		pSupportedChannels = pRegulatoryDomain->supportedChannels_band_2_4;
		arrayLen = sizeof(pRegulatoryDomain->supportedChannels_band_2_4) /
					sizeof(pRegulatoryDomain->supportedChannels_band_2_4[0]);
	}
	else
	{
		GTRACE(GRP_GENERAL_ERROR, "ERROR: only 2.4 and 5 GHz "
								  "bands are supported", channel);
		return -1;
	}

	if (channelIndex >= arrayLen)
	{
		GTRACE(GRP_GENERAL_ERROR,
			   "ERROR: regulatoryDomain_isChannelSupprted(): "
			   "invalid channel #%u", channel);
		return -1;
	}

	if (isDfsChannel != NULL)
	{
		if (pSupportedChannels[channelIndex].uFlags & TIW_REG_DOMAIN_DFS)
		{
			*isDfsChannel = TRUE;
			// verifyDfsChannelValidity(pSupportedChannels, channelIndex);
		}
		else
		{
			*isDfsChannel = FALSE;
		}
	}

	return pSupportedChannels[channelIndex].channelValidityActive;
}

/* Note!
 * For now the following function is deprecated.
 * currently when a beacon with Country IE is found, we override the
 * entire regulatory domain context block and rely solely on the
 * data we received in the beacon.
 * Moreover, we don't update the regulatory domain database accordingly,
 * we just set a flag there that says so.
 * For more info see: regulatoryDomain_handlePowerConstraint().
 */
/***********************************************************************
 *                       setSupportedChannelsAccording2CountryIe	   *
 ***********************************************************************
DESCRIPTION:	Called when beacon/Probe Response with Country IE
				is found.
				The function sets the local countryIE per band with the CountryIE
				 that was detected in the last passive scan.
				 It is assumed that only one Country IE per band is allowed.
				 If Country is changed when the TNET is loaded, it should
				 be re-loaded in order to re-config the new Country domain.

INPUT:      hRegulatoryDomain	-	RegulatoryDomain handle.
			pCountry	-	pointer to the detected country IE.

OUTPUT:

RETURN:     OK - New country code was set (or the same one was already configured)
           -1 - The new country code could not be set

************************************************************************/
int32_t regulatoryDomain_setSupportedChannelsAccording2CountryIe(dot11_COUNTRY_t *pCountry,
																   Bool32 band_2_4,
																   Bool32 updateFw)
{

    RegulatoryDomain_t  *pRegulatoryDomain = &RegulatoryDomain;
	channelCapability_t	*pSupportedChannels;
	uint8_t	             channelIndex;
	uint8_t              tripletChannelIndex, tripletChannelCnt;
	uint8_t              channelStep, numberOfChannels, minChannelNumber, maxChannelNumber;
	uint32_t			 baseFreq;
	uint32_t 			 countryID = 0xFFFFFFFF;

    HOOK(HOOK_IN_REGULATORY_DOMAIN);

    /* If country override disabled - return*/
	/* For now, pRegulatoryDomain->uDontOverride is always set */
	if (pRegulatoryDomain->uDontOverride ||
		(!pCountry->countryIE.CountryString[0] && !pCountry->countryIE.CountryString[1]))
	{
        if (pRegulatoryDomain->bFwUpdateRequired)
			sendRegDomainCmdToFw();
        return OK;
	}

	/* Find the country in internal tables*/
	if (getCountryIdInTable(pCountry->countryIE.CountryString, &countryID) != OK)
	{
        /*New country not found in internal DB - Keep pervious country*/
		GTRACE(GRP_GENERAL_ERROR, "ERROR: Trying to set country %c%c, but country not found in internal DB. Country wasn't saved",  pCountry->countryIE.CountryString[0],  pCountry->countryIE.CountryString[1]);
		GTRACE(GRP_GENERAL_ERROR, "ERROR: Add the country to tiwlanRegDomain.ini");
        return-1;
	}

    if( band_2_4 == TRUE )
	{
		/* If same country - Nothing to do */
		if (!memcmp( (void *)&pCountry->countryIE,
					 (void *)&pRegulatoryDomain->country24.countryIE,
					 sizeof(dot11_countryIE_t)))
		{
            if (pRegulatoryDomain->bFwUpdateRequired)
				sendRegDomainCmdToFw();
			return OK;
		}

        /* New country for 2.4G - prepare for setting */
		pSupportedChannels = pRegulatoryDomain->supportedChannels_band_2_4;
        channelStep = BG_24G_BAND_CHANNEL_HOPS;
		maxChannelNumber = NUM_OF_CHANNELS_24;
		minChannelNumber = BG_24G_BAND_MIN_CHANNEL;
		numberOfChannels = NUM_OF_CHANNELS_24;
		baseFreq = BASE_FREQ_2_4;

		/* save the country IE */
		memcpy((void*)&pRegulatoryDomain->country24, (void *)pCountry, sizeof(dot11_COUNTRY_t));

		/* Zero all the 2.4G channels configuration */
		pRegulatoryDomain->fwRegDomainChannelBitField.chBitMap1 &= ~(FW_REG_DOMAIN_CHANNEL_BITMASK_2_4G);

        GTRACE(GRP_REG_DOMAIN, "Country 2.4 =%c%c%c",pRegulatoryDomain->country24.countryIE.CountryString[0], pRegulatoryDomain->country24.countryIE.CountryString[1], pRegulatoryDomain->country24.countryIE.CountryString[2]);
	}
	else    /* band 5.0 */
	{
		/* If same country - Nothing to do */
		if (!memcmp( (void *)&pCountry->countryIE,
					 (void *)&pRegulatoryDomain->country5.countryIE,
					 sizeof(dot11_countryIE_t)))
		{
			if (pRegulatoryDomain->bFwUpdateRequired)
				sendRegDomainCmdToFw();
			return OK;
		}

		/* New country for 5G - prepare for setting */
		pSupportedChannels = pRegulatoryDomain->supportedChannels_band_5;
        channelStep = A_5G_BAND_CHANNEL_HOPS;
		maxChannelNumber = A_5G_BAND_MAX_CHANNEL;
		minChannelNumber = A_5G_BAND_MIN_CHANNEL;
		numberOfChannels = A_5G_BAND_NUM_CHANNELS;
		baseFreq = BASE_FREQ_5_0;

		/* save the country IE */
		memcpy((void*)&pRegulatoryDomain->country5, (void*)pCountry, sizeof(dot11_COUNTRY_t));

        /* Zero all the 5G channels configuration */
        pRegulatoryDomain->fwRegDomainChannelBitField.chBitMap1 &= ~(FW_REG_DOMAIN_CHANNEL_LOW_BITMASK_5G);
        pRegulatoryDomain->fwRegDomainChannelBitField.chBitMap2 &= ~(FW_REG_DOMAIN_CHANNEL_HIGH_BITMASK_5G);

        GTRACE(GRP_REG_DOMAIN, "Country 5 =%c%c%c",pRegulatoryDomain->country5.countryIE.CountryString[0], pRegulatoryDomain->country5.countryIE.CountryString[1], pRegulatoryDomain->country5.countryIE.CountryString[2]);
	}

    /* 802.11k changes (to be used during the RRM) */
    if ((pCountry->countryIE.CountryString[0] == 'U') && (pCountry->countryIE.CountryString[1] == 'S'))
    {
        pRegulatoryDomain->countryZone = REGULATORY_ZONE_USA;
    }
    else if ((pCountry->countryIE.CountryString[0] == 'J') && (pCountry->countryIE.CountryString[1] == 'P'))
    {
        pRegulatoryDomain->countryZone = REGULATORY_ZONE_JAPAN;
    }
    else /* Europe and the rest of the World */
    {
        pRegulatoryDomain->countryZone = REGULATORY_ZONE_RST;
    }

    GTRACE(GRP_REG_DOMAIN, "setSupportedChannelsAccording2CountryIe: Zone updated to %d (0=US, 1=JAPAN, 2=RestOfTheWorld)", pRegulatoryDomain->countryZone);


	/* New Country IE was saved - update the supported channels and update FW */

	/* Clear the validity of all channels */
	for (channelIndex=0; channelIndex<numberOfChannels; channelIndex++)
	{
		pSupportedChannels[channelIndex].channelValidityActive = FALSE;
		pSupportedChannels[channelIndex].channelValidityPassive = FALSE;
		pSupportedChannels[channelIndex].uFlags = 0;
		pSupportedChannels[channelIndex].uMaxTxPowerDomain = WLAN_MIN_TX_POWER_DBM;
	}

	/* Set validity of the channels according to triplets in IE */
	tripletChannelCnt = (pCountry->hdr.eleLen - DOT11_COUNTRY_STRING_LEN) / 3;
    for (tripletChannelIndex = 0; tripletChannelIndex < tripletChannelCnt ; tripletChannelIndex++)
	{
		uint8_t	firstChannelNumInTriplet;
		uint32_t	minFreqInTriplet, maxFreqInTriplet;

		firstChannelNumInTriplet = pCountry->countryIE.tripletChannels[tripletChannelIndex].firstChannelNumber;
		minFreqInTriplet = firstChannelNumInTriplet*5 + baseFreq;
		maxFreqInTriplet = (firstChannelNumInTriplet+((pCountry->countryIE.tripletChannels[tripletChannelIndex].numberOfChannels-1)*channelStep))*5 + baseFreq;
        GTRACE(GRP_REG_DOMAIN, "firstChannelNumInTriplet=%d,channelStep=%d", firstChannelNumInTriplet, channelStep);

		for (channelIndex=0; channelIndex<pCountry->countryIE.tripletChannels[tripletChannelIndex].numberOfChannels; channelIndex++)
		{
			uint16_t	channelNumber;

			channelNumber = firstChannelNumInTriplet+(channelIndex*channelStep);
            GTRACE(GRP_REG_DOMAIN, "setSupportedChannelsAccording2CountryIe of channel=%d", channelNumber);

			if (channelNumber <= maxChannelNumber)
			{
				uint8_t 	channelIndex4Band;
				uint32_t	channelFreq;

				channelIndex4Band = (channelNumber-minChannelNumber);
				channelFreq = channelNumber*5 + baseFreq;
				if (channelIndex4Band < numberOfChannels)
				{
					pSupportedChannels[channelIndex4Band].channelValidityPassive = TRUE;

                    /* If this is a DFS channel it is not valid for active yet */
					if (!isDfsChannelInCountry(countryID, channelNumber))
					{
						pSupportedChannels[channelIndex4Band].channelValidityActive = TRUE;
						if (setChannelAsFwBitmap(channelNumber, band_2_4, TRUE) == FALSE)
						{
							GTRACE(GRP_GENERAL_ERROR, "ERROR: Channel to index translation failed, received channel : = %d, channelIndex4Band = %d, CountryString = %c%c ",
								  channelNumber, channelIndex4Band, pCountry->countryIE.CountryString[0], pCountry->countryIE.CountryString[1]);
						}
					}
					else
					{
						pSupportedChannels[channelIndex4Band].uFlags |= TIW_REG_DOMAIN_DFS;
					}

					#if 0//we dont support HT40
					/*Set HT40 attributes for the channel*/
					if (channelNumber != 14)
					{
						if (channelFreq - 30 >= minFreqInTriplet && channelFreq - 10 <= maxFreqInTriplet)
							pSupportedChannels[channelIndex4Band].uFlags |= TIW_REG_DOMAIN_HT40MINUS;
						if (channelFreq + 10 >= minFreqInTriplet && channelFreq + 30 <= maxFreqInTriplet)
							pSupportedChannels[channelIndex4Band].uFlags |= TIW_REG_DOMAIN_HT40PLUS;
					}
                    #endif
					pSupportedChannels[channelIndex4Band].uMaxTxPowerDomain =
						pCountry->countryIE.tripletChannels[tripletChannelIndex].maxTxPowerLevel;

                    GTRACE(GRP_REG_DOMAIN, "channel = %d uMaxTxPowerDomain=%d", channelNumber, pSupportedChannels[channelIndex4Band].uMaxTxPowerDomain);
				}
				else
				{
					GTRACE(GRP_REG_DOMAIN, "setSupportedChannelsAccording2CountryIe index out of bounds=%d numberOfChannels = %d", channelIndex4Band, numberOfChannels);
				}
			}
		}
	}

    /* Update fw with new configuration*/
	if (updateFw)
		sendRegDomainCmdToFw();
	else
		pRegulatoryDomain->bFwUpdateRequired = TRUE;

	return OK;
}

int32_t regulatoryDomain_GetCapability(RadioBand_e band, uint16_t channel, channelCapability_t *ChannelCapability)
{
    RegulatoryDomain_t  *pRegulatoryDomain = &RegulatoryDomain;
	uint16_t channelIndex;
	channelCapability_t* pSupportedChannels;

    HOOK(HOOK_IN_REGULATORY_DOMAIN);

    if (band == RADIO_BAND_5GHZ)
	{
		channelIndex = (channel - A_5G_BAND_MIN_CHANNEL);
		if (channelIndex > A_5G_BAND_NUM_CHANNELS)
		{
			GTRACE(GRP_GENERAL_ERROR, "ERROR: regulatoryDomain_GetCapability: channelIndex = %d", channelIndex);
			return -1;
		}
		pSupportedChannels = pRegulatoryDomain->supportedChannels_band_5;
	}
	else
	{
		channelIndex = (channel - BG_24G_BAND_MIN_CHANNEL);
		if (channelIndex > NUM_OF_CHANNELS_24)
		{
			GTRACE(GRP_GENERAL_ERROR, "ERROR: regulatoryDomain_GetCapability: channelIndex = %d", channelIndex);
			return -1;
		}
		pSupportedChannels = pRegulatoryDomain->supportedChannels_band_2_4;
	}

	//verifyDfsChannelValidity(pSupportedChannels, channelIndex);

	ChannelCapability->uFlags = pSupportedChannels[channelIndex].uFlags;
	ChannelCapability->channelValidityActive = pSupportedChannels[channelIndex].channelValidityActive;
	ChannelCapability->channelValidityPassive = pSupportedChannels[channelIndex].channelValidityPassive;
	ChannelCapability->timestamp = pSupportedChannels[channelIndex].timestamp;
	ChannelCapability->uMaxTxPowerDomain = pSupportedChannels[channelIndex].uMaxTxPowerDomain;
	//REG_DOMAIN_PRINT_REPORT("capability on 2.4/5G channel uFlags= %d,validityActive=%d,validityPassive=%d,timestamp=%d,MAxTx=%d\n",ChannelCapability->uFlags,ChannelCapability->channelValidityActive,ChannelCapability->channelValidityPassive ,ChannelCapability->timestamp,ChannelCapability->uMaxTxPowerDomain);
	
	return OK;
}


void regulatoryDomain_GetCahnnelOnBand(RadioBand_e band, supportedChannels_t *supportedChannels)
{
    RegulatoryDomain_t  *pRegulatoryDomain = &RegulatoryDomain;
//	channelCapability_t *pSupportedChannelsCap = NULL;
	uint32_t i;

    HOOK(HOOK_IN_REGULATORY_DOMAIN);

    if (band == RADIO_BAND_2_4GHZ)
	{
		supportedChannels->listOfChannels = (uint8_t*)pRegulatoryDomain->supportedChannels_band_2_4;
		supportedChannels->sizeOfList = NUM_OF_CHANNELS_24;
//		pSupportedChannelsCap = pRegulatoryDomain->supportedChannels_band_2_4;
	}
	else
	{
		supportedChannels->listOfChannels = (uint8_t*)pRegulatoryDomain->supportedChannels_band_5;
		supportedChannels->sizeOfList = A_5G_BAND_NUM_CHANNELS;
//		pSupportedChannelsCap = pRegulatoryDomain->supportedChannels_band_5;

        /* Varify activity of DFS channels*/
		for (i=0; i<A_5G_BAND_NUM_CHANNELS; i++)
		{
			verifyDfsChannelValidity(pRegulatoryDomain->supportedChannels_band_5, i);
		}
	}
}

/*****************************************************************************
 * Module:    	regulatoryDomain module, 
 * API:         
 *
 * Description: decompress the rom/patch compressed country data tables
 * Callers:     
 * Input: pCountryString - Country code string
 * Return: Country index to the country data tables on sucess, -1 otherwise
 ****************************************************************************/
int16_t regulatoryDomain_GetCountryRegion(uint8_t *pCountryString)
{
    int8_t countryIndex = -1;
	int8_t i, foundMatch = 0;
   
    HOOK(HOOK_IN_REGULATORY_DOMAIN);
    
    for (i = 0; i < REG_DOMAIN_NUM_OF_REGIONS; i++)
    {
		foundMatch = !os_memcmp(gConfigCountryCompressedTable[i].countryStr,
					   			pCountryString,
					   			REG_DOMAIN_COUNTRY_STR_LEN);
        if (foundMatch)
        {
			/* If the country is not a custom region, use its region index 
			 * This helps avoiding overwriting the custom region with a new country code
			 * without a custom region in the DB.
			 */
			if (gConfigCountryCompressedTable[i].region != REG_DOMAIN_CUSTOM_REGION)
			{
				countryIndex = gConfigCountryCompressedTable[i].region;
			}
			break;
        }
    }

    return countryIndex;
}

int32_t regulatoryDomain_SetCountry(uint8_t *pCountryStr)
{
	int16_t countryIndex = 0;
	uint8_t customCount = 0;

	countryIndex = regulatoryDomain_GetCountryRegion(pCountryStr);

    if (countryIndex < 0)
    {
        /* Country not found in internal DB - Keep in custom domain*/
		GTRACE(GRP_REG_DOMAIN, "regulatoryDomain_SetCountry: Country code %c%c "
							   "not found in DB. Setting it to custom entry",
							   pCountryStr[0],  pCountryStr[1]);

		if (!isCountryCodeValid(pCountryStr))
		{
			CME_PRINT_REPORT_ERROR("\n\rregulatoryDomain_SetCountry: "
							   	   "Country code %c%c not valid.",
							   	   pCountryStr[0], pCountryStr[1]);

			return WlanError(WLAN_ERROR_SEVERITY__LOW,
							 WLAN_ERROR_MODULE__COMMANDS,
							 WLAN_ERROR_TYPE__INVALID_PARAM_SET_TYPE);
		}

		customCount = regulatoryDomain_GetCustomDomainEntriesCount();
		if (customCount == 0)
		{
			CME_PRINT_REPORT_ERROR("\n\rERROR: Choosing a custom country code, "
								   "but no custom entry is available in the DB.\n\r"
								   "Please add a custom entry to the DB first.");
			return WlanError(WLAN_ERROR_SEVERITY__LOW,
							 WLAN_ERROR_MODULE__COMMANDS,
							 WLAN_ERROR_TYPE__INVALID_PARAM_SET_TYPE);
		}

		/* Copy country code to the DB at the custom entry */
		countryIndex = REG_DOMAIN_CUSTOM_REGION;
		os_memcpy(gConfigCountryCompressedTable[countryIndex].countryStr,
				  pCountryStr,
				  REG_DOMAIN_COUNTRY_STR_LEN);
	}

	/* Set country code as current country code */
    os_memcpy(gCountryDomainStr, pCountryStr, REG_DOMAIN_COUNTRY_STR_LEN);

    /* Ensure environment byte is valid per 802.11d §7.3.2.12.
     * REG_DOMAIN_COUNTRY_STR_LEN is 2, so byte[2] is not copied above.
     * 0x20 = "any environment" (the safe default). */
    if (gCountryDomainStr[2] == 0x00)
    {
        gCountryDomainStr[2] = 0x20;
    }

    return OK;
}

/********************************************************************************/
/*						Internal functions implementation.						*/
/********************************************************************************/

///************************************************************************
// *      setSupportedChannelsAccording2ScanControlTable 					*
// ************************************************************************/
///**
//*
//*
//* \b Description:
//*
//* This function is called in config and sets the supported channels according to
//* the scan control table read from registry and reg domain read from the chip.
//*
//* \b ARGS:
//*
//*  I   - pRegulatoryDomain - pointer to the regDoamin SM context  \n
//*
//* \b RETURNS:
//*
//*  None.
//*
//*
//*************************************************************************/
static void setWorldWideDomainSupportedChannels()
{
    RegulatoryDomain_t  *pRegulatoryDomain = &RegulatoryDomain;
	uint8_t 	channelIndex = 0;

	uint8_t localDefaultABandChannels[A_5G_BAND_NUM_CHANNELS];

	HOOK(HOOK_IN_REGULATORY_DOMAIN);

	GTRACE_NVIC(GRP_REG_DOMAIN, "setWorldWideDomainSupportedChannels");
	REG_DOMAIN_PRINT_REPORT("setWorldWideDomainSupportedChannels\n" );
	//work on local copy so that original copy can reside in ROM
	memcpy(localDefaultABandChannels, DefaultABandChannels, A_5G_BAND_NUM_CHANNELS);

	/* If Japan channels are NOT supported - remove from default A band channel list*/
	if (!pRegulatoryDomain->japanChannelsEnabled)
	{
		while (JapanABandChannels[channelIndex])
		{
		    localDefaultABandChannels[JapanABandChannels[channelIndex] - A_5G_BAND_MIN_CHANNEL] = 0;
			channelIndex++;
		}
	}

	/* Step 1: Set WW 2.4Ghz Active channels*/
	for (channelIndex = 0; channelIndex < WORLD_WIDE_ACTIVE_2_4_CHANNEL; channelIndex++)
	{
		pRegulatoryDomain->supportedChannels_band_2_4[channelIndex].channelValidityActive = TRUE;
		pRegulatoryDomain->supportedChannels_band_2_4[channelIndex].channelValidityPassive = TRUE;
        #if 0//we dont support HT40
		if (channelIndex < WORLD_WIDE_2_4_CHANNEL_HT40_MAX)
			pRegulatoryDomain->supportedChannels_band_2_4[channelIndex].uFlags |= TIW_REG_DOMAIN_HT40PLUS;
		if (channelIndex > WORLD_WIDE_2_4_CHANNEL_HT40_MIN)
			pRegulatoryDomain->supportedChannels_band_2_4[channelIndex].uFlags |= TIW_REG_DOMAIN_HT40MINUS;
        #endif
		GTRACE_NVIC(GRP_REG_DOMAIN, "setWorldWideDomainSupportedChannels = %d", channelIndex);
		/* Update FW channel bitmap */
		setChannelAsFwBitmap ((TWD_CALIBRATION_CHANNEL_2_4_MIN + channelIndex), TRUE, TRUE);

		pRegulatoryDomain->supportedChannels_band_2_4[channelIndex].uMaxTxPowerDomain = WLAN_MAX_TX_POWER_DBM;
	}

	/* Step 2: Set WW 2.4Ghz Passive channels*/
	for (channelIndex = WORLD_WIDE_ACTIVE_2_4_CHANNEL; channelIndex < NUM_OF_CHANNELS_24; channelIndex++)
	{
		pRegulatoryDomain->supportedChannels_band_2_4[channelIndex].channelValidityActive = FALSE;
		pRegulatoryDomain->supportedChannels_band_2_4[channelIndex].channelValidityPassive = TRUE;
		pRegulatoryDomain->supportedChannels_band_2_4[channelIndex].uFlags = 0;
	}
	if (!pRegulatoryDomain->japanChannelsEnabled)
	{
		/* Japan channels are not supported - remove channel 14 from 2.4Ghz channel list*/
		channelIndex--;
		pRegulatoryDomain->supportedChannels_band_2_4[channelIndex].channelValidityPassive = FALSE;
	}

	/* Step 3: Set WW 5Ghz channels*/
	for (channelIndex = 0; channelIndex < A_5G_BAND_NUM_CHANNELS; channelIndex++)
	{
		pRegulatoryDomain->supportedChannels_band_5[channelIndex].channelValidityActive = FALSE;
		pRegulatoryDomain->supportedChannels_band_5[channelIndex].channelValidityPassive = (Bool32)localDefaultABandChannels[channelIndex];
		pRegulatoryDomain->supportedChannels_band_5[channelIndex].uMaxTxPowerDomain = WLAN_MAX_TX_POWER_DBM;
		if (pRegulatoryDomain->supportedChannels_band_5[channelIndex].channelValidityPassive)
		{
			pRegulatoryDomain->supportedChannels_band_5[channelIndex].uFlags = TIW_REG_DOMAIN_DFS;
		}
		else
			pRegulatoryDomain->supportedChannels_band_5[channelIndex].uFlags = 0;
	}

}

static void sendRegDomainCmdToFw()
{
    HOOK(HOOK_IN_REGULATORY_DOMAIN);
}


static void verifyDfsChannelValidity(channelCapability_t *pSupportedChannels, uint8_t channelIndex)
{
//    RegulatoryDomain_t  *pRegulatoryDomain = &RegulatoryDomain;
    HOOK(HOOK_IN_REGULATORY_DOMAIN);

    if ((pSupportedChannels[channelIndex].uFlags & TIW_REG_DOMAIN_DFS) &&
		((osi_GetTimeMS() - pSupportedChannels[channelIndex].timestamp) >= CHANNEL_VALIDITY_TS_THRESHOLD ))
	{
		/* If 802.11h is enabled, a DFS channel is valid only for 10 sec from the last Beacon/ProbeResponse */
        pSupportedChannels[channelIndex].channelValidityActive = FALSE;
        GTRACE(GRP_REG_DOMAIN,
			  "DFS channel (# %d) - last beacon/probe req was received more then %d msec !!",
			  channelIndex+A_5G_BAND_MIN_CHANNEL,
			  CHANNEL_VALIDITY_TS_THRESHOLD);
	}
}

static int32_t getCountryIdInTable(uint8_t *pCountryStr, uint32_t *pCountryID)
{

    RegulatoryDomain_t  *pRegulatoryDomain = &RegulatoryDomain;
	uint32_t cntrId;

    HOOK(HOOK_IN_REGULATORY_DOMAIN);

    for (cntrId =0; cntrId < pRegulatoryDomain->uNumOfCountriesInTable; cntrId++)
	{
        if (!memcmp(pRegulatoryDomain->pRegDomainTable[cntrId].countryStr, pCountryStr, REG_DOMAIN_COUNTRY_STR_LEN))
		{
			*pCountryID = cntrId;
			return OK;
		}
	}
	return-1;
}


static Bool32 isDfsChannelInCountry(uint32_t cntrId, uint32_t uChannel)
{

    RegulatoryDomain_t  *pRegulatoryDomain = &RegulatoryDomain;
	RegDomainCountryInfo_t *pRegDomainTable;
    uint32_t group, channel;

    HOOK(HOOK_IN_REGULATORY_DOMAIN);

    if (cntrId >= pRegulatoryDomain->uNumOfCountriesInTable)
		return FALSE;

	pRegDomainTable = &pRegulatoryDomain->pRegDomainTable[cntrId];

    for (group=0; group < REG_DOMAIN_MAX_ROWS_IN_COUNTRY; group++)
	{
		for (channel=0; channel<REG_DOMAIN_MAX_CHAN_NUM; channel++)
		{
			if (pRegDomainTable->domainReg[group].Channel[channel] == uChannel)
				return pRegDomainTable->domainReg[group].DfsChannel;
		}
	}
	return FALSE;
}


/***********************************************************************
 *                       setChannelAsFwBitmap
 ***********************************************************************
DESCRIPTION:    Writes the appropriate bit to the FW bitmap

INPUT:      hRegulatoryDomain   -   RegulatoryDomain handle.
            channelNumber       -  desired channel
            band_2_4            - boolean - True if band is 2.4G

OUTPUT: pRegulatoryDomain->fwRegDomainChannelBitField - channel bitfield

RETURN: FALSE - No change was made to bitmap

************************************************************************/
static Bool32 setChannelAsFwBitmap(uint16_t channelNumber, Bool32 band_2_4, Bool32 shouldSet)
{
    RegulatoryDomain_t  *pRegulatoryDomain = &RegulatoryDomain;
    int8_t  channelFWIdx = getChannelIndexTranslation(channelNumber,band_2_4);
	uint32_t *pBitMap;
	Bool32 isBitSet;

	HOOK(HOOK_IN_REGULATORY_DOMAIN);

    if (channelFWIdx == -1)
    {
		/* We have received a bad channel !*/
        return FALSE;
    }

	/* meaning we are in the LOW bitmap */
    if (channelFWIdx <= 31)
    {
		pBitMap = &(pRegulatoryDomain->fwRegDomainChannelBitField.chBitMap1);
	}
	else
	{
		channelFWIdx = channelFWIdx -32;
		pBitMap = &(pRegulatoryDomain->fwRegDomainChannelBitField.chBitMap2);
	}

	isBitSet = IS_BIT_SET(*pBitMap, channelFWIdx);

    /* Change to bitmap is required*/
	if (shouldSet != isBitSet)
	{
		if (shouldSet)
		    SET_BIT_IN_BITMAP(*pBitMap, channelFWIdx)
		else
		    CLEAR_BIT_IN_BITMAP(*pBitMap, channelFWIdx)

		return TRUE;
	}

    return FALSE;
}

/***********************************************************************
 *                       getChannelIndexTranslation
 ***********************************************************************
DESCRIPTION:    Returns the bit index values according to the FW-values.
                See full table above.
INPUT:
            channelNumber       -  desired channel
            band_2_4            - boolean - True if band is 2.4G

RETURN: int8_t - bit index value (0-61) as we treat the struct as a full 64 bitmap

************************************************************************/
static int8_t getChannelIndexTranslation(uint16_t chNumber, Bool32 band_2_4)
{
    int8_t idx = -1;
    uint8_t FIRST_5G_CHANNEL_IDX= 18;

    HOOK(HOOK_IN_REGULATORY_DOMAIN);

    /* Bits (14-17) are relevant to 4.9 G and ignored here. as we don't have 4.9 band indication */
    if (band_2_4)
    {
        /* All the 2_4 channels are located in the First bitmap (Bits 0..13) */
        if (chNumber >= BG_24G_BAND_MIN_CHANNEL && chNumber <= NUM_OF_CHANNELS_24)
        {
            idx = chNumber - 1;
        }
        else
        {
            idx = -1;
        }
    }
    else
    {
        /* 5G channels are located in the first and second bitmap,
         * starting from position 18 for channel 8, up to 30 for channel 184
         * bits (..18-31) ==> channels (8-60)
         * Bits    (18,19,20) ==>
         * Channels(8,12,16)  (hops are 4)
         */
        if (chNumber >= 8 && chNumber <= 16)
        {
            idx = ((chNumber-8)/4 + FIRST_5G_CHANNEL_IDX);
        }
        /*
         * last total 3
         * Bits    (21,22,23,24,25,26,27,28) ==>
         * Channels(34,36,38,40,42,44,46,48) (hops are 2)
         */
        else if (chNumber >= 34 && chNumber <= 48)
        {
            idx = ((chNumber-34)/2 + 3 + FIRST_5G_CHANNEL_IDX);
        }
        /*
         * last total 11
         * Bits    (29,30,31,32) ==>
         * Channels(52,56,60,64) (hops are 4)
         */
        else if (chNumber >= 52 && chNumber <= 64)
        {
            idx = ((chNumber-52)/4 + 11 + FIRST_5G_CHANNEL_IDX);
        }
        /*
         * last total 15
         * Bits    (33 ,34 ,35 ,36 ,37 ,38 ,39 ,40 ,41 ,42, 43) ==>
         * Channels(100,104,108,112,116,120,124,128,132,136,140) (hops are 4)
         */
        else if (chNumber >= 100 && chNumber <= 144)
        {
            idx = ((chNumber-100)/4 + 15 + FIRST_5G_CHANNEL_IDX);
        }
        /*
         * last total 26
         * Bits    (44 ,45 ,46 ,47 ,48 ) ==>
         * Channels(149,153,157,161,165) (hops are 4)
         */
        else if (chNumber >= 149 && chNumber <= 165)
        {
            idx = ((chNumber-149)/4 + 26 + FIRST_5G_CHANNEL_IDX);
        }
        /*
         * last total 31
         * Bits    (49 ,50 ,51 ,52 ,53, 54, 55, 56, 57, 58, 59, 60, 61, 62 ) ==>
         * Channels(171,172,173,174,175,176,177,178,179,180,181,182,183,184) (hops are 1)
         */
        else if (chNumber >= 171 && chNumber <= 184)
        {
            idx = ((chNumber-171) + 31 + FIRST_5G_CHANNEL_IDX);
        }
        else
        {
            idx = -1;
        }
    }

    return idx;
}


static int16_t getIndexChannelTranslation(uint8_t chIndex, uint8_t band)
{
    int16_t channel = -1;

    HOOK(HOOK_IN_REGULATORY_DOMAIN);

    if (band == RADIO_BAND_2_4GHZ)
    {
        if (chIndex >= 0 && chIndex < NUM_OF_CHANNELS_24)
        {
            /* rom_dot11g_channels holds the channel numbers for 2.4Ghz */
            channel = rom_dot11g_channels[chIndex];
        }
        else
        {
            channel = 0;
        }
    }
    else
    {
        if (chIndex >= 0 && chIndex < A_BAND_CHANNEL_COUNT)
        {
            /* rom_dot11a_channels holds the channel numbers for 5Ghz */
            channel = rom_dot11a_channels[chIndex];
        }
        else
        {
            channel = 0;
        }
    }

    return channel;
}

static int8_t setSupportedChannelsAccording2Domain(void)
{
    RegulatoryDomain_t  *pRegulatoryDomain = &RegulatoryDomain;
	channelCapability_t *pSupportedChannels;
	uint8_t              channelIndex = 0;
	uint8_t              groupPatternIndex;
    uint8_t              chanPatternIndex;
	uint32_t             channelBitmask;
    uint32_t             minClassFreq, maxClassFreq, baseFreq;
    uint32_t             channel;
    uint32_t             channelbit;
    uint32_t             channelFreq;
    uint32_t             i;
    
    ConfigChanPattern_t *pChanPattern;

    groupPatternIndex = regulatoryDomain_GetCountryRegion(gCountryDomainStr);
    pRegulatoryDomain->countryDomain = groupPatternIndex;
    pRegulatoryDomain->countryZone   = (RegulatoryZone_e)groupPatternIndex;

    if (pRegulatoryDomain->countryZone == REGULATORY_ZONE_JAPAN)
    {
        pRegulatoryDomain->japanChannelsEnabled = TRUE;
    }

    /*Country found in internal tables - configure new country parameters*/
	memcpy(pRegulatoryDomain->country24.countryIE.CountryString, gCountryDomainStr, DOT11_COUNTRY_STRING_LEN);
	memcpy(pRegulatoryDomain->country5.countryIE.CountryString, gCountryDomainStr, DOT11_COUNTRY_STRING_LEN);
	pRegulatoryDomain->country24.hdr.eleLen = DOT11_COUNTRY_STRING_LEN;
	pRegulatoryDomain->country5.hdr.eleLen = DOT11_COUNTRY_STRING_LEN;

	/* Zero FW channel configuration bitmap */
	os_memset(&pRegulatoryDomain->fwRegDomainChannelBitField, 0, sizeof(RegDomainChannelConfigBitField_t));

    /* Clear the validity of all channels */
	os_memset(&pRegulatoryDomain->supportedChannels_band_2_4, 0, sizeof(pRegulatoryDomain->supportedChannels_band_2_4));
	os_memset(&pRegulatoryDomain->supportedChannels_band_5, 0, sizeof(pRegulatoryDomain->supportedChannels_band_5));

	/* Zero all the 2.4G channels configuration */
	pRegulatoryDomain->fwRegDomainChannelBitField.chBitMap1 &= ~(FW_REG_DOMAIN_CHANNEL_BITMASK_2_4G);

    /* Zero all the 5G channels configuration */
    pRegulatoryDomain->fwRegDomainChannelBitField.chBitMap1 &= ~(FW_REG_DOMAIN_CHANNEL_LOW_BITMASK_5G);
    pRegulatoryDomain->fwRegDomainChannelBitField.chBitMap2 &= ~(FW_REG_DOMAIN_CHANNEL_HIGH_BITMASK_5G);

    /* Configure the supported channels of the new country for both bands */
    /* Collect all channels from all sub-bands */
    /* on same band - do OR between all sub-band masks */

    /* Configure the supported channels of the new country for both bands*/
    for (i=0; i<gConfigGroupChanPatternsTable[groupPatternIndex].chanAmount; i++)
    {

        /* Extract channel pattern index by group index and sub-band index */
        /* "US" example:     --    4,    13 --    {  0,  8,  4,  5,  9 },    US, group=4, chanPatternIndex = 0 and 8 and 4 and 5 and 9 */
        chanPatternIndex = gConfigGroupChanPatternsTable[groupPatternIndex].chanPatternsList[i];

        /* Extract channel pattern by channel pattern index */
        pChanPattern = &gConfigChanPatternsTable[chanPatternIndex];
        
        if (pChanPattern->band == RADIO_BAND_2_4GHZ)
        {
            pSupportedChannels = &pRegulatoryDomain->supportedChannels_band_2_4[0];
			baseFreq = BASE_FREQ_2_4;
        }
        else if (pChanPattern->band == RADIO_BAND_5GHZ)
        {
            pSupportedChannels = &pRegulatoryDomain->supportedChannels_band_5[0];
			baseFreq = BASE_FREQ_5_0;
        }
        else
            continue;

        channelbit = 0;
        channelBitmask = pChanPattern->chanBitmap;
     
		minClassFreq = pChanPattern->minChannel*5 + baseFreq - 10;
		maxClassFreq = pChanPattern->maxChannel*5 + baseFreq + 10;

        while (channelBitmask > 0)
        {
            channelIndex = 0;
			if (channelBitmask & 1)
            {
                channel = getIndexChannelTranslation(channelbit, pChanPattern->band);
                channelFreq = channel*5 + baseFreq;

                if (pChanPattern->band == RADIO_BAND_5GHZ)
                {
                    channelIndex = channel - A_5G_BAND_MIN_CHANNEL;
					pRegulatoryDomain->is5GHzBandSupported = TRUE;
                }
                else
                {
                    channelIndex = channel - BG_24G_BAND_MIN_CHANNEL;
					pRegulatoryDomain->is2_4GHzBandSupported = TRUE;
                }

                pSupportedChannels[channelIndex].uFlags = 0;
                pSupportedChannels[channelIndex].channelValidityPassive = TRUE;

                /* Set DFS attribute for the channel */
                if (pChanPattern->dfsChannel)
                {
                    pSupportedChannels[channelIndex].channelValidityActive = FALSE;
                    pSupportedChannels[channelIndex].uFlags |= TIW_REG_DOMAIN_DFS;
                }
                else
                {
                    pSupportedChannels[channelIndex].channelValidityActive = TRUE;
					setChannelAsFwBitmap(channel, pChanPattern->band == RADIO_BAND_2_4GHZ ? TRUE : FALSE, TRUE);
                }
                pSupportedChannels[channelIndex].uMaxTxPowerDomain = (int8_t)MIN(pChanPattern->txPowerPerRegion[groupPatternIndex],
                                                                                   WLAN_MAX_TX_POWER_DBM);
            }
            channelBitmask>>=1;
            channelbit++;
        }
    }

    /* Update FW with the new configuration*/
    sendRegDomainCmdToFw();
    
    return OK;
}

/**********************************************************************
*              regulatoryDomain_getChMaxPower                   	  *
***********************************************************************
DESCRIPTION: Find the Max Tx power of selected channel.
             The value returned in dbm according to the channel and
			 country domain.

RETURN:      TRUE if valid channel TX power found, FALSE otherwise.
************************************************************************/
Bool_e regulatoryDomain_getChMaxPower(uint16_t channel, int8_t *max_tx_power)
{
    channelCapability_t channelCapability;
    RadioBand_e temp_band;
    int32_t status;

    if (channel > 14)
    {
        temp_band = RADIO_BAND_5GHZ;
    }
    else
    {
        temp_band = RADIO_BAND_2_4GHZ;
    }

    status = regulatoryDomain_GetCapability(temp_band,
                                            channel,
                                            &channelCapability);

    if (status == OK)
    {
        *max_tx_power = channelCapability.uMaxTxPowerDomain;
        GTRACE(GRP_REG_DOMAIN, "max_tx_power for channel %d = %d dbm",
								channel,
								*max_tx_power);
        return TRUE;
    }
    else
    {
        GTRACE(GRP_GENERAL_ERROR, "max_tx_power for channel ERROR!!!");
        return FALSE;
    }
}

static uint8_t isCountryCodeValid(uint8_t *pCountryStr)
{
	if (pCountryStr == NULL)
	{
		return 0;
	}

	/* 802.11d §7.3.2.12: valid environment bytes are
	 * 0x20 (any), 0x49 ('I' indoor), 0x4F ('O' outdoor). */
	if ((pCountryStr[0] >= 'A') && (pCountryStr[0] <= 'Z') &&
		(pCountryStr[1] >= 'A') && (pCountryStr[1] <= 'Z') &&
		((pCountryStr[2] == 0x20) || (pCountryStr[2] == 'I') ||
		 (pCountryStr[2] == 'O')))
	{
		return 1;
	}
	else if ((pCountryStr[0] == '0') && (pCountryStr[1] == '0') &&
			 ((pCountryStr[2] == 0x20) || (pCountryStr[2] == 'I') ||
			  (pCountryStr[2] == 'O')))
	{
		return 1;
	}

	return 0;
}


/**********************************************************************
*              regulatoryDomain_getCountryString                   	  *
***********************************************************************
DESCRIPTION: return the country code

RETURN:     void
************************************************************************/
int32_t regulatoryDomain_getCountryString(uint8_t *pCountryStr)
{
	if (isCountryCodeValid(gCountryDomainStr))
	{
		os_memcpy(pCountryStr, gCountryDomainStr, DOT11_COUNTRY_STRING_LEN);
		return OK;
	}
	else
	{
		return -1;
	}
}

uint8_t regulatoryDomain_isBandSupported(RadioBand_e band)
{
	RegulatoryDomain_t *pRegulatoryDomain = &RegulatoryDomain;
	if (band == RADIO_BAND_2_4GHZ)
	{
		return pRegulatoryDomain->is2_4GHzBandSupported;
	}
	else if (band == RADIO_BAND_5GHZ)
	{
		return pRegulatoryDomain->is5GHzBandSupported;
	}
	else
	{
		return 0;
	}
}

/***********************************************************************
 *            		getCountryElementTripletsCount					   *
 ***********************************************************************
DESCRIPTION: Returns the number of sub-band triplets in an IEEE80211d
			 country IE.

INPUT:		 dot11_COUNTRY_t *pIE - pointer to the country IE.

RETURN: 	 Number of triplets in IEEE80211d country IE.

************************************************************************/
uint8_t getCountryElementTripletsCount(dot11_COUNTRY_t *pIE)
{
	uint8_t infoElementLen = pIE->hdr.eleLen;
	uint8_t iePadLen = infoElementLen % 3;

	return (infoElementLen - iePadLen - DOT11_COUNTRY_STRING_LEN) / 3;
}

/***********************************************************************
 *            		getCountryElementMaxTxPower						   *
 ***********************************************************************
DESCRIPTION: Extract specific channel max TX power from 
			 IEEE80211d IE triplets.

INPUT:		 pCountryIE 	- IEEE80211d IE.
			 tripletsCount	- number of triplets.
			 channel 		- operating channel.
			 band 			- operating band.
			 channelPower	- output parameter. IEEE80211d IE power level.

RETURN: 	 TRUE if channel can be found in IEEE80211d IE, 
			 FALSE otherwise.

************************************************************************/
Bool_e getCountryElementMaxTxPower(dot11_COUNTRY_t *pIE,
								   uint8_t tripletsCount,
								   uint8_t channel,
								   uint8_t band,
								   int8_t *sta11dMaxTxPower)
{
	uint8_t channelStep, lastChannelNumber;
	dot11_TripletChannel_t *pCurrentTriplet;

	for (int i = 0;  i < tripletsCount;  i++)
	{
		pCurrentTriplet = &(pIE->countryIE.tripletChannels[i]);

		channelStep = (band == RADIO_BAND_2_4GHZ) ? BG_24G_BAND_CHANNEL_HOPS : \
												    A_5G_BAND_CHANNEL_HOPS;

		lastChannelNumber = pCurrentTriplet->firstChannelNumber + \
							((pCurrentTriplet->numberOfChannels - 1)* channelStep);

		if (channel >= pCurrentTriplet->firstChannelNumber &&
			channel <= lastChannelNumber)
		{
			*sta11dMaxTxPower = pCurrentTriplet->maxTxPowerLevel;
			return TRUE;
		}
	}

	return FALSE;
}

/***********************************************************************
 *            	 regulatoryDomain_getPowerFromCountryIE				   *
 ***********************************************************************
DESCRIPTION: This function receives a country IE as input, parses it and
			 finds the channel`s regulatory limit according to that
			 country IE.

INPUT:		 pCountryIE 	- IEEE80211d IE.
			 channel 		- operating channel.
			 band 			- operating band.
			 channelPower	- output parameter. IEEE80211d IE power level.

RETURN: 	 TRUE if successfully read country IE, FALSE otherwise.

************************************************************************/
Bool_e regulatoryDomain_getPowerFromCountryIE(dot11_COUNTRY_t *pCountryIE,
											  uint8_t channel,
											  uint8_t apBand,
											  int8_t *channelPower)
{
	uint8_t tripletsCount;
	Bool_e hasChannelPower = FALSE;

    tripletsCount = getCountryElementTripletsCount(pCountryIE);
	if (tripletsCount == 0)
	{
		return FALSE;
	}

    hasChannelPower = getCountryElementMaxTxPower(pCountryIE,
                                                  tripletsCount,
                                                  channel,
												  apBand,
												  channelPower);
	if (!hasChannelPower)
	{
		GTRACE(GRP_REG_DOMAIN, "ERROR: Operated channel %d can't be found "
							   "in country IE", channel);
	}

	return hasChannelPower;
}

/***********************************************************************
 *            				   findCiscoDtpc						   *
 ***********************************************************************
DESCRIPTION: Take a Cisco DTPC IE (Cisco vendor specific IE actualy),
			 validate it's a DTPC IE and not any other Cisco vendor
			 specific IE, return the value of DTPC.

INPUT:		 ciscoDtpcIE	 - Cisco DTPC IE.
			 powerLevelCisco - power level dictated by Cisco DTPC.

RETURN: 	 TRUE if IE is DTPC and is valid, else otherwise.

************************************************************************/
Bool_e findCiscoDtpc(dot11_CELL_TP_t *ciscoDtpcIE, int8_t *powerLevelCisco)
{

	if (ciscoDtpcIE->hdr.eleLen != 6)
	{
		return FALSE;
	}

	if (ciscoDtpcIE->oui[0] != 0x00 || ciscoDtpcIE->oui[1] != 0x40 ||
		ciscoDtpcIE->oui[2] != 0x96 || ciscoDtpcIE->oui[3] != 0x00)
	{
		return FALSE;
	}

	*powerLevelCisco = ciscoDtpcIE->power;
	
	return TRUE;
}

/***********************************************************************
 *            	   regulatoryDomain_setRoleMaxTxPower				   *
 ***********************************************************************
DESCRIPTION: Set a role`s max TX power. Send a FW command to register
			 this value to FW.

INPUT:		 pDrv		- role`s driver instance.
			 maxTxPower - desired max TX power level for the device.

RETURN: 	 N/A.

************************************************************************/
void regulatoryDomain_setRoleMaxTxPower(ti_driver_ifData_t *pDrv,
										int8_t maxTxPower)
{
	int ret = ctrlCmdFw_SetRoleMaxTxPower(pDrv->roleId, maxTxPower);

	if (ret == 0)
    {
        pDrv->fwMaxTxPower = maxTxPower;
		GTRACE(GRP_REG_DOMAIN, "roleId %d max TX power was set to %d dBm",
							   pDrv->roleId,
							   maxTxPower);
    }
	else
	{
		GTRACE(GRP_REG_DOMAIN, "Failed setting role max TX power to FW");
	}
}

/***********************************************************************
 *            	  regulatoryDomain_handlePowerConstraint			   *
 ***********************************************************************
DESCRIPTION: This function is used for interpreting the regulatory max
			 TX power that should be used for a STA. It takes into
			 account IEEE80211d IE, IEEE80211h IE and also Cisco`s
			 DTPC mechanism.

INPUT:		 pDrv				- role`s driver instance.
			 apCapabilities 	- desired max TX power for the device.
			 countryIE 			- IEEE80211d IE.
			 powerConstraintIE	- IEEE80211h TPC Power Constraint IE.
			 ciscoDtpcIE		- Cisco DTPC IE.

RETURN: 	 N/A.

************************************************************************/
void regulatoryDomain_handlePowerConstraint(ti_driver_ifData_t *pDrv,
                               				uint16_t apCapabilities,
                               				dot11_COUNTRY_t *countryIE,
                               				dot11_POWER_CONSTRAINT_t *powerConstraintIE,
                               				dot11_CELL_TP_t *ciscoDtpcIE)
{
    Bool_e hasChannelPower = FALSE, hasCiscoPower = FALSE, validChannelPower = FALSE;
    int8_t apPowerLevel, powerReduction80211h, powerLevelCisco;
    int8_t newApLevel, powerLevel80211d, newMaxPowerLevel;
    uint8_t apBssid[MAC_ADDR_LEN];
    uint8_t channel, apBand;
    int8_t  channelTxPower;
    
    if (freq_to_chan(pDrv->freq, &channel, &apBand) < 0)
	{
		GTRACE(GRP_REG_DOMAIN, "ERROR: driver frequency is invalid");
		return;
	}

    if (countryIE &&
       (apCapabilities & WLAN_CAPABILITY_SPECTRUM_MGMT ||
        apCapabilities & WLAN_CAPABILITY_RADIO_MEASUREMENT))
    {
        hasChannelPower = regulatoryDomain_getPowerFromCountryIE(countryIE,
                                                                 channel,
                                                                 apBand,
                                                                 &powerLevel80211d);
        if (powerConstraintIE)
        {
			powerReduction80211h = powerConstraintIE->powerConstraint;
            apPowerLevel = MAX(0, powerLevel80211d - powerReduction80211h);
        }
		else
		{
			apPowerLevel = MAX(0, powerLevel80211d);
		}
    }

    if (ciscoDtpcIE)
    {
        hasCiscoPower = findCiscoDtpc(ciscoDtpcIE, &powerLevelCisco);
    }

    if (!hasChannelPower && !hasCiscoPower)
    {
        return;
    }

    if (ti_driver_get_bssid((void *)pDrv, apBssid) < 0)
	{
		return;
	}

    /* If we have both 802.11h and Cisco DTPC, apply both limits
	 * by picking the smallest of the two power levels advertised.
	 */
	if (hasChannelPower &&
	    (!hasCiscoPower || apPowerLevel <= powerLevelCisco))
    {
        newApLevel = apPowerLevel;

        if (newApLevel == pDrv->fwMaxTxPower)
        {
            return;
        }

        GTRACE(GRP_REG_DOMAIN, "Limiting TX power to %d (%d - %d) "
							    "as advertised by " MACSTR " (attenuating to "
							    "max of device`s power 21dBm, if necessary)",
							    apPowerLevel,
							    powerLevel80211d,
							    powerConstraintIE ? powerReduction80211h : 0,
							    MAC2STR(apBssid));
    } 
	else /* hasCiscoPower is always true here. */
	{ 
        newApLevel = powerLevelCisco;

        if (newApLevel == pDrv->fwMaxTxPower)
        {
            return;
        }

        GTRACE(GRP_REG_DOMAIN, "Limiting TX power to %d dBm "
							    "as advertised by " MACSTR " (DTPC) "
							    "(attenuating to max of device`s power 21dBm, "
								"if necessary)",
							    powerLevelCisco,
							    MAC2STR(apBssid));
    }

    pDrv->apPowerLevel = newApLevel;

    validChannelPower = regulatoryDomain_getChMaxPower((uint16_t )channel,
													   &channelTxPower);
	if (!validChannelPower)
	{
		return;
	}

	/* Take minimum of max TX power from reg domain DB and 11d
	 * reducing TPC power constraint.
	 */
	newMaxPowerLevel = MIN(MIN(channelTxPower, pDrv->apPowerLevel), pDrv->fwMaxTxPower);
    
    if (newMaxPowerLevel != pDrv->fwMaxTxPower)
    {
        regulatoryDomain_setRoleMaxTxPower(pDrv, newMaxPowerLevel);
    }
}

int32_t checkCustomDomainEntryValidity(WlanSetRegDomainCustomEntry_t *entryParams)
{
	uint8_t minChannelAllowed = 0, maxChannelAllowed = 0;
	uint8_t bitsSetCount = 0;

	switch (entryParams->band)
	{
		case RADIO_BAND_2_4GHZ:
			minChannelAllowed = CHANNEL_1;
			maxChannelAllowed = CHANNEL_14;
			break;

		case RADIO_BAND_5GHZ:
			minChannelAllowed = CHANNEL_36;
			maxChannelAllowed = CHANNEL_169;
			break;

		default:
		{
			CME_PRINT_REPORT_ERROR("\n\rInvalid band used for custom regulatory domain entry");
			return WlanError(WLAN_ERROR_SEVERITY__LOW,
							 WLAN_ERROR_MODULE__COMMANDS,
							 WLAN_ERROR_TYPE__INVALID_PARAM_SET_TYPE);
		}
	}

	if ((entryParams->minChannel < minChannelAllowed) ||
		(entryParams->minChannel > maxChannelAllowed) ||
		(entryParams->maxChannel < minChannelAllowed) ||
		(entryParams->maxChannel > maxChannelAllowed) ||
		(entryParams->minChannel > entryParams->maxChannel))
	{
		CME_PRINT_REPORT_ERROR("\n\rRequested invalid channels combination");
		return WlanError(WLAN_ERROR_SEVERITY__LOW,
						 WLAN_ERROR_MODULE__COMMANDS,
						 WLAN_ERROR_TYPE__INVALID_PARAM_SET_TYPE);
	}

	if (entryParams->numOfChannels > NUM_BITS_IN_WORD)
	{
		CME_PRINT_REPORT_ERROR("\n\rInvalid channel amount for reg domain rule. "
			   				   "maximum is 32.");
		return WlanError(WLAN_ERROR_SEVERITY__LOW,
						 WLAN_ERROR_MODULE__COMMANDS,
						 WLAN_ERROR_TYPE__INVALID_PARAM_SET_TYPE);
	}

	bitsSetCount = popcount32(entryParams->chanBitmap);
	if (bitsSetCount != entryParams->numOfChannels)
	{
		CME_PRINT_REPORT_ERROR("Incosistency between number of channels set "
							   "and bitmask. bitmap number of channels: %d, "
							   "suggested number: %d",
			   				   bitsSetCount, entryParams->numOfChannels);

		return WlanError(WLAN_ERROR_SEVERITY__LOW,
						 WLAN_ERROR_MODULE__COMMANDS,
						 WLAN_ERROR_TYPE__INVALID_PARAM_SET_TYPE);
	}

	if (entryParams->MaxTxPower > WLAN_MAX_TX_POWER_DBM)
	{
		CME_PRINT_REPORT_ERROR("Invalid TX power for reg domain rule. "
			   				   "max is %d dBm",
							   WLAN_MAX_TX_POWER_DBM);
		return WlanError(WLAN_ERROR_SEVERITY__LOW,
						 WLAN_ERROR_MODULE__COMMANDS,
						 WLAN_ERROR_TYPE__INVALID_PARAM_SET_TYPE);
	}

	return 0;
}

/***********************************************************************
 *                regulatoryDomain_SetCustomDomainEntry                *
 ***********************************************************************
DESCRIPTION: This function sets an entry in the
			 "gConfigChanPatternsTable".
             The entry is dedicated to the custom entries
			 (The last entries in the table that are initialized to 0).

INPUT:       entryParams - pointer to a user input custom reg domain rule

RETURN:      0 on sucess, -1 otherwise
************************************************************************/
int32_t regulatoryDomain_SetCustomDomainEntry(WlanSetRegDomainCustomEntry_t *entryParams)
{
	int32_t ret = 0;
	uint8_t tableEntryIndex = 0;
	ConfigChanPattern_t *pTableEntry = NULL;
	int8_t minChannelBit = 0, maxChannelBit = 0;
	bool isOverwrite = false;

	if (!entryParams)
	{
		return WlanError(WLAN_ERROR_SEVERITY__LOW,
						 WLAN_ERROR_MODULE__COMMANDS,
						 WLAN_ERROR_TYPE__FW_RESPONSE_NULL_BUF);
	}

	if ((entryParams->customIndex < 0) ||
		(entryParams->customIndex >=
			gConfigGroupChanPatternsTable[REG_DOMAIN_CUSTOM_REGION].chanAmount))
	{
		return WlanError(WLAN_ERROR_SEVERITY__LOW,
						 WLAN_ERROR_MODULE__COMMANDS,
						 WLAN_ERROR_TYPE__INVALID_PARAM_SET_TYPE);
	}

	tableEntryIndex = REG_DOMAIN_CUSTOM_ENTRY_BASE + entryParams->customIndex;
	pTableEntry = &(gConfigChanPatternsTable[tableEntryIndex]);
	isOverwrite = (pTableEntry->chanBitmap != 0);

	if (entryParams->resetEntry)
	{
		if (pTableEntry->chanBitmap != 0)
		{
			gCustomRegDomainEntriesCount--;
			ASSERT_GENERAL(gCustomRegDomainEntriesCount <= CUSTOM_RULES_COUNT);
		}
		os_memset(pTableEntry, 0x0, sizeof(ConfigChanPattern_t));
		return 0;
	}

	minChannelBit = FIND_LOWEST_BIT_SET(entryParams->chanBitmap);
	if (minChannelBit < 0)
	{
		CME_PRINT_REPORT_ERROR("No bit is set in custom reg domain entry bitmask!");
		return WlanError(WLAN_ERROR_SEVERITY__LOW,
						 WLAN_ERROR_MODULE__COMMANDS,
						 WLAN_ERROR_TYPE__INVALID_PARAM_SET_TYPE);
	}

	/* We don't care if highest == lowest bit. We only care about the edge 
	 * case in which no bit is set.
	 */
	maxChannelBit = FIND_HIGHEST_BIT_SET(entryParams->chanBitmap);

	/* Return values in case of error for the two following calls will
	 * be checked in the entry validity checking function
	 */
	entryParams->minChannel = getIndexChannelTranslation(minChannelBit,
														 entryParams->band);
	entryParams->maxChannel = getIndexChannelTranslation(maxChannelBit,
														 entryParams->band);
	ret = checkCustomDomainEntryValidity(entryParams);
	if (ret < 0)
	{
		return ret;
	}

	pTableEntry->minChannel = entryParams->minChannel;
	pTableEntry->maxChannel = entryParams->maxChannel;
	pTableEntry->dfsChannel = entryParams->IsDfsChannel;
	pTableEntry->band = entryParams->band;
	pTableEntry->numOfChannels = entryParams->numOfChannels;
	pTableEntry->txPowerPerRegion[REG_DOMAIN_CUSTOM_REGION] = entryParams->MaxTxPower;
	pTableEntry->chanBitmap = entryParams->chanBitmap;

	GTRACE(GRP_REG_DOMAIN,
		   "Entry index %d was added to table with the following parameters: "
		   "IsDfsChannel:%d, MaxTxPower:%d, band:%d, chanBitmap:0x%08x "
		   "minChannel:%d, maxChannel: %d, numOfChannels:%d",
		   entryParams->customIndex, entryParams->IsDfsChannel,
		   entryParams->MaxTxPower, entryParams->band,
		   entryParams->chanBitmap, entryParams->minChannel,
		   entryParams->maxChannel, entryParams->numOfChannels);

	if (!isOverwrite)
	{
		gCustomRegDomainEntriesCount++;
		ASSERT_GENERAL(gCustomRegDomainEntriesCount <= CUSTOM_RULES_COUNT);
	}

    return 0;
}

/***********************************************************************
 *                regulatoryDomain_GetCustomDomainEntry                *
 ***********************************************************************
DESCRIPTION: This function gets an entry from the
			 "gConfigChanPatternsTable".
             The entry is dedicated to the custom entries
			 (The last entries in the table that are initialized to 0).

INPUT:       entryParams - pointer to a user output custom reg domain rule

RETURN:      0 on sucess, -1 otherwise
************************************************************************/
int32_t regulatoryDomain_GetCustomDomainEntry(WlanSetRegDomainCustomEntry_t *entryParams)
{
	uint8_t tableEntryIndex = 0;
	ConfigChanPattern_t *pTableEntry = NULL;

	if (!entryParams)
	{
		return WlanError(WLAN_ERROR_SEVERITY__LOW,
						 WLAN_ERROR_MODULE__COMMANDS,
						 WLAN_ERROR_TYPE__FW_RESPONSE_NULL_BUF);
	}
	
	if ((entryParams->customIndex < 0) ||
		(entryParams->customIndex >=
			gConfigGroupChanPatternsTable[REG_DOMAIN_CUSTOM_REGION].chanAmount))
	{
		return WlanError(WLAN_ERROR_SEVERITY__LOW,
						 WLAN_ERROR_MODULE__COMMANDS,
						 WLAN_ERROR_TYPE__INVALID_PARAM_SET_TYPE);
	}

	tableEntryIndex = REG_DOMAIN_CUSTOM_ENTRY_BASE + entryParams->customIndex;
	pTableEntry = &(gConfigChanPatternsTable[tableEntryIndex]);

	entryParams->IsDfsChannel = pTableEntry->dfsChannel;
	entryParams->band = pTableEntry->band;
	entryParams->maxChannel = pTableEntry->maxChannel;
	entryParams->minChannel = pTableEntry->minChannel;
	entryParams->numOfChannels = pTableEntry->numOfChannels;
	entryParams->MaxTxPower = pTableEntry->txPowerPerRegion[REG_DOMAIN_CUSTOM_REGION];
	entryParams->chanBitmap = pTableEntry->chanBitmap;

	return 0;
}

/***********************************************************************
 *                regulatoryDomain_GetCustomDomainEntriesCount        *
 ***********************************************************************
DESCRIPTION: This function returns the number of custom entries that were
			 added to the "gConfigChanPatternsTable".

INPUT:       N/A

RETURN: 	 Number of custom entries in the table.

************************************************************************/
uint8_t regulatoryDomain_GetCustomDomainEntriesCount(void)
{
	return gCustomRegDomainEntriesCount;
}