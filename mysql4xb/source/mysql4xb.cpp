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
XPPRET XPPENTRY MYSQL4XB(XppParamList pl)
{

   ContainerHandle conco = _conClsObj("MYSQL4XB");
   if (conco == NULLCONTAINER)
   {
      TXbClass* pc = new TXbClass; pc->ClassName("MYSQL4XB");
      pc->EXPORTED();
      pc->Var("m_mysql");
      pc->Var("m_mysql4xb_flags");
      pc->Var("m_resultset_class_object");
      pc->Var("m_result_field_class_object");
      pc->Var("m_result_rows_class_object");
      pc->Var("m_last_connect_result");
      pc->Var("m_props");

      // --------------------
      pc->MethodCB("get_prop", "{|s,k| s:m_props:get_prop( k) }");
      pc->MethodCB("is_prop", "{|s,k| s:m_props:is_prop( k) }");
      pc->MethodCB("set_prop", "{|s,k,v| s:m_props:set_prop( k,v) }");

      // -------------------
      pc->ClassProperty_cbbs("version", "{|| \"%s\" }", MYSQL4XB_VERSION_STRING);
      // -------------------
      pc->Method_cbbs("init", "{|s,flags| "
         "  s:m_resultset_class_object := MYSQL4XB_RESULTSET_T() "
         ", s:m_result_field_class_object := MYSQL4XB_RESULT_FIELD_T()  "
         ", s:m_result_rows_class_object  := MYSQL4XB_RESULT_ROWS_T()"
         ", s:m_last_connect_result := NIL  "
         ", s:m_props := _ot4xb_expando_():new()  "
         ", XbFpCall(%i,s,flags) }", (DWORD) mysql_xb_init );

      pc->Method_cbbs("close", "{|s| XbFpCall(%i,s) }", (DWORD) mysql_xb_close);
      pc->Method_cbbs("last_error", "{|s|   XbFpCall(%i,s)  }", (DWORD) mysql_xb_last_error);
      pc->Method_cbbs("last_error_string", "{|s| XbFpCall(%i,s) }", (DWORD) mysql_xb_last_error_string);
      pc->Method_cbbs("info", "{|s| XbFpCall(%i,s) }", (DWORD) mysql_xb_info);
      pc->Method_cbbs("commit", "{|s| XbFpCall(%i,s) }", (DWORD) mysql_xb_commit);
      pc->Method_cbbs("ping", "{|s| XbFpCall(%i,s) }", (DWORD) mysql_xb_ping);
      pc->Method_cbbs("rollback", "{|s|  XbFpCall(%i,s) }", (DWORD) mysql_xb_rollback);
      // --------------------
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
      pc->ClassMethod_cbbs("mysql4xb_global_flags_set_get", "{|s,pos,v,ptr| pos := nAnd(pos,0xFFFF) , "
         "iif( pos < %i , iif( v == NIL , PeekByte(%i,pos ), PokeByte(%i,pos,nAnd(v,0xFF))  ) , NIL )",
         mysqlxb_global_flags_enum::max_flags ,  mysqlxb_global_flags, mysqlxb_global_flags);
      // --------------------
      pc->ClassMethod_cbbs("mysql4xb_global_flags_tiny_to_bool", "{|s,v| s:mysql4xb_global_flags_set_get( %i , v )  }", mysqlxb_global_flags, mysqlxb_global_flags_enum::tiny_to_bool);
      pc->ClassMethod_cbbs("mysql4xb_global_flags_null_to_empty", "{|s,v| s:mysql4xb_global_flags_set_get( %i , v )  }", mysqlxb_global_flags, mysqlxb_global_flags_enum::null_to_empty);
      pc->ClassMethod_cbbs("mysql4xb_global_flags_auto_truncate_values", "{|s,v| s:mysql4xb_global_flags_set_get( %i , v )  }", mysqlxb_global_flags, mysqlxb_global_flags_enum::auto_truncate_values);

      

      // -------------------
 
      
      
      // -------------------
      pc->Method_cbbs("set_option_string", "{|s,n,v| XbFpCall(%i,s:m_mysql,n,v)}", mysql_xb_set_option_string);
      pc->Method_cbbs("set_option_dword", "{|s,n,v| XbFpCall(%i,s:m_mysql,n,v)}", mysql_xb_set_option_dword);
      pc->Method_cbbs("set_option_bool", "{|s,n,v| XbFpCall(%i,s:m_mysql,n,v)}", mysql_xb_set_option_bool);
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
      pc->Method_cbbs("set_option_ssl_mode", "{|s,v| XbFpCall(%i,s:m_mysql,%i,v)}", mysql_xb_set_option_dword, MYSQL_OPT_SSL_MODE);
      pc->Method_cbbs("set_option_get_server_public_key", "{|s,v| XbFpCall(%i,s:m_mysql,%i,v)}", mysql_xb_set_option_bool, MYSQL_OPT_GET_SERVER_PUBLIC_KEY);
      // -----
      pc->Method_cbbs("connect", "{|s,host,user,pwd,db,port,sk,flags| "
         " s:m_last_connect_result := XbFpCall(%i,s:m_mysql,host,user,pwd,db,port,sk,nOr(flags, s:m_mysql4xb_flags) )}", mysql_xb_real_connect); // ::connect( host,user,pwd,db,port,unix_socket,flags) -> lOk
      
      pc->Method_cbbs("query", "{|s,sql,rs_co|  XbFpCall(%i,s:m_mysql,sql" // 1 , 2 
         ",__vdef(rs_co,s:m_resultset_class_object)" // 3
         ",s:m_result_rows_class_object" // 4
         ",s:m_result_field_class_object" // 5
         ",s)}", mysql_xb_quick_query); // mysql_xb_quick_query(1pMysql,2sql,3rs_co,4 rows_co , 5 fld_co, 6 self) // ::exec( sql ) -> resulset | NIL
      
      pc->Method_cbbs("field_count", "{|s| nFpCall( %i , s ) }",mysql_xb_field_count );
      pc->Method_cbbs("last_insert_id","{|s|  XbFpCall(%i,s) }", mysql_xb_last_inserted_id);
      pc->Method_cbbs("affected_rows", "{|s|  XbFpCall(%i,s) }", mysql_xb_affected_rows );
      
      





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
// ---------------------------------------------------------------------------------

// -----------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------------------------------------

