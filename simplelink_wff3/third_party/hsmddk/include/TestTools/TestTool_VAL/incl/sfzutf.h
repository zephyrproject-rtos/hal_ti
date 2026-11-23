/* sfzutf.h
 *
 * Description: SFZUTF header.
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

#ifndef INCLUDE_GUARD_SFZUTF_H
#define INCLUDE_GUARD_SFZUTF_H

#include <third_party/hsmddk/include/Kit/DriverFramework/Basic_Defs_API/incl/basic_defs.h>
#include <third_party/hsmddk/include/Kit/Log/incl/log.h>
#include <third_party/hsmddk/include/Kit/DriverFramework/CLib_Abstraction_API/incl/clib.h>

#ifdef SFZUTF_USERMODE
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>             // usleep, getpid

#define SFZUTF_MALLOC(x)    malloc((x)>0?(x):1)
#define SFZUTF_CALLOC(x,y)  malloc(x*y)
#define SFZUTF_REALLOC(x,y) realloc(x, y)
#define SFZUTF_FREE(x)      free(x)
#define SFZUTF_USLEEP(x)    usleep(x)
#define SFZUTF_GETPID()     ((int)getpid())
#else
#define EXPORT_SYMTAB

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>       // printk
#include <linux/slab.h>
#include <linux/sched.h>        // for "struct task_struct"
#include <asm/delay.h>          // udelay
#include <asm/current.h>        // process information

#define SFZUTF_MALLOC(x)    kmalloc((x)>0?(x):1, GFP_KERNEL)
#define SFZUTF_CALLOC(x,y)  kmalloc(x*y, GFP_KERNEL)
#define SFZUTF_REALLOC(x,y) krealloc(x, y, GFP_KERNEL)
#define SFZUTF_FREE(x)      kfree(x)
#define SFZUTF_USLEEP(x)    udelay(x)
#define SFZUTF_GETPID()     ((int)current->pid)
#endif


#define SFZUTF_MEMCMP(a,b,l) memcmp(a, b, l)
#define SFZUTF_MEMCPY(a,b,l) memcpy(a, b, l)
static inline uint32_t
sfzutf_strlen(
    const char * str)
{
    uint32_t len = 0;
    const char *string_it = str;
    while(*string_it != '\0')
    {
        len++;
        string_it++;
    }
    return len;
}
#define SFZUTF_STRLEN(s) sfzutf_strlen(s)

/* Compositions of above, for common string operations. */
#define SFZUTF_STREQ(s1,s2)                          \
  (SFZUTF_STRLEN(s1) == SFZUTF_STRLEN(s2) &&         \
   SFZUTF_MEMCMP((s1), (s2), SFZUTF_STRLEN(s1)) == 0)

#define SFZUTF_STREQ_PREFIX(s1,sp)                   \
  (SFZUTF_STRLEN(s1) >= SFZUTF_STRLEN(sp) &&         \
   SFZUTF_MEMCMP((s1), (sp), SFZUTF_STRLEN(sp)) == 0)


// Test framework function prototypes and defines
typedef int (*TFun)(int _i);
typedef void (*SFun)(void);


extern const char * g_pActiveTestName;
extern int g_ActiveTestLoop;

#define START_TEST(name)                                           \
  static int name(int _i)                                          \
  {                                                                \
    g_pActiveTestName = __func__;                                  \
    g_ActiveTestLoop = _i;                                         \
    LOG_INFO("%d:%s:L%d> START\n", SFZUTF_GETPID(), __func__, _i); \
    do

#define END_TEST_SUCCES         0
#define END_TEST_FAIL           (-1)
#define END_TEST_UNSUPPORTED    (-2)
#define END_TEST_SKIPPED        (-3)
#define END_TEST_ABORT          (-64321)

#define END_TEST while(0);                                                                   \
      LOG_CRIT("%d:%s:L%d> PASSED\n", SFZUTF_GETPID(), g_pActiveTestName, g_ActiveTestLoop); \
    return END_TEST_SUCCES;                                                                  \
  }
//LOG_CRIT("."); or LOG_CRIT("%d:%s:L%d> PASSED\n", SFZUTF_GETPID(), g_pActiveTestName, g_ActiveTestLoop);

#ifdef GCOV_PROFILE
void
__gcov_flush(); /* Function to write profiles on disk. */

#define SFZUTF_GCOV_FLUSH  __gcov_flush()
#else /* !GCOV_PROFILE */
#define SFZUTF_GCOV_FLUSH
#endif /* GCOV_PROFILE */

#define SFZUTF_FAILURE(expr,info,status)                                                                                                   \
  do {                                                                                                                                     \
    SFZUTF_GCOV_FLUSH;                                                                                                                     \
    LOG_CRIT("%d:%s:L%d:%d> FAILED: %s%s(%d)\n", SFZUTF_GETPID(), g_pActiveTestName, g_ActiveTestLoop, __LINE__, expr, info, (int)status); \
    return END_TEST_FAIL;                                                                                                                  \
  } while(0)

#define SFZUTF_UNSUPPORTED(expr,info)                                                                                            \
  do {                                                                                                                           \
    SFZUTF_GCOV_FLUSH;                                                                                                           \
    LOG_CRIT("%d:%s:L%d:%d> NOT SUPPORTED: %s%s\n", SFZUTF_GETPID(), g_pActiveTestName, g_ActiveTestLoop, __LINE__, expr, info); \
    return END_TEST_UNSUPPORTED;                                                                                                 \
  } while(0)


/* Mark test failures */
#define fail(info,status)             \
  do {                                \
      SFZUTF_FAILURE("",info,status); \
  } while(0)

#define fail_if(expr,info,status)             \
  do {                                        \
    if (expr) {                               \
      SFZUTF_FAILURE(""#expr" ",info,status); \
    }                                         \
  } while(0)

#define print_fail(info, status) \
  do {                                        \
        SFZUTF_GCOV_FLUSH;                    \
        LOG_CRIT("%d:%s:L%d:%d> FAILED: %s(%d)\n", SFZUTF_GETPID(), g_pActiveTestName, g_ActiveTestLoop, __LINE__, info, (int)status); \
  } while (0)

#define fail_unless(expr,info,status)          \
  do {                                         \
    if (!(expr)) {                             \
      SFZUTF_FAILURE("!"#expr" ",info,status); \
    }                                          \
  } while(0)


/* Mark test as unsupported if condition is true. */
#define unsupported(info)        \
  do {                           \
    SFZUTF_UNSUPPORTED("",info); \
  } while(0)

#define unsupported_if(expr,info)          \
  do {                                     \
    if (expr) {                            \
      SFZUTF_UNSUPPORTED(""#expr" ",info); \
    }                                      \
  } while(0)

#define unsupported_unless(expr,info)       \
  do {                                      \
    if (!(expr)) {                          \
      SFZUTF_UNSUPPORTED("!"#expr" ",info); \
    }                                       \
  } while(0)


struct TestSuite
{
    struct TestSuite * NextSuite_p;
    const char * Name_p;
    struct TestCase * TestCaseList_p;
    bool Enabled;
};

struct TestCase
{
    struct TestCase * NextCase_p;
    const char * Name_p;
    SFun FixtureStartFunc;
    SFun FixtureEndFunc;
    struct Test * TestList_p;
    unsigned int TestsSuccess;
    unsigned int TestsFailed;
    bool Enabled;
};

struct Test
{
    struct Test * NextTest_p;
    const char * Name_p;
    TFun TestFunc;
    int Start;
    int NumberOfLoops;
    bool Enabled;
};


typedef enum
{
    SFZUTF_ENABLE_UNDETERMINED,
    SFZUTF_ENABLE_SINGLE,
    SFZUTF_ENABLE_AFTER,
    SFZUTF_ENABLE_ALL
}
SfzUtfEnable_t;


/* Note:
 *       Each suite needs to provide a interface that builds the test suite.
 *
 * Example:
 * int build_suite(void)
 * {
 *     struct TestSuite * TestSuite_p = sfzutf_tsuite_create("TestSuite name");
 *     if (TestSuite_p != NULL)
 *     {
 *         struct TestCase *TestCase_p = sfzutf_tcase_create(TestSuite_p, "TestCase name");
 *         if (TestCase_p != NULL)
 *         {
 *             if (sfzutf_test_add(TestCase_p, <test function>) != 0) goto FuncErrorReturn;
 *             ...
 *         }
 *         else
 *         {
 *             goto FuncErrorReturn;
 *         }
 *         TestCase_p = sfzutf_tcase_create(TestSuite_p, "Next TestCase name");
 *         if (TestCase_p != NULL)
 *         {
 *             if (sfzutf_test_add(TestCase_p, <test function>) != 0) goto FuncErrorReturn;
 *             ...
 *         }
 *         ...
 *     }
 *     return 0;
 *
 * FuncErrorReturn:
 *     return -1;
 * }
 **/

/* TestSuite helpers */
struct TestSuite *
sfzutf_tsuite_create(
        const char * Name_p);

void
sfzutf_tsuite_dump(void);

void
sfzutf_tsuite_release(
        const char * Name_p);

struct TestSuite *
sfzutf_tsuite_get(
        const char * const SuiteName_p);

bool
sfzutf_tsuite_enable(
        struct TestSuite * TestSuite_p,
        const char * const SuiteName_p,
        const char * const TCaseName_p,
        const char * const TestName_p,
        const int * const IterValue_p,
        const SfzUtfEnable_t OrigEnableMode);

void
sfzutf_tsuite_disable(
        struct TestSuite * TestSuite_p);

int
sfzutf_tsuite_run(
        struct TestSuite * TestSuite_p,
        unsigned int * pSuccesses,
        unsigned int * pFailures);

/* TestCase helpers */
struct TestCase *
sfzutf_tcase_create(
        struct TestSuite * TestSuite_p,
        const char *Name_p);

void
sfzutf_tcase_release(
        struct TestCase *TestCaseList_p,
        const char *Name_p);

int
sfzutf_tcase_add_fixture(
        struct TestCase * TestCase_p,
        SFun StartFunc,
        SFun EndFunc);

/* Test helpers */
#define sfzutf_test_add(case,func) \
    sfzutf_ttest_create(case,func,""#func"",0)

#define sfzutf_test_add_loop(case,func,loops) \
    sfzutf_ttest_create(case,func,""#func"",loops)

int
sfzutf_ttest_create(
        struct TestCase * TestCase_p,
        TFun TestFunction,
        const char * Name_p,
        int NumberOfLoops);

void
sfzutf_ttest_release(
        struct Test * TestList_p,
        const char * Name_p);

/* Discard const qualifier from pointer */
static inline void *
sfzutf_discard_const(
        const void * Ptr_p)
{
    union
    {
        const void * c_p;
        void * n_p;
    } Conversion;

    Conversion.c_p = Ptr_p;
    return Conversion.n_p;
}

/* Switch ordering of array.
   This implementation works byte at a time. */
static inline void
sfzutf_endian_flip(
        void *dst,
        uint32_t len)
{
    unsigned char *dst_c = dst;
    unsigned char t;
    uint32_t i;

    for(i=0; i < len/2; i++)
    {
        t = dst_c[i];
        dst_c[i] = dst_c[len-i-1];
        dst_c[len-i-1] = t;
    }
}


#endif /* INCLUDE_GUARD_SFZUTF_H */

/* end of file sfzutf.h */
