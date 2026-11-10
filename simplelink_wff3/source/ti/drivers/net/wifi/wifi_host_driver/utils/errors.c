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

#include "errors.h"
#include "macro_utils.h"


//------------------------------------------------------------------------------------------------
// FW Errors: Returned values from WSoC FW, received by complete.retVal.
//            The following values are converted to WLAN_ERROR format by WlanError_ConvertWsocError()
//-------------------------------------------------------------------------------------------------
#define WLAN_RET_CODE_MALLOC_ERROR                 (-2009L)
#define WLAN_RET_CODE_DEV_NOT_STARTED              (-2018L)
#define WLAN_RET_CODE_ZALLOC_ERROR                 (-2021L)
#define WLAN_ERROR_INVALID_ROLE                    (-2050L)
#define WLAN_ERROR_INVALID_SECURITY_TYPE           (-2054L)
#define WLAN_ERROR_PASSPHRASE_TOO_LONG             (-2055L)
#define WLAN_ERROR_PASSWORD_ERROR                  (-2058L)
#define WLAN_ERROR_SSID_LEN_ERROR                  (-2060L)
#define WLAN_ERROR_NO_ROLE_ACTIVE                  (-4121L)    /* No AP or STA role active */
#define WLAN_ERROR_ACTIVE_ROLE_SIWTCH              (-4122L)    /* Active role switch so can't perform scan */
#define WLAN_ERROR_SITE_SURVEY_RUNNING             (-4123L)    /* site survey running so can't perform scan */
#define WLAN_ERROR_INVALID_MAC_ADDR                (-4124L)    /* Invalid mac address */
#define WLAN_ERROR_NULL_BUF                        (-4125L)    /* NULL buffer*/
#define WLAN_ERROR_INVALID_PARAM                   (-14338L)
#define WLAN_ERROR_EXCEED_MAX_NUM_OF_ENTRIES       (-6223L)   /* exceed max number of entries in custom mode  */


/*!
    \brief Generate WLAN error

    This function generates a signed integer representing an error bitmap

    \param[in]      severity
    \param[in]      module
    \param[in]      type

    \return         Negative int32 errorbitmap

    \sa
    \note
    \warning
*/
int32_t WlanError(wlanErrorSeverity_e severity, wlanErrorModule_e module, wlanErrorType_e type)
{
    wlanError_u error = { .type     = (uint32_t) type,
                      .module   = (uint32_t) module,
                      .severity = (uint32_t) severity,
                      .reserved = (uint32_t) 0,
                      .sign     = (uint32_t) 1
                    };

    return error.word;
}


/*!
    \brief Gets error type from error structure

    \param[in]      error

    \return         Error type

    \sa
    \note
    \warning
*/
uint32_t WlanError_GetType(int32_t error)
{
    wlanError_u err;
    err.word = (uint32_t)error;
    return err.type;
}


/*!
    \brief Gets error module from error structure

    \param[in]      error

    \return         Error module

    \sa
    \note
    \warning
*/
uint32_t WlanError_GetModule(int32_t error)
{
    wlanError_u err;
    err.word = (uint32_t)error;
    return err.module;
}


/*!
    \brief Gets error severity from error structure

    \param[in]      error

    \return         Error severity

    \sa
    \note
    \warning
*/
uint32_t WlanError_GetSeverity(int32_t error)
{
    wlanError_u err;
    err.word = (uint32_t)error;
    return err.severity;
}

/*!
    \brief Convert FW error to Host error

    \param[in]      FW error number

    \return         Host Error number

    \sa
    \note
    \warning
*/
wlanErrorType_e WlanError_ConvertWsocError(int error)
{
    switch (error)
    {
        case  WLAN_RET_CODE_MALLOC_ERROR:
        {
            return WLAN_ERROR_TYPE__FW_RESPONSE_RET_CODE_MALLOC;
        }
        break;
        case  WLAN_RET_CODE_DEV_NOT_STARTED:
        {
            return WLAN_ERROR_TYPE__FW_RESPONSE_RET_CODE_DEV_NOT_STARTED;
        }
        break;
        case  WLAN_RET_CODE_ZALLOC_ERROR:
        {
            return WLAN_ERROR_TYPE__FW_RESPONSE_RET_CODE_ZALLOC;
        }
        break;
        case  WLAN_ERROR_INVALID_ROLE:
        {
            return WLAN_ERROR_TYPE__FW_RESPONSE_INVALID_ROLE;
        }
        break;
        case  WLAN_ERROR_INVALID_SECURITY_TYPE:
        {
            return WLAN_ERROR_TYPE__FW_RESPONSE_INVALID_SECURITY_TYPE;
        }
        break;
        case  WLAN_ERROR_PASSPHRASE_TOO_LONG:
        {
            return WLAN_ERROR_TYPE__FW_RESPONSE_PASSPHRASE_TOO_LONG;
        }
        break;
        case  WLAN_ERROR_PASSWORD_ERROR:
        {
            return WLAN_ERROR_TYPE__FW_RESPONSE_PASSWORD;
        }
        break;
        case  WLAN_ERROR_SSID_LEN_ERROR:
        {
            return WLAN_ERROR_TYPE__FW_RESPONSE_SSID_LEN;
        }
        break;
        case  WLAN_ERROR_NO_ROLE_ACTIVE:
        {
            return WLAN_ERROR_TYPE__FW_RESPONSE_NO_ROLE_ACTIVE;
        }
        break;
        case  WLAN_ERROR_ACTIVE_ROLE_SIWTCH:
        {
            return WLAN_ERROR_TYPE__FW_RESPONSE_ACTIVE_ROLE_SWITCH;
        }
        break;
        case  WLAN_ERROR_SITE_SURVEY_RUNNING:
        {
            return WLAN_ERROR_TYPE__FW_RESPONSE_SITE_SURVEY_RUNNING;
        }
        break;
        case  WLAN_ERROR_INVALID_MAC_ADDR:
        {
            return WLAN_ERROR_TYPE__FW_RESPONSE_INVALID_MAC_ADDR;
        }
        break;
        case  WLAN_ERROR_NULL_BUF:
        {
            return WLAN_ERROR_TYPE__FW_RESPONSE_NULL_BUF;
        }
        break;
        case  WLAN_ERROR_INVALID_PARAM:
        {
            return WLAN_ERROR_TYPE__FW_RESPONSE_INVALID_PARAM;
        }
        break;
        case  WLAN_ERROR_EXCEED_MAX_NUM_OF_ENTRIES:
        {
            return WLAN_ERROR_TYPE__FW_RESPONSE_EXCEED_MAX_NUM_OF_ENTRIES;
        }
        break;


        default:
            return WLAN_ERROR_TYPE__FW_RESPONSE_GENERAL;
    }
}
