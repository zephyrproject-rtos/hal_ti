#!/bin/bash
#
# Script for building binaries for a selected regression configuration
#

#------------------------------------------------------------------------------
#
#    Module        : DDK-130_bsd
#    Version       : 4.1.1
#    Configuration : DDK_EIP130_BSD
#
#    Date          : 2023-Mar-10
#
# Copyright (c) 2014-2023 by Rambus, Inc. and/or its subsidiaries.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are
# met:
#
# 1. Redistributions of source code must retain the above copyright
# notice, this list of conditions and the following disclaimer.
#
# 2. Redistributions in binary form must reproduce the above copyright
# notice, this list of conditions and the following disclaimer in the
# documentation and/or other materials provided with the distribution.
#
# 3. Neither the name of the copyright holder nor the names of its
# contributors may be used to endorse or promote products derived from
# this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
# A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
# HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
# SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
# LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#------------------------------------------------------------------------------

#-------------------------------------------------------------------------------
# check_file_exists
#
# Arguments:
#  1. path to file to check, may include whitespaces.
#
# This function checks if the given file exists. The function returns when
# the file exists. Otherwise a message is printed and the script is aborted
# with exit code 1.
#
check_file_exists()
{
  if [ ! -f "$1" ]
  then
      echo "Missing file $1"
      exit 1
  fi
}


#-------------------------------------------------------------------------------
# check_build_log
#
# Arguments:
#  1. Base path
#  2. Relative path to build log file
#
# This function checks the logfile for errors and reports these.
# When there are no errors, a check is made for warnings.
#
check_build_log()
{
    grep -w '\*\*\*\|error' $1/$2 | grep -v "Makefile:10: \*\*\* mixed implicit and normal rules: deprecated syntax" > /dev/null
    if [ $? -eq 0 ]
    then
        echo "Found ERRORS. Check $2 for details"
        return
    fi

    grep -i "warning" $1/$2 > /dev/null
    if [ $? -eq 0 ]
    then
        echo "Found warnings. Examine $2 for details"
        return
    fi
}


#-------------------------------------------------------------------------------
# check_copy
#
# Arguments:
#   1. path to file to check and copy
#   2. destination for copy
#
# This function checks if the given file exists. If it does not exist, a
# warning message is printed. Otherwise the file is copied to the destination
# folder.
#
check_copy()
{
    if [ ! -f "$1" ]
    then
        echo "Build FAILED! Missing file $1"
    else
        cp $1 $2
    fi
}


#-------------------------------------------------------------------------------
# make_build_temp
#
# Arguments:
#   None
#
# This function sets up a copy of the "build" sub-directory based on the
# name in $BUILD_WORK. The new directory is made the current directory.
#
make_build_temp()
{
    rm -rf $BUILD_WORK
    mkdir $BUILD_WORK
    cd $BUILD_WORK
    cp -r ../build/* .
    cp -f $BUILD_CONFIG_DIR/cs_*.h . 2>/dev/null
}


#-------------------------------------------------------------------------------
# remove_build_temp
#
# Arguments:
#   None
#
# This function removes the temporary "build" sub-directory created by
# make_build_temp().
#
remove_build_temp()
{
    if [ "$COVER_DDK" != 'y' ]
    then
        cd ..
        rm -rf $BUILD_WORK
    fi
}


#-------------------------------------------------------------------------------
# print_status
#
# Arguments:
#   1. Product
#   2. Configuration
#   3. Architecture
#
# This function prints the build progress.
#
print_status()
{
    echo "Building $2 for $3: $1"
}


#-------------------------------------------------------------------------------
# clang_out_set
#
# Arguments:
#   1. Name
#   2. Configuration
#
# This function makes a name for the clang output directory
# in the CLANG_OUT_ARG variable.
#
clang_out_set()
{
    if [ "$CLANG_OUT" != "" ]
    then
        if [ -z "$2" ]
        then
            mkdir -p $CLANG_OUT/$1
            CLANG_OUT_ARG="-o $CLANG_OUT/$1"
        else
            mkdir -p $CLANG_OUT/$2/$1
            CLANG_OUT_ARG="-o $CLANG_OUT/$2/$1"
        fi
    fi
}


#-------------------------------------------------------------------------------
# build_one
#
# Arguments:
#   None
#
build_one()
{
    BUILD_CONFIG_DIR=$BUILD_BASE/Configs/$BUILD_CONFIG
    BUILD_WORK=build_temp_$BUILD_CONFIG
    BUILD_LOG=Logs/buildlog_${BUILD_CONFIG}_$ARCH
    BUILD_OUTPUT=$BUILD_BASE/Builds/$BUILD_CONFIG

    if [ -d $BUILD_OUTPUT ]
    then
        rm -rf $BUILD_OUTPUT
    fi
    mkdir -p $BUILD_OUTPUT

    # Set system configuration to test
    export SYSTEMTEST_CONFIGURATION=`echo "-DSYSTEMTEST_CONFIGURATION=${BUILD_CONFIG//C}"`

    # Applications take the path to Module.symvers in this env var
    export PATH_DRIVER_VIP_SYMVERS=$BUILD_OUTPUT
    export PATH_DRIVER_VAL_SYMVERS=$BUILD_OUTPUT
    export PATH_DRIVER_PSA_SYMVERS=$BUILD_OUTPUT

    # build combined (VIP = GC + VAL + VEX) driver
    print_status "Driver (Combined VIP=GC+VAL)" $BUILD_CONFIG $ARCH
    cd $BUILD_BASE/../../Examples/Driver
    make_build_temp
    make clean > /dev/null
    clang_out_set driver $BUILD_CONFIG

    $CLANG_BIN $CLANG_OUT_ARG make $CLANG_ARG > $BUILD_BASE/${BUILD_LOG}_driver.log 2>&1

    check_build_log $BUILD_BASE ${BUILD_LOG}_driver.log
    check_copy libdriver_vip_u.a $BUILD_OUTPUT
    check_copy libdf.a $BUILD_OUTPUT
    if [ "$BUILD_LKM" = "y" ]
    then
        check_copy Module.symvers $BUILD_OUTPUT
        check_copy Module.symvers $BUILD_OUTPUT/driver_vip_k.symvers
        check_copy driver_vip_k.ko $BUILD_OUTPUT
    fi

    if [ "$ARCH" != "mb" ]
    then
        if [ "$COVER_DDK" != "y" ] || [ "$COVER_DDK" = "y" -a "$COVER_VEX_PROXY" = "y" ]
        then
            # build combined (VIP = GC + VAL) user-space driver with VEX proxy
            print_status "Driver user-space (Combined VIP=GC+VAL, VAL with VEX proxy)" $BUILD_CONFIG $ARCH
            cd $BUILD_BASE/../../Examples/Driver
            make_build_temp
            make clean > /dev/null
            clang_out_set driver $BUILD_CONFIG

            $CLANG_BIN $CLANG_OUT_ARG make $CLANG_ARG DDK_VEX_PROXY=y driver_vip_u >> $BUILD_BASE/${BUILD_LOG}_driver.log 2>&1

            check_build_log $BUILD_BASE ${BUILD_LOG}_driver.log
            check_copy libdriver_vip_up.a $BUILD_OUTPUT
            remove_build_temp
        fi

        # build VAL + VEX Driver
        print_status "Driver_VAL user-space" $BUILD_CONFIG $ARCH
        cd $BUILD_BASE/../../Examples/Driver_VAL
        make_build_temp
        make clean > /dev/null
        clang_out_set driver_val $BUILD_CONFIG

        $CLANG_BIN $CLANG_OUT_ARG make $CLANG_ARG > $BUILD_BASE/${BUILD_LOG}_driver_val.log 2>&1
        check_build_log $BUILD_BASE ${BUILD_LOG}_driver_val.log
        if [ "$BUILD_LKM" = "y" ]
        then
            check_copy Module.symvers $BUILD_OUTPUT
            check_copy Module.symvers $BUILD_OUTPUT/driver_val_k.symvers
            check_copy driver_val_k.ko $BUILD_OUTPUT
        fi

        if [ "$COVER_DDK" != "y" ] || [ "$COVER_DDK" = "y" -a "$COVER_VEX_PROXY" = "y" ]
        then
            # build VAL user-space driver with VEX proxy
            print_status "Driver_VAL user-space, VAL with VEX proxy" $BUILD_CONFIG $ARCH
            $CLANG_BIN $CLANG_OUT_ARG make $CLANG_ARG DDK_VEX_PROXY=y driver_val_up >> $BUILD_BASE/${BUILD_LOG}_driver_val.log 2>&1
            check_build_log $BUILD_BASE ${BUILD_LOG}_driver_val.log
            check_copy libdriver_val_up.a $BUILD_OUTPUT
            remove_build_temp
        fi

        # build PSA + VEX Driver
        print_status "Driver_PSA user-space" $BUILD_CONFIG $ARCH
        cd $BUILD_BASE/../../Examples/Driver_PSA
        make_build_temp
        make clean > /dev/null
        clang_out_set driver_psa $BUILD_CONFIG

        $CLANG_BIN $CLANG_OUT_ARG make $CLANG_ARG > $BUILD_BASE/${BUILD_LOG}_driver_psa.log 2>&1
        check_build_log $BUILD_BASE ${BUILD_LOG}_driver_psa.log
        if [ "$COVER_DDK" != "y" ] || [ "$COVER_DDK" = "y" -a "$COVER_VEX_PROXY" = "y" ]
        then
            # build PSA user-space driver with VEX proxy
            print_status "Driver_PSA user-space, PSA with VEX proxy" $BUILD_CONFIG $ARCH
            $CLANG_BIN $CLANG_OUT_ARG make $CLANG_ARG DDK_VEX_PROXY=y driver_psa_up >> $BUILD_BASE/${BUILD_LOG}_driver_psa.log 2>&1
            check_build_log $BUILD_BASE ${BUILD_LOG}_driver_psa.log
            check_copy libdriver_psa_up.a $BUILD_OUTPUT
            remove_build_temp
        fi

        # build GC Driver
        print_status "Driver_GC" $BUILD_CONFIG $ARCH
        cd $BUILD_BASE/../../Examples/Driver_GC
        make_build_temp
        make clean > /dev/null
        clang_out_set driver_gc $BUILD_CONFIG

        $CLANG_BIN $CLANG_OUT_ARG make $CLANG_ARG > $BUILD_BASE/${BUILD_LOG}_driver_gc.log 2>&1
        check_build_log $BUILD_BASE ${BUILD_LOG}_driver_gc.log

        if [ "$BUILD_LKM" = "y" ]
        then
            check_copy Module.symvers $BUILD_OUTPUT/driver_gc_k.symvers
            check_copy driver_gc_k.ko $BUILD_OUTPUT
        fi
        remove_build_temp
    fi

    if [ "$ARCH" = "mb" ]
    then
        APP_NAME_PREFIX=lib
        APP_NAME_POSTFIX=.a
        DA_OTPKEYBLOB_BUILD_RULES="asset keyblob da_otpkeyblob_u"
        DA_OTPPROGRAM_BUILD_RULES="keyblob da_otpprogram_u"
    else
        APP_NAME_PREFIX=
        APP_NAME_POSTFIX=
        DA_OTPKEYBLOB_BUILD_RULES=da_otpkeyblob_u
        DA_OTPPROGRAM_BUILD_RULES=da_otpprogram_u
    fi

    TEST_VAL_NAME=${APP_NAME_PREFIX}test_val_combined_u${APP_NAME_POSTFIX}
    TEST_PSA_NAME=${APP_NAME_PREFIX}test_psa_combined_u${APP_NAME_POSTFIX}
    DA_VAL_NAME=${APP_NAME_PREFIX}da_val_combined_u${APP_NAME_POSTFIX}
    DA_VAL_ASYM_NAME=${APP_NAME_PREFIX}da_val_asym_combined_u${APP_NAME_POSTFIX}
    DA_VAL_ENCRYPT_NAME=${APP_NAME_PREFIX}da_val_encrypt_combined_u${APP_NAME_POSTFIX}
    DA_VAL_HASH_NAME=${APP_NAME_PREFIX}da_val_hash_combined_u${APP_NAME_POSTFIX}
    DA_VAL_SPECIALS_NAME=${APP_NAME_PREFIX}da_val_specials_combined_u${APP_NAME_POSTFIX}
    DA_SECUREDEBUG_NAME=${APP_NAME_PREFIX}da_securedebug_combined_u${APP_NAME_POSTFIX}
    DA_OTPKEYBLOB_NAME=${APP_NAME_PREFIX}da_otpkeyblob_combined_u${APP_NAME_POSTFIX}
    DA_OTPPROGRAM_NAME=${APP_NAME_PREFIX}da_otpprogram_combined_u${APP_NAME_POSTFIX}

    # build MicroBlaze FreeRTOS custom standard C library
    if [ "$ARCH" = "mb" ]
    then
        print_status "Custom standard C library" $BUILD_CONFIG $ARCH
        cd $BUILD_BASE/../../TestTools/Regress_vip/mb_freertos
        make clean > /dev/null
        make mbfreertos > $BUILD_BASE/${BUILD_LOG}_mbfreertos.log 2>&1
        check_copy libmbfreertos.a $BUILD_OUTPUT
        check_build_log $BUILD_BASE ${BUILD_LOG}_mbfreertos.log
        make clean > /dev/null
        remove_build_temp
    fi

    # build VAL API test tool
    print_status "TestTool_VAL" $BUILD_CONFIG $ARCH
    cd $BUILD_BASE/../../TestTools/TestTool_VAL
    make_build_temp
    make clean > /dev/null
    clang_out_set test_val $BUILD_CONFIG
    if [ "$BUILD_LKM" = "y" ]
    then
        $CLANG_BIN $CLANG_OUT_ARG make $CLANG_ARG > $BUILD_BASE/${BUILD_LOG}_test_val.log 2>&1
        check_copy test_val_k.ko $BUILD_OUTPUT
    else
        $CLANG_BIN $CLANG_OUT_ARG make test_val_u $CLANG_ARG > $BUILD_BASE/${BUILD_LOG}_test_val.log 2>&1
    fi
    check_copy $TEST_VAL_NAME $BUILD_OUTPUT
    if [ -f test_val_combined_up ]
    then
        check_copy test_val_combined_up $BUILD_OUTPUT
    fi
    if [ -f test_val_up ]
    then
        check_copy test_val_up $BUILD_OUTPUT
    fi
    check_build_log $BUILD_BASE ${BUILD_LOG}_test_val.log
    remove_build_temp

    # build PSA API test tool
    print_status "TestTool_PSA" $BUILD_CONFIG $ARCH
    cd $BUILD_BASE/../../TestTools/TestTool_PSA
    make_build_temp
    make clean > /dev/null
    clang_out_set test_psa $BUILD_CONFIG
    if [ "$BUILD_LKM" = "y" ]
    then
        $CLANG_BIN $CLANG_OUT_ARG make $CLANG_ARG > $BUILD_BASE/${BUILD_LOG}_test_psa.log 2>&1
    else
        $CLANG_BIN $CLANG_OUT_ARG make test_psa_u $CLANG_ARG > $BUILD_BASE/${BUILD_LOG}_test_psa.log 2>&1
    fi
    check_copy $TEST_PSA_NAME $BUILD_OUTPUT
    if [ -f test_psa_combined_up ]
    then
        check_copy test_psa_combined_up $BUILD_OUTPUT
    fi
    if [ -f test_psa_up ]
    then
        check_copy test_psa_up $BUILD_OUTPUT
    fi
    check_build_log $BUILD_BASE ${BUILD_LOG}_test_psa.log
    remove_build_temp

    # build VAL API demo applications.
    print_status "DemoApp_VAL" $BUILD_CONFIG $ARCH
    cd $BUILD_BASE/../../Examples/DemoApp_VAL
    make_build_temp
    make clean > /dev/null
    clang_out_set da_val $BUILD_CONFIG
    if [ "$BUILD_LKM" = "y" ]
    then
        $CLANG_BIN $CLANG_OUT_ARG make $CLANG_ARG > $BUILD_BASE/${BUILD_LOG}_da_val.log 2>&1
        check_copy da_val_k.ko $BUILD_OUTPUT
    else
        $CLANG_BIN $CLANG_OUT_ARG make da_val_u $CLANG_ARG > $BUILD_BASE/${BUILD_LOG}_da_val.log 2>&1
    fi
    check_copy $DA_VAL_NAME $BUILD_OUTPUT
    if [ -f da_val_combined_up ]
    then
        check_copy da_val_combined_up $BUILD_OUTPUT
    fi
    if [ -f da_val_up ]
    then
        check_copy da_val_up $BUILD_OUTPUT
    fi
    check_build_log $BUILD_BASE ${BUILD_LOG}_da_val.log
    remove_build_temp

    print_status "DemoApp_VAL_Specials" $BUILD_CONFIG $ARCH
    cd $BUILD_BASE/../../Examples/DemoApp_VAL_Specials
    make_build_temp
    make clean > /dev/null
    clang_out_set da_val_specials $BUILD_CONFIG
    $CLANG_BIN $CLANG_OUT_ARG make da_val_specials_u $CLANG_ARG > $BUILD_BASE/${BUILD_LOG}_da_val_specials.log 2>&1
    check_copy $DA_VAL_SPECIALS_NAME $BUILD_OUTPUT
    if [ -f da_val_specials_combined_up ]
    then
        check_copy da_val_specials_combined_up $BUILD_OUTPUT
    fi
    if [ -f da_val_specials_up ]
    then
        check_copy da_val_specials_up $BUILD_OUTPUT
    fi
    check_build_log $BUILD_BASE ${BUILD_LOG}_da_val_specials.log
    remove_build_temp

    print_status "DemoApp_SecureDebug" $BUILD_CONFIG $ARCH
    cd $BUILD_BASE/../../Examples/DemoApp_SecureDebug
    make_build_temp
    make clean > /dev/null
    clang_out_set da_securedebug $BUILD_CONFIG
    if [ "$BUILD_LKM" = "y" ]
    then
        $CLANG_BIN $CLANG_OUT_ARG make $CLANG_ARG > $BUILD_BASE/${BUILD_LOG}_da_securedebug.log 2>&1
        check_copy da_securedebug_k.ko $BUILD_OUTPUT
    else
        $CLANG_BIN $CLANG_OUT_ARG make da_securedebug_u $CLANG_ARG > $BUILD_BASE/${BUILD_LOG}_da_securedebug.log 2>&1
    fi
    check_copy $DA_SECUREDEBUG_NAME $BUILD_OUTPUT
    if [ -f da_securedebug_combined_up ]
    then
        check_copy da_securedebug_combined_up $BUILD_OUTPUT
    fi
    if [ -f da_securedebug_up ]
    then
        check_copy da_securedebug_up $BUILD_OUTPUT
    fi
    check_build_log $BUILD_BASE ${BUILD_LOG}_da_securedebug.log
    remove_build_temp

    print_status "DemoApp_OTPKeyBlob" $BUILD_CONFIG $ARCH
    cd $BUILD_BASE/../../Examples/DemoApp_OTPKeyBlob
    make_build_temp
    make clean > /dev/null
    clang_out_set da_otpkeyblob $BUILD_CONFIG
    $CLANG_BIN $CLANG_OUT_ARG make $DA_OTPKEYBLOB_BUILD_RULES $CLANG_ARG > $BUILD_BASE/${BUILD_LOG}_da_otpkeyblob.log 2>&1
    check_copy $DA_OTPKEYBLOB_NAME $BUILD_OUTPUT
    if [ -f da_otpkeyblob_combined_up ]
    then
        check_copy da_otpkeyblob_combined_up $BUILD_OUTPUT
    fi
    if [ -f da_otpkeyblob_up ]
    then
        check_copy da_otpkeyblob_up $BUILD_OUTPUT
    fi
    check_build_log $BUILD_BASE ${BUILD_LOG}_da_otpkeyblob.log
    remove_build_temp

    print_status "DemoApp_OTPProgram" $BUILD_CONFIG $ARCH
    cd $BUILD_BASE/../../Examples/DemoApp_OTPProgram
    make_build_temp
    make clean > /dev/null
    clang_out_set da_otpprogram $BUILD_CONFIG
    $CLANG_BIN $CLANG_OUT_ARG make $DA_OTPPROGRAM_BUILD_RULES $CLANG_ARG > $BUILD_BASE/${BUILD_LOG}_da_otpprogram.log 2>&1
    check_copy $DA_OTPPROGRAM_NAME $BUILD_OUTPUT
    if [ -f da_otpprogram_combined_up ]
    then
        check_copy da_otpprogram_combined_up $BUILD_OUTPUT
    fi
    if [ -f da_otpprogram_up ]
    then
        check_copy da_otpprogram_up $BUILD_OUTPUT
    fi
    check_build_log $BUILD_BASE ${BUILD_LOG}_da_otpprogram.log
    remove_build_temp

    if [ "$ARCH" = "mb" ]
    then
        print_status "Regression shell for test and demo apps" $BUILD_CONFIG $ARCH
        cd $BUILD_BASE/../../TestTools/Regress_vip/mb_freertos
        make clean > /dev/null
        TEMP_LIB_PATH=$REGRESS_LIB_PATH
        export REGRESS_LIB_PATH="-L. -L$BUILD_OUTPUT"
        make regress boot > $BUILD_BASE/${BUILD_LOG}_regress.log 2>&1
        export REGRESS_LIB_PATH=$TEMP_LIB_PATH
        check_copy regress.elf $BUILD_OUTPUT
        check_copy BOOT.bin $BUILD_OUTPUT
        check_build_log $BUILD_BASE ${BUILD_LOG}_regress.log
        make clean > /dev/null
        rm -f $BUILD_OUTPUT/*.a
        remove_build_temp
        unset REGRESS_LIB_PATH
    fi

    #rm -f $BUILD_OUTPUT/*.symvers $BUILD_OUTPUT/*.a

    unset PATH_DRIVER_VIP_SYMVERS
    unset PATH_DRIVER_VAL_SYMVERS
    unset SYSTEMTEST_CONFIGURATION
}


#-------------------------------------------------------------------------------
# build_all
#
# Arguments:
#   None
#
build_all()
{
    # Cleanup/Initialize build environment
    if [ "$SYSTEMTEST_CONFIGURATION" != '' ]
    then
        unset SYSTEMTEST_CONFIGURATION
    fi

    BUILD_OUTPUT=$BUILD_BASE/Builds
    if [ -d $BUILD_OUTPUT ]
    then
        rm -rf $BUILD_OUTPUT
    fi
    mkdir -p $BUILD_OUTPUT

    # build UMDevXS
    if [ "$BUILD_LKM" = "y" ]
    then
        echo "Building for $ARCH: Driver_ks"
        cd ../../Examples/Driver_KernelSupport/UMDevXS/build
        make clean > /dev/null
        clang_out_set $KO_NAME_DRIVER
        $CLANG_BIN $CLANG_OUT_ARG make $CLANG_ARG > $BUILD_BASE/Logs/buildlog_${ARCH}_${KO_NAME_DRIVER}.log 2>&1
        check_build_log $BUILD_BASE Logs/buildlog_${ARCH}_${KO_NAME_DRIVER}.log
        check_copy ${KO_NAME_DRIVER}.ko $BUILD_OUTPUT
        cd $BUILD_BASE
    fi

    # build MemXS utility
    if [ "$ARCH" != "mb" ]
    then
        echo "Building for $ARCH: MemXS"
        cd ../../Examples/Driver/build
        make clean > /dev/null
        make > /dev/null
        cd ../../../TestTools/MemXS/build
        make clean > /dev/null
        export PATH_DF_LIB=$BUILD_BASE/../../Examples/Driver/build
        clang_out_set memxs
        $CLANG_BIN $CLANG_OUT_ARG make $CLANG_ARG > $BUILD_BASE/Logs/buildlog_${ARCH}_memxs.log 2>&1
        unset PATH_DF_LIB
        check_build_log $BUILD_BASE Logs/buildlog_${ARCH}_memxs.log
        check_copy memxs $BUILD_OUTPUT
        cd $BUILD_BASE
    fi

    # build all configurations
    if [ "X$BUILD_CONFIGS" = "X" ]
    then
        # Build all possible configurations
        BUILD_CONFIGS="C0 C1 C2 C3 C4 C5"
    fi

    for ConfigLp in $BUILD_CONFIGS;
    do
        # invoke self script
        ./build_vip.sh $ConfigLp
    done

    # create the tarball
    BUILD_TARNAME=regressvip_${ARCH}.tar.gz
    echo "Creating tarball $BUILD_TARNAME"
    rm -f $BUILD_TARNAME
    cd ../..
    rm -f $BUILD_TARNAME
    tar -zcf $BUILD_TARNAME TestTools/Regress_vip/Builds/* TestTools/Regress_vip/regress*.sh Examples/Driver/scripts/* Examples/Driver_VAL/scripts/* Examples/Driver_KernelSupport/UMDevXS/scripts/*.sh
    # Examples/Driver_PSA/scripts/*

    mv $BUILD_TARNAME TestTools/Regress_vip
    cd TestTools/Regress_vip
    ls -l $BUILD_TARNAME
}


# main script starts here

if [ -z $ARCH ]
then
    echo "Please set ARCH, KERNEL_DIR and optionally CROSS_COMPILE"
    exit 1
fi

if [ "$#" -ne 1 ]
then
   echo "Please provide ALL or one configuration: C0, C1, C2, ..."
   exit 1
fi

export HOST_HW_PLATFORM=FPGA_Zynq_ZC702

BUILD_BASE=`pwd`
BUILD_CONFIG=`echo $1 | tr [:lower:] [:upper:]`

CLANG_BIN=
CLANG_ARG=
CLANG_OUT=
CLANG_OUT_ARG=

if [ "$ARCH" = "mb" ]
then
    BUILD_LKM=
else
    BUILD_LKM=y
fi

BUILD_INTERRUPTS=y
BUILD_MULTIPLE=y
KO_NAME_DRIVER=umdevxs_k

# set clang tool parameters if configured
if [ "$CLANG_DDK" = 'y' ]
then
    CLANG_BIN=scan-build

    if [ -d "$CLANG_OUTPUT_DIR" ]
    then
        CLANG_OUT=$CLANG_OUTPUT_DIR/Clang
    else
        CLANG_OUT=$BUILD_BASE/Clang
    fi

    # remove previous data if any
    if [ $BUILD_CONFIG == "ALL" ]
    then
        rm -rf $CLANG_OUT
    fi
fi

mkdir -p Logs

if [ $BUILD_CONFIG == "ALL" ]
then
    # build all configurations
    build_all
else
    # build one specific configuration
    build_one
fi

# end of file
