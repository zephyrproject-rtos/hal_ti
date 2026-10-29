/*
 * Copyright (c) 2023-2025, Texas Instruments Incorporated
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
 *  ======== Math.c ========
 */

#include <ti/drivers/utils/Math.h>

/*
 *  ======== Math_divideBy1000 ========
 */
uint32_t Math_divideBy1000(uint32_t dividend)
{
    uint32_t p1 = (dividend >> 16U) * (0x83126E98U >> 16U);
    uint32_t p2 = (dividend & 0xFFFFU) * (0x83126E98U >> 16U);
    p2 += (dividend >> 16U) * (0x83126E98U & 0xFFFFU);
    p2 >>= 7U;
    p2 += 222U;
    p1 += p2 >> 9U;
    return p1 >> 9U;
}

/*
 *  ======== Math_avgBestOfThreeValues ========
 */
uint16_t Math_avgBestOfThreeValues(uint16_t arr[])
{
    uint16_t diff01, diff02, diff12;
    uint16_t average;

    /* Calculate the difference of each combination of the three values */
    if (arr[0] > arr[1])
    {
        diff01 = arr[0] - arr[1];
    }
    else
    {
        diff01 = arr[1] - arr[0];
    }

    if (arr[0] > arr[2])
    {
        diff02 = arr[0] - arr[2];
    }
    else
    {
        diff02 = arr[2] - arr[0];
    }

    if (arr[1] > arr[2])
    {
        diff12 = arr[1] - arr[2];
    }
    else
    {
        diff12 = arr[2] - arr[1];
    }

    /* Calculate the average value of the two samples with the least difference */
    if (diff01 > diff02)
    {
        if (diff02 > diff12)
        {
            average = (arr[1] + arr[2]) / 2;
        }
        else
        {
            average = (arr[0] + arr[2]) / 2;
        }
    }
    else
    {
        if (diff01 > diff12)
        {
            average = (arr[1] + arr[2]) / 2;
        }
        else
        {
            average = (arr[0] + arr[1]) / 2;
        }
    }

    return average;
}

/*
 *  ======== Math_calcAverage ========
 */
uint16_t Math_calcAverage(uint16_t arr[], uint_fast16_t size)
{
    uint32_t sum     = 0;
    uint16_t average = 0;

    /* Check for empty array to avoid division by zero */
    if (size == 0)
    {
        return 0;
    }

    /* Calculate the sum of all elements */
    int i;
    for (i = 0; i < size; i++)
    {
        sum += arr[i];
    }

    /* Calculate the average */
    if (sum > 0)
    {
        average = sum / size;
    }

    return average;
}
