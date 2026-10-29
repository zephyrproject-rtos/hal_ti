#ifndef ti_log_config_h
#define ti_log_config_h

#include <ti/log/Log.h>

/* The application must declare the log module name using the
 * `Log_MODULE_USE` macro at all call sites of TI's `Log_printf()`.
 *
 * For example, the declaration below shows how to declare the RCL
 * (Radio Control Layer) log module. RCL source code includes logs that
 * are disabled by default:
 *
 * `Log_printf(LogModule_RCL, Log_VERBOSE, ...)`
 *
 * The log module used in Log_printf() must match its declaration.
 *
 * Applications can declare multiple log modules with different names.
 */
Log_MODULE_USE(LogModule_RCL);

#endif /* ti_log_config_h */
