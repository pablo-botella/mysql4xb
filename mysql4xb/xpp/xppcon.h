//////////////////////////////////////////////////////////////////////
//
//     xppcon.h
//
//  Copyright:
//     Alaska Software, (c) 1997-2009. All rights reserved.         
//
//  Contents :
//
//     C-API container interface
//
//////////////////////////////////////////////////////////////////////
#ifndef _XPP_CON_H
#define _XPP_CON_H

/*-------------------------------------------------------------------------
                                INCLUDES
--------------------------------------------------------------------------*/
#include <xpppar.h>                                                                                                             

/*-------------------------------------------------------------------------
                                INCLUDES
--------------------------------------------------------------------------*/
#define _conRUnlockC( ch )    _conUnlockC( ch )
#define _conWUnlockC( ch )    _conUnlockC( ch )

/*-------------------------------------------------------------------------
                               PROTOTYPES
--------------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {
#endif
/*
   Container API
*/
/* create new array container (... is LONG list) */
ContainerHandle XPPAPIENTRY _conNewArray(ULONG numDimensions, ...);
ContainerHandle XPPAPIENTRY _conNewArrayA(ContainerHandle chT,int *dimensions);

/* assign new value to array element (... is null-terminated LONG list) */
XPPAPIRET XPPAPIENTRY _conArrayPut(ContainerHandle hArray, ContainerHandle hValue, ...);

XPPAPIRET XPPAPIENTRY _conArrayPutA(ContainerHandle chArray, ContainerHandle chValue, int *index);

/* copy element of array to container (... is null-terminated LONG list) */
ContainerHandle XPPAPIENTRY _conArrayGet(ContainerHandle hArray, ContainerHandle hResult, ...);

ContainerHandle XPPAPIENTRY _conArrayGetA(ContainerHandle chArray, ContainerHandle chValue, int *index);

/* Delete array element and shrink array's size */
XPPAPIRET XPPAPIENTRY _conArrayDelA( ContainerHandle hArray, ULONG ulElem );

ContainerHandle XPPAPIENTRY _conGetMemvar(CHAR *name, ContainerHandle chDest);

XPPAPIRET XPPAPIENTRY _conSetMemvar(CHAR *name, ContainerHandle chValue);

ContainerHandle XPPAPIENTRY _conGetCurrentField(CHAR *field, ContainerHandle chDest);

ContainerHandle XPPAPIENTRY _conGetFieldCC(CHAR *warea, CHAR *field, ContainerHandle chDest);

ContainerHandle XPPAPIENTRY _conGetFieldNC(int warea, CHAR *field, ContainerHandle chDest);

XPPAPIRET XPPAPIENTRY _conSetCurrentField(CHAR *field, ContainerHandle chValue);

XPPAPIRET XPPAPIENTRY _conSetFieldCC(CHAR *warea, CHAR *field, ContainerHandle chValue);

XPPAPIRET XPPAPIENTRY _conSetFieldNC(int warea, CHAR *field, ContainerHandle chValue);

XPPAPIRET XPPAPIENTRY _conSetIWArea(int newWArea, int *oldWArea);

XPPAPIRET XPPAPIENTRY _conSetCWArea(char *newWArea, int *oldWArea);

XPPAPIRET XPPAPIENTRY _conRestWArea(int oldWArea);

/* copy string-container to buffer  */
XPPAPIRET XPPAPIENTRY _conGetCL(ContainerHandle hString, 
                                ULONG *ulCopy, CHAR *pBuffer, ULONG ulSize);

/* read-lock of string-container */
XPPAPIRET XPPAPIENTRY _conRLockC(ContainerHandle hString, CHAR **ppString, ULONG *ulSize);

/* write-lock of string-container */
XPPAPIRET XPPAPIENTRY _conWLockC(ContainerHandle hString, CHAR **ppString, ULONG *ulSize);

/* end of read-/write-lock */
XPPAPIRET XPPAPIENTRY _conUnlockC(ContainerHandle hString);

  /* return julian date of date-container */
XPPAPIRET XPPAPIENTRY _conGetDJ(ContainerHandle chDate, Date *pJulian);

/* copy date-container to string-buffer (Format: YYYYMMDD) */
XPPAPIRET XPPAPIENTRY _conGetDS(ContainerHandle hString, char buffer[8]);
   
/* return value of logic-container */
XPPAPIRET XPPAPIENTRY _conGetL(ContainerHandle hLogic, BOOL *lValue);

/* return value of numeric-contaienr as long */
XPPAPIRET XPPAPIENTRY _conGetNL(ContainerHandle hNumeric, LONG *nlValue);

/* return value of numeric-container as double */
XPPAPIRET XPPAPIENTRY _conGetND(ContainerHandle hNumeric, double *ndValue);

/* return double-value and format of a numeric-container */
XPPAPIRET XPPAPIENTRY _conGetNDF(ContainerHandle hNumeric, double *ndValue,
                                 LONG *intDigits, LONG *decDigits);

/* create new container (copy hSource if not NULLCONTAINER) */
ContainerHandle XPPAPIENTRY _conNew(ContainerHandle hSource);

/* return a parameter container (NOT A COPY!) */
ContainerHandle XPPAPIENTRY _conParam(XppParamList pList, ULONG paramIndex, BOOL *bReference);


/* assign container to another container (if hDest is NULLCONTAINER: create!) */
ContainerHandle XPPAPIENTRY _conPut(ContainerHandle hDest, ContainerHandle hSrc);

/* assign null-terminated string to a container (if hDest is NULLCONTAINER: create!) */
ContainerHandle XPPAPIENTRY _conPutC(ContainerHandle hDest, char *string);

/* assign any data-string to a container (if hDest is NULLCONTAINER: create!) */
ContainerHandle XPPAPIENTRY _conPutCL(ContainerHandle hDest, char *buffer, ULONG bufferSize);

/* assign a memo-string to a container (if hDest is NULLCONTAINER: create!) */
ContainerHandle XPPAPIENTRY _conPutML(ContainerHandle hDest, char *buffer, ULONG bufferSize);

/* assign julian date to container object, if chDest is NULL - creste */
ContainerHandle XPPAPIENTRY _conPutDJ(ContainerHandle chDest,Date jDate);

/* assign date-string to a container (if hDest is NULLCONTAINER: create!) */
ContainerHandle XPPAPIENTRY _conPutDS(ContainerHandle hDest, char buffer[9]);

/* assign logic value to a container (if hDest is NULLCONTAINER: create!) */
ContainerHandle XPPAPIENTRY _conPutL(ContainerHandle hDest, BOOL logic);

/* assign double-value to a container (if hDest is NULLCONTAINER: create!) */
ContainerHandle XPPAPIENTRY _conPutND(ContainerHandle hDest, double numFloat);

/* assign double-value with pedefined format to a container */
/* (if hDest is NULLCONTAINER: create!) */
ContainerHandle XPPAPIENTRY _conPutNDF(ContainerHandle hDest, double numFloat, 
                                       LONG intDigits, LONG decDigits);

/* assign long-value to a container (if hDest is NULLCONTAINER: create!) */
ContainerHandle XPPAPIENTRY _conPutNL(ContainerHandle hDest, LONG numLong);

/* return true of container of any type is empty */
XPPAPIRET XPPAPIENTRY _conIsEmpty(ContainerHandle hDest, BOOL *lEmpty);

/* assign defalt values if there is no data */
ContainerHandle XPPAPIENTRY _conPutEmptyData(ContainerHandle hDest, ULONG xppType,
															LONG length, LONG decDegits);


/* release a container */
XPPAPIRET XPPAPIENTRY _conRelease(ContainerHandle hOld);

/* set return-container value */
XPPAPIRET XPPAPIENTRY _conReturn(XppParamList pList, ContainerHandle hValue);

/* get length of array/string (... is null-terminated LONG list) */
XPPAPIRET XPPAPIENTRY _conSizeA(ContainerHandle, ULONG *size, ...);
XPPAPIRET XPPAPIENTRY _conSizeC(ContainerHandle, ULONG *size);

/* change size of string-container */
XPPAPIRET XPPAPIENTRY _conResizeC(ContainerHandle hString, ULONG newSize);
/* change size of array-container */
XPPAPIRET XPPAPIENTRY _conResizeA(ContainerHandle hArray, ULONG newSize);

/* get type of container or array element (... is null-terminated LONG list) */
XPPAPIRET XPPAPIENTRY _conTypeA(ContainerHandle, ULONG *type, ...);
XPPAPIRET XPPAPIENTRY _conType(ContainerHandle, ULONG *type);

/* get error-code when last Container-API call failed */
XPPAPIRET XPPAPIENTRY _conLastError();

XPPAPIRET XPPAPIENTRY _conSetMember(ContainerHandle chObject, 
												char *mName, ContainerHandle chValue);

XPPAPIRET XPPAPIENTRY _conGetMember(ContainerHandle chObject, 
												char *mName, ContainerHandle chDest);

XPPAPIRET XPPAPIENTRY _conGetRefMember(ContainerHandle chObject, 
													char *mName, ContainerHandle chDest);

/*
   Eval-API
*/
/* eval codeblock with list of (reference) parameters */
XPPAPIRET XPPAPIENTRY _conEvalB(ContainerHandle hResult, ContainerHandle hCodeblock,
                                ULONG numParams, ...);

/* eval codeblock with list of (reference) parameters */
XPPAPIRET XPPAPIENTRY _conEvalBa(ContainerHandle hResult, ContainerHandle hCodeblock,
											ULONG numParams, ContainerHandle *chArgs );

/* execute an string-container as macro-expression */
XPPAPIRET XPPAPIENTRY _conEvalMacro(ContainerHandle chResult, 
												ContainerHandle hExprString);

/* execute an expression-string */
XPPAPIRET XPPAPIENTRY _conEvalMacroStr(ContainerHandle chResult, char *exprString);

/* execute an expression-string 
 * with break handling
 */
XPPAPIRET XPPAPIENTRY _conEvalString(ContainerHandle chResult, char *exprString,
												 ContainerHandle *chBreak);

/* call Xbase++ function with list of (reference) parameters */
XPPAPIRET XPPAPIENTRY _conCall(ContainerHandle chResult, char *funcName, 
										 ULONG numParams, ...);

/* call Xbase++ function with array of parameters */
XPPAPIRET XPPAPIENTRY _conCallPa(ContainerHandle chResult, char *funcName, 
											ULONG numParams, ContainerHandle *chArray);

/* call Xbase++ method with array of parameters */
XPPAPIRET XPPAPIENTRY _conCallMethodPa(ContainerHandle chResult, char *methName, 
													ULONG numParams, ContainerHandle *chParams);


/* compare two containers */
XPPAPIRET XPPAPIENTRY _conCompare(LONG *cmp, ContainerHandle ch1, ContainerHandle ch2);

/* compare two strings */
LONG XPPAPIENTRY _conCompareStr(char *str1, ULONG len1, char *str2, ULONG len2);

LONG XPPAPIENTRY _conCompareLazyStr(char *str1, ULONG len1, char *str2, ULONG len2);
XPPAPIRET XPPAPIENTRY _conCompareLazy(LONG *cmp, ContainerHandle ch1, ContainerHandle ch2);

/* register function symbols */
XPPAPIRET XPPAPIENTRY _conRegisterF(XppRegisterFunction *funcs, int numOfFuncs,
                                    XppRegisterTable *tbl);

/* unregister function symbols */
XPPAPIRET XPPAPIENTRY _conUnRegisterF(XppRegisterTable *tbl);

/* register/deregister DLL for dynamic load/unload 
 * XppDllRegistration is defined in xppdef.h
 */
BOOL XPPAPIENTRY _conRegisterDll(ULONG hHandle, XppDllRegistration *pReg);
BOOL XPPAPIENTRY _conUnRegisterDll(ULONG hHandle);


/*
   Memory API 
*/
MomHandle XPPAPIENTRY _momAlloc(ULONG size);
XPPAPIRET XPPAPIENTRY _momFree(MomHandle hMemory);

XPPAPIRET XPPAPIENTRY _momSize(MomHandle hMemory, ULONG *ulSize);
XPPAPIRET XPPAPIENTRY _momResize(MomHandle hMemory, ULONG newSize);

BYTE *XPPAPIENTRY _momLock(MomHandle hMemory);
XPPAPIRET XPPAPIENTRY _momUnlock(MomHandle hMemory);

/* for debugging: check internal structures of memory manager */
XPPAPIRET XPPAPIENTRY _momDebug();

/* interface for ANSI/OEM conversion */
ULONG XPPAPIENTRY _conGetCharSet();
BOOL XPPAPIENTRY _conCharSetIsOem();
BOOL XPPAPIENTRY _conCharSetIsAnsi();
XPPAPIRET XPPAPIENTRY _conToAnsiCp(CHAR *strAnsi, const CHAR *strOem, ULONG oemLength);
XPPAPIRET XPPAPIENTRY _conToOemCp(CHAR *strOem, const CHAR *strAnsi, ULONG ansiLength);

#ifdef __cplusplus
}
#endif
#endif /* _XPP_CON_H */
