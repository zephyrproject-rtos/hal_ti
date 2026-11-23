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

#define ERRNO_ALREADY_PROVIDED 1 /* errno provided by lwip */

#ifndef ERRNO_ALREADY_PROVIDED

#ifndef _ERRNO /* this is when errno comes from the compiler, do not redfeine the errno again */
#ifndef _WIRELESS_H
#define _WIRELESS_H

#ifndef EBUSY
#define EBUSY (11)
#endif

/* ERROR CODES */

#define ESUCCESS                    0

#define EERROR                     -1

#define ENOTAVAILABLE
#define EOVFLW
#define EILLEGAL


#ifdef ENOENT
#undef ENOENT
#endif
#define ENOENT          2               /* No such file or directory */


#ifdef EBUSY
#undef EBUSY
#endif
#define EBUSY           16              /* Device busy */

#ifndef EAGAIN
#define EAGAIN          (11)              /* Resource temporarily unavailable */
#endif

#ifdef _EOPNOTSUPP
#undef _EOPNOTSUPP
#endif
#define _EOPNOTSUPP      95              /* Operation not supported */

#ifdef ENOTSUP
#undef ENOTSUP
#endif
#define ENOTSUP         _EOPNOTSUPP      /* Operation not supported */

#ifndef EIO
#define EIO             5               /* Input/output error */
#endif

#endif  /* _WIRELESS_H */
#endif /*  _ERRNO */
#endif
