/*
 * Copyright (c) 2022-2026, Texas Instruments Incorporated
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

#ifndef ti_drivers_rcl_commands_ble_cs__include
#define ti_drivers_rcl_commands_ble_cs__include

#include <ti/drivers/rcl/RCL_Command.h>
#include <ti/drivers/rcl/RCL_Buffer.h>
#include <ti/drivers/rcl/handlers/ble_cs.h>

#include <ti/drivers/utils/List.h>

/* Forward declaration of types */
typedef struct RCL_CMD_BLE_CS_t                           RCL_CmdBleCs;
typedef struct RCL_CMD_BLE_CS_STEP_INTERNAL_t             RCL_CmdBleCs_Step_Internal;
typedef struct RCL_CMD_BLE_CS_STEP_RESULT_INTERNAL_t      RCL_CmdBleCs_StepResult_Internal;
typedef struct RCL_CMD_BLE_CS_STEP_t                      RCL_CmdBleCs_Step;
typedef struct RCL_CMD_BLE_CS_SUBEVENT_RESULTS_t          RCL_CmdBleCs_SubeventResults;
typedef struct RCL_CMD_BLE_CS_SUBEVENT_RESULTS_CONTINUE_t RCL_CmdBleCs_SubeventResultsContinue;
typedef struct RCL_CMD_BLE_CS_S2R_t                       RCL_CmdBleCs_S2r;
typedef struct RCL_CMD_BLE_CS_STATS_t                     RCL_CmdBleCs_Stats;
typedef struct RCL_CMD_BLE_CS_IQ_SAMPLE_t                 RCL_CmdBleCs_IQSample;
typedef struct RCL_CMD_BLE_CS_DC_SAMPLE_t                 RCL_CmdBleCs_DCSample;
typedef struct RCL_CMD_BLE_CS_PRECAL_t                    RCL_CmdBleCs_Precal;
typedef struct RCL_CMD_BLE_CS_PRECAL_TABLE_t              RCL_CmdBleCs_PrecalTable;
typedef struct RCL_CMD_BLE_CS_PRECAL_ENTRY_t              RCL_CmdBleCs_PrecalEntry;

typedef struct RCL_CMD_BLE_CS_PCT_COMP_TABLE_t            RCL_CmdBleCs_PctCompTable;
typedef struct RCL_CMD_BLE_CS_PCT_COMP_ENTRY_t            RCL_CmdBleCs_PctCompEntry;

typedef struct RCL_CMD_BLE_CS_STEP_RESULTS_TONE_t         RCL_CmdBleCs_Tone;
typedef struct RCL_CMD_BLE_CS_STEP_RESULTS_t              RCL_CmdBleCs_Result;
typedef struct RCL_CMD_BLE_CS_STEP_RESULTS_I0_t           RCL_CmdBleCs_ResultI0;
typedef struct RCL_CMD_BLE_CS_STEP_RESULTS_R0_t           RCL_CmdBleCs_ResultR0;
typedef struct RCL_CMD_BLE_CS_STEP_RESULTS_IR1_t          RCL_CmdBleCs_ResultIR1;
typedef struct RCL_CMD_BLE_CS_STEP_RESULTS_IR2_t          RCL_CmdBleCs_ResultIR2;
typedef struct RCL_CMD_BLE_CS_STEP_RESULTS_IR3_t          RCL_CmdBleCs_ResultIR3;

typedef enum   RCL_CMD_BLE_CS_Phy_e                       RCL_CmdBleCs_Phy;
typedef enum   RCL_CMD_BLE_CS_Role_e                      RCL_CmdBleCs_Role;
typedef enum   RCL_CMD_BLE_CS_StepMode_e                  RCL_CmdBleCs_StepMode;
typedef enum   RCL_CMD_BLE_CS_PacketResult_e              RCL_CmdBleCs_PacketResult;
typedef enum   RCL_CMD_BLE_CS_Tfcs_e                      RCL_CmdBleCs_Tfcs;
typedef enum   RCL_CMD_BLE_CS_Tpm_e                       RCL_CmdBleCs_Tpm;
typedef enum   RCL_CMD_BLE_CS_Tip_e                       RCL_CmdBleCs_Tip;
typedef enum   RCL_CMD_BLE_CS_Tsw_e                       RCL_CmdBleCs_Tsw;
typedef enum   RCL_CMD_BLE_CS_AntennaConfig_e             RCL_CmdBleCs_AntennaConfig;
typedef enum   RCL_CMD_BLE_CS_Payload_e                   RCL_CmdBleCs_Payload;
typedef enum   RCL_CMD_BLE_CS_RxGain_e                    RCL_CmdBleCs_RxGain;
typedef enum   RCL_CMD_BLE_CS_ToneQuality_e               RCL_CmdBleCs_ToneQuality;
typedef enum   RCL_CMD_BLE_CS_ToneExtensionSlot_e         RCL_CmdBleCs_ToneExtensionSlot;

typedef enum   RCL_CMD_BLE_CS_ReportFormat_e              RCL_CmdBleCs_ReportFormat;
typedef enum   RCL_CMD_BLE_CS_PacketAntenna_e             RCL_CmdBleCs_PacketAntenna;
typedef enum   RCL_CMD_BLE_CS_Nadm_e                      RCL_CmdBleCs_Nadm;

/* Command IDs for generic commands */
#define RCL_CMDID_BLE_CS                        0x1101U
#define RCL_CMDID_BLE_CS_PRECAL                 0x1102U

/* Helper macros to convert between time units */
#define RCL_BLE_CS_US_TO_MCE_TIMER(x)           ((x)*48U)
#define RCL_BLE_CS_US_TO_PBE_TIMER(x)           ((x)*4U)
#define RCL_BLE_CS_MCE_TIMER_TO_US(x)           ((x)/48U)
#define RCL_BLE_CS_PBE_TIMER_TO_US(x)           ((x)/12U)
#define RCL_BLE_CS_MCE_TIMER_TO_PBE_TIMER(x)    (uint16_t) ((x)/4U)
#define RCL_BLE_CS_MCE_TIMER_TO_PREFREF(x)      ((x)/3U)
#define RCL_BLE_CS_DELAY_PS_TO_LUT(x)           (((x)+16U)/32U)

/* Helper macros for constants */
#define RCL_BLE_CS_MAX_NUM_ANT                  4U
#define RCL_BLE_CS_MAX_NUM_ANT_PATH             5U
#define RCL_BLE_CS_MAX_PAYLOAD_SIZE             4U
#define RCL_BLE_CS_NUM_CORR                     3U
#define RCL_BLE_CS_NUM_STIM                     2U
#define RCL_BLE_CS_MAX_S2R_LEN                  1024U
#define RCL_BLE_CS_NUM_RX_GAIN_LEVEL            2U
#define RCL_BLE_CS_STEP_RX_GAIN_DB              3U
#define RCL_BLE_CS_NUM_PRECAL_CHANNELS          8U

/**
 *  @brief BLE Channel Sounding IQ Sample
 *
 *  Container to store complex vectors
 */
struct RCL_CMD_BLE_CS_IQ_SAMPLE_t {
    int16_t i;   /*!< Sample I-branch */
    int16_t q;   /*!< Sample Q-branch */
};

/**
 *  @brief BLE Channel Sounding
 *
 *  Command to execute a BLE Channel Sounding event
 */
struct RCL_CMD_BLE_CS_t {
    RCL_Command common;

    union {
        struct {
            uint16_t role:2;                     /*!< Role of the device @ref RCL_CmdBleCs_Role */
            uint16_t phy:2;                      /*!< Phy used for packet exchange @ref RCL_CmdBleCs_Phy */
            uint16_t repeatSteps:1;              /*!< Enable continuous repetition of step list */
            uint16_t reportFormat:1;             /*!< Select a vendor specific report format instead of the default HCI LE CS subevent result */
            uint16_t inlinePhase:1;              /*!< Enable the reflector to apply inline phase adjustment */
            uint16_t reserved0:1;
            uint16_t nSteps:8;                   /*!< Total number of steps within the BLE CS Sub-Event */
        };
        uint16_t val;
    } mode;

    struct {
        uint8_t select;                          /*!< Antenna path configuration by index @ref RCL_CmdBleCs_AntennaConfig */
        uint8_t gpoMask;                         /*!< IO mask defining the actively used pins for antenna control */
        uint8_t gpoVal[RCL_BLE_CS_MAX_NUM_ANT];  /*!< IO value to be used to activate the corresponding antenna ([0]:ANT0, [1]:ANT1, [2]:ANT3, [3]:ANT3) */
    } antennaConfig;

    struct {
        uint16_t tFcs;                           /*!< Config of time of Frequency Change period @ref RCL_CmdBleCs_Tfcs */
        uint16_t tFm;                            /*!< Config of time of Frequency Measurement period */
        uint16_t tPm;                            /*!< Config of time of Phase Measurement Duration @ref RCL_CmdBleCs_Tpm */
        uint16_t tIp1;                           /*!< Config of time of Interlude Period 1 @ref RCL_CmdBleCs_Tip */
        uint16_t tIp2;                           /*!< Config of time of Interlude Period 2 @ref RCL_CmdBleCs_Tip */
        uint16_t tRxWideningR0;                  /*!< Config of additional time of RX timeout of mode-0 steps on reflector. */
        uint16_t tSw;                            /*!< Config of time of Antenna Switching duration @ref RCL_CmdBleCs_Tsw */
        uint16_t tSwAdjustA;                     /*!< Time adjustment of first set of antenna switching within a step (Pkt-Tn / ...) */
        uint16_t tSwAdjustB;                     /*!< Time adjustment of second set of antenna switching within a step (... / Tn-Pkt) */
    } timing;

    RCL_Command_TxPower txPower;                  /*!< Transmit power in dBm format */

    uint8_t  rxGainPolicy:2;                      /*!< 0: Automatic RX gain selection, 1: Use cached value from previous subevent, 2: Manual override */
    uint8_t  foffPolicy:2;                        /*!< 0: Automatic frequency offset selection, 1: Use cached value from previous subevent, 2: Manual override */
    uint16_t rxGainVal;                           /*!< Manual RX gain control override value in SPARE register format*/
    int16_t  foffVal;                             /*!< Manual frequency offset override value in [4xFOFF = 4x (FRF/2^21)] format. */

    RCL_CmdBleCs_PrecalTable *precalTable;        /*!< Pointer to a table contains DC values from precalibration */
    RCL_CmdBleCs_StepResult_Internal *results;    /*!< Pointer to result list */
    RCL_CmdBleCs_Stats *stats;                    /*!< Pointer to statistics structure */
    List_List           stepBuffers;              /*!< Linked list of steps to be executed */
    List_List           stepBuffersDone;          /*!< Linked list of steps have been executed */
    List_List           resultBuffers;            /*!< Linked list of empty result buffers */
    List_List           resultBuffersDone;        /*!< Linked list of result buffers containing data */
    List_List           s2rBuffers;               /*!< Linked list of empty s2r containers */
    List_List           s2rBuffersDone;           /*!< Linked list of s2r containers with data */
};

/* Default configuration of command */
#define RCL_CmdBleCs_Default()                          \
{                                                       \
    .common = RCL_Command_Default(RCL_CMDID_BLE_CS,     \
                                  RCL_Handler_BLE_CS),  \
}
#define RCL_CmdBleCs_DefaultRuntime() (RCL_CmdBleCs) RCL_CmdBleCs_Default()

/**
 *  @brief BLE Channel Sounding Step
 *
 *  Descriptor to configure a single step within the BLE Channel Sounding Event
 */
struct RCL_CMD_BLE_CS_STEP_INTERNAL_t {
    uint8_t  channelIdx;                             /*!< Integer index of channel information (0: 2402MHz) */
    uint8_t  reserved0;
    uint8_t  mode;                                   /*!< Step mode @ref RCL_CmdBleCs_StepMode */
    uint8_t  reserved1;
    uint8_t  toneExtension;                          /*!< Configuration of tone extension */
    uint8_t  reserved2;
    uint8_t  payloadLen;                             /*!< Length of payload in units of 32bit words @ref RCL_CmdBleCs_Payload */
    uint8_t  reserved3;
    int16_t  foffErr;                                /*!< Used for frequency offset compensation */
    int16_t  tAdjustA;                               /*!< Used for timegrid adjustment */
    int16_t  tAdjustB;                               /*!< Used for timegrid adjustment */
    uint16_t tPllRx;                                 /*!< Used for PLL adjustment */    
    RCL_CmdBleCs_IQSample dcComp[RCL_BLE_CS_NUM_RX_GAIN_LEVEL]; /*!< Used for DC compensation with precalibrated values */
    uint32_t payloadTx[RCL_BLE_CS_MAX_PAYLOAD_SIZE]; /*!< Payload to transmit containing random bit sequence (TX) */
    uint32_t payloadRx[RCL_BLE_CS_MAX_PAYLOAD_SIZE]; /*!< Expected payload to receive containing random bit sequence (RX) */
    uint32_t aaTx;                                   /*!< Access Address to be transmitted */
    uint32_t aaRx;                                   /*!< Access Address to be received */
    uint8_t  antennaPermIdx;                         /*!< Index of entry to be used from the antenna permutation table @ref RCL_CmdBleCs_AntennaConfig */
    uint8_t  antennaPacket;                          /*!< Index of physical antenna to be used for all packet exchanges @ref RCL_CMD_BLE_CS_PacketAntenna_e */
    uint16_t antennaSequence;                        /*!< Decoded antenna control sequence based on permutation table */
    uint16_t tStep;                                  /*!< The total duration of step dynamically calculated */
    int16_t  tAntennaA;                              /*!< Antenna timing adjustment */
    int16_t  tAntennaB;                              /*!< Antenna timing adjustment */
    uint16_t reserved4;
};

/**
 *  @brief BLE Channel Sounding QQ data
 *
 *  Container to store RSSI data for postprocess of the quality of tone
 */
typedef struct {
    uint16_t magnMin;     /*!< Minimum of signal magnitude during TPM */
    uint16_t magnMax;     /*!< Maximum of signal magnitude during TPM */
    uint16_t magnAvg;     /*!< Average of signal magnitude during TPM */
    uint16_t magnAvgdB;   /*!< Average of signal magnitude during TPM in dB */
} MagnData;

/**
 *  @brief BLE Channel Sounding Step Result
 *
 *  Container to store the results of a single step within the BLE Channel Sounding Event
 */
struct RCL_CMD_BLE_CS_STEP_RESULT_INTERNAL_t {
    uint8_t  channelIdx;                                     /*!< Integer index of channel information (0: 2402MHz) */
    uint8_t  reserved0;
    uint8_t  mode;                                          /*!< Step mode @ref RCL_CmdBleCs_StepMode */
    uint8_t  reserved1;
    uint8_t  toneExtension;                                 /*!< Configuration of tone extension */
    uint8_t  reserved2;
    uint8_t  payloadLen;                                    /*!< Length of payload in units of 32bit words @ref RCL_CmdBleCs_Payload */
    uint8_t  reserved3;
    uint16_t reserved4;
    int16_t  foffMeasured;                                  /*!< Frequency offset between devices (only set on Initiator Mode 0) */
    uint8_t  pktResult;                                     /*!< Result of packet reception @ref RCL_CmdBleCs_PacketResult */
    uint8_t  reserved5;
    uint8_t  gain;                                          /*!< LNA gain used (Low/High)*/
    int8_t   pktRssi;                                       /*!< Receiver Signal Strength Indicator [dBm] captured during packet reception */
    uint16_t rtt;                                           /*!< RTT timestamp */
    uint16_t corr[RCL_BLE_CS_NUM_CORR];                     /*!< Correlator before-peak-after values for fractional time estimation */
    RCL_CmdBleCs_IQSample dc;                               /*!< DC offset measured on packet */
    RCL_CmdBleCs_IQSample pct[RCL_BLE_CS_MAX_NUM_ANT_PATH]; /*!< Phase Correction Terms per antenna path (incl. extension) */
    uint32_t payload[RCL_BLE_CS_MAX_PAYLOAD_SIZE];          /*!< Payload containing random bit sequence (RX) */
    MagnData magn[RCL_BLE_CS_MAX_NUM_ANT_PATH];             /*!< Received magnitude data of tone per antenna path for quality estimation (incl. extension) */

    /* Echoed by PBE */
    uint8_t  antennaPermIdx;                                /*!< Index of entry to be used from the antenna permutation table @ref RCL_CmdBleCs_AntennaConfig */
    uint8_t  antennaPacket;                                 /*!< Index of physical antenna to be used for all packet exchanges @ref RCL_CMD_BLE_CS_PacketAntenna_e */
    uint16_t reserved6;
};

/**
 *  @brief BLE Channel Sounding S2R Sample type definition
 *
 *  One S2R sample can be interpreted multiple ways, depending of the signal source
 */
typedef union {
    uint32_t word;                 /*!< Sample format for copying data */
    uint8_t  byte[4];              /*!< Sample format of the Decoding Stage */
    RCL_CmdBleCs_IQSample iq;      /*!< Sample format of the Front End Stage */
} S2RSample;

/**
 *  @brief BLE Channel Sounding S2R IQ Data
 *
 *  Container to store raw S2R samples of a BLE Channel Sounding Step
 */
struct RCL_CMD_BLE_CS_S2R_t {
    uint8_t   idx;                 /*!< The index of entry in the step list which the data belongs to */
    uint8_t   phy;                 /*!< Phy the samples captured on */
    uint8_t   channel;             /*!< Frequency channel */
    uint8_t   payloadLen;          /*!< Payload length in bits */
    uint32_t  payload0;            /*!< Payload bits [00:31] */
    uint32_t  payload1;            /*!< Payload bits [32:63] */
    uint32_t  payload2;            /*!< Payload bits [64:95] */
    uint32_t  payload3;            /*!< Payload bits [96:127] */
    uint16_t  iqLength;            /*!< Number of valid iq samples in data[] */
    uint16_t  reserved;
    S2RSample data[];              /*!< Raw samples captured */
};

/**
 *  @brief BLE Channel Sounding Statistics
 *
 *  Container to store the statistical outputs of the BLE Channel Sounding Event
 */
struct RCL_CMD_BLE_CS_STATS_t {
    uint8_t  nStepsWritten;        /*!< Number of steps sent to the PBE through the FIFO */
    uint8_t  nResultsRead;         /*!< Number of results read from the PBE through the FIFO */
    uint8_t  nStepsDone;           /*!< Number of steps have been executed by the PBE */
    uint8_t  nRxOk;                /*!< Number of steps where pktResult == OK, filled by the CM0 */
    uint8_t  nRxNok;               /*!< Number of steps where pktResult != OK, filled by the CM0 */
    uint8_t  nS2RDone;             /*!< Number of Samples-To-Ram containers filled by the CM0 */
    uint8_t  nMode0;               /*!< Number of mode-0 steps in the subevent */
    uint8_t  nMode0Ok;             /*!< Number of sucessfull mode-0 steps */
    uint8_t  reserved0;
    int8_t   lastRssi;             /*!< Last valid RSSI received by the PBE */
    int16_t  lastFoff;             /*!< Last valid frequency offset received by the PBE */
    uint16_t rxGain;               /*!< RX gain used for main mode steps */
    int16_t  foffComp;             /*!< Frequency offset compensation value */
    uint8_t  numAntennaPath;       /*!< Number of true antenna paths (1...4) */
    uint8_t  reserved1;
};

/**
 *  @brief Enumerator of phy types
 *
 *  Describes the phy packets shall be transmitted
 */
enum RCL_CMD_BLE_CS_Phy_e {
    RCL_CmdBleCs_Phy_1M,    /*!< (M) 1Mbps BT=0.5 */
    RCL_CmdBleCs_Phy_2M,    /*!< (O) 2Mbps BT=0.5 */
    RCL_CmdBleCs_Phy_2M2BT, /*!< (O) 2Mbps BT=2.0 */
    RCL_CmdBleCs_Phy_Length
};

/**
 *  @brief Enumerator of role types
 *
 *  Describes the role of the device during a BLE channel sounding event
 */
enum RCL_CMD_BLE_CS_Role_e {
    RCL_CmdBleCs_Role_Initiator, /*!< (C.1) TX-RX */
    RCL_CmdBleCs_Role_Reflector, /*!< (C.2) RX-TX */
    RCL_CmdBleCs_Role_Length
};

/**
 *  @brief Enumerator of step types
 *
 *  Describes the available modes of a BLE CS step
 */
enum RCL_CMD_BLE_CS_StepMode_e {
    RCL_CmdBleCs_StepMode_0,       /*!< (M) Pkt-Pkt-Tn */
    RCL_CmdBleCs_StepMode_1,       /*!< (M) Pkt-Pkt */
    RCL_CmdBleCs_StepMode_2,       /*!< (M) Tn-Tn */
    RCL_CmdBleCs_StepMode_3,       /*!< (O) Pkt-Tn-Tn-Pkt */
    RCL_CmdBleCs_StepMode_Length
};

/**
 *  @brief Enumerator of packet status options
 *
 *  Describes the available packet status words
 */
enum RCL_CMD_BLE_CS_PacketResult_e {
    RCL_CmdBleCs_PacketResult_Ok        =  0,   /*!< The packet reception was successful */
    RCL_CmdBleCs_PacketResult_BitError  =  1,   /*!< The packet was received with one or more bit errors */
    RCL_CmdBleCs_PacketResult_Lost      =  2,   /*!< The packet reception was terminated by timeout */
    RCL_CmdBleCs_PacketResult_Length
};

/**
 *  @brief Enumerator of tFcs duration options
 *
 *  Describes the available durations for frequency change
 */
enum RCL_CMD_BLE_CS_Tfcs_e {
    RCL_CmdBleCs_Tfcs_80us,     /*!< (C.1) */
    RCL_CmdBleCs_Tfcs_100us,
    RCL_CmdBleCs_Tfcs_120us,
    RCL_CmdBleCs_Tfcs_150us,    /*!< (M) */
    RCL_CmdBleCs_Tfcs_Length,
};

/**
 *  @brief Enumerator of tPm duration options
 *
 *  Describes the available durations for phase measurement
 */
enum RCL_CMD_BLE_CS_Tpm_e {
    RCL_CmdBleCs_Tpm_10us,
    RCL_CmdBleCs_Tpm_20us,
    RCL_CmdBleCs_Tpm_40us,      /*!< (M) */
    RCL_CmdBleCs_Tpm_Length,
};

/**
 *  @brief Enumerator of tIp duration
 *
 *  Describes the available durations for interlude period
 */
enum RCL_CMD_BLE_CS_Tip_e {
    RCL_CmdBleCs_Tip_40us,      /*!< (C.1) */
    RCL_CmdBleCs_Tip_50us,
    RCL_CmdBleCs_Tip_60us,
    RCL_CmdBleCs_Tip_80us,      /*!< (C.1) */
    RCL_CmdBleCs_Tip_145us,     /*!< (M) */
    RCL_CmdBleCs_Tip_Length,
};

/**
 *  @brief Enumerator of antenna switch duration
 *
 *  Describes the available durations for antenna switching transient
 */
enum RCL_CMD_BLE_CS_Tsw_e {
    RCL_CmdBleCs_Tsw_0us,       /*!< (M) for 1x1 */
    RCL_CmdBleCs_Tsw_1us,
    RCL_CmdBleCs_Tsw_2us,
    RCL_CmdBleCs_Tsw_4us,
    RCL_CmdBleCs_Tsw_10us,      /*!< (M) */
    RCL_CmdBleCs_Tsw_Length
};

/**
 *  @brief Enumerator of antenna configuration
 *
 *  Describes the available values for configuration of
 *  antenna control for PCT measurement.
 */
enum RCL_CMD_BLE_CS_AntennaConfig_e {
    RCL_CmdBleCs_AntennaConfig_1x1,     /*!< (M) */
    RCL_CmdBleCs_AntennaConfig_2x1,
    RCL_CmdBleCs_AntennaConfig_3x1,
    RCL_CmdBleCs_AntennaConfig_4x1,
    RCL_CmdBleCs_AntennaConfig_1x2,
    RCL_CmdBleCs_AntennaConfig_1x3,
    RCL_CmdBleCs_AntennaConfig_1x4,
    RCL_CmdBleCs_AntennaConfig_2x2,
    RCL_CmdBleCs_AntennaConfig_Length,
};

/**
 *  @brief Enumerator of payload length
 *
 *  Describes the available payload lengths
 */
enum RCL_CMD_BLE_CS_Payload_e {
    RCL_CmdBleCs_Payload_None,
    RCL_CmdBleCs_Payload_32bit,
    RCL_CmdBleCs_Payload_64bit,
    RCL_CmdBleCs_Payload_96bit,
    RCL_CmdBleCs_Payload_128bit,
    RCL_CmdBleCs_Payload_Length
};

/**
 *  @brief Enumerator of policies
 *
 *  Describes the available policy rules
 */
enum RCL_CMD_BLE_CS_Policy_e {
    RCL_CmdBleCs_Policy_Auto   = 0,
    RCL_CmdBleCs_Policy_Cache  = 1,
    RCL_CmdBleCs_Policy_Manual = 2,
};

/**
 *  @brief Enumerator of tone quality
 *
 *  Describes the classification of tone quality
 */
enum RCL_CMD_BLE_CS_ToneQuality_e {
    RCL_CmdBleCs_ToneQuality_High,
    RCL_CmdBleCs_ToneQuality_Medium,
    RCL_CmdBleCs_ToneQuality_Low,
    RCL_CmdBleCs_ToneQuality_Unavailable,
    RCL_CmdBleCs_ToneQuality_Length
};

/**
 *  @brief Enumerator of tone extension slot
 *
 *  Describes the classification of tone extension slot
 */
enum RCL_CMD_BLE_CS_ToneExtensionSlot_e {
    RCL_CmdBleCs_ToneExtensionSlot_Disabled,
    RCL_CmdBleCs_ToneExtensionSlot_Enabled_NoToneExpected,
    RCL_CmdBleCs_ToneExtensionSlot_Enabled_ToneExpected,
    RCL_CmdBleCs_ToneExtensionSlot_Length
};

/**
 *  @brief Enumerator of report format
 *
 *  Selects the format of step results
 */
enum RCL_CMD_BLE_CS_ReportFormat_e {
    RCL_CmdBleCs_ReportFormat_HCI = 0,
    RCL_CmdBleCs_ReportFormat_Custom = 1
};

/*****************************************************
    DC precalibration
*****************************************************/

/**
 *  @brief Callback function for DC precalibration feature
 *
 *  Describes the method that can select the right compensation value from the available precalibration table.
 */
typedef void (*RCL_CmdBleCs_PrecalCallback)(RCL_CmdBleCs_PrecalTable *table, uint8_t channel, RCL_CmdBleCs_IQSample *pHigh, RCL_CmdBleCs_IQSample *pLow);

/**
 *  @brief BLE Channel Sounding DC Sample
 *
 *  Container to store DC information
 */
struct RCL_CMD_BLE_CS_DC_SAMPLE_t {
    int16_t  i;             /*!< DC I-branch */
    int16_t  q;             /*!< DC Q-branch */
    int8_t   phaseStart;    /*!< Cordic at start of integration */
    int8_t   phaseStop;     /*!< Cordic at stop of integration */
    uint16_t magnMin;       /*!< Minimum value of signal magnitude during integration */
    uint16_t magnMax;       /*!< Maximum value of signal magnitude during integration */
    uint16_t magnAvg;       /*!< Average value of signal magnitude during integration */
};

/**
 *  @brief DC precalibration entry
 *
 *  Data structure to store a single DC precalibration entry.
 */
struct RCL_CMD_BLE_CS_PRECAL_ENTRY_t {
    uint8_t channel;
    uint8_t lowValid  : 1;
    uint8_t highValid : 1;
    RCL_CmdBleCs_DCSample high;
    RCL_CmdBleCs_DCSample low;
};

/**
 *  @brief DC precalibration table
 *
 *  Data structure to store and use the DC precalibration table.
 */
struct RCL_CMD_BLE_CS_PRECAL_TABLE_t {
    RCL_CmdBleCs_PrecalCallback callback;
    uint32_t timestamp;
    int16_t  temperature;
    uint8_t  highThreshold;
    uint8_t  lowThreshold;
    uint8_t  chSpacing;
    uint8_t  numEntries : 7;
    uint8_t  valid      : 1;
    RCL_CmdBleCs_PrecalEntry entries[];
};

/* Default callback implemented in the driver */
void RCL_Handler_BLE_CS_PrecalDefaultCallback(RCL_CmdBleCs_PrecalTable *table, uint8_t channel, RCL_CmdBleCs_IQSample *pHigh, RCL_CmdBleCs_IQSample *pLow);

/* Default configuration of DC precalibration */
#define RCL_CmdBleCs_PrecalTable_Default()                     \
{                                                              \
    .callback      = RCL_Handler_BLE_CS_PrecalDefaultCallback, \
    .timestamp     = 0,                                        \
    .temperature   = 0,                                        \
    .highThreshold = 50,                                       \
    .lowThreshold  = 10,                                       \
    .chSpacing     = 10,                                       \
    .numEntries    = 8,                                        \
    .valid         = 0,                                        \
    .entries       = {{.channel =  5},                         \
                      {.channel = 15},                         \
                      {.channel = 25},                         \
                      {.channel = 35},                         \
                      {.channel = 45},                         \
                      {.channel = 55},                         \
                      {.channel = 65},                         \
                      {.channel = 75}},                        \
}

/**
 *  @brief DC precalibration command
 *
 *  Command to run precalibration for a list of channels.
 */
struct RCL_CMD_BLE_CS_PRECAL_t {
    RCL_Command               common;
    RCL_CmdBleCs_PrecalTable *table;
};

/* Default configuration of DC precalibration command */
#define RCL_CmdBleCs_Precal_Default(pTable)                    \
{                                                              \
    .common = RCL_Command_Default(RCL_CMDID_BLE_CS_PRECAL,     \
                                  RCL_Handler_BLE_CS_Precal),  \
    .table  = pTable                                           \
}
#define RCL_CmdBleCs_Precal_DefaultRuntime(pTable) (RCL_CmdBleCs_Precal) RCL_CmdBleCs_Precal_Default(pTable)

/*****************************************************
    PCT compensation for antenna/front-end delay
*****************************************************/

/**
 *  @brief Channel entry for PCT compensation for antenna/front-end delay
 *
 *  Data structure for PCT compensation for antenna delay (phase) and magnitude.
 */
struct RCL_CMD_BLE_CS_PCT_COMP_ENTRY_t {
    uint8_t phaseDelay;                 /*!< Phase delay to subtract, in multiple of 32 picoseconds (i.e. max compensation is 255*32=8.16ns)*/
    uint8_t magnCoeff;                  /*!< Linear magnitude compensation coefficient of I/Q of PCT, k = magnCoeff/128 */
};

/**
 *  @brief PCT compensation table for antenna/front-end delay
 *
 *  Data describing the magnitude/phase compensation to adjust PCT due to antenna/fronte-end.
 */
struct RCL_CMD_BLE_CS_PCT_COMP_TABLE_t {
    uint8_t firstChannelIdx;            /*!< Integer channel index (0: 2402MHz) for first entry */
    uint8_t chSpacing          : 7;     /*!< Channel spacing between entries in the table, assuming uniform spacing */
    uint8_t enPhaseComp        : 1;     /*!< Enable phase compensation */
    uint8_t enMagnComp         : 1;     /*!< Enable magnitude compensation */
    uint8_t numEntries         : 7;     /*!< Number of channel entries per antenna */
    RCL_CmdBleCs_PctCompEntry entries[];
};


/* Adjust RCL_BLE_CS_PHASE_DELAY_PS for linear PCT phase compensation due to antenna/front-end design,
 * or adjust RCL_CmdBleCs_PctCompTable bleCsPctCompTable, using a calibrated instrument */
#ifndef RCL_BLE_CS_PHASE_DELAY_PS
#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX)
    /* Example: LP-EM-CC2745R10-Q1 Launchpad development kit, SMA port */
    #define RCL_BLE_CS_PHASE_DELAY_PS  (1100UL)
#else
    /* Example: LP-EM-CC2340R5 Launchpad development kit, SMA port */
    #define RCL_BLE_CS_PHASE_DELAY_PS  (1500UL)
#endif
#endif

/* Default PCT compensation table: Only phase comp. Channels: 2402, 2402+n*8, ..., 2402+(11-1)*8 = 2482MHz */
#define RCL_CmdBleCs_PctCompTable_Default()                                                     \
{                                                                                               \
    .firstChannelIdx = 0,                                                                       \
    .chSpacing       = 8,                                                                       \
    .enPhaseComp     = 1,                                                                       \
    .enMagnComp      = 0,                                                                       \
    .numEntries      = 11,                                                                      \
    .entries         = {{.phaseDelay = RCL_BLE_CS_DELAY_PS_TO_LUT(RCL_BLE_CS_PHASE_DELAY_PS)},  \
                        {.phaseDelay = RCL_BLE_CS_DELAY_PS_TO_LUT(RCL_BLE_CS_PHASE_DELAY_PS)},  \
                        {.phaseDelay = RCL_BLE_CS_DELAY_PS_TO_LUT(RCL_BLE_CS_PHASE_DELAY_PS)},  \
                        {.phaseDelay = RCL_BLE_CS_DELAY_PS_TO_LUT(RCL_BLE_CS_PHASE_DELAY_PS)},  \
                        {.phaseDelay = RCL_BLE_CS_DELAY_PS_TO_LUT(RCL_BLE_CS_PHASE_DELAY_PS)},  \
                        {.phaseDelay = RCL_BLE_CS_DELAY_PS_TO_LUT(RCL_BLE_CS_PHASE_DELAY_PS)},  \
                        {.phaseDelay = RCL_BLE_CS_DELAY_PS_TO_LUT(RCL_BLE_CS_PHASE_DELAY_PS)},  \
                        {.phaseDelay = RCL_BLE_CS_DELAY_PS_TO_LUT(RCL_BLE_CS_PHASE_DELAY_PS)},  \
                        {.phaseDelay = RCL_BLE_CS_DELAY_PS_TO_LUT(RCL_BLE_CS_PHASE_DELAY_PS)},  \
                        {.phaseDelay = RCL_BLE_CS_DELAY_PS_TO_LUT(RCL_BLE_CS_PHASE_DELAY_PS)},  \
                        {.phaseDelay = RCL_BLE_CS_DELAY_PS_TO_LUT(RCL_BLE_CS_PHASE_DELAY_PS)}}, \
}


/*****************************************************
    HCI interface
*****************************************************/

/* Special values for categorical parameters */
enum RCL_CMD_BLE_CS_PacketAntenna_e {
    RCL_CmdBleCs_PacketAntenna_1 = 1, /*!< Default choice */
    RCL_CmdBleCs_PacketAntenna_2 = 2,
    RCL_CmdBleCs_PacketAntenna_3 = 3,
    RCL_CmdBleCs_PacketAntenna_4 = 4,
};

enum RCL_CMD_BLE_CS_Nadm_e {
    RCL_CmdBleCs_Nadm_ExtremelyUnlikely,
    RCL_CmdBleCs_Nadm_VeryUnlikely,
    RCL_CmdBleCs_Nadm_Unlikely,
    RCL_CmdBleCs_Nadm_Possible,
    RCL_CmdBleCs_Nadm_Likely,
    RCL_CmdBleCs_Nadm_VeryLikely,
    RCL_CmdBleCs_Nadm_ExtremelyLikely,
    RCL_CmdBleCs_Nadm_Unknown = 0xFF /*!< Default value for RTT types that do not have a random or sounding sequence. */
};

/* Special values for linear parameters */
#define RCL_CMD_BLE_CS_FREQCOMP_NA  0xC000
#define RCL_CMD_BLE_CS_TOAD_NA      (int16_t) 0x8000
#define RCL_CMD_BLE_CS_RSSI_NA      0x7F

/* Opcodes */
#define RCL_CMD_BLE_CS_SUBEVENT_RESULTS_OPCODE           0x31
#define RCL_CMD_BLE_CS_SUBEVENT_RESULTS_CONTINUE_OPCODE  0x32

/**
 *  @brief Container format for a single step in the subevent
 *
 *  Compressed format used within a multibuffer
 */
struct RCL_CMD_BLE_CS_STEP_t {
    uint32_t channelIdx : 7;                         /*!< Integer index of channel information (0: 2402MHz) */
    uint32_t mode : 2;                               /*!< Step mode @ref RCL_CmdBleCs_StepMode */
    uint32_t antennaPacket: 3;                       /*!< Index of physical antenna for the packet exchange @ref RCL_CMD_BLE_CS_PacketAntenna_e */
    uint32_t antennaPermIdx : 5;                     /*!< Index of entry to be used from the antenna permutation table @ref RCL_CmdBleCs_AntennaConfig */
    uint32_t toneExtension : 2;                      /*!< Enable tone extension, [0]=first tone (transmitted by initiator), [1]=second tone (transmitted by reflector) */
    uint32_t payloadLen : 3;                         /*!< Length of payload in units of 32bit words @ref RCL_CmdBleCs_Payload */
    uint32_t reserved : 10;
    uint32_t aaTx;                                   /*!< Access Address to be transmitted */
    uint32_t aaRx;                                   /*!< Access Address to be received */
    uint32_t payloadTx[RCL_BLE_CS_MAX_PAYLOAD_SIZE]; /*!< Payload to transmit containing random bit sequence (TX) */
    uint32_t payloadRx[RCL_BLE_CS_MAX_PAYLOAD_SIZE]; /*!< Expected payload to receive containing random bit sequence (RX) */
};

/**
 *  @brief Container format for a batch of step results in the subevent (first segment)
 *
 *  The data[] field contains the results in mode specific format (size varies with step-mode)
 */
struct RCL_CMD_BLE_CS_SUBEVENT_RESULTS_t {
    uint8_t  subeventCode;
    uint16_t connectionHandle;
    uint8_t  configID;
    uint16_t startAclConnectionEvent;
    uint16_t procedureCounter;
    int16_t  frequencyCompensation;
    int8_t   referencePowerLevel;
    uint8_t  procedureDoneStatus;
    uint8_t  subeventDoneStatus;
    uint8_t  abortReason;
    uint8_t  numAntennaPath;
    uint8_t  numStepsReported;
    uint8_t  data[];
} __attribute__ ((packed));

/**
 *  @brief Container format for a batch of step results in the subevent (second+ segment)
 *
 *  The data[] field contains the results in mode specific format (size varies with step-mode)
 */
struct RCL_CMD_BLE_CS_SUBEVENT_RESULTS_CONTINUE_t {
    uint8_t  subeventCode;
    uint16_t connectionHandle;
    uint8_t  configID;
    uint8_t  procedureDoneStatus;
    uint8_t  subeventDoneStatus;
    uint8_t  abortReason;
    uint8_t  numAntennaPath;
    uint8_t  numStepsReported;
    uint8_t  data[];
} __attribute__ ((packed));

/**
 *  @brief Container format for tones
 *
 */
struct RCL_CMD_BLE_CS_STEP_RESULTS_TONE_t {
    uint32_t i       : 12;
    uint32_t q       : 12;
    uint32_t quality : 8;
};

/**
 *  @brief Container format for common section of step results
 *
 */
struct RCL_CMD_BLE_CS_STEP_RESULTS_t {
    /* Common */
    uint8_t mode;
    uint8_t channel;
    uint8_t dataLength;
    uint8_t data[];
} __attribute__((packed));

/**
 *  @brief Container format for mode-0 step results
 *
 */
struct RCL_CMD_BLE_CS_STEP_RESULTS_I0_t {
    /* Common */
    uint8_t mode;
    uint8_t channel;
    uint8_t dataLength;
    /* Packet */
    uint8_t packetAAQuality;
    int8_t  packetRssi;
    uint8_t packetAntenna;
    /* Frequency */
    int16_t measuredFreqOffset;
};

/**
 *  @brief Container format for mode-0 step results
 *
 */
struct RCL_CMD_BLE_CS_STEP_RESULTS_R0_t {
    /* Common */
    uint8_t mode;
    uint8_t channel;
    uint8_t dataLength;
    /* Packet */
    uint8_t packetAAQuality;
    int8_t  packetRssi;
    uint8_t packetAntenna;
};

/**
 *  @brief Container format for mode-1 step results
 *
 */
struct RCL_CMD_BLE_CS_STEP_RESULTS_IR1_t {
    /* Common */
    uint8_t mode;
    uint8_t channel;
    uint8_t dataLength;
    /* Packet */
    uint8_t packetAAQuality;
    uint8_t nadm;
    int8_t  packetRssi;
    int16_t packetToF;
    uint8_t packetAntenna;
};

/**
 *  @brief Container format for mode-2 step results
 *
 */
struct RCL_CMD_BLE_CS_STEP_RESULTS_IR2_t {
    /* Common */
    uint8_t mode;
    uint8_t channel;
    uint8_t dataLength;
    /* Tones */
    uint8_t antennaPermutationIndex;
    RCL_CmdBleCs_Tone tones[];
};

/**
 *  @brief Container format for mode-3 step results
 *
 */
struct RCL_CMD_BLE_CS_STEP_RESULTS_IR3_t {
    /* Common */
    uint8_t mode;
    uint8_t channel;
    uint8_t dataLength;
    /* Packet */
    uint8_t packetAAQuality;
    uint8_t nadm;
    int8_t  packetRssi;
    int16_t packetToF;
    uint8_t packetAntenna;
    /* Tones */
    uint8_t antennaPermutationIndex;
    RCL_CmdBleCs_Tone tones[];
};

#endif /* ti_drivers_rcl_commands_ble_cs__include */
