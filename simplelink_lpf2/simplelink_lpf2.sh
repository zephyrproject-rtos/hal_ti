#!/bin/sh

# A simple script to copy relevant files from TI Simplelink F2 SDK.

SOURCE=$1
OUTPUT=$2

mkdir -p ${OUTPUT}/source/ti
rsync --include='*/' --include='*.c' --include='*.h' --exclude='*' -amv ${SOURCE}/source/ti/drivers $OUTPUT/source/ti/

rsync --include='*/' --include='*.c' --include='*.h' --exclude='*' -amv ${SOURCE}/source/ti/log $OUTPUT/source/ti/

mkdir -p ${OUTPUT}/source/ti/devices
rsync --include='*/' --include='*.c' --include='*.h' --exclude='*' -amv ${SOURCE}/source/ti/devices/DeviceFamily.h $OUTPUT/source/ti/devices/
rsync --include='*/' --include='*.c' --include='*.h' --exclude='*' -amv ${SOURCE}/source/ti/devices/cc13x2x7_cc26x2x7 $OUTPUT/source/ti/devices/

echo "Please make Zephyr specific changes to source/ti/devices/cc13x2x7_cc26x2x7/startup_files/ccfg.c"
echo "Please make Zephyr specific changes to source/ti/drivers/power/PowerCC26X2.c"
