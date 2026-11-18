#ifndef TI_FLASH_MAP_CONFIG_H_
#define TI_FLASH_MAP_CONFIG_H_

#include <stdint.h>

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

/* BL2 Slot 1 memory configuration */
extern uint32_t bl2_physical_slot_1_address;
extern uint32_t bl2_logical_slot_1_address;
extern uint32_t bl2_slot_1_region_size;

/* BL2 Slot 2 memory configuration */
extern uint32_t bl2_physical_slot_2_address;
extern uint32_t bl2_logical_slot_2_address;
extern uint32_t bl2_slot_2_region_size;

/* NVOCMP memory configuration */
extern uint32_t nvocmp_physical_slot_address;
extern uint32_t nvocmp_logical_slot_address;
extern uint32_t nvocmp_region_size;

/* Key Storage memory configuration */
extern uint32_t key_storage_physical_slot_address;
extern uint32_t key_storage_logical_slot_address;
extern uint32_t key_storage_region_size;

#endif /* TI_FLASH_MAP_CONFIG_H_ */
