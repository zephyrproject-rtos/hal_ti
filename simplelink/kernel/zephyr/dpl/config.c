#include <stdbool.h>
#include <stdint.h>

#include <zephyr/kernel.h>

#include "stubs.h"

#if defined(CONFIG_HAS_CC13X2_CC26X2_SDK) || defined(CONFIG_HAS_CC13X2X7_CC26X2X7_SDK)
#include "ti/devices/cc13x2_cc26x2/driverlib/interrupt.h"
#include "ti/drivers/power/PowerCC26X2.h"
#endif /* CONFIG_HAS_CC13X2_CC26X2_SDK */

#include "ti/drivers/rf/RF.h"

#if (defined(CONFIG_HAS_CC13X2_CC26X2_SDK) || defined(CONFIG_HAS_CC13X2X7_CC26X2X7_SDK)) && !defined(CONFIG_CC13X2_CC26X2_HAS_CUSTOM_RF_HWATTRS)

const RFCC26XX_HWAttrsV2 RFCC26XX_hwAttrs = {
    .hwiPriority        = INT_PRI_LEVEL7,  // Lowest HWI priority:  INT_PRI_LEVEL7
                                           // Highest HWI priority: INT_PRI_LEVEL1

    .swiPriority        = 0,               // Lowest SWI priority:  0
                                           // Highest SWI priority: Swi.numPriorities - 1

    .xoscHfAlwaysNeeded = true             // Power driver always starts XOSC-HF:       true
                                           // RF driver will request XOSC-HF if needed: false
};

#endif /* defined(CONFIG_HAS_CC13X2_CC26X2_SDK) || defined(CONFIG_HAS_CC13X2X7_CC26X2X7_SDK) && !CONFIG_CC13X2_CC26X2_HAS_CUSTOM_RF_HWATTRS */
