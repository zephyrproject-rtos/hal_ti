/*
 * Copyright (c) 2021-2025, Texas Instruments Incorporated
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
 *  ======== RCL_Buffer.c ========
 */
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#include <ti/drivers/rcl/RCL_Command.h>
#include <ti/drivers/rcl/RCL_Scheduler.h>
#include <ti/drivers/rcl/RCL_Buffer.h>
#include <ti/drivers/rcl/RCL_Debug.h>

#include <ti/drivers/dpl/HwiP.h>

#include <ti/devices/DeviceFamily.h>
#include DeviceFamily_constructPath(inc/hw_ints.h)

#include <ti/log/Log.h>

static bool RxEntry_isAtEnd(RCL_MultiBuffer *multiBuffer, uint16_t curIndex);
static void List_consumeAndStore(List_List *list, List_List *consumedBuffers);

/*
 *  ======== RCL_TxBuffer_put ========
 */
void RCL_TxBuffer_put(List_List *list, RCL_Buffer_TxBuffer *elem)
{

    List_put(list, (List_Elem *)elem);
    /* Notify running command */
    (void) RCL_Scheduler_postEvent(rclSchedulerState.currCmd, RCL_EventTxBufferUpdate);
}

/*
 *  ======== RCL_TxBuffer_init ========
 */
uint8_t *RCL_TxBuffer_init(RCL_Buffer_TxBuffer *buffer, uint32_t numPad, uint32_t hdrLen,
                           uint32_t dataLen)
{
    if (buffer == NULL)
    {
        return NULL;
    }
    else
    {
        buffer->state = RCL_BufferStatePending;
        buffer->length = (uint16_t) (sizeof(buffer->numPad) + numPad + hdrLen + dataLen);
        buffer->numPad = (uint8_t) numPad;
        /* Start writing at pad0, then continue into data field */
        uint8_t *data = &buffer->pad0;
        if (numPad > 0U)
        {
            --numPad;
            *data = (uint8_t) numPad;
            data = buffer->data;
        }
        while (numPad > 0U)
        {
            --numPad;
            *data++ = (uint8_t) numPad;
        }
        return data;
    }
}

/*
 *  ======== RCL_MultiBuffer_clear ========
 */
void RCL_MultiBuffer_clear(RCL_MultiBuffer *buffer)
{
    buffer->state = RCL_BufferStatePending;
    buffer->headIndex = 0;
    buffer->tailIndex = 0;
}

/*
 *  ======== RCL_MultiBuffer_init ========
 */
void RCL_MultiBuffer_init(RCL_MultiBuffer *buffer, size_t size)
{
    size -= offsetof(RCL_MultiBuffer, data);
    RCL_Debug_assert(size > 0U && size <= 0xFFFFU);
    buffer->length = (uint16_t) size;
    RCL_MultiBuffer_clear(buffer);

}

/*
 *  ======== RCL_MultiBuffer_put ========
 */
void RCL_MultiBuffer_put(List_List *list, RCL_MultiBuffer *elem)
{
    List_put(list, (List_Elem *)elem);
    /* Notify running command */
    (void) RCL_Scheduler_postEvent(rclSchedulerState.currCmd, RCL_EventRxBufferUpdate);

}

/*
 *  ======== RCL_MultiBuffer_RxEntry_get ========
 */
RCL_Buffer_DataEntry *RCL_MultiBuffer_RxEntry_get(List_List *list, List_List *consumedBuffers)
{
    RCL_Buffer_DataEntry *rxEntry = NULL;
    RCL_MultiBuffer *multiBuffer = (RCL_MultiBuffer *)list->head;
    if (multiBuffer != NULL)
    {
        uint32_t headIndex = (uint32_t) multiBuffer->headIndex;
        uint32_t tailIndex = (uint32_t) multiBuffer->tailIndex;

        RCL_Debug_assert(headIndex <= tailIndex);

        if (headIndex >= tailIndex)
        {
            if (multiBuffer->state == RCL_BufferStateFinished)
            {
                List_consumeAndStore(list, consumedBuffers);
                multiBuffer = (RCL_MultiBuffer *) List_head(list);
                headIndex = 0;
                tailIndex = multiBuffer->tailIndex;
                RCL_Debug_assert(multiBuffer->headIndex == 0U);

            }
        }

        if (headIndex < tailIndex)
        {
            rxEntry = (RCL_Buffer_DataEntry *) &multiBuffer->data[headIndex];
            headIndex += RCL_Buffer_DataEntry_paddedLen(rxEntry->length);
            RCL_Debug_assert(headIndex <= tailIndex);
            multiBuffer->headIndex = (uint16_t) headIndex;
            if (headIndex >= tailIndex)
            {
                if (multiBuffer->state == RCL_BufferStateFinished)
                {
                    List_consumeAndStore(list, consumedBuffers);
                }
            }
        }
    }
    return rxEntry;
}

/*
 *  ======== RCL_MultiBuffer_RxEntry_isEmpty ========
 */
bool RCL_MultiBuffer_RxEntry_isEmpty(List_List *list)
{
    RCL_MultiBuffer *multiBuffer = (RCL_MultiBuffer *)list->head;

    if (multiBuffer != NULL)
    {
        return RxEntry_isAtEnd(multiBuffer, multiBuffer->headIndex);
    }
    else {
        return true;
    }
}

/*
 *  ======== RCL_MultiBuffer_ListInfo_init ========
 */
void RCL_MultiBuffer_ListInfo_init(RCL_MultiBuffer_ListInfo *listInfo, List_List *list)
{
    RCL_Debug_assert(listInfo != NULL);
    RCL_Debug_assert(list != NULL);

    if (listInfo != NULL && list != NULL)
    {
        listInfo->multiBuffers = list;
        listInfo->nextBuffer = (RCL_MultiBuffer *) List_head(list);
        if (listInfo->nextBuffer != NULL)
        {
            listInfo->nextIndex = listInfo->nextBuffer->headIndex;
        }
        else
        {
            listInfo->nextIndex = 0;
        }
    }
}
/*
 *  ======== RCL_MultiBuffer_RxEntry_next ========
 */
RCL_Buffer_DataEntry *RCL_MultiBuffer_RxEntry_next(RCL_MultiBuffer_ListInfo *listInfo)
{
    RCL_Buffer_DataEntry *rxEntry = NULL;

    RCL_Debug_assert(listInfo != NULL);
    if (listInfo != NULL)
    {
        RCL_MultiBuffer *nextBuffer = listInfo->nextBuffer;

        if (nextBuffer == NULL && listInfo->multiBuffers != NULL)
        {
            RCL_Debug_assert(listInfo->multiBuffers != NULL);
            nextBuffer = RCL_MultiBuffer_head(listInfo->multiBuffers);
        }

        if (nextBuffer != NULL)
        {
            uint32_t nextIndex = (uint32_t) listInfo->nextIndex;
            uint32_t tailIndex = (uint32_t) nextBuffer->tailIndex;
            if (nextIndex >= tailIndex)
            {
                if (nextBuffer->state == RCL_BufferStateFinished)
                {
                    nextBuffer = (RCL_MultiBuffer *) List_next((List_Elem *) nextBuffer);
                    nextIndex = 0;
                    tailIndex = (uint32_t) nextBuffer->tailIndex;
                }
            }

            if (nextIndex < tailIndex)
            {
                rxEntry = (RCL_Buffer_DataEntry *) &nextBuffer->data[nextIndex];
                nextIndex += RCL_Buffer_DataEntry_paddedLen(rxEntry->length);
                RCL_Debug_assert(nextIndex <= tailIndex);
                if (nextIndex >= tailIndex)
                {
                    if (nextBuffer->state == RCL_BufferStateFinished)
                    {
                        nextBuffer = (RCL_MultiBuffer *) List_next((List_Elem *) nextBuffer);
                        nextIndex = 0;
                    }
                }
            }
            listInfo->nextBuffer = nextBuffer;
            listInfo->nextIndex = (uint16_t) nextIndex;
        }
        return rxEntry;
    }
    else
    {
        /* If listInfo is NULL we cannot advance. Return NULL to indicate “no entry”. */
        return NULL;
    }

}

/*
 *  ======== RCL_MultiBuffer_RxEntry_isLast ========
 */
bool RCL_MultiBuffer_RxEntry_isLast(RCL_MultiBuffer_ListInfo *listInfo)
{
    RCL_Debug_assert(listInfo != NULL);

    if (listInfo != NULL)
    {
        RCL_MultiBuffer *nextBuffer = listInfo->nextBuffer;

        if (nextBuffer != NULL)
        {
            return RxEntry_isAtEnd(nextBuffer, listInfo->nextIndex);
        }
        else
        {
            RCL_Debug_assert(listInfo->multiBuffers != NULL);
            if (listInfo->multiBuffers != NULL)
            {
                return RxEntry_isAtEnd((RCL_MultiBuffer *)List_head(listInfo->multiBuffers), 0);
            }
            else
            {
                return false;
            }
        }
    }
    else
    {
        return false;
    }
}

/*
 *  ======== RCL_Buffer_readPartialRxBuffer ========
 */
size_t RCL_Buffer_readPartialRxBuffer(RCL_Buffer_DataEntry *dataEntry, size_t entrySize)
{
    /* Default to no data available */
    size_t numBytesAvailable = 0;
    if (dataEntry != NULL && entrySize >= offsetof(RCL_Buffer_DataEntry, data))
    {
        uint32_t rp;
        uintptr_t key = HwiP_disable();
        numBytesAvailable = LRF_getUncommittedFifoStatus(&rp);
        /* Round number of words up - uninitialized bytes may be read, but will not be shown as available */
        uint32_t numWords = RCL_Buffer_bytesToWords(numBytesAvailable);
        /* Make sure that everything fits in the entry, and do not use non-word part of end of entry */
        if ((numWords << 2) > entrySize)
        {
            numWords = entrySize >> 2;
            numBytesAvailable = numWords << 2;
        }

        if (numBytesAvailable >= sizeof(dataEntry->length))
        {
            LRF_peekRxFifoWords((uint32_t *)dataEntry, numWords, rp);
            /* Write actual number of available bytes in length field */
            dataEntry->length = (uint16_t) (numBytesAvailable - sizeof(dataEntry->length));
        }
        HwiP_restore(key);
    }
    return numBytesAvailable;
}

/*
 *  ======== RCL_MultiBuffer_findFirstWritableBuffer ========
 */
RCL_MultiBuffer *RCL_MultiBuffer_findFirstWritableBuffer(RCL_MultiBuffer *head)
{
    RCL_MultiBuffer *curBuffer = head;
    while (curBuffer != NULL && curBuffer->state == RCL_BufferStateFinished)
    {
        curBuffer = (RCL_MultiBuffer *) List_next((List_Elem *)curBuffer);
    }
    return curBuffer;
}

/*
 *  ======== RCL_MultiBuffer_getBuffer ========
 */
RCL_MultiBuffer *RCL_MultiBuffer_getBuffer(RCL_MultiBuffer *curBuffer,
                                           uint32_t minLength)
{
    /* Try to find a buffer with enough space */
    if (curBuffer != NULL)
    {
        /* Check if first buffer in queue needs initialization */
        if (curBuffer->state != RCL_BufferStateInUse)
        {
            /* Initialize buffer for use */
            curBuffer->state = RCL_BufferStateInUse;
            /* Initialize indeces */
            curBuffer->headIndex = 0;
            curBuffer->tailIndex = 0;
        }
        if (minLength + curBuffer->tailIndex > curBuffer->length)
        {
            /* Not room in this buffer. Need to go to next buffer - unless buffer is empty */
            if (curBuffer->tailIndex == 0U)
            {
                /* New buffer already - give up, as buffer is too small */
                curBuffer = NULL;
            }
            else
            {
                curBuffer->state = RCL_BufferStateFinished;
                curBuffer = (RCL_MultiBuffer *) List_next((List_Elem *)curBuffer);
                /* Check that buffer is available */
                if (curBuffer != NULL) {
                    /* Make sure that length is enough */
                    if (minLength > curBuffer->length)
                    {
                        /* Buffer too short */
                        curBuffer = NULL;
                    }
                    else
                    {
                        /* Initialize buffer for use */
                        curBuffer->state = RCL_BufferStateInUse;
                        /* Initialize indeces */
                        curBuffer->headIndex = 0;
                        curBuffer->tailIndex = 0;
                    }
                }
            }
        }
    }

    return curBuffer;
}

/*
 *  ======== RCL_MultiBuffer_findAvailableRxSpace ========
 */
uint32_t RCL_MultiBuffer_findAvailableRxSpace(const RCL_MultiBuffer *curBuffer)
{
    uint32_t space = 0;

    if (curBuffer != NULL)
    {
        /* Find available space in current buffer */
        if (curBuffer->state == RCL_BufferStateInUse)
        {
            const RCL_MultiBuffer *nextBuffer;
            nextBuffer = (RCL_MultiBuffer *) List_next((List_Elem *)curBuffer);
            /* Check if there is another buffer available */
            if (nextBuffer == NULL)
            {
                /* No - use remaining space in this buffer */
                space = curBuffer->length - curBuffer->tailIndex;
            }
            else
            {
                /* Yes - use space in next buffer */
                space = nextBuffer->length;
            }
        }
        else
        {
            space = curBuffer->length;
        }
    }
    return space;
}

/*
 *  ======== RxEntry_isAtEnd ========
 */
static bool RxEntry_isAtEnd(RCL_MultiBuffer *multiBuffer, uint16_t curIndex)
{
    bool isAtEnd = true;

    if (multiBuffer != NULL)
    {
        if (curIndex < multiBuffer->tailIndex)
        {
            isAtEnd = false;
        }
        else
        {
            if (multiBuffer->state == RCL_BufferStateFinished)
            {
                /* Look in next MultiBuffer to see if there is data there */
                multiBuffer = (RCL_MultiBuffer *) List_next((List_Elem *)multiBuffer);
                if (multiBuffer != NULL && multiBuffer->tailIndex > 0U)
                {
                    isAtEnd = false;
                }
            }
        }
    }

    return isAtEnd;
}

/*
 *  ======== List_consumeAndStore ========
 */
static void List_consumeAndStore(List_List *list, List_List *consumedBuffers)
{
    List_Elem *consumedBuffer = List_get(list);

    if (consumedBuffers != NULL)
    {
        List_put(consumedBuffers, consumedBuffer);
    }
}
