/*
 * Copyright (c) 2024, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef __MACRO_UTILS_included__
#define __MACRO_UTILS_included__


/**
 * \DEF COPY_WLAN_WORD
 * \BRIEF  COPY WORD BYTE BY BYTE IN LITTLE ENDIAN HOST WHEN OPPOSING LITTLE ENDIAN DATA - DON'T SWAP BYTES
 */

#define COPY_WLAN_WORD(dst,src)     os_memcpy(((uint8_t*)(dst)),((uint8_t*)(src)),sizeof(uint16_t));
#define COPY_WLAN_32BIT(dst,src)   os_memcpy(((uint8_t*)(dst)),((uint8_t*)(src)),sizeof(uint32_t));
#define MEMCMP_WLAN_32BYTE(comp1,comp2)  os_memcpy(((uint8_t*)(comp1)),((uint8_t*)(comp2)),sizeof(uint32_t))


// Prototype of functions from utils.c
uint32_t  FIND_NEXT_BIT_IN_BITMAP (   uint32_t   data_snapshot   ,
                                    uint32_t                  current_flid    );

#define NUM_BITS_IN_BYTE             8
#define NUM_BITS_IN_HALF_WORD       16
#define NUM_BITS_IN_WORD            32
#define NUM_BITS_IN_U64             64
#define NUM_BITS_IN_TYPE(t)         (sizeof(t) * NUM_BITS_IN_BYTE)

#define NUM_ELEMENTS_IN_VEC(vec)    ( sizeof(vec) / sizeof((vec)[0])  )


#define __MAX__(a,b)    (  ((a) > (b))  ? (a) : (b) )
#define __MIN__(a,b)    (  ((a) < (b))  ? (a) : (b) )

//-------------------------------------------------------------------------------------------------
// 64 to 32 bit conversions
//-------------------------------------------------------------------------------------------------
// Part I - The following macros work on an expression
#define GET_LOW32_BITS_FROM_64BIT(__64bit__)    (  (uint32_t)((__64bit__) & 0xFFFFFFFF)  )
#define GET_HIGH32_BITS_FROM_64BIT(__64bit__)   (  (uint32_t)((__64bit__) >> 32       )  )
#define GET_64BIT_FROM_LOW32_AND_HIGH32(__low_32bit__, __high_32bit__)      \
        (                                                                   \
                (   ((uint64)(__low_32bit__))   <<      0   )               \
            |   (   ((uint64)(__high_32bit__))  <<     32   )               \
        ) // MACRO GET_64BIT_FROM_LOW32_AND_HIGH32(). //

// Part I - The following macros work on a variable and generate less code
#define LOW_32_OF_64_BIT(x) (((uint64_t *)(&(x)))->low)
#define HIGH_32_OF_64_BIT(x) (((uint64_t *)(&(x)))->high)

#define CAST_TO_UINT64(x) (*((uint64 *)(&(x))))


/*-----------------------------------------------------------------------------*/
/* Needed for offsetof() macro.                                                */
/*-----------------------------------------------------------------------------*/
#include <stddef.h>

#ifndef BIT
#define BIT(x) (1U << (x))
#endif

//----------------------------------------------------------------------------//
// Macro's to improve readability of the ( ? : ) tri-nary operator.           //
//----------------------------------------------------------------------------//
#define __IF__(x)       (x)
#define __THEN__(x)     ? (x)
#define __ELSE__(x)     : (x)
#define __ELSE_IF__(x)  : (x)


#define BIT_x(x)        	(1 << (x))
#define BIT_MSB_x(x) 		(0x80000000 >> x)               //returns a bit mask with the x-th bit, from the MSB, set
#define BIT_MSB_U16_x(x) 	(0x00008000 >> x)               //returns a bit mask with the x-th bit, from the MSB, set
#define BIT_MSB_U8_x(x)     (0x00000080 >> x)               //returns a bit mask with the x-th bit, from the MSB, set
#define BIT_MSB_U64_x(x)    (0x8000000000000000L >> x)      //returns a bit mask with the x-th bit, from the MSB, set

//----------------------------------------------------------------------------//
// BITMASK_x_0() returns a bit mask of "1" from Bits[x:0]                     //
//                                                                            //
// E.g., for x=5                                                              //
//                                                                            //
// BITMASK_x_0(5) = ........111111     Bits[5:0] = "111111"                   //
// BITMASK_x_0(0) = .............1     Bits[0:0] = "000001"                   //
//                                                                            //
//----------------------------------------------------------------------------//
#define BITMASK_x_0(x)                                              \
        (                                                           \
            __IF__((x) == 31)                                       \
                /* For x==31, we immediately return 0xFFFFFFFF */   \
                __THEN__(0xFFFFFFFF)                                \
                /* For other x, we return 2^(x+1) - 1.         */   \
                __ELSE__(                                           \
                            (1 << ((x)+1))                          \
                            -                                       \
                            1                                       \
                        )                                           \
        )   // MACRO BITMASK_x_0() //


//----------------------------------------------------------------------------//
// BITMASK_x_y() returns a bit mask of "1" from Bits[x:y]                     //
// (naturally, x >= y should be enforces by the caller!!)                     //
//                                                                            //
// E.g., for x=5, y=2                                                         //
//                                                                            //
// BITMASK_x_y(5,5) = ......1.....     Bits[5:5] = "100000"                   //
// BITMASK_x_y(5,2) = ......1111..     Bits[5:0] = "111100"                   //
// BITMASK_x_0(5,1) = ......11111.     Bits[5:1] = "111110"                   //
// BITMASK_x_0(5,0) = ......111111     Bits[5:0] = "111111"                   //
//                                                                            //
//----------------------------------------------------------------------------//
#define BITMASK_x_y(x,y)                                            \
        (                                                           \
            __IF__((y) == 0)                                        \
                /* For y==0, we return Bits[x:0]               */   \
                __THEN__(   BITMASK_x_0(x)  )                       \
                /* For y> 0, we return Bits[x:0] - Bits[y-1:0] */   \
                __ELSE__(                                           \
                            BITMASK_x_0(x)                          \
                            -                                       \
                            BITMASK_x_0((y)-1)                      \
                        )                                           \
        )   // MACRO BITMASK_x_y(). //




//#######################################################################################//
// Using compiler TMS470 5.1.4, supporting intrinsic functions:                          //
//        __rev()																		 //
//        __rev16()																		 //
//        __rbit()																		 //
//        __revsh()																		 //
//        __ror()																		 //
//	Wrapping with more understandable macros:											 //
//#######################################################################################//

//----------------------------------------------------------------------------//
// REVERSE_32BITS(x) returns a 32 bit inverted x.                             //
// Note that we rely on the caller to #include the proper prototypes.         //
//                                                                            //
// Examples:                                                                  //
//                                                                            //
// REVERSE_32BITS(0x00000000) = 0x00000000                                    //
// REVERSE_32BITS(0x00000001) = 0x80000000                                    //
// REVERSE_32BITS(0x00000003) = 0xC0000000                                    //
// REVERSE_32BITS(0xABCDEF01) = 0x80F7B3D5                                    //
//----------------------------------------------------------------------------//
#define REVERSE_32BITS(x)		(__rbit(x))
#define REVERSE_64BITS(x)       (IRQ_UtilReverse64Bits(x))
#define REVERSE_8BITS(x)		(__rbit((uint32_t)x) >> 24)


//----------------------------------------------------------------------------//
// REVERSE_4BYTES(x) returns a 4 byte reversed version of x.                  //
// Note that we rely on the caller to #include the proper prototypes.         //
//                                                                            //
// Examples:                                                                  //
//                                                                            //
// REVERSE_4BYTES(0x00000000) = 0x00000000                                    //
// REVERSE_4BYTES(0x00000001) = 0x01000000                                    //
// REVERSE_4BYTES(0x11223344) = 0x44332211                                    //
// REVERSE_4BYTES(0x12345678) = 0x78563412                                    //
//----------------------------------------------------------------------------//
#define REVERSE_4BYTES(x)       (__rev(x))
//----------------------------------------------------------------------------//
// REVERSE_2BYTES(x) returns a 2 x 1/2 word byte reversed value of x.         //
//                                                                            //
// Examples:                                                                  //
//                                                                            //
// REVERSE_2BYTES(0x00000000) = 0x00000000                                    //
// REVERSE_2BYTES(0x00000001) = 0x00000100                                    //
// REVERSE_2BYTES(0x11223344) = 0x22114433                                    //
// REVERSE_2BYTES(0x12345678) = 0x34127856                                    //
//----------------------------------------------------------------------------//
#define REVERSE_2BYTES(x)       (__rev16(x))

/*
 *  REVERSE_LOWER_BYTE_EXTEND_SIGN(x):
 *
 *  Reverses byte order in the lower byte of a
 *  word, and extends the sign to 32 bits. That is,
 *	converts 16-bit signed data to 32-bit signed
 *	data, while also converting between big-endian
 *	and little-endian or vice versa.
 */
#define REVERSE_LOWER_BYTE_EXTEND_SIGN(x)	(__revsh(x))

/*
 * ROTATE_BITS_RIGHT(x,shift)
 *
 * Rotates the value to the right by the number of
 * bits specified. Bits rotated off the right end are
 * placed into empty bits on the left.
 */
#define ROTATE_BITS_RIGHT(x,shift)			(__ror(x,shift))

#define IS_BIT_SET(bit_field, bit_num)                  (((bit_field) & BIT_x(bit_num)) > 0)
#define CLEAR_BIT_IN_BITMAP(bit_field,bit_num)          { (bit_field) &= ~ BIT_x(bit_num) ; }
#define SET_BIT_IN_BITMAP(bit_field,bit_num)            { (bit_field) |=   BIT_x(bit_num) ; }
//----------------------------------------------------------------------------//
// ISOLATE_LOWEST_BIT_SET(x) returns a mask x with only the lowest bit set of //
// x.                                                                         //
//                                                                            //
// E.g., for x=...1100110000 returns ...0000010000                            //
// E.g., for x=............1 returns ............1                            //
// E.g., for x=...0000000000 returns ...0000000000                            //
// E.g., for x=...1000000000 returns ...1000000000                            //
// Etc.                                                                       //
//                                                                            //
// Reference: "Algorithms for Programmers" http://www.jjj.de/fxt/             //
//                                                                            //
// We do this by     result = (x & (-x))                                      //
// where (-x) is the 2's complement of x.                                     //
//                                                                            //
//----------------------------------------------------------------------------//
#define ISOLATE_LOWEST_BIT_SET(x)       (  (x) & (-x) ) 

//----------------------------------------------------------------------------//
// REMOVE_LOWEST_BIT_SET(x) returns a bitmask with the lowest "1" bit cleared.//
//                                                                            //
//                                                                            //
// E.g., for x=...1100110000 returns ...1100100000                            //
// E.g., for x=............1 returns ............0                            //
// E.g., for x=...0000000000 returns ...0000000000                            //
// E.g., for x=...1000000000 returns ...0000000000                            //
// Etc.                                                                       //
//                                                                            //
// Reference: "Algorithms for Programmers" http://www.jjj.de/fxt/             //
//                                                                            //
// We do this by     result = (x & (x-1) )                                    //
//                                                                            //
//----------------------------------------------------------------------------//
#define REMOVE_LOWEST_BIT_SET(x)        (  (x) & ((x)-1)  )

//----------------------------------------------------------------------------//
// Removing the lowest bit set of a bitmask which has just 1 bit can be used  //
// to ask whether this is the only bit set.                                   //
// (note that x itself has to be non-zero to begin with...).                  //
//----------------------------------------------------------------------------//
#define IS_JUST_ONE_BIT_SET(x)          (((x) != 0) && (REMOVE_LOWEST_BIT_SET(x) == 0) )


//----------------------------------------------------------------------------//
// F/W type normalization - use CLANG __builtin_clz() function.                      //
//----------------------------------------------------------------------------//
#   define  __BUILTIN_NORM(x)     (__builtin_clz(x))




//----------------------------------------------------------------------------//
// NUM_OF_LEADING_ZEROS(x) is a wrapper around _norm() instrinsic function,   //
// which counts the # of leading zero's in an argument.                       //
//                                                                            //
// It returns a number beween 0--32, where 32 means all zero's, of the number //
// of bits, from the MSB, until the 1st "1" is seen.                          //
//                                                                            //
//----------------------------------------------------------------------------//
#define NUM_OF_LEADING_ZEROS(x)         (__BUILTIN_NORM(x))
#define FIND_FIRST_SET(x)               (__BUILTIN_NORM(x))
#define FIND_FIRST_SET_U16(x)           ( FIND_FIRST_SET(x & 0xFFFF) - NUM_BITS_IN_HALF_WORD)
#define FIND_FIRST_SET_U8(x)            ( FIND_FIRST_SET(x & 0xFF) - 24 )

//----------------------------------------------------------------------------//
// FIND_HIGHEST_BIT_SET_32_0(x) returns a number between 32 and 0 which       //
// indicates which bit # is the top bit# set.                                 //
//                                                                            //
// 0 indicates NO bit is set.                                                 //
// 1 Indicates bit[0] is the top bit set.                                     //
// 2 Indicates bit[1] is the top bit set.                                     //
// .                                                                          //
// .                                                                          //
// .                                                                          //
// n Indicates bit[n-1] is the the top bit set.                               //
//                                                                            //
//----------------------------------------------------------------------------//
#define FIND_HIGHEST_BIT_SET_32_0(x)    (NUM_BITS_IN_WORD - NUM_OF_LEADING_ZEROS(x))

//----------------------------------------------------------------------------//
// FIND_HIGHEST_BIT_SET(x) returns a number between 31--0 indicating the top  //
// bit # set.                                                                 //
// If x is all zero's, then 0xFFFFFFFF is returned (-1).                      //
//                                                                            //
//----------------------------------------------------------------------------//
#define FIND_HIGHEST_BIT_SET(x)         (FIND_HIGHEST_BIT_SET_32_0(x) - 1)

//----------------------------------------------------------------------------//
// FIND_HIGHEST_ZERO_BIT_U16(x) returns a number between 16--0 indicating the //
// top bit # set.                                                             //
//                     //
//                                                                            //
//----------------------------------------------------------------------------//
#define FIND_HIGHEST_BIT_SET_U16(x)         (FIND_HIGHEST_BIT_SET((~x) & 0xFFFF))

//----------------------------------------------------------------------------//
// FIND_LOWEST_BIT_SET(x) returns a number between 0--32 indicating the bit   //
// position of the lowest "1".                                                //
// Note that we accomplish this by reversing x - which can only be done       //
// with an aux. asm function.                                                 //
//                                                                            //
//                                                                            //
// Examples:                                                                  //
//                                                                            //
//-1 indicates NO BIT is set!  (corrected thanx to Luda N.).                  //
//                             (Thus, casting to int32_t and checking sign is   //
//                              enough to see that an actual bit is set).     //
// 0 indicates bit[0] is the lowest bit set.                                  //
// 1 indicates bit[1] is the lowest bit set.                                  //
// .                                                                          //
// .                                                                          //
// .                                                                          //
//31 indicates bit[31] is the lowest bit set.                                 //
//----------------------------------------------------------------------------//
#define FIND_LOWEST_BIT_SET(x)          (FIND_HIGHEST_BIT_SET(ISOLATE_LOWEST_BIT_SET(x)))


#define FIND_LOWEST_BIT_SET_IDX(x)     	( (0 == x) ? NUM_BITS_IN_WORD : FIND_LOWEST_BIT_SET(x) )

/* Return number of bits set in a 32-bit unsigned integer */
static inline int popcount32(uint32_t x) {
    return __builtin_popcount(x);
}

//----------------------------------------------------------------------------//
// GET_CONTAINER_FROM_FIELD(_typedef,_member,_member_address)                 //
// Returns the address of the containing structure, whose type is _typedef,   //
// when the address of a member _member_address is given, and the member's    //
// name is _member.                                                           //
//                                                                            //
// E.g.:                                                                      //
//                                                                            //
// Suppose we have the structure MPDUHeader_t                                 //
//  typedef struct                                                            //
//  {                                                                         //
//      FrameType_t frameType;                                                //
//      FrameCtrl_t frameCtrl;                                                //
//      uint16_t      duration;                                               //
//      uint8_t       MACAddress1[6];                                         //
//      uint8_t       MACAddress2[6];                                         //
//      uint8_t       MACAddress3[6];                                         //
//      uint16_t      seqNum;                                                 //
//  } MPDUHeader_t;                                                           //
//                                                                            //
// Now, given the address, of say, MACAddress3 to be, say, 0x80040116         //
// then, the address of the containing MPDU header is 0x80040100.             //
//                                                                            //
//----------------------------------------------------------------------------//
#define GET_CONTAINER_FROM_FIELD(container_typedef,member_field_name,member_field_address)  \
        (                                                                                   \
            (container_typedef *)                                                           \
            (                                                                               \
                ((uint32_t)(member_field_address))                                            \
                -                                                                           \
                offsetof(container_typedef,member_field_name)                               \
            )                                                                               \
        ) // MACRO GET_CONTAINER_FROM_FIELD(). //


//----------------------------------------------------------------------------//
// Align the value _x_ to the next 4B alignment, unless it is already aligned //
//----------------------------------------------------------------------------//
#define ALIGN_TO_4_BYTE(_x_)    (   ((_x_) + 3) & (~ 0x3) )
#define ALIGN_TO_BLOCK_SIZE(_x_)    (   ((_x_) + 128) & (~ 0x7F) ) //important when working with sdio, SDIO_BLOCK_SIZE = 128
#define ALIGN_TO_256_BYTE(_x_)  (   ((_x_) + 255) & (~ 0xFF) )

#define ALIGN_TO_256_BYTE_LOWER(_x_)  ( ((_x_)) & (~ 0xFF) )
#define ALIGN_TO_BLOCK_SIZE_LOWER(_x_)    (   ((_x_)) & (~ 0x7F) ) //important when working with sdio, SDIO_BLOCK_SIZE = 128



#define ALIGNN_TO_4(x) (((x) + 3) & (~3)) // for reading the records
        

//----------------------------------------------------------------------------//
// GET_TSF32_SIGNED_DIFF(tsf_1, tsf_2)                                        //
//                                                                            //
// signed difference between tsf2 and tsf1 (positive if tsf2 is later than    //
//                                          tsf1).                            //
//                                                                            //
// Returns the __signed__ difference of 2 TSF values specified by their lower //
// 32 bit values. In order for this macro to be meaningful, the TSF cannot    //
// designated locations in time which are more than 1/2 TSF 32bit value.      //
// For 2^32 usec in a single TSF 32bit, this amounts to ~4294sec, or          //
// approximately 71.5 minutes.                                                //
//                                                                            //
// This means that tsf_1 and tsf_2 cannot designate locations in time which   //
// are more than 71.5/2 = ~35 minutes and ~47 seconds.                        //
// Otherwise, the macro may return the wrong result.                          //
//                                                                            //
//----------------------------------------------------------------------------//
#define GET_TSF32_SIGNED_DIFF(tsf_1,tsf_2)                                                   \
         (                                                                                   \
             (int32_t)                                                                         \
             (                                                                               \
                 (tsf_2)                                                                     \
                 -                                                                           \
                 (tsf_1)                                                                     \
             )                                                                               \
         ) // MACRO GET_TSF32_SIGNED_DIFF(). //

//----------------------------------------------------------------------------//
// IS_TSF2_LATER_THAN_TSF1(tsf_1, tsf_2)                                      //
// Uses the macro above to return TRUE/FALSE whether tsf_2 is later than      //
// tsf_1.                                                                     //
//----------------------------------------------------------------------------//
#define IS_TSF2_LATER_THAN_TSF1(tsf_1,tsf_2)                                                \
        (                                                                                   \
            GET_TSF32_SIGNED_DIFF(tsf_1,tsf_2) > 0                                          \
        ) // MACRO IS_TSF2_LATER_THAN_TSF1(). //

/*-----------------------------------------------------------------------------*/
/* Returns the latest of 2 given TSF in 32bit format, using                    */
/* the 32bit tsf macro's above.                                                */
/*-----------------------------------------------------------------------------*/
#define GET_LATER_TSF32(__tsf_32_1__, __tsf_32_2__)                                         \
        (                                                                                   \
            __IF__(  IS_TSF2_LATER_THAN_TSF1(__tsf_32_1__, __tsf_32_2__)   )                \
            __THEN__(__tsf_32_2__) /* TSF2 > TSF1 */                                        \
            __ELSE__(__tsf_32_1__) /* TSF2 < TSF1 */                                        \
        ) // MACRO GET_LATER_TSF32(). //

#define GET_EARLIER_TSF32(__tsf_32_1__, __tsf_32_2__)                                       \
        (                                                                                   \
            __IF__(  IS_TSF2_LATER_THAN_TSF1(__tsf_32_1__, __tsf_32_2__)   )                \
            __THEN__(__tsf_32_1__) /* TSF1 < TSF2 */                                        \
            __ELSE__(__tsf_32_2__) /* TSF1 > TSF2 */                                        \
        ) // MACRO GET_LATER_TSF32(). //


/*-----------------------------------------------------------------------------*/
/* TSF diff is the signed difference between two TSF 64 values.                */
/* This macro checks whether this difference is also expressible as a signed   */
/* 32 bit tsf value.                                                           */
/*-----------------------------------------------------------------------------*/
#define IS_TSF_DIFF_64_CASTABLE_TO_TSF_DIFF_32(__tsf_diff_64__)                             \
        (                                                                                   \
            __IF__ (  (__tsf_diff_64__) < 0  )                                              \
                __THEN__ (                                                                  \
                            __IF__( (__tsf_diff_64__) < (int64)(-0x7FFFFFFFLL) )            \
                                __THEN__(FALSE)                                             \
                                __ELSE__(TRUE )                                             \
                         )                                                                  \
                __ELSE__ (                                                                  \
                            __IF__( (__tsf_diff_64__) > (int64)(+0x7FFFFFFFLL) )            \
                                __THEN__(FALSE)                                             \
                                __ELSE__(TRUE )                                             \
                         )                                                                  \
        ) // MACRO IS_TSF_DIFF_64_CASTABLE_TO_TSF_DIFF_32(). //

//----------------------------------------------------------------------------//
// CEIL_DIVIDE - divide and obtain the ceil value of the quotient.            //
//----------------------------------------------------------------------------//
// (Reference: http://en.wikipedia.org/wiki/Floor_and_ceiling_functions)      //
// This is done as follows:                                                   //
// a = dividend                                                               //
// b = divisor                                                                //
// q = ceil (a/b)                                                             //
//   = floor( (a+b-1)/b )                                                     //
//   = floor( (a-1)/b + b/b )                                                 //
//   = floor( (a-1)/b ) + 1                                                   //
// Now, standard C integer division is essentially a floor division.          //
// I.e., in C language:                                                       //
// q = a/b ==> q = floor(a/b)                                                 //
// Thus, in C language the following is true:                                 //
// q = ceil(a/b) = floor((a-1)/b) + 1 = ((a-1)/b) + 1 = (a-1)/b + 1           //
//----------------------------------------------------------------------------//
#define  CEIL_DIVIDE(__dividend__, __divisor__)             \
         (                                                  \
            (                                               \
                    ((__dividend__) - 1)                    \
                    /                                       \
                    (__divisor__       )                    \
            )                                               \
            +                                               \
            1                                               \
         ) // MACRO CEIL_DIVIDE(). //


//----------------------------------------------------------------------------//
// GCC extensions section.                                                    //
//----------------------------------------------------------------------------//
// P2P PS project.                                                            //
//----------------------------------------------------------------------------//
// In the following, we provide some aid macro's to ease the using of GCC     //
// extensions.                                                                //
//                                                                            //
// The packed macro allows packing of structures.                             //
// We define here the packed attribute as the maximal packing allowed.        //
//                                                                            //
//----------------------------------------------------------------------------//
#define __PACKED__      __attribute__((aligned(1)))  __attribute__((packed))
#define __UNALIGNED__   __attribute__((aligned(1)))


//----------------------------------------------------------------------------//
// multi-role scheduler                                                       //
//----------------------------------------------------------------------------//
// for compiling in GCC compielrs - we occassionally need to enforce inlining //
// extensions.                                                                //
//                                                                            //
// The packed macro allows packing of structures.                             //
// We define here the packed attribute as the maximal packing allowed.        //
//                                                                            //
//----------------------------------------------------------------------------//
#if !defined(__INLINE__)
#       define __INLINE__   inline
#endif

//----------------------------------------------------------------------------//
// In order to verify whether type is a volatile (for example:                //
// bit banding usage), comparison of type performed and causing compilation   //
// fault in case type not matched.                                            //
// Same method can be used for different type comparisons                     //
//----------------------------------------------------------------------------//
#define __VAR_LINE       	 				   _VAR_LINE(__LINE__)
#define _VAR_LINE(line)       					VAR_LINE(line)
#define VAR_LINE(line)        					redundent_ ## line
#define __COMPILATION_FAULT(types_compatible)   typedef char __VAR_LINE[(types_compatible) ? 1 : -1]

// 							IMPORTANT!!!!							      	  //
// 							IMPORTANT!!!!							      	  //
// INPUT: Must be a pointer to the parameter you wish to compare			  //
// 							IMPORTANT!!!!							      	  //
// 							IMPORTANT!!!!							      	  //
#define VOLATILE_COMPARISON(ptr) \
    __COMPILATION_FAULT (__builtin_types_compatible_p(typeof(ptr), typeof(volatile int    * )) || \
						 __builtin_types_compatible_p(typeof(ptr), typeof(volatile uint16_t * )) || \
						 __builtin_types_compatible_p(typeof(ptr), typeof(volatile int16_t  * )) || \
						 __builtin_types_compatible_p(typeof(ptr), typeof(volatile uint32_t * )) || \
						 __builtin_types_compatible_p(typeof(ptr), typeof(volatile int32_t  * )) || \
						 __builtin_types_compatible_p(typeof(ptr), typeof(volatile UINT64 * )) || \
						 __builtin_types_compatible_p(typeof(ptr), typeof(volatile uint8_t  * )) || \
						 __builtin_types_compatible_p(typeof(ptr), typeof(volatile int8_t   * )) || \
						 __builtin_types_compatible_p(typeof(ptr), typeof(volatile char   * ))	)

//----------------------------------------------------------------------------//
// MAC address macros		                              //
//----------------------------------------------------------------------------//
//
// Translate MAC address to a string, mainly for logging
// User is responsible to supply a destination buffer of MAC_STR_LEN bytes in
// order to avoid dynamic allocation.
#define MAC_STR_LEN	(20)
#define GET_MAC_STR(mac, str)								\
		( 													\
			sprintf(str, "%02x:%02x:%02x:%02x:%02x:%02x",	\
					mac[0], mac[1], mac[2],					\
					mac[3], mac[4], mac[5])					\
		)

//--------------------------------------------------------------------------------------------------
// imported from cc3100 - 18/6/2014
// dbg_get_func_caller is a helper macro to find out
// from which address the function was called
// usage must be at the very first line of the function
// and also surround the function in which the macro is used
// with the following lines before the function:
// #pragma diag_suppress 551 // Ignore uninitialized variable warning
// #pragma diag_suppress 179 // Ignore unreferenced variable warning
//
// and with the following lines after the function:
// #pragma diag_warning 179 // Re-enable unreferenced variable warning
// #pragma diag_warning 551 // Re-enable uninitialized variable warning
//
// e.g.:
// #pragma diag_suppress 551 // Ignore uninitialized variable warning
// #pragma diag_suppress 179 // Ignore unreferenced variable warning
// uint8_t foo(void)
// {
//     dbg_get_func_caller(lr); // <-- must be first call in function
//     ..
// }
// #pragma diag_warning 179 // Re-enable unreferenced variable warning
// #pragma diag_warning 551 // Re-enable uninitialized variable warning
//
// after the above call to dbg_get_func_caller, the variable lr
// will contain the address of the caller function
#define dbg_get_func_caller(lr)   \
            uint32_t lr;            \
            asm("        MOV       A1, LR") ; \
//--------------------------------------------------------------------------------------------------

/**
 * \def IP_COPY
 * \brief Macro which copies IP V4 source to IP V4 destination
 */
#define IP_COPY(dst,src)            ((uint8_t*)(dst))[0] = ((uint8_t*)(src))[0]; \
                                    ((uint8_t*)(dst))[1] = ((uint8_t*)(src))[1]; \
                                    ((uint8_t*)(dst))[2] = ((uint8_t*)(src))[2]; \
                                    ((uint8_t*)(dst))[3] = ((uint8_t*)(src))[3]; \
/**
 * \def MAC_COPY
 * \brief Macro which copies 6 bytes source to 6 bytes destination \n
 * Due to alignment exceptions MAC_COPY is done byte by byte
 */
#define MAC_COPY(dst,src)           ((uint8_t*)(dst))[0] = ((uint8_t*)(src))[0]; \
                                    ((uint8_t*)(dst))[1] = ((uint8_t*)(src))[1]; \
                                    ((uint8_t*)(dst))[2] = ((uint8_t*)(src))[2]; \
                                    ((uint8_t*)(dst))[3] = ((uint8_t*)(src))[3]; \
                                    ((uint8_t*)(dst))[4] = ((uint8_t*)(src))[4]; \
                                    ((uint8_t*)(dst))[5] = ((uint8_t*)(src))[5]
/**
 * \def MAC_EQUAL
 * \brief Macro which compares 6 bytes ofmac1 to 6 bytes of mac2 and returns True if all are equall \n
 * Otherwise returns False \n
 * Due to alignment exceptions MAC_EQUAL is done byte by byte
 */
#define MAC_EQUAL(mac1,mac2)        (((uint8_t*)(mac1))[0] == ((uint8_t*)(mac2))[0] && \
                                     ((uint8_t*)(mac1))[1] == ((uint8_t*)(mac2))[1] && \
                                     ((uint8_t*)(mac1))[2] == ((uint8_t*)(mac2))[2] && \
                                     ((uint8_t*)(mac1))[3] == ((uint8_t*)(mac2))[3] && \
                                     ((uint8_t*)(mac1))[4] == ((uint8_t*)(mac2))[4] && \
                                     ((uint8_t*)(mac1))[5] == ((uint8_t*)(mac2))[5])

/**
 * \def MAC_BROADCAST
 * \brief Macro which returns True if MAC address is broadcast (equals "\xff\xff\xff\xff\xff\xff") \n
 * Otherwise returns False
 */
#define MAC_BROADCAST(mac)          MAC_EQUAL (mac, "\xff\xff\xff\xff\xff\xff")
/**
 * \def MAC_NULL  - !!! use IRQ_UtilIsZeroMacAddress instead !!!
 * \brief Macro which returns True if MAC address is Null (equals "\x0\x0\x0\x0\x0\x0") \n
 * Otherwise returns False
 */
//#define MAC_NULL(mac)               MAC_EQUAL (mac, "\x0\x0\x0\x0\x0\x0")



/**
 * \def MAC_MULTICAST
 * \brief Macro which returns True if MAC address is Multicast\n
 * Otherwise returns False
 */
#define MAC_MULTICAST(mac)          ((mac)[0] & 0x01)


#define CONVERT_SIGN(num)           (1 + ~((uint32_t)(int32_t)num))



/**
 * \def GET_RSSI_VAL_FROM_DESC
 * \brief Macro which returns RSSI stored on the descriptor\n
 */
#define GET_RSSI_VAL_FROM_DESC(desc)      ( ((int8_t)(desc->phy_information1.rssi) - 110) )

/**
 * \def WLANTOHL
 * \brief  Handle endianness of Long in Little Endian host when opposing Big Endian data - swap bytes
 */
#define WLANTOHL(x)                 BYTE_SWAP_LONG (x)
/**
 * \def WLANTOHS
 * \brief  Handle endianness of Word in Little Endian host when opposing Big Endian data - swap bytes
 */
#define WLANTOHS(x)                 BYTE_SWAP_WORD (x)
/**
 * \def HTOWLANL
 * \brief  Handle endianness of Long in Little Endian host when opposing Big Endian data - swap bytes
 */
#define HTOWLANL(x)                 BYTE_SWAP_LONG (x)
/**
 * \def HTOWLANS
 * \brief  Handle endianness of Word in Little Endian host when opposing Big Endian data - swap bytes
 */
#define HTOWLANS(x)                 BYTE_SWAP_WORD (x)


#endif // #if !defined(__MACRO_UTILS_included__) //

