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
#ifndef __WSPI__H__
#define __WSPI__H__

#include "osi_kernel.h"

/******************************************************************************
                                    DEFINE 
******************************************************************************/
#define WSPI_INIT_CMD_LEN       8
#define WSPI_INIT_CMD_CRC_LEN   5

#define WSPI_INIT_CMD_START         0x00
#define WSPI_INIT_CMD_TX            0x40
#define WSPI_INIT_CMD_OPS_NEGATIVE  0x08
#define WSPI_INIT_CMD_OPS_POSITIVE  0x00
#define WSPI_INIT_CMD_BYPASS_BIT    0x80 /* the extra bypass bit is sampled by the TNET as '1' */
#define WSPI_INIT_CMD_EN_FIXEDBUSY  0x80
#define WSPI_INIT_CMD_DIS_FIXEDBUSY 0x00
#define WSPI_INIT_CMD_IOD           0x40
#define WSPI_INIT_CMD_IP            0x20
#define WSPI_INIT_CMD_CS            0x10 /* CS Enabled - 0x10 ; CS Disabled - 0x00 */
#define WSPI_INIT_CMD_WS            0x08
#define WSPI_INIT_BIT_SWIZZLE       0x04
#define WSPI_INIT_CMD_WSPI          0x01
#define WSPI_INIT_CMD_END           0x01
#define WSPI_INIT_CMD_CRC_INPUT_LEN 40

/* The 31's bit in the WSPI cmd is read bit */
#define WSPI_CMD_READ                 0x40000000
#define WSPI_CMD_WRITE                0x00000000
#define WSPI_CMD_FIXED                0x20000000
#define WSPI_CMD_BYTE_LENGTH          0x1FFE0000
#define WSPI_CMD_BYTE_LENGTH_OFFSET   17
#define WSPI_CMD_BYTE_ADDR            0x0001FFFF

#define WSPI_INIT_CMD_MASK            0
#define WSPI_INIT_CMD_FBRW_MASK       0x7
#define WSPI_SIZEOF_CMD               4


/* SPI CMD 0 setting */
#define SPI_16_BIT_SUPPORT            0x1
#define SPI_FIXEDBUSY_EN              0x2
#define SPI_BIT_SWIZZLE               0x4
#define SPI_CS_BIT_CLEAN              0x8
#define SPI_DATA_POL_BIT_SET          0x10
/* SPI set CLK */  
#define SPI_SET_CLK_FREQ              0x20
/* When needed to add 1 CLK after init CMD */
#define SPI_ADD_1_CLK                 0x40



/******************************************************************************
                                    MACRO 
******************************************************************************/
/* Macro used for SPI_16_BIT only, since Init Cmd and address+Cmd should be swapped */
#define SWAP16BIT(x)      { uint32_t HighCmd = ((uint32_t)(x) >> 16) & 0xFFFF; \
                                  (x) = (((uint32_t)(x) << 16) & 0xFFFF0000) | HighCmd; }

/* Macro for deciding if to turn on the "more" flag */
#define MORE_FLAG(uCurrentTxn, uLastTxn, bMore)     ((!(uCurrentTxn ^ uLastTxn)) & bMore)



#endif // __WSPI__H__





