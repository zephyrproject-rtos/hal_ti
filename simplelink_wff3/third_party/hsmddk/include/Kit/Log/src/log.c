/* log.c
 *
 * Log implementation for specific environment
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

#define LOG_SEVERITY_MAX  LOG_SEVERITY_NO_OUTPUT

// Logging API
#include <third_party/hsmddk/include/Kit/Log/incl/log.h>            // the API to implement


/*----------------------------------------------------------------------------
 * Log_HexDump
 *
 * This function logs Hex Dump of a Buffer
 *
 * szPrefix
 *     Prefix to be printed on every row.
 *
 * PrintOffset
 *     Offset value that is printed at the start of every row. Can be used
 *     when the byte printed are located at some offset in another buffer.
 *
 * Buffer_p
 *     Pointer to the start of the array of bytes to hex dump.
 *
 * ByteCount
 *     Number of bytes to include in the hex dump from Buffer_p.
 *
 * Return Value
 *     None.
 */
#ifndef LOG_REMOVE_HEXDUMP
void
Log_HexDump(
        const char * szPrefix_p,
        const uint32_t PrintOffset,
        const uint8_t * Buffer_p,
        const uint32_t ByteCount)
{
    uint32_t i;

    for(i = 0; i < ByteCount; i += 16U)
    {
        uint32_t j, Limit;

        // if we do not have enough data for a full line
        if ((i + 16U) > ByteCount)
        {
            Limit = ByteCount - i;
        }
        else
        {
            Limit = 16U;
        }

        Log_FormattedMessage("%s %08d:", szPrefix_p, PrintOffset + i);

        for (j = 0; j < Limit; j++)
        {
            Log_FormattedMessage(" %02X", Buffer_p[i+j]);
        }

        Log_FormattedMessage("\n");
    }
}
#endif


/*----------------------------------------------------------------------------
 * Log_HexDump32
 *
 * This function logs Hex Dump of an array of 32-bit words
 *
 * szPrefix
 *     Prefix to be printed on every row.
 *
 * PrintOffset
 *     Offset value that is printed at the start of every row. Can be used
 *     when the byte printed are located at some offset in another buffer.
 *
 * Buffer_p
 *     Pointer to the start of the array of 32-bit words to hex dump.
 *
 * Word32Count
 *     Number of 32-bit words to include in the hex dump from Buffer_p.
 *
 * Return Value
 *     None.
 */
#ifndef LOG_REMOVE_HEXDUMP32
void
Log_HexDump32(
        const char * szPrefix_p,
        const uint32_t PrintOffset,
        const uint32_t * Buffer_p,
        const uint32_t Word32Count)
{
    uint32_t i;

    for(i = 0; i < Word32Count; i += 4U)
    {
        uint32_t j, Limit;

        // if we do not have enough data for a full line
        if ((i + 4U) > Word32Count)
        {
            Limit = Word32Count - i;
        }
        else
        {
            Limit = 4U;
        }

        Log_FormattedMessage("%s %08d:", szPrefix_p, PrintOffset + (i * 4U));

        for (j = 0; j < Limit; j++)
        {
            Log_FormattedMessage(" %08X", Buffer_p[i+j]);
        }

        Log_FormattedMessage("\n");
    }
}
#endif

/*----------------------------------------------------------------------------
 * Log_FormattedMessage
 *
 * This function allows a message to be composed and output using a format
 * specifier in line with printf. Caller should be restrictive in the format
 * options used since not all platforms support all exotic variants.
 *
 * szFormat_p
 *     Pointer to the zero-terminated format specifier string.
 *
 * ...
 *     Variable number of additional arguments. These will be processed
 *     according to the specifiers found in the format specifier string.
 *
 * Return Value
 *     None.
 */
#ifndef Log_FormattedMessage
void
Log_FormattedMessage(
        const char * szFormat_p,
        ...)
{

}
#endif

/* end of file log.c */
