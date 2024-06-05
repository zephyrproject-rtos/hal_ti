
#include <ti/drivers/rcl/LRF.h>
#include <ti/devices/DeviceFamily.h>
#include DeviceFamily_constructPath(inc/hw_lrfddbell.h)
#include DeviceFamily_constructPath(inc/hw_lrfdtrc.h)

#include DeviceFamily_constructPath(inc/hw_types.h)
#include DeviceFamily_constructPath(inc/hw_memmap.h)
#include DeviceFamily_constructPath(inc/hw_clkctl.h)
#include DeviceFamily_constructPath(inc/hw_ioc.h)

#include <ti/drivers/Power.h>
#include <ti/drivers/rcl/RCL_Tracer.h>
#ifndef RCL_LITE_ONLY
#include <ti/drivers/rcl/RCL.h>
#endif

static bool tracerEnabled = false;

void RCL_Tracer_enable(void)
{
    /* TODO: As part of RCL-96, this should be changed so that enabling the clock is not part of
     * the tracer wakeup routine, only the first enabling. That avoids the need for this global variable */
    if (!tracerEnabled)
    {
        tracerEnabled = true;

        /* Enable tracer clock */
        Power_setDependency(PowerLPF3_PERIPH_LRFD_TRC);

#ifndef RCL_LITE_ONLY
        /* Request power notification to keep tracer up after standby */
        RCL_openPowerNotifications();
#endif

        /* Do the same enabling as after wakeup */
        RCL_Tracer_wakeup();
    }
}

void RCL_Tracer_disable(void)
{
    if (tracerEnabled)
    {
        /* Disable tracer pins as when going to standby */
        RCL_Tracer_standby();

#ifndef RCL_LITE_ONLY
        /* Remove power notifications */
        RCL_closePowerNotifications();
#endif

        /* Disable the tracer */
        HWREG_WRITE_LRF(LRFDTRC_BASE + LRFDTRC_O_CFG) = (LRFDTRC_CFG_CH1EN_OFF) |
                                                        (LRFDTRC_CFG_CH2EN_OFF) |
                                                        (LRFDTRC_CFG_CH3EN_OFF) |
                                                        (LRFDTRC_CFG_TSEN_OFF);

        /* Disable tracer clock */
        Power_releaseDependency(PowerLPF3_PERIPH_LRFD_TRC);

        tracerEnabled = false;
    }
}

void RCL_Tracer_wakeup(void)
{
    if (tracerEnabled)
    {
        /* Enable the Tracer */
        HWREG_WRITE_LRF(LRFDTRC_BASE + LRFDTRC_O_CFG) = LRFDTRC_CFG_CH1EN_NORM |
                                                        LRFDTRC_CFG_CH2EN_TOPSM |
                                                        LRFDTRC_CFG_CH3EN_TOPSM |
                                                        LRFDTRC_CFG_TSEN_M |
                                                        LRFDTRC_CFG_PRESCAL_DIV1;

#ifdef DeviceFamily_CC23X0R2
        /* Set tracer on GPO6 */
        HWREG_WRITE_LRF(LRFDDBELL_BASE + LRFDDBELL_O_GPOSEL0) = HWREG_READ_LRF(LRFDDBELL_BASE + LRFDDBELL_O_GPOSEL0) | (LRFDDBELL_GPOSEL0_SRC2_RFCTRC);
        HWREG(IOC_BASE + IOC_O_IOC6) = IOC_IOC6_PORTCFG_PFUNC4; // LRFD2 [trace]
#elif defined(DeviceFamily_CC23X0R5) || defined(DeviceFamily_CC23X0R22) || defined(DeviceFamily_CC2340R53)
        /* Set tracer on GPO5 */
        HWREG_WRITE_LRF(LRFDDBELL_BASE + LRFDDBELL_O_GPOSEL1) = HWREG_READ_LRF(LRFDDBELL_BASE + LRFDDBELL_O_GPOSEL1) | (LRFDDBELL_GPOSEL1_SRC6_RFCTRC);
        HWREG(IOC_BASE + IOC_O_IOC5) = IOC_IOC5_PORTCFG_PFUNC3; // LRFD6 [trace]
#elif defined (DeviceFamily_CC27XX)
        /* Set tracer on GPO20 */
        HWREG_WRITE_LRF(LRFDDBELL_BASE + LRFDDBELL_O_GPOSEL0) = HWREG_READ_LRF(LRFDDBELL_BASE + LRFDDBELL_O_GPOSEL0) | (LRFDDBELL_GPOSEL0_SRC3_RFCTRC);
        HWREG(IOC_BASE + IOC_O_IOC20) = IOC_IOC20_PORTCFG_PFUNC5; // LRFD3 [trace]
#endif
    }
}

void RCL_Tracer_standby(void)
{
    if (tracerEnabled)
    {
#ifdef DeviceFamily_CC23X0R2
        HWREG(IOC_BASE + IOC_O_IOC6) = 0;
#elif defined(DeviceFamily_CC23X0R5) || defined(DeviceFamily_CC23X0R22) || defined(DeviceFamily_CC2340R53)
        HWREG(IOC_BASE + IOC_O_IOC5) = 0;
#elif defined (DeviceFamily_CC27XX)
        HWREG(IOC_BASE + IOC_O_IOC20) = 0;
#endif
    }
    /* Do not disable tracer module here, as it can give a lockup if tracing was ongoing and another trace is started */
}
