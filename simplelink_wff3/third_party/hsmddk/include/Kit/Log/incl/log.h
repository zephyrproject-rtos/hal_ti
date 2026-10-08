/* log.h
 *
 * Logging API
 *
 * The service provided by this interface allows the caller to output trace
 * messages. The implementation can use whatever output channel is available
 * in a specific environment.
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

#ifndef INCLUDE_GUARD_LOG_H
#define INCLUDE_GUARD_LOG_H

// Driver Framework Basic Defs API
#include <third_party/hsmddk/include/Kit/DriverFramework/Basic_Defs_API/incl/basic_defs.h>

// Disable dump functions
//#define LOG_REMOVE_HEXDUMP
#define LOG_REMOVE_HEXDUMP32


/*----------------------------------------------------------------------------
 * LOG_SEVERITY_MAX
 *
 * This preprocessor symbol is used to control the definition of three macros
 * that can be used to selectively compile three classes of log messages:
 * Informational, Warnings and Critical. Define this symbol before including
 * this header file. When absent, full logging is assumed.
 */

// set LOG_SEVERITY_MAX to one of the following values
#define LOG_SEVERITY_NO_OUTPUT  0
#define LOG_SEVERITY_CRIT       1
#define LOG_SEVERITY_CRITICAL   1
#define LOG_SEVERITY_WARN       2
#define LOG_SEVERITY_WARNING    2
#define LOG_SEVERITY_INFO       3

#ifndef LOG_SEVERITY_MAX
#define LOG_SEVERITY_MAX  LOG_SEVERITY_NO_OUTPUT
#endif


/*----------------------------------------------------------------------------
 * LOG_CRIT_ENABLED
 * LOG_WARN_ENABLED
 * LOG_INFO_ENABLED
 *
 * This preprocessor symbols can be used to test if a specific class of log
 * message has been enabled by the LOG_SEVERITY_MAX selection.
 *
 * Example usage:
 *
 * #ifdef LOG_SEVERITY_INFO
 *   dump command descriptor details to log
 * #endif
 */

#if LOG_SEVERITY_MAX >= LOG_SEVERITY_CRITICAL
#define LOG_CRIT_ENABLED
#endif

#if LOG_SEVERITY_MAX >= LOG_SEVERITY_WARNING
#define LOG_WARN_ENABLED
#endif

#if LOG_SEVERITY_MAX >= LOG_SEVERITY_INFO
#define LOG_INFO_ENABLED
#endif

#define Log_FormattedMessageINFO  Log_FormattedMessage
#define Log_FormattedMessageWARN  Log_FormattedMessage
#define Log_FormattedMessageCRIT  Log_FormattedMessage


/*----------------------------------------------------------------------------
 * Log_Message
 *
 * This function adds a simple constant message to the log buffer.
 *
 * Message_p
 *     Pointer to the zero-terminated log message. The message must be
 *     complete and terminated with a newline character ("\n"). This avoids
 *     blending of partial messages.
 *
 * Return Value
 *     None.
 */
#ifndef Log_Message
void
Log_Message(
        const char * szMessage_p);
#endif


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
        const uint32_t ByteCount);
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
        const uint32_t Word32Count);
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
        ...);
#endif


/*----------------------------------------------------------------------------
 * LOG_CRIT
 * LOG_WARN
 * LOG_INFO
 *
 * These three helper macros can be used to conditionally compile code that
 * outputs log messages and make the actual log line more compact.
 * Each macro is enabled when the class of messages is activated with the
 * LOG_SEVERITY_MAX setting.
 *
 * Example usage:
 *
 * LOG_INFO("MyFunc: selected mode %u (%s)\n", mode, Mode2Str[mode]);
 *
 * LOG_INFO("MyFunc: "
 *          "selected mode %u (%s)\n",
 *          mode,
 *          Mode2Str[mode]);
 *
 * LOG_WARN("MyFunc: Unexpected return value %d\n", res);
 */

#undef LOG_CRIT

#ifdef LOG_CRIT_ENABLED
#define LOG_CRIT Log_FormattedMessageCRIT
#else
#define LOG_CRIT(...)
#endif

#undef LOG_WARN
#ifdef LOG_WARN_ENABLED
#define LOG_WARN Log_FormattedMessageWARN
#else
#define LOG_WARN(...)
#endif

#undef LOG_INFO
#ifdef LOG_INFO_ENABLED
#define LOG_INFO Log_FormattedMessageINFO
#else
#define LOG_INFO(...)
#endif


#endif /* INCLUDE_GUARD_LOG_H */

/* end of file log.h */
