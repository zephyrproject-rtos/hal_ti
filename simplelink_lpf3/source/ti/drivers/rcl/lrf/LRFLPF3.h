/*
 * Copyright (c) 2021-2026, Texas Instruments Incorporated
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

#ifndef ti_drivers_rcl_lrf_LRFLPF3__include
#define ti_drivers_rcl_lrf_LRFLPF3__include

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <ti/devices/DeviceFamily.h>
#include DeviceFamily_constructPath(inc/hw_memmap.h)
#include DeviceFamily_constructPath(inc/hw_lrfdpbe.h)
#include DeviceFamily_constructPath(inc/hw_lrfddbell.h)
#include DeviceFamily_constructPath(inc/pbe_generic_regdef_regs.h)
#include <ti/drivers/Power.h>
#include <ti/drivers/rcl/RCL_Types.h>
#include <ti/drivers/rcl/hal/RCL_Hal.h>

/** @brief Type for tx power configuration.
 *
 * Register value to be written to registers, prior to temperature compensation
 */
#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX)
typedef union
{
    struct {
        uint16_t ibBoost: 2;
        uint16_t ib: 6;
        uint16_t gain: 3;
        uint16_t mode: 2;
        uint16_t rtrimTxCompCtl: 1;
        uint16_t pa20dBmEsdCtl: 1;
        uint16_t noIfampRfLdoBypass: 1;
    };
    uint16_t rawValue;
} LRF_TxPowerTable_Value;
#else
typedef union
{
    struct {
        uint16_t reserved: 5;
        uint16_t ib: 6;
        uint16_t gain: 3;
        uint16_t mode: 1;
        uint16_t noIfampRfLdoBypass: 1;
    };
    uint16_t rawValue;
} LRF_TxPowerTable_Value;
#endif
#define LRF_TxPowerTable_INVALID_VALUE ((LRF_TxPowerTable_Value){.rawValue = 0xFFFF})              /*!< Value indicating that no valid tx power could be found in the table. */

typedef uint8_t LRF_TxPowerTable_TempCoeff;

typedef enum LRF_TxPowerResult_e {
    TxPowerResult_Ok,                  /*!< TX power value was OK */
    TxPowerResult_Error,               /*!< TX power value had an error */
} LRF_TxPowerResult;


#define LRF_EventNone                  ((LRF_Events){ .value = (0U << 0U)})   /*!< No events */
#define LRF_EventOpDone                ((LRF_Events){ .value = (1U << 0U)})   /*!< The PBE operation has finished */
#define LRF_EventPingRsp               ((LRF_Events){ .value = (1U << 1U)})   /*!< When receiving a CMD_PING, PBE responds with a PINGRSP. */
#define LRF_EventRxCtrl                ((LRF_Events){ .value = (1U << 2U)})   /*!< Frame filtering passed, or LL control packet received correctly */
#define LRF_EventRxCtrlAck             ((LRF_Events){ .value = (1U << 3U)})   /*!< LL control packet received with CRC OK, not to be ignored, then acknowledgement sent */
#define LRF_EventRxNok                 ((LRF_Events){ .value = (1U << 4U)})   /*!< Packet received with CRC error */
#define LRF_EventRxIgnored             ((LRF_Events){ .value = (1U << 5U)})   /*!< Packet received, but may be ignored by MCU */
#define LRF_EventRxEmpty               ((LRF_Events){ .value = (1U << 6U)})   /*!< Empty packet received, or Rx ACK treatment finished */
#define LRF_EventRxBufFull             ((LRF_Events){ .value = (1U << 7U)})   /*!< Packet received which did not fit in the RX FIFO and was not to be discarded.  */
#define LRF_EventRxOk                  ((LRF_Events){ .value = (1U << 8U)})   /*!< Packet received with CRC OK and not to be ignored by the MCU */
#define LRF_EventTxCtrl                ((LRF_Events){ .value = (1U << 9U)})   /*!< Transmitted LL control packet */
#define LRF_EventTxCtrlAckAck          ((LRF_Events){ .value = (1U << 10U)})  /*!< Acknowledgement received on a transmitted LL control packet, and acknowledgement transmitted for that packet */
#define LRF_EventTxRetrans             ((LRF_Events){ .value = (1U << 11U)})  /*!< Packet retransmitted with same SN */
#define LRF_EventTxAck                 ((LRF_Events){ .value = (1U << 12U)})  /*!< Acknowledgement transmitted, or acknowledgement received on a transmitted packet. */
#define LRF_EventTxDone                ((LRF_Events){ .value = (1U << 13U)})  /*!< Packet transmitted */
#define LRF_EventTxCtrlAck             ((LRF_Events){ .value = (1U << 14U)})  /*!< Acknowledgement received on a transmitted LL control packet */
#define LRF_EventOpError               ((LRF_Events){ .value = (1U << 15U)})  /*!< Something went awfully wrong, the reason is indicated in RAM-based register BLE_ENDCAUSE. */
#define LRF_EventRxfifo                ((LRF_Events){ .value = (1U << 16U)})  /*!< Event from fifo, triggered when crossing threshold. Normal use for rxfifo is to generate IRQ when crossing threshold upwards (filling fifo). But downwards is also possible to configure, could be use case for using both fifos for TX or both for RX */
#define LRF_EventTxfifo                ((LRF_Events){ .value = (1U << 17U)})  /*!< Event from fifo, triggered when crossing threshold. Normal use for txfifo is to generate IRQ when crossing threshold downwards (emptying fifo). But upwards is also possible to configure, could be use case for using both fifos for TX or both for RX */
#define LRF_EventLossOfLock            ((LRF_Events){ .value = (1U << 18U)})  /*!< LOSS_OF_LOCK event */
#define LRF_EventLock                  ((LRF_Events){ .value = (1U << 19U)})  /*!< LOCK event */
#define LRF_EventRfesoft0              ((LRF_Events){ .value = (1U << 20U)})  /*!< RFESOFT0 event */
#define LRF_EventRfesoft1              ((LRF_Events){ .value = (1U << 21U)})  /*!< RFESOFT1 event */
#define LRF_EventRfedone               ((LRF_Events){ .value = (1U << 22U)})  /*!< RFEDONE event */
#define LRF_EventMdmsoft0              ((LRF_Events){ .value = (1U << 23U)})  /*!< MDMSOFT event */
#define LRF_EventMdmsoft1              ((LRF_Events){ .value = (1U << 24U)})  /*!< MDMSOFT1 event */
#define LRF_EventMdmsoft2              ((LRF_Events){ .value = (1U << 25U)})  /*!< MDMSOFT event */
#define LRF_EventMdmout                ((LRF_Events){ .value = (1U << 26U)})  /*!< MDMOUT event */
#define LRF_EventMdmin                 ((LRF_Events){ .value = (1U << 27U)})  /*!< MDMIN event */
#define LRF_EventMdmdone               ((LRF_Events){ .value = (1U << 28U)})  /*!< MDMDONE event */
#define LRF_EventSystim0               ((LRF_Events){ .value = (1U << 29U)})  /*!< SYSTIM0 event */
#define LRF_EventSystim1               ((LRF_Events){ .value = (1U << 30U)})  /*!< SYSTIM1 event */
#define LRF_EventSystim2               ((LRF_Events){ .value = (1U << 31U)})  /*!< SYSTIM2 event */


union LRF_Events_u {
    struct {
        uint32_t opDone              : 1; /*!< The PBE operation has finished */
        uint32_t pingRsp             : 1; /*!< When receiving a CMD_PING, PBE responds with a PINGRSP. */
        uint32_t rxCtrl              : 1; /*!< LL control packet received correctly */
        uint32_t rxCtrlAck           : 1; /*!< LL control packet received with CRC OK, not to be ignored, then acknowledgement sent */
        uint32_t rxNok               : 1; /*!< Packet received with CRC error */
        uint32_t rxIgnored           : 1; /*!< Packet received, but may be ignored by MCU */
        uint32_t rxEmpty             : 1; /*!< Empty packet received */
        uint32_t rxBufFull           : 1; /*!< Packet received which did not fit in the RX FIFO and was not to be discarded.  */
        uint32_t rxOk                : 1; /*!< Packet received with CRC OK and not to be ignored by the MCU */
        uint32_t txCtrl              : 1; /*!< Transmitted LL control packet */
        uint32_t txCtrlAckAck        : 1; /*!< Acknowledgement received on a transmitted LL control packet, and acknowledgement transmitted for that packet */
        uint32_t txRetrans           : 1; /*!< Packet retransmitted with same SN */
        uint32_t txAck               : 1; /*!< Acknowledgement received on a transmitted packet. */
        uint32_t txDone              : 1; /*!< Packet transmitted */
        uint32_t txCtrlAck           : 1; /*!< Acknowledgement received on a transmitted LL control packet */
        uint32_t opError             : 1; /*!< Something went awfully wrong, the reason is indicated in RAM-based register BLE_ENDCAUSE. */
        uint32_t rxfifo              : 1; /*!< Event from fifo, triggered when crossing threshold. Normal use for rxfifo is to generate IRQ when crossing threshold upwards (filling fifo). But downwards is also possible to configure, could be use case for using both fifos for TX or both for RX */
        uint32_t txfifo              : 1; /*!< Event from fifo, triggered when crossing threshold. Normal use for txfifo is to generate IRQ when crossing threshold downwards (emptying fifo). But upwards is also possible to configure, could be use case for using both fifos for TX or both for RX */
        uint32_t lossOfLock          : 1; /*!< LOSS_OF_LOCK event */
        uint32_t lock                : 1; /*!< LOCK event */
        uint32_t rfesoft0            : 1; /*!< RFESOFT0 event */
        uint32_t rfesoft1            : 1; /*!< RFESOFT1 event */
        uint32_t rfedone             : 1; /*!< RFEDONE event */
        uint32_t mdmsoft0            : 1; /*!< MDMSOFT event */
        uint32_t mdmsoft1            : 1; /*!< MDMSOFT1 event */
        uint32_t mdmsoft2            : 1; /*!< MDMSOFT event */
        uint32_t mdmout              : 1; /*!< MDMOUT event */
        uint32_t mdmin               : 1; /*!< MDMIN event */
        uint32_t mdmdone             : 1; /*!< MDMDONE event */
        uint32_t systim0             : 1; /*!< SYSTIM0 event */
        uint32_t systim1             : 1; /*!< SYSTIM1 event */
        uint32_t systim2             : 1; /*!< SYSTIM2 event */
    };
    uint32_t value;
};

typedef struct LRF_RegConfig_s {
    uint32_t configLen;
    uint32_t regConfig[];
} LRF_RegConfig;

/**
 * @brief Index of the tx power table.
 */
typedef union
{
    struct {
        uint8_t fraction : 1; /*!< If set to 1, raises the requested power level by 0.5 dB */
        int8_t dBm : 7; /*!< Unit of level used to indicate that a power level is expressed in decibels (dB) with reference to one milliwatt (mW). */
    };
    int8_t rawValue; /*!< rawValue is twice the dBm number, allowing 0.5 dB steps */
} LRF_TxPowerTable_Index;

/**
 * @brief Single entry of the tx power table. Maps power in dBm to specific
 * register settings.
 */
typedef struct {
    LRF_TxPowerTable_Index power;            /*!< Power level */
    LRF_TxPowerTable_TempCoeff tempCoeff;    /*!< Temperature coefficient */
    LRF_TxPowerTable_Value value;            /*!< Settings to be compensated and written into register */
} LRF_TxPowerTable_Entry;

/** Value indicating that no valid tx power could be found in the table. */
#define LRF_TxPowerEntry_INVALID_VALUE \
((LRF_TxPowerTable_Entry) {\
    .power = LRF_TxPower_None,\
    .tempCoeff = 0,\
    .value = LRF_TxPowerTable_INVALID_VALUE,\
})

/**
 * @brief Tx power table, containing all characterized dBm to register settings mappings
 *
 *  The table must be sorted from lowest to highest power level
 */
typedef struct {
    uint32_t numEntries;
    LRF_TxPowerTable_Entry powerTable[];
} LRF_TxPowerTable;

/**
 * @brief Single entry of the Tx power limit table.
 */
typedef struct {
    uint16_t minFreq;                        /*!< Start of frequency range */
    uint16_t maxFreq;                        /*!< End of frequency range. Single frequency specified by maxFreq = minFreq */
    uint8_t regulatoryMask;                  /*!< Regulatory domain mask */
    LRF_TxPowerTable_Index maxTxPower;       /*!< Max power level for frequency in range [minFreq,maxFreq] */
} LRF_TxPowerLimitTable_Entry;

/**
 * @brief Tx power limit table, containing frequency dependent power limits for specific
 * regulatory domain
 */
typedef struct {
    uint32_t numEntries;                             /*!< Number of entries in the table*/
    uint32_t freqDiv;                                /*!< Frequency divisor. Used to determine the prefix of the frequency in the table */
    LRF_TxPowerLimitTable_Entry limitTable[];        /*!< Table with frequency specific power limits */
} LRF_TxPowerLimitTable;

typedef struct LRF_TxShape_s {
    struct {
        uint32_t      scale    :17;
        uint32_t      numCoeff :15;
    };
    uint8_t       coeff[];
} LRF_TxShape;

typedef struct {
    uint16_t T1;            /* T1 constant (RF activity latency) in 0.25 us steps. 0: REQUEST and PRIORITY not used */
    uint8_t T2;             /* T2 constant (Priority indication time) in 0.25 us steps. 0: No priority indication */
    uint8_t grantPin;       /* Grant pin in use if coex is enabled, or "disabled" if globally disabled */
    bool invertedPriority;  /* True if coex priority signal is inverted (0 means high priority) */
    uint16_t ieeeTSync;     /* IEEE 802.15.4: Timeout (0.25 us steps) of REQUEST on frame indication before sync must be seen */
    uint8_t ieeeCorrMask;   /* IEEE 802.15.4: Bit mask indicating correlation tops needed to declare frame indication */
} LRF_CoexConfiguration;

/* Definitions for trim */
#define LRF_TRIM_NUM_VARIANTS 2

typedef struct {
    uint32_t word[2];
} LRF_DoubleWord;

#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX)
typedef struct {
    union {
        struct {
            uint16_t r0     : 4;
            uint16_t r1     : 4;
            uint16_t r2     : 4;
            uint16_t r3     : 4;
        } fields;
        uint16_t value;
    };
} LRF_Trim_vddsComp;
typedef struct {
    int8_t thr;
    union {
        struct {
            uint8_t val     : 4;
            uint8_t spare   : 4;
        } fields;
        uint8_t value;
    };
} LRF_Trim_rtrimTxComp;
typedef struct {
    union {
        struct {
            uint16_t lowCmp  : 4;
            uint16_t highCmp : 4;
            uint16_t nomTmp  : 4;
            uint16_t nomIdx  : 4;
        } fields;
        uint16_t value;
    };
} LRF_Trim_tempCoeffComp;
#endif //DeviceFamily_PARENT_CC27XX

typedef union {
    struct {
        // Trim value for LRFDRFE:PA0.TRIM
        union {
            struct {    // length: 2B
                uint16_t trim           : 5;
                uint16_t zero           : 11;
            } pa0;
#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX)
            // Trim values for PA (mode0, mode1)
            struct {    // length: 2B
                uint16_t trim0           : 5;
                uint16_t zero0           : 3;
                uint16_t trim1           : 5;
                uint16_t zero1           : 3;
            } pa2trim01;
#endif
        };
        // Trim value for LRFDRFE:ATSTREFH.IREFTRIM
        struct {    // length: 2B
            uint16_t zero0          : 10;
            uint16_t irefTrim       : 5;
            uint16_t zero1          : 1;
        } atstRefH;
    } fields;
    struct {
#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX)
        uint16_t pa2trim01;
#else
        uint16_t pa0;
#endif
        uint16_t atstRefH;
    };
    uint32_t data;
} LRF_Trim0;

typedef union {
    struct {
        // Trim value for LRFDRFE:LNA.TRIM
        struct {    // length: 2B
            uint16_t zero0          : 4;
            uint16_t trim           : 4;
            uint16_t zero1          : 8;
        } lna;
        // Trim value for LRFDRFE:IFAMPRFLDO.TRIM
        struct {    // length: 2B
            uint16_t zero           : 9;
            uint16_t trim           : 7;
        } ifampRfLdo;
        // Trim value for LRFDRFE:DIVLDO.VOUTTRIM
        struct {    // length: 2B
            uint16_t zero0          : 8;
            uint16_t voutTrim       : 7;
            uint16_t zero1          : 1;
        } divLdo;
        // Trim value for LRFDRFE:TDCLDO.VOUTTRIM
        struct {    // length: 2B
            uint16_t zero0          : 8;
            uint16_t voutTrim       : 7;
            uint16_t zero1          : 1;
        } tdcLdo;
    } fields;
    struct {
        uint16_t lna;
        uint16_t ifampRfLdo;
        uint16_t divLdo;
        uint16_t tdcLdo;
    };
    LRF_DoubleWord data;
} LRF_Trim1;

typedef union {
    struct {
        // Trim values for LRFDRFE:DCOLDO0
        struct {    // length: 2B
            uint16_t zero0          : 4;
            uint16_t firstTrim      : 4;
            uint16_t secondTrim     : 6;
            uint16_t zero1          : 2;
        } dcoLdo0;
        // Trim value for LRFDRFE:IFADCALDO.TRIMOUT
        struct {    // length: 2B
            uint16_t zero0          : 8;
            uint16_t trimout        : 6;
            uint16_t zero1          : 2;
        } ifadcAldo;
        // Trim value for LRFDRFE:IFADCDLDO.TRIMOUT
        struct {    // length: 2B
            uint16_t zero0          : 8;
            uint16_t trimout        : 6;
            uint16_t zero1          : 2;
        } ifadcDldo;
        // Trim value for LRFDRFE:DCO.TAILRESTRIM
        struct {    // length: 2B
            uint16_t zero0          : 3;
            uint16_t tailresTrim    : 4;
            uint16_t zero1          : 9;
        } dco;
    } fields;
    struct {
        uint16_t dcoLdo0;
        uint16_t ifadcAldo;
        uint16_t ifadcDldo;
        uint16_t dco;
    };
    LRF_DoubleWord data;
} LRF_Trim2;

typedef union {
    struct {
        // Trim value for LRFDRFE:IFADCQUANT.QUANTTHR
        struct {    // length: 2B
            uint16_t quantThr       : 3;
            uint16_t zero           : 13;
        } ifadcQuant;
        // Trim values for LRFDRFE:IFADC0
        struct {    // length: 2B
            uint16_t zero0          : 2;
            uint16_t aafcap         : 2;
            uint16_t int2Adj        : 4;
            uint16_t zero1          : 2;
            uint16_t ditheren       : 2;    /* Revision >= 4 only */
            uint16_t dithertrim     : 3;
            uint16_t zero2          : 1;
        } ifadc0;
        // Trim value for LRFDRFE:IFADC1.TRIM
        struct {    // length: 2B
            uint16_t zero0          : 9;
            uint16_t trim           : 6;
            uint16_t nrz            : 1;
        } ifadc1;
        // Trim values for LRFDRFE:IFADCLF
        struct {    // length: 2B
            uint16_t int3           : 4;
            uint16_t ff1            : 4;
            uint16_t ff2            : 4;
            uint16_t ff3            : 4;
        } ifadclf;
    } fields;
    struct {
        uint16_t ifadcQuant;
        uint16_t ifadc0;
        uint16_t ifadc1;
        uint16_t ifadclf;
    };
    LRF_DoubleWord data;
} LRF_Trim_Variant;

typedef struct
{
    uint16_t rtrimMinOffset : 2;
    uint16_t rtrimMaxOffset : 2;
    uint16_t divLdoMinOffset: 2;
    uint16_t divLdoMaxOffset: 2;
    uint16_t tdcLdoMinOffset: 2;
    uint16_t tdcLdoMaxOffset: 2;
    uint16_t tThrl          : 2;
    uint16_t tThrh          : 2;
} LRF_Trim_tempLdoRtrim;

typedef struct {
    int32_t rssiTcomp      : 4;
    int32_t magnTcomp      : 4;
    int32_t magnOffset     : 4;
    int32_t rfu            : 4;
    int32_t agcThrTcomp    : 4;
    int32_t agcThrOffset   : 4;
    int32_t lowGainOffset  : 4;
    int32_t highGainOffset : 4;
} LRF_Trim_tempRssiAgc;

typedef struct {
    uint8_t dcoldoFirstMinOffset       : 2;
    uint8_t dcoldoFirstMaxOffset       : 2;
    uint8_t dcoldoSecondMinOffset      : 2;
    uint8_t dcoldoSecondMaxOffset      : 2;
} LRF_Trim_dcoldoOffset;
typedef union {
    struct {
        struct {    // length: 4B
            LRF_Trim_tempLdoRtrim tempLdoRtrim;
            uint8_t hfxtPdError;
            LRF_Trim_dcoldoOffset dcoldoOffset; /* Revision >= 8 only */
         } lrfdrfeExtTrim1;                  /* Revision >= 4 only */
        // Trim values for synth divider 0
        LRF_Trim_tempRssiAgc lrfdrfeExtTrim0;
    } fields;
    struct {
        uint32_t lrfdrfeExtTrim1;
        uint32_t lrfdrfeExtTrim0;
    };
    uint32_t data;
} LRF_Trim3;

typedef union {
    struct {
        struct {    // length: 2B
                    // RSSI measured for front end 0 in production test.
                    // Value is read by RF Core FW during RF Core initialization
            uint16_t offset         : 8;
            uint16_t trimCompleteN  : 1;
            uint16_t zero           : 7;
        } fend0Rssi;
        // Trim values for synth divider 0
        struct {    // length: 2B
                    // Trim value for IQ mismatch compensation.
                    // Value is read by RF Core FW during RF Core initialization
            uint16_t iqmc           : 16;
        } syntDiv0;
#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX)
        // Trim values for PA (mode2, mode3)
        struct {    // length: 2B
            uint16_t trim2           : 5;
            uint16_t zero0           : 3;
            uint16_t trim3           : 5;
            uint16_t zero1           : 3;
        } pa2trim23;
#else
        uint16_t res1;
#endif
        struct {
            uint8_t zero            : 4;
            uint8_t aafcap          : 4;
        } ifamprfldo[LRF_TRIM_NUM_VARIANTS];     /* Revision >= 4 only */
    } fields;
    struct {
        int8_t   rssiOffset;
        uint8_t  trimCompleteN;
        uint16_t demIQMC0;
#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX)
        uint16_t pa2trim23;
#else
        uint16_t res1;
#endif
        uint8_t  ifamprfldo[LRF_TRIM_NUM_VARIANTS];
    };
    uint32_t data;
} LRF_Trim4;

#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX)
typedef union {
    struct {
        LRF_Trim_vddsComp vddsComp;
        uint16_t reserved;
        LRF_Trim_rtrimTxComp rtrimTxComp;
        LRF_Trim_tempCoeffComp tempCoeffComp;
    };
    uint32_t data;
} LRF_Trim11;
#endif //DeviceFamily_PARENT_CC27XX

/* This definition is used instead of the definition from hw_fcfg.h to accommodate implementation
   and cut parameters not relevant to LRF */
typedef struct {
    uint8_t             revision;           /* Revision of appTrims */
    uint8_t             nToolsClientOffset;
    uint8_t             reserved[2];
    LRF_Trim0           trim0;
    LRF_Trim1           trim1;
    LRF_Trim2           trim2;
    LRF_Trim_Variant    trimVariant[LRF_TRIM_NUM_VARIANTS];
    LRF_Trim3           trim3;
    LRF_Trim4           trim4;
#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX)
    uint32_t            reserved1[15];
    LRF_Trim11          trim11;
#endif //DeviceFamily_PARENT_CC27XX
} LRF_TrimDef;

/**
 *  @brief Software defined PHY parameters
 */
typedef struct LRF_SwConfig_s {
    int32_t           rxIntFrequency;         /*!< Receiver intermediate frequency [Hz] */
    int32_t           rxFrequencyOffset;      /*!< Receiver frequency offset [Hz] */
    int32_t           txFrequencyOffset;      /*!< Transmitter frequency offset [Hz] */
    uint32_t          modFrequencyDeviation;  /*!< Transmitter frequency deviation [Hz] */
    const LRF_TxShape *txShape;               /*!< Transmitter shape definition */
    uint8_t           bwIndex;                /*!< Index to use for bandwitdh dependent settings (0: normal 1: high) */
    uint8_t           bwIndexDither;          /*!< Index to use for bandwitdh dependent ADC dithering settings (0: low 1: normal/high) */
} LRF_SwConfig;

/**
 *  @brief Software defined PHY parameter list
 */
typedef struct LRF_SwParam_s {
    const LRF_SwConfig          *swConfig;          /*!< Software defined parameters. */
    const LRF_TxPowerLimitTable *txPowerLimitTable; /*!< TX power limit table */
    const LRF_TxPowerTable      *txPowerTable;      /*!< TX power table */
    const LRF_TrimDef           *trimDef;           /*!< Trim definitions. NULL: Do not apply trim. */
} LRF_SwParam;

/**
 *  @brief Radio configuration structure
 */
typedef struct LRF_Config_s {
    const LRF_TOPsmImage    *pbeImage;       /*!< Image for the PBE */
    const LRF_TOPsmImage    *mceImage;       /*!< Image for the MCE */
    const LRF_TOPsmImage    *rfeImage;       /*!< Image for the RFE */
    const LRF_RegConfigList *regConfigList;  /*!< List of pointers to register definitions */
} LRF_Config;

#define LRF_BASE_ADDR           0x40080000U
#define PBE_RAM_BASE_ADDR       0x40090000U
#define BUF_RAM_BASE_ADDR       0x40092000U
#define RXF_UNWRAPPED_BASE_ADDR 0x40093000U
#define TXF_UNWRAPPED_BASE_ADDR 0x40093800U
#define MCE_RAM_BASE_ADDR       0x40094000U
#define RFE_RAM_BASE_ADDR       0x40096000U
#define S2R_RAM_BASE_ADDR       0x40098000U
#define TOPSM_RAM_SZ            0x00001000U /* 4 KB */
#define MAX_REG_CONFIG_LEN      1024U        /* 1024 entries, using 4 KB */

#define LRF_TXPOWER_REFERENCE_TEMPERATURE      25          /*!< Reference temperature for TX power, degrees C */
#define LRF_TXPOWER_TEMPERATURE_SCALING        0x100       /*!< Scaling factor for TX power temperature coefficients */
#define LRF_TXPOWER_BYPASS_FREQUENCY_BACKOFF   0xFFFFFFFF  /*!< Special value to indicate that no frequency specific back-off should be applied */

extern const LRF_TxShape LRF_shapeBaseGfsk05;
extern const LRF_TxShape LRF_shapeBaseGfsk067;
extern const LRF_TxShape LRF_shapeBaseGfsk20;

static inline void LRF_sendHardStop(void)
{
    /* Send stop to PBE */
    /* This API is the same across PBE banks */
    HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_API) = PBE_GENERIC_REGDEF_API_OP_STOP;
}

static inline void LRF_sendGracefulStop(void)
{
    /* Send stop to PBE */
    /* This API is the same across PBE banks */
    HWREG_WRITE_LRF(LRFDPBE_BASE + LRFDPBE_O_API) = PBE_GENERIC_REGDEF_API_OP_EOPSTOP;
}

static inline void LRF_hardStop(void)
{
    /* LRF does not need to do anything special after hard stop is sent */
}

/**
 * @brief Programs current TX power setting in radio with temperature compensation
 */
void LRF_programTemperatureCompensatedTxPower(void);

/**
 * @brief Finds settings corresponding to the highest tx power lower than
 * the specified value in the tx power table and programs it in the radio
 *
 *  @param  powerLevel maximum allowed power level in dBm, or special value
 *      (%LRF_TxPower_Use_Min, %LRF_TxPower_Use_Max, %LRF_TxPower_Use_Raw, or %LRF_TxPower_None)
 *  @param  rfFreq Radio frequency in Hz for which the maximum Tx power is calculated
 *
 *  @return TxPowerResult_Ok on success; TxPowerResult_Error if no valid settings were found
 *
 */
LRF_TxPowerResult LRF_programTxPower(LRF_TxPowerTable_Index powerLevel, uint32_t rfFreq);

/**
 * @brief Reads maximum RSSI from register
 */
int8_t LRF_readMaxRssi(void);

/**
 * @brief Initialize maximum RSSI register
 */
void LRF_initializeMaxRssi(int8_t initRssi);

/**
 * @brief Request specific clock enable bits for use by the RCL
 *
 *  @param  mask Bit mask of clock enable bits to be set; bit positions as in LRFDDBELL_CLKCTL
 *
 */
static inline void LRF_setRclClockEnable(uint16_t mask)
{
    RCL_Hal_setRclClockEnable(mask);
}

/**
 * @brief Remove request of specific clock enable bits for use by the RCL
 *
 *  @param  mask Bit mask of clock enable bits to be cleared; bit positions as in LRFDDBELL_CLKCTL
 *
 */
static inline void LRF_clearRclClockEnable(uint16_t mask)
{
    RCL_Hal_clearRclClockEnable(mask);
}

/**
 * @brief Enable monitoring of coexistence grant signal in RFE
 *
 *  Turns on the coex grant signal for the configured IO pin (if any). The function must be called
 *  before starting a PBE operation. The handler is responsible for disabling in order to avoid
 *  coex operation in commands not supporting it.
 *
 *  @note This function is intended as internal to RCL and its handlers
 *
 */
void LRF_enableCoexGrant(void);

/**
 * @brief Disable monitoring of coexistence grant signal in RFE
 *
 *  Turns off the coex grant signal to the RFE. Should be called by the handler at the end of a
 *  command where LRF_enableCoexGrant was called. The function must be called after the PBE
 *  operation ended, but can safely be called even without a previous LRF_enableCoexGrant.
 *
 *  @note This function is intended as internal to RCL and its handlers
 *
 */
void LRF_disableCoexGrant(void);

/**
 * @brief Deassert coexistence REQUEST
 *
 *  Set coex REQUEST and PRIORITY lines low to indicate no request. Should only be done when PBE
 *  is finished.
 *
 *  @note This function is intended as internal to RCL and its handlers
 *
 */
void LRF_deassertCoexRequest(void);

/**
 * @brief Enable temperature monitoring to allow handlers to update temperature compensation
 *
 *  @note This function is intended as internal to RCL and its handlers
 *
 */
void LRF_enableTemperatureMonitoring(void);

/**
 * @brief Disable temperature monitoring
 *
 *  @note This function is intended as internal to RCL and its handlers
 *
 */
void LRF_disableTemperatureMonitoring(void);

/**
 * @brief Update temperature compensation in radio
 *
 * Update temperature compensation by allowing TCXO updates, set new RF frequency correction,
 * update temperature compensated trim values, and update temperature compensation for TX power
 *
 *  @note This function is intended as internal to RCL and its handlers
 *
 *  @param rfFrequency RF frequency at which the command is operating
 *  @param tx True if radio will be starting in TX; false if it will be starting in RX
 *
 */
void LRF_updateTemperatureCompensation(uint32_t rfFrequency, bool tx);

/**
 * @brief Get temperature used in last setting of trims
 */
int16_t LRF_getLastTrimTemperature(void);

/**
 * @brief Set the default antenna to be used during the next radio configuration.
 *
 * This function configures the antenna selection value for the current PHY.
 * The selection does not take effect immediately but will be applied the next
 * time the radio is configured. This typically occurs when a radio command is
 * started or when the device wakes up from standby while running a radio command.
 *
 * @note This function is intended for internal use only.
 *
 * @param value Antenna selection value.
 *
 */
void LRF_setAntennaSelection(uint32_t value);

#if (DeviceFamily_PARENT == DeviceFamily_PARENT_CC27XX)
/**
 * @brief Update the PA ESD protection configuration
 *
 * This function updates the PA ESD protection configuration by following these
 * rules:
 * - Enable the PA ESD protection if the 20dBm mode is enabled and the VDDS
 *   supply voltage is equal to or greater than 3.635V.
 * - Otherwise, disable the PA ESD protection.
 *
 * The new configuration does not take effect immediately but will be applied
 * the next time the PA is enabled in the modem.
 *
 * @note This function is intended for internal use only.
 *
 */
void LRF_updatePaEsdProtection();
#endif

#endif /* ti_drivers_rcl_lrf_LRFLPF3__include */
