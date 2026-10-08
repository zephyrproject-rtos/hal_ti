#!/bin/bash
#
# This script runs the VAL demo application once.
# 1. Load Driver kernel module
# 2. Load da_val kernel module
# 3. Capture results
# 4. Unload da_val
# 5. Unload Driver
#
# Unless a path is provided, this script will load the components from their
# default location in the DDK, relative to the location of the script itself.
# The optional directory pointed to must contain all binaries.
#
# This script makes dmesg output and clear its message buffer.
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
      echo "[run_da_val.sh] Missing file $1"
      exit 1
  fi
}

# main script starts here

KO_NAME_DRIVER=driver_val_k.ko
KO_NAME_DEMOAPP=da_val_k.ko

# move to the script base directory
MY_DIR=$(dirname $0)
cd $MY_DIR

if [ $# -eq 0 ]
then
    PATH_DRIVER=../../Driver/build
    PATH_DEMOAPP=../build
else
    PATH_DRIVER=$1
    PATH_DEMOAPP=$1
fi

# make sure the components are in place
check_file_exists $PATH_DRIVER/$KO_NAME_DRIVER
check_file_exists $PATH_DEMOAPP/$KO_NAME_DEMOAPP

# empty dmesg output prior to starting DEMOAPP
dmesg -c > /dev/null

# load the kernel modules
$INSMOD $PATH_DRIVER/$KO_NAME_DRIVER

# capture load messages
dmesg -c

# following line starts execution of the tests
$INSMOD $PATH_DEMOAPP/$KO_NAME_DEMOAPP

# capture test execution results
dmesg -c

$RMMOD $KO_NAME_DEMOAPP
$RMMOD $KO_NAME_DRIVER

# end of file
