/*
 * Copyright (c) 2026 Conclusive Engineering Sp. z o.o.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdint.h>

#include <zephyr/device.h>
#include <zephyr/drivers/entropy.h>
#include <zephyr/kernel.h>
#include <zephyr/random/random.h>

#include <mbedtls/entropy.h>

static const struct device *const entropy_dev =
	DEVICE_DT_GET_OR_NULL(DT_CHOSEN(zephyr_entropy));

int mbedtls_hardware_poll(void *data, unsigned char *output, size_t len, size_t *olen)
{
	uint16_t request_len = len > UINT16_MAX ? UINT16_MAX : len;

	ARG_UNUSED(data);

	if (output == NULL || olen == NULL || len == 0) {
		return MBEDTLS_ERR_ENTROPY_SOURCE_FAILED;
	}

	if (!IS_ENABLED(CONFIG_ENTROPY_HAS_DRIVER)) {
		sys_rand_get(output, len);
		*olen = len;

		return 0;
	}

	if (entropy_dev == NULL || !device_is_ready(entropy_dev)) {
		return MBEDTLS_ERR_ENTROPY_SOURCE_FAILED;
	}

	if (entropy_get_entropy(entropy_dev, output, request_len) < 0) {
		return MBEDTLS_ERR_ENTROPY_SOURCE_FAILED;
	}

	*olen = request_len;

	return 0;
}
