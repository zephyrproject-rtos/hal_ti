/*****************************************************************************

  Copyright (c) 2022-2026 Texas Instruments Incorporated

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:

  1) Redistributions of source code must retain the above copyright notice,
     this list of conditions and the following disclaimer.

  2) Redistributions in binary form must reproduce the above copyright notice,
     this list of conditions and the following disclaimer in the documentation
     and/or other materials provided with the distribution.

  3) Neither the name of the copyright holder nor the names of its
     contributors may be used to endorse or promote products derived from this
     software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE.

*****************************************************************************/
/* Include SysConfig-generated linker file */
#include "ti_build_linker.cmd.toolbox"

--stack_size=1024   /* C stack is also used for ISR stack */
--heap_size=16384   /* Application heap for malloc/free */
--entry_point resetISR

/* Retain interrupt vector table variable                                    */
--retain "*(.resetVecs)"

/* Suppress warnings and errors:                                             */
/* - 10063: Warning about entry point not being _c_int00                     */
/* - 16011, 16012: 8-byte alignment errors. Observed when linking in object  */
/*   files compiled using Keil (ARM compiler)                                */
--diag_suppress=10063,16011,16012

/* Set severity of diagnostics to Remark instead of Warning                  */
/* - 10068: Warning about no matching log_ptr* sections                      */
--diag_remark=10068

#define FLASH_BASE              0x14000000
#define FLASH_SIZE              build_linker_toolbox_FLASH_SIZE
#define RESERVED_FLASH_SIZE     0x00002000
#define CRAM_BASE               0x00000000
#define CRAM_SIZE               0x00008000
#define DRAM_BASE               0x28000000
#define DRAM_SIZE               0x00030000 /* (Static only) DRAM1: 128K + DRAM2: 64K */
#define FLASH_INT_VEC_SIZE      0x00002400 /* Including padding */

/* System memory map */
MEMORY
{
    /* Application stored in and executes from external flash */
    FLASH_INT_VEC (RWX) : origin = FLASH_BASE, length = FLASH_INT_VEC_SIZE
    FLASH (RX) : origin = end(FLASH_INT_VEC), length = FLASH_SIZE - FLASH_INT_VEC_SIZE
    /* Application uses internal CRAM for code/data */
    CRAM (RWX) : origin = CRAM_BASE, length = CRAM_SIZE
    /* Fast memory that can be used as cache memory */
    TCM_DRAM_NON_SECURE (RW) : origin = 0x20000000, length = ((build_linker_toolbox_PSRAM_SIZE == 0) * 0x10000 + 0xFFFF)  //0x20000000-0x2000FFFF  64Kbyte for PSRAM / //0x20000000-0x2001FFFF  128Kbyte for NO-PSRAM
    /* Application uses internal DRAM for data */
    CONNECTIVITY_SHARED_MEM (RW) : origin = DRAM_BASE, length = 0x00000100
    BOOT_REPORT_SHARED_MEM (RW) : origin = end(CONNECTIVITY_SHARED_MEM), length = 0x00000CB0
    DRAM (RWX) : origin = end(BOOT_REPORT_SHARED_MEM), length = DRAM_SIZE - SIZE(CONNECTIVITY_SHARED_MEM) - SIZE(BOOT_REPORT_SHARED_MEM)
    /* Explicitly placed off target for the storage of logging data.
     * The ARM memory map allocates 1 GB of external memory from 0x60000000 - 0x9FFFFFFF.
     * Unlikely that all of this will be used, so we are using the upper parts of the region.
     * ARM memory map: https://developer.arm.com/documentation/ddi0337/e/memory-map/about-the-memory-map*/
    LOG_DATA (R) : origin = 0x90000000, length = 0x40000        /* 256 KB */
    LOG_PTR  (R) : origin = 0x94000008, length = 0x40000        /* 256 KB */
    /* PSRAM Configured by sysconfig. Normally our launchpads are not equipped with PSRAM and the length will be set to 1 */
    PSRAM (RW) : origin = 0x60000000, length = build_linker_toolbox_PSRAM_SIZE + (build_linker_toolbox_PSRAM_SIZE == 0)

    /* Other memory regions */
    PERIPH_API (RW)  : origin = 0x45602000, length = 0x0000001F
    MEM_POOL   (RW)  : origin = 0x28044000, length = 0x00004000
    DB_MEM     (RW)  : origin = 0x45A80000, length = 0x0000FFFF
    PHY_CTX    (RW)  : origin = 0x45900000, length = 0x00010000
    PHY_SCR    (RW)  : origin = 0x45910000, length = 0x00004800
    CPERAM     (RWX) : origin = 0x45C00000, length = 0x00010000 /* 64K PROGRAM MEMORY  */
    MCERAM     (RWX) : origin = 0x45C80000, length = 0x00001000 /* 4K PROGRAM MEMORY   */
    RFERAM     (RWX) : origin = 0x45CA0000, length = 0x00001000 /* 4K PROGRAM MEMORY   */
    MDMRAM     (RWX) : origin = 0x45CC0000, length = 0x00000100 /* 256B PROGRAM MEMORY */
}

/* Section allocation in memory */
SECTIONS
{
    /* Flash */
    GROUP {
        /* The first 2 flash sectors (8KB) are reserved for metadata used by the
         * bootloader.
         */
        .reserved:                   { . += RESERVED_FLASH_SIZE; } (NOLOAD)
        .resetVecs:                  {} PALIGN(4)
    } > FLASH_INT_VEC
    .text           :   > FLASH PALIGN(4)
    .text.__TI      : { *(.text.__TI*) } > FLASH PALIGN(4)
    .const          :   > FLASH PALIGN(4)
    .constdata      :   > FLASH PALIGN(4)
    .rodata         :   > FLASH PALIGN(4)
    .binit          :   > FLASH PALIGN(4)
    .cinit          :   > FLASH PALIGN(4)
    .pinit          :   > FLASH PALIGN(4)
    .init_array     :   > FLASH PALIGN(4)
    .emb_text       :   > FLASH PALIGN(4)

    /* Boot report shared section required by the XMEM driver */
    GROUP {
        .boot_report_shared_section: { _Boot_report_address = start(BOOT_REPORT_SHARED_MEM);} palign(4) (NOLOAD)
    } > BOOT_REPORT_SHARED_MEM

    /* Code RAM */
    .ramVecs        :   > CRAM_BASE, type = NOLOAD, ALIGN(512)
    .TI.ramfunc     : {} load=FLASH, run=CRAM, table(BINIT)

    /* Sections for specifically placing data in internal memory. Try to fit as
     * much as possible into faster TCM memory, and the remainder into DRAM.
     */
    GROUP {
        .internalRAM:        {} align(4) /* Should not be used */
        .internalRAM.bss:    {} align(4)
        .internalRAM.data:   {} align(4)
    } >> TCM_DRAM_NON_SECURE | DRAM

    .heap  > DRAM
    .stack > DRAM HIGH


    /* Split the data and bss sections across TCM, DRAM, and PSRAM. Try to fit as
     * much as possible into faster TCM memory, then DRAM, and lastly PSRAM.
     */
    GROUP {
        .bss:    {} align(4)   /* This is where uninitialized globals go */
        .data:   {} align(4)   /* This is where initialized globals and static go */
    } >> TCM_DRAM_NON_SECURE | DRAM | PSRAM

    /* Special sections for explicitly placing data in external memory */
    .externalRAM      :   > PSRAM /* Should not be used */
    .externalRAM.bss  :   > PSRAM
    .externalRAM.data :   > PSRAM

    .cio            :   > DRAM
    .ARM.exidx      :   > DRAM
    .ARM.extab      :   > DRAM
    .vtable         :   > DRAM
    .args           :   > DRAM

    /* Other memory regions */
    .ctx_ull        :   > PHY_CTX
    .scr_ull        :   > PHY_SCR
    .cperam         :   > CPERAM         /* CPE CODE */
    .rferam         :   > RFERAM         /* RFE CODE */
    .mceram         :   > MCERAM         /* MCE CODE */
    .mdmram         :   > MDMRAM         /* MDM CODE */
    .db_mem         :   > DB_MEM
    .perif_if       :   > PERIPH_API
    .mem_pool       :   > MEM_POOL

    .log_data       :   > LOG_DATA, type = COPY
    .log_ptr        : { *(.log_ptr*) } > LOG_PTR align 4, type = COPY
}
