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
/*-----------------------------------------------------------------------------

 FILENAME:       register_macros.h

 DESCRIPTION:    This file defines macros for accessing HW registers.
 SET_FIELD/GET_FIELD (or fields) should be used whenever possible.
 Registers & fields defined in one of the cc33_REG_FILE_NAME.h
 located at exp directory.

 ----------------------------------------------------------------------------- */
#ifndef __REGISTER_MACROS_H_
#define __REGISTER_MACROS_H_

#include <osi_type.h>
//CC33xx        - Imported from hdk_register_maps.h
//				  legacy load and store regs for implicit
//				  address access
//				  prefere not to use those but only the SET_FIELD/GET_FIELD below
//
#define REG_ADDR_CAST(addr)     ((volatile uint32 *)(addr))

#define LOAD_REG(addr)          ( * REG_ADDR_CAST(addr) )
#define STORE_REG(addr,val)     { * REG_ADDR_CAST(addr) = (val); }


typedef volatile uint32* RegTypePtr_t;

#define REGISTER(address) (*(volatile uint32 *)(address))

////////////////////////////////////////////////

////////////////////////////////////////////////
// CC33XX New Register Macros
////////////////////////////////////////////////



//
// CC33xx        - setting register field into a local variable
//                 so that accessing the actual register will be done only after the local
#define SET_FIELD_REGISTER_FROM_VARIABLE(_base_reg, _field, _val) REGISTER(_base_reg) = SET_FIELD_TO_LOCAL(_field,_val)

// exmple:
// _local = SET_FIELD_TO_LOCAL( _field, _val)
// 16/10/2017 - there is an error in this macro. in the second part (read-modify-write) we read the register
// that was used for defining the fields, although the update operation takes place on local variable.
// no read modify write should take place when using this macro.
// see fixed macro below.
#define SET_FIELD_TO_LOCAL_obs( _field, _val)   \
	    ( \
	        (VERIFY_ARGUMENT_IS_A_REGISTER_OR_FIELD(_field)), \
	        (VERIFY_WRITABLE(_field)),\
	        ( \
	            ((REG_PARSE_FLDCNT(_field) == 1) || ((REG_PARSE_FROMBIT(_field) == 0) && (REG_PARSE_TOBIT_RAW(_field) == 0))) ? \
	                 ( \
	                 (REG_PARSE_SIZE(_field) == REG_SIZE_32BITS) ? \
	                        FORMAT_FIELD_32((_val), REG_PARSE_FROMBIT(_field), REG_PARSE_FLDLEN(_field)) \
	                    : \
	                    (REG_PARSE_SIZE(_field) == REG_SIZE_16BITS) ? \
	                    	FORMAT_FIELD_32((_val), REG_PARSE_FROMBIT(_field), REG_PARSE_FLDLEN(_field)) \
	                    : \
	                        FORMAT_FIELD_32((_val), REG_PARSE_FROMBIT(_field), REG_PARSE_FLDLEN(_field)) \
	                 ) \
	            : \
	                 ( \
	                    (VERIFY_READABLE(_field)), \
	                    (REG_PARSE_SIZE(_field) == REG_SIZE_32BITS) ? \
	                    		(get_32_bits(REG_PARSE_ADDR(_field)) & GENERATE_FIELD_MASK_32(REG_PARSE_FROMBIT(_field), REG_PARSE_FLDLEN(_field))) | FORMAT_FIELD_32((_val), REG_PARSE_FROMBIT(_field), REG_PARSE_FLDLEN(_field)) \
	                    : \
	                    (REG_PARSE_SIZE(_field) == REG_SIZE_16BITS) ? \
	                    		(get_16_bits(REG_PARSE_ADDR(_field)) & GENERATE_FIELD_MASK_32(REG_PARSE_FROMBIT(_field), REG_PARSE_FLDLEN(_field))) | FORMAT_FIELD_32((_val), REG_PARSE_FROMBIT(_field), REG_PARSE_FLDLEN(_field)) \
	                    : \
	                            (get_8_bits_only(REG_PARSE_ADDR(_field)) & GENERATE_FIELD_MASK_32(REG_PARSE_FROMBIT(_field), REG_PARSE_FLDLEN(_field))) | FORMAT_FIELD_32((_val), REG_PARSE_FROMBIT(_field), REG_PARSE_FLDLEN(_field)) \
	                 ) \
	        ) \
	    )

#define SET_FIELD_TO_LOCAL( _field, _val)   \
        ( \
            (VERIFY_ARGUMENT_IS_A_REGISTER_OR_FIELD(_field)), \
            (VERIFY_WRITABLE(_field)),\
            ( \
                     ( \
                     (REG_PARSE_SIZE(_field) == REG_SIZE_32BITS) ? \
                            FORMAT_FIELD_32((_val), REG_PARSE_FROMBIT(_field), REG_PARSE_FLDLEN(_field)) \
                        : \
                        (REG_PARSE_SIZE(_field) == REG_SIZE_16BITS) ? \
                            FORMAT_FIELD_32((_val), REG_PARSE_FROMBIT(_field), REG_PARSE_FLDLEN(_field)) \
                        : \
                            FORMAT_FIELD_32((_val), REG_PARSE_FROMBIT(_field), REG_PARSE_FLDLEN(_field)) \
                     ) \
            ) \
        )

#define SET_FIELD(_field, _val)	\
	( \
		(VERIFY_ARGUMENT_IS_A_REGISTER_OR_FIELD(_field)), \
		(VERIFY_WRITABLE(_field)),\
		( \
			((REG_PARSE_FLDCNT(_field) == 1) || ((REG_PARSE_FROMBIT(_field) == 0) && (REG_PARSE_TOBIT_RAW(_field) == 0))) ? \
				 ( \
				 (REG_PARSE_SIZE(_field) == REG_SIZE_32BITS) ? \
				 		set_32_bits(REG_PARSE_ADDR(_field), FORMAT_FIELD_32((_val), REG_PARSE_FROMBIT(_field), REG_PARSE_FLDLEN(_field))) \
				 	: \
				 	(REG_PARSE_SIZE(_field) == REG_SIZE_16BITS) ? \
				 		set_16_bits(REG_PARSE_ADDR(_field), FORMAT_FIELD_32((_val), REG_PARSE_FROMBIT(_field), REG_PARSE_FLDLEN(_field))) \
				 	: \
				 		set_8_bits_only(REG_PARSE_ADDR(_field), FORMAT_FIELD_32((_val), REG_PARSE_FROMBIT(_field), REG_PARSE_FLDLEN(_field))) \
				 ) \
		 	: \
				 ( \
					(VERIFY_READABLE(_field)), \
				 	(REG_PARSE_SIZE(_field) == REG_SIZE_32BITS) ? \
				 		set_32_bits(REG_PARSE_ADDR(_field), (get_32_bits(REG_PARSE_ADDR(_field)) & GENERATE_FIELD_MASK_32(REG_PARSE_FROMBIT(_field), REG_PARSE_FLDLEN(_field))) | FORMAT_FIELD_32((_val), REG_PARSE_FROMBIT(_field), REG_PARSE_FLDLEN(_field))) \
				 	: \
				 	(REG_PARSE_SIZE(_field) == REG_SIZE_16BITS) ? \
				 		set_16_bits(REG_PARSE_ADDR(_field), (get_16_bits(REG_PARSE_ADDR(_field)) & GENERATE_FIELD_MASK_32(REG_PARSE_FROMBIT(_field), REG_PARSE_FLDLEN(_field))) | FORMAT_FIELD_32((_val), REG_PARSE_FROMBIT(_field), REG_PARSE_FLDLEN(_field))) \
				 	: \
				 		set_8_bits_only(REG_PARSE_ADDR(_field), (get_8_bits_only(REG_PARSE_ADDR(_field)) & GENERATE_FIELD_MASK_32(REG_PARSE_FROMBIT(_field), REG_PARSE_FLDLEN(_field))) | FORMAT_FIELD_32((_val), REG_PARSE_FROMBIT(_field), REG_PARSE_FLDLEN(_field))) \
				 ) \
		) \
	)

#define SET_2_FIELDS(_field1, _val1, _field2, _val2)	\
	( \
		(VERIFY_ARGUMENT_IS_A_REGISTER_OR_FIELD(_field1)), \
		(VERIFY_ARGUMENT_IS_A_REGISTER_OR_FIELD(_field2)), \
		(VERIFY_WRITABLE(_field1)), \
		(VERIFY_WRITABLE(_field2)), \
		SET_2_FIELDS_VALIDATE_ARGS((_field1), (_val1), (_field2), (_val2)), \
		( \
		 	((REG_PARSE_FLDCNT(_field1) <= 2)) ? \
				 ( \
				 	(REG_PARSE_SIZE(_field1) == REG_SIZE_32BITS) ? \
				 		set_32_bits(REG_PARSE_ADDR(_field1), \
				 			FORMAT_FIELD_32((_val1), REG_PARSE_FROMBIT(_field1), REG_PARSE_FLDLEN(_field1)) \
				 			| FORMAT_FIELD_32((_val2), REG_PARSE_FROMBIT(_field2), REG_PARSE_FLDLEN(_field2))) \
				 	: \
				 	(REG_PARSE_SIZE(_field1) == REG_SIZE_16BITS) ? \
				 		set_16_bits(REG_PARSE_ADDR(_field1), \
				 			FORMAT_FIELD_32((_val1), REG_PARSE_FROMBIT(_field1), REG_PARSE_FLDLEN(_field1)) \
				 			| FORMAT_FIELD_32((_val2), REG_PARSE_FROMBIT(_field2), REG_PARSE_FLDLEN(_field2))) \
				 	: \
				 		set_8_bits_only(REG_PARSE_ADDR(_field1), \
				 			FORMAT_FIELD_32((_val1), REG_PARSE_FROMBIT(_field1), REG_PARSE_FLDLEN(_field1)) \
				 			| FORMAT_FIELD_32((_val2), REG_PARSE_FROMBIT(_field2), REG_PARSE_FLDLEN(_field2))) \
				 ) \
		 	: \
				 ( \
					(VERIFY_READABLE(_field1)), \
				 	(REG_PARSE_SIZE(_field1) == REG_SIZE_32BITS) ? \
				 		set_32_bits(REG_PARSE_ADDR(_field1), \
				 			(get_32_bits(REG_PARSE_ADDR(_field1)) \
				 			& GENERATE_FIELD_MASK_32(REG_PARSE_FROMBIT(_field1), REG_PARSE_FLDLEN(_field1)) \
				 			& GENERATE_FIELD_MASK_32(REG_PARSE_FROMBIT(_field2), REG_PARSE_FLDLEN(_field2)) \
				 			) \
				 			| FORMAT_FIELD_32((_val1), REG_PARSE_FROMBIT(_field1), REG_PARSE_FLDLEN(_field1)) \
				 			| FORMAT_FIELD_32((_val2), REG_PARSE_FROMBIT(_field2), REG_PARSE_FLDLEN(_field2))) \
				 	: \
				 	(REG_PARSE_SIZE(_field1) == REG_SIZE_16BITS) ? \
				 		set_16_bits(REG_PARSE_ADDR(_field1), \
				 			(get_16_bits(REG_PARSE_ADDR(_field1)) \
				 			& GENERATE_FIELD_MASK_32(REG_PARSE_FROMBIT(_field1), REG_PARSE_FLDLEN(_field1)) \
				 			& GENERATE_FIELD_MASK_32(REG_PARSE_FROMBIT(_field2), REG_PARSE_FLDLEN(_field2)) \
				 			) \
				 			| FORMAT_FIELD_32((_val1), REG_PARSE_FROMBIT(_field1), REG_PARSE_FLDLEN(_field1)) \
				 			| FORMAT_FIELD_32((_val2), REG_PARSE_FROMBIT(_field2), REG_PARSE_FLDLEN(_field2))) \
				 	: \
				 		set_8_bits_only(REG_PARSE_ADDR(_field1), \
				 			(get_8_bits_only(REG_PARSE_ADDR(_field1)) \
				 			& GENERATE_FIELD_MASK_32(REG_PARSE_FROMBIT(_field1), REG_PARSE_FLDLEN(_field1)) \
				 			& GENERATE_FIELD_MASK_32(REG_PARSE_FROMBIT(_field2), REG_PARSE_FLDLEN(_field2)) \
				 			) \
				 			| FORMAT_FIELD_32((_val1), REG_PARSE_FROMBIT(_field1), REG_PARSE_FLDLEN(_field1)) \
				 			| FORMAT_FIELD_32((_val2), REG_PARSE_FROMBIT(_field2), REG_PARSE_FLDLEN(_field2))) \
				 ) \
		) \
	)

#define SET_3_FIELDS(_field1, _val1, _field2, _val2, _field3, _val3)	\
	( \
		(VERIFY_ARGUMENT_IS_A_REGISTER_OR_FIELD(_field1)), \
		(VERIFY_ARGUMENT_IS_A_REGISTER_OR_FIELD(_field2)), \
		(VERIFY_ARGUMENT_IS_A_REGISTER_OR_FIELD(_field3)), \
		(VERIFY_WRITABLE(_field1)), \
		(VERIFY_WRITABLE(_field2)), \
		(VERIFY_WRITABLE(_field3)), \
		SET_3_FIELDS_VALIDATE_ARGS((_field1), (_val1), (_field2), (_val2), (_field3), (_val3)), \
		( \
		 	((REG_PARSE_FLDCNT(_field1) <= 3)) ? \
				 ( \
				 	(REG_PARSE_SIZE(_field1) == REG_SIZE_32BITS) ? \
				 		set_32_bits(REG_PARSE_ADDR(_field1), \
				 			FORMAT_FIELD_32((_val1), REG_PARSE_FROMBIT(_field1), REG_PARSE_FLDLEN(_field1)) \
				 			| FORMAT_FIELD_32((_val2), REG_PARSE_FROMBIT(_field2), REG_PARSE_FLDLEN(_field2)) \
				 			| FORMAT_FIELD_32((_val3), REG_PARSE_FROMBIT(_field3), REG_PARSE_FLDLEN(_field3))) \
				 	: \
				 	(REG_PARSE_SIZE(_field1) == REG_SIZE_16BITS) ? \
				 		set_16_bits(REG_PARSE_ADDR(_field1), \
				 			FORMAT_FIELD_32((_val1), REG_PARSE_FROMBIT(_field1), REG_PARSE_FLDLEN(_field1)) \
				 			| FORMAT_FIELD_32((_val2), REG_PARSE_FROMBIT(_field2), REG_PARSE_FLDLEN(_field2)) \
				 			| FORMAT_FIELD_32((_val3), REG_PARSE_FROMBIT(_field3), REG_PARSE_FLDLEN(_field3))) \
				 	: \
				 		set_8_bits_only(REG_PARSE_ADDR(_field1), \
				 			FORMAT_FIELD_32((_val1), REG_PARSE_FROMBIT(_field1), REG_PARSE_FLDLEN(_field1)) \
				 			| FORMAT_FIELD_32((_val2), REG_PARSE_FROMBIT(_field2), REG_PARSE_FLDLEN(_field2)) \
				 			| FORMAT_FIELD_32((_val3), REG_PARSE_FROMBIT(_field3), REG_PARSE_FLDLEN(_field3))) \
				 ) \
		 	: \
				 ( \
				 	(REG_PARSE_SIZE(_field1) == REG_SIZE_32BITS) ? \
					(VERIFY_READABLE(_field1)), \
				 		set_32_bits(REG_PARSE_ADDR(_field1), \
				 			(get_32_bits(REG_PARSE_ADDR(_field1)) \
				 			& GENERATE_FIELD_MASK_32(REG_PARSE_FROMBIT(_field1), REG_PARSE_FLDLEN(_field1)) \
				 			& GENERATE_FIELD_MASK_32(REG_PARSE_FROMBIT(_field2), REG_PARSE_FLDLEN(_field2)) \
				 			& GENERATE_FIELD_MASK_32(REG_PARSE_FROMBIT(_field3), REG_PARSE_FLDLEN(_field3)) \
				 			) \
				 			| FORMAT_FIELD_32((_val1), REG_PARSE_FROMBIT(_field1), REG_PARSE_FLDLEN(_field1)) \
				 			| FORMAT_FIELD_32((_val2), REG_PARSE_FROMBIT(_field2), REG_PARSE_FLDLEN(_field2)) \
				 			| FORMAT_FIELD_32((_val3), REG_PARSE_FROMBIT(_field3), REG_PARSE_FLDLEN(_field3))) \
				 	: \
				 	(REG_PARSE_SIZE(_field1) == REG_SIZE_16BITS) ? \
				 		set_16_bits(REG_PARSE_ADDR(_field1), \
				 			(get_16_bits(REG_PARSE_ADDR(_field1)) \
				 			& GENERATE_FIELD_MASK_32(REG_PARSE_FROMBIT(_field1), REG_PARSE_FLDLEN(_field1)) \
				 			& GENERATE_FIELD_MASK_32(REG_PARSE_FROMBIT(_field2), REG_PARSE_FLDLEN(_field2)) \
				 			& GENERATE_FIELD_MASK_32(REG_PARSE_FROMBIT(_field3), REG_PARSE_FLDLEN(_field3)) \
				 			) \
				 			| FORMAT_FIELD_32((_val1), REG_PARSE_FROMBIT(_field1), REG_PARSE_FLDLEN(_field1)) \
				 			| FORMAT_FIELD_32((_val2), REG_PARSE_FROMBIT(_field2), REG_PARSE_FLDLEN(_field2)) \
				 			| FORMAT_FIELD_32((_val3), REG_PARSE_FROMBIT(_field3), REG_PARSE_FLDLEN(_field3))) \
				 	: \
				 		set_8_bits_only(REG_PARSE_ADDR(_field1), \
				 			(get_8_bits_only(REG_PARSE_ADDR(_field1)) \
				 			& GENERATE_FIELD_MASK_32(REG_PARSE_FROMBIT(_field1), REG_PARSE_FLDLEN(_field1)) \
				 			& GENERATE_FIELD_MASK_32(REG_PARSE_FROMBIT(_field2), REG_PARSE_FLDLEN(_field2)) \
				 			& GENERATE_FIELD_MASK_32(REG_PARSE_FROMBIT(_field3), REG_PARSE_FLDLEN(_field3)) \
				 			) \
				 			| FORMAT_FIELD_32((_val1), REG_PARSE_FROMBIT(_field1), REG_PARSE_FLDLEN(_field1)) \
				 			| FORMAT_FIELD_32((_val2), REG_PARSE_FROMBIT(_field2), REG_PARSE_FLDLEN(_field2)) \
				 			| FORMAT_FIELD_32((_val3), REG_PARSE_FROMBIT(_field3), REG_PARSE_FLDLEN(_field3))) \
				 ) \
		) \
	)

//----------------------------------------------------------------------------------
// IMPORTANT:
// SET_WRITE_ONLY_FIELD macro is currently not allowed to be used
// it doesn't do what you'd expect.
// in order to write to registers, do SET_FIELD on register name
//set write only field
//#define SET_WRITE_ONLY_FIELD(_field, _val)	\
//	( \
//		(VERIFY_ARGUMENT_IS_A_REGISTER_OR_FIELD(_field)), \
//		(VERIFY_WRITABLE(_field)),\
//		( \
//			((REG_PARSE_FLDCNT(_field) == 1) || ((REG_PARSE_FROMBIT(_field) == 0) && (REG_PARSE_TOBIT_RAW(_field) == 0))) ? \
//				 ( \
//				 (REG_PARSE_SIZE(_field) == REG_SIZE_32BITS) ? \
//				 		set_32_bits(REG_PARSE_ADDR(_field), FORMAT_FIELD_32((_val), REG_PARSE_FROMBIT(_field), REG_PARSE_FLDLEN(_field))) \
//				 	: \
//				 	(REG_PARSE_SIZE(_field) == REG_SIZE_16BITS) ? \
//				 		set_16_bits(REG_PARSE_ADDR(_field), FORMAT_FIELD_32((_val), REG_PARSE_FROMBIT(_field), REG_PARSE_FLDLEN(_field))) \
//				 	: \
//				 		set_8_bits_only(REG_PARSE_ADDR(_field), FORMAT_FIELD_32((_val), REG_PARSE_FROMBIT(_field), REG_PARSE_FLDLEN(_field))) \
//				 ) \
//		 	: \
//				 ( \
//				 	(REG_PARSE_SIZE(_field) == REG_SIZE_32BITS) ? \
//				 		set_32_bits(REG_PARSE_ADDR(_field), GENERATE_FIELD_MASK_32(REG_PARSE_FROMBIT(_field), REG_PARSE_FLDLEN(_field)) | FORMAT_FIELD_32((_val), REG_PARSE_FROMBIT(_field), REG_PARSE_FLDLEN(_field))) \
//				 	: \
//				 	(REG_PARSE_SIZE(_field) == REG_SIZE_16BITS) ? \
//				 		set_16_bits(REG_PARSE_ADDR(_field), GENERATE_FIELD_MASK_32(REG_PARSE_FROMBIT(_field), REG_PARSE_FLDLEN(_field)) | FORMAT_FIELD_32((_val), REG_PARSE_FROMBIT(_field), REG_PARSE_FLDLEN(_field))) \
//				 	: \
//				 		set_8_bits_only(REG_PARSE_ADDR(_field), GENERATE_FIELD_MASK_32(REG_PARSE_FROMBIT(_field), REG_PARSE_FLDLEN(_field)) | FORMAT_FIELD_32((_val), REG_PARSE_FROMBIT(_field), REG_PARSE_FLDLEN(_field))) \
//				 ) \
//		) \
//	)
//
//----------------------------------------------------------------------------------

// CC33xx        - if register is in a variable (say lut or inputted parameter)
//                 then GET/SET_FIELD wont work as it needs the implicit register string here
//                 so for that we will use the legacy "REGISTER" call with the GET_FIELD_FROM_LOCAL

#define GET_FIELD_REGISTER_FROM_VARIABLE(_base_reg, _field) GET_FIELD_FROM_LOCAL(REGISTER(_base_reg),_field)


#define GET_FIELD_FROM_LOCAL(_local,_field)   \
    ( \
        (VERIFY_ARGUMENT_IS_A_REGISTER_OR_FIELD(_field)), \
        (VERIFY_READABLE(_field)), \
        GET_FIELD_VALIDATE_ARGS(_field), \
        ( \
            (REG_PARSE_SIZE(_field) == REG_SIZE_32BITS) ? \
                PARSE_FIELD_32((_local), REG_PARSE_FROMBIT(_field), REG_PARSE_FLDLEN(_field)) \
            : \
            (REG_PARSE_SIZE(_field) == REG_SIZE_16BITS) ? \
                PARSE_FIELD_16((_local), REG_PARSE_FROMBIT(_field), REG_PARSE_FLDLEN(_field)) \
            : \
                PARSE_FIELD_8((_local), REG_PARSE_FROMBIT(_field), REG_PARSE_FLDLEN(_field)) \
        ) \
    )


#define GET_FIELD(_field)	\
	( \
		(VERIFY_ARGUMENT_IS_A_REGISTER_OR_FIELD(_field)), \
		(VERIFY_READABLE(_field)), \
		GET_FIELD_VALIDATE_ARGS(_field), \
		( \
		 	(REG_PARSE_SIZE(_field) == REG_SIZE_32BITS) ? \
		 		PARSE_FIELD_32(get_32_bits(REG_PARSE_ADDR(_field)), REG_PARSE_FROMBIT(_field), REG_PARSE_FLDLEN(_field)) \
		 	: \
		 	(REG_PARSE_SIZE(_field) == REG_SIZE_16BITS) ? \
		 		PARSE_FIELD_16(get_16_bits(REG_PARSE_ADDR(_field)), REG_PARSE_FROMBIT(_field), REG_PARSE_FLDLEN(_field)) \
		 	: \
		 		PARSE_FIELD_8(get_8_bits_only(REG_PARSE_ADDR(_field)), REG_PARSE_FROMBIT(_field), REG_PARSE_FLDLEN(_field)) \
		) \
	)


#define GET_2_FIELDS(_field1, _val1ptr, _field2, _val2ptr, _tempvalptr) \
	( \
		(VERIFY_ARGUMENT_IS_A_REGISTER_OR_FIELD(_field1)), \
		(VERIFY_ARGUMENT_IS_A_REGISTER_OR_FIELD(_field2)), \
		(VERIFY_READABLE(_field1)), \
		(VERIFY_READABLE(_field2)), \
		GET_2_FIELDS_VALIDATE_ARGS((_field1), (_val1ptr), (_field2), (_val2ptr), (_tempvalptr)), \
		( \
			((_tempvalptr) == NULL) ? \
				( \
				 	(REG_PARSE_SIZE(_field1) == REG_SIZE_32BITS) ? \
				 		(((*(_val1ptr)) = PARSE_FIELD_32(get_32_bits(REG_PARSE_ADDR(_field1)), REG_PARSE_FROMBIT(_field1), REG_PARSE_FLDLEN(_field1))), \
				 		((*(_val2ptr)) = PARSE_FIELD_32(get_32_bits(REG_PARSE_ADDR(_field2)), REG_PARSE_FROMBIT(_field2), REG_PARSE_FLDLEN(_field2)))) \
				 	: \
				 	(REG_PARSE_SIZE(_field1) == REG_SIZE_16BITS) ? \
				 		(((*(_val1ptr)) = PARSE_FIELD_16(get_16_bits(REG_PARSE_ADDR(_field1)), REG_PARSE_FROMBIT(_field1), REG_PARSE_FLDLEN(_field1))), \
				 		((*(_val2ptr)) = PARSE_FIELD_16(get_16_bits(REG_PARSE_ADDR(_field2)), REG_PARSE_FROMBIT(_field2), REG_PARSE_FLDLEN(_field2)))) \
				 	: \
				 		(((*(_val1ptr)) = PARSE_FIELD_8(get_8_bits_only(REG_PARSE_ADDR(_field1)), REG_PARSE_FROMBIT(_field1), REG_PARSE_FLDLEN(_field1))), \
				 		((*(_val2ptr)) = PARSE_FIELD_8(get_8_bits_only(REG_PARSE_ADDR(_field2)), REG_PARSE_FROMBIT(_field2), REG_PARSE_FLDLEN(_field2)))) \
				 ) \
			: \
				( \
				 	(REG_PARSE_SIZE(_field1) == REG_SIZE_32BITS) ? \
				 		(((*((uint32 *)(_tempvalptr))) = get_32_bits(REG_PARSE_ADDR(_field1))), \
				 		((*(_val1ptr)) = PARSE_FIELD_32((*((uint32 *)(_tempvalptr))), REG_PARSE_FROMBIT(_field1), REG_PARSE_FLDLEN(_field1))), \
				 		((*(_val2ptr)) = PARSE_FIELD_32((*((uint32 *)(_tempvalptr))), REG_PARSE_FROMBIT(_field2), REG_PARSE_FLDLEN(_field2)))) \
				 	: \
				 	(REG_PARSE_SIZE(_field1) == REG_SIZE_16BITS) ? \
				 		(((*((uint16 *)(_tempvalptr))) = get_16_bits(REG_PARSE_ADDR(_field1))), \
				 		((*(_val1ptr)) = PARSE_FIELD_16((*((uint16 *)(_tempvalptr))), REG_PARSE_FROMBIT(_field1), REG_PARSE_FLDLEN(_field1))), \
				 		((*(_val2ptr)) = PARSE_FIELD_16((*((uint16 *)(_tempvalptr))), REG_PARSE_FROMBIT(_field2), REG_PARSE_FLDLEN(_field2)))) \
				 	: \
				 		(((*((uint8 *)(_tempvalptr))) = get_8_bits_only(REG_PARSE_ADDR(_field1))), \
				 		((*(_val1ptr)) = PARSE_FIELD_8((*((uint8 *)(_tempvalptr))), REG_PARSE_FROMBIT(_field1), REG_PARSE_FLDLEN(_field1))), \
				 		((*(_val2ptr)) = PARSE_FIELD_8((*((uint8 *)(_tempvalptr))), REG_PARSE_FROMBIT(_field2), REG_PARSE_FLDLEN(_field2)))) \
				 ) \
		) \
	)


#define GET_3_FIELDS(_field1, _val1ptr, _field2, _val2ptr, _field3, _val3ptr, _tempvalptr) \
	( \
		(VERIFY_ARGUMENT_IS_A_REGISTER_OR_FIELD(_field1)), \
		(VERIFY_ARGUMENT_IS_A_REGISTER_OR_FIELD(_field2)), \
		(VERIFY_ARGUMENT_IS_A_REGISTER_OR_FIELD(_field3)), \
		(VERIFY_READABLE(_field1)), \
		(VERIFY_READABLE(_field2)), \
		(VERIFY_READABLE(_field3)), \
		GET_3_FIELDS_VALIDATE_ARGS((_field1), (_val1ptr), (_field2), (_val2ptr), (_field3), (_val3ptr), (_tempvalptr)), \
		( \
			((_tempvalptr) == NULL) ? \
				( \
				 	(REG_PARSE_SIZE(_field1) == REG_SIZE_32BITS) ? \
				 		(((*(_val1ptr)) = PARSE_FIELD_32(get_32_bits(REG_PARSE_ADDR(_field1)), REG_PARSE_FROMBIT(_field1), REG_PARSE_FLDLEN(_field1))), \
				 		((*(_val2ptr)) = PARSE_FIELD_32(get_32_bits(REG_PARSE_ADDR(_field2)), REG_PARSE_FROMBIT(_field2), REG_PARSE_FLDLEN(_field2))), \
				 		((*(_val3ptr)) = PARSE_FIELD_32(get_32_bits(REG_PARSE_ADDR(_field3)), REG_PARSE_FROMBIT(_field3), REG_PARSE_FLDLEN(_field3)))) \
				 	: \
				 	(REG_PARSE_SIZE(_field1) == REG_SIZE_16BITS) ? \
				 		(((*(_val1ptr)) = PARSE_FIELD_16(get_16_bits(REG_PARSE_ADDR(_field1)), REG_PARSE_FROMBIT(_field1), REG_PARSE_FLDLEN(_field1))), \
				 		((*(_val2ptr)) = PARSE_FIELD_16(get_16_bits(REG_PARSE_ADDR(_field2)), REG_PARSE_FROMBIT(_field2), REG_PARSE_FLDLEN(_field2))), \
				 		((*(_val3ptr)) = PARSE_FIELD_16(get_16_bits(REG_PARSE_ADDR(_field3)), REG_PARSE_FROMBIT(_field3), REG_PARSE_FLDLEN(_field3)))) \
				 	: \
				 		(((*(_val1ptr)) = PARSE_FIELD_8(get_8_bits_only(REG_PARSE_ADDR(_field1)), REG_PARSE_FROMBIT(_field1), REG_PARSE_FLDLEN(_field1))), \
				 		((*(_val2ptr)) = PARSE_FIELD_8(get_8_bits_only(REG_PARSE_ADDR(_field2)), REG_PARSE_FROMBIT(_field2), REG_PARSE_FLDLEN(_field2))), \
				 		((*(_val3ptr)) = PARSE_FIELD_8(get_8_bits_only(REG_PARSE_ADDR(_field3)), REG_PARSE_FROMBIT(_field3), REG_PARSE_FLDLEN(_field3)))) \
				 ) \
			: \
				( \
				 	(REG_PARSE_SIZE(_field1) == REG_SIZE_32BITS) ? \
				 		(((*((uint32 *)(_tempvalptr))) = get_32_bits(REG_PARSE_ADDR(_field1))), \
				 		((*(_val1ptr)) = PARSE_FIELD_32((*((uint32 *)(_tempvalptr))), REG_PARSE_FROMBIT(_field1), REG_PARSE_FLDLEN(_field1))), \
				 		((*(_val2ptr)) = PARSE_FIELD_32((*((uint32 *)(_tempvalptr))), REG_PARSE_FROMBIT(_field2), REG_PARSE_FLDLEN(_field2))), \
				 		((*(_val3ptr)) = PARSE_FIELD_32((*((uint32 *)(_tempvalptr))), REG_PARSE_FROMBIT(_field3), REG_PARSE_FLDLEN(_field3)))) \
				 	: \
				 	(REG_PARSE_SIZE(_field1) == REG_SIZE_16BITS) ? \
				 		(((*((uint16 *)(_tempvalptr))) = get_16_bits(REG_PARSE_ADDR(_field1))), \
				 		((*(_val1ptr)) = PARSE_FIELD_16((*((uint16 *)(_tempvalptr))), REG_PARSE_FROMBIT(_field1), REG_PARSE_FLDLEN(_field1))), \
				 		((*(_val2ptr)) = PARSE_FIELD_16((*((uint16 *)(_tempvalptr))), REG_PARSE_FROMBIT(_field2), REG_PARSE_FLDLEN(_field2))), \
				 		((*(_val3ptr)) = PARSE_FIELD_16((*((uint16 *)(_tempvalptr))), REG_PARSE_FROMBIT(_field3), REG_PARSE_FLDLEN(_field3)))) \
				 	: \
				 		(((*((uint8 *)(_tempvalptr))) = get_8_bits_only(REG_PARSE_ADDR(_field1))), \
				 		((*(_val1ptr)) = PARSE_FIELD_8((*((uint8 *)(_tempvalptr))), REG_PARSE_FROMBIT(_field1), REG_PARSE_FLDLEN(_field1))), \
				 		((*(_val2ptr)) = PARSE_FIELD_8((*((uint8 *)(_tempvalptr))), REG_PARSE_FROMBIT(_field2), REG_PARSE_FLDLEN(_field2))), \
				 		((*(_val3ptr)) = PARSE_FIELD_8((*((uint8 *)(_tempvalptr))), REG_PARSE_FROMBIT(_field3), REG_PARSE_FLDLEN(_field3)))) \
				 ) \
		) \
	)

//######################################################################################################//
//Field is actually a 64bits constants, containing various information about a field inside a register, which is:
//	offset_from_base - Register's offset relative to a common base address (in the current implementation, the base address is 0, so this is actually the absolute address)
//	frombit - The bit-number (within the register) of the first bit of the field
//	tobit - The bit-number (within the register) of the last bit of the field
//	fldcnt - the total number of fields in the register
//	ipids - which IP's are allowed to access the register (relevant for TOP registers)
//	size - the register's size (16 or 32 bits)
//	index_intervals - the addresses difference between two consecutive elements (in case of registers array)
//	type - the register's type - read-only or read-write
//	Valid bit - Checks that the user didn't misuse the registers (mask or offset instead of proper composed registers).
//
//The format of the field constant:
//
//
//######################################################################################################//
//   63  |    62    |   61-53   | 52-51 |  50-49  | 48-47 | 46-44 | 43-42  | 41-37 | 36-32   |                 31-0                    |
// spare | validBit |   spare   | type  | idx_int | size  | ipids | fldcnt | tobit | frombit |             offs_fr_base                |
//######################################################################################################//


//######################################################################################################//
//dummy
//#define CURRENT_FILENAME_FOR_ERROR_REPORTING xxxxx
//######################################################################################################//

//#define ENABLE_FIELDS_ERROR_DETECTION

#define REG_ACCESS_BASE_ADDR			0

#define REG_OFFSET_FROM_BASE_OFFSET		0
#define REG_OFFSET_FROM_BASE_LEN		32

#define REG_FROMBIT_OFFSET				32
#define REG_FROMBIT_LEN					5

#define REG_TOBIT_OFFSET				37
#define REG_TOBIT_LEN					5

#define REG_FLDCNT_OFFSET				42
#define REG_FLDCNT_LEN					2
#define REG_FLDCNT_MAX_VALUE 			0x3

#define REG_IPIDs_OFFSET				44
#define REG_IPIDs_LEN					3

#define REG_SIZE_OFFSET					47
#define REG_SIZE_LEN					2
#define REG_SIZE_8BITS					0
#define REG_SIZE_16BITS					1
#define REG_SIZE_32BITS					2

#define REG_INDEX_INTERVAL_OFFSET		49
#define REG_INDEX_INTERVAL_LEN			2


#define REG_TYPE_OFFSET					51
#define REG_TYPE_LEN					2


#define REG_SPARE1_OFFSET				53
#define REG_SPARE1_LEN					 9

#define REG_VALID_BIT_OFFSET			62
#define REG_VALID_BIT_LEN				1

#define REG_SPARE2_OFFSET				63
#define REG_SPARE2_LEN					1


#define REG_INDEX_INTERVAL_0x10			0
#define REG_INDEX_INTERVAL_0x20			1
#define REG_INDEX_INTERVAL_0xFFU1		2
#define REG_INDEX_INTERVAL_0xFFU2		3

#define REG_TYPE_RW						0
#define REG_TYPE_RO						1
#define REG_TYPE_WO						2

#define REG_INVALID_REGISTER			0
#define REG_VALID_REGISTER				1


#define MASK_4_BITS     BITMASK_x_0(3)
#define MASK_1_BITS     BITMASK_x_0(0)


#define set_8_bits_only(_addr, _val)							((*(volatile uint8*)(_addr)) = ((uint8)(_val)))
#define get_8_bits_only(_addr)								    (*(volatile uint8*)(_addr))
#define set_16_bits(_addr, _val)								((*(volatile uint16 *)(_addr)) = ((uint16)(_val)))
#define get_16_bits(_addr)									    (*(volatile uint16 *)(_addr))
#define set_32_bits(_addr, _val)								((*(volatile uint32 *)(_addr)) = ((uint32)(_val)))
#define get_32_bits(_addr)									    (*(volatile uint32 *)(_addr))

#define set_4_bits(_addr, _val, _offset)           set_16_bits(_addr, (get_16_bits(_addr) & ~(MASK_4_BITS << _offset)) | (_val << _offset))
#define get_4_bits(_addr, _offset)                 ((get_16_bits(_addr) >> _offset) & MASK_4_BITS)
#define get_1_bit(_addr, _offset)                  ((get_16_bits(_addr) >> _offset) & MASK_1_BITS)

#define FORMAT_FIELD_64(_val, _offset, _len)		((((uint64)(_val)) << (_offset)) & (((_offset) + (_len)) < 64 ? ((((uint64)0x1) << ((_offset) + (_len)))-1) : 0xFFFFFFFFFFFFFFFF))
#define FORMAT_FIELD_32(_val, _offset, _len)		((((uint32)(_val)) << (_offset)) & (((_offset) + (_len)) < 32 ? ((((uint32)0x1) << ((_offset) + (_len)))-1) : 0xFFFFFFFF))
#define FORMAT_FIELD_8(_val, _offset, _len)		((((uint8)(_val)) << (_offset)) & (((_offset) + (_len)) < 8 ? ((((uint8)0x1) << ((_offset) + (_len)))-1) : 0xFF))
#define PARSE_FIELD_64(_val, _offset, _len)		((((uint64)(_val)) >> (_offset)) & (((_len) == 64) ? 0xFFFFFFFFFFFFFFFF : ((((uint64)0x1) << (_len)) - 1))) /*lint !e648 */
#define PARSE_FIELD_32(_val, _offset, _len)		((((uint32)(_val)) >> (_offset)) & (((_len) == 32) ? 0xFFFFFFFF : ((((uint32)0x1) << (_len)) - 1))) /*lint !e648 */
#define PARSE_FIELD_16(_val, _offset, _len)		((((uint16)(_val)) >> (_offset)) & ((((uint16)0x1) << (_len)) - 1)) /*lint !e648 */
#define PARSE_FIELD_8(_val, _offset, _len)		((((uint8)(_val)) >> (_offset)) & ((((uint8)0x1) << (_len)) - 1)) /*lint !e648 */

#define GENERATE_FIELD_MASK_64(_offset, _len)	(~((((_len) == 64) ? 0xFFFFFFFFFFFFFFFF : ((((uint64)0x1) << (_len)) - 1)) << (_offset)))
#define GENERATE_FIELD_MASK_32(_offset, _len)	(~((((_len) == 32) ? 0xFFFFFFFF : ((((uint32)0x1) << (_len)) - 1)) << (_offset)))
#define GENERATE_FIELD_MASK_8(_offset, _len)	(~((((_len) == 8) ? 0xFF : ((((uint8)0x1) << (_len)) - 1)) << (_offset)))

#define REG_PARSE_ACCESS(_field) 			((uint8)(PARSE_FIELD_64(	(_field),	REG_TYPE_OFFSET,			REG_TYPE_LEN	)))
#define REG_PARSE_ALLOWED_IPS(_field)		((uint8)(PARSE_FIELD_64(	(_field),	REG_IPIDs_OFFSET,				REG_IPIDs_LEN)))
#define REG_PARSE_FLDCNT(_field)			((uint8)(PARSE_FIELD_64(	(_field),	REG_FLDCNT_OFFSET,				REG_FLDCNT_LEN	) + 1))
#define REG_PARSE_SIZE(_field) 				((uint8)(PARSE_FIELD_64(	(_field),	REG_SIZE_OFFSET,				REG_SIZE_LEN	)))
#define REG_PARSE_FROMBIT(_field)			((uint8)(PARSE_FIELD_64(	(_field),	REG_FROMBIT_OFFSET,			REG_FROMBIT_LEN)))
#define REG_PARSE_TOBIT_RAW(_field)			((uint8)(PARSE_FIELD_64(	(_field),	REG_TOBIT_OFFSET,			REG_TOBIT_LEN)))
#define REG_PARSE_TOBIT(_field)				((uint8)(((REG_PARSE_SIZE(_field) == REG_SIZE_32BITS) ? 31 : (REG_PARSE_SIZE(_field) == REG_SIZE_16BITS) ? 15 : 7) - REG_PARSE_TOBIT_RAW(_field)))
#define REG_PARSE_ADDR(_field)				((uint32)(PARSE_FIELD_64(	(_field), REG_OFFSET_FROM_BASE_OFFSET,	REG_OFFSET_FROM_BASE_LEN) + REG_ACCESS_BASE_ADDR))
#define REG_PARSE_FLDLEN(_field) 			(REG_PARSE_TOBIT(_field) - REG_PARSE_FROMBIT(_field) + 1)
#define REG_PARSE_INDEX_INTERVAL(_field)	((((uint8)PARSE_FIELD_64(	(_field), REG_INDEX_INTERVAL_OFFSET, 		REG_INDEX_INTERVAL_LEN)) == REG_INDEX_INTERVAL_0x10) ? 0x10 : 0x20)
#define REG_PARSE_VALIDITY_BIT(_field)		((uint8)(PARSE_FIELD_64(	(_field),	REG_VALID_BIT_OFFSET,			REG_VALID_BIT_LEN)))
#define FIELD_PARSE_REG(_field)				((_field & (~ GENERATE_FIELD_MASK_64(REG_FROMBIT_OFFSET, REG_FROMBIT_LEN))) & (~ GENERATE_FIELD_MASK_64(REG_TOBIT_OFFSET, REG_TOBIT_LEN)))

#define SET_FIELD_VALIDATE_ARGS(_field, _val)	((void)((TOP_IP_ID_LOCAL & REG_PARSE_ALLOWED_IPS(_field)) ? 0 : REPORT_ERROR(_IP_IS_NOT_ALLOWED_TO_USE_REGISTER_))) //" #_field)))

#define VERIFY_ARGUMENT_IS_A_REGISTER_OR_FIELD(_field)		((void)((REG_PARSE_VALIDITY_BIT(_field) == REG_VALID_REGISTER) ? 0 : REPORT_ERROR(USED_NON_REGISTER_ARGUMENT)))
#define VERIFY_WRITABLE(_field)                             ((void)((REG_PARSE_ACCESS(_field) != REG_TYPE_RO) ? 0 : REPORT_ERROR(USED_NON_REGISTER_ARGUMENT)))
#define VERIFY_READABLE(_field)                             ((void)((REG_PARSE_ACCESS(_field) != REG_TYPE_WO) ? 0 : REPORT_ERROR(USED_NON_REGISTER_ARGUMENT)))

/* This macro manipulate bytes in variable, corresponding to the given field */
#define SET_FIELD_IN_VAR(_var, _field, _val)	\
	( \
		( \
		 	((REG_PARSE_FLDCNT(_field) == 1) || ((REG_PARSE_FROMBIT(_field) == 0) && (REG_PARSE_TOBIT_RAW(_field) == 0))) ? \
				 ( \
				 	(REG_PARSE_SIZE(_field) == REG_SIZE_32BITS) ? \
				 		((_var) = FORMAT_FIELD_32((_val), REG_PARSE_FROMBIT(_field), REG_PARSE_FLDLEN(_field))) \
				 	: \
				 	(REG_PARSE_SIZE(_field) == REG_SIZE_16BITS) ? \
				 		((_var) = FORMAT_FIELD_32((_val), REG_PARSE_FROMBIT(_field), REG_PARSE_FLDLEN(_field))) \
				 	: \
				 		((_var) = FORMAT_FIELD_32((_val), REG_PARSE_FROMBIT(_field), REG_PARSE_FLDLEN(_field))) \
				 ) \
		 	: \
				 ( \
				 	(REG_PARSE_SIZE(_field) == REG_SIZE_32BITS) ? \
				 		((_var) = (((_var) & GENERATE_FIELD_MASK_32(REG_PARSE_FROMBIT(_field), REG_PARSE_FLDLEN(_field))) | FORMAT_FIELD_32((_val), REG_PARSE_FROMBIT(_field), REG_PARSE_FLDLEN(_field)))) \
				 	: \
				 	(REG_PARSE_SIZE(_field) == REG_SIZE_16BITS) ? \
				 		((_var) = (((_var) & GENERATE_FIELD_MASK_32(REG_PARSE_FROMBIT(_field), REG_PARSE_FLDLEN(_field))) | FORMAT_FIELD_32((_val), REG_PARSE_FROMBIT(_field), REG_PARSE_FLDLEN(_field)))) \
				 	: \
				 		(((_var) = ((_var) & GENERATE_FIELD_MASK_32(REG_PARSE_FROMBIT(_field), REG_PARSE_FLDLEN(_field))) | FORMAT_FIELD_32((_val), REG_PARSE_FROMBIT(_field), REG_PARSE_FLDLEN(_field)))) \
				 ) \
		) \
	)


#define SET_2_FIELDS_VALIDATE_ARGS(_field1, _val1, _field2, _val2)	((void)((REG_PARSE_ADDR(_field1) == REG_PARSE_ADDR(_field2)) ? 0 : REPORT_ERROR(__CANNOT_USE_FIELDS_FROM_DIFFERENT_REGISTERS__))) // ((void)0) //TBD - check if not writing to R/O, check that IP was registered for this reg, etc. Also verify register format if 01, because currently format 00 is not supported.

#define SET_3_FIELDS_VALIDATE_ARGS(_field1, _val1, _field2, _val2, _field3, _val3)	((void)(((REG_PARSE_ADDR(_field1) == REG_PARSE_ADDR(_field2)) && (REG_PARSE_ADDR(_field1) == REG_PARSE_ADDR(_field3)))? 0 : REPORT_ERROR(__CANNOT_USE_FIELDS_FROM_DIFFERENT_REGISTERS__))) // ((void)0) //TBD - check if not writing to R/O, check that IP was registered for this reg, etc. Also verify register format if 01, because currently format 00 is not supported.

#define GET_FIELD_VALIDATE_ARGS(_field)	((void)0)


/* This macro parse bytes from variable, corresponding to the given field */
#define GET_FIELD_FROM_VAR(_var, _field)	\
	( \
		GET_FIELD_VALIDATE_ARGS(_field), \
		( \
		 	(REG_PARSE_SIZE(_field) == REG_SIZE_32BITS) ? \
		 		PARSE_FIELD_32((_var), REG_PARSE_FROMBIT(_field), REG_PARSE_FLDLEN(_field)) \
		 	: \
		 	(REG_PARSE_SIZE(_field) == REG_SIZE_16BITS) ? \
		 		PARSE_FIELD_16((_var), REG_PARSE_FROMBIT(_field), REG_PARSE_FLDLEN(_field)) \
		 	: \
		 		PARSE_FIELD_8((_var), REG_PARSE_FROMBIT(_field), REG_PARSE_FLDLEN(_field)) \
		) \
	)


#define GET_2_FIELDS_VALIDATE_ARGS(_field1, _val1ptr, _field2, _val2ptr, _tempvalptr)	((void)((REG_PARSE_ADDR(_field1) == REG_PARSE_ADDR(_field2)) ? 0 : REPORT_ERROR(__CANNOT_USE_FIELDS_FROM_DIFFERENT_REGISTERS__))) // ((void)0) //TBD - check if not writing to R/O, check that IP was registered for this reg, etc. Also verify register format if 01, because currently format 00 is not supported.

#define GET_3_FIELDS_VALIDATE_ARGS(_field1, _val1ptr, _field2, _val2ptr, _field3, _val3ptr, _tempvalptr)	((void)(((REG_PARSE_ADDR(_field1) == REG_PARSE_ADDR(_field2)) && (REG_PARSE_ADDR(_field1) == REG_PARSE_ADDR(_field3)))? 0 : REPORT_ERROR(__CANNOT_USE_FIELDS_FROM_DIFFERENT_REGISTERS__))) // ((void)0) //TBD - check if not writing to R/O, check that IP was registered for this reg, etc. Also verify register format if 01, because currently format 00 is not supported.

//*********************************************************************************************************//

#define _err_func_name(x,y,z) ERROR__ ## z ## __IN_LINE_ ## y ## __AT__ ## x
#define err_func_name(x,y,z) _err_func_name(x,y,z)

#ifdef ENABLE_FIELDS_ERROR_DETECTION
    #ifndef CURRENT_FILENAME_FOR_ERROR_REPORTING
    //#error "Please define CURRENT_FILENAME_FOR_ERROR_REPORTING as the current file's name (using a combination of only alphanumeric characters and underscore)"
        #define CURRENT_FILENAME_FOR_ERROR_REPORTING SEE_OBJ_FILENAME_AT_THE_RIGHT
    #endif
    #define REPORT_ERROR(_description) (err_func_name(CURRENT_FILENAME_FOR_ERROR_REPORTING, __LINE__, _description)(0))
#else
    #define REPORT_ERROR(_description) (THERE_IS_AN_ERROR_WITH_SOME_FIELD_MACROS__PLEASE_ENABLE_FIELDS_ERROR_REPORTING(0))
    int THERE_IS_AN_ERROR_WITH_SOME_FIELD_MACROS__PLEASE_ENABLE_FIELDS_ERROR_REPORTING(int);
    //IMPORTANT NOTE: if you get a linkage error specifying the function above, you should uncomment the definition of ENABLE_FIELDS_ERROR_DETECTION at the top of this file (do not change the location of that definition)
#endif


//######################################################################################################//


#endif


