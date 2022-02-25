#define DT_DRV_COMPAT	ti_cc31xx

#include <zephyr.h>
#include <kernel.h>
#include <device.h>
#include <errno.h>
#include <drivers/spi.h>
#include <drivers/gpio.h>
#include <logging/log.h>

#include <ti/drivers/net/wifi/simplelink.h>
#include <ti/drivers/net/wifi/porting/cc_pal.h>
#include <ti/drivers/net/wifi/source/driver.h>

LOG_MODULE_REGISTER(cc31xx_pal, CONFIG_LOG_DEFAULT_LEVEL);

struct cc31xx_gpio {
    const struct device *dev;
    unsigned int pin;
};

struct cc31xx_data {
    struct spi_dt_spec bus;
    struct gpio_callback irq_cb;
    struct cc31xx_gpio irq;
    struct cc31xx_gpio nhib;
    struct cc31xx_gpio cs;
};

static struct cc31xx_data cc31xx_data = {
    .bus = SPI_DT_SPEC_INST_GET(0,
				SPI_OP_MODE_MASTER | SPI_TRANSFER_MSB | 
		        SPI_WORD_SET(8), 0),
};

Fd_t spi_Open(char *ifName, unsigned long flags)
{
    return (Fd_t)(&cc31xx_data.bus);
}

int spi_Close(Fd_t fd)
{
    return 0;
}

int spi_Read(Fd_t fd, unsigned char *pBuff, int len)
{
	const struct cc31xx_data *spi = &cc31xx_data;
    char *data = pBuff;
	struct spi_buf spi_rx_buf[1];
	struct spi_buf_set spi_rx;
	int status;

	spi_rx_buf[0].buf = data;
	spi_rx_buf[0].len = len;
	spi_rx.buffers = spi_rx_buf;
	spi_rx.count = ARRAY_SIZE(spi_rx_buf);

    LOG_DBG("spi recv: %d bytes", len);

	status = spi_read_dt(&spi->bus, &spi_rx);
	if (status) {
		LOG_ERR("SPI read error %d", status);
        status = 0;
	} else {
		status = len;
	}

	return status;
}

int spi_Write(Fd_t fd, unsigned char *pBuff, int len)
{
	const struct cc31xx_data *spi = &cc31xx_data;
    char *data = pBuff;
	struct spi_buf spi_tx_buf[1];
	struct spi_buf_set spi_tx;
	int status;

	spi_tx_buf[0].buf = data;
	spi_tx_buf[0].len = len;
	spi_tx.buffers = spi_tx_buf;
	spi_tx.count = ARRAY_SIZE(spi_tx_buf);

    LOG_DBG("spi write: %d bytes", len);

	status = spi_write_dt(&spi->bus, &spi_tx);
	if (status) {
		LOG_ERR("SPI write error %d", status);
        status = 0;
	} else {
		status = len;
	}

    return status;
}

P_EVENT_HANDLER SlInterruptHandler;

int NwpRegisterInterruptHandler(P_EVENT_HANDLER InterruptHdl , void* pValue)
{
    if (InterruptHdl) {
        SlInterruptHandler = InterruptHdl;
    }

    if (!SlInterruptHandler) {
        return -1;
    } else {
        return OS_OK;
    }
}

static void irq_isr(const struct device *unused1,
		       struct gpio_callback *unused2,
		       uint32_t unused3)
{
    if (SlInterruptHandler) {
        SlInterruptHandler();
    }
}


/** @FIXME: Revisit needs for this implementation
*/
void NwpMaskInterrupt(void)
{
}

/** @FIXME: Revisit needs for this implementation
*/
void NwpUnMaskInterrupt(void)
{
}

void NwpPowerOff(void)
{
    gpio_pin_set(cc31xx_data.nhib.dev, cc31xx_data.nhib.pin, 1);
}

void NwpPowerOn(void)
{
    gpio_pin_set(cc31xx_data.nhib.dev, cc31xx_data.nhib.pin, 0);

}

#if defined(SL_PLATFORM_MULTI_THREADED)

int Semaphore_pend_handle(sem_t* pSemHandle,  uint32_t timeout)
{
    if (OS_WAIT_FOREVER == timeout)
    {
        return sem_wait(pSemHandle);
    }
    else
    {
        struct timespec abstime;
        abstime.tv_nsec = 0;
        abstime.tv_sec = 0;

        /* Since POSIX timeout are relative and not absolute,
         * take the current timestamp. */
        clock_gettime(CLOCK_REALTIME, &abstime);
        if(abstime.tv_nsec < 0)
        {
            abstime.tv_sec = timeout;
            return (sem_timedwait(pSemHandle, &abstime));
        }

        /* Add the amount of time to wait */
        abstime.tv_sec += timeout / 1000;
        abstime.tv_nsec += (timeout % 1000) * 1000000;

        abstime.tv_sec += (abstime.tv_nsec / 1000000000);
        abstime.tv_nsec = abstime.tv_nsec % 1000000000;

        /* Call the semaphore wait API */
        return(sem_timedwait(pSemHandle, &abstime));
    }
}

int Mutex_create_handle(pthread_mutex_t* pMutexHandle)
{
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);

    if (pthread_mutex_init(pMutexHandle, &attr) < 0)
    {
        return Mutex_FAILURE ;
    }

    return Mutex_OK;
}

#endif

unsigned long TimerGetCurrentTimestamp(void)
{
    return (ClockP_getSystemTicks());
}

/** @FIXME: According to device.c, this function is unique for the CC32XX family. */
void NwpWaitForShutDownInd()
{
}

/** 
 * @FIXME: This is a re-definition to match how is being initialized
 *          on simplelink_support.c */
void CC3220SF_LAUNCHXL_init(void)
{
    struct cc31xx_data *dev_data = &cc31xx_data;

	dev_data->irq.dev = device_get_binding(
			DT_INST_GPIO_LABEL(0, irq_gpios));
	if (!dev_data->irq.dev) {
		LOG_ERR("Failed to initialize GPIO driver: %s",
			    DT_INST_GPIO_LABEL(0, irq_gpios));
		return;
	}
	dev_data->irq.pin = DT_INST_GPIO_PIN(0, irq_gpios);
	gpio_pin_configure(dev_data->irq.dev, dev_data->irq.pin,
			   DT_INST_GPIO_FLAGS(0, irq_gpios) |
			   GPIO_INPUT);

	gpio_init_callback(&dev_data->irq_cb, irq_isr, BIT(dev_data->irq.pin));

	if (gpio_add_callback(dev_data->irq.dev, &dev_data->irq_cb)) {
        LOG_ERR("Failed to add int-cb");
		return;
	}

    gpio_pin_interrupt_configure(cc31xx_data.irq.dev, cc31xx_data.irq.pin,
					     GPIO_INT_EDGE_TO_ACTIVE);

	dev_data->nhib.dev = device_get_binding(
			DT_INST_GPIO_LABEL(0, nhib_gpios));
	if (!dev_data->nhib.dev) {
		LOG_ERR("Failed to initialize GPIO driver: %s",
			    DT_INST_GPIO_LABEL(0, nhib_gpios));
		return;
	}
	dev_data->nhib.pin = DT_INST_GPIO_PIN(0, nhib_gpios);
	gpio_pin_configure(dev_data->nhib.dev, dev_data->nhib.pin,
			   DT_INST_GPIO_FLAGS(0, nhib_gpios) |
			   GPIO_OUTPUT_INACTIVE | GPIO_ACTIVE_LOW);

    LOG_INF("Initialized successfully");
}

static int cc31xx_init(const struct device *dev)
{
    return 0;
}

DEVICE_DT_INST_DEFINE(0, &cc31xx_init, NULL, 
            &cc31xx_data, NULL, 
            POST_KERNEL, CONFIG_APPLICATION_INIT_PRIORITY,
            NULL);
