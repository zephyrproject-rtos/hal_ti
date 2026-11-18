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
#include "spi_adapt.h"
#include "txn_bus_drv.h"
#include "io.h"

#include <bus_if.h>

#include "bus_spi.h"



/******************************************************************************
                                FUNCTION 
******************************************************************************/
int32_t ioTranslateAddr(TPartition *aPartition, int32_t addr)
{
    TPartition *part = aPartition;
    /*
     * To translate, first check to which window of addresses the
     * particular address belongs. Then subtract the starting address
     * of that window from the address. Then, add offset of the
     * translated region.
     *
     * The translated regions occur next to each other in physical device
     * memory, so just add the sizes of the preceding address regions to
     * get the offset to the new region.
     */
    if (((uint32_t)addr >= part[0].uMemAdrr) &&
        ((uint32_t)addr < part[0].uMemAdrr + part[0].uMemSize))
    {
        return addr - part[0].uMemAdrr;
    }
    else if (((uint32_t)addr >= part[1].uMemAdrr) &&
            ((uint32_t)addr < part[1].uMemAdrr + part[1].uMemSize))
    {
        return addr - part[1].uMemAdrr + part[0].uMemSize;
    }
    else if (((uint32_t)addr >= part[2].uMemAdrr) &&
             ((uint32_t)addr < part[2].uMemAdrr + part[2].uMemSize))
    {
        return addr - part[2].uMemAdrr + part[1].uMemSize + part[0].uMemSize;
    }
    else if (((uint32_t)addr >= part[3].uMemAdrr) &&
             ((uint32_t)addr < part[3].uMemAdrr + part[3].uMemSize))
    {
        return addr - part[3].uMemAdrr + part[2].uMemSize + part[1].uMemSize + part[0].uMemSize;
    }
    return 0;

}


/* Set the partitions to access the chip addresses
 *
 * To simplify driver code, a fixed (virtual) memory map is defined for
 * register and memory addresses. Because in the chipset, in different stages
 * of operation, those addresses will move around, an address translation
 * mechanism is required.
 *
 * There are four partitions (three memory and one register partition),
 * which are mapped to two different areas of the hardware memory.
 *
 *                                Virtual address
 *                                     space
 *
 *                                    |    |
 *                                 ...+----+--> mem.start
 *          Physical address    ...   |    |
 *               space       ...      |    | [PART_0]
 *                        ...         |    |
 *  00000000  <--+----+...         ...+----+--> mem.start + mem.size
 *               |    |         ...   |    |
 *               |MEM |      ...      |    |
 *               |    |   ...         |    |
 *  mem.size  <--+----+...            |    | {unused area)
 *               |    |   ...         |    |
 *               |REG |      ...      |    |
 *  mem.size     |    |         ...   |    |
 *      +     <--+----+...         ...+----+--> reg.start
 *  reg.size     |    |   ...         |    |
 *               |MEM2|      ...      |    | [PART_1]
 *               |    |         ...   |    |
 *                                 ...+----+--> reg.start + reg.size
 *                                    |    |
 *
 */

int32_t SetPartition ()
{
    int32_t ret = 0;

    return ret;
}


/**
 * \fn     ioSetPartition
 * \brief  Set HW addresses partition
 *
 * Set the HW address ranges for download or working memory and registers access.
 * Generate and configure the bus access address mapping table.
 * The partition is split between register (fixed partition of 24KB size, exists in all modes),
 *     and memory (dynamically changed during init and gets constant value in run-time, 104KB size).
 * The TwIf configures the memory mapping table on the device by issuing write transaction to
 *     table address (note that the bus driver see this as a regular transaction).
 *
 * \note In future versions, a specific bus may not support partitioning (as in wUART),
 *       In this case the HwInit module shall not call this function (will learn the bus
 *       configuration from the INI file).
 *
 * \param  pPartition  - all partition base address
 * \return void
 * \sa
 */
void ioSetPartition ()
{

#ifdef ENABLE_INIT
    UART_PRINT("ioSetPartition: uMemAddr1=0x%x, MemSize1=0x%x uMemAddr2=0x%x, MemSize2=0x%x, uMemAddr3=0x%x, MemSize3=0x%x, uMemAddr4=0x%x, MemSize4=0x%x\n",pPartition[0].uMemAdrr, pPartition[0].uMemSize,pPartition[1].uMemAdrr, pPartition[1].uMemSize,pPartition[2].uMemAdrr, pPartition[2].uMemSize,pPartition[3].uMemAdrr );
#endif
    /* Prepare partition Txn data and send to HW */
    SetPartition ();
}

void TopReadReg(uint32_t addr,  uint16_t * data)
{
    uint32_t val = 0;
    int32_t ret;

    if ((addr % 4) == 0)
    {
        /* address is 4-bytes aligned */
        ret = Read32();
        if(ret >=0 && data)
            *data = val & 0xffff;
    }
    else
    {
        ret = Read32();
        if(ret >=0 && data)
            *data = (val & 0xfff0000) >> 16;
    }
}

void TopWriteReg(uint32_t addr,  uint16_t data)
{
    uint32_t val = 0;

    if ((addr % 4) == 0)
    {
        /* address is 4-bytes aligned */
        Read32();
        val = (val &0xffff0000) | data;
        Write32();
    }
    else
    {
        Read32();
        val = (val & 0xffff) | (data << 16);
        Write32();
    }
}


void ioInit()
{
    uint32_t wspi_config = 0;

    spi_Init();

    // Send a WSPI init command
    bus_sendInitCommand(wspi_config, 0 /* fbrw - Not used */);
}


