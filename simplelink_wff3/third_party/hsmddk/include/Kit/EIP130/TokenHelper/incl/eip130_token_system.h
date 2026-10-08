/* eip130_token_system.h
 *
 * Security Module Token helper functions
 * - System token related functions and definitions
 *
 * This module can convert a set of parameters into a Security Module Command
 * token, or parses a set of parameters from a Security Module Result token.
 */

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

/* -------------------------------------------------------------------------- */
/*                                                                            */
/*   Module        : DDK-130_bsd                                              */
/*   Version       : 4.1.1                                                    */
/*   Configuration : DDK_EIP130_BSD                                           */
/*                                                                            */
/*   Date          : 2023-Mar-10                                              */
/*                                                                            */
/* Copyright (c) 2014-2023 by Rambus, Inc. and/or its subsidiaries.           */
/*                                                                            */
/* Redistribution and use in source and binary forms, with or without         */
/* modification, are permitted provided that the following conditions are     */
/* met:                                                                       */
/*                                                                            */
/* 1. Redistributions of source code must retain the above copyright          */
/* notice, this list of conditions and the following disclaimer.              */
/*                                                                            */
/* 2. Redistributions in binary form must reproduce the above copyright       */
/* notice, this list of conditions and the following disclaimer in the        */
/* documentation and/or other materials provided with the distribution.       */
/*                                                                            */
/* 3. Neither the name of the copyright holder nor the names of its           */
/* contributors may be used to endorse or promote products derived from       */
/* this software without specific prior written permission.                   */
/*                                                                            */
/* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS        */
/* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT          */
/* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR      */
/* A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT       */
/* HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,     */
/* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT           */
/* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,      */
/* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY      */
/* THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT        */
/* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE      */
/* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.       */
/* -------------------------------------------------------------------------- */

#ifndef INCLUDE_GUARD_EIP130TOKEN_SYSTEM_H
#define INCLUDE_GUARD_EIP130TOKEN_SYSTEM_H

#include <third_party/hsmddk/include/Kit/DriverFramework/Basic_Defs_API/incl/basic_defs.h>             /* uint32_t, bool, inline, etc. */
#include <third_party/hsmddk/include/Kit/DriverFramework/CLib_Abstraction_API/incl/clib.h>                   /* memset */
#include <third_party/hsmddk/include/Kit/EIP130/TokenHelper/incl/eip130_token_common.h>    /* Eip130Token_Command/Result_t */

/* OTP Anomaly codes */
#define EIP130TOKEN_SYSINFO_OTP_NO_ANOMALY          0U
#define EIP130TOKEN_SYSINFO_OTP_EMPTY               1U
#define EIP130TOKEN_SYSINFO_OTP_UNSUPPORTED_SIZE    2U
#define EIP130TOKEN_SYSINFO_OTP_FAT_ERROR           3U
#define EIP130TOKEN_SYSINFO_OTP_ZEROIZED            8U


typedef struct
{
    struct
    {
        uint8_t Major;
        uint8_t Minor;
        uint8_t Patch;
        uint16_t MemorySizeInBytes;
    } Hardware;

    struct
    {
        uint8_t Major;
        uint8_t Minor;
        uint8_t Patch;
        bool fIsTestFW;
    } Firmware;

    struct
    {
        uint8_t HostID;
        uint32_t Identity;
        uint8_t NonSecure;      /* 0=Secure, !0=Non-Secure */
        uint8_t CryptoOfficer;  /* 0=Not available, !0=Available */
        uint8_t Mode;           /* 0=Active mode, 4..6=Error modes, 15=Active mode, with successful Login */
        uint8_t ErrorTest;      /* Self-test error (only valid when Fatal Error is caused by a self-test) */
    } Self;

    struct
    {
        uint8_t ErrorCode;
        uint16_t ErrorLocation;
    } OTP;

} Eip130Token_SystemInfo_t;


/*----------------------------------------------------------------------------
 * Eip130Token_Command_SystemInfo
 *
 * This function writes the System Information command token.
 *
 * CommandToken_p
 *     Pointer to the command token buffer.
 */
static inline void
Eip130Token_Command_SystemInfo(
        Eip130Token_Command_t * const CommandToken_p)
{
    CommandToken_p->W[0] = (EIP130TOKEN_OPCODE_SYSTEM |
                            EIP130TOKEN_SUBCODE_SYSTEMINFO);
}


/*----------------------------------------------------------------------------
 * Eip130Token_Result_SystemInfo
 *
 * This function parses the System Information result token. It can also
 * be used to query the (fixed) length of the firmware versions string this
 * function can generate.
 *
 * ResultToken_p
 *     Pointer to the result token buffer.
 *
 * Info_p
 *     Pointer to the information structure that this function will populate.
 */
static inline void
Eip130Token_Result_SystemInfo(
        const Eip130Token_Result_t * const ResultToken_p,
        Eip130Token_SystemInfo_t * const Info_p)
{
    uint32_t MaMiPa;

    (void)memset(Info_p, 0, sizeof(Eip130Token_SystemInfo_t));

    MaMiPa = ResultToken_p->W[1];
    Info_p->Firmware.Major = (uint8_t)(MaMiPa >> 16);
    Info_p->Firmware.Minor = (uint8_t)(MaMiPa >> 8);
    Info_p->Firmware.Patch = (uint8_t)MaMiPa;
    if ((MaMiPa & BIT_31) != 0U)
    {
        Info_p->Firmware.fIsTestFW = true;
    }

    MaMiPa = ResultToken_p->W[2];
    Info_p->Hardware.Major = (uint8_t)(MaMiPa >> 16);
    Info_p->Hardware.Minor = (uint8_t)(MaMiPa >> 8);
    Info_p->Hardware.Patch = (uint8_t)MaMiPa;

    Info_p->Hardware.MemorySizeInBytes = (uint16_t)ResultToken_p->W[3];

    Info_p->Self.HostID = (uint8_t)((ResultToken_p->W[3] >> 16) & MASK_4_BITS);
    Info_p->Self.Identity = ResultToken_p->W[4];
    Info_p->Self.NonSecure = (uint8_t)((ResultToken_p->W[3] >> 19) & MASK_1_BIT);
    Info_p->Self.CryptoOfficer = (uint8_t)((ResultToken_p->W[3] >> 27) & MASK_1_BIT);
    Info_p->Self.Mode = (uint8_t)((ResultToken_p->W[3] >> 28) & MASK_4_BITS);
    Info_p->Self.ErrorTest = (uint8_t)((ResultToken_p->W[5] >> 16) & MASK_8_BITS);
    
    Info_p->OTP.ErrorCode = (uint8_t)((ResultToken_p->W[5] >> 12) & MASK_4_BITS);
    Info_p->OTP.ErrorLocation = (uint16_t)(ResultToken_p->W[5] & MASK_12_BITS);
}


/*----------------------------------------------------------------------------
 * Eip130Token_Command_SystemSelfTest
 *
 * This function writes the Self Test command token, with which the self test
 * can be selected manually.
 *
 * CommandToken_p
 *     Pointer to the command token buffer.
 */
static inline void
Eip130Token_Command_SystemSelfTest(
        Eip130Token_Command_t * const CommandToken_p)
{
    CommandToken_p->W[0] = (EIP130TOKEN_OPCODE_SYSTEM |
                            EIP130TOKEN_SUBCODE_SELFTEST);
}

/*----------------------------------------------------------------------------
 * Eip130Token_Command_SystemLogin
 *
 * This function writes the Login command token.
 * To comply with the FIPS140-3 requirement that operations in �FIPS-Approved
 * mode� can only be invoked by an authenticated user (or role), the Login
 * Token must be run after each hard reset or power-cycle before any other
 * Token can be used
 *
 * CommandToken_p
 *     Pointer to the command token buffer.
 */
static inline void
Eip130Token_Command_SystemLogin(
        Eip130Token_Command_t * const CommandToken_p)
{
    CommandToken_p->W[0] = (EIP130TOKEN_OPCODE_SYSTEM |
                            EIP130TOKEN_SUBCODE_LOGIN);
}


/*----------------------------------------------------------------------------
 * Eip130Token_Command_Reset
 *
 * This function writes the Reset command token, with which a software wise
 * reset of the firmware can be performed.
 *
 * CommandToken_p
 *     Pointer to the command token buffer.
 */
static inline void
Eip130Token_Command_SystemReset(
        Eip130Token_Command_t * const CommandToken_p)
{
    CommandToken_p->W[0] = (EIP130TOKEN_OPCODE_SYSTEM |
                            EIP130TOKEN_SUBCODE_RESET);
}


#ifdef EIP130_ENABLE_FIRMWARE_SLEEP
/*----------------------------------------------------------------------------
 * Eip130Token_Command_SystemSleep
 *
 * This function writes the Sleep command token, with which the HW (EIP-130)
 * is placed in sleep mode.
 *
 * CommandToken_p
 *     Pointer to the command token buffer.
 */
static inline void
Eip130Token_Command_SystemSleep(
        Eip130Token_Command_t * const CommandToken_p)
{
    CommandToken_p->W[0] = (EIP130TOKEN_OPCODE_SYSTEM |
                            EIP130TOKEN_SUBCODE_SLEEP);
}


/*----------------------------------------------------------------------------
 * Eip130Token_Command_SystemResumeFromSleep
 *
 * This function writes the Resume From Sleep command token, with which the
 * HW (EIP-130) resumed to normal operation coming out of sleep mode.
 *
 * CommandToken_p
 *     Pointer to the command token buffer.
 */
static inline void
Eip130Token_Command_SystemResumeFromSleep(
        Eip130Token_Command_t * const CommandToken_p)
{
    CommandToken_p->W[0] = (EIP130TOKEN_OPCODE_SYSTEM |
                            EIP130TOKEN_SUBCODE_RESUMEFROMSLEEP);
}
#endif


#endif /* INCLUDE_GUARD_EIP130TOKEN_SYSTEM_H */

/* end of file eip130_token_system.h */
