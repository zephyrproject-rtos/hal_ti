/*
     * UDMALPF3_CONFIG_BASE below must match UDMALPF3_CONFIG_BASE defined
     * by ti/drivers/dma/UDMALPF3.h
     * The user is allowed to change UDMALPF3_CONFIG_BASE to move it away from
     * the default address 0x2000_0400, but remember it must be 1024 bytes aligned.
     */
    UDMALPF3_CONFIG_BASE = 0x20000400;

    /*
     * Define absolute addresses for the DMA channels.
     * DMA channels must always be allocated at a fixed offset from the DMA base address.
     * --------- DO NOT MODIFY -----------
     */
    DMA_CHANNEL0_CONTROL_TABLE_ENTRY_ADDRESS = (UDMALPF3_CONFIG_BASE + 0x00);
    DMA_CHANNEL1_CONTROL_TABLE_ENTRY_ADDRESS = (UDMALPF3_CONFIG_BASE + 0x10);
    DMA_CHANNEL2_CONTROL_TABLE_ENTRY_ADDRESS = (UDMALPF3_CONFIG_BASE + 0x20);
    DMA_CHANNEL3_CONTROL_TABLE_ENTRY_ADDRESS = (UDMALPF3_CONFIG_BASE + 0x30);
    DMA_CHANNEL4_CONTROL_TABLE_ENTRY_ADDRESS = (UDMALPF3_CONFIG_BASE + 0x40);
    DMA_CHANNEL5_CONTROL_TABLE_ENTRY_ADDRESS = (UDMALPF3_CONFIG_BASE + 0x50);
    DMA_CHANNEL6_CONTROL_TABLE_ENTRY_ADDRESS = (UDMALPF3_CONFIG_BASE + 0x60);
    DMA_CHANNEL7_CONTROL_TABLE_ENTRY_ADDRESS = (UDMALPF3_CONFIG_BASE + 0x70);

    /* Device has 8 DMA channels => the alt. control table is at offset 0x80 */
    DMA_CHANNEL0_ALT_CONTROL_TABLE_ENTRY_ADDRESS = (UDMALPF3_CONFIG_BASE + 0x80);
    DMA_CHANNEL1_ALT_CONTROL_TABLE_ENTRY_ADDRESS = (UDMALPF3_CONFIG_BASE + 0x90);
    DMA_CHANNEL2_ALT_CONTROL_TABLE_ENTRY_ADDRESS = (UDMALPF3_CONFIG_BASE + 0xA0);
    DMA_CHANNEL3_ALT_CONTROL_TABLE_ENTRY_ADDRESS = (UDMALPF3_CONFIG_BASE + 0xB0);
    DMA_CHANNEL4_ALT_CONTROL_TABLE_ENTRY_ADDRESS = (UDMALPF3_CONFIG_BASE + 0xC0);
    DMA_CHANNEL5_ALT_CONTROL_TABLE_ENTRY_ADDRESS = (UDMALPF3_CONFIG_BASE + 0xD0);
    DMA_CHANNEL6_ALT_CONTROL_TABLE_ENTRY_ADDRESS = (UDMALPF3_CONFIG_BASE + 0xE0);
    DMA_CHANNEL7_ALT_CONTROL_TABLE_ENTRY_ADDRESS = (UDMALPF3_CONFIG_BASE + 0xF0);


    /*
     * Allocate Channel n descriptors at absolute addresses.
     * --------- DO NOT MODIFY -----------
     */
    UDMALPF3_channel0ControlTableEntry_is_placed = 0;
    .dmaChannel0ControlTableEntry DMA_CHANNEL0_CONTROL_TABLE_ENTRY_ADDRESS (NOLOAD) : AT (DMA_CHANNEL0_CONTROL_TABLE_ENTRY_ADDRESS) {*(.dmaChannel0ControlTableEntry)} > RAM
    UDMALPF3_channel1ControlTableEntry_is_placed = 0;
    .dmaChannel1ControlTableEntry DMA_CHANNEL1_CONTROL_TABLE_ENTRY_ADDRESS (NOLOAD) : AT (DMA_CHANNEL1_CONTROL_TABLE_ENTRY_ADDRESS) {*(.dmaChannel1ControlTableEntry)} > RAM
    UDMALPF3_channel2ControlTableEntry_is_placed = 0;
    .dmaChannel2ControlTableEntry DMA_CHANNEL2_CONTROL_TABLE_ENTRY_ADDRESS (NOLOAD) : AT (DMA_CHANNEL2_CONTROL_TABLE_ENTRY_ADDRESS) {*(.dmaChannel2ControlTableEntry)} > RAM
    UDMALPF3_channel3ControlTableEntry_is_placed = 0;
    .dmaChannel3ControlTableEntry DMA_CHANNEL3_CONTROL_TABLE_ENTRY_ADDRESS (NOLOAD) : AT (DMA_CHANNEL3_CONTROL_TABLE_ENTRY_ADDRESS) {*(.dmaChannel3ControlTableEntry)} > RAM
    UDMALPF3_channel4ControlTableEntry_is_placed = 0;
    .dmaChannel4ControlTableEntry DMA_CHANNEL4_CONTROL_TABLE_ENTRY_ADDRESS (NOLOAD) : AT (DMA_CHANNEL4_CONTROL_TABLE_ENTRY_ADDRESS) {*(.dmaChannel4ControlTableEntry)} > RAM
    UDMALPF3_channel5ControlTableEntry_is_placed = 0;
    .dmaChannel5ControlTableEntry DMA_CHANNEL5_CONTROL_TABLE_ENTRY_ADDRESS (NOLOAD) : AT (DMA_CHANNEL5_CONTROL_TABLE_ENTRY_ADDRESS) {*(.dmaChannel5ControlTableEntry)} > RAM
    UDMALPF3_channel6ControlTableEntry_is_placed = 0;
    .dmaChannel6ControlTableEntry DMA_CHANNEL6_CONTROL_TABLE_ENTRY_ADDRESS (NOLOAD) : AT (DMA_CHANNEL6_CONTROL_TABLE_ENTRY_ADDRESS) {*(.dmaChannel6ControlTableEntry)} > RAM
    UDMALPF3_channel7ControlTableEntry_is_placed = 0;
    .dmaChannel7ControlTableEntry DMA_CHANNEL7_CONTROL_TABLE_ENTRY_ADDRESS (NOLOAD) : AT (DMA_CHANNEL7_CONTROL_TABLE_ENTRY_ADDRESS) {*(.dmaChannel7ControlTableEntry)} > RAM

    UDMALPF3_channel0AltControlTableEntry_is_placed = 0;
    .dmaChannel0AltControlTableEntry DMA_CHANNEL0_ALT_CONTROL_TABLE_ENTRY_ADDRESS (NOLOAD) : AT (DMA_CHANNEL0_ALT_CONTROL_TABLE_ENTRY_ADDRESS) {*(.dmaChannel0AltControlTableEntry)} > RAM
    UDMALPF3_channel1AltControlTableEntry_is_placed = 0;
    .dmaChannel1AltControlTableEntry DMA_CHANNEL1_ALT_CONTROL_TABLE_ENTRY_ADDRESS (NOLOAD) : AT (DMA_CHANNEL1_ALT_CONTROL_TABLE_ENTRY_ADDRESS) {*(.dmaChannel1AltControlTableEntry)} > RAM
    UDMALPF3_channel2AltControlTableEntry_is_placed = 0;
    .dmaChannel2AltControlTableEntry DMA_CHANNEL2_ALT_CONTROL_TABLE_ENTRY_ADDRESS (NOLOAD) : AT (DMA_CHANNEL2_ALT_CONTROL_TABLE_ENTRY_ADDRESS) {*(.dmaChannel2AltControlTableEntry)} > RAM
    UDMALPF3_channel3AltControlTableEntry_is_placed = 0;
    .dmaChannel3AltControlTableEntry DMA_CHANNEL3_ALT_CONTROL_TABLE_ENTRY_ADDRESS (NOLOAD) : AT (DMA_CHANNEL3_ALT_CONTROL_TABLE_ENTRY_ADDRESS) {*(.dmaChannel3AltControlTableEntry)} > RAM
    UDMALPF3_channel4AltControlTableEntry_is_placed = 0;
    .dmaChannel4AltControlTableEntry DMA_CHANNEL4_ALT_CONTROL_TABLE_ENTRY_ADDRESS (NOLOAD) : AT (DMA_CHANNEL4_ALT_CONTROL_TABLE_ENTRY_ADDRESS) {*(.dmaChannel4AltControlTableEntry)} > RAM
    UDMALPF3_channel5AltControlTableEntry_is_placed = 0;
    .dmaChannel5AltControlTableEntry DMA_CHANNEL5_ALT_CONTROL_TABLE_ENTRY_ADDRESS (NOLOAD) : AT (DMA_CHANNEL5_ALT_CONTROL_TABLE_ENTRY_ADDRESS) {*(.dmaChannel5AltControlTableEntry)} > RAM
    UDMALPF3_channel6AltControlTableEntry_is_placed = 0;
    .dmaChannel6AltControlTableEntry DMA_CHANNEL6_ALT_CONTROL_TABLE_ENTRY_ADDRESS (NOLOAD) : AT (DMA_CHANNEL6_ALT_CONTROL_TABLE_ENTRY_ADDRESS) {*(.dmaChannel6AltControlTableEntry)} > RAM
    UDMALPF3_channel7AltControlTableEntry_is_placed = 0;
    .dmaChannel7AltControlTableEntry DMA_CHANNEL7_ALT_CONTROL_TABLE_ENTRY_ADDRESS (NOLOAD) : AT (DMA_CHANNEL7_ALT_CONTROL_TABLE_ENTRY_ADDRESS) {*(.dmaChannel7AltControlTableEntry)} > RAM
