/*
 * tls_mbedtls.h
 *
 *  Created on: 4 Nov 2025
 *      Author: user
 */

#ifndef TLS_MBEDTLS_H_
#define TLS_MBEDTLS_H_



//#define DEBUG_BLOCK_ACK
#ifdef DEBUG_TLS_MBEDTLS
#define TLS_MBEDTLS_PRINT_REPORT Report
#define TLS_MBEDTLS_PRINT_REPORT_ERROR Report
#else
#define TLS_MBEDTLS_PRINT_REPORT(...)
#define TLS_MBEDTLS_PRINT_REPORT_ERROR Report
#endif




#endif /* MBEDTLS_H_ */
