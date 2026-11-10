/* adapter_driver_psa_init.c
 *
 * Adapter top level module, EIP-130 ARM PSA Crypto API driver's entry point.
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

/*----------------------------------------------------------------------------
 * This module implements (provides) the following interface(s):
 */

#include <third_party/hsmddk/include/Integration/Adapter_DriverInit/incl/api_driver_init.h>        // Driver Init API


/*----------------------------------------------------------------------------
 * This module uses (requires) the following interface(s):
 */

// Top-level Adapter configuration
#include <third_party/hsmddk/include/Config/cs_adapter.h>             // ADAPTER_DRIVER_NAME

// Logging API
#include <third_party/hsmddk/include/Kit/Log/incl/log.h>                    // LOG_INFO


/*----------------------------------------------------------------------------
 * Local prototypes
 */

int32_t
DriverPSA_Custom_Init(void);

void
DriverPSA_Custom_UnInit(void);


/*----------------------------------------------------------------------------
 * Driver130_Init
 */
int32_t
Driver130_Init(void)
{
    int32_t funcres;

    LOG_INFO("%s: initialize driver %s\n", __func__, ADAPTER_DRIVER_NAME);

    if (DriverPSA_Custom_Init() < 0)
    {
        funcres = -1;
    }
    else
    {
        LOG_INFO("%s: done\n", __func__);
        funcres = 0;
    }

    return funcres;
}


/*----------------------------------------------------------------------------
 * Driver130_Exit
 */
void
Driver130_Exit(void)
{
    LOG_INFO("%s: exit driver %s\n", __func__, ADAPTER_DRIVER_NAME);

    DriverPSA_Custom_UnInit();

    LOG_INFO("%s: done\n", __func__);
}

/*----------------------------------------------------------------------------
 * DriverPSA_Custom_Init
 */
int32_t
DriverPSA_Custom_Init(void)
{
    return 0; // success
}


/*----------------------------------------------------------------------------
 * DriverPSA_Custom_UnInit
 */
void
DriverPSA_Custom_UnInit(void)
{
    return;
}

// TI Modification: Investigate why this file has empty implementations to some APIs
// TI Modification: HSM_DDK-6 to track
// #include <third_party/hsmddk/include/Integration/Adapter_DriverInit/src/um/adapter_driver_psa_init_ext.h>

/* end of file adapter_driver_psa_init.c */
