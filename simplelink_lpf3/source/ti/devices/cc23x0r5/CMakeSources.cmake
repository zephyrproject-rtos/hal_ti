set(SOURCES_DRIVERLIB
    adc.c
    evtsvt.c
    aes_gcc.s
    chipinfo.c
    cpu.c
    gpio.c
    i2c.c
    interrupt.c
    lrfd.c
    setup.c
    spi.c
    systimer.c
    uart.c
    udma.c
    ioc.c
)

list(TRANSFORM SOURCES_DRIVERLIB PREPEND driverlib/)

set(SOURCES_RF_PATCHES
    lrf_mce_binary_ble_cs_cc23x0r5.c
    lrf_mce_binary_ble5_cc23x0r5.c
    lrf_mce_binary_common_cc23x0r5.c
    lrf_mce_binary_genfsk_cc23x0r5.c
    lrf_mce_binary_ieee_cc23x0r5.c
    lrf_pbe_binary_ble_cs_cc23x0r5.c
    lrf_pbe_binary_ble5_cc23x0r5.c
    lrf_pbe_binary_common_cc23x0r5.c
    lrf_pbe_binary_generic_cc23x0r5.c
    lrf_pbe_binary_ieee_cc23x0r5.c
    lrf_rfe_binary_ble_cs_cc23x0r5.c
    lrf_rfe_binary_ble_cs_nopll_cc23x0r5.c
    lrf_rfe_binary_ble5_cc23x0r5.c
    lrf_rfe_binary_ble5_nopll_cc23x0r5.c
    lrf_rfe_binary_coherent_pll_cc23x0r5.c
    lrf_rfe_binary_coherent_pll_nopll_cc23x0r5.c
    lrf_rfe_binary_common_cc23x0r5.c
    lrf_rfe_binary_common_nopll_cc23x0r5.c
    lrf_rfe_binary_genfsk_cc23x0r5.c
    lrf_rfe_binary_genfsk_nopll_cc23x0r5.c
    lrf_rfe_binary_ieee_cc23x0r5.c
    lrf_rfe_binary_ieee_nopll_cc23x0r5.c
)

list(TRANSFORM SOURCES_RF_PATCHES PREPEND rf_patches/)
