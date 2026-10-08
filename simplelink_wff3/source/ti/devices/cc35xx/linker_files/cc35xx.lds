/******************************************************************************
*  @file      cc35xx.lds
*  @brief     CC35XX linker configuration file for GNU toolchain.
*
*  Copyright (c) 2024-2026 Texas Instruments Incorporated
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
*  3) Neither the name of the copyright holder nor the names of its
*     contributors may be used to endorse or promote products derived from this
*     software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
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

/* Include SysConfig-generated linker file */
INCLUDE "ti_build_linker.lds.toolbox"

STACKSIZE = 2048;
HEAPSIZE = 16384;
FLASH_BASE          = 0x14000000;
FLASH_RESERVED_SIZE = 0x2000;
FLASH_INT_VEC_SIZE  = 0x2400;
FLASH_MAIN_SIZE     = build_linker_toolbox_FLASH_SIZE - FLASH_RESERVED_SIZE - FLASH_INT_VEC_SIZE;
DRAM_SIZE           = 0x80000 - 0x100 - 0xCB0;

MEMORY
{
    /* Reserved flash region at the start of the external flash used for
     * bootloader metadata and for padding between bootloader metadata and
     * the vector table in flash, which will be placed at the start of the
     * FLASH memory region.
     */
    RESERVED_FLASH (R) : ORIGIN = FLASH_BASE, LENGTH = FLASH_RESERVED_SIZE
    /* Application stored in and executes from external flash */
    FLASH_INT_VEC (RX) : ORIGIN = FLASH_BASE + FLASH_RESERVED_SIZE, LENGTH = FLASH_INT_VEC_SIZE
    FLASH (RX) : ORIGIN = FLASH_BASE + FLASH_RESERVED_SIZE + FLASH_INT_VEC_SIZE, LENGTH = FLASH_MAIN_SIZE
    /* Application uses internal CRAM for code/data */
    CRAM (RWX) : ORIGIN = 0x00000000, LENGTH = 0x00008000
    /* Fast memory that can be used as cache memory */
    TCM_DRAM_NON_SECURE   (RWX) : ORIGIN = 0x20000000, LENGTH = (build_linker_toolbox_PSRAM_SIZE == 0 ? 0x1FFFF : 0x0FFFF)  /* 64KB for PSRAM */  /* 128KB for NO-PSRAM */
    /* Application uses internal DRAM for data */
    CONNECTIVITY_SHARED_MEM (RWX) : ORIGIN = 0x28000000, LENGTH = 0x100
    BOOT_REPORT_SHARED_MEM (RWX) : ORIGIN = 0x28000100, LENGTH = 0xCB0
    DRAM (RWX) : ORIGIN = 0x28000DB0, LENGTH = DRAM_SIZE
    /* PSRAM Configured by sysconfig. Normally our launchpads are not equipped with PSRAM and the length will be set to 1 */
    PSRAM (RW) : ORIGIN = 0x60000000, LENGTH = (build_linker_toolbox_PSRAM_SIZE > 0 ? build_linker_toolbox_PSRAM_SIZE : 0x1)

    /* Explicitly placed off target for the storage of logging data.
     * The ARM memory map allocates 1 GB of external memory from 0x60000000 - 0x9FFFFFFF.
     * Unlikely that all of this will be used, so we are using the upper parts of the region.
     * ARM memory map: https://developer.arm.com/documentation/ddi0337/e/memory-map/about-the-memory-map*/
    LOG_DATA (R) : ORIGIN = 0x90000000, LENGTH = 0x40000
    LOG_PTR  (R) : ORIGIN = 0x94000008, LENGTH = 0x40000

    /* Other memory regions */
    PERIPH_API (RW)  : ORIGIN = 0x45602000, LENGTH = 0x0000001F
    MEM_POOL   (RW)  : ORIGIN = 0x28044000, LENGTH = 0x00004000
    DB_MEM     (RW)  : ORIGIN = 0x45A80000, LENGTH = 0x0000FFFF
    PHY_CTX    (RW)  : ORIGIN = 0x45900000, LENGTH = 0x00010000
    PHY_SCR    (RW)  : ORIGIN = 0x45910000, LENGTH = 0x00004800
    CPERAM     (RWX) : ORIGIN = 0x45C00000, LENGTH = 0x00010000 /* 64K PROGRAM MEMORY  */
    MCERAM     (RWX) : ORIGIN = 0x45C80000, LENGTH = 0x00001000 /* 4K PROGRAM MEMORY   */
    RFERAM     (RWX) : ORIGIN = 0x45CA0000, LENGTH = 0x00001000 /* 4K PROGRAM MEMORY   */
    MDMRAM     (RWX) : ORIGIN = 0x45CC0000, LENGTH = 0x00000100 /* 256B PROGRAM MEMORY */
}

SECTIONS
{
    /* Reserved for bootloader metadata */
    .reserved (FLASH_BASE) (NOLOAD) : AT (FLASH_BASE) {
        . += FLASH_RESERVED_SIZE;
    } > RESERVED_FLASH

    /* Vector table in flash */
    .resetVecs (FLASH_BASE + FLASH_RESERVED_SIZE) : AT (FLASH_BASE + FLASH_RESERVED_SIZE) {
        KEEP (*(.resetVecs))
    } > FLASH_INT_VEC

    /* Vector table in RAM.
     * Section from interrupt.c (driverlib) */
    .ramVecs (NOLOAD) : ALIGN(512) {
        KEEP (*(.ramVecs))
        . = ALIGN(512);
    } > CRAM

    .text : {
        CREATE_OBJECT_SYMBOLS
        *(.text)
        *(.text.*)
        . = ALIGN(0x4);
        KEEP (*(.ctors))
        . = ALIGN(0x4);
        KEEP (*(.dtors))
        . = ALIGN(0x4);
        __init_array_start = .;
        KEEP (*(.init_array*))
        __init_array_end = .;
        *(.init)
        *(.fini*)
    } > FLASH AT> FLASH

    PROVIDE (__etext = .);
    PROVIDE (_etext = .);
    PROVIDE (etext = .);

    /* Boot report shared section required by the XMEM driver */
    .boot_report_shared_section (NOLOAD) : ALIGN(4) {
        _Boot_report_address = .;
    } > BOOT_REPORT_SHARED_MEM

    .rodata : {
        *(.rodata)
        *(.rodata.*)
        *(.rodata_*)
        KEEP (*(.timestampPFormat))
    } > FLASH AT> FLASH

    .cinit : {
        *(.cinit)
    } > FLASH

    .binit : {
        *(.binit)
    } > FLASH

    /* TI RAM functions - code that runs from RAM */
    .TI.ramfunc : ALIGN(4) {
        __ramfunc_load__ = LOADADDR(.TI.ramfunc);
        __ramfunc_start__ = .;
        *(.TI.ramfunc)
        __ramfunc_end__ = .;
    } > CRAM AT> FLASH

    .tcm_data : ALIGN(4) {
        __tcm_data_load__ = LOADADDR (.tcm_data);
        __tcm_data_start__ = .;
        *(.data)
        *(.data.*)
        *(.internalRAM.data)
        . = ALIGN (4);
        __tcm_data_end__ = .;
    } > TCM_DRAM_NON_SECURE AT> FLASH

    .data : ALIGN(4) {
        __data_load__ = LOADADDR (.data);
        __data_start__ = .;
        *(.data)
        *(.data.*)
        *(.internalRAM.data)
        . = ALIGN (4);
        __data_end__ = .;
    } > DRAM AT> FLASH

    .psram_data : ALIGN(4) {
        __psram_data_load__ = LOADADDR (.psram_data);
        __psram_data_start__ = .;
        *(.data)
        *(.data.*)
        *(.externalRAM.data)
        . = ALIGN (4);
        __psram_data_end__ = .;
    } > PSRAM AT> FLASH

    .ARM.exidx : {
        __exidx_start = .;
        *(.ARM.exidx* .gnu.linkonce.armexidx.*)
        __exidx_end = .;
    } > FLASH AT> FLASH

    .ARM.extab : {
        *(.ARM.extab* .gnu.linkonce.armextab.*)
    } > FLASH AT> FLASH

    .bss (NOLOAD) : {
        __bss_start__ = .;
        *(.shbss)
        *(.bss)
        *(.bss.*)
        *(.internalRAM) /* Should not be used */
        *(.internalRAM.bss)
        *(COMMON)
        . = ALIGN (4);
        __bss_end__ = .;
    } > DRAM

    .psram_bss (NOLOAD) : {
        __psram_bss_start__ = .;
        *(.shbss)
        *(.bss)
        *(.bss.*)
        *(.externalRAM) /* Should not be used */
        *(.externalRAM.bss)
        *(COMMON)
        . = ALIGN (4);
        __psram_bss_end__ = .;
    } > PSRAM

    .heap (NOLOAD) : {
        __heap_start__ = .;
        end = __heap_start__;
        _end = end;
        __end = end;
        . += HEAPSIZE;
        KEEP(*(.heap))
        __heap_end__ = .;
        __HeapLimit = __heap_end__;
    } > DRAM

    .stack (NOLOAD) : ALIGN(0x8) {
        _stack = .;
        __stack = .;
        KEEP(*(.stack))
        . += STACKSIZE;
        _stack_end = .;
        __stack_end = .;
    } > DRAM

    .log_data (COPY) : {
        KEEP (*(.log_data))
    } > LOG_DATA
    .log_ptr (COPY) : {
        KEEP (*(.log_ptr*))
    } > LOG_PTR
}

ENTRY(resetISR)
