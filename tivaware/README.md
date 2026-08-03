# TI Tiva C Series HAL for Zephyr RTOS

This directory contains the Hardware Abstraction Layer (HAL) files extracted
from TI TivaWare C Series v2.2.0.295 for use as a Zephyr RTOS module.

## Directory Structure

```
tivaware/
├── CMakeLists.txt          # Zephyr build integration
├── README.md               # This file
├── zephyr/
│   └── module.yml          # Zephyr module descriptor
├── inc/                    # Hardware register definitions
│   ├── hw_memmap.h         #   Memory map (peripheral base addresses)
│   ├── hw_types.h          #   Common type macros (HWREG, etc.)
│   ├── hw_ints.h           #   Interrupt number definitions
│   ├── hw_gpio.h           #   GPIO register offsets/fields
│   ├── hw_uart.h           #   UART register offsets/fields
│   ├── hw_*.h              #   ... (all peripheral register definitions)
│   ├── asmdefs.h           #   Assembly helper macros
│   ├── tm4c123gh6pm.h      #   Device-specific header (TM4C123G LaunchPad)
│   ├── tm4c1294ncpdt.h     #   Device-specific header (TM4C1294 Connected LaunchPad)
│   └── tm4c*.h / sc4c*.h   #   ... (all supported part numbers)
└── driverlib/              # Peripheral driver library
    ├── sysctl.c / .h       #   System control (clocking, reset, peripherals)
    ├── gpio.c / .h         #   GPIO configuration and control
    ├── uart.c / .h         #   UART peripheral driver
    ├── interrupt.c / .h    #   NVIC interrupt controller
    ├── rom.h               #   ROM API function pointers
    ├── rom_map.h           #   ROM/Flash API redirection macros
    ├── pin_map.h           #   Pin mux configuration defines
    ├── debug.h             #   ASSERT macro for debug builds
    ├── rtos_bindings.h     #   RTOS integration hooks
    └── *.c / *.h           #   ... (all peripheral drivers)
```

## Source

Extracted from: **TivaWare C Series v2.2.0.295**
License: BSD-3-Clause (see LICENSE)

## Updating the DriverLib

The TivaWare SDK provides the peripheral driver library (driverlib) and device
hardware register access header files for the Texas Instruments Tiva C Series
(TM4C) SoCs.

The current version supported in Zephyr is the TivaWare C Series 2.2.0.295
downloaded from:

  https://www.ti.com/tool/SW-TM4C

The driver library source is copied from the SDK, as follows:

```
  # Install/extract the SW-TM4C-2.2.0.295 package, then:
  cd ~/SW-TM4C-2.2.0.295
  find . -mindepth 1 -maxdepth 1 ! -name driverlib ! -name inc -exec rm -r "{}" \;
  find driverlib -type f ! -name '*.c' ! -name '*.h' ! -name '*.s' -delete
  find inc -type f ! -name '*.h' -delete
  cp -r driverlib inc modules/hal/ti/tivaware/
```

New driver sources must be added to CMakeLists.txt with a matching
`zephyr_library_sources_ifdef(CONFIG_USE_TIVAWARE_<X> driverlib/<x>.c)` line, and
the Kconfig `HAS_TIVAWARE / USE__*` symbols in the Zephyr tree kept in sync.
