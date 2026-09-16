/*{{topic_: mysql4xb-overview
   | _slug_: mysql4xb-overview
   | category: mysql/reference
   | desc: mysql4xb is a wrapper over `libmysql.dll`, the client library of MySQL, for Xbase++ programs, built on
     [ot4xb](https://www.xbwin.com/ot4xb/doc/). It is one DLL, `mysql4xb.dll`, that registers four Xbase++ classes
     when it loads and needs nothing else from the program: no `.ch`, no `.lib` beyond the import library, the
     connection, the query and the rows are objects.
   |: ## The four classes
     - {{ilink: <class mysql4xb> mysql4xb}} - the connection: options, `connect()`, `query()`, transactions, errors.
     - {{ilink: <class mysql4xb_resultset_t> mysql4xb_resultset_t}} - what a query returns: a result set with the API of a workarea (`DbGoTop()`, `DbSkip()`, `eof()`,
       `FieldGet()`, `DbAppend()`, `DbDelete()`) and the columns as virtual instance variables (`rs:name`).
     - {{ilink: <class mysql4xb_result_rows_t> mysql4xb_result_rows_t}} - the rows behind the result set: the values, the column descriptors, the position and, per row,
       the change flags and the new/deleted marks a save needs.
     - {{ilink: <class mysql4xb_result_field_t> mysql4xb_result_field_t}} - the descriptor of a column: names, table, type, flags, and the SQL escaping of a value for it.

     A query is one call: `my:query( cSql )` stores the whole result in memory, already converted to Xbase++ values
     ({{ilink: <topic mysql4xb-type-mapping> type mapping}}), and returns the object; the rows are walked as a table. Writing goes back the other way: the
     application composes the `INSERT`, `UPDATE` and `DELETE` statements from the rows that changed - `changed()`,
     `IsNewRow()`, `deleted()` and `escape_value()` give everything needed - and runs them with `query()`. The examples
     show a complete version of that.
   |: ## Global flags
     Three flags of the DLL, read and written with the class methods `mysql4xb_global_flags_*()` of {{ilink: <class mysql4xb> mysql4xb}}, apply to
     every connection of the process and start on: `tiny_to_bool` (`TINYINT` as logical), `null_to_empty` (`NULL` as the
     blank value of the column instead of NIL) and `auto_truncate_values` (character values cut to the column width when
     escaped).
   |: ## Threads
     libmysql is initialised once per process and per thread from `DllMain`, so any thread can use the library; a
     connection object belongs to the thread that created it. The {{ilink: <example mysql-app> mysql-app}} example keeps one connection per thread
     in thread-local storage.
   |: ## Extending the classes
     The classes are ordinary Xbase++ classes as far as `CLASS x FROM mysql4xb` is concerned. Two things to know: the
     derived class needs an `initclass` class method (an empty one will do), and the result class of a connection is
     pluggable - `m_resultset_class_object` - so a derived result set gets used by every `query()` without touching the
     calls. {{ilink: <example mysql-class> mysql-class}} and {{ilink: <example mysql-recordset> mysql-recordset}} do exactly that: a connection that reconnects and throws, a result set that
     filters, saves and dumps to expandos.
   |: ## Building the DLL
     Visual Studio, the solution `mysql4xb.sln`; `Directory.Build.props` takes the two dependencies, the MySQL client
     (`MYSQL_CLI_DIR`, headers and `libmysql.lib`) and ot4xb (`OT4XB_DIR`), from environment variables, `msbuild`
     properties or a git-ignored `local.props`. The Xbase++ exports are declared in `mysql4xb.xbmac` and generated into
     the `.def` and `.hpp` files by ot4xb-tool before the build (`mysql4xb.ot4xb-tool`), which also produces the
     `.lib` for Xbase++ and the release zips afterwards. `mysql4xb_version.h` carries the version the `version` class
     property reports.
   | _kw_: mysql4xb, overview, libmysql, MySQL, Xbase++, Topic
   }}*/
//------------------------------------------------------------
//  Project: libmysql cli wrapper for Xbase++                -
//  Repository : http://www.xbwin.com                        -
//  Author: Pablo Botella Navarro ( http://www.xbwin.com )   -
//------------------------------------------------------------
#pragma once
// -----------------------------------------------------------------------------------------------------------------

#pragma warning( disable:  5045 4711)
#pragma warning( push)
#pragma warning( disable:  4265 4365 4668 4820 5039  )
#include <ot4xb_api.h>

#ifdef _MYSQL4XB_API_
#define MYSQL4XB_API __declspec(dllexport)
#include <mysql4xb_xbexports.hpp>
#else
#define MYSQL4XB_API __declspec(dllimport)
#endif

#include <mysql.h>
#pragma warning( pop)

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