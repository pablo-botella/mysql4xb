#include <mysql4xb_api.h>
#include <mysql4xb_version.h>
// -----------------------------------------------------------------------------------------------------------------
#pragma comment( lib , "kernel32")
#pragma comment( lib , "user32")
#pragma comment( lib , "gdi32")
#pragma comment( lib , "shell32")
#pragma comment( lib , "Rpcrt4")
#pragma comment( lib , "xpprt1")
#pragma comment( lib , "Ws2_32")
#pragma comment( lib , "Oleaut32")
#pragma comment( lib , "ole32")
#pragma comment( lib , "olepro32")
#pragma comment( lib , "shlwapi")
#pragma comment( lib , "comsuppw")
#pragma comment( lib , "comctl32")
#pragma comment( lib , "ot4xb_Cpp")
//----------------------------------------------------------------------------------------------------------------------
BYTE mysqlxb_global_flags[(DWORD)mysqlxb_global_flags_enum::max_flags] = { 0 };
char mysqlxb_plugin_dir[MAX_PATH] = { 0 };
BEGIN_EXTERN_C
//----------------------------------------------------------------------------------------------------------------------
static HINSTANCE hMySql4XbInstance = 0;
static HANDLE    hCurrentProcess = 0;
//----------------------------------------------------------------------------------------------------------------------
static HMODULE   hShell32 = 0;
//----------------------------------------------------------------------------------------------------------------------
BEGIN_REGISTER_XBASE_TABLE()
#include <MySql4Xb_xbfunclist.hpp>
END_REGISTER_XBASE_TABLE()
//----------------------------------------------------------------------------------------------------------------------
BOOL WINAPI DllMain(HINSTANCE hDll, DWORD dwReason, LPVOID )
{
   
   switch (dwReason)
   {
      case DLL_PROCESS_ATTACH:
      {
         hMySql4XbInstance = hDll;
         
         if (!_conRegisterDll((ULONG)hDll, &__dllreg__)) return 0;
         break;
      }
      case DLL_THREAD_ATTACH:
      {
         mysql_thread_init();
         break;
      }
      case DLL_THREAD_DETACH:
      {
         mysql_thread_end();
         break;
      }
      case DLL_PROCESS_DETACH:
      {
         _conUnRegisterDll((ULONG)hDll);
         if (hCurrentProcess) { CloseHandle(hCurrentProcess); hCurrentProcess = 0; }
         break;
      }

   }
   return TRUE;
}
//----------------------------------------------------------------------------------------------------------------------
XBASE_INIT_PROC()
{
   mysql_library_init(0, 0, 0);
   mysql_thread_init();
   // the client plugins (caching_sha2_password.dll, ...) are looked for in the application folder by default
   if (GetModuleFileNameA(NULL, mysqlxb_plugin_dir, MAX_PATH))
   {
      char* p = strrchr(mysqlxb_plugin_dir, '\\');
      if (p) *p = 0;
   }
   mysqlxb_global_flags[(DWORD)mysqlxb_global_flags_enum::tiny_to_bool] = 1;
   mysqlxb_global_flags[(DWORD)mysqlxb_global_flags_enum::null_to_empty] = 1;
   mysqlxb_global_flags[(DWORD)mysqlxb_global_flags_enum::auto_truncate_values] = 1;

   return 1;
}
// -----------------------------------------------------------------------------------------------------------------

// -----------------------------------------------------------------------------------------------------------------



//----------------------------------------------------------------------------------------------------------------------
XBASE_EXIT_PROC()
{

   return 1;
}
// -----------------------------------------------------------------------------------------------------------------
END_EXTERN_C


// -----------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: mysql4xb
   | _slug_: mysql4xb
   | category: mysql/connection
   | desc: The connection object of mysql4xb: a thin Xbase++ class over the `MYSQL` handle of libmysql, created with
     `mysql4xb():new()`. It keeps the class objects the queries use to build their results, the connection flags, the
     result of the last `connect()` and a property bag. `connect()` opens the session, `query()` runs one statement
     or several and returns the result as a {{ilink: <class mysql4xb_resultset_t> mysql4xb_resultset_t}} - or the number of affected rows, or an array of
     both when the multi-result flag is on - the `set_option_*()` methods map `mysql_options()` one option each, and
     the class-level `mysql4xb_global_flags_*()` methods switch the three conversion flags that apply to every
     connection of the process.
   | note: The class is built from C++ with `TXbClass` when the DLL loads; every method is a code block that calls into
     the C side with `XbFpCall()`. Deriving from it works as with any Xbase++ class - the examples do it - with one
     rule: the derived class needs an `initclass` class method, even an empty one.
   | note: The client library is initialised once per process and once per thread (`mysql_thread_init()` from `DllMain`). Each
     thread creates its own `mysql4xb` object; a connection is never shared between threads.
   | see-also: {{ilink: <class mysql4xb_resultset_t> mysql4xb_resultset_t}} - what `query()` returns, and the recordset API over it.
   | see-also: {{ilink: <topic mysql4xb-overview> overview}} - the four classes and how they fit together.
   | example: ```
     local my := mysql4xb():new()
     local rs
     my:set_option_connect_timeout( 5 )
     if my:connect( "127.0.0.1", "user", "secret", "test", 3306, NIL, 0 )
        rs := my:query( "SELECT id, name FROM customers ORDER BY name;" )
        while !rs:eof()
           ? rs:id, rs:name      // the columns are virtual instance variables
           rs:DbSkip()
        end
        my:close()
     else
        ? my:last_error(), my:last_error_string()
     end
     ```
   | _kw_: mysql4xb, mysql, connection, libmysql, Class
   }}*/
XPPRET XPPENTRY MYSQL4XB(XppParamList pl)
{

   ContainerHandle conco = _conClsObj("MYSQL4XB");
   if (conco == NULLCONTAINER)
   {
      TXbClass* pc = new TXbClass; pc->ClassName("MYSQL4XB");
      /*{{|:**BEGIN CLASS  mysql4xb** }}*/
      pc->EXPORTED();
      /*{{|ivar_: - VAR m_mysql
         | desc_: The `MYSQL*` of libmysql as a number: 0 until `new()`, back to 0 after `close()`. The C side reads it from here.
         }}*/
      pc->Var("m_mysql");
      /*{{|ivar_: - VAR m_mysql4xb_flags
         | desc_: The client flags given to `new()`; `connect()` ORs them with its own `flags` parameter.
         }}*/
      pc->Var("m_mysql4xb_flags");
      /*{{|ivar_: - VAR m_resultset_class_object
         | desc_: The class object `query()` instantiates for each result set: {{ilink: <class mysql4xb_resultset_t> mysql4xb_resultset_t}} by default.
           A derived class replaces it to get its own result objects (the examples do).
         }}*/
      pc->Var("m_resultset_class_object");
      /*{{|ivar_: - VAR m_result_field_class_object
         | desc_: The class object of the field descriptors: {{ilink: <class mysql4xb_result_field_t> mysql4xb_result_field_t}}.
         }}*/
      pc->Var("m_result_field_class_object");
      /*{{|ivar_: - VAR m_result_rows_class_object
         | desc_: The class object of the row store: {{ilink: <class mysql4xb_result_rows_t> mysql4xb_result_rows_t}}.
         }}*/
      pc->Var("m_result_rows_class_object");
      /*{{|ivar_: - VAR m_last_connect_result
         | desc_: The logical returned by the last `connect()`; NIL before the first one.
         }}*/
      pc->Var("m_last_connect_result");
      /*{{|ivar_: - VAR m_props
         | desc_: An [_ot4xb_expando_](https://www.xbwin.com/ot4xb/doc/search?k=_ot4xb_expando_) for whatever the application wants to hang on the connection; `get_prop()`,
           `is_prop()` and `set_prop()` go through it.
         }}*/
      pc->Var("m_props");

      // --------------------
      /*{{|method_: - `METHOD get_prop( cKey )`
         | return: xValue or NIL
         | desc_: Reads a property of `m_props`; `is_prop( cKey )` tells whether it exists and `set_prop( cKey, xValue )` writes it.
           The three are the same calls of [_ot4xb_expando_](https://www.xbwin.com/ot4xb/doc/search?k=_ot4xb_expando_).
         }}*/
      pc->MethodCB("get_prop", "{|s,k| s:m_props:get_prop( k) }");
      pc->MethodCB("is_prop", "{|s,k| s:m_props:is_prop( k) }");
      pc->MethodCB("set_prop", "{|s,k,v| s:m_props:set_prop( k,v) }");

      // -------------------
      /*{{|class-property_: - `CLASS PROPERTY version`
         | return: cVersion
         | desc_: The version of the DLL as `"maj.min.build.rev"` with three digits per part, so versions compare as strings:
           `mysql4xb():version >= "001.000.021.000"`.
         }}*/
      pc->ClassProperty_cbbs("version", "{|| \"%s\" }", MYSQL4XB_VERSION_STRING);
      // -------------------
      /*{{|method_: - `METHOD new( [nFlags] )`
         | return: Self
         | desc_: Creates the three class objects, the property bag and the `MYSQL` handle (`mysql_init()`); a handle from a
           previous `new()` on the same object is closed first. `nFlags` are the client flags stored in `m_mysql4xb_flags`
           (default 1, `CLIENT_LONG_PASSWORD`); see the `flag_CLIENT_*` class properties.
         }}*/
      pc->Method_cbbs("init", "{|s,flags| "
         "  s:m_resultset_class_object := MYSQL4XB_RESULTSET_T() "
         ", s:m_result_field_class_object := MYSQL4XB_RESULT_FIELD_T()  "
         ", s:m_result_rows_class_object  := MYSQL4XB_RESULT_ROWS_T()"
         ", s:m_last_connect_result := NIL  "
         ", s:m_props := _ot4xb_expando_():new()  "
         ", XbFpCall(%i,s,flags) }", (DWORD) mysql_xb_init );

      /*{{|method_: - `METHOD close()`
         | return: NIL
         | desc_: Closes the connection (`mysql_close()`) and sets `m_mysql` to 0. The object can be reused with `new()`.
         }}*/
      pc->Method_cbbs("close", "{|s| XbFpCall(%i,s) }", (DWORD) mysql_xb_close);
      /*{{|method_: - `METHOD last_error()`
         | return: nErrno
         | desc_: The error code of the last libmysql call (`mysql_errno()`): 0 when there was none, -1 without a handle.
           The `CR_*` client errors (2006 `CR_SERVER_GONE_ERROR`, 2013 `CR_SERVER_LOST`) are the ones worth a reconnect.
         }}*/
      pc->Method_cbbs("last_error", "{|s|   XbFpCall(%i,s)  }", (DWORD) mysql_xb_last_error);
      /*{{|method_: - `METHOD last_error_string()`
         | return: cMessage
         | desc_: The message of the last error (`mysql_error()`), empty when there was none.
         }}*/
      pc->Method_cbbs("last_error_string", "{|s| XbFpCall(%i,s) }", (DWORD) mysql_xb_last_error_string);
      /*{{|method_: - `METHOD info()`
         | return: cInfo
         | desc_: The information string of the last statement (`mysql_info()`): rows matched, changed, warnings, for the
           statements that produce one.
         }}*/
      pc->Method_cbbs("info", "{|s| XbFpCall(%i,s) }", (DWORD) mysql_xb_info);
      /*{{|method_: - `METHOD commit()`
         | return: lOk
         | desc_: Commits the current transaction (`mysql_commit()`).
         }}*/
      pc->Method_cbbs("commit", "{|s| XbFpCall(%i,s) }", (DWORD) mysql_xb_commit);
      /*{{|method_: - `METHOD ping()`
         | return: nResult
         | desc_: Checks the connection (`mysql_ping()`): 0 when alive, an error code otherwise, -1 without a handle. With
           `set_option_reconnect( .T. )` the ping itself reconnects.
         }}*/
      pc->Method_cbbs("ping", "{|s| XbFpCall(%i,s) }", (DWORD) mysql_xb_ping);
      /*{{|method_: - `METHOD rollback()`
         | return: lOk
         | desc_: Rolls back the current transaction (`mysql_rollback()`).
         }}*/
      pc->Method_cbbs("rollback", "{|s|  XbFpCall(%i,s) }", (DWORD) mysql_xb_rollback);
      // --------------------
      /*{{|class-property_: - `CLASS PROPERTY flag_CLIENT_*`
         | desc_: The client flags of libmysql (`CLIENT_*` in `mysql.h`), one read-only class property each, to compose the
           `nFlags` of `new()` and `connect()` with `nOr()`. The ones the examples use: `flag_CLIENT_REMEMBER_OPTIONS`,
           `flag_CLIENT_SSL`, `flag_CLIENT_MULTI_RESULTS` (needed for `query()` to run several statements in one call).
         | list_: - `CLASS PROPERTY flag_CLIENT_LONG_PASSWORD`
           - `CLASS PROPERTY flag_CLIENT_FOUND_ROWS`
           - `CLASS PROPERTY flag_CLIENT_LONG_FLAG`
           - `CLASS PROPERTY flag_CLIENT_CONNECT_WITH_DB`
           - `CLASS PROPERTY flag_CLIENT_NO_SCHEMA`
           - `CLASS PROPERTY flag_CLIENT_COMPRESS`
           - `CLASS PROPERTY flag_CLIENT_LOCAL_FILES`
           - `CLASS PROPERTY flag_CLIENT_IGNORE_SPACE`
           - `CLASS PROPERTY flag_CLIENT_PROTOCOL_41`
           - `CLASS PROPERTY flag_CLIENT_INTERACTIVE`
           - `CLASS PROPERTY flag_CLIENT_SSL`
           - `CLASS PROPERTY flag_CLIENT_IGNORE_SIGPIPE`
           - `CLASS PROPERTY flag_CLIENT_TRANSACTIONS`
           - `CLASS PROPERTY flag_CLIENT_RESERVED`
           - `CLASS PROPERTY flag_CLIENT_RESERVED2`
           - `CLASS PROPERTY flag_CLIENT_MULTI_STATEMENTS`
           - `CLASS PROPERTY flag_CLIENT_MULTI_RESULTS`
           - `CLASS PROPERTY flag_CLIENT_PS_MULTI_RESULTS`
           - `CLASS PROPERTY flag_CLIENT_PLUGIN_AUTH`
           - `CLASS PROPERTY flag_CLIENT_CONNECT_ATTRS`
           - `CLASS PROPERTY flag_CLIENT_PLUGIN_AUTH_LENENC_CLIENT_DATA`
           - `CLASS PROPERTY flag_CLIENT_CAN_HANDLE_EXPIRED_PASSWORDS`
           - `CLASS PROPERTY flag_CLIENT_SESSION_TRACK`
           - `CLASS PROPERTY flag_CLIENT_DEPRECATE_EOF`
           - `CLASS PROPERTY flag_CLIENT_SSL_VERIFY_SERVER_CERT`
           - `CLASS PROPERTY flag_CLIENT_REMEMBER_OPTIONS`
         }}*/
      pc->ClassProperty_cbbs("flag_CLIENT_LONG_PASSWORD", "{|| %i }", CLIENT_LONG_PASSWORD);
      pc->ClassProperty_cbbs("flag_CLIENT_FOUND_ROWS", "{|| %i }", CLIENT_FOUND_ROWS);
      pc->ClassProperty_cbbs("flag_CLIENT_LONG_FLAG", "{|| %i }", CLIENT_LONG_FLAG);
      pc->ClassProperty_cbbs("flag_CLIENT_CONNECT_WITH_DB", "{|| %i }", CLIENT_CONNECT_WITH_DB);
      pc->ClassProperty_cbbs("flag_CLIENT_NO_SCHEMA", "{|| %i }", CLIENT_NO_SCHEMA);
      pc->ClassProperty_cbbs("flag_CLIENT_COMPRESS", "{|| %i }", CLIENT_COMPRESS);
      pc->ClassProperty_cbbs("flag_CLIENT_LOCAL_FILES", "{|| %i }", CLIENT_LOCAL_FILES);
      pc->ClassProperty_cbbs("flag_CLIENT_IGNORE_SPACE", "{|| %i }", CLIENT_IGNORE_SPACE);
      pc->ClassProperty_cbbs("flag_CLIENT_PROTOCOL_41", "{|| %i }", CLIENT_PROTOCOL_41);
      pc->ClassProperty_cbbs("flag_CLIENT_INTERACTIVE", "{|| %i }", CLIENT_INTERACTIVE);
      pc->ClassProperty_cbbs("flag_CLIENT_SSL", "{|| %i }", CLIENT_SSL);
      pc->ClassProperty_cbbs("flag_CLIENT_IGNORE_SIGPIPE", "{|| %i }", CLIENT_IGNORE_SIGPIPE);
      pc->ClassProperty_cbbs("flag_CLIENT_TRANSACTIONS", "{|| %i }", CLIENT_TRANSACTIONS);
      pc->ClassProperty_cbbs("flag_CLIENT_RESERVED", "{|| %i }", CLIENT_RESERVED);
      pc->ClassProperty_cbbs("flag_CLIENT_RESERVED2", "{|| %i }", CLIENT_RESERVED2);
      pc->ClassProperty_cbbs("flag_CLIENT_MULTI_STATEMENTS", "{|| %i }", CLIENT_MULTI_STATEMENTS);
      pc->ClassProperty_cbbs("flag_CLIENT_MULTI_RESULTS", "{|| %i }", CLIENT_MULTI_RESULTS);
      pc->ClassProperty_cbbs("flag_CLIENT_PS_MULTI_RESULTS", "{|| %i }", CLIENT_PS_MULTI_RESULTS);
      pc->ClassProperty_cbbs("flag_CLIENT_PLUGIN_AUTH", "{|| %i }", CLIENT_PLUGIN_AUTH);
      pc->ClassProperty_cbbs("flag_CLIENT_CONNECT_ATTRS", "{|| %i }", CLIENT_CONNECT_ATTRS);
      pc->ClassProperty_cbbs("flag_CLIENT_PLUGIN_AUTH_LENENC_CLIENT_DATA", "{|| %i }", CLIENT_PLUGIN_AUTH_LENENC_CLIENT_DATA);
      pc->ClassProperty_cbbs("flag_CLIENT_CAN_HANDLE_EXPIRED_PASSWORDS", "{|| %i }", CLIENT_CAN_HANDLE_EXPIRED_PASSWORDS);
      pc->ClassProperty_cbbs("flag_CLIENT_SESSION_TRACK", "{|| %i }", CLIENT_SESSION_TRACK);
      pc->ClassProperty_cbbs("flag_CLIENT_DEPRECATE_EOF", "{|| %i }", CLIENT_DEPRECATE_EOF);
      pc->ClassProperty_cbbs("flag_CLIENT_SSL_VERIFY_SERVER_CERT", "{|| %i }", CLIENT_SSL_VERIFY_SERVER_CERT);
      pc->ClassProperty_cbbs("flag_CLIENT_REMEMBER_OPTIONS", "{|| %i }", CLIENT_REMEMBER_OPTIONS);


      // -------------------
      /*{{|class-method_: - `CLASS METHOD mysql4xb_global_flags_set_get( nPos, [xValue] )`
         | return: nValue or NIL
         | desc_: Reads (one parameter) or writes (two) one of the global conversion flags of the DLL, by position; the three
           methods below are the named forms. They are global: they apply to every connection of the process, and the
           three start at 1 (on). See the {{ilink: <topic mysql4xb-type-mapping> type mapping}}.
         }}*/
      pc->ClassMethod_cbbs("mysql4xb_global_flags_set_get", "{|s,pos,v,ptr| pos := nAnd(pos,0xFFFF) , "
         "iif( pos < %i , iif( v == NIL , PeekByte(%i,pos ), PokeByte(%i,pos,nAnd(v,0xFF))  ) , NIL )",
         mysqlxb_global_flags_enum::max_flags ,  mysqlxb_global_flags, mysqlxb_global_flags);
      // --------------------
      /*{{|class-method_: - `CLASS METHOD mysql4xb_global_flags_tiny_to_bool( [lOnOff] )`
         | return: nValue
         | desc_: `TINYINT` columns come out as logical (`.T.`/`.F.`) when on, as numbers when off. Also decides the
           Xbase++ type the field descriptor reports for them.
         }}*/
      pc->ClassMethod_cbbs("mysql4xb_global_flags_tiny_to_bool", "{|s,v| s:mysql4xb_global_flags_set_get( %i , v )  }", mysqlxb_global_flags, mysqlxb_global_flags_enum::tiny_to_bool);
      /*{{|class-method_: - `CLASS METHOD mysql4xb_global_flags_null_to_empty( [lOnOff] )`
         | return: nValue
         | desc_: A `NULL` cell comes out as the blank value of its type when on (empty string, 0, empty date, `.F.`), as
           NIL when off.
         }}*/
      pc->ClassMethod_cbbs("mysql4xb_global_flags_null_to_empty", "{|s,v| s:mysql4xb_global_flags_set_get( %i , v )  }", mysqlxb_global_flags, mysqlxb_global_flags_enum::null_to_empty);
      /*{{|class-method_: - `CLASS METHOD mysql4xb_global_flags_auto_truncate_values( [lOnOff] )`
         | return: nValue
         | desc_: When on, `escape_value()` of a field truncates a character value longer than the column before quoting
           it; when off the value is passed as it is and the server decides.
         }}*/
      pc->ClassMethod_cbbs("mysql4xb_global_flags_auto_truncate_values", "{|s,v| s:mysql4xb_global_flags_set_get( %i , v )  }", mysqlxb_global_flags, mysqlxb_global_flags_enum::auto_truncate_values);

      

      // -------------------
 
      
      
      // -------------------
      /*{{|method_: - `METHOD set_option_string( nOption, cValue )`
         | desc_: The generic form of `mysql_options()`: `nOption` is a `mysql_option` value of `mysql.h` and the value a string;
           `set_option_dword( nOption, nValue )` and `set_option_bool( nOption, lValue )` are the same for an unsigned
           int and a boolean. The named methods below pick the option and the type for you. Options are set before
           `connect()`.
         }}*/
      pc->Method_cbbs("set_option_string", "{|s,n,v| XbFpCall(%i,s:m_mysql,n,v)}", mysql_xb_set_option_string);
      pc->Method_cbbs("set_option_dword", "{|s,n,v| XbFpCall(%i,s:m_mysql,n,v)}", mysql_xb_set_option_dword);
      pc->Method_cbbs("set_option_bool", "{|s,n,v| XbFpCall(%i,s:m_mysql,n,v)}", mysql_xb_set_option_bool);
      /*{{|method_: - `METHOD set_option_*( xValue )`
         | desc_: One method per option of `mysql_options()`, named after it, with the value type the option wants:
           `set_option_connect_timeout( 5 )`, `set_option_reconnect( .T. )`, `set_option_ssl_mode( 3 )`
           (`SSL_MODE_REQUIRED`), `set_option_set_charset_name( "utf8mb4" )`. The option each one sets:
         | list_: - `METHOD set_option_connect_timeout( nValue )` - `MYSQL_OPT_CONNECT_TIMEOUT`
           - `METHOD set_option_init_command( cValue )` - `MYSQL_INIT_COMMAND`
           - `METHOD set_option_read_default_file( cValue )` - `MYSQL_READ_DEFAULT_FILE`
           - `METHOD set_option_read_default_group( cValue )` - `MYSQL_READ_DEFAULT_GROUP`
           - `METHOD set_option_set_charset_dir( cValue )` - `MYSQL_SET_CHARSET_DIR`
           - `METHOD set_option_set_charset_name( cValue )` - `MYSQL_SET_CHARSET_NAME`
           - `METHOD set_option_local_infile( nValue )` - `MYSQL_OPT_LOCAL_INFILE`
           - `METHOD set_option_protocol( nValue )` - `MYSQL_OPT_PROTOCOL`
           - `METHOD set_option_shared_memory_base_name( cValue )` - `MYSQL_SHARED_MEMORY_BASE_NAME`
           - `METHOD set_option_read_timeout( nValue )` - `MYSQL_OPT_READ_TIMEOUT`
           - `METHOD set_option_write_timeout( nValue )` - `MYSQL_OPT_WRITE_TIMEOUT`
           - `METHOD set_option_client_ip( cValue )` - `MYSQL_SET_CLIENT_IP`
           - `METHOD set_option_secure_auth( lValue )` - `MYSQL_SECURE_AUTH`
           - `METHOD set_option_report_data_truncation( lValue )` - `MYSQL_REPORT_DATA_TRUNCATION`
           - `METHOD set_option_reconnect( lValue )` - `MYSQL_OPT_RECONNECT`
           - `METHOD set_option_ssl_verify_server_cert( lValue )` - `MYSQL_OPT_SSL_VERIFY_SERVER_CERT`
           - `METHOD set_option_plugin_dir( cValue )` - `MYSQL_PLUGIN_DIR`
           - `METHOD set_option_default_auth( cValue )` - `MYSQL_DEFAULT_AUTH`
           - `METHOD set_option_bind( cValue )` - `MYSQL_OPT_BIND`
           - `METHOD set_option_ssl_key( cValue )` - `MYSQL_OPT_SSL_KEY`
           - `METHOD set_option_ssl_cert( cValue )` - `MYSQL_OPT_SSL_CERT`
           - `METHOD set_option_ssl_ca( cValue )` - `MYSQL_OPT_SSL_CA`
           - `METHOD set_option_ssl_capath( cValue )` - `MYSQL_OPT_SSL_CAPATH`
           - `METHOD set_option_ssl_cipher( cValue )` - `MYSQL_OPT_SSL_CIPHER`
           - `METHOD set_option_ssl_crl( cValue )` - `MYSQL_OPT_SSL_CRL`
           - `METHOD set_option_ssl_crlpath( cValue )` - `MYSQL_OPT_SSL_CRLPATH`
           - `METHOD set_option_connect_attr_delete( cValue )` - `MYSQL_OPT_CONNECT_ATTR_DELETE`
           - `METHOD set_option_server_public_key( cValue )` - `MYSQL_SERVER_PUBLIC_KEY`
           - `METHOD set_option_enable_cleartext_plugin( lValue )` - `MYSQL_ENABLE_CLEARTEXT_PLUGIN`
           - `METHOD set_option_can_handle_expired_passwords( lValue )` - `MYSQL_OPT_CAN_HANDLE_EXPIRED_PASSWORDS`
           - `METHOD set_option_ssl_enforce( lValue )` - `MYSQL_OPT_SSL_ENFORCE`
           - `METHOD set_option_max_allowed_packet( nValue )` - `MYSQL_OPT_MAX_ALLOWED_PACKET`
           - `METHOD set_option_net_buffer_length( nValue )` - `MYSQL_OPT_NET_BUFFER_LENGTH`
           - `METHOD set_option_tls_version( cValue )` - `MYSQL_OPT_TLS_VERSION`
           - `METHOD set_option_ssl_mode( nValue )` - the `SSL_MODE_*` of libmysql 5.7 (1 `DISABLED` .. 5 `VERIFY_IDENTITY`),
             mapped onto `MYSQL_OPT_SSL_ENFORCE` and `MYSQL_OPT_SSL_VERIFY_SERVER_CERT`, which is what MariaDB
             Connector/C has; see {{ilink: <internal-function mysql_xb_set_option_ssl_mode> mysql_xb_set_option_ssl_mode}}.
         }}*/
      pc->Method_cbbs("set_option_connect_timeout", "{|s,v| XbFpCall(%i,s:m_mysql,%i,v)}", mysql_xb_set_option_dword, MYSQL_OPT_CONNECT_TIMEOUT);
      pc->Method_cbbs("set_option_init_command", "{|s,v| XbFpCall(%i,s:m_mysql,%i,v)}", mysql_xb_set_option_string, MYSQL_INIT_COMMAND);
      pc->Method_cbbs("set_option_read_default_file", "{|s,v| XbFpCall(%i,s:m_mysql,%i,v)}", mysql_xb_set_option_string, MYSQL_READ_DEFAULT_FILE);
      pc->Method_cbbs("set_option_read_default_group", "{|s,v| XbFpCall(%i,s:m_mysql,%i,v)}", mysql_xb_set_option_string, MYSQL_READ_DEFAULT_GROUP);
      pc->Method_cbbs("set_option_set_charset_dir", "{|s,v| XbFpCall(%i,s:m_mysql,%i,v)}", mysql_xb_set_option_string, MYSQL_SET_CHARSET_DIR);
      pc->Method_cbbs("set_option_set_charset_name", "{|s,v| XbFpCall(%i,s:m_mysql,%i,v)}", mysql_xb_set_option_string, MYSQL_SET_CHARSET_NAME);
      pc->Method_cbbs("set_option_local_infile", "{|s,v| XbFpCall(%i,s:m_mysql,%i,v)}", mysql_xb_set_option_dword, MYSQL_OPT_LOCAL_INFILE);
      pc->Method_cbbs("set_option_protocol", "{|s,v| XbFpCall(%i,s:m_mysql,%i,v)}", mysql_xb_set_option_dword, MYSQL_OPT_PROTOCOL);
      pc->Method_cbbs("set_option_shared_memory_base_name", "{|s,v| XbFpCall(%i,s:m_mysql,%i,v)}", mysql_xb_set_option_string, MYSQL_SHARED_MEMORY_BASE_NAME);
      pc->Method_cbbs("set_option_read_timeout", "{|s,v| XbFpCall(%i,s:m_mysql,%i,v)}", mysql_xb_set_option_dword, MYSQL_OPT_READ_TIMEOUT);
      pc->Method_cbbs("set_option_write_timeout", "{|s,v| XbFpCall(%i,s:m_mysql,%i,v)}", mysql_xb_set_option_dword, MYSQL_OPT_WRITE_TIMEOUT);
      pc->Method_cbbs("set_option_client_ip", "{|s,v| XbFpCall(%i,s:m_mysql,%i,v)}", mysql_xb_set_option_string, MYSQL_SET_CLIENT_IP);
      pc->Method_cbbs("set_option_secure_auth", "{|s,v| XbFpCall(%i,s:m_mysql,%i,v)}", mysql_xb_set_option_bool, MYSQL_SECURE_AUTH);
      pc->Method_cbbs("set_option_report_data_truncation", "{|s,v| XbFpCall(%i,s:m_mysql,%i,v)}", mysql_xb_set_option_bool, MYSQL_REPORT_DATA_TRUNCATION);
      pc->Method_cbbs("set_option_reconnect", "{|s,v| XbFpCall(%i,s:m_mysql,%i,v)}", mysql_xb_set_option_bool, MYSQL_OPT_RECONNECT);
      pc->Method_cbbs("set_option_ssl_verify_server_cert", "{|s,v| XbFpCall(%i,s:m_mysql,%i,v)}", mysql_xb_set_option_bool, MYSQL_OPT_SSL_VERIFY_SERVER_CERT);
      pc->Method_cbbs("set_option_plugin_dir", "{|s,v| XbFpCall(%i,s:m_mysql,%i,v)}", mysql_xb_set_option_string, MYSQL_PLUGIN_DIR);
      pc->Method_cbbs("set_option_default_auth", "{|s,v| XbFpCall(%i,s:m_mysql,%i,v)}", mysql_xb_set_option_string, MYSQL_DEFAULT_AUTH);
      pc->Method_cbbs("set_option_bind", "{|s,v| XbFpCall(%i,s:m_mysql,%i,v)}", mysql_xb_set_option_string, MYSQL_OPT_BIND);
      pc->Method_cbbs("set_option_ssl_key", "{|s,v| XbFpCall(%i,s:m_mysql,%i,v)}", mysql_xb_set_option_string, MYSQL_OPT_SSL_KEY);
      pc->Method_cbbs("set_option_ssl_cert", "{|s,v| XbFpCall(%i,s:m_mysql,%i,v)}", mysql_xb_set_option_string, MYSQL_OPT_SSL_CERT);
      pc->Method_cbbs("set_option_ssl_ca", "{|s,v| XbFpCall(%i,s:m_mysql,%i,v)}", mysql_xb_set_option_string, MYSQL_OPT_SSL_CA);
      pc->Method_cbbs("set_option_ssl_capath", "{|s,v| XbFpCall(%i,s:m_mysql,%i,v)}", mysql_xb_set_option_string, MYSQL_OPT_SSL_CAPATH);
      pc->Method_cbbs("set_option_ssl_cipher", "{|s,v| XbFpCall(%i,s:m_mysql,%i,v)}", mysql_xb_set_option_string, MYSQL_OPT_SSL_CIPHER);
      pc->Method_cbbs("set_option_ssl_crl", "{|s,v| XbFpCall(%i,s:m_mysql,%i,v)}", mysql_xb_set_option_string, MYSQL_OPT_SSL_CRL);
      pc->Method_cbbs("set_option_ssl_crlpath", "{|s,v| XbFpCall(%i,s:m_mysql,%i,v)}", mysql_xb_set_option_string, MYSQL_OPT_SSL_CRLPATH);
      pc->Method_cbbs("set_option_connect_attr_delete", "{|s,v| XbFpCall(%i,s:m_mysql,%i,v)}", mysql_xb_set_option_string, MYSQL_OPT_CONNECT_ATTR_DELETE);
      pc->Method_cbbs("set_option_server_public_key", "{|s,v| XbFpCall(%i,s:m_mysql,%i,v)}", mysql_xb_set_option_string, MYSQL_SERVER_PUBLIC_KEY);
      pc->Method_cbbs("set_option_enable_cleartext_plugin", "{|s,v| XbFpCall(%i,s:m_mysql,%i,v)}", mysql_xb_set_option_bool, MYSQL_ENABLE_CLEARTEXT_PLUGIN);
      pc->Method_cbbs("set_option_can_handle_expired_passwords", "{|s,v| XbFpCall(%i,s:m_mysql,%i,v)}", mysql_xb_set_option_bool, MYSQL_OPT_CAN_HANDLE_EXPIRED_PASSWORDS);
      pc->Method_cbbs("set_option_ssl_enforce", "{|s,v| XbFpCall(%i,s:m_mysql,%i,v)}", mysql_xb_set_option_bool, MYSQL_OPT_SSL_ENFORCE);
      pc->Method_cbbs("set_option_max_allowed_packet", "{|s,v| XbFpCall(%i,s:m_mysql,%i,v)}", mysql_xb_set_option_dword, MYSQL_OPT_MAX_ALLOWED_PACKET);
      pc->Method_cbbs("set_option_net_buffer_length", "{|s,v| XbFpCall(%i,s:m_mysql,%i,v)}", mysql_xb_set_option_dword, MYSQL_OPT_NET_BUFFER_LENGTH);
      pc->Method_cbbs("set_option_tls_version", "{|s,v| XbFpCall(%i,s:m_mysql,%i,v)}", mysql_xb_set_option_string, MYSQL_OPT_TLS_VERSION);
      pc->Method_cbbs("set_option_ssl_mode", "{|s,v| XbFpCall(%i,s:m_mysql,v)}", mysql_xb_set_option_ssl_mode);
      // -----
      /*{{|method_: - `METHOD connect( cHost, cUser, cPassword, cDb, nPort, cUnixSocket, nFlags )`
         | return: lConnected
         | desc_: Opens the session (`mysql_real_connect()`) with the options set so far; `nPort` 0 and `cUnixSocket` NIL take
           the defaults of libmysql, `nFlags` is ORed with the flags given to `new()`. The result is also kept in
           `m_last_connect_result`; on failure `last_error()` and `last_error_string()` say why.
         }}*/
      pc->Method_cbbs("connect", "{|s,host,user,pwd,db,port,sk,flags| "
         " s:m_last_connect_result := XbFpCall(%i,s:m_mysql,host,user,pwd,db,port,sk,nOr(flags, s:m_mysql4xb_flags) )}", mysql_xb_real_connect); // ::connect( host,user,pwd,db,port,unix_socket,flags) -> lOk
      
      /*{{|method_: - `METHOD query( cSql, [oResultSetClass], [nFlags] )`
         | return: oResultSet, nAffectedRows, aResults or NIL
         | desc_: Runs `cSql` (`mysql_real_query()`) and stores the whole result set in memory (`mysql_store_result()`),
           converted to Xbase++ values as the {{ilink: <topic mysql4xb-type-mapping> type mapping}} says. A statement that returns rows gives an object of
           `oResultSetClass` - `m_resultset_class_object` when omitted - built over a {{ilink: <class mysql4xb_result_rows_t> mysql4xb_result_rows_t}}; one that returns
           none gives the affected rows as a number. With `nFlags` 0x1000 the return is an array with one entry per
           result of the call, which is how several statements in one string (`CLIENT_MULTI_RESULTS`) or a stored
           procedure with several selects come back. NIL when there is no handle or the statement failed: check
           `last_error()`.
         }}*/
      pc->Method_cbbs("query", "{|s,sql,rs_co,flags|  XbFpCall(%i,s:m_mysql,sql" // 1 , 2 
         ",__vdef(rs_co,s:m_resultset_class_object)" // 3
         ",s:m_result_rows_class_object" // 4
         ",s:m_result_field_class_object" // 5
         ",s,flags)}", mysql_xb_quick_query); // mysql_xb_quick_query(1pMysql,2sql,3rs_co,4 rows_co , 5 fld_co, 6 self, 7 flags) // ::exec( sql ) -> resulset | NIL
      
      /*{{|method_: - `METHOD field_count()`
         | return: nFields
         | desc_: The number of columns of the last statement (`mysql_field_count()`); 0 for a statement without result set.
         }}*/
      pc->Method_cbbs("field_count", "{|s| nFpCall( %i , s ) }",mysql_xb_field_count );
      /*{{|method_: - `METHOD last_insert_id()`
         | return: nId
         | desc_: The `AUTO_INCREMENT` value generated by the last `INSERT` (`mysql_insert_id()`), -1 without a handle.
         }}*/
      pc->Method_cbbs("last_insert_id","{|s|  XbFpCall(%i,s) }", mysql_xb_last_inserted_id);
      /*{{|method_: - `METHOD affected_rows()`
         | return: nRows
         | desc_: The rows changed, deleted or inserted by the last statement (`mysql_affected_rows()`), -1 without a handle.
         }}*/
      pc->Method_cbbs("affected_rows", "{|s|  XbFpCall(%i,s) }", mysql_xb_affected_rows );
      
      





      /*{{|:**END CLASS** }}*/
      conco = pc->Create();
      delete pc;
      if (conco == NULLCONTAINER)
      {
         _ret(pl);
         return;
      }

   }
   _conReturn(pl, conco);
   _conRelease(conco);
}
/*{{end-class}}*/
// ---------------------------------------------------------------------------------

// -----------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------------------------------------

