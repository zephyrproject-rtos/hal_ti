# README for TI Mbed TLS

TI provides hardware accelerated TLS and X509 support using Mbed TLS v3.6.6. The
underlying crypto drivers supported include AES-ECB, AES-CBC, AES-CMAC,
AES-CBC-MAC, AES-CCM, AES-GCM, TRNG (entropy), ECDH, ECDSA, ECJPAKE, SHA-2-256,
and SHA-2-512. On CC13XX/CC26XX devices, the PSA Crypto implementation from Mbed
TLS (with TI modifications) is used. For HSM-enabled devices (CC27XX and
CC35XX), TI's own implementation of the PSA Crypto API is linked to Mbed TLS,
for use with crypto operations that are hardware-accelerated.

## Using pre-built libraries

TI provides pre-built libraries for supported devices using GCC, IAR and TICLANG
compilers tools. With the following steps, the user can use TI Mbed TLS library
in their project:

* Add include paths:
  * `[SDK]/source/third_party/mbedtls/include`,
  * `[SDK]/source/third_party/mbedtls/ti`
  * `[SDK]/source/third_party/mbedtls/ti/port`
* Add predefined symbol:
  * `"MBEDTLS_CONFIG_FILE="<configs/config-<device>.h>"`
* Link the library:
  * `[SDK]/source/third_party/mbedtls/ti/lib/[TOOL]/m33f/mbedtls.a`

## Customizing the Mbed TLS support

The user may customize the configuration in Mbed TLS and rebuild the libraries
using the following steps:

* Enable/disable the required configurations in
  `[SDK]/source/third_party/mbedtls/ti/configs/config-<device>.h`
  * Note the following restrictions for the configuration:
    * MBEDTLS_PSA_CRYPTO_KEY_ID_ENCODES_OWNER must be DISABLED
    * MBEDTLS_PSA_CRYPTO_C must be ENABLED
    * MBEDTLS_USE_PSA_CRYPTO must be ENABLED
* Re-build the library using the makefile in
  `[SDK]/source/third_party/mbedtls/ti/makefile`. From the SDK root directory,
  perform the following steps:

>       cd source/third_party/mbedtls/ti/
>       make

Once the library is built with the desired configurations, the user can use the
libraries as described above in "Using pre-built libraries".
