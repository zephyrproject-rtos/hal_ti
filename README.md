<div align="center">

<picture>
  <source media="(prefers-color-scheme: dark)" srcset="https://www.ti.com/content/dam/ticom/images/identities/ti-brand/ti-logo-hz-1c-white.svg" width="300">
  <img alt="Texas Instruments Logo" src="https://www.ti.com/content/dam/ticom/images/identities/ti-brand/ti-hz-2c-pos-rgb.svg" width="300">
</picture>

<div align="left">

# ASM Downstream Support For Zephyr 
This repository contains early Zephyr Support for ASM-class devices

The Texas Instruments Zephyr GitHub repository is the starting point for Zephyr
development on supported Texas Instruments devices. TI's Zephyr solution is
based on the Zephyr project and utilizes the same familiar environment, tools,
and dependencies.

## What is Zephyr?

The Zephyr Project is a scalable real-time operating system (RTOS) supporting
multiple hardware architectures, optimized for resource constrained devices,
and built with security in mind.

The Zephyr OS is based on a small-footprint kernel designed for use on
resource-constrained systems: from simple embedded environmental sensors and
LED wearables to sophisticated smart watches and IoT wireless gateways.

This downstream repository of TI Zephyr is based on the current upstream and 
advance features concerning specific MSP MCUs.

This release contains
support for the `AM261x` devices.

### Devices

Supported:

- [AM261x](https://www.ti.com/product/AM2612)

### Boards

Supported:

- [AM261x_LP](https://www.ti.com/tool/LP-AM261)

## Getting Started

For getting started, please refer to the [Zephyr Getting Started Guide](https://docs.zephyrproject.org/latest/develop/getting_started/index.html)

> **_NOTE:_** When running `west init` in the getting-started guide it's
> important to instead run `west init -m https://github.com/TexasInstruments/zephyr zephyrproject`
> in order to use the TI Zephyr repository.
> The `{tag-name}` changes with each release from TI.
>
> You can look up the latest tag from the following link:
> https://github.com/TexasInstruments/zephyr/tags

## Tools support

Currently the XDS110 debugger supplied with TI Launchpads is not natively
supported in the `west` Zephyr tool using OpenOCD. Note that it is also possible
to build an application in Zephyr, flash using `west`, and use 
[Code Composer Studio](https://www.ti.com/tool/CCSTUDIO) to debug the 
application using the XDS110 debugger. More details can be found here [AM261x Board Overview](https://github.com/TexasInstruments/zephyr/blob/am261x/release/boards/ti/am261x_lp/doc/index.rst)

## Versioning

TI will tag each release with the following format: {upstream-tag}-ti-M.mm.pp(\_optional-qualifier)

This tag can be broken down into 4 components:

- upstream-tag: This is the tag or commit of the [Zephyr](https://github.com/zephyrproject-rtos/zephyr)
  repo that the TI release is based on
- -ti-: Separator
- TI release version: This is TI's version on top of the upstream Zephyr
  version. The version scheme is explained below.
- Qualifier. The qualifier keyword is described below.

### TI Versioning Scheme

The TI version follows a version format, M.mm.pp, where:

- M is a 1 digit major number,
- mm is a 2 digit minor number,
- pp is a 2 digit patch number.

M.mm will follow TI's MCU PLUS SDK version and is an indicator that the TI
added content is based on the MCU PLUS SDK SDK with matching M.mm.

### Disclaimer

This release is provided as-is and should be considered Beta quality. This
product is meant for demonstration purposes only. Please refer to the Release Notes for
details on specific limitations and known issues.

## Need help?

- For technical support with TI Zephyr, including bugs and feature requests -
  submit a ticket to [TI's E2E forum](https://e2e.ti.com/support/microcontrollers/arm-based-microcontrollers-group/arm-based-microcontrollers/f/arm-based-microcontrollers-forum/)
  > **_NOTE:_** Please do not use the Github issue tracker for this project.

Additionally, we welcome any feedback that you can give to improve the
documentation!
