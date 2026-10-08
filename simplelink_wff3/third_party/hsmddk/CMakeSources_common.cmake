cmake_minimum_required(VERSION ${TI_MIN_CMAKE_VERSION})

file(GLOB_RECURSE SOURCES_INTEGRATION_ADAPTER_DRIVERINIT "include/Integration/Adapter_DriverInit/Driver/src/*.c")

file(GLOB_RECURSE SOURCES_INTEGRATION_ADAPTER_GENERIC "include/Integration/Adapter_Generic/src/*.c")

file(GLOB_RECURSE SOURCES_INTEGRATION_ADAPTER_PSA "include/Integration/Adapter_PSA/src/*.c")

file(GLOB_RECURSE SOURCES_INTEGRATION_ADAPTER_PSA_MBEDTLS "include/Integration/Adapter_PSA/Adapter_mbedTLS/src/*.c")

file(GLOB_RECURSE SOURCES_INTEGRATION_ADAPTER_VEX "include/Integration/Adapter_VEX/src/*.c")

file(GLOB_RECURSE SOURCES_INTEGRATION_ASN1DER "include/Integration/Asn1Der/src/*.c")

file(GLOB_RECURSE SOURCES_INTEGRATION_DRIVER_FRAMEWORK "include/Integration/DriverFramework/src/*.c")

file(GLOB_RECURSE SOURCES_INTEGRATION_ADAPTER_ITS "include/Integration/Adapter_ITS/src/*.c")

set(SOURCES_INTEGRATION_HSMSAL
    include/Integration/HSMSAL/HSMSAL.c
)

set(SOURCES_COMMON_INTEGRATION
    ${SOURCES_INTEGRATION_ADAPTER_DRIVERINIT}
    # ${SOURCES_INTEGRATION_ADAPTER_GENERIC}
    include/Integration/Adapter_Generic/src/adapter_interrupts.c
    # ${SOURCES_INTEGRATION_ADAPTER_PSA}
    include/Integration/Adapter_PSA/src/adapter_psa_asset.c
    include/Integration/Adapter_PSA/src/adapter_psa_asym_parse.c
    include/Integration/Adapter_PSA/src/adapter_psa_asym_write.c
    include/Integration/Adapter_PSA/src/adapter_psa_exchangetoken.c
    include/Integration/Adapter_PSA/src/adapter_psa_init.c
    include/Integration/Adapter_PSA/src/adapter_psa_internal.c
    include/Integration/Adapter_PSA/src/adapter_psa_key_derivation.c
    include/Integration/Adapter_PSA/src/adapter_psa_key_management.c
    include/Integration/Adapter_PSA/src/adapter_psa_preprovisioned_keys.c
    include/Integration/Adapter_PSA/src/adapter_psa_system.c
    include/Integration/Adapter_PSA/src/psa_key_store.c
    ${SOURCES_INTEGRATION_ADAPTER_PSA_MBEDTLS}
    # ${SOURCES_INTEGRATION_ADAPTER_VEX}
    include/Integration/Adapter_VEX/src/adapter_vex_device.c
    include/Integration/Adapter_VEX/src/adapter_vex_identity.c
    include/Integration/Adapter_VEX/src/adapter_vex_init.c
    include/Integration/Adapter_VEX/src/adapter_vex_mailbox.c
    include/Integration/Adapter_VEX/src/adapter_vex_physicaltoken.c
    ${SOURCES_INTEGRATION_ASN1DER}
    # ${SOURCES_INTEGRATION_DRIVER_FRAMEWORK}
    include/Integration/DriverFramework/src/device_generic.c
    include/Integration/DriverFramework/src/hwpal_device_mb.c
    ${SOURCES_INTEGRATION_HSMSAL}
)

set(SOURCES_KIT_EIP130
    include/Kit/EIP130/DomainHelper/src/eip130_domain_ecc_getcurve.c
    include/Kit/EIP130/MailboxControl/src/eip130.c
    include/Kit/EIP130/TokenHelper/src/eip130_token_common.c
)

set(SOURCES_KIT_EIP201
    include/Kit/EIP201/src/eip201.c
)

set(SOURCES_KIT_LOG
    include/Kit/Log/src/log.c
)

set(SOURCES_COMMON_KIT
    ${SOURCES_KIT_EIP130}
    ${SOURCES_KIT_EIP201}
    ${SOURCES_KIT_LOG}
)

set(SOURCES_COMMON
    ${SOURCES_COMMON_INTEGRATION}
    ${SOURCES_COMMON_KIT}
)