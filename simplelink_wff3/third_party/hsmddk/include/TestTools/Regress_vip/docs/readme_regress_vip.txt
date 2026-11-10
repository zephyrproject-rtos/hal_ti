+======================================================================+
| Copyright (c) 2014-2023 by Rambus, Inc. and/or its subsidiaries.     |
|                                                                      |
| Subject   : README for the Regression System                         |
| Product   : EIP-130 Driver Development Kit                           |
| Date      : 2023-Mar-10                                              |
|                                                                      |
+======================================================================+

This readme describes the EIP-130 DDK Regression System provided with
the EIP-130 Driver Development Kit.

The Regression Test system contains pre-defined configurations for
the examples, e.g. the Drivers, Demo Applications and VAL Test Tool.

The following scripts are available:

build_vip.sh        - builds the executables for one or all configurations.
regress_vip.sh      - executes the regression tests set for one configuration.
regress_all_vip.sh  - calls regress_vip.sh for each of the configurations.

The build_vip.sh script takes one argument.
This is the configuration number (like C0) or all to build all
the pre-defined configurations.

The build_vip.sh script captures the build output in a log file specific for
the active architecture (x86, arm, arm64 or mb) and configuration.
Log files are stored in the Logs sub-directory, for example
TestTools/Regress_vip/Logs/buildlog_C0_x86_driver.log.  Build output is stored
in the Builds sub-directory, for example TestTools/Regress_vip/Builds/C0/.

When using build_vip.sh all, the script builds the binaries for all
the pre-defined configurations and creates a file containing all these
binaries and scripts required to run the regression tests. This compressed file
(regressvip_$ARCH.tar.gz) is convenient for transferring to target system,
if this is different from the build system.

The regress_vip.sh script takes two arguments:
1) Configuration to run (for example C0)
2) Number of iterations (optional, default = 1) or "-i" for interactive runs

The regress_vip.sh script defines the subset of tests for each of the
configurations. Regress test output is captured in the Logs directory,
for example TestTools/Regress_vip/Logs/testlog_C0_x86.log. At the end
of a regression run the number of passed and failed tests are reported
(and added to the log) and the log is sanity-checked for typical error
reports. If such issues are detected, a warning message is printed and
a special log file is created, for example
TestTools/Regress_vip/Logs/testlog_C0_x86_issues.log.

On targets that do not support file systems, such as MicroBlaze on Xilinx Zynq
ZC706 FPGA, the regress_vip.sh script cannot be used. See below how to use
the regression system on targets without the file system support.

In order to get the test results matching those in the provided Test Report
refer to the Linux kernel configuration section.

Running regression tests on the build host
------------------------------------------

- Setup the environment variables for ARCH, HOST_HW_PLATFORM,
  and KERNEL_DIR, for example:

  # export ARCH=x86
  # export KERNEL_DIR=<your kernel source location>

  Specify the correct host hardware platform. This will typically be FPGA:

  # export HOST_HW_PLATFORM=FPGA_Virtex6_PCI

  Specify whether the host is a 64-bit platform (y or n):

  # export DDK_HOST64=y

  or

  # export DDK_HOST64=n

  Usually all these environment variables are set during the DDK
  installation. The install script creates the script setvars.sh,
  which can be sourced to set these variables again a later time.

  # source setvars.sh

- Change directory to the Regress_vip directory.
  # cd TestTools/Regress_vip

- Build the binaries and produce the tarball with the binaries,
  test vectors and scripts.
  # ./build_vip.sh all

- Run all regression tests via the regress_all_vip.sh script.
  # ./regress_all_vip.sh

- Inspect the regression test logs: Regress_vip/Logs/testlog*.log
  especially Regress_vip/Logs/testlog_summary_x86.log

- Run the regression tests for a single configuration (e.g. C0) using the
  regress_vip.sh script with the configuration name as parameter.
  # ./regress_vip.sh C0

Running regression tests on target using cross-compilation
----------------------------------------------------------

- Setup the environment variables for ARCH, HOST_HW_PLATFORM,
  KERNEL_DIR, CROSS_COMPILE and CROSS_LIB_PATH, for example:

  # export ARCH=arm64
  # export KERNEL_DIR=<your kernel source location>
  # export CROSS_COMPILE=aarch64-linux-gnu-
  # export CROSS_LIB_PATH=<your installation of linaro toolchain>/aarch64-linux-gnu/lib

  Specify the correct host hardware platform:

  # export HOST_HW_PLATFORM=FPGA_V2M_Juno

  Specify whether the host is a 64-bit platform (y or n):

  # export DDK_HOST64=y

  or

  # export DDK_HOST64=n

  Usually all these environment variables are set during the DDK
  installation. The install script creates the script setvars.sh,
  which can be sourced to set these variables again a later time.

  # source setvars.sh

- Change directory to the Regress_vip directory.
  # cd TestTools/Regress_vip

- Build the binaries and produce the tarball with the binaries,
  test vectors and scripts.
  # ./build_vip.sh all

- Transfer the regressvip_arm64.tar.gz file to
  the target system using target-specific method (not detailed here),
  for example scp or tftp.

- Unpack the tarball on target:
  # mkdir regress
  # cd regress
  # tar -zxf ../regressvip_arm64.tar.gz
  # cd TestTools/Regress_vip

- Make sure that the ARCH and HOST_HW_PLATFORM environment variables are set.
  # export ARCH=arm64
  # export HOST_HW_PLATFORM=FPGA_V2M_Juno

- Run all regression tests via the regress_all_vip.sh script.
  # ./regress_all_vip.sh

- Inspect the regression test logs: Regress_vip/Logs/testlog*.log
  especially Regress_vip/Logs/testlog_summary_arm64.log

- Run the regression tests for a single configuration (e.g. C0) using the
  regress_vip.sh script with the configuration name as parameter.
  # ./regress_vip.sh C0

Running regression tests on target without file system support
--------------------------------------------------------------

- Setup the environment variables for ARCH, HOST_HW_PLATFORM,
  XSDK_PATH, XBSP_PATH, CRREGRESS_LIB_PATH, REGRESS_LIB, CROSS_COMPILE and
  CROSS_LIB_PATH, for example:

  # export ARCH=mb
  # export XSDK_PATH=<your Xilinx SDK location>
  # export XBSP_PATH=<your MicroBlaze FreeRTOS BSP location>
  # export CROSS_COMPILE=mb-
  # export CROSS_LIB_PATH=<your MicroBlaze FreeRTOS BSP location>/lib
  # export REGRESS_LIB="-lda_val_combined_u -ltest_val_combined_u"
  # export REGRESS_LIB_PATH="-L$DDKDIR/Examples/DemoApp_VAL/build -L$DDKDIR/TestTools/TestTool_VAL/build"

  Specify the correct host hardware platform:

  # export HOST_HW_PLATFORM=FPGA_Zynq_ZC702

  Specify whether the host is a 64-bit platform (y or n):

  # export DDK_HOST64=n

  Usually all these environment variables are set during the DDK
  installation. The install script install_ddk.sh creates the script setvars.sh,
  which can be sourced to set these variables again a later time.

  # source setvars.sh

- Change directory to the Regress_vip directory.
  # cd TestTools/Regress_vip

- Build the binaries and produce the BOOT.bin file and regress.elf executable
  per configuration.
  # ./build_vip.sh all

- Connect USB UART cable to the USB port of the development PC where
  the terminal program will run and at the other end to the USB UART port of
  the Zynq ZC702 FPGA board, at 115200 bit rate.

- Optionally connect the USB JTAG cable to the the USB port of the development
  PC where the Xilinx SDK debugger will run and at the other end to the USB
  JTAG port of the Zynq ZC702 FPGA board.

- Copy the BOOT.bin file to the SD card and boot the Zynq ZC702 FPGA board
  with it. The BOOT.bin contains the FPGA bitstream, arm first stage bootloader
  and the MicroBlaze regression shell regerss.elf linked with the DDK demo
  application, test tool and EIP-130 driver built for a specific configuration.
  The FPGA bitstream and the first stage boot loader are located in the
  MicroBlaze Board Support Package (BSP) that can be obtained on request
  from RAMBUS or built spearately outside of the DDK using the Xilinx SDK.

- Capture and inspect the regression shell log in the terminal program.

- Alternatively to booting the FPGA board from the SD card the JTAG interface
  can be used to program the board with the FPGA bitstream and
  run the regress.elf for teh required configuration.

Special build and run options
-----------------------------

There are several environment variables that can be set to enable
special build and run options. These options have been used on the x86
platform only, but they may work on the arm and arm64 platforms too if the
required tools are installed on the target platform. Use of these
options requires that the related tools are installed on the host.
The build options DEBUG_DDK, COVER_DDK, PROFILE_DDK and CLANG_DDK must
be set before building the DDK. The VALGRIND_BIN option can be set
after building, but before running the regression script.

The following options exist:
- DEBUG_DDK. Set to 'y' in order to build the DDK and all applications with
  debugging support. The user mode applications can then be run under a
  debugger such as gdb,

  # export DEBUG_DDK=y

- COVER_DDK. Set to 'y' in order to build the DDK (user mode deployment) with
  coverage support. After running the user mode applications, object files
  of the driver can be analyzed with gcov.

  # export COVER_DDK=y

  The output directory can optionally be specified using the
  COVER_OUTPUT_DIR environment variable.

- PROFILE_DDK. Set to 'y' in order to build the DDK (user mode deployment) with
  profiling support. After running the user mode applications, these
  applications can be analyzed with gprof.

- CLANG_DDK. Set to 'y' in order to build with static code analysis using
  clang. The 'scan-build' program from LLVM/Clang must be in the path.

  The output directory can optionally be specified using the
  CLANG_OUTPUT_DIR environment variable.

- VALGRIND_BIN. Set to 'valgrind' in order to run the regression (user mode
  applications) under valgrind for dynamic code analysis.


Linux kernel configuration for successful driver regression
-----------------------------------------------------------

Refer to the provided example Linux kernel configuration files were used
to configure the Linux kernel for the driver verification

1) linux-x86-32-config: Kernel 2.6.29.4 non-debug configuration, 32-bit
2) linux-x86-64-config: Kernel 3.16.0 non-debug configuration, 64-bit
3) linux-arm64-config:  Kernel 3.10.63 non-debug configuration, 64-bit
3) linux-arm-config:    Kernel 4.6.0 non-debug configuration, 32-bit

These example Linux kernel configuration files can be found in the directory
TestTools/Regress_vip/docs.

The Linux kernel debug configuration can be used to verify the driver run-time
using the kernel built-in debug mechanisms. The non-debug kernel configuration
is recommended for the optimal driver performance.

Note: The Xilinx Virtex6 PCIe FPGA board used for driver verification has
      a PCIe interface and could only deliver interrupts via MSI. Therefore
      MSI (Message Signaled Interrupts) had to be supported by the kernel.
      The kernel configuration parameters CONFIG_ARCH_SUPPORTS_MSI and
      CONFIG_PCI_MSI must be configured.


<end-of-document>
