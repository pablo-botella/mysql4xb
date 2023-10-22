//////////////////////////////////////////////////////////////////////
//
//     xpppar.h
//
//  Copyright:
//     Alaska Software, (c) 1997-2009. All rights reserved.         
//
//  Contents :
//
//     C-API parameter interface
//
//////////////////////////////////////////////////////////////////////
#ifndef _XPPPAR_H
#define _XPPPAR_H

/*-------------------------------------------------------------------------
                                INCLUDES
--------------------------------------------------------------------------*/
#include <xppdef.h>                                                                                                             
#include "types.ch"

/*-------------------------------------------------------------------------
                                 MACROS
--------------------------------------------------------------------------*/
#define XPP_NO_REF(xppType)                ((xppType)&(~XPP_REFERENCE))
#define XPP_IS_SUBTYPE(xppType,typeValue)  (XPP_NO_REF(xppType)==XPP_NO_REF(typeValue))
#define XPP_IS_BASETYPE(xppType,typeValue) ((((xppType)&XPP_BASETYPE_MASK)&typeValue)!=0)
#define XPP_IS_TYPE(xppType, typeValue)    (((typeValue)&XPP_SUBTYPE_MASK) ? \
                                              XPP_IS_SUBTYPE((xppType),(typeValue)) : \
                                              XPP_IS_BASETYPE((xppType),(typeValue)))


#define XPP_IS_UNDEF(xppType)  XPP_IS_BASETYPE(xppType, XPP_UNDEF)
#define XPP_IS_CHAR(xppType)   XPP_IS_BASETYPE(xppType, XPP_CHARACTER)
#define XPP_IS_MEMO(xppType)   XPP_IS_SUBTYPE(xppType, XPP_MEMO)
#define XPP_IS_NUM(xppType)    XPP_IS_BASETYPE(xppType, XPP_NUMERIC)
#define XPP_IS_FLOAT(xppType)  XPP_IS_SUBTYPE(xppType, XPP_DOUBLE)
#define XPP_IS_LOGIC(xppType)  XPP_IS_BASETYPE(xppType, XPP_LOGICAL)
#define XPP_IS_DATE(xppType)   XPP_IS_BASETYPE(xppType, XPP_DATE)
#define XPP_IS_ARRAY(xppType)  XPP_IS_BASETYPE(xppType, XPP_ARRAY)
#define XPP_IS_BLOCK(xppType)  XPP_IS_BASETYPE(xppType, XPP_BLOCK)
#define XPP_IS_OBJECT(xppType) XPP_IS_BASETYPE(xppType, XPP_OBJECT)

#define XPP_IS_REFPAR(xppType) ((xppType)&XPP_REFERENCE)

#define PCOUNT(paramList)   _partype(paramList, 0)
/*-------------------------------------------------------------------------
                                TYPEDEFS
--------------------------------------------------------------------------*/
/*
   since int has the same size as long and we don't support 16-bit code 
   we can define all int functions as long:
*/
#define _parni          _parnl
#define _parniarr       _parnlarr
#define _retni          _retnl
#define _retniarr       _retnlarr
#define _storni         _stornl
#define _storniarr      _stornlarr


/*-------------------------------------------------------------------------
                         PROTOTYPES of ext_param.c
--------------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {
#endif
/*
   retrieve value of a paramter
*/
ULONG XPPAPIENTRY _parc(CHAR* cBuffer, ULONG ulSize, XppParamList pList, ULONG ulIndex, ...);
ULONG XPPAPIENTRY _parclen(XppParamList pList, ULONG paramIndex, ...);
void XPPAPIENTRY _pards(char dateBuffer[8], XppParamList pList, ULONG paramIndex, ...);
BOOL XPPAPIENTRY _parl(XppParamList pList, ULONG paramIndex, ...);
double XPPAPIENTRY _parnd(XppParamList pList, ULONG paramIndex, ...);
LONG XPPAPIENTRY _parnl(XppParamList pList, ULONG paramIndex, ...);
#define _parnul(p,x) (ULONG)_parnd(p,x)

ULONG XPPAPIENTRY _partype(XppParamList pList, ULONG paramIndex);
ULONG XPPAPIENTRY _paratype(XppParamList pList, ULONG paramIndex, ...);
ULONG XPPAPIENTRY _paralen(XppParamList pList, ULONG paramIndex, ...);

/*
   set the return value of a XPP-function 
*/
BOOL XPPAPIENTRY _ret(XppParamList pList);
BOOL XPPAPIENTRY _retc(XppParamList pList, CHAR *string);
BOOL XPPAPIENTRY _retclen(XppParamList pList, CHAR *buffer, ULONG bufferLength);
BOOL XPPAPIENTRY _retds(XppParamList pList, CHAR *dateString);
BOOL XPPAPIENTRY _retl(XppParamList pList, BOOL logic);
BOOL XPPAPIENTRY _retnd(XppParamList pList, double numFloat);
BOOL XPPAPIENTRY _retnl(XppParamList pList, LONG numInt);

/*
   store a new value into a parameter
*/
BOOL XPPAPIENTRY _stor(XppParamList pList, ULONG paramIndex, ...);
BOOL XPPAPIENTRY _storc(char *string, XppParamList pList, ULONG paramIndex, ...);
BOOL XPPAPIENTRY _storclen(char *buffer, ULONG bufferLength, 
                          XppParamList pList, ULONG paramIndex, ...);
BOOL XPPAPIENTRY _stords(char dateBuffer[8], XppParamList pList, ULONG paramIndex, ...);
BOOL XPPAPIENTRY _storl(BOOL logic, XppParamList pList, ULONG paramIndex, ...);
BOOL XPPAPIENTRY _stornd(double numFloat, XppParamList pList, ULONG paramIndex, ...);
BOOL XPPAPIENTRY _stornl(LONG numInt, XppParamList pList, ULONG paramIndex, ...);

#ifdef __cplusplus
}
#endif
#endif /* _XPPPAR_H */

