/* adapter_vex_identity.c
 *
 * Implementation of the VEX API.
 *
 * This file implements the identity related functionality.
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

#include <third_party/hsmddk/include/Integration/Adapter_VEX/incl/c_adapter_vex.h>          // configuration

#include <third_party/hsmddk/include/Kit/DriverFramework/Basic_Defs_API/incl/basic_defs.h>
#include <third_party/hsmddk/include/Kit/DriverFramework/CLib_Abstraction_API/incl/clib.h>
#include <third_party/hsmddk/include/Kit/Log/incl/log.h>

#include <third_party/hsmddk/include/Integration/Adapter_Generic/incl/adapter_getpid.h>
#include <third_party/hsmddk/include/Integration/Adapter_VEX/incl/adapter_vex_internal.h>   // API implementation

#define VEX_IDENTITY_MAX_USERS 4
#define VEX_IDENTITY_CO_INDEX  VEX_IDENTITY_MAX_USERS

static uint32_t crypto_officer_id = (uint32_t)VEX_CRYPTO_OFFICER_ID;

struct vex_identity
{
   int32_t  ProcessId;
   uint32_t Identity;
};

static struct vex_identity gl_Identities[VEX_IDENTITY_MAX_USERS + 1] =
{
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, VEX_CRYPTO_OFFICER_ID }
};

/*----------------------------------------------------------------------------
 * vex_IdentityUserAdd
 *
 * This function adds the process id from the calling process to identified a
 * user.
 *
 * Return Value:
 *     -
 */
uint32_t
vex_IdentityUserAdd(void);


/*----------------------------------------------------------------------------
 * vex_IdentityUserRemove
 *
 * This function removes the process id from the calling process (user).
 *
 * Return Value:
 *     -
 */
void
vex_IdentityUserRemove(void);


/*----------------------------------------------------------------------------
 * vex_IdentityGet
 */
uint32_t
vex_IdentityGet(void)
{
    uint32_t identity = 0;

    if (vex_DeviceIsSecureConnected())
    {
        identity = crypto_officer_id;
    }
    else
    {
        identity = ((uint32_t)VEX_CRYPTO_OFFICER_ID ^ 0xFFFFFFFFU);
    }
    return identity;
}

/*----------------------------------------------------------------------------
 * vex_IdentityCryptoOfficer
 */
void
vex_IdentityCryptoOfficer(
        uint32_t CryptoOfficerId)
{
    gl_Identities[VEX_IDENTITY_CO_INDEX].ProcessId = Adapter_GetPid();

    crypto_officer_id = CryptoOfficerId;

    gl_Identities[VEX_IDENTITY_CO_INDEX].Identity = CryptoOfficerId;

    LOG_CRIT(VEX_LOG_PREFIX "Set CryptoOfficerId: Process ID=0x%x (%u)\n",
             gl_Identities[VEX_IDENTITY_CO_INDEX].ProcessId,
             gl_Identities[VEX_IDENTITY_CO_INDEX].Identity);
}


/*----------------------------------------------------------------------------
 * vex_IdentityUserAdd
 */
uint32_t
vex_IdentityUserAdd(void)
{
    static uint32_t gl_IdentityRef = 0x1;
    int32_t local_pid = Adapter_GetPid();
    uint32_t identity = 0;
    uint32_t i;

    for (i = 0U; i < (uint32_t)VEX_IDENTITY_MAX_USERS; i++)
    {
        if (gl_Identities[i].ProcessId == local_pid)
        {
            identity = gl_Identities[i].Identity;
            break;
        }
    }
    if (identity == 0U)
    {
        // Add process if not known
        // Note: Setting of Crypto Officer pid requires
        gl_IdentityRef++;
        gl_IdentityRef = (uint32_t)(gl_IdentityRef & 0x0FFFFFFFU);
        if (gl_IdentityRef == 0U)
        {
            gl_IdentityRef = 0x1;
        }
        for (i = 0U; i < (uint32_t)VEX_IDENTITY_MAX_USERS; i++)
        {
            if (gl_Identities[i].ProcessId == 0)
            {
                gl_Identities[i].ProcessId = local_pid;
                identity = (uint32_t)((gl_IdentityRef << 4) + i);
                gl_Identities[i].Identity = identity;

                LOG_CRIT(VEX_LOG_PREFIX "Add User%u: Process ID=0x%x (%u)\n",
                         i+1U,
                         gl_Identities[i].ProcessId,
                         gl_Identities[i].Identity);
                break;
            }
        }
        if (identity == 0U)
        {
            LOG_CRIT(VEX_LOG_PREFIX "FAILED to add User - No free entry\n");
        }
    }

    return identity;
}


/*----------------------------------------------------------------------------
 * vex_IdentityUserRemove
 */
void
vex_IdentityUserRemove(void)
{
    int32_t local_pid = Adapter_GetPid();
    int32_t i;

    for (i = 0; i < VEX_IDENTITY_MAX_USERS; i++)
    {
        if (gl_Identities[i].ProcessId == local_pid)
        {
            gl_Identities[i].ProcessId = 0;
            gl_Identities[i].Identity = 0;

            LOG_CRIT(VEX_LOG_PREFIX "Remove User%u: Process ID=0x%x\n",
                     i+1, local_pid);
            break;
        }
    }
}

/* end of file adapter_vex_identity.c */
