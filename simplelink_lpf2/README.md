# Simplelink LPF2

This folder contains the low-level support required from the
Simplelink LPF2 SDK.

### Version

The current version of simplelink_lpf2 is based on
[Simplelink LPF2 8.31.00.11](https://github.com/TexasInstruments/simplelink-lowpower-f2-sdk).

## Contents

The folder-structure herein reflects the folder-structure in the
Simplelink SDK. All files required to support Zephyr have been copied
manually from the Simplelink SDK, with the exception of DPL files under
`kernel/zephyr/dpl`, which are original and maintained in this repository.

When updating to a new SDK, a comparison of the files in the 'devices'
and 'drivers' directories should be performed to pick up any new changes.

There is a simple helper script present to copy the relevant directories.
