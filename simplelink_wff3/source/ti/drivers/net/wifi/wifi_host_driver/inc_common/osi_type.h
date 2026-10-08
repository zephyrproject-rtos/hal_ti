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
#ifndef OSI_TYPE_H
#define OSI_TYPE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include <stdint.h>



#define __PACKED__      __attribute__((aligned(1)))  __attribute__((packed))


/*-----------------------------------------------------------------------------
    Basic types definitions
  ----------------------------------------------------------------------------- */

/* unsigned types */
#ifndef uint8
typedef uint8_t uint8;
#endif

#ifndef uint16
typedef uint16_t uint16;
#endif

#ifndef uint32
typedef uint32_t uint32;
#endif

#ifndef uint64
typedef uint64_t uint64;
#endif

/* signed types */
#ifndef int8
typedef int8_t int8;
#endif

#ifndef int16
typedef int16_t int16;
#endif

#ifndef int32
typedef int32_t int32;
#endif

#ifndef int64
typedef int64_t int64;
#endif

#ifndef VOID
#define VOID void
#endif
/*-----------------------------------------------------------------------------
    Basic macros
  ----------------------------------------------------------------------------- */

#ifdef NULL
#else
#define NULL     0
#endif /* NULL */

#ifdef FALSE
#else
#define FALSE  0
#endif /* FALSE */

#ifdef TRUE
#else
#define TRUE   (!FALSE)
#endif /* TRUE */


#ifdef OK
#else
#define OK  (0)
#endif /* OK */

#ifdef NOK
#else
#define NOK  (1)
#endif /* NOK */


#ifdef _UINT8
#else
#define _UINT8
typedef unsigned char   UINT8;
#endif

#ifdef _UINT16
#else
#define _UINT16
typedef unsigned short  UINT16;
#endif

#ifdef _WIN32
typedef unsigned int    UINT32, *PUINT32;
typedef signed   int    INT32, *PINT32;
#else
#ifdef _UINT32
#else
#define _UINT32
typedef unsigned long   UINT32;
#endif

#ifdef _UINT64
#else
#define _UINT64
typedef unsigned long long   UINT64;
#endif

#ifdef _INT32
#else
#define _INT32
typedef signed   long   INT32;
#endif

#endif /* _WIN32 */

#ifdef _INT8
#else
#define _INT8
typedef signed   char   INT8;
#endif

#ifdef _INT16
#else
#define _INT16
typedef signed   short  INT16;
#endif

#ifdef _INT64
#else
#define _INT64
typedef signed   long   INT64;
#endif

typedef float           FLOAT;
typedef double          DOUBLE;

#ifdef _WINDOWS_VXD
#else

#ifdef _BOOLEAN
#else
#define _BOOLEAN
typedef unsigned char   BOOLEAN;
#endif

/*-----------------------------------------------------------------------------
    Boolean definitions
    For efficiency, the 32 bit definition should be preferred whenever possible
  ----------------------------------------------------------------------------- */

#ifndef Bool_e
typedef uint8 Bool_e;
#endif
#ifndef Bool32
typedef uint32 Bool32;
#endif

#endif /* _WINDOWS_VXD */

typedef unsigned char   UBYTE;

#ifdef __arm
#define PACKED  __packed
#ifndef INLINE
#define INLINE  __inline
#endif
#else
#define PACKED
#ifndef INLINE
#define INLINE inline
#endif /* INLINE */
#endif /* __arm */
#ifdef SL2_HOST

//Important: duplicated definitions in nx_port.h

#ifndef STELLARIS
#define htons   ntohs
#define htonl   ntohl

/* For Big Endian Processors Swap the words, and long words */
#if defined(_GKI_InH8) || defined(__BIG_ENDIAN)
extern UINT16 ntohs(UINT16 n);
extern UINT32 ntohl(UINT32 n);
extern UINT8 *ntoh6(UINT8 *p);
#else
#define ntohs(n) (UINT16)(((n << 8) | (n >> 8)) & 0xffff)
#define ntohl(n) (n)
#define ntoh6(n) (n)
#endif /* (_GKI_InH8) || (__BIG_ENDIAN) */

#if defined(__BIG_ENDIAN)
#define nettohs(n) (n)
#define nettohl(n) (n)
#else
extern UINT16 nettohs(UINT16 n);
extern UINT32 nettohl(UINT32 n);
#endif /* __BIG_ENDIAN */

#define htonets nettohs
#define htonetl nettohl

#endif /* STELLARIS */

#endif
/*-----------------------------------------------------------------------------
    Basic utilities
  ----------------------------------------------------------------------------- */
#define UINT16_LOW_BYTE(x)      ((x) & 0xff)
#define UINT16_HI_BYTE(x)       ((x) >> 8)

#ifndef MIN
#define MIN(a,b) ( ((a)<(b)) ? (a) : (b) )
#endif

#ifndef MAX
#define MAX(a,b) ( ((a)>(b)) ? (a) : (b) )
#endif

#ifndef ABS
#define ABS(a) ( ((a) < 0 ) ? (0-(a)) : (a) )
#endif

#define M_ALIGN_TO_X_BYTES(_value,_x_bytes)    (((_value)+((_x_bytes)-1)) & (~((_x_bytes)-1)))
#define M_ALIGN_TO_4_BYTES(__value)            (M_ALIGN_TO_X_BYTES((__value),4))

#define M_IS_ALIGNED_TO_X_BYTES(_value,_x_bytes) ((((UINT32)(_value) & (~((_x_bytes)-1))) == (UINT32)(_value)) ? 1 : 0)
#define M_IS_ALIGNED_TO_4_BYTES(__value)        (M_IS_ALIGNED_TO_X_BYTES((__value),4))

/*-----------------------------------------------------------------------------
    Prototypes
  ----------------------------------------------------------------------------- */

typedef void (*VOID_UINT8_FUNCPTR)(unsigned char);
typedef void (*VOIDFUNCPTR)();
typedef void (*VOID_UINT8_UINT8_FUNCPTR)(unsigned char,unsigned char);
typedef unsigned char (*BYTEFUNCPTR)(void);
typedef unsigned char (*BYTEFUNCPTRUINT8)(unsigned char);

typedef void (P_HANDLE_BUFF_FUNC)(UINT8 *pBuf);
typedef UINT8* (*P_GET_BUFF_FUNC)(void);

#endif /* SL_DATA_TYPES_H */




