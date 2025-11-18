# Simplelink LPF2

This folder contains the low-level support required from the
Simplelink LPF2 SDK.

### Version

The current version of simplelink_lpf2 is based on
[Simplelink LPF2 8.33.00.16](https://github.com/TexasInstruments/simplelink-lowpower-f2-sdk).

## Contents

The folder-structure herein reflects the folder-structure in the
Simplelink SDK. All files required to support Zephyr have been copied
manually from the Simplelink SDK, with the exception of DPL files under
`kernel/zephyr/dpl`, which are original and maintained in this repository.

When updating to a new SDK, a comparison of the files in the 'devices'
and 'drivers' directories should be performed to pick up any new changes.

## Updating the SDK

The SDK sources are copied from the SDK repository, keeping only `.c`/`.h`
files and the SDK folder structure:

```sh
git clone https://github.com/TexasInstruments/simplelink-lowpower-f2-sdk.git
cd simplelink-lowpower-f2-sdk
git checkout <new SDK tag>

SDK=$(pwd)
OUT=<zephyr-workspace>/modules/hal/ti/simplelink_lpf2
copy_src() {
    rsync -amv --include='*/' --include='*.c' --include='*.h' --exclude='*' "$@"
}

rm -r ${OUT}/source
mkdir -p ${OUT}/source/ti/devices
copy_src ${SDK}/source/ti/drivers ${OUT}/source/ti/
copy_src ${SDK}/source/ti/log ${OUT}/source/ti/
copy_src ${SDK}/source/ti/devices/DeviceFamily.h ${OUT}/source/ti/devices/
copy_src ${SDK}/source/ti/devices/cc13x2x7_cc26x2x7 ${OUT}/source/ti/devices/
```

Then re-apply the Zephyr-specific changes. Look for the `Zephyr` keyword
in `git diff` and restore those changes:

- `source/ti/devices/cc13x2x7_cc26x2x7/startup_files/ccfg.c`: include
  `<zephyr/linker/sections.h>` and put `__ccfg` in `__ti_ccfg_section`.
- `source/ti/drivers/power/PowerCC26X2.c`: send power constraint
  set/release to Zephyr's `pm_policy_state_lock_get/put()`, and keep
  interrupts disabled after `Power_sleep()` returns (comment out
  `CPUcpsie()`).

Finally, update the version above and check for new or changed files that
`CMakeLists.txt` needs.
