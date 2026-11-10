/*
 * Copyright (c) 2026 Conclusive Engineering Sp. z o.o.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef TI_ITS_INIT_H_
#define TI_ITS_INIT_H_

#include <third_party/hsmddk/include/Integration/Adapter_PSA/incl/psa/error.h>

psa_status_t ti_cc35xx_its_status(void);
psa_status_t ti_cc35xx_its_lock(void);
void ti_cc35xx_its_unlock(void);

#endif /* TI_ITS_INIT_H_ */
