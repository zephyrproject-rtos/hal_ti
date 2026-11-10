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

  FILENAME:       public_share.h

  DESCRIPTION:    Basic types and macros definitions.

  ----------------------------------------------------------------------------- */
#ifndef LOWER_MAC_IF_SHARED_PUBLIC_SHARE_H_
#define LOWER_MAC_IF_SHARED_PUBLIC_SHARE_H_

#include "public_defines.h"

#ifndef CC33xx // WiLink8 headers //TODO need to be removed
#ifdef TNETW18xx // WiLink8 headers
#include "init_wl18xx.h"
#include "wl18xx_public_commands.h"
#include "wl18xx_public_descriptors.h"
#include "wl18xx_public_radio.h"
#include "wl18xx_public_infoele.h"
#include "wl18xx_public_event_mbox.h"
#endif
#else // Osprey headers

#define NUM_TX_DESCRIPTORS  60      /* Total number of Tx descriptors in the FW */

#include <cc3xxx_public_commands.h>
#include <inc_common_fw/cc3xxx_public_data_path.h>
#include <inc_common_fw/cc3xxx_public_event.h>
//#include <inc_common_fw/cc3xxx_public_host_if.h>
#endif



#endif /* LOWER_MAC_IF_SHARED_PUBLIC_SHARE_H_ */
