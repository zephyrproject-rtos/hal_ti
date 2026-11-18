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
/** \file   w_queue.c 
 *  \brief  This module provides generic queueing services, including enqueue, dequeue
 *            and requeue of any object that contains TQueNodeHdr in its structure.                                  
 *
 *  \see    w_queue.h
 */



#define __FILE_ID__  FILE_ID_95

#include "osi_type.h"
#include "osi_kernel.h"
#include "w_queue.h"


/* Queue structure */
typedef struct 
{
    TQueNodeHdr tHead;          /* The queue first node */
    uint32_t   uCount;         /* Current number of nodes in queue */
    uint32_t   uLimit;         /* Upper limit of nodes in queue */
    uint32_t   uMaxCount;      /* Maximum uCount value (for debug) */
    uint32_t   uOverflow;      /* Number of overflow occurences - couldn't insert node (for debug) */
    uint32_t   uNodeHeaderOffset; /* Offset of NodeHeader field from the entry of the queued item */
} TQueue;	



/*
 *              INTERNAL  FUNCTIONS 
 *        =============================== 
 */


/*
 *  InsertNode():  Insert new node between pPrev and pNext 
 */
void InsertNode( TQueNodeHdr volatile *pNode, TQueNodeHdr volatile *pPrev, TQueNodeHdr volatile *pNext)
{
    pNext->pPrev = pNode;
    pNode->pNext = pNext;
    pNode->pPrev = pPrev;
    pPrev->pNext = pNode;
}

/*
 *  RemoveNode():  Remove node from between pPrev and pNext 
 */
void RemoveNode( TQueNodeHdr volatile *pPrev, TQueNodeHdr volatile *pNext)
{
    TQueNodeHdr volatile *prev = pPrev;
    TQueNodeHdr volatile *next = pNext;
    pNext->pPrev = prev;
    pPrev->pNext = next;
}

/*
 *  AddToHead():  Add node to queue head (last in queue) 
 */
void AddToHead( TQueNodeHdr *pNode, TQueNodeHdr *pListHead)
{
	InsertNode (pNode, pListHead, pListHead->pNext);
}

/*
 *  AddToTail():  Add node to queue tail (first in queue)
 */
void AddToTail( TQueNodeHdr volatile *pNode, TQueNodeHdr volatile *pListHead)
{
	InsertNode( pNode, pListHead->pPrev, pListHead );
}

/*
 *  DelFromTail():  Delete node from queue tail (first in queue)
 */
void DelFromTail (TQueNodeHdr volatile *pNode)
{
    TQueNodeHdr volatile *prev = pNode->pPrev;
    TQueNodeHdr volatile *next = pNode->pNext;
	RemoveNode (prev, next);
}



/*
 *              EXTERNAL  FUNCTIONS 
 *        =============================== 
 */


/** 
 * \fn     que_Create 
 * \brief  Create a queue. 
 * 
 * Allocate and init a queue object.
 * 
 * \note    
 * \param  uLimit            - Maximum items to store in queue
 * \param  uNodeHeaderOffset - Offset of NodeHeader field from the entry of the queued item.
 * \return Handle to the allocated queue 
 * \sa     que_Destroy
 */ 
void * que_Create (uint32_t uLimit, uint32_t uNodeHeaderOffset)
{
	TQueue *pQue;

	/* allocate queue module */
	pQue = os_malloc(sizeof(TQueue));
	
	if (!pQue)
	{
		return NULL;
	}
	
    os_memset (pQue, 0, sizeof(TQueue));

	/* Intialize the queue header */
    pQue->tHead.pNext = pQue->tHead.pPrev = &pQue->tHead;

	/* Set the Queue parameters */
	pQue->uLimit            = uLimit;
	pQue->uNodeHeaderOffset = uNodeHeaderOffset;
	return (void *)pQue;
}

/** 
 * \fn     que_Destroy
 * \brief  Destroy the queue. 
 * 
 * Free the queue memory.
 * 
 * \note   The queue's owner should first free the queued items!
 * \param  hQue - The queue object
 * \return 0 on success or -1 on failure
 * \sa     que_Create
 */ 
int que_Destroy (void * hQue)
{
    TQueue *pQue = (TQueue *)hQue;

    if (pQue)
	{
        /* free Queue object */
        os_free (pQue);
    }
	
    return 0;
}

/** 
 * \fn     que_Enqueue
 * \brief  Enqueue an item 
 * 
 * Enqueue an item at the queue's head (last in queue).
 * 
 * \note   
 * \param  hQue   - The queue object
 * \param  hItem  - Handle to queued item
 * \return 0 if item was queued, or -1 if not queued due to overflow
 * \sa     que_Dequeue, que_Requeue
 */ 
int que_Enqueue (void * hQue, void * hItem)
{
	TQueue      *pQue = (TQueue *)hQue;
    TQueNodeHdr *pQueNodeHdr;  /* the Node-Header in the given item */

    //pQue is not verified in order to avoid TP effect on data path
    /* Check queue limit */
	if(pQue->uCount < pQue->uLimit)
	{
        /* Find NodeHeader in the given item */
        pQueNodeHdr = (TQueNodeHdr *)(((uint8_t*)hItem) + pQue->uNodeHeaderOffset);

        /* Verify that pNext is NULL --> Sanity check that this item is not already linked to a queue */
        if (pQueNodeHdr->pNext)
        {
            /* Not an error since we have a case where a timer may expire twice in a row (in TxDataQueue) */
            return -1;
        }

        /* Enqueue item and increment items counter */
		AddToHead (pQueNodeHdr, &pQue->tHead);
		pQue->uCount++;

        return 0;
	}
	
	/* 
	 *  Queue is overflowed, return -1.
	 */


	return -1;
}


/** 
 * \fn     que_Dequeue
 * \brief  Dequeue an item 
 * 
 * Dequeue an item from the queue's tail (first in queue).
 * 
 * \note   
 * \param  hQue - The queue object
 * \return pointer to dequeued item or NULL if queue is empty
 * \sa     que_Enqueue, que_Requeue
 */ 
void * que_Dequeue (void * hQue)
{
    TQueue   *pQue = (TQueue *)hQue;
	void * hItem;
 
	//pQue is not verified in order to avoid TP effect on data path
    if (pQue->uCount)
    {
        /* Queue is not empty, take packet from the queue tail */

        /* find pointer to the node entry */
         hItem = (void *)(((uint8_t*)pQue->tHead.pPrev) - pQue->uNodeHeaderOffset);

         DelFromTail (pQue->tHead.pPrev);    /* remove node from the queue */

         pQue->uCount--;

         ((TQueNodeHdr *)(((uint8_t *)hItem) + pQue->uNodeHeaderOffset))->pNext = NULL;

         return (hItem);
    }
    
	/* Queue is empty */
    return NULL;
}


/** 
 * \fn     que_Requeue
 * \brief  Requeue an item 
 * 
 * Requeue an item at the queue's tail (first in queue).
 * 
 * \note   
 * \param  hQue   - The queue object
 * \param  hItem  - Handle to queued item
 * \return 0 if item was queued, or -1 if not queued due to overflow
 * \sa     que_Enqueue, que_Dequeue
 */ 
int que_Requeue (void * hQue, void * hItem)
{
    TQueue      *pQue = (TQueue *)hQue;
    TQueNodeHdr *pQueNodeHdr;  /* the NodeHeader in the given item */

    /* 
	 *  If queue's limits not exceeded add the packet to queue's tail and return 0
	 */
    if (pQue->uCount < pQue->uLimit)
	{
        /* Find NodeHeader in the given item */
        pQueNodeHdr = (TQueNodeHdr *)((uint8_t*)hItem + pQue->uNodeHeaderOffset);

        /* Verify that pNext is NULL --> Sanity check that this item is not already linked to a queue */
        if (pQueNodeHdr->pNext)
        {
            return -1;
        }

        /* Enqueue item and increment items counter */
		AddToTail (pQueNodeHdr, &pQue->tHead);
		pQue->uCount++;

		return 0;
    }
    
	/* 
	 *  Queue is overflowed, return -1.
	 *  Note: This is not expected in the current design, since Tx packet may be requeued
	 *          only right after it was dequeued in the same context so the queue can't be full.
	 */
    return -1;
}


/** 
 * \fn     que_Size
 * \brief  Return queue size 
 * 
 * Return number of items in queue.
 * 
 * \note   
 * \param  hQue - The queue object
 * \return uint32_t - the items count
 * \sa     
 */ 
uint32_t que_Size (void * hQue)
{
    TQueue *pQue = (TQueue *)hQue;
 
    return (pQue->uCount);
}


/** 
 * \fn     que_GetFirst
 * \brief  Return the first utem in the queue
 * 
 * Return the first item in the queue. It doesn't remove the
 * item from the queue.
 * 
 * \note   
 * \param  hQue - The queue object
 * \return void * - the item
 * \sa     
 */
void * que_GetFirst (void * hQue)
{
    TQueue   *pQue = (TQueue *)hQue;
	void * hItem = NULL;
 
    if (pQue->uCount)
    {
        /* Queue is not empty, get first node from the queue tail */
         hItem = (void *)((uint8_t*)pQue->tHead.pPrev - pQue->uNodeHeaderOffset);
    }

    return hItem;
}


/** 
 * \fn     que_GetNext
 * \brief  Return the next item in the queue
 * 
 * Return the next item in the queue.  It doesn't remove the
 * item from the queue.
 * 
 * \note   
 * \param  hQue - The queue object
 * \param  hItem - The current item in the queue
 * \return void * - the next item
 * \sa     
 */
void * que_GetNext (void * hQue, void * hItem)
{
    TQueue   *pQue = (TQueue *)hQue;
    TQueNodeHdr *pQueNodeHdr;
	void * hNextItem = NULL;

    pQueNodeHdr = (TQueNodeHdr *)((uint8_t*)hItem + pQue->uNodeHeaderOffset);

    if (pQueNodeHdr->pPrev != &pQue->tHead)
    {
        /* This is not the last item in the queue. Return next item */
         hNextItem = (void *)((uint8_t*)pQueNodeHdr->pPrev - pQue->uNodeHeaderOffset);
         return hNextItem;
    }

    return NULL;
}


/** 
 * \fn     que_DeleteItem
 * \brief  Delete the requested item from the queue
 * 
 * \note   
 * \param  hQue - The queue object
 * \param  hItem - The item to delete
 * \return int
 * \sa     
 */
int que_DeleteItem (void * hQue, void * hItem)
{
    TQueue   *pQue = (TQueue *)hQue;
    TQueNodeHdr *pQueNodeHdr;

    pQueNodeHdr = (TQueNodeHdr *)((uint8_t*)hItem + pQue->uNodeHeaderOffset);

    if (!pQueNodeHdr->pNext || !pQueNodeHdr->pPrev)
    {
        return -1;
    }

    RemoveNode(pQueNodeHdr->pPrev, pQueNodeHdr->pNext);
    pQue->uCount--;
    return 0;
}

uint32_t que_GetLimit (void * hQue)
{
    TQueue   *pQue = (TQueue *)hQue;
    return(pQue->uLimit);

}




