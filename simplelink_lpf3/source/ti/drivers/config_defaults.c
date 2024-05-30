#include <stdint.h>
#include <stddef.h>

/*
 *  ======== AESCCM ========
 */

extern const uint_least8_t                  CONFIG_AESCCM_0_CONST;
#define CONFIG_AESCCM_0                     0
#define CONFIG_TI_DRIVERS_AESCCM_COUNT      1


/*
 *  ======== AESCMAC ========
 */

extern const uint_least8_t                  CONFIG_AESCMAC_0_CONST;
#define CONFIG_AESCMAC_0                    0
#define CONFIG_TI_DRIVERS_AESCMAC_COUNT     1


/*
 *  ======== AESCTR ========
 */

extern const uint_least8_t                  CONFIG_AESCTR_0_CONST;
#define CONFIG_AESCTR_0                     0
#define CONFIG_TI_DRIVERS_AESCTR_COUNT      1


/*
 *  ======== AESCTRDRBG ========
 */

extern const uint_least8_t                      CONFIG_AESCTRDRBG_0_CONST;
#define CONFIG_AESCTRDRBG_0                     0
#define CONFIG_TI_DRIVERS_AESCTRDRBG_COUNT      1


/*
 *  ======== AESECB ========
 */

extern const uint_least8_t                  CONFIG_AESECB_0_CONST;
#define CONFIG_AESECB_0                     0
#define CONFIG_TI_DRIVERS_AESECB_COUNT      1


/*
 *  ======== ECDH ========
 */

extern const uint_least8_t              CONFIG_ECDH_0_CONST;
#define CONFIG_ECDH_0                   0
#define CONFIG_TI_DRIVERS_ECDH_COUNT    1

/*
 *  =============================== AESCCM ===============================
 */

#include <ti/drivers/AESCCM.h>
#include <ti/drivers/aesccm/AESCCMLPF3.h>

#define CONFIG_AESCCM_COUNT 1
AESCCMLPF3_Object AESCCMLPF3_objects[CONFIG_AESCCM_COUNT];

/*
 *  ======== AESCCMLPF3_hwAttrs ========
 */
const AESCCMLPF3_HWAttrs AESCCMLPF3_hwAttrs[CONFIG_AESCCM_COUNT] = {
    {
        .intPriority = (~0),
    },
};

const AESCCM_Config AESCCM_config[CONFIG_AESCCM_COUNT] = {
    {   /* CONFIG_AESCCM_0 */
        .object  = &AESCCMLPF3_objects[CONFIG_AESCCM_0],
        .hwAttrs = &AESCCMLPF3_hwAttrs[CONFIG_AESCCM_0]
    },
};

const uint_least8_t CONFIG_AESCCM_0_CONST = CONFIG_AESCCM_0;
const uint_least8_t AESCCM_count = CONFIG_AESCCM_COUNT;

/*
 *  =============================== AESCMAC ===============================
 */

#include <ti/drivers/AESCMAC.h>
#include <ti/drivers/aescmac/AESCMACLPF3.h>

#define CONFIG_AESCMAC_COUNT 1
AESCMACLPF3_Object AESCMACLPF3_objects[CONFIG_AESCMAC_COUNT];

/*
 *  ======== AESCMACLPF3_hwAttrs ========
 */
const AESCMACLPF3_HWAttrs AESCMACLPF3_hwAttrs[CONFIG_AESCMAC_COUNT] = {
    {
        .intPriority = (~0),
    },
};

const AESCMAC_Config AESCMAC_config[CONFIG_AESCMAC_COUNT] = {
    {   /* CONFIG_AESCMAC_0 */
        .object  = &AESCMACLPF3_objects[CONFIG_AESCMAC_0],
        .hwAttrs = &AESCMACLPF3_hwAttrs[CONFIG_AESCMAC_0]
    },
};

const uint_least8_t CONFIG_AESCMAC_0_CONST = CONFIG_AESCMAC_0;
const uint_least8_t AESCMAC_count = CONFIG_AESCMAC_COUNT;

/*
 *  =============================== AESCTR ===============================
 */

#include <ti/drivers/AESCTR.h>
#include <ti/drivers/aesctr/AESCTRLPF3.h>

#define CONFIG_AESCTR_COUNT 1
AESCTRLPF3_Object AESCTRLPF3_objects[CONFIG_AESCTR_COUNT];

/*
 *  ======== AESCTRLPF3_hwAttrs ========
 */
const AESCTRLPF3_HWAttrs AESCTRLPF3_hwAttrs[CONFIG_AESCTR_COUNT] = {
    {
        .intPriority = (~0),
    },
};

const AESCTR_Config AESCTR_config[CONFIG_AESCTR_COUNT] = {
    {   /* CONFIG_AESCTR_0 */
        .object  = &AESCTRLPF3_objects[CONFIG_AESCTR_0],
        .hwAttrs = &AESCTRLPF3_hwAttrs[CONFIG_AESCTR_0]
    },
};

const uint_least8_t CONFIG_AESCTR_0_CONST = CONFIG_AESCTR_0;
const uint_least8_t AESCTR_count = CONFIG_AESCTR_COUNT;

/*
 *  =============================== AESCTRDRBG ===============================
 */

#include <ti/drivers/AESCTRDRBG.h>
#include <ti/drivers/aesctrdrbg/AESCTRDRBGXX.h>

#define CONFIG_AESCTRDRBG_COUNT 1

/*
 *  ======== aesctrdrbgXXObjects ========
 */
AESCTRDRBGXX_Object aesctrdrbgXXObjects[CONFIG_AESCTRDRBG_COUNT];

/*
 *  ======== aesctrdrbgXXHWAttrs ========
 */
const AESCTRDRBGXX_HWAttrs aesctrdrbgXXHWAttrs[CONFIG_AESCTRDRBG_COUNT] = {
    /* CONFIG_AESCTRDRBG_0 */
    {
        .aesctrHWAttrs.intPriority = (~0)
    },
};

/*
 *  ======== AESCTRDRBG_config ========
 */
const AESCTRDRBG_Config AESCTRDRBG_config[CONFIG_AESCTRDRBG_COUNT] = {
    /* CONFIG_AESCTRDRBG_0 */
    {
        .object = &aesctrdrbgXXObjects[CONFIG_AESCTRDRBG_0],
        .hwAttrs = &aesctrdrbgXXHWAttrs[CONFIG_AESCTRDRBG_0]
    },
};

const uint_least8_t CONFIG_AESCTRDRBG_0_CONST = CONFIG_AESCTRDRBG_0;
const uint_least8_t AESCTRDRBG_count = CONFIG_AESCTRDRBG_COUNT;

/*
 *  =============================== AESECB ===============================
 */

#include <ti/drivers/AESECB.h>
#include <ti/drivers/aesecb/AESECBLPF3.h>

#define CONFIG_AESECB_COUNT 1
AESECBLPF3_Object AESECBLPF3_objects[CONFIG_AESECB_COUNT];

/*
 *  ======== AESECBLPF3_hwAttrs ========
 */
const AESECBLPF3_HWAttrs AESECBLPF3_hwAttrs[CONFIG_AESECB_COUNT] = {
    {
        .intPriority = (~0),
    },
};

const AESECB_Config AESECB_config[CONFIG_AESECB_COUNT] = {
    {   /* CONFIG_AESECB_0 */
        .object  = &AESECBLPF3_objects[CONFIG_AESECB_0],
        .hwAttrs = &AESECBLPF3_hwAttrs[CONFIG_AESECB_0]
    },
};


const uint_least8_t CONFIG_AESECB_0_CONST = CONFIG_AESECB_0;
const uint_least8_t AESECB_count = CONFIG_AESECB_COUNT;

/*
 *  =============================== DMA ===============================
 */

#include <ti/drivers/dma/UDMALPF3.h>
#include <ti/devices/cc23x0r5/inc/hw_memmap.h>

const UDMALPF3_Config UDMALPF3_config = {
        .CtrlBaseAddr = UDMALPF3_CONFIG_BASE,
};

/*
 *  =============================== BatMon Support ===============================
 */
#include <ti/drivers/batterymonitor/BatMonSupportLPF3.h>

#include <ti/devices/DeviceFamily.h>
#include DeviceFamily_constructPath(inc/hw_evtsvt.h)
#include DeviceFamily_constructPath(inc/hw_ints.h)

const BatMonSupportLPF3_Config BatMonSupportLPF3_config = {
    .intNum = INT_CPUIRQ0,
    .intPriority = (~0),
    .intMux = EVTSVT_CPUIRQ0SEL_PUBID_AON_PMU_COMB
};
