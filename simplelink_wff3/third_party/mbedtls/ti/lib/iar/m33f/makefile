# Bring in common target-independent definitions
include ../../../defs.mak

# Enable local overrides via a top-directory 'products.mak'
# -include ../../../products.mak

CC = "$(IAR_ARMCOMPILER)/bin/iccarm"
AR = "$(IAR_ARMCOMPILER)/bin/iarchive"

IAR_M33F_CFLAGS = "-I$(IAR_ARMCOMPILER)/inc" --silent --aeabi --cpu=Cortex-M33.fp \
        --diag_suppress=Pa050 --endian=little -e --fpu=FPv5_sp --thumb -Ohs

CFLAGS_HSM = $(INCS_HSM) $(IAR_M33F_CFLAGS)
DEFAULT_OBJ_DIR = default
OBJS_DEFAULTDIR = $(addprefix $(DEFAULT_OBJ_DIR)/,$(OBJS_HSM))

vpath %.c ../../../../library

vpath %.c ../../../port

$(DEFAULT_OBJ_DIR)/%.obj: %.c | $(DEFAULT_OBJ_DIR)
	@ echo "#"
	@ echo "# Building $@"
	$(CC) $(CFLAGS_HSM) $(POSIX_INCS_IAR) $< -o $@

all: mbedtls.a

$(DEFAULT_OBJ_DIR):
	mkdir $@

clean:
	@ rm -rf $(DEFAULT_OBJ_DIR)
	@ $(RM) *.a

mbedtls.a: $(OBJS_DEFAULTDIR)
	@ echo "#"
	@ echo "# Building $@"
	@ $(RM) $@
	$(AR) $@ $^