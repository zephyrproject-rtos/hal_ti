+======================================================================+
| Copyright (c) 2014-2023 by Rambus, Inc. and/or its subsidiaries.     |
|                                                                      |
| Subject   : README for the Demo Application for VAL API use          |
| Product   : EIP-130 Driver Development Kit                           |
| Date      : 2023-Mar-10                                              |
|                                                                      |
+======================================================================+

ATTENTION: This program can altered the OTP, which can make the SOC
           unusable for future use. So please use this program wisely.

ATTENTION: This program has an "IntegrationItem" point, which is related
           to the TRNG configuration that needs to be adapted to meet
           the customer specific FROs timing/behavior.

This is the readme file for building the Demo Application for the VAL API
use in combination with the EIP-130 driver. It shows the usage of the
VAL API. It is built both for kernel deployment (the demo application
will run as a Linux kernel module using the kernel mode driver) and for
user mode deployment (the demo application will run as a user mode program
and it is linked with the user mode or proxy driver).

Once started the Demo Application performs the following actions/tests:

1. To retrieve the hardware and firmware version.
2. To retrieve the state information.
3. To perform an OTP scan to check to availability of certain Static Assets.
4. To perform a NOP operation.

The purpose of the above-mentioned actions/tests is to validate the Mailbox
interface for the EIP-130 tokens and the DMA interface for reading and
writing data from EIP-130 point of view.

When the Demo Application is used in user mode, the application provides
additional functionality that can be selected via command line arguments.
Please use the argument '-help' to retrieve information about this additional
functionality.


Build Instructions:
--------------------

 - Ensure that the ARCH, KERNEL_DIR and optionally CROSS_COMPILE environment
   variables are set as described in Examples/DemoApp_VAL/build/Makefile

 - Build the Driver that the demo application depends on, otherwise
   the build cannot start. The demo application will use the Module.symver
   file from the Driver.

 - Go to the DemoApp_VAL build directory
   # cd Examples/DemoApp_VAL/build

 - Build the da_val module and user mode application.
   # make

   This will build da_val_k.ko, da_val_up, da_val_combined_u and
   da_val_combined_up.


Usage Instructions:
-------------------

  - Make sure the Driver(s) and DemoApp VAL modules are built.

  - Run the script
    # Examples/DemoApp_VAL/scripts/run_da_val.sh

    This runs the script in kernel mode. A successful run of the test
    should show "PASSED" in the output, both for the single packet test and
    for the multiple packet test (transport as well as tunnel).

  - Make sure the Global Control and VAL driver are loaded, and the
    /dev/vexp_c device node created. Then run the program da_val_up. This
    should produce the same output.

    # insmod driver_gc_k.ko
    # insmod driver_val_k.ko
    # major_nr=`awk "\\$2==\"vexp_c\" {print \\$1}" /proc/devices`
    # mknod /dev/vexp_c c ${major_nr} 0
    # ./da_val_up
    # rmmod driver_val_k
    # rmmod driver_gc_k
    # rm /dev/vexp_c

  - Make sure the UMPCI driver is loaded, and the /dev/umpci_c device node
    created. Then run the program da_val_combined_u. This should produce
    the same output.

    # insmod umpci_k.ko
    # major_nr=`awk "\\$2==\"umcpi_c\" {print \\$1}" /proc/devices`
    # mknod /dev/umcpi_c c ${major_nr} 0
    # ./da_val_combined_u
    # rmmod umpci_k
    # rm /dev/umcpi_c


<end-of-document>

