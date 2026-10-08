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

#include <osi_kernel.h>
#include <string.h>
#include <zephyr/kernel.h>
#include <zephyr/init.h>
#include <zephyr/fs/nvs.h>
#include <zephyr/storage/flash_map.h>
#include <zephyr/drivers/flash.h>
#include <zephyr/logging/log.h>

#ifdef CONFIG_WIFI_TI_CC33XX
#include <cc33xx_fw_blobs.h>
#endif /* CONFIG_WIFI_TI_CC33XX */

/* Zephyr 3.7 exposes only the legacy FIXED_PARTITION_* helpers. */
#if !defined(PARTITION_DEVICE)
#define PARTITION_DEVICE(label) FIXED_PARTITION_DEVICE(label)
#define PARTITION_OFFSET(label) FIXED_PARTITION_OFFSET(label)
#define PARTITION_SIZE(label)   FIXED_PARTITION_SIZE(label)
#endif

#define FW_SLOT1_DEV    PARTITION_DEVICE(wifi_fw_slot1_partition)
#define FW_SLOT1_OFFSET PARTITION_OFFSET(wifi_fw_slot1_partition)
#define FW_SLOT2_DEV    PARTITION_DEVICE(wifi_fw_slot2_partition)
#define FW_SLOT2_OFFSET PARTITION_OFFSET(wifi_fw_slot2_partition)

LOG_MODULE_REGISTER(osi_filesystem, CONFIG_LOG_DEFAULT_LEVEL);

/*
 * NVS item IDs - direct mapping from TI's NVOCMP item IDs.
 */
#define NVS_ID_BLE_OUR_SEC      0x01
#define NVS_ID_BLE_PEER_SEC     0x02
#define NVS_ID_BLE_CCCD         0x03
#define NVS_ID_WLAN_CONN_POL    0x04
#define NVS_ID_WLAN_PROFILES    0x05
#define NVS_ID_WLAN_FAST_CONN   0x06

/*
 * GPE (General Purpose Entity) flash format constants.
 */
#define GPE_MANIFEST_IMAGE_START_OFFSET 0xFFC
#define GPE_MANIFEST_INTEGRITY_LEN      0x10
#define GPE_HEADER_MAGIC_NUM            0x690c47c2
#define GPE_PROTECTED_TLV_MAGIC_NUM     0x6908
#define CONF_BIN_TLV_TYPE               0x00B2
#define GPE_MANIFEST_TLV_TYPE           0x00A0

/* Default FW data offset within the GPE slot */
#define FW_GPE_DATA_OFFSET_DEFAULT      0x101c


typedef enum {
	OSI_FILE_CONNECTIVITY_FW_SLOT_1,
	OSI_FILE_CONNECTIVITY_FW_SLOT_2,
	OSI_FILE_CONF,
	OSI_FILE_RAMBTLR,
	OSI_FILE_BLE_OUR_SEC,
	OSI_FILE_BLE_PEER_SEC,
	OSI_FILE_BLE_CCCD,
	OSI_FILE_WLAN_CONNECTION_POLICY,
	OSI_FILE_WLAN_PROFILE,
	OSI_FILE_WLAN_FAST_CONNECT,
} osiInternalType_e;

typedef struct {
	osiInternalType_e ftype;
	void *ptr;
} osiFileP_t;

typedef struct {
	uint32_t ihMagic;
	uint32_t ihLoadAddr;
	uint16_t ihHdrSize;
	uint16_t ihProtectTlvSize;
	uint32_t ihImgSize;
	uint32_t ihFlags;
} gpeManifestHeader_t;

typedef struct {
	uint16_t itMagic;
	uint16_t itTlvTot;
} gpeTlvInfo_t;

typedef struct {
	uint16_t itType;
	uint16_t itLen;
} gpeTlvManifestHeader_t;

typedef struct {
	uint16_t itType;
	uint16_t reserved;
	uint32_t tlvTablePointerShift;
} gpeTlvManifestTableLine_t;

typedef struct {
	uint16_t itType;
	uint16_t itLen;
} gpeTlvHeader_t;

#define IS_NV_FILE(t) ((t) >= OSI_FILE_BLE_OUR_SEC && (t) <= OSI_FILE_WLAN_FAST_CONNECT)


/* Static file handle for cc35xx-conf. */
static osiFileP_t conf_file = {
	.ftype = OSI_FILE_CONF,
};

#ifdef CONFIG_HAS_CC35XX_SDK
/* Runtime offset of conf.bin within vendor_image_partition */
static off_t conf_flash_offset;
static bool conf_flash_found;
#endif /* CONFIG_HAS_CC35XX_SDK */


/* Module state */
static struct nvs_fs wifi_nvs;
static uint32_t active_fw_slot = OSI_FLASH_CONNECTIVITY_FW_SLOT_1;
#ifdef CONFIG_HAS_CC35XX_SDK
static uint32_t fw_gpe_data_offset = FW_GPE_DATA_OFFSET_DEFAULT;
#endif /* CONFIG_HAS_CC35XX_SDK */

/* NVS ID lookup table indexed by osiInternalType_e */
static const uint16_t nvs_id_map[] = {
	[OSI_FILE_BLE_OUR_SEC]            = NVS_ID_BLE_OUR_SEC,
	[OSI_FILE_BLE_PEER_SEC]           = NVS_ID_BLE_PEER_SEC,
	[OSI_FILE_BLE_CCCD]               = NVS_ID_BLE_CCCD,
	[OSI_FILE_WLAN_CONNECTION_POLICY] = NVS_ID_WLAN_CONN_POL,
	[OSI_FILE_WLAN_PROFILE]           = NVS_ID_WLAN_PROFILES,
	[OSI_FILE_WLAN_FAST_CONNECT]      = NVS_ID_WLAN_FAST_CONN,
};

#ifdef CONFIG_HAS_CC35XX_SDK
/*
 * GPE TLV parser
 * This function gets the offset to the protected TLV manifest
 * zone within a flash GPE.
 */
static int32_t osi_get_protected_tlv_manifest_hdr(const struct device *dev,
						   gpeTlvManifestHeader_t *tlv_mhdr,
						   uint32_t *hdr_offset)
{
	gpeManifestHeader_t gpe_hdr;
	gpeTlvInfo_t tlv_info;
	uint32_t offset, magic;

	/* Verify GPE magic sentinel at manifest + 0x1C */
	if (flash_read(dev, GPE_MANIFEST_IMAGE_START_OFFSET + 0x1C,
		       &magic, sizeof(magic)) != 0 ||
	    magic != GPE_HEADER_MAGIC_NUM) {
		return -1;
	}

	/* Read GPE manifest header at 0xFFC (magic field unreliable) */
	offset = GPE_MANIFEST_IMAGE_START_OFFSET;
	if (flash_read(dev, offset, &gpe_hdr, sizeof(gpe_hdr)) != 0) {
		return -1;
	}

	if (gpe_hdr.ihProtectTlvSize == 0) {
		return -1;
	}

	/* Protected TLV zone: after header + image data */
	offset += gpe_hdr.ihHdrSize + gpe_hdr.ihImgSize;

	if (flash_read(dev, offset, &tlv_info, sizeof(tlv_info)) != 0 ||
	    tlv_info.itMagic != GPE_PROTECTED_TLV_MAGIC_NUM) {
		return -1;
	}

	/* Read manifest TLV header */
	offset += sizeof(gpeTlvInfo_t);
	if (flash_read(dev, offset, tlv_mhdr, sizeof(*tlv_mhdr)) != 0 ||
	    tlv_mhdr->itType != GPE_MANIFEST_TLV_TYPE) {
		return -1;
	}

	*hdr_offset = offset;
	return 0;
}

/*
 * This function iterates a GPE TLV zone (either protected or
 * not) and extracts a requested TLV.
 */
static int32_t osi_find_tlv_in_manifest(const struct device *dev,
					uint32_t manifest_hdr_offset,
					gpeTlvManifestHeader_t *tlv_mhdr,
					uint16_t requested_type,
					uint32_t *requested_offset)
{
	gpeTlvManifestTableLine_t line;
	uint32_t table_offset, tlv_start;
	uint16_t count;

	table_offset = manifest_hdr_offset + sizeof(gpeTlvManifestHeader_t);
	count = tlv_mhdr->itLen / sizeof(gpeTlvManifestTableLine_t);
	tlv_start = table_offset + tlv_mhdr->itLen;

	for (uint16_t i = 0; i < count; i++) {
		if (flash_read(dev, table_offset, &line, sizeof(line)) != 0) {
			return -1;
		}

		if (line.itType == requested_type) {
			*requested_offset = tlv_start + line.tlvTablePointerShift;
			return 0;
		}

		table_offset += sizeof(gpeTlvManifestTableLine_t);
	}

	return -1;
}

/*
 * This function gets the cc35xx-conf.bin file offset within the
 * vendor image GPE slot.
 */
static void osi_conf_flash_init(void)
{
	const struct device *dev;
	gpeTlvManifestHeader_t tlv_mhdr;
	uint32_t manifest_offset, conf_tlv_offset;

	dev = PARTITION_DEVICE(vendor_image_partition);
	if (!device_is_ready(dev)) {
		LOG_ERR("vendor_image flash not ready");
		return;
	}

	if (osi_get_protected_tlv_manifest_hdr(dev, &tlv_mhdr,
					       &manifest_offset) != 0) {
		LOG_ERR("GPE manifest parse failed");
		return;
	}

	if (osi_find_tlv_in_manifest(dev, manifest_offset, &tlv_mhdr,
				     CONF_BIN_TLV_TYPE,
				     &conf_tlv_offset) != 0) {
		LOG_ERR("CONF_BIN TLV not found in manifest");
		return;
	}

	/* Skip TLV header to get to conf data */
	conf_flash_offset = conf_tlv_offset + sizeof(gpeTlvHeader_t);
	conf_flash_found = true;

	LOG_DBG("cc35xx-conf loaded from flash GPE at 0x%x",
		(unsigned int)conf_flash_offset);
}
#endif /* CONFIG_HAS_CC35XX_SDK */

/*
 * Initialize the NVS filesystem on the wifi-nvs partition.
 */
static int osi_nvs_init(void)
{
	int rc;
	struct flash_pages_info info;

#ifdef CONFIG_HAS_CC35XX_SDK
	/* Find conf in flash GPE */
	osi_conf_flash_init();
#endif /* CONFIG_HAS_CC35XX_SDK */

	wifi_nvs.flash_device = PARTITION_DEVICE(wifi_nvs_partition);
	if (!device_is_ready(wifi_nvs.flash_device)) {
		LOG_ERR("NVS flash device not ready");
		return -ENODEV;
	}

	wifi_nvs.offset = PARTITION_OFFSET(wifi_nvs_partition);

	rc = flash_get_page_info_by_offs(wifi_nvs.flash_device, wifi_nvs.offset,
					 &info);
	if (rc) {
		LOG_ERR("Failed to get flash page info: %d", rc);
		return rc;
	}

	wifi_nvs.sector_size = info.size;
	wifi_nvs.sector_count = PARTITION_SIZE(wifi_nvs_partition) / info.size;

	rc = nvs_mount(&wifi_nvs);
	if (rc) {
		LOG_ERR("NVS mount failed: %d", rc);
		return rc;
	}

	return 0;
}

/*
 * Allocate a file handle for an NV-backed file.
 */
static FILE *open_nv_file(osiInternalType_e ftype)
{
	osiFileP_t *f;

	f = k_malloc(sizeof(osiFileP_t));
	if (!f) {
		return NULL;
	}

	f->ftype = ftype;
	return (FILE *)f;
}

int ATTRIBUTE osi_fset(osiFileSetType containerType, void *params)
{
	if (containerType == OSI_FILESYSTEM_SET_CONNECTIVITY_FW_CONTAINER) {
		osiFlashFwSlot_e slot = *(osiFlashFwSlot_e *)params;

		if (slot == OSI_FLASH_CONNECTIVITY_FW_SLOT_1 ||
		    slot == OSI_FLASH_CONNECTIVITY_FW_SLOT_2) {
			active_fw_slot = slot;
		}
	}

	return 0;
}

int ATTRIBUTE osi_fget(osiFileGetType containerType, void *params)
{
	if (containerType == OSI_FILESYSTEM_GET_CONNECTIVITY_FW_CONTAINER) {
		*(osiFlashFwSlot_e *)params = active_fw_slot;
	}

	return 0;
}

int ATTRIBUTE osi_fclose(FILE *_fp)
{
	osiFileP_t *f = (osiFileP_t *)_fp;

	if (!f) {
		return -EINVAL;
	}

	if (f != &conf_file) {
		k_free(f);
	}
	return 0;
}

FILE *ATTRIBUTE osi_fopen(const char *_fname, const char *_mode)
{
	osiFileP_t *f;

	if (strcmp("rambtlr", _fname) == 0) {
		f = k_malloc(sizeof(osiFileP_t));
		if (!f) {
			return NULL;
		}
		f->ftype = OSI_FILE_RAMBTLR;
#ifdef CONFIG_HAS_CC35XX_SDK
		f->ptr = NULL;
#else
		f->ptr = (void*)gRAMbootBuffer;
#endif /* CONFIG_HAS_CC35XX_SDK */
		return (FILE *)f;
	}

	if (strcmp("fw", _fname) == 0) {
		f = k_malloc(sizeof(osiFileP_t));
		if (!f) {
			return NULL;
		}

		if (active_fw_slot == OSI_FLASH_CONNECTIVITY_FW_SLOT_1) {
			f->ftype = OSI_FILE_CONNECTIVITY_FW_SLOT_1;
		} else {
			f->ftype = OSI_FILE_CONNECTIVITY_FW_SLOT_2;
		}

#ifdef CONFIG_HAS_CC35XX_SDK
		f->ptr = NULL;
#else
		f->ptr = (void*)gFWbuffer;
#endif /* CONFIG_HAS_CC35XX_SDK */
		return (FILE *)f;
	}

	if (strcmp("cc35xx-conf", _fname) == 0) {
		f = &conf_file;
#ifdef CONFIG_HAS_CC35XX_SDK
		f->ptr = NULL;
#else
		f->ptr = (void*)gINIbuffer;
#endif /* CONFIG_HAS_CC35XX_SDK */
		return (FILE *)f;
	}

	/* NV-backed files */
	if (strcmp("our_sec", _fname) == 0) {
		return open_nv_file(OSI_FILE_BLE_OUR_SEC);
	}
	if (strcmp("peer_sec", _fname) == 0) {
		return open_nv_file(OSI_FILE_BLE_PEER_SEC);
	}
	if (strcmp("cccd", _fname) == 0) {
		return open_nv_file(OSI_FILE_BLE_CCCD);
	}
	if (strcmp("conn_p", _fname) == 0) {
		return open_nv_file(OSI_FILE_WLAN_CONNECTION_POLICY);
	}
	if (strcmp("profiles", _fname) == 0) {
		return open_nv_file(OSI_FILE_WLAN_PROFILE);
	}
	if (strcmp(".fast", _fname) == 0) {
		return open_nv_file(OSI_FILE_WLAN_FAST_CONNECT);
	}

	LOG_WRN("Unknown file: %s", _fname);
	return NULL;
}

size_t ATTRIBUTE osi_fread(void *_ptr, size_t len, size_t offset, FILE *_fp)
{
	osiFileP_t *f = (osiFileP_t *)_fp;
#ifdef CONFIG_HAS_CC35XX_SDK
	const struct device *fw_dev;
	off_t fw_base;
	int ret;
#endif /* CONFIG_HAS_CC35XX_SDK */

	if (!f) {
		return 0;
	}

	if (f->ftype == OSI_FILE_RAMBTLR) {
		/* RAM bootloader - memcpy from ptr if available */
		if (f->ptr) {
			memcpy(_ptr, (void *)((uintptr_t)(f->ptr) + offset), len);
			return len;
		}
		return 0;
	}

	if (f->ftype == OSI_FILE_CONF) {
		if (f->ptr) {
			memcpy(_ptr, (void *)((uintptr_t)(f->ptr) + offset), len);
			return len;
		}
#ifdef CONFIG_HAS_CC35XX_SDK
		if (!conf_flash_found) {
			LOG_ERR("Conf not found in flash GPE");
			return 0;
		}
		ret = flash_read(
			PARTITION_DEVICE(vendor_image_partition),
			conf_flash_offset + offset, _ptr, len);
		if (ret < 0) {
			LOG_ERR("Conf flash read failed: %d", ret);
			return 0;
		}
		return len;
#endif /* CONFIG_HAS_CC35XX_SDK */
	}

	if (f->ftype == OSI_FILE_CONNECTIVITY_FW_SLOT_1 ||
	    f->ftype == OSI_FILE_CONNECTIVITY_FW_SLOT_2) {
		if (f->ptr) {
			memcpy(_ptr, (void *)((uintptr_t)(f->ptr) + offset), len);
			return len;
		}
#ifdef CONFIG_HAS_CC35XX_SDK
		fw_dev = (f->ftype == OSI_FILE_CONNECTIVITY_FW_SLOT_1)
			 ? FW_SLOT1_DEV : FW_SLOT2_DEV;
		fw_base = (f->ftype == OSI_FILE_CONNECTIVITY_FW_SLOT_1)
			  ? FW_SLOT1_OFFSET : FW_SLOT2_OFFSET;

		ret = flash_read(fw_dev, fw_base + fw_gpe_data_offset + offset,
				 _ptr, len);
		if (ret < 0) {
			LOG_ERR("Flash read FW failed: %d", ret);
			return 0;
		}
		return len;
#endif /* CONFIG_HAS_CC35XX_SDK */
	}

	if (IS_NV_FILE(f->ftype)) {
		uint16_t nvs_id = nvs_id_map[f->ftype];
		ssize_t bytes = nvs_read(&wifi_nvs, nvs_id, _ptr, len);

		if (bytes < 0) {
			LOG_DBG("NVS read id=0x%02x failed: %zd", nvs_id, bytes);
			return 0;
		}
		return (size_t)bytes;
	}

	return 0;
}

size_t osi_fwrite(const void *_ptr, size_t _size, size_t _count, FILE *_fp)
{
	osiFileP_t *f = (osiFileP_t *)_fp;

	if (!f) {
		return 0;
	}

	if (IS_NV_FILE(f->ftype)) {
		uint16_t nvs_id = nvs_id_map[f->ftype];
		size_t total = _size * _count;
		ssize_t bytes = nvs_write(&wifi_nvs, nvs_id, _ptr, total);

		if (bytes < 0) {
			LOG_ERR("NVS write id=0x%02x failed: %zd", nvs_id, bytes);
			return 0;
		}
		return total;
	}

	LOG_WRN("Write not supported for file type %d", f->ftype);
	return 0;
}

int osi_fremove(FILE *_fp)
{
	osiFileP_t *f = (osiFileP_t *)_fp;

	if (!f) {
		return -1;
	}

	if (IS_NV_FILE(f->ftype)) {
		uint16_t nvs_id = nvs_id_map[f->ftype];
		int ret = nvs_delete(&wifi_nvs, nvs_id);

		if (ret < 0) {
			LOG_ERR("NVS delete id=0x%02x failed: %d", nvs_id, ret);
			return -1;
		}
		return 0;
	}

	return 0;
}

size_t ATTRIBUTE osi_filelength(const char *FileName)
{
	return 0;
}

SYS_INIT(osi_nvs_init, POST_KERNEL, CONFIG_WIFI_TI_CC3XXX_NVS_INIT_PRIORITY);
