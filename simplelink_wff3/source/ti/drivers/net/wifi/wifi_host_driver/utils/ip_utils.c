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
/**   Common Utils		 						                          */
/**                                                                       */
/**************************************************************************/
/**************************************************************************/
#include "osi_kernel.h"
#include "osi_type.h"
#include "ip_utils.h"
#include "osi_network.h"


/**************************************************************************/
/*                                                                        */
/*  FUNCTION                                               RELEASE        */
/*                                                                        */
/*    ipUtils_ConvertDecimalNumberToString                        PORTABLE C      */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function converts Decimal number into an ASCII string.         */
/*    currently supporting only 2 and 3 digits                            */
/*  INPUT                                                                 */
/*                                                                        */
/*    decNum                                The Decimal number to convert */
/*    destination                           Pointer to destination string */
/*    numberOfDigits                         number of digits to convert  */
/*    printZeros                            Add zeros before the number   */
/*                                                                        */
/**************************************************************************/
int ipUtils_ConvertDecimalNumberToString(uint32_t decNum, char *destination, int numberOfDigits, int printZeros)
{
    int i;
    unsigned char digit_1, digit_2, digit_3, digit_4;
    int strIndex = 0;


    for (i = 0; i < numberOfDigits; i++)
    {
        destination[i] = ' ';
    }

    
    if (4 == numberOfDigits)
    {
        digit_1 = decNum / 1000;
        if (printZeros || digit_1)
        {
            destination[strIndex] = digit_1 + 0x30;
            strIndex++;
        }
        digit_2 = (decNum - (digit_1 * 1000)) / 100;
        if (printZeros || digit_2 || digit_1 )
        {
            destination[strIndex] = digit_2 + 0x30;
            strIndex++;
        }
        digit_3 = (decNum - (digit_2 * 100) - (digit_1 * 1000)) / 10;
        if (printZeros || digit_3 || digit_2 || digit_1)
        {
            destination[strIndex] = digit_3 + 0x30;
            strIndex++;
        }

        digit_4 = (decNum - (digit_1 * 1000) - (digit_2 * 100) - (digit_3 * 10));
        destination[strIndex] = digit_4 + 0x30;
        strIndex++;
    }
    else if (3 == numberOfDigits)
    {
        digit_1 = decNum / 100;
        if (printZeros || digit_1)
        {
            destination[strIndex] = digit_1 + 0x30;
            strIndex++;
        }
        digit_2 = (decNum - digit_1 * 100) / 10;
        if (printZeros || digit_2 || digit_1)
        {
            destination[strIndex] = digit_2 + 0x30;
            strIndex++;
        }

        digit_3 = (decNum - digit_1 * 100 - digit_2 * 10);
        destination[strIndex] = digit_3 + 0x30;
        strIndex++;
    }
    else
    {
        digit_1 = decNum / 10;
        if (printZeros || digit_1)
        {
            destination[0] = digit_1 + 0x30;
            strIndex++;
        }

        digit_2 = decNum - digit_1 * 10;
        destination[1] = digit_2 + 0x30;
        strIndex++;
    }

    return strIndex; // return the size of the string

}

#ifdef DEBUG_IP
void ipUtils_ConvertIpFromNumber2String(
                                 /* INPUT  */  unsigned long    ipV4,     /* FFFFFF00          */
                                 /* OUTPUT */  char*            ipString  /* "xxx.yyy.zzz.ttt" */ )
{
    int stringLength, stringIndex = 0;
	

    stringLength = ipUtils_ConvertDecimalNumberToString((ipV4 >> 24) & 0xFF, &ipString[stringIndex], 3, 0);
    stringIndex += stringLength;
    ipString[stringIndex] = '.';
    stringIndex++;
    stringLength = ipUtils_ConvertDecimalNumberToString((ipV4 >> 16) & 0xFF, &ipString[stringIndex], 3, 0);
    stringIndex += stringLength;
    ipString[stringIndex] = '.';
    stringIndex++;
    stringLength = ipUtils_ConvertDecimalNumberToString((ipV4 >> 8) & 0xFF, &ipString[stringIndex], 3, 0);
    stringIndex += stringLength;
    ipString[stringIndex] = '.';
    stringIndex++;
    stringLength = ipUtils_ConvertDecimalNumberToString((ipV4) & 0xFF, &ipString[stringIndex], 3, 0);
    stringIndex += stringLength;
    ipString[stringIndex] = '\0';
}

/* Get IP address in string format
   Current implementation is IPV4. Need future support for IPV6 */
int ipUtils_ConvertIpFromString2Number(
                                /* INPUT  */ char*   pStr,          /* "xxx.yyy.zzz.ttt" */
                                /* OUTPUT */ unsigned long*   ipV4  /* FFFFFF00          */ )
{
    UINT32 tempFull = 0, tempNum;
    int returnError = 0;
    int numberSize = 0, stringCnt = 0;


	*ipV4 = 0;
	
    while (0 != *pStr)
    {
        if (*pStr != '.')
        {
            numberSize++;
            tempNum = *pStr - 0x30; // numbers only
            if (*pStr < 0x30 || *pStr > 0x39 || numberSize > 3)
            {
                returnError = -1;
                break; //Error - invalid input
            }
            tempFull *= 10;
            tempFull += tempNum;
        }
        else
        {
            if(tempFull >= 256)
	    {
                returnError = -1; // Don't update the IPCONFIG file
                break; //Error - invalid input
	    }
            numberSize = 0;
            *ipV4 += tempFull;
            *ipV4 = *ipV4 << 8;
            stringCnt++; // another sanity check - we should have 4 numbers
            tempFull = 0;
        }

        pStr++;
    }
    // For the last string
    if(tempFull >= 256)
    {
        returnError = -1;
    }
    
    *ipV4 += tempFull;
    stringCnt++; // another sanity check - we should have 4 numbers

    if (stringCnt != 4 || 0 != returnError)
    {
        returnError = -1;
    }

    return returnError;
}
#endif

int inet_ntop4(const unsigned char *src, char *dst, size_t size)
{
    const char *fmt = "%u.%u.%u.%u";
    char tmp[sizeof "255.255.255.255"];

    if ( (size_t)sprintf(tmp, fmt, src[0], src[1], src[2], src[3]) >= size )
    {
        return 0;
    }
    strcpy(dst, tmp);

    return 1;
}

int inet_ntop6(const unsigned char *src, char *dst, size_t size)
{
    /*
     * Note that int32_t and int16_t need only be "at least" large enough
     * to contain a value of the specified size.  On some systems, like
     * Crays, there is no such thing as an integer variable with 16 bits.
     * Keep this in mind if you think this function should have been coded
     * to use pointer overlays.  All the world's not a VAX.
     */
    char tmp[sizeof "ffff:ffff:ffff:ffff:ffff:ffff:255.255.255.255"], *tp;
    struct
    {
        int base, len;
    } best, cur;
    unsigned int words[NS_IN6ADDRSZ / NS_INT16SZ];
    int i;

    /*
     * Preprocess:
     *      Copy the input (bytewise) array into a wordwise array.
     *      Find the longest run of 0x00's in src[] for :: shorthanding.
     */
    memset(words, '\0', sizeof words);
    for ( i = 0; i < NS_IN6ADDRSZ; i++ )
        words[i / 2] |= (src[i] << ((1 - (i % 2)) << 3));
    best.base = -1;
    cur.base = -1;
    for ( i = 0; i < (NS_IN6ADDRSZ / NS_INT16SZ); i++ )
    {
        if ( words[i] == 0 )
        {
            if ( cur.base == -1 )
                cur.base = i, cur.len = 1;
            else
                cur.len++;
        }
        else
        {
            if ( cur.base != -1 )
            {
                if ( best.base == -1 || cur.len > best.len )
                    best = cur;
                cur.base = -1;
            }
        }
    }
    if ( cur.base != -1 )
    {
        if ( best.base == -1 || cur.len > best.len )
            best = cur;
    }
    if ( best.base != -1 && best.len < 2 )
        best.base = -1;

    /*
     * Format the result.
     */
    tp = tmp;
    for ( i = 0; i < (NS_IN6ADDRSZ / NS_INT16SZ); i++ )
    {
        /* Are we inside the best run of 0x00's? */
        if ( best.base != -1 && i >= best.base &&
             i < (best.base + best.len) )
        {
            if ( i == best.base )
                *tp++ = ':';
            continue;
        }
        /* Are we following an initial run of 0x00s or any real hex? */
        if ( i != 0 )
            *tp++ = ':';
        /* Is this address an encapsulated IPv4? */
        if ( i == 6 && best.base == 0 &&
             (best.len == 6 || (best.len == 5 && words[5] == 0xffff)) )
        {
            if ( !inet_ntop4(src+12, tp,
                             sizeof tmp - (tp - tmp)) )
                return 0;
            tp += strlen(tp);
            break;
        }
        tp += sprintf(tp, "%x", words[i]);
    }
    /* Was it a trailing run of 0x00's? */
    if ( best.base != -1 && (best.base + best.len) ==
         (NS_IN6ADDRSZ / NS_INT16SZ) )
        *tp++ = ':';
    *tp++ = '\0';

    /*
     * Check for overflow, copy, and we're done.
     */
    if ( (size_t)(tp - tmp) > size )
    {
        return 0;
    }
    strcpy(dst, tmp);
    return 1;
}

int inet_ntop(int af, const void *src, void *dst, size_t size)
{
    switch ( af )
    {
        case AF_INET:
            return (inet_ntop4(src, dst, size));
        case AF_INET6:
            return (inet_ntop6(src, dst, size));
        default:
            return 0;
    }
}
