/******************************************************************************
*  Filename:       hw_soc_ic.h
*
*  Description:    Defines and prototypes for the SOC_IC peripheral.
*
*  Copyright (c) 2023-2025, Texas Instruments Incorporated
*  All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions are met:
*
*  1) Redistributions of source code must retain the above copyright notice,
*     this list of conditions and the following disclaimer.
*
*  2) Redistributions in binary form must reproduce the above copyright notice,
*     this list of conditions and the following disclaimer in the documentation
*     and/or other materials provided with the distribution.
*
*  3) Neither the name of the ORGANIZATION nor the names of its contributors may
*     be used to endorse or promote products derived from this software without
*     specific prior written permission.
*
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
*  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
*  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
*  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
*  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
*  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
*  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
*  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
*  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
*  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
*  POSSIBILITY OF SUCH DAMAGE.
*
******************************************************************************/
#ifndef __HW_SOC_IC_H__
#define __HW_SOC_IC_H__
/*-------------------------------------------------------------------------------

This section defines the register offsets of the SOC_IC component

--------------------------------------------------------------------------------- */

//SOC Interconnect priority registers
#define SOC_IC_O_PRIO0                                               0x00000000U

//SOC Interconnect priority registers
#define SOC_IC_O_PRIO1                                               0x00000004U

//SOC Interconnect priority registers
#define SOC_IC_O_PRIO2                                               0x00000008U

//SOC Interconnect priority registers
#define SOC_IC_O_PRIO3                                               0x0000000CU

//SOC Interconnect priority registers
#define SOC_IC_O_PRIO4                                               0x00000010U

//OCP Slave serror and Time-out Status 1
#define SOC_IC_O_ERRSTA1                                             0x00000014U

//OCP Slave serror and Time-out Status 2
#define SOC_IC_O_ERRSTA2                                             0x00000018U

//Address Watch Configuration 1
#define SOC_IC_O_ADDRCFG1                                            0x0000001CU

//Address Watch Configuration 2
#define SOC_IC_O_ADDRCFG2                                            0x00000020U

//Address Watch Configuration 3
#define SOC_IC_O_ADDRCFG3                                            0x00000024U

//Address Watch Configuration 4
#define SOC_IC_O_ADDRCFG4                                            0x00000028U

//Address Watch Status 1
#define SOC_IC_O_ADDRSTA1                                            0x0000002CU

//Address Watch Status 2
#define SOC_IC_O_ADDRSTA2                                            0x00000030U

//Time-out Masters Configuration
#define SOC_IC_O_TOMSTCFG                                            0x00000034U

//Time-out Slave Configuration
#define SOC_IC_O_TOSLVCFG                                            0x00000038U



/*-----------------------------------REGISTER------------------------------------
    Register name:       PRIO0
    Offset name:         SOC_IC_O_PRIO0
    Relative address:    0x0
    Description:         SOC Interconnect priority registers. Define the priority in which master will be arbitered toward each slave.
    Default Value:       0x00000001

        Field:           L3WSOCIC
        From..to bits:   0...2
        DefaultValue:    0x1
        Access type:     read-write
        Description:     <Slave-name><Master-name>
                         Set the priority for specific Master transaction toward a specific slave.
                         priority values:
                         0 - N.A
                         1 - Lowest priority
                         2 - Higher priority
                         3- ...
                         N - Highest priority
                         where N is NUM_OF_MASTERS


*/
#define SOC_IC_PRIO0_L3WSOCIC_W                                      3U
#define SOC_IC_PRIO0_L3WSOCIC_M                                      0x00000007U
#define SOC_IC_PRIO0_L3WSOCIC_S                                      0U
/*

        Field:           L3DMARD
        From..to bits:   3...5
        DefaultValue:    0x0
        Access type:     read-write
        Description:     <Slave-name><Master-name>
                         Set the priority for specific Master transaction toward a specific slave.
                         priority values:
                         0 - N.A
                         1 - Lowest priority
                         2 - Higher priority
                         3- ...
                         N - Highest priority
                         where N is NUM_OF_MASTERS


*/
#define SOC_IC_PRIO0_L3DMARD_W                                       3U
#define SOC_IC_PRIO0_L3DMARD_M                                       0x00000038U
#define SOC_IC_PRIO0_L3DMARD_S                                       3U
/*

        Field:           L3DMAWR
        From..to bits:   6...8
        DefaultValue:    0x0
        Access type:     read-write
        Description:     <Slave-name><Master-name>
                         Set the priority for specific Master transaction toward a specific slave.
                         priority values:
                         0 - N.A
                         1 - Lowest priority
                         2 - Higher priority
                         3- ...
                         N - Highest priority
                         where N is NUM_OF_MASTERS


*/
#define SOC_IC_PRIO0_L3DMAWR_W                                       3U
#define SOC_IC_PRIO0_L3DMAWR_M                                       0x000001C0U
#define SOC_IC_PRIO0_L3DMAWR_S                                       6U
/*

        Field:           L3HMCU
        From..to bits:   9...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     <Slave-name><Master-name>
                         Set the priority for specific Master transaction toward a specific slave.
                         priority values:
                         0 - N.A
                         1 - Lowest priority
                         2 - Higher priority
                         3- ...
                         N - Highest priority
                         where N is NUM_OF_MASTERS


*/
#define SOC_IC_PRIO0_L3HMCU_W                                        3U
#define SOC_IC_PRIO0_L3HMCU_M                                        0x00000E00U
#define SOC_IC_PRIO0_L3HMCU_S                                        9U
/*

        Field:           L3I2S
        From..to bits:   12...14
        DefaultValue:    0x0
        Access type:     read-write
        Description:     <Slave-name><Master-name>
                         Set the priority for specific Master transaction toward a specific slave.
                         priority values:
                         0 - N.A
                         1 - Lowest priority
                         2 - Higher priority
                         3- ...
                         N - Highest priority
                         where N is NUM_OF_MASTERS


*/
#define SOC_IC_PRIO0_L3I2S_W                                         3U
#define SOC_IC_PRIO0_L3I2S_M                                         0x00007000U
#define SOC_IC_PRIO0_L3I2S_S                                         12U
/*

        Field:           L3HSM
        From..to bits:   15...17
        DefaultValue:    0x0
        Access type:     read-write
        Description:     <Slave-name><Master-name>
                         Set the priority for specific Master transaction toward a specific slave.
                         priority values:
                         0 - N.A
                         1 - Lowest priority
                         2 - Higher priority
                         3- ...
                         N - Highest priority
                         where N is NUM_OF_MASTERS


*/
#define SOC_IC_PRIO0_L3HSM_W                                         3U
#define SOC_IC_PRIO0_L3HSM_M                                         0x00038000U
#define SOC_IC_PRIO0_L3HSM_S                                         15U
/*

        Field:           HMCUWSOCIC
        From..to bits:   18...20
        DefaultValue:    0x0
        Access type:     read-write
        Description:     <Slave-name><Master-name>
                         Set the priority for specific Master transaction toward a specific slave.
                         priority values:
                         0 - N.A
                         1 - Lowest priority
                         2 - Higher priority
                         3- ...
                         N - Highest priority
                         where N is NUM_OF_MASTERS


*/
#define SOC_IC_PRIO0_HMCUWSOCIC_W                                    3U
#define SOC_IC_PRIO0_HMCUWSOCIC_M                                    0x001C0000U
#define SOC_IC_PRIO0_HMCUWSOCIC_S                                    18U
/*

        Field:           HMCUDMARD
        From..to bits:   21...23
        DefaultValue:    0x0
        Access type:     read-write
        Description:     <Slave-name><Master-name>
                         Set the priority for specific Master transaction toward a specific slave.
                         priority values:
                         0 - N.A
                         1 - Lowest priority
                         2 - Higher priority
                         3- ...
                         N - Highest priority
                         where N is NUM_OF_MASTERS


*/
#define SOC_IC_PRIO0_HMCUDMARD_W                                     3U
#define SOC_IC_PRIO0_HMCUDMARD_M                                     0x00E00000U
#define SOC_IC_PRIO0_HMCUDMARD_S                                     21U
/*

        Field:           HMCUDMAWR
        From..to bits:   24...26
        DefaultValue:    0x0
        Access type:     read-write
        Description:     <Slave-name><Master-name>
                         Set the priority for specific Master transaction toward a specific slave.
                         priority values:
                         0 - N.A
                         1 - Lowest priority
                         2 - Higher priority
                         3- ...
                         N - Highest priority
                         where N is NUM_OF_MASTERS


*/
#define SOC_IC_PRIO0_HMCUDMAWR_W                                     3U
#define SOC_IC_PRIO0_HMCUDMAWR_M                                     0x07000000U
#define SOC_IC_PRIO0_HMCUDMAWR_S                                     24U
/*

        Field:           HMCUI2S
        From..to bits:   27...29
        DefaultValue:    0x0
        Access type:     read-write
        Description:     <Slave-name><Master-name>
                         Set the priority for specific Master transaction toward a specific slave.
                         priority values:
                         0 - N.A
                         1 - Lowest priority
                         2 - Higher priority
                         3- ...
                         N - Highest priority
                         where N is NUM_OF_MASTERS


*/
#define SOC_IC_PRIO0_HMCUI2S_W                                       3U
#define SOC_IC_PRIO0_HMCUI2S_M                                       0x38000000U
#define SOC_IC_PRIO0_HMCUI2S_S                                       27U


/*-----------------------------------REGISTER------------------------------------
    Register name:       PRIO1
    Offset name:         SOC_IC_O_PRIO1
    Relative address:    0x4
    Description:         SOC Interconnect priority registers. Define the priority in which master will be arbitered toward each slave.
    Default Value:       0x00000001

        Field:           HMCUHSM
        From..to bits:   0...2
        DefaultValue:    0x1
        Access type:     read-write
        Description:     <Slave-name><Master-name>
                         Set the priority for specific Master transaction toward a specific slave.
                         priority values:
                         0 - N.A
                         1 - Lowest priority
                         2 - Higher priority
                         3- ...
                         N - Highest priority
                         where N is NUM_OF_MASTERS


*/
#define SOC_IC_PRIO1_HMCUHSM_W                                       3U
#define SOC_IC_PRIO1_HMCUHSM_M                                       0x00000007U
#define SOC_IC_PRIO1_HMCUHSM_S                                       0U
/*

        Field:           SPWSOCIC
        From..to bits:   3...5
        DefaultValue:    0x0
        Access type:     read-write
        Description:     <Slave-name><Master-name>
                         Set the priority for specific Master transaction toward a specific slave.
                         priority values:
                         0 - N.A
                         1 - Lowest priority
                         2 - Higher priority
                         3- ...
                         N - Highest priority
                         where N is NUM_OF_MASTERS


*/
#define SOC_IC_PRIO1_SPWSOCIC_W                                      3U
#define SOC_IC_PRIO1_SPWSOCIC_M                                      0x00000038U
#define SOC_IC_PRIO1_SPWSOCIC_S                                      3U
/*

        Field:           SPDMARD
        From..to bits:   6...8
        DefaultValue:    0x0
        Access type:     read-write
        Description:     <Slave-name><Master-name>
                         Set the priority for specific Master transaction toward a specific slave.
                         priority values:
                         0 - N.A
                         1 - Lowest priority
                         2 - Higher priority
                         3- ...
                         N - Highest priority
                         where N is NUM_OF_MASTERS


*/
#define SOC_IC_PRIO1_SPDMARD_W                                       3U
#define SOC_IC_PRIO1_SPDMARD_M                                       0x000001C0U
#define SOC_IC_PRIO1_SPDMARD_S                                       6U
/*

        Field:           SPDMAWR
        From..to bits:   9...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     <Slave-name><Master-name>
                         Set the priority for specific Master transaction toward a specific slave.
                         priority values:
                         0 - N.A
                         1 - Lowest priority
                         2 - Higher priority
                         3- ...
                         N - Highest priority
                         where N is NUM_OF_MASTERS


*/
#define SOC_IC_PRIO1_SPDMAWR_W                                       3U
#define SOC_IC_PRIO1_SPDMAWR_M                                       0x00000E00U
#define SOC_IC_PRIO1_SPDMAWR_S                                       9U
/*

        Field:           SPHMCU
        From..to bits:   12...14
        DefaultValue:    0x0
        Access type:     read-write
        Description:     <Slave-name><Master-name>
                         Set the priority for specific Master transaction toward a specific slave.
                         priority values:
                         0 - N.A
                         1 - Lowest priority
                         2 - Higher priority
                         3- ...
                         N - Highest priority
                         where N is NUM_OF_MASTERS


*/
#define SOC_IC_PRIO1_SPHMCU_W                                        3U
#define SOC_IC_PRIO1_SPHMCU_M                                        0x00007000U
#define SOC_IC_PRIO1_SPHMCU_S                                        12U
/*

        Field:           SPHSM
        From..to bits:   15...17
        DefaultValue:    0x0
        Access type:     read-write
        Description:     <Slave-name><Master-name>
                         Set the priority for specific Master transaction toward a specific slave.
                         priority values:
                         0 - N.A
                         1 - Lowest priority
                         2 - Higher priority
                         3- ...
                         N - Highest priority
                         where N is NUM_OF_MASTERS


*/
#define SOC_IC_PRIO1_SPHSM_W                                         3U
#define SOC_IC_PRIO1_SPHSM_M                                         0x00038000U
#define SOC_IC_PRIO1_SPHSM_S                                         15U
/*

        Field:           COREDMARD
        From..to bits:   18...20
        DefaultValue:    0x0
        Access type:     read-write
        Description:     <Slave-name><Master-name>
                         Set the priority for specific Master transaction toward a specific slave.
                         priority values:
                         0 - N.A
                         1 - Lowest priority
                         2 - Higher priority
                         3- ...
                         N - Highest priority
                         where N is NUM_OF_MASTERS


*/
#define SOC_IC_PRIO1_COREDMARD_W                                     3U
#define SOC_IC_PRIO1_COREDMARD_M                                     0x001C0000U
#define SOC_IC_PRIO1_COREDMARD_S                                     18U
/*

        Field:           COREDMAWR
        From..to bits:   21...23
        DefaultValue:    0x0
        Access type:     read-write
        Description:     <Slave-name><Master-name>
                         Set the priority for specific Master transaction toward a specific slave.
                         priority values:
                         0 - N.A
                         1 - Lowest priority
                         2 - Higher priority
                         3- ...
                         N - Highest priority
                         where N is NUM_OF_MASTERS


*/
#define SOC_IC_PRIO1_COREDMAWR_W                                     3U
#define SOC_IC_PRIO1_COREDMAWR_M                                     0x00E00000U
#define SOC_IC_PRIO1_COREDMAWR_S                                     21U
/*

        Field:           COREHMCU
        From..to bits:   24...26
        DefaultValue:    0x0
        Access type:     read-write
        Description:     <Slave-name><Master-name>
                         Set the priority for specific Master transaction toward a specific slave.
                         priority values:
                         0 - N.A
                         1 - Lowest priority
                         2 - Higher priority
                         3- ...
                         N - Highest priority
                         where N is NUM_OF_MASTERS


*/
#define SOC_IC_PRIO1_COREHMCU_W                                      3U
#define SOC_IC_PRIO1_COREHMCU_M                                      0x07000000U
#define SOC_IC_PRIO1_COREHMCU_S                                      24U
/*

        Field:           COREHSM
        From..to bits:   27...29
        DefaultValue:    0x0
        Access type:     read-write
        Description:     <Slave-name><Master-name>
                         Set the priority for specific Master transaction toward a specific slave.
                         priority values:
                         0 - N.A
                         1 - Lowest priority
                         2 - Higher priority
                         3- ...
                         N - Highest priority
                         where N is NUM_OF_MASTERS


*/
#define SOC_IC_PRIO1_COREHSM_W                                       3U
#define SOC_IC_PRIO1_COREHSM_M                                       0x38000000U
#define SOC_IC_PRIO1_COREHSM_S                                       27U


/*-----------------------------------REGISTER------------------------------------
    Register name:       PRIO2
    Offset name:         SOC_IC_O_PRIO2
    Relative address:    0x8
    Description:         SOC Interconnect priority registers. Define the priority in which master will be arbitered toward each slave.
    Default Value:       0x00000004

        Field:           XIPWSOCIC
        From..to bits:   0...2
        DefaultValue:    0x4
        Access type:     read-write
        Description:     <Slave-name><Master-name>
                         Set the priority for specific Master transaction toward a specific slave.
                         priority values:
                         0 - N.A
                         1 - Lowest priority
                         2 - Higher priority
                         3- ...
                         N - Highest priority
                         where N is NUM_OF_MASTERS


*/
#define SOC_IC_PRIO2_XIPWSOCIC_W                                     3U
#define SOC_IC_PRIO2_XIPWSOCIC_M                                     0x00000007U
#define SOC_IC_PRIO2_XIPWSOCIC_S                                     0U
/*

        Field:           XIPDMARD
        From..to bits:   3...5
        DefaultValue:    0x0
        Access type:     read-write
        Description:     <Slave-name><Master-name>
                         Set the priority for specific Master transaction toward a specific slave.
                         priority values:
                         0 - N.A
                         1 - Lowest priority
                         2 - Higher priority
                         3- ...
                         N - Highest priority
                         where N is NUM_OF_MASTERS


*/
#define SOC_IC_PRIO2_XIPDMARD_W                                      3U
#define SOC_IC_PRIO2_XIPDMARD_M                                      0x00000038U
#define SOC_IC_PRIO2_XIPDMARD_S                                      3U
/*

        Field:           XIPDMAWR
        From..to bits:   6...8
        DefaultValue:    0x0
        Access type:     read-write
        Description:     <Slave-name><Master-name>
                         Set the priority for specific Master transaction toward a specific slave.
                         priority values:
                         0 - N.A
                         1 - Lowest priority
                         2 - Higher priority
                         3- ...
                         N - Highest priority
                         where N is NUM_OF_MASTERS


*/
#define SOC_IC_PRIO2_XIPDMAWR_W                                      3U
#define SOC_IC_PRIO2_XIPDMAWR_M                                      0x000001C0U
#define SOC_IC_PRIO2_XIPDMAWR_S                                      6U
/*

        Field:           XIPHMCU
        From..to bits:   9...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     <Slave-name><Master-name>
                         Set the priority for specific Master transaction toward a specific slave.
                         priority values:
                         0 - N.A
                         1 - Lowest priority
                         2 - Higher priority
                         3- ...
                         N - Highest priority
                         where N is NUM_OF_MASTERS


*/
#define SOC_IC_PRIO2_XIPHMCU_W                                       3U
#define SOC_IC_PRIO2_XIPHMCU_M                                       0x00000E00U
#define SOC_IC_PRIO2_XIPHMCU_S                                       9U
/*

        Field:           XIPHSM
        From..to bits:   12...14
        DefaultValue:    0x0
        Access type:     read-write
        Description:     <Slave-name><Master-name>
                         Set the priority for specific Master transaction toward a specific slave.
                         priority values:
                         0 - N.A
                         1 - Lowest priority
                         2 - Higher priority
                         3- ...
                         N - Highest priority
                         where N is NUM_OF_MASTERS


*/
#define SOC_IC_PRIO2_XIPHSM_W                                        3U
#define SOC_IC_PRIO2_XIPHSM_M                                        0x00007000U
#define SOC_IC_PRIO2_XIPHSM_S                                        12U
/*

        Field:           HDMAWSOCIC
        From..to bits:   15...16
        DefaultValue:    0x0
        Access type:     read-write
        Description:     <Slave-name><Master-name>
                         Set the priority for specific Master transaction toward a specific slave.
                         priority values:
                         0 - N.A
                         1 - Lowest priority
                         2 - Higher priority
                         3- ...
                         N - Highest priority
                         where N is NUM_OF_MASTERS


*/
#define SOC_IC_PRIO2_HDMAWSOCIC_W                                    2U
#define SOC_IC_PRIO2_HDMAWSOCIC_M                                    0x00018000U
#define SOC_IC_PRIO2_HDMAWSOCIC_S                                    15U
/*

        Field:           HDMAHOSTMCU
        From..to bits:   17...18
        DefaultValue:    0x0
        Access type:     read-write
        Description:     <Slave-name><Master-name>
                         Set the priority for specific Master transaction toward a specific slave.
                         priority values:
                         0 - N.A
                         1 - Lowest priority
                         2 - Higher priority
                         3- ...
                         N - Highest priority
                         where N is NUM_OF_MASTERS


*/
#define SOC_IC_PRIO2_HDMAHOSTMCU_W                                   2U
#define SOC_IC_PRIO2_HDMAHOSTMCU_M                                   0x00060000U
#define SOC_IC_PRIO2_HDMAHOSTMCU_S                                   17U
/*

        Field:           HDMAHSM
        From..to bits:   19...20
        DefaultValue:    0x0
        Access type:     read-write
        Description:     <Slave-name><Master-name>
                         Set the priority for specific Master transaction toward a specific slave.
                         priority values:
                         0 - N.A
                         1 - Lowest priority
                         2 - Higher priority
                         3- ...
                         N - Highest priority
                         where N is NUM_OF_MASTERS


*/
#define SOC_IC_PRIO2_HDMAHSM_W                                       2U
#define SOC_IC_PRIO2_HDMAHSM_M                                       0x00180000U
#define SOC_IC_PRIO2_HDMAHSM_S                                       19U
/*

        Field:           HSMWSOCIC
        From..to bits:   21...23
        DefaultValue:    0x0
        Access type:     read-write
        Description:     <Slave-name><Master-name>
                         Set the priority for specific Master transaction toward a specific slave.
                         priority values:
                         0 - N.A
                         1 - Lowest priority
                         2 - Higher priority
                         3- ...
                         N - Highest priority
                         where N is NUM_OF_MASTERS


*/
#define SOC_IC_PRIO2_HSMWSOCIC_W                                     3U
#define SOC_IC_PRIO2_HSMWSOCIC_M                                     0x00E00000U
#define SOC_IC_PRIO2_HSMWSOCIC_S                                     21U
/*

        Field:           HSMDMARD
        From..to bits:   24...26
        DefaultValue:    0x0
        Access type:     read-write
        Description:     <Slave-name><Master-name>
                         Set the priority for specific Master transaction toward a specific slave.
                         priority values:
                         0 - N.A
                         1 - Lowest priority
                         2 - Higher priority
                         3- ...
                         N - Highest priority
                         where N is NUM_OF_MASTERS


*/
#define SOC_IC_PRIO2_HSMDMARD_W                                      3U
#define SOC_IC_PRIO2_HSMDMARD_M                                      0x07000000U
#define SOC_IC_PRIO2_HSMDMARD_S                                      24U
/*

        Field:           HSMDMAWR
        From..to bits:   27...29
        DefaultValue:    0x0
        Access type:     read-write
        Description:     <Slave-name><Master-name>
                         Set the priority for specific Master transaction toward a specific slave.
                         priority values:
                         0 - N.A
                         1 - Lowest priority
                         2 - Higher priority
                         3- ...
                         N - Highest priority
                         where N is NUM_OF_MASTERS


*/
#define SOC_IC_PRIO2_HSMDMAWR_W                                      3U
#define SOC_IC_PRIO2_HSMDMAWR_M                                      0x38000000U
#define SOC_IC_PRIO2_HSMDMAWR_S                                      27U


/*-----------------------------------REGISTER------------------------------------
    Register name:       PRIO3
    Offset name:         SOC_IC_O_PRIO3
    Relative address:    0xC
    Description:         SOC Interconnect priority registers. Define the priority in which master will be arbitered toward each slave.
    Default Value:       0x00000004

        Field:           HSMHMCU
        From..to bits:   0...2
        DefaultValue:    0x4
        Access type:     read-write
        Description:     <Slave-name><Master-name>
                         Set the priority for specific Master transaction toward a specific slave.
                         priority values:
                         0 - N.A
                         1 - Lowest priority
                         2 - Higher priority
                         3- ...
                         N - Highest priority
                         where N is NUM_OF_MASTERS


*/
#define SOC_IC_PRIO3_HSMHMCU_W                                       3U
#define SOC_IC_PRIO3_HSMHMCU_M                                       0x00000007U
#define SOC_IC_PRIO3_HSMHMCU_S                                       0U
/*

        Field:           A2NDMARD
        From..to bits:   3...5
        DefaultValue:    0x0
        Access type:     read-write
        Description:     <Slave-name><Master-name>
                         Set the priority for specific Master transaction toward a specific slave.
                         priority values:
                         0 - N.A
                         1 - Lowest priority
                         2 - Higher priority
                         3- ...
                         N - Highest priority
                         where N is NUM_OF_MASTERS


*/
#define SOC_IC_PRIO3_A2NDMARD_W                                      3U
#define SOC_IC_PRIO3_A2NDMARD_M                                      0x00000038U
#define SOC_IC_PRIO3_A2NDMARD_S                                      3U
/*

        Field:           A2NDMAWR
        From..to bits:   6...8
        DefaultValue:    0x0
        Access type:     read-write
        Description:     <Slave-name><Master-name>
                         Set the priority for specific Master transaction toward a specific slave.
                         priority values:
                         0 - N.A
                         1 - Lowest priority
                         2 - Higher priority
                         3- ...
                         N - Highest priority
                         where N is NUM_OF_MASTERS


*/
#define SOC_IC_PRIO3_A2NDMAWR_W                                      3U
#define SOC_IC_PRIO3_A2NDMAWR_M                                      0x000001C0U
#define SOC_IC_PRIO3_A2NDMAWR_S                                      6U
/*

        Field:           A2NHMCU
        From..to bits:   9...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     <Slave-name><Master-name>
                         Set the priority for specific Master transaction toward a specific slave.
                         priority values:
                         0 - N.A
                         1 - Lowest priority
                         2 - Higher priority
                         3- ...
                         N - Highest priority
                         where N is NUM_OF_MASTERS


*/
#define SOC_IC_PRIO3_A2NHMCU_W                                       3U
#define SOC_IC_PRIO3_A2NHMCU_M                                       0x00000E00U
#define SOC_IC_PRIO3_A2NHMCU_S                                       9U
/*

        Field:           A2NHSM
        From..to bits:   12...14
        DefaultValue:    0x0
        Access type:     read-write
        Description:     <Slave-name><Master-name>
                         Set the priority for specific Master transaction toward a specific slave.
                         priority values:
                         0 - N.A
                         1 - Lowest priority
                         2 - Higher priority
                         3- ...
                         N - Highest priority
                         where N is NUM_OF_MASTERS


*/
#define SOC_IC_PRIO3_A2NHSM_W                                        3U
#define SOC_IC_PRIO3_A2NHSM_M                                        0x00007000U
#define SOC_IC_PRIO3_A2NHSM_S                                        12U
/*

        Field:           HMCUHMCU
        From..to bits:   15...17
        DefaultValue:    0x0
        Access type:     read-write
        Description:     <Slave-name><Master-name>
                         Set the priority for specific Master transaction toward a specific slave.
                         priority values:
                         0 - N.A
                         1 - Lowest priority
                         2 - Higher priority
                         3- ...
                         N - Highest priority
                         where N is NUM_OF_MASTERS


*/
#define SOC_IC_PRIO3_HMCUHMCU_W                                      3U
#define SOC_IC_PRIO3_HMCUHMCU_M                                      0x00038000U
#define SOC_IC_PRIO3_HMCUHMCU_S                                      15U
/*

        Field:           CAONWSOCIC
        From..to bits:   18...20
        DefaultValue:    0x0
        Access type:     read-write
        Description:     <Slave-name><Master-name>
                         Set the priority for specific Master transaction toward a specific slave.
                         priority values:
                         0 - N.A
                         1 - Lowest priority
                         2 - Higher priority
                         3- ...
                         N - Highest priority
                         where N is NUM_OF_MASTERS


*/
#define SOC_IC_PRIO3_CAONWSOCIC_W                                    3U
#define SOC_IC_PRIO3_CAONWSOCIC_M                                    0x001C0000U
#define SOC_IC_PRIO3_CAONWSOCIC_S                                    18U
/*

        Field:           CAONHMCU
        From..to bits:   21...23
        DefaultValue:    0x0
        Access type:     read-write
        Description:     <Slave-name><Master-name>
                         Set the priority for specific Master transaction toward a specific slave.
                         priority values:
                         0 - N.A
                         1 - Lowest priority
                         2 - Higher priority
                         3- ...
                         N - Highest priority
                         where N is NUM_OF_MASTERS


*/
#define SOC_IC_PRIO3_CAONHMCU_W                                      3U
#define SOC_IC_PRIO3_CAONHMCU_M                                      0x00E00000U
#define SOC_IC_PRIO3_CAONHMCU_S                                      21U
/*

        Field:           CAONDMARD
        From..to bits:   24...26
        DefaultValue:    0x0
        Access type:     read-write
        Description:     <Slave-name><Master-name>
                         Set the priority for specific Master transaction toward a specific slave.
                         priority values:
                         0 - N.A
                         1 - Lowest priority
                         2 - Higher priority
                         3- ...
                         N - Highest priority
                         where N is NUM_OF_MASTERS


*/
#define SOC_IC_PRIO3_CAONDMARD_W                                     3U
#define SOC_IC_PRIO3_CAONDMARD_M                                     0x07000000U
#define SOC_IC_PRIO3_CAONDMARD_S                                     24U
/*

        Field:           CAONDMAWR
        From..to bits:   27...29
        DefaultValue:    0x0
        Access type:     read-write
        Description:     <Slave-name><Master-name>
                         Set the priority for specific Master transaction toward a specific slave.
                         priority values:
                         0 - N.A
                         1 - Lowest priority
                         2 - Higher priority
                         3- ...
                         N - Highest priority
                         where N is NUM_OF_MASTERS


*/
#define SOC_IC_PRIO3_CAONDMAWR_W                                     3U
#define SOC_IC_PRIO3_CAONDMAWR_M                                     0x38000000U
#define SOC_IC_PRIO3_CAONDMAWR_S                                     27U


/*-----------------------------------REGISTER------------------------------------
    Register name:       PRIO4
    Offset name:         SOC_IC_O_PRIO4
    Relative address:    0x10
    Description:         SOC Interconnect priority registers. Define the priority in which master will be arbitered toward each slave.
    Default Value:       0x00000002

        Field:           CAONI2S
        From..to bits:   0...2
        DefaultValue:    0x2
        Access type:     read-write
        Description:     <Slave-name><Master-name>
                         Set the priority for specific Master transaction toward a specific slave.
                         priority values:
                         0 - N.A
                         1 - Lowest priority
                         2 - Higher priority
                         3- ...
                         N - Highest priority
                         where N is NUM_OF_MASTERS


*/
#define SOC_IC_PRIO4_CAONI2S_W                                       3U
#define SOC_IC_PRIO4_CAONI2S_M                                       0x00000007U
#define SOC_IC_PRIO4_CAONI2S_S                                       0U
/*

        Field:           CAONHSM
        From..to bits:   3...5
        DefaultValue:    0x0
        Access type:     read-write
        Description:     <Slave-name><Master-name>
                         Set the priority for specific Master transaction toward a specific slave.
                         priority values:
                         0 - N.A
                         1 - Lowest priority
                         2 - Higher priority
                         3- ...
                         N - Highest priority
                         where N is NUM_OF_MASTERS


*/
#define SOC_IC_PRIO4_CAONHSM_W                                       3U
#define SOC_IC_PRIO4_CAONHSM_M                                       0x00000038U
#define SOC_IC_PRIO4_CAONHSM_S                                       3U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ERRSTA1
    Offset name:         SOC_IC_O_ERRSTA1
    Relative address:    0x14
    Description:         OCP Slave serror and Time-out Status 1.

                        status bits when ocp slave response with serror
                        clear on write
                        sticky - catch the first error, until register is cleared to 0
    Default Value:       0x00000000

        Field:           STA1
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     status bits when ocp slave response with serror
                         clear on write
                         sticky - catch the first error, until register is cleared to 0

                         [31:0] - maddr
                         *note - can only clear on write to 32'b0
                         writing 1 byte will clear all 4 bytes

*/
#define SOC_IC_ERRSTA1_STA1_W                                        32U
#define SOC_IC_ERRSTA1_STA1_M                                        0xFFFFFFFFU
#define SOC_IC_ERRSTA1_STA1_S                                        0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ERRSTA2
    Offset name:         SOC_IC_O_ERRSTA2
    Relative address:    0x18
    Description:         OCP Slave serror and Time-out Status 2.

    Default Value:       0x00000000

        Field:           STA2
        From..to bits:   0...9
        DefaultValue:    0x0
        Access type:     read-write
        Description:     status bits when ocp slave response with serror or timeout:
                         clear on write
                         sticky - catch the first error, until register is cleared to 0
                         for serror and timeout handeling:
                         [9:6] cause
                         [5:4] mcmd - command type: 2=RD ; 1=WR
                         [3:0] masterid
                         cause mapping:
                         0 - masters
                         1 - core aon
                         2 - hsm
                         3 - host xip
                         4 - host dma
                         5 - host mcu
                         6 - shared periph
                         7 - app2nab
                         8 - core wsocic
                         9 - l3 slaves
                         if cuase is 'masters' - masterid mapped as it mapped in [TOMSTCFG.SEL].
                         else - masterid mapping:
                         0   - M33NS
                         1   - M33S
                         6   - Core (wsoc_ic)
                         8   - I2S/HSM M33NS access
                         9   - I2S/HSM M33S access
                         10 - I2S/HSM Core access
                         12 - DMA M33NS access
                         13 - DMA M33S access
                         14 - DMA Core access

                         *note - can only clear on write to 10'b0
                         writing 1 byte will clear all 2 bytes

*/
#define SOC_IC_ERRSTA2_STA2_W                                        10U
#define SOC_IC_ERRSTA2_STA2_M                                        0x000003FFU
#define SOC_IC_ERRSTA2_STA2_S                                        0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ADDRCFG1
    Offset name:         SOC_IC_O_ADDRCFG1
    Relative address:    0x1C
    Description:         Address Watch Configuration 1.
    Default Value:       NA

        Field:           SEL
        From..to bits:   0...3
        DefaultValue:    NA
        Access type:     read-write
        Description:     select which slave port of ocp_ic is checked in  address-watch:
                         0 -  core_aon
                         1 -  hsm
                         2 -  host_xip_cfg
                         3 -  host_dma
                         4 -  host_mcu
                         5 -  shared_periph (all shared peripheral I2C,UART,I2S,SDMMC,SPI,CAN,PDM,GPTIMERS,AFA,ADC,SDIO)
                         6 -  app2nab
                         7 -  core_wsocic
                         8 -  all l3 peripherals under bridge (COEX,IOMUX,PRCM,SCRTCHPAD,PRCM_AON,CKM,FUSE_FARM,GPADC_CTRL,DEBUGSS,
                               SOC_IC,SOC_AON_SECURED/NON_SECURED,RTC,OCLA,MEMSS_GLOBALPORT,HOST_AON,SYSREASOURCES,SYSTIMER)


*/
#define SOC_IC_ADDRCFG1_SEL_W                                        4U
#define SOC_IC_ADDRCFG1_SEL_M                                        0x0000000FU
#define SOC_IC_ADDRCFG1_SEL_S                                        0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ADDRCFG2
    Offset name:         SOC_IC_O_ADDRCFG2
    Relative address:    0x20
    Description:         Address Watch Configuration 2.
    Default Value:       NA

        Field:           LOW
        From..to bits:   0...31
        DefaultValue:    NA
        Access type:     read-write
        Description:     lower maddr threshold for address-watch
                         addr_hit = (maddr >= thr_low) & (maddr <= thr_high)

*/
#define SOC_IC_ADDRCFG2_LOW_W                                        32U
#define SOC_IC_ADDRCFG2_LOW_M                                        0xFFFFFFFFU
#define SOC_IC_ADDRCFG2_LOW_S                                        0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ADDRCFG3
    Offset name:         SOC_IC_O_ADDRCFG3
    Relative address:    0x24
    Description:         Address Watch Configuration 3.
    Default Value:       NA

        Field:           HIGH
        From..to bits:   0...31
        DefaultValue:    NA
        Access type:     read-write
        Description:     upper maddr threshold for address-watch
                         addr_hit = (maddr >= thr_low) & (maddr <= thr_high)

*/
#define SOC_IC_ADDRCFG3_HIGH_W                                       32U
#define SOC_IC_ADDRCFG3_HIGH_M                                       0xFFFFFFFFU
#define SOC_IC_ADDRCFG3_HIGH_S                                       0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ADDRCFG4
    Offset name:         SOC_IC_O_ADDRCFG4
    Relative address:    0x28
    Description:         Address Watch Configuration 4.
    Default Value:       NA

        Field:           MSTIDWR
        From..to bits:   0...15
        DefaultValue:    NA
        Access type:     read-write
        Description:     each bit enables check on MCMD=WR per MASTERID
                         for example value of 0x0120 will enable check of masterid=5 and masterid=8
                         if check_wr=0x0000 and check_rd=0x0000 then the clock for address-watch is disabled locally to save power

*/
#define SOC_IC_ADDRCFG4_MSTIDWR_W                                    16U
#define SOC_IC_ADDRCFG4_MSTIDWR_M                                    0x0000FFFFU
#define SOC_IC_ADDRCFG4_MSTIDWR_S                                    0U
/*

        Field:           MSTIDRD
        From..to bits:   16...31
        DefaultValue:    NA
        Access type:     read-write
        Description:     each bit enables check on MCMD=RD per MASTERID
                         for example value of 0x0120 will enable check of masterid=5 and masterid=8
                         if check_wr=0x0000 and check_rd=0x0000 then the clock for address-watch is disabled locally to save power

*/
#define SOC_IC_ADDRCFG4_MSTIDRD_W                                    16U
#define SOC_IC_ADDRCFG4_MSTIDRD_M                                    0xFFFF0000U
#define SOC_IC_ADDRCFG4_MSTIDRD_S                                    16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ADDRSTA1
    Offset name:         SOC_IC_O_ADDRSTA1
    Relative address:    0x2C
    Description:         Address Watch Status 1.
    Default Value:       0x00000000

        Field:           STA1
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     keep when hit - Clear on Write
                         [31:0] - maddr


*/
#define SOC_IC_ADDRSTA1_STA1_W                                       32U
#define SOC_IC_ADDRSTA1_STA1_M                                       0xFFFFFFFFU
#define SOC_IC_ADDRSTA1_STA1_S                                       0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ADDRSTA2
    Offset name:         SOC_IC_O_ADDRSTA2
    Relative address:    0x30
    Description:         Address Watch Status 2.
    Default Value:       0x00000000

        Field:           STA2
        From..to bits:   0...4
        DefaultValue:    0x0
        Access type:     read-write
        Description:     keep when hit - Clear on Write
                         [4]     - command type: 0=RD ; 1=WR
                         [3:0] - masterid

                         masterid mapping:
                         0   - M33NS
                         1   - M33S
                         6   - Core (wsoc_ic)
                         8   - I2S/HSM M33NS access
                         9   - I2S/HSM M33S access
                         10 - I2S/HSM Core access
                         12 - DMA M33NS access
                         13 - DMA M33S access
                         14 - DMA Core access

*/
#define SOC_IC_ADDRSTA2_STA2_W                                       5U
#define SOC_IC_ADDRSTA2_STA2_M                                       0x0000001FU
#define SOC_IC_ADDRSTA2_STA2_S                                       0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       TOMSTCFG
    Offset name:         SOC_IC_O_TOMSTCFG
    Relative address:    0x34
    Description:         Time-out Masters Configuration.
    Default Value:       0x00010084

        Field:           VAL
        From..to bits:   4...8
        DefaultValue:    0x8
        Access type:     read-write
        Description:     value for timeout for all slaves:
                         valid value - 0x0- 0x1F

                         if value is 0 timeout feature is disabled for all slaves

                         Granulation is double word (64b): 1 - means 16 clocks period, 2 - means 32 clocks period...

                         in h/w the value in FIELD is shifted left 4 times (x16). example: 0x08 =>  0x80 (8 means 128)


*/
#define SOC_IC_TOMSTCFG_VAL_W                                        5U
#define SOC_IC_TOMSTCFG_VAL_M                                        0x000001F0U
#define SOC_IC_TOMSTCFG_VAL_S                                        4U
/*

        Field:           SEL
        From..to bits:   10...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     select master for timeout by masterid.

                         0x0. M33NS
                         0x1. M33S
                         0x6. Core (wsoc_ic)
                         0x8. I2S/HSM M33NS access
                         0x9. I2S/HSM M33S access
                         0xA. I2S/HSM Core access
                         0xC. DMA M33NS access
                         0xD. DMA M33S access
                         0xE. DMA Core access


*/
#define SOC_IC_TOMSTCFG_SEL_W                                        4U
#define SOC_IC_TOMSTCFG_SEL_M                                        0x00003C00U
#define SOC_IC_TOMSTCFG_SEL_S                                        10U


/*-----------------------------------REGISTER------------------------------------
    Register name:       TOSLVCFG
    Offset name:         SOC_IC_O_TOSLVCFG
    Relative address:    0x38
    Description:         Time-out Slave Configuration.
    Default Value:       0x00010088

        Field:           VAL
        From..to bits:   4...8
        DefaultValue:    0x8
        Access type:     read-write
        Description:     value for timeout for all slaves:
                         valid value - 0x0- 0x1F

                         if value is 0 timeout feature is disabled for all slaves

                         Granulation is double word (64b): 1 - means 16 clocks period, 2 - means 32 clocks period...

                         in h/w the value in FIELD is shifted left 4 times (x16). example: 0x08 =>  0x80 (8 means 128)


*/
#define SOC_IC_TOSLVCFG_VAL_W                                        5U
#define SOC_IC_TOSLVCFG_VAL_M                                        0x000001F0U
#define SOC_IC_TOSLVCFG_VAL_S                                        4U

#endif /* __HW_SOC_IC_H__*/
