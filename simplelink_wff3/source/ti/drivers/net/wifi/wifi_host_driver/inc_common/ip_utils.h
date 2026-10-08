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
/**************************************************************************/
/**************************************************************************/
/**                                                                       */
/** TI Component                                  	                      */
/**                                                                       */
/**   Simple DNS Server 						                          */
/**                                                                       */
/**************************************************************************/
/**************************************************************************/

#ifndef _SL_UTILS_H
#define _SL_UTILS_H



#define NS_INT16SZ       2
#define NS_INADDRSZ     4
#define NS_IN6ADDRSZ    16

#define BYTE0(data) (data & 0xFF)
#define BYTE1(data) ((data >> 8) & 0xFF)
#define BYTE2(data) ((data >> 16) & 0xFF)
#define BYTE3(data) ((data >> 24) & 0xFF)

#define ROTATE16(data)  ( ((BYTE0(data) <<  8)) | (BYTE1(data)) )
#define ROTATE32(data)  ( ((BYTE0(data) << 24)) | ((BYTE1(data) << 16)) | ((BYTE2(data) << 8)) | (BYTE3(data)) )


int ipUtils_ConvertDecimalNumberToString(uint32_t decNum, char *destination, int numberOfDigits, int printZeros);
void ipUtils_ConvertIpFromNumber2String(
                                 /* INPUT  */  unsigned long    ipV4,     /* FFFFFF00          */
                                 /* OUTPUT */  char*            ipString  /* "xxx.yyy.zzz.ttt" */ );
void ipUtils_GetIPAddressString (char * ipString);
#ifdef COMPILE_DEAD_FUNC
int ipUtils_ConvertIpFromString2Number(
                                /* INPUT  */ char*   pStr,          /* "xxx.yyy.zzz.ttt" */
                                /* OUTPUT */ unsigned long*   ipV4  /* FFFFFF00          */ );


void ipUtils_itoa(int, char *);
char *ipUtils_SputI(int, char *);
char * ipUtils_SputI64(uint64_t num, char *buf);
char *ipUtils_SputIp1(int, char *);
#endif
#ifndef INET_ADDRSTRLEN
#define INET_ADDRSTRLEN     NS_INADDRSZ
#endif
#ifndef INET_ADDRSTRLEN
#define INET6_ADDRSTRLEN    NS_IN6ADDRSZ
#endif
#ifdef COMPILE_DEAD_FUNC
int inet_pton(int af,const char *src,void *dst);
int inet_pton4(const char *src, unsigned char *dst);
int inet_pton6(const char *src, unsigned char *dst);
#endif
int inet_ntop(int af, const void *src, void *dst, size_t size);
int inet_ntop4(const unsigned char *src, char *dst, size_t size);
int inet_ntop6(const unsigned char *src, char *dst, size_t size);

void ipUtils_StringReverse (char* s);



#endif
