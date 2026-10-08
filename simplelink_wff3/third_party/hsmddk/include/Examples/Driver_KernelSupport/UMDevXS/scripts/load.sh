#!/bin/sh
#
# load.sh
#
# This script loads the Kernel Support Driver (UMDevXS) and creates
# the communication point for the application (using the proxy).
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

if [ -f /sbin/insmod ]
then
    INSMOD=/sbin/insmod
else
    INSMOD=insmod
fi

DIR_NAME_DRIVER=UMDevXS

if [ $HOST_HW_PLATFORM = "FPGA_Zynq_ZC702" ]
then
    KO_NAME_DRIVER=umdevxs_k.ko
    CHAR_NAME_DEVICE=umdevxs_c
elif [ $HOST_HW_PLATFORM = "FPGA_V2M_Juno" ]
then
    KO_NAME_DRIVER=umdevxs_k.ko
    CHAR_NAME_DEVICE=umdevxs_c
elif [ $HOST_HW_PLATFORM = "FPGA_Virtex6_PCI" ]
then
    KO_NAME_DRIVER=umpci_k.ko
    CHAR_NAME_DEVICE=umpci_c
else
    echo "Unsupported HOST_HW_PLATFORM $HOST_HW_PLATFORM"
    exit 1
fi

dmesg -c > /dev/null 2>&1
if [ $? -ne 0 ]
then
    echo "Not enough rights. Try sudo."
    exit
fi

# check if the driver binary location is provided, if not use default
if [ $# -eq 1 ]
then
    build=$1/$KO_NAME_DRIVER
else
    build=../../Driver_KernelSupport/$DIR_NAME_DRIVER/build/$KO_NAME_DRIVER
fi

if [ ! -f "$build" ]
then
    echo "Fatal: cannot find driver"
    exit
fi

# load the driver
$INSMOD $build

# grab the major number for the character device
major_nr=`awk "\\$2==\"$CHAR_NAME_DEVICE\" {print \\$1}" /proc/devices`
#echo "Major nr: $major_nr"

# make the communication pointer
mknod /dev/$CHAR_NAME_DEVICE c ${major_nr} 0

# make accessible to application
chmod 666 /dev/$CHAR_NAME_DEVICE

# print and clear start-up messages
dmesg -c

# end of file load.sh
