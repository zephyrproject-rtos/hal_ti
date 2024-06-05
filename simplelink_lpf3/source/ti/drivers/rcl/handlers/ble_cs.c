/*
 * Copyright (c) 2022-2024, Texas Instruments Incorporated
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
/*
 *  ======== ble_cs.c ========
 */

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <ti/log/Log.h>

#include <ti/drivers/rcl/RCL_Command.h>
#include <ti/drivers/rcl/RCL_Buffer.h>
#include <ti/drivers/rcl/RCL_Scheduler.h>

#include <ti/drivers/rcl/hal/hal.h>
#include <ti/drivers/rcl/commands/ble_cs.h>

#include <ti/devices/DeviceFamily.h>
#include DeviceFamily_constructPath(inc/hw_lrfdtxf.h)
#include DeviceFamily_constructPath(inc/hw_lrfdrxf.h)
#include DeviceFamily_constructPath(inc/hw_lrfddbell.h)
#include DeviceFamily_constructPath(inc/hw_lrfdpbe.h)
#include DeviceFamily_constructPath(inc/hw_lrfdpbe32.h)
#include DeviceFamily_constructPath(inc/hw_lrfdmdm.h)
#include DeviceFamily_constructPath(inc/hw_lrfdmdm32.h)
#include DeviceFamily_constructPath(inc/hw_lrfdrfe.h)
#include DeviceFamily_constructPath(inc/hw_lrfdrfe32.h)
#include DeviceFamily_constructPath(inc/hw_lrfds2r.h)
#include DeviceFamily_constructPath(inc/rfe_common_ram_regs.h)
#include DeviceFamily_constructPath(inc/pbe_generic_ram_regs.h)
#include DeviceFamily_constructPath(inc/pbe_common_ram_regs.h)
#include DeviceFamily_constructPath(inc/pbe_ble5_ram_regs.h)
#include DeviceFamily_constructPath(inc/pbe_ble_cs_ram_regs.h)
#include DeviceFamily_constructPath(inc/pbe_ble_cs_regdef_regs.h)

#ifndef OCTOPUS
#include DeviceFamily_constructPath(inc/hw_types.h)
#include DeviceFamily_constructPath(inc/hw_memmap.h)
#include DeviceFamily_constructPath(inc/hw_gpio.h)
#include DeviceFamily_constructPath(inc/hw_ioc.h)
#endif

#define BLE_CS_BASE_FREQ_MHZ            2402
#define BLE_CS_MAX_CHANNEL              78
#define BLE_CS_NUM_CHANNELS             90
#define BLE_CS_NUM_INVALID_CHANNELS     7
#define BLE_CS_SILENT_CHANNEL           100
#define BLE_CS_NUM_PERMUTATION          24
#define BLE_CS_S2R_OVERSAMPLE_RATE      4
#define BLE_CS_S2R_MEMORY_OFFSET        0x0C00
#define BLE_CS_TXFIFO_BASE_ADDR         128
#define BLE_CS_TXFIFO_LEN               96
#define BLE_CS_RXFIFO_BASE_ADDR         224
#define BLE_CS_RXFIFO_LEN               160
#define BLE_CS_FIRST_BATCH_SIZE         2
#define BLE_CS_TONE_QUALITY_GOOD_THR    25
#define BLE_CS_TONE_QUALITY_MEDIUM_THR  50
#define BLE_CS_TONE_EXTENSION_INITIATOR_TX 0b01
#define BLE_CS_TONE_EXTENSION_REFLECTOR_TX 0b10
#define DECODE_ANTENNA(x, y)            (((x) >> ((y)*2)) & 0x03)
#define ENCODE_ANTENNA(x, y)            (((x) << ((y)*4)))
#define INT16_MSB(x)                    (((x) >> 8) & 0xFF)
#define INT16_LSB(x)                    ((x) & 0xFF)

/* Prepare constant terms for step specific calculations */
#define T1US  48  // Constant 1us at 48MHz
#define T3US  144 // Constant 3us at 48MHz
#define TRD   240 // Constant 5us at 48MHz
#define TGD   480 // Constant 10us at 48MHz
#define TPLT  960 // Constant 20us at 48MHz
#define TPYL  0   // Unknown at this point

/*
 *  ======== Execution status ========
 */
struct
{
    struct {
        RCL_CommandStatus endStatus;
    } common;
    struct {
        uint32_t startTime;
    } ble_cs;
} bleCsHandlerState;

/* Storage to decompress data */
RCL_CmdBleCs_Step_Internal       step;
RCL_CmdBleCs_StepResult_Internal result;

/* Precalculated base terms */
uint32_t tStepLut[RCL_CmdBleCs_StepMode_Length];
uint16_t tAdjALut[RCL_CmdBleCs_StepMode_Length];
uint16_t tAdjBLut[RCL_CmdBleCs_StepMode_Length];
uint16_t tAntALut[RCL_CmdBleCs_StepMode_Length];
uint16_t tAntBLut[RCL_CmdBleCs_StepMode_Length];
uint16_t tRttAdjustLut[RCL_CmdBleCs_StepMode_Length];

/*
 *  ======== Type for indexing antenna sequence ========
 */
typedef union {
    struct {
        uint8_t a0 : 2;
        uint8_t a1 : 2;
        uint8_t a2 : 2;
        uint8_t a3 : 2;
    } a;
    uint8_t apn;
} RCL_AntennaPath_t;

/*
 *  ======== Type for mapping antenna permutation to antenna sequence ========
 */
typedef struct {
    uint8_t numPath : 3;    /*!< Total number of antenna path */
    uint8_t numPerm : 5;    /*!< Total number of permutation possible with this configuration */
    uint8_t increment;      /*!< How to index the permutation table */
    RCL_AntennaPath_t ap[2];
} RCL_AntennaConfig_t;

/*
 *  ======== Antenna permutation table ========
 */
const RCL_AntennaPath_t antennaPermutation[BLE_CS_NUM_PERMUTATION] = {
    /*[ 0:5 ]=*/{{0,1,2,3}}, {{0,1,3,2}}, {{0,2,3,1}}, {{0,2,1,3}}, {{0,3,1,2}}, {{0,3,2,1}},
    /*[ 6:11]=*/{{1,0,2,3}}, {{1,0,3,2}}, {{1,2,3,0}}, {{1,2,0,3}}, {{1,3,0,2}}, {{1,3,2,0}},
    /*[12:17]=*/{{2,0,1,3}}, {{2,0,3,1}}, {{2,1,3,0}}, {{2,1,0,3}}, {{2,3,0,1}}, {{2,3,1,0}},
    /*[18:24]=*/{{3,0,2,1}}, {{3,0,1,2}}, {{3,1,2,0}}, {{3,1,0,2}}, {{3,2,0,1}}, {{3,2,1,0}}
};

/*
 *  ======== Antenna permutation selection mapping ========
 */
const RCL_AntennaConfig_t antennaConfig[RCL_CmdBleCs_AntennaConfig_Length] = {
    /*1x1=*/{.numPath=1, .numPerm=1,  .increment=0, .ap={/*initiator=*/{{0,0,0,0}}, /*reflector=*/{{0,0,0,0}}}},
    /*2x1=*/{.numPath=2, .numPerm=2,  .increment=6, .ap={/*initiator=*/{{0,1,0,0}}, /*reflector=*/{{0,0,0,0}}}},
    /*3x1=*/{.numPath=3, .numPerm=6,  .increment=3, .ap={/*initiator=*/{{0,1,2,0}}, /*reflector=*/{{0,0,0,0}}}},
    /*4x1=*/{.numPath=4, .numPerm=24, .increment=1, .ap={/*initiator=*/{{0,1,2,3}}, /*reflector=*/{{0,0,0,0}}}},
    /*1x2=*/{.numPath=2, .numPerm=2,  .increment=6, .ap={/*initiator=*/{{0,0,0,0}}, /*reflector=*/{{0,1,0,0}}}},
    /*1x3=*/{.numPath=3, .numPerm=6,  .increment=3, .ap={/*initiator=*/{{0,0,0,0}}, /*reflector=*/{{0,1,2,0}}}},
    /*1x4=*/{.numPath=4, .numPerm=24, .increment=1, .ap={/*initiator=*/{{0,0,0,0}}, /*reflector=*/{{0,1,2,3}}}},
    /*2x2=*/{.numPath=4, .numPerm=24, .increment=1, .ap={/*initiator=*/{{0,0,1,1}}, /*reflector=*/{{0,1,1,0}}}}
};

/*
 *  ======== Type of configuration of MCE and FIDC accumulator used for PCT measurement ========
 */
typedef union {
    struct {
        uint8_t period       : 2;   /*!< Configures the accumulation period of DEMFIDC module */
        uint8_t numIteration : 2;   /*!< Configures how many times to run the accumulator period */
        uint8_t fracWaitAdj  : 4;
        uint8_t fracWait;
    };
    uint16_t val;
} RCL_PctConfig_t;

typedef union {
    struct {
        uint8_t magnIteration;
        uint8_t reserved;
    };
    uint16_t val;
} RCL_MagnConfig_t;

typedef struct {
    int16_t mode0[2];
    int16_t mode1[2];
    int16_t mode2[2];
    int16_t mode3[2];
} RCL_Tadjust_t;

/*
 *  ======== Type of configuration for phy specific settings ========
 */
typedef struct {
    /* Modem specific registers */
    uint16_t        baud;
    uint16_t        symmap;
    uint16_t        demmisc2;
    uint16_t        demmisc3;
    uint16_t        rssioffset;

    /* Timing parameters [48 MHz units unless specified otherwise] */
    uint16_t        tPostProcessDiv1;   /*!<  Duration set aside for post processing */
    uint16_t        tPostProcessDiv12;  /*!<  Duration set aside for post processing */
    uint16_t        tRxTimeoutI0;       /*!<  Initiator must terminate packet reception before end of step */
    uint16_t        tRxTimeoutI3;       /*!<  Initiator must terminate packet reception before end of step */
    int16_t         tPilotAdjust;       /*!<  Pilot tone need to be adjusted with shaper delay */
    uint16_t        tStartup;           /*!<  Duration set aside for starting up the topSMs and start to emit a tone on the antenna */
    uint16_t        tPacket;            /*!<  Duration of packet [preamble + AA + Trailer] */
    uint16_t        tRxTimeoutRn;       /*!<  Reception timeout on reflector side */
    uint16_t        tInfiniteRx;        /*!<  Correction of step duration when packet reception is used as anchor point */
    uint16_t        tTr;                /*!<  Duration of trailer bits */
    uint16_t        tCorr;              /*!<  Time between signal on antenna and correlation event */
    uint16_t        tDem;               /*!<  Time between signal on antenna and demodulation completed*/
    uint16_t        tFidc;              /*!<  Time between signal on antenna and FIDC */
    uint16_t        tTxModDelay;        /*!<  Time between modulator and signal on antenna (mostly shaper delay) */
    uint16_t        tTimestampDelay1;   /*!<  Sum of delays between signal on antenna vs capture on timer by HW for mode-1 */
    uint16_t        tTimestampDelay3;   /*!<  Sum of delays between signal on antenna vs capture on timer by HW for mode-3 */

    /* Accumulator period and iteration number in order to fit into the same TPM period. */
    RCL_PctConfig_t pctConfig[RCL_CmdBleCs_Tpm_Length];

    /* Magnitude accumulator configuration used by RFE for tone quality estimation */
    RCL_MagnConfig_t magnConfig[RCL_CmdBleCs_Tpm_Length];

    /* Adjustment of TIP period per mode */
    RCL_Tadjust_t tAdj[RCL_CmdBleCs_Role_Length];

    /* Adjustment of antenna timings for mode 2 & 3 */
    RCL_Tadjust_t tAnt[RCL_CmdBleCs_Role_Length];
} RCL_PhyConfig_t;

//#define FE_8MHZ 1
/*
 *  ======== Configuration per PHY ========
 */
const RCL_PhyConfig_t phyConfigLut[RCL_CmdBleCs_Phy_Length] = {
    #ifdef FE_8MHZ
    {   /* Phy_1M @ 8MHZ*/
        .baud       = 0x4000,
        .symmap     = 0x001F,
        .demmisc2   = 0x15F8,
        .demmisc3   = 0x10A1,
        .rssioffset = 0x0049,

        /* Theory */
        .tPacket           = 2112, // 8+32+4 bits = 44us
        .tTr               = 192,  // 4us

        /* Tuned */
        .tStartup          = 93,  // 1.937us (pbe_timer_event -> mce_timer start)
        .tTxModDelay       = 245, // 5.109us (wait -> signal on shaper)
        .tPilotAdjust      = 264, // 5.5us
        .tPostProcessDiv1  = 936, // 19.5us
        .tPostProcessDiv12 = 78,  // 19.5us
        .tInfiniteRx       = 60,  // 1.25us

        .tFidc             = 161, // 3.35us
        .tCorr             = 244, // 5.08us
        .tDem              = 783, // 16.31us

        .tRxTimeoutI0      = RCL_BLE_CS_US_TO_MCE_TIMER(70),
        .tRxTimeoutI3      = RCL_BLE_CS_US_TO_MCE_TIMER(56),
        .tRxTimeoutRn      = RCL_BLE_CS_US_TO_MCE_TIMER(76),

        /* Sum of demodulation and modulation delay (HW only) */
        .tTimestampDelay1  = 477,
        .tTimestampDelay3  = 481,

        .pctConfig = {
            /*TPM = 10US*/{.period = (LRFDMDM_DEMFIDC0_ACCPERIOD_SMPL32 >> LRFDMDM_DEMFIDC0_ACCPERIOD_S),  .numIteration = 2, .fracWait = 32,  .fracWaitAdj = 9},
            /*TPM = 20US*/{.period = (LRFDMDM_DEMFIDC0_ACCPERIOD_SMPL128 >> LRFDMDM_DEMFIDC0_ACCPERIOD_S), .numIteration = 1, .fracWait = 128, .fracWaitAdj = 0},
            /*TPM = 40US*/{.period = (LRFDMDM_DEMFIDC0_ACCPERIOD_SMPL128 >> LRFDMDM_DEMFIDC0_ACCPERIOD_S), .numIteration = 2, .fracWait = 128, .fracWaitAdj = 0}
        },

        .magnConfig = {
            /*TPM = 10US*/{.magnIteration = 5},
            /*TPM = 20US*/{.magnIteration = 14},
            /*TPM = 40US*/{.magnIteration = 30}
        },

        .tAdj = { /* { pkt-tn, tn-tn} */
            {
                /* Initiator */
                .mode0 = {0, 0},
                .mode1 = {0, 0},
                .mode2 = {-147, +112},
                .mode3 = {0, +28}
            },
            {
                /* Reflector */
                .mode0 = {+11, 0},
                .mode1 = {+11, 0},
                .mode2 = {-66, -96},
                .mode3 = {-50, -54}
            }
        },

        .tAnt = {
            {
                /* Initiator */
                .mode2 = {0, 0},
                .mode3 = {0, 0}
            },
            {
                /* Reflector */
                .mode2 = {0, 0},
                .mode3 = {0, 0}
            }
        }
    },
    #else
    {   /* Phy_1M @ 4MHZ*/
        .baud       = 0x4000,
        .symmap     = 0x001F,
        .demmisc2   = 0x05F8,
        .demmisc3   = 0x1082,
        .rssioffset = 0x0049,

        /* Theory */
        .tPacket           = 2112, // 8+32+4 bits = 44us
        .tTr               = 192,  // 4us

        /* Tuned */
        .tStartup          = 93,  // 1.937us (pbe_timer_event -> mce_timer start)
        .tTxModDelay       = 245, // 5.109us (wait -> signal on shaper)
        .tPilotAdjust      = 259, // 5.39us
        .tPostProcessDiv1  = 936, // 19.5us
        .tPostProcessDiv12 = 78,  // 19.5us
        .tInfiniteRx       = 60,  // 1.25us

        .tFidc             = 264, // 5.5us
        .tCorr             = 377, // 7.85us
        .tDem              = 914, // 19.05us

        .tRxTimeoutI0      = RCL_BLE_CS_US_TO_MCE_TIMER(70),
        .tRxTimeoutI3      = RCL_BLE_CS_US_TO_MCE_TIMER(56),
        .tRxTimeoutRn      = RCL_BLE_CS_US_TO_MCE_TIMER(76),

        /* Sum of demodulation and modulation delay (HW only) */
        .tTimestampDelay1  = 603,
        .tTimestampDelay3  = 601,

        .pctConfig = {
            /*TPM = 10US*/{.period = (LRFDMDM_DEMFIDC0_ACCPERIOD_SMPL32 >> LRFDMDM_DEMFIDC0_ACCPERIOD_S),  .numIteration = 1, .fracWait = 32,  .fracWaitAdj = 0},
            /*TPM = 20US*/{.period = (LRFDMDM_DEMFIDC0_ACCPERIOD_SMPL32 >> LRFDMDM_DEMFIDC0_ACCPERIOD_S),  .numIteration = 2, .fracWait = 32,  .fracWaitAdj = 0},
            /*TPM = 40US*/{.period = (LRFDMDM_DEMFIDC0_ACCPERIOD_SMPL128 >> LRFDMDM_DEMFIDC0_ACCPERIOD_S), .numIteration = 1, .fracWait = 128, .fracWaitAdj = 0}
        },

        .magnConfig = {
            /*TPM = 10US*/{.magnIteration = 3},
            /*TPM = 20US*/{.magnIteration = 6},
            /*TPM = 40US*/{.magnIteration = 14}
        },

        .tAdj = { /* { pkt-tn, tn-tn} */
            {
                /* Initiator */
                .mode0 = {0, 0},
                .mode1 = {0, 0},
                .mode2 = {-147, +64},
                .mode3 = {0, -22}
            },
            {
                /* Reflector */
                .mode0 = {+27, 0},
                .mode1 = {+27, 0},
                .mode2 = {-94, -48},
                .mode3 = {-96, +16}
            }
        },

        .tAnt = {
            {
                /* Initiator */
                .mode2 = {+60, 0},
                .mode3 = {+66, 0}
            },
            {
                /* Reflector */
                .mode2 = {+105, 0},
                .mode3 = {+105, 0}
            }
        }
    },
    #endif
    {   /* Phy_2M */
        .baud       = 0x8000,
        .symmap     = 0x002E,
        .demmisc2   = 0x04F8,
        .demmisc3   = 0x1081,
        .rssioffset = 0x0049,

        /* Theory */
        .tPacket           = 1248, // 16+32+4bit = 26us
        .tTr               = 96,   // 2us

        /* Tuned */
        .tStartup          = 95,   // 1.979us (pbe_timer_event -> mce_timer start)
        .tTxModDelay       = 142,  // 2.957us (wait -> signal on shaper)
        .tPilotAdjust      = 156,  // 4.02us
        .tPostProcessDiv1  = 720,  // 15us
        .tPostProcessDiv12 = 60,   // 15us
        .tInfiniteRx       = 60,   // 1.25us

        .tFidc             = 146, // 3.05us
        .tCorr             = 204, // 4.25us
        .tDem              = 565, // 11.77us

        .tRxTimeoutI0      = 2448+24, // 51us   MCE
        .tRxTimeoutI3      = 1776,    // 37us   MCE
        .tRxTimeoutRn      = 3096,    // 64.5us MCE

        /* Sum of demodulation and modulation delay (HW only) */
        .tTimestampDelay1  = 333,
        .tTimestampDelay3  = 335,

        .pctConfig = {
            /*TPM = 10US*/{.period = (LRFDMDM_DEMFIDC0_ACCPERIOD_SMPL32 >> LRFDMDM_DEMFIDC0_ACCPERIOD_S),  .numIteration = 2, .fracWait = 32,  .fracWaitAdj = 9},
            /*TPM = 20US*/{.period = (LRFDMDM_DEMFIDC0_ACCPERIOD_SMPL128 >> LRFDMDM_DEMFIDC0_ACCPERIOD_S), .numIteration = 1, .fracWait = 128, .fracWaitAdj = 0},
            /*TPM = 40US*/{.period = (LRFDMDM_DEMFIDC0_ACCPERIOD_SMPL128 >> LRFDMDM_DEMFIDC0_ACCPERIOD_S), .numIteration = 2, .fracWait = 128, .fracWaitAdj = 0}
        },

        .magnConfig = {
            /*TPM = 10US*/{.magnIteration = 5},
            /*TPM = 20US*/{.magnIteration = 14},
            /*TPM = 40US*/{.magnIteration = 30}
        },

        .tAdj = {
            {
                /* Initiator */
                .mode0 = {0, 0},
                .mode1 = {0, 0},
                .mode2 = {-48, +107},
                .mode3 = {0, 0}
            },
            {
                /* Reflector */
                .mode0 = {+32, 0},
                .mode1 = {+32, 0},
                .mode2 = {-38, -93},
                .mode3 = {-60, -20}
            }
        },

        .tAnt = {
            {
                /* Initiator */
                .mode2 = {+63, 0},
                .mode3 = {+63, 0}
            },
            {
                /* Reflector */
                .mode2 = {+129, 0},
                .mode3 = {+129, 0}
            }
        }
    }
};

/* Frequency compensation value due to the fixed CMIXN value use. Resolution is 4x FOFF unit.
   Calculated based on the formula:
   foffError = 4x ((((1<<21) * fif) / (BLE_CS_BASE_FREQ_MHZ + pStepI->channelIdx) / 1e3)
             - ((1<<21) * (1024 - pStepI->cmixn) / 288 / 1024)); */
const int8_t foffErrorLut[BLE_CS_NUM_CHANNELS] = {
    /*2402 MHz =*/  38, 34, 34, 34, 30, 30, 30, 26,
    /*2410 MHz =*/  26, 26, 26, 22, 22, 22, 18, 18, 18, 14,
    /*2420 MHz =*/  14, 14, 10, 10, 10, 10,  6,  6,  6,  2,
    /*2430 MHz =*/   2,  2, -2, -2, -2, -2, -6, -6, -6,-10,
    /*2440 MHz =*/ -10,-10,-14,-14,-14,-14,-18,-18,-18,-22,
    /*2450 MHz =*/ -22,-22,-26,-26,-26,-26,-30,-30,-30,-34,
    /*2460 MHz =*/ -34,-34,-34,-38,-38,-38,-42,-42,-42,-46,
    /*2470 MHz =*/ -46,-46,-46,-50,-50,-50,-54,-54,-54,-54,
    /*2480 MHz =*/ -58,-58,-58,-62,-62,-62,-62,-66,-66,-66
};

/* Look up table of payload length in units of MCE Timer at rate of [1M]. Scaling dynamically if needed. */
const uint16_t payloadLut[RCL_CmdBleCs_Payload_Length] = {
    /*0 bits =*/   RCL_BLE_CS_US_TO_MCE_TIMER(0),
    /*32 bits =*/  RCL_BLE_CS_US_TO_MCE_TIMER(32),
    /*64 bits =*/  RCL_BLE_CS_US_TO_MCE_TIMER(64),
    /*96 bits =*/  RCL_BLE_CS_US_TO_MCE_TIMER(96),
    /*128 bits =*/ RCL_BLE_CS_US_TO_MCE_TIMER(128)
};

/* Forward declarations */
static RCL_MultiBuffer* RCL_Handler_BLE_CS_findBufferFitNumberOfBytes(List_List *pHead, uint16_t numBytes);
static void RCL_Handler_BLE_CS_configureTxRxFifo(RCL_CmdBleCs* pCmd);
static void RCL_Handler_BLE_CS_retrieveAndStoreNextResult(RCL_CmdBleCs* pCmd, bool forceBufferToFinishState);
static void RCL_Handler_BLE_CS_fetchAndforwardNextStep(RCL_CmdBleCs* pCmd);
static RCL_Events RCL_Handler_BLE_CS_preFillTxBuffer(RCL_CmdBleCs* pCmd);
static RCL_Events RCL_Handler_BLE_CS_readWriteBuffer(RCL_CmdBleCs* pCmd, bool forceBufferToFinishState);
static bool RCL_Handler_BLE_CS_transferFinishedBuffers(List_List *pSrc, List_List *pDst);
static void RCL_Handler_BLE_CS_configureS2R(RCL_CmdBleCs *pCmd);
static RCL_Events RCL_Handler_BLE_CS_readS2RSamples(RCL_CmdBleCs *pCmd);
static void RCL_Handler_BLE_CS_readStatistics(RCL_CmdBleCs *pCmd);
static void RCL_Handler_BLE_CS_preprocessCommand(RCL_CmdBleCs *pCmd);
static void RCL_Handler_BLE_CS_preprocessStep(RCL_CmdBleCs *pCmd, RCL_CmdBleCs_Step *pStep, RCL_CmdBleCs_Step_Internal *pStepI);
static RCL_CmdBleCs_StepResult_Internal* RCL_Handler_BLE_CS_fetchNextStepResult(RCL_CmdBleCs *pCmd);
static int16_t RCL_Handler_BLE_CS_convertFreqOffset(int16_t foffMeasured);
static int16_t RCL_Handler_BLE_CS_convertRtt(RCL_CmdBleCs *pCmd, uint8_t mode, int8_t channel, int16_t foff, uint8_t payload, bool secondToneExtensionSlot, float toAD, uint16_t corrBefore, uint16_t corrPeak, uint16_t corrAfter);
static uint32_t RCL_Handler_BLE_CS_convertPct(int16_t pct_i, int16_t pct_q, uint8_t channelIdx);
static uint8_t RCL_Handler_BLE_CS_convertPctQuality(uint16_t qMin, uint16_t qMax, uint16_t qAvg, bool toneExtensionSlot, bool toneExpected);
static uint16_t RCL_Handler_BLE_CS_estimateStepResultLength(RCL_CmdBleCs *pCmd,RCL_CmdBleCs_StepResult_Internal* src);
static uint16_t RCL_Handler_BLE_CS_convertStepResult(RCL_CmdBleCs* pCmd, uint8_t *dst, RCL_CmdBleCs_StepResult_Internal* src);
static RCL_CommandStatus RCL_Handler_BLE_CS_findPbeErrorEndStatus(uint16_t pbeEndStatus);

/*
 *  ======== Traverse multibuffer list looking for space ========
 */
static RCL_MultiBuffer* RCL_Handler_BLE_CS_findBufferFitNumberOfBytes(List_List *pHead, uint16_t numBytes)
{
    /* Start search from the head of list */
    RCL_MultiBuffer *pBuffer = RCL_MultiBuffer_head(pHead);

    /* Traverse the chain of buffers and find the first free one */
    do {
        pBuffer = RCL_MultiBuffer_findFirstWritableBuffer(pBuffer);

        /* Avoid NULL pointer dereferencing */
        if (pBuffer)
        {
            /* Check for available space */
            if (pBuffer->length - pBuffer->tailIndex >= numBytes)
            {
                /* Mark the buffer to be written */
                pBuffer->state = RCL_BufferStateInUse;

                break;
            }
            else
            {
                /* The buffer will not fit the incoming number of bytes */
                pBuffer->state = RCL_BufferStateFinished;
            }
        }
    } while (pBuffer);

    return (pBuffer);
}

/*
 *  ======== Transfer all buffers marked as finished from one list to another ========
 */
static bool RCL_Handler_BLE_CS_transferFinishedBuffers(List_List *pSrc, List_List *pDst)
{
    /* Initialize return value */
    bool callbackEvent = false;
    RCL_MultiBuffer *pBuffer = NULL;

    /* Transfer the used buffers */
    do
    {
        pBuffer = RCL_MultiBuffer_head(pSrc);

        if (pBuffer && (pBuffer->state == RCL_BufferStateFinished))
        {
            /* Pop from list and add to done list */
            RCL_MultiBuffer *pBuff = RCL_MultiBuffer_get(pSrc);
            RCL_MultiBuffer_put(pDst, pBuff);

            /* Trigger callback side effect*/
            callbackEvent = true;
        }
        else
        {
            break;
        }
    } while (pBuffer);

    return (callbackEvent);
}

/*
 *  ======== Configure the BUFRAM size and interrupts for BLE CS ========
 */
static void RCL_Handler_BLE_CS_configureTxRxFifo(RCL_CmdBleCs* pCmd)
{
    /* Override the FIFO location and size */
    HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_FCFG1) = BLE_CS_TXFIFO_BASE_ADDR;
    HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_FCFG2) = BLE_CS_TXFIFO_LEN;
    HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_FCFG3) = BLE_CS_RXFIFO_BASE_ADDR;
    HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_FCFG4) = BLE_CS_RXFIFO_LEN;

    /* Reset FIFOs to have a clean start */
    /* Writing to FCMD is safe since the PBE is not running, ref. RCL-367 */
    HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_FCMD) = LRFDPBE_FCMD_DATA_FIFO_RESET;

    /* Calculate how many entries can be stored simultaneous in given size of tx/rx fifos */
    uint16_t nStepsFit = HWREG_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_TXFWRITABLE) / sizeof(RCL_CmdBleCs_Step_Internal);
    HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_TXFWBTHRS) = (nStepsFit - 1) * sizeof(RCL_CmdBleCs_Step_Internal);

    uint16_t nResultsFit = HWREG_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_RXFWRITABLE) / sizeof(RCL_CmdBleCs_StepResult_Internal);
    HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_RXFRBTHRS) = (nResultsFit - 1) * sizeof(RCL_CmdBleCs_StepResult_Internal);

    #ifndef PG2
    /* CDDS BUG00003 - Temporarily workaround */
    HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_RXFRBTHRS) = sizeof(RCL_CmdBleCs_StepResult_Internal);
    #endif

    /* FIFO pointers should auto-commit/auto-dealloc, enable threshold events */
    HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_FCFG0)   = HWREG_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_FCFG0) | (LRFDPBE_FCFG0_TXACOM_M | LRFDPBE_FCFG0_TXADEAL_M | LRFDPBE_FCFG0_RXACOM_M | LRFDPBE_FCFG0_RXADEAL_M);
    HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_FCFG0)   = HWREG_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_FCFG0) & (~(LRFDPBE_FCFG0_RXIRQMET_M | LRFDPBE_FCFG0_TXIRQMET_M));

    /* Clear any interrupts left from uninitialized fifos */
    HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_EVTCLR1)  =  (LRFDPBE_EVTCLR1_RXRDBTHR_M |  LRFDPBE_EVTCLR1_RXWRBTHR_M | LRFDPBE_EVTCLR1_TXRDBTHR_M | LRFDPBE_EVTCLR1_TXWRBTHR_M);
    HWREG_WRITE_LRF(LRFDDBELL_BASE + LRFDDBELL_O_ICLR0) = HWREG_READ_LRF(LRFDDBELL_BASE + LRFDDBELL_O_ICLR0) | (LRFDDBELL_ICLR0_RXFIFO_M | LRFDDBELL_ICLR0_TXFIFO_M);
}

/*
 *  ======== Fill the BLE CS step descriptors into the BUFRAM TX FIFO ========
 */
static RCL_Events RCL_Handler_BLE_CS_preFillTxBuffer(RCL_CmdBleCs* pCmd)
{
    /* Initialize return value */
    RCL_Events events = {.value = 0};

    /* Calculate how many additional step will fit (which might be all) */
    uint16_t nWritable  = HWREG_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_TXFWRITABLE) / sizeof(RCL_CmdBleCs_Step_Internal);
    uint16_t nRemaining = (pCmd->mode.repeatSteps) ? (pCmd->mode.nSteps) : (pCmd->mode.nSteps - pCmd->stats->nStepsWritten);
    uint16_t nBatch     = (nWritable < nRemaining) ? nWritable : nRemaining;

    /* Limited time is available when we start the command (ABS_START_TIME_OFFSET),
        so the first batch is reduced */
    if (pCmd->stats->nStepsWritten == 0)
    {
        nBatch = (nBatch < BLE_CS_FIRST_BATCH_SIZE) ? nBatch : BLE_CS_FIRST_BATCH_SIZE;
    }

    /* Transfer the calculated number of steps into the fifo */
    for (uint16_t i=0; i<nBatch; i++)
    {
        RCL_Handler_BLE_CS_fetchAndforwardNextStep(pCmd);
    }

    /* Transfer the used buffers, should trigger a callback if any */
    events.txBufferFinished = (uint32_t) RCL_Handler_BLE_CS_transferFinishedBuffers(&pCmd->stepBuffers, &pCmd->stepBuffersDone);

    return (events);
}

/*
 *  ======== Write the BLE CS Steps to the BUFRAM TX fifo ========
 */
static void RCL_Handler_BLE_CS_fetchAndforwardNextStep(RCL_CmdBleCs* pCmd)
{
    /* Default return value */
    RCL_CmdBleCs_Step *pStep = NULL;

    /* Buffers are served on a FIFO basis */
    RCL_MultiBuffer *pStepBuffer = RCL_MultiBuffer_head(&pCmd->stepBuffers);

    /* Handle buffer boundaries within a batch */
    pStepBuffer = RCL_MultiBuffer_findFirstWritableBuffer(pStepBuffer);
    if (pStepBuffer)
    {
        /* Flag the buffer */
        pStepBuffer->state = RCL_BufferStateInUse;

        /* Point to the beginning of step list */
        pStep = (RCL_CmdBleCs_Step *) &pStepBuffer->data[0];

        /* Verify that there is enough bytes in the buffer */
        if ((pStepBuffer->headIndex + sizeof(RCL_CmdBleCs_Step)) <= pStepBuffer->tailIndex)
        {
            /* Point to the next entry */
            pStep += pStepBuffer->headIndex/sizeof(RCL_CmdBleCs_Step);

            /* Decompress and calculate internal parameters on step */
            RCL_Handler_BLE_CS_preprocessStep(pCmd, pStep, &step);

            /* Send it to PBE */
            uint32_t *ptr = (uint32_t *) &step;
            for(uint8_t j=0; j<sizeof(RCL_CmdBleCs_Step_Internal)/sizeof(uint32_t); j++)
            {
                HWREG_WRITE_LRF(LRFDTXF_BASE + LRFDTXF_O_TXD) = *(ptr + j);
            }

            /* The step have been consumed */
            pCmd->stats->nStepsWritten++;
            pStepBuffer->headIndex += sizeof(RCL_CmdBleCs_Step);

            /* This buffer is exhausted, or end of subevent */
            if (pStepBuffer->headIndex == pStepBuffer->tailIndex)
            {
                if (pCmd->mode.repeatSteps == false)
                {
                    /* Update state and move the buffer */
                    pStepBuffer->state = RCL_BufferStateFinished;
                }
                else
                {
                    /* Pretend that this is the beginning of the sequence */
                    pStepBuffer->headIndex = 0;
                    pCmd->stats->nStepsWritten = 0;
                }
            }
        }
    }
}

/*
 *  ======== Read the BLE CS Step results from the BUFRAM RX fifo ========
 */
static void RCL_Handler_BLE_CS_retrieveAndStoreNextResult(RCL_CmdBleCs* pCmd, bool forceBufferToFinishState)
{
    uint32_t *ptr = (uint32_t *) &result;
    for(uint8_t j=0; j<sizeof(RCL_CmdBleCs_StepResult_Internal)/sizeof(uint32_t); j++)
    {
        *(ptr+j) = HWREG_READ_LRF(LRFDRXF_BASE + LRFDRXF_O_RXD);
    }

    if (result.pktResult == RCL_CmdBleCs_PacketResult_Ok)
    {
        pCmd->stats->nRxOk += 1;
    }
    else
    {
        pCmd->stats->nRxNok += 1;
    }

    /* Pop and fill the next container */
    RCL_CmdBleCs_StepResult_Internal *pResult = RCL_Handler_BLE_CS_fetchNextStepResult(pCmd);
    if (pResult)
    {
        memcpy(pResult, (RCL_CmdBleCs_StepResult_Internal *) &result, sizeof(RCL_CmdBleCs_StepResult_Internal));
    }

    /* Identify HCI compression size */
    uint16_t requiredSpaceInBytes = RCL_Handler_BLE_CS_estimateStepResultLength(pCmd, (RCL_CmdBleCs_StepResult_Internal *) &result);

    /* Alternative HCI destination */
    RCL_MultiBuffer *pResultBuffer = RCL_Handler_BLE_CS_findBufferFitNumberOfBytes(&pCmd->resultBuffers, requiredSpaceInBytes);

    /* Increment if either internal or HCI format is used */
    if (pResult || pResultBuffer) 
    {
        pCmd->stats->nResultsRead++;
    }

    /* Avoid NULL pointer dereferencing */
    if (pResultBuffer)
    {
        /* Decode the start of the segment */
        RCL_CmdBleCs_SubeventResults *pSubeventResults = (RCL_CmdBleCs_SubeventResults *) pResultBuffer->data;

        /* Initialize header in an empty buffer */
        if (pResultBuffer->tailIndex == 0)
        {
            /* No steps reported yet */
            pSubeventResults->numStepsReported = 0;

            /* Increment tail with header length */
            RCL_MultiBuffer_commitBytes(pResultBuffer, sizeof(RCL_CmdBleCs_SubeventResults));
        }

        /* Update the HCI header */
        pSubeventResults->numStepsReported     += 1;
        pSubeventResults->numAntennaPath        = pCmd->stats->numAntennaPath + 1;
        pSubeventResults->referencePowerLevel   = result.gain;
        pSubeventResults->frequencyCompensation = RCL_Handler_BLE_CS_convertFreqOffset(HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_FOFFCOMP) << 2);

        if (pCmd->stats->nResultsRead == 1) 
        {
            pCmd->stats->reserved0 = result.gain;
        }

        /* Decode the offset of data field */
        uint8_t *pResult = RCL_MultiBuffer_getNextWritableByte(pResultBuffer);

        /* Compress and write the data */
        uint32_t nBytes = RCL_Handler_BLE_CS_convertStepResult(pCmd, pResult, (RCL_CmdBleCs_StepResult_Internal *) &result);

        /* Commit the pointers in the buffer */
        RCL_MultiBuffer_commitBytes(pResultBuffer, nBytes);

        /* Force close the multibuffer, even if there is more space left */
        if ( (pCmd->mode.repeatSteps == false) && (pCmd->mode.nSteps == pCmd->stats->nResultsRead) )
        {
            pResultBuffer->state = RCL_BufferStateFinished;
        }
        else if (forceBufferToFinishState)
        {
            pResultBuffer->state = RCL_BufferStateFinished;
        }
    }
}

/*
 *  ======== Read the BLE CS Step results from the BUFRAM RX fifo ========
 */
static RCL_Events RCL_Handler_BLE_CS_readWriteBuffer(RCL_CmdBleCs* pCmd, bool forceBufferToFinishState)
{
    /* Initialize return value */
    RCL_Events events = {.value = 0};

    /* Calculate how many result entries are available in rx fifo (might be all that has left) */
    uint16_t nBatch  = HWREG_READ_LRF(LRFDPBE_BASE + LRFDPBE_O_RXFREADABLE) / sizeof(RCL_CmdBleCs_StepResult_Internal);

    /* Read out the calculated number of entries */
    for (uint16_t i=0; i<nBatch; i++)
    {
        /* Retrieve all that's available and terminate*/
        bool forceTerminate = (forceBufferToFinishState && (i == nBatch-1));

        RCL_Handler_BLE_CS_retrieveAndStoreNextResult(pCmd, forceTerminate);
        RCL_Handler_BLE_CS_fetchAndforwardNextStep(pCmd);
    }

    /* Transfer the used buffers, should trigger a callback if any */
    events.rxBufferFinished = (uint32_t) RCL_Handler_BLE_CS_transferFinishedBuffers(&pCmd->resultBuffers, &pCmd->resultBuffersDone);
    events.txBufferFinished = (uint32_t) RCL_Handler_BLE_CS_transferFinishedBuffers(&pCmd->stepBuffers, &pCmd->stepBuffersDone);

    /* Reduce the batch size if there is only a few entries missing */
    int16_t nRemaining = pCmd->mode.nSteps - pCmd->stats->nResultsRead;
    if (nRemaining <= 0)
    {
        if (pCmd->mode.repeatSteps == false)
        {
            /* No more results expected, set the threshold to the max */
            HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_RXFRBTHRS) = 0x3FF;
        }
    }
    else if (nRemaining < nBatch)
    {
        /* Reduce the Fifo threshold to number of remaining steps */
        HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_RXFRBTHRS) = (nRemaining * sizeof(RCL_CmdBleCs_StepResult_Internal));
    }

    return (events);
}


/*
 *  ======== Initialize the S2R engine ========
 */
static void RCL_Handler_BLE_CS_configureS2R(RCL_CmdBleCs *pCmd)
{
    LRF_setRclClockEnable(LRFDDBELL_CLKCTL_S2RRAM_M | LRFDDBELL_CLKCTL_S2R_M);

    /* Access the list of multibuffers */
    RCL_MultiBuffer *pS2rBuffer = RCL_MultiBuffer_head(&pCmd->s2rBuffers);

    /* Only set up S2R, if there is buffer on the list */
    if (pS2rBuffer)
    {
        /* Store 32bit words in S2R (offset 3072) memory; don't arm yet */
        HWREG_WRITE_LRF(LRFDS2R_BASE + LRFDS2R_O_START) = BLE_CS_S2R_MEMORY_OFFSET;
        HWREG_WRITE_LRF(LRFDS2R_BASE + LRFDS2R_O_STOP)  = HWREG_READ_LRF(LRFDS2R_BASE + LRFDS2R_O_START) + (RCL_BLE_CS_MAX_S2R_LEN >> pCmd->mode.phy);
        HWREG_WRITE_LRF(LRFDS2R_BASE + LRFDS2R_O_CFG)   = LRFDS2R_CFG_CTL_EN 
                                                        | LRFDS2R_CFG_SEL_FRONTEND 
                                                        | LRFDS2R_CFG_TRIGMODE_ONESHOT 
                                                        | LRFDS2R_CFG_LAST0_DIS;
    }
}

/*
 *  ======== Read the S2R memory ========
 */
RCL_Events RCL_Handler_BLE_CS_readS2RSamples(RCL_CmdBleCs *pCmd)
{
    RCL_Events events = {.value = 0};

    uint16_t s2rLength  = sizeof(S2RSample) * HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_S2ROUTWORDSIZE);
    uint16_t dataLength = sizeof(RCL_CmdBleCs_S2r) + s2rLength;

    /* Access the list of multibuffers */
    RCL_MultiBuffer *pS2rBuffer = RCL_Handler_BLE_CS_findBufferFitNumberOfBytes(&pCmd->s2rBuffers, dataLength);

    if (pS2rBuffer)
    {
        /* Decode the next free slot in the multibuffer */
        RCL_CmdBleCs_S2r *pS2rData = (RCL_CmdBleCs_S2r *) RCL_MultiBuffer_getNextWritableByte(pS2rBuffer);

        /* Store the step index */
        pS2rData->phy        = pCmd->mode.phy;
        pS2rData->idx        = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_S2ROUTIDX);
        pS2rData->channel    = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_S2ROUTCHIDX);
        pS2rData->payloadLen = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_S2ROUTPAYLOADLEN);
        /* 32 bit access */
        pS2rData->payload0   = HWREG_READ_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_S2ROUTPAYLOAD0L);
        pS2rData->payload1   = HWREG_READ_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_S2ROUTPAYLOAD1L);
        pS2rData->payload2   = HWREG_READ_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_S2ROUTPAYLOAD2L);
        pS2rData->payload3   = HWREG_READ_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_S2ROUTPAYLOAD3L);

        /* Number of valid samples to be copied out with 32bit operation
        Need to calculate with 0/32/64/96/128 bit @ 8MHz/4MHz front-end sampling */
        pS2rData->iqLength = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_S2ROUTWORDSIZE);

        /* Store the data, unwrap the loop for faster copying */
        uint32_t *src = (uint32_t *)S2R_RAM_BASE_ADDR;
        uint32_t *dst = (uint32_t *)&pS2rData->data;

        #ifdef NO_INLINE_ASM
            for(uint16_t i=0; i<(pS2rData->iqLength >> 3); i++)
            {
                *dst++ = *src++;
                *dst++ = *src++;
                *dst++ = *src++;
                *dst++ = *src++;
                *dst++ = *src++;
                *dst++ = *src++;
                *dst++ = *src++;
                *dst++ = *src++;
            }
        #else
            for(uint16_t i=0; i<(pS2rData->iqLength >> 2); i++)
            {
                __asm(
                "LDMIA %0!, {r4, r5, r6, r7} \n"
                "STMIA %1!, {r4, r5, r6, r7} \n"
                : "+r" (src), "+r" (dst) :
                : "r4", "r5", "r6", "r7");
            }
        #endif

        /* Flag the entry */
        RCL_MultiBuffer_commitBytes(pS2rBuffer, dataLength);
        pCmd->stats->nS2RDone++;

        /* Force close the buffer, even if there is more space left */
        pS2rBuffer->state = RCL_BufferStateFinished;

        /* Transfer the used buffers, should trigger a callback if any */
        events.swTriggered = (uint32_t) RCL_Handler_BLE_CS_transferFinishedBuffers(&pCmd->s2rBuffers, &pCmd->s2rBuffersDone);
    }

    return (events);
}

/*
 *  ======== Read the statistics from the PBE ========
 */
static void RCL_Handler_BLE_CS_readStatistics(RCL_CmdBleCs *pCmd)
{
    if (pCmd->stats) 
    {
        pCmd->stats->nStepsDone = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_NSTEPSDONE);
        pCmd->stats->lastRssi   = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_RSSILAST);
        pCmd->stats->lastFoff   = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_FOFFLAST);
        pCmd->stats->foffComp   = HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_FOFFCOMP);
    }
}

/*
 *  ======== Load the command and step descriptors into LRF REGISTERS/BUFRAM ========
 */
static void RCL_Handler_BLE_CS_preprocessCommand(RCL_CmdBleCs *pCmd)
{
    /* Force antenna switching time to zero for single antenna path per spec */
    if (pCmd->antennaConfig.select == 0)
    {
        pCmd->timing.tSw = 0;
    }

    /* Decode mapping of configuration to antennas */
    const RCL_AntennaConfig_t *antennaEntry = &antennaConfig[pCmd->antennaConfig.select];

    /* Decode the Phy specific settings */
    const RCL_PhyConfig_t *config = &phyConfigLut[pCmd->mode.phy];

    /* Clear output statistics */
    if (pCmd->stats)
    {
        memset((void *)pCmd->stats, 0, sizeof(RCL_CmdBleCs_Stats));

        pCmd->stats->lastRssi = LRF_RSSI_INVALID;
        pCmd->stats->numAntennaPath = antennaEntry->numPath;
    }

    /* Mode */
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_MODE) = ((pCmd->mode.role        << PBE_BLE_CS_RAM_MODE_ROLE_S)      & PBE_BLE_CS_RAM_MODE_ROLE_M) |
                                                                 ((pCmd->mode.phy         << PBE_BLE_CS_RAM_MODE_PHY_S)       & PBE_BLE_CS_RAM_MODE_PHY_M) |
                                                                 ((pCmd->mode.repeatSteps << PBE_BLE_CS_RAM_MODE_INFINIT_S)   & PBE_BLE_CS_RAM_MODE_INFINIT_M) |
                                                                 ((pCmd->mode.nSteps      << PBE_BLE_CS_RAM_MODE_NUM_STEPS_S) & PBE_BLE_CS_RAM_MODE_NUM_STEPS_M);

    /* Antenna */
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_ANTN)   = antennaEntry->numPath;
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_ANTMSK) = pCmd->antennaConfig.gpoMask;
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_ANT0)   = pCmd->antennaConfig.gpoVal[0];
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_ANT1)   = pCmd->antennaConfig.gpoVal[1];
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_ANT2)   = pCmd->antennaConfig.gpoVal[2];
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_ANT3)   = pCmd->antennaConfig.gpoVal[3];

    /* Timing */
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_TFCS)        = pCmd->timing.tFcs - (TPLT + config->tStartup); // Pilot tone + startup time is included into the TFCS budget
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_TFM)         = pCmd->timing.tFm;
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_TPM)         = pCmd->timing.tPm;
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_TIP1)        = pCmd->timing.tIp1;
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_TIP2)        = pCmd->timing.tIp2;
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_TSW)         = pCmd->timing.tSw;
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_TSWADJA)     = pCmd->timing.tSwAdjustA;
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_TSWADJB)     = pCmd->timing.tSwAdjustB;

    /* Timegrid adjustment shall be initialized with maximum unsigned value (ca. 536s @ 4MHz) */
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_TSTEPACCTHRH)= 0x7FFF;
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_TSTEPACCTHRL)= 0xFFFF;
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_TSTEPACCH)   = 0;
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_TSTEPACCL)   = 0;
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_TSTEPCOMP)   = 0;

    /* Initialize MOD.FOFF values. Usueful for sub-events without mode 0 steps */
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_FOFFSUM)     = 0;
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_FOFFNUM)     = 0;
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_RSSILAST)    = LRF_RSSI_INVALID;
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_RSSISUM0)    = 0;
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_RSSINUM0)    = 0;
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_NSTEPSDONE)  = 0;

    /* Apply override if configured */
    if (pCmd->frontend.foffOverrideEnable)
    {
        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_FOFFSUM) = pCmd->frontend.foffOverride;
        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_FOFFNUM) = (1 << 15) | 1; // [15]=Enable, [1]=NUM hardcoded to 1
    }

    /* Program frequency dependent config: hardcode on 2440MHz, to be updated on the fly */
    HWREG_WRITE_LRF(LRFDMDM32_BASE + LRFDMDM32_O_DEMFRAC1_DEMFRAC0) = 0x0D800000;     // P: Constant
    HWREG_WRITE_LRF(LRFDMDM32_BASE + LRFDMDM32_O_DEMFRAC3_DEMFRAC2) = 0x0E4C0000;     // Q: Being dynammically scaled by RFE per channel

    /* Shaper gain */
    HWREG_WRITE_LRF(LRFDRFE_BASE + LRFDRFE_O_MOD0) = 0x1824;

    /* Configure AGC with gain=15/7 or a static value=gain/gain */
    uint16_t rxGain = pCmd->frontend.rxGain;
    HWREG_WRITE_LRF(LRFDRFE_BASE + LRFDRFE_O_SPARE0) = (rxGain == 0)
                                                     ? (0x30F7)
                                                     : ((rxGain << 4) | rxGain);

    uint8_t lutIdx = RCL_CmdBleCs_Tpm_40us;
    if (pCmd->timing.tPm <= RCL_BLE_CS_US_TO_MCE_TIMER(20))
    {
        lutIdx = RCL_CmdBleCs_Tpm_20us;
    }
    if (pCmd->timing.tPm <= RCL_BLE_CS_US_TO_MCE_TIMER(10))
    {
        lutIdx = RCL_CmdBleCs_Tpm_10us;
    }

    /* MAFC gain */
    #ifdef DeviceFamily_CC27XX
        /* Workaround for IQ swap */
        HWREG_WRITE_LRF(LRFDMDM_BASE + LRFDMDM_O_DEMMISC2) = config->demmisc2 | LRFDMDM_DEMMISC2_PDIFIQCONJEN;
    #else
        HWREG_WRITE_LRF(LRFDMDM_BASE + LRFDMDM_O_DEMMISC2) = config->demmisc2;
    #endif

    /* Channel filter = 0.33 */
    HWREG_WRITE_LRF(LRFDMDM_BASE + LRFDMDM_O_DEMMISC1) = 0x0001;

    /* Fife IIR adaptation rate = 64 (provides good mode-0 frequency tolerance for both PHYs) */
    HWREG_WRITE_LRF(LRFDMDM_BASE + LRFDMDM_O_DEMFIFE0) = 0x0007;

    /* Use precalibration values or mode-0 estimates */
    if ((pCmd->precalTable) && (pCmd->precalTable->valid))
    {
        HWREG_WRITE_LRF(LRFDMDM_BASE + LRFDMDM_O_SPARE1) = (1<<8);
    }
    else
    {
        HWREG_WRITE_LRF(LRFDMDM_BASE + LRFDMDM_O_SPARE1) = 0;
    }

    /* Baudrate specific settings */
    HWREG_WRITE_LRF(LRFDMDM_BASE + LRFDMDM_O_SPARE0)                        = config->pctConfig[lutIdx].val;
    HWREG_WRITE_LRF(LRFDMDM_BASE + LRFDMDM_O_BAUD)                          = config->baud;
    HWREG_WRITE_LRF(LRFDMDM_BASE + LRFDMDM_O_MODSYMMAP0)                    = config->symmap;
    HWREG_WRITE_LRF(LRFDRFE_BASE + LRFDRFE_O_SPARE3)                        = config->magnConfig[lutIdx].val;
    HWREG_WRITE_LRF(LRFDRFE_BASE + LRFDRFE_O_RSSIOFFSET)                    = config->rssioffset;
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_DEMMISC3)          = config->demmisc3;
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_TPOSTPROCESSDIV1)  = config->tPostProcessDiv1;
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_TPOSTPROCESSDIV12) = config->tPostProcessDiv12;
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_TRXTIMEOUTI0)      = config->tRxTimeoutI0;
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_TRXTIMEOUTI3)      = config->tRxTimeoutI3;
    HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_TPILOTADJ)         = config->tPilotAdjust;

    /* Alias for dynamic parameters for calculations */
    uint16_t tIp1  = pCmd->timing.tIp1;
    uint16_t tIp2  = pCmd->timing.tIp2;
    uint16_t tFm   = pCmd->timing.tFm;
    uint16_t tPm   = pCmd->timing.tPm;
    uint16_t tFcs  = pCmd->timing.tFcs;
    uint16_t tSw   = pCmd->timing.tSw;
    uint16_t nPath = antennaEntry->numPath;

    /* Phy specific delays */
    uint16_t tStartup    = config->tStartup;
    uint16_t tPkt        = config->tPacket;
    uint16_t tCorr       = config->tCorr;
    uint16_t tDem        = config->tDem;
    uint16_t tTr         = config->tTr;
    uint16_t tFidc       = config->tFidc;
    uint16_t tTxModDelay = config->tTxModDelay;
    uint16_t tInfiniteRx = config->tInfiniteRx;

    /* Modulation + Demodulation delay for timestamp capturing */
    uint16_t tTimestampDelay1 = config->tTimestampDelay1;
    uint16_t tTimestampDelay3 = config->tTimestampDelay3;

    /* Calculate base terms of step duration for each mode.
       Later can be extended with optional payload per step before sending it over to the PBE. */
    tStepLut[RCL_CmdBleCs_StepMode_0] = (tFcs + ((tPkt + TRD) << 1) + TGD + tIp1 + tFm);
    tStepLut[RCL_CmdBleCs_StepMode_1] = (tFcs + ((tPkt + TPYL + TRD) << 1) + tIp1);
    tStepLut[RCL_CmdBleCs_StepMode_2] = (tFcs + ((((tPm + tSw) * (nPath + 1)) + TRD) << 1) + tIp2);
    tStepLut[RCL_CmdBleCs_StepMode_3] = (tFcs + ((tPkt + TPYL + TGD + ((tPm + tSw) * (nPath + 1)) + TRD) << 1) + tIp2);

    /* Adjustment of MCE timegrid */
    const RCL_Tadjust_t *tAdj = &config->tAdj[pCmd->mode.role];

    if (pCmd->mode.role == RCL_CmdBleCs_Role_Initiator)
    {
        /* Calculate base terms of interlude period. Later will scale with payload. */

        /* TX */
        tAdjALut[RCL_CmdBleCs_StepMode_0] = tAdj->mode0[0] + 0xFFFF;
        tAdjALut[RCL_CmdBleCs_StepMode_1] = tAdj->mode1[0] + 0xFFFF;
        tAdjALut[RCL_CmdBleCs_StepMode_2] = tAdj->mode2[0] + 0x0000; // No packet, variable used for pilot adjustment
        tAdjALut[RCL_CmdBleCs_StepMode_3] = tAdj->mode3[0] + 0xFFFF;

        /* RX */
        tAdjBLut[RCL_CmdBleCs_StepMode_0] = tAdj->mode0[1] + TRD + tIp1 - TPLT;
        tAdjBLut[RCL_CmdBleCs_StepMode_1] = tAdj->mode1[1] + TRD + tIp1 - TPLT;
        tAdjBLut[RCL_CmdBleCs_StepMode_2] = tAdj->mode2[1] + TRD + tIp2 + tSw + tFidc;
        tAdjBLut[RCL_CmdBleCs_StepMode_3] = tAdj->mode3[1] + TRD + tIp2 + tSw + tFidc;

        /* ToAD common term */
        tRttAdjustLut[RCL_CmdBleCs_StepMode_0] = 0; /* NA, no RTT defined */
        tRttAdjustLut[RCL_CmdBleCs_StepMode_1] = TPYL + TRD + tIp1 + tPkt + tTimestampDelay1;
        tRttAdjustLut[RCL_CmdBleCs_StepMode_2] = 0; /* NA, no RTT defined */
        tRttAdjustLut[RCL_CmdBleCs_StepMode_3] = TPYL + (TGD << 1) + (((tPm + tSw) * ((nPath << 1) + 1))) + TRD + tIp2 + tPkt + tTimestampDelay3;

        /* Initiator: timeout is hardcoded in the MCE in order to comply with the static timegrid.
           This parameter is therefor ignored.  */
        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_TRXTIMEOUTR013)   = 0;
        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_TRXWIDENINGR0)    = 0;
        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_TSTEPREMAININGR0) = 0;
    }
    else
    {
        /* RX */
        tAdjALut[RCL_CmdBleCs_StepMode_0] = tAdj->mode0[0] - tCorr + tTr + TRD + tIp1 - TPLT - tTxModDelay;
        tAdjALut[RCL_CmdBleCs_StepMode_1] = tAdj->mode1[0] - tCorr + tTr + TRD + tIp1 - TPLT - tTxModDelay;
        tAdjALut[RCL_CmdBleCs_StepMode_2] = tAdj->mode2[0] + tStartup + TPLT + tSw + tFidc;
        tAdjALut[RCL_CmdBleCs_StepMode_3] = tAdj->mode3[0] - tCorr + tTr + TGD + tSw + tFidc;

        /* TX */
        tAdjBLut[RCL_CmdBleCs_StepMode_0] = tAdj->mode0[1];
        tAdjBLut[RCL_CmdBleCs_StepMode_1] = tAdj->mode1[1];
        tAdjBLut[RCL_CmdBleCs_StepMode_2] = tAdj->mode2[1] - tFidc - tSw /* + TRD */ + tIp2 - TPLT; // Ramp-down delay is added by the topSM
        tAdjBLut[RCL_CmdBleCs_StepMode_3] = tAdj->mode3[1] - tFidc - tSw /* + TRD */ + tIp2 - TPLT - tTxModDelay;

        /* ToAD common term */
        tRttAdjustLut[RCL_CmdBleCs_StepMode_0] = 0; /* NA, no RTT defined */
        tRttAdjustLut[RCL_CmdBleCs_StepMode_1] = TPYL + TRD + tIp1 + tPkt - tTimestampDelay1;
        tRttAdjustLut[RCL_CmdBleCs_StepMode_2] = 0; /* NA, no RTT defined */
        tRttAdjustLut[RCL_CmdBleCs_StepMode_3] = TPYL + (TGD << 1) + (((tPm + tSw) * ((nPath << 1) + 1))) + TRD + tIp2 + tPkt - tTimestampDelay3;

        /* The miminum value is defined by the static timegrid. Different for each datarate and implemented by the MCE. */
        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_TRXTIMEOUTR013) = config->tRxTimeoutRn;

        /* Handle infinite/extended RX timeout implemented by PBE */
        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_TRXWIDENINGR0)
            = (pCmd->timing.tRxWideningR0 == 0xFFFF)
            ? (0xFFFF)
            : RCL_BLE_CS_MCE_TIMER_TO_PBE_TIMER(tFcs + (tPkt - tTr) + tDem + T3US + pCmd->timing.tRxWideningR0);

        HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_TSTEPREMAININGR0) =
          RCL_BLE_CS_MCE_TIMER_TO_PBE_TIMER(0 - tDem + tTr + TRD + tIp1 + tPkt + TGD + tFm + TRD - tInfiniteRx);
    }

    /* Adjustment of antenna control per mode per phy */
    const RCL_Tadjust_t *tAnt = &config->tAnt[pCmd->mode.role & 1];

    tAntALut[RCL_CmdBleCs_StepMode_0] = 0; /* NA - no antenna */
    tAntALut[RCL_CmdBleCs_StepMode_1] = 0; /* NA - no antenna */
    tAntALut[RCL_CmdBleCs_StepMode_2] = tAnt->mode2[0] + TPLT;
    tAntALut[RCL_CmdBleCs_StepMode_3] = tAnt->mode3[0] + TPLT + tPkt + TGD;

    tAntBLut[RCL_CmdBleCs_StepMode_0] = 0; /* NA - no antenna */
    tAntBLut[RCL_CmdBleCs_StepMode_1] = 0; /* NA - no antenna */
    tAntBLut[RCL_CmdBleCs_StepMode_2] = tAnt->mode2[1];
    tAntBLut[RCL_CmdBleCs_StepMode_3] = tAnt->mode3[1];

    /* Enforce modulator and demodulator clock. RTL bug with automatic control. */
    LRF_setRclClockEnable(LRFDDBELL_CLKCTL_DEM_M | LRFDDBELL_CLKCTL_MOD_M);
}

/*
 *  ======== Preprocess the step ========
 */
static void RCL_Handler_BLE_CS_preprocessStep(RCL_CmdBleCs *pCmd, RCL_CmdBleCs_Step *pStep, RCL_CmdBleCs_Step_Internal *pStepI)
{
    /* Decompress the HCI format into PBE internal format */
    pStepI->channelIdx     = pStep->channelIdx;
    pStepI->mode           = pStep->mode;
    pStepI->antennaPermIdx = pStep->antennaPermIdx;
    pStepI->toneExtension  = pStep->toneExtension;
    pStepI->payloadLen     = pStep->payloadLen;
    pStepI->aaTx           = pStep->aaTx;
    pStepI->aaRx           = pStep->aaRx;

    for (uint8_t i=0; i<RCL_BLE_CS_MAX_PAYLOAD_SIZE; i++)
    {
        pStepI->payloadTx[i] = pStep->payloadTx[i];
        pStepI->payloadRx[i] = pStep->payloadRx[i];
    }

    /* Disable restricted channels if filtering is turned on */
    if (pCmd->mode.chFilterEnable == true)
    {
        uint16_t channelIdx = pStepI->channelIdx;

        if (  channelIdx > BLE_CS_MAX_CHANNEL
           || channelIdx == 0  /* Advertisement frequency (channel 37)*/
           || channelIdx == 1
           || channelIdx == 23
           || channelIdx == 24 /* Advertisement frequency (channel 38)*/
           || channelIdx == 25
           || channelIdx == 77
           || channelIdx == 78 /* Advertisement frequency (channel 39)*/)
        {
            /* The user configured a channel outside the allowed domain or
               a restricted channel. Guard channels also covered!
               We still keep the timegrid but silence this step. */
            pStepI->channelIdx = BLE_CS_SILENT_CHANNEL;
        }
    }

    /* Decode the base term for the complete duration of the step */
    uint32_t tStep = tStepLut[pStepI->mode];
    uint16_t tAdjA = tAdjALut[pStepI->mode];
    uint16_t tAdjB = tAdjBLut[pStepI->mode];

    /* Scale with bit length and 1M/2M rate */
    uint16_t tPyl = (payloadLut[pStepI->payloadLen]) >> pCmd->mode.phy;

    /* Extend with timing of optional payload */
    if (pStepI->payloadLen)
    {
        /* Adjustment only on Reflector */
        uint16_t tAdj = (pCmd->mode.role == RCL_CmdBleCs_Role_Reflector)
                      ? (tPyl)
                      : (0);

        /* Payload is only allowed for certain modes. */
        if (pStepI->mode == RCL_CmdBleCs_StepMode_1 ||
            pStepI->mode == RCL_CmdBleCs_StepMode_3)
        {
            /* Multiplied by two for combined effect of TX and RX */
            tStep += (tPyl << 1);

            /* The duration from AA sync until the next activity scales with payload on reflector only */
            tAdjA += tAdj;
        }
        else
        {
            /* Enforce no payload for mode 0 & 2 */
            pStepI->payloadLen = 0;

            /* No adjustment needed */
            tPyl = 0;
        }
    }

    /* Configure the PBE with the scaled step duration */
    pStepI->tStep = (uint16_t) RCL_BLE_CS_MCE_TIMER_TO_PBE_TIMER(tStep);

    /* Configure the MCE with the scaled intermediate timegrid parameters */
    pStepI->tAdjustA = tAdjA;
    pStepI->tAdjustB = tAdjB;

    /* Antenna timing from beginning of step */
    pStepI->tAntennaA = tAntALut[pStepI->mode] + tPyl;
    pStepI->tAntennaB = tAntBLut[pStepI->mode];

    /* DC compensation */
    if ((pCmd->precalTable) && (pCmd->precalTable->valid))
    {
        pCmd->precalTable->callback(pCmd->precalTable, pStepI->channelIdx, (uint32_t *)&pStepI->dcComp[0], (uint32_t *)&pStepI->dcComp[1]);
    }
    else
    {   
        pStepI->dcComp[0].i = 0;
        pStepI->dcComp[0].q = 0;
        pStepI->dcComp[1].i = 0;
        pStepI->dcComp[1].q = 0;
    }

    /* Antenna calculations */
    pStepI->antennaSequence = 0;

    /* Decode mapping of configuration to antennas */
    const RCL_AntennaConfig_t *antennaEntry = &antennaConfig[pCmd->antennaConfig.select];

    /*  Avoid indexing out of range */
    if (pStepI->antennaPermIdx < antennaEntry->numPerm)
    {
        /* Find the proper permutation pattern based on generic config and random step related selection.
            The same table is used, but we index the entries differently */
        uint8_t apn = antennaPermutation[pStepI->antennaPermIdx * antennaEntry->increment].apn;

        /* We reuse the same permutation table for 1:1, 1:N, N:1 and 2:2,
            but only use the appropriate number of entries from each row */
        for(uint8_t k1=0; k1<antennaEntry->numPath; k1++)
        {
            uint8_t apm = antennaEntry->ap[pCmd->mode.role & 1].apn;

            /* Decode bitfields */
            uint8_t k2 = DECODE_ANTENNA(apn, k1);
            uint8_t k3 = DECODE_ANTENNA(apm, k2);

            /* Antenna sequence is stored as [7:6]=A4, [5:4]=A3, [3:2]=A2, [1:0]=A1.
                The PBE will decode it accordingly. */
            pStepI->antennaSequence |= ENCODE_ANTENNA(k3, k1);
        }
    }

    /* Look up the frequency offset actuation error (only used by mode 0) */
    pStepI->foffErr = (uint16_t) foffErrorLut[pStepI->channelIdx];
}

/*
 *  ======== Fetch the next available step result container in the list and return a pointer to it ========
 */
static RCL_CmdBleCs_StepResult_Internal* RCL_Handler_BLE_CS_fetchNextStepResult(RCL_CmdBleCs *pCmd)
{
    RCL_CmdBleCs_StepResult_Internal *pResult = NULL;

    if ((pCmd->stats->nResultsRead < pCmd->mode.nSteps) && pCmd->results)
    {
        pResult = &pCmd->results[pCmd->stats->nResultsRead];
    }

    return (pResult);
}

/*
 *  ======== RCL_Handler_BLE_CS_convertFreqOffset ========
 */
static int16_t RCL_Handler_BLE_CS_convertFreqOffset(int16_t foffMeasured)
{
    /* Intermediate arithmetics on 32bit
       freqOffset = foff * 100 * 1e6 / 2^23
                  = foff * (100 * 1e6 / 2^7) / 2^16 
                  = foff * 0xBEBC2 / 2^16 [0.01 ppm] */
    int32_t freqOffset = (int32_t)foffMeasured;
    freqOffset *= 0xBEBC2;
    freqOffset >>= 16;

    return (int16_t)(freqOffset);
}

/*
 *  ======== RCL_Handler_BLE_CS_convertRtt ========
 */
static int16_t RCL_Handler_BLE_CS_convertRtt(RCL_CmdBleCs *pCmd, uint8_t mode, int8_t channel, int16_t foff, uint8_t payloadLen, bool secondToneExtensionSlot,
                                             float toAD, uint16_t corrBefore, uint16_t corrPeak, uint16_t corrAfter)
{
    /* Raw RTT need to be compensated with:
       - Correlator before/after fractional approximation
       - Nominal tunr-around time T = TSY + TIP + TEXT + TPYL + ...
       - Time drift due to XTAL offset (initiator only)
       - CMIX (channel specific) and layout related errors */

    /* Conversion from 4M/8M baudrate to 48M clock tick */
    uint8_t baud2tick = (pCmd->mode.phy) ? (6) : (12);

    /* Quadratic interpolation with correlator values */
    float corr = (float)(baud2tick * (corrBefore - corrAfter))
               / (float)((corrAfter << 1) + (corrBefore << 1) - (corrPeak << 2));

    /* Compensation applies with different sign */
    toAD += (pCmd->mode.role == RCL_CmdBleCs_Role_Initiator) ? (+corr) : (-corr);

    /* Remove nominal turn-around time (adjust to the signal on the antenna) */
    toAD -= tRttAdjustLut[mode];

    /* Adjust with optional payload duration */
    toAD -= (payloadLut[payloadLen] >> pCmd->mode.phy);

    /* Adjust with optional tone-extension slot for mode-3 */
    if (secondToneExtensionSlot == true)
    {
         toAD -= (pCmd->timing.tPm + pCmd->timing.tSw);
    }

    /* Adjust initiator */
    if (pCmd->mode.role == RCL_CmdBleCs_Role_Initiator)
    {
        /* XTAL offset related drift */
        //toAD *= 100e6/(100e6 + foff); //TODO: This takes to much execution time
    }

    /* Channel specific delays */
    #define CHANNEL_MID (float)(40.0)
    #define CHANNEL_CAL (float)(0.0415)
    float adj = CHANNEL_CAL * (channel - CHANNEL_MID);
    toAD -= (pCmd->mode.role == RCL_CmdBleCs_Role_Initiator) ? (-adj) : (+adj);

    /* Convert to 0.5ns units as per HCI spec requires */
    toAD *= (float)41.6666;

    /* Round */
    toAD += (float)0.5;

    /* Return the adjusted timeticks */
    return ((int16_t) toAD);
}

/*
 *  ======== RCL_Handler_BLE_CS_rotateVector ========
 */
void RCL_Handler_BLE_CS_rotateVector(int16_t *pct_i, int16_t *pct_q, int16_t theta)
{
    /* Quickly return if nothing to do */
    if (theta != 0)
    {
        /* CORDIC implementation of rotating a vector with given angle
        *
        * theta = 16bit representation of the angle in [-pi = -32768, +pi = 32767] range to rotate the PCT with
        * pct_i = I component of PCT
        * pct_q = Q component of PCT
        * */
        #define PI_div2 (1 << (16-2))

        /* The LUT and normalization factor is generated by the following python expression:
        *
        * f = 1.0
        * for i in range(NBITS):
        *     x = np.arctan(1 / 2**i) / (np.pi/2) * (2**NBITS)
        *     atanLut += [ (np.floor)(x + 0.5) ]
        *
        *     f = (f * (2**(2*i) + 1)) / 2**(2*i)
        *
        * f = 1/np.sqrt(f) * (2**NBITS)
        * K = (np.floor) (f + 0.5)
        * */
        #define NBITS  (14)
        #define K14    (9949)
        const uint16_t atanLut[NBITS] = { 8192, 4836, 2555, 1297, 651, 326, 163, 81, 41, 20, 10, 5, 3, 1 };

        /* Swap coordinates when angle is between [-pi,-pi/2] or [pi/2,pi] */
        int32_t x = ((int32_t) *pct_i);
        int32_t y = ((int32_t) *pct_q);
        if (theta > PI_div2)
        {
            theta -= PI_div2;
            x = -((int32_t) *pct_q);
            y = +((int32_t) *pct_i);
        }
        else if (theta < (-PI_div2))
        {
            theta += PI_div2;
            x = +((int32_t) *pct_q);
            y = -((int32_t) *pct_i);
        }
        x *= K14;
        y *= K14;

        /* Initialize local variables */
        int32_t x1  = 0;
        int32_t y1  = 0;

        /* The direction follows the mathematical positive direction */
        int32_t phi = (int32_t)(-theta);

        /* Rotate iteratively */
        for (uint8_t i = 0; i < NBITS; i++)
        {
            if (phi < 0)
            {   /* Counter-clockwise */
                phi += atanLut[i];
                y1 = y + (x >> i);
                x1 = x - (y >> i);
            }
            else
            {   /* Clockwise */
                phi -= atanLut[i];
                y1 = y - (x >> i);
                x1 = x + (y >> i);
            }

            x = x1;
            y = y1;
        }

        /* Scale according to LUT normalization weight */
        *pct_i = (x >> NBITS);
        *pct_q = (y >> NBITS);
    }
}

/*
 *  ======== RCL_Handler_BLE_CS_convertPct ========
 */
static uint32_t RCL_Handler_BLE_CS_convertPct(int16_t pct_i, int16_t pct_q, uint8_t channelIdx)
{
    /* Calibrate via the t_picosec parameter */
    #define t_picosec       (uint64_t)(1000)
    #define t_picosec_      (uint64_t)(t_picosec * 3/2)
    #define t_const         (uint64_t)((t_picosec_ << 31) / 1e6)
    #define t_scaler        (15)
    #define CALC_ANGLE(ch)  (-(int16_t)((((uint64_t)ch) * t_const) >> t_scaler))

    /* Adjust the phase to the signal on the antenna (group delay and layout) */
    RCL_Handler_BLE_CS_rotateVector(&pct_i, &pct_q, CALC_ANGLE(channelIdx));

    /* Compress PCTs to 24bit */
    uint32_t pct = (((pct_q >> 1) & 0x0FFF) << 12)
                 | ( (pct_i >> 1) & 0x0FFF);

    return (pct);
}

/*
 *  ======== RCL_Handler_BLE_CS_convertPctQuality ========
 */
static uint8_t RCL_Handler_BLE_CS_convertPctQuality(uint16_t qMin, uint16_t qMax, uint16_t qAvg, bool toneExtensionSlot, bool toneExpected)
{
    /* Initialize with unavailable */
    uint8_t tnQ = RCL_CmdBleCs_ToneQuality_Unavailable;

    /* Avoid zero-division. Metric is unavailable. Also for Initiator mode-3. */
    if (qAvg != 0)
    {
        /* Calculate Q3 scale */
        uint8_t Q3 = 100 * (qMax - qMin)/qAvg;

        /* Classify based on thresholds */
        if      (Q3 < BLE_CS_TONE_QUALITY_GOOD_THR)   tnQ = RCL_CmdBleCs_ToneQuality_Good;
        else if (Q3 < BLE_CS_TONE_QUALITY_MEDIUM_THR) tnQ = RCL_CmdBleCs_ToneQuality_Medium;
        else                                          tnQ = RCL_CmdBleCs_ToneQuality_Low;

        /* Add additional flag for the tone extension slot */
        if (toneExtensionSlot)
        {
            /* Decode the appropriate flag */
            uint8_t toneExtensionFlag = (toneExpected)
                                      ? (RCL_CmdBleCs_ToneExtensionSlot_Enabled_ToneExpected)
                                      : (RCL_CmdBleCs_ToneExtensionSlot_Enabled_NoToneExpected);

            tnQ |= (toneExtensionFlag << 4);
        }
    }

    return (tnQ);
}

/*
 *  ======== RCL_Handler_BLE_CS_estimateStepResultLength ========
 */
static uint16_t RCL_Handler_BLE_CS_estimateStepResultLength(RCL_CmdBleCs *pCmd, RCL_CmdBleCs_StepResult_Internal* src)
{
    /* Information extracted from registers */
    uint8_t role           = pCmd->mode.role;
    uint8_t numAntennaPath = pCmd->stats->numAntennaPath + 1; // +1 = tone extension

    /* First two fields are mandatory */
    uint16_t length = 0;

    /* Dataformat varies based on the mode. Constants are known from the spec */
    switch (src->mode)
    {
        case (RCL_CmdBleCs_StepMode_0):
            /* Initiator also contains the measured frequency offset */
            length = (role == RCL_CmdBleCs_Role_Initiator) ? sizeof(RCL_CmdBleCs_ResultI0) : sizeof(RCL_CmdBleCs_ResultR0);
            break;
        case (RCL_CmdBleCs_StepMode_1):
            length = sizeof(RCL_CmdBleCs_ResultIR1);
            break;
        case (RCL_CmdBleCs_StepMode_2):
            length = sizeof(RCL_CmdBleCs_ResultIR2) + numAntennaPath * sizeof(RCL_CmdBleCs_Tone);
            break;
        case (RCL_CmdBleCs_StepMode_3):
            length = sizeof(RCL_CmdBleCs_ResultIR3) + numAntennaPath * sizeof(RCL_CmdBleCs_Tone);
            break;
    }

    return (length);
}

/*
 *  ======== RCL_Handler_BLE_CS_convertStepResult ========
 */
static uint16_t RCL_Handler_BLE_CS_convertStepResult(RCL_CmdBleCs* pCmd, uint8_t *dst, RCL_CmdBleCs_StepResult_Internal* src)
{
    #define NADM_NOT_SUPPORTED 0xFF
    #define PACKET_ANTENNA     1

    uint8_t numAntennaPath = pCmd->stats->numAntennaPath + 1; // +1 = tone extension

    /* Use register access to guarantee the latest-greatest value for the first burst */
    int16_t foff = RCL_Handler_BLE_CS_convertFreqOffset(HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_FOFFCOMP) << 2);

    /* Dataformat varies based on the mode */
    uint8_t mode          = src->mode;
    uint8_t channel       = src->channelIdx;
    uint8_t payloadLen    = src->payloadLen;
    uint8_t toneExtension = src->toneExtension;

    /* Mode independent fields */
    *dst++ = mode;
    *dst++ = channel;

    /* Remember the address of field 'datalength' and skip it for now, will be filled later */
    uint8_t *dataLength = dst++;

    if (mode == RCL_CmdBleCs_StepMode_0)
    {
        *dst++ = src->pktResult;   /* Packet_AA_Quality */
        *dst++ = src->pktRssi;     /* Packet_RSSI */
        *dst++ = PACKET_ANTENNA;   /* Packet_Antenna */

        if (pCmd->mode.role == RCL_CmdBleCs_Role_Initiator)
        {
            int16_t freqOffset = RCL_Handler_BLE_CS_convertFreqOffset(src->foffMeasured);
            *dst++ = INT16_LSB(freqOffset);
            *dst++ = INT16_MSB(freqOffset);
        }
    }
    else if (mode == RCL_CmdBleCs_StepMode_1)
    {
        *dst++ = src->pktResult;     /* Packet_AA_Quality */
        *dst++ = NADM_NOT_SUPPORTED; /* Packet_NADM */
        *dst++ = src->pktRssi;       /* Packet_RSSI */
        *dst++ = PACKET_ANTENNA;     /* Packet_Antenna */

        /* RTT calculation using correlator values */
        int16_t toAD = RCL_Handler_BLE_CS_convertRtt(pCmd,
                                                     RCL_CmdBleCs_StepMode_1,
                                                     channel,
                                                     foff,
                                                     payloadLen,
                                                     false, // secondToneExtensionSlot=NA, there are no tones in mode-1
                                                     src->rtt, src->corr[0], src->corr[1], src->corr[2]);
        *dst++ = INT16_LSB(toAD);
        *dst++ = INT16_MSB(toAD);
    }
    else if (mode == RCL_CmdBleCs_StepMode_2)
    {
        *dst++ = src->antennaPermIdx;
        for (uint8_t j = 0; j < numAntennaPath; j++)
        {
            /* Compress PCT to 24bits */
            int16_t i = src->pct[j].i;
            int16_t q = src->pct[j].q;

            uint32_t pct = RCL_Handler_BLE_CS_convertPct(i, q, channel);
            *dst++       = (uint8_t)((pct) & 0xFF);
            *dst++       = (uint8_t)((pct >> 8) & 0xFF);
            *dst++       = (uint8_t)((pct >> 16) & 0xFF);

            /* Calculate PCT quality */
            bool toneExtensionSlot = (bool)(j == (numAntennaPath - 1));
            bool toneExpected = (bool)((pCmd->mode.role == RCL_CmdBleCs_Role_Reflector)
                              ? (toneExtension & BLE_CS_TONE_EXTENSION_INITIATOR_TX)
                              : (toneExtension & BLE_CS_TONE_EXTENSION_REFLECTOR_TX));

            uint16_t min = src->magn[j].magnMin;
            uint16_t max = src->magn[j].magnMax;
            uint16_t avg = src->magn[j].magnAvg;
            *dst++ = RCL_Handler_BLE_CS_convertPctQuality(min, max, avg, toneExtensionSlot, toneExpected);
        }
    }
    else if (mode == RCL_CmdBleCs_StepMode_3)
    {
        /* Packet related data */
        *dst++ = src->pktResult;                     /* Packet_AA_Quality */
        *dst++ = NADM_NOT_SUPPORTED;                 /* Packet_NADM */
        *dst++ = src->pktRssi;                       /* Packet_RSSI */
        *dst++ = PACKET_ANTENNA;                     /* Packet_Antenna */

        /* RTT calculation using correlator values */
        int16_t toAD = RCL_Handler_BLE_CS_convertRtt(pCmd,
                                                     RCL_CmdBleCs_StepMode_3,
                                                     channel,
                                                     foff,
                                                     payloadLen,
                                                     (bool)(toneExtension & 2),
                                                     src->rtt, src->corr[0], src->corr[1], src->corr[2]);
        *dst++ = INT16_LSB(toAD);
        *dst++ = INT16_MSB(toAD);

        /* Tone related data */
        *dst++ = src->antennaPermIdx;
        for (uint8_t j = 0; j < numAntennaPath; j++)
        {
            /* Compress PCT to 24bits */
            int16_t i = src->pct[j].i;
            int16_t q = src->pct[j].q;

            uint32_t pct = RCL_Handler_BLE_CS_convertPct(i, q, channel);
            *dst++       = (uint8_t)((pct) & 0xFF);
            *dst++       = (uint8_t)((pct >> 8) & 0xFF);
            *dst++       = (uint8_t)((pct >> 16) & 0xFF);

            /* Calculate PCT quality */
            bool toneExtensionSlot = (bool)(j == (numAntennaPath - 1));

            /* Mode-3 may or may not have the R->I tone extension present */
            bool toneExpected = (bool)((pCmd->mode.role == RCL_CmdBleCs_Role_Reflector)
                              ? (toneExtension & BLE_CS_TONE_EXTENSION_INITIATOR_TX)
                              : (toneExtension & BLE_CS_TONE_EXTENSION_REFLECTOR_TX));

            uint16_t min = src->magn[j].magnMin;
            uint16_t max = src->magn[j].magnMax;
            uint16_t avg = src->magn[j].magnAvg;
            *dst++ = RCL_Handler_BLE_CS_convertPctQuality(min, max, avg, toneExtensionSlot, toneExpected);
        }
    }

    /* Fill the Step_Data_Length based on difference of addresses */
    *dataLength = (dst - dataLength - 1);

    /* Return the number of bytes written (+3 = mode&channel&dataLength) */
    return (*dataLength + 3);
}

/*
 *  ======== RCL_Handler_BLE_CS_findPbeErrorEndStatus ========
 */
static RCL_CommandStatus RCL_Handler_BLE_CS_findPbeErrorEndStatus(uint16_t pbeEndStatus)
{
    RCL_CommandStatus status;
    switch (pbeEndStatus)
    {
    case PBE_COMMON_RAM_ENDCAUSE_STAT_ERR_RXF:
        status = RCL_CommandStatus_Error_RxFifo;
        break;
    case PBE_COMMON_RAM_ENDCAUSE_STAT_ERR_TXF:
        status = RCL_CommandStatus_Error_TxFifo;
        break;
    case PBE_COMMON_RAM_ENDCAUSE_STAT_ERR_SYNTH:
        status = RCL_CommandStatus_Error_Synth;
        break;
    case PBE_COMMON_RAM_ENDCAUSE_STAT_ERR_STOP:
        status = RCL_Scheduler_findStopStatus(RCL_StopType_Hard);
        break;
    case PBE_COMMON_RAM_ENDCAUSE_STAT_ERR_PAR:
        status = RCL_CommandStatus_Error_Param;
        break;
    case PBE_COMMON_RAM_ENDCAUSE_STAT_ERR_BADOP:
        status = RCL_CommandStatus_Error_UnknownOp;
        break;
    default:
        Log_printf(RclCore, Log_ERROR, "Unexpected error 0x%04X from PBE", pbeEndStatus);
        status = RCL_CommandStatus_Error;
        break;
    }
    return (status);
}

/*
 *  ======== RCL_Handler_BLE_CS ========
 */
RCL_Events RCL_Handler_BLE_CS(RCL_Command *cmd, LRF_Events lrfEvents, RCL_Events rclEventsIn)
{
    RCL_CmdBleCs *pCmd = (RCL_CmdBleCs *) cmd;
    RCL_Events rclEvents = {.value = 0};

    if (rclEventsIn.setup != 0)
    {
        uint32_t earliestStartTime;

        /* Start by enabling refsys */
        earliestStartTime = LRF_enableSynthRefsys();

        /* Check if valid PLLDIV0 synth setting is used. */
        /* BLE CS currently supports only either 3 => FREF0=16MHz or 12 => FREF0=4MHz */
        uint32_t plldiv0 = (HWREG_READ_LRF(LRFDRFE_BASE + LRFDRFE_O_PRE0) & LRFDRFE_PRE0_PLLDIV0_M) >> LRFDRFE_PRE0_PLLDIV0_S;
        if ((plldiv0 != 3U) && (plldiv0 != 12U))
        {
            /* Override to use PLLDIV0=12, gives FREF0=4MHz */
            Log_printf(RclCore, Log_WARNING, "Unsupported RFE_PRE0_PLLDIV0 synth setting detected. Will override to use 12 (FREF=4MHz)");
            HWREG_WRITE_LRF(LRFDRFE_BASE + LRFDRFE_O_PRE0) = ((12U << LRFDRFE_PRE0_PLLDIV0_S) & LRFDRFE_PRE0_PLLDIV0_M) |
                                                             ((12U << LRFDRFE_PRE0_PLLDIV1_S) & LRFDRFE_PRE0_PLLDIV1_M);
        }

        /* Mark as active */
        cmd->status = RCL_CommandStatus_Active;

        /* Default end status */
        bleCsHandlerState.common.endStatus = RCL_CommandStatus_Finished;

        /* Enable radio */
        LRF_enable();

        RCL_CommandStatus startTimeStatus = RCL_Scheduler_setStartStopTimeEarliestStart(cmd, earliestStartTime);
        if (startTimeStatus >= RCL_CommandStatus_Finished)
        {
            cmd->status = startTimeStatus;
            rclEvents.lastCmdDone = 1;
        }
        else
        {
            /* Enable interrupts (LRF_EventMdmsoft0 => "S2R samples available") */
            HWREG_WRITE_LRF(LRFDDBELL_BASE + LRFDDBELL_O_IMASK0) =
                            HWREG_READ_LRF(LRFDDBELL_BASE + LRFDDBELL_O_IMASK0)
                            | LRF_EventOpDone.value
                            | LRF_EventOpError.value
                            | LRF_EventMdmsoft0.value
                            | LRF_EventRxfifo.value;

            /* Initialize BLE CS specific registers and FIFO */
            RCL_Handler_BLE_CS_preprocessCommand(pCmd);

            /* Configure TX power*/
            if (LRF_programTxPower(pCmd->frontend.txPower) != TxPowerResult_Ok)
            {
                cmd->status = RCL_CommandStatus_Error_Param;
                rclEvents.lastCmdDone = 1;
            }
            else
            {
                /* Configure the BUFRAM fifo size and interrupts */
                RCL_Handler_BLE_CS_configureTxRxFifo(pCmd);

                /* Configure S2R size and mode */
                RCL_Handler_BLE_CS_configureS2R(pCmd);

                /* Fill the first batch of step descriptors into the BUFRAM TX fifo */
                RCL_Handler_BLE_CS_preFillTxBuffer(pCmd);

                /* Post command */
                LRF_waitForTopsmReady();
                HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_COMMON_RAM_O_MSGBOX) = 0;
                HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_API) = PBE_BLE_CS_REGDEF_API_OP_BLE_CS;

                /* Forward fill more steps */
                RCL_Handler_BLE_CS_preFillTxBuffer(pCmd);
            }
        }
    }

    if (cmd->status == RCL_CommandStatus_Active)
    {
        /* Read the statistics */
        RCL_Handler_BLE_CS_readStatistics(pCmd);

        if (rclEventsIn.timerStart != 0)
        {
            rclEvents.cmdStarted = 1;
        }

        if (lrfEvents.opDone != 0 || lrfEvents.opError != 0)
        {
            /* Drain the rx fifo of the final batch of results. Force close the buffer. */
            rclEvents.value |= RCL_Handler_BLE_CS_readWriteBuffer(pCmd, true).value;
        }
        else
        {
            if (lrfEvents.rxfifo != 0)
            {
                /* Read the available results, and issue event if multibuffer is exhausted */
                rclEvents.value |= RCL_Handler_BLE_CS_readWriteBuffer(pCmd, false).value;
            }
        }

        if (lrfEvents.mdmsoft0 != 0)
        {
            /* Read S2R samples upon MCE event */
            rclEvents.value |= RCL_Handler_BLE_CS_readS2RSamples(pCmd).value;
        }

        if (lrfEvents.opDone != 0)
        {
            cmd->status = bleCsHandlerState.common.endStatus;
            rclEvents.lastCmdDone = 1;
        }
        else if (lrfEvents.opError != 0)
        {
            RCL_CommandStatus endStatus = bleCsHandlerState.common.endStatus;
            if (endStatus == RCL_CommandStatus_Finished)
            {
                cmd->status = RCL_Handler_BLE_CS_findPbeErrorEndStatus(HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_COMMON_RAM_O_ENDCAUSE));
            }
            else
            {
                cmd->status = endStatus;
            }
            rclEvents.lastCmdDone = 1;
        }
        else
        {
            /* Other events need to be handled unconditionally */
        }
    }

    if (rclEvents.lastCmdDone != 0)
    {
        LRF_disable();
        LRF_disableSynthRefsys();
    }
    return (rclEvents);
}



/*
 *  ======== RCL_Handler_BLE_CS_Precal ========
 */
RCL_Events RCL_Handler_BLE_CS_Precal(RCL_Command *cmd, LRF_Events lrfEvents, RCL_Events rclEventsIn)
{
    RCL_CmdBleCs_Precal *pCmd = (RCL_CmdBleCs_Precal *) cmd;
    RCL_Events rclEvents = {.value = 0};

    if (rclEventsIn.setup != 0)
    {
        uint32_t earliestStartTime;

        /* Start by enabling refsys */
        earliestStartTime = LRF_enableSynthRefsys();

        /* Mark as active */
        cmd->status = RCL_CommandStatus_Active;

        /* Default end status */
        bleCsHandlerState.common.endStatus = RCL_CommandStatus_Finished;

        /* Enable radio */
        LRF_enable();

        RCL_CommandStatus startTimeStatus = RCL_Scheduler_setStartStopTimeEarliestStart(cmd, earliestStartTime);
        if (startTimeStatus >= RCL_CommandStatus_Finished)
        {
            cmd->status = startTimeStatus;
            rclEvents.lastCmdDone = 1;
        }
        else
        {
            /* Enable interrupts */
            HWREG_WRITE_LRF(LRFDDBELL_BASE + LRFDDBELL_O_IMASK0)
                            = HWREG_READ_LRF(LRFDDBELL_BASE + LRFDDBELL_O_IMASK0)
                            | LRF_EventOpDone.value
                            | LRF_EventOpError.value;

            RCL_Handler_BLE_CS_configureTxRxFifo(NULL);

            /* Number of channels to calibrate on */
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_BLE_CS_RAM_O_MODE) = ((pCmd->table->numEntries << PBE_BLE_CS_RAM_MODE_NUM_STEPS_S) & PBE_BLE_CS_RAM_MODE_NUM_STEPS_M);
            HWREG_WRITE_LRF(LRFDRFE_BASE + LRFDRFE_O_SPARE0) = pCmd->table->rxGain;

            for (uint8_t j=0; j<pCmd->table->numEntries; j++)
            {
                /* 32bit aperture */
                HWREG_WRITE_LRF(LRFDTXF_BASE + LRFDTXF_O_TXD) = pCmd->table->entries[j].channel;
            }

            /* Post command */
            LRF_waitForTopsmReady();
            HWREGH_WRITE_LRF(LRFD_BUFRAM_BASE + PBE_COMMON_RAM_O_MSGBOX) = 0;
            HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_API) = PBE_BLE_CS_REGDEF_API_OP_PRECAL;
        }
    }

    if (cmd->status == RCL_CommandStatus_Active)
    {
        if (lrfEvents.opDone != 0)
        {
            for (uint8_t j=0; j<pCmd->table->numEntries; j++)
            {
                /* uint32_t per read via the FIFO */
                uint32_t data = HWREG_READ_LRF(LRFDRXF_BASE + LRFDRXF_O_RXD);
                pCmd->table->entries[j].hdc.i = ((data >> 0 ) & 0xFFFF);
                pCmd->table->entries[j].hdc.q = ((data >> 16) & 0xFFFF);

                data = HWREG_READ_LRF(LRFDRXF_BASE + LRFDRXF_O_RXD);
                pCmd->table->entries[j].ldc.i = ((data >> 0 ) & 0xFFFF);
                pCmd->table->entries[j].ldc.q = ((data >> 16) & 0xFFFF);
            }

            /* Validate the table */
            pCmd->table->valid = 1;

            cmd->status = bleCsHandlerState.common.endStatus;
            rclEvents.lastCmdDone = 1;
        }
        else if (lrfEvents.opError != 0)
        {
            /* Invalidate the table */
            pCmd->table->valid = 0;

            RCL_CommandStatus endStatus = bleCsHandlerState.common.endStatus;
            if (endStatus == RCL_CommandStatus_Finished)
            {
                cmd->status = RCL_Handler_BLE_CS_findPbeErrorEndStatus(HWREGH_READ_LRF(LRFD_BUFRAM_BASE + PBE_COMMON_RAM_O_ENDCAUSE));
            }
            else
            {
                cmd->status = endStatus;
            }
            rclEvents.lastCmdDone = 1;
        }
        else
        {
           /* Other events need to be handled unconditionally */
        }
    }

    if (rclEvents.lastCmdDone != 0)
    {
        LRF_disable();
        LRF_disableSynthRefsys();
    }
    return (rclEvents);
}

/*
 *  ======== RCL_Handler_BLE_CS_PrecalDefaultCallback ========
 */
void RCL_Handler_BLE_CS_PrecalDefaultCallback(RCL_CmdBleCs_PrecalTable *table, uint8_t channel, uint32_t *hdc, uint32_t *ldc)    
{
    *hdc = 0;
    *ldc = 0;

    if (channel <= BLE_CS_MAX_CHANNEL)
    {
        /* Default channel blocks : 10-30-50-70 MHz */
        #define BLE_CS_PRECAL_BIN_WIDTH 20

        uint8_t k = channel / BLE_CS_PRECAL_BIN_WIDTH;

        if (k < table->numEntries)
        {
            /* Populate the DC measured with high gain */
            uint32_t i = table->entries[k].hdc.i;
            uint32_t q = table->entries[k].hdc.q;
            *hdc = (q << 16 | i);

            i = table->entries[k].ldc.i;
            q = table->entries[k].ldc.q;
            *ldc = (q << 16 | i);
        }
    }
}
