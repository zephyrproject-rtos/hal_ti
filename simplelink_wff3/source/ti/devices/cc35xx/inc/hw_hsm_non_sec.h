/******************************************************************************
*  Filename:       hw_hsm_non_sec.h
*
*  Description:    Defines and prototypes for the HSM_NON_SEC peripheral.
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
#ifndef __HW_HSM_NON_SEC_H__
#define __HW_HSM_NON_SEC_H__
/*-------------------------------------------------------------------------------

This section defines the register offsets of the HSM_NON_SEC component

--------------------------------------------------------------------------------- */

//This register is used for enabling clock to the module
#define HSM_NON_SEC_O_CLK_MEM_CTRL                                   0x00000000U

//This register is used for aborting PKA operation
#define HSM_NON_SEC_O_PKA_ABORT_CTRL                                 0x00000004U

//This register provides EIP130 status
#define HSM_NON_SEC_O_HSM_STA_REG                                    0x00000008U

//This register stores status of asset clear indication
#define HSM_NON_SEC_O_RAM_CLR_STA                                    0x0000000CU



/*-----------------------------------REGISTER------------------------------------
    Register name:       CLK_MEM_CTRL
    Offset name:         HSM_NON_SEC_O_CLK_MEM_CTRL
    Relative address:    0x0
    Description:         This register is used for enabling clock to the module

    Default Value:       0x00000000

        Field:           MEM_CLK_GO
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Write this bit to enable clock to the module




        ENUMs:
            EN:                          Write 1b to enable clock
            DIS:                         Write 0b to disable clock

*/
#define HSM_NON_SEC_CLK_MEM_CTRL_MEM_CLK_GO                          0x00000001U
#define HSM_NON_SEC_CLK_MEM_CTRL_MEM_CLK_GO_M                        0x00000001U
#define HSM_NON_SEC_CLK_MEM_CTRL_MEM_CLK_GO_S                        0U
#define HSM_NON_SEC_CLK_MEM_CTRL_MEM_CLK_GO_EN                       0x00000001U
#define HSM_NON_SEC_CLK_MEM_CTRL_MEM_CLK_GO_DIS                      0x00000000U
/*

        Field:           MEM_SLV_CLK_GO
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Write this bit to enable host interface clock



        ENUMs:
            EN:                          Write 1b to enable clock
            DIS:                         Write 0b to disable clock

*/
#define HSM_NON_SEC_CLK_MEM_CTRL_MEM_SLV_CLK_GO                      0x00000002U
#define HSM_NON_SEC_CLK_MEM_CTRL_MEM_SLV_CLK_GO_M                    0x00000002U
#define HSM_NON_SEC_CLK_MEM_CTRL_MEM_SLV_CLK_GO_S                    1U
#define HSM_NON_SEC_CLK_MEM_CTRL_MEM_SLV_CLK_GO_EN                   0x00000002U
#define HSM_NON_SEC_CLK_MEM_CTRL_MEM_SLV_CLK_GO_DIS                  0x00000000U
/*

        Field:           MEM_CTR_CLK_GO
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Write this bit to enable counter clock

        ENUMs:
            DIS:                         Write 0b to disable clock

            EN:                          Write 1b to enable clock
*/
#define HSM_NON_SEC_CLK_MEM_CTRL_MEM_CTR_CLK_GO                      0x00000004U
#define HSM_NON_SEC_CLK_MEM_CTRL_MEM_CTR_CLK_GO_M                    0x00000004U
#define HSM_NON_SEC_CLK_MEM_CTRL_MEM_CTR_CLK_GO_S                    2U
#define HSM_NON_SEC_CLK_MEM_CTRL_MEM_CTR_CLK_GO_DIS                  0x00000000U
#define HSM_NON_SEC_CLK_MEM_CTRL_MEM_CTR_CLK_GO_EN                   0x00000004U
/*

        Field:           MEM_CLK_GO_M3
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     M3 writes this bit to enable clock to the module

        ENUMs:
            DIS:                         Write 0b to disable clock

            EN:                          Write 1b to enable clock
*/
#define HSM_NON_SEC_CLK_MEM_CTRL_MEM_CLK_GO_M3                       0x00000008U
#define HSM_NON_SEC_CLK_MEM_CTRL_MEM_CLK_GO_M3_M                     0x00000008U
#define HSM_NON_SEC_CLK_MEM_CTRL_MEM_CLK_GO_M3_S                     3U
#define HSM_NON_SEC_CLK_MEM_CTRL_MEM_CLK_GO_M3_DIS                   0x00000000U
#define HSM_NON_SEC_CLK_MEM_CTRL_MEM_CLK_GO_M3_EN                    0x00000008U
/*

        Field:           MEM_SLV_CLK_GO_M3
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Write this bit to enable host interface clock

        ENUMs:
            EN:                          Write 1b to enable clock
            DIS:                         Write 0b to disable clock

*/
#define HSM_NON_SEC_CLK_MEM_CTRL_MEM_SLV_CLK_GO_M3                   0x00000010U
#define HSM_NON_SEC_CLK_MEM_CTRL_MEM_SLV_CLK_GO_M3_M                 0x00000010U
#define HSM_NON_SEC_CLK_MEM_CTRL_MEM_SLV_CLK_GO_M3_S                 4U
#define HSM_NON_SEC_CLK_MEM_CTRL_MEM_SLV_CLK_GO_M3_EN                0x00000010U
#define HSM_NON_SEC_CLK_MEM_CTRL_MEM_SLV_CLK_GO_M3_DIS               0x00000000U
/*

        Field:           MEM_CTR_CLK_GO_M3
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Write this bit to enable counter clock

        ENUMs:
            DIS:                         Write 0b to disable clock

            EN:                          Write 1b to enable clock
*/
#define HSM_NON_SEC_CLK_MEM_CTRL_MEM_CTR_CLK_GO_M3                   0x00000020U
#define HSM_NON_SEC_CLK_MEM_CTRL_MEM_CTR_CLK_GO_M3_M                 0x00000020U
#define HSM_NON_SEC_CLK_MEM_CTRL_MEM_CTR_CLK_GO_M3_S                 5U
#define HSM_NON_SEC_CLK_MEM_CTRL_MEM_CTR_CLK_GO_M3_DIS               0x00000000U
#define HSM_NON_SEC_CLK_MEM_CTRL_MEM_CTR_CLK_GO_M3_EN                0x00000020U
/*

        Field:           CLK_BUSY
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     when 1b, indicates that the module is active and busy with processing data and tokens.

*/
#define HSM_NON_SEC_CLK_MEM_CTRL_CLK_BUSY                            0x00000040U
#define HSM_NON_SEC_CLK_MEM_CTRL_CLK_BUSY_M                          0x00000040U
#define HSM_NON_SEC_CLK_MEM_CTRL_CLK_BUSY_S                          6U
/*

        Field:           SLV_CLK_BUSY
        From..to bits:   7...7
        DefaultValue:    0x0
        Access type:     read-only
        Description:     When 1b indicates the Host interface is active and busy with Host bus transfers.

*/
#define HSM_NON_SEC_CLK_MEM_CTRL_SLV_CLK_BUSY                        0x00000080U
#define HSM_NON_SEC_CLK_MEM_CTRL_SLV_CLK_BUSY_M                      0x00000080U
#define HSM_NON_SEC_CLK_MEM_CTRL_SLV_CLK_BUSY_S                      7U
/*

        Field:           CTR_CLK_BUSY
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-only
        Description:     When 1b, indicates that the counter clock domain is active. This signal is always asserted (set to '1'), except when the
                         counter module is in reset (ctr_reset_n set to '0').

*/
#define HSM_NON_SEC_CLK_MEM_CTRL_CTR_CLK_BUSY                        0x00000100U
#define HSM_NON_SEC_CLK_MEM_CTRL_CTR_CLK_BUSY_M                      0x00000100U
#define HSM_NON_SEC_CLK_MEM_CTRL_CTR_CLK_BUSY_S                      8U


/*-----------------------------------REGISTER------------------------------------
    Register name:       PKA_ABORT_CTRL
    Offset name:         HSM_NON_SEC_O_PKA_ABORT_CTRL
    Relative address:    0x4
    Description:         This register is used for aborting PKA operation.
    Default Value:       0x00000000

        Field:           MEM_PKA_ABORT_NS
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Write 1 to this bit to abort PKA operation


        ENUMs:
            ABORT:                       Set to 1, to abort PKA operation
*/
#define HSM_NON_SEC_PKA_ABORT_CTRL_MEM_PKA_ABORT_NS                  0x00000001U
#define HSM_NON_SEC_PKA_ABORT_CTRL_MEM_PKA_ABORT_NS_M                0x00000001U
#define HSM_NON_SEC_PKA_ABORT_CTRL_MEM_PKA_ABORT_NS_S                0U
#define HSM_NON_SEC_PKA_ABORT_CTRL_MEM_PKA_ABORT_NS_ABORT            0x00000001U


/*-----------------------------------REGISTER------------------------------------
    Register name:       HSM_STA_REG
    Offset name:         HSM_NON_SEC_O_HSM_STA_REG
    Relative address:    0x8
    Description:         This register provides EIP130 status

    Default Value:       0x00000000

        Field:           FIPS_MODE
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     If active (set to 1b), EIP130 is in FIPS mode


*/
#define HSM_NON_SEC_HSM_STA_REG_FIPS_MODE                            0x00000001U
#define HSM_NON_SEC_HSM_STA_REG_FIPS_MODE_M                          0x00000001U
#define HSM_NON_SEC_HSM_STA_REG_FIPS_MODE_S                          0U
/*

        Field:           NON_FIPS_MODE
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-only
        Description:     If active (set to 1b), EIP130 is in NON-FIPS mode

*/
#define HSM_NON_SEC_HSM_STA_REG_NON_FIPS_MODE                        0x00000002U
#define HSM_NON_SEC_HSM_STA_REG_NON_FIPS_MODE_M                      0x00000002U
#define HSM_NON_SEC_HSM_STA_REG_NON_FIPS_MODE_S                      1U
/*

        Field:           FATAL_ERROR
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-only
        Description:     If active (set to 1b), EIP130 detected a fatal error and stops operation. fatal error can happen when CRC on firmware ROM fails or selftest fails.

*/
#define HSM_NON_SEC_HSM_STA_REG_FATAL_ERROR                          0x00000004U
#define HSM_NON_SEC_HSM_STA_REG_FATAL_ERROR_M                        0x00000004U
#define HSM_NON_SEC_HSM_STA_REG_FATAL_ERROR_S                        2U
/*

        Field:           POWER_MODE
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Power mode value 1'b1 indicates hsm is in sleep and value 1'b0 indicates hsm is out of sleep.

*/
#define HSM_NON_SEC_HSM_STA_REG_POWER_MODE                           0x00000008U
#define HSM_NON_SEC_HSM_STA_REG_POWER_MODE_M                         0x00000008U
#define HSM_NON_SEC_HSM_STA_REG_POWER_MODE_S                         3U


/*-----------------------------------REGISTER------------------------------------
    Register name:       RAM_CLR_STA
    Offset name:         HSM_NON_SEC_O_RAM_CLR_STA
    Relative address:    0xC
    Description:         This register stores status of asset clear indication.

    Default Value:       0x00000000

        Field:           OTP_CLR_DONE
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     If active (set to 1b), it indicates that auto clear of OTP on reset release has been completed.

*/
#define HSM_NON_SEC_RAM_CLR_STA_OTP_CLR_DONE                         0x00000001U
#define HSM_NON_SEC_RAM_CLR_STA_OTP_CLR_DONE_M                       0x00000001U
#define HSM_NON_SEC_RAM_CLR_STA_OTP_CLR_DONE_S                       0U
/*

        Field:           DATARAM_CLR_DONE
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-only
        Description:     If active (set to 1b), it indicates that auto clear of Dataram on reset release has been completed.

*/
#define HSM_NON_SEC_RAM_CLR_STA_DATARAM_CLR_DONE                     0x00000002U
#define HSM_NON_SEC_RAM_CLR_STA_DATARAM_CLR_DONE_M                   0x00000002U
#define HSM_NON_SEC_RAM_CLR_STA_DATARAM_CLR_DONE_S                   1U

#endif /* __HW_HSM_NON_SEC_H__*/
