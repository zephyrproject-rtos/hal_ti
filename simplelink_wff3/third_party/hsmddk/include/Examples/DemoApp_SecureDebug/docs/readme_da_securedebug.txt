+======================================================================+
| Copyright (c) 2014-2023 by Rambus, Inc. and/or its subsidiaries.     |
|                                                                      |
| Subject   : README for the Demo Application for VAL API use          |
| Product   : EIP-130 Driver Development Kit                           |
| Date      : 2023-Mar-10                                              |
|                                                                      |
+======================================================================+

ATTENTION: This program has an "IntegrationItem" point, which is related
           to the TRNG configuration that needs to be adapted to meet
           the customer specific FROs timing/behavior.

This is the readme file for building the Demo Application for the
Authenticated Unlock and Secure Debug using the VAL API in combination
with the EIP-130 driver. It shows the usage of the VAL API. It is built
both for kernel deployment (the demo application will run as a Linux
kernel module using the kernel mode driver) and for user mode deployment
(the demo application will run as a user mode program and it is linked
with the user mode driver).

Once started the Demo Application enables and disables the Secure Debug
based on the default Authenticated keys. The Demo Application is intended
as an example how to use the Authenticated Unlock and Secure Debug
functionality.
Note that the Demo Application will switch between ECDSA-256 or ECDSA-521
scheme use based on the provide HW/FW configuration on compile time.

When the Demo Application is used in user mode, the application provides
additional functionality that can be selected via command line arguments.
Please use the argument '-help' to retrieve information about this additional
functionality.


Build Instructions:
--------------------

 - Ensure that the ARCH, KERNEL_DIR and optionally CROSS_COMPILE environment
   variables are set as described in Examples/DemoApp_SecureDebug/build/Makefile

 - Build the Driver that the demo application depends on, otherwise
   the build cannot start. The demo application will use the Module.symver
   file from the Driver.

 - Go to the DemoApp_SecureDebug build directory
   # cd Examples/DemoApp_SecureDebug/build

 - Build the da_securedebug module and user mode application.
   # make

   This will build da_securedebug_k.ko, da_securedebug_up,
   da_securedebug_combined_u and da_securedebug_combined_up.


Usage Instructions:
-------------------

  - Make sure the Driver(s) and DemoApp SecureDebug modules are built.

  - Run the script
    # Examples/DemoApp_VAL/scripts/run_da_securedebug.sh

    This runs the script in kernel mode. A successful run of the test
    should show "PASSED" in the output, both for the single packet test and
    for the multiple packet test (transport as well as tunnel).

  - Make sure the Global Control and VAL driver are loaded, and the
    /dev/vexp_c device node created. Then run the program da_securedebug.
    This should produce the same output.

    # insmod driver_gc_k.ko
    # insmod driver_val_k.ko
    # major_nr=`awk "\\$2==\"vexp_c\" {print \\$1}" /proc/devices`
    # mknod /dev/vexp_c c ${major_nr} 0
    # ./da_securedebug_up
    # rmmod driver_val_k
    # rmmod driver_gc_k
    # rm /dev/vexp_c

  - Make sure the UMPCI driver is loaded, and the /dev/umpci_c device node
    created. Then run the program da_securedebug_combined_u. This should
    produce the same output.

    # insmod umpci_k.ko
    # major_nr=`awk "\\$2==\"umcpi_c\" {print \\$1}" /proc/devices`
    # mknod /dev/umcpi_c c ${major_nr} 0
    # ./da_securedebug_combined_u
    # rmmod umpci_k
    # rm /dev/umcpi_c


<end-of-document>

