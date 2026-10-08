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
/*
 *  Terminal
 */

// Standard includes
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <osi_kernel.h>

OsiLockObj_t LockObj;
extern int vsnprintf(char * s,
                     size_t n,
                     const char * format,
                     va_list arg);

void Message(const char *str);

//*****************************************************************************
//
//! prints the formatted string on to the console
//!
//! \param[in]  format  - is a pointer to the character string specifying the
//!                       format in the following arguments need to be
//!                       interpreted.
//! \param[in]  [variable number of] arguments according to the format in the
//!             first parameters
//!
//! \return count of characters printed
//
//*****************************************************************************
//TODO! if want to use static buffer for the report, which is better,
//need to create buffer per thread
//Using the same buffer with lock is not working well,
//Because vsnprintf sometimes gets asserted if it is wrapped with lock
//The reason is that the lock create high latency if it is been used
//for long time.and the operating system can't wait long when priority inversion
//is happening.it can be verified in stability tests, you can see that vsprintf
//gets asserted.
#define USE_HEAP_BUF  //if using the heap buff no possibility to debug the heap

int Report(const char *pcFormat,...)
{
    int iRet = 0;
    char        *pcTemp;
#ifdef USE_HEAP_BUF
    char        *pcBuff;
    int iSize = 256;
#else
    char        *pcBuff=gPcBuff;
    int iSize = 898;
#endif
    va_list list;

#ifdef USE_HEAP_BUF
    //osi_LockObjLock(&LockObj,OSI_WAIT_FOREVER);
    pcBuff = (char*)os_malloc(iSize);
    if(pcBuff == NULL)
    {
        return(-1);
    }
#else
    osi_LockObjLock(&LockObj,OSI_WAIT_FOREVER);
#endif
    while(1)
    {
        va_start(list,pcFormat);
        iRet = vsnprintf(pcBuff, iSize, pcFormat, list);
        va_end(list);
        if((iRet > -1) && (iRet < iSize))
        {
            break;
        }
#ifdef USE_HEAP_BUF
        else
        {
            iSize *= 2;
            if((pcTemp = os_realloc(pcBuff, iSize)) == NULL)
            {
                Message("Could not reallocate memory\n\r");
                iRet = -1;
                break;
            }
            else
            {
                pcBuff = pcTemp;
            }
        }
#else
        else
        {
            osi_LockObjUnlock(&LockObj);
            return -1;
        }
#endif
    }
    Message(pcBuff);//Note! this is not under lock, so messages may be combined, but it is better than the overhead of lock
#ifdef USE_HEAP_BUF
    os_free(pcBuff);
    //osi_LockObjUnlock(&LockObj);
#else
    osi_LockObjUnlock(&LockObj);
#endif

    return(iRet);
}

#ifdef COLLECT_HEAP_DEBUG_INFO //OSPREY_MX-17
char gPcBuff[900];
int ReportNoLock(const char *pcFormat,...)
{
    int iRet = 0;
    char        *pcTemp;
    char        *pcBuff=gPcBuff;
    int iSize = 898;
    va_list list;

    //osi_LockObjLock(&LockObj,OSI_WAIT_FOREVER);
    while(1)
    {
        va_start(list,pcFormat);
        iRet = vsnprintf(pcBuff, iSize, pcFormat, list);
        va_end(list);
        if((iRet > -1) && (iRet < iSize))
        {
            break;
        }
        else
        {
            //osi_LockObjUnlock(&LockObj);
            return -1;
        }
    }
    Message(pcBuff);//Note! this is not under lock, so messages may be combined, but it is better than the overhead of lock
    //osi_LockObjUnlock(&LockObj);

    return(iRet);
}
#endif

//*****************************************************************************
//
//! Outputs a character string to the console
//!
//! This function
//!        1. prints the input string character by character on to the console.
//!
//! \param[in]  str - is the pointer to the string to be printed
//!
//! \return none
//!
//! \note If UART_NONPOLLING defined in than Message or UART write should be
//!       called in task/thread context only.
//
//*****************************************************************************
void Message(const char *str)
{
	printf("%s", str);
}
