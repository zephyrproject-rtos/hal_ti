/*
 * Copyright (c) 2020-2023, Texas Instruments Incorporated
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

#ifndef ti_drivers_RCL_Buffers_h__include
#define ti_drivers_RCL_Buffers_h__include

#include <stdint.h>
#include <ti/drivers/utils/List.h>


/**
 *  @brief Buffer state
 */
typedef enum {
    RCL_BufferStatePending  = 0U, /*!< Buffer is not yet accessed by RCL */
    RCL_BufferStateInUse    = 1U, /*!< Buffer has been accessed by RCL, and may be accessed again */
    RCL_BufferStateFinished = 2U  /*!< RCL is finished with the buffer. It may be reused or freed. */
} RCL_BufferState;

typedef struct RCL_Buffer_TxBuffer_s      RCL_Buffer_TxBuffer;
typedef struct RCL_Buffer_DataEntry_s     RCL_Buffer_DataEntry;
typedef struct RCL_MultiBuffer_s          RCL_MultiBuffer;
typedef struct RCL_MultiBuffer_ListInfo_s RCL_MultiBuffer_ListInfo;

/**
 *  @brief Definition of an RCL Tx Buffer
 *
 *  Instances of %RCL_Buffer_TxBuffer shall be allocated by the protocol stacks.
 */
struct RCL_Buffer_TxBuffer_s {
    List_Elem            __elem__;
    RCL_BufferState      state;                                  /*!< Buffer state */
    uint16_t             length   __attribute__ ((aligned (4))); /*!< Number of bytes in buffer after the length field */
    uint8_t              numPad;                                 /*!< Number of pad bytes before start of the packet */
    uint8_t              pad0;                                   /*!< First pad byte, or first byte of the packet if numPad == 0 */
    uint8_t              data[];                                 /*!< Remaining pad bytes and packet */
};

/**
 *  @brief Definition of an RCL Rx Buffer Entry
 *
 *  Instances of %RCL_Buffer_DataEntry are written by LRF into %RCL_MultiBuffer
 *  instances allocated by the protocol stacks, or used for a single TX packet
 */
struct RCL_Buffer_DataEntry_s {
    uint16_t             length  __attribute__ ((aligned (4))); /*!< Number of bytes in buffer after the length field */
    uint8_t              numPad;                                /*!< Number of pad bytes before start of the packet */
    uint8_t              pad0;                                  /*!< First pad byte, or first byte of the packet if numPad == 0 */
    uint8_t              data[];                                /*!< Remaining pad bytes and packet */
};

/**
 *  @brief Definition of an RCL Rx MultiBuffer
 *
 *  Instances of %RCL_MultiBuffer are allocated by the protocol stacks, and
 *  provided to RCL
 */
struct RCL_MultiBuffer_s {
    List_Elem            __elem__;
    RCL_BufferState      state;       /*!< Buffer state */
    uint16_t             length;      /*!< Number of bytes in the data field */
    uint16_t             headIndex;   /*!< Number of bytes consumed */
    uint16_t             tailIndex;   /*!< Number of bytes written */
    uint8_t              data[];      /*!< Data buffer consisting of %RCL_Buffer_DataEntry elements */
};

/**
 *  @brief Information about an RCL_MultiBuffer list being traversed
 *
 *  An instance of %RCL_MultiBuffer_ListInfo is used to hold information
 *  of an RX queue which is read without consuming directly.
 */
struct RCL_MultiBuffer_ListInfo_s {
    List_List            *multiBuffers;    /*!< Pointer to list of MultiBuffers */
    RCL_MultiBuffer      *nextBuffer;      /*!< Pointer to next MultiBuffer to traverse */
    uint16_t             nextIndex;        /*!< Index of nextBuffer->data for next entry */
};

/**
 *  @brief Number of 32-bit words needed to hold a given number of bytes (rounded up)
 */
#define RCL_Buffer_bytesToWords(byteLen) (((byteLen) + sizeof(uint32_t) - 1) / sizeof(uint32_t))

/**
 *  @brief Total length of a data entry in bytes based on length field of the entry
 */
/* Include the data entry's length field and padding to uint32_t boundary */
#define RCL_Buffer_DataEntry_paddedLen(len) (RCL_Buffer_bytesToWords((len) + sizeof(uint16_t)) * sizeof(uint32_t))

/** @defgroup bufferApiFunctions Buffer APIs
 *  These functions are useful as part of the API to RCL
 *  @{
 */

/**
 *  @brief Total length of a data entry in bytes, including entry length field and padding
 *
 *  @param  numPad    Number of padding bytes in front of the packet
 *
 *  @param  hdrLen    Number of header bytes to hold
 *
 *  @param  dataLen   Number of payload bytes to hold
 *
 */
#define RCL_Buffer_entryLen(numPad, hdrLen, dataLen) (RCL_Buffer_DataEntry_paddedLen(sizeof(uint8_t) + (numPad) + (hdrLen) + (dataLen)))

/**
 *  @brief Total length of a TX buffer in bytes, including all fields and padding
 *
 *  @param  numPad    Number of padding bytes in front of the packet
 *
 *  @param  hdrLen    Number of header bytes to hold
 *
 *  @param  dataLen   Number of payload bytes to hold
 *
 */
#define RCL_TxBuffer_len(numPad, hdrLen, dataLen) (offsetof(RCL_Buffer_TxBuffer, length) + RCL_Buffer_entryLen(numPad, hdrLen, dataLen))

/**
 *  @brief Total length of a TX buffer in 32-bit words, including all fields and padding
 *
 *  @param  numPad    Number of padding bytes in front of the packet
 *
 *  @param  hdrLen    Number of header bytes to hold
 *
 *  @param  dataLen   Number of payload bytes to hold
 *
 */
#define RCL_TxBuffer_len_u32(numPad, hdrLen, dataLen) (RCL_Buffer_bytesToWords(RCL_TxBuffer_len(numPad, hdrLen, dataLen)))

/**
 *  @brief Total length of a multi buffer in bytes, including all fields
 *
 *  @param  dataLen   Number of bytes available to store data entries
 *
 */
#define RCL_MultiBuffer_len(dataLen) (offsetof(RCL_MultiBuffer, data) + (dataLen))

/**
 *  @brief Total length of a multi buffer in 32-bit words, including all fields
 *
 *  @param  dataLen   Number of bytes available to store data entries
 *
 */
#define RCL_MultiBuffer_len_u32(dataLen) (RCL_Buffer_bytesToWords(RCL_MultiBuffer_len(dataLen)))

/**
 *  @brief  Function to atomically get the first elem in a Tx Buffer list
 *
 *  @param  list A pointer to a linked list of Tx Buffers
 *
 *  @return Pointer the first elem in the linked list or NULL if empty
 */
static inline RCL_Buffer_TxBuffer *RCL_TxBuffer_get(List_List *list)
{
    return (RCL_Buffer_TxBuffer *)List_get(list);
}

/**
 *  @brief  Function to return the head of a TxBuffer list
 *
 *  This function does not remove the head, it simply returns a pointer to
 *  it. This function is typically used when traversing a linked list.
 *
 *  @param  list A pointer to the linked list of Tx Buffers
 *
 *  @return Pointer to the first elem in the linked list or NULL if empty
 */
static inline RCL_Buffer_TxBuffer *RCL_TxBuffer_head(List_List *list)
{
    return (RCL_Buffer_TxBuffer *) (list->head);
}

/**
 *  @brief  Function to return the next elem in a linked list of Tx Buffers
 *
 *  This function does not remove the elem, it simply returns a pointer to
 *  next one. This function is typically used when traversing a linked list.
 *
 *  @param  elem Elem in the TxBuffer list
 *
 *  @return Pointer to the next elem in linked list or NULL if at the end
 */
static inline RCL_Buffer_TxBuffer *RCL_TxBuffer_next(RCL_Buffer_TxBuffer *elem)
{
    return (RCL_Buffer_TxBuffer *)(((List_Elem *)elem)->next);
}

/**
 *  @brief  Function to initialize a TX buffer entry for use by RCL
 *
 * Initialize a new TX buffer entry with the correct length and padding
 *
 *  @param  buffer    Tx buffer to initialize
 *
 *  @param  numPad    Number of padding bytes in front of the packet
 *
 *  @param  hdrLen    Number of header bytes to hold
 *
 *  @param  dataLen   Number of payload bytes to hold
 *
 * @return  Pointer to address where first header byte should be stored (followed by payload)
*/
extern uint8_t *RCL_TxBuffer_init(RCL_Buffer_TxBuffer *buffer, uint32_t numPad, uint32_t hdrLen,
                                  uint32_t dataLen);

/**
 *  @brief  Function to atomically put an elem onto the end of a Tx Buffer list
 *
 * Add an entry to the TX buffer list and notify the running command if there is any
 *
 *  @param  list A pointer to the Tx buffer list
 *
 *  @param  elem Element to place onto the end of the linked list
 */
extern void RCL_TxBuffer_put(List_List *list, RCL_Buffer_TxBuffer *elem);

/**
 *  @brief  Function to return the head of a MultiBuffer list
 *
 *  This function does not remove the head, it simply returns a pointer to
 *  it. This function is typically used when traversing a linked list.
 *
 *  @param  list A pointer to the linked list of Multi Buffers
 *
 *  @return Pointer to the first elem in the linked list or NULL if empty
 */
static inline RCL_MultiBuffer *RCL_MultiBuffer_head(List_List *list)
{
    return (RCL_MultiBuffer *) (list->head);
}

/**
 *  @brief  Function to return the next elem in a linked list of MultiBuffers
 *
 *  This function does not remove the elem, it simply returns a pointer to
 *  next one. This function is typically used when traversing a linked list.
 *
 *  @param  elem Elem in the MultiBuffer list
 *
 *  @return Pointer to the next elem in linked list or NULL if at the end
 */
static inline RCL_MultiBuffer *RCL_MultiBuffer_next(RCL_MultiBuffer *elem)
{
    return (RCL_MultiBuffer *)(((List_Elem *)elem)->next);
}

/**
 *  @brief  Function to get the first elem in a MultiBuffer list
 *
 *  Returns the first whole MultiBuffer from a list. Note that this
 *  will be done even if the buffer wasn't finished and that the
 *  buffer may contain several entries.
 *
 *  @param  list A pointer to a linked list of Tx Buffers
 *
 *  @return Pointer the first elem in the linked list or NULL if empty
 */
static inline RCL_MultiBuffer *RCL_MultiBuffer_get(List_List *list)
{
    return (RCL_MultiBuffer *)List_get(list);
}

/**
 *  @brief  Function to clear a multi buffer entry for re-use by RCL
 *
 * Clear a new multi buffer entry so that it can be re-used by RCL for
 * storing received packets
 *
 *  @param  buffer Multi buffer to clear
 */
extern void RCL_MultiBuffer_clear(RCL_MultiBuffer *buffer);

/**
 *  @brief  Function to initialize a multi buffer entry for use by RCL
 *
 * Initialize a new multi buffer entry so that it can be provided to
 * RCL for storing received packets
 *
 *  @param  buffer Multi buffer to initialize
 *
 *  @param  size Size of the buffer in bytes including all fields
 */
extern void RCL_MultiBuffer_init(RCL_MultiBuffer *buffer, size_t size);

/**
 *  @brief  Function to get the first entry in a MultiBuffer list
 *
 *  This function gets the first entry in a MultiBuffer list and
 *  consumes it. If one or two whole %RCL_MultiBuffer are consumed as
 *  a result of this, they are added to the consumedBuffers list.
 *
 *  @param  list A pointer to a linked list of MultiBuffers
 *
 *  @param consumedBuffers A pointer to a linked list which will hold
 *                          the buffers that were consumed and can now
 *                          be re-used. The list is not initialized,
 *                          so that it is possible to get consumed
 *                          entries appended. If this is not desired,
 *                          the list should be cleared first. If NULL,
 *                          consumed buffers are not reported
 *
 *  @return Pointer the first entry in the linked list or NULL if empty
 */
extern RCL_Buffer_DataEntry *RCL_MultiBuffer_RxEntry_get(List_List *list, List_List *consumedBuffers);

/**
 *  @brief  Function to check if the MultiBuffer List is out of entries
 *
 *  This function returns true if there are no more entries to read
 *  from a list of MultiBuffers
 *
 *  @param  list        Pointer to list of multi buffers
 *
 *  @return true if there are no more entries to read now; false if
 *          there are more entries to read
 */
extern bool RCL_MultiBuffer_RxEntry_isEmpty(List_List *list);

/**
 *  @brief  Function to initialize information for traversing a multi buffer list
 *
 *  This function prepares a struct for holding information about entries being
 *  read from a list of multi buffers. It will set up the struct to start by
 *  traversing the head of the list.
 *
 *  @param  listInfo    Pointer to list information which will be set up to start
 *                      traversing the head of the list
 *
 *  @param  list        Pointer to list of multi buffers
 *
 */
extern void RCL_MultiBuffer_ListInfo_init(RCL_MultiBuffer_ListInfo *listInfo, List_List *list);

/**
 *  @brief  Function to return the next entry in a list of multi buffers
 *
 *  This function does not remove the entry, it simply returns a pointer to
 *  next one. This function is typically used when traversing a linked list of
 *  multi buffers.
 *
 *  @param  listInfo    Struct with information of the next entry to
 *                      access. Set up using
 *                      %RCL_MultiBuffer_ListInfo_init before starting.
 *
 *  @return Pointer to the entry in the linked list of MultiBuffers or NULL if
 *          at the end
 */
extern RCL_Buffer_DataEntry *RCL_MultiBuffer_RxEntry_next(RCL_MultiBuffer_ListInfo *listInfo);

/**
 *  @brief  Function to check a traversed entry was the last one
 *
 *  This function returns true if the latest entry returned by
 *  %RCL_MultiBuffer_RxEntry_next was the last one
 *
 *  @param  listInfo    Struct with information of the next entry to
 *                      access
 *
 *  @return true if there are no more entries to read now; false if
 *          there are more entries to read
 */
extern bool RCL_MultiBuffer_RxEntry_isLast(RCL_MultiBuffer_ListInfo *listInfo);

/**
 *  @brief  Function to atomically put an elem onto the end of a multi buffer list
 *
 *  Add an entry to the multi buffer list and notify the running command if there is any
 *
 *  @param  list A pointer to the multi buffer list
 *
 *  @param  elem Multi buffer to place onto the end of the linked list
 */
extern void RCL_MultiBuffer_put(List_List *list, RCL_MultiBuffer *elem);
/** @}
 */

/** @defgroup bufferHandlerFunctions Buffer Handler Functions
 *  These functions are meant mostly to be used by handlers and RCL itself
 *  @{
 */
/**
 *  @brief Find the first writable buffer in a list of MultiBuffers
 *
 *  @note This function is intended as internal to RCL and its handlers
 *
 *  @param head [in] - The head of the list
 *
 *  @return Pointer to first non-finished MultiBuffer after head; NULL if none
 */
RCL_MultiBuffer *RCL_MultiBuffer_findFirstWritableBuffer(RCL_MultiBuffer *head);

/**
 *  @brief Returns a buffer with at least `minLength` bytes remaining capacity.
 *
 *  Checks current buffer and next buffer against minLength, returns current if enough
 *  space, otherwise moves to next buffer.
 *
 *  If no such buffer is available, NULL is returned.
 *
 *  @note This function is intended as internal to RCL and its handlers
 *
 *  @note The caller is responsible for issuing the necessary event if the decision is
 *        made to use the returned buffer and it is != curBuffer, or if the result of a
 *        NULL return is to stop using curBuffer.
 *
 *  @param curBuffer [in] - Buffer to search from
 *  @param minLength [in] - Minimum amount of bytes needed in buffer
 *
 *  @return Suitable %RCL_MultiBuffer or NULL
 */
RCL_MultiBuffer *RCL_MultiBuffer_getBuffer(RCL_MultiBuffer *curBuffer,
                                           uint32_t minLength);

/**
 *  @brief Find the minumum number of bytes that can be stored in available MultiBuffers
 *
 *  Finds the number of bytes that can be guaranteed to be possible to store in available
 *  MultiBuffers, regardless of packet sizes. This is the size of a free MultiBuffer if that
 *  is available, or the remaining space in a MultiBuffer.
 *
 *  @note This function is intended as internal to RCL and its handlers
 *
 *  @param curBuffer [in] - Pointer to the first writable %RCL_MultiBuffer
 *
 *  @return Number of available bytes
 */
uint32_t RCL_MultiBuffer_findAvailableRxSpace(const RCL_MultiBuffer *curBuffer);

/**
 *  @brief Find the first byte to write in an %RCL_MultiBuffer
 *
 *  @note This function is intended as internal to RCL and its handlers
 *
 *  @param curBuffer [in] - Pointer to %RCL_MultiBuffer
 *
 *  @return Pointer to first writable byte in curBuffer
 */
static inline uint8_t *RCL_MultiBuffer_getNextWritableByte(RCL_MultiBuffer *curBuffer)
{
    return & curBuffer->data[curBuffer->tailIndex];
}

/**
 *  @brief Update number of bytes written to %RCL_MultiBuffer
 *
 *  @note This function is intended as internal to RCL and its handlers
 *
 *  @note The caller is responsible for ensuring that the buffer can fit the bytes
 *        to be committed for issuing the necessary event if the decision is
 *
 *  @param curBuffer [in] - Pointer to %RCL_MultiBuffer
 *  @param numBytes [in] - Number of bytes that have been written
 */
static inline void RCL_MultiBuffer_commitBytes(RCL_MultiBuffer *curBuffer, uint32_t numBytes)
{
    curBuffer->tailIndex += numBytes;
}
/** @}
 */

#endif
