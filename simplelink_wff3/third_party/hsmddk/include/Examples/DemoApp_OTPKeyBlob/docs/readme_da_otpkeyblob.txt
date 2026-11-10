+======================================================================+
| Copyright (c) 2014-2023 by Rambus, Inc. and/or its subsidiaries.     |
|                                                                      |
| Subject   : README for the Demo Application for VAL API use          |
| Product   : EIP-130 Driver Development Kit                           |
| Date      : 2023-Mar-10                                              |
|                                                                      |
+======================================================================+

This is the readme file for building the Demo Application for the OTP
Key Blob generation using the VAL API in combination with the EIP-130
driver. It shows the usage of the VAL API. It is only built for user mode
deployment (the demo application will run as a user mode program and it
is linked with the user mode driver).

The Demo Application is intended as an example how to generate a key
blob that can be used for OTP programming. The usage of the Demo
Application can be retrieved when the program is executed with the command
line argument '-help'.


Build Instructions:
--------------------

 - Ensure that the ARCH, KERNEL_DIR and optionally CROSS_COMPILE environment
   variables are set as described in Examples/DemoApp_OTPKeyBlob/build/Makefile

 - Build the Driver that the demo application depends on, otherwise
   the build cannot start.

 - Go to the DemoApp_OTPKeyBlob build directory
   # cd Examples/DemoApp_OTPKeyBlob/build

 - Build the da_otpkeyblob module and user mode application.
   # make

   This will build da_otpkeyblob_up, da_otpkeyblob_combined_u and
   da_otpkeyblob_combined_up.


Usage Instructions:
-------------------

  - Make sure the Driver(s) and DemoApp OTP Key Blob modules are built.

  - Make sure the Global Control and VAL driver are loaded, and the
    /dev/vexp_c device node created. Then run the program da_otpkeyblob.
    This should produce the same output.

    # insmod driver_gc_k.ko
    # insmod driver_val_k.ko
    # major_nr=`awk "\\$2==\"vexp_c\" {print \\$1}" /proc/devices`
    # mknod /dev/vexp_c c ${major_nr} 0
    # ./da_otpkeyblob_up
    # rmmod driver_val_k
    # rmmod driver_gc_k
    # rm /dev/vexp_c

  - Make sure the UMPCI driver is loaded, and the /dev/umpci_c device node
    created. Then run the program da_otpkeyblob_combined_u. This should
    produce the same output.

    # insmod umpci_k.ko
    # major_nr=`awk "\\$2==\"umcpi_c\" {print \\$1}" /proc/devices`
    # mknod /dev/umcpi_c c ${major_nr} 0
    # ./da_otpkeyblob_combined_u
    # rmmod umpci_k
    # rm /dev/umcpi_c


<end-of-document>

