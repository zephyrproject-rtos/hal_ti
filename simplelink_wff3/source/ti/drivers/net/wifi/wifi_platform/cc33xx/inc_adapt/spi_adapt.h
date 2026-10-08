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
#ifndef SPI_ADAPT_H_
#define SPI_ADAPT_H_

#ifndef OSPREY_BUILD_MX

#include <stdint.h>
/* Maximal block size in a single SPI transfer --> Firmware image load chunk size */
#define MAX_SPI_BLOCK                  (0x1000)

/******************************************************************************
                       FUNCTION
******************************************************************************/
/**
 * @brief Read SPI synchronously.
 *
 * @param data Pointer to the payload.
 * @param length Length of the payload in bytes.
 * @note when implementing this function, make sure to align
 *       the length of payload to 4 bytes (word), for example
 *       if the length is 5, the actual transaction on the bus
 *       should be 8
 * @return int 0 on success, -1 on failure.
 */
extern int spi_ReadSync(uint8_t *data, uint32_t length);

/**
 * @brief Write SPI synchronously.
 *
 * @param data Pointer to the payload.
 * @param length Length of the payload in bytes.
 * @note when implementing this function, make sure to align
 *       the length of payload to 4 bytes (word), for example
 *       if the length is 5, the actual transaction on the bus
 *       should be 8
 * @return int 0 on success, -1 on failure.
 */
extern int spi_WriteSync(uint8_t *data, uint32_t length);

/**
 * @brief Initialize the SPI interface.
 * @note this might not be needed, dependce
 *       on the spi driver of the platform
 *       in some platform there is a central driver
 *       initialization function
 */
extern void spi_Init();

#endif // OSPREY_BUILD_MX


#endif /* SPI_ADAPT_H_ */
