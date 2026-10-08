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

#include "otfde_driver.h"
#include "register_macros.h"
#include "host_xip_cc35.h"
#include "FlashWFF3.h"

/*
 * @description         : This function configures the otfde region based on the parameters collected in the init func.
 * @param region_number:         Region number (0-3)
 * @param security_id:           Security_id (Manifest Integrity)
 * @param security_id_size:      Security_id buf size
 */
__attribute__((section(".TI.ramfunc")))
uint8_t otfdeDriver_Config(const uint32_t region_number,
                           const uint8_t* security_id,
                           const uint32_t security_id_size)
{

    uint32_t sec_id_lsb = security_id[0] + (security_id[1] << 8) + (security_id[2] << 16) + (security_id[3] << 24);
    uint32_t sec_id_msb = security_id[4];
    if (region_number > 3)
    {
        return 0;
    }
    FlashSetOTFDE(FLASH_OTFDE_DISABLE);

    if (region_number == 0) { //region 0
        //configure Sec ID
        SET_FIELD(HOST_XIP__SECGB_REGION_0_PARAMS_3__MEM_REGION_0_SECURITY_ID_LSB, sec_id_lsb);
        SET_FIELD(HOST_XIP__SECGB_REGION_0_PARAMS_0__MEM_REGION_0_SECURITY_ID_MSB, (sec_id_msb & 0x3F));
    }
    else if (region_number == 1) { //region 1
        //configure Sec ID
        SET_FIELD(HOST_XIP__SECGC_REGION_1_PARAMS_3__MEM_REGION_1_SECURITY_ID_LSB, sec_id_lsb);
        SET_FIELD(HOST_XIP__SECGC_REGION_1_PARAMS_0__MEM_REGION_1_SECURITY_ID_MSB, (sec_id_msb & 0x3F));
    }
    else if (region_number == 2) { //region 2
        //configure Sec ID
        SET_FIELD(HOST_XIP__SECGD_REGION_2_PARAMS_3__MEM_REGION_2_SECURITY_ID_LSB, sec_id_lsb);
        SET_FIELD(HOST_XIP__SECGD_REGION_2_PARAMS_0__MEM_REGION_2_SECURITY_ID_MSB, (sec_id_msb & 0x3F));
    }
    else if (region_number == 3) { //region 3
        //configure Sec ID
        SET_FIELD(HOST_XIP__SECGE_REGION_3_PARAMS_3__MEM_REGION_3_SECURITY_ID_LSB, sec_id_lsb);
        SET_FIELD(HOST_XIP__SECGE_REGION_3_PARAMS_0__MEM_REGION_3_SECURITY_ID_MSB, (sec_id_msb & 0x3F));
    }

    FlashSetOTFDE(FLASH_OTFDE_ENABLE);

    return 1;
}
