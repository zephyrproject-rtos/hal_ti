+======================================================================+
| Copyright (c) 2014-2023 by Rambus, Inc. and/or its subsidiaries.     |
|                                                                      |
| Subject   : README for the Demo Application for special operations   |
|             provided by the VAL API                                  |
| Product   : EIP-130 Driver Development Kit                           |
| Date      : 2023-Mar-10                                              |
|                                                                      |
+======================================================================+

ATTENTION: This program can altered the OTP, which can make the SOC
           unusable for future use. So please use this program wisely.

ATTENTION: This program has multiple "IntegrationItem" points, which are
           related to the TRNG configuration that needs to be adapted to
           meet the customer specific FROs timing/behavior.

This is the readme file for building the Demo Application for special
operations that are provided by the VAL API and must be used in combination
with the EIP-130 driver. The Demo Application shows the usage of the
VAL API for these special operations, which can make the hardware unusable
for normal use.

The Demo Application is built for user mode deployment only.

The usage of the Demo Application can be retrieved when the program is
executed with the command line argument '-help'. Based on the given
arguments, the Demo Application can perform the following actions/tests:

- Reset firmware (hardware).
- Configure and start the TRNG (based on AES-DRBG).
- Configure and start the ARIA-DRBG.
- Configure the AES-DRBG with a force seed (note disables FRO's use)
- Read TRNG raw data
- Initialization of the OTP with a default COID and HUK.
- Initialization of the OTP with a default COID and a generated random HUK.
  The generation can be based on AES-DRBG or ARIA-DRBG.
- Create a 32-bit monotonic counter in OTP.
- Increment a monotonic counter, which is located in OTP.
- Validate Asset key blob generation when the KEK derivation is based on
  a monotonic counter.
- Zeroize/Destroy the OTP.
- Write a default Milenage K and OPc values to OTP.
- Check Milenage AUTN verification related functionality.
- Check Milenage AUTS generation related functionality.
- Set hardware in Sleep mode.
- Resume hardware from Sleep mode.
- Read the HW registers for Module Status, HW options and HW version.
- Read internal registers
- Read system information
- Perform self-test
- Reset/Clear dynamic Asset Store

Note that the provided Demo Application functionality can vary based on the
provided HW/FW configuration at compile time. Calling the Demo Application
with the -help argument will display the actual available functionality.


Build Instructions:
--------------------

 - Ensure that the ARCH, KERNEL_DIR and optionally CROSS_COMPILE environment
   variables are set as described in Examples/DemoApp_VAL_Specials/build/Makefile

 - Build the required libraries on which the application variants that are
   built depend.

 - Go to the DemoApp_VAL_Specials build directory
   # cd Examples/DemoApp_VAL_Specials/build

 - Build the da_val_specials user mode application.
   # make

   This will build da_val_specials_up, da_val_specials_combined_u and
   da_val_specials_combined_up.


Usage Instructions:
-------------------

  - Make sure the Global Control and VAL driver are loaded, and the /dev/vexp_c
    device node created. Then run the program da_val_specials_up. Use the
    following command sequence example to run the program:

    # insmod driver_gc_k.ko
    # insmod driver_val_k.ko
    # major_nr=`awk "\\$2==\"vexp_c\" {print \\$1}" /proc/devices`
    # mknod /dev/vexp_c c ${major_nr} 0
    # ./da_val_specials_up [<arguments> ...]
    # rmmod driver_val_k
    # rmmod driver_gc_k
    # rm /dev/vexp_c

  - Make sure the UMPCI driver is loaded, and the /dev/umpci_c device node
    created. Then run the program da_val_specials_combined_u. Use the
    following command sequence example to run the program:

    # insmod umpci_k.ko
    # major_nr=`awk "\\$2==\"umcpi_c\" {print \\$1}" /proc/devices`
    # mknod /dev/umcpi_c c ${major_nr} 0
    # ./da_val_specials_combined_u [<arguments> ...]
    # rmmod umpci_k
    # rm /dev/umcpi_c


<end-of-document>

