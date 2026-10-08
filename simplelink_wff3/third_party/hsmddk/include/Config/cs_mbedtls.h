/**
 * \file cs_mbedtls.h
 *
 * \brief Configuration options (set of defines) for mbedTLS
 *        type definitions for the PSA Crypto API.
 *
 *  This set of compile-time options may be used to enable
 *  or disable features selectively, and reduce the global
 *  memory footprint.
 */
/*
 *  Copyright The Mbed TLS Contributors
 *  Copyright (c) 2024, Texas Instruments Incorporated
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
#ifndef cs_mbedtls_H
#define cs_mbedtls_H

/* Add a default owner id to match with client ID in TFM-Enabled builds */
#define MBEDTLS_PSA_CRYPTO_KEY_ID_DEFAULT_OWNER -1

#endif /* cs_mbedtls_H */

/* end of file cs_mbedtls.h */