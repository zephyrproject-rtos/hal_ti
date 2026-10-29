/******************************************************************************
*  Filename:       hw_coex.h
*
*  Description:    Defines and prototypes for the COEX peripheral.
*
*  Copyright (c) 2023, Texas Instruments Incorporated
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
#ifndef __HW_COEX_H__
#define __HW_COEX_H__
/*-------------------------------------------------------------------------------

This section defines the register offsets of the COEX component

--------------------------------------------------------------------------------- */

//General COEX Configurations
#define COEX_O_GENCFG                                                0x00000000U

//Wifi Configuration
#define COEX_O_WIFICFG                                               0x00000004U

//BLE Configuration
#define COEX_O_BLECFG                                                0x00000008U

//SOC Configuration
#define COEX_O_EXTSOCCFG                                             0x0000000CU

//BLE High Priority Rx
#define COEX_O_BLEHIPRIRX                                            0x00000010U

//BLE Low Priority Rx
#define COEX_O_BLELOPRIRX                                            0x00000014U

//BLE High Priority Tx
#define COEX_O_BLEHIPRITX                                            0x00000018U

//BLE Low Priority Tx
#define COEX_O_BLELOPRITX                                            0x0000001CU

//SOC High Priority
#define COEX_O_SOCHIPRI                                              0x00000020U

//SOC Low Priority
#define COEX_O_SOCLOPRI                                              0x00000024U

//Tie Breaker
#define COEX_O_TIEBREAKER                                            0x00000028U

//WIFI MIN GRANT TIME:
#define COEX_O_WIFIMINGT                                             0x0000002CU

//BLE MIN GRANT TIME:
#define COEX_O_BLEMINGT                                              0x00000030U

//SOC MIN GRANT TIME:
#define COEX_O_SOCMINGT                                              0x00000034U

//SW Grant Override
#define COEX_O_SWGRNTOVR                                             0x00000038U

//BLE Max Grant Time
#define COEX_O_BLEMAXGT                                              0x0000003CU

//SOC Max Grant Time
#define COEX_O_SOCMAXGT                                              0x00000040U

//BLE T2 Time
#define COEX_O_BLET2TIME                                             0x00000044U

//SOC T2 Time
#define COEX_O_SOCT2TIME                                             0x00000048U

//WIFI to BLE Grant Delay
#define COEX_O_W2BDLY                                                0x0000004CU

//WIFI to SOC Grant Delay
#define COEX_O_W2SDLY                                                0x00000050U

//BLE to SOC Grant Delay
#define COEX_O_B2SDLY                                                0x00000054U

//BLE to WIFI Grant Delay
#define COEX_O_B2WDLY                                                0x00000058U

//SOC to WIFI Grant Delay
#define COEX_O_S2WDLY                                                0x0000005CU

//SOC to BLE Grant Delay
#define COEX_O_S2BDLY                                                0x00000060U

//Debug Report Register
#define COEX_O_DBGREP                                                0x00000064U

//WIFI Request and Grant Log Register
#define COEX_O_WIFILOG                                               0x00000068U

//BLE Request and Grant Log Register
#define COEX_O_BLELOG                                                0x0000006CU

//SOC Request and Grant Log Register
#define COEX_O_SOCLOG                                                0x00000070U

//WIFI Priority Reject Log Register
#define COEX_O_WIFIPRIREJ                                            0x00000078U

//SOC Priority Reject Log Register
#define COEX_O_SOCPRIREJ                                             0x0000007CU

//BLE Priority Reject Log Register
#define COEX_O_BLEPRIREJ                                             0x00000080U

//Timestamp Register
#define COEX_O_TIMESTAMP                                             0x00000084U

//WIFI Grant During Dual Antenna Log Register
#define COEX_O_WIFIANTLOG                                            0x00000088U

//IRQ Event Masking
#define COEX_O_IRQEVTMSK                                             0x0000008CU

//Antenna Control Configuration 1
#define COEX_O_ANTCTLCFG1                                            0x000000C0U

//Antenna Control Configuration 2
#define COEX_O_ANTCTLCFG2                                            0x000000C4U

//Antenna Control Status
#define COEX_O_ANTCTLSTA                                             0x000000C8U



/*-----------------------------------REGISTER------------------------------------
    Register name:       GENCFG
    Offset name:         COEX_O_GENCFG
    Relative address:    0x0
    Description:         General COEX Configurations.

                        This register is a static configuration.
    Default Value:       0x00000002

        Field:           EN
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This bit configuration is available to enable or disable COEX. Enable --> 1; Disable --> 0.

*/
#define COEX_GENCFG_EN                                               0x00000001U
#define COEX_GENCFG_EN_M                                             0x00000001U
#define COEX_GENCFG_EN_S                                             0U
/*

        Field:           DEFGRNTDIS
        From..to bits:   1...2
        DefaultValue:    0x1
        Access type:     read-write
        Description:     def grant when coex disabled:
                         This bit configuration is available to select the entity which has the grant when COEX is disabled. 00 --> Wifi; 01 --> BLE, 10 --> SOC, 11 --> invalid configuration.

*/
#define COEX_GENCFG_DEFGRNTDIS_W                                     2U
#define COEX_GENCFG_DEFGRNTDIS_M                                     0x00000006U
#define COEX_GENCFG_DEFGRNTDIS_S                                     1U
/*

        Field:           DEFGRTNREQ
        From..to bits:   3...4
        DefaultValue:    0x0
        Access type:     read-write
        Description:     def grant when no req:
                         This bit configuration is available to select the entity which has the grant when there is no request from any entity.00 --> Wifi; 01 --> BLE, 10 --> SOC, 11 --> Wifi.

*/
#define COEX_GENCFG_DEFGRTNREQ_W                                     2U
#define COEX_GENCFG_DEFGRTNREQ_M                                     0x00000018U
#define COEX_GENCFG_DEFGRTNREQ_S                                     3U
/*

        Field:           DEBREPEN
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     read-write
        Description:     debug reporting enable:
                         This bit configuration is available to enable or disable the debug reporting.0 --> No IRQ is generated; 1 --> Debug Mode enable. IRQ is generated whenever there is change in grant state.

*/
#define COEX_GENCFG_DEBREPEN                                         0x00000020U
#define COEX_GENCFG_DEBREPEN_M                                       0x00000020U
#define COEX_GENCFG_DEBREPEN_S                                       5U
/*

        Field:           FREQ40N80
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This bit configuration is available to select the freq. at which COEX is operating. 1 --> 80 MHz; 0 --> 40 MHz.

*/
#define COEX_GENCFG_FREQ40N80                                        0x00000040U
#define COEX_GENCFG_FREQ40N80_M                                      0x00000040U
#define COEX_GENCFG_FREQ40N80_S                                      6U


/*-----------------------------------REGISTER------------------------------------
    Register name:       WIFICFG
    Offset name:         COEX_O_WIFICFG
    Relative address:    0x4
    Description:         Wifi Configuration.

                        This register is available is to program Wifi related general configuration. This register is static configuration.
    Default Value:       0x00000001

        Field:           WIFIEN
        From..to bits:   0...0
        DefaultValue:    0x1
        Access type:     read-write
        Description:     This bit configuration is available to indicate if Wifi is enabled in the design or not. 0 --> Wifi disabled; 1 --> Wifi enabled..

*/
#define COEX_WIFICFG_WIFIEN                                          0x00000001U
#define COEX_WIFICFG_WIFIEN_M                                        0x00000001U
#define COEX_WIFICFG_WIFIEN_S                                        0U
/*

        Field:           WIFIGRTPOL
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This bit configuration is available to select Wifi Grant Polarity. 1 --> Default Polarity/Active Low; 0 --> Reverse Polarity/Active High.

*/
#define COEX_WIFICFG_WIFIGRTPOL                                      0x00000002U
#define COEX_WIFICFG_WIFIGRTPOL_M                                    0x00000002U
#define COEX_WIFICFG_WIFIGRTPOL_S                                    1U
/*

        Field:           ALTBNDBYP
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     wifi alt band input bypass:
                         This bit configuration is available to bypass Wifi alt band input. 1 --> Bypass wifi alt band input; 0 --> Do not bypass wifi alt band input.

*/
#define COEX_WIFICFG_ALTBNDBYP                                       0x00000004U
#define COEX_WIFICFG_ALTBNDBYP_M                                     0x00000004U
#define COEX_WIFICFG_ALTBNDBYP_S                                     2U
/*

        Field:           RXBYP
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     wifi rx only input bypass:
                         This bit configuration is available to bypass Wifi RX only input. 1 --> Bypass wifi rx only input; 0 --> Do not bypass wifi rx only input.

*/
#define COEX_WIFICFG_RXBYP                                           0x00000008U
#define COEX_WIFICFG_RXBYP_M                                         0x00000008U
#define COEX_WIFICFG_RXBYP_S                                         3U
/*

        Field:           ALTBNDBYPV
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     read-write
        Description:     wifi alt band input bypass val:
                         This bit configuration is available to configure Wifi_alt_band value.

*/
#define COEX_WIFICFG_ALTBNDBYPV                                      0x00000010U
#define COEX_WIFICFG_ALTBNDBYPV_M                                    0x00000010U
#define COEX_WIFICFG_ALTBNDBYPV_S                                    4U
/*

        Field:           RXBYPV
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     read-write
        Description:     wifi rx only input bypass val:
                         This bit configuration is available to bypass Wifi_RX_only value.

*/
#define COEX_WIFICFG_RXBYPV                                          0x00000020U
#define COEX_WIFICFG_RXBYPV_M                                        0x00000020U
#define COEX_WIFICFG_RXBYPV_S                                        5U


/*-----------------------------------REGISTER------------------------------------
    Register name:       BLECFG
    Offset name:         COEX_O_BLECFG
    Relative address:    0x8
    Description:         BLE Configuration.

                        This register is available is to program BLE related general configuration. This register is static configuration.
    Default Value:       0x00000001

        Field:           BLEEN
        From..to bits:   0...0
        DefaultValue:    0x1
        Access type:     read-write
        Description:     This bit configuration is available to indicate if BLE is enabled in the design or not. 0 --> BLE disabled; 1 --> BLE enabled..

*/
#define COEX_BLECFG_BLEEN                                            0x00000001U
#define COEX_BLECFG_BLEEN_M                                          0x00000001U
#define COEX_BLECFG_BLEEN_S                                          0U
/*

        Field:           BLEGRNTPOL
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This bit configuration is available to select BLE Grant Polarity. 1 --> Default Polarity/Active Low; 0 --> Reverse Polarity/Active High.

*/
#define COEX_BLECFG_BLEGRNTPOL                                       0x00000002U
#define COEX_BLECFG_BLEGRNTPOL_M                                     0x00000002U
#define COEX_BLECFG_BLEGRNTPOL_S                                     1U
/*

        Field:           PTASGNLM
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     ble pta signalling mode:
                         This bit configuration is available to select if BLE_TX and BLE_RX are to be bypassed. 1 --> Bypass BLE_TX and BLE_RX; 0 --> Do not bypass BLE_TX and BLE_RX input.

*/
#define COEX_BLECFG_PTASGNLM                                         0x00000004U
#define COEX_BLECFG_PTASGNLM_M                                       0x00000004U
#define COEX_BLECFG_PTASGNLM_S                                       2U
/*

        Field:           TXBYPV
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     ble tx bypass val:
                         This bit configuration is available to configure BLE_TX value. This bit takes effect when mem_ble_pta_signalling_mode is set to 1.

*/
#define COEX_BLECFG_TXBYPV                                           0x00000008U
#define COEX_BLECFG_TXBYPV_M                                         0x00000008U
#define COEX_BLECFG_TXBYPV_S                                         3U
/*

        Field:           RXBYPV
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     read-write
        Description:     ble rx bypass val:
                         This bit configuration is available to configure BLE_RX value. This bit takes effect when mem_ble_pta_signalling_mode is set to 1.

*/
#define COEX_BLECFG_RXBYPV                                           0x00000010U
#define COEX_BLECFG_RXBYPV_M                                         0x00000010U
#define COEX_BLECFG_RXBYPV_S                                         4U


/*-----------------------------------REGISTER------------------------------------
    Register name:       EXTSOCCFG
    Offset name:         COEX_O_EXTSOCCFG
    Relative address:    0xC
    Description:         SOC Configuration.

                        This register is available is to program EXT SOC related general configuration. This register is a static configuration.
    Default Value:       0x00000003

        Field:           SOCEN
        From..to bits:   0...0
        DefaultValue:    0x1
        Access type:     read-write
        Description:     This bit configuration is available to indicate if SOC is enabled in the design or not. 0 --> SOC disabled; 1 --> SOC enabled..

*/
#define COEX_EXTSOCCFG_SOCEN                                         0x00000001U
#define COEX_EXTSOCCFG_SOCEN_M                                       0x00000001U
#define COEX_EXTSOCCFG_SOCEN_S                                       0U
/*

        Field:           PTASGNLM
        From..to bits:   1...2
        DefaultValue:    0x1
        Access type:     read-write
        Description:     soc pta signalling mode:
                         This bit configuration is available to select the Ext SOC PTA signalling mode. 00 --> Reserved; 01 --> 1-wire, 10 --> 2-wires, 11 --> 3-wires.

*/
#define COEX_EXTSOCCFG_PTASGNLM_W                                    2U
#define COEX_EXTSOCCFG_PTASGNLM_M                                    0x00000006U
#define COEX_EXTSOCCFG_PTASGNLM_S                                    1U
/*

        Field:           REQPOL
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This bit configuration is available to select Ext SOC Request Polarity. 1 --> Default Polarity/Active High; 0 --> Reverse Polarity/Active Low.

*/
#define COEX_EXTSOCCFG_REQPOL                                        0x00000008U
#define COEX_EXTSOCCFG_REQPOL_M                                      0x00000008U
#define COEX_EXTSOCCFG_REQPOL_S                                      3U
/*

        Field:           PRIPOL
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This bit configuration is available to select Ext SOC Priority Polarity. 1 --> Default Polarity/Active High; 0 --> Reverse Polarity/Active Low.

*/
#define COEX_EXTSOCCFG_PRIPOL                                        0x00000010U
#define COEX_EXTSOCCFG_PRIPOL_M                                      0x00000010U
#define COEX_EXTSOCCFG_PRIPOL_S                                      4U
/*

        Field:           GRNTPOL
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This bit configuration is available to select SOC Grant Polarity. 1 --> Default Polarity/Active Low; 0 --> Reverse Polarity/Active High.

*/
#define COEX_EXTSOCCFG_GRNTPOL                                       0x00000020U
#define COEX_EXTSOCCFG_GRNTPOL_M                                     0x00000020U
#define COEX_EXTSOCCFG_GRNTPOL_S                                     5U
/*

        Field:           GRNTREBYP
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-write
        Description:     soc grant renew bypass:
                         This bit configuration is available to bypass need to renew soc grant. 1 --> Bypass SOC grant renew; 0 --> SOC needs to renew grant.

*/
#define COEX_EXTSOCCFG_GRNTREBYP                                     0x00000040U
#define COEX_EXTSOCCFG_GRNTREBYP_M                                   0x00000040U
#define COEX_EXTSOCCFG_GRNTREBYP_S                                   6U
/*

        Field:           REQSIGDET
        From..to bits:   7...8
        DefaultValue:    0x0
        Access type:     read-write
        Description:     This bit configuration is available to select detection mechanism for SOC request. 00 --> Rise edge detection (L -> H)  ; 01 --> Fall edge detection (H -> L)  ; 10 --> Level detection (active high)  ; 11 ->  level detection (active low).

*/
#define COEX_EXTSOCCFG_REQSIGDET_W                                   2U
#define COEX_EXTSOCCFG_REQSIGDET_M                                   0x00000180U
#define COEX_EXTSOCCFG_REQSIGDET_S                                   7U


/*-----------------------------------REGISTER------------------------------------
    Register name:       BLEHIPRIRX
    Offset name:         COEX_O_BLEHIPRIRX
    Relative address:    0x10
    Description:         BLE High Priority Rx.

                        This Priority register selected when BLE Priority is high and BLE_RX is asserted. This register value should not be changed when BLE request is asserted.
    Default Value:       NA

        Field:           BLEHIPRIRX
        From..to bits:   0...3
        DefaultValue:    NA
        Access type:     read-write
        Description:     Priority levels can be 1 to 15. 0 level indicates no request from BLE.

*/
#define COEX_BLEHIPRIRX_BLEHIPRIRX_W                                 4U
#define COEX_BLEHIPRIRX_BLEHIPRIRX_M                                 0x0000000FU
#define COEX_BLEHIPRIRX_BLEHIPRIRX_S                                 0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       BLELOPRIRX
    Offset name:         COEX_O_BLELOPRIRX
    Relative address:    0x14
    Description:         BLE Low Priority Rx.

                        This Priority register selected when BLE Priority is low and BLE_RX is asserted. This register value should not be changed when BLE request is asserted.
    Default Value:       NA

        Field:           BLELOPRIRX
        From..to bits:   0...3
        DefaultValue:    NA
        Access type:     read-write
        Description:     Priority levels can be 1 to 15. 0 level indicates no request from BLE.

*/
#define COEX_BLELOPRIRX_BLELOPRIRX_W                                 4U
#define COEX_BLELOPRIRX_BLELOPRIRX_M                                 0x0000000FU
#define COEX_BLELOPRIRX_BLELOPRIRX_S                                 0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       BLEHIPRITX
    Offset name:         COEX_O_BLEHIPRITX
    Relative address:    0x18
    Description:         BLE High Priority Tx.

                        This Priority register selected when BLE Priority is high and BLE_TX is asserted. This register value should not be changed when BLE request is asserted.
    Default Value:       NA

        Field:           BLEHIPRITX
        From..to bits:   0...3
        DefaultValue:    NA
        Access type:     read-write
        Description:     Priority levels can be 1 to 15. 0 level indicates no request from BLE.

*/
#define COEX_BLEHIPRITX_BLEHIPRITX_W                                 4U
#define COEX_BLEHIPRITX_BLEHIPRITX_M                                 0x0000000FU
#define COEX_BLEHIPRITX_BLEHIPRITX_S                                 0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       BLELOPRITX
    Offset name:         COEX_O_BLELOPRITX
    Relative address:    0x1C
    Description:         BLE Low Priority Tx.

                        This Priority register selected when BLE Priority is low and BLE_TX is asserted. This register value should not be changed when BLE request is asserted.
    Default Value:       NA

        Field:           BLELOPRITX
        From..to bits:   0...3
        DefaultValue:    NA
        Access type:     read-write
        Description:     Priority levels can be 1 to 15. 0 level indicates no request from BLE.

*/
#define COEX_BLELOPRITX_BLELOPRITX_W                                 4U
#define COEX_BLELOPRITX_BLELOPRITX_M                                 0x0000000FU
#define COEX_BLELOPRITX_BLELOPRITX_S                                 0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       SOCHIPRI
    Offset name:         COEX_O_SOCHIPRI
    Relative address:    0x20
    Description:         SOC High Priority.

                        This Priority register selected when SOC Priority is high. This register value should not be changed when SOC request is asserted.
    Default Value:       NA

        Field:           SOCHIPRI
        From..to bits:   0...3
        DefaultValue:    NA
        Access type:     read-write
        Description:     Priority levels can be 1 to 15. 0 level indicates no request from SOC.

*/
#define COEX_SOCHIPRI_SOCHIPRI_W                                     4U
#define COEX_SOCHIPRI_SOCHIPRI_M                                     0x0000000FU
#define COEX_SOCHIPRI_SOCHIPRI_S                                     0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       SOCLOPRI
    Offset name:         COEX_O_SOCLOPRI
    Relative address:    0x24
    Description:         SOC Low Priority.

                        This Priority register selected when SOC Priority is low. This register value should not be changed when SOC request is asserted.
    Default Value:       NA

        Field:           SOCLOPRI
        From..to bits:   0...3
        DefaultValue:    NA
        Access type:     read-write
        Description:     Priority levels can be 1 to 15. 0 level indicates no request from SOC.

*/
#define COEX_SOCLOPRI_SOCLOPRI_W                                     4U
#define COEX_SOCLOPRI_SOCLOPRI_M                                     0x0000000FU
#define COEX_SOCLOPRI_SOCLOPRI_S                                     0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       TIEBREAKER
    Offset name:         COEX_O_TIEBREAKER
    Relative address:    0x28
    Description:         Tie Breaker.

                        This register is available is to program entity priority which comes into effect when there is a tie between contesting entities. This register is a static configuration. The values in all the three fields need to be unique.
    Default Value:       0x00000002

        Field:           WIFI
        From..to bits:   0...1
        DefaultValue:    0x2
        Access type:     read-write
        Description:     Priority value for Wifi.

*/
#define COEX_TIEBREAKER_WIFI_W                                       2U
#define COEX_TIEBREAKER_WIFI_M                                       0x00000003U
#define COEX_TIEBREAKER_WIFI_S                                       0U
/*

        Field:           BLE
        From..to bits:   2...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Priority value for BLE.

*/
#define COEX_TIEBREAKER_BLE_W                                        2U
#define COEX_TIEBREAKER_BLE_M                                        0x0000000CU
#define COEX_TIEBREAKER_BLE_S                                        2U
/*

        Field:           SOC
        From..to bits:   4...5
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Priority value for SOC.

*/
#define COEX_TIEBREAKER_SOC_W                                        2U
#define COEX_TIEBREAKER_SOC_M                                        0x00000030U
#define COEX_TIEBREAKER_SOC_S                                        4U


/*-----------------------------------REGISTER------------------------------------
    Register name:       WIFIMINGT
    Offset name:         COEX_O_WIFIMINGT
    Relative address:    0x2C
    Description:         WIFI MIN GRANT TIME:
                        This register is available is to program wifi minimum grant time. This register is static configuration.
    Default Value:       NA

        Field:           VAL
        From..to bits:   0...12
        DefaultValue:    NA
        Access type:     read-write
        Description:     Wifi min grant time.

*/
#define COEX_WIFIMINGT_VAL_W                                         13U
#define COEX_WIFIMINGT_VAL_M                                         0x00001FFFU
#define COEX_WIFIMINGT_VAL_S                                         0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       BLEMINGT
    Offset name:         COEX_O_BLEMINGT
    Relative address:    0x30
    Description:         BLE MIN GRANT TIME:
                        This register is available is to program ble minimum grant time. This register is static configuration.
    Default Value:       NA

        Field:           VAL
        From..to bits:   0...12
        DefaultValue:    NA
        Access type:     read-write
        Description:     BLE min grant time.

*/
#define COEX_BLEMINGT_VAL_W                                          13U
#define COEX_BLEMINGT_VAL_M                                          0x00001FFFU
#define COEX_BLEMINGT_VAL_S                                          0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       SOCMINGT
    Offset name:         COEX_O_SOCMINGT
    Relative address:    0x34
    Description:         SOC MIN GRANT TIME:
                        This register is available is to program soc minimum grant time. This register is static configuration.
    Default Value:       NA

        Field:           VAL
        From..to bits:   0...12
        DefaultValue:    NA
        Access type:     read-write
        Description:     SOC min grant time.

*/
#define COEX_SOCMINGT_VAL_W                                          13U
#define COEX_SOCMINGT_VAL_M                                          0x00001FFFU
#define COEX_SOCMINGT_VAL_S                                          0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       SWGRNTOVR
    Offset name:         COEX_O_SWGRNTOVR
    Relative address:    0x38
    Description:         SW Grant Override.

                        This register is available to override the grant via SW.
    Default Value:       NA

        Field:           WIFICTL
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     read-write
        Description:     wifi grant override control.

*/
#define COEX_SWGRNTOVR_WIFICTL                                       0x00000001U
#define COEX_SWGRNTOVR_WIFICTL_M                                     0x00000001U
#define COEX_SWGRNTOVR_WIFICTL_S                                     0U
/*

        Field:           WIFIVAL
        From..to bits:   1...1
        DefaultValue:    NA
        Access type:     read-write
        Description:     wifi grant override value

*/
#define COEX_SWGRNTOVR_WIFIVAL                                       0x00000002U
#define COEX_SWGRNTOVR_WIFIVAL_M                                     0x00000002U
#define COEX_SWGRNTOVR_WIFIVAL_S                                     1U
/*

        Field:           SOCCTL
        From..to bits:   2...2
        DefaultValue:    NA
        Access type:     read-write
        Description:     soc grant override control.

*/
#define COEX_SWGRNTOVR_SOCCTL                                        0x00000004U
#define COEX_SWGRNTOVR_SOCCTL_M                                      0x00000004U
#define COEX_SWGRNTOVR_SOCCTL_S                                      2U
/*

        Field:           SOCVAL
        From..to bits:   3...3
        DefaultValue:    NA
        Access type:     read-write
        Description:     soc grant override value.

*/
#define COEX_SWGRNTOVR_SOCVAL                                        0x00000008U
#define COEX_SWGRNTOVR_SOCVAL_M                                      0x00000008U
#define COEX_SWGRNTOVR_SOCVAL_S                                      3U
/*

        Field:           BLECTL
        From..to bits:   4...4
        DefaultValue:    NA
        Access type:     read-write
        Description:     BLE grant override control.

*/
#define COEX_SWGRNTOVR_BLECTL                                        0x00000010U
#define COEX_SWGRNTOVR_BLECTL_M                                      0x00000010U
#define COEX_SWGRNTOVR_BLECTL_S                                      4U
/*

        Field:           BLEVAL
        From..to bits:   5...5
        DefaultValue:    NA
        Access type:     read-write
        Description:     BLE grant override value.

*/
#define COEX_SWGRNTOVR_BLEVAL                                        0x00000020U
#define COEX_SWGRNTOVR_BLEVAL_M                                      0x00000020U
#define COEX_SWGRNTOVR_BLEVAL_S                                      5U


/*-----------------------------------REGISTER------------------------------------
    Register name:       BLEMAXGT
    Offset name:         COEX_O_BLEMAXGT
    Relative address:    0x3C
    Description:         BLE Max Grant Time.

                        This register is available is to program ble maximum grant time. This register is static configuration.
    Default Value:       NA

        Field:           VAL
        From..to bits:   0...13
        DefaultValue:    NA
        Access type:     read-write
        Description:     BLE max grant time.

*/
#define COEX_BLEMAXGT_VAL_W                                          14U
#define COEX_BLEMAXGT_VAL_M                                          0x00003FFFU
#define COEX_BLEMAXGT_VAL_S                                          0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       SOCMAXGT
    Offset name:         COEX_O_SOCMAXGT
    Relative address:    0x40
    Description:         SOC Max Grant Time.

                        This register is available is to program soc maximum grant time. This register is static configuration.
    Default Value:       NA

        Field:           VAL
        From..to bits:   0...13
        DefaultValue:    NA
        Access type:     read-write
        Description:     SOC max grant time.

*/
#define COEX_SOCMAXGT_VAL_W                                          14U
#define COEX_SOCMAXGT_VAL_M                                          0x00003FFFU
#define COEX_SOCMAXGT_VAL_S                                          0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       BLET2TIME
    Offset name:         COEX_O_BLET2TIME
    Relative address:    0x44
    Description:         BLE T2 Time.

                        This register is available is to program ble T2 time. This register is static configuration.
    Default Value:       NA

        Field:           VAL
        From..to bits:   0...5
        DefaultValue:    NA
        Access type:     read-write
        Description:     BLE T2 time.

*/
#define COEX_BLET2TIME_VAL_W                                         6U
#define COEX_BLET2TIME_VAL_M                                         0x0000003FU
#define COEX_BLET2TIME_VAL_S                                         0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       SOCT2TIME
    Offset name:         COEX_O_SOCT2TIME
    Relative address:    0x48
    Description:         SOC T2 Time.

                        This register is available is to program soc T2 time. This register is static configuration.
    Default Value:       NA

        Field:           VAL
        From..to bits:   0...5
        DefaultValue:    NA
        Access type:     read-write
        Description:     SOC T2 time.

*/
#define COEX_SOCT2TIME_VAL_W                                         6U
#define COEX_SOCT2TIME_VAL_M                                         0x0000003FU
#define COEX_SOCT2TIME_VAL_S                                         0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       W2BDLY
    Offset name:         COEX_O_W2BDLY
    Relative address:    0x4C
    Description:         WIFI to BLE Grant Delay.

                        This register is available is to program wifi to ble grant delay time. This register is static configuration.
    Default Value:       NA

        Field:           VAL
        From..to bits:   0...7
        DefaultValue:    NA
        Access type:     read-write
        Description:     WIFI to BLE grant delay time.

*/
#define COEX_W2BDLY_VAL_W                                            8U
#define COEX_W2BDLY_VAL_M                                            0x000000FFU
#define COEX_W2BDLY_VAL_S                                            0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       W2SDLY
    Offset name:         COEX_O_W2SDLY
    Relative address:    0x50
    Description:         WIFI to SOC Grant Delay.

                        This register is available is to program wifi to soc grant delay time. This register is static configuration.
    Default Value:       NA

        Field:           VAL
        From..to bits:   0...7
        DefaultValue:    NA
        Access type:     read-write
        Description:     WIFI to SOC grant delay time.

*/
#define COEX_W2SDLY_VAL_W                                            8U
#define COEX_W2SDLY_VAL_M                                            0x000000FFU
#define COEX_W2SDLY_VAL_S                                            0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       B2SDLY
    Offset name:         COEX_O_B2SDLY
    Relative address:    0x54
    Description:         BLE to SOC Grant Delay.

                        This register is available is to program ble to soc grant delay time. This register is static configuration.
    Default Value:       NA

        Field:           VAL
        From..to bits:   0...7
        DefaultValue:    NA
        Access type:     read-write
        Description:     BLE to SOC grant delay time.

*/
#define COEX_B2SDLY_VAL_W                                            8U
#define COEX_B2SDLY_VAL_M                                            0x000000FFU
#define COEX_B2SDLY_VAL_S                                            0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       B2WDLY
    Offset name:         COEX_O_B2WDLY
    Relative address:    0x58
    Description:         BLE to WIFI Grant Delay.

                        This register is available is to program ble to wifi grant delay time. This register is static configuration.
    Default Value:       NA

        Field:           VAL
        From..to bits:   0...7
        DefaultValue:    NA
        Access type:     read-write
        Description:     BLE to WIFI grant delay time.

*/
#define COEX_B2WDLY_VAL_W                                            8U
#define COEX_B2WDLY_VAL_M                                            0x000000FFU
#define COEX_B2WDLY_VAL_S                                            0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       S2WDLY
    Offset name:         COEX_O_S2WDLY
    Relative address:    0x5C
    Description:         SOC to WIFI Grant Delay.

                        This register is available is to program soc to wifi grant delay time. This register is static configuration.
    Default Value:       NA

        Field:           VAL
        From..to bits:   0...7
        DefaultValue:    NA
        Access type:     read-write
        Description:     SOC to WIFI grant delay time.

*/
#define COEX_S2WDLY_VAL_W                                            8U
#define COEX_S2WDLY_VAL_M                                            0x000000FFU
#define COEX_S2WDLY_VAL_S                                            0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       S2BDLY
    Offset name:         COEX_O_S2BDLY
    Relative address:    0x60
    Description:         SOC to BLE Grant Delay.

                        This register is available is to program soc to ble grant delay time. This register is static configuration.
    Default Value:       NA

        Field:           VAL
        From..to bits:   0...7
        DefaultValue:    NA
        Access type:     read-write
        Description:     SOC to BLE grant delay time.

*/
#define COEX_S2BDLY_VAL_W                                            8U
#define COEX_S2BDLY_VAL_M                                            0x000000FFU
#define COEX_S2BDLY_VAL_S                                            0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DBGREP
    Offset name:         COEX_O_DBGREP
    Relative address:    0x64
    Description:         Debug Report Register.

                        This register captures state of COEX.
    Default Value:       NA

        Field:           WIFIPRILVL
        From..to bits:   0...3
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field of the register captures the wifi_prio_lvl.

*/
#define COEX_DBGREP_WIFIPRILVL_W                                     4U
#define COEX_DBGREP_WIFIPRILVL_M                                     0x0000000FU
#define COEX_DBGREP_WIFIPRILVL_S                                     0U
/*

        Field:           BLEPRILVL
        From..to bits:   4...7
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field of the register captures the ble_prio_lvl.

*/
#define COEX_DBGREP_BLEPRILVL_W                                      4U
#define COEX_DBGREP_BLEPRILVL_M                                      0x000000F0U
#define COEX_DBGREP_BLEPRILVL_S                                      4U
/*

        Field:           SOCPRILVL
        From..to bits:   8...11
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field of the register captures the soc_prio_lvl.

*/
#define COEX_DBGREP_SOCPRILVL_W                                      4U
#define COEX_DBGREP_SOCPRILVL_M                                      0x00000F00U
#define COEX_DBGREP_SOCPRILVL_S                                      8U
/*

        Field:           WIFIGRNTM
        From..to bits:   12...12
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field of the register captures the wifi_grant_m.

*/
#define COEX_DBGREP_WIFIGRNTM                                        0x00001000U
#define COEX_DBGREP_WIFIGRNTM_M                                      0x00001000U
#define COEX_DBGREP_WIFIGRNTM_S                                      12U
/*

        Field:           BLEGRNTM
        From..to bits:   13...13
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field of the register captures the ble_grant_m.

*/
#define COEX_DBGREP_BLEGRNTM                                         0x00002000U
#define COEX_DBGREP_BLEGRNTM_M                                       0x00002000U
#define COEX_DBGREP_BLEGRNTM_S                                       13U
/*

        Field:           SOCGRNTM
        From..to bits:   14...14
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field of the register captures the soc_grant_m.

*/
#define COEX_DBGREP_SOCGRNTM                                         0x00004000U
#define COEX_DBGREP_SOCGRNTM_M                                       0x00004000U
#define COEX_DBGREP_SOCGRNTM_S                                       14U
/*

        Field:           WIFIGRNT
        From..to bits:   15...15
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field of the register captures the wifi_grant.

*/
#define COEX_DBGREP_WIFIGRNT                                         0x00008000U
#define COEX_DBGREP_WIFIGRNT_M                                       0x00008000U
#define COEX_DBGREP_WIFIGRNT_S                                       15U
/*

        Field:           BLEGRNT
        From..to bits:   16...16
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field of the register captures the ble_grant.

*/
#define COEX_DBGREP_BLEGRNT                                          0x00010000U
#define COEX_DBGREP_BLEGRNT_M                                        0x00010000U
#define COEX_DBGREP_BLEGRNT_S                                        16U
/*

        Field:           SOCGRNT
        From..to bits:   17...17
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field of the register captures the soc_grant.

*/
#define COEX_DBGREP_SOCGRNT                                          0x00020000U
#define COEX_DBGREP_SOCGRNT_M                                        0x00020000U
#define COEX_DBGREP_SOCGRNT_S                                        17U


/*-----------------------------------REGISTER------------------------------------
    Register name:       WIFILOG
    Offset name:         COEX_O_WIFILOG
    Relative address:    0x68
    Description:         WIFI Request and Grant Log Register.

                        This register keeps a log of wifi request and grant.
    Default Value:       NA

        Field:           REQASRT
        From..to bits:   0...7
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field of the register captures the number of times the wifi request was asserted since last reset.

*/
#define COEX_WIFILOG_REQASRT_W                                       8U
#define COEX_WIFILOG_REQASRT_M                                       0x000000FFU
#define COEX_WIFILOG_REQASRT_S                                       0U
/*

        Field:           REQDEASRT
        From..to bits:   8...15
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field of the register captures the number of times the wifi request was dropped/deasserted since last reset.

*/
#define COEX_WIFILOG_REQDEASRT_W                                     8U
#define COEX_WIFILOG_REQDEASRT_M                                     0x0000FF00U
#define COEX_WIFILOG_REQDEASRT_S                                     8U
/*

        Field:           GRNTASRT
        From..to bits:   16...23
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field of the register captures the number of times the wifi grant was asserted since last reset.

*/
#define COEX_WIFILOG_GRNTASRT_W                                      8U
#define COEX_WIFILOG_GRNTASRT_M                                      0x00FF0000U
#define COEX_WIFILOG_GRNTASRT_S                                      16U
/*

        Field:           GRNTDEASRT
        From..to bits:   24...31
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field of the register captures the number of times the wifi grant was deasserted since last reset.

*/
#define COEX_WIFILOG_GRNTDEASRT_W                                    8U
#define COEX_WIFILOG_GRNTDEASRT_M                                    0xFF000000U
#define COEX_WIFILOG_GRNTDEASRT_S                                    24U


/*-----------------------------------REGISTER------------------------------------
    Register name:       BLELOG
    Offset name:         COEX_O_BLELOG
    Relative address:    0x6C
    Description:         BLE Request and Grant Log Register.

                        This register keeps a log of ble request and grant.
    Default Value:       NA

        Field:           REQASRT
        From..to bits:   0...7
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field of the register captures the number of times the ble request was asserted since last reset.

*/
#define COEX_BLELOG_REQASRT_W                                        8U
#define COEX_BLELOG_REQASRT_M                                        0x000000FFU
#define COEX_BLELOG_REQASRT_S                                        0U
/*

        Field:           REQDEASRT
        From..to bits:   8...15
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field of the register captures the number of times the ble request was dropped/deasserted since last reset.

*/
#define COEX_BLELOG_REQDEASRT_W                                      8U
#define COEX_BLELOG_REQDEASRT_M                                      0x0000FF00U
#define COEX_BLELOG_REQDEASRT_S                                      8U
/*

        Field:           GRNTASRT
        From..to bits:   16...23
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field of the register captures the number of times the ble grant was asserted since last reset.

*/
#define COEX_BLELOG_GRNTASRT_W                                       8U
#define COEX_BLELOG_GRNTASRT_M                                       0x00FF0000U
#define COEX_BLELOG_GRNTASRT_S                                       16U
/*

        Field:           GRNTDEASRT
        From..to bits:   24...31
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field of the register captures the number of times the ble grant was deasserted since last reset.

*/
#define COEX_BLELOG_GRNTDEASRT_W                                     8U
#define COEX_BLELOG_GRNTDEASRT_M                                     0xFF000000U
#define COEX_BLELOG_GRNTDEASRT_S                                     24U


/*-----------------------------------REGISTER------------------------------------
    Register name:       SOCLOG
    Offset name:         COEX_O_SOCLOG
    Relative address:    0x70
    Description:         SOC Request and Grant Log Register.

                        This register keeps a log of soc request and grant.
    Default Value:       NA

        Field:           REQASRT
        From..to bits:   0...7
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field of the register captures the number of times the soc request was asserted since last reset.

*/
#define COEX_SOCLOG_REQASRT_W                                        8U
#define COEX_SOCLOG_REQASRT_M                                        0x000000FFU
#define COEX_SOCLOG_REQASRT_S                                        0U
/*

        Field:           REQDEASRT
        From..to bits:   8...15
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field of the register captures the number of times the soc request was dropped/deasserted since last reset.

*/
#define COEX_SOCLOG_REQDEASRT_W                                      8U
#define COEX_SOCLOG_REQDEASRT_M                                      0x0000FF00U
#define COEX_SOCLOG_REQDEASRT_S                                      8U
/*

        Field:           GRNTASRT
        From..to bits:   16...23
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field of the register captures the number of times the soc grant was asserted since last reset.

*/
#define COEX_SOCLOG_GRNTASRT_W                                       8U
#define COEX_SOCLOG_GRNTASRT_M                                       0x00FF0000U
#define COEX_SOCLOG_GRNTASRT_S                                       16U
/*

        Field:           GRNTDEASRT
        From..to bits:   24...31
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field of the register captures the number of times the soc grant was deasserted since last reset.

*/
#define COEX_SOCLOG_GRNTDEASRT_W                                     8U
#define COEX_SOCLOG_GRNTDEASRT_M                                     0xFF000000U
#define COEX_SOCLOG_GRNTDEASRT_S                                     24U


/*-----------------------------------REGISTER------------------------------------
    Register name:       WIFIPRIREJ
    Offset name:         COEX_O_WIFIPRIREJ
    Relative address:    0x78
    Description:         WIFI Priority Reject Log Register.

                        This register keeps a log of number of times wifi prio was rejected.
    Default Value:       NA

        Field:           LOGVAL
        From..to bits:   0...7
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field of the register captures the number of times the soc request was asserted since last reset.

*/
#define COEX_WIFIPRIREJ_LOGVAL_W                                     8U
#define COEX_WIFIPRIREJ_LOGVAL_M                                     0x000000FFU
#define COEX_WIFIPRIREJ_LOGVAL_S                                     0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       SOCPRIREJ
    Offset name:         COEX_O_SOCPRIREJ
    Relative address:    0x7C
    Description:         SOC Priority Reject Log Register.

                        This register keeps a log of number of times soc prio was rejected.
    Default Value:       NA

        Field:           HILOGVAL
        From..to bits:   0...7
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field of the register captures the number of times the soc high priority was rejected since last reset.

*/
#define COEX_SOCPRIREJ_HILOGVAL_W                                    8U
#define COEX_SOCPRIREJ_HILOGVAL_M                                    0x000000FFU
#define COEX_SOCPRIREJ_HILOGVAL_S                                    0U
/*

        Field:           LOLOGVAL
        From..to bits:   8...15
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field of the register captures the number of times the soc low priority was rejected since last reset.

*/
#define COEX_SOCPRIREJ_LOLOGVAL_W                                    8U
#define COEX_SOCPRIREJ_LOLOGVAL_M                                    0x0000FF00U
#define COEX_SOCPRIREJ_LOLOGVAL_S                                    8U


/*-----------------------------------REGISTER------------------------------------
    Register name:       BLEPRIREJ
    Offset name:         COEX_O_BLEPRIREJ
    Relative address:    0x80
    Description:         BLE Priority Reject Log Register.

                        This register keeps a log of number of times ble prio was rejected.
    Default Value:       NA

        Field:           TXHILOG
        From..to bits:   0...7
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field of the register captures the number of times the ble tx high priority was rejected since last reset.

*/
#define COEX_BLEPRIREJ_TXHILOG_W                                     8U
#define COEX_BLEPRIREJ_TXHILOG_M                                     0x000000FFU
#define COEX_BLEPRIREJ_TXHILOG_S                                     0U
/*

        Field:           TXLOLOG
        From..to bits:   8...15
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field of the register captures the number of times the ble tx low priority was rejected since last reset.

*/
#define COEX_BLEPRIREJ_TXLOLOG_W                                     8U
#define COEX_BLEPRIREJ_TXLOLOG_M                                     0x0000FF00U
#define COEX_BLEPRIREJ_TXLOLOG_S                                     8U
/*

        Field:           RXHILOG
        From..to bits:   16...23
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field of the register captures the number of times the ble rx high priority was rejected since last reset.

*/
#define COEX_BLEPRIREJ_RXHILOG_W                                     8U
#define COEX_BLEPRIREJ_RXHILOG_M                                     0x00FF0000U
#define COEX_BLEPRIREJ_RXHILOG_S                                     16U
/*

        Field:           RXLOLOG
        From..to bits:   24...31
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field of the register captures the number of times the ble rx low priority was rejected since last reset.

*/
#define COEX_BLEPRIREJ_RXLOLOG_W                                     8U
#define COEX_BLEPRIREJ_RXLOLOG_M                                     0xFF000000U
#define COEX_BLEPRIREJ_RXLOLOG_S                                     24U


/*-----------------------------------REGISTER------------------------------------
    Register name:       TIMESTAMP
    Offset name:         COEX_O_TIMESTAMP
    Relative address:    0x84
    Description:         Timestamp Register.

                        This register captures the timestamp (from TSF counter) when the coex_irq was generated.
    Default Value:       NA

        Field:           TS
        From..to bits:   0...31
        DefaultValue:    NA
        Access type:     read-only
        Description:     This register captures the timestamp (from TSF counter) when the coex_irq was generated since last reset.

*/
#define COEX_TIMESTAMP_TS_W                                          32U
#define COEX_TIMESTAMP_TS_M                                          0xFFFFFFFFU
#define COEX_TIMESTAMP_TS_S                                          0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       WIFIANTLOG
    Offset name:         COEX_O_WIFIANTLOG
    Relative address:    0x88
    Description:         WIFI Grant During Dual Antenna Log Register.

                        This register keeps a log of number of times ble prio was rejected.
    Default Value:       NA

        Field:           DALOG
        From..to bits:   0...7
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field of the register captures the number of times the wifi grant was deasserted during rx_only or alt_band mode since last reset.

*/
#define COEX_WIFIANTLOG_DALOG_W                                      8U
#define COEX_WIFIANTLOG_DALOG_M                                      0x000000FFU
#define COEX_WIFIANTLOG_DALOG_S                                      0U
/*

        Field:           ALOG
        From..to bits:   8...15
        DefaultValue:    NA
        Access type:     read-only
        Description:     This field of the register captures the number of times the wifi grant was deasserted during rx_only or alt_band mode since last reset.

*/
#define COEX_WIFIANTLOG_ALOG_W                                       8U
#define COEX_WIFIANTLOG_ALOG_M                                       0x0000FF00U
#define COEX_WIFIANTLOG_ALOG_S                                       8U


/*-----------------------------------REGISTER------------------------------------
    Register name:       IRQEVTMSK
    Offset name:         COEX_O_IRQEVTMSK
    Relative address:    0x8C
    Description:         IRQ Event Masking.

                        This register can be configured to mask the IRQ event.
    Default Value:       NA

        Field:           WIFIGRNTM
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field of the register is used to mask the interrupt generation caused due to changes in wifi_grant_m. 1--> mask the IRQ; 0 --> Unmask the IRQ

*/
#define COEX_IRQEVTMSK_WIFIGRNTM                                     0x00000001U
#define COEX_IRQEVTMSK_WIFIGRNTM_M                                   0x00000001U
#define COEX_IRQEVTMSK_WIFIGRNTM_S                                   0U
/*

        Field:           BLEGRNTM
        From..to bits:   1...1
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field of the register is used to mask the interrupt generation caused due to changes in ble_grant_m. 1--> mask the IRQ; 0 --> Unmask the IRQ

*/
#define COEX_IRQEVTMSK_BLEGRNTM                                      0x00000002U
#define COEX_IRQEVTMSK_BLEGRNTM_M                                    0x00000002U
#define COEX_IRQEVTMSK_BLEGRNTM_S                                    1U
/*

        Field:           SOCGRNTM
        From..to bits:   2...2
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field of the register is used to mask the interrupt generation caused due to changes in soc_grant_m. 1--> mask the IRQ; 0 --> Unmask the IRQ

*/
#define COEX_IRQEVTMSK_SOCGRNTM                                      0x00000004U
#define COEX_IRQEVTMSK_SOCGRNTM_M                                    0x00000004U
#define COEX_IRQEVTMSK_SOCGRNTM_S                                    2U
/*

        Field:           WIFIGRNT
        From..to bits:   3...3
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field of the register is used to mask the interrupt generation caused due to changes in wifi_grant. 1--> mask the IRQ; 0 --> Unmask the IRQ

*/
#define COEX_IRQEVTMSK_WIFIGRNT                                      0x00000008U
#define COEX_IRQEVTMSK_WIFIGRNT_M                                    0x00000008U
#define COEX_IRQEVTMSK_WIFIGRNT_S                                    3U
/*

        Field:           BLEGRNT
        From..to bits:   4...4
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field of the register is used to mask the interrupt generation caused due to changes in ble_grant. 1--> mask the IRQ; 0 --> Unmask the IRQ

*/
#define COEX_IRQEVTMSK_BLEGRNT                                       0x00000010U
#define COEX_IRQEVTMSK_BLEGRNT_M                                     0x00000010U
#define COEX_IRQEVTMSK_BLEGRNT_S                                     4U
/*

        Field:           SOCGRNT
        From..to bits:   5...5
        DefaultValue:    NA
        Access type:     read-write
        Description:     This field of the register is used to mask the interrupt generation caused due to changes in soc_grant. 1--> mask the IRQ; 0 --> Unmask the IRQ

*/
#define COEX_IRQEVTMSK_SOCGRNT                                       0x00000020U
#define COEX_IRQEVTMSK_SOCGRNT_M                                     0x00000020U
#define COEX_IRQEVTMSK_SOCGRNT_S                                     5U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ANTCTLCFG1
    Offset name:         COEX_O_ANTCTLCFG1
    Relative address:    0xC0
    Description:         Antenna Control Configuration 1.
    Default Value:       NA

        Field:           GRANTOV
        From..to bits:   0...2
        DefaultValue:    NA
        Access type:     read-write
        Description:     0- External enable
                         1- BLE only enable
                         2- WiFi only enable

*/
#define COEX_ANTCTLCFG1_GRANTOV_W                                    3U
#define COEX_ANTCTLCFG1_GRANTOV_M                                    0x00000007U
#define COEX_ANTCTLCFG1_GRANTOV_S                                    0U
/*

        Field:           SWENGRNT
        From..to bits:   4...6
        DefaultValue:    NA
        Access type:     read-write
        Description:     0- External mask mode
                         1- BLE Only
                         2- WiFi Only

*/
#define COEX_ANTCTLCFG1_SWENGRNT_W                                   3U
#define COEX_ANTCTLCFG1_SWENGRNT_M                                   0x00000070U
#define COEX_ANTCTLCFG1_SWENGRNT_S                                   4U
/*

        Field:           ANTCTLOV
        From..to bits:   8...9
        DefaultValue:    NA
        Access type:     read-write
        Description:     antenna control Mux override      <2>

*/
#define COEX_ANTCTLCFG1_ANTCTLOV_W                                   2U
#define COEX_ANTCTLCFG1_ANTCTLOV_M                                   0x00000300U
#define COEX_ANTCTLCFG1_ANTCTLOV_S                                   8U
/*

        Field:           SWANTCTL
        From..to bits:   12...15
        DefaultValue:    NA
        Access type:     read-write
        Description:     SW Enable register     <4>

*/
#define COEX_ANTCTLCFG1_SWANTCTL_W                                   4U
#define COEX_ANTCTLCFG1_SWANTCTL_M                                   0x0000F000U
#define COEX_ANTCTLCFG1_SWANTCTL_S                                   12U
/*

        Field:           SWIDX
        From..to bits:   16...17
        DefaultValue:    NA
        Access type:     read-write
        Description:     Bit 0 - SW index value
                         Bit 1 - SW index override

*/
#define COEX_ANTCTLCFG1_SWIDX_W                                      2U
#define COEX_ANTCTLCFG1_SWIDX_M                                      0x00030000U
#define COEX_ANTCTLCFG1_SWIDX_S                                      16U
/*

        Field:           GPIOWIFIEX
        From..to bits:   20...21
        DefaultValue:    NA
        Access type:     read-write
        Description:     FW padding for Wifi Core inputs for output mux

*/
#define COEX_ANTCTLCFG1_GPIOWIFIEX_W                                 2U
#define COEX_ANTCTLCFG1_GPIOWIFIEX_M                                 0x00300000U
#define COEX_ANTCTLCFG1_GPIOWIFIEX_S                                 20U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ANTCTLCFG2
    Offset name:         COEX_O_ANTCTLCFG2
    Relative address:    0xC4
    Description:         Antenna Control Configuration 2.
    Default Value:       NA

        Field:           ANTIDX0
        From..to bits:   0...3
        DefaultValue:    NA
        Access type:     read-write
        Description:     index 0 - GPIO ANT Polarity 6x4. Mem is statically set on init

*/
#define COEX_ANTCTLCFG2_ANTIDX0_W                                    4U
#define COEX_ANTCTLCFG2_ANTIDX0_M                                    0x0000000FU
#define COEX_ANTCTLCFG2_ANTIDX0_S                                    0U
/*

        Field:           ANTIDX1
        From..to bits:   4...7
        DefaultValue:    NA
        Access type:     read-write
        Description:     index 1 - GPIO ANT Polarity 6x4. Mem is statically set on init

*/
#define COEX_ANTCTLCFG2_ANTIDX1_W                                    4U
#define COEX_ANTCTLCFG2_ANTIDX1_M                                    0x000000F0U
#define COEX_ANTCTLCFG2_ANTIDX1_S                                    4U
/*

        Field:           ANTIDX2
        From..to bits:   8...11
        DefaultValue:    NA
        Access type:     read-write
        Description:     index 2 - GPIO ANT Polarity 6x4. Mem is statically set on init

*/
#define COEX_ANTCTLCFG2_ANTIDX2_W                                    4U
#define COEX_ANTCTLCFG2_ANTIDX2_M                                    0x00000F00U
#define COEX_ANTCTLCFG2_ANTIDX2_S                                    8U
/*

        Field:           ANTIDX3
        From..to bits:   12...15
        DefaultValue:    NA
        Access type:     read-write
        Description:     index 3 - GPIO ANT Polarity 6x4. Mem is statically set on init

*/
#define COEX_ANTCTLCFG2_ANTIDX3_W                                    4U
#define COEX_ANTCTLCFG2_ANTIDX3_M                                    0x0000F000U
#define COEX_ANTCTLCFG2_ANTIDX3_S                                    12U
/*

        Field:           ANTIDX4
        From..to bits:   16...19
        DefaultValue:    NA
        Access type:     read-write
        Description:     index 4 - GPIO ANT Polarity 6x4. Mem is statically set on init

*/
#define COEX_ANTCTLCFG2_ANTIDX4_W                                    4U
#define COEX_ANTCTLCFG2_ANTIDX4_M                                    0x000F0000U
#define COEX_ANTCTLCFG2_ANTIDX4_S                                    16U
/*

        Field:           ANTIDX5
        From..to bits:   20...23
        DefaultValue:    NA
        Access type:     read-write
        Description:     index 5 - GPIO ANT Polarity 6x4. Mem is statically set on init

*/
#define COEX_ANTCTLCFG2_ANTIDX5_W                                    4U
#define COEX_ANTCTLCFG2_ANTIDX5_M                                    0x00F00000U
#define COEX_ANTCTLCFG2_ANTIDX5_S                                    20U


/*-----------------------------------REGISTER------------------------------------
    Register name:       ANTCTLSTA
    Offset name:         COEX_O_ANTCTLSTA
    Relative address:    0xC8
    Description:         Antenna Control Status.
    Default Value:       NA

        Field:           ANTSEL0
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     read-only
        Description:     Captures the ant_sel_0 bit.

*/
#define COEX_ANTCTLSTA_ANTSEL0                                       0x00000001U
#define COEX_ANTCTLSTA_ANTSEL0_M                                     0x00000001U
#define COEX_ANTCTLSTA_ANTSEL0_S                                     0U
/*

        Field:           ANTSEL1
        From..to bits:   1...1
        DefaultValue:    NA
        Access type:     read-only
        Description:     Captures the ant_sel_1 bit.

*/
#define COEX_ANTCTLSTA_ANTSEL1                                       0x00000002U
#define COEX_ANTCTLSTA_ANTSEL1_M                                     0x00000002U
#define COEX_ANTCTLSTA_ANTSEL1_S                                     1U
/*

        Field:           ANTSEL2
        From..to bits:   2...2
        DefaultValue:    NA
        Access type:     read-only
        Description:     Captures the ant_sel_2 bit .

*/
#define COEX_ANTCTLSTA_ANTSEL2                                       0x00000004U
#define COEX_ANTCTLSTA_ANTSEL2_M                                     0x00000004U
#define COEX_ANTCTLSTA_ANTSEL2_S                                     2U
/*

        Field:           ANTSEL3
        From..to bits:   3...3
        DefaultValue:    NA
        Access type:     read-only
        Description:     Captures the ant_sel_3 bit.

*/
#define COEX_ANTCTLSTA_ANTSEL3                                       0x00000008U
#define COEX_ANTCTLSTA_ANTSEL3_M                                     0x00000008U
#define COEX_ANTCTLSTA_ANTSEL3_S                                     3U

#endif /* __HW_COEX_H__*/
