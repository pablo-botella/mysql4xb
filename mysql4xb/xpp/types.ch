//////////////////////////////////////////////////////////////////////
//
//  TYPES.CH
//
//  Copyright:
//      Alaska Software, (c) 1998-2009. All rights reserved.         
//  
//  Contents:
//      #define constants for data types of Xbase++ for C-API and
//      the function FieldInfo()
//   
//////////////////////////////////////////////////////////////////////

#ifndef  _TYPES_CH
#define  _TYPES_CH

// type could not be determined    
#define XPP_ILLEGAL       (0x00000000)

// parameter was passed by reference     
#define XPP_REFERENCE     (0x10000000)  

// reserved for sub-type resolution
#define XPP_SUBTYPE_MASK  (0xEFF00000)
#define XPP_SUBTYPE1      (0x20000000)
#define XPP_SUBTYPE2      (0x40000000)
#define XPP_SUBTYPE3      (0x80000000)
#define XPP_SUBTYPE4      (0x01000000)
#define XPP_SUBTYPE5      (0x02000000)
#define XPP_SUBTYPE6      (0x04000000)
#define XPP_SUBTYPE7      (0x08000000)
#define XPP_SUBTYPE8      (0x00100000)
#define XPP_SUBTYPE9      (0x00200000)
#define XPP_SUBTYPE10     (0x00400000)
#define XPP_SUBTYPE11     (0x00800000)


// to be combined with XPP_CHARACTER,XPP_BINARY
// and XPP_WIDECHAR. See XPP_MEMO 
#define XPP_ST_VARSIZE    (XPP_SUBTYPE1) 
#define XPP_ST_LARGE      (XPP_SUBTYPE2)


// system level sub-types are used by 
// XPP_INT and XPP_DOUBLE to specify valid range
#define XPP_ST_INT32      (XPP_SUBTYPE1) 
#define XPP_ST_INT64      (XPP_SUBTYPE2)
#define XPP_ST_FLOAT32    (XPP_SUBTYPE3)
#define XPP_ST_FLOAT64    (XPP_SUBTYPE4) 
#define XPP_ST_FLOAT80    (XPP_SUBTYPE5) 
#define XPP_ST_FIXED      (XPP_SUBTYPE6)
#define XPP_ST_FIXED4     (XPP_SUBTYPE7)


/* Defines for user-level datatypes support by
 * the language itself. Version 1.x
 */
#define XPP_BASETYPE_MASK (0x000FFFFF)
#define XPP_UNDEF         (0x00000001)    
#define XPP_CHARACTER     (0x00000002)    
#define XPP_NUMERIC       (0x00000004)    
#define XPP_LOGICAL       (0x00000008)    
#define XPP_DATE          (0x00000010)    
#define XPP_ARRAY         (0x00000020)    
#define XPP_BLOCK         (0x00000040)    
#define XPP_OBJECT        (0x00000080)    


/* Additional datatypes used at Data-Definition-
 * Language (DDL) level such as DbCreate() / DbStruct()
 */
#define XPP_MEMO          (XPP_CHARACTER+XPP_ST_LARGE)
#define XPP_VARCHAR       (XPP_CHARACTER+XPP_ST_VARSIZE)
#define XPP_BINARY        (0x00000100)
#define XPP_BLOB          (XPP_BINARY+XPP_ST_LARGE)
#define XPP_VARBINARY     (XPP_BINARY+XPP_ST_VARSIZE)
#define XPP_WIDECHAR      (0x00000200)
#define XPP_WIDEMEMO      (XPP_WIDECHAR+XPP_ST_LARGE)
#define XPP_VARWIDECHAR   (XPP_WIDECHAR+XPP_ST_VARSIZE)

#define XPP_INT           (XPP_NUMERIC+XPP_ST_INT32)
#define XPP_FLOAT         (XPP_NUMERIC+XPP_ST_FLOAT32)
#define XPP_DOUBLE        (XPP_NUMERIC+XPP_ST_FLOAT64)
#define XPP_DECIMAL       (XPP_NUMERIC+XPP_ST_FIXED)
#define XPP_CURRENCY      (XPP_NUMERIC+XPP_ST_FIXED4)

#define XPP_SEQUENCE      (0x00000400)
#define XPP_POINTER       (0x00000800)

#define XPP_TIME          (0x00001000) 
#define XPP_TIMESTAMP     (0x00002000)
#define XPP_TIMESPAN      (0x00004000)

#define XPP_GUID          (0x00008000)


// Character type identifier 
#define XPP_TYPE_UNDEF       "U"

#define XPP_TYPE_CHARACTER   "C"
#define XPP_TYPE_MEMO        "M"
#define XPP_TYPE_VARCHAR     "R"

#define XPP_TYPE_BINARY      "X"
#define XPP_TYPE_BLOB        "V"
#define XPP_TYPE_VARBINARY   "Z"

#define XPP_TYPE_WIDECHAR    "W"
#define XPP_TYPE_WIDEMEMO    "Q"
#define XPP_TYPE_VARWIDECHAR "J"

#define XPP_TYPE_LOGICAL     "L"

#define XPP_TYPE_INT         "I"
#define XPP_TYPE_FLOAT       "F"
#define XPP_TYPE_DOUBLE      "F"
#define XPP_TYPE_NUMERIC     "N"
#define XPP_TYPE_DECIMAL     "N"
#define XPP_TYPE_CURRENCY    "Y"

#define XPP_TYPE_SEQUENCE    "S"
#define XPP_TYPE_POINTER     "P"

#define XPP_TYPE_DATE        "D"
#define XPP_TYPE_TIME        "H"
#define XPP_TYPE_TIMESTAMP   "T"
#define XPP_TYPE_TIMESPAN    "E"

#define XPP_TYPE_ARRAY       "A"
#define XPP_TYPE_BLOCK       "B"
#define XPP_TYPE_OBJECT      "O"
#define XPP_TYPE_GUID        "G"

#ifdef __XBASE2__
#ifndef _XB2_CH
#include "xb2.ch"
#endif
#endif

#endif // _TYPES_CH
