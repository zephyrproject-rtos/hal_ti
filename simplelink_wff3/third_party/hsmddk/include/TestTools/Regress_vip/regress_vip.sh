#!/bin/sh
#
# This script executes a set of test vectors on a pre-defined configuration.
# The output is captured in a logfile and stored in the Logs directory.
#
# This script depends on driver load scripts
# Examples/Driver/scripts/load_vip.sh
# Examples/Driver/scripts/unload_vip.sh
# scripts/runone.sh
#
# This script captures the results and stores it in a logfile.
#
# Command line argument:
# 1. Configuration to run (for example C1)
# 2. Number of iterations (optional, default = 1)
#    or "-i" for interactive runs
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

if [ -f /sbin/rmmod ]
then
    RMMOD=/sbin/rmmod
else
    RMMOD=rmmod
fi
if [ -f /sbin/insmod ]
then
    INSMOD=/sbin/insmod
else
    INSMOD=insmod
fi

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
        echo "Cannot locate $1"
        echo "Please use build_vip.sh first"
        exit 1
    fi
}


#-------------------------------------------------------------------------------
# remove_timestamp
#
# Arguments:
#   None
#
# Removes "[12345something] " from the start of $line
#
remove_timestamp()
{
    # check for debug kernel timestamp
    start_char=$(expr substr "$line" 1 1)
    if [ "$start_char" =  "[" ]
    then
        # remove the timestamp
        stamp_len=1
        end_char=x
        while [ "$end_char" != "]" ]
        do
            stamp_len=$((stamp_len+1))
            end_char=$(expr substr "$line" $stamp_len 1)
        done

        # remove stamp-end and following space
        stamp_len=$((stamp_len+1))
        line=$(expr substr "$line" $stamp_len 500)

        # remove the initial spaces, like read does
        # expr can return empty string
        start_char=$(expr substr "$line" 1 1)
        while [ "$start_char" = " " ]
        do
            line=$(expr substr "$line" 2 500)
            start_char=$(expr substr "$line" 1 1)
        done
    fi
}

# main script starts here
# move to the script base directory
MY_DIR=$(dirname $0)
cd $MY_DIR

# process arguments
num_iterations=1
prompt_after_iteration="n"
NoResetAllowed=""
while [ "$2" != "" ]; do
    case $2 in
        "-i" ) prompt_after_iteration="y";;
        "-r") NoResetAllowed="-noreset";;
        *) num_iterations=$2;;
    esac
    shift
done

if [ "$ARCH" = '' ]
then
    export ARCH=arm
fi
export HOST_HW_PLATFORM=FPGA_Zynq_ZC702

DDK_DIR=$(pwd)/../../
DRV_VIP_SCRIPTS_DIR=../../Examples/Driver/scripts
DRV_VAL_SCRIPTS_DIR=../../Examples/Driver_VAL/scripts
DRV_PSA_SCRIPTS_DIR=../../Examples/Driver_PSA/scripts
KSUPP_DIR=../../Examples/Driver_KernelSupport/UMDevXS/scripts
DEMOAPP_DIR=../../Examples/DemoApp_VAL/scripts
BUILDS_DIR=$(pwd)/Builds/$1

# User Mode device
KO_NAME_DRIVER=umdevxs_k
CHAR_NAME_DEVICE=umdevxs_c

# create the empty log file
LOG_FILE=Logs/testlog_$1_${ARCH}.log
SANITY_LOG_FILE=Logs/testlog_$1_${ARCH}_issues.log
COV_LOG_FILE=Logs/covlog_$1_${ARCH}.log
mkdir -p Logs
echo $1 > $LOG_FILE

# clear the dmesg output
dmesg -c  > /dev/null

echo "[Regress $1] Start Date and Time : `date`"
echo "[Regress $1] Logging to $LOG_FILE"

if grep $KO_NAME_DRIVER /proc/modules >/dev/null
then
    echo Removing Kernel Support driver
    $RMMOD $KO_NAME_DRIVER
    rm -f /dev/$CHAR_NAME_DEVICE
fi

# Single application tests using combined (VIP) driver

if [ -f $BUILDS_DIR/driver_vip_k.ko ]
then
    echo "[Regress $1] Single application tests using VIP driver" >>$LOG_FILE
    echo "[Regress $1] Single application tests using VIP driver"

    # load the kernel-space combined (VIP) driver
    $DRV_VIP_SCRIPTS_DIR/load_vip.sh $BUILDS_DIR

    if [ "$NoResetAllowed" != "-noreset" ]
    then
        if [ -f $BUILDS_DIR/da_val_combined_up ]
        then
            echo "[Regress $1] Starting DemoApp VAL Combined VEX-proxied user-space to perform a FW reset"
            echo "[Regress $1] Starting DemoApp VAL Combined VEX-proxied user-space to perform a FW reset" >>$LOG_FILE
            $VALGRIND $BUILDS_DIR/da_val_combined_up -reset >> $LOG_FILE 2>&1
            dmesg -c >> $LOG_FILE
        fi
    fi

    # Kernel-space applications
    if [ -f $BUILDS_DIR/test_val_k.ko ]
    then
        count=0

        while [ $count -ne ${num_iterations} ]
        do
            count=$(expr $count + 1)

            echo "[Regress $1] Starting TestTool VAL kernel-space (Iteration $count)" >> $LOG_FILE
            echo "[Regress $1] Starting TestTool VAL kernel-space (Iteration $count)"
            $INSMOD $BUILDS_DIR/test_val_k.ko >> $LOG_FILE 2>&1
            $RMMOD test_val_k >> $LOG_FILE 2>&1

            if [ "$prompt_after_iteration" != "n" ]
            then
                echo "[Regress $1] Press ENTER to proceed"
                read response
            fi
        done

        # capture final output, which could include leakage details
        dmesg -c >> $LOG_FILE

        echo "[Regress $1] Starting DemoApp VAL kernel-space" >>$LOG_FILE
        echo "[Regress $1] Starting DemoApp VAL kernel-space"
        $INSMOD $BUILDS_DIR/da_val_k.ko >> $LOG_FILE 2>&1
        $RMMOD da_val_k >> $LOG_FILE 2>&1
        dmesg -c >> $LOG_FILE
    else
        echo "[Regress $1] Kernel-space test val not compiled, skipped!" >>$LOG_FILE
        echo "[Regress $1] Kernel-space test val not compiled, skipped!"
    fi

    # User-space VEX-proxied applications
    if [ -f $BUILDS_DIR/test_val_combined_up ]
    then
        count=0
        export VALGRIND=$VALGRIND_BIN

        while [ $count -ne ${num_iterations} ]
        do
            count=$(expr $count + 1)

            echo "[Regress $1] Starting TestTool VAL Combined VEX-proxied user-space (Iteration $count)" >> $LOG_FILE
            echo "[Regress $1] Starting TestTool VAL Combined VEX-proxied user-space (Iteration $count)"
            $VALGRIND $BUILDS_DIR/test_val_combined_up $NoResetAllowed >> $LOG_FILE 2>&1

            if [ "$prompt_after_iteration" != "n" ]
            then
                echo "[Regress $1] Press ENTER to proceed"
                read response
            fi
        done

        # capture final output, which could include leakage details
        dmesg -c >> $LOG_FILE

        echo "[Regress $1] Starting DemoApp VAL Combined VEX-proxied user-space" >>$LOG_FILE
        echo "[Regress $1] Starting DemoApp VAL Combined VEX-proxied user-space"
        $VALGRIND $BUILDS_DIR/da_val_combined_up >> $LOG_FILE 2>&1
        dmesg -c >> $LOG_FILE
    else
        echo "[Regress $1] User-space VEX-proxied apps not compiled, skipped!" >>$LOG_FILE
        echo "[Regress $1] User-space VEX-proxied apps not compiled, skipped!"
    fi

    # unload the kernel-space combined (VIP) driver
    $DRV_VIP_SCRIPTS_DIR/unload_vip.sh
    dmesg -c >> $LOG_FILE
else
     echo "[Regress $1] Kernel-space VIP driver not compiled, skipped!" >>$LOG_FILE
     echo "[Regress $1] Kernel-space VIP driver not compiled, skipped!"
fi

# User-space applications,
# based on Kernel Support UMDevXS driver and combined VIP user-space driver
if [ -f $BUILDS_DIR/../${KO_NAME_DRIVER}.ko ]
then
    # load the kernel components
    $KSUPP_DIR/load.sh $BUILDS_DIR/..
    export VALGRIND=$VALGRIND_BIN

    if [ "$NoResetAllowed" != "-noreset" ]
    then
        # Perform FW reset to have control over the starting-point
        echo "[Regress $1] Starting DemoApp VAL UMDevXS user-space to perform a FW reset"
        echo "[Regress $1] Starting DemoApp VAL UMDevXS user-space to perform a FW reset" >>$LOG_FILE
        $VALGRIND $BUILDS_DIR/da_val_combined_u -reset >> $LOG_FILE 2>&1
    fi

    # Run TestTool VAL
    count=0
    while [ $count -ne ${num_iterations} ]
    do
        count=$(expr $count + 1)

        echo "[Regress $1] Starting TestTool VAL UMDevXS user-space (Iteration $count)" >>$LOG_FILE
        echo "[Regress $1] Starting TestTool VAL UMDevXS user-space (Iteration $count)"
        $VALGRIND $BUILDS_DIR/test_val_combined_u $NoResetAllowed >> $LOG_FILE 2>&1

        if [ "$prompt_after_iteration" != "n" ]
        then
            echo "[Regress $1] Press ENTER to proceed"
            read response
        fi
    done

    # Run TestTool PSA
    count=0
    while [ $count -ne ${num_iterations} ]
    do
        count=$(expr $count + 1)

        echo "[Regress $1] Starting TestTool PSA UMDevXS user-space (Iteration $count)" >>$LOG_FILE
        echo "[Regress $1] Starting TestTool PSA UMDevXS user-space (Iteration $count)"
        $VALGRIND $BUILDS_DIR/test_psa_combined_u $NoResetAllowed >> $LOG_FILE 2>&1

        if [ "$prompt_after_iteration" != "n" ]
        then
            echo "[Regress $1] Press ENTER to proceed"
            read response
        fi
    done

    # Run DemoApp VAL
    echo "[Regress $1] Starting DemoApp VAL UMDevXS user-space" >>$LOG_FILE
    echo "[Regress $1] Starting DemoApp VAL UMDevXS user-space"
    $VALGRIND $BUILDS_DIR/da_val_combined_u >> $LOG_FILE 2>&1

    $KSUPP_DIR/unload.sh
    dmesg -c >> $LOG_FILE
else
     echo "[Regress $1] UMDevXS driver not compiled, skipped!" >>$LOG_FILE
     echo "[Regress $1] UMDevXS driver not compiled, skipped!"
fi

echo "[Regress $1] Finish Date and Time : `date`"

# Gather coverage data
if [ "$COVER_DDK" = 'y' ]
then
    lcov -c -d $DDK_DIR -o $1.info > $COV_LOG_FILE 2>&1

    if [ -d "$COVER_OUTPUT_DIR" ]
    then
        COVER_OUT=$COVER_OUTPUT_DIR/Coverage
    else
        COVER_OUT=$BUILDS_DIR/../../Coverage
    fi

    mkdir -p $COVER_OUT/$1
    genhtml -o $1 $1.info >> $COV_LOG_FILE 2>&1
    mv $1 $COVER_OUT
    rm -f $1.info
fi

# Sanity-check the log file
grep -i -E "error|warning|dump|bug|fault|oops|fail|fatal|panic|poison|overflow|corrupt" $LOG_FILE | grep -v "Pass=100, Fail=0" > $SANITY_LOG_FILE
sanity_count=$(cat $SANITY_LOG_FILE | wc -l)
if test $sanity_count = 0
then
    rm $SANITY_LOG_FILE
else
    echo "[Regress $1] Found" $sanity_count "ISSUES!" >> $LOG_FILE
    echo "[Regress $1] Found" $sanity_count "ISSUES! Please inspect $SANITY_LOG_FILE"
fi

# Count and report the results
count_pass=$(grep "PASSED" $LOG_FILE | wc -l)
echo "[Regress $1] Tests PASSED:" $count_pass >> $LOG_FILE
echo "[Regress $1] Tests PASSED:" $count_pass

count_fail=$(grep "FAILED" $LOG_FILE | wc -l)
echo "[Regress $1] Tests FAILED:" $count_fail >> $LOG_FILE
echo "[Regress $1] Tests FAILED:" $count_fail

# Update the summary logs
SUMMARY_LOG_FILE=Logs/testlog_summary_${ARCH}.log
echo "Summary Log File" > $SUMMARY_LOG_FILE
# No support for interrupt configurations yet
BUILD_CONFIGS="C0 C1 C2 C3 C4 C5"
for ConfigLp in $BUILD_CONFIGS
do
    LOG_FILE=Logs/testlog_${ConfigLp}_${ARCH}.log
    if [ -f  $LOG_FILE ]
    then
        # copy the ISSUES line
        grep "Regress $ConfigLp" $LOG_FILE | grep "ISSUES" >> $SUMMARY_LOG_FILE
        # copy the PASSED and FAILED lines
        grep "Regress $ConfigLp" $LOG_FILE | grep "] Tests " >> $SUMMARY_LOG_FILE
    fi
done

count_pass=$(grep "PASSED" Logs/testlog_C*_${ARCH}.log | grep -v "] Tests PASSED" | wc -l)
count_fail=$(grep "FAILED" Logs/testlog_C*_${ARCH}.log | grep -v "] Tests FAILED" | wc -l)
echo "----" >> $SUMMARY_LOG_FILE
echo "Total tests PASSED:" $count_pass >> $SUMMARY_LOG_FILE
echo "Total tests FAILED:" $count_fail >> $SUMMARY_LOG_FILE

# end of file
