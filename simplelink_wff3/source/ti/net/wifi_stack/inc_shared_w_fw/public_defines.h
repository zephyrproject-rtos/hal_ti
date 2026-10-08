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
/**********************************************************************************************************************

  FILENAME:       public_defines.h

  DESCRIPTION:    Common definitions of:
                  a. table sizes
                  b. limitations
                  etc.
                  pertaining to F/W.

***********************************************************************************************************************/
#ifndef PUBLIC_DEFINES_H
#define PUBLIC_DEFINES_H


#include <public_types.h>
#ifndef HOST_COMPILE
#include "build_configs.h"
#endif
/**********************************************************************************************************************

    Multi-role support definitions:
    ===============================

    Multi-role pertains to the ability of the F/W to act as a unit participating
    in more than 1 WLAN BSS's in a different role.

    At present, the (intended) supported roles are:

    a. BSS STA 
    b. IBSS STA
    c. AP - with links up to 4 STAs.

    In a multi-role, the supported combinations are:
    a. BSS STA + IBSS STA
    b. BSS STA + AP


    Relation to LINKS:
    ==================

    Each role comprises of a set of WLAN LINKS (WLINKS for short).

    BSS STA has only one link associated with it (we do not intend to support a connection to more than one AP at 
    a time).
    IBSS STA has 2 types of links: unicast and broadcast.
    AP STA has 3 types of links  : unicast, broadcast and global.

    The exact definitions appear below.

    +---------+---------------+----------------+-----------------------------------------------------------------+
    | Role    | Sub-role      | Multiplicity   | Description                                                     |
    +---------+---------------+----------------+-----------------------------------------------------------------+
    | BSS STA | N/A           |       1        | This is the old default role - we are a STA connected to an AP. |
    +---------+---------------+----------------+-----------------------------------------------------------------+
    |         | UNICAST       |       4        | In an IBSS, we intend to support upto 4 STA's for unicast.      |
    |         +---------------+----------------+-----------------------------------------------------------------+
    | IBSS    | BROADCAST     |       1        | IBSS has one link reserved for broadcast traffic.               |
    |         +---------------+----------------+-----------------------------------------------------------------+
    |         | GLOBAL        |       1        | Probe responses would probably go here.                         |
    +---------+---------------+----------------+-----------------------------------------------------------------+
    |         | UNICAST       |       4        | Same a IBSS # of unicast STA's to be supported.                 |
    |         +---------------+----------------+-----------------------------------------------------------------+
    | AP      | BROADCAST     |   1 x # BSS's  | Each AP BSS instance has a sepearate broadcast traffic link.    |
    |         +---------------+----------------+-----------------------------------------------------------------+
    |         | GLOBAL        |   1 x # BSS's  | Global traffic is for unicast traffic to unassociated STA's,    |
    |         |               |                | mostly relevant for WLAN link bringup (or disconnection).       |
    +---------+---------------+----------------+-----------------------------------------------------------------+
    | Other   | BA SESSIONS   |   2 Rx 2 Tx    |  Number of RX & TX allowed BA session.                          |
    +---------+---------------+----------------+-----------------------------------------------------------------+


    *NOTES:
    =======

    a. As an AP, there is a privision to support more than 1 AP BSS.

    b. Each AP BSS has its own set of global and broadcast links, separated for clarity and cleanness.

    c. Link ID: 

       Each link has its own ID. 
       At the moment, the host/driver keeps their own set of LID's, and so does the F/W.
       The host LIDs are termed HLID's, and the F/w LID's are termed FLID's.

       The F/W is in charge of translating to and from HLID <===> FLID.

***********************************************************************************************************************/


#define  SYSTEM_LINK_HLID                   (0)
//#define  MAX_NUM_SYSTEM_LINK                (1)

#define  MAX_NUM_WLAN_ROLE_IDS              (3)
/*
 * Role:   BSS STA
 * 
 * Only 1 link is needed.
 *
 */
//#define  MAX_NUM_BSS_STA_LINKS               1


/*
 * Role:   IBSS STA
 * 
 * 8 unicast links.
 * 1 broadcast link.
 * 1 global link.
 *
 */
#define  MAX_NUM_IBSS_UNICAST_STA_LINKS         10
#define  MAX_NUM_IBSS_BROADCAST_STA_LINKS       1
#define  WLINKS_MAX_NUM_IBSS_GLOBAL_STA_LINKS   1

/*
 * Role:   AP
 * 
 * 5 unicast links = # of IBSS unicast links.
 * 1 supported BSS multiplicity - leading to:
 *   1 broadcast link.
 *   1 global    link.
 *
 */

#define  MAX_NUM_AP_BSS                      1                    /* This has impact on NUMBER_OF_SECURITY_ELEMENTS       */
//#define  MAX_NUM_AP_GLOBAL_LINKS             (1 * MAX_NUM_AP_BSS) /* 1 broadcast link for each possible AP BSS instance.  */
//#define  MAX_NUM_AP_BROADCAST_LINKS          (1 * MAX_NUM_AP_BSS) /* 1 global    link for each possible AP BSS instance.  */


//Host should always see the links number without data reduction patches.
#ifdef HOST_COMPILE
//#define  MAX_NUM_AP_UNICAST_LINKS            4//MAX_NUM_IBSS_UNICAST_STA_LINKS
#define MAX_NUM_OF_AP_UNICAST_LINKS          (16)

/*
 * All: total number of WLAN links to be supported by the F/W.
 *
 * These include all __simultaneous__ roles to be supported.
 * Note that we assume that IBSS and AP have the same number of unicast links.
 *
 */
typedef enum
{
    STA_LINK = 0,
    AP_UNICAST_LINK_FIRST = 1,
    AP_UNICAST_LINK_LAST = AP_UNICAST_LINK_FIRST + MAX_NUM_OF_AP_UNICAST_LINKS - 1,
    AP_GLOBAL_LINK,
    AP_BROADCAST_LINK,
    DEVICE_GLOBAL_LINK,
    STA_2_LINK,
    MAX_LINK_NUM = STA_2_LINK,
    NUM_OF_LINKS,
    INVALID_LINK = 0xFF
}linkId_e;
//#define  MAX_NUM_LINKS                       (                                    \
//                                                     MAX_NUM_BSS_STA_LINKS        \
//                                                 +   MAX_NUM_AP_UNICAST_LINKS     \
//                                                 +   MAX_NUM_AP_GLOBAL_LINKS      \
//                                                 +   MAX_NUM_AP_BROADCAST_LINKS   \
//                                                 +   MAX_NUM_SYSTEM_LINK  )
//
//
#define  MAX_NUM_LINKS  (NUM_OF_LINKS)

#else /*************** This is FW ONLY section (data reduction for debug) ****************/

    //
    // data ram memory reduction patch for debug version - reduce to 6 --> we left with ~2K bytes free in DTA_RAM [7/11/2012 Eyaln]
    // note that the driver will not be aware to this compilation flag (NDEBUG) and there for will compile with MAX_NUM_IBSS_UNICAST_STA_LINKS
    //
    #if defined(NDEBUG)
    #define  MAX_NUM_AP_UNICAST_LINKS            MAX_NUM_IBSS_UNICAST_STA_LINKS
    #else
    #define  MAX_NUM_AP_UNICAST_LINKS            (6-2)  //30.7.12 - minus two because the stack was increased by 1K
    #endif


    #define  MAX_NUM_LINKS                       (                                    \
                                                         MAX_NUM_BSS_STA_LINKS        \
                                                     +   MAX_NUM_AP_UNICAST_LINKS     \
                                                     +   MAX_NUM_AP_GLOBAL_LINKS      \
                                                     +   MAX_NUM_AP_BROADCAST_LINKS   \
                                                     +   MAX_NUM_SYSTEM_LINK  )

#endif /*************** END of FW ONLY section (data reduction for debug) ****************/

#define  BIT_ROLE_TYPE_STA              BIT_0
#define  BIT_ROLE_TYPE_IBSS             BIT_1
#define  BIT_ROLE_TYPE_AP               BIT_2
#define  BIT_ROLE_TYPE_DEVICE           BIT_3
#define  BIT_ROLE_TYPE_P2P_CLIENT       BIT_4
#define  BIT_ROLE_TYPE_P2P_GO           BIT_5


//Other
//
// BA Sessions
#ifdef TNETW18xx
#define NUM_OF_TX_BA_SESSIONS_SUPPORTED           13
#define NUM_OF_RX_BA_SESSIONS_SUPPORTED           13
#else
#define NUM_OF_TX_BA_SESSIONS_SUPPORTED           2
#define NUM_OF_RX_BA_SESSIONS_SUPPORTED           3
#endif

#define FW_LOAD_PLT     (0xBABABEBE)
#define RX_FILTER_MAGIC_NUMBER   0xABADABAD

#endif /* PUBLIC_DEFINES_H */

