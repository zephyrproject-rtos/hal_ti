/* cs_asn1der.h
 *
 * Configuration Settings for the ANS1DER functions.
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

#ifndef INCLUDE_GUARD_CS_ASN1DER_H
#define INCLUDE_GUARD_CS_ASN1DER_H

/** The next switches are intended for footprint reduction.\n
 *  Uncomment to disable the function to reduce code size and overhead.\n
 *  Comment to enable the function
 */
#define ASN1DER_REMOVE_GETBOOLEAN
#define ASN1DER_REMOVE_GETENUM

#define ASN1DER_REMOVE_WRITEALGORITHMID
#define ASN1DER_REMOVE_WRITEBIGNUMBERINT
#define ASN1DER_REMOVE_WRITEBITSTR
#define ASN1DER_REMOVE_WRITEBOOLEAN
#define ASN1DER_REMOVE_WRITEENUM
#define ASN1DER_REMOVE_WRITEIA5STR
#define ASN1DER_REMOVE_WRITEINTEGER
#define ASN1DER_REMOVE_WRITENAMEDBITSTR
#define ASN1DER_REMOVE_WRITENULL
//#define ASN1DER_REMOVE_WRITEOBJECTID
#define ASN1DER_REMOVE_WRITEOCTETSTR
#define ASN1DER_REMOVE_WRITEPRINTSTR
#define ASN1DER_REMOVE_WRITERAWDATA
#define ASN1DER_REMOVE_WRITETAGGEDSTR
#define ASN1DER_REMOVE_WRITEUTF8STR

#define ASN1DER_REMOVE_TRAVERSESEQUENCE
#define ASN1DER_REMOVE_NAMEDDATA

#endif /* INCLUDE_GUARD_CS_ASN1DER_H */

/* end of file cs_asn1der.h */
