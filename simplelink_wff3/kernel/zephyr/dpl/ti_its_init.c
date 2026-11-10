/*
 * Copyright (c) 2026 Conclusive Engineering Sp. z o.o.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <errno.h>

#include <zephyr/init.h>
#include <zephyr/kernel.h>

#include <third_party/hsmddk/include/Integration/Adapter_ITS/incl/tfm_internal_trusted_storage.h>

#include "ti_its_init.h"

static psa_status_t its_status = PSA_ERROR_BAD_STATE;
K_MUTEX_DEFINE(its_mutex);

static int ti_cc35xx_its_init(void)
{
	its_status = tfm_its_init();

	return its_status == PSA_SUCCESS ? 0 : -EIO;
}

SYS_INIT(ti_cc35xx_its_init, APPLICATION, CONFIG_APPLICATION_INIT_PRIORITY);

psa_status_t ti_cc35xx_its_status(void)
{
	return its_status;
}

psa_status_t ti_cc35xx_its_lock(void)
{
	if (its_status != PSA_SUCCESS) {
		return its_status;
	}

	return k_mutex_lock(&its_mutex, K_FOREVER) == 0 ? PSA_SUCCESS : PSA_ERROR_BAD_STATE;
}

void ti_cc35xx_its_unlock(void)
{
	k_mutex_unlock(&its_mutex);
}
