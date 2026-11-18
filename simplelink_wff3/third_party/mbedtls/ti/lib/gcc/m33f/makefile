# Bring in common target-independent definitions
include ../../../defs.mak

# Enable local overrides via a top-directory 'products.mak'
# -include ../../../products.mak

CC = "$(GCC_ARMCOMPILER)/bin/arm-none-eabi-gcc"
AR = "$(GCC_ARMCOMPILER)/bin/arm-none-eabi-gcc-ar"

GCC_M33_CFLAGS= $(POSIX_INCS_GCC) -mcpu=cortex-m33 -mfloat-abi=hard -mfpu=fpv5-sp-d16 \
				-Wno-builtin-requires-header -g -Ofast -ffunction-sections \
        		-fdata-sections -g -Wall -std=c99 -c

CFLAGS_HSM = $(INCS_HSM) $(GCC_M33_CFLAGS)

ARFLAGS = -c -q

DEFAULT_OBJ_DIR = default
OBJS_DEFAULT = $(addprefix $(DEFAULT_OBJ_DIR)/,$(OBJS_HSM))

vpath %.c ../../../../library

vpath %.c ../../../port

$(DEFAULT_OBJ_DIR)/%.obj: %.c | $(DEFAULT_OBJ_DIR)
	@ echo "#"
	@ echo "# Building $@"
	$(CC) $(CFLAGS_HSM) $< -o $@

all: mbedtls.a

$(DEFAULT_OBJ_DIR):
	mkdir $@

clean:
	@ rm -rf $(DEFAULT_OBJ_DIR)
	@ $(RM) *.a

mbedtls.a: $(OBJS_DEFAULT)
	@ echo "#"
	@ echo "# Building $@"
	$(AR) $(ARFLAGS) $@ $^