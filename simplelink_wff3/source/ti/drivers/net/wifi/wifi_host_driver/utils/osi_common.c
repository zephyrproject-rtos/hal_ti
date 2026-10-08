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
#include <time.h>
#include <limits.h>
#include <stdio.h>
#include <ctype.h>
#include "osi_kernel.h"
#include <stdlib.h>

void os_sleep(os_time_t sec, os_time_t usec)
{
    if (sec)
    {
        osi_Sleep(sec);
    }
    if (usec)
    {
        osi_uSleep(usec);
    }
}


int os_get_time(struct os_time *t)
{
    uint32_t time;

    time = osi_GetTimeMS();
    t->sec = (os_time_t)(time / 1000);
    t->usec = (os_time_t) ((time % 1000) * 1000);

    return 0;
}

int os_get_reltime(struct os_reltime *t)
{
    uint32_t time;

    time = osi_GetTimeMS();
    t->sec = (os_time_t)(time / 1000);
    t->usec = (os_time_t) ((time % 1000) * 1000);

    return 0;
}

int os_gmtime(os_time_t t, struct os_tm *tm)
{
    return 0;
}

int os_daemonize(const char *pid_file)
{
    return 0;
}

void os_daemonize_terminate(const char *pid_file)
{
}

int os_get_random(unsigned char *buf, size_t len)
{
    size_t i;

    for (i=0 ; i<len ; ++i)
    {
        buf[i] = rand();
    }

    return 0;
}

unsigned long os_random(void)
{
    return rand();
}

char * os_readfile(const char *name, size_t *len)
{
    return NULL;
}

int os_strncasecmp(const char *s1, const char *s2, size_t n)
{
    const unsigned char *p1 = (const unsigned char *)s1;
    const unsigned char *p2 = (const unsigned char *)s2;

    int result;
    int count=0;
    while (( (result = tolower(*p1) - tolower(*p2++)) == 0 ) && (count < n)) {
        if (*p1++ == '\0') {
            break;
        }
        count++;
    }
    return result;
}

char * os_strdup(const char *s)
{
    char *res;
    size_t len;
    if (s == NULL)
        return NULL;
    len = os_strlen(s);
    res = os_malloc(len + 1);
    if (res)
        os_memcpy(res, s, len + 1);
    return res;
}


void * os_memdup(const void *src, size_t len)
{
    void *r;
    
    if (len)
        r = os_malloc(len);
    else
        r = os_malloc(1);

    if (r)
        os_memcpy(r, src, len);
    return r;
}

char * os_strchr(const char *s, int c)
{
    while (*s) {
        if (*s == c)
            return (char *) s;
        s++;
    }
    return NULL;
}

size_t os_strlcpy(char *dest, const char *src, size_t siz)
{
    const char *s = src;
    size_t left = siz;

    if (left) {
        /* Copy string up to the maximum size of the dest buffer */
        while (--left != 0) {
            if ((*dest++ = *s++) == '\0')
                break;
        }
    }

    if (left == 0) {
        /* Not enough room for the string; force NUL-termination */
        if (siz != 0)
            *dest = '\0';
        while (*s++)
            ; /* determine total src string length */
    }

    return s - src - 1;
}

int os_memcmp_const(const void *a, const void *b, size_t len)
{
    const UINT8 *aa = a;
    const UINT8 *bb = b;
    size_t i;
    UINT8 res;

    for (res = 0, i = 0; i < len; i++)
        res |= aa[i] ^ bb[i];

    return res;
}







