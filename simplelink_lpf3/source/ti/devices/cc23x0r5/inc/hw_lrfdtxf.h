/******************************************************************************
*  Filename:       hw_lrfdtxf_h
******************************************************************************
*  Copyright (c) 2021 Texas Instruments Incorporated. All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions are met:
*
*  1) Redistributions of source code must retain the above copyright notice,
*     this list of conditions and the following disclaimer.
*
*  2) Redistributions in binary form must reproduce the above copyright notice,
*     this list of conditions and the following disclaimer in the documentation
*     and/or other materials provided with the distribution.
*
*  3) Neither the name of the copyright holder nor the names of its contributors
*     may be used to endorse or promote products derived from this software
*     without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
*  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
*  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
*  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
*  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
*  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
*  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
*  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
*  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
*  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
*  POSSIBILITY OF SUCH DAMAGE.
******************************************************************************/

#ifndef __HW_LRFDTXF_H__
#define __HW_LRFDTXF_H__

//*****************************************************************************
//
// This section defines the register offsets of
// LRFDTXF component
//
//*****************************************************************************
// Data to from TXFIFO
#define LRFDTXF_O_TXD                                               0x00000000U

//*****************************************************************************
//
// Register: LRFDTXF_O_TXD
//
//*****************************************************************************
// Field:  [31:0] DATA
//
// TX FIFO data. When written the register data is pushed to the TX FIFO. When
// read, data is popped from the TX FIFO. When writing or reading this register
// the access size will determine how many bytes are pushed to or popped from
// the FIFO. It is possible to push or pop 1,2 or 4 bytes depending on the
// access being done.
#define LRFDTXF_TXD_DATA_W                                                  32U
#define LRFDTXF_TXD_DATA_M                                          0xFFFFFFFFU
#define LRFDTXF_TXD_DATA_S                                                   0U


#endif // __LRFDTXF__
