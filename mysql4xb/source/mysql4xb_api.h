//------------------------------------------------------------
//  Project: libmysql cli wrapper for Xbase++                -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#pragma once
// -----------------------------------------------------------------------------------------------------------------

#include <ot4xb_api.h>

#ifdef _MYSQL4XB_API_
#define MYSQL4XB_API __declspec(dllexport)
#include <mysql4xb_xbexports.hpp>
#else
#define MYSQL4XB_API __declspec(dllimport)
#endif
#include <mysql.h>
enum class mysqlxb_global_flags_enum : DWORD
{
   tiny_to_bool,
   null_to_empty,
   max_flags
};


extern BYTE mysqlxb_global_flags[(DWORD)mysqlxb_global_flags_enum::max_flags];

// mysql_xb_functions.cpp
void __cdecl mysql_xb_set_option_dword(XppParamList pl);
void __cdecl mysql_xb_set_option_bool(XppParamList pl);
void __cdecl mysql_xb_set_option_string(XppParamList pl);
// --------
void __cdecl mysql_xb_real_connect(XppParamList pl);
void __cdecl mysql_xb_quick_query(XppParamList pl);

// ------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include <mysql4xb_resultset_rows_t.h>