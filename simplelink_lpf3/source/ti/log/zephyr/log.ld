/*
 * TI Logging framework metadata sections.
 *
 * Placed in the ARM external memory map (0x60000000 - 0x9FFFFFFF).
 * These addresses are intentionally off-target: data lives in the ELF
 * for host tools (Wireshark, TI ROV) but is never loaded to the device.
 * ARM memory map: https://developer.arm.com/documentation/ddi0337/e/memory-map/about-the-memory-map
 *
 */

.log_data 0x90000000 (COPY) : {
    KEEP(*(.log_data))
}
ASSERT(SIZEOF(.log_data) <= 0x40000, "ERROR: .log_data exceeds 256KB")

.log_ptr 0x94000008 (COPY) : {
    KEEP(*(.log_ptr*))
    . = ALIGN(4);
}
ASSERT(SIZEOF(.log_ptr) <= 0x40000, "ERROR: .log_ptr exceeds 256KB")
