/*****************************************************************************
  FILENAME:       build_configs.h

  DESCRIPTION:    Overall definitions of various sets of build configurations.

    ##################################################################################################################

    #################  !!!!!!!!!!!!!!! DO NOT INCLUDE THIS FILE !!!!!!!!!!!!!!!!!!!!!!!!! ############################

    ################## THIS HEADER IS ALREADY PREINCLUDED IN THE MAEKFILE FOR ALL PROJECT SOURCES ####################

    #################  !!!!!!!!!!!!!!! DO NOT INCLUDE THIS FILE !!!!!!!!!!!!!!!!!!!!!!!!! ############################

    ##################################################################################################################


  Copyright (c) 2001 Texas Instruments Inc.
  All Rights Reserved This program is the confidential and proprietary
  product of Texas Instruments Inc.  Any Unauthorized use, reproduction or
  transfer of this program is strictly prohibited.
*****************************************************************************/
#ifndef BUILD_CONFIGS_H
#define BUILD_CONFIGS_H


#define CC33xx

#define TNETW18xx

//Used for NSDEV Dragon compilation
#define DRAGON_NWP

//    ##################################################################################################################
//
//    #################  !!!!!!!!!!!!!!! DO NOT INCLUDE THIS FILE !!!!!!!!!!!!!!!!!!!!!!!!! ############################
//
//    ################## THIS HEADER IS ALREADY PREINCLUDED IN THE MAEKFILE FOR ALL PROJECT SOURCES ####################
//
//    #################  !!!!!!!!!!!!!!! DO NOT INCLUDE THIS FILE !!!!!!!!!!!!!!!!!!!!!!!!! ############################
//
//    ##################################################################################################################


//------------------------------------------------------------------------------------------------------------
// define CC33XX_NO_CME_TEST to disable CME tests (both manual, i.e. hard coded, and also from cme tester)
#define CC33XX_NO_CME_TEST
//-------------------------------------------- IMPORTANT NOTE ------------------------------------------------
// This means that CC33XX_NO_CME_TEST flag will probably change from one delivery to the next depending on
// the person delivering the version, as it is currently undefined by WLAN team for most of their supplicant
// tests without a WLAN interface
// and on the other hand defined by the networking team working with the WLAN interface to run traffic.
//------------------------------------------------------------------------------------------------------------
// WiLink8 MCU Attached
#define HOST_COMPILE


//Enable debug mechanisms for the cc33xx CME
//#define CC33XX_CME_DEBUG

//open this + compile calib_agine_test.c from the test library to have
//calibration running constantly. this will make the Scheduler always running
//#define CALIB_TEST

// If this flag is defined, the new logger will be used instead of the old logger
// #define GTRACE_ENABLE
#define ENABLE_ASSERT

//endianess is removed in NAB
//#define CC33XX_NAB_ENDIANESS_DISABLED

// for osprey - we must set tx exchnage complete for each host packet.
#define ALWAYS_FORCE_EXCHANGE
// Temp. until PMAC RX HW supports STA PSD.
#define PMAC_RX_PSD_PATCH


#define INCLUDE_BGET_STATS
#define SIMPLE_LINK2_NO_INTRINSIC
#define TX_DISABLE_INLINE

//print the duration spent at each PM Mode
#define PM_MODE_TIME_STAT_DEBUG

// define modules debug level
#define TIMERS_MNG_DEBUG

//PMAC request LISTEN mode. PHY is accepting this request but for now move to RX ONLY
#define LISTEN_PHY_SUPPORT     1


//PMAC should change PHY mode according to Beacon indications.
//It is not supported yet by the FPGA version
#define PMAC_CONTROL_PHY       0

// O3 data path preparation
#define OSPREY_DATA_PATH 0
#define OSPREY_DATA_PATH_OVER_DRAGON 1

//==========================================
// TODO: to be removed before ROM version
#define DEBUG_CODE_ROM_WATCHPOINT
//==========================================

//CC33XX - we intend to not prioritize the NVICs since the OS need to do most of the job
//				  but if priorities needed - this is the right order (wrapped with this define)
//#define NVIC_PRIORITIES

//threadX flags
#define TX_INCLUDE_USER_DEFINE_FILE
//end of threadX flags

//NetX flags
//#define USE_RAW_TAP_NAB_HOST_INTERFACE
#define USE_CC33XX_WLAN_NAB_HOST_INTERFACE
//end of netX flags

//Disable SSL until crypto will be configured
#define CC33XX_DISABLE_SSL_UNTIL_CRYPTO

//Disable cc31xx HW checksum mechanism
#define CC33XX_NO_CHECKSUM_ACCELERATOR
//Disable cc31xx RX filters
#define CC33XX_NO_RX_FILTERS
//Disable cc31xx transceiver mode
#define CC33XX_NO_TRANSCEIVER_MODE
//Disable cc31xx flow control
#define CC33XX_NO_FLOW_CONTROL


//Enable HOSTAP/WPA_SUPPLICANT and CME debug messages, uncomment the define below
//#define HOSTAP_AND_CME_ENABLE_DEBUG
#ifndef HOSTAP_AND_CME_ENABLE_DEBUG
//in case HOSTAP_AND_CME_ENABLE_DEBUG is enabled, you will need to reduce the code size
//by temporarily remove unused functionality
#define CONFIG_NO_STDOUT_DEBUG
#else
#define CONFIG_DEBUG_SYSLOG

// Determine the HOSTAP log level, e.g. MSG_EXCESSIVE for full logs
#define WPA_DEBUG_LEVEL MSG_DEBUG // MSG_DEBUG //MSG_EXCESSIVE /MSG_INFO

// Enable GTRACE for CME debug messages
//#define GTRACE_ENABLE
#endif

/*********** DISABLE IPv6 - Eran Harary ******************************/
/*********************************************************************/
//CC33xx disable ipv6 for now
//#define NX_DISABLE_IPV6    //Eran Harary - Enable this flag in order to operate IPv6

//#ifndef NX_DISABLE_IPV6
//Disable Tx Fast Path (should be commented out by default)
#define CC33XX_NO_TX_FAST_PATH    //Eran Harary - ipv6 development
//#endif
/*********************************************************************/

#define CC33XX_NO_TX_FAST_PATH_IPV6    //eran harary fast path: define

//
//cc33xx Dec 31 2015 - Last comment for year 2015!!!!
//       well, rx multicast filters are not needed here as it is a single processor
//       so the filtering will be done by netx ip recieve, and the multicast
//       will be filtered according to igmp joined addresses
//       it is agreed that if we see that the processor is overloaded due to multicast packets
//       we will consider this filtering to be done in rxpp scripter
//
#define CC33XX_NO_MC_IP_FILTERS
//Disable cc31xx file system
#define CC33XX_NO_FILESYSTEM


//Disable MDNS
#define CC33XX_NO_MDNS


//Disable PRMC - Can we determine if init is from sleep or init is from hibernate for
// determining if RTC is still running
#define CC33XX_NO_PRMC_FOR_RTC


//Disable cc31xx netapps
#define CC33XX_NO_NETAPPS
//Disable DHCP client specifically
//#define CC33XX_NO_DHCP_CLIENT

//Disable cc31xx packet pools
#define CC33XX_NO_PACKET_ALLOCATION
//No multi-interface by NX (also includes netx implications of multi-role, but also ethernet, etc.)
#define CC33XX_NO_NX_MULTI_INTERFACE

// Comment out RX TCP flow control in certain places.
// This is pending implementation of the Rx path on CC33xx.
#define CC33XX_NO_RX_TCP_FLOW_CONTROL

// Comment out ARP update on Rx of IP frames.
// At the moment, this is CC31xx code which looks into Ethernet
// header. As we intend to work with WLAN L2 headers, this may change.
#define CC33XX_NO_ARP_UPDATE_ON_RX

//
// This is probably redundant - as there should not be any other choice.
// (I.e., all local application traffic via NetX BSD/proprietary socket API should be
//  forwarded to UTxP, no exceptions...).
// But for the time being, this is a 'configurable' #define.
//
#define CC33XX_NETX_VIA_UTXP


//#define NX_DISABLE_TCP_IPV6


//Eran Harary - dhcpv6: disable black list
//#define NX_DISABLE_IPV6_DHCPV6_BLACK_LIST


//CC33xx disable provisioning hooks
#define SL_DISABLE_PROVISIONING


//this is used to trck memory heep statistics such as num of alloc/free/...
//it is also used to verify that no allocations remains when going to lpds
#define SUPPORT_MEM_STATISTICS


// uncomment NX_BSD_FLAG_BITMAP_SET_CALLER_DEBUG_ENABLE to see who is the caller to nx_bsd_flag_bitmap_set
//#define NX_BSD_FLAG_BITMAP_SET_CALLER_DEBUG_ENABLE


//CC33xx disable provisioning hooks
//#define SL_DISABLE_DHCP_FAST_RENEW

//
// Raw sockets - not there yet.
//
/// #define CC33xx_RAW_PACKET_PROCESSING_SUPPORTED

//Stack overflow protection modules
#define TX_STACK_OVERFLOW_HW_ACTIVATE
#define TX_STACK_OVERFLOW_SW_ACTIVATE
//end of stack overflow protection modules

//Statistics
#define ENABLE_STATISTICS
//end of statistics

//Run Time analysis
//#define RUN_TIME_ANALYSIS_ENABLED
//for run_time_analysis - only one should be defined
#define RUN_TIME_ANALYSIS_FAST_CONNECT
//#define RUN_TIME_ANALYSIS_DATA_PATH
#if defined(RUN_TIME_ANALYSIS_FAST_CONNECT) && defined(RUN_TIME_ANALYSIS_DATA_PATH)
#error "Only one should be defined"
#endif
//end of Run Time analysis

//worker thread group enable
#define OSI_WORKING_THREAD_GROUP_ENABLE
//

#define FPGA_MODE

//I2C flags
//#define I2C_CLOCK_SUPPORT_ENABLE 1
//#define I2C_LEGACY 1

// When defined, MEM_POOL_MONIOTR enables verifying memory pools are intact before
// every memory allocation and after every memory relase operation.
// #define MEM_POOL_MONIOTR

//#define TIMERS_MNG_TESTS

//#define BRINGUP_TESTS

#define MEM_POOL_MONIOTR

#ifdef BRINGUP_TESTS
#define NVIC_PRIORITIES
#undef RUN_TIME_ANALYSIS_ENABLED

//#define BRINGUP_TEST_INCLUDE_MMU
#endif

//
//#define NETX_TESTS
//#define NETX_DHCP_TESTS
#define NETX_HTTP_TESTS
#define HDI_SCRIPTER


//--------------------------------------------------------------------


//--------------------------------------------------------------------
// comment this out for mmu cyclic buffer debug enable
//#define CYCLIC_BUFFER_DISABLE
//--------------------------------------------------------------------

#ifndef CYCLIC_BUFFER_DISABLE
//-----------------------------------------------------------------------
// selectors of HW cyclic buffer debug modes (Tx/Rx or both)
// #define CYCLIC_BUFFER_DEBUG_ENABLE_TX_HW
// #define CYCLIC_BUFFER_DEBUG_ENABLE_RX_HW
//-----------------------------------------------------------------------

//-----------------------------------------------------------------------
// cyclic buffer HW
// debug of Hw tx (HDI and PMAC) and SW tx (utxp and release)
// no defines for NAB - it currently writes everything (though currently only
// tx is implemented)
#ifdef CYCLIC_BUFFER_DEBUG_ENABLE_TX_HW
#define HDI_SCRIPTER_CYCLIC_DEBUG_ENABLE // HDI debug can be used as long as base6 (linkdb) is still not used 
#define UTXP_SW_CYCLIC_DEBUG_ENABLE
#define PMAC_TX_SCRIPTER_CYCLIC_DEBUG_ENABLE
#define RELEASE_SW_TX_CYCLIC_DEBUG_ENABLE
#endif
//-----------------------------------------------------------------------

//--------------------------------------------------------------------
// cyclic buffer HW debug of rx (RxPP and PMAC and SW release)
// no NAB writes in Rx supported yet
#ifdef CYCLIC_BUFFER_DEBUG_ENABLE_RX_HW
#define RXPP_SCRIPTER_CYCLIC_DEBUG_ENABLE // RxPP can be used as long as base6 (linkdb) is still not used 
#define PMAC_RX_SCRIPTER_CYCLIC_DEBUG_ENABLE
#define RELEASE_SW_RX_CYCLIC_DEBUG_ENABLE
#endif
//--------------------------------------------------------------------

#endif // CYCLIC_BUFFER_DISABLE

//#define SL_NX_ALLOC_DEBUG


//#define SL_NX_TIMING_DEBUG

// PMAC testing flags
#define FPGA_PMAC_TX
//#define PMAC_OLD_RX

// Enable AGC in the PHY. this configuration affect the PHY init & scripter
#define PHY_AGC

// Enable specific testing for PMAC
//#define PMAC_TX_TEST
#define PMAC_AX
// code dedicated for AX brinup / debug
#define PMAC_AX_DEBUG
//#define AX_DISABLE_OW
#define AX_DEBUG_FIXES
#define	AX_DELIVER_FIXES
#define AX_IPV6_PATCH
//#define AX_DISABLE_RX
//#define SUSPEND_DEBUG
#define BET_VALIDATION
//#define FORCE_BA_RX_SESSION
//#define PSD_DEBUG            // Please dont remove yet
//#define DEBUG_OSI_WAIT_EVENT // Please dont remove yet
//#define ABORT_INITIATE
#define ABORT_SUPPORT

//CME queue debug prints - non-operational code
//CME queue is not peotected
//use this code only for debug
//define CME_QUEUE_DEBUG

// Enable define to configure OCLA recording on cold boot
//#define OCLA_RECORD_EN
//
// Jigal - for compiling host-driver header files - need to indicate
//         that we define our own types of _u8, _u16, _u32 and their signed counterparts _i8, _i16 and _i32.
//
#define _SL_USER_TYPES
#define _SL_NWP_COMPILE

//should be defined once RTC is implemented in HW
//#define RTC_HW_AVAILABLE

//--------------------------------------------------------
// WolfSSL build configurations
#define SL_WOLFSSL_PORTING
//#define SUPPLICANT_WITH_WOLFSSL_OCSP
//#define FIXED_TLS_CONNECT_HOST_SOCKET

#ifdef SL_WOLFSSL_PORTING
//--------------------------------------------------------------------------
// define SL_WOLFSSL_BRINGUP_TESTS to compile and run wolfssl bringup tests
//#define SL_WOLFSSL_BRINGUP_TESTS
//--------------------------------------------------------------------------
#define SL_WOLFSSL_REDUCED_DATA_PATH_CONTEXT_SIZE
#define SL_RUN_FROM_NWP_SEC_SS
//#define SL_RUN_FROM_NWP_AUX_M0_SEC
#define SEC_SS_AES_HAL_IN_HW_DISABLE
#define SEC_SS_SHA_HAL_IN_HW_DISABLE
#define SEC_SS_CHACHA_HAL_IN_HW_DISABLE
#define SEC_SS_POLY_HAL_IN_HW_DISABLE
#define NWP_SEC_SS_PORTING_PD_M3
#endif
//--------------------------------------------------------
//Enable debug mechanism for the cc33xx driver
//#define CC33XX_DRIVER_DEBUG

//Temp!!!! - temporary patch for working with old Cisco APs on automation setups

//set the RSC to zero in broadcast re-key, in order to work with old AP
// this will cause us not to pass krack attack tests
#define CC33XX_DRIVER_DO_NOT_TAKE_KEY_RSC_IN_BROADCAST_SET_KEY
//--------------------------------------------------------
//WPA Supplicant Flags
#define CONFIG_TI_COMPILER
#define CONFIG_DRIVER_CC33XX
#define __BYTE_ORDER_LITTLE_ENDIAN
#define CONFIG_NO_VLAN
#define OS_NO_C_LIB_DEFINES
#define CONFIG_AP
#define NEED_AP_MLME
#define CONFIG_IEEE80211N
#define CONFIG_IEEE80211AX
#define CONFIG_IEEE80211AC
#define CONFIG_NO_RADIUS
#define CONFIG_NO_ACCOUNTING
#define CONFIG_GAS
#define CONFIG_SAE
#define CONFIG_SME
#define NO_SYS_TYPES_H
//#define CONFIG_NO_WPA_MSG
#define CONFIG_NO_HOSTAPD_LOGGER
#define CONFIG_NO_VLAN
#define CONFIG_NO_RANDOM_POOL
#define CONFIG_P2P
#define CONFIG_WPS
#define CONFIG_OFFCHANNEL
//#define CONFIG_WPS2
//WPS registrar is currently not supported and is compiled out for code reduction (part of it)
#define CONFIG_WPS_REGISTRAR
//#define EAP_SERVER
#define IEEE8021X_EAPOL
#define EAP_WSC
#define EAP_TLS
#define EAP_TTLS
#define EAP_GTC
#define EAP_MSCHAPv2
//#define EAP_PSK
#define EAP_PEAP
//#define EAP_FAST
//#define EAP_GPSK
//#define EAP_GPSK_SHA256


#define CONFIG_SHA256
#define CONFIG_SHA384
#define CONFIG_DES
#define CONFIG_SUITEB
#define CONFIG_SUITEB192

#undef CONFIG_NO_CONFIG_BLOBS
#undef CONFIG_BACKEND_FILE

//management frame protection
#define CONFIG_IEEE80211W


//Use internal security lib
#define CONFIG_TLS_INTERNAL_CLIENT
#define LTM_FAST
#define CONFIG_CRYPTO_INTERNAL
#define WOLFSSL_KEY_GEN
#define CONFIG_ECC
#define EAP_SERVER_IDENTITY
#define EAP_SERVER_WSC
#define CONFIG_INTERNAL_LIBTOMMATH // Don't use internal libtomath (keep remarked), instead, use integer.h of wolfssl


//Enterprise testing
//#define EAP_DISABLED_ENTERPRISE  //TODO: Temp, till enterprise memory allocation will be handled.
                                 //             Memory for enterprise is allocated today anyway at supplicant init.
//#define EAP_USE_TEST_CERTIFICATES //Uses hard coded certificates for testing

//Disable bss loss event for enterprise
//#define DISABLE_BSS_LOSS_EVENT //Temporary - disables the BSS loss event (till wolfssl hw crypto integration)

//Supplicant uses wolfSSL crypto
//#define CONFIG_CRYPTO_WOLFSSL

//temp until pmk will be calculated by HW. it starve threads with
//lower priority as it takes several seconds. this leads connected
//STA to disconnect as beacons are not handled by LRXP.
#define PMK_SW_CONFIG_PATCH


//for windows simulation - must be true
#define FTL_COMPILE_IN_NWP_ENV                                      /* 0 - means: NWP is not compiled */

#define CONFIG_NO_RADIUS
#define CONFIG_NO_VLAN
#define CONFIG_NO_ACCOUNTING

#define CONFIG_MBO
#define CONFIG_WNM
#define CONFIG_IEEE80211R

#define CONFIG_TI_MRSNO

//TODO: enable the following supplicant flags?:
//-dHOSTAPD
//-dEAP_FAST -dCONFIG_NO_STDOUT_DEBUG -dEAP_SERVER_IDENTITY -dEAP_SERVER_WSC
//------------------------------------------------------------------------------------------

//    ##################################################################################################################
//
//    #################  !!!!!!!!!!!!!!! DO NOT INCLUDE THIS FILE !!!!!!!!!!!!!!!!!!!!!!!!! ############################
//
//    ################## THIS HEADER IS ALREADY PREINCLUDED IN THE MAEKFILE FOR ALL PROJECT SOURCES ####################
//
//    #################  !!!!!!!!!!!!!!! DO NOT INCLUDE THIS FILE !!!!!!!!!!!!!!!!!!!!!!!!! ############################
//
//    ##################################################################################################################
#endif // BUILD_CONFIGS_H

