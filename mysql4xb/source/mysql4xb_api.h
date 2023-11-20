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
   auto_truncate_values,

   max_flags
};


extern BYTE mysqlxb_global_flags[(DWORD)mysqlxb_global_flags_enum::max_flags];

// mysql_xb_functions.cpp
void __cdecl mysql_xb_set_option_dword(XppParamList pl);
void __cdecl mysql_xb_set_option_bool(XppParamList pl);
void __cdecl mysql_xb_set_option_string(XppParamList pl);
// --------
void __cdecl mysql_xb_real_connect(XppParamList pl);

void __cdecl mysql_xb_init(XppParamList pl);
void __cdecl mysql_xb_close(XppParamList pl);
void __cdecl mysql_xb_last_error(XppParamList pl);
void __cdecl mysql_xb_last_error_string(XppParamList pl);
void __cdecl mysql_xb_info(XppParamList pl);
void __cdecl mysql_xb_commit(XppParamList pl);
void __cdecl mysql_xb_ping(XppParamList pl);
void __cdecl mysql_xb_rollback(XppParamList pl);

void __cdecl mysql_xb_affected_rows(XppParamList pl);
void __cdecl mysql_xb_last_inserted_id(XppParamList pl);
void __cdecl mysql_xb_field_count(XppParamList pl);

// my_bool         mysql_autocommit(MYSQL* mysql,   my_bool mode)
// const char* mysql_character_set_name(MYSQL* mysql)
// const char* mysql_get_server_info(MYSQL* mysql)
// unsigned long mysql_real_escape_string_quote(MYSQL* mysql,char* to,const char* from,unsigned long length, char quote)
// const char* mysql_get_client_info(void)
// unsigned long mysql_get_client_version(void)
// const char* mysql_get_host_info(MYSQL* mysql)
// unsigned int mysql_get_proto_info(MYSQL* mysql)
// const char* mysql_get_server_info(MYSQL* mysql) 
// unsigned long mysql_get_server_version(MYSQL* mysql)
// const char* mysql_get_ssl_cipher(MYSQL* mysql)
// unsigned long mysql_hex_string(char* to,    const char* from,    unsigned long length)









void __cdecl mysql_xb_quick_query(XppParamList pl);

// ------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include <mysql4xb_resultset_rows_t.h>