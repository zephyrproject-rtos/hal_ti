/******************************************************************************
*  Filename:       hw_soc_aaon.h
*
*  Description:    Defines and prototypes for the SOC_AAON peripheral.
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
#ifndef __HW_SOC_AAON_H__
#define __HW_SOC_AAON_H__
/*-------------------------------------------------------------------------------

This section defines the register offsets of the SOC_AAON component

--------------------------------------------------------------------------------- */

//DMA M33 Secure Event IMASK
#define SOC_AAON_O_DMASIMASK                                         0x00000000U

//DMA M33 Secure Event ISET
#define SOC_AAON_O_DMASISET                                          0x00000004U

//DMA M33 Secure Event ICLR
#define SOC_AAON_O_DMASICLR                                          0x00000008U

//DMA M33 Secure Event IMSET
#define SOC_AAON_O_DMASIMSET                                         0x0000000CU

//DMA M33 Secure Event IMCLR
#define SOC_AAON_O_DMASIMCLR                                         0x00000010U

//DMA M33 Secure Event RIS
#define SOC_AAON_O_DMASRIS                                           0x00000014U

//DMA M33 Secure Event MIS
#define SOC_AAON_O_DMASMIS                                           0x00000018U

//DMA M33 Non-Secured IMASK
#define SOC_AAON_O_DMANSIMASK                                        0x00001000U

//DMA M33 Non-Secured ISET
#define SOC_AAON_O_DMANSISET                                         0x00001004U

//DMA M33 Non-Secured ICLR
#define SOC_AAON_O_DMANSICLR                                         0x00001008U

//DMA M33 Non-Secured IMSET
#define SOC_AAON_O_DMANSIMSET                                        0x0000100CU

//DMA M33 Non-Secured IMCLR
#define SOC_AAON_O_DMANSIMCLR                                        0x00001010U

//DMA M33 Non-Secured RIS
#define SOC_AAON_O_DMANSRIS                                          0x00001014U

//DMA M33 Non-Secured MIS
#define SOC_AAON_O_DMANSMIS                                          0x00001018U

//DMA M3 Event IMASK
#define SOC_AAON_O_DMAM3IMASK                                        0x00002000U

//DMA M3 Event ISET
#define SOC_AAON_O_DMAM3ISET                                         0x00002004U

//DMA M3 Event ICLR
#define SOC_AAON_O_DMAM3ICLR                                         0x00002008U

//DMA M3 Event IMSET
#define SOC_AAON_O_DMAM3IMSET                                        0x0000200CU

//DMA M3 Event IMCLR
#define SOC_AAON_O_DMAM3IMCLR                                        0x00002010U

//DMA M3 Event RIS
#define SOC_AAON_O_DMAM3RIS                                          0x00002014U

//DMA M3 Event MIS
#define SOC_AAON_O_DMAM3MIS                                          0x00002018U



/*-----------------------------------REGISTER------------------------------------
    Register name:       DMASIMASK
    Offset name:         SOC_AAON_O_DMASIMASK
    Relative address:    0x0
    Description:         DMA M33 Secure Event IMASK.
                        Mask Event.
                        '0' - CLR - Clear Interrupt Mask
                        '1' - SET - Set Interrupt Mask
    Default Value:       0x00000000

        Field:           IMASK
        From..to bits:   0...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     '0' - CLR - Clear Interrupt Mask
                         '1' - SET - Set Interrupt Mask

*/
#define SOC_AAON_DMASIMASK_IMASK_W                                   12U
#define SOC_AAON_DMASIMASK_IMASK_M                                   0x00000FFFU
#define SOC_AAON_DMASIMASK_IMASK_S                                   0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DMASISET
    Offset name:         SOC_AAON_O_DMASISET
    Relative address:    0x4
    Description:         DMA M33 Secure Event ISET.
                        Sets event in RIS
                        Write 0 - NO_EFFECT - Writing 0 has no effect
                        Write 1 - SET - Sets interrupt
    Default Value:       0x00000000

        Field:           ISET
        From..to bits:   0...11
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Write 0 - NO_EFFECT - Writing 0 has no effect
                         Write 1 - SET - Sets interrupt
                         Type: Write-Clear.

*/
#define SOC_AAON_DMASISET_ISET_W                                     12U
#define SOC_AAON_DMASISET_ISET_M                                     0x00000FFFU
#define SOC_AAON_DMASISET_ISET_S                                     0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DMASICLR
    Offset name:         SOC_AAON_O_DMASICLR
    Relative address:    0x8
    Description:         DMA M33 Secure Event ICLR.
                        Clears event in RIS
                        Write 0 - NO_EFFECT - Writing 0 has no effect
                        Write 1 - CLR - Clears the Event
    Default Value:       0x00000000

        Field:           ICLR
        From..to bits:   0...11
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Write 0 - NO_EFFECT - Writing 0 has no effect
                         Write 1 - CLR - Clears the Event
                         Type: Write-Clear.

*/
#define SOC_AAON_DMASICLR_ICLR_W                                     12U
#define SOC_AAON_DMASICLR_ICLR_M                                     0x00000FFFU
#define SOC_AAON_DMASICLR_ICLR_S                                     0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DMASIMSET
    Offset name:         SOC_AAON_O_DMASIMSET
    Relative address:    0xC
    Description:         DMA M33 Secure Event IMSET.
                        Sets Event
                        Write 0 - NO_EFFECT - Writing 0 has no effect
                        Write 1 - SET - Set interrupt mask
    Default Value:       0x00000000

        Field:           IMSET
        From..to bits:   0...11
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Write 0 - NO_EFFECT - Writing 0 has no effect
                         Write 1 - SET - Set interrupt mask
                         Type: Write-Clear

*/
#define SOC_AAON_DMASIMSET_IMSET_W                                   12U
#define SOC_AAON_DMASIMSET_IMSET_M                                   0x00000FFFU
#define SOC_AAON_DMASIMSET_IMSET_S                                   0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DMASIMCLR
    Offset name:         SOC_AAON_O_DMASIMCLR
    Relative address:    0x10
    Description:         DMA M33 Secure Event IMCLR.
                        Clears Event
                        Write 0 - NO_EFFECT - Writing 0 has no effect
                        Write 1 - CLR - Clear interrupt mask
    Default Value:       0x00000000

        Field:           IMCLR
        From..to bits:   0...11
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Write 0 - NO_EFFECT - Writing 0 has no effect
                         Write 1 - CLR - Clear interrupt mask
                         Type: Write-Clear.

*/
#define SOC_AAON_DMASIMCLR_IMCLR_W                                   12U
#define SOC_AAON_DMASIMCLR_IMCLR_M                                   0x00000FFFU
#define SOC_AAON_DMASIMCLR_IMCLR_S                                   0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DMASRIS
    Offset name:         SOC_AAON_O_DMASRIS
    Relative address:    0x14
    Description:         DMA M33 Secure Event RIS.
                        Raw interrupt status for event.
                        This bit is set to 1 when an event is received. when the corresponding bit in ICLR is set to 1, this bit will be cleared.
                        Read 0 - CLR - Interrupt did not occur
                        Read 1 - SET - Interrupt occurred
    Default Value:       0x00000000

        Field:           RIS
        From..to bits:   0...11
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Read 0 - CLR - Interrupt did not occur
                         Read 1 - SET - Interrupt occurred

*/
#define SOC_AAON_DMASRIS_RIS_W                                       12U
#define SOC_AAON_DMASRIS_RIS_M                                       0x00000FFFU
#define SOC_AAON_DMASRIS_RIS_S                                       0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DMASMIS
    Offset name:         SOC_AAON_O_DMASMIS
    Relative address:    0x18
    Description:         DMA M33 Secure Event MIS.
                        Mask interrupt status for event
                        Read 0 - CLR - Interrupt did not occur
                        Read 1 - SET - Interrupt occurred
    Default Value:       0x00000000

        Field:           MIS
        From..to bits:   0...11
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Read 0 - CLR - Interrupt did not occur
                         Read 1 - SET - Interrupt occurred

*/
#define SOC_AAON_DMASMIS_MIS_W                                       12U
#define SOC_AAON_DMASMIS_MIS_M                                       0x00000FFFU
#define SOC_AAON_DMASMIS_MIS_S                                       0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DMANSIMASK
    Offset name:         SOC_AAON_O_DMANSIMASK
    Relative address:    0x1000
    Description:         DMA M33 Non-Secured IMASK.
                        Mask Event.
                        '0' - CLR - Clear Interrupt Mask
                        '1' - SET - Set Interrupt Mask
    Default Value:       0x00000000

        Field:           IMASK
        From..to bits:   0...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     '0' - CLR - Clear Interrupt Mask
                         '1' - SET - Set Interrupt Mask

*/
#define SOC_AAON_DMANSIMASK_IMASK_W                                  12U
#define SOC_AAON_DMANSIMASK_IMASK_M                                  0x00000FFFU
#define SOC_AAON_DMANSIMASK_IMASK_S                                  0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DMANSISET
    Offset name:         SOC_AAON_O_DMANSISET
    Relative address:    0x1004
    Description:         DMA M33 Non-Secured ISET.
                        Sets event in RIS
                        Write 0 - NO_EFFECT - Writing 0 has no effect
                        Write 1 - SET - Sets interrupt
    Default Value:       0x00000000

        Field:           ISET
        From..to bits:   0...11
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Write 0 - NO_EFFECT - Writing 0 has no effect
                         Write 1 - SET - Sets interrupt
                         Type: Write-Clear.

*/
#define SOC_AAON_DMANSISET_ISET_W                                    12U
#define SOC_AAON_DMANSISET_ISET_M                                    0x00000FFFU
#define SOC_AAON_DMANSISET_ISET_S                                    0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DMANSICLR
    Offset name:         SOC_AAON_O_DMANSICLR
    Relative address:    0x1008
    Description:         DMA M33 Non-Secured ICLR.
                        Clears event in RIS
                        Write 0 - NO_EFFECT - Writing 0 has no effect
                        Write 1 - CLR - Clears the Event
    Default Value:       0x00000000

        Field:           ICLR
        From..to bits:   0...11
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Write 0 - NO_EFFECT - Writing 0 has no effect
                         Write 1 - CLR - Clears the Event
                         Type: Write-Clear.

*/
#define SOC_AAON_DMANSICLR_ICLR_W                                    12U
#define SOC_AAON_DMANSICLR_ICLR_M                                    0x00000FFFU
#define SOC_AAON_DMANSICLR_ICLR_S                                    0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DMANSIMSET
    Offset name:         SOC_AAON_O_DMANSIMSET
    Relative address:    0x100C
    Description:         DMA M33 Non-Secured IMSET.
                        Sets Event
                        Write 0 - NO_EFFECT - Writing 0 has no effect
                        Write 1 - SET - Set interrupt mask
    Default Value:       0x00000000

        Field:           IMSET
        From..to bits:   0...11
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Write 0 - NO_EFFECT - Writing 0 has no effect
                         Write 1 - SET - Set interrupt mask
                         Type: Write-Clear

*/
#define SOC_AAON_DMANSIMSET_IMSET_W                                  12U
#define SOC_AAON_DMANSIMSET_IMSET_M                                  0x00000FFFU
#define SOC_AAON_DMANSIMSET_IMSET_S                                  0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DMANSIMCLR
    Offset name:         SOC_AAON_O_DMANSIMCLR
    Relative address:    0x1010
    Description:         DMA M33 Non-Secured IMCLR.
                        Clears Event
                        Write 0 - NO_EFFECT - Writing 0 has no effect
                        Write 1 - CLR - Clear interrupt mask
    Default Value:       0x00000000

        Field:           IMCLR
        From..to bits:   0...11
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Write 0 - NO_EFFECT - Writing 0 has no effect
                         Write 1 - CLR - Clear interrupt mask
                         Type: Write-Clear.

*/
#define SOC_AAON_DMANSIMCLR_IMCLR_W                                  12U
#define SOC_AAON_DMANSIMCLR_IMCLR_M                                  0x00000FFFU
#define SOC_AAON_DMANSIMCLR_IMCLR_S                                  0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DMANSRIS
    Offset name:         SOC_AAON_O_DMANSRIS
    Relative address:    0x1014
    Description:         DMA M33 Non-Secured RIS.
                        Raw interrupt status for event.
                        This bit is set to 1 when an event is received. when the corresponding bit in ICLR is set to 1, this bit will be cleared.
                        Read 0 - CLR - Interrupt did not occur
                        Read 1 - SET - Interrupt occurred
    Default Value:       0x00000000

        Field:           RIS
        From..to bits:   0...11
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Read 0 - CLR - Interrupt did not occur
                         Read 1 - SET - Interrupt occurred

*/
#define SOC_AAON_DMANSRIS_RIS_W                                      12U
#define SOC_AAON_DMANSRIS_RIS_M                                      0x00000FFFU
#define SOC_AAON_DMANSRIS_RIS_S                                      0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DMANSMIS
    Offset name:         SOC_AAON_O_DMANSMIS
    Relative address:    0x1018
    Description:         DMA M33 Non-Secured MIS.
                        Mask interrupt status for event
                        Read 0 - CLR - Interrupt did not occur
                        Read 1 - SET - Interrupt occurred
    Default Value:       0x00000000

        Field:           MIS
        From..to bits:   0...11
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Read 0 - CLR - Interrupt did not occur
                         Read 1 - SET - Interrupt occurred

*/
#define SOC_AAON_DMANSMIS_MIS_W                                      12U
#define SOC_AAON_DMANSMIS_MIS_M                                      0x00000FFFU
#define SOC_AAON_DMANSMIS_MIS_S                                      0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DMAM3IMASK
    Offset name:         SOC_AAON_O_DMAM3IMASK
    Relative address:    0x2000
    Description:         DMA M3 Event IMASK.
                        Mask Event.
                        '0' - CLR - Clear Interrupt Mask
                        '1' - SET - Set Interrupt Mask
    Default Value:       0x00000000

        Field:           IMASK
        From..to bits:   0...11
        DefaultValue:    0x0
        Access type:     read-write
        Description:     '0' - CLR - Clear Interrupt Mask
                         '1' - SET - Set Interrupt Mask

*/
#define SOC_AAON_DMAM3IMASK_IMASK_W                                  12U
#define SOC_AAON_DMAM3IMASK_IMASK_M                                  0x00000FFFU
#define SOC_AAON_DMAM3IMASK_IMASK_S                                  0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DMAM3ISET
    Offset name:         SOC_AAON_O_DMAM3ISET
    Relative address:    0x2004
    Description:         DMA M3 Event ISET.
                        Sets event in RIS
                        Write 0 - NO_EFFECT - Writing 0 has no effect
                        Write 1 - SET - Sets interrupt
    Default Value:       0x00000000

        Field:           ISET
        From..to bits:   0...11
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Write 0 - NO_EFFECT - Writing 0 has no effect
                         Write 1 - SET - Sets interrupt
                         Type: Write-Clear.

*/
#define SOC_AAON_DMAM3ISET_ISET_W                                    12U
#define SOC_AAON_DMAM3ISET_ISET_M                                    0x00000FFFU
#define SOC_AAON_DMAM3ISET_ISET_S                                    0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DMAM3ICLR
    Offset name:         SOC_AAON_O_DMAM3ICLR
    Relative address:    0x2008
    Description:         DMA M3 Event ICLR.
                        Clears event in RIS
                        Write 0 - NO_EFFECT - Writing 0 has no effect
                        Write 1 - CLR - Clears the Event
    Default Value:       0x00000000

        Field:           ICLR
        From..to bits:   0...11
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Write 0 - NO_EFFECT - Writing 0 has no effect
                         Write 1 - CLR - Clears the Event
                         Type: Write-Clear.

*/
#define SOC_AAON_DMAM3ICLR_ICLR_W                                    12U
#define SOC_AAON_DMAM3ICLR_ICLR_M                                    0x00000FFFU
#define SOC_AAON_DMAM3ICLR_ICLR_S                                    0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DMAM3IMSET
    Offset name:         SOC_AAON_O_DMAM3IMSET
    Relative address:    0x200C
    Description:         DMA M3 Event IMSET.
                        Sets Event
                        Write 0 - NO_EFFECT - Writing 0 has no effect
                        Write 1 - SET - Set interrupt mask
    Default Value:       0x00000000

        Field:           IMSET
        From..to bits:   0...11
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Write 0 - NO_EFFECT - Writing 0 has no effect
                         Write 1 - SET - Set interrupt mask
                         Type: Write-Clear

*/
#define SOC_AAON_DMAM3IMSET_IMSET_W                                  12U
#define SOC_AAON_DMAM3IMSET_IMSET_M                                  0x00000FFFU
#define SOC_AAON_DMAM3IMSET_IMSET_S                                  0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DMAM3IMCLR
    Offset name:         SOC_AAON_O_DMAM3IMCLR
    Relative address:    0x2010
    Description:         DMA M3 Event IMCLR.
                        Clears Event
                        Write 0 - NO_EFFECT - Writing 0 has no effect
                        Write 1 - CLR - Clear interrupt mask
    Default Value:       0x00000000

        Field:           IMCLR
        From..to bits:   0...11
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Write 0 - NO_EFFECT - Writing 0 has no effect
                         Write 1 - CLR - Clear interrupt mask
                         Type: Write-Clear.

*/
#define SOC_AAON_DMAM3IMCLR_IMCLR_W                                  12U
#define SOC_AAON_DMAM3IMCLR_IMCLR_M                                  0x00000FFFU
#define SOC_AAON_DMAM3IMCLR_IMCLR_S                                  0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DMAM3RIS
    Offset name:         SOC_AAON_O_DMAM3RIS
    Relative address:    0x2014
    Description:         DMA M3 Event RIS.
                        This bit is set to 1 when an event is received. when the corresponding bit in ICLR is set to 1, this bit will be cleared.
                        Read 0 - CLR - Interrupt did not occur
                        Read 1 - SET - Interrupt occurred
    Default Value:       0x00000000

        Field:           RIS
        From..to bits:   0...11
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Read 0 - CLR - Interrupt did not occur
                         Read 1 - SET - Interrupt occurred

*/
#define SOC_AAON_DMAM3RIS_RIS_W                                      12U
#define SOC_AAON_DMAM3RIS_RIS_M                                      0x00000FFFU
#define SOC_AAON_DMAM3RIS_RIS_S                                      0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       DMAM3MIS
    Offset name:         SOC_AAON_O_DMAM3MIS
    Relative address:    0x2018
    Description:         DMA M3 Event MIS.
                        Mask interrupt status for event
                        Read 0 - CLR - Interrupt did not occur
                        Read 1 - SET - Interrupt occurred
    Default Value:       0x00000000

        Field:           MIS
        From..to bits:   0...11
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Read 0 - CLR - Interrupt did not occur
                         Read 1 - SET - Interrupt occured

*/
#define SOC_AAON_DMAM3MIS_MIS_W                                      12U
#define SOC_AAON_DMAM3MIS_MIS_M                                      0x00000FFFU
#define SOC_AAON_DMAM3MIS_MIS_S                                      0U

#endif /* __HW_SOC_AAON_H__*/
