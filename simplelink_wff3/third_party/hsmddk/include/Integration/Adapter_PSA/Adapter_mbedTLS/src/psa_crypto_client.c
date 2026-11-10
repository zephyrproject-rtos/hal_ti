/*
 *  Copyright The Mbed TLS Contributors
 *  SPDX-License-Identifier: Apache-2.0
 *
 *  Licensed under the Apache License, Version 2.0 (the "License"); you may
 *  not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 *  WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

/* This file is currently not used in mbedTLS 3.6.3, so its contents do not need to be
 * built into the DDK library. The file will remain for reference, but likely can be
 * removed at some point in the future.
 */
#if 0

#include <string.h>

#include <third_party/hsmddk/include/Integration/Adapter_PSA/Adapter_mbedTLS/incl/private_access.h>
#include <third_party/hsmddk/include/Integration/Adapter_PSA/Adapter_mbedTLS/incl/platform.h>
#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/psa/crypto.h>

psa_status_t psa_set_key_domain_parameters(psa_key_attributes_t *attributes,
                                           psa_key_type_t type,
                                           const uint8_t *data,
                                           size_t data_length)
{
    uint8_t *copy = NULL;

    if (data_length != 0)
    {
        copy = psaInt_mbedtls_calloc(1, data_length);
        if (copy == NULL)
        {
            return PSA_ERROR_INSUFFICIENT_MEMORY;
        }
        memcpy(copy, data, data_length);
    }
    /* After this point, this function is guaranteed to succeed, so it
     * can start modifying `*attributes`. */

    if (attributes->MBEDTLS_PRIVATE(domain_parameters) != NULL)
    {
        psaInt_mbedtls_free(attributes->MBEDTLS_PRIVATE(domain_parameters));
        attributes->MBEDTLS_PRIVATE(domain_parameters) = NULL;
        attributes->MBEDTLS_PRIVATE(domain_parameters_size) = 0;
    }

    attributes->MBEDTLS_PRIVATE(domain_parameters) = copy;
    attributes->MBEDTLS_PRIVATE(domain_parameters_size) = data_length;
    attributes->MBEDTLS_PRIVATE(core).MBEDTLS_PRIVATE(type) = type;

    return PSA_SUCCESS;
}
#endif
