/*-----------------------------------------------------------------------------

  FILENAME:       host_xip

  DESCRIPTION:    Defines module registers - address, fields masks and offsets
                  NOTE: SET_FIELD/GET_FIELD macros (defined in register_macro.h) 
                  must be used for accessing registers

  CREATED:        2025-03-11T10:37:34.093633
  ----------------------------------------------------------------------------- */

#ifndef _CC35_REGS_HOST_XIP_H_
#define _CC35_REGS_HOST_XIP_H_

/*-----------------------------------------------------------------------------
      Module:   HOST_XIP
      Version:  1.0
  ----------------------------------------------------------------------------- */
/*-----------------------------------------------------------------------------
   Module registers address summary (for fast allocation of registers)

    HOST_XIP__WRR_ARB_EN                               (0x41912000)
    HOST_XIP__WRR_ARB_HALT                             (0x41912004)
    HOST_XIP__WRR_ARB_AGENT0_CFG                       (0x41912008)
    HOST_XIP__WRR_ARB_AGENT1_CFG                       (0x4191200c)
    HOST_XIP__WRR_ARB_AGENT2_CFG                       (0x41912010)
    HOST_XIP__DEVICE_SWITCH_EXT_DLY                    (0x41912014)
    HOST_XIP__RCM_CLOCK_DISABLE                        (0x41912020)
    HOST_XIP__RCM_CLOCK_FORCE                          (0x41912024)
    HOST_XIP__RCM_CLOCK_STATUS                         (0x41912028)
    HOST_XIP__OSPI_CONFIG                              (0x41912040)
    HOST_XIP__UDMA_SEC_SRC_ADDR_CFG                    (0x41913000)
    HOST_XIP__UDMA_SEC_DST_ADDR_CFG                    (0x41913004)
    HOST_XIP__UDMA_SEC_LENGTH_CFG                      (0x41913008)
    HOST_XIP__UDMA_SEC_MODE_CFG                        (0x4191300c)
    HOST_XIP__UDMA_SEC_START                           (0x41913010)
    HOST_XIP__UDMA_SEC_CLEAR                           (0x41913014)
    HOST_XIP__UDMA_SEC_STATUS                          (0x41913020)
    HOST_XIP__UDMA_SEC_IRQ_STATUS                      (0x41913024)
    HOST_XIP__UDMA_SEC_STATUS_1                        (0x4191302c)
    HOST_XIP__UDMA_SEC_PERIPHERAL_CFG                  (0x41913040)
    HOST_XIP__UDMA_SEC_PERIPHERAL_SEL                  (0x41913060)
    HOST_XIP__UDMA_NONSEC_PERIPHERAL_SEL               (0x41913064)
    HOST_XIP__UDMA_NONSEC_SRC_ADDR_CFG                 (0x41914000)
    HOST_XIP__UDMA_NONSEC_DST_ADDR_CFG                 (0x41914004)
    HOST_XIP__UDMA_NONSEC_LENGTH_CFG                   (0x41914008)
    HOST_XIP__UDMA_NONSEC_MODE_CFG                     (0x4191400c)
    HOST_XIP__UDMA_NONSEC_START                        (0x41914010)
    HOST_XIP__UDMA_NONSEC_CLEAR                        (0x41914014)
    HOST_XIP__UDMA_NONSEC_STATUS                       (0x41914020)
    HOST_XIP__UDMA_NONSEC_IRQ_STATUS                   (0x41914024)
    HOST_XIP__UDMA_THR_CNG                             (0x41914028)
    HOST_XIP__UDMA_NONSEC_STATUS_1                     (0x4191402c)
    HOST_XIP__UDMA_NONSEC_PERIPHERAL_CFG               (0x41914040)
    HOST_XIP__OTFDE_CFG_OSPI                           (0x41915000)
    HOST_XIP__SECGA_OTFDE_PROTECTION_CONFIG            (0x41916000)
    HOST_XIP__SECGA_REGION_0_KEY_0                     (0x41916004)
    HOST_XIP__SECGA_REGION_0_KEY_1                     (0x41916008)
    HOST_XIP__SECGA_REGION_0_KEY_2                     (0x4191600c)
    HOST_XIP__SECGA_REGION_0_KEY_3                     (0x41916010)
    HOST_XIP__SECGA_REGION_0_NONCE_0                   (0x41916014)
    HOST_XIP__SECGA_REGION_0_NONCE_1                   (0x41916018)
    HOST_XIP__SECGA_REGION_1_KEY_0                     (0x41916020)
    HOST_XIP__SECGA_REGION_1_KEY_1                     (0x41916024)
    HOST_XIP__SECGA_REGION_1_KEY_2                     (0x41916028)
    HOST_XIP__SECGA_REGION_1_KEY_3                     (0x4191602c)
    HOST_XIP__SECGA_REGION_1_NONCE_0                   (0x41916030)
    HOST_XIP__SECGA_REGION_1_NONCE_1                   (0x41916034)
    HOST_XIP__SECGA_REGION_2_KEY_0                     (0x41916040)
    HOST_XIP__SECGA_REGION_2_KEY_1                     (0x41916044)
    HOST_XIP__SECGA_REGION_2_KEY_2                     (0x41916048)
    HOST_XIP__SECGA_REGION_2_KEY_3                     (0x4191604c)
    HOST_XIP__SECGA_REGION_2_NONCE_0                   (0x41916050)
    HOST_XIP__SECGA_REGION_2_NONCE_1                   (0x41916054)
    HOST_XIP__SECGA_REGION_3_KEY_0                     (0x41916060)
    HOST_XIP__SECGA_REGION_3_KEY_1                     (0x41916064)
    HOST_XIP__SECGA_REGION_3_KEY_2                     (0x41916068)
    HOST_XIP__SECGA_REGION_3_KEY_3                     (0x4191606c)
    HOST_XIP__SECGA_REGION_3_NONCE_0                   (0x41916070)
    HOST_XIP__SECGA_REGION_3_NONCE_1                   (0x41916074)
    HOST_XIP__OTFDE_ENABLE_CONFIG                      (0x41917000)
    HOST_XIP__OTFDE_DISABLE_CONFIG                     (0x41917004)
    HOST_XIP__OTFDE_SUSPEND_CONFIG                     (0x41917008)
    HOST_XIP__OTFDE_RESUME_CONFIG                      (0x4191700c)
    HOST_XIP__OTFDE_SOFT_RESET_CONFIG                  (0x41917010)
    HOST_XIP__OTFDE_GENERAL_CONFIG_0                   (0x41917020)
    HOST_XIP__OTFDE_GENERAL_CONFIG_1                   (0x41917030)
    HOST_XIP__OTFDE_GENERAL_CONFIG_2                   (0x41917040)
    HOST_XIP__OTFDE_GENERAL_CONFIG_3                   (0x41917050)
    HOST_XIP__OTFDE_JOB_DONE_GRANT_SEL                 (0x41917060)
    HOST_XIP__OTFDE_DEVICE_0_CONFIG                    (0x41917070)
    HOST_XIP__OTFDE_DEVICE_0_POLLING_TIMER             (0x41917074)
    HOST_XIP__OTFDE_DEVICE_0_WRAP                      (0x41917078)
    HOST_XIP__OTFDE_DEVICE_1_CONFIG                    (0x41917080)
    HOST_XIP__OTFDE_DEVICE_1_WRAP                      (0x41917084)
    HOST_XIP__OTFDE_GLOBAL_WATCHDOG                    (0x41917090)
    HOST_XIP__SECGB_REGION_0_PARAMS_0                  (0x41918000)
    HOST_XIP__SECGB_REGION_0_PARAMS_1                  (0x41918004)
    HOST_XIP__SECGB_REGION_0_PARAMS_2                  (0x41918008)
    HOST_XIP__SECGB_REGION_0_PARAMS_3                  (0x4191800c)
    HOST_XIP__SECGC_REGION_1_PARAMS_0                  (0x41919000)
    HOST_XIP__SECGC_REGION_1_PARAMS_1                  (0x41919004)
    HOST_XIP__SECGC_REGION_1_PARAMS_2                  (0x41919008)
    HOST_XIP__SECGC_REGION_1_PARAMS_3                  (0x4191900c)
    HOST_XIP__SECGD_REGION_2_PARAMS_0                  (0x4191a000)
    HOST_XIP__SECGD_REGION_2_PARAMS_1                  (0x4191a004)
    HOST_XIP__SECGD_REGION_2_PARAMS_2                  (0x4191a008)
    HOST_XIP__SECGD_REGION_2_PARAMS_3                  (0x4191a00c)
    HOST_XIP__SECGE_REGION_3_PARAMS_0                  (0x4191b000)
    HOST_XIP__SECGE_REGION_3_PARAMS_1                  (0x4191b004)
    HOST_XIP__SECGE_REGION_3_PARAMS_2                  (0x4191b008)
    HOST_XIP__SECGE_REGION_3_PARAMS_3                  (0x4191b00c)

  ----------------------------------------------------------------------------- */

/*-----------------------------------------------------------------------------
    Register name:       WRR_ARB_EN
    Relative address:    0x0
    Absolute address:    0x41912000
    Description:         WRR Arbiter Enable
    Default Value:       0x00000003

        Field:          MEM_WRR_ARB_EN
        From..to bits:  0..0
        Default Value:  0x1
        Access type:    read-write
        Description:    0 - Disabled, use SIE-200 arbitration logic.
                        1 - Enable, use wrapper arbitration logic.

        Field:          MEM_WRR_ARB_POLICY_RR
        From..to bits:  1..1
        Default Value:  0x1
        Access type:    read-write
        Description:    WRR ARB POLICY RR:
                        0 - Fixed Priority
                        1 - Round Robin (Default)

  ----------------------------------------------------------------------------- */
#define HOST_XIP__WRR_ARB_EN__ADDR                           (0x41912000)
#define HOST_XIP__WRR_ARB_EN                                 (0x4003040041912000)

#define HOST_XIP__WRR_ARB_EN__MEM_WRR_ARB_EN                 (0x400307e041912000)
#define HOST_XIP__WRR_ARB_EN__MEM_WRR_ARB_POLICY_RR          (0x400307c141912000)

/*-----------------------------------------------------------------------------
    Register name:       WRR_ARB_HALT
    Relative address:    0x4
    Absolute address:    0x41912004
    Description:         WRR ARBITER HALT.
                         With sending halt request, Arbiter will finish current burst and then stop transmission of data.
                         Write ENABLE = 0 to stop halting 
    Default Value:       0x00000000

        Field:          MEM_ARBITER_HALT_EN
        From..to bits:  0..0
        Default Value:  0x0
        Access type:    read-write
        Description:    MEM_ARBITER_HALT_EN ARBITER HALT.
                        0: Arbiter transmiting data/ disable halt
                        1: Arbiter will stop transmiting data

        Field:          ARBITER_HALTED_STS
        From..to bits:  1..1
        Default Value:  0x0
        Access type:    read-only
        Description:    1: Arbiter curently halted

  ----------------------------------------------------------------------------- */
#define HOST_XIP__WRR_ARB_HALT__ADDR                         (0x41912004)
#define HOST_XIP__WRR_ARB_HALT                               (0x4003040041912004)

#define HOST_XIP__WRR_ARB_HALT__MEM_ARBITER_HALT_EN          (0x400307e041912004)
#define HOST_XIP__WRR_ARB_HALT__ARBITER_HALTED_STS           (0x400b07c141912004)

/*-----------------------------------------------------------------------------
    Register name:       WRR_ARB_AGENT0_CFG
    Relative address:    0x8
    Absolute address:    0x41912008
    Description:         WRR Arbiter - Agent 0 Configuration
    Default Value:       0x04010010

        Field:          MEM_WRR_ARB_NUM_OF_WORDS_S0
        From..to bits:  0..12
        Default Value:  0x010
        Access type:    read-write
        Description:    Number of words to be served in each arbitration grant.
                        Up to 8,192 words (32KB).
                        Value must be > 0.

        Field:          MEM_WRR_ARB_FIX_PRIO_S0
        From..to bits:  16..17
        Default Value:  0x1
        Access type:    read-write
        Description:    For Fixed Priority:
                        0 - Highest.
                        1 - Medium.
                        2 - Lowest (default).

        Field:          MEM_WRR_ARB_TRANS_DLY_S0
        From..to bits:  24..28
        Default Value:  0x4
        Access type:    read-write
        Description:    Number of cycle before starting to serve next agent in line.
                        Up to 32 cycles.

  ----------------------------------------------------------------------------- */
#define HOST_XIP__WRR_ARB_AGENT0_CFG__ADDR                   (0x41912008)
#define HOST_XIP__WRR_ARB_AGENT0_CFG                         (0x4003080041912008)

#define HOST_XIP__WRR_ARB_AGENT0_CFG__MEM_WRR_ARB_NUM_OF_WORDS_S0 (0x40030a6041912008)
#define HOST_XIP__WRR_ARB_AGENT0_CFG__MEM_WRR_ARB_FIX_PRIO_S0 (0x400309d041912008)
#define HOST_XIP__WRR_ARB_AGENT0_CFG__MEM_WRR_ARB_TRANS_DLY_S0 (0x4003087841912008)

/*-----------------------------------------------------------------------------
    Register name:       WRR_ARB_AGENT1_CFG
    Relative address:    0xc
    Absolute address:    0x4191200c
    Description:         WRR Arbiter - Agent 1 Configuration
    Default Value:       0x00020001

        Field:          MEM_WRR_ARB_NUM_OF_WORDS_S1
        From..to bits:  0..12
        Default Value:  0x001
        Access type:    read-write
        Description:    Number of words to be served in each arbitration grant.
                        Up to 8,192 words (32KB).
                        Value must be atleast 1. 0(Zero) is not allowed.

        Field:          MEM_WRR_ARB_FIX_PRIO_S1
        From..to bits:  16..17
        Default Value:  0x2
        Access type:    read-write
        Description:    For Fixed Priority:
                        0 - Highest.
                        1 - Medium (default).
                        2 - Lowest.

        Field:          MEM_WRR_ARB_TRANS_DLY_S1
        From..to bits:  24..28
        Default Value:  0x0
        Access type:    read-write
        Description:    Number of cycle before starting to serve next agent in line.
                        Up to 32 cycles.

  ----------------------------------------------------------------------------- */
#define HOST_XIP__WRR_ARB_AGENT1_CFG__ADDR                   (0x4191200c)
#define HOST_XIP__WRR_ARB_AGENT1_CFG                         (0x400308004191200c)

#define HOST_XIP__WRR_ARB_AGENT1_CFG__MEM_WRR_ARB_NUM_OF_WORDS_S1 (0x40030a604191200c)
#define HOST_XIP__WRR_ARB_AGENT1_CFG__MEM_WRR_ARB_FIX_PRIO_S1 (0x400309d04191200c)
#define HOST_XIP__WRR_ARB_AGENT1_CFG__MEM_WRR_ARB_TRANS_DLY_S1 (0x400308784191200c)

/*-----------------------------------------------------------------------------
    Register name:       WRR_ARB_AGENT2_CFG
    Relative address:    0x10
    Absolute address:    0x41912010
    Description:         WRR Arbiter - Agent 2 Configuration
    Default Value:       0x04000004

        Field:          MEM_WRR_ARB_NUM_OF_WORDS_S2
        From..to bits:  0..12
        Default Value:  0x004
        Access type:    read-write
        Description:    Number of words to be served in each arbitration grant.
                        Up to 8,192 words (32KB).
                        Value must be > 0.

        Field:          MEM_WRR_ARB_FIX_PRIO_S2
        From..to bits:  16..17
        Default Value:  0x0
        Access type:    read-write
        Description:    For Fixed Priority:
                        0 - Highest (default).
                        1 - Medium.
                        2 - Lowest.

        Field:          MEM_WRR_ARB_TRANS_DLY_S2
        From..to bits:  24..28
        Default Value:  0x4
        Access type:    read-write
        Description:    Number of cycle before starting to serve next agent in line.
                        Up to 32 cycles.

  ----------------------------------------------------------------------------- */
#define HOST_XIP__WRR_ARB_AGENT2_CFG__ADDR                   (0x41912010)
#define HOST_XIP__WRR_ARB_AGENT2_CFG                         (0x4003080041912010)

#define HOST_XIP__WRR_ARB_AGENT2_CFG__MEM_WRR_ARB_NUM_OF_WORDS_S2 (0x40030a6041912010)
#define HOST_XIP__WRR_ARB_AGENT2_CFG__MEM_WRR_ARB_FIX_PRIO_S2 (0x400309d041912010)
#define HOST_XIP__WRR_ARB_AGENT2_CFG__MEM_WRR_ARB_TRANS_DLY_S2 (0x4003087841912010)

/*-----------------------------------------------------------------------------
    Register name:       DEVICE_SWITCH_EXT_DLY
    Relative address:    0x14
    Absolute address:    0x41912014
    Description:         Register to configure the extra delay added before the device switch
    Default Value:       0x00000001

        Field:          MEM_DEVICE_SWITCH_EXTRA_DELAY
        From..to bits:  0..1
        Default Value:  0x1
        Access type:    read-write
        Description:    This field configures the extra delay added before the device switch
        Enumeration:     0x0 - SEL0 No extra delay
                         0x1 - SEL1 Extra delay of 16 cycles
                         0x2 - SEL2 Extra delay of 32 cycles
                         0x3 - SEL3 Extra delay of 64 cycles

  ----------------------------------------------------------------------------- */
#define HOST_XIP__DEVICE_SWITCH_EXT_DLY__ADDR                (0x41912014)
#define HOST_XIP__DEVICE_SWITCH_EXT_DLY                      (0x4003000041912014)

#define HOST_XIP__DEVICE_SWITCH_EXT_DLY__MEM_DEVICE_SWITCH_EXTRA_DELAY (0x400303c041912014)

/*-----------------------------------------------------------------------------
    Register name:       RCM_CLOCK_DISABLE
    Relative address:    0x20
    Absolute address:    0x41912020
    Description:         Disable clocks using HOST_XIP_RCM Module
    Default Value:       0x00000000

        Field:          MEM_HOST_XIP_CLK_SW_DISABLE
        From..to bits:  0..0
        Default Value:  0x0
        Access type:    read-write
        Description:    HOST_XIP CLK SW DISABLE:
                        1 - Clock is permanent blocked (not depended on clk_req input)
                        0 - (default) - Clock is not blocked, but gated with clk_req input port

        Field:          MEM_SOC_CLK_SW_DISABLE
        From..to bits:  1..1
        Default Value:  0x0
        Access type:    read-write
        Description:    SOC CLK SW DISABLE:
                        1 - Clock is permanent blocked (not depended on clk_req input)
                        0 - (default) - Clock is not blocked, but gated with clk_req input port

        Field:          MEM_OSPI_REF_CLK_SW_DISABLE
        From..to bits:  2..2
        Default Value:  0x0
        Access type:    read-write
        Description:    OSPI REF CLK SW DISABLE:
                        1 - Clock is permanent blocked (not depended on clk_req input)
                        0 - (default) - Clock is not blocked, but gated with clk_req input port

  ----------------------------------------------------------------------------- */
#define HOST_XIP__RCM_CLOCK_DISABLE__ADDR                    (0x41912020)
#define HOST_XIP__RCM_CLOCK_DISABLE                          (0x4003080041912020)

#define HOST_XIP__RCM_CLOCK_DISABLE__MEM_HOST_XIP_CLK_SW_DISABLE (0x40030be041912020)
#define HOST_XIP__RCM_CLOCK_DISABLE__MEM_SOC_CLK_SW_DISABLE  (0x40030bc141912020)
#define HOST_XIP__RCM_CLOCK_DISABLE__MEM_OSPI_REF_CLK_SW_DISABLE (0x40030ba241912020)

/*-----------------------------------------------------------------------------
    Register name:       RCM_CLOCK_FORCE
    Relative address:    0x24
    Absolute address:    0x41912024
    Description:         Force clocks using HOST_XIP_RCM Module
    Default Value:       0x00000000

        Field:          MEM_HOST_XIP_CLK_SW_FORCE
        From..to bits:  0..0
        Default Value:  0x0
        Access type:    read-write
        Description:    HOST_XIP CLK SW FORCE:
                        1 - Force clk (even if sw_disable_clk is 1 or clk_req is 0)
                        0 - Clock is not forced, but gated with clk_req input port

        Field:          MEM_SOC_CLK_SW_FORCE
        From..to bits:  1..1
        Default Value:  0x0
        Access type:    read-write
        Description:    SOC CLK SW FORCE:
                        1 - Force clk (even if sw_disable_clk is 1 or clk_req is 0)
                        0 - Clock is not forced, but gated with clk_req input port

        Field:          MEM_OSPI_REF_CLK_SW_FORCE
        From..to bits:  2..2
        Default Value:  0x0
        Access type:    read-write
        Description:    OSPI REF CLK SW FORCE:
                        1 - Force clk (even if sw_disable_clk is 1 or clk_req is 0)
                        0 - Clock is not forced, but gated with clk_req input port

  ----------------------------------------------------------------------------- */
#define HOST_XIP__RCM_CLOCK_FORCE__ADDR                      (0x41912024)
#define HOST_XIP__RCM_CLOCK_FORCE                            (0x4003080041912024)

#define HOST_XIP__RCM_CLOCK_FORCE__MEM_HOST_XIP_CLK_SW_FORCE (0x40030be041912024)
#define HOST_XIP__RCM_CLOCK_FORCE__MEM_SOC_CLK_SW_FORCE      (0x40030bc141912024)
#define HOST_XIP__RCM_CLOCK_FORCE__MEM_OSPI_REF_CLK_SW_FORCE (0x40030ba241912024)

/*-----------------------------------------------------------------------------
    Register name:       RCM_CLOCK_STATUS
    Relative address:    0x28
    Absolute address:    0x41912028
    Description:         (ICG) Clock Status from HOST_XIP_RCM Module
    Default Value:       0x00000000

        Field:          HOST_XIP_CLK_EN_STS
        From..to bits:  0..0
        Default Value:  0x0
        Access type:    read-only
        Description:    1 - Force clk (even if sw_disable_clk is 1 or clk_req is 0)
                        0 - Clock is not forced, but gated with clk_req input port

        Field:          SOC_CLK_EN_STS
        From..to bits:  1..1
        Default Value:  0x0
        Access type:    read-only
        Description:    1 - Force clk (even if sw_disable_clk is 1 or clk_req is 0)
                        0 - Clock is not forced, but gated with clk_req input port

        Field:          OSPI_REF_CLK_EN_STS
        From..to bits:  2..2
        Default Value:  0x0
        Access type:    read-only
        Description:    1 - Force clk (even if sw_disable_clk is 1 or clk_req is 0)
                        0 - Clock is not forced, but gated with clk_req input port

  ----------------------------------------------------------------------------- */
#define HOST_XIP__RCM_CLOCK_STATUS__ADDR                     (0x41912028)
#define HOST_XIP__RCM_CLOCK_STATUS                           (0x400b080041912028)

#define HOST_XIP__RCM_CLOCK_STATUS__HOST_XIP_CLK_EN_STS      (0x400b0be041912028)
#define HOST_XIP__RCM_CLOCK_STATUS__SOC_CLK_EN_STS           (0x400b0bc141912028)
#define HOST_XIP__RCM_CLOCK_STATUS__OSPI_REF_CLK_EN_STS      (0x400b0ba241912028)

/*-----------------------------------------------------------------------------
    Register name:       OSPI_CONFIG
    Relative address:    0x40
    Absolute address:    0x41912040
    Description:         
    Default Value:       0x00000003

        Field:          MEM_OSPI_CLK_GLITCH_FIX_EN
        From..to bits:  1..1
        Default Value:  0x1
        Access type:    read-write
        Description:    Field to enable the *OSPI* glitch fix
        Enumeration:     0x0 -  DIS Disable
                         0x1 -   EN Enable

        Field:          MEM_OSPI_GZ_HOLD_FIX_EN
        From..to bits:  0..0
        Default Value:  0x1
        Access type:    read-write
        Description:    HOLD FIX ENABLE
                        
                        Field to enable the *OSPI* hold fix
        Enumeration:     0x0 -  DIS Disable
                         0x1 -   EN Enable

  ----------------------------------------------------------------------------- */
#define HOST_XIP__OSPI_CONFIG__ADDR                          (0x41912040)
#define HOST_XIP__OSPI_CONFIG                                (0x4003040041912040)

#define HOST_XIP__OSPI_CONFIG__MEM_OSPI_CLK_GLITCH_FIX_EN    (0x400307c141912040)
#define HOST_XIP__OSPI_CONFIG__MEM_OSPI_GZ_HOLD_FIX_EN       (0x400307e041912040)

/*-----------------------------------------------------------------------------
    Register name:       UDMA_SEC_SRC_ADDR_CFG
    Relative address:    0x1000
    Absolute address:    0x41913000
    Description:         uDMA source address for secured read master.
                         Must be Word aligned.
    Default Value:       0x00000000

        Field:          MEM_DMA_SEC_JOB_SRC_ADDR
        From..to bits:  0..31
        Default Value:  0x00000000
        Access type:    read-write
        Description:    DMA SEC JOB SRC ADDR:
                        Specifies source address for secured read master.
                        Source address must comply with bit.26 to enable Sec/Non-Sec accesses, otherwise transactions will be blocked.

  ----------------------------------------------------------------------------- */
#define HOST_XIP__UDMA_SEC_SRC_ADDR_CFG__ADDR                (0x41913000)
#define HOST_XIP__UDMA_SEC_SRC_ADDR_CFG                      (0x4003000041913000)

#define HOST_XIP__UDMA_SEC_SRC_ADDR_CFG__MEM_DMA_SEC_JOB_SRC_ADDR (0x4003000041913000)

/*-----------------------------------------------------------------------------
    Register name:       UDMA_SEC_DST_ADDR_CFG
    Relative address:    0x1004
    Absolute address:    0x41913004
    Description:         uDMA destination address for secured write master.
                         Must be Word aligned.
    Default Value:       0x00000000

        Field:          MEM_DMA_SEC_JOB_DST_ADDR
        From..to bits:  0..31
        Default Value:  0x00000000
        Access type:    read-write
        Description:    DMA SEC JOB DST ADDR:
                        Specifies destination address for secured write master.
                        Destination address must comply with bit.26 to enable Sec/Non-Sec accesses, otherwise transactions will be blocked.

  ----------------------------------------------------------------------------- */
#define HOST_XIP__UDMA_SEC_DST_ADDR_CFG__ADDR                (0x41913004)
#define HOST_XIP__UDMA_SEC_DST_ADDR_CFG                      (0x4003000041913004)

#define HOST_XIP__UDMA_SEC_DST_ADDR_CFG__MEM_DMA_SEC_JOB_DST_ADDR (0x4003000041913004)

/*-----------------------------------------------------------------------------
    Register name:       UDMA_SEC_LENGTH_CFG
    Relative address:    0x1008
    Absolute address:    0x41913008
    Description:         uDMA secured job Length
    Default Value:       0x00000000

        Field:          MEM_DMA_SEC_JOB_LENGTH
        From..to bits:  0..17
        Default Value:  0x0000
        Access type:    read-write
        Description:    DMA SEC JOB LENGTH:
                        Resolution - 32 bits/4 bytes
                        Maximum configurable job size - 1 Mega byte (256K Words).
                        (Maximum available size in MEMSS is 1MB).

  ----------------------------------------------------------------------------- */
#define HOST_XIP__UDMA_SEC_LENGTH_CFG__ADDR                  (0x41913008)
#define HOST_XIP__UDMA_SEC_LENGTH_CFG                        (0x4003000041913008)

#define HOST_XIP__UDMA_SEC_LENGTH_CFG__MEM_DMA_SEC_JOB_LENGTH (0x400301c041913008)

/*-----------------------------------------------------------------------------
    Register name:       UDMA_SEC_MODE_CFG
    Relative address:    0x100c
    Absolute address:    0x4191300c
    Description:         uDMA Direction
    Default Value:       0x00000000

        Field:          MEM_DMA_SEC_JOB_MODE
        From..to bits:  0..0
        Default Value:  0x0
        Access type:    read-write
        Description:    DMA SEC JOB MODE:
                        0 - Data movement from External memory to Internal memory/Peripheral
                        1 - Data movement from Internal memory/Peripheral to External memory.

        Field:          MEM_SEC_MODE
        From..to bits:  1..1
        Default Value:  0x0
        Access type:    read-write
        Description:    Secure channel mode
                        0: Memory Mode
                        1: Peripheral Mode

  ----------------------------------------------------------------------------- */
#define HOST_XIP__UDMA_SEC_MODE_CFG__ADDR                    (0x4191300c)
#define HOST_XIP__UDMA_SEC_MODE_CFG                          (0x400304004191300c)

#define HOST_XIP__UDMA_SEC_MODE_CFG__MEM_DMA_SEC_JOB_MODE    (0x400307e04191300c)
#define HOST_XIP__UDMA_SEC_MODE_CFG__MEM_SEC_MODE            (0x400307c14191300c)

/*-----------------------------------------------------------------------------
    Register name:       UDMA_SEC_START
    Relative address:    0x1010
    Absolute address:    0x41913010
    Description:         uDMA secured job kick
    Default Value:       0x00000000

        Field:          DMA_SEC_JOB_START_WRCL
        From..to bits:  0..0
        Default Value:  0x0
        Access type:    write-only
        Description:    DMA SEC JOB START WRCL:
                        Start command for uDMA to start working on secured configured job.

  ----------------------------------------------------------------------------- */
#define HOST_XIP__UDMA_SEC_START__ADDR                       (0x41913010)
#define HOST_XIP__UDMA_SEC_START                             (0x4003000041913010)

#define HOST_XIP__UDMA_SEC_START__DMA_SEC_JOB_START_WRCL     (0x401303e041913010)

/*-----------------------------------------------------------------------------
    Register name:       UDMA_SEC_CLEAR
    Relative address:    0x1014
    Absolute address:    0x41913014
    Description:         uDMA secured job abort
    Default Value:       0x00000000

        Field:          DMA_SEC_JOB_CLEAR_WRCL
        From..to bits:  0..0
        Default Value:  0x0
        Access type:    write-only
        Description:    DMA SEC JOB CLEAR WRCL:
                        Clear command for uDMA to stop working and clear configuration.

  ----------------------------------------------------------------------------- */
#define HOST_XIP__UDMA_SEC_CLEAR__ADDR                       (0x41913014)
#define HOST_XIP__UDMA_SEC_CLEAR                             (0x4003000041913014)

#define HOST_XIP__UDMA_SEC_CLEAR__DMA_SEC_JOB_CLEAR_WRCL     (0x401303e041913014)

/*-----------------------------------------------------------------------------
    Register name:       UDMA_SEC_STATUS
    Relative address:    0x1020
    Absolute address:    0x41913020
    Description:         uDMA secured Status bits
    Default Value:       0x00000000

        Field:          DMA_SEC_JOB_ACTIVE
        From..to bits:  0..0
        Default Value:  0x0
        Access type:    read-only
        Description:    DMA SEC JOB ACTIVE:
                        Status bit to indicate that DMA is processing a secured job.
                        When this bit is set, SW has written all the job parameters and also provided a start_pulse to HW, 
                        and cannot change job parameters without clear_pulse.
                        Job will wait to be executed (indicated by job_in_progress)

        Field:          DMA_SEC_JOB_IN_PROGRESS
        From..to bits:  4..4
        Default Value:  0x0
        Access type:    read-only
        Description:    DMA SEC JOB IN PROGRESS:
                        1- sec job is currently in progress and being executed by uDMA

        Field:          DMA_SEC_JOB_READ_WORDS_LEFT
        From..to bits:  8..27
        Default Value:  0x00000
        Access type:    read-only
        Description:    DMA SEC JOB READ WORDS LEFT:
                        number of read words left in sec job.
                        Note: This value would be updated on a read to this register. [UDSSTA1.WRWRDSLFT] is updated on a read to this register
                        This register value shows number of words in 32 bit when field [UDSCFG3.JDIR] is configured '0' else shows number of words in 8/16/32 bit based on the configuration of [UDSCFG3.SMODE] and [UDPERCFG.SWORDSZ] fields

  ----------------------------------------------------------------------------- */
#define HOST_XIP__UDMA_SEC_STATUS__ADDR                      (0x41913020)
#define HOST_XIP__UDMA_SEC_STATUS                            (0x400b080041913020)

#define HOST_XIP__UDMA_SEC_STATUS__DMA_SEC_JOB_ACTIVE        (0x400b0be041913020)
#define HOST_XIP__UDMA_SEC_STATUS__DMA_SEC_JOB_IN_PROGRESS   (0x400b0b6441913020)
#define HOST_XIP__UDMA_SEC_STATUS__DMA_SEC_JOB_READ_WORDS_LEFT (0x400b088841913020)

/*-----------------------------------------------------------------------------
    Register name:       UDMA_SEC_IRQ_STATUS
    Relative address:    0x1024
    Absolute address:    0x41913024
    Description:         uDMA secured IRQ Status bits
    Default Value:       0x00000000

        Field:          DMA_SEC_JOB_IRQ_STS_RDCL
        From..to bits:  0..1
        Default Value:  0x0
        Access type:    read-only
        Description:    Status vector for IRQ indication for secured DMA IRQ:
                        2'd0 - DMA done.
                        2'd1 - DMA Internal bus error occurred. check SEC_STATUS in order to recovers

        Field:          DMA_SEC_JOB_BUS_ERR_DIR_RDCL
        From..to bits:  2..2
        Default Value:  0x0
        Access type:    read-only
        Description:    Bus Error direction
                        0: Source bus
                        1: Destination bus
                        Note: Source and destination is determined based on [UDMA_SEC_MODE_CFG.MEM_DMA_SEC_JOB_MODE] configuration

  ----------------------------------------------------------------------------- */
#define HOST_XIP__UDMA_SEC_IRQ_STATUS__ADDR                  (0x41913024)
#define HOST_XIP__UDMA_SEC_IRQ_STATUS                        (0x400b040041913024)

#define HOST_XIP__UDMA_SEC_IRQ_STATUS__DMA_SEC_JOB_IRQ_STS_RDCL (0x400b07c041913024)
#define HOST_XIP__UDMA_SEC_IRQ_STATUS__DMA_SEC_JOB_BUS_ERR_DIR_RDCL (0x400b07a241913024)

/*-----------------------------------------------------------------------------
    Register name:       UDMA_SEC_STATUS_1
    Relative address:    0x102c
    Absolute address:    0x4191302c
    Description:         uDMA secured Status bits in addition to [UDMSSTA] register
    Default Value:       NA

        Field:          DMA_SEC_JOB_WRITE_WORDS_LEFT
        From..to bits:  8..27
        Default Value:  0x00000
        Access type:    read-only
        Description:    DMA SEC JOB WRITE WORDS LEFT:
                        Number of write words left in sec job.
                        Note: This value would be updated only on a read to [UDSSTA] register.
                        This register value shows number of words in 32 bit when field [UDSCFG3.JDIR] is configured '1' else shows number of words in 8/16/32 bit based on the configuration of [UDSCFG3.SMODE] and [UDPERCFG.SWORDSZ] fields

        Field:          DMA_SEC_PERIPH_WORD_OFFSET
        From..to bits:  0..7
        Default Value:  0x00
        Access type:    read-only
        Description:    DMA SEC PERIPH WORD OFFSET:
                        Number of words left in a peripheral block.
                        Note: This value would be updated only on a read to [UDSSTA] register.
                        This register value shows number of words in 8/16/32 bit based on the configuration of [UDSCFG3.SMODE] and [UDPERCFG.SWORDSZ] fields

  ----------------------------------------------------------------------------- */
#define HOST_XIP__UDMA_SEC_STATUS_1__ADDR                    (0x4191302c)
#define HOST_XIP__UDMA_SEC_STATUS_1                          (0x400b04004191302c)

#define HOST_XIP__UDMA_SEC_STATUS_1__DMA_SEC_JOB_WRITE_WORDS_LEFT (0x400b04884191302c)
#define HOST_XIP__UDMA_SEC_STATUS_1__DMA_SEC_PERIPH_WORD_OFFSET (0x400b07004191302c)

/*-----------------------------------------------------------------------------
    Register name:       UDMA_SEC_PERIPHERAL_CFG
    Relative address:    0x1040
    Absolute address:    0x41913040
    Description:         uDMA Secure channel peripheral config register
    Default Value:       0x00000000

        Field:          MEM_SEC_PERIPH_WORD_SIZE
        From..to bits:  0..1
        Default Value:  0x0
        Access type:    read-write
        Description:    Secure channel peripheral job word size
                        8/16/32 (Word Size of 1/2/4 bytes)
                        Sel_0 - 32 bit
                        Sel_1 -  16 bit
                        Sel_2 - 8 bit

        Field:          MEM_SEC_PERIPH_BLOCK_SIZE
        From..to bits:  2..7
        Default Value:  0x0
        Access type:    read-write
        Description:    Secure channel peripheral block size(in 32bits/4bytes)
                        Multiplication of Word size
                        
                        Upto 64 words based on the word size selected
                        
                        Block = block_size * word_size

        Field:          MEM_SEC_EN_CLR_AT_START
        From..to bits:  8..8
        Default Value:  0x0
        Access type:    read-write
        Description:    Enable uDMA to set a rd/wr clear pulse at the beginning of a job

  ----------------------------------------------------------------------------- */
#define HOST_XIP__UDMA_SEC_PERIPHERAL_CFG__ADDR              (0x41913040)
#define HOST_XIP__UDMA_SEC_PERIPHERAL_CFG                    (0x4003080041913040)

#define HOST_XIP__UDMA_SEC_PERIPHERAL_CFG__MEM_SEC_PERIPH_WORD_SIZE (0x40030bc041913040)
#define HOST_XIP__UDMA_SEC_PERIPHERAL_CFG__MEM_SEC_PERIPH_BLOCK_SIZE (0x40030b0241913040)
#define HOST_XIP__UDMA_SEC_PERIPHERAL_CFG__MEM_SEC_EN_CLR_AT_START (0x40030ae841913040)

/*-----------------------------------------------------------------------------
    Register name:       UDMA_SEC_PERIPHERAL_SEL
    Relative address:    0x1060
    Absolute address:    0x41913060
    Description:         Register to select the peripheral to be served on secured channel
    Default Value:       0x00000000

        Field:          MEM_SEC_PERIPH_SEL
        From..to bits:  0..3
        Default Value:  0x0
        Access type:    read-write
        Description:    Select the peripheral to serve job. This field along with [UDMA_SEC_MODE.MEM_SEC_MODE] selects the peripheral to the channel
                        0x0 UART0
                        0x1 UART1
                        0x2 SPI0
                        0x3 SPI1
                        0x4 I2C0
                        0x5 I2C1
                        0x6 SDMMC
                        0x7 SDIO
                        0x8 MCAN
                        0x9 ADC
                        0xA PDM
                        0xB HIF
                        

  ----------------------------------------------------------------------------- */
#define HOST_XIP__UDMA_SEC_PERIPHERAL_SEL__ADDR              (0x41913060)
#define HOST_XIP__UDMA_SEC_PERIPHERAL_SEL                    (0x4003000041913060)

#define HOST_XIP__UDMA_SEC_PERIPHERAL_SEL__MEM_SEC_PERIPH_SEL (0x4003038041913060)

/*-----------------------------------------------------------------------------
    Register name:       UDMA_NONSEC_PERIPHERAL_SEL
    Relative address:    0x1064
    Absolute address:    0x41913064
    Description:         Register to select the peripheral to be served on non secured channel
    Default Value:       0x00000000

        Field:          MEM_NON_SEC_PERIPH_SEL
        From..to bits:  0..3
        Default Value:  0x0
        Access type:    read-write
        Description:    Select the peripheral to serve job. This field along with [UDMA_NONSEC_MODE.MEM_NON_SEC_MODE] selects the peripheral to the channel
                        0x0 UART0
                        0x1 UART1
                        0x2 SPI0
                        0x3 SPI1
                        0x4 I2C0
                        0x5 I2C1
                        0x6 SDMMC
                        0x7 SDIO
                        0x8 MCAN
                        0x9 ADC
                        0xA PDM
                        0xB HIF

  ----------------------------------------------------------------------------- */
#define HOST_XIP__UDMA_NONSEC_PERIPHERAL_SEL__ADDR           (0x41913064)
#define HOST_XIP__UDMA_NONSEC_PERIPHERAL_SEL                 (0x4003000041913064)

#define HOST_XIP__UDMA_NONSEC_PERIPHERAL_SEL__MEM_NON_SEC_PERIPH_SEL (0x4003038041913064)

/*-----------------------------------------------------------------------------
    Register name:       UDMA_NONSEC_SRC_ADDR_CFG
    Relative address:    0x2000
    Absolute address:    0x41914000
    Description:         uDMA source address for non-secured read master.
                         Must be Word aligned.
    Default Value:       0x00000000

        Field:          MEM_DMA_NONSEC_JOB_SRC_ADDR
        From..to bits:  0..31
        Default Value:  0x00000000
        Access type:    read-write
        Description:    DMA NONSEC JOB SRC ADDR:
                        Specifies source address for non-secured read master.
                        Source address must comply with bit.26 to enable Sec/Non-Sec accesses, otherwise transactions will be blocked.
                        In case using SAU to define secured memory region 'inside' the non-secured, this channel will allow this.

  ----------------------------------------------------------------------------- */
#define HOST_XIP__UDMA_NONSEC_SRC_ADDR_CFG__ADDR             (0x41914000)
#define HOST_XIP__UDMA_NONSEC_SRC_ADDR_CFG                   (0x4003000041914000)

#define HOST_XIP__UDMA_NONSEC_SRC_ADDR_CFG__MEM_DMA_NONSEC_JOB_SRC_ADDR (0x4003000041914000)

/*-----------------------------------------------------------------------------
    Register name:       UDMA_NONSEC_DST_ADDR_CFG
    Relative address:    0x2004
    Absolute address:    0x41914004
    Description:         uDMA destination address for non-secured write master.
                         Must be Word aligned.
    Default Value:       0x00000000

        Field:          MEM_DMA_NONSEC_JOB_DST_ADDR
        From..to bits:  0..31
        Default Value:  0x00000000
        Access type:    read-write
        Description:    DMA NONSEC JOB DST ADDR:
                        Specifies destination address for non-secured write master.
                        Destination address must comply with bit.26 to enable Sec/Non-Sec accesses, otherwise transactions will be blocked.
                        In case using SAU to define secured memory region 'inside' the non-secured, this channel will allow this.

  ----------------------------------------------------------------------------- */
#define HOST_XIP__UDMA_NONSEC_DST_ADDR_CFG__ADDR             (0x41914004)
#define HOST_XIP__UDMA_NONSEC_DST_ADDR_CFG                   (0x4003000041914004)

#define HOST_XIP__UDMA_NONSEC_DST_ADDR_CFG__MEM_DMA_NONSEC_JOB_DST_ADDR (0x4003000041914004)

/*-----------------------------------------------------------------------------
    Register name:       UDMA_NONSEC_LENGTH_CFG
    Relative address:    0x2008
    Absolute address:    0x41914008
    Description:         uDMA non-secured job Length
    Default Value:       0x00000000

        Field:          MEM_DMA_NONSEC_JOB_LENGTH
        From..to bits:  0..17
        Default Value:  0x0000
        Access type:    read-write
        Description:    DMA NONSEC JOB LENGTH:
                        Resolution - 32 bits/4bytes
                        Maximum configurable job size - 1 Mega byte (256K Words).
                        (Maximum available size in MEMSS is 1MB).

  ----------------------------------------------------------------------------- */
#define HOST_XIP__UDMA_NONSEC_LENGTH_CFG__ADDR               (0x41914008)
#define HOST_XIP__UDMA_NONSEC_LENGTH_CFG                     (0x4003000041914008)

#define HOST_XIP__UDMA_NONSEC_LENGTH_CFG__MEM_DMA_NONSEC_JOB_LENGTH (0x400301c041914008)

/*-----------------------------------------------------------------------------
    Register name:       UDMA_NONSEC_MODE_CFG
    Relative address:    0x200c
    Absolute address:    0x4191400c
    Description:         uDMA Direction
    Default Value:       0x00000000

        Field:          MEM_DMA_NONSEC_JOB_MODE
        From..to bits:  0..0
        Default Value:  0x0
        Access type:    read-write
        Description:    DMA NONSEC JOB MODE:
                        0 - Data movement from External memory to Internal memory.
                        1 - Data movement from Internal memory to External memory.

        Field:          MEM_NON_SEC_MODE
        From..to bits:  1..1
        Default Value:  0x0
        Access type:    read-write
        Description:    Non secure channel mode
                        0: Memory Mode
                        1: Peripheral Mode

  ----------------------------------------------------------------------------- */
#define HOST_XIP__UDMA_NONSEC_MODE_CFG__ADDR                 (0x4191400c)
#define HOST_XIP__UDMA_NONSEC_MODE_CFG                       (0x400304004191400c)

#define HOST_XIP__UDMA_NONSEC_MODE_CFG__MEM_DMA_NONSEC_JOB_MODE (0x400307e04191400c)
#define HOST_XIP__UDMA_NONSEC_MODE_CFG__MEM_NON_SEC_MODE     (0x400307c14191400c)

/*-----------------------------------------------------------------------------
    Register name:       UDMA_NONSEC_START
    Relative address:    0x2010
    Absolute address:    0x41914010
    Description:         uDMA non-secured job kick
    Default Value:       0x00000000

        Field:          DMA_NONSEC_JOB_START_WRCL
        From..to bits:  0..0
        Default Value:  0x0
        Access type:    write-only
        Description:    DMA NONSEC JOB START WRCL:
                        Start command for uDMA to start working on non-secured configured job.

  ----------------------------------------------------------------------------- */
#define HOST_XIP__UDMA_NONSEC_START__ADDR                    (0x41914010)
#define HOST_XIP__UDMA_NONSEC_START                          (0x4003000041914010)

#define HOST_XIP__UDMA_NONSEC_START__DMA_NONSEC_JOB_START_WRCL (0x401303e041914010)

/*-----------------------------------------------------------------------------
    Register name:       UDMA_NONSEC_CLEAR
    Relative address:    0x2014
    Absolute address:    0x41914014
    Description:         uDMA non-secured job abort
    Default Value:       0x00000000

        Field:          DMA_NONSEC_JOB_CLEAR_WRCL
        From..to bits:  0..0
        Default Value:  0x0
        Access type:    write-only
        Description:    DMA NONSEC JOB CLEAR WRCL:
                        Clear command for uDMA to stop working and clear configuration.

  ----------------------------------------------------------------------------- */
#define HOST_XIP__UDMA_NONSEC_CLEAR__ADDR                    (0x41914014)
#define HOST_XIP__UDMA_NONSEC_CLEAR                          (0x4003000041914014)

#define HOST_XIP__UDMA_NONSEC_CLEAR__DMA_NONSEC_JOB_CLEAR_WRCL (0x401303e041914014)

/*-----------------------------------------------------------------------------
    Register name:       UDMA_NONSEC_STATUS
    Relative address:    0x2020
    Absolute address:    0x41914020
    Description:         uDMA non-secured Status bits
    Default Value:       0x00000000

        Field:          DMA_NONSEC_JOB_ACTIVE
        From..to bits:  0..0
        Default Value:  0x0
        Access type:    read-only
        Description:    DMA NONSEC JOB ACTIVE:
                        Status bit to indicate that DMA is processing a non-secured job.
                        When this bit is set, SW has written all the job parameters and also provided a start_pulse to HW, 
                        and cannot change job parameters without clear_pulse.
                        Job will wait to be executed (indicated by job_in_progress)

        Field:          DMA_NONSEC_JOB_IN_PROGRESS
        From..to bits:  4..4
        Default Value:  0x0
        Access type:    read-only
        Description:    DMA NONSEC JOB IN PROGRESS:
                        1- nonsec job is currently in progress and being executed by uDMA

        Field:          DMA_NONSEC_JOB_READ_WORDS_LEFT
        From..to bits:  8..27
        Default Value:  0x00000
        Access type:    read-only
        Description:    DMA NONSEC JOB READ WORDS LEFT:
                        Number of read words left in nonsec job
                        Note: This value would be updated on a read to this register. [UDNSSTA1.WRWRDSLFT] is updated on a read to this register
                        This register value shows number of words in 32 bit when field [UDNSCFG3.JDIR] is configured '0' else shows number of words in 8/16/32 bit based on the configuration of [UDNSCFG3.NSMODE] and [UDPERCFG.NSWORDSZ] fields

  ----------------------------------------------------------------------------- */
#define HOST_XIP__UDMA_NONSEC_STATUS__ADDR                   (0x41914020)
#define HOST_XIP__UDMA_NONSEC_STATUS                         (0x400b080041914020)

#define HOST_XIP__UDMA_NONSEC_STATUS__DMA_NONSEC_JOB_ACTIVE  (0x400b0be041914020)
#define HOST_XIP__UDMA_NONSEC_STATUS__DMA_NONSEC_JOB_IN_PROGRESS (0x400b0b6441914020)
#define HOST_XIP__UDMA_NONSEC_STATUS__DMA_NONSEC_JOB_READ_WORDS_LEFT (0x400b088841914020)

/*-----------------------------------------------------------------------------
    Register name:       UDMA_NONSEC_IRQ_STATUS
    Relative address:    0x2024
    Absolute address:    0x41914024
    Description:         uDMA non-secured IRQ Status bits
    Default Value:       0x00000000

        Field:          DMA_NONSEC_JOB_IRQ_STS_RDCL
        From..to bits:  0..1
        Default Value:  0x0
        Access type:    read-only
        Description:    Status vector for IRQ indication for non-secured DMA IRQ:
                        2'd0 - DMA done.
                        2'd1 - DMA bus error occurred. check NONSEC_STATUS in order to recovers

        Field:          DMA_NONSEC_JOB_BUS_ERR_DIR_RDCL
        From..to bits:  2..2
        Default Value:  0x0
        Access type:    read-only
        Description:    Bus Error direction
                        0: Source bus
                        1: Destination bus
                        Note: Source and destination is determined based on [UDMA_NONSEC_MODE_CFG.MEM_DMA_NONSEC_JOB_MODE] configuration

  ----------------------------------------------------------------------------- */
#define HOST_XIP__UDMA_NONSEC_IRQ_STATUS__ADDR               (0x41914024)
#define HOST_XIP__UDMA_NONSEC_IRQ_STATUS                     (0x400b040041914024)

#define HOST_XIP__UDMA_NONSEC_IRQ_STATUS__DMA_NONSEC_JOB_IRQ_STS_RDCL (0x400b07c041914024)
#define HOST_XIP__UDMA_NONSEC_IRQ_STATUS__DMA_NONSEC_JOB_BUS_ERR_DIR_RDCL (0x400b07a241914024)

/*-----------------------------------------------------------------------------
    Register name:       UDMA_THR_CNG
    Relative address:    0x2028
    Absolute address:    0x41914028
    Description:         uDMA threshold configuration
    Default Value:       0x00000090

        Field:          MEM_FIFO_WRITE_THRESH
        From..to bits:  0..4
        Default Value:  0x10
        Access type:    read-write
        Description:    FIFO WRITE THRESHOLD:
                        In case of write to ext mem, uDMA will reach the threshold and after that will send the data to the ext mem
                        Note: 0(Zero) is not allowed

        Field:          MEM_FIFO_WRITE_BURST_LENGTH
        From..to bits:  5..6
        Default Value:  0x0
        Access type:    read-write
        Description:    FIFO WRITE BURST LEN:
                        After uDMA will reached the threshold, uDMA will sent the data in blocks.
                        0x0 : block size = 4   word
                        0x1 : block size = 8   word
                        0x2 : block size = 16 word
                        0x3 : block size = 32 word

  ----------------------------------------------------------------------------- */
#define HOST_XIP__UDMA_THR_CNG__ADDR                         (0x41914028)
#define HOST_XIP__UDMA_THR_CNG                               (0x4003040041914028)

#define HOST_XIP__UDMA_THR_CNG__MEM_FIFO_WRITE_THRESH        (0x4003076041914028)
#define HOST_XIP__UDMA_THR_CNG__MEM_FIFO_WRITE_BURST_LENGTH  (0x4003072541914028)

/*-----------------------------------------------------------------------------
    Register name:       UDMA_NONSEC_STATUS_1
    Relative address:    0x202c
    Absolute address:    0x4191402c
    Description:         uDMA non-secured Status bits in addition to [UDNSSTA] register
    Default Value:       NA

        Field:          DMA_NONSEC_JOB_WRITE_WORDS_LEFT
        From..to bits:  8..27
        Default Value:  0x00000
        Access type:    read-only
        Description:    DMA NONSEC JOB WRITE WORDS LEFT:
                        Number of write words left in nonsec job.
                        Note: This value would be updated only on a read to [UDNSSTA] register.
                        This register value shows number of words in 32 bit when field [UDNSCFG3.JDIR] is configured '1' else shows number of words in 8/16/32 bit based on the configuration of [UDNSCFG3.NSMODE] and [UDPERCFG.NSWORDSZ] fields

        Field:          DMA_NONSEC_PERIPH_WORD_OFFSET
        From..to bits:  0..7
        Default Value:  0x00
        Access type:    read-only
        Description:    DMA NONSEC PERIPH WORD OFFSET:
                        Number of words left in a peripheral block.
                        Note: This value would be updated only on a read to [UDNSSTA] register.
                        This register value shows number of words in 8/16/32 bit based on the configuration of [UDNSCFG3.NSMODE] and [UDPERCFG.NSWORDSZ] fields

  ----------------------------------------------------------------------------- */
#define HOST_XIP__UDMA_NONSEC_STATUS_1__ADDR                 (0x4191402c)
#define HOST_XIP__UDMA_NONSEC_STATUS_1                       (0x400b04004191402c)

#define HOST_XIP__UDMA_NONSEC_STATUS_1__DMA_NONSEC_JOB_WRITE_WORDS_LEFT (0x400b04884191402c)
#define HOST_XIP__UDMA_NONSEC_STATUS_1__DMA_NONSEC_PERIPH_WORD_OFFSET (0x400b07004191402c)

/*-----------------------------------------------------------------------------
    Register name:       UDMA_NONSEC_PERIPHERAL_CFG
    Relative address:    0x2040
    Absolute address:    0x41914040
    Description:         Non secure peirpheral job configuration
    Default Value:       0x00000000

        Field:          MEM_NON_SEC_PERIPH_WORD_SIZE
        From..to bits:  0..1
        Default Value:  0x0
        Access type:    read-write
        Description:    Non-secure channel peripheral job word size
                        8/16/32 (Word Size of 1/2/4 bytes)
                        
                        Sel_0 - 32 bit
                        Sel_1 -  16 bit
                        Sel_2 - 8 bit

        Field:          MEM_NON_SEC_PERIPH_BLOCK_SIZE
        From..to bits:  2..7
        Default Value:  0x0
        Access type:    read-write
        Description:    Non-secure channel peripheral job block size(in 32bits/4bytes)
                        Multiplication of Word size.
                        
                        Upto 64 words based on Word size
                        
                        Block = block_size * word_size

        Field:          MEM_NON_SEC_EN_CLR_AT_START
        From..to bits:  8..8
        Default Value:  0x0
        Access type:    read-write
        Description:    Enable uDMA to set a rd/wr clear pulse at the beginning of a job

  ----------------------------------------------------------------------------- */
#define HOST_XIP__UDMA_NONSEC_PERIPHERAL_CFG__ADDR           (0x41914040)
#define HOST_XIP__UDMA_NONSEC_PERIPHERAL_CFG                 (0x4003080041914040)

#define HOST_XIP__UDMA_NONSEC_PERIPHERAL_CFG__MEM_NON_SEC_PERIPH_WORD_SIZE (0x40030bc041914040)
#define HOST_XIP__UDMA_NONSEC_PERIPHERAL_CFG__MEM_NON_SEC_PERIPH_BLOCK_SIZE (0x40030b0241914040)
#define HOST_XIP__UDMA_NONSEC_PERIPHERAL_CFG__MEM_NON_SEC_EN_CLR_AT_START (0x40030ae841914040)

/*-----------------------------------------------------------------------------
    Register name:       OTFDE_CFG_OSPI
    Relative address:    0x3000
    Absolute address:    0x41915000
    Description:         For Load/Read xSPI config job in OTFDE memory
    Default Value:       0x00000000

        Field:          OTFDE_CFG_OSPI_81FC_WRMEMP
        From..to bits:  0..31
        Default Value:  0x00000000
        Access type:    read-write
        Description:    OTFDE CFG OSPI 81FC WR MEM
                        xSPI config Memory wr/rd access (under OTFDE module)

  ----------------------------------------------------------------------------- */
#define HOST_XIP__OTFDE_CFG_OSPI__ADDR                       (0x41915000)
#define HOST_XIP__OTFDE_CFG_OSPI                             (0x4003000041915000)

#define HOST_XIP__OTFDE_CFG_OSPI__OTFDE_CFG_OSPI_81FC_WRMEMP (0x4003000041915000)

/*-----------------------------------------------------------------------------
    Register name:       SECGA_OTFDE_PROTECTION_CONFIG
    Relative address:    0x4000
    Absolute address:    0x41916000
    Description:         SECGA OTFDE PROTECTION CONFIG:
                         General OTFDE protection Configurations
    Default Value:       0x0000000a

        Field:          MEM_OTFDE_INITIAL_DELAY
        From..to bits:  0..3
        Default Value:  0xa
        Access type:    read-write
        Description:    OTFDE INITIAL DELAY:
                        0-15 160MHz cycles of initial delay of the first transaction of a task
                        must configure value greater than 10 (0xa)

        Field:          MEM_OTFDE_REGION_0_WRITE_LOCK_EN
        From..to bits:  4..4
        Default Value:  0x0
        Access type:    read-write
        Description:    OTFDE REGION 0 WRITE LOCK EN:
                        Locks the ability to write into Region 0 registers
                        0- Lock Disabled
                        1- Lock Enabled

        Field:          MEM_OTFDE_REGION_0_ENC_DEC_BYPASS
        From..to bits:  5..5
        Default Value:  0x0
        Access type:    read-write
        Description:    OTFDE REGION 0 ENC DEC BYPASS:
                        Encrypt  Decrypt or Bypass transactions for region 0
                        0- Enable bypass and no enc dec
                        1- Disable bypass and use enc dec

        Field:          MEM_OTFDE_REGION_1_WRITE_LOCK_EN
        From..to bits:  8..8
        Default Value:  0x0
        Access type:    read-write
        Description:    OTFDE REGION 1 WRITE LOCK EN:
                        Locks the ability to write into Region 1 registers
                        0- Lock Disabled
                        1- Lock Enabled

        Field:          MEM_OTFDE_REGION_1_ENC_DEC_BYPASS
        From..to bits:  9..9
        Default Value:  0x0
        Access type:    read-write
        Description:    OTFDE REGION 1 ENC DEC BYPASS:
                        Encrypt  Decrypt or Bypass transactions for region 1
                        0- Enable bypass and no enc dec
                        1- Disable bypass and use enc dec

        Field:          MEM_OTFDE_REGION_2_WRITE_LOCK_EN
        From..to bits:  12..12
        Default Value:  0x0
        Access type:    read-write
        Description:    OTFDE REGION 2 WRITE LOCK EN:
                        Locks the ability to write into Region 2 registers
                        0- Lock Disabled
                        1- Lock Enabled

        Field:          MEM_OTFDE_REGION_2_ENC_DEC_BYPASS
        From..to bits:  13..13
        Default Value:  0x0
        Access type:    read-write
        Description:    OTFDE REGION 2 ENC DEC BYPASS:
                        Encrypt  Decrypt or Bypass transactions for region 2
                        0- Enable bypass and no enc dec
                        1- Disable bypass and use enc dec

        Field:          MEM_OTFDE_REGION_3_WRITE_LOCK_EN
        From..to bits:  16..16
        Default Value:  0x0
        Access type:    read-write
        Description:    OTFDE REGION 3 WRITE LOCK EN:
                        Locks the ability to write into Region 3 registers
                        0- Lock Disabled
                        1- Lock Enabled

        Field:          MEM_OTFDE_REGION_3_ENC_DEC_BYPASS
        From..to bits:  17..17
        Default Value:  0x0
        Access type:    read-write
        Description:    OTFDE REGION 3 ENC DEC BYPASS:
                        Encrypt  Decrypt or Bypass transactions for region 3
                        0- Enable bypass and no enc dec
                        1- Disable bypass and use enc dec

  ----------------------------------------------------------------------------- */
#define HOST_XIP__SECGA_OTFDE_PROTECTION_CONFIG__ADDR        (0x41916000)
#define HOST_XIP__SECGA_OTFDE_PROTECTION_CONFIG              (0x40030c0041916000)

#define HOST_XIP__SECGA_OTFDE_PROTECTION_CONFIG__MEM_OTFDE_INITIAL_DELAY (0x40030f8041916000)
#define HOST_XIP__SECGA_OTFDE_PROTECTION_CONFIG__MEM_OTFDE_REGION_0_WRITE_LOCK_EN (0x40030f6441916000)
#define HOST_XIP__SECGA_OTFDE_PROTECTION_CONFIG__MEM_OTFDE_REGION_0_ENC_DEC_BYPASS (0x40030f4541916000)
#define HOST_XIP__SECGA_OTFDE_PROTECTION_CONFIG__MEM_OTFDE_REGION_1_WRITE_LOCK_EN (0x40030ee841916000)
#define HOST_XIP__SECGA_OTFDE_PROTECTION_CONFIG__MEM_OTFDE_REGION_1_ENC_DEC_BYPASS (0x40030ec941916000)
#define HOST_XIP__SECGA_OTFDE_PROTECTION_CONFIG__MEM_OTFDE_REGION_2_WRITE_LOCK_EN (0x40030e6c41916000)
#define HOST_XIP__SECGA_OTFDE_PROTECTION_CONFIG__MEM_OTFDE_REGION_2_ENC_DEC_BYPASS (0x40030e4d41916000)
#define HOST_XIP__SECGA_OTFDE_PROTECTION_CONFIG__MEM_OTFDE_REGION_3_WRITE_LOCK_EN (0x40030df041916000)
#define HOST_XIP__SECGA_OTFDE_PROTECTION_CONFIG__MEM_OTFDE_REGION_3_ENC_DEC_BYPASS (0x40030dd141916000)

/*-----------------------------------------------------------------------------
    Register name:       SECGA_REGION_0_KEY_0
    Relative address:    0x4004
    Absolute address:    0x41916004
    Description:         Region 0 key word 0
    Default Value:       0x00000000

        Field:          MEM_REGION_0_KEY_0
        From..to bits:  0..31
        Default Value:  0x00000000
        Access type:    read-write
        Description:    AES encryption Key LSBs

  ----------------------------------------------------------------------------- */
#define HOST_XIP__SECGA_REGION_0_KEY_0__ADDR                 (0x41916004)
#define HOST_XIP__SECGA_REGION_0_KEY_0                       (0x4003000041916004)

#define HOST_XIP__SECGA_REGION_0_KEY_0__MEM_REGION_0_KEY_0   (0x4003000041916004)

/*-----------------------------------------------------------------------------
    Register name:       SECGA_REGION_0_KEY_1
    Relative address:    0x4008
    Absolute address:    0x41916008
    Description:         Region 0 key word 1
    Default Value:       0x00000000

        Field:          MEM_REGION_0_KEY_1
        From..to bits:  0..31
        Default Value:  0x00000000
        Access type:    read-write
        Description:    AES encryption Key

  ----------------------------------------------------------------------------- */
#define HOST_XIP__SECGA_REGION_0_KEY_1__ADDR                 (0x41916008)
#define HOST_XIP__SECGA_REGION_0_KEY_1                       (0x4003000041916008)

#define HOST_XIP__SECGA_REGION_0_KEY_1__MEM_REGION_0_KEY_1   (0x4003000041916008)

/*-----------------------------------------------------------------------------
    Register name:       SECGA_REGION_0_KEY_2
    Relative address:    0x400c
    Absolute address:    0x4191600c
    Description:         Region 0 key word 2
    Default Value:       0x00000000

        Field:          MEM_REGION_0_KEY_2
        From..to bits:  0..31
        Default Value:  0x00000000
        Access type:    read-write
        Description:    AES encryption Key

  ----------------------------------------------------------------------------- */
#define HOST_XIP__SECGA_REGION_0_KEY_2__ADDR                 (0x4191600c)
#define HOST_XIP__SECGA_REGION_0_KEY_2                       (0x400300004191600c)

#define HOST_XIP__SECGA_REGION_0_KEY_2__MEM_REGION_0_KEY_2   (0x400300004191600c)

/*-----------------------------------------------------------------------------
    Register name:       SECGA_REGION_0_KEY_3
    Relative address:    0x4010
    Absolute address:    0x41916010
    Description:         Region 0 key word 3
    Default Value:       0x00000000

        Field:          MEM_REGION_0_KEY_3
        From..to bits:  0..31
        Default Value:  0x00000000
        Access type:    read-write
        Description:    AES encryption Key MSBs

  ----------------------------------------------------------------------------- */
#define HOST_XIP__SECGA_REGION_0_KEY_3__ADDR                 (0x41916010)
#define HOST_XIP__SECGA_REGION_0_KEY_3                       (0x4003000041916010)

#define HOST_XIP__SECGA_REGION_0_KEY_3__MEM_REGION_0_KEY_3   (0x4003000041916010)

/*-----------------------------------------------------------------------------
    Register name:       SECGA_REGION_0_NONCE_0
    Relative address:    0x4014
    Absolute address:    0x41916014
    Description:         Region 0 nonce word 0
    Default Value:       0x00000000

        Field:          MEM_REGION_0_NONCE_0
        From..to bits:  0..31
        Default Value:  0x00000000
        Access type:    read-write
        Description:    Nonce (IV)

  ----------------------------------------------------------------------------- */
#define HOST_XIP__SECGA_REGION_0_NONCE_0__ADDR               (0x41916014)
#define HOST_XIP__SECGA_REGION_0_NONCE_0                     (0x4003000041916014)

#define HOST_XIP__SECGA_REGION_0_NONCE_0__MEM_REGION_0_NONCE_0 (0x4003000041916014)

/*-----------------------------------------------------------------------------
    Register name:       SECGA_REGION_0_NONCE_1
    Relative address:    0x4018
    Absolute address:    0x41916018
    Description:         Region 0 nonce word 1
    Default Value:       0x00000000

        Field:          MEM_REGION_0_NONCE_1
        From..to bits:  0..31
        Default Value:  0x00000000
        Access type:    read-write
        Description:    Nonce (IV)

  ----------------------------------------------------------------------------- */
#define HOST_XIP__SECGA_REGION_0_NONCE_1__ADDR               (0x41916018)
#define HOST_XIP__SECGA_REGION_0_NONCE_1                     (0x4003000041916018)

#define HOST_XIP__SECGA_REGION_0_NONCE_1__MEM_REGION_0_NONCE_1 (0x4003000041916018)

/*-----------------------------------------------------------------------------
    Register name:       SECGA_REGION_1_KEY_0
    Relative address:    0x4020
    Absolute address:    0x41916020
    Description:         Region 1 key word 0
    Default Value:       0x00000000

        Field:          MEM_REGION_1_KEY_0
        From..to bits:  0..31
        Default Value:  0x00000000
        Access type:    read-write
        Description:    AES encryption Key LSBs

  ----------------------------------------------------------------------------- */
#define HOST_XIP__SECGA_REGION_1_KEY_0__ADDR                 (0x41916020)
#define HOST_XIP__SECGA_REGION_1_KEY_0                       (0x4003000041916020)

#define HOST_XIP__SECGA_REGION_1_KEY_0__MEM_REGION_1_KEY_0   (0x4003000041916020)

/*-----------------------------------------------------------------------------
    Register name:       SECGA_REGION_1_KEY_1
    Relative address:    0x4024
    Absolute address:    0x41916024
    Description:         Region 1 key word 1
    Default Value:       0x00000000

        Field:          MEM_REGION_1_KEY_1
        From..to bits:  0..31
        Default Value:  0x00000000
        Access type:    read-write
        Description:    AES encryption Key

  ----------------------------------------------------------------------------- */
#define HOST_XIP__SECGA_REGION_1_KEY_1__ADDR                 (0x41916024)
#define HOST_XIP__SECGA_REGION_1_KEY_1                       (0x4003000041916024)

#define HOST_XIP__SECGA_REGION_1_KEY_1__MEM_REGION_1_KEY_1   (0x4003000041916024)

/*-----------------------------------------------------------------------------
    Register name:       SECGA_REGION_1_KEY_2
    Relative address:    0x4028
    Absolute address:    0x41916028
    Description:         Region 1 key word 2
    Default Value:       0x00000000

        Field:          MEM_REGION_1_KEY_2
        From..to bits:  0..31
        Default Value:  0x00000000
        Access type:    read-write
        Description:    AES encryption Key

  ----------------------------------------------------------------------------- */
#define HOST_XIP__SECGA_REGION_1_KEY_2__ADDR                 (0x41916028)
#define HOST_XIP__SECGA_REGION_1_KEY_2                       (0x4003000041916028)

#define HOST_XIP__SECGA_REGION_1_KEY_2__MEM_REGION_1_KEY_2   (0x4003000041916028)

/*-----------------------------------------------------------------------------
    Register name:       SECGA_REGION_1_KEY_3
    Relative address:    0x402c
    Absolute address:    0x4191602c
    Description:         Region 1 key word 3
    Default Value:       0x00000000

        Field:          MEM_REGION_1_KEY_3
        From..to bits:  0..31
        Default Value:  0x00000000
        Access type:    read-write
        Description:    AES encryption Key MSBs

  ----------------------------------------------------------------------------- */
#define HOST_XIP__SECGA_REGION_1_KEY_3__ADDR                 (0x4191602c)
#define HOST_XIP__SECGA_REGION_1_KEY_3                       (0x400300004191602c)

#define HOST_XIP__SECGA_REGION_1_KEY_3__MEM_REGION_1_KEY_3   (0x400300004191602c)

/*-----------------------------------------------------------------------------
    Register name:       SECGA_REGION_1_NONCE_0
    Relative address:    0x4030
    Absolute address:    0x41916030
    Description:         Region 1 nonce word 0
    Default Value:       0x00000000

        Field:          MEM_REGION_1_NONCE_0
        From..to bits:  0..31
        Default Value:  0x00000000
        Access type:    read-write
        Description:    Nonce (IV)

  ----------------------------------------------------------------------------- */
#define HOST_XIP__SECGA_REGION_1_NONCE_0__ADDR               (0x41916030)
#define HOST_XIP__SECGA_REGION_1_NONCE_0                     (0x4003000041916030)

#define HOST_XIP__SECGA_REGION_1_NONCE_0__MEM_REGION_1_NONCE_0 (0x4003000041916030)

/*-----------------------------------------------------------------------------
    Register name:       SECGA_REGION_1_NONCE_1
    Relative address:    0x4034
    Absolute address:    0x41916034
    Description:         Region 1 nonce word 1
    Default Value:       0x00000000

        Field:          MEM_REGION_1_NONCE_1
        From..to bits:  0..31
        Default Value:  0x00000000
        Access type:    read-write
        Description:    Nonce (IV)

  ----------------------------------------------------------------------------- */
#define HOST_XIP__SECGA_REGION_1_NONCE_1__ADDR               (0x41916034)
#define HOST_XIP__SECGA_REGION_1_NONCE_1                     (0x4003000041916034)

#define HOST_XIP__SECGA_REGION_1_NONCE_1__MEM_REGION_1_NONCE_1 (0x4003000041916034)

/*-----------------------------------------------------------------------------
    Register name:       SECGA_REGION_2_KEY_0
    Relative address:    0x4040
    Absolute address:    0x41916040
    Description:         Region 2 key word 0
    Default Value:       0x00000000

        Field:          MEM_REGION_2_KEY_0
        From..to bits:  0..31
        Default Value:  0x00000000
        Access type:    read-write
        Description:    AES encryption Key LSBs

  ----------------------------------------------------------------------------- */
#define HOST_XIP__SECGA_REGION_2_KEY_0__ADDR                 (0x41916040)
#define HOST_XIP__SECGA_REGION_2_KEY_0                       (0x4003000041916040)

#define HOST_XIP__SECGA_REGION_2_KEY_0__MEM_REGION_2_KEY_0   (0x4003000041916040)

/*-----------------------------------------------------------------------------
    Register name:       SECGA_REGION_2_KEY_1
    Relative address:    0x4044
    Absolute address:    0x41916044
    Description:         Region 1 key word 1
    Default Value:       0x00000000

        Field:          MEM_REGION_2_KEY_1
        From..to bits:  0..31
        Default Value:  0x00000000
        Access type:    read-write
        Description:    AES encryption Key

  ----------------------------------------------------------------------------- */
#define HOST_XIP__SECGA_REGION_2_KEY_1__ADDR                 (0x41916044)
#define HOST_XIP__SECGA_REGION_2_KEY_1                       (0x4003000041916044)

#define HOST_XIP__SECGA_REGION_2_KEY_1__MEM_REGION_2_KEY_1   (0x4003000041916044)

/*-----------------------------------------------------------------------------
    Register name:       SECGA_REGION_2_KEY_2
    Relative address:    0x4048
    Absolute address:    0x41916048
    Description:         Region 1 key word 2
    Default Value:       0x00000000

        Field:          MEM_REGION_2_KEY_2
        From..to bits:  0..31
        Default Value:  0x00000000
        Access type:    read-write
        Description:    AES encryption Key

  ----------------------------------------------------------------------------- */
#define HOST_XIP__SECGA_REGION_2_KEY_2__ADDR                 (0x41916048)
#define HOST_XIP__SECGA_REGION_2_KEY_2                       (0x4003000041916048)

#define HOST_XIP__SECGA_REGION_2_KEY_2__MEM_REGION_2_KEY_2   (0x4003000041916048)

/*-----------------------------------------------------------------------------
    Register name:       SECGA_REGION_2_KEY_3
    Relative address:    0x404c
    Absolute address:    0x4191604c
    Description:         Region 1 key word 3
    Default Value:       0x00000000

        Field:          MEM_REGION_2_KEY_3
        From..to bits:  0..31
        Default Value:  0x00000000
        Access type:    read-write
        Description:    AES encryption Key MSBs

  ----------------------------------------------------------------------------- */
#define HOST_XIP__SECGA_REGION_2_KEY_3__ADDR                 (0x4191604c)
#define HOST_XIP__SECGA_REGION_2_KEY_3                       (0x400300004191604c)

#define HOST_XIP__SECGA_REGION_2_KEY_3__MEM_REGION_2_KEY_3   (0x400300004191604c)

/*-----------------------------------------------------------------------------
    Register name:       SECGA_REGION_2_NONCE_0
    Relative address:    0x4050
    Absolute address:    0x41916050
    Description:         Region 2 nonce word 0
    Default Value:       0x00000000

        Field:          MEM_REGION_2_NONCE_0
        From..to bits:  0..31
        Default Value:  0x00000000
        Access type:    read-write
        Description:    Nonce (IV)

  ----------------------------------------------------------------------------- */
#define HOST_XIP__SECGA_REGION_2_NONCE_0__ADDR               (0x41916050)
#define HOST_XIP__SECGA_REGION_2_NONCE_0                     (0x4003000041916050)

#define HOST_XIP__SECGA_REGION_2_NONCE_0__MEM_REGION_2_NONCE_0 (0x4003000041916050)

/*-----------------------------------------------------------------------------
    Register name:       SECGA_REGION_2_NONCE_1
    Relative address:    0x4054
    Absolute address:    0x41916054
    Description:         Region 2 nonce word 1
    Default Value:       0x00000000

        Field:          MEM_REGION_2_NONCE_1
        From..to bits:  0..31
        Default Value:  0x00000000
        Access type:    read-write
        Description:    Nonce (IV)

  ----------------------------------------------------------------------------- */
#define HOST_XIP__SECGA_REGION_2_NONCE_1__ADDR               (0x41916054)
#define HOST_XIP__SECGA_REGION_2_NONCE_1                     (0x4003000041916054)

#define HOST_XIP__SECGA_REGION_2_NONCE_1__MEM_REGION_2_NONCE_1 (0x4003000041916054)

/*-----------------------------------------------------------------------------
    Register name:       SECGA_REGION_3_KEY_0
    Relative address:    0x4060
    Absolute address:    0x41916060
    Description:         Region 3 key word 0
    Default Value:       0x00000000

        Field:          MEM_REGION_3_KEY_0
        From..to bits:  0..31
        Default Value:  0x00000000
        Access type:    read-write
        Description:    AES encryption Key LSBs

  ----------------------------------------------------------------------------- */
#define HOST_XIP__SECGA_REGION_3_KEY_0__ADDR                 (0x41916060)
#define HOST_XIP__SECGA_REGION_3_KEY_0                       (0x4003000041916060)

#define HOST_XIP__SECGA_REGION_3_KEY_0__MEM_REGION_3_KEY_0   (0x4003000041916060)

/*-----------------------------------------------------------------------------
    Register name:       SECGA_REGION_3_KEY_1
    Relative address:    0x4064
    Absolute address:    0x41916064
    Description:         Region 3 key word 1
    Default Value:       0x00000000

        Field:          MEM_REGION_3_KEY_1
        From..to bits:  0..31
        Default Value:  0x00000000
        Access type:    read-write
        Description:    AES encryption Key

  ----------------------------------------------------------------------------- */
#define HOST_XIP__SECGA_REGION_3_KEY_1__ADDR                 (0x41916064)
#define HOST_XIP__SECGA_REGION_3_KEY_1                       (0x4003000041916064)

#define HOST_XIP__SECGA_REGION_3_KEY_1__MEM_REGION_3_KEY_1   (0x4003000041916064)

/*-----------------------------------------------------------------------------
    Register name:       SECGA_REGION_3_KEY_2
    Relative address:    0x4068
    Absolute address:    0x41916068
    Description:         Region 3 key word 2
    Default Value:       0x00000000

        Field:          MEM_REGION_3_KEY_2
        From..to bits:  0..31
        Default Value:  0x00000000
        Access type:    read-write
        Description:    AES encryption Key

  ----------------------------------------------------------------------------- */
#define HOST_XIP__SECGA_REGION_3_KEY_2__ADDR                 (0x41916068)
#define HOST_XIP__SECGA_REGION_3_KEY_2                       (0x4003000041916068)

#define HOST_XIP__SECGA_REGION_3_KEY_2__MEM_REGION_3_KEY_2   (0x4003000041916068)

/*-----------------------------------------------------------------------------
    Register name:       SECGA_REGION_3_KEY_3
    Relative address:    0x406c
    Absolute address:    0x4191606c
    Description:         Region 3 key word 3
    Default Value:       0x00000000

        Field:          MEM_REGION_3_KEY_3
        From..to bits:  0..31
        Default Value:  0x00000000
        Access type:    read-write
        Description:    AES encryption Key MSBs

  ----------------------------------------------------------------------------- */
#define HOST_XIP__SECGA_REGION_3_KEY_3__ADDR                 (0x4191606c)
#define HOST_XIP__SECGA_REGION_3_KEY_3                       (0x400300004191606c)

#define HOST_XIP__SECGA_REGION_3_KEY_3__MEM_REGION_3_KEY_3   (0x400300004191606c)

/*-----------------------------------------------------------------------------
    Register name:       SECGA_REGION_3_NONCE_0
    Relative address:    0x4070
    Absolute address:    0x41916070
    Description:         Region 3 nonce word 0
    Default Value:       0x00000000

        Field:          MEM_REGION_3_NONCE_0
        From..to bits:  0..31
        Default Value:  0x00000000
        Access type:    read-write
        Description:    Nonce (IV)

  ----------------------------------------------------------------------------- */
#define HOST_XIP__SECGA_REGION_3_NONCE_0__ADDR               (0x41916070)
#define HOST_XIP__SECGA_REGION_3_NONCE_0                     (0x4003000041916070)

#define HOST_XIP__SECGA_REGION_3_NONCE_0__MEM_REGION_3_NONCE_0 (0x4003000041916070)

/*-----------------------------------------------------------------------------
    Register name:       SECGA_REGION_3_NONCE_1
    Relative address:    0x4074
    Absolute address:    0x41916074
    Description:         Region 3 nonce word 1
    Default Value:       0x00000000

        Field:          MEM_REGION_3_NONCE_1
        From..to bits:  0..31
        Default Value:  0x00000000
        Access type:    read-write
        Description:    Nonce (IV)

  ----------------------------------------------------------------------------- */
#define HOST_XIP__SECGA_REGION_3_NONCE_1__ADDR               (0x41916074)
#define HOST_XIP__SECGA_REGION_3_NONCE_1                     (0x4003000041916074)

#define HOST_XIP__SECGA_REGION_3_NONCE_1__MEM_REGION_3_NONCE_1 (0x4003000041916074)

/*-----------------------------------------------------------------------------
    Register name:       OTFDE_ENABLE_CONFIG
    Relative address:    0x5000
    Absolute address:    0x41917000
    Description:         Pulse signaled by SW to enable OTFDE and start handling incoming tasks
    Default Value:       0x00000000

        Field:          OTFDE_SW_ENABLE_REQ_WRCL
        From..to bits:  0..0
        Default Value:  0x0
        Access type:    write-only
        Description:    OTFDE SW ENABLE REQ WRCL:
                        Pulse signaled by SW to enable OTFDE and start handling incoming tasks

  ----------------------------------------------------------------------------- */
#define HOST_XIP__OTFDE_ENABLE_CONFIG__ADDR                  (0x41917000)
#define HOST_XIP__OTFDE_ENABLE_CONFIG                        (0x4003000041917000)

#define HOST_XIP__OTFDE_ENABLE_CONFIG__OTFDE_SW_ENABLE_REQ_WRCL (0x401303e041917000)

/*-----------------------------------------------------------------------------
    Register name:       OTFDE_DISABLE_CONFIG
    Relative address:    0x5004
    Absolute address:    0x41917004
    Description:         Pulse signaled by SW to disable OTFDE and stop handling incoming task
                         and erase all task related data
    Default Value:       0x00000000

        Field:          OTFDE_SW_DISBALE_REQ_WRCL
        From..to bits:  0..0
        Default Value:  0x0
        Access type:    write-only
        Description:    OTFDE SW DISABLE REQ WRCL:
                        Pulse signaled by SW to disable OTFDE and stop handling incoming task 
                        and erase all task related data

  ----------------------------------------------------------------------------- */
#define HOST_XIP__OTFDE_DISABLE_CONFIG__ADDR                 (0x41917004)
#define HOST_XIP__OTFDE_DISABLE_CONFIG                       (0x4003000041917004)

#define HOST_XIP__OTFDE_DISABLE_CONFIG__OTFDE_SW_DISBALE_REQ_WRCL (0x401303e041917004)

/*-----------------------------------------------------------------------------
    Register name:       OTFDE_SUSPEND_CONFIG
    Relative address:    0x5008
    Absolute address:    0x41917008
    Description:         Pulse signaled by SW to suspend OTFDE task and hold task related data
    Default Value:       0x00000000

        Field:          OTFDE_SW_SUSPEND_TASK_REQ_WRCL
        From..to bits:  0..0
        Default Value:  0x0
        Access type:    write-only
        Description:    OTFDE SW SUSPEND TASK REQ WRCL:
                        Pulse signaled by SW to suspend OTFDE task and hold task related data

  ----------------------------------------------------------------------------- */
#define HOST_XIP__OTFDE_SUSPEND_CONFIG__ADDR                 (0x41917008)
#define HOST_XIP__OTFDE_SUSPEND_CONFIG                       (0x4003000041917008)

#define HOST_XIP__OTFDE_SUSPEND_CONFIG__OTFDE_SW_SUSPEND_TASK_REQ_WRCL (0x401303e041917008)

/*-----------------------------------------------------------------------------
    Register name:       OTFDE_RESUME_CONFIG
    Relative address:    0x500c
    Absolute address:    0x4191700c
    Description:         Pulse signaled by SW to resume OTFDE suspended task
    Default Value:       0x00000000

        Field:          OTFDE_SW_RESUME_TASK_REQ_WRCL
        From..to bits:  0..0
        Default Value:  0x0
        Access type:    write-only
        Description:    OTFDE SW RESUME TASK REQ WRCL:
                        Pulse signaled by SW to resume OTFDE suspended task

  ----------------------------------------------------------------------------- */
#define HOST_XIP__OTFDE_RESUME_CONFIG__ADDR                  (0x4191700c)
#define HOST_XIP__OTFDE_RESUME_CONFIG                        (0x400300004191700c)

#define HOST_XIP__OTFDE_RESUME_CONFIG__OTFDE_SW_RESUME_TASK_REQ_WRCL (0x401303e04191700c)

/*-----------------------------------------------------------------------------
    Register name:       OTFDE_SOFT_RESET_CONFIG
    Relative address:    0x5010
    Absolute address:    0x41917010
    Description:         Pulse signaled by SW to soft reset OTFDE engine and fifo and move to active idle
    Default Value:       0x00000000

        Field:          OTFDE_SW_SOFT_RESET_REQ_WRCL
        From..to bits:  0..0
        Default Value:  0x0
        Access type:    write-only
        Description:    OTFDE SW SOFT RESET REQ WRCL:
                        1- Soft Reset request pulse

  ----------------------------------------------------------------------------- */
#define HOST_XIP__OTFDE_SOFT_RESET_CONFIG__ADDR              (0x41917010)
#define HOST_XIP__OTFDE_SOFT_RESET_CONFIG                    (0x4003000041917010)

#define HOST_XIP__OTFDE_SOFT_RESET_CONFIG__OTFDE_SW_SOFT_RESET_REQ_WRCL (0x401303e041917010)

/*-----------------------------------------------------------------------------
    Register name:       OTFDE_GENERAL_CONFIG_0
    Relative address:    0x5020
    Absolute address:    0x41917020
    Description:         OTFDE status
    Default Value:       0x00000100

        Field:          OTFDE_ACTIVE
        From..to bits:  0..0
        Default Value:  0x0
        Access type:    read-only
        Description:    OTFDE ACTIVE:
                        0- OTFDE is disabled IF OTFDE_TASK_SUSPENDED is also de-asserted
                        1- OTFDE is active

        Field:          OTFDE_TASK_SUSPENDED
        From..to bits:  1..1
        Default Value:  0x0
        Access type:    read-only
        Description:    OTFDE TASK SUSPENDED
                        1- OTFDE is in task suspended mode
                        0- OTFDE is either active or disabled (IF OTFDE_ACTIVE is also de-asserted then OTFDE is disabled)

        Field:          OTFDE_SELECT_EXTERNAL_MUX
        From..to bits:  2..2
        Default Value:  0x0
        Access type:    read-only
        Description:    OTFDE SELECT EXTERNAL MUX:
                        0- External Muxes bypassing OTFDE allowing System/ SW access to xspi
                        1- External Muxes are controlled by OTFDE which is Active and has access to xspi

        Field:          OTFDE_ACTIVE_TASK_VALID
        From..to bits:  3..3
        Default Value:  0x0
        Access type:    read-only
        Description:    OTFDE ACTIVE TASK VALID:
                        0- No task is being handled, 
                        1- A   task is being handled,
                        note: decide if OTFDE is active or suspended using OTFDE_ACTIVE and OTFDE_TASK_SUSPENDED

        Field:          OTFDE_ACTIVE_TASK_TYPE
        From..to bits:  4..4
        Default Value:  0x0
        Access type:    read-only
        Description:    OTFDE ACTIVE TASK TYPE:
                        0- Active read task
                        1- Active write task
                        value is valid only if OTFDE_ACTIVE or OTFDE_TASK_SUSPENDED are set

        Field:          OTFDE_ACTIVE_TASK_DEVICE
        From..to bits:  5..5
        Default Value:  0x0
        Access type:    read-only
        Description:    OTFDE ACTIVE TASK DEVICE:
                        0- Device 0 active task
                        1- Device 1 active task
                        value is valid only if OTFDE_ACTIVE or OTFDE_TASK_SUSPENDED are set

        Field:          OTFDE_ACTIVE_TASK_REGION
        From..to bits:  6..7
        Default Value:  0x0
        Access type:    read-only
        Description:    OTFDE ACTIVE TASK REGION:
                        0- Region 0 active task
                        1- Region 1 active task
                        2- Region 2 active task
                        3- Region 3 active task
                        value is valid only if OTFDE_ACTIVE or OTFDE_TASK_SUSPENDED are set

        Field:          OTFDE_NOT_BUSY
        From..to bits:  8..8
        Default Value:  0x1
        Access type:    read-only
        Description:    OTFDE IS NOT BUSY.
                        This bit set when OTFDE NOT in the middle of configuration or transmitting data.
                        OTFDE can be halted only when this bit is set.

  ----------------------------------------------------------------------------- */
#define HOST_XIP__OTFDE_GENERAL_CONFIG_0__ADDR               (0x41917020)
#define HOST_XIP__OTFDE_GENERAL_CONFIG_0                     (0x400b0c0041917020)

#define HOST_XIP__OTFDE_GENERAL_CONFIG_0__OTFDE_ACTIVE       (0x400b0fe041917020)
#define HOST_XIP__OTFDE_GENERAL_CONFIG_0__OTFDE_TASK_SUSPENDED (0x400b0fc141917020)
#define HOST_XIP__OTFDE_GENERAL_CONFIG_0__OTFDE_SELECT_EXTERNAL_MUX (0x400b0fa241917020)
#define HOST_XIP__OTFDE_GENERAL_CONFIG_0__OTFDE_ACTIVE_TASK_VALID (0x400b0f8341917020)
#define HOST_XIP__OTFDE_GENERAL_CONFIG_0__OTFDE_ACTIVE_TASK_TYPE (0x400b0f6441917020)
#define HOST_XIP__OTFDE_GENERAL_CONFIG_0__OTFDE_ACTIVE_TASK_DEVICE (0x400b0f4541917020)
#define HOST_XIP__OTFDE_GENERAL_CONFIG_0__OTFDE_ACTIVE_TASK_REGION (0x400b0f0641917020)
#define HOST_XIP__OTFDE_GENERAL_CONFIG_0__OTFDE_NOT_BUSY     (0x400b0ee841917020)

/*-----------------------------------------------------------------------------
    Register name:       OTFDE_GENERAL_CONFIG_1
    Relative address:    0x5030
    Absolute address:    0x41917030
    Description:         Event indication
    Default Value:       0x00000000

        Field:          OTFDE_RESET_EVENT_RDCL
        From..to bits:  0..0
        Default Value:  0x0
        Access type:    read-only
        Description:    OTFDE RESET EVENT RDCL:
                        0 - Disable
                        1- Set Indication
                        OTFDE Hard reset or Disable request completion event indication

        Field:          OTFDE_SOFT_RESET_EVENT_RDCL
        From..to bits:  1..1
        Default Value:  0x0
        Access type:    read-only
        Description:    OTFDE SOFT RESET EVENT RDCL:
                        0 - Disable
                        1- Set Indication
                        OTFDE Soft reset completion event indication

        Field:          OTFDE_BYPASS_MODE_CHANGE_EVENT_RDCL
        From..to bits:  2..2
        Default Value:  0x0
        Access type:    read-only
        Description:    OTFDE BYPASS MODE CHANGE EVENT RDCL:
                        0 - Disable
                        1- Set Indication
                        OTFDE entered or exited bypass mode between suspend and resume states

        Field:          OTFDE_GENERAL_ERROR_RDCL
        From..to bits:  4..4
        Default Value:  0x0
        Access type:    read-only
        Description:    OTFDE GENERAL ERROR RDCL:
                        0 - Disable
                        1- Set Indication
                        General error event indication

        Field:          OTFDE_XSPI_DATA_PATH_ERROR_RDCL
        From..to bits:  5..5
        Default Value:  0x0
        Access type:    read-only
        Description:    OTFDE XSPI DATA PATH ERROR_RDCL:
                        0 - Disable
                        1- Set Indication
                        xSPI error on the data path to OTFDE

        Field:          OTFDE_XSPI_CNFG_PATH_ERROR_RDCL
        From..to bits:  6..6
        Default Value:  0x0
        Access type:    read-only
        Description:    OTFDE XSPI CNFG PATH ERROR RDCL:
                        0 - Disable
                        1- Set Indication
                        xSPI error on the config path to OTFDE

        Field:          OTFDE_XSPI_SERVICE_INTERRUPT_INDICATION_RDCL
        From..to bits:  7..7
        Default Value:  0x0
        Access type:    read-only
        Description:    OTFDE XSPI SERVICE INTERRUPT INDICATION RDCL:
                        0 - Disable
                        1- Set Indication
                        indication that service interruption criteria was triggered

        Field:          OTFDE_TRANS_DEVICE_DISABLED_ERROR_RDCL
        From..to bits:  8..8
        Default Value:  0x0
        Access type:    read-only
        Description:    OTFDE TRANS DEVICE DISABLED ERROR RDCL:
                        0 - Disable
                        1- Set Indication
                        indication that the current transaction is into a disabled device

        Field:          OTFDE_TRANS_REGION_DISABLED_ERROR_RDCL
        From..to bits:  9..9
        Default Value:  0x0
        Access type:    read-only
        Description:    OTFDE TRANS REGION DISABLED ERROR RDCL:
                        0 - Disable
                        1- Set Indication
                        indication that the current transaction is into a disabled region

        Field:          OTFDE_TRANS_XSPI_POLLING_ITR_EXPIRED_RDCL
        From..to bits:  10..10
        Default Value:  0x0
        Access type:    read-only
        Description:    OTFDE TRANS XSPI POLLING ITR EXPIRED RDCL:
                        0 - Disable
                        1- Set Indication
                        Polling Request iterations expired

        Field:          OTFDE_TRANS_MULTIPLE_REGIONS_MAPPED_ERROR_RDCL
        From..to bits:  11..11
        Default Value:  0x0
        Access type:    read-only
        Description:    OTFDE TRANS MULTIPLE REGIONS MAPPED ERROR RDCL:
                        0 - Disable
                        1- Set Indication
                        Indication that a transaction was mapped into more than one region

        Field:          OTFDE_TRANS_ADDRESS_NOT_32_BIT_VIOLATION_RDCL
        From..to bits:  12..12
        Default Value:  0x0
        Access type:    read-only
        Description:    OTFDE TRANS ADDRESS NOT 32 BIT VIOLATION RDCL:
                        0 - Disable
                        1- Set Indication
                        Indication that a transaction address was not 32 bit aligned

        Field:          OTFDE_TRANS_SIZE_NOT_32_BIT_VIOLATION_RDCL
        From..to bits:  13..13
        Default Value:  0x0
        Access type:    read-only
        Description:    OTFDE TRANS SIZE NOT 32 BIT VIOLATION RDCL:
                        0 - Disable
                        1- Set Indication
                        Indication that a transaction size was not 32 bit

        Field:          OTFDE_TRANS_BURST_NOT_32_BIT_VIOLATION_RDCL
        From..to bits:  14..14
        Default Value:  0x0
        Access type:    read-only
        Description:    OTFDE TRANS BURST NOT 32 BIT VIOLATION RDCL:
                        0 - Disable
                        1- Set Indication
                        Indication that a transaction burst was not non-seq

        Field:          OTFDE_REGION_READ_WRITE_DEF_VIOLATION_RDCL
        From..to bits:  15..15
        Default Value:  0x0
        Access type:    read-only
        Description:    OTFDE REGION READ WRITE DEF VIOLATION RDCL:
                        0 - Disable
                        1- Set Indication
                        Indication that a transaction type was not allowed according to region definitions

        Field:          OTFDE_SW_SUSPEND_REQ_WHILE_DISABLED_RDCL
        From..to bits:  16..16
        Default Value:  0x0
        Access type:    read-only
        Description:    OTFDE SW SUSPEND REQ WHILE DISABLED RDCL:
                        0 - Disable
                        1- Set Indication
                        indication that SW requested suspend while OTFDE is disabled

  ----------------------------------------------------------------------------- */
#define HOST_XIP__OTFDE_GENERAL_CONFIG_1__ADDR               (0x41917030)
#define HOST_XIP__OTFDE_GENERAL_CONFIG_1                     (0x400b0c0041917030)

#define HOST_XIP__OTFDE_GENERAL_CONFIG_1__OTFDE_RESET_EVENT_RDCL (0x400b0fe041917030)
#define HOST_XIP__OTFDE_GENERAL_CONFIG_1__OTFDE_SOFT_RESET_EVENT_RDCL (0x400b0fc141917030)
#define HOST_XIP__OTFDE_GENERAL_CONFIG_1__OTFDE_BYPASS_MODE_CHANGE_EVENT_RDCL (0x400b0fa241917030)
#define HOST_XIP__OTFDE_GENERAL_CONFIG_1__OTFDE_GENERAL_ERROR_RDCL (0x400b0f6441917030)
#define HOST_XIP__OTFDE_GENERAL_CONFIG_1__OTFDE_XSPI_DATA_PATH_ERROR_RDCL (0x400b0f4541917030)
#define HOST_XIP__OTFDE_GENERAL_CONFIG_1__OTFDE_XSPI_CNFG_PATH_ERROR_RDCL (0x400b0f2641917030)
#define HOST_XIP__OTFDE_GENERAL_CONFIG_1__OTFDE_XSPI_SERVICE_INTERRUPT_INDICATION_RDCL (0x400b0f0741917030)
#define HOST_XIP__OTFDE_GENERAL_CONFIG_1__OTFDE_TRANS_DEVICE_DISABLED_ERROR_RDCL (0x400b0ee841917030)
#define HOST_XIP__OTFDE_GENERAL_CONFIG_1__OTFDE_TRANS_REGION_DISABLED_ERROR_RDCL (0x400b0ec941917030)
#define HOST_XIP__OTFDE_GENERAL_CONFIG_1__OTFDE_TRANS_XSPI_POLLING_ITR_EXPIRED_RDCL (0x400b0eaa41917030)
#define HOST_XIP__OTFDE_GENERAL_CONFIG_1__OTFDE_TRANS_MULTIPLE_REGIONS_MAPPED_ERROR_RDCL (0x400b0e8b41917030)
#define HOST_XIP__OTFDE_GENERAL_CONFIG_1__OTFDE_TRANS_ADDRESS_NOT_32_BIT_VIOLATION_RDCL (0x400b0e6c41917030)
#define HOST_XIP__OTFDE_GENERAL_CONFIG_1__OTFDE_TRANS_SIZE_NOT_32_BIT_VIOLATION_RDCL (0x400b0e4d41917030)
#define HOST_XIP__OTFDE_GENERAL_CONFIG_1__OTFDE_TRANS_BURST_NOT_32_BIT_VIOLATION_RDCL (0x400b0e2e41917030)
#define HOST_XIP__OTFDE_GENERAL_CONFIG_1__OTFDE_REGION_READ_WRITE_DEF_VIOLATION_RDCL (0x400b0e0f41917030)
#define HOST_XIP__OTFDE_GENERAL_CONFIG_1__OTFDE_SW_SUSPEND_REQ_WHILE_DISABLED_RDCL (0x400b0df041917030)

/*-----------------------------------------------------------------------------
    Register name:       OTFDE_GENERAL_CONFIG_2
    Relative address:    0x5040
    Absolute address:    0x41917040
    Description:         Event Masked
    Default Value:       0x0001ffff

        Field:          MEM_OTFDE_RESET_MASK
        From..to bits:  0..0
        Default Value:  0x1
        Access type:    read-write
        Description:    OTFDE RESET MASK:
                        0- Masked 
                        1- Enabled
                        Enable / Mask hard reset completion event

        Field:          MEM_OTFDE_SOFT_RESET_MASK
        From..to bits:  1..1
        Default Value:  0x1
        Access type:    read-write
        Description:    OTFDE SOFT RESET MASK:
                        0- Masked 
                        1- Enabled
                        Enable / Mask soft reset completion event

        Field:          MEM_OTFDE_BYPASS_MODE_CHANGE_MASK
        From..to bits:  2..2
        Default Value:  0x1
        Access type:    read-write
        Description:    OTFDE BYPASS MODE CHANGE MASK:
                        0- Masked
                        1- Enabled
                        Enable / Mask bypass mode change between suspend and resume completion event

        Field:          MEM_OTFDE_GENERAL_MASK
        From..to bits:  4..4
        Default Value:  0x1
        Access type:    read-write
        Description:    OTFDE GENERAL MASK:
                        0- Masked
                        1- Enabled
                        Enable / Mask general error event

        Field:          MEM_OTFDE_XSPI_DATA_PATH_MASK
        From..to bits:  5..5
        Default Value:  0x1
        Access type:    read-write
        Description:    OTFDE XSPI DATA PATH MASK:
                        0- Masked
                        1- Enabled
                        Enable / Mask xSPI data path related errors signaled to OTFDE

        Field:          MEM_OTFDE_XSPI_CNFG_PATH_MASK
        From..to bits:  6..6
        Default Value:  0x1
        Access type:    read-write
        Description:    0- Masked
                        1- Enabled
                        Enable / Mask xSPI config path related errors signaled to OTFDE

        Field:          MEM_OTFDE_XSPI_SERVICE_INTERRUPT_MASK
        From..to bits:  7..7
        Default Value:  0x1
        Access type:    read-write
        Description:    OTFDE XSPI SERVICE INTERRUPT MASK:
                        0- Masked
                        1- Enabled
                        Enable / Mask xSPI service interrupt criteria event indication

        Field:          MEM_OTFDE_TRANS_DEVICE_DISABLED_MASK
        From..to bits:  8..8
        Default Value:  0x1
        Access type:    read-write
        Description:    OTFDE TRANS DEVICE DISABLED MASK:
                        0- Masked
                        1- Enabled
                        Enable / Mask transaction into a disabled device event indication

        Field:          MEM_OTFDE_TRANS_REGION_DISABLED_MASK
        From..to bits:  9..9
        Default Value:  0x1
        Access type:    read-write
        Description:    OTFDE TRANS REGION DISABLED MASK:
                        0- Masked
                        1- Enabled
                        Enable / Mask transaction into a disabled region event indication

        Field:          MEM_OTFDE_XSPI_POLLING_ITR_EXPIRED_MASK
        From..to bits:  10..10
        Default Value:  0x1
        Access type:    read-write
        Description:    OTFDE XSPI POLLING ITR EXPIRED MASK:
                        0- Masked
                        1- Enabled
                        Polling requests iterations expired

        Field:          MEM_OTFDE_TRANS_MULTIPLE_REGIONS_MAPPED_MASK
        From..to bits:  11..11
        Default Value:  0x1
        Access type:    read-write
        Description:    OTFDE TRANS MULTIPLE REGIONS MAPPED MASK:
                        0- Masked
                        1- Enabled
                        Enable / Mask transaction was mapped into more than one region indication

        Field:          MEM_OTFDE_TRANS_ADDRESS_NOT_32_BIT_MASK
        From..to bits:  12..12
        Default Value:  0x1
        Access type:    read-write
        Description:    OTFDE TRANS ADDRESS NOT 32 BIT MASK:
                        0- Masked
                        1- Enabled
                        Enable / Mask transaction address was not 32 bit aligned indication

        Field:          MEM_OTFDE_TRANS_SIZE_NOT_32_BIT_MASK
        From..to bits:  13..13
        Default Value:  0x1
        Access type:    read-write
        Description:    OTFDE TRANS SIZE NOT 32 BIT MASK:
                        0- Masked
                        1- Enabled
                        Enable / Mask transaction size was not 32 bit indication

        Field:          MEM_OTFDE_TRANS_BURST_NOT_32_BIT_MASK
        From..to bits:  14..14
        Default Value:  0x1
        Access type:    read-write
        Description:    OTFDE TRANS BURST NOT 32 BIT MASK:
                        0- Masked
                        1- Enabled
                        Enable / Mask transaction burst was not non-seq indication

        Field:          MEM_OTFDE_REGION_READ_WRITE_DEF_MASK
        From..to bits:  15..15
        Default Value:  0x1
        Access type:    read-write
        Description:    OTFDE REGION READ WRITE DEF MASK:
                        0- Masked
                        1- Enabled
                        Enable / Mask transaction type was not allowed according to region definitions

        Field:          MEM_OTFDE_SUSPEND_WHILE_DISABLED_MASK
        From..to bits:  16..16
        Default Value:  0x1
        Access type:    read-write
        Description:    OTFDE SUSPEND WHILE DISABLED MASK:
                        0- Masked
                        1- Enabled
                        Enable / Mask SW requested suspend while OTFDE is disabled indication

  ----------------------------------------------------------------------------- */
#define HOST_XIP__OTFDE_GENERAL_CONFIG_2__ADDR               (0x41917040)
#define HOST_XIP__OTFDE_GENERAL_CONFIG_2                     (0x40030c0041917040)

#define HOST_XIP__OTFDE_GENERAL_CONFIG_2__MEM_OTFDE_RESET_MASK (0x40030fe041917040)
#define HOST_XIP__OTFDE_GENERAL_CONFIG_2__MEM_OTFDE_SOFT_RESET_MASK (0x40030fc141917040)
#define HOST_XIP__OTFDE_GENERAL_CONFIG_2__MEM_OTFDE_BYPASS_MODE_CHANGE_MASK (0x40030fa241917040)
#define HOST_XIP__OTFDE_GENERAL_CONFIG_2__MEM_OTFDE_GENERAL_MASK (0x40030f6441917040)
#define HOST_XIP__OTFDE_GENERAL_CONFIG_2__MEM_OTFDE_XSPI_DATA_PATH_MASK (0x40030f4541917040)
#define HOST_XIP__OTFDE_GENERAL_CONFIG_2__MEM_OTFDE_XSPI_CNFG_PATH_MASK (0x40030f2641917040)
#define HOST_XIP__OTFDE_GENERAL_CONFIG_2__MEM_OTFDE_XSPI_SERVICE_INTERRUPT_MASK (0x40030f0741917040)
#define HOST_XIP__OTFDE_GENERAL_CONFIG_2__MEM_OTFDE_TRANS_DEVICE_DISABLED_MASK (0x40030ee841917040)
#define HOST_XIP__OTFDE_GENERAL_CONFIG_2__MEM_OTFDE_TRANS_REGION_DISABLED_MASK (0x40030ec941917040)
#define HOST_XIP__OTFDE_GENERAL_CONFIG_2__MEM_OTFDE_XSPI_POLLING_ITR_EXPIRED_MASK (0x40030eaa41917040)
#define HOST_XIP__OTFDE_GENERAL_CONFIG_2__MEM_OTFDE_TRANS_MULTIPLE_REGIONS_MAPPED_MASK (0x40030e8b41917040)
#define HOST_XIP__OTFDE_GENERAL_CONFIG_2__MEM_OTFDE_TRANS_ADDRESS_NOT_32_BIT_MASK (0x40030e6c41917040)
#define HOST_XIP__OTFDE_GENERAL_CONFIG_2__MEM_OTFDE_TRANS_SIZE_NOT_32_BIT_MASK (0x40030e4d41917040)
#define HOST_XIP__OTFDE_GENERAL_CONFIG_2__MEM_OTFDE_TRANS_BURST_NOT_32_BIT_MASK (0x40030e2e41917040)
#define HOST_XIP__OTFDE_GENERAL_CONFIG_2__MEM_OTFDE_REGION_READ_WRITE_DEF_MASK (0x40030e0f41917040)
#define HOST_XIP__OTFDE_GENERAL_CONFIG_2__MEM_OTFDE_SUSPEND_WHILE_DISABLED_MASK (0x40030df041917040)

/*-----------------------------------------------------------------------------
    Register name:       OTFDE_GENERAL_CONFIG_3
    Relative address:    0x5050
    Absolute address:    0x41917050
    Description:         Event IRQ next state
    Default Value:       0x0000f3fa

        Field:          MEM_OTFDE_RESET_NS
        From..to bits:  0..0
        Default Value:  0x0
        Access type:    read-write
        Description:    RESET NON SECURED

        Field:          MEM_OTFDE_SOFT_RESET_NS
        From..to bits:  1..1
        Default Value:  0x1
        Access type:    read-write
        Description:    OTFDE SOFT RESET NS:
                        0- Disable
                        1- Active Idle
                        Decision of next state for  soft reset completion event

        Field:          MEM_OTFDE_BYPASS_MODE_CHANGE_NS
        From..to bits:  2..2
        Default Value:  0x0
        Access type:    read-write
        Description:    BYPASS MODE CHANGE
                        
                        Used in ECO for PG1.
                        Problem Statement
                        In DDR 80MHz mode RD cmd, Seen in QPI (Octal not yet checked) the xSPI IP stop driving the data to soon violating Ext Mem hold requirement (~0.5ns v. up to ~2-3ns requirement for most vendors)
                        Suggested Fix
                        extend IO data drive by additional logic at IP for read commands in the DDR 80MHz mode

        Field:          MEM_OTFDE_GENERAL_ERROR_NS
        From..to bits:  4..4
        Default Value:  0x1
        Access type:    read-write
        Description:    OTFDE GENERAL ERROR NS:
                        0- Disable
                        1- Active Idle
                        Decision of next state for  general error event

        Field:          MEM_OTFDE_XSPI_DATA_PATH_ERROR_NS
        From..to bits:  5..5
        Default Value:  0x1
        Access type:    read-write
        Description:    OTFDE XSPI DATA PATH ERROR NS:
                        0- Disable
                        1- Active Idle
                        Decision of next state for xSPI data path related errors signaled to OTFDE

        Field:          MEM_OTFDE_XSPI_CNFG_PATH_ERROR_NS
        From..to bits:  6..6
        Default Value:  0x1
        Access type:    read-write
        Description:    OTFDE XSPI CNFG PATH ERROR NS:
                        0- Disable
                        1- Active Idle
                        Decision of next state for xSPI config path related errors signaled to OTFDE

        Field:          MEM_OTFDE_XSPI_SERVICE_INTERRUPT_NS
        From..to bits:  7..7
        Default Value:  0x1
        Access type:    read-write
        Description:    XSPI SERVICE INTERRUPT

        Field:          MEM_OTFDE_TRANS_DEVICE_DISABLED_NS
        From..to bits:  8..8
        Default Value:  0x1
        Access type:    read-write
        Description:    OTFDE TRANS DEVICE DISABLED NS:
                        0- Disable
                        1- Active Idle
                        Decision of next state for transaction into a disabled device event indication

        Field:          MEM_OTFDE_TRANS_REGION_DISABLED_NS
        From..to bits:  9..9
        Default Value:  0x1
        Access type:    read-write
        Description:    OTFDE TRANS REGION DISABLED NS:
                        0- Disable
                        1- Active Idle
                        Decision of next state for transaction into a disabled region event indication

        Field:          MEM_OTFDE_TRANS_MULTIPLE_REGIONS_MAPPED_NS
        From..to bits:  11..11
        Default Value:  0x0
        Access type:    read-write
        Description:    OTFDE TRANS MULTIPLE REGIONS MAPPED NS:
                        0- Disable
                        1- N/A
                        Decision of next state for transaction was mapped into more than one region

        Field:          MEM_OTFDE_TRANS_ADDRESS_NOT_32_BIT_NS
        From..to bits:  12..12
        Default Value:  0x1
        Access type:    read-write
        Description:    OTFDE TRANS ADDRESS NOT 32 BIT NS:
                        0- Disable
                        1- Active Idle
                        Decision of next state for transaction address was not 32 bit aligned indication

        Field:          MEM_OTFDE_TRANS_SIZE_NOT_32_BIT_NS
        From..to bits:  13..13
        Default Value:  0x1
        Access type:    read-write
        Description:    OTFDE TRANS SIZE NOT 32 BIT NS:
                        0- Disable
                        1- Active Idle
                        Decision of next state for transaction size was not 32 bit indication

        Field:          MEM_OTFDE_TRANS_BURST_NOT_32_BIT_NS
        From..to bits:  14..14
        Default Value:  0x1
        Access type:    read-write
        Description:    OTFDE TRANS BURST NOT 32 BIT NS:
                        0- Disable
                        1- Active Idle
                        Decision of next state for transaction burst was not non-seq indication

        Field:          MEM_OTFDE_REGION_READ_WRITE_VIOLATION_NS
        From..to bits:  15..15
        Default Value:  0x1
        Access type:    read-write
        Description:    OTFDE REGION READ WRITE VIOLATION NS:
                        0- Disable
                        1- Active Idle
                        Decision of next state for transaction type was not allowed according to region definitions

        Field:          MEM_OTFDE_SUSPEND_WHILE_DISABLED_NS
        From..to bits:  16..16
        Default Value:  0x0
        Access type:    read-write
        Description:    OTFDE SUSPEND WHILE DISABLED NS:
                        0- Disable
                        1- N/A
                        Decision of next state for SW requested suspend while OTFDE is disabled

  ----------------------------------------------------------------------------- */
#define HOST_XIP__OTFDE_GENERAL_CONFIG_3__ADDR               (0x41917050)
#define HOST_XIP__OTFDE_GENERAL_CONFIG_3                     (0x40030c0041917050)

#define HOST_XIP__OTFDE_GENERAL_CONFIG_3__MEM_OTFDE_RESET_NS (0x40030fe041917050)
#define HOST_XIP__OTFDE_GENERAL_CONFIG_3__MEM_OTFDE_SOFT_RESET_NS (0x40030fc141917050)
#define HOST_XIP__OTFDE_GENERAL_CONFIG_3__MEM_OTFDE_BYPASS_MODE_CHANGE_NS (0x40030fa241917050)
#define HOST_XIP__OTFDE_GENERAL_CONFIG_3__MEM_OTFDE_GENERAL_ERROR_NS (0x40030f6441917050)
#define HOST_XIP__OTFDE_GENERAL_CONFIG_3__MEM_OTFDE_XSPI_DATA_PATH_ERROR_NS (0x40030f4541917050)
#define HOST_XIP__OTFDE_GENERAL_CONFIG_3__MEM_OTFDE_XSPI_CNFG_PATH_ERROR_NS (0x40030f2641917050)
#define HOST_XIP__OTFDE_GENERAL_CONFIG_3__MEM_OTFDE_XSPI_SERVICE_INTERRUPT_NS (0x40030f0741917050)
#define HOST_XIP__OTFDE_GENERAL_CONFIG_3__MEM_OTFDE_TRANS_DEVICE_DISABLED_NS (0x40030ee841917050)
#define HOST_XIP__OTFDE_GENERAL_CONFIG_3__MEM_OTFDE_TRANS_REGION_DISABLED_NS (0x40030ec941917050)
#define HOST_XIP__OTFDE_GENERAL_CONFIG_3__MEM_OTFDE_TRANS_MULTIPLE_REGIONS_MAPPED_NS (0x40030e8b41917050)
#define HOST_XIP__OTFDE_GENERAL_CONFIG_3__MEM_OTFDE_TRANS_ADDRESS_NOT_32_BIT_NS (0x40030e6c41917050)
#define HOST_XIP__OTFDE_GENERAL_CONFIG_3__MEM_OTFDE_TRANS_SIZE_NOT_32_BIT_NS (0x40030e4d41917050)
#define HOST_XIP__OTFDE_GENERAL_CONFIG_3__MEM_OTFDE_TRANS_BURST_NOT_32_BIT_NS (0x40030e2e41917050)
#define HOST_XIP__OTFDE_GENERAL_CONFIG_3__MEM_OTFDE_REGION_READ_WRITE_VIOLATION_NS (0x40030e0f41917050)
#define HOST_XIP__OTFDE_GENERAL_CONFIG_3__MEM_OTFDE_SUSPEND_WHILE_DISABLED_NS (0x40030df041917050)

/*-----------------------------------------------------------------------------
    Register name:       OTFDE_JOB_DONE_GRANT_SEL
    Relative address:    0x5060
    Absolute address:    0x41917060
    Description:         set of controller non STIG configurations
    Default Value:       0x00000000

        Field:          MEM_OTFDE_DEV0_JOB0_GRANT_SEL
        From..to bits:  0..0
        Default Value:  0x0
        Access type:    read-write
        Description:    Used when the access address does not match any region
                        0- Reject not mapped address access 
                        1- Bypass not mapped address access (address is forwarded as is to xspi)

        Field:          MEM_OTFDE_DEV0_JOB4_GRANT_SEL
        From..to bits:  4..4
        Default Value:  0x0
        Access type:    read-write
        Description:    Used when the access address does not match any region
                        0- Reject not mapped address access 
                        1- Bypass not mapped address access (address is forwarded as is to xspi)

        Field:          MEM_OTFDE_DEV0_JOB5_GRANT_SEL
        From..to bits:  5..5
        Default Value:  0x0
        Access type:    read-write
        Description:    Used when the access address does not match any region
                        0- Reject not mapped address access 
                        1- Bypass not mapped address access (address is forwarded as is to xspi)

        Field:          MEM_OTFDE_DEV0_JOB6_GRANT_SEL
        From..to bits:  6..6
        Default Value:  0x0
        Access type:    read-write
        Description:    Used when the access address does not match any region
                        0- Reject not mapped address access 
                        1- Bypass not mapped address access (address is forwarded as is to xspi)

        Field:          MEM_OTFDE_DEV0_JOB7_GRANT_SEL
        From..to bits:  7..7
        Default Value:  0x0
        Access type:    read-write
        Description:    Used when the access address does not match any region
                        0- Reject not mapped address access 
                        1- Bypass not mapped address access (address is forwarded as is to xspi)

        Field:          MEM_OTFDE_DEV1_JOB0_GRANT_SEL
        From..to bits:  8..8
        Default Value:  0x0
        Access type:    read-write
        Description:    Used when the access address does not match any region
                        0- Reject not mapped address access 
                        1- Bypass not mapped address access (address is forwarded as is to xspi)

        Field:          MEM_OTFDE_DEV1_JOB4_GRANT_SEL
        From..to bits:  12..12
        Default Value:  0x0
        Access type:    read-write
        Description:    Used when the access address does not match any region
                        0- Reject not mapped address access 
                        1- Bypass not mapped address access (address is forwarded as is to xspi)

        Field:          MEM_OTFDE_DEV1_JOB5_GRANT_SEL
        From..to bits:  13..13
        Default Value:  0x0
        Access type:    read-write
        Description:    Used when the access address does not match any region
                        0- Reject not mapped address access 
                        1- Bypass not mapped address access (address is forwarded as is to xspi)

        Field:          MEM_OTFDE_DEV1_JOB6_GRANT_SEL
        From..to bits:  14..14
        Default Value:  0x0
        Access type:    read-write
        Description:    Used when the access address does not match any region
                        0- Reject not mapped address access 
                        1- Bypass not mapped address access (address is forwarded as is to xspi)

        Field:          MEM_OTFDE_DEV1_JOB7_GRANT_SEL
        From..to bits:  15..15
        Default Value:  0x0
        Access type:    read-write
        Description:    Used when the access address does not match any region
                        0- Reject not mapped address access 
                        1- Bypass not mapped address access (address is forwarded as is to xspi)

  ----------------------------------------------------------------------------- */
#define HOST_XIP__OTFDE_JOB_DONE_GRANT_SEL__ADDR             (0x41917060)
#define HOST_XIP__OTFDE_JOB_DONE_GRANT_SEL                   (0x40030c0041917060)

#define HOST_XIP__OTFDE_JOB_DONE_GRANT_SEL__MEM_OTFDE_DEV0_JOB0_GRANT_SEL (0x40030fe041917060)
#define HOST_XIP__OTFDE_JOB_DONE_GRANT_SEL__MEM_OTFDE_DEV0_JOB4_GRANT_SEL (0x40030f6441917060)
#define HOST_XIP__OTFDE_JOB_DONE_GRANT_SEL__MEM_OTFDE_DEV0_JOB5_GRANT_SEL (0x40030f4541917060)
#define HOST_XIP__OTFDE_JOB_DONE_GRANT_SEL__MEM_OTFDE_DEV0_JOB6_GRANT_SEL (0x40030f2641917060)
#define HOST_XIP__OTFDE_JOB_DONE_GRANT_SEL__MEM_OTFDE_DEV0_JOB7_GRANT_SEL (0x40030f0741917060)
#define HOST_XIP__OTFDE_JOB_DONE_GRANT_SEL__MEM_OTFDE_DEV1_JOB0_GRANT_SEL (0x40030ee841917060)
#define HOST_XIP__OTFDE_JOB_DONE_GRANT_SEL__MEM_OTFDE_DEV1_JOB4_GRANT_SEL (0x40030e6c41917060)
#define HOST_XIP__OTFDE_JOB_DONE_GRANT_SEL__MEM_OTFDE_DEV1_JOB5_GRANT_SEL (0x40030e4d41917060)
#define HOST_XIP__OTFDE_JOB_DONE_GRANT_SEL__MEM_OTFDE_DEV1_JOB6_GRANT_SEL (0x40030e2e41917060)
#define HOST_XIP__OTFDE_JOB_DONE_GRANT_SEL__MEM_OTFDE_DEV1_JOB7_GRANT_SEL (0x40030e0f41917060)

/*-----------------------------------------------------------------------------
    Register name:       OTFDE_DEVICE_0_CONFIG
    Relative address:    0x5070
    Absolute address:    0x41917070
    Description:         Device 0 parameters
    Default Value:       0x00500001

        Field:          MEM_OTFDE_DEVICE_0_ENABLED
        From..to bits:  0..0
        Default Value:  0x1
        Access type:    read-write
        Description:    OTFDE DEVICE 0 ENABLED:
                        Device enabled (and all the device parameters were checked in SW)
                        0- Device Disabled
                        1- Device Enabled

        Field:          MEM_OTFDE_DEVICE_0_WRITE_PROTECTION_TIMER_EN
        From..to bits:  1..1
        Default Value:  0x0
        Access type:    read-write
        Description:    OTFDE DEVICE 0 WRITE PROTECTION TIMER EN:
                        Set the write protection timer after a write task
                        0- Write protection timer is disabled
                        1- Write protection timer is enabled

        Field:          MEM_OTFDE_DEVICE_0_ISSUE_PRE_WRITE_CMD
        From..to bits:  2..2
        Default Value:  0x0
        Access type:    read-write
        Description:    OTFDE DEVICE 0 ISSUE PRE WRITE CMD:
                        Issue a Pre Write command before the next write task
                        0- Do not issue PRE WR CMD
                        1- Issue PRE WR CMD before every write task

        Field:          MEM_OTFDE_DEVICE_0_ISSUE_POST_WRITE_CMD
        From..to bits:  3..3
        Default Value:  0x0
        Access type:    read-write
        Description:    OTFDE DEVICE 0 ISSUE POST WRITE CMD:
                        Issue a Post Write command after the write task ended
                        0- Do not issue POST WR CMD
                        1- Issue POST WR CMD after every write task

        Field:          MEM_OTFDE_DEVICE_0_WRITE_BUFFER_TIMER_MODE
        From..to bits:  4..5
        Default Value:  0x0
        Access type:    read-write
        Description:    OTFDE DEVICE 0 WRITE BUFFER TIMER MODE:
                        00- mode0 is   16usec resolution
                        01- mode1 is   32usec resolution 
                        10- mode2 is   64usec resolution
                        11- mode3 is 256usec resolution

        Field:          MEM_OTFDE_DEVICE_0_WRITE_BUFFER_TIMER_RANGE
        From..to bits:  8..13
        Default Value:  0x0
        Access type:    read-write
        Description:    OTFDE DEVICE 0 WRITE BUFFER TIMER RANGE:
                        range is 0 - 63 multiplied by Mode resolution 
                        mode0: timer res is   16usec, timer range is   16-1024usec
                        mode1: timer res is   32usec, timer range is   32-2048usec
                        mode2: timer res is   64usec, timer range is   64-4192usec
                        mode3: timer res is 256usec, timer range is 256-16384usec

        Field:          MEM_OTFDE_DEVICE_0_RWW_EN
        From..to bits:  16..16
        Default Value:  0x0
        Access type:    read-write
        Description:    OTFDE DEVICE 0 RWW EN:
                        0- Read while Write is disabled 
                        1- Read while Write is Enabled

        Field:          MEM_OTFDE_DEVICE_0_SIZE
        From..to bits:  20..22
        Default Value:  0x5
        Access type:    read-write
        Description:    OTFDE DEVICE 0 SIZE:
                        000 -   2 MByte
                        001 -   4 MByte
                        010 -   8 MByte
                        011 - 16 MByte
                        100 - 32 MByte
                        101 - 64 MByte

        Field:          MEM_OTFDE_DEVICE_0_NUMBER_OF_BANKS
        From..to bits:  24..26
        Default Value:  0x0
        Access type:    read-write
        Description:    OTFDE DEVICE 0 NUMBER OF BANKS:
                        000 -   1 Bank
                        001 -   2 Banks
                        010 -   4 Banks
                        011 -   8 Banks
                        100 - 16 Banks

        Field:          MEM_OTFDE_DEVICE_0_SERVICE_INTERRUPT_CRITERIA
        From..to bits:  28..31
        Default Value:  0x0
        Access type:    read-write
        Description:    OTFDE DEVICE 0 SERVICE INTERRUPT CRITERIA:
                        0- No service interruption criteria. 
                        any other value is in 160MHz cycles between two transactions towards xSPI

  ----------------------------------------------------------------------------- */
#define HOST_XIP__OTFDE_DEVICE_0_CONFIG__ADDR                (0x41917070)
#define HOST_XIP__OTFDE_DEVICE_0_CONFIG                      (0x40030c0041917070)

#define HOST_XIP__OTFDE_DEVICE_0_CONFIG__MEM_OTFDE_DEVICE_0_ENABLED (0x40030fe041917070)
#define HOST_XIP__OTFDE_DEVICE_0_CONFIG__MEM_OTFDE_DEVICE_0_WRITE_PROTECTION_TIMER_EN (0x40030fc141917070)
#define HOST_XIP__OTFDE_DEVICE_0_CONFIG__MEM_OTFDE_DEVICE_0_ISSUE_PRE_WRITE_CMD (0x40030fa241917070)
#define HOST_XIP__OTFDE_DEVICE_0_CONFIG__MEM_OTFDE_DEVICE_0_ISSUE_POST_WRITE_CMD (0x40030f8341917070)
#define HOST_XIP__OTFDE_DEVICE_0_CONFIG__MEM_OTFDE_DEVICE_0_WRITE_BUFFER_TIMER_MODE (0x40030f4441917070)
#define HOST_XIP__OTFDE_DEVICE_0_CONFIG__MEM_OTFDE_DEVICE_0_WRITE_BUFFER_TIMER_RANGE (0x40030e4841917070)
#define HOST_XIP__OTFDE_DEVICE_0_CONFIG__MEM_OTFDE_DEVICE_0_RWW_EN (0x40030df041917070)
#define HOST_XIP__OTFDE_DEVICE_0_CONFIG__MEM_OTFDE_DEVICE_0_SIZE (0x40030d3441917070)
#define HOST_XIP__OTFDE_DEVICE_0_CONFIG__MEM_OTFDE_DEVICE_0_NUMBER_OF_BANKS (0x40030cb841917070)
#define HOST_XIP__OTFDE_DEVICE_0_CONFIG__MEM_OTFDE_DEVICE_0_SERVICE_INTERRUPT_CRITERIA (0x40030c1c41917070)

/*-----------------------------------------------------------------------------
    Register name:       OTFDE_DEVICE_0_POLLING_TIMER
    Relative address:    0x5074
    Absolute address:    0x41917074
    Description:         Device 0 polling timer parameters
    Default Value:       0x000103ff

        Field:          MEM_OTFDE_DEVICE_0_POLLING_RESP_COUNT
        From..to bits:  0..9
        Default Value:  0x3ff
        Access type:    read-write
        Description:    This value holds the amount of time in us between each polling iteration sent to xspi control
                        range : 1us-1023us
                        value zero is NA

        Field:          MEM_OTFDE_DEVICE_0_POLLING_ITERATIONS
        From..to bits:  16..20
        Default Value:  0x1
        Access type:    read-write
        Description:    This value holds the number of additional iterations before polling process is considered complete
                        range : 0-31 iterations
                        Translating into total polling request iterations: min 1 and max 32

  ----------------------------------------------------------------------------- */
#define HOST_XIP__OTFDE_DEVICE_0_POLLING_TIMER__ADDR         (0x41917074)
#define HOST_XIP__OTFDE_DEVICE_0_POLLING_TIMER               (0x4003040041917074)

#define HOST_XIP__OTFDE_DEVICE_0_POLLING_TIMER__MEM_OTFDE_DEVICE_0_POLLING_RESP_COUNT (0x400306c041917074)
#define HOST_XIP__OTFDE_DEVICE_0_POLLING_TIMER__MEM_OTFDE_DEVICE_0_POLLING_ITERATIONS (0x4003057041917074)

/*-----------------------------------------------------------------------------
    Register name:       OTFDE_DEVICE_0_WRAP
    Relative address:    0x5078
    Absolute address:    0x41917078
    Description:         Device 0 wrap configuration
    Default Value:       0x000103ff

        Field:          MEM_OTFDE_DEVICE_0_WRAP_ENABLE
        From..to bits:  0..0
        Default Value:  0x0
        Access type:    read-write
        Description:    Enable wrap feature for device 0

        Field:          MEM_OTFDE_DEVICE_0_WRAP_SIZE
        From..to bits:  1..4
        Default Value:  0x0
        Access type:    read-write
        Description:    Define the wrap size, this field is active only if [EN] is set.
                        0x0. 8 Bytes
                        0x1. 16 Bytes
                        0x2. 32 Bytes
                        0x3. 64 Bytes
                        0x4. 128 Bytes
                        0x5. 256 Bytes
                        0x6. 512 Bytes
                        0x7. 1024 Bytes
                        0x8. 2048 Bytes
                        0x9. 4096 Bytes
                        

  ----------------------------------------------------------------------------- */
#define HOST_XIP__OTFDE_DEVICE_0_WRAP__ADDR                  (0x41917078)
#define HOST_XIP__OTFDE_DEVICE_0_WRAP                        (0x4003040041917078)

#define HOST_XIP__OTFDE_DEVICE_0_WRAP__MEM_OTFDE_DEVICE_0_WRAP_ENABLE (0x400307e041917078)
#define HOST_XIP__OTFDE_DEVICE_0_WRAP__MEM_OTFDE_DEVICE_0_WRAP_SIZE (0x4003076141917078)

/*-----------------------------------------------------------------------------
    Register name:       OTFDE_DEVICE_1_CONFIG
    Relative address:    0x5080
    Absolute address:    0x41917080
    Description:         Device 1 parameters
    Default Value:       0x00000000

        Field:          MEM_OTFDE_DEVICE_1_ENABLED
        From..to bits:  0..0
        Default Value:  0x0
        Access type:    read-write
        Description:    OTFDE DEVICE 1 ENABLED:
                        Device enabled (and all the device parameters were checked in SW)
                        0 - Device Disabled
                        1- Device Enabled

        Field:          MEM_OTFDE_DEVICE_1_WRITE_PROTECTION_TIMER_EN
        From..to bits:  1..1
        Default Value:  0x0
        Access type:    read-write
        Description:    OTFDE DEVICE 1 WRITE PROTECTION TIMER EN:
                        Set the write protection timer after a write task
                        0- Write protection timer is disabled
                        1- Write protection timer is enabled

        Field:          MEM_OTFDE_DEVICE_1_ISSUE_PRE_WRITE_CMD
        From..to bits:  2..2
        Default Value:  0x0
        Access type:    read-write
        Description:    OTFDE DEVICE 1 ISSUE PRE WRITE CMD:
                        Issue a Pre Write command before the next write task
                        0- Do not issue PRE WR CMD
                        1- Issue PRE WR CMD before every write task

        Field:          MEM_OTFDE_DEVICE_1_ISSUE_POST_WRITE_CMD
        From..to bits:  3..3
        Default Value:  0x0
        Access type:    read-write
        Description:    OTFDE DEVICE 1 ISSUE POST WRITE CMD:
                        Issue a Post Write command after the write task ended
                        0- Do not issue POST WR CMD
                        1- Issue POST WR CMD after every write task

        Field:          MEM_OTFDE_DEVICE_1_WRITE_BUFFER_TIMER_MODE
        From..to bits:  4..5
        Default Value:  0x0
        Access type:    read-write
        Description:    OTFDE DEVICE 1 WRITE BUFFER TIMER MODE:
                        00- mode0 is   16usec resolution
                        01- mode1 is   32usec resolution 
                        10- mode2 is   64usec resolution
                        11- mode3 is 256usec resolution

        Field:          MEM_OTFDE_DEVICE_1_WRITE_BUFFER_TIMER_RANGE
        From..to bits:  8..13
        Default Value:  0x0
        Access type:    read-write
        Description:    OTFDE DEVICE 1 WRITE BUFFER TIMER RANGE:
                        range is 0 - 63 multiplied by Mode resolution 
                        mode0: timer res is   16usec, timer range is   16-1024usec
                        mode1: timer res is   32usec, timer range is   32-2048usec
                        mode2: timer res is   64usec, timer range is   64-4192usec
                        mode3: timer res is 256usec, timer range is 256-16384usec

        Field:          MEM_OTFDE_DEVICE_1_SERVICE_INTERRUPT_CRITERIA
        From..to bits:  16..19
        Default Value:  0x0
        Access type:    read-write
        Description:    OTFDE DEVICE 1 SERVICE INTERRUPT CRITERIA:
                        0- No service interruption criteria. 
                        any other value is in 160MHz cycles between two transactions towards xSPI

  ----------------------------------------------------------------------------- */
#define HOST_XIP__OTFDE_DEVICE_1_CONFIG__ADDR                (0x41917080)
#define HOST_XIP__OTFDE_DEVICE_1_CONFIG                      (0x40030c0041917080)

#define HOST_XIP__OTFDE_DEVICE_1_CONFIG__MEM_OTFDE_DEVICE_1_ENABLED (0x40030fe041917080)
#define HOST_XIP__OTFDE_DEVICE_1_CONFIG__MEM_OTFDE_DEVICE_1_WRITE_PROTECTION_TIMER_EN (0x40030fc141917080)
#define HOST_XIP__OTFDE_DEVICE_1_CONFIG__MEM_OTFDE_DEVICE_1_ISSUE_PRE_WRITE_CMD (0x40030fa241917080)
#define HOST_XIP__OTFDE_DEVICE_1_CONFIG__MEM_OTFDE_DEVICE_1_ISSUE_POST_WRITE_CMD (0x40030f8341917080)
#define HOST_XIP__OTFDE_DEVICE_1_CONFIG__MEM_OTFDE_DEVICE_1_WRITE_BUFFER_TIMER_MODE (0x40030f4441917080)
#define HOST_XIP__OTFDE_DEVICE_1_CONFIG__MEM_OTFDE_DEVICE_1_WRITE_BUFFER_TIMER_RANGE (0x40030e4841917080)
#define HOST_XIP__OTFDE_DEVICE_1_CONFIG__MEM_OTFDE_DEVICE_1_SERVICE_INTERRUPT_CRITERIA (0x40030d9041917080)

/*-----------------------------------------------------------------------------
    Register name:       OTFDE_DEVICE_1_WRAP
    Relative address:    0x5084
    Absolute address:    0x41917084
    Description:         Device 1 wrap configuration
    Default Value:       0x000103ff

        Field:          MEM_OTFDE_DEVICE_1_WRAP_ENABLE
        From..to bits:  0..0
        Default Value:  0x0
        Access type:    read-write
        Description:    Enable wrap feature for device 1

        Field:          MEM_OTFDE_DEVICE_1_WRAP_SIZE
        From..to bits:  1..4
        Default Value:  0x0
        Access type:    read-write
        Description:    Define the wrap size, this field is active only if [EN] is set.
                        0x0. 8 Bytes
                        0x1. 16 Bytes
                        0x2. 32 Bytes
                        0x3. 64 Bytes
                        0x4. 128 Bytes
                        0x5. 256 Bytes
                        0x6. 512 Bytes
                        0x7. 1024 Bytes
                        0x8. 2048 Bytes
                        0x9. 4096 Bytes
                        

  ----------------------------------------------------------------------------- */
#define HOST_XIP__OTFDE_DEVICE_1_WRAP__ADDR                  (0x41917084)
#define HOST_XIP__OTFDE_DEVICE_1_WRAP                        (0x4003040041917084)

#define HOST_XIP__OTFDE_DEVICE_1_WRAP__MEM_OTFDE_DEVICE_1_WRAP_ENABLE (0x400307e041917084)
#define HOST_XIP__OTFDE_DEVICE_1_WRAP__MEM_OTFDE_DEVICE_1_WRAP_SIZE (0x4003076141917084)

/*-----------------------------------------------------------------------------
    Register name:       OTFDE_GLOBAL_WATCHDOG
    Relative address:    0x5090
    Absolute address:    0x41917090
    Description:         Global watchdog timer
                         counting before raising IRQ
    Default Value:       0x00000005

        Field:          MEM_OTFDE_GENERAL_WATCHDOG_TIMER
        From..to bits:  0..2
        Default Value:  0x5
        Access type:    read-write
        Description:    Watchdog timer in ms 
                        Timer pops watchdog IRQ in case a process within OTFDE crosses the required time
                        range 0-7
                        translated to up to 7ms
                        value 0 is NA

  ----------------------------------------------------------------------------- */
#define HOST_XIP__OTFDE_GLOBAL_WATCHDOG__ADDR                (0x41917090)
#define HOST_XIP__OTFDE_GLOBAL_WATCHDOG                      (0x4003000041917090)

#define HOST_XIP__OTFDE_GLOBAL_WATCHDOG__MEM_OTFDE_GENERAL_WATCHDOG_TIMER (0x400303a041917090)

/*-----------------------------------------------------------------------------
    Register name:       SECGB_REGION_0_PARAMS_0
    Relative address:    0x6000
    Absolute address:    0x41918000
    Description:         region 0 parameters config 0
    Default Value:       0x0000000d

        Field:          MEM_REGION_0_ENABLED
        From..to bits:  0..0
        Default Value:  0x1
        Access type:    read-write
        Description:    REGION 0 ENABLED:
                        0- Disabled  
                        1- Enabled
                        Region enabled for incoming transactions

        Field:          MEM_REGION_0_DEVICE_ID
        From..to bits:  1..1
        Default Value:  0x0
        Access type:    read-write
        Description:    REGION 0 DEVICE ID:
                        0- Device_0
                        1- Device_1

        Field:          MEM_REGION_0_SPI_WRITE_ENABLE
        From..to bits:  2..2
        Default Value:  0x1
        Access type:    read-write
        Description:    REGION 0 SPI WRITE ENABLE:
                        0- Cannot issue a SPI Write to this  region
                        1- Can issue a SPI Write to this  region

        Field:          MEM_REGION_0_SPI_READ_ENABLE
        From..to bits:  3..3
        Default Value:  0x1
        Access type:    read-write
        Description:    REGION 0 SPI READ ENABLE:
                        0- Cannot issue a SPI Read from this region
                        1- Can issue a SPI Read from this region

        Field:          MEM_REGION_0_PHYSICAL_OFFSET
        From..to bits:  4..17
        Default Value:  0x000
        Access type:    read-write
        Description:    Device related address offset

        Field:          MEM_REGION_0_SECURITY_ID_MSB
        From..to bits:  20..25
        Default Value:  0x0
        Access type:    read-write
        Description:    6 MSB bits of ID+COUNTER field (out of 38bits)

  ----------------------------------------------------------------------------- */
#define HOST_XIP__SECGB_REGION_0_PARAMS_0__ADDR              (0x41918000)
#define HOST_XIP__SECGB_REGION_0_PARAMS_0                    (0x40030c0041918000)

#define HOST_XIP__SECGB_REGION_0_PARAMS_0__MEM_REGION_0_ENABLED (0x40030fe041918000)
#define HOST_XIP__SECGB_REGION_0_PARAMS_0__MEM_REGION_0_DEVICE_ID (0x40030fc141918000)
#define HOST_XIP__SECGB_REGION_0_PARAMS_0__MEM_REGION_0_SPI_WRITE_ENABLE (0x40030fa241918000)
#define HOST_XIP__SECGB_REGION_0_PARAMS_0__MEM_REGION_0_SPI_READ_ENABLE (0x40030f8341918000)
#define HOST_XIP__SECGB_REGION_0_PARAMS_0__MEM_REGION_0_PHYSICAL_OFFSET (0x40030dc441918000)
#define HOST_XIP__SECGB_REGION_0_PARAMS_0__MEM_REGION_0_SECURITY_ID_MSB (0x40030cd441918000)

/*-----------------------------------------------------------------------------
    Register name:       SECGB_REGION_0_PARAMS_1
    Relative address:    0x6004
    Absolute address:    0x41918004
    Description:         region 0 parameters config 1
    Default Value:       0x00010000

        Field:          MEM_REGION_0_START_ADDRESS
        From..to bits:  0..19
        Default Value:  0x10000
        Access type:    read-write
        Description:    System start address

  ----------------------------------------------------------------------------- */
#define HOST_XIP__SECGB_REGION_0_PARAMS_1__ADDR              (0x41918004)
#define HOST_XIP__SECGB_REGION_0_PARAMS_1                    (0x4003000041918004)

#define HOST_XIP__SECGB_REGION_0_PARAMS_1__MEM_REGION_0_START_ADDRESS (0x4003018041918004)

/*-----------------------------------------------------------------------------
    Register name:       SECGB_REGION_0_PARAMS_2
    Relative address:    0x6008
    Absolute address:    0x41918008
    Description:         region 0 parameters config 2
    Default Value:       0x00017fff

        Field:          MEM_REGION_0_END_ADDRESS
        From..to bits:  0..19
        Default Value:  0x17fff
        Access type:    read-write
        Description:    System end address

  ----------------------------------------------------------------------------- */
#define HOST_XIP__SECGB_REGION_0_PARAMS_2__ADDR              (0x41918008)
#define HOST_XIP__SECGB_REGION_0_PARAMS_2                    (0x4003000041918008)

#define HOST_XIP__SECGB_REGION_0_PARAMS_2__MEM_REGION_0_END_ADDRESS (0x4003018041918008)

/*-----------------------------------------------------------------------------
    Register name:       SECGB_REGION_0_PARAMS_3
    Relative address:    0x600c
    Absolute address:    0x4191800c
    Description:         region 0 parameters config 3
    Default Value:       0x00000000

        Field:          MEM_REGION_0_SECURITY_ID_LSB
        From..to bits:  0..31
        Default Value:  0x00000000
        Access type:    read-write
        Description:    32 LSB bits of ID+COUNTER field (out of 38bits)

  ----------------------------------------------------------------------------- */
#define HOST_XIP__SECGB_REGION_0_PARAMS_3__ADDR              (0x4191800c)
#define HOST_XIP__SECGB_REGION_0_PARAMS_3                    (0x400300004191800c)

#define HOST_XIP__SECGB_REGION_0_PARAMS_3__MEM_REGION_0_SECURITY_ID_LSB (0x400300004191800c)

/*-----------------------------------------------------------------------------
    Register name:       SECGC_REGION_1_PARAMS_0
    Relative address:    0x7000
    Absolute address:    0x41919000
    Description:         region 1 parameters config 0
    Default Value:       0x00000000

        Field:          MEM_REGION_1_ENABLED
        From..to bits:  0..0
        Default Value:  0x0
        Access type:    read-write
        Description:    REGION 1 ENABLED:
                        0- Disabled
                        1- Enabled
                        Region enabled for incoming transactions

        Field:          MEM_REGION_1_DEVICE_ID
        From..to bits:  1..1
        Default Value:  0x0
        Access type:    read-write
        Description:    REGION 1 DEVICE ID:
                        0- Device_0 
                        1- Device_1

        Field:          MEM_REGION_1_SPI_WRITE_ENABLE
        From..to bits:  2..2
        Default Value:  0x0
        Access type:    read-write
        Description:    REGION 1 SPI WRITE ENABLE:
                        0- Cannot issue a SPI Write to this  region
                        1- Can issue a SPI Write to this  region

        Field:          MEM_REGION_1_SPI_READ_ENABLE
        From..to bits:  3..3
        Default Value:  0x0
        Access type:    read-write
        Description:    REGION 1 SPI READ ENABLE:
                        0- Cannot issue a SPI Read from this region
                        1- Can issue a SPI Read from this region

        Field:          MEM_REGION_1_PHYSICAL_OFFSET
        From..to bits:  4..17
        Default Value:  0x000
        Access type:    read-write
        Description:    Device related address offset

        Field:          MEM_REGION_1_SECURITY_ID_MSB
        From..to bits:  20..25
        Default Value:  0x0
        Access type:    read-write
        Description:    6 MSB bits of ID+COUNTER field (out of 38bits)

  ----------------------------------------------------------------------------- */
#define HOST_XIP__SECGC_REGION_1_PARAMS_0__ADDR              (0x41919000)
#define HOST_XIP__SECGC_REGION_1_PARAMS_0                    (0x40030c0041919000)

#define HOST_XIP__SECGC_REGION_1_PARAMS_0__MEM_REGION_1_ENABLED (0x40030fe041919000)
#define HOST_XIP__SECGC_REGION_1_PARAMS_0__MEM_REGION_1_DEVICE_ID (0x40030fc141919000)
#define HOST_XIP__SECGC_REGION_1_PARAMS_0__MEM_REGION_1_SPI_WRITE_ENABLE (0x40030fa241919000)
#define HOST_XIP__SECGC_REGION_1_PARAMS_0__MEM_REGION_1_SPI_READ_ENABLE (0x40030f8341919000)
#define HOST_XIP__SECGC_REGION_1_PARAMS_0__MEM_REGION_1_PHYSICAL_OFFSET (0x40030dc441919000)
#define HOST_XIP__SECGC_REGION_1_PARAMS_0__MEM_REGION_1_SECURITY_ID_MSB (0x40030cd441919000)

/*-----------------------------------------------------------------------------
    Register name:       SECGC_REGION_1_PARAMS_1
    Relative address:    0x7004
    Absolute address:    0x41919004
    Description:         region 1 parameters config 1
    Default Value:       0x00000001

        Field:          MEM_REGION_1_START_ADDRESS
        From..to bits:  0..19
        Default Value:  0x00001
        Access type:    read-write
        Description:    System start address

  ----------------------------------------------------------------------------- */
#define HOST_XIP__SECGC_REGION_1_PARAMS_1__ADDR              (0x41919004)
#define HOST_XIP__SECGC_REGION_1_PARAMS_1                    (0x4003000041919004)

#define HOST_XIP__SECGC_REGION_1_PARAMS_1__MEM_REGION_1_START_ADDRESS (0x4003018041919004)

/*-----------------------------------------------------------------------------
    Register name:       SECGC_REGION_1_PARAMS_2
    Relative address:    0x7008
    Absolute address:    0x41919008
    Description:         region 1 parameters config 2
    Default Value:       0x00000000

        Field:          MEM_REGION_1_END_ADDRESS
        From..to bits:  0..19
        Default Value:  0x00000
        Access type:    read-write
        Description:    System end address

  ----------------------------------------------------------------------------- */
#define HOST_XIP__SECGC_REGION_1_PARAMS_2__ADDR              (0x41919008)
#define HOST_XIP__SECGC_REGION_1_PARAMS_2                    (0x4003000041919008)

#define HOST_XIP__SECGC_REGION_1_PARAMS_2__MEM_REGION_1_END_ADDRESS (0x4003018041919008)

/*-----------------------------------------------------------------------------
    Register name:       SECGC_REGION_1_PARAMS_3
    Relative address:    0x700c
    Absolute address:    0x4191900c
    Description:         region 1 parameters config 3
    Default Value:       0x00000000

        Field:          MEM_REGION_1_SECURITY_ID_LSB
        From..to bits:  0..31
        Default Value:  0x00000000
        Access type:    read-write
        Description:    32 LSB bits of ID+COUNTER field (out of 38bits)

  ----------------------------------------------------------------------------- */
#define HOST_XIP__SECGC_REGION_1_PARAMS_3__ADDR              (0x4191900c)
#define HOST_XIP__SECGC_REGION_1_PARAMS_3                    (0x400300004191900c)

#define HOST_XIP__SECGC_REGION_1_PARAMS_3__MEM_REGION_1_SECURITY_ID_LSB (0x400300004191900c)

/*-----------------------------------------------------------------------------
    Register name:       SECGD_REGION_2_PARAMS_0
    Relative address:    0x8000
    Absolute address:    0x4191a000
    Description:         region 2 parameters config 0
    Default Value:       0x00000000

        Field:          MEM_REGION_2_ENABLED
        From..to bits:  0..0
        Default Value:  0x0
        Access type:    read-write
        Description:    REGION 2 ENABLED:
                        0- Disabled 
                        1- Enabled
                        Region enabled for incoming transactions

        Field:          MEM_REGION_2_DEVICE_ID
        From..to bits:  1..1
        Default Value:  0x0
        Access type:    read-write
        Description:    REGION 2 DEVICE ID:
                        0- Device_0
                        1- Device_1

        Field:          MEM_REGION_2_SPI_WRITE_ENABLE
        From..to bits:  2..2
        Default Value:  0x0
        Access type:    read-write
        Description:    REGION 2 SPI WRITE ENABLE:
                        0- Cannot issue a SPI Write to this  region
                        1- Can issue a SPI Write to this  region

        Field:          MEM_REGION_2_SPI_READ_ENABLE
        From..to bits:  3..3
        Default Value:  0x0
        Access type:    read-write
        Description:    REGION 2 SPI READ ENABLE:
                        0- Cannot issue a SPI Read from this region
                        1- Can issue a SPI Read from this region

        Field:          MEM_REGION_2_PHYSICAL_OFFSET
        From..to bits:  4..17
        Default Value:  0x000
        Access type:    read-write
        Description:    Device related address offset

        Field:          MEM_REGION_2_SECURITY_ID_MSB
        From..to bits:  20..25
        Default Value:  0x0
        Access type:    read-write
        Description:    6 MSB bits of ID+COUNTER field (out of 38bits)

  ----------------------------------------------------------------------------- */
#define HOST_XIP__SECGD_REGION_2_PARAMS_0__ADDR              (0x4191a000)
#define HOST_XIP__SECGD_REGION_2_PARAMS_0                    (0x40030c004191a000)

#define HOST_XIP__SECGD_REGION_2_PARAMS_0__MEM_REGION_2_ENABLED (0x40030fe04191a000)
#define HOST_XIP__SECGD_REGION_2_PARAMS_0__MEM_REGION_2_DEVICE_ID (0x40030fc14191a000)
#define HOST_XIP__SECGD_REGION_2_PARAMS_0__MEM_REGION_2_SPI_WRITE_ENABLE (0x40030fa24191a000)
#define HOST_XIP__SECGD_REGION_2_PARAMS_0__MEM_REGION_2_SPI_READ_ENABLE (0x40030f834191a000)
#define HOST_XIP__SECGD_REGION_2_PARAMS_0__MEM_REGION_2_PHYSICAL_OFFSET (0x40030dc44191a000)
#define HOST_XIP__SECGD_REGION_2_PARAMS_0__MEM_REGION_2_SECURITY_ID_MSB (0x40030cd44191a000)

/*-----------------------------------------------------------------------------
    Register name:       SECGD_REGION_2_PARAMS_1
    Relative address:    0x8004
    Absolute address:    0x4191a004
    Description:         region 2 parameters config 1
    Default Value:       0x00000001

        Field:          MEM_REGION_2_START_ADDRESS
        From..to bits:  0..19
        Default Value:  0x00001
        Access type:    read-write
        Description:    System start address

  ----------------------------------------------------------------------------- */
#define HOST_XIP__SECGD_REGION_2_PARAMS_1__ADDR              (0x4191a004)
#define HOST_XIP__SECGD_REGION_2_PARAMS_1                    (0x400300004191a004)

#define HOST_XIP__SECGD_REGION_2_PARAMS_1__MEM_REGION_2_START_ADDRESS (0x400301804191a004)

/*-----------------------------------------------------------------------------
    Register name:       SECGD_REGION_2_PARAMS_2
    Relative address:    0x8008
    Absolute address:    0x4191a008
    Description:         region 2 parameters config 2
    Default Value:       0x00000000

        Field:          MEM_REGION_2_END_ADDRESS
        From..to bits:  0..19
        Default Value:  0x00000
        Access type:    read-write
        Description:    System end address

  ----------------------------------------------------------------------------- */
#define HOST_XIP__SECGD_REGION_2_PARAMS_2__ADDR              (0x4191a008)
#define HOST_XIP__SECGD_REGION_2_PARAMS_2                    (0x400300004191a008)

#define HOST_XIP__SECGD_REGION_2_PARAMS_2__MEM_REGION_2_END_ADDRESS (0x400301804191a008)

/*-----------------------------------------------------------------------------
    Register name:       SECGD_REGION_2_PARAMS_3
    Relative address:    0x800c
    Absolute address:    0x4191a00c
    Description:         region 2 parameters config 3
    Default Value:       0x00000000

        Field:          MEM_REGION_2_SECURITY_ID_LSB
        From..to bits:  0..31
        Default Value:  0x00000000
        Access type:    read-write
        Description:    32 LSB bits of ID+COUNTER field (out of 38bits)

  ----------------------------------------------------------------------------- */
#define HOST_XIP__SECGD_REGION_2_PARAMS_3__ADDR              (0x4191a00c)
#define HOST_XIP__SECGD_REGION_2_PARAMS_3                    (0x400300004191a00c)

#define HOST_XIP__SECGD_REGION_2_PARAMS_3__MEM_REGION_2_SECURITY_ID_LSB (0x400300004191a00c)

/*-----------------------------------------------------------------------------
    Register name:       SECGE_REGION_3_PARAMS_0
    Relative address:    0x9000
    Absolute address:    0x4191b000
    Description:         region 3 parameters config 0
    Default Value:       0x00000000

        Field:          MEM_REGION_3_ENABLED
        From..to bits:  0..0
        Default Value:  0x0
        Access type:    read-write
        Description:    REGION 3 ENABLED:
                        0- Disabled
                        1- Enabled
                        Region enabled for incoming transactions

        Field:          MEM_REGION_3_DEVICE_ID
        From..to bits:  1..1
        Default Value:  0x0
        Access type:    read-write
        Description:    REGION 3 DEVICE ID:
                        0- Device_0 
                        1- Device_1

        Field:          MEM_REGION_3_SPI_WRITE_ENABLE
        From..to bits:  2..2
        Default Value:  0x0
        Access type:    read-write
        Description:    REGION 3 SPI WRITE ENABLE:
                        0- Cannot issue a SPI Write to this  region
                        1- Can issue a SPI Write to this  region

        Field:          MEM_REGION_3_SPI_READ_ENABLE
        From..to bits:  3..3
        Default Value:  0x0
        Access type:    read-write
        Description:    REGION 3 SPI READ ENABLE:
                        0- Cannot issue a SPI Read from this region
                        1- Can issue a SPI Read from this region

        Field:          MEM_REGION_3_PHYSICAL_OFFSET
        From..to bits:  4..17
        Default Value:  0x000
        Access type:    read-write
        Description:    Device related address offset

        Field:          MEM_REGION_3_SECURITY_ID_MSB
        From..to bits:  20..25
        Default Value:  0x0
        Access type:    read-write
        Description:    6 MSB bits of ID+COUNTER field (out of 38bits)

  ----------------------------------------------------------------------------- */
#define HOST_XIP__SECGE_REGION_3_PARAMS_0__ADDR              (0x4191b000)
#define HOST_XIP__SECGE_REGION_3_PARAMS_0                    (0x40030c004191b000)

#define HOST_XIP__SECGE_REGION_3_PARAMS_0__MEM_REGION_3_ENABLED (0x40030fe04191b000)
#define HOST_XIP__SECGE_REGION_3_PARAMS_0__MEM_REGION_3_DEVICE_ID (0x40030fc14191b000)
#define HOST_XIP__SECGE_REGION_3_PARAMS_0__MEM_REGION_3_SPI_WRITE_ENABLE (0x40030fa24191b000)
#define HOST_XIP__SECGE_REGION_3_PARAMS_0__MEM_REGION_3_SPI_READ_ENABLE (0x40030f834191b000)
#define HOST_XIP__SECGE_REGION_3_PARAMS_0__MEM_REGION_3_PHYSICAL_OFFSET (0x40030dc44191b000)
#define HOST_XIP__SECGE_REGION_3_PARAMS_0__MEM_REGION_3_SECURITY_ID_MSB (0x40030cd44191b000)

/*-----------------------------------------------------------------------------
    Register name:       SECGE_REGION_3_PARAMS_1
    Relative address:    0x9004
    Absolute address:    0x4191b004
    Description:         region 3 parameters config 1
    Default Value:       0x00000001

        Field:          MEM_REGION_3_START_ADDRESS
        From..to bits:  0..19
        Default Value:  0x00001
        Access type:    read-write
        Description:    System start address

  ----------------------------------------------------------------------------- */
#define HOST_XIP__SECGE_REGION_3_PARAMS_1__ADDR              (0x4191b004)
#define HOST_XIP__SECGE_REGION_3_PARAMS_1                    (0x400300004191b004)

#define HOST_XIP__SECGE_REGION_3_PARAMS_1__MEM_REGION_3_START_ADDRESS (0x400301804191b004)

/*-----------------------------------------------------------------------------
    Register name:       SECGE_REGION_3_PARAMS_2
    Relative address:    0x9008
    Absolute address:    0x4191b008
    Description:         region 3 parameters config 2
    Default Value:       0x00000000

        Field:          MEM_REGION_3_END_ADDRESS
        From..to bits:  0..19
        Default Value:  0x00000
        Access type:    read-write
        Description:    System end address

  ----------------------------------------------------------------------------- */
#define HOST_XIP__SECGE_REGION_3_PARAMS_2__ADDR              (0x4191b008)
#define HOST_XIP__SECGE_REGION_3_PARAMS_2                    (0x400300004191b008)

#define HOST_XIP__SECGE_REGION_3_PARAMS_2__MEM_REGION_3_END_ADDRESS (0x400301804191b008)

/*-----------------------------------------------------------------------------
    Register name:       SECGE_REGION_3_PARAMS_3
    Relative address:    0x900c
    Absolute address:    0x4191b00c
    Description:         region 3 parameters config 3
    Default Value:       0x00000000

        Field:          MEM_REGION_3_SECURITY_ID_LSB
        From..to bits:  0..31
        Default Value:  0x00000000
        Access type:    read-write
        Description:    32 LSB bits of ID+COUNTER field (out of 38bits)

  ----------------------------------------------------------------------------- */
#define HOST_XIP__SECGE_REGION_3_PARAMS_3__ADDR              (0x4191b00c)
#define HOST_XIP__SECGE_REGION_3_PARAMS_3                    (0x400300004191b00c)

#define HOST_XIP__SECGE_REGION_3_PARAMS_3__MEM_REGION_3_SECURITY_ID_LSB (0x400300004191b00c)


#endif //_CC35_REGS_HOST_XIP_H_
