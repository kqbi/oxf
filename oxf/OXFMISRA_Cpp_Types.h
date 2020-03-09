//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: MISRA_Cpp_Types
//!	File name		: $Source$
//!	File version	: $Revision$
//
//!	Date changed	: $Date$
//!	Last change by	: $Author$
//
//	Licensed Materials - Property of IBM
//	(c) Copyright IBM Corporation 2004, 2016. All Rights Reserved.
//	
//	Note to U.S. Government Users Restricted Rights:  
//	Use, duplication or disclosure restricted by GSA ADP Schedule 
//	Contract with IBM Corp.


#ifndef OXFMISRA_Cpp_Types_H
#define OXFMISRA_Cpp_Types_H

//## package Design::oxf::Services::Types::MISRA_Cpp_Types


//#[ ignore
// MISRA C++ 2008 Types for a 32 bit machine
// There is no need for these types to be in a namespace
// They are all prepended with Rhp_ to avoid any conflict with 
// types with similar nmaes that might be used by existing software.
//#]

// plain 8 bit character
//#[ type Rhp_char_t
typedef char Rhp_char_t;
//#]

// signed 8 bit integer
//#[ type Rhp_int8_t
typedef signed char Rhp_int8_t;
//#]

// signed 16 bit integer
//#[ type Rhp_int16_t
typedef signed short Rhp_int16_t;
//#]

// signed 32 bit integer
//#[ type Rhp_int32_t
typedef signed int Rhp_int32_t;
//#]

// signed 64 bit integer
//#[ type Rhp_int64_t
typedef signed long long Rhp_int64_t;
//#]

// unsigned 8 bit integer
//#[ type Rhp_uint8_t
typedef unsigned char Rhp_uint8_t;
//#]

// unsigned 16 bit integer
//#[ type Rhp_uint16_t
typedef unsigned short Rhp_uint16_t;
//#]

// unsigned 32 bit integer
//#[ type Rhp_uint32_t
typedef unsigned int Rhp_uint32_t;
//#]

// unsigned 64 bit integer
//#[ type Rhp_uint64_t
typedef unsigned long long Rhp_uint64_t;
//#]

// 32 bit floating point
//#[ type Rhp_float32_t
typedef float Rhp_float32_t;
//#]

// 64 bit floating point
//#[ type Rhp_float64_t
typedef double Rhp_float64_t;
//#]

// 128 bit floating point
//#[ type Rhp_float128_t
typedef long double Rhp_float128_t;
//#]

// plain pointer to an 8 bit character
//#[ type Rhp_char_pt
typedef char* Rhp_char_pt;
//#]

// plain pointer to an 8 bit character
//#[ type Rhp_const_char_pt
typedef const char* Rhp_const_char_pt;
//#]

#endif



