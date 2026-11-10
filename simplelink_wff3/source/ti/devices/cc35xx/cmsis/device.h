/******************************************************************************
*  Filename:       device.h
*
*  Description:    Redirection file for CMSIS core device header file
*
// ##### LICENSE HEADER #####
*
******************************************************************************/
#ifndef __DEVICE_H__
#define __DEVICE_H__

// Device-specific configuration file
#include "cc35xx.h"

// Core-specific cmsis header file
#include "core/core_cm33.h"

// Toolchain-specific cmsis header files
#if defined(__IAR_SYSTEMS_ICC__)
#include "core/cmsis_iccarm.h"
#elif defined(__GNUC__) || defined(__clang__)
#include "core/cmsis_gcc.h"
#else
    #error "Unexpected toolchain used when importing cmsis headers"
#endif

#endif // #ifndef __DEVICE_H__
