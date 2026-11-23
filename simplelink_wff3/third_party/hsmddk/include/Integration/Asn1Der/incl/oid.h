/**
 * @file oid.h
 *
 * @brief Object Identifier (OID) database
 */

/* -------------------------------------------------------------------------- */
/*                                                                            */
/*   Module        : DDK-130_bsd                                              */
/*   Version       : 4.1.1                                                    */
/*   Configuration : DDK_EIP130_BSD                                           */
/*                                                                            */
/*   Date          : 2023-Mar-10                                              */
/*                                                                            */
/* Copyright (c) 2014-2023 by Rambus, Inc. and/or its subsidiaries.           */
/*                                                                            */
/* Redistribution and use in source and binary forms, with or without         */
/* modification, are permitted provided that the following conditions are     */
/* met:                                                                       */
/*                                                                            */
/* 1. Redistributions of source code must retain the above copyright          */
/* notice, this list of conditions and the following disclaimer.              */
/*                                                                            */
/* 2. Redistributions in binary form must reproduce the above copyright       */
/* notice, this list of conditions and the following disclaimer in the        */
/* documentation and/or other materials provided with the distribution.       */
/*                                                                            */
/* 3. Neither the name of the copyright holder nor the names of its           */
/* contributors may be used to endorse or promote products derived from       */
/* this software without specific prior written permission.                   */
/*                                                                            */
/* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS        */
/* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT          */
/* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR      */
/* A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT       */
/* HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,     */
/* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT           */
/* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,      */
/* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY      */
/* THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT        */
/* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE      */
/* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.       */
/* -------------------------------------------------------------------------- */

#ifndef INCLUDE_GUARD_OID_H
#define INCLUDE_GUARD_OID_H

/* Top level OID tuples */
#define OID_ISO_MEMBER_BODIES           "\x2a"          /* {iso(1) member-body(2)} */
#define OID_ISO_IDENTIFIED_ORG          "\x2b"          /* {iso(1) identified-organization(3)} */
#define OID_ISO_CCITT_DS                "\x55"          /* {joint-iso-ccitt(2) ds(5)} */
#define OID_ISO_ITU_COUNTRY             "\x60"          /* {joint-iso-itu-t(2) country(16)} */

/* ISO Member bodies OID parts */
#define OID_COUNTRY_US                  "\x86\x48"      /* {us(840)} */
#define OID_ORG_RSA_DATA_SECURITY       "\x86\xf7\x0d"  /* {rsadsi(113549)} */
#define OID_RSA_COMPANY                 OID_ISO_MEMBER_BODIES OID_COUNTRY_US OID_ORG_RSA_DATA_SECURITY
#define OID_ORG_ANSI_X9_62              "\xce\x3d"      /* ansi-X9-62(10045) */
#define OID_ANSI_X9_62                  OID_ISO_MEMBER_BODIES OID_COUNTRY_US OID_ORG_ANSI_X9_62

/* ISO Identified organization OID parts */
#define OID_ORG_DOD                     "\x06"          /* {dod(6)} */
#define OID_ORG_OIW                     "\x0e"
#define OID_OIW_SECSIG                  OID_ORG_OIW "\x03"
#define OID_OIW_SECSIG_ALG              OID_OIW_SECSIG "\x02"
#define OID_OIW_SECSIG_SHA1             OID_OIW_SECSIG_ALG "\x1a"
#define OID_ORG_CERTICOM                "\x81\x04"      /* certicom(132) */
#define OID_CERTICOM                    OID_ISO_IDENTIFIED_ORG OID_ORG_CERTICOM
#define OID_ORG_TELETRUST               "\x24"          /* teletrust(36) */
#define OID_TELETRUST                   OID_ISO_IDENTIFIED_ORG OID_ORG_TELETRUST

/* ISO ITU OID parts */
#define OID_ORGANIZATION                "\x01"          /* {organization(1)} */
#define OID_ISO_ITU_US_ORG              OID_ISO_ITU_COUNTRY OID_COUNTRY_US OID_ORGANIZATION
                                                        /* {joint-iso-itu-t(2) country(16) us(840) organization(1)} */
#define OID_ORG_GOV                     "\x65"          /* {gov(101)} */
#define OID_GOV                         OID_ISO_ITU_US_ORG OID_ORG_GOV
                                                        /* {joint-iso-itu-t(2) country(16) us(840) organization(1) gov(101)} */
#define OID_ORG_NETSCAPE                "\x86\xF8\x42"  /* {netscape(113730)} */
#define OID_NETSCAPE                    OID_ISO_ITU_US_ORG OID_ORG_NETSCAPE
                                                        /* Netscape OID {joint-iso-itu-t(2) country(16) us(840) organization(1) netscape(113730)} */

/* ISO arc for standard certificate and CRL extensions */
#define OID_ID_CE                       OID_ISO_CCITT_DS "\x1D"
                                                        /* {joint-iso-ccitt(2) ds(5) 29} */
#define OID_NIST_ALG                    OID_GOV "\x03\x04"
                                                        /* {joint-iso-itu-t(2) country(16) us(840) organization(1) gov(101) csor(3) nistAlgorithm(4)} */

/* Private Internet Extensions */
#define OID_INTERNET                    OID_ISO_IDENTIFIED_ORG OID_ORG_DOD "\x01"
                                                        /* {iso(1) identified-organization(3) dod(6) internet(1)} */
#define OID_PRIVATE_ENTERPRISE          OID_INTERNET "\x04\x01"
                                                        /* {iso(1) identified-organization(3) dod(6) internet(1) private(4) enterprise(1)} */
#define OID_PKIX                        OID_INTERNET "\x05\x05\x07"
                                                        /* {iso(1) identified-organization(3) dod(6) internet(1) security(5) mechanisms(5) pkix(7)} */

/* Arc for standard naming attributes */
#define OID_AT                          OID_ISO_CCITT_DS "\x04"
                                                        /* {joint-iso-ccitt(2) ds(5) 4} */
#define OID_AT_CN                       OID_AT "\x03"   /* {id-at 3} */
#define OID_AT_SUR_NAME                 OID_AT "\x04"   /* {id-at 4} */
#define OID_AT_SERIAL_NUMBER            OID_AT "\x05"   /* {id-at 5} */
#define OID_AT_COUNTRY                  OID_AT "\x06"   /* {id-at 6} */
#define OID_AT_LOCALITY                 OID_AT "\x07"   /* {id-at 7} */
#define OID_AT_STATE                    OID_AT "\x08"   /* {id-at 8} */
#define OID_AT_ORGANIZATION             OID_AT "\x0A"   /* {id-at 10} */
#define OID_AT_ORG_UNIT                 OID_AT "\x0B"   /* {id-at 11} */
#define OID_AT_TITLE                    OID_AT "\x0C"   /* {id-at 12} */
#define OID_AT_POSTAL_ADDRESS           OID_AT "\x10"   /* {id-at 16} */
#define OID_AT_POSTAL_CODE              OID_AT "\x11"   /* {id-at 17} */
#define OID_AT_GIVEN_NAME               OID_AT "\x2A"   /* {id-at 42} */
#define OID_AT_INITIALS                 OID_AT "\x2B"   /* {id-at 43} */
#define OID_AT_GENERATION_QUALIFIER     OID_AT "\x2C"   /* {id-at 44} */
#define OID_AT_UNIQUE_IDENTIFIER        OID_AT "\x2D"   /* {id-at 45} */
#define OID_AT_DN_QUALIFIER             OID_AT "\x2E"   /* {id-at 46} */
#define OID_AT_PSEUDONYM                OID_AT "\x41"   /* {id-at 65} */

#define OID_UID                         "\x09\x92\x26\x89\x93\xF2\x2C\x64\x01\x01"
                                                        /* {itu-t(0) data(9) pss(2342) ucl(19200300) pilot(100) pilotAttributeType(1) uid(1)} */
#define OID_DOMAIN_COMPONENT            "\x09\x92\x26\x89\x93\xF2\x2C\x64\x01\x19"
                                                        /* {itu-t(0) data(9) pss(2342) ucl(19200300) pilot(100) pilotAttributeType(1) domainComponent(25)} */

/* OIDs for standard certificate extensions */
#define OID_AUTHORITY_KEY_IDENTIFIER    OID_ID_CE "\x23" /* {id-ce 35} */
#define OID_SUBJECT_KEY_IDENTIFIER      OID_ID_CE "\x0E" /* {id-ce 14} */
#define OID_KEY_USAGE                   OID_ID_CE "\x0F" /* {id-ce 15} */
#define OID_CERTIFICATE_POLICIES        OID_ID_CE "\x20" /* {id-ce 32} */
#define OID_POLICY_MAPPINGS             OID_ID_CE "\x21" /* {id-ce 33} */
#define OID_SUBJECT_ALT_NAME            OID_ID_CE "\x11" /* {id-ce 17} */
#define OID_ISSUER_ALT_NAME             OID_ID_CE "\x12" /* {id-ce 18} */
#define OID_SUBJECT_DIRECTORY_ATTRS     OID_ID_CE "\x09" /* {id-ce  9} */
#define OID_BASIC_CONSTRAINTS           OID_ID_CE "\x13" /* {id-ce 19} */
#define OID_NAME_CONSTRAINTS            OID_ID_CE "\x1E" /* {id-ce 30} */
#define OID_POLICY_CONSTRAINTS          OID_ID_CE "\x24" /* {id-ce 36} */
#define OID_EXTENDED_KEY_USAGE          OID_ID_CE "\x25" /* {id-ce 37} */
#define OID_CRL_DISTRIBUTION_POINTS     OID_ID_CE "\x1F" /* {id-ce 31} */
#define OID_INIHIBIT_ANYPOLICY          OID_ID_CE "\x36" /* {id-ce 54} */
#define OID_FRESHEST_CRL                OID_ID_CE "\x2E" /* {id-ce 46} */

/* Certificate policies */
#define OID_ANY_POLICY                  OID_CERTIFICATE_POLICIES "\x00"
                                                        /* {id-ce-certificatePolicies 0} */

/* Netscape certificate extensions */
#define OID_NS_CERT                     OID_NETSCAPE "\x01"
#define OID_NS_CERT_TYPE                OID_NS_CERT  "\x01"
#define OID_NS_BASE_URL                 OID_NS_CERT  "\x02"
#define OID_NS_REVOCATION_URL           OID_NS_CERT  "\x03"
#define OID_NS_CA_REVOCATION_URL        OID_NS_CERT  "\x04"
#define OID_NS_RENEWAL_URL              OID_NS_CERT  "\x07"
#define OID_NS_CA_POLICY_URL            OID_NS_CERT  "\x08"
#define OID_NS_SSL_SERVER_NAME          OID_NS_CERT  "\x0C"
#define OID_NS_COMMENT                  OID_NS_CERT  "\x0D"
#define OID_NS_DATA_TYPE                OID_NETSCAPE "\x02"
#define OID_NS_CERT_SEQUENCE            OID_NS_DATA_TYPE "\x05"

/* OIDs for CRL extensions */
#define OID_PRIVATE_KEY_USAGE_PERIOD    OID_ID_CE "\x10"
#define OID_CRL_NUMBER                  OID_ID_CE "\x14" /* {id-ce 20} */

/* X.509 v3 Extended key usage OIDs */
#define OID_ANY_EXTENDED_KEY_USAGE      OID_EXTENDED_KEY_USAGE "\x00"
                                                        /* {id-ce-extKeyUsage 0} */
#define OID_KP                          OID_PKIX "\x03" /* {id-pkix 3} */
#define OID_SERVER_AUTH                 OID_KP "\x01"   /* {id-kp 1} */
#define OID_CLIENT_AUTH                 OID_KP "\x02"   /* {id-kp 2} */
#define OID_CODE_SIGNING                OID_KP "\x03"   /* {id-kp 3} */
#define OID_EMAIL_PROTECTION            OID_KP "\x04"   /* {id-kp 4} */
#define OID_TIME_STAMPING               OID_KP "\x08"   /* {id-kp 8} */
#define OID_OCSP_SIGNING                OID_KP "\x09"   /* {id-kp 9} */

/* Wi-SUN Alliance Field Area Network */
#define OID_WISUN_FAN                   OID_PRIVATE_ENTERPRISE "\x82\xe4\x25\x01"
                                                        /* {iso(1) identified-organization(3) dod(6) internet(1) private(4) enterprise(1) WiSUN(45605) FieldAreaNetwork(1)} */
#define OID_ON                          OID_PKIX "\x08" /* {id-pkix 8} */
#define OID_ON_HW_MODULE_NAME           OID_ON "\x04"   /* {id-on 4} */

/* PKCS definition OIDs */
#define OID_PKCS                        OID_RSA_COMPANY "\x01"
                                                        /* {iso(1) member-body(2) us(840) rsadsi(113549) 1} */
#define OID_PKCS1                       OID_PKCS "\x01" /* {iso(1) member-body(2) us(840) rsadsi(113549) pkcs(1) 1} */
#define OID_PKCS5                       OID_PKCS "\x05" /* {iso(1) member-body(2) us(840) rsadsi(113549) pkcs(1) 5} */
#define OID_PKCS9                       OID_PKCS "\x09" /* {iso(1) member-body(2) us(840) rsadsi(113549) pkcs(1) 9} */
#define OID_PKCS12                      OID_PKCS "\x0c" /* {iso(1) member-body(2) us(840) rsadsi(113549) pkcs(1) 12} */

/* PKCS#1 OIDs */
#define OID_PKCS1_RSA                   OID_PKCS1 "\x01" /* {pkcs-1  1} */
#define OID_PKCS1_MD5                   OID_PKCS1 "\x04" /* {pkcs-1  4} */
#define OID_PKCS1_SHA1                  OID_PKCS1 "\x05" /* {pkcs-1  5} */
#define OID_PKCS1_SHA224                OID_PKCS1 "\x0e" /* {pkcs-1 14} */
#define OID_PKCS1_SHA256                OID_PKCS1 "\x0b" /* {pkcs-1 11} */
#define OID_PKCS1_SHA384                OID_PKCS1 "\x0c" /* {pkcs-1 12} */
#define OID_PKCS1_SHA512                OID_PKCS1 "\x0d" /* {pkcs-1 13} */

#define OID_RSA_SHA_OBS                 "\x2B\x0E\x03\x02\x1D"
#define OID_PKCS9_EMAIL                 OID_PKCS9 "\x01" /* {pkcs-9 1} */

/* RFC4055 */
#define OID_RSASSA_PSS                  OID_PKCS1 "\x0a" /* {pkcs-1 10} */
#define OID_MGF1                        OID_PKCS1 "\x08" /* {pkcs-1 8} */

/* Digest algorithms */
#define OID_DIGEST_ALG_MD5              OID_RSA_COMPANY "\x02\x05"
                                                        /* {iso(1) member-body(2) us(840) rsadsi(113549) digestAlgorithm(2) 5} */
#define OID_DIGEST_ALG_SHA1             OID_ISO_IDENTIFIED_ORG OID_OIW_SECSIG_SHA1
                                                        /* {iso(1) identified-organization(3) oiw(14) secsig(3) algorithms(2) 26} */
#define OID_DIGEST_ALG_SHA224           OID_NIST_ALG "\x02\x04"
                                                        /* {joint-iso-itu-t(2) country(16) us(840) organization(1) gov(101) csor(3) nistalgorithm(4) hashalgs(2) 4} */
#define OID_DIGEST_ALG_SHA256           OID_NIST_ALG "\x02\x01"
                                                        /* {joint-iso-itu-t(2) country(16) us(840) organization(1) gov(101) csor(3) nistalgorithm(4) hashalgs(2) 1} */
#define OID_DIGEST_ALG_SHA384           OID_NIST_ALG "\x02\x02"
                                                        /* {joint-iso-itu-t(2) country(16) us(840) organization(1) gov(101) csor(3) nistalgorithm(4) hashalgs(2) 2} */
#define OID_DIGEST_ALG_SHA512           OID_NIST_ALG "\x02\x03"
                                                        /* {joint-iso-itu-t(2) country(16) us(840) organization(1) gov(101) csor(3) nistalgorithm(4) hashalgs(2) 3} */
#define OID_DIGEST_ALG_RIPEMD160        OID_TELETRUST "\x03\x02\x01"
                                                        /* {iso(1) identified-organization(3) teletrust(36) algorithm(3) hashAlgorithm(2) ripemd160(1)} */

#define OID_HMAC_SHA1                   OID_RSA_COMPANY "\x02\x07"
                                                        /* {iso(1) member-body(2) us(840) rsadsi(113549) digestAlgorithm(2) 7} */
#define OID_HMAC_SHA224                 OID_RSA_COMPANY "\x02\x08"
                                                        /* {iso(1) member-body(2) us(840) rsadsi(113549) digestAlgorithm(2) 8} */
#define OID_HMAC_SHA256                 OID_RSA_COMPANY "\x02\x09"
                                                        /* {iso(1) member-body(2) us(840) rsadsi(113549) digestAlgorithm(2) 9} */
#define OID_HMAC_SHA384                 OID_RSA_COMPANY "\x02\x0A"
                                                        /* {iso(1) member-body(2) us(840) rsadsi(113549) digestAlgorithm(2) 10} */
#define OID_HMAC_SHA512                 OID_RSA_COMPANY "\x02\x0B"
                                                        /* {iso(1) member-body(2) us(840) rsadsi(113549) digestAlgorithm(2) 11} */

/* Encryption algorithms */
#define OID_DES_CBC                     OID_ISO_IDENTIFIED_ORG OID_OIW_SECSIG_ALG "\x07"
                                                        /* {iso(1) identified-organization(3) oiw(14) secsig(3) algorithms(2) 7} */
#define OID_DES_EDE3_CBC                OID_RSA_COMPANY "\x03\x07"
                                                        /* {iso(1) member-body(2) us(840) rsadsi(113549) encryptionAlgorithm(3) 7} */
#define OID_AES                         OID_NIST_ALG "\x01"
                                                        /* {joint-iso-itu-t(2) country(16) us(840) organization(1) gov(101) csor(3) nistAlgorithm(4) 1} */

/* Key Wrapping algorithms */
/* RFC5649 */
#define OID_AES128_KW                   OID_AES "\x05"  /* {aes 5} */
#define OID_AES128_KWP                  OID_AES "\x08"  /* {aes 8} */
#define OID_AES192_KW                   OID_AES "\x19"  /* {aes 25} */
#define OID_AES192_KWP                  OID_AES "\x1c"  /* {aes 28} */
#define OID_AES256_KW                   OID_AES "\x2d"  /* {aes 45} */
#define OID_AES256_KWP                  OID_AES "\x30"  /* {aes 48} */

/* PKCS#5 OIDs */
#define OID_PKCS5_PBKDF2                OID_PKCS5 "\x0c" /* {pkcs-5 12} */
#define OID_PKCS5_PBES2                 OID_PKCS5 "\x0d" /* {pkcs-5 13} */
#define OID_PKCS5_PBMAC1                OID_PKCS5 "\x0e" /* {pkcs-5 14} */

/* PKCS#5 PBES1 algorithms */
#define OID_PKCS5_PBE_MD5_DES_CBC       OID_PKCS5 "\x03" /* {pkcs-5 3} */
#define OID_PKCS5_PBE_MD5_RC2_CBC       OID_PKCS5 "\x06" /* {pkcs-5 6} */
#define OID_PKCS5_PBE_SHA1_DES_CBC      OID_PKCS5 "\x0a" /* {pkcs-5 10} */
#define OID_PKCS5_PBE_SHA1_RC2_CBC      OID_PKCS5 "\x0b" /* {pkcs-5 11} */

/* PKCS#8 OIDs */
#define OID_PKCS9_CSR_EXT_REQ           OID_PKCS9 "\x0e" /* {pkcs-9 14} */

/* PKCS#12 PBE OIDs */
#define OID_PKCS12_PBE                      OID_PKCS12 "\x01"
                                                        /* {pkcs-12 1} */
#define OID_PKCS12_PBE_SHA1_DES3_EDE_CBC    OID_PKCS12_PBE "\x03"
                                                        /* {pkcs-12Pbe 3} */
#define OID_PKCS12_PBE_SHA1_DES2_EDE_CBC    OID_PKCS12_PBE "\x04"
                                                        /* {pkcs-12Pbe 4} */
#define OID_PKCS12_PBE_SHA1_RC2_128_CBC     OID_PKCS12_PBE "\x05"
                                                        /* {pkcs-12Pbe 5} */
#define OID_PKCS12_PBE_SHA1_RC2_40_CBC      OID_PKCS12_PBE "\x06"
                                                        /* {pkcs-12Pbe 6} */

/* EC key algorithms from RFC5480 */
#define OID_EC_ALG_UNRESTRICTED         OID_ANSI_X9_62 "\x02\01"
                                                        /* {iso(1) member-body(2) us(840) ansi-X9-62(10045) keyType(2) 1} */
#define OID_EC_ALG_ECDH                 OID_CERTICOM "\x01\x0c"
                                                        /* {iso(1) identified-organization(3) certicom(132) schemes(1) ecdh(12)} */

/* ECParameters namedCurve identifiers, from RFC5480, RFC5639, and SEC2 */
#define OID_EC_GRP_SECP192R1            OID_ANSI_X9_62 "\x03\x01\x01"
                                                        /* {iso(1) member-body(2) us(840) ansi-X9-62(10045) curves(3) prime(1) 1} */
#define OID_EC_GRP_SECP224R1            OID_CERTICOM "\x00\x21"
                                                        /* {iso(1) identified-organization(3) certicom(132) curve(0) 33} */
#define OID_EC_GRP_SECP256R1            OID_ANSI_X9_62 "\x03\x01\x07"
                                                        /* {iso(1) member-body(2) us(840) ansi-X9-62(10045) curves(3) prime(1) 7} */
#define OID_EC_GRP_SECP384R1            OID_CERTICOM "\x00\x22"
                                                        /* {iso(1) identified-organization(3) certicom(132) curve(0) 34} */
#define OID_EC_GRP_SECP521R1            OID_CERTICOM "\x00\x23"
                                                        /* {iso(1) identified-organization(3) certicom(132) curve(0) 35} */

#define OID_EC_GRP_SECP192K1            OID_CERTICOM "\x00\x1f"
                                                        /* {iso(1) identified-organization(3) certicom(132) curve(0) 31} */
#define OID_EC_GRP_SECP224K1            OID_CERTICOM "\x00\x20"
                                                        /* {iso(1) identified-organization(3) certicom(132) curve(0) 32} */
#define OID_EC_GRP_SECP256K1            OID_CERTICOM "\x00\x0a"
                                                        /* {iso(1) identified-organization(3) certicom(132) curve(0) 10} */

/* RFC5639 4.1 brainpool {versionOne} */
#define OID_EC_BRAINPOOL_V1             OID_TELETRUST "\x03\x03\x02\x08\x01\x01"
                                                        /* {iso(1) identified-organization(3) teletrust(36) algorithm(3) signatures(3) ecSign(2) 8 1 1} */
#define OID_EC_GRP_BP224R1              OID_EC_BRAINPOOL_V1 "\x05"
                                                        /* {versionOne 5} */
#define OID_EC_GRP_BP256R1              OID_EC_BRAINPOOL_V1 "\x07"
                                                        /* {versionOne 7} */
#define OID_EC_GRP_BP384R1              OID_EC_BRAINPOOL_V1 "\x0B"
                                                        /* {versionOne 11} */
#define OID_EC_GRP_BP512R1              OID_EC_BRAINPOOL_V1 "\x0D"
                                                        /* {versionOne 13} */

/* RFC8410 */
#define OID_ID_EDWARDS                  OID_ISO_IDENTIFIED_ORG "\x65"
                                                        /* {iso(1) identified-organization(3) thawte(101)} */
#define OID_ID_X25519                   OID_ID_EDWARDS "\x6e"
                                                        /* {iso(1) identified-organization(3) thawte(101) id-X25519(110)} */
#define OID_ID_ED25519                  OID_ID_EDWARDS "\x70"
                                                        /* {iso(1) identified-organization(3) thawte(101) id-Ed25519(112)} */

/* SEC1 C.1 */
#define OID_ANSI_X9_62_FIELD_TYPE       OID_ANSI_X9_62 "\x01"
#define OID_ANSI_X9_62_PRIME_FIELD      OID_ANSI_X9_62_FIELD_TYPE "\x01"

/* ECDSA signature identifiers, from RFC5480 */
#define OID_ANSI_X9_62_SIG              OID_ANSI_X9_62 "\x04"
                                                         /* signatures(4) */
#define OID_ANSI_X9_62_SIG_SHA2         OID_ANSI_X9_62_SIG "\x03"
                                                         /* ecdsa-with-SHA2(3) */
#define OID_ECDSA_SHA1                  OID_ANSI_X9_62_SIG "\x01"
                                                        /* {iso(1) member-body(2) us(840) ansi-X9-62(10045) signatures(4) 1} */
#define OID_ECDSA_SHA224                OID_ANSI_X9_62_SIG_SHA2 "\x01"
                                                        /* {iso(1) member-body(2) us(840) ansi-X9-62(10045) signatures(4) ecdsa-with-SHA2(3) 1} */
#define OID_ECDSA_SHA256                OID_ANSI_X9_62_SIG_SHA2 "\x02"
                                                        /* {iso(1) member-body(2) us(840) ansi-X9-62(10045) signatures(4) ecdsa-with-SHA2(3) 2} */
#define OID_ECDSA_SHA384                OID_ANSI_X9_62_SIG_SHA2 "\x03"
                                                        /* {iso(1) member-body(2) us(840) ansi-X9-62(10045) signatures(4) ecdsa-with-SHA2(3) 3} */
#define OID_ECDSA_SHA512                OID_ANSI_X9_62_SIG_SHA2 "\x04"
                                                        /* {iso(1) member-body(2) us(840) ansi-X9-62(10045) signatures(4) ecdsa-with-SHA2(3) 4} */


#endif

/* end of file oid.h */
