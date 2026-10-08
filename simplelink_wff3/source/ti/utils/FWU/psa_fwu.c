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

// SPDX-FileCopyrightText: Copyright 2020-2023 Arm Limited and/or its affiliates <open-source-office@arm.com>
// SPDX-License-Identifier: Apache-2.0

/*
 *  ======== psa_fwu.c ========
 * This file is a reference template for implementation of the
 * PSA Certified Firmware Update API v1.0.0
 */

//#include <stddef.h>
//#include <stdint.h>
//#include "osi_kernel.h"

#include <stdbool.h>
#include "psa_fwu.h"
#include "otfde_driver.h"
//#include "fw_status.h"
#include "XMEMWFF3.h"
#include "osi_kernel.h"
#include "PowerWFF3.h"

/*****************************************************************************/
/*                           Enums and Defines                               */
/*****************************************************************************/

typedef enum {
    BL2,                 /* ID 0 */
    WSOC_OR_RFTool,      /* ID 1 */
    Vendor_Image,        /* ID 2 */
    Vendor_BL3,          /* ID 3 */
    MAX_COMPONENT_TYPES
} PSA_FWU_Component_TYPES_e;

#define PRIMARY                     (1)
#define NOT_PRIMARY                 (0)
#define ACTIVE                      (1)
#define LOADED                      (0)
#define SECTOR_SIZE                 (4096)

#define SLOT_1_OK                   (0x01)
#define SLOT_2_OK                   (0x02)
#define OTA_VER_CONFLICT            (0x04)
#define ALTERNATE_OTA               (0x08)
#define NO_VALID_MAIN               (0x10)
#define OTA_DONT_CARE               (0x20)
#define BOTH_SLOTS_INVALID          (0x40)
#define AUTH_ERROR                  (0x80)

#define NO_OTA                      (0x0)
#define OTA_VALIDATE                (0x1)
#define OTA_COMMIT                  (0x2)
#define OTA_COMMIT_AND_PROTECT      (0x3)

#define OTA_VALIDATE_BIT            (0x1)
#define OTA_COMMIT_BIT              (0x2)
#define OTA_COMMIT_AND_PROTECT_BIT  (0x4)

#define SUCCESS                     (0x0)
#define ROLLBACK_NEXT_BOOT          (0x1)
#define GENERAL_ERROR               (0x2)
#define SECURITY_FAILURE            (0x3)

#define READ_STATUS_SUCCESS         (0x00)
#define READ_STATUS_SECONDARY_SLOT  (0x01)
#define READ_STATUS_NO_OTA          (0x02)
#define READ_STATUS_ALREADY_PRIMARY (0x03)
#define READ_STATUS_NOT_SUPPORTED   (0x04)
#define READ_STATUS_ERROR           (0x05)

#define GPE_ACTIVE                  (0x0)
#define GPE_STAGED                  (0x1)
#define GPE_DIRTY                   (0x2)
#define GPE_ERASED                  (0x3)

#define MAGIC_MISSING               (0x0)
#define MAGIC_EXISTS                (0x1)

#define COMPONENT_READ_STATUS_OK     (0x0)
#define COMPONENT_READ_STATUS_EMPTY  (0x1)
#define COMPONENT_READ_STATUS_FAIL   (0x2)

#define COMPONENT_FLOW_STATE_RESET_VALIDATE  (8)
#define COMPONENT_FLOW_STATE_RESET_COMMIT    (9)

#define GPE_DATA_VERSION_OFFSET   (0x10)

#define PRCM_AON_NON_SECURED__PRCM_CORE_STOP_ENABLE__ADDR    (0x41091060)
#define PRCM_SCRATCHPAD__PRCM_SCPAD2__ADDR                   (0x41099000)
#define REGISTER(address) (*(volatile uint32 *)(address))

#define IS_VALID_COMPONENT_ID(componentID)                        ( componentID < MAX_COMPONENT_ID )
#define IS_COMPONENT_ID_PRIMARY(componentID)                      ( gImageStore[componentID].ComponentInfo.impl.Primary == PRIMARY )
#define IS_COMPONENT_ID_ACTIVE(componentID)                       ( gImageStore[componentID].ComponentInfo.impl.running_status == ACTIVE )
#define IS_WSOC_COMPONENT(componentID)                            ( componentID == WSOC_OR_RFTool_Slot_1 || componentID == WSOC_OR_RFTool_Slot_2 )
#define UPDATE_COMPONENT_INFO_AND_RETURN_ERROR(state, error)        update_ComponentInfo(component, state, error); \
                                                                    return error;
extern uint32_t _Boot_report_address;
#define BOOT_REPORT_ADDR ((uint32_t) (&_Boot_report_address))

/*****************************************************************************/
/*                           Structures                                      */
/*****************************************************************************/
typedef union
{
    struct
    {
        uint16_t BL2                      : 3; /* BITS:[0:2] */
        uint16_t WSOC_OR_RFTOOL           : 3; /* BITS:[3:5] */
        uint16_t VENDOR_BL3               : 3; /* BITS:[6:8] */
        uint16_t VENDOR_IMAGE             : 3; /* BITS:[9:11] */
        uint16_t START_MODE               : 3; /* BITS:[12:14] */
        uint16_t M33_REQUEST              : 1; /* BITS:[15:15] */
    } FIELD;
    uint16_t ALL;
} PSA_FWU_SCRATCHPAD_FOR_TYPES;

typedef union
{
    struct
    {
        uint8_t REQ_TYPE    : 2; /* BITS:[0-1] */
        uint8_t REQ_STATUS  : 6; /* BITS:[2-7] */
    } FIELD;
    uint8_t ALL;
} PSA_FWU_Request_Report;

typedef struct
{
    PSA_FWU_Request_Report  Logical_Slot_Address;
    uint8_t                 Image_Select_Report;
} PSA_FWU_Report_Structure_t;

typedef struct
{
    uint32_t  Physical_Slot_Address;
    uint32_t  Logical_Slot_Address;
    uint32_t  Region_Size;
} PSA_FWU_Slot_Address_t;

/* This struct holds the starting pointer for the slot of specific ComponentID
   and if this slot is primary or not */
typedef struct
{
    psa_fwu_component_t      ComponentID;
    psa_fwu_component_info_t ComponentInfo;
    XMEM_Handle              XMEMhandle;
} PSA_FWU_Slot_Info_t;

/*****************************************************************************/
/*                           Global parameters                               */
/*****************************************************************************/
PSA_FWU_Magic_t gGPEMagicNumber[MAX_COMPONENT_TYPES] = {
    0x690c47c2 ,  /* BL2          */
    0x690c47c2 ,  /* WSOC_OR_RFTool */
    0x690c47c2 ,  /* Vendor_Image */
    0x690c47c2    /* Vendor_BL3   */
};

PSA_FWU_Slot_Address_t gSlotAddress[MAX_COMPONENT_ID];

/* Alternate addressing for vendor image and BL3 slot swap (secondary slot active) */
PSA_FWU_Slot_Address_t gSlotAddressAlternate[4];

PSA_FWU_Report_Structure_t gOTAReport[MAX_COMPONENT_TYPES];

PSA_FWU_Slot_Info_t gImageStore[MAX_COMPONENT_ID] = {0};

uint16_t Request_type[MAX_COMPONENT_TYPES] = {0};

static bool isInitialized = false;

/*****************************************************************************/
/*                           Extern parameters                               */
/*****************************************************************************/

/* BL2 Slot 1 memory configuration */
extern uint32_t bl2_physical_slot_1_address;
extern uint32_t bl2_logical_slot_1_address;
extern uint32_t bl2_slot_1_region_size;

/* BL2 Slot 2 memory configuration */
extern uint32_t bl2_physical_slot_2_address;
extern uint32_t bl2_logical_slot_2_address;
extern uint32_t bl2_slot_2_region_size;

/* WiFi Connectivity Slot 1 memory configuration */
extern uint32_t wifi_connectivity_physical_slot_1_address;
extern uint32_t wifi_connectivity_logical_slot_1_address;
extern uint32_t wifi_connectivity_slot_1_region_size;

/* WiFi Connectivity Slot 2 memory configuration */
extern uint32_t wifi_connectivity_physical_slot_2_address;
extern uint32_t wifi_connectivity_logical_slot_2_address;
extern uint32_t wifi_connectivity_slot_2_region_size;

/* Vendor Image Slot 1 memory configuration */
extern uint32_t vendor_image_physical_slot_1_address;
extern uint32_t vendor_image_logical_slot_1_address;
extern uint32_t vendor_image_slot_1_region_size;

/* Vendor Image Slot 2 memory configuration */
extern uint32_t vendor_image_physical_slot_2_address;
extern uint32_t vendor_image_logical_slot_2_address;
extern uint32_t vendor_image_slot_2_region_size;

/* Vendor BL3 Slot 1 memory configuration */
extern uint32_t vendor_bl3_physical_slot_1_address;
extern uint32_t vendor_bl3_logical_slot_1_address;
extern uint32_t vendor_bl3_slot_1_region_size;

/* Vendor BL3 Slot 2 memory configuration */
extern uint32_t vendor_bl3_physical_slot_2_address;
extern uint32_t vendor_bl3_logical_slot_2_address;
extern uint32_t vendor_bl3_slot_2_region_size;

/*****************************************************************************/
/*                      Utility Functions Prototypes                         */
/*****************************************************************************/
uint32_t     Retrieve_active_and_loaded_components(psa_fwu_component_t component, psa_fwu_component_t *active_component, psa_fwu_component_t *loaded_component);
void         Create_component_XMEMHandle(psa_fwu_component_t component, uint32_t readStatus);
uint8_t      Magic_validation_and_coping_version(psa_fwu_component_t component);
psa_status_t is_manifest_integrity_valid(uint32_t *manifest);
psa_status_t is_GPE_magic_number_valid(psa_fwu_component_t component, PSA_FWU_Magic_t *GPE_magic_number);
bool         isVersionNewer(psa_fwu_image_version_t* v1, psa_fwu_image_version_t* v2);
uint32_t     read_component_state_from_flash(psa_fwu_component_t component, int8_t *state, int8_t *reset_state);
psa_status_t write_component_multiple_state_in_flash(psa_fwu_component_t component, uint8_t states);
psa_status_t write_component_state_in_flash(psa_fwu_component_t component, uint8_t state);
void         update_ComponentGPEState(psa_fwu_component_t component, uint8_t state);
void         update_ComponentInfo(psa_fwu_component_t component, uint8_t state, psa_status_t error);
psa_status_t validation_check(psa_fwu_component_t component, uint8_t state);
bool         flow_check(psa_fwu_component_t component, uint8_t state);
psa_status_t erase_GPE(psa_fwu_component_t component);
uint32_t     Read_report_and_update_status(psa_fwu_component_t component);
void         update_component_loaded_state(psa_fwu_component_t component, uint32_t readReportStatus);
void         initialize_slot_addresses(void);

/*****************************************************************************/
/*                      Utility Functions implementation                     */
/*****************************************************************************/
psa_status_t is_manifest_integrity_valid(uint32_t *manifest)
{
    uint8_t Index;

    for (Index = 0; Index < MANIFEST_INTEGRITY_SIZE_IN_WORDS; Index++)
    {
        if (manifest[Index] != 0xFFFFFFFF)
        {
            return PSA_SUCCESS;
        }
    }

    return PSA_ERROR_INVALID_SIGNATURE;
}

psa_status_t is_GPE_magic_number_valid(psa_fwu_component_t component, PSA_FWU_Magic_t *GPE_magic_number)
{
    uint8_t Index;

    if (GPE_magic_number->Magic_Number != gGPEMagicNumber[component >> 1].Magic_Number)
    {
        return PSA_ERROR_INVALID_ARGUMENT;
    }
    return PSA_SUCCESS;
}

bool isVersionNewer(psa_fwu_image_version_t* v1, psa_fwu_image_version_t* v2)
{
    if (v1->major != v2->major) return v1->major > v2->major;
    if (v1->minor != v2->minor) return v1->minor > v2->minor;
    if (v1->patch != v2->patch) return v1->patch > v2->patch;
    return v1->build > v2->build;
}

uint32_t read_component_state_from_flash(psa_fwu_component_t component, int8_t *state, int8_t *reset_state)
{
    int_fast16_t retXMEM;
    uint32_t flow_state;

    retXMEM = XMEMWFF3_read(gImageStore[component].XMEMhandle, SECTOR_SIZE - ( TI_FWU_MAGIC_NUMBER_SIZE + TI_FWU_MANIFEST_INTEGRITY_SIZE + sizeof(uint32_t) ), &(flow_state), sizeof(uint32_t), XMEM_READ_STIG);
    if (retXMEM != XMEM_STATUS_SUCCESS)
    {
        *state = PSA_FWU_FAILED;
        return COMPONENT_READ_STATUS_FAIL;
    }

    if ( flow_state == 0xFFFFFFFF )
    {
        *state = PSA_FWU_FAILED;
        return COMPONENT_READ_STATUS_EMPTY;
    }

    if ((~flow_state) & (1 << COMPONENT_FLOW_STATE_RESET_COMMIT))
    {
        *reset_state = COMPONENT_FLOW_STATE_RESET_COMMIT;
    }
    else if ((~flow_state) & (1 << COMPONENT_FLOW_STATE_RESET_VALIDATE))
    {
        *reset_state = COMPONENT_FLOW_STATE_RESET_VALIDATE;
    }



    if ((~flow_state) & (1 << PSA_FWU_FAILED))
    {
        *state = PSA_FWU_FAILED;
    }
    else if ((~flow_state) & (1 << PSA_FWU_REJECTED))
    {
        *state = PSA_FWU_REJECTED;
    }
    else
    {
        for (*state = 7; *state > 0; (*state)--)
        {
            if ( !(flow_state & (1 << (*state))) )
            {
                break;
            }
        }

    }

    return COMPONENT_READ_STATUS_OK;
}

psa_status_t write_component_multiple_state_in_flash(psa_fwu_component_t component, uint8_t states)
{
    int_fast16_t retXMEM;
    uint32_t flow_state = (0xFFFFFFFF & ~(states));

    retXMEM = XMEMWFF3_write(gImageStore[component].XMEMhandle, SECTOR_SIZE - ( TI_FWU_MAGIC_NUMBER_SIZE + TI_FWU_MANIFEST_INTEGRITY_SIZE + sizeof(uint32_t) ), &(flow_state), sizeof(uint32_t), XMEM_WRITE_STIG);
    if (retXMEM != XMEM_STATUS_SUCCESS)
    {
        return PSA_ERROR_STORAGE_FAILURE;
    }

    return PSA_SUCCESS;
}

psa_status_t write_component_state_in_flash(psa_fwu_component_t component, uint8_t state)
{
    int_fast16_t retXMEM;
    uint32_t flow_state = (0xFFFFFFFF & ~(1 << state));

    retXMEM = XMEMWFF3_write(gImageStore[component].XMEMhandle, SECTOR_SIZE - ( TI_FWU_MAGIC_NUMBER_SIZE + TI_FWU_MANIFEST_INTEGRITY_SIZE + sizeof(uint32_t) ), &(flow_state), sizeof(uint32_t), XMEM_WRITE_STIG);
    if (retXMEM != XMEM_STATUS_SUCCESS)
    {
        return PSA_ERROR_STORAGE_FAILURE;
    }

    return PSA_SUCCESS;
}

psa_status_t validation_check(psa_fwu_component_t component, uint8_t state)
{
    if (!(IS_VALID_COMPONENT_ID(component)))
    {
        UPDATE_COMPONENT_INFO_AND_RETURN_ERROR(state ,PSA_ERROR_DOES_NOT_EXIST)
    }

    if (IS_COMPONENT_ID_PRIMARY(component))
    {
        UPDATE_COMPONENT_INFO_AND_RETURN_ERROR(state ,PSA_ERROR_NOT_PERMITTED)
    }
    return PSA_SUCCESS;
}

bool flow_check(psa_fwu_component_t component, uint8_t state)
{
    if (gImageStore[component].ComponentInfo.state != state)
    {
        return false;
    }

    return true;
}

psa_status_t erase_GPE(psa_fwu_component_t component)
{
    int_fast16_t retXMEM;
    uint32_t SectorIndex = 1;

    while (SectorIndex < ((gSlotAddress[component].Region_Size) >> 12))
    {
        retXMEM = XMEMWFF3_erase(gImageStore[component].XMEMhandle, SECTOR_SIZE * SectorIndex, SECTOR_SIZE);
        if (retXMEM != XMEM_STATUS_SUCCESS)
        {
            UPDATE_COMPONENT_INFO_AND_RETURN_ERROR(PSA_FWU_FAILED ,PSA_ERROR_STORAGE_FAILURE)
        }
        SectorIndex++;
    }

    retXMEM = XMEMWFF3_erase(gImageStore[component].XMEMhandle, 0, SECTOR_SIZE);
    if (retXMEM != XMEM_STATUS_SUCCESS)
    {
        UPDATE_COMPONENT_INFO_AND_RETURN_ERROR(PSA_FWU_FAILED ,PSA_ERROR_STORAGE_FAILURE)
    }
    return PSA_SUCCESS;
}


uint32_t Retrieve_active_and_loaded_components(psa_fwu_component_t component, psa_fwu_component_t *active_component, psa_fwu_component_t *loaded_component)
{
    if (gOTAReport[component>>1].Image_Select_Report & SLOT_1_OK)
    {
        *active_component = component;
        *loaded_component = component ^ 0x1;
    }
    else if (gOTAReport[component>>1].Image_Select_Report & SLOT_2_OK)
    {
        *active_component = component ^ 0x1;
        *loaded_component = component;
        return READ_STATUS_SECONDARY_SLOT;
    }
    else
    {
        return READ_STATUS_ERROR;
    }
    return READ_STATUS_SUCCESS;
}

void Create_component_XMEMHandle(psa_fwu_component_t component, uint32_t readStatus)
{
    psa_fwu_component_t AlternateImage_component;
    XMEM_Params params;

    if ((readStatus == READ_STATUS_SECONDARY_SLOT) && (component >= Vendor_Image_Slot_1))
    {
        AlternateImage_component = component - Vendor_Image_Slot_1;
        params.regionBase = gSlotAddressAlternate[AlternateImage_component].Physical_Slot_Address;
        params.regionStartAddr = gSlotAddressAlternate[AlternateImage_component].Logical_Slot_Address;
        params.regionSize = gSlotAddressAlternate[AlternateImage_component].Region_Size;
    }
    else
    {
        params.regionBase = gSlotAddress[component].Physical_Slot_Address;
        params.regionStartAddr = gSlotAddress[component].Logical_Slot_Address;
        params.regionSize = gSlotAddress[component].Region_Size;
    }

    params.deviceNum = 0;
    gImageStore[component].XMEMhandle = XMEMWFF3_open(&params);

}
uint8_t Magic_validation_and_coping_version(psa_fwu_component_t component)

{
    int_fast16_t retXMEM;
    PSA_FWU_GPESlot_t GPE_Manifest;

    retXMEM = XMEMWFF3_read(gImageStore[component].XMEMhandle, SECTOR_SIZE - TI_FWU_MAGIC_NUMBER_SIZE, &(GPE_Manifest.Manifest.GPE_Header.ih_magic.Magic_Number), TI_FWU_MAGIC_NUMBER_SIZE, XMEM_READ_STIG);
    if (retXMEM == XMEM_STATUS_SUCCESS)
    {
        if (is_GPE_magic_number_valid(component, &(GPE_Manifest.Manifest.GPE_Header.ih_magic)) == PSA_SUCCESS)
        {
            retXMEM = XMEMWFF3_read(gImageStore[component].XMEMhandle, SECTOR_SIZE, (void *)((uint8_t *)&(GPE_Manifest.Manifest) + TI_FWU_MAGIC_NUMBER_SIZE), sizeof(PSA_FWU_GPEManifest_t) - TI_FWU_MAGIC_NUMBER_SIZE, 0);
            if (retXMEM == XMEM_STATUS_SUCCESS)
            {
                if (is_GPE_magic_number_valid(component, &(GPE_Manifest.Manifest.GPE_Header.ih_magic)) != PSA_SUCCESS)
                {
                    return MAGIC_MISSING;
                }
                else
                {
                    os_memcpy(&(gImageStore[component].ComponentInfo.version), &(GPE_Manifest.Manifest.GPE_Version), sizeof(PSA_FWU_GPEVersion_t));
                    return MAGIC_EXISTS;
                }
            }
        }
    }
    return MAGIC_MISSING;
}

void update_ComponentGPEState(psa_fwu_component_t component, uint8_t state)
{
    switch (state)
    {
        case PSA_FWU_UPDATED:
        {
            gImageStore[component].ComponentInfo.impl.GPE_state = GPE_ACTIVE;
        }
        break;
        case PSA_FWU_WRITING:
        case PSA_FWU_STAGED:
        case PSA_FWU_CANDIDATE:
        case PSA_FWU_TRIAL:
        {
            gImageStore[component].ComponentInfo.impl.GPE_state = GPE_STAGED;
        }
        break;
        case PSA_FWU_FAILED:
        case PSA_FWU_REJECTED:
        {
            gImageStore[component].ComponentInfo.impl.GPE_state = GPE_DIRTY;
        }
        break;
        case PSA_FWU_READY:
        {
            gImageStore[component].ComponentInfo.impl.GPE_state = GPE_ERASED;
        }
        break;
    }
    return;
}

void update_ComponentInfo(psa_fwu_component_t component, uint8_t state, psa_status_t error)
{
    gImageStore[component].ComponentInfo.error = error;

    if (error == PSA_SUCCESS)
    {
        gImageStore[component].ComponentInfo.state = state;
        write_component_state_in_flash(component, state);

        update_ComponentGPEState(component, state);
    }
    return;
}

uint32_t Read_report_and_update_status(psa_fwu_component_t component)
{
    int8_t flash_state;
    int8_t reset_state;
    uint32_t readStateRetVal;

    psa_fwu_component_info_t *info = &(gImageStore[component].ComponentInfo);


    info->impl.request_type = gOTAReport[component>>1].Logical_Slot_Address.FIELD.REQ_TYPE;
    info->impl.extended_report_status = gOTAReport[component>>1].Image_Select_Report;

    uint8_t magic_exists = Magic_validation_and_coping_version(component);
    readStateRetVal = read_component_state_from_flash(component, &flash_state, &reset_state);
    info->state = flash_state;
    info->impl.running_status = ACTIVE;
    info->impl.Primary = PRIMARY;

    if (gOTAReport[component>>1].Logical_Slot_Address.FIELD.REQ_TYPE == NO_OTA)
    {
        if ( (info->impl.extended_report_status & AUTH_ERROR) ||
             (info->impl.extended_report_status & NO_VALID_MAIN) ||
             (info->impl.extended_report_status & BOTH_SLOTS_INVALID) )
        {
            info->error = PSA_ERROR_DATA_INVALID;
        }
        else
        {
            info->error = PSA_SUCCESS;
        }

        if (readStateRetVal == COMPONENT_READ_STATUS_EMPTY)
        {
            if (info->error == PSA_ERROR_DATA_INVALID)
            {
                info->impl.running_status = LOADED;
                info->impl.Primary = NOT_PRIMARY;
            }
            info->state = PSA_FWU_UPDATED;
            update_ComponentInfo(component, info->state, info->error);

            flash_state = (1 << PSA_FWU_TRIAL) | (1 << PSA_FWU_STAGED) | (1 << PSA_FWU_CANDIDATE) | (1 << PSA_FWU_WRITING) | (1 << PSA_FWU_READY);
            write_component_multiple_state_in_flash(component, flash_state);
        }

        return READ_STATUS_NO_OTA;
    }

    //Shouldn't happen
    #if 0
    if (readStateRetVal == COMPONENT_READ_STATUS_EMPTY)
    {
        flash_state = (1 << PSA_FWU_TRIAL) | (1 << PSA_FWU_STAGED) | (1 << PSA_FWU_CANDIDATE) | (1 << PSA_FWU_WRITING) | (1 << PSA_FWU_READY);
        write_component_multiple_state_in_flash(component, flash_state);
    }
    #endif

    if (gOTAReport[component>>1].Logical_Slot_Address.FIELD.REQ_STATUS == SUCCESS)
    {
        if (!(gOTAReport[component>>1].Image_Select_Report & ALTERNATE_OTA))
        {
            if (flow_check(component, PSA_FWU_STAGED))
            {
                if (info->impl.request_type == OTA_VALIDATE)
                {
                    info->impl.Primary = NOT_PRIMARY;
                    info->state = PSA_FWU_TRIAL;
                }
            }
            else if (flow_check(component, PSA_FWU_TRIAL))
            {
                if (info->impl.request_type == OTA_COMMIT)
                {
                    info->state = PSA_FWU_UPDATED;
                }
                else if (info->impl.request_type == OTA_COMMIT_AND_PROTECT)
                {
                    info->state = PSA_FWU_UPDATED;
                }
            }
        }
        info->error = PSA_SUCCESS;
    }
    else if (gOTAReport[component>>1].Logical_Slot_Address.FIELD.REQ_STATUS == ROLLBACK_NEXT_BOOT)
    {
        if (info->impl.request_type == OTA_COMMIT_AND_PROTECT)
        {
            info->state = PSA_FWU_UPDATED;
            info->error = PSA_SUCCESS;
        }
        else
        {
            info->error = PSA_ERROR_DOES_NOT_EXIST;
            info->impl.Primary = NOT_PRIMARY;
        }
    }
    else
    {
        //Think more
        if (gOTAReport[component>>1].Logical_Slot_Address.FIELD.REQ_STATUS == SECURITY_FAILURE)
        {
            info->error = PSA_ERROR_INVALID_SIGNATURE;
        }
        else if (gOTAReport[component>>1].Logical_Slot_Address.FIELD.REQ_STATUS == GENERAL_ERROR)
        {
            info->error = PSA_ERROR_PROGRAMMER_ERROR;
        }
        else
        {
            info->error = PSA_ERROR_DOES_NOT_EXIST;
        }
        info->impl.running_status = LOADED;
        info->impl.Primary = NOT_PRIMARY;
    }
    update_ComponentInfo(component, info->state, info->error);

    return READ_STATUS_SUCCESS;
}

void update_component_loaded_state(psa_fwu_component_t component, uint32_t readReportStatus)
{
    psa_status_t retVal = PSA_SUCCESS;
    uint8_t state;
    uint8_t magic_exists;
    int8_t flash_state;
    int8_t reset_state;
    uint32_t readStateRetVal;

    gImageStore[component].ComponentInfo.impl.running_status = LOADED;
    gImageStore[component].ComponentInfo.impl.Primary = NOT_PRIMARY;

    magic_exists = Magic_validation_and_coping_version(component);
    readStateRetVal = read_component_state_from_flash(component, &flash_state, &reset_state);

    gImageStore[component].ComponentInfo.state = flash_state;

    if ( (readStateRetVal == COMPONENT_READ_STATUS_EMPTY) && (magic_exists == MAGIC_EXISTS) )
    {
        gImageStore[component].ComponentInfo.impl.GPE_state = GPE_STAGED;
        state = (1 << PSA_FWU_CANDIDATE) | (1 << PSA_FWU_WRITING) | (1 << PSA_FWU_READY);
        write_component_multiple_state_in_flash(component, state);
        update_ComponentInfo(component, PSA_FWU_CANDIDATE, PSA_SUCCESS);
        return;
    }
    else if (readStateRetVal == COMPONENT_READ_STATUS_OK)
    {
        if (magic_exists == MAGIC_EXISTS)
        {
            update_ComponentGPEState(component, flash_state);
            if (readReportStatus == READ_STATUS_NO_OTA)
            {
                if (flow_check(component, PSA_FWU_REJECTED))
                {
                    update_ComponentInfo(component, PSA_FWU_FAILED, PSA_SUCCESS);
                }
                else if (flow_check(component, PSA_FWU_TRIAL))
                {
                    write_component_state_in_flash(component, PSA_FWU_REJECTED);
                    update_ComponentInfo(component, PSA_FWU_FAILED, PSA_SUCCESS);
                }
                else if ( ( (reset_state == COMPONENT_FLOW_STATE_RESET_VALIDATE) && (!flow_check(component, PSA_FWU_TRIAL)) ) ||
                          ( (reset_state == COMPONENT_FLOW_STATE_RESET_COMMIT) && (!flow_check(component, PSA_FWU_UPDATED)) ) )
                {
                    gImageStore[component].ComponentInfo.impl.GPE_state = GPE_DIRTY;
                    gImageStore[component].ComponentInfo.error = PSA_ERROR_CORRUPTION_DETECTED;
                    return;
                }
            }
            if (flow_check(component, PSA_FWU_UPDATED))
            {
                gImageStore[component].ComponentInfo.error = PSA_SUCCESS;
                gImageStore[component].ComponentInfo.impl.GPE_state = GPE_STAGED;
                if (readReportStatus != READ_STATUS_NO_OTA)
                {
                    gImageStore[component].ComponentInfo.impl.Primary = PRIMARY;
                }
                else
                {
                    if (flow_check(component^0x01, PSA_FWU_UPDATED))
                    {
                        write_component_state_in_flash(component, PSA_FWU_REJECTED);
                        update_ComponentInfo(component, PSA_FWU_FAILED, PSA_SUCCESS);
                        gImageStore[component].ComponentInfo.error = PSA_ERROR_NOT_PERMITTED;
                    }
                }
            }
            return;
        }
        else
        {
            if (!flow_check(component, PSA_FWU_READY))
            {
                write_component_state_in_flash(component, PSA_FWU_REJECTED);
                update_ComponentInfo(component, PSA_FWU_FAILED, PSA_SUCCESS);
            }
        }
    }

    if (flow_check(component, PSA_FWU_READY))
    {
        gImageStore[component].ComponentInfo.impl.GPE_state = GPE_ERASED;
        gImageStore[component].ComponentInfo.error = PSA_SUCCESS;
        gImageStore[component].ComponentInfo.state = PSA_FWU_READY;
        return;
    }

    write_component_state_in_flash(component, PSA_FWU_REJECTED);
    update_ComponentInfo(component, PSA_FWU_FAILED, PSA_SUCCESS);
    return;
}

void initialize_slot_addresses(void)
{
    // BL2 Slot 1
    gSlotAddress[0].Physical_Slot_Address = bl2_physical_slot_1_address;
    gSlotAddress[0].Logical_Slot_Address = bl2_logical_slot_1_address;
    gSlotAddress[0].Region_Size = bl2_slot_1_region_size;

    // BL2 Slot 2
    gSlotAddress[1].Physical_Slot_Address = bl2_physical_slot_2_address;
    gSlotAddress[1].Logical_Slot_Address = bl2_logical_slot_2_address;
    gSlotAddress[1].Region_Size = bl2_slot_2_region_size;

    // WiFi Connectivity Slot 1
    gSlotAddress[2].Physical_Slot_Address = wifi_connectivity_physical_slot_1_address;
    gSlotAddress[2].Logical_Slot_Address = wifi_connectivity_logical_slot_1_address;
    gSlotAddress[2].Region_Size = wifi_connectivity_slot_1_region_size;

    // WiFi Connectivity Slot 2
    gSlotAddress[3].Physical_Slot_Address = wifi_connectivity_physical_slot_2_address;
    gSlotAddress[3].Logical_Slot_Address = wifi_connectivity_logical_slot_2_address;
    gSlotAddress[3].Region_Size = wifi_connectivity_slot_2_region_size;

    // Vendor Image Slot 1
    gSlotAddress[4].Physical_Slot_Address = vendor_image_physical_slot_1_address;
    gSlotAddress[4].Logical_Slot_Address = vendor_image_logical_slot_1_address;
    gSlotAddress[4].Region_Size = vendor_image_slot_1_region_size;

    // Vendor Image Slot 2
    gSlotAddress[5].Physical_Slot_Address = vendor_image_physical_slot_2_address;
    gSlotAddress[5].Logical_Slot_Address = vendor_image_logical_slot_2_address;
    gSlotAddress[5].Region_Size = vendor_image_slot_2_region_size;

    // Vendor BL3 Slot 1
    gSlotAddress[6].Physical_Slot_Address = vendor_bl3_physical_slot_1_address;
    gSlotAddress[6].Logical_Slot_Address = vendor_bl3_logical_slot_1_address;
    gSlotAddress[6].Region_Size = vendor_bl3_slot_1_region_size;

    // Vendor BL3 Slot 2
    gSlotAddress[7].Physical_Slot_Address = vendor_bl3_physical_slot_2_address;
    gSlotAddress[7].Logical_Slot_Address = vendor_bl3_logical_slot_2_address;
    gSlotAddress[7].Region_Size = vendor_bl3_slot_2_region_size;

    // Vendor Image Alternate Slot configurations (secondary slot active)
    gSlotAddressAlternate[0].Physical_Slot_Address = vendor_image_physical_slot_1_address;
    gSlotAddressAlternate[0].Logical_Slot_Address = vendor_image_logical_slot_2_address;
    gSlotAddressAlternate[0].Region_Size = vendor_image_slot_2_region_size;

    gSlotAddressAlternate[1].Physical_Slot_Address = vendor_image_physical_slot_2_address;
    gSlotAddressAlternate[1].Logical_Slot_Address = vendor_image_logical_slot_1_address;
    gSlotAddressAlternate[1].Region_Size = vendor_image_slot_1_region_size;

    // Vendor BL3 Alternate Slot configurations (secondary slot active)
    gSlotAddressAlternate[2].Physical_Slot_Address = vendor_bl3_physical_slot_1_address;
    gSlotAddressAlternate[2].Logical_Slot_Address = vendor_bl3_logical_slot_2_address;
    gSlotAddressAlternate[2].Region_Size = vendor_bl3_slot_2_region_size;

    gSlotAddressAlternate[3].Physical_Slot_Address = vendor_bl3_physical_slot_2_address;
    gSlotAddressAlternate[3].Logical_Slot_Address = vendor_bl3_logical_slot_1_address;
    gSlotAddressAlternate[3].Region_Size = vendor_bl3_slot_1_region_size;
}

/*****************************************************************************/
/*                           API Functions implementation                    */
/*****************************************************************************/

psa_status_t psa_fwu_query(psa_fwu_component_t component,
                           psa_fwu_component_info_t *info)
{
    if (!(IS_VALID_COMPONENT_ID(component)))
    {
        return PSA_ERROR_DOES_NOT_EXIST;
    }

    os_memcpy(info, &(gImageStore[component].ComponentInfo), sizeof(psa_fwu_component_info_t));

    return PSA_SUCCESS;
}

psa_status_t psa_fwu_start(psa_fwu_component_t component,
                           const void *manifest,
                           size_t manifest_size)
{

    int_fast16_t retXMEM;
    PSA_FWU_GPESlot_t *Manifest = (PSA_FWU_GPESlot_t *)manifest;
    uint8_t Index;
    psa_status_t retVal;

    retVal = validation_check(component, gImageStore[component].ComponentInfo.state);
    if (retVal != PSA_SUCCESS)
    {
        UPDATE_COMPONENT_INFO_AND_RETURN_ERROR(PSA_FWU_READY ,retVal)
    }

    /* Check that this function is called after the component is in PSA_FWU_READY state */
    if (!flow_check(component, PSA_FWU_READY))
    {
        UPDATE_COMPONENT_INFO_AND_RETURN_ERROR(PSA_FWU_READY ,PSA_ERROR_BAD_STATE)
    }

    retVal =  is_manifest_integrity_valid((uint32_t*)Manifest);
    if (retVal != PSA_SUCCESS)
    {
        UPDATE_COMPONENT_INFO_AND_RETURN_ERROR(PSA_FWU_READY ,retVal)
    }

    retVal = is_GPE_magic_number_valid(component, &(Manifest->Manifest.GPE_Magic));
    if (retVal != PSA_SUCCESS)
    {
        UPDATE_COMPONENT_INFO_AND_RETURN_ERROR(PSA_FWU_READY ,retVal)
    }

    /* Block only if the incoming version is strictly older than the active slot (downgrade) */
    psa_fwu_image_version_t *secondaryVersion  = (psa_fwu_image_version_t*)&(Manifest->Manifest.GPE_Version);
    psa_fwu_image_version_t *primaryVersion = &(gImageStore[component ^ 0x01].ComponentInfo.version);

    /* Compare versions in order of significance (major, minor, patch, build) */
    if (isVersionNewer(primaryVersion, secondaryVersion))
    {
        UPDATE_COMPONENT_INFO_AND_RETURN_ERROR(PSA_FWU_READY ,PSA_ERROR_NOT_PERMITTED)
    }

    /* Write manifest integrity*/
    /* Update state in flash before writing starts in order to know that the flash
       won't be clean */
    write_component_state_in_flash(component, PSA_FWU_WRITING);
    for (Index = 0; Index < MANIFEST_INTEGRITY_SIZE_IN_WORDS; Index++)
    {
        retXMEM = XMEMWFF3_write(gImageStore[component].XMEMhandle, SECTOR_SIZE - TI_FWU_MAGIC_NUMBER_SIZE - TI_FWU_MANIFEST_INTEGRITY_SIZE + Index*4, (void *)&(Manifest->Manifest_Integrity.Manifest_Integrity[Index]), sizeof(uint32_t), XMEM_WRITE_STIG);
        if (retXMEM != XMEM_STATUS_SUCCESS)
        {
            UPDATE_COMPONENT_INFO_AND_RETURN_ERROR(PSA_FWU_WRITING ,PSA_ERROR_STORAGE_FAILURE)
        }
    }

    /* OTFDE region assignment:
     *   Region 0 — Vendor_Image_Slot_1 and Vendor_BL3_Slot_1 (same OTFDE window)
     *   Region 1 — BL2_Slot_1
     *   Region 2 — Vendor_Image_Slot_2 and Vendor_BL3_Slot_2 (same OTFDE window)
     * BL3 shares the vendor image OTFDE regions because it executes from the
     * same on-the-fly decryption window as the vendor application. */
    if (component == Vendor_Image_Slot_1)
    {
        otfdeDriver_Config(0, (const uint8_t*)Manifest->Manifest_Integrity.Manifest_Integrity, TI_FWU_MANIFEST_INTEGRITY_SIZE);
    }
    else if (component == BL2_Slot_1)
    {
        otfdeDriver_Config(1, (const uint8_t*)Manifest->Manifest_Integrity.Manifest_Integrity, TI_FWU_MANIFEST_INTEGRITY_SIZE);
    }
    else if (component == Vendor_Image_Slot_2)
    {
        otfdeDriver_Config(2, (const uint8_t*)Manifest->Manifest_Integrity.Manifest_Integrity, TI_FWU_MANIFEST_INTEGRITY_SIZE);
    }

    /* Write manifest without ih_magic */
    retXMEM = XMEMWFF3_write(gImageStore[component].XMEMhandle, SECTOR_SIZE, (void *)(uint8 *)Manifest + TI_FWU_MANIFEST_INTEGRITY_SIZE + TI_FWU_MAGIC_NUMBER_SIZE, manifest_size  - TI_FWU_MAGIC_NUMBER_SIZE - TI_FWU_MANIFEST_INTEGRITY_SIZE, 0);

    if (retXMEM != XMEM_STATUS_SUCCESS)
    {
        UPDATE_COMPONENT_INFO_AND_RETURN_ERROR(PSA_FWU_WRITING ,PSA_ERROR_STORAGE_FAILURE)
    }

    /* All required steps passed, update version */
    os_memcpy(&(gImageStore[component].ComponentInfo.version), &(Manifest->Manifest.GPE_Version), sizeof(PSA_FWU_GPEVersion_t));

    /* All required steps passed, update state */
    UPDATE_COMPONENT_INFO_AND_RETURN_ERROR(PSA_FWU_WRITING ,PSA_SUCCESS)

}


psa_status_t psa_fwu_write(psa_fwu_component_t component,
                           size_t image_offset,
                           const void *block,
                           size_t block_size)
{
    int_fast16_t retXMEM;
    psa_status_t retVal;

    retVal = validation_check(component,PSA_FWU_WRITING);
    if (retVal != PSA_SUCCESS)
    {
        return retVal;
    }

    /* Check that this function is called after the component is in PSA_FWU_WRITING state */
    if (!flow_check(component, PSA_FWU_WRITING))
    {
        UPDATE_COMPONENT_INFO_AND_RETURN_ERROR(PSA_FWU_WRITING ,PSA_ERROR_BAD_STATE)
    }

    /* Offset needs to be greater than manifest size */
    if (image_offset < TI_FWU_MANIFEST_SIZE)
    {
        UPDATE_COMPONENT_INFO_AND_RETURN_ERROR(PSA_FWU_WRITING ,PSA_ERROR_INVALID_ARGUMENT)
    }

    retXMEM = XMEMWFF3_write(gImageStore[component].XMEMhandle, SECTOR_SIZE - TI_FWU_MAGIC_NUMBER_SIZE - TI_FWU_MANIFEST_INTEGRITY_SIZE + image_offset, (void *)block, block_size, 0);
    if (retXMEM != XMEM_STATUS_SUCCESS)
    {
        UPDATE_COMPONENT_INFO_AND_RETURN_ERROR(PSA_FWU_WRITING ,PSA_ERROR_STORAGE_FAILURE)
    }

    /* All required steps passed, update state */
    UPDATE_COMPONENT_INFO_AND_RETURN_ERROR(PSA_FWU_WRITING ,PSA_SUCCESS)
}


psa_status_t psa_fwu_finish(psa_fwu_component_t component)
{
    int_fast16_t retXMEM;
    psa_status_t retVal;

    retVal = validation_check(component, PSA_FWU_WRITING);
    if (retVal != PSA_SUCCESS)
    {
        return retVal;
    }

    /* Check that this function is called after the component is in PSA_FWU_WRITING state */
    if (!flow_check(component, PSA_FWU_WRITING))
    {
        UPDATE_COMPONENT_INFO_AND_RETURN_ERROR(PSA_FWU_WRITING ,PSA_ERROR_BAD_STATE)
    }

    /* For WSOC components, verify that the version in the image data matches
       the manifest version. This prevents loading an image whose manifest was
       modified to claim a different version than the actual firmware. */
    if (IS_WSOC_COMPONENT(component))
    {
        PSA_FWU_GPEVersion_t GPE_dataVersion;
        size_t flashOffset = SECTOR_SIZE + TI_FWU_GPE_MANIFEST_SECTION_SIZE + GPE_DATA_VERSION_OFFSET;

        retXMEM = XMEMWFF3_read(gImageStore[component].XMEMhandle, flashOffset,
                                &GPE_dataVersion, sizeof(PSA_FWU_GPEVersion_t), 0);
        if (retXMEM != XMEM_STATUS_SUCCESS)
        {
            UPDATE_COMPONENT_INFO_AND_RETURN_ERROR(PSA_FWU_WRITING, PSA_ERROR_STORAGE_FAILURE)
        }

        if (os_memcmp(&GPE_dataVersion,
                      &(gImageStore[component].ComponentInfo.version),
                      sizeof(PSA_FWU_GPEVersion_t)) != 0)
        {
            UPDATE_COMPONENT_INFO_AND_RETURN_ERROR(PSA_FWU_FAILED, PSA_ERROR_NOT_PERMITTED)
        }
    }

    retXMEM = XMEMWFF3_write(gImageStore[component].XMEMhandle, SECTOR_SIZE - TI_FWU_MAGIC_NUMBER_SIZE, &(gGPEMagicNumber[component >> 1].Magic_Number), TI_FWU_MAGIC_NUMBER_SIZE, XMEM_WRITE_STIG);
    if (retXMEM != XMEM_STATUS_SUCCESS)
    {
        UPDATE_COMPONENT_INFO_AND_RETURN_ERROR(PSA_FWU_WRITING ,PSA_ERROR_STORAGE_FAILURE)
    }

    /* All required steps passed, update state */
    UPDATE_COMPONENT_INFO_AND_RETURN_ERROR(PSA_FWU_CANDIDATE ,PSA_SUCCESS)
}


psa_status_t psa_fwu_cancel(psa_fwu_component_t component)
{
    int_fast16_t retXMEM;
    PSA_FWU_Magic_t Emptymagic = {0};
    psa_status_t retVal;

    retVal = validation_check(component, gImageStore[component].ComponentInfo.state);
    if (retVal != PSA_SUCCESS)
    {
        return retVal;
    }

    /* Check that this function is called after the component is in PSA_FWU_WRITING state */
    if ( (!flow_check(component, PSA_FWU_WRITING)) &&
         (!flow_check(component, PSA_FWU_CANDIDATE)) )
    {
        UPDATE_COMPONENT_INFO_AND_RETURN_ERROR(gImageStore[component].ComponentInfo.state ,PSA_ERROR_BAD_STATE)
    }

    if (gImageStore[component].ComponentInfo.impl.running_status == ACTIVE)
    {
        UPDATE_COMPONENT_INFO_AND_RETURN_ERROR(gImageStore[component].ComponentInfo.state ,PSA_ERROR_NOT_PERMITTED)
    }

    retXMEM = XMEMWFF3_write(gImageStore[component].XMEMhandle, SECTOR_SIZE - TI_FWU_MAGIC_NUMBER_SIZE, &(Emptymagic.Magic_Number), TI_FWU_MAGIC_NUMBER_SIZE, XMEM_WRITE_STIG);

    if (retXMEM != XMEM_STATUS_SUCCESS)
    {
        UPDATE_COMPONENT_INFO_AND_RETURN_ERROR(PSA_FWU_FAILED ,PSA_ERROR_STORAGE_FAILURE)
    }

    /* All required steps passed, update state */
    UPDATE_COMPONENT_INFO_AND_RETURN_ERROR(PSA_FWU_FAILED ,PSA_SUCCESS)
}


psa_status_t psa_fwu_clean(psa_fwu_component_t component)
{
    psa_status_t retVal;

    retVal = validation_check(component, gImageStore[component].ComponentInfo.state);
    if (retVal != PSA_SUCCESS)
    {
        return retVal;
    }

    /* Previous state must be REJECTED or FAILED before cleaning */
    if ( (!flow_check(component, PSA_FWU_UPDATED)) &&
         (!flow_check(component, PSA_FWU_FAILED)) )
    {
        UPDATE_COMPONENT_INFO_AND_RETURN_ERROR(gImageStore[component].ComponentInfo.state ,PSA_ERROR_BAD_STATE)
    }

    retVal = erase_GPE(component);
    if (retVal != PSA_SUCCESS)
    {
        return retVal;
    }

    os_memset(&gImageStore[component].ComponentInfo.version, 0, sizeof(psa_fwu_image_version_t));

    /* All required steps passed, update state */
    UPDATE_COMPONENT_INFO_AND_RETURN_ERROR(PSA_FWU_READY ,PSA_SUCCESS)

}

psa_status_t psa_fwu_install(void)
{
    psa_fwu_component_t component;
    bool                isAtLeastOneCandidate = false;
    uint8_t             slotIndex;

    for (component = 0; component < MAX_COMPONENT_ID; component++ )
    {
        if ( (flow_check(component, PSA_FWU_STAGED)) ||
             (flow_check(component, PSA_FWU_TRIAL))  ||
             (flow_check(component, PSA_FWU_REJECTED)) )
        {
            return PSA_ERROR_BAD_STATE;
        }
    }

    for (component = 0; component < MAX_COMPONENT_ID;)
    {
        Request_type[component>>1] = 0;

        for (slotIndex = 0; slotIndex < 2; component++, slotIndex++)
        {
            if (IS_COMPONENT_ID_PRIMARY(component))
            {
                continue;
            }
            /* If component is not ready, skip */
            if (flow_check(component, PSA_FWU_CANDIDATE))
            {
                update_ComponentInfo(component, PSA_FWU_STAGED, PSA_SUCCESS);
                Request_type[component>>1] |= OTA_VALIDATE_BIT;
                isAtLeastOneCandidate = true;
            }
        }
    }

    if (!isAtLeastOneCandidate)
    {
        return PSA_ERROR_BAD_STATE;
    }

    return PSA_SUCCESS_REBOOT;
}


psa_status_t psa_fwu_request_reboot(void)
{
    psa_fwu_component_t           component;
    bool                          resetNeeded = false;
    uint8_t                       slotIndex;
    PSA_FWU_SCRATCHPAD_FOR_TYPES  scratchpad = {0};

    for (component = 0; component < MAX_COMPONENT_ID;)
    {
        for (slotIndex = 0; slotIndex < 2; component++, slotIndex++)
        {
            if (IS_COMPONENT_ID_PRIMARY(component))
            {
                continue;
            }

            if (Request_type[component>>1] & OTA_VALIDATE_BIT)
            {
                write_component_state_in_flash(component, COMPONENT_FLOW_STATE_RESET_VALIDATE);
                resetNeeded = true;
            }
            else if (Request_type[component>>1] & OTA_COMMIT_AND_PROTECT_BIT)
            {
                write_component_state_in_flash(component, COMPONENT_FLOW_STATE_RESET_COMMIT);
                resetNeeded = true;
            }
            else if (flow_check(component, PSA_FWU_REJECTED))
            {
                resetNeeded = true;
            }
        }
    }

    if (!resetNeeded)
    {
        return PSA_ERROR_BAD_STATE;
    }
    scratchpad.FIELD.BL2 = Request_type[BL2];
    scratchpad.FIELD.WSOC_OR_RFTOOL = Request_type[WSOC_OR_RFTool];
    scratchpad.FIELD.VENDOR_IMAGE = Request_type[Vendor_Image];
    scratchpad.FIELD.VENDOR_BL3 = Request_type[Vendor_BL3];

    REGISTER(PRCM_SCRATCHPAD__PRCM_SCPAD2__ADDR) = scratchpad.ALL;

    Power_reset();

    return PSA_SUCCESS;
}

void psa_fwu_init(void)
{
    PSA_FWU_Report_Structure_t *pSharedReport = (PSA_FWU_Report_Structure_t *)BOOT_REPORT_ADDR;
    psa_fwu_component_t component;
    psa_fwu_component_t active_component;
    psa_fwu_component_t loaded_component;
    uint32_t readStatus;
    uint32_t readReportStatus;
    uint8_t magic_exists = MAGIC_MISSING;

    if (!isInitialized)
    {
        isInitialized = (bool)true;

        initialize_slot_addresses();

        os_memcpy(gOTAReport, pSharedReport, sizeof(gOTAReport));

        for (component = 0; component < MAX_COMPONENT_ID; component+=2 )
        {
            Request_type[component>>1] = 0;

            readStatus = Retrieve_active_and_loaded_components(component, &active_component, &loaded_component);

            if (readStatus == READ_STATUS_ERROR)
            {
                continue;
            }

            Create_component_XMEMHandle(active_component, readStatus);
            Create_component_XMEMHandle(loaded_component, readStatus);

            /* Update active component fields */
            readReportStatus = Read_report_and_update_status(active_component);

            /* Update loaded component fields */
            update_component_loaded_state(loaded_component, readReportStatus);
        }
    }
}



psa_status_t psa_fwu_reject(psa_status_t error)
{
    psa_fwu_component_t           component;
    bool                          resetNeeded = false;
    bool                          rejectedFound = false;
    uint8_t                       slotIndex;

    for (component = 0; component < MAX_COMPONENT_ID;)
    {
        for (slotIndex = 0; slotIndex < 2; component++, slotIndex++)
        {
            if (IS_COMPONENT_ID_PRIMARY(component))
            {
                continue;
            }
            if (flow_check(component, PSA_FWU_STAGED))
            {
                update_ComponentInfo(component, PSA_FWU_FAILED, PSA_SUCCESS);
                gImageStore[component].ComponentInfo.error = error;
                rejectedFound = true;
            }
            else if (flow_check(component, PSA_FWU_TRIAL))
            {
                update_ComponentInfo(component, PSA_FWU_REJECTED, PSA_SUCCESS);
                gImageStore[component].ComponentInfo.error = error;
                rejectedFound = true;

                if (IS_COMPONENT_ID_ACTIVE(component))
                {
                    resetNeeded = true;
                }
            }
        }
    }

    if (!rejectedFound)
    {
        return PSA_ERROR_BAD_STATE;
    }
    if (resetNeeded)
    {
        return PSA_SUCCESS_REBOOT;
    }

    return PSA_SUCCESS;
}


psa_status_t psa_fwu_accept(void)
{
    psa_fwu_component_t           component;
    bool                          resetNeeded = false;
    bool                          trailFound = false;
    uint8_t                       slotIndex;

    for (component = 0; component < MAX_COMPONENT_ID;)
    {
        for (slotIndex = 0; slotIndex < 2; component++, slotIndex++)
        {
            if (IS_COMPONENT_ID_PRIMARY(component))
            {
                continue;
            }

            if (flow_check(component, PSA_FWU_TRIAL))
            {
                Request_type[component>>1] = OTA_COMMIT_AND_PROTECT_BIT;
                trailFound = true;
                resetNeeded = true;

            }
        }
    }

    if (!trailFound)
    {
        return PSA_ERROR_BAD_STATE;
    }
    if (resetNeeded)
    {
        return PSA_SUCCESS_REBOOT;
    }

    return PSA_SUCCESS;
}
