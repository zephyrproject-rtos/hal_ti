+======================================================================+
| Copyright (c) 2014-2023 by Rambus, Inc. and/or its subsidiaries.     |
|                                                                      |
| Subject   : README for the Demo Application for VAL API use          |
| Product   : EIP-130 Driver Development Kit                           |
| Date      : 2023-Mar-10                                              |
|                                                                      |
+======================================================================+

ATTENTION: This program can alter the OTP, which can make the SOC unusable
           for future use. So please use this program wisely.

This is the readme file for building the Demo Application for OTP
programming using the VAL API in combination with the EIP-130 driver.
It shows the usage of the VAL API. It is only built for user mode deployment
(the demo application will run as a user mode program and it is linked with
the user mode driver).

The Demo Application is intended as an example how to program an OTP item.
The usage of the Demo Application can be retrieved when the program is
executed with the command line argument '-help'.


Build Instructions:
--------------------

 - Ensure that the ARCH, KERNEL_DIR and optionally CROSS_COMPILE environment
   variables are set as described in Examples/DemoApp_OTPProgram/build/Makefile

 - Build the required libraries on which the application variants that are
   built depend.

 - Go to the DemoApp_OTPProgram build directory
   # cd Examples/DemoApp_OTPProgram/build

 - Build the da_otpprogram module and user mode application.
   # make

   This will build da_otpprogram_up, da_otpprogram_combined_u and
   da_otpprogram_combined_up.


Usage Instructions:
-------------------

  - Make sure the Driver(s) and DemoApp OTP Program modules are built.

  - Make sure the Global Control and VAL driver are loaded, and the
    /dev/vexp_c device node created. Then run the program da_otpprogram.
    This should produce the same output.

    # insmod driver_gc_k.ko
    # insmod driver_val_k.ko
    # major_nr=`awk "\\$2==\"vexp_c\" {print \\$1}" /proc/devices`
    # mknod /dev/vexp_c c ${major_nr} 0
    # ./da_otpprogram_up
    # rmmod driver_val_k
    # rmmod driver_gc_k
    # rm /dev/vexp_c

  - Make sure the UMPCI driver is loaded, and the /dev/umpci_c device node
    created. Then run the program da_otpprogram_combined_u. This should
    produce the same output.

    # insmod umpci_k.ko
    # major_nr=`awk "\\$2==\"umcpi_c\" {print \\$1}" /proc/devices`
    # mknod /dev/umcpi_c c ${major_nr} 0
    # ./da_otpprogram_combined_u
    # rmmod umpci_k
    # rm /dev/umcpi_c


<end-of-document>

