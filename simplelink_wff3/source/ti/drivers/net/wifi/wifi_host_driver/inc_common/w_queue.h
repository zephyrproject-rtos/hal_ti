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
/** \file   w_queue.h 
 *  \brief  queue module header file.                                  
 *
 *  \see    w_queue.c
 */


#ifndef _QUEUE_H_
#define _QUEUE_H_


#define QUE_UNLIMITED_SIZE      0xFFFFFFFF

/* A queue node header structure */                        
typedef struct _TQueNodeHdr 
{
    struct _TQueNodeHdr  volatile *pNext;
    struct _TQueNodeHdr  volatile *pPrev;
} TQueNodeHdr;


/**
 * \def FIELD_OFFSET
 * \brief Macro which returns a field offset from structure begin
 */
#define FIELD_OFFSET(type,field)    ((uint32_t)(&(((type*)0)->field)))

/* External Functions Prototypes */
/* ============================= */
void* que_Create(uint32_t uLimit, uint32_t uNodeHeaderOffset);
int que_Destroy(void *hQue);
int que_Enqueue(void *hQue, void *hItem);
void* que_Dequeue(void *hQue);
int que_Requeue(void *hQue, void *hItem);
uint32_t que_Size(void *hQue);
void* que_GetFirst(void *hQue);
void* que_GetNext(void *hQue, void *hItem);
int que_DeleteItem(void *hQue, void *hItem);
uint32_t que_GetLimit (void * hQue);

#ifdef TI_DBG
void      que_Print   (void * hQue);
#endif /* TI_DBG */



#endif  /* _QUEUE_H_ */
