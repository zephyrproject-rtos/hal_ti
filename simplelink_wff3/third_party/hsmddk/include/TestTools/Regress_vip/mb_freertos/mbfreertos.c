/* mbfreertos.c
 *
 * C runtime library and some POSIX functions implementation
 * for MicroBlaze and FreeRTOS
 *
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

/*----------------------------------------------------------------------------
 * This module implements (provides) the following interface(s):
 */

#include <stdlib.h>   // malloc, free
#include <unistd.h>   // usleep
#include <string.h>   // memcpy, memset

#if defined(__IAR_SYSTEMS_ICC__)
    #include <ti/posix/iar/pthread.h>
#elif defined(__clang__) || defined(__TI_COMPILER_VERSION__) || defined(__ti_version__)
    #include <ti/posix/ticlang/pthread.h>
#elif defined(__GNUC__)
    #include <ti/posix/gcc/pthread.h>
#else
    #error "Unsupported compiler"
#endif

/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

// FreeRTOS API
#include <FreeRTOS.h>
#include <portable.h>   // pvPortMalloc, vPortFree
#include "task.h"       // vTaskDelay


/*----------------------------------------------------------------------------
 * Definitions and macros
 */

#ifndef pdUS_TO_TICKS
#define pdUS_TO_TICKS( xTimeInMs ) ( ( TickType_t ) ( ( ( TickType_t ) \
                        ( xTimeInMs ) * ( TickType_t ) configTICK_RATE_HZ ) / \
                            ( TickType_t ) 1000000 ) )
#endif


/*----------------------------------------------------------------------------
 * Local variables
 */


/*----------------------------------------------------------------------------
 * malloc
 */
void *
malloc(
        size_t byte_count)
{
    return pvPortMalloc(byte_count);
}


/*----------------------------------------------------------------------------
 * free
 */
void
free(
        void * p)
{
    vPortFree(p);
}


/*----------------------------------------------------------------------------
 * usleep
 */
int
usleep(
        useconds_t useconds)
{
    vTaskDelay(pdUS_TO_TICKS(useconds) ? pdUS_TO_TICKS(useconds) : 1);

    return 0;
}


/* end of file mbfreertos.c */
