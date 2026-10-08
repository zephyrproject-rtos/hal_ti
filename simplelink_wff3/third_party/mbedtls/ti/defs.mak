#
# By default, look for an SDK-provided imports.mak file to provide
# dependency locations (e.g. toolchains).
#
# Note, this SDK's imports.mak inclusion is optional (the leading '-'
# when including).  If exists, we'll use variables in it, else the
# user will have to set these variables themselves.  The variables
# this build system may use, depending on what you're trying to build, include:
#    CCS_ARMCOMPILER     - CCS ARM toolchain
#    IAR_ARMCOMPILER     - IAR ARM toolchain
#    GCC_ARMCOMPILER     - GCC ARM toolchain
#    GCC_ARM64COMPILER   - GCC 64-bit ARM toolchain
#    CCS_C6XCOMPILER     - CCS C6x toolchain
#    TICLANG_ARMCOMPILER - TI ARM CLANG toolchain
#    RM                  - delete a file in an OS-independent way
#    RMDIR               - delete a directory in an OS-independent way
#
# Note that this SDK_INSTALL_DIR path is relative to the
# makefiles including this defs.mak, which are 3 directories deeper
# (lib/<toolchain>/<isa>) than this file.
# NOTE: This assumes the same folder structure for SDKs across
# CC13XX/CC26XX devices and CC27XX/CC35XX devices.

# When developing outside of an SDK context, the SDK_INSTALL_DIR
# should be manually set to a local SDK installation.
SDK_INSTALL_DIR ?= $(abspath ../../../../../../..)

# Retrieve variables defined in the SDK's imports.mak, such as compiler paths
include $(SDK_INSTALL_DIR)/imports.mak

# Default POSIX is in the SDK's source/ directory, but users can
# override this
POSIX_ROOT = $(SDK_INSTALL_DIR)/source

OBJS_X509= \
	   x509.obj \
	   x509_create.obj \
	   x509_crl.obj \
	   x509_crt.obj \
	   x509_csr.obj \
	   x509write.obj \
	   x509write_crt.obj \
	   x509write_csr.obj \
	   pkcs7.obj \
	   # This line is intentionally left blank

OBJS_TLS= \
	  debug.obj \
	  mps_reader.obj \
	  mps_trace.obj \
	  net_sockets.obj \
	  ssl_cache.obj \
	  ssl_ciphersuites.obj \
	  ssl_client.obj \
	  ssl_cookie.obj \
	  ssl_debug_helpers_generated.obj \
	  ssl_msg.obj \
	  ssl_ticket.obj \
	  ssl_tls.obj \
	  ssl_tls12_client.obj \
	  ssl_tls12_server.obj \
	  ssl_tls13_keys.obj \
	  ssl_tls13_client.obj \
	  ssl_tls13_server.obj \
	  ssl_tls13_generic.obj \
	  # This line is intentionally left blank

# psa_util is included for some conversions between legacy and PSA crypto APIs
OBJS_CRYPTO= \
	  aes.obj \
	  aesni.obj \
	  aesce.obj \
	  aria.obj \
	  asn1parse.obj \
	  asn1write.obj \
	  base64.obj \
	  bignum.obj \
	  bignum_core.obj \
	  bignum_mod.obj \
	  bignum_mod_raw.obj \
	  block_cipher.obj \
	  camellia.obj \
	  ccm.obj \
	  chacha20.obj \
	  chachapoly.obj \
	  cipher.obj \
	  cipher_wrap.obj \
	  cmac.obj \
	  constant_time.obj \
	  ctr_drbg.obj \
	  des.obj \
	  dhm.obj \
	  ecdh.obj \
	  ecdsa.obj \
	  ecjpake.obj \
	  ecp.obj \
	  ecp_curves.obj \
	  ecp_curves_new.obj \
	  entropy.obj \
	  entropy_poll.obj \
	  error.obj \
	  gcm.obj \
	  hkdf.obj \
	  hmac_drbg.obj \
	  lmots.obj \
	  lms.obj \
	  md.obj \
	  md5.obj \
	  nist_kw.obj \
	  oid.obj \
	  padlock.obj \
	  pem.obj \
	  pk.obj \
	  pk_ecc.obj \
	  pk_wrap.obj \
	  pkcs12.obj \
	  pkcs5.obj \
	  pkparse.obj \
	  pkwrite.obj \
	  poly1305.obj \
	  psa_crypto_aead.obj \
	  psa_crypto_cipher.obj \
	  psa_crypto_ffdh.obj \
	  psa_crypto_hash.obj \
	  psa_crypto_mac.obj \
	  psa_crypto_rsa.obj \
	  psa_util.obj \
	  ripemd160.obj \
	  rsa.obj \
	  rsa_alt_helpers.obj \
	  sha1.obj \
	  sha256.obj \
	  sha512.obj \
	  sha3.obj \
	  timing.obj \
	  # This line is intentionally left blank


OBJS_HSM = \
		$(OBJS_X509) \
		$(OBJS_TLS) \
		$(OBJS_CRYPTO) \
		memory_buffer_alloc.obj \
		platform.obj \
		platform_util.obj \
		threading.obj \
		threading_alt.obj \
		version.obj \
		version_features.obj \
		# This line is intentionally left blank

# For development outside of an SDK context: Add the following two include
# paths:
# -I$(SECURE_DRIVERS_LPF3_INSTALL_DIR)/source \
# -I$(HSMDDK_INSTALL_DIR)/source
# These paths are not needed in an SDK context, because the POSIX_ROOT
# include path is equivalent to it in the SDK. Outside of the SDK,
# the paths must start from separate conan packages.

INCS_GENERAL = -I../../../../include \
			   -I../../../../ti/configs \
			   -I../../../../ti/port \

# For development outside of an SDK context: If using the LPF3 SDK for the
# SDK_INSTALL_DIR change -DDeviceFamily_CC35XX to an LPF3 device family

INCS_HSM = $(INCS_GENERAL) \
		   -DMBEDTLS_CONFIG_FILE='"config-hsm.h"' \
		   -DMBEDTLS_PSA_CRYPTO_CONFIG_FILE='"config-psa-crypto-hsm.h"' \
		   -DDeviceFamily_CC35XX


POSIX_INCS_CCS = -I$(POSIX_ROOT)/ti/posix/ccs -I$(POSIX_ROOT)
POSIX_INCS_IAR = -I$(POSIX_ROOT)/ti/posix/iar -I$(POSIX_ROOT)
POSIX_INCS_GCC = -I$(POSIX_ROOT)/ti/posix/gcc -I$(POSIX_ROOT)
POSIX_INCS_TICLANG = -I$(POSIX_ROOT)/ti/posix/ticlang -I$(POSIX_ROOT)