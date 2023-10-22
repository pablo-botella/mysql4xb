//////////////////////////////////////////////////////////////////////
//
//     xppdef.h
//
//  Copyright:
//     Alaska Software, (c) 1997-2009. All rights reserved.         
//
//  Contents :
//
//     C-API type definitions
//
//////////////////////////////////////////////////////////////////////
#ifndef _XPPDEF_H_
#define _XPPDEF_H_

#ifdef __OS2__
#include <os2def.h>
#else
#include <windef.h>                                                                                                             
#endif
#ifdef __cplusplus
struct MomHandleEntry;
#else
typedef void MomHandleEntry;
#endif

typedef MomHandleEntry *MomHandle;     /* handle of a memory object */
#define MOM_NULLHANDLE  ((MomHandle)0) /* null handle value */


typedef MomHandle ContainerHandle;  /* container object */
#define NULLCONTAINER ((ContainerHandle) MOM_NULLHANDLE)

typedef ULONG           Date;	

/*-----------------------------------------------------------------------------
  							  Xbase++ Function Type
-----------------------------------------------------------------------------*/

#ifdef __OS2__
#define XPPENTRY  __cdecl 
#else // __WINDOWS__
#define XPPENTRY  __cdecl
#endif

#define XPPAPIENTRY __cdecl

#define XPPRET    void
#define XPPAPIRET ULONG		/* see XPP_ERR_... in error.ch */

/*
   define formal function parameters of a XPP-function
*/
typedef void     *XppParamList;

/*
   define the XPP-function
*/
typedef XPPRET (XPPENTRY *XppFuncType)(XppParamList);

/* 
 * The XppRegisterFunction structure is used by the 
 * _conRegisterF() and _conUnregisterF() functions
 * to pass an array of function names / function addresses
 * which will be made globally visible for symblic calling
 */
typedef struct  {
      char *functionName;
      XppFuncType capiFunc;
} XppRegisterFunction;

/*
 * The XppRegisterTable holds values about the created
 * symbolic information for each C-API function.
 * You must have one static of them to pass to the
 * _conUnregisterF() when deinstalling the DLL.
 */
typedef struct {
      MomHandle funcHandle;
      void     *funcStart;
      void     *funcEnd;
} XppRegisterTable;

typedef ULONG (XPPAPIENTRY *XPPDLLFUNC)(void *);

#define XPPDLLREG_RESERVED sizeof(void*)*16

/* Xbase++ DLL registration record */
typedef struct {
      XppRegisterFunction *xppFuncs;
      ULONG		  numFunc;
      MomHandle  funcHandle;
      XPPDLLFUNC createFunc;
      XPPDLLFUNC destroyFunc;
      void      *userData;
		BYTE       reserved[XPPDLLREG_RESERVED];
} XppDllRegistration;


#endif /* _XPPDEF_H_ */

