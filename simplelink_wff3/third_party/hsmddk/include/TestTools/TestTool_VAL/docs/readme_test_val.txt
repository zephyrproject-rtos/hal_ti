+======================================================================+
| Copyright (c) 2014-2023 by Rambus, Inc. and/or its subsidiaries.     |
|                                                                      |
| Subject   : README for the test Tool for the VAL API                 |
| Product   : EIP-130 Driver Development Kit                           |
| Date      : 2023-Mar-10                                              |
|                                                                      |
+======================================================================+

ATTENTION: This program can alter the OTP, which can make the SOC
           unusable for future use. So please use this program wisely.

ATTENTION: This program has multiple "IntegrationItem" points, which are
           related to the TRNG configuration that needs to be adapted to
           meet the customer specific FROs timing/behavior.

This is the readme file for building the Test Tool for validating the
of VAL API. The Test Tool tests all functions provided by the VAL API.
It is built both for kernel deployment (the Test Tool will run as a Linux
kernel module using the kernel mode driver) and for user mode deployment
(the Test Tool will run as a user mode program and it is linked with the
user mode driver or kernel mode driver depending on the deployment).

The Test Tool has all test vectors hardcoded in the C source files as
initialized structures. These files are located in the folder TestTools/
TestVectors and are compiled into the program. Test vectors typically
include the applicable key information, input and expected output.
Whenever the program is started, it runs all tests and it reports
whether each test passed or failed.

The Test Tool executes one Test Suite that has multiple Test Cases. Each
Test Cases will test a specific part of the VAL API and consists of one or
more Known Answer Tests (KAT). A test can be skipped based on the result
environment and hardware probing. For example, if the Test Tool is run in
non-secure environment certain operations not be executed (e.g. will
generate an error) like TRNG reseed.

When the Demo Application is used in user mode, the application provides
additional functionality that can be selected via command line arguments.
Please use the argument '-help' to retrieve information about this additional
functionality.


Build Instructions:
--------------------

 - Ensure that the ARCH, KERNEL_DIR and optionally CROSS_COMPILE environment
   variables are set as described in Examples/TestTool_VAL/build/Makefile

 - Build the Driver that the Test Tool depends on, otherwise
   the build cannot start. The Test Tool will use the Module.symver
   file from the Driver.

 - Go to the TestTool_VAL build directory
   # cd Examples/TestTool_VAL/build

 - Build the test_val module and user mode application.
   # make

   This will build test_val_k.ko, test_val[_combined]_up and test_val_combined_u.


Usage Instructions:
-------------------

  - Make sure the Driver and Test Tool are built.

  - Run the script
    # Examples/TestTool_VAL/scripts/run_val.sh

    This runs the script in kernel mode. A successful run of the test
    should show "PASSED" in the output for each test executed.

  - Make sure the UMDevXS or UMPCI driver is loaded, and the device node
    /dev/umdevxs_c or /dev/umpci_c is created (check the /proc/devices
    file for the major number, see the example below).
    Then run the program test_val_combined_u. A successful run of the test
    should show "PASSED" in the output for each test executed.

    # insmod umdevxs_k.ko
    # major_nr=`awk "\\$2==\"umdevxs_c\" {print \\$1}" /proc/devices`
    # mknod /dev/umdevxs_c c ${major_nr} 0
    # ./test_val_combined_u

    Or,

    # insmod umpci_k.ko
    # major_nr=`awk "\\$2==\"umcpi_c\" {print \\$1}" /proc/devices`
    # mknod /dev/umcpi_c c ${major_nr} 0
    # ./test_val_combined_u


<end-of-document>
