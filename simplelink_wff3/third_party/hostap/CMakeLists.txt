cmake_minimum_required(VERSION ${TI_MIN_CMAKE_VERSION})

cmake_path(GET CMAKE_CURRENT_LIST_DIR FILENAME    TARGET_NAME)


message(STATUS "Generating target           ${TARGET_NAME}")

#read the version file
file(READ src/common/version.h hostap_versions)
#set the hostap version
string(REGEX MATCH "VERSION_STR[ \t]+\"([0-9|.]+)\"" _ ${hostap_versions})
set(HOSTAP_VERSION       ${CMAKE_MATCH_1} CACHE INTERNAL "")

#common source files for openssl and mbedTLS
set(${TARGET_NAME}_SOURCES

    ${CMAKE_CURRENT_LIST_DIR}/hostapd/eap_register.c
    ${CMAKE_CURRENT_LIST_DIR}/hostapd/sae_pk_gen.c
    ${CMAKE_CURRENT_LIST_DIR}/src/common/dragonfly.c
    ${CMAKE_CURRENT_LIST_DIR}/src/common/gas.c
    ${CMAKE_CURRENT_LIST_DIR}/src/common/hw_features_common.c
    ${CMAKE_CURRENT_LIST_DIR}/src/common/ieee802_11_common.c
    ${CMAKE_CURRENT_LIST_DIR}/src/common/ocv.c
    ${CMAKE_CURRENT_LIST_DIR}/src/common/wpa_common.c
    ${CMAKE_CURRENT_LIST_DIR}/src/common/sae.c
    ${CMAKE_CURRENT_LIST_DIR}/src/common/wpa_ctrl.c
    ${CMAKE_CURRENT_LIST_DIR}/src/crypto/dh_group5.c
    ${CMAKE_CURRENT_LIST_DIR}/src/crypto/dh_groups.c
    ${CMAKE_CURRENT_LIST_DIR}/src/crypto/sha1-prf.c
    ${CMAKE_CURRENT_LIST_DIR}/src/crypto/sha256-prf.c    
    ${CMAKE_CURRENT_LIST_DIR}/src/crypto/sha256-kdf.c
    ${CMAKE_CURRENT_LIST_DIR}/src/crypto/sha1-tprf.c
    ${CMAKE_CURRENT_LIST_DIR}/src/crypto/
    ${CMAKE_CURRENT_LIST_DIR}/src/crypto/ms_funcs.c
    ${CMAKE_CURRENT_LIST_DIR}/src/drivers/driver_common.c 
    ${CMAKE_CURRENT_LIST_DIR}/src/drivers/drivers.c
    ${CMAKE_CURRENT_LIST_DIR}/src/eap_common/chap.c
    ${CMAKE_CURRENT_LIST_DIR}/src/eap_common/eap_common.c
    ${CMAKE_CURRENT_LIST_DIR}/src/eap_common/eap_fast_common.c
    ${CMAKE_CURRENT_LIST_DIR}/src/eap_common/eap_peap_common.c
    ${CMAKE_CURRENT_LIST_DIR}/src/eap_common/eap_teap_common.c
    ${CMAKE_CURRENT_LIST_DIR}/src/eap_common/eap_wsc_common.c
    ${CMAKE_CURRENT_LIST_DIR}/src/eap_peer/eap.c
    ${CMAKE_CURRENT_LIST_DIR}/src/eap_peer/eap_fast.c
    ${CMAKE_CURRENT_LIST_DIR}/src/eap_peer/eap_fast_pac.c
    ${CMAKE_CURRENT_LIST_DIR}/src/eap_peer/eap_gtc.c
    ${CMAKE_CURRENT_LIST_DIR}/src/eap_peer/eap_leap.c
    ${CMAKE_CURRENT_LIST_DIR}/src/eap_peer/eap_md5.c
    ${CMAKE_CURRENT_LIST_DIR}/src/eap_peer/eap_methods.c
    ${CMAKE_CURRENT_LIST_DIR}/src/eap_peer/eap_mschapv2.c
    ${CMAKE_CURRENT_LIST_DIR}/src/eap_peer/eap_otp.c
    ${CMAKE_CURRENT_LIST_DIR}/src/eap_peer/eap_peap.c
    ${CMAKE_CURRENT_LIST_DIR}/src/eap_peer/eap_teap.c
    ${CMAKE_CURRENT_LIST_DIR}/src/eap_peer/eap_teap_pac.c
    ${CMAKE_CURRENT_LIST_DIR}/src/eap_peer/eap_tls.c
    ${CMAKE_CURRENT_LIST_DIR}/src/eap_peer/eap_tls_common.c
    ${CMAKE_CURRENT_LIST_DIR}/src/eap_peer/eap_ttls.c
    ${CMAKE_CURRENT_LIST_DIR}/src/eap_peer/eap_wsc.c
    ${CMAKE_CURRENT_LIST_DIR}/src/eap_peer/mschapv2.c
    ${CMAKE_CURRENT_LIST_DIR}/src/eap_server/eap_server.c
    ${CMAKE_CURRENT_LIST_DIR}/src/eap_server/eap_server_identity.c
    ${CMAKE_CURRENT_LIST_DIR}/src/eap_server/eap_server_methods.c
    ${CMAKE_CURRENT_LIST_DIR}/src/eap_server/eap_server_teap.c
    ${CMAKE_CURRENT_LIST_DIR}/src/eap_server/eap_server_wsc.c
    ${CMAKE_CURRENT_LIST_DIR}/src/eapol_auth/eapol_auth_sm.c
    ${CMAKE_CURRENT_LIST_DIR}/src/eapol_supp/eapol_supp_sm.c
    ${CMAKE_CURRENT_LIST_DIR}/src/rsn_supp/peerkey.c
    ${CMAKE_CURRENT_LIST_DIR}/src/rsn_supp/pmksa_cache.c
    ${CMAKE_CURRENT_LIST_DIR}/src/rsn_supp/preauth.c
    ${CMAKE_CURRENT_LIST_DIR}/src/rsn_supp/wpa.c
    ${CMAKE_CURRENT_LIST_DIR}/src/rsn_supp/wpa_ft.c
    ${CMAKE_CURRENT_LIST_DIR}/src/rsn_supp/wpa_ie.c
    ${CMAKE_CURRENT_LIST_DIR}/src/utils/base64.c
    ${CMAKE_CURRENT_LIST_DIR}/src/utils/bitfield.c
    ${CMAKE_CURRENT_LIST_DIR}/src/utils/common.c
    ${CMAKE_CURRENT_LIST_DIR}/src/utils/config.c
    ${CMAKE_CURRENT_LIST_DIR}/src/utils/crc32.c
    ${CMAKE_CURRENT_LIST_DIR}/src/utils/ext_password_file.c
    ${CMAKE_CURRENT_LIST_DIR}/src/utils/ip_addr.c
    ${CMAKE_CURRENT_LIST_DIR}/src/utils/os_internal.c
    ${CMAKE_CURRENT_LIST_DIR}/src/utils/uuid.c
    ${CMAKE_CURRENT_LIST_DIR}/src/utils/wpa_debug.c
    ${CMAKE_CURRENT_LIST_DIR}/src/utils/wpabuf.c
    ${CMAKE_CURRENT_LIST_DIR}/src/wps/wps.c
    ${CMAKE_CURRENT_LIST_DIR}/src/wps/wps_attr_build.c
    ${CMAKE_CURRENT_LIST_DIR}/src/wps/wps_attr_parse.c
    ${CMAKE_CURRENT_LIST_DIR}/src/wps/wps_attr_process.c
    ${CMAKE_CURRENT_LIST_DIR}/src/wps/wps_common.c
    ${CMAKE_CURRENT_LIST_DIR}/src/wps/wps_dev_attr.c
    ${CMAKE_CURRENT_LIST_DIR}/src/wps/wps_enrollee.c
    ${CMAKE_CURRENT_LIST_DIR}/src/wps/wps_registrar.c
)

if(NOT TI_STA_ONLY_BUILD)
    list(APPEND ${TARGET_NAME}_SOURCES
        ${CMAKE_CURRENT_LIST_DIR}/src/p2p/p2p.c
        ${CMAKE_CURRENT_LIST_DIR}/src/p2p/p2p_build.c
        ${CMAKE_CURRENT_LIST_DIR}/src/p2p/p2p_dev_disc.c
        ${CMAKE_CURRENT_LIST_DIR}/src/p2p/p2p_go_neg.c
        ${CMAKE_CURRENT_LIST_DIR}/src/p2p/p2p_group.c
        ${CMAKE_CURRENT_LIST_DIR}/src/p2p/p2p_invitation.c
        ${CMAKE_CURRENT_LIST_DIR}/src/p2p/p2p_parse.c
        ${CMAKE_CURRENT_LIST_DIR}/src/p2p/p2p_pd.c
        ${CMAKE_CURRENT_LIST_DIR}/src/p2p/p2p_sd.c
        ${CMAKE_CURRENT_LIST_DIR}/src/p2p/p2p_utils.c
        ${CMAKE_CURRENT_LIST_DIR}/src/ap/ap_config.c
        ${CMAKE_CURRENT_LIST_DIR}/src/ap/ap_drv_ops.c
        ${CMAKE_CURRENT_LIST_DIR}/src/ap/ap_list.c
        ${CMAKE_CURRENT_LIST_DIR}/src/ap/ap_mlme.c
        ${CMAKE_CURRENT_LIST_DIR}/src/ap/authsrv.c
        ${CMAKE_CURRENT_LIST_DIR}/src/ap/beacon.c
        ${CMAKE_CURRENT_LIST_DIR}/src/ap/bss_load.c
        ${CMAKE_CURRENT_LIST_DIR}/src/ap/dfs.c
        ${CMAKE_CURRENT_LIST_DIR}/src/ap/drv_callbacks.c
        ${CMAKE_CURRENT_LIST_DIR}/src/ap/eap_user_db.c
        ${CMAKE_CURRENT_LIST_DIR}/src/ap/hostapd.c
        ${CMAKE_CURRENT_LIST_DIR}/src/ap/hw_features.c
        ${CMAKE_CURRENT_LIST_DIR}/src/ap/ieee802_11.c
        ${CMAKE_CURRENT_LIST_DIR}/src/ap/ieee802_11_he.c
        ${CMAKE_CURRENT_LIST_DIR}/src/ap/ieee802_11_auth.c
        ${CMAKE_CURRENT_LIST_DIR}/src/ap/ieee802_11_ht.c
        ${CMAKE_CURRENT_LIST_DIR}/src/ap/ieee802_11_vht.c
        ${CMAKE_CURRENT_LIST_DIR}/src/ap/ieee802_11_shared.c
        ${CMAKE_CURRENT_LIST_DIR}/src/ap/ieee802_1x.c
        ${CMAKE_CURRENT_LIST_DIR}/src/ap/mbo_ap.c
        ${CMAKE_CURRENT_LIST_DIR}/src/ap/neighbor_db.c
        ${CMAKE_CURRENT_LIST_DIR}/src/ap/peerkey_auth.c
        ${CMAKE_CURRENT_LIST_DIR}/src/ap/pmksa_cache_auth.c
        ${CMAKE_CURRENT_LIST_DIR}/src/ap/p2p_hostapd.c
        ${CMAKE_CURRENT_LIST_DIR}/src/ap/rrm.c
        ${CMAKE_CURRENT_LIST_DIR}/src/ap/sta_info.c
        ${CMAKE_CURRENT_LIST_DIR}/src/ap/tkip_countermeasures.c
        ${CMAKE_CURRENT_LIST_DIR}/src/ap/utils.c
        ${CMAKE_CURRENT_LIST_DIR}/src/ap/wmm.c
        ${CMAKE_CURRENT_LIST_DIR}/src/ap/wpa_auth.c
        ${CMAKE_CURRENT_LIST_DIR}/src/ap/wpa_auth_ft.c
        ${CMAKE_CURRENT_LIST_DIR}/src/ap/wpa_auth_glue.c
        ${CMAKE_CURRENT_LIST_DIR}/src/ap/wpa_auth_ie.c
        ${CMAKE_CURRENT_LIST_DIR}/src/ap/wps_hostapd.c
    )
endif()

list(APPEND ${TARGET_NAME}_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/wpa_supplicant/bss.c
    ${CMAKE_CURRENT_LIST_DIR}/wpa_supplicant/bssid_ignore.c
    ${CMAKE_CURRENT_LIST_DIR}/wpa_supplicant/config.c
    ${CMAKE_CURRENT_LIST_DIR}/wpa_supplicant/eap_register.c
    ${CMAKE_CURRENT_LIST_DIR}/wpa_supplicant/events.c
    ${CMAKE_CURRENT_LIST_DIR}/wpa_supplicant/gas_query.c
    ${CMAKE_CURRENT_LIST_DIR}/wpa_supplicant/mbo.c
    ${CMAKE_CURRENT_LIST_DIR}/wpa_supplicant/notify.c
    ${CMAKE_CURRENT_LIST_DIR}/wpa_supplicant/offchannel.c
    ${CMAKE_CURRENT_LIST_DIR}/wpa_supplicant/op_classes.c
    ${CMAKE_CURRENT_LIST_DIR}/wpa_supplicant/robust_av.c
    ${CMAKE_CURRENT_LIST_DIR}/wpa_supplicant/rrm_sta.c
    ${CMAKE_CURRENT_LIST_DIR}/wpa_supplicant/scan.c
    ${CMAKE_CURRENT_LIST_DIR}/wpa_supplicant/sme.c
    ${CMAKE_CURRENT_LIST_DIR}/wpa_supplicant/twt.c
    ${CMAKE_CURRENT_LIST_DIR}/wpa_supplicant/wmm_ac.c
    ${CMAKE_CURRENT_LIST_DIR}/wpa_supplicant/wnm_sta.c
    ${CMAKE_CURRENT_LIST_DIR}/wpa_supplicant/wpas_glue.c
    ${CMAKE_CURRENT_LIST_DIR}/wpa_supplicant/wpa_supplicant.c
)

list(APPEND ${TARGET_NAME}_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/wpa_supplicant/wps_supplicant.c
)

if(NOT TI_STA_ONLY_BUILD)
    list(APPEND ${TARGET_NAME}_SOURCES
        ${CMAKE_CURRENT_LIST_DIR}/wpa_supplicant/ap.c
        ${CMAKE_CURRENT_LIST_DIR}/wpa_supplicant/p2p_supplicant.c
        ${CMAKE_CURRENT_LIST_DIR}/wpa_supplicant/p2p_supplicant_sd.c
    )
endif()

set (${TARGET_NAME}_HEADERS

    ${CMAKE_CURRENT_LIST_DIR}/ti_config/build_configs.h
)

set (${TARGET_NAME}_INCLUDES

    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/src
    ${CMAKE_CURRENT_LIST_DIR}/hostapd
    ${CMAKE_CURRENT_LIST_DIR}/src/crypto
    ${CMAKE_CURRENT_LIST_DIR}/wpa_supplicant
    ${CMAKE_CURRENT_LIST_DIR}/src/utils
    ${CMAKE_CURRENT_LIST_DIR}/src/eapol_supp
    ${CMAKE_CURRENT_LIST_DIR}/src/ap
    ${CMAKE_CURRENT_LIST_DIR}/src/common
    ${CMAKE_CURRENT_LIST_DIR}/src/drivers
    ${CMAKE_CURRENT_LIST_DIR}/src/eap_common
    ${CMAKE_CURRENT_LIST_DIR}/src/eap_peer
    ${CMAKE_CURRENT_LIST_DIR}/src/eap_server
    ${CMAKE_CURRENT_LIST_DIR}/src/eapol_auth
    ${CMAKE_CURRENT_LIST_DIR}/src/l2_packet
    ${CMAKE_CURRENT_LIST_DIR}/src/p2p
    ${CMAKE_CURRENT_LIST_DIR}/src/radius
    ${CMAKE_CURRENT_LIST_DIR}/src/rsn_supp
    ${CMAKE_CURRENT_LIST_DIR}/src/wps
    ${CMAKE_CURRENT_LIST_DIR}/src/fst
    ${CMAKE_CURRENT_LIST_DIR}/src/tls
    ${CMAKE_CURRENT_LIST_DIR}/wpa_supplicant/dbus

    $<TARGET_PROPERTY:wifi_host_driver,INCLUDE_DIRECTORIES>

)

set (${TARGET_NAME}_LIBRARIES

    wifi_stack
    ${CMAKE_COMMON_LIBRARY}
    
)

#we will build always with optimization due to space constraints.
set (${TARGET_NAME}_COMPILER_FLAGS ${RELEASE_FLAGS} 

    -Wno-error
    --include=${CMAKE_CURRENT_LIST_DIR}/ti_config/build_configs.h

) #check release flags 

set (${TARGET_NAME}_DEFINITIONS

    HOSTAP
)


#openssl library flavour
if(CRYPTO_OPENSSL)

    list(APPEND ${TARGET_NAME}_SOURCES 

        ${CMAKE_CURRENT_LIST_DIR}/src/crypto/crypto_openssl.c
        ${CMAKE_CURRENT_LIST_DIR}/src/crypto/tls_none.c
        ${CMAKE_CURRENT_LIST_DIR}/src/tls/bignum.c
    )

    list(APPEND ${TARGET_NAME}_DEFINITIONS 
        
        CONFIG_OPENSSL_CMAC
    )
    
endif()

add_library               (${TARGET_NAME}         ${${TARGET_NAME}_SOURCES})
target_compile_options    (${TARGET_NAME} PRIVATE ${${TARGET_NAME}_COMPILER_FLAGS})
target_compile_definitions(${TARGET_NAME} PRIVATE ${${TARGET_NAME}_DEFINITIONS})
target_include_directories(${TARGET_NAME} PRIVATE ${${TARGET_NAME}_INCLUDES})
target_precompile_headers (${TARGET_NAME} PRIVATE ${${TARGET_NAME}_HEADERS})
target_link_libraries     (${TARGET_NAME} PRIVATE ${${TARGET_NAME}_LIBRARIES})


#set install option
install(TARGETS ${TARGET_NAME} DESTINATION ${CMAKE_CURRENT_LIST_DIR}/${LIB_DEST_DIR})
