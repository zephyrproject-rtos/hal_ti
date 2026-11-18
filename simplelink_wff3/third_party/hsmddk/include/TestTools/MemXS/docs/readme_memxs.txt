+======================================================================+
| Copyright (c) 2014-2023 by Rambus, Inc. and/or its subsidiaries.     |
|                                                                      |
| Subject   : README for MemXS                                         |
| Product   : Security-IP User Mode Device Access                      |
| Date      : 2023-Mar-10                                              |
|                                                                      |
+======================================================================+

Introduction
------------

This is the readme file for building the user-space test application for
the MemXS module. This application can be used to read and write data at
the specified memory addresses for the devices supported by the EIP-130
example driver. This application can be used to verify that these devices
are accessible before using the EIP-130 example driver.

This application can also be used as an example for how to use the Driver
Framework Device API to access a device registers. For details about this
API refer to the Security-IP Driver Framework Porting Guide document.


Build Instructions
--------------------

  - Build the test application

    $ cd $TOP_DIR/MemXS/build
    $ make

    This will build the memxs executable.

    Note: The MemXS module depends on the Driver Framework user-space library
          libdf_u.a which can be found either in the corresponding to the
          required Cn configuration Regress_vip/Builds/Cn directory or in the
          local example driver build directory Driver/build

    Note: The MemXS_Init() function looks up devices whose registers can be
          read and written, e.g. the PCI Configuration Space (PCI_CONFIG_SPACE)
          or the EIP-130 hardware. These devices must be configured by exactly
          the same names in the Driver Framework user-space library, see its
          configuration file cs_hwpal.h in the local example driver build
          directory Driver/build


Usage Instructions:
-------------------

  - Make sure that the kernel umpci_k (or umdevxs) driver is loaded. This
    driver can be found either in the corresponding to the required Cn
    configuration Regress_vip/Builds/Cn directory or in the local build
    directory Integration/Linux_UMDevXS/UMPCI_Driver/build.

    For running test application:

    ./memxs -a [EIP*|PCI_CONFIG_SPACE] [-r|-w] REGISTER_ADDRESS DATA

    or

    ./memxs -i [FILE]

    Either -i must be used or complete command must be provided at the command
    line. Details of the configuration file format are present in the example
    file config.

    Examples:
    # Write: ./memxs -a [EIP*|PCI_CONFIG_SPACE] -w REGISTER_ADDRESS DATA.
    # Read:  ./memxs -a [EIP*|PCI_CONFIG_SPACE] -r REGISTER_ADDRESS.
    # Use configuration file: ./memxs -i config

ARGUMENTS:

    -i FILE:                         Read command from the configuration file.
    -a [EIP*|PCI_CONFIG_SPACE|BOARD_CTRL]:  PCI device or PCI Configuration Space
    -w REGISTER_ADDRESS DATA:        Write data on the register address.
    -r REGISTER_ADDRESS:             Read value from the register address.

EXAMPLE 1:

    This example shows how to read one word from the PCI Configuration Space
    of the Xilinx FPGA PCIe board programmed with EIP-130 hardware.

    [root@GW1 Regress_vip]# Builds/memxs -a PCI_CONFIG_SPACE -r 0x0
    >> 0x0
    MemXS_Init: MemXS successfully initialized
    MemXS_Read32: dev nr = 0, dev name = PCI_CONFIG_SPACE
    Value read from offset 0x0 is 0x601810ee
    MemXS_Uninit: MemXS uninitialized


Package Contents
----------------

This package contains the following components:

`-- MemXS/
    |-- build
    |   |-- config
    |   |-- cs_memxs.h
    |   `-- Makefile
    |-- docs
    |   `-- readme_memxs.txt
    `-- src
        |-- c_memxs.h
        `-- memxs_testapp.c

------------------------------------------------------------------------

<end-of-document>

