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
#include "bus_spi.h"

#include <bus_if.h>
#include "spi_adapt.h"
#include "macro_utils.h"

#if defined(__ZEPHYR__)
#undef CRC
#undef SUCCESS
#undef FAILURE
#endif

/******************************************************************************
                      INTERNAL FUNCTION 
******************************************************************************/
static uint8_t generateCRC7(uint8_t* bits, uint32_t len);
void bitSwizzle(uint8_t* pBuffer, uint32_t uLen);
int SPI_SkipBusyWords();
#define WSPI_MAX_CHUNK_SIZE (4092)



/**
 * bus_sendInitCommand
 *
 * Sends a WSPI Init command (to turn the chip over into WSPI mode)
 *
 * Params:
 *      config - A 32-bit flag for configuring WSPI mode:
 *          SPI_DATA_POL_BIT_SET = Polarity is negative (positive otherwise)
 *          SPI_FIXEDBUSY_EN = Fixed busy enabled
 *          SPI_BIT_SWIZZLE = Bit Swizzle on
 *          SPI_CS_BIT_CLEAN = CS Disabled
 *          SPI_16_BIT_SUPPORT = Word Size (WS) = 16 bits
 *      fbrw - Number of fixed-busy response words (only if SPI_FIXEDBUSY_EN)
 *
*/
uint32_t bus_AlignLength(uint32_t length)
{
    return ALIGN_TO_4_BYTE(length);
}

int bus_sendInitCommand(uint32_t config_param, uint8_t fbrw)
{
    // marking the parameter as unused to bypass 'unused parameter' warning
    (void)config_param;

    uint8_t   aCRCBuffer[WSPI_INIT_CMD_CRC_LEN];
    uint32_t uTempCmd;
    /* In order to shift init CMD by one */
    uint8_t  aTempCmd0[WSPI_INIT_CMD_LEN];
    uint32_t i;
    /* The buffer used for sending in 16-bit chunks */
    //uint16_t sendBuffer[WSPI_INIT_CMD_LEN / 2];

    uint16_t sendBuffer[WSPI_INIT_CMD_LEN / 2];
    uint8_t initCmd[WSPI_INIT_CMD_LEN];
    uint32_t config;

    /* send command 0 on the SPI lines */
    config = (SPI_DATA_POL_BIT_SET | SPI_ADD_1_CLK); // 32 bit SPI

    /*
     * Set WSPI_INIT_COMMAND
     * the data is being send from the MSB to LSB
     */
    aTempCmd0[0] = initCmd[3] = 0xff;
    aTempCmd0[1] = initCmd[2] = 0xff;
    aTempCmd0[2] = initCmd[1] = WSPI_INIT_CMD_START | WSPI_INIT_CMD_TX;
    aTempCmd0[3] = initCmd[0] = 0;
    aTempCmd0[4] = initCmd[7] = 0;
    aTempCmd0[5] = initCmd[6] = 0;
    aTempCmd0[6] = initCmd[5] = WSPI_INIT_CMD_IOD
                                          | WSPI_INIT_CMD_IP
                                          | WSPI_INIT_CMD_WSPI;

    /* if not set data bit */
    if (!(SPI_DATA_POL_BIT_SET & config))
    {
        aTempCmd0[5] = initCmd[6] = WSPI_INIT_CMD_OPS_POSITIVE;
    }
    else
    {
        aTempCmd0[5] = initCmd[6] = WSPI_INIT_CMD_OPS_NEGATIVE;
    }

    /* if Fix busy mode */
    if (SPI_FIXEDBUSY_EN & config)
    {
        aTempCmd0[5] = initCmd[6] |= (WSPI_INIT_CMD_FBRW_MASK & fbrw);
        aTempCmd0[6] = initCmd[5] |= WSPI_INIT_CMD_EN_FIXEDBUSY;
    }
    else
    {
        aTempCmd0[6] = initCmd[5] |= WSPI_INIT_CMD_DIS_FIXEDBUSY;  /* Working without fixed busy words */
    }

    /* if bit swizzle mode */
    if (SPI_BIT_SWIZZLE & config)
    {
        aTempCmd0[6] = initCmd[5] |= WSPI_INIT_BIT_SWIZZLE;
    }

    /* if not CS bit clean */
    if (!(SPI_CS_BIT_CLEAN & config))
    {
        aTempCmd0[6] = initCmd[5] |= WSPI_INIT_CMD_CS; /* a rising of the CS in the middle of a word will abort
                                                                    the command and put the 1251 SPI SM in idle. */
    } else {
        /* Clear the CS line */
    }

    /* if not work 16 bit mode */
    if(!(SPI_16_BIT_SUPPORT & config))
    {
        aTempCmd0[6] = initCmd[5] |= WSPI_INIT_CMD_WS;
    }

    /* Generate CRC7 for the command */
    aCRCBuffer[0] = initCmd[1];
    aCRCBuffer[1] = initCmd[0];
    aCRCBuffer[2] = initCmd[7];
    aCRCBuffer[3] = initCmd[6];
    aCRCBuffer[4] = initCmd[5];

    aTempCmd0[7] = initCmd[4] =
        (generateCRC7(aCRCBuffer, WSPI_INIT_CMD_CRC_INPUT_LEN) << 1)
        | WSPI_INIT_CMD_END;

    if (SPI_ADD_1_CLK & config)
    {
        /*
         * We need to add 1 CLK after init CMD.
         * We shift all init CMD by 1 bit to do that.
         */

        for (i=1; i<WSPI_INIT_CMD_LEN;++i)
        {
            if(aTempCmd0[i] & 0x80)
                aTempCmd0[i-1] |= 0x01;

            aTempCmd0[i] = aTempCmd0[i] << 1;
        }
        aTempCmd0[7] |= 0x01;

        initCmd[3] = aTempCmd0[0];
        initCmd[2] = aTempCmd0[1];
        initCmd[1] = aTempCmd0[2];
        initCmd[0] = aTempCmd0[3];
        initCmd[7] = aTempCmd0[4];
        initCmd[6] = aTempCmd0[5];
        initCmd[5] = aTempCmd0[6];
        initCmd[4] = aTempCmd0[7];
    }

    /* In case of 16 bit processor we need to swap the Init command bytes */
    uTempCmd = *(uint32_t*)initCmd;
    if (SPI_16_BIT_SUPPORT & config)
    {
        SWAP16BIT(uTempCmd)
    }
    *((uint32_t*)(initCmd)) = uTempCmd;

    uTempCmd = *(uint32_t*)(initCmd+4);
    if (SPI_16_BIT_SUPPORT & config)
    {
        SWAP16BIT(uTempCmd)
    }
    *((uint32_t*)(initCmd+4)) = uTempCmd;

    /* Convert the Init CMD into 16-bit chunks */
    sendBuffer[0] = ((uint16_t)(initCmd[1] << 8)) | (initCmd[0]);
    sendBuffer[1] = ((uint16_t)(initCmd[3] << 8)) | (initCmd[2]);
    sendBuffer[2] = ((uint16_t)(initCmd[5] << 8)) | (initCmd[4]);
    sendBuffer[3] = ((uint16_t)(initCmd[7] << 8)) | (initCmd[6]);

    return spi_WriteSync((uint8_t *)sendBuffer, 8);

}


/**
 * wspibus_sendReadCommand
 *
 * Sends a WSPI Read command
 *
 * Params:
 *      config - A 32-bit flag for WSPI configuration (see bus_sendInitCommand)
 *      data - The data buffer to read into (should be pre-allocated)
 *      length - The length of the data to read
 *      isFixed - Is the address fixed? (or incremental)
 *      flags - ignored
 *
*/
int bus_sendReadCommand(uint32_t address, uint8_t * data, uint32_t length, uint8_t isFixed, uint32_t flags)
{
    // marking the parameter as unused to bypass 'unused parameter' warning
    (void)flags;

    uint32_t uTempCmd;
    int retVal;

    /* Build the wspi command */
    uTempCmd = WSPI_CMD_READ;

    /* Set bFixedAddr */
    if (isFixed)
    {
        uTempCmd |= WSPI_CMD_FIXED;
    }

    /* Set the length */
    uTempCmd |= ((uint32_t)(length) << WSPI_CMD_BYTE_LENGTH_OFFSET) & WSPI_CMD_BYTE_LENGTH;

    /* Set the address */
    uTempCmd |= (address) & WSPI_CMD_BYTE_ADDR;


    /* Send the Read command */
    retVal = spi_WriteSync((uint8_t *)&uTempCmd, WSPI_SIZEOF_CMD);
    if (retVal < 0)
        goto out;
    retVal = SPI_SkipBusyWords();
    if (retVal < 0)
        goto out;
    retVal = spi_ReadSync(data, length);

out:
    return retVal;

}

/**
 * bus_sendWriteCommand
 *
 * Sends a WSPI Write command
 *
 * Params:
 *      config - A 32-bit flag for WSPI configuration (see bus_sendInitCommand)
 *      data - The data to write
 *      length - The length of the data
 *      isFixed - Is the address fixed? (or incremental)
 *
*/
int bus_sendWriteCommand(uint32_t address, uint8_t * data, uint32_t length, uint8_t isFixed)
{
    uint32_t uWordRound = 0;
    uint32_t uTempCmd;
    uint32_t chunkLen = 0;
    int32_t     length1 = (int32_t)length;
    int retVal = 0;

    while(length1 > 0)
    {
        chunkLen = MIN(WSPI_MAX_CHUNK_SIZE,length1);

        /* Calculate distance to 4 byte length */
        uWordRound = ((chunkLen + 3) & (~(0x3))) - chunkLen;

        /* Align the length to 4 byte length */
        chunkLen += uWordRound;

        uTempCmd = 0;

        /* Build the WSPI command */
        uTempCmd = WSPI_CMD_WRITE;

        /* Set bFixedAddr */
        if (isFixed)
        {
            uTempCmd |= WSPI_CMD_FIXED;
        }

        /* Set the length */
        uTempCmd |= (chunkLen << WSPI_CMD_BYTE_LENGTH_OFFSET) & WSPI_CMD_BYTE_LENGTH;
        /* Set the address */
        uTempCmd |= (address & WSPI_CMD_BYTE_ADDR);

        //write the command first
        retVal = spi_WriteSync((uint8_t *)&uTempCmd, WSPI_SIZEOF_CMD);
        if(retVal < 0)
            goto out;

        retVal = SPI_SkipBusyWords();
        if(retVal < 0)
             goto out;

        //write the data second
        retVal = spi_WriteSync(data, chunkLen);
        if(retVal < 0)
            goto out;

        if(!isFixed)
        {
            address += chunkLen;
        }

        data += chunkLen;
        length1 -= chunkLen;
    }

    out:
        return retVal;
}

int bus_Send_deInit()
{
    return(0);
}

/******************************************************************************
                      UTILITY FUNCTIONS
******************************************************************************/



/**
 * SPI_SkipBusyWords
 *
 * This function is used to wait for a response from the target.
 * in the CC3xxx devices the target will send 0000 0000 until there is
 * one word that has any sequence of F for example 0FFF, after consuming this word
 * by the controller, the target device is ready to send data or receive data
 *
*/
int SPI_SkipBusyWords()
{

    int32_t count=0;

    while(1)
    {
        int32_t data = 0xFFFFFFFF;

        spi_ReadSync((uint8_t *)(&data),4);
        if (data != 0)
            return 0;
        if (count++ > 10000)
        {
            Report("SPI not responsive!\r\n");
            ASSERT_GENERAL(0);
            return -1;
        }

    }
}

/**
 * generateCRC7
 * Calculates the CRC7 for the WSPI init command
 *
 * Params:
 *      bits - A string that holds the bits, in the order from the first to last.
 *      len  - The number of bits.
 *
 * Returns:
 *      uint8_t - the CRC byte
 */
static uint8_t generateCRC7(uint8_t* bits, uint32_t len)
{
    uint8_t CRC, CRC0, CRC1, CRC2, CRC3, CRC4, CRC5, CRC6;
    uint8_t bit, temp;
    uint32_t  i;

    CRC0 = CRC1 = CRC2 = CRC3 = CRC4 = CRC5 = CRC6 = 0;

    /* Calculate the CRC with the formula : G(x) = x^7 + x^3 + 1 */
    for (i = 0; i < len; i++)
    {
        bit = (bits[i / 8] & (1 << (7 - (i % 8)))) >> (7 - (i % 8));
        temp = CRC6;
        CRC6 = CRC5;
        CRC5 = CRC4;
        CRC4 = CRC3;
        CRC3 = CRC2;
        CRC2 = CRC1;
        CRC1 = CRC0;
        CRC0 = temp ^ bit;
        CRC3 = CRC0 ^ CRC3;
    }

    CRC = CRC0;
    CRC |= CRC1 << 1;
    CRC |= CRC2 << 2;
    CRC |= CRC3 << 3;
    CRC |= CRC4 << 4;
    CRC |= CRC5 << 5;
    CRC |= CRC6 << 6;

    return CRC;
}

/**
 * bitSwizzle
 *
 * Does a bit swizzle on WSPI data
 *
 * Params:
 *      bits - A string that holds the bits, in the order from the first to last.
 *      len  - The number of bits.
 *
 */
void bitSwizzle(uint8_t* pBuffer, uint32_t uLen)
{
        uint8_t  uTempData;
        uint8_t* pWorkBuffer = pBuffer;

        while ( pWorkBuffer < (pBuffer + uLen) )
        {
            uint8_t i,j;

            /* Bytes swizzle */
            uTempData          = *(pWorkBuffer);
            *(pWorkBuffer)     = *(pWorkBuffer + 3);
            *(pWorkBuffer + 3) = uTempData;
            uTempData          = *(pWorkBuffer + 1);
            *(pWorkBuffer + 1) = *(pWorkBuffer + 2);
            *(pWorkBuffer + 2) = uTempData;

            /* bit swizzle */
            for (j=0; j<4; ++j)
            {
                uTempData = 0;

                for (i=0; i < 8; ++i)
                {
                    ( *(pWorkBuffer + j) & (1 << i) ) ? uTempData |= 1 << (7-i) : 0;
                }
                *(pWorkBuffer + j) = uTempData;
            }

            pWorkBuffer += 4;
        }
}


