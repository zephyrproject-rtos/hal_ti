/* adapter_bufmanager.h
 *
 * Buffer Manager intended for EIP-130 tokens.
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

#ifndef INCLUDE_GUARD_ADAPTER_BUFMANAGER_H
#define INCLUDE_GUARD_ADAPTER_BUFMANAGER_H


/*----------------------------------------------------------------------------
 * This module implements (provides) the following interface(s):
 */


/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */
#include <third_party/hsmddk/include/Kit/DriverFramework/CLib_Abstraction_API/incl/clib.h>                   // size_t
#include <third_party/hsmddk/include/Kit/DriverFramework/Basic_Defs_API/incl/basic_defs.h>             // uint32_t, uint64_t

/*----------------------------------------------------------------------------
 * Definitions and macros
 */

/*----------------------------------------------------------------------------
 * BufManager_BufferType_t - Buffer type indication
 */
typedef enum
{
    BUFMANAGER_BUFFERTYPE_NOT_USED = 0,
    BUFMANAGER_BUFFERTYPE_IN,
    BUFMANAGER_BUFFERTYPE_OUT,
    BUFMANAGER_BUFFERTYPE_INOUT,
} BufManager_BufferType_t;


typedef size_t (*BufManager_CB_SizeAlignment_t)(const size_t Size);
typedef int (*BufManager_CB_CheckClear_t)(void * Buffer_p, const size_t Size, void * UserData_p);
typedef int (*BufManager_CB_CheckReady_t)(void * Buffer_p, const size_t Size, void * UserData_p);

/*----------------------------------------------------------------------------
 * Local variables
 */


/*----------------------------------------------------------------------------
 * BufManager_Register
 *
 * SizeAlignment
 *     The callback function that must be called when an output buffer is
 *     mapped to get the actual size of the buffer to map. The required
 *     buffer size can differ when a buffer ready check must performed.
 *     Note NULL is allowed.
 *
 * CheckClear
 *     The callback function that must be called when an output buffer is
 *     mapped that must be bounced.
 *     The purpose of this function is to clear (reset) the check that is
 *     performed during the CheckReady call.
 *     Note NULL is allowed.
 *
 * CheckReady
 *     The callback function that must be called when an output buffer is
 *     unmapped to check if buffer is ready to be unmapped.
 *     Note NULL is allowed.
 *
 * Return Value:
 *      0   Successful
 *     -1   An internal error occurred
 */
int32_t
BufManager_Register(
        BufManager_CB_SizeAlignment_t SizeAlignment,
        BufManager_CB_CheckClear_t CheckClear,
        BufManager_CB_CheckReady_t CheckReady);


/*----------------------------------------------------------------------------
 * BufManager_Map
 *
 * This function maps a host buffer to a physical buffer. The function will
 * do the pre-DMA operation to hand-over control to the device.
 *
 * Based on the type of the buffer the following actions will be performed:
 * IN    The host data buffer is converted to an address that is usable by a
 *       device and refers to a DMAable buffer.
 *       If the host data buffer is not DMAable, the data is copied to a newly
 *       allocated DMAable buffer (bounced).
 * OUT   The host data buffer is converted to an address that is usable by a
 *       device and refers to a DMAable data buffer.
 *       Before the a DMAable buffer is allocated, the SizeAlignment function
 *       (if given) is called to retrieve the actual required buffer size.
 *       After the DMAable buffer is allocated, the CheckClear function (if
 *       given) is called to clear the check ready area if needed.
 *       Additionally the pre-DMA operation is performed to hand-over control
 *       to the device.
 * INOUT The host data buffer is converted to an address that is usable by a
 *       device and refers to a DMAable buffer.
 *       Before the a DMAable buffer is allocated, the SizeAlignment function
 *       (if given) is called to retrieve the actual required buffer size.
 *       After the DMAable buffer is allocated, the CheckClear function (if
 *       given) is called to clear the check ready area if needed.
 *       The input data is copied to the newly allocated DMAable buffer
 *       (bounced) and additionally the pre-DMA operation is performed to
 *       hand-over control to the device.
 *
 * fFromUserSpace
 *     Indication that the host data buffer comes from the User Space.
 *
 * Type
 *     Buffer type, see above-mention information.
 *
 * Data_p
 *     Pointer to a host data buffer.
 *
 * DataSize
 *     Size of the host data buffer in bytes, will be used when data must be
 *     bounced.
 *
 * UserData_p
 *     Pointer to the caller's user buffer, which is passed on as an argument
 *     when a callback function is called.
 *     Ignored in case the buffer type is IN.
 *
 * Return Value:
 *     A physical address that can be used by an device.
 *     Note that 0 refers to memory allocation error.
 */
uint64_t
BufManager_Map(
        bool fFromUserSpace,
        BufManager_BufferType_t Type,
        const void * const Data_p,
        size_t DataSize,
        void * UserData_p);


/*----------------------------------------------------------------------------
 * BufManager_Alloc
 *
 * This function allocates a DMAable and copies the input data to that new
 * (bigger) buffer if needed. Note that NO pre-DMA operation is performed,
 * because additional data is assumed to be added to the buffer. So this
 * means that the BufManager_PreDmaAddress() must be called the device is
 * allowed to use the buffer.
 *
 * The function returns address to the physical buffer.
 * Based on the type of the buffer the following actions will be performed:
 * IN    A DMAable buffer is allocated with specified BufferSize. The data is
 *       copied to the newly allocated DMAable buffer.
 * OUT   A DMAable buffer is allocated with specified BufferSize after the
 *       SizeAlignment function (if given) is called to retrieve the actual
 *       required buffer size.
 *       After the DMAable buffer is allocated, the CheckClear function (if
 *       given) is called to clear the check ready area if needed.
 * INOUT A DMAable buffer is allocated with specified BufferSize after the
 *       SizeAlignment function (if given) is called to retrieve the actual
 *       required buffer size. The input data is copied to the newly allocated
 *       DMAable buffer.
 *       After the DMAable buffer is allocated, the CheckClear function (if
 *       given) is called to clear the check ready area if needed.
 *
 * fFromUserSpace
 *     Indication that the host data buffer comes from the User Space.
 *
 * Type
 *     Buffer type, see above-mention information.
 *
 * BufferSize
 *     Size of the buffer to allocate in bytes.
 *
 * Data_p
 *     Pointer to a host data buffer.
 *
 * DataSize
 *     Size of the host data buffer in bytes.
 *
 * UserData_p
 *     Pointer to the caller's user buffer, which is passed on as an argument
 *     when a callback function is called.
 *     Ignored in case the buffer type is IN.
 *
 * Return Value:
 *     A physical address that can be used by an device.
 *     Note that 0 refers to memory allocation error.
 */
uint64_t
BufManager_Alloc(
        bool fFromUserSpace,
        BufManager_BufferType_t Type,
        size_t BufferSize,
        const void * const Data_p,
        size_t DataSize,
        void * UserData_p);


/*----------------------------------------------------------------------------
 * BufManager_Unmap
 *
 * This function unmaps/releases a DMAable buffer.
 *
 * Based on the type of the buffer the following actions will be performed:
 * IN    The buffer is simply released.
 * OUT   If the fCopy flag is set, after a post-DMA operation the CheckReady
 *       function (if given) is called to check if all data is available in
 *       the buffer. When this is the case the data is copied to its final
 *       location when it is bounced. After the data is copied, the buffer is
 *       released.
 *       If the fCopy flag is NOT set, the buffer is simply released.
 * INOUT  See OUT buffer type description.
 *
 * BufferAddress
 *     Physical address of the DMAable buffer.
 *
 * fOutputBuffer
 *     Indication that it should be an output buffer.
 *
 * fCopy
 *     Indication to copy the data.
 *
 * ActualSize
 *     In case of fCopy==true, this argument can hold the actual size to copy.
 *     Thus, when ActualSize!=0 and fCopy==true, the specified ActualSize is
 *     used in the copy operation, otherwise (ActualSize==0) the size of the
 *     actual mapped buffer.
 *
 * Return Value:
 *      0   Successful
 *     -1   Unknown address
 *     -2   An internal error occurred
 *     -3   Data ready check timeout
 */
int32_t
BufManager_Unmap(
        uint64_t BufferAddress,
        bool fOutputBuffer,
        bool fCopy,
        size_t ActualSize);


/*----------------------------------------------------------------------------
 * BufManager_Zeroize
 *
 * This function zeroizes the DMAable buffer.
 *
 * BufferAddress
 *     Physical address of the DMAable buffer.
 *
 * Return Value: N/A
 */
void
BufManager_Zeroize(
        uint64_t BufferAddress);


/*----------------------------------------------------------------------------
 * BufManager_GetSize
 *
 * This function returns the actual size of the DMAable buffer.
 *
 * BufferAddress
 *     Physical address of the DMAable buffer.
 *
 * Return Value:
 *     0    Unknown address
 *     !=0  Size of the buffer
 */
size_t
BufManager_GetSize(
        uint64_t BufferAddress);


/*----------------------------------------------------------------------------
 * BufManager_GetHostAddress
 *
 * This function returns the host pointer from a DMAable data buffer referred
 * to by DataAddress.
 * Note: Can return an host pointer for both address types (In/Out).
 *
 * BufferAddress
 *     Address of a DMAable buffer.
 *
 * Return Value:
 *     Host pointer.
 *     Note that NULL refers to an invalid address.
 */
void *
BufManager_GetHostAddress(
        uint64_t BufferAddress);


/*----------------------------------------------------------------------------
 * BufManager_PreDmaAddress
 *
 * This function performs a pre-DMA operation.
 * Note: Only intended for an buffer that is allocated via BufManager_Alloc().
 *
 * BufferAddress
 *     Address of a DMAable buffer.
 *
 * Return Value:
 *      0   Success.
 *     -1   Failed, wrong address.
 */
int32_t
BufManager_PreDmaAddress(
        uint64_t BufferAddress);


/*----------------------------------------------------------------------------
 * BufManager_PostDmaAddress
 *
 * This function performs a post-DMA operation.
 * Note: Only intended for an buffer that is allocated via BufManager_Alloc().
 *
 * Buffer_p
 *     Pointer to the DMAable buffer.
 *
 * Return Value:
 *     N/A
 */
void
BufManager_PostDmaAddress(
        const void * const Buffer_p);


#endif /* INCLUDE_GUARD_ADAPTER_BUFMANAGER_H */

/* end of file adapter_bufmanager.h */
