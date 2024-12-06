# Simplelink LPF3

This folder contains the low-level support required from the
Simplelink LPF3 SDK.

### Version

The current version of simplelink_lpf3 is based on
[Simplelink LPF3 8.20.00](https://www.ti.com/tool/download/SIMPLELINK-LOWPOWER-F3-SDK/).

Specifically, the following components have been used:
- Core SDK 8.10.01.04
- RCL 8.20.01.04

## Contents

The folder-structure herein reflects the folder-structure in the
Simplelink SDK. All files required to support Zephyr have been copied
manually from the Simplelink SDK, with the exception of DPL files under
`kernel/zephyr/dpl`, which are original and maintained in this repository.

When updating to a new SDK, a comparison of the files in the 'devices'
and 'drivers' directories should be performed to pick up any new changes.
