#include <stdint.h>

/*
 * PG2 RTM, 4MB flash, NO OTA layout.
 * Derived from board config: boards/ti/lp_em_cc35x1/config/flash_disc_param_ext_mem.json
 *
 * Region 1 (boot): 0x00000000 - 0x00105FFF
 *   WiFi FW slot 1: GPE at 0x00068FFC
 *   WiFi FW slot 2: GPE at 0x000DAFFC
 *   Protected storage header: 0x000DA000, size 0x01000
 *   WiFi NVS:       0x000DB000, size 0x23000
 *   Key storage:    0x000FE000, size 0x08000
 * Region 0 (code): 0x00106000 - 0x003FFFFF
 *   Vendor image:   GPE at 0x00106FFC
 */

/* WiFi Connectivity Slot 1 memory configuration
 * JSON: nvs_region_primary_wsoc_start_phy_address = 0x68FFC (GPE header)
 * Slot base = 0x68FFC - 0xFFC = 0x68000
 * Slot size = slot2_base - slot1_base = 0xDA000 - 0x68000 = 0x72000
 */
uint32_t wifi_connectivity_physical_slot_1_address = 0x00068000;
uint32_t wifi_connectivity_logical_slot_1_address = 0xA0068000;
uint32_t wifi_connectivity_slot_1_region_size = 0x00072000;

/* WiFi Connectivity Slot 2 memory configuration
 * JSON: nvs_region_sec_wsoc_start_phy_address = 0xDAFFC (GPE header)
 * Slot base = 0xDAFFC - 0xFFC = 0xDA000
 * No OTA layout: the secondary WiFi slot is unused.
 */
uint32_t wifi_connectivity_physical_slot_2_address = 0x000DA000;
uint32_t wifi_connectivity_logical_slot_2_address = 0xA00DA000;
uint32_t wifi_connectivity_slot_2_region_size = 0;

/* Vendor Image Slot 1 memory configuration
 * JSON: main_code_region_vendor_image_start_phy_address = 0x106FFC
 * Slot base = 0x106FFC - 0xFFC = 0x106000
 * Region 0 end = 0x3FFFFF, size = 0x400000 - 0x106000 = 0x2FA000
 */
uint32_t vendor_image_physical_slot_1_address = 0x00106000;
uint32_t vendor_image_logical_slot_1_address = 0x14000000;
uint32_t vendor_image_slot_1_region_size = 0x002FA000;

/* Vendor Image Slot 2 (not used in NO OTA) */
uint32_t vendor_image_physical_slot_2_address = 0;
uint32_t vendor_image_logical_slot_2_address = 0;
uint32_t vendor_image_slot_2_region_size = 0;

/* BL2 Slot 1 memory configuration
 * JSON: boot_region_primary_ti_bl_start_phy_address = 0x2FFC
 * Slot base = 0x2FFC - 0xFFC = 0x2000
 */
uint32_t bl2_physical_slot_1_address = 0x00002000;
uint32_t bl2_logical_slot_1_address = 0xA0002000;
uint32_t bl2_slot_1_region_size = 0x00066000;

/* BL2 Slot 2
 * JSON: boot_region_sec_ti_bl_start_phy_address = 0x68FFC
 * Overlaps with WiFi slot 1 — not used in NO OTA
 */
uint32_t bl2_physical_slot_2_address = 0;
uint32_t bl2_logical_slot_2_address = 0;
uint32_t bl2_slot_2_region_size = 0;

/* NVOCMP memory configuration
 * MemoryConfigurator: protected storage header at 0xDA000, then NVS at
 * 0xDB000 with a size of 0x23000.
 */
uint32_t nvocmp_physical_slot_address = 0x000DB000;
uint32_t nvocmp_logical_slot_address = 0xA00DB000;
uint32_t nvocmp_region_size = 0x00023000;

/* Key Storage: fixed 32 KiB region after WiFi NVS. */
uint32_t key_storage_physical_slot_address = 0x000FE000;
uint32_t key_storage_logical_slot_address = 0xA00FE000;
uint32_t key_storage_region_size = 0x00008000;
