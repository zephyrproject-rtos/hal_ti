/*
 * Copyright (c) 2025, Texas Instruments Incorporated
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

#ifndef ti_drivers_rcl_LRF_Platform__include
#define ti_drivers_rcl_LRF_Platform__include

#include <ti/devices/DeviceFamily.h>

#define DeviceFamily_PARENT_CC130x 98
#define DeviceFamily_PARENT_CC140x 99

#if defined(DeviceFamily_CC1308)
    #define DeviceFamily_LRF_PARENT DeviceFamily_PARENT_CC130x
#elif defined(DeviceFamily_CC1404_CC1407)
    #define DeviceFamily_LRF_PARENT DeviceFamily_PARENT_CC140x
#else
    #define DeviceFamily_LRF_PARENT DeviceFamily_PARENT
#endif

#if (DeviceFamily_LRF_PARENT == DeviceFamily_PARENT_CC23X0) || \
    (DeviceFamily_LRF_PARENT == DeviceFamily_PARENT_CC27XX)
    #include DeviceFamily_constructPath(inc/hw_types.h)
    #include DeviceFamily_constructPath(inc/hw_lrfdpbe.h)
    #include <ti/drivers/rcl/lrf/LRFLPF3.h>
    #include <ti/drivers/rcl/lrf/LRFLPF3_Interface.h>
    #include <ti/drivers/rcl/lrf/LRFLPF3_Interface_Generic.h>
#elif (DeviceFamily_PARENT == DeviceFamily_PARENT_CC283X)
    #include <ti/drivers/rcl/lrf/LRFLPF4.h>
    #include <ti/drivers/rcl/lrf/LRFLPF4_Access.h>
    #include <ti/drivers/rcl/lrf/LRFLPF4_Interface.h>
    #include <ti/drivers/rcl/lrf/LRFLPF4_Interface_Generic.h>
#endif

#ifdef DeviceFamily_CC1308
    #define BUFFER_SPLIT_SUPPORT
    #include "ti/drivers/rcl/LRFCC1308.h"
#endif

#ifdef DeviceFamily_CC1404_CC1407
    #define BUFFER_SPLIT_SUPPORT
    #include "ti/drivers/rcl/LRFCC1407.h"
#endif

#endif /* ti_drivers_rcl_LRF_Platform__include */
