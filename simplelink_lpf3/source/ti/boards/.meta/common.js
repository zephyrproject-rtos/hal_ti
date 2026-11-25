/* Copyright (c) 2025, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

scripting.excludeFromBuild("ti_secure_boot_properties.json");
scripting.excludeFromBuild("ti_secure_boot_properties.h");
scripting.excludeFromBuild("syscfg_c.rov.xs");
scripting.excludeFromBuild("ti_devices_config.c");
scripting.excludeFromBuild("ti_utils_build_linker.cmd.genlibs");
scripting.excludeFromBuild("ti_utils_build_compiler.opt");

/**
 * Import the modules used in this configuration.
 */
const custom   = scripting.addModule("/ti/devices/radioconfig/custom");
const rfdesign = scripting.addModule("/ti/devices/radioconfig/rfdesign");

/**
 * Write custom configuration values to the imported modules.
 */
custom.ble                                                = ["adc_noise","ble"];
custom.radioConfigadc_noise.$name                         = "ti_devices_radioconfig_settings_ble1";
custom.radioConfigadc_noise.codeExportConfig.$name        = "ti_devices_radioconfig_code_export_param1";
custom.radioConfigadc_noise.codeExportConfig.symGenMethod = "Custom";
custom.radioConfigadc_noise.codeExportConfig.phyAbbr      = true;
custom.radioConfigble.$name                               = "ti_devices_radioconfig_settings_ble0";
custom.radioConfigble.codeExportConfig.$name              = "ti_devices_radioconfig_code_export_param0";
scripting.suppress("This PHY property has no effect on the exported code \\(no corresponding RCL command selected\\)\\.", custom.radioConfigble, "subPhy");
scripting.suppress("This PHY property has no effect on the exported code \\(no corresponding RCL command selected\\)\\.", custom.radioConfigble, "codedTxRate");

const Board = scripting.addModule("/ti/drivers/Board");
Board.generateInitializationFunctions = false;
Board.generateBoardInit = false;

const BatteryMonitor = scripting.addModule("/ti/drivers/BatteryMonitor");
const BatMonSupportLPF3 = scripting.addModule("/ti/drivers/batterymonitor/BatMonSupportLPF3");
BatMonSupportLPF3.interruptNumber = "INT_CPUIRQ2";

const Power          = scripting.addModule("/ti/drivers/Power");
Power.policyInitFunction = "Not Required"
Power.policyFunction = "Custom";
