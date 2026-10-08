/* psa_key_store.c
 *
 * Implementation of the PSA key storage functions.
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

#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/c_adapter_psa.h>              // configuration
#include <third_party/hsmddk/include/Kit/DriverFramework/Basic_Defs_API/incl/basic_defs.h>
#include <third_party/hsmddk/include/Kit/Log/incl/log.h>
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/psa_key_store.h>
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/adapter_psa_internal.h>


/*----------------------------------------------------------------------------
 * psaInt_KeyStore_VolatileAlloc
 */
uint8_t *
psaInt_KeyStore_VolatileAlloc(size_t Size)
{
    uint8_t * pReference = (uint8_t *)Adapter_Alloc((uint32_t)Size);
    return pReference;
}


/*----------------------------------------------------------------------------
 * psaInt_KeyStore_VolatileFree
 */
void
psaInt_KeyStore_VolatileFree(uint8_t * pReference)
{
    Adapter_Free(pReference);
}


/*----------------------------------------------------------------------------
 * psaInt_KeyStore_PersistentInfo
 */
psa_status_t
psaInt_KeyStore_PersistentInfo(psa_storage_uid_t UId,
                               struct psa_storage_info_t * pInfo)
{
    return psa_its_get_info(UId, pInfo);
}


/*----------------------------------------------------------------------------
 * psaInt_KeyStore_PersistentRead
 */
psa_status_t
psaInt_KeyStore_PersistentRead(psa_storage_uid_t UId,
                               size_t ReadSize,
                               void * pData,
                               size_t * pDataSize)
{
    return psa_its_get(UId, 0U, ReadSize, pData, pDataSize);
}

/*----------------------------------------------------------------------------
 * psaInt_KeyStore_PersistentWrite
 */
psa_status_t
psaInt_KeyStore_PersistentWrite(psa_storage_uid_t UId,
                                size_t DataSize,
                                const void * pData)
{
    return psa_its_set(UId, DataSize, pData, PSA_STORAGE_FLAG_NONE);
}


/*----------------------------------------------------------------------------
 * psaInt_KeyStore_PersistentRelease
 */
psa_status_t
psaInt_KeyStore_PersistentRelease(psa_storage_uid_t UId)
{
    return psa_its_remove(UId);
}


/* end of file psa_key_store.c */
