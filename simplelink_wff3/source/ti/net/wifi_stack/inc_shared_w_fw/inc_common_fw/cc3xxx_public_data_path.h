/*
 * Copyright (c) 2024, Texas Instruments Incorporated
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
#ifndef FW_CC3XXX_PUBLIC_DATA_PATH_H_
#define FW_CC3XXX_PUBLIC_DATA_PATH_H_

#include "cc3xxx_public_types.h"
//******************************************************************************
//                        TX descriptor
//******************************************************************************

/* The Tx Descriptor preceding each Tx packet copied to the FW (before the packet). */
    typedef struct TxIfDescriptor_t
    {
        uint16_t          length;         /* Length of packet in words, including descriptor+header+data */
        uint8_t           totalMemBlks;   /* Total number of memory blocks allocated by the host for this packet. */
                                        /* Must be equal or greater than the actual blocks number allocated by HW!! */
        uint8_t           extraMemBlks;   /* Number of extra memory blocks to allocate for this packet in addition */

        uint8_t           descID;         /* Packet identifier used also in the Tx-Result. */
        uint8_t           tid;            /* The packet TID value (as User-Priority) */
        uint8_t           hlid;           /* Identifier of link. each hlid (host lid) is mapped to a flid (fw lid) */
        uint8_t           csumData;       /* bit 0 - TCP/UDP indication bit 1-7 IP header offset*/
        uint16_t          lifeTime;       /* Max delay in TUs until transmission. The last device time the
                                                packet can be transmitted is: startTime+(1024*LifeTime) */
         uint16_t          txAttr;         /* Bitwise fields - see TX_ATTR... definitions above. */
    } TxIfDescriptor_t;

    /* TX attributes masks and offset used in the txAttr of TxIfDescriptor_t. */
    #define     TX_ATTR_SAVE_RETRIES          BIT_0
    #define     TX_ATTR_HEADER_PAD            BIT_1
    #define     TX_ATTR_SESSION_COUNTER       (BIT_2 | BIT_3 | BIT_4)
    #define     TX_ATTR_RATE_POLICY           (BIT_5 | BIT_6 | BIT_7 | BIT_8 | BIT_9)
    #define     TX_ATTR_LAST_WORD_PAD         (BIT_10 | BIT_11)
    #define     TX_ATTR_TX_CMPLT_REQ          BIT_12
    #define     TX_ATTR_TX_DUMMY_REQ          BIT_13
    #define     TX_ATTR_HOST_ENCRYPT_PACKET   BIT_14
    #define     TX_ATTR_EAPOL_FRAME           BIT_15 /* 26-feb-2013 - igal chernobelsky & jigal - added EAPOL tagging of frames */

    #define     TX_ATTR_OFST_SAVE_RETRIES     0
    #define     TX_ATTR_OFST_HEADER_PAD       1
    #define     TX_ATTR_OFST_SESSION_COUNTER  2
    #define     TX_ATTR_OFST_RATE_POLICY      5
    #define     TX_ATTR_OFST_LAST_WORD_PAD    10
    #define     TX_ATTR_OFST_TX_CMPLT_REQ     12
    #define     TX_ATTR_OFST_TX_DUMMY_REQ     13
    #define     TX_ATTR_OFST_HOST_ENCRYPT_PACKET   14
    #define     TX_ATTR_OFST_EAPOL_FRAME           15


    /******************************************************************************

            RX PATH

    ******************************************************************************/
    /* ------------------------------------- */
    /* flags field in the RxIfDescriptor_t   */
    /* ------------------------------------- */
    /*   Bit5-7: Encryption type:            */
    /*           0 - none                    */
    /*           1 - WEP                     */
    /*           2 - TKIP                    */
    /*           3 - AES                     */
    /*           4 - GEM                     */
    /*   Bit4: HT                            */
    /*   Bit3: Was part of A-MPDU            */
    /*   Bit2: STBC                          */
    /*   Bit0-1: Band the frame was received */
    /*           from (0=2.4, 1=4.9, 2=5.0)  */
    /* ------------------------------------- */
    #define    RX_DESC_BAND_MASK        0x03  /* Band is in Bits 0-1 */
    #define    RX_DESC_BAND_BG          0x00
    #define    RX_DESC_BAND_J           0x01
    #define    RX_DESC_BAND_A           0x02
    #define    RX_DESC_STBC             0x04
    #define    RX_DESC_A_MPDU           0x08
    #define    RX_DESC_HT               0x10
    #define    RX_DESC_ENCRYPT_MASK     0xE0  /* Encryption is in Bits 5-7 */
    #define    RX_DESC_ENCRYPT_WEP      0x20
    #define    RX_DESC_ENCRYPT_TKIP     0x40
    #define    RX_DESC_ENCRYPT_AES      0x60
    #define    RX_DESC_ENCRYPT_GEM      0x80


    /* ------------------------------------- */
    /* Status field in the RxIfDescriptor_t  */
    /* ------------------------------------- */
    /*   Bit6-7: checksum validation state   */
    /*   Bit3-5: reserved (0)                */
    /*   Bits[2:0] = Error code:                      */
    /*             0  ==> SUCCESS                   */
    /*             1  ==> RX_DECRYPT_FAIL           */
    /*             2  ==> RX_MIC_FAIL               */
    /*             3  ==> STA_NOT_FOUND             */
    /*             4  ==> KEY_NOT_FOUND             */
    /* ------------------------------------- */
    #define    RX_DESC_STATUS_SUCCESS           0
    #define    RX_DESC_STATUS_DECRYPT_FAIL      1
    #define    RX_DESC_STATUS_MIC_FAIL          2
    #define    RX_DESC_STATUS_DRIVER_RX_Q_FAIL  3

    #define    RX_DESC_HOST_STATUS_FAIL                5
    #define    RX_DESC_HOST_STATUS_HANDLED             6
    #define    RX_DESC_HOST_UNWANTED_SEQUENCE_NUMBER   7


    #define    RX_DESC_STATUS_MASK              3

    /* this bit is used to mark the first packet received from a new key */
    /* currenlty used only for unicast keys */
    #define    RX_DESC_STATUS_NEW_KEY           BIT_6


    /* ---------------------------------------- */
    /* rx_level field in the RxIfDescriptor_t   */
    /* ---------------------------------------- */
    /*   Bits 0-6: RSSI value of current frame  */
    /*   Bit    7: current antenna              */
    /* ---------------------------------------- */
    #define    RX_DESC_RX_LEVEL_RSSI_MASK   0x7F
    #define    RX_DESC_RX_LEVEL_ANT_BIT     BIT_7
    #define    RX_DESC_RX_LEVEL_ANT_SHIFT   7
    // turned on in driverFlags in every RxIfDescriptor to indicate RX QoS Alignment
    #define    RX_DESC_QOS_ALIGNMENT_FLAG       BIT_4

    #define    RX_DESC_STATUS_CHECKSUM_NONE          0
    #define    RX_DESC_STATUS_CHECKSUM_UNNECESSARY  0x40
    #define    RX_DESC_STATUS_CHECKSUM_COMPLETE     0x80

    #define    RX_DESC_STATUS_CSUM_MASK             0xC0



    /* Add hlid: process_id_tag field moved into status fileds bits [5..3] */
    #define    RX_DESC_STATUS_PROC_ID_TAG_MASK  0x7
    #define    RX_DESC_STATUS_PROC_ID_TAG_SHFT  3

    /**********************************************
        clasify tagging
    ***********************************************/
    typedef enum
    {
        TAG_CLASS_UNKNOWN       = 0,
        TAG_CLASS_MANAGEMENT    = 1, /* other than Beacon or Probe Resp */
        TAG_CLASS_DATA          = 2,
        TAG_CLASS_QOS_DATA      = 3,
        TAG_CLASS_BCN_PRBRSP    = 4,
        TAG_CLASS_EAPOL         = 5,
        TAG_CLASS_BA_EVENT      = 6,
        TAG_CLASS_AMSDU         = 7,
        TAG_CLASS_LOGGER        = 8,
        TAG_CLASS_IAPP          = 9 /*USED BY MCP for CCX*/
    } PacketClassTag_enum;

    #ifdef HOST_COMPILE
    typedef uint8_t PacketClassTag_e;
    #else
    typedef PacketClassTag_enum PacketClassTag_e;
    #endif

    typedef uint8_t ProcessIDTag_e;

    /* ------------------------------------------------------- */
    /* flags field in the driverFlags of the RxIfDescriptor_t  */
    /* ------------------------------------------------------- */
    /*   Bit0   :  EndOfBurst flag                              */
    /*   Bit1-7 : - not in use                                 */
    /* ------------------------------------------------------- */

    /* Set by driver(!) to indicate last packet in current burst (current FW interrupt) */
    #define DRV_RX_FLAG_END_OF_BURST  0x01


    typedef enum wl_rx_buf_align {
            WLCORE_RX_BUF_ALIGNED,
            WLCORE_RX_BUF_UNALIGNED,
            WLCORE_RX_BUF_PADDED,
        } rxBufAlign_e;
    /******************************************************************************

        RxIfDescriptor_t

        the structure of the Rx Descriptor recieved by HOST.

    ******************************************************************************/
    typedef struct
    {
        uint16_t                length;             /* Length of payload (including headers)*/
        uint8_t/*rxBufAlign_e*/ header_alignment;   /* Packet classification tagging info */

        uint8_t               status;             /* status is now a bit-field structure:         */
                                                /* Bit 7     = reserved                         */
                                                /* Bit 6     = new key indication               */
                                                /* Bits[5:3] = Process_ID_Tag                   */
                                                /* Bits[2:0] = Error code:                      */
                                                /*             0  ==> SUCCESS                   */
                                                /*             1  ==> RX_DECRYPT_FAIL           */
                                                /*             2  ==> RX_MIC_FAIL               */
                                                /*             3  ==> STA_NOT_FOUND             */
                                                /*             4  ==> KEY_NOT_FOUND             */
                                                /*                                              */
        uint32_t              timestamp;          /* Timestamp in microseconds,     */

        uint8_t               flags;              /* See RX_DESC_xxx above */

        uint8_t               rate;               /* Recevied Rate:at ETxRateClassId format */

        uint8_t               channel;            /* The received channel*/

        int8_t                rx_level;           /* The computed RSSI value in db of current frame */
                                                /* The msb is reserved to represent the antenna used to receive the frame */

        uint8_t               rx_snr;             /* The computed SNR value in db of current frame */


        uint8_t               hlid;               /* Host Link ID associated with the source of the frame  */
        uint8_t               extraBytes;         /* Number of padding bytes added to actual packet length */

        uint8_t               frameFormat;        /* holds the driver flags to be used internally */

    } RxIfDescriptor_t;


/* \brief Macro which gets a pointer to BUF packet header and returns the pointer to the start address of the WLAN packet's data
 */
#ifndef ALIGMENT_AND_EXTRA_BYTES_REMOVED_IN_XFR
#define RX_BUF_DATA(pBuf)    ((void*)((uint8_t *)pBuf + sizeof(RxIfDescriptor_t)))

/* \brief Macro which gets a pointer to BUF packet header and returns the buffer length (without Rx Descriptor) of the WLAN packet
 */
#define RX_BUF_LEN(pBuf)    ( (((RxIfDescriptor_t *)(pBuf))->length) -  \
                              sizeof(RxIfDescriptor_t) )
#else
#define RX_BUF_DATA(pBuf)   ( (((RxIfDescriptor_t *)pBuf)->header_alignment == WLCORE_RX_BUF_PADDED) ?   \
                              ((void*)((uint8_t *)pBuf + sizeof(RxIfDescriptor_t) + 2)) :   \
                              ((void*)((uint8_t *)pBuf + sizeof(RxIfDescriptor_t))) )

/* \brief Macro which gets a pointer to BUF packet header and returns the buffer length (without Rx Descriptor) of the WLAN packet
 */
#define RX_BUF_LEN(pBuf)    ( (((RxIfDescriptor_t *)(pBuf))->length) -  \
                              ((RxIfDescriptor_t *)(pBuf))->extraBytes -     \
                              sizeof(RxIfDescriptor_t) )
#endif
/* \brief Macro which gets a pointer to BUF packet header and returns the pointer to the start address of the ETH packet's data
 */
#define RX_ETH_PKT_DATA(pBuf)   *((void **)(((uint32_t)pBuf + sizeof(RxIfDescriptor_t) + 2) & ~3))

/* \brief Macro which gets a pointer to BUF packet header and returns the buffer length (without Rx Descriptor) of the ETH packet
 */
#define RX_ETH_PKT_LEN(pBuf)    *((uint32_t *)(((uint32_t)pBuf + sizeof(RxIfDescriptor_t) + 6) & ~3))

#define RX_PKT_NEXT_MSDU(pBuf)  *((void **)(((uint32)pBuf + sizeof(RxIfDescriptor_t) + 8) & ~3))

#endif /* FW_CC3XXX_PUBLIC_DATA_PATH_H_ */
