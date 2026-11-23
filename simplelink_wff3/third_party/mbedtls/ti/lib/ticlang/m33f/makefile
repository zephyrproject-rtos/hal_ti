# Bring in common target-independent definitions
include ../../../defs.mak

# Enable local overrides via a top-directory 'products.mak'
#-include ../../../products.mak

CC = "$(TICLANG_ARMCOMPILER)/bin/tiarmclang"
AR = "$(TICLANG_ARMCOMPILER)/bin/tiarmar"

TICLANG_M33F_CFLAGS = $(POSIX_INCS_TICLANG) \
	-mcpu=cortex-m33 -mfloat-abi=hard -mfpu=fpv5-sp-d16 \
	-g -Ofast

CFLAGS_HSM = $(INCS_HSM) $(TICLANG_M33F_CFLAGS)

ARFLAGS = -c -q

DEFAULT_OBJ_DIR = default
OBJS_DEFAULT = $(addprefix $(DEFAULT_OBJ_DIR)/,$(OBJS_HSM))

vpath %.c ../../../../library

vpath %.c ../../../port

$(DEFAULT_OBJ_DIR)/%.obj: %.c | $(DEFAULT_OBJ_DIR)
	@ echo "#"
	@ echo "# Building $@"
	$(CC) -c $(CFLAGS_HSM) $< -o $@

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