#!/bin/sh
#
# unload.sh
#
# This script unloads the Kernel Support Driver and deletes the communication
# point for the application (using the proxy).
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

# print and clear messages
dmesg -c 2>/dev/null

# check that we run with root rights
# (this assumes dmesg -c is root-only)
if [ $? -ne 0 ]
then
    echo "Not enough rights. Try sudo."
    exit
fi

# unload the driver
$RMMOD $KO_NAME_DRIVER

# remove the communication point
rm -f /dev/$CHAR_NAME_DEVICE

# print and clear the shutdown-messages
dmesg -c

# end of script unload.sh
