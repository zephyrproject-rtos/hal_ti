/*
 * Copyright (c) 2025, Texas Instruments Incorporated - http://www.ti.com
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

/* This file is a reference template for implementation of the
 * PSA Certified Firmware Update API v1.0.0
 */

#ifndef PSA_FWU_H
#define PSA_FWU_H

#include <stdint.h>

#include "fwu/1.0/psa/update.h"
#include "status-code/1.0/psa/error.h"

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************/
/*                           Enums and Defines                               */
/*****************************************************************************/

typedef enum {
    BL2_Slot_1,                 /* ID 0 */
    BL2_Slot_2,                 /* ID 1 */
    WSOC_OR_RFTool_Slot_1,      /* ID 2 */
    WSOC_OR_RFTool_Slot_2,      /* ID 3 */
    Vendor_Image_Slot_1,        /* ID 4 */
    Vendor_Image_Slot_2,        /* ID 5 */
    Vendor_BL3_Slot_1,          /* ID 6 */
    Vendor_BL3_Slot_2,          /* ID 7 */
    MAX_COMPONENT_ID
} PSA_FWU_Component_ID_e;

#define MANIFEST_INTEGRITY_SIZE_IN_WORDS (4)
/*****************************************************************************/
/*                           Structures                                      */
/*****************************************************************************/

/* This union struct holds M33->M3 Scratchpad for FWU */
#if 0
typedef union
{
    struct
    {
        uint16_t M33_REQUEST : 1; /* BITS:[0:0] */
        uint16_t START_MODE : 3; /* BITS:[1:3] */
        uint16_t VALIDATION_BITMAP : 4; /* BITS:[4:7] */
        uint16_t COMMIT_BITMAP : 4; /* BITS:[8:11] */
        uint16_t COMMIT_FUSE_UPDATE_BITMAP : 4; /* BITS:[12:15] */
    } FIELD;
    uint16_t ALL;
} PSA_FWU_SCRATCHPAD;
#endif



/* This struct holds the MAGIC Number format entity  */
typedef struct
{
    uint32_t Magic_Number;
} PSA_FWU_Magic_t;

/* This struct holds the GPE Header format entities */
typedef struct
{
    PSA_FWU_Magic_t ih_magic;
    uint32_t        ih_load_addr;
    uint16_t        ih_hdr_size;
    uint16_t        ih_protect_tlv_size;
    uint32_t        ih_img_size;
    uint32_t        ih_flags;
} PSA_FWU_GPEHeader_t;

/* This struct holds the GPE Version format entities */
typedef struct
{
    uint8_t  iv_major;
    uint8_t  iv_minor;
    uint16_t iv_revision;
    uint32_t iv_build_num;
} PSA_FWU_GPEVersion_t;

/* This struct holds the GPE Manifest format entities */
typedef struct
{
    PSA_FWU_GPEHeader_t  GPE_Header;
    PSA_FWU_GPEVersion_t GPE_Version;
    PSA_FWU_Magic_t      GPE_Magic;
} PSA_FWU_GPEManifest_t;

typedef struct
{
  uint32_t              Manifest_Integrity[MANIFEST_INTEGRITY_SIZE_IN_WORDS];
} PSA_FWU_Manifest_Integrity_t;

#if 0
/* This struct holds the TLV info entity  */ - need more
typedef struct
{
    uint16_t it_magic;      /* Secure or non Secure*/
    uint16_t it_tlv_tot;
} PSA_FWU_GPETLVInf_t;

/* This struct holds the GPE MAGIC format entity  */ - need more
typedef struct
{
    uint16_t it_type;
    uint16_t it_len;
} PSA_FWU_GPETLVHeader_t;

/* This struct holds the GPE MAGIC format entity  */ - need more
typedef struct
{
    uint16_t it_type;
    uint16_t reserved;
    uint32_t *pTLV_Table;
} PSA_FWU_GPETLVParameter_t;

/* This struct holds the GPE MAGIC format entity  */ - need more
typedef struct
{
    PSA_FWU_GPETLVHeader_t TLV_Header;
    PSA_FWU_GPETLVParameter_t *pTLV_Record;
} PSA_FWU_GPEManifestTLV_t;

/* This struct holds the GPE MAGIC format entity  */ - need more
typedef struct
{
    PSA_FWU_GPETLVHeader_t TLV_Header;
    uint32_t *TLV_Parameter;
} PSA_FWU_GPEManifestTLV_t;

/* This struct holds the GPE MAGIC format entity  */ - need more
typedef struct
{
    uint32_t GPE_Magic;
} PSA_FWU_GPETLV_t;

/* This struct holds the GPE MAGIC format entity  */ - need more
typedef struct
{
    PSA_FWU_GPETLVInf_t TLV_Info;
    PSA_FWU_GPEManifestTLV_t Manifest_TLV;
    PSA_FWU_GPETLV_t GPE_Magic;
} PSA_FWU_GPETLVZone_t;



/* This struct holds the GPE Trailer entities  */
typedef struct
{
    uint32_t Swap_Status;
    uint32_t Encryption_key_0[4];
    uint32_t Encryption_key_1[4];
    uint8_t  Swap_Size;
    uint8_t  Swap_info;
    uint8_t  Copy_Done;
    uint8_t  Image_OK;
    uint32_t Magic[4];
} PSA_FWU_GPETrailer_t;

/* This struct holds the GPE Slot entities */
typedef struct
{
    uint32_t              Manifest_Integrity[4];
    PSA_FWU_GPEManifest_t Manifest;
    uint32_t             *GPE_Data;
    PSA_FWU_GPETLVZone_t *Protected_Zone;
    PSA_FWU_GPETLVZone_t *Non_Protected_Zone;
    PSA_FWU_GPETrailer_t *GPETrailer;

} PSA_FWU_GPESlot_t;
#endif

/* This struct holds the GPE Manifest entities */
typedef struct
{
    PSA_FWU_Manifest_Integrity_t Manifest_Integrity;
    PSA_FWU_GPEManifest_t Manifest;
} PSA_FWU_GPESlot_t;

/*****************************************************************************/
/*                           Size of definitions                             */
/*****************************************************************************/
/* Defines the size of manifest integrity */
#define TI_FWU_MANIFEST_INTEGRITY_SIZE      (sizeof(PSA_FWU_Manifest_Integrity_t))

/* Defines the size of magic number */
#define TI_FWU_MAGIC_NUMBER_SIZE            (sizeof(PSA_FWU_Magic_t))

/* Defines the size of the GPE manifest without ih_magic */
#define TI_FWU_GPE_MANIFEST_SECTION_SIZE    (sizeof(PSA_FWU_GPEManifest_t) - TI_FWU_MAGIC_NUMBER_SIZE)

/* Defines the size of the full manifest (GPE manifest and manifest integrity) */
#define TI_FWU_MANIFEST_SIZE                (sizeof(PSA_FWU_GPESlot_t))


/*****************************************************************************/
/*                           Static Functions                                */
/*****************************************************************************/


/*****************************************************************************/
/*                           Functions Prototype                             */
/*****************************************************************************/

void psa_fwu_init(void);



#ifdef __cplusplus
}
#endif

#endif // PSA_FWU_H
