/*
 * Copyright (c) 2018-2026, Texas Instruments Incorporated
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
 *  ======== pbe_ieee_ram_regs.h ========
*/

#ifndef __PBE_IEEE_RAM_REGS_H
#define __PBE_IEEE_RAM_REGS_H

//******************************************************************************
// REGISTER OFFSETS
//******************************************************************************
// Configure synth calibration timeout
#define PBE_IEEE_RAM_O_SYNTHCALTIMEOUT                               0x00000020U

// Configure FIFO what statuses to append
#define PBE_IEEE_RAM_O_FIFOCFG                                       0x00000022U

// 
#define PBE_IEEE_RAM_O_EXTRABYTES                                    0x00000024U

// 
#define PBE_IEEE_RAM_O_PRETXIFS                                      0x00000026U

// 
#define PBE_IEEE_RAM_O_PRERXIFS                                      0x00000028U

// 
#define PBE_IEEE_RAM_O_PRETXIFSV2                                    0x0000002AU

// 
#define PBE_IEEE_RAM_O_PILOTLEN                                      0x0000002CU

// How long to search for sync before giving up
#define PBE_IEEE_RAM_O_RXTIMEOUT                                     0x0000002EU

// Combined tx/rx/fs configuration
#define PBE_IEEE_RAM_O_OPCFG                                         0x00000030U

// 
#define PBE_IEEE_RAM_O_PATTERN                                       0x00000032U

// Initialization for the whitener, if 0 the whitener is not used
#define PBE_IEEE_RAM_O_WHITEINIT                                     0x00000034U

// 
#define PBE_IEEE_RAM_O_PIB                                           0x00000036U

// 
#define PBE_IEEE_RAM_O_FFTYPE                                        0x00000038U

// 
#define PBE_IEEE_RAM_O_NRXNOK                                        0x0000003AU

// 
#define PBE_IEEE_RAM_O_NRXIGNORED                                    0x0000003CU

// 
#define PBE_IEEE_RAM_O_NTXENHACK                                     0x0000003EU

// 
#define PBE_IEEE_RAM_O_NRXFIFOFULL                                   0x00000040U

// 
#define PBE_IEEE_RAM_O_NRXOK                                         0x00000042U

// 
#define PBE_IEEE_RAM_O_NTX                                           0x00000044U

// 
#define PBE_IEEE_RAM_O_NTXACK                                        0x00000046U

// 
#define PBE_IEEE_RAM_O_NRXTIMEOUT                                    0x00000048U

// 
#define PBE_IEEE_RAM_O_LASTRSSI                                      0x0000004AU

// 
#define PBE_IEEE_RAM_O_LASTFREQOFF                                   0x0000004CU

// 
#define PBE_IEEE_RAM_O_LASTLQI                                       0x0000004EU

// 
#define PBE_IEEE_RAM_O_LASTTIMESTAMPL                                0x00000050U

// 
#define PBE_IEEE_RAM_O_LASTTIMESTAMPH                                0x00000052U

// Status of receiver and transmitter
#define PBE_IEEE_RAM_O_RXSTATUS                                      0x00000054U

// General use purpose for storing values
#define PBE_IEEE_RAM_O_TMPREG1                                       0x00000056U

// General use purpose for storing values
#define PBE_IEEE_RAM_O_TMPREG2                                       0x00000058U

// General use purpose for storing values
#define PBE_IEEE_RAM_O_TMPREG3                                       0x0000005AU

// General use purpose for storing values
#define PBE_IEEE_RAM_O_TMPREG4                                       0x0000005CU

// Value of last sequence number found
#define PBE_IEEE_RAM_O_LSEQNR                                        0x0000005EU

// Source matching index
#define PBE_IEEE_RAM_O_SRCMATCHIDX                                   0x00000060U

// 
#define PBE_IEEE_RAM_O_PANID0                                        0x00000064U

// 
#define PBE_IEEE_RAM_O_SHORTADDR0                                    0x00000066U

// 
#define PBE_IEEE_RAM_O_EXTADDR00                                     0x00000068U

// 
#define PBE_IEEE_RAM_O_EXTADDR01                                     0x0000006AU

// 
#define PBE_IEEE_RAM_O_EXTADDR02                                     0x0000006CU

// 
#define PBE_IEEE_RAM_O_EXTADDR03                                     0x0000006EU

// 
#define PBE_IEEE_RAM_O_FFOPT0                                        0x00000070U

// 
#define PBE_IEEE_RAM_O_PANID1                                        0x00000074U

// 
#define PBE_IEEE_RAM_O_SHORTADDR1                                    0x00000076U

// 
#define PBE_IEEE_RAM_O_EXTADDR10                                     0x00000078U

// 
#define PBE_IEEE_RAM_O_EXTADDR11                                     0x0000007AU

// 
#define PBE_IEEE_RAM_O_EXTADDR12                                     0x0000007CU

// 
#define PBE_IEEE_RAM_O_EXTADDR13                                     0x0000007EU

// 
#define PBE_IEEE_RAM_O_FFOPT1                                        0x00000080U

// 
#define PBE_IEEE_RAM_O_TMPRSSI                                       0x00000082U

// 
#define PBE_IEEE_RAM_O_ENTRYENABLE00                                 0x00000084U

// 
#define PBE_IEEE_RAM_O_ENTRYENABLE01                                 0x00000086U

// 
#define PBE_IEEE_RAM_O_ENTRYENABLE02                                 0x00000088U

// 
#define PBE_IEEE_RAM_O_ENTRYENABLE03                                 0x0000008AU

// 
#define PBE_IEEE_RAM_O_FRAMEPENDING00                                0x0000008CU

// 
#define PBE_IEEE_RAM_O_FRAMEPENDING01                                0x0000008EU

// 
#define PBE_IEEE_RAM_O_FRAMEPENDING02                                0x00000090U

// 
#define PBE_IEEE_RAM_O_FRAMEPENDING03                                0x00000092U

// 
#define PBE_IEEE_RAM_O_ENTRYENABLE10                                 0x00000094U

// 
#define PBE_IEEE_RAM_O_ENTRYENABLE11                                 0x00000096U

// 
#define PBE_IEEE_RAM_O_ENTRYENABLE12                                 0x00000098U

// 
#define PBE_IEEE_RAM_O_ENTRYENABLE13                                 0x0000009AU

// 
#define PBE_IEEE_RAM_O_FRAMEPENDING10                                0x0000009CU

// 
#define PBE_IEEE_RAM_O_FRAMEPENDING11                                0x0000009EU

// 
#define PBE_IEEE_RAM_O_FRAMEPENDING12                                0x000000A0U

// 
#define PBE_IEEE_RAM_O_FRAMEPENDING13                                0x000000A2U

// 
#define PBE_IEEE_RAM_O_PANCFGED                                      0x000000A4U

// 
#define PBE_IEEE_RAM_O_TMPFCF                                        0x000000A6U

// 
#define PBE_IEEE_RAM_O_CFGAUTOACK                                    0x000000A8U

// 
#define PBE_IEEE_RAM_O_MACCMDID                                      0x000000AAU

// 
#define PBE_IEEE_RAM_O_ACKSTATUS                                     0x000000ACU

// 
#define PBE_IEEE_RAM_O_CORRCNT                                       0x000000AEU

// 
#define PBE_IEEE_RAM_O_COEXCORRMASK                                  0x000000B0U

// 
#define PBE_IEEE_RAM_O_TSYNC                                         0x000000B2U

// 
#define PBE_IEEE_RAM_O_COEXT1                                        0x000000B4U

// 
#define PBE_IEEE_RAM_O_COEXT2                                        0x000000B6U

// 
#define PBE_IEEE_RAM_O_COEXCFG                                       0x000000B8U

// 
#define PBE_IEEE_RAM_O_EXTSRCADDRTBL                                 0x000000BAU

// 
#define PBE_IEEE_RAM_O_MATCHIDXFILT                                  0x000000BCU

// 
#define PBE_IEEE_RAM_O_PAN0_SRC_MATCH_SHORT_START                    0x00000104U

// 
#define PBE_IEEE_RAM_O_PAN0_SRC_MATCH_EXT_START                      0x00000184U

// 
#define PBE_IEEE_RAM_O_PAN1_SRC_MATCH_SHORT_START                    0x00000204U

// 
#define PBE_IEEE_RAM_O_PAN1_SRC_MATCH_EXT_START                      0x00000284U

//******************************************************************************
// Register: SYNTHCALTIMEOUT
//******************************************************************************
// Field: [15:0] val
//
// SynthCal timeout in 0.25us unit. 0 means infinite (no timeout)
#define PBE_IEEE_RAM_SYNTHCALTIMEOUT_VAL_W                                   16U
#define PBE_IEEE_RAM_SYNTHCALTIMEOUT_VAL_M                               0xFFFFU
#define PBE_IEEE_RAM_SYNTHCALTIMEOUT_VAL_S                                    0U

//******************************************************************************
// Register: FIFOCFG
//******************************************************************************
// Field: [15:15] appendtimestamp
//
// Append 16 bit TIMESTAMP
#define PBE_IEEE_RAM_FIFOCFG_APPENDTIMESTAMP                             0x8000U
#define PBE_IEEE_RAM_FIFOCFG_APPENDTIMESTAMP_M                           0x8000U
#define PBE_IEEE_RAM_FIFOCFG_APPENDTIMESTAMP_S                               15U

// Field: [14:14] appendrssi
//
// Append 8 bit RSSI
#define PBE_IEEE_RAM_FIFOCFG_APPENDRSSI                                  0x4000U
#define PBE_IEEE_RAM_FIFOCFG_APPENDRSSI_M                                0x4000U
#define PBE_IEEE_RAM_FIFOCFG_APPENDRSSI_S                                    14U

// Field: [12:12] appendlqi
//
// Append 8 bit Modem LQI estimate (Frequency offset)
#define PBE_IEEE_RAM_FIFOCFG_APPENDLQI                                   0x1000U
#define PBE_IEEE_RAM_FIFOCFG_APPENDLQI_M                                 0x1000U
#define PBE_IEEE_RAM_FIFOCFG_APPENDLQI_S                                     12U

// Field: [11:11] appendstatus
//
// Append 8 bit status from STATUSBYTE
#define PBE_IEEE_RAM_FIFOCFG_APPENDSTATUS                                0x0800U
#define PBE_IEEE_RAM_FIFOCFG_APPENDSTATUS_M                              0x0800U
#define PBE_IEEE_RAM_FIFOCFG_APPENDSTATUS_S                                  11U

// Field: [10:10] appendcrc
//
// Append all received crc bits
#define PBE_IEEE_RAM_FIFOCFG_APPENDCRC                                   0x0400U
#define PBE_IEEE_RAM_FIFOCFG_APPENDCRC_M                                 0x0400U
#define PBE_IEEE_RAM_FIFOCFG_APPENDCRC_S                                     10U

// Field: [8:8] autoflushign
//
// Automatically removes packets than can be ignored according to the frame filtering in Rx queue.
#define PBE_IEEE_RAM_FIFOCFG_AUTOFLUSHIGN                                0x0100U
#define PBE_IEEE_RAM_FIFOCFG_AUTOFLUSHIGN_M                              0x0100U
#define PBE_IEEE_RAM_FIFOCFG_AUTOFLUSHIGN_S                                   8U
#define PBE_IEEE_RAM_FIFOCFG_AUTOFLUSHIGN_KEEP                           0x0000U
#define PBE_IEEE_RAM_FIFOCFG_AUTOFLUSHIGN_FLUSH                          0x0100U

// Field: [7:7] autoflushcrc
//
// Automatically removes packets with CRC error from the Rx queue.
#define PBE_IEEE_RAM_FIFOCFG_AUTOFLUSHCRC                                0x0080U
#define PBE_IEEE_RAM_FIFOCFG_AUTOFLUSHCRC_M                              0x0080U
#define PBE_IEEE_RAM_FIFOCFG_AUTOFLUSHCRC_S                                   7U
#define PBE_IEEE_RAM_FIFOCFG_AUTOFLUSHCRC_KEEP                           0x0000U
#define PBE_IEEE_RAM_FIFOCFG_AUTOFLUSHCRC_FLUSH                          0x0080U

//******************************************************************************
// Register: EXTRABYTES
//******************************************************************************
// Field: [15:0] val
//
// Indicates how many bytes that are required after the PDU to hold the statuses configured in FIFOCFG.
#define PBE_IEEE_RAM_EXTRABYTES_VAL_W                                        16U
#define PBE_IEEE_RAM_EXTRABYTES_VAL_M                                    0xFFFFU
#define PBE_IEEE_RAM_EXTRABYTES_VAL_S                                         0U

//******************************************************************************
// Register: PRETXIFS
//******************************************************************************
// Field: [15:0] val
//
// Base value used after RX to set timer0 for when to start Transmission.
#define PBE_IEEE_RAM_PRETXIFS_VAL_W                                          16U
#define PBE_IEEE_RAM_PRETXIFS_VAL_M                                      0xFFFFU
#define PBE_IEEE_RAM_PRETXIFS_VAL_S                                           0U

//******************************************************************************
// Register: PRERXIFS
//******************************************************************************
// Field: [15:0] val
//
// Base value used after TX to set timer0 for when to start Receiving.
#define PBE_IEEE_RAM_PRERXIFS_VAL_W                                          16U
#define PBE_IEEE_RAM_PRERXIFS_VAL_M                                      0xFFFFU
#define PBE_IEEE_RAM_PRERXIFS_VAL_S                                           0U

//******************************************************************************
// Register: PRETXIFSV2
//******************************************************************************
// Field: [15:0] val
//
// Base value used after RX, for frame version 2, to set timer0 for when to start Transmission.
#define PBE_IEEE_RAM_PRETXIFSV2_VAL_W                                        16U
#define PBE_IEEE_RAM_PRETXIFSV2_VAL_M                                    0xFFFFU
#define PBE_IEEE_RAM_PRETXIFSV2_VAL_S                                         0U

//******************************************************************************
// Register: PILOTLEN
//******************************************************************************
// Field: [15:0] val
//
// Pilot tone length expressed in 0.25 µs
#define PBE_IEEE_RAM_PILOTLEN_VAL_W                                          16U
#define PBE_IEEE_RAM_PILOTLEN_VAL_M                                      0xFFFFU
#define PBE_IEEE_RAM_PILOTLEN_VAL_S                                           0U

//******************************************************************************
// Register: RXTIMEOUT
//******************************************************************************
// Field: [15:0] val
//
// RX timeout in 0.25us unit. 0 means infinite (no timeout)
#define PBE_IEEE_RAM_RXTIMEOUT_VAL_W                                         16U
#define PBE_IEEE_RAM_RXTIMEOUT_VAL_M                                     0xFFFFU
#define PBE_IEEE_RAM_RXTIMEOUT_VAL_S                                          0U

//******************************************************************************
// Register: OPCFG
//******************************************************************************
// Field: [14:14] systim0beh
//
// Treatment of systim0 during operation
#define PBE_IEEE_RAM_OPCFG_SYSTIM0BEH                                    0x4000U
#define PBE_IEEE_RAM_OPCFG_SYSTIM0BEH_M                                  0x4000U
#define PBE_IEEE_RAM_OPCFG_SYSTIM0BEH_S                                      14U
#define PBE_IEEE_RAM_OPCFG_SYSTIM0BEH_NORMAL                             0x0000U
#define PBE_IEEE_RAM_OPCFG_SYSTIM0BEH_IGNORE                             0x4000U

// Field: [13:13] stop
//
// Rejected frame behaviour
#define PBE_IEEE_RAM_OPCFG_STOP                                          0x2000U
#define PBE_IEEE_RAM_OPCFG_STOP_M                                        0x2000U
#define PBE_IEEE_RAM_OPCFG_STOP_S                                            13U
#define PBE_IEEE_RAM_OPCFG_STOP_SOFTEND                                  0x0000U
#define PBE_IEEE_RAM_OPCFG_STOP_HARDEND                                  0x2000U

// Field: [12:12] rxrepeatok
//
// Rule for what to do after packets with correct CRC
#define PBE_IEEE_RAM_OPCFG_RXREPEATOK                                    0x1000U
#define PBE_IEEE_RAM_OPCFG_RXREPEATOK_M                                  0x1000U
#define PBE_IEEE_RAM_OPCFG_RXREPEATOK_S                                      12U
#define PBE_IEEE_RAM_OPCFG_RXREPEATOK_YES                                0x0000U
#define PBE_IEEE_RAM_OPCFG_RXREPEATOK_NO                                 0x1000U

// Field: [11:11] rxrepeatnok
//
// Rule for what to do after packets with CRC error or address mismatch.
#define PBE_IEEE_RAM_OPCFG_RXREPEATNOK                                   0x0800U
#define PBE_IEEE_RAM_OPCFG_RXREPEATNOK_M                                 0x0800U
#define PBE_IEEE_RAM_OPCFG_RXREPEATNOK_S                                     11U
#define PBE_IEEE_RAM_OPCFG_RXREPEATNOK_NO                                0x0000U
#define PBE_IEEE_RAM_OPCFG_RXREPEATNOK_YES                               0x0800U

// Field: [10:10] txinfinite
//
// Infinite TX control
#define PBE_IEEE_RAM_OPCFG_TXINFINITE                                    0x0400U
#define PBE_IEEE_RAM_OPCFG_TXINFINITE_M                                  0x0400U
#define PBE_IEEE_RAM_OPCFG_TXINFINITE_S                                      10U
#define PBE_IEEE_RAM_OPCFG_TXINFINITE_NO                                 0x0000U
#define PBE_IEEE_RAM_OPCFG_TXINFINITE_YES                                0x0400U

// Field: [9:9] txpattern
//
// Send fixed pattern
#define PBE_IEEE_RAM_OPCFG_TXPATTERN                                     0x0200U
#define PBE_IEEE_RAM_OPCFG_TXPATTERN_M                                   0x0200U
#define PBE_IEEE_RAM_OPCFG_TXPATTERN_S                                        9U
#define PBE_IEEE_RAM_OPCFG_TXPATTERN_NO                                  0x0000U
#define PBE_IEEE_RAM_OPCFG_TXPATTERN_YES                                 0x0200U

// Field: [8:7] txfcmd
//
// Rule for FCMD after TX_DONE
#define PBE_IEEE_RAM_OPCFG_TXFCMD_W                                           2U
#define PBE_IEEE_RAM_OPCFG_TXFCMD_M                                      0x0180U
#define PBE_IEEE_RAM_OPCFG_TXFCMD_S                                           7U
#define PBE_IEEE_RAM_OPCFG_TXFCMD_NONE                                   0x0000U
#define PBE_IEEE_RAM_OPCFG_TXFCMD_RETRY                                  0x0080U
#define PBE_IEEE_RAM_OPCFG_TXFCMD_DEALLOC                                0x0100U

// Field: [6:6] start
//
// Rule for start od operation
#define PBE_IEEE_RAM_OPCFG_START                                         0x0040U
#define PBE_IEEE_RAM_OPCFG_START_M                                       0x0040U
#define PBE_IEEE_RAM_OPCFG_START_S                                            6U
#define PBE_IEEE_RAM_OPCFG_START_SYNC                                    0x0000U
#define PBE_IEEE_RAM_OPCFG_START_ASYNC                                   0x0040U

// Field: [3:3] nextop
//
// Enable automatic RX/TX switching, does nothing if OPCFG_SINGLE is selected. This is a feature not used currently.
#define PBE_IEEE_RAM_OPCFG_NEXTOP                                        0x0008U
#define PBE_IEEE_RAM_OPCFG_NEXTOP_M                                      0x0008U
#define PBE_IEEE_RAM_OPCFG_NEXTOP_S                                           3U
#define PBE_IEEE_RAM_OPCFG_NEXTOP_SWITCH                                 0x0000U
#define PBE_IEEE_RAM_OPCFG_NEXTOP_SAME                                   0x0008U

// Field: [2:2] single
//
// Only one shall be high of SINGLE or IFSPERIOD.
#define PBE_IEEE_RAM_OPCFG_SINGLE                                        0x0004U
#define PBE_IEEE_RAM_OPCFG_SINGLE_M                                      0x0004U
#define PBE_IEEE_RAM_OPCFG_SINGLE_S                                           2U
#define PBE_IEEE_RAM_OPCFG_SINGLE_DIS                                    0x0000U
#define PBE_IEEE_RAM_OPCFG_SINGLE_EN                                     0x0004U

// Field: [1:1] ifsperiod
//
// Only one shall be high of SINGLE or IFSPERIOD.
#define PBE_IEEE_RAM_OPCFG_IFSPERIOD                                     0x0002U
#define PBE_IEEE_RAM_OPCFG_IFSPERIOD_M                                   0x0002U
#define PBE_IEEE_RAM_OPCFG_IFSPERIOD_S                                        1U
#define PBE_IEEE_RAM_OPCFG_IFSPERIOD_DIS                                 0x0000U
#define PBE_IEEE_RAM_OPCFG_IFSPERIOD_EN                                  0x0002U

// Field: [0:0] rsvd0
//
// Reserved bitfield
#define PBE_IEEE_RAM_OPCFG_RSVD0                                         0x0001U
#define PBE_IEEE_RAM_OPCFG_RSVD0_M                                       0x0001U
#define PBE_IEEE_RAM_OPCFG_RSVD0_S                                            0U
#define PBE_IEEE_RAM_OPCFG_RSVD0_DIS                                     0x0000U
#define PBE_IEEE_RAM_OPCFG_RSVD0_EN                                      0x0001U

//******************************************************************************
// Register: PATTERN
//******************************************************************************
// Field: [15:0] val
//
// Data to send if OPCFG.TXPATTERN is 1
#define PBE_IEEE_RAM_PATTERN_VAL_W                                           16U
#define PBE_IEEE_RAM_PATTERN_VAL_M                                       0xFFFFU
#define PBE_IEEE_RAM_PATTERN_VAL_S                                            0U

//******************************************************************************
// Register: WHITEINIT
//******************************************************************************
// Field: [15:0] val
//
// Whitener initialization value
#define PBE_IEEE_RAM_WHITEINIT_VAL_W                                         16U
#define PBE_IEEE_RAM_WHITEINIT_VAL_M                                     0xFFFFU
#define PBE_IEEE_RAM_WHITEINIT_VAL_S                                          0U

//******************************************************************************
// Register: PIB
//******************************************************************************
// Field: [1:0] panmode
//
// PAN Information Base sw register
#define PBE_IEEE_RAM_PIB_PANMODE_W                                            2U
#define PBE_IEEE_RAM_PIB_PANMODE_M                                       0x0003U
#define PBE_IEEE_RAM_PIB_PANMODE_S                                            0U
#define PBE_IEEE_RAM_PIB_PANMODE_PROMISCUOUS                             0x0000U
#define PBE_IEEE_RAM_PIB_PANMODE_SINGLE                                  0x0001U
#define PBE_IEEE_RAM_PIB_PANMODE_DUAL                                    0x0002U

//******************************************************************************
// Register: FFTYPE
//******************************************************************************
// Field: [15:15] extended1
//
// Treatment of frames with frame type 111 (Extended) (NOT supported)
#define PBE_IEEE_RAM_FFTYPE_EXTENDED1                                    0x8000U
#define PBE_IEEE_RAM_FFTYPE_EXTENDED1_M                                  0x8000U
#define PBE_IEEE_RAM_FFTYPE_EXTENDED1_S                                      15U

// Field: [14:14] frag1
//
// Treatment of frames with frame type 110 (Fragment) (NOT supported)
#define PBE_IEEE_RAM_FFTYPE_FRAG1                                        0x4000U
#define PBE_IEEE_RAM_FFTYPE_FRAG1_M                                      0x4000U
#define PBE_IEEE_RAM_FFTYPE_FRAG1_S                                          14U

// Field: [13:13] multi1
//
// Treatment of frames with frame type 101 (Multipurpose) (NOT supported)
#define PBE_IEEE_RAM_FFTYPE_MULTI1                                       0x2000U
#define PBE_IEEE_RAM_FFTYPE_MULTI1_M                                     0x2000U
#define PBE_IEEE_RAM_FFTYPE_MULTI1_S                                         13U

// Field: [12:12] reserved1
//
// Treatment of frames with frame type 100 (reserved) (NOT supported)
#define PBE_IEEE_RAM_FFTYPE_RESERVED1                                    0x1000U
#define PBE_IEEE_RAM_FFTYPE_RESERVED1_M                                  0x1000U
#define PBE_IEEE_RAM_FFTYPE_RESERVED1_S                                      12U

// Field: [11:11] maccmd1
//
// Treatment of frames with frame type 011 (MAC command)
#define PBE_IEEE_RAM_FFTYPE_MACCMD1                                      0x0800U
#define PBE_IEEE_RAM_FFTYPE_MACCMD1_M                                    0x0800U
#define PBE_IEEE_RAM_FFTYPE_MACCMD1_S                                        11U

// Field: [10:10] ack1
//
// Treatment of frames with frame type 010 (ACK)
#define PBE_IEEE_RAM_FFTYPE_ACK1                                         0x0400U
#define PBE_IEEE_RAM_FFTYPE_ACK1_M                                       0x0400U
#define PBE_IEEE_RAM_FFTYPE_ACK1_S                                           10U
#define PBE_IEEE_RAM_FFTYPE_ACK1_ACCEPT                                  0x0400U

// Field: [9:9] data1
//
// Treatment of frames with frame type 001 (data)
#define PBE_IEEE_RAM_FFTYPE_DATA1                                        0x0200U
#define PBE_IEEE_RAM_FFTYPE_DATA1_M                                      0x0200U
#define PBE_IEEE_RAM_FFTYPE_DATA1_S                                           9U

// Field: [8:8] beacon1
//
// Treatment of frames with frame type 000 (beacon)
#define PBE_IEEE_RAM_FFTYPE_BEACON1                                      0x0100U
#define PBE_IEEE_RAM_FFTYPE_BEACON1_M                                    0x0100U
#define PBE_IEEE_RAM_FFTYPE_BEACON1_S                                         8U

// Field: [7:7] extended0
//
// Treatment of frames with frame type 111 (Extended) (NOT supported)
#define PBE_IEEE_RAM_FFTYPE_EXTENDED0                                    0x0080U
#define PBE_IEEE_RAM_FFTYPE_EXTENDED0_M                                  0x0080U
#define PBE_IEEE_RAM_FFTYPE_EXTENDED0_S                                       7U

// Field: [6:6] frag0
//
// Treatment of frames with frame type 110 (Fragment) (NOT supported)
#define PBE_IEEE_RAM_FFTYPE_FRAG0                                        0x0040U
#define PBE_IEEE_RAM_FFTYPE_FRAG0_M                                      0x0040U
#define PBE_IEEE_RAM_FFTYPE_FRAG0_S                                           6U

// Field: [5:5] multi0
//
// Treatment of frames with frame type 101 (Multipurpose) (NOT supported)
#define PBE_IEEE_RAM_FFTYPE_MULTI0                                       0x0020U
#define PBE_IEEE_RAM_FFTYPE_MULTI0_M                                     0x0020U
#define PBE_IEEE_RAM_FFTYPE_MULTI0_S                                          5U

// Field: [4:4] reserved0
//
// Treatment of frames with frame type 100 (reserved) (NOT supported)
#define PBE_IEEE_RAM_FFTYPE_RESERVED0                                    0x0010U
#define PBE_IEEE_RAM_FFTYPE_RESERVED0_M                                  0x0010U
#define PBE_IEEE_RAM_FFTYPE_RESERVED0_S                                       4U

// Field: [3:3] maccmd0
//
// Treatment of frames with frame type 011 (MAC command)
#define PBE_IEEE_RAM_FFTYPE_MACCMD0                                      0x0008U
#define PBE_IEEE_RAM_FFTYPE_MACCMD0_M                                    0x0008U
#define PBE_IEEE_RAM_FFTYPE_MACCMD0_S                                         3U

// Field: [2:2] ack0
//
// Treatment of frames with frame type 010 (ACK)
#define PBE_IEEE_RAM_FFTYPE_ACK0                                         0x0004U
#define PBE_IEEE_RAM_FFTYPE_ACK0_M                                       0x0004U
#define PBE_IEEE_RAM_FFTYPE_ACK0_S                                            2U
#define PBE_IEEE_RAM_FFTYPE_ACK0_ACCEPT                                  0x0004U

// Field: [1:1] data0
//
// Treatment of frames with frame type 001 (data)
#define PBE_IEEE_RAM_FFTYPE_DATA0                                        0x0002U
#define PBE_IEEE_RAM_FFTYPE_DATA0_M                                      0x0002U
#define PBE_IEEE_RAM_FFTYPE_DATA0_S                                           1U

// Field: [0:0] beacon0
//
// Treatment of frames with frame type 000 (beacon)
#define PBE_IEEE_RAM_FFTYPE_BEACON0                                      0x0001U
#define PBE_IEEE_RAM_FFTYPE_BEACON0_M                                    0x0001U
#define PBE_IEEE_RAM_FFTYPE_BEACON0_S                                         0U

//******************************************************************************
// Register: NRXNOK
//******************************************************************************
// Field: [15:0] val
//
// Number of packets received with CRC error
#define PBE_IEEE_RAM_NRXNOK_VAL_W                                            16U
#define PBE_IEEE_RAM_NRXNOK_VAL_M                                        0xFFFFU
#define PBE_IEEE_RAM_NRXNOK_VAL_S                                             0U

//******************************************************************************
// Register: NRXIGNORED
//******************************************************************************
// Field: [15:0] val
//
// Number of packets received with CRC OK, but to be ignored by the MCU
#define PBE_IEEE_RAM_NRXIGNORED_VAL_W                                        16U
#define PBE_IEEE_RAM_NRXIGNORED_VAL_M                                    0xFFFFU
#define PBE_IEEE_RAM_NRXIGNORED_VAL_S                                         0U

//******************************************************************************
// Register: NTXENHACK
//******************************************************************************
// Field: [15:0] val
//
// Number of transmitted enh-ack frames. This register was renamed from NRXEMPTY.
#define PBE_IEEE_RAM_NTXENHACK_VAL_W                                         16U
#define PBE_IEEE_RAM_NTXENHACK_VAL_M                                     0xFFFFU
#define PBE_IEEE_RAM_NTXENHACK_VAL_S                                          0U

//******************************************************************************
// Register: NRXFIFOFULL
//******************************************************************************
// Field: [15:0] val
//
// Number of received packets discarded because the Rx FIFO was full
#define PBE_IEEE_RAM_NRXFIFOFULL_VAL_W                                       16U
#define PBE_IEEE_RAM_NRXFIFOFULL_VAL_M                                   0xFFFFU
#define PBE_IEEE_RAM_NRXFIFOFULL_VAL_S                                        0U

//******************************************************************************
// Register: NRXOK
//******************************************************************************
// Field: [15:0] val
//
// Number of non-empty packets received with CRC OK and not  to be ignored by the MCU
#define PBE_IEEE_RAM_NRXOK_VAL_W                                             16U
#define PBE_IEEE_RAM_NRXOK_VAL_M                                         0xFFFFU
#define PBE_IEEE_RAM_NRXOK_VAL_S                                              0U

//******************************************************************************
// Register: NTX
//******************************************************************************
// Field: [15:0] val
//
// Number of transmitted packets,incremented for every transmitted packet
#define PBE_IEEE_RAM_NTX_VAL_W                                               16U
#define PBE_IEEE_RAM_NTX_VAL_M                                           0xFFFFU
#define PBE_IEEE_RAM_NTX_VAL_S                                                0U

//******************************************************************************
// Register: NTXACK
//******************************************************************************
// Field: [15:0] val
//
// Number of Imm-Ack transmitted packets, from auto-ack mode,incremented for every transmitted packet
#define PBE_IEEE_RAM_NTXACK_VAL_W                                            16U
#define PBE_IEEE_RAM_NTXACK_VAL_M                                        0xFFFFU
#define PBE_IEEE_RAM_NTXACK_VAL_S                                             0U

//******************************************************************************
// Register: NRXTIMEOUT
//******************************************************************************
// Field: [15:0] val
//
// Number of RX timeout
#define PBE_IEEE_RAM_NRXTIMEOUT_VAL_W                                        16U
#define PBE_IEEE_RAM_NRXTIMEOUT_VAL_M                                    0xFFFFU
#define PBE_IEEE_RAM_NRXTIMEOUT_VAL_S                                         0U

//******************************************************************************
// Register: LASTRSSI
//******************************************************************************
// Field: [15:0] val
//
// RSSI of last received packet with crc OK
#define PBE_IEEE_RAM_LASTRSSI_VAL_W                                          16U
#define PBE_IEEE_RAM_LASTRSSI_VAL_M                                      0xFFFFU
#define PBE_IEEE_RAM_LASTRSSI_VAL_S                                           0U

//******************************************************************************
// Register: LASTFREQOFF
//******************************************************************************
// Field: [15:0] val
//
// FREQOFF of last received packet with crc OK
#define PBE_IEEE_RAM_LASTFREQOFF_VAL_W                                       16U
#define PBE_IEEE_RAM_LASTFREQOFF_VAL_M                                   0xFFFFU
#define PBE_IEEE_RAM_LASTFREQOFF_VAL_S                                        0U

//******************************************************************************
// Register: LASTLQI
//******************************************************************************
// Field: [15:0] val
//
// LQI of last received packet with crc OK
#define PBE_IEEE_RAM_LASTLQI_VAL_W                                           16U
#define PBE_IEEE_RAM_LASTLQI_VAL_M                                       0xFFFFU
#define PBE_IEEE_RAM_LASTLQI_VAL_S                                            0U

//******************************************************************************
// Register: LASTTIMESTAMPL
//******************************************************************************
// Field: [15:0] val
//
// Lower part of timestamp.
#define PBE_IEEE_RAM_LASTTIMESTAMPL_VAL_W                                    16U
#define PBE_IEEE_RAM_LASTTIMESTAMPL_VAL_M                                0xFFFFU
#define PBE_IEEE_RAM_LASTTIMESTAMPL_VAL_S                                     0U

//******************************************************************************
// Register: LASTTIMESTAMPH
//******************************************************************************
// Field: [15:0] val
//
// Upper part of timestamp.
#define PBE_IEEE_RAM_LASTTIMESTAMPH_VAL_W                                    16U
#define PBE_IEEE_RAM_LASTTIMESTAMPH_VAL_M                                0xFFFFU
#define PBE_IEEE_RAM_LASTTIMESTAMPH_VAL_S                                     0U

//******************************************************************************
// Register: RXSTATUS
//******************************************************************************
// Field: [2:2] txinprogress
//
// Status of frame transmission
#define PBE_IEEE_RAM_RXSTATUS_TXINPROGRESS                               0x0004U
#define PBE_IEEE_RAM_RXSTATUS_TXINPROGRESS_M                             0x0004U
#define PBE_IEEE_RAM_RXSTATUS_TXINPROGRESS_S                                  2U
#define PBE_IEEE_RAM_RXSTATUS_TXINPROGRESS_IDLE                          0x0000U
#define PBE_IEEE_RAM_RXSTATUS_TXINPROGRESS_TX                            0x0004U

// Field: [1:1] txackinprogress
//
// Status of auto ACK transmission
#define PBE_IEEE_RAM_RXSTATUS_TXACKINPROGRESS                            0x0002U
#define PBE_IEEE_RAM_RXSTATUS_TXACKINPROGRESS_M                          0x0002U
#define PBE_IEEE_RAM_RXSTATUS_TXACKINPROGRESS_S                               1U
#define PBE_IEEE_RAM_RXSTATUS_TXACKINPROGRESS_IDLE                       0x0000U
#define PBE_IEEE_RAM_RXSTATUS_TXACKINPROGRESS_TXACK                      0x0002U

// Field: [0:0] frameinprogress
//
// Status of frame reception
#define PBE_IEEE_RAM_RXSTATUS_FRAMEINPROGRESS                            0x0001U
#define PBE_IEEE_RAM_RXSTATUS_FRAMEINPROGRESS_M                          0x0001U
#define PBE_IEEE_RAM_RXSTATUS_FRAMEINPROGRESS_S                               0U
#define PBE_IEEE_RAM_RXSTATUS_FRAMEINPROGRESS_IDLE                       0x0000U
#define PBE_IEEE_RAM_RXSTATUS_FRAMEINPROGRESS_FRAME                      0x0001U

//******************************************************************************
// Register: TMPREG1
//******************************************************************************
// Field: [15:0] val
//
// Value can be anything is necessary to be stored temporary
#define PBE_IEEE_RAM_TMPREG1_VAL_W                                           16U
#define PBE_IEEE_RAM_TMPREG1_VAL_M                                       0xFFFFU
#define PBE_IEEE_RAM_TMPREG1_VAL_S                                            0U

//******************************************************************************
// Register: TMPREG2
//******************************************************************************
// Field: [15:0] val
//
// Value can be anything is necessary to be stored temporary
#define PBE_IEEE_RAM_TMPREG2_VAL_W                                           16U
#define PBE_IEEE_RAM_TMPREG2_VAL_M                                       0xFFFFU
#define PBE_IEEE_RAM_TMPREG2_VAL_S                                            0U

//******************************************************************************
// Register: TMPREG3
//******************************************************************************
// Field: [15:0] val
//
// Value can be anything is necessary to be stored temporary
#define PBE_IEEE_RAM_TMPREG3_VAL_W                                           16U
#define PBE_IEEE_RAM_TMPREG3_VAL_M                                       0xFFFFU
#define PBE_IEEE_RAM_TMPREG3_VAL_S                                            0U

//******************************************************************************
// Register: TMPREG4
//******************************************************************************
// Field: [15:0] val
//
// Value can be anything is necessary to be stored temporary
#define PBE_IEEE_RAM_TMPREG4_VAL_W                                           16U
#define PBE_IEEE_RAM_TMPREG4_VAL_M                                       0xFFFFU
#define PBE_IEEE_RAM_TMPREG4_VAL_S                                            0U

//******************************************************************************
// Register: LSEQNR
//******************************************************************************
// Field: [7:0] val
//
// Last decoded sequence number
#define PBE_IEEE_RAM_LSEQNR_VAL_W                                             8U
#define PBE_IEEE_RAM_LSEQNR_VAL_M                                        0x00FFU
#define PBE_IEEE_RAM_LSEQNR_VAL_S                                             0U

//******************************************************************************
// Register: SRCMATCHIDX
//******************************************************************************
// Field: [7:0] tblidx
//
// Store the index from the src table for which there was a match with the src field of the received frame
#define PBE_IEEE_RAM_SRCMATCHIDX_TBLIDX_W                                     8U
#define PBE_IEEE_RAM_SRCMATCHIDX_TBLIDX_M                                0x00FFU
#define PBE_IEEE_RAM_SRCMATCHIDX_TBLIDX_S                                     0U

//******************************************************************************
// Register: PANID0
//******************************************************************************
// Field: [15:0] val
//
// Local PAN ID0
#define PBE_IEEE_RAM_PANID0_VAL_W                                            16U
#define PBE_IEEE_RAM_PANID0_VAL_M                                        0xFFFFU
#define PBE_IEEE_RAM_PANID0_VAL_S                                             0U

//******************************************************************************
// Register: SHORTADDR0
//******************************************************************************
// Field: [15:0] val
//
// Local PAN ID0 short address
#define PBE_IEEE_RAM_SHORTADDR0_VAL_W                                        16U
#define PBE_IEEE_RAM_SHORTADDR0_VAL_M                                    0xFFFFU
#define PBE_IEEE_RAM_SHORTADDR0_VAL_S                                         0U

//******************************************************************************
// Register: EXTADDR00
//******************************************************************************
// Field: [15:0] val
//
// Local PAN ID0 extended address, bits 15:0
#define PBE_IEEE_RAM_EXTADDR00_VAL_W                                         16U
#define PBE_IEEE_RAM_EXTADDR00_VAL_M                                     0xFFFFU
#define PBE_IEEE_RAM_EXTADDR00_VAL_S                                          0U

//******************************************************************************
// Register: EXTADDR01
//******************************************************************************
// Field: [15:0] val
//
// Local PAN ID0 extended address, bits 31:16
#define PBE_IEEE_RAM_EXTADDR01_VAL_W                                         16U
#define PBE_IEEE_RAM_EXTADDR01_VAL_M                                     0xFFFFU
#define PBE_IEEE_RAM_EXTADDR01_VAL_S                                          0U

//******************************************************************************
// Register: EXTADDR02
//******************************************************************************
// Field: [15:0] val
//
// Local PAN ID0 extended address, bits 47:32
#define PBE_IEEE_RAM_EXTADDR02_VAL_W                                         16U
#define PBE_IEEE_RAM_EXTADDR02_VAL_M                                     0xFFFFU
#define PBE_IEEE_RAM_EXTADDR02_VAL_S                                          0U

//******************************************************************************
// Register: EXTADDR03
//******************************************************************************
// Field: [15:0] val
//
// Local PAN ID0 extended address, bits 63:48
#define PBE_IEEE_RAM_EXTADDR03_VAL_W                                         16U
#define PBE_IEEE_RAM_EXTADDR03_VAL_M                                     0xFFFFU
#define PBE_IEEE_RAM_EXTADDR03_VAL_S                                          0U

//******************************************************************************
// Register: FFOPT0
//******************************************************************************
// Field: [9:8] maxframe
//
// Reject frames where the frame version field in the FCF is greater than this value
#define PBE_IEEE_RAM_FFOPT0_MAXFRAME_W                                        2U
#define PBE_IEEE_RAM_FFOPT0_MAXFRAME_M                                   0x0300U
#define PBE_IEEE_RAM_FFOPT0_MAXFRAME_S                                        8U

// Field: [7:7] pancoord
//
// 
#define PBE_IEEE_RAM_FFOPT0_PANCOORD                                     0x0080U
#define PBE_IEEE_RAM_FFOPT0_PANCOORD_M                                   0x0080U
#define PBE_IEEE_RAM_FFOPT0_PANCOORD_S                                        7U
#define PBE_IEEE_RAM_FFOPT0_PANCOORD_DISABLED                            0x0000U
#define PBE_IEEE_RAM_FFOPT0_PANCOORD_EN                                  0x0080U

// Field: [6:6] preqonly
//
// 
#define PBE_IEEE_RAM_FFOPT0_PREQONLY                                     0x0040U
#define PBE_IEEE_RAM_FFOPT0_PREQONLY_M                                   0x0040U
#define PBE_IEEE_RAM_FFOPT0_PREQONLY_S                                        6U
#define PBE_IEEE_RAM_FFOPT0_PREQONLY_ANY                                 0x0000U
#define PBE_IEEE_RAM_FFOPT0_PREQONLY_DATAREQ                             0x0040U

// Field: [5:5] defpend
//
// The value of the pending data bit in auto ACK packets that are not subject to auto-pend
#define PBE_IEEE_RAM_FFOPT0_DEFPEND                                      0x0020U
#define PBE_IEEE_RAM_FFOPT0_DEFPEND_M                                    0x0020U
#define PBE_IEEE_RAM_FFOPT0_DEFPEND_S                                         5U

// Field: [4:4] autopend
//
// 
#define PBE_IEEE_RAM_FFOPT0_AUTOPEND                                     0x0010U
#define PBE_IEEE_RAM_FFOPT0_AUTOPEND_M                                   0x0010U
#define PBE_IEEE_RAM_FFOPT0_AUTOPEND_S                                        4U
#define PBE_IEEE_RAM_FFOPT0_AUTOPEND_DISABLE                             0x0000U
#define PBE_IEEE_RAM_FFOPT0_AUTOPEND_EN                                  0x0010U

// Field: [2:2] autoack
//
// 
#define PBE_IEEE_RAM_FFOPT0_AUTOACK                                      0x0004U
#define PBE_IEEE_RAM_FFOPT0_AUTOACK_M                                    0x0004U
#define PBE_IEEE_RAM_FFOPT0_AUTOACK_S                                         2U
#define PBE_IEEE_RAM_FFOPT0_AUTOACK_DISABLE                              0x0000U
#define PBE_IEEE_RAM_FFOPT0_AUTOACK_EN                                   0x0004U

// Field: [1:1] immacksel
//
// Select from where the imm-ack frame will be taken for PAN0
#define PBE_IEEE_RAM_FFOPT0_IMMACKSEL                                    0x0002U
#define PBE_IEEE_RAM_FFOPT0_IMMACKSEL_M                                  0x0002U
#define PBE_IEEE_RAM_FFOPT0_IMMACKSEL_S                                       1U
#define PBE_IEEE_RAM_FFOPT0_IMMACKSEL_PBE                                0x0000U
#define PBE_IEEE_RAM_FFOPT0_IMMACKSEL_MCU                                0x0002U

// Field: [0:0] srcaddrtbl0
//
// Let PBE know the source address table configuration for PAN0
#define PBE_IEEE_RAM_FFOPT0_SRCADDRTBL0                                  0x0001U
#define PBE_IEEE_RAM_FFOPT0_SRCADDRTBL0_M                                0x0001U
#define PBE_IEEE_RAM_FFOPT0_SRCADDRTBL0_S                                     0U
#define PBE_IEEE_RAM_FFOPT0_SRCADDRTBL0_SHORTONLY                        0x0000U
#define PBE_IEEE_RAM_FFOPT0_SRCADDRTBL0_MIX                              0x0001U

//******************************************************************************
// Register: PANID1
//******************************************************************************
// Field: [15:0] val
//
// Local PAN ID1
#define PBE_IEEE_RAM_PANID1_VAL_W                                            16U
#define PBE_IEEE_RAM_PANID1_VAL_M                                        0xFFFFU
#define PBE_IEEE_RAM_PANID1_VAL_S                                             0U

//******************************************************************************
// Register: SHORTADDR1
//******************************************************************************
// Field: [15:0] val
//
// Local PAN ID1 short address
#define PBE_IEEE_RAM_SHORTADDR1_VAL_W                                        16U
#define PBE_IEEE_RAM_SHORTADDR1_VAL_M                                    0xFFFFU
#define PBE_IEEE_RAM_SHORTADDR1_VAL_S                                         0U

//******************************************************************************
// Register: EXTADDR10
//******************************************************************************
// Field: [15:0] val
//
// Local PAN ID1 extended address, bits 15:0
#define PBE_IEEE_RAM_EXTADDR10_VAL_W                                         16U
#define PBE_IEEE_RAM_EXTADDR10_VAL_M                                     0xFFFFU
#define PBE_IEEE_RAM_EXTADDR10_VAL_S                                          0U

//******************************************************************************
// Register: EXTADDR11
//******************************************************************************
// Field: [15:0] val
//
// Local PAN ID1 extended address, bits 31:16
#define PBE_IEEE_RAM_EXTADDR11_VAL_W                                         16U
#define PBE_IEEE_RAM_EXTADDR11_VAL_M                                     0xFFFFU
#define PBE_IEEE_RAM_EXTADDR11_VAL_S                                          0U

//******************************************************************************
// Register: EXTADDR12
//******************************************************************************
// Field: [15:0] val
//
// Local PAN ID1 extended address, bits 47:32
#define PBE_IEEE_RAM_EXTADDR12_VAL_W                                         16U
#define PBE_IEEE_RAM_EXTADDR12_VAL_M                                     0xFFFFU
#define PBE_IEEE_RAM_EXTADDR12_VAL_S                                          0U

//******************************************************************************
// Register: EXTADDR13
//******************************************************************************
// Field: [15:0] val
//
// Local PAN ID1 extended address, bits 63:48
#define PBE_IEEE_RAM_EXTADDR13_VAL_W                                         16U
#define PBE_IEEE_RAM_EXTADDR13_VAL_M                                     0xFFFFU
#define PBE_IEEE_RAM_EXTADDR13_VAL_S                                          0U

//******************************************************************************
// Register: FFOPT1
//******************************************************************************
// Field: [9:8] maxframe
//
// Reject frames where the frame version field in the FCF is greater than this value
#define PBE_IEEE_RAM_FFOPT1_MAXFRAME_W                                        2U
#define PBE_IEEE_RAM_FFOPT1_MAXFRAME_M                                   0x0300U
#define PBE_IEEE_RAM_FFOPT1_MAXFRAME_S                                        8U

// Field: [7:7] pancoord
//
// 
#define PBE_IEEE_RAM_FFOPT1_PANCOORD                                     0x0080U
#define PBE_IEEE_RAM_FFOPT1_PANCOORD_M                                   0x0080U
#define PBE_IEEE_RAM_FFOPT1_PANCOORD_S                                        7U
#define PBE_IEEE_RAM_FFOPT1_PANCOORD_DISABLED                            0x0000U
#define PBE_IEEE_RAM_FFOPT1_PANCOORD_EN                                  0x0080U

// Field: [6:6] preqonly
//
// 
#define PBE_IEEE_RAM_FFOPT1_PREQONLY                                     0x0040U
#define PBE_IEEE_RAM_FFOPT1_PREQONLY_M                                   0x0040U
#define PBE_IEEE_RAM_FFOPT1_PREQONLY_S                                        6U
#define PBE_IEEE_RAM_FFOPT1_PREQONLY_ANY                                 0x0000U
#define PBE_IEEE_RAM_FFOPT1_PREQONLY_DATAREQ                             0x0040U

// Field: [5:5] defpend
//
// The value of the pending data bit in auto ACK packets that are not subject to auto-pend
#define PBE_IEEE_RAM_FFOPT1_DEFPEND                                      0x0020U
#define PBE_IEEE_RAM_FFOPT1_DEFPEND_M                                    0x0020U
#define PBE_IEEE_RAM_FFOPT1_DEFPEND_S                                         5U

// Field: [4:4] autopend
//
// 
#define PBE_IEEE_RAM_FFOPT1_AUTOPEND                                     0x0010U
#define PBE_IEEE_RAM_FFOPT1_AUTOPEND_M                                   0x0010U
#define PBE_IEEE_RAM_FFOPT1_AUTOPEND_S                                        4U
#define PBE_IEEE_RAM_FFOPT1_AUTOPEND_DISABLE                             0x0000U
#define PBE_IEEE_RAM_FFOPT1_AUTOPEND_EN                                  0x0010U

// Field: [2:2] autoack
//
// 
#define PBE_IEEE_RAM_FFOPT1_AUTOACK                                      0x0004U
#define PBE_IEEE_RAM_FFOPT1_AUTOACK_M                                    0x0004U
#define PBE_IEEE_RAM_FFOPT1_AUTOACK_S                                         2U
#define PBE_IEEE_RAM_FFOPT1_AUTOACK_DISABLE                              0x0000U
#define PBE_IEEE_RAM_FFOPT1_AUTOACK_EN                                   0x0004U

// Field: [1:1] immacksel
//
// Select from where the imm-ack frame will be taken for PAN1
#define PBE_IEEE_RAM_FFOPT1_IMMACKSEL                                    0x0002U
#define PBE_IEEE_RAM_FFOPT1_IMMACKSEL_M                                  0x0002U
#define PBE_IEEE_RAM_FFOPT1_IMMACKSEL_S                                       1U
#define PBE_IEEE_RAM_FFOPT1_IMMACKSEL_PBE                                0x0000U
#define PBE_IEEE_RAM_FFOPT1_IMMACKSEL_MCU                                0x0002U

// Field: [0:0] srcaddrtbl1
//
// Let PBE know the source address table configuration for PAN1
#define PBE_IEEE_RAM_FFOPT1_SRCADDRTBL1                                  0x0001U
#define PBE_IEEE_RAM_FFOPT1_SRCADDRTBL1_M                                0x0001U
#define PBE_IEEE_RAM_FFOPT1_SRCADDRTBL1_S                                     0U
#define PBE_IEEE_RAM_FFOPT1_SRCADDRTBL1_SHORTONLY                        0x0000U
#define PBE_IEEE_RAM_FFOPT1_SRCADDRTBL1_MIX                              0x0001U

//******************************************************************************
// Register: TMPRSSI
//******************************************************************************
// Field: [15:0] val
//
// A temporary storage of the signal strength of received signal
#define PBE_IEEE_RAM_TMPRSSI_VAL_W                                           16U
#define PBE_IEEE_RAM_TMPRSSI_VAL_M                                       0xFFFFU
#define PBE_IEEE_RAM_TMPRSSI_VAL_S                                            0U

//******************************************************************************
// Register: ENTRYENABLE00
//******************************************************************************
// Field: [15:0] val
//
// Source matching entry enable bits for entry  0-15 of PAN 0
#define PBE_IEEE_RAM_ENTRYENABLE00_VAL_W                                     16U
#define PBE_IEEE_RAM_ENTRYENABLE00_VAL_M                                 0xFFFFU
#define PBE_IEEE_RAM_ENTRYENABLE00_VAL_S                                      0U

//******************************************************************************
// Register: ENTRYENABLE01
//******************************************************************************
// Field: [15:0] val
//
// Source matching entry enable bits for entry 16-31 of PAN 0
#define PBE_IEEE_RAM_ENTRYENABLE01_VAL_W                                     16U
#define PBE_IEEE_RAM_ENTRYENABLE01_VAL_M                                 0xFFFFU
#define PBE_IEEE_RAM_ENTRYENABLE01_VAL_S                                      0U

//******************************************************************************
// Register: ENTRYENABLE02
//******************************************************************************
// Field: [15:0] val
//
// Source matching entry enable bits for entry 32-47 of PAN 0
#define PBE_IEEE_RAM_ENTRYENABLE02_VAL_W                                     16U
#define PBE_IEEE_RAM_ENTRYENABLE02_VAL_M                                 0xFFFFU
#define PBE_IEEE_RAM_ENTRYENABLE02_VAL_S                                      0U

//******************************************************************************
// Register: ENTRYENABLE03
//******************************************************************************
// Field: [15:0] val
//
// Source matching entry enable bits for entry 48-63 of PAN 0
#define PBE_IEEE_RAM_ENTRYENABLE03_VAL_W                                     16U
#define PBE_IEEE_RAM_ENTRYENABLE03_VAL_M                                 0xFFFFU
#define PBE_IEEE_RAM_ENTRYENABLE03_VAL_S                                      0U

//******************************************************************************
// Register: FRAMEPENDING00
//******************************************************************************
// Field: [15:0] val
//
// Frame pending bits for source matching entry  0-15 of PAN 0
#define PBE_IEEE_RAM_FRAMEPENDING00_VAL_W                                    16U
#define PBE_IEEE_RAM_FRAMEPENDING00_VAL_M                                0xFFFFU
#define PBE_IEEE_RAM_FRAMEPENDING00_VAL_S                                     0U

//******************************************************************************
// Register: FRAMEPENDING01
//******************************************************************************
// Field: [15:0] val
//
// Frame pending bits for source matching entry 16-31 of PAN 0
#define PBE_IEEE_RAM_FRAMEPENDING01_VAL_W                                    16U
#define PBE_IEEE_RAM_FRAMEPENDING01_VAL_M                                0xFFFFU
#define PBE_IEEE_RAM_FRAMEPENDING01_VAL_S                                     0U

//******************************************************************************
// Register: FRAMEPENDING02
//******************************************************************************
// Field: [15:0] val
//
// Frame pending bits for source matching entry 32-47 of PAN 0
#define PBE_IEEE_RAM_FRAMEPENDING02_VAL_W                                    16U
#define PBE_IEEE_RAM_FRAMEPENDING02_VAL_M                                0xFFFFU
#define PBE_IEEE_RAM_FRAMEPENDING02_VAL_S                                     0U

//******************************************************************************
// Register: FRAMEPENDING03
//******************************************************************************
// Field: [15:0] val
//
// Frame pending bits for source matching entry 48-63 of PAN 0
#define PBE_IEEE_RAM_FRAMEPENDING03_VAL_W                                    16U
#define PBE_IEEE_RAM_FRAMEPENDING03_VAL_M                                0xFFFFU
#define PBE_IEEE_RAM_FRAMEPENDING03_VAL_S                                     0U

//******************************************************************************
// Register: ENTRYENABLE10
//******************************************************************************
// Field: [15:0] val
//
// Source matching entry enable bits for entry   0-15 of PAN 1
#define PBE_IEEE_RAM_ENTRYENABLE10_VAL_W                                     16U
#define PBE_IEEE_RAM_ENTRYENABLE10_VAL_M                                 0xFFFFU
#define PBE_IEEE_RAM_ENTRYENABLE10_VAL_S                                      0U

//******************************************************************************
// Register: ENTRYENABLE11
//******************************************************************************
// Field: [15:0] val
//
// Source matching entry enable bits for entry  16-31 of PAN 1
#define PBE_IEEE_RAM_ENTRYENABLE11_VAL_W                                     16U
#define PBE_IEEE_RAM_ENTRYENABLE11_VAL_M                                 0xFFFFU
#define PBE_IEEE_RAM_ENTRYENABLE11_VAL_S                                      0U

//******************************************************************************
// Register: ENTRYENABLE12
//******************************************************************************
// Field: [15:0] val
//
// Source matching entry enable bits for entry  32-47 of PAN 1
#define PBE_IEEE_RAM_ENTRYENABLE12_VAL_W                                     16U
#define PBE_IEEE_RAM_ENTRYENABLE12_VAL_M                                 0xFFFFU
#define PBE_IEEE_RAM_ENTRYENABLE12_VAL_S                                      0U

//******************************************************************************
// Register: ENTRYENABLE13
//******************************************************************************
// Field: [15:0] val
//
// Source matching entry enable bits for entry  48-63 of PAN 1
#define PBE_IEEE_RAM_ENTRYENABLE13_VAL_W                                     16U
#define PBE_IEEE_RAM_ENTRYENABLE13_VAL_M                                 0xFFFFU
#define PBE_IEEE_RAM_ENTRYENABLE13_VAL_S                                      0U

//******************************************************************************
// Register: FRAMEPENDING10
//******************************************************************************
// Field: [15:0] val
//
// Frame pending bits for source matching entry  0-15 of PAN 1
#define PBE_IEEE_RAM_FRAMEPENDING10_VAL_W                                    16U
#define PBE_IEEE_RAM_FRAMEPENDING10_VAL_M                                0xFFFFU
#define PBE_IEEE_RAM_FRAMEPENDING10_VAL_S                                     0U

//******************************************************************************
// Register: FRAMEPENDING11
//******************************************************************************
// Field: [15:0] val
//
// Frame pending bits for source matching entry 16-31 of PAN 1
#define PBE_IEEE_RAM_FRAMEPENDING11_VAL_W                                    16U
#define PBE_IEEE_RAM_FRAMEPENDING11_VAL_M                                0xFFFFU
#define PBE_IEEE_RAM_FRAMEPENDING11_VAL_S                                     0U

//******************************************************************************
// Register: FRAMEPENDING12
//******************************************************************************
// Field: [15:0] val
//
// Frame pending bits for source matching entry 32-47 of PAN 1
#define PBE_IEEE_RAM_FRAMEPENDING12_VAL_W                                    16U
#define PBE_IEEE_RAM_FRAMEPENDING12_VAL_M                                0xFFFFU
#define PBE_IEEE_RAM_FRAMEPENDING12_VAL_S                                     0U

//******************************************************************************
// Register: FRAMEPENDING13
//******************************************************************************
// Field: [15:0] val
//
// Frame pending bits for source matching entry 48-63 of PAN 1
#define PBE_IEEE_RAM_FRAMEPENDING13_VAL_W                                    16U
#define PBE_IEEE_RAM_FRAMEPENDING13_VAL_M                                0xFFFFU
#define PBE_IEEE_RAM_FRAMEPENDING13_VAL_S                                     0U

//******************************************************************************
// Register: PANCFGED
//******************************************************************************
// Field: [15:0] val
//
// PANID of the PAN for which there was a match
#define PBE_IEEE_RAM_PANCFGED_VAL_W                                          16U
#define PBE_IEEE_RAM_PANCFGED_VAL_M                                      0xFFFFU
#define PBE_IEEE_RAM_PANCFGED_VAL_S                                           0U

//******************************************************************************
// Register: TMPFCF
//******************************************************************************
// Field: [15:0] val
//
// Frame Control Field received from the frame
#define PBE_IEEE_RAM_TMPFCF_VAL_W                                            16U
#define PBE_IEEE_RAM_TMPFCF_VAL_M                                        0xFFFFU
#define PBE_IEEE_RAM_TMPFCF_VAL_S                                             0U

//******************************************************************************
// Register: CFGAUTOACK
//******************************************************************************
// Field: [10:9] ackmode
//
// Control the filtering process of sequence number
#define PBE_IEEE_RAM_CFGAUTOACK_ACKMODE_W                                     2U
#define PBE_IEEE_RAM_CFGAUTOACK_ACKMODE_M                                0x0600U
#define PBE_IEEE_RAM_CFGAUTOACK_ACKMODE_S                                     9U
#define PBE_IEEE_RAM_CFGAUTOACK_ACKMODE_NOFILT                           0x0000U
#define PBE_IEEE_RAM_CFGAUTOACK_ACKMODE_FILTIMMACK                       0x0200U
#define PBE_IEEE_RAM_CFGAUTOACK_ACKMODE_FILTENHACK                       0x0400U

// Field: [8:8] flagreq
//
// Control the status flag towards MCU, when timeout occured waiting for Ack frame
#define PBE_IEEE_RAM_CFGAUTOACK_FLAGREQ                                  0x0100U
#define PBE_IEEE_RAM_CFGAUTOACK_FLAGREQ_M                                0x0100U
#define PBE_IEEE_RAM_CFGAUTOACK_FLAGREQ_S                                     8U
#define PBE_IEEE_RAM_CFGAUTOACK_FLAGREQ_DIS                              0x0000U
#define PBE_IEEE_RAM_CFGAUTOACK_FLAGREQ_EN                               0x0100U

// Field: [7:0] expseqnm
//
// Expected sequence number to correlate with the received one
#define PBE_IEEE_RAM_CFGAUTOACK_EXPSEQNM_W                                    8U
#define PBE_IEEE_RAM_CFGAUTOACK_EXPSEQNM_M                               0x00FFU
#define PBE_IEEE_RAM_CFGAUTOACK_EXPSEQNM_S                                    0U

//******************************************************************************
// Register: MACCMDID
//******************************************************************************
// Field: [7:0] val
//
// MAC command frame command ID field received
#define PBE_IEEE_RAM_MACCMDID_VAL_W                                           8U
#define PBE_IEEE_RAM_MACCMDID_VAL_M                                      0x00FFU
#define PBE_IEEE_RAM_MACCMDID_VAL_S                                           0U

//******************************************************************************
// Register: ACKSTATUS
//******************************************************************************
// Field: [5:5] fpstate
//
// While ACKDONE is raised to indicate CRC ok, if received ACK frame had FP on, enable FPSTATE
#define PBE_IEEE_RAM_ACKSTATUS_FPSTATE                                   0x0020U
#define PBE_IEEE_RAM_ACKSTATUS_FPSTATE_M                                 0x0020U
#define PBE_IEEE_RAM_ACKSTATUS_FPSTATE_S                                      5U

// Field: [4:4] crcok
//
// ACKDONE event is raised indicating the frame was received with CRC ok
#define PBE_IEEE_RAM_ACKSTATUS_CRCOK                                     0x0010U
#define PBE_IEEE_RAM_ACKSTATUS_CRCOK_M                                   0x0010U
#define PBE_IEEE_RAM_ACKSTATUS_CRCOK_S                                        4U

// Field: [3:3] ignored
//
// ACKDONE event is raised indicating the frame was received but ignored (seq. number mismatch included)
#define PBE_IEEE_RAM_ACKSTATUS_IGNORED                                   0x0008U
#define PBE_IEEE_RAM_ACKSTATUS_IGNORED_M                                 0x0008U
#define PBE_IEEE_RAM_ACKSTATUS_IGNORED_S                                      3U

// Field: [2:2] otherfrm
//
// ACKDONE event is raised indicating other frame than ACK has been received
#define PBE_IEEE_RAM_ACKSTATUS_OTHERFRM                                  0x0004U
#define PBE_IEEE_RAM_ACKSTATUS_OTHERFRM_M                                0x0004U
#define PBE_IEEE_RAM_ACKSTATUS_OTHERFRM_S                                     2U

// Field: [1:1] crcerr
//
// ACKDONE event is raised indicating the frame was received with CRC error
#define PBE_IEEE_RAM_ACKSTATUS_CRCERR                                    0x0002U
#define PBE_IEEE_RAM_ACKSTATUS_CRCERR_M                                  0x0002U
#define PBE_IEEE_RAM_ACKSTATUS_CRCERR_S                                       1U

// Field: [0:0] synctimeout
//
// ACKDONE event is raised indicating in the receiving window no ACK arrived
#define PBE_IEEE_RAM_ACKSTATUS_SYNCTIMEOUT                               0x0001U
#define PBE_IEEE_RAM_ACKSTATUS_SYNCTIMEOUT_M                             0x0001U
#define PBE_IEEE_RAM_ACKSTATUS_SYNCTIMEOUT_S                                  0U

//******************************************************************************
// Register: CORRCNT
//******************************************************************************
// Field: [7:0] val
//
// Counter of MDMPROG events to be used for CCA mode 2
#define PBE_IEEE_RAM_CORRCNT_VAL_W                                            8U
#define PBE_IEEE_RAM_CORRCNT_VAL_M                                       0x00FFU
#define PBE_IEEE_RAM_CORRCNT_VAL_S                                            0U

//******************************************************************************
// Register: COEXCORRMASK
//******************************************************************************
// Field: [7:0] val
//
// Number of subsequent correlation tops  needed to assert REQUEST when COEXCFG.RXSYNC is ONPREAMBLE; thermometer encoded (example: 0b00000011 means two correlation tops needed)
#define PBE_IEEE_RAM_COEXCORRMASK_VAL_W                                       8U
#define PBE_IEEE_RAM_COEXCORRMASK_VAL_M                                  0x00FFU
#define PBE_IEEE_RAM_COEXCORRMASK_VAL_S                                       0U

//******************************************************************************
// Register: TSYNC
//******************************************************************************
// Field: [15:0] val
//
// Coex, mode 1, T1 expressed in 0.25 µs steps for sync timeout
#define PBE_IEEE_RAM_TSYNC_VAL_W                                             16U
#define PBE_IEEE_RAM_TSYNC_VAL_M                                         0xFFFFU
#define PBE_IEEE_RAM_TSYNC_VAL_S                                              0U

//******************************************************************************
// Register: COEXT1
//******************************************************************************
// Field: [15:0] val
//
// Coex, mode 0, T1 expressed in 0.25 µs steps
#define PBE_IEEE_RAM_COEXT1_VAL_W                                            16U
#define PBE_IEEE_RAM_COEXT1_VAL_M                                        0xFFFFU
#define PBE_IEEE_RAM_COEXT1_VAL_S                                             0U

//******************************************************************************
// Register: COEXT2
//******************************************************************************
// Field: [7:0] val
//
// Shadow register, coex T2 expressed in 0.25 µs steps
#define PBE_IEEE_RAM_COEXT2_VAL_W                                             8U
#define PBE_IEEE_RAM_COEXT2_VAL_M                                        0x00FFU
#define PBE_IEEE_RAM_COEXT2_VAL_S                                             0U

//******************************************************************************
// Register: COEXCFG
//******************************************************************************
// Field: [14:14] rxsync
//
// Control the position where coex shall be executed
#define PBE_IEEE_RAM_COEXCFG_RXSYNC                                      0x4000U
#define PBE_IEEE_RAM_COEXCFG_RXSYNC_M                                    0x4000U
#define PBE_IEEE_RAM_COEXCFG_RXSYNC_S                                        14U
#define PBE_IEEE_RAM_COEXCFG_RXSYNC_ONSYSTIM                             0x0000U
#define PBE_IEEE_RAM_COEXCFG_RXSYNC_ONPREAMBLE                           0x4000U

// Field: [13:13] setreqonrx
//
// Not supported yet
#define PBE_IEEE_RAM_COEXCFG_SETREQONRX                                  0x2000U
#define PBE_IEEE_RAM_COEXCFG_SETREQONRX_M                                0x2000U
#define PBE_IEEE_RAM_COEXCFG_SETREQONRX_S                                    13U

// Field: [12:12] priority
//
// The GPO level indicating priority during T2
#define PBE_IEEE_RAM_COEXCFG_PRIORITY                                    0x1000U
#define PBE_IEEE_RAM_COEXCFG_PRIORITY_M                                  0x1000U
#define PBE_IEEE_RAM_COEXCFG_PRIORITY_S                                      12U

// Field: [9:9] retainreq
//
// If set, the REQUEST GPO retains current state when the operation ends.
#define PBE_IEEE_RAM_COEXCFG_RETAINREQ                                   0x0200U
#define PBE_IEEE_RAM_COEXCFG_RETAINREQ_M                                 0x0200U
#define PBE_IEEE_RAM_COEXCFG_RETAINREQ_S                                      9U

// Field: [8:8] coexen
//
// Coex enable bit
#define PBE_IEEE_RAM_COEXCFG_COEXEN                                      0x0100U
#define PBE_IEEE_RAM_COEXCFG_COEXEN_M                                    0x0100U
#define PBE_IEEE_RAM_COEXCFG_COEXEN_S                                         8U

// Field: [7:0] t2
//
// T2 time period expressed in 0.25 µs steps
#define PBE_IEEE_RAM_COEXCFG_T2_W                                             8U
#define PBE_IEEE_RAM_COEXCFG_T2_M                                        0x00FFU
#define PBE_IEEE_RAM_COEXCFG_T2_S                                             0U

//******************************************************************************
// Register: EXTSRCADDRTBL
//******************************************************************************
// Field: [15:0] val
//
// Pointer to the extended source address table
#define PBE_IEEE_RAM_EXTSRCADDRTBL_VAL_W                                     16U
#define PBE_IEEE_RAM_EXTSRCADDRTBL_VAL_M                                 0xFFFFU
#define PBE_IEEE_RAM_EXTSRCADDRTBL_VAL_S                                      0U

//******************************************************************************
// Register: MATCHIDXFILT
//******************************************************************************
// Field: [15:0] val
//
// Register to disqualigy exteded addresses from the source table that did not had match
#define PBE_IEEE_RAM_MATCHIDXFILT_VAL_W                                      16U
#define PBE_IEEE_RAM_MATCHIDXFILT_VAL_M                                  0xFFFFU
#define PBE_IEEE_RAM_MATCHIDXFILT_VAL_S                                       0U

//******************************************************************************
// Register: PAN0_SRC_MATCH_SHORT_START
//******************************************************************************
// Field: [15:0] val
//
// First entry of short source match table for PAN 0
#define PBE_IEEE_RAM_PAN0_SRC_MATCH_SHORT_START_VAL_W                        16U
#define PBE_IEEE_RAM_PAN0_SRC_MATCH_SHORT_START_VAL_M                    0xFFFFU
#define PBE_IEEE_RAM_PAN0_SRC_MATCH_SHORT_START_VAL_S                         0U

//******************************************************************************
// Register: PAN0_SRC_MATCH_EXT_START
//******************************************************************************
// Field: [15:0] val
//
// First entry of extended source match table for PAN 0 if present
#define PBE_IEEE_RAM_PAN0_SRC_MATCH_EXT_START_VAL_W                          16U
#define PBE_IEEE_RAM_PAN0_SRC_MATCH_EXT_START_VAL_M                      0xFFFFU
#define PBE_IEEE_RAM_PAN0_SRC_MATCH_EXT_START_VAL_S                           0U

//******************************************************************************
// Register: PAN1_SRC_MATCH_SHORT_START
//******************************************************************************
// Field: [15:0] val
//
// First entry of short source match table for PAN 1
#define PBE_IEEE_RAM_PAN1_SRC_MATCH_SHORT_START_VAL_W                        16U
#define PBE_IEEE_RAM_PAN1_SRC_MATCH_SHORT_START_VAL_M                    0xFFFFU
#define PBE_IEEE_RAM_PAN1_SRC_MATCH_SHORT_START_VAL_S                         0U

//******************************************************************************
// Register: PAN1_SRC_MATCH_EXT_START
//******************************************************************************
// Field: [15:0] val
//
// First entry of extended source match table for PAN 1 if present
#define PBE_IEEE_RAM_PAN1_SRC_MATCH_EXT_START_VAL_W                          16U
#define PBE_IEEE_RAM_PAN1_SRC_MATCH_EXT_START_VAL_M                      0xFFFFU
#define PBE_IEEE_RAM_PAN1_SRC_MATCH_EXT_START_VAL_S                           0U


#endif // __PBE_IEEE_RAM_REGS_H
