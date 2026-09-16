#include <mysql4xb_api.h>
// ------------------------------------------------------------------------------------------------------------
/*{{internal-function_: mysql_xb_set_option_dword
   | syntax_: `void mysql_xb_set_option_dword( XppParamList pl )` - `( pMysql, nOption, nValue )`
   | category: mysql/internals
   | desc: `mysql_options()` with an unsigned int value; the C side of `set_option_dword()` and of the named methods that take a number.
     Reached from the methods of {{ilink: <class mysql4xb> mysql4xb}} through `XbFpCall()`.
   | _kw_: mysql_xb_set_option_dword, Internal
   }}*/
void __cdecl mysql_xb_set_option_dword(XppParamList pl) // ( MYSQL* pMysql , nOption , value ) -> NIL
{
   TXppParamList xpp(pl, 3);
   MYSQL* my = (MYSQL*)xpp[1]->GetDWord();
   if (my)
   {
      DWORD value = xpp[3]->GetDWord();

      mysql_options(my, (mysql_option)xpp[2]->GetLong(), (void*)&value);
   }
}
// ------------------------------------------------------------------------------------------------------------
/*{{internal-function_: mysql_xb_set_option_bool
   | syntax_: `void mysql_xb_set_option_bool( XppParamList pl )` - `( pMysql, nOption, lValue )`
   | category: mysql/internals
   | desc: `mysql_options()` with a boolean (an int 0/1); the C side of `set_option_bool()` and of the named methods that take a logical.
     Reached from the methods of {{ilink: <class mysql4xb> mysql4xb}} through `XbFpCall()`.
   | _kw_: mysql_xb_set_option_bool, Internal
   }}*/
void __cdecl mysql_xb_set_option_bool(XppParamList pl) // ( MYSQL* pMysql , nOption , value ) -> NIL
{
   TXppParamList xpp(pl, 3);
   MYSQL* my = (MYSQL*)xpp[1]->GetDWord();
   if (my)
   {
      int value = (xpp[3]->GetBool() ? 1 : 0);

      mysql_options(my, (mysql_option)xpp[2]->GetLong(), (void*)&value);
   }
}
// ------------------------------------------------------------------------------------------------------------
/*{{internal-function_: mysql_xb_set_option_string
   | syntax_: `void mysql_xb_set_option_string( XppParamList pl )` - `( pMysql, nOption, cValue )`
   | category: mysql/internals
   | desc: `mysql_options()` with a string; the C side of `set_option_string()` and of the named methods that take one.
     Reached from the methods of {{ilink: <class mysql4xb> mysql4xb}} through `XbFpCall()`.
   | _kw_: mysql_xb_set_option_string, Internal
   }}*/
void __cdecl mysql_xb_set_option_string(XppParamList pl) // ( MYSQL* pMysql , nOption , value ) -> NIL
{
   TXppParamList xpp(pl, 3);
   MYSQL* my = (MYSQL*)xpp[1]->GetDWord();
   if (my)
   {
      LPSTR value = xpp[3]->LockStr();
      mysql_options(my, (mysql_option)xpp[2]->GetLong(), (void*)value);
   }
}
// ------------------------------------------------------------------------------------------------------------
/*{{internal-function_: mysql_xb_real_connect
   | syntax_: `void mysql_xb_real_connect( XppParamList pl )` - `( pMysql, cHost, cUser, cPassword, cDb, nPort, cUnixSocket, nFlags ) -> lOk`
   | category: mysql/internals
   | desc: `mysql_real_connect()`; a NIL string parameter is passed as a null pointer, which is how libmysql takes its defaults.
     Reached from the methods of {{ilink: <class mysql4xb> mysql4xb}} through `XbFpCall()`.
   | _kw_: mysql_xb_real_connect, Internal
   }}*/
void __cdecl mysql_xb_real_connect(XppParamList pl) // mysql_xb_real_connect(1MYSQL *, 2char* host, 3const char* user, 4char* pwd, 5const char* db, 6uint port, 7char* unix_socket, 8 ULONG clientflag);
// ( MYSQL* pMysql , nOption , value ) -> NIL
{
   TXppParamList xpp(pl, 8);
   MYSQL* my = (MYSQL*)xpp[1]->GetDWord();
   MYSQL* result = 0;
   if (my)
   {
      result = mysql_real_connect(my,
         (const char*)xpp[2]->LockStrEx(),//host,
         (const char*)xpp[3]->LockStrEx(),//user,
         (const char*)xpp[4]->LockStrEx(),//passwd,
         (const char*)xpp[5]->LockStrEx(),//db,
         (unsigned int)xpp[6]->GetLong(),//port,
         (const char*)xpp[7]->LockStrEx(),   //unix_socket,
         (unsigned long)xpp[8]->GetLong());  //clientflag)
   }
   xpp[0]->PutBool(result ? 1 : 0);
}
// -------------------------------------------------------------------------------------------------------------

/*{{internal-function_: mysql_xb_init
   | syntax_: `void mysql_xb_init( XppParamList pl )` - `( oSelf, [nFlags] ) -> oSelf`
   | category: mysql/internals
   | desc: `mysql_init()`: creates the handle stored in `m_mysql`, closing a previous one, and stores `nFlags` (default 1) in
     `m_mysql4xb_flags`. The C side of `new()`.
     Reached from the methods of {{ilink: <class mysql4xb> mysql4xb}} through `XbFpCall()`.
   | _kw_: mysql_xb_init, Internal
   }}*/
void __cdecl mysql_xb_init(XppParamList pl)
{
   TXppParamList xpp(pl, 2);
   ContainerHandle Self = xpp[1]->con();
   LONG flags = xpp[2]->CheckType(XPP_NUMERIC) ? xpp[2]->GetLong() : 1;
   MYSQL* my = (MYSQL*) _conGetNLMember(Self, "m_mysql");
   _conSetNLMember(Self, "m_mysql4xb_flags", flags);
   if (my)
   {
      mysql_close(my);
   }
   my = mysql_init((MYSQL*) 0 );
   _conSetNLMember(Self, "m_mysql", (LONG)((void*)my));
   xpp[0]->Put(Self);
}
// -------------------------------------------------------------------------------------------------------------
/*{{internal-function_: mysql_xb_close
   | syntax_: `void mysql_xb_close( XppParamList pl )` - `( oSelf )`
   | category: mysql/internals
   | desc: `mysql_close()` and `m_mysql := 0`.
     Reached from the methods of {{ilink: <class mysql4xb> mysql4xb}} through `XbFpCall()`.
   | _kw_: mysql_xb_close, Internal
   }}*/
void __cdecl mysql_xb_close(XppParamList pl)
{
   TXppParamList xpp(pl, 2);
   ContainerHandle Self = xpp[1]->con();
   MYSQL* my = (MYSQL*)_conGetNLMember(Self, "m_mysql");
   if (my)
   {
      mysql_close(my);
   }
   _conSetNLMember(Self, "m_mysql", (LONG)((void*) 0 ));


}
// -------------------------------------------------------------------------------------------------------------

/*{{internal-function_: mysql_xb_last_error
   | syntax_: `void mysql_xb_last_error( XppParamList pl )` - `( oSelf ) -> nErrno`
   | category: mysql/internals
   | desc: `mysql_errno()`, -1 without a handle.
     Reached from the methods of {{ilink: <class mysql4xb> mysql4xb}} through `XbFpCall()`.
   | _kw_: mysql_xb_last_error, Internal
   }}*/
void __cdecl mysql_xb_last_error(XppParamList pl)
{
   TXppParamList xpp(pl, 2);
   ContainerHandle Self = xpp[1]->con();
   MYSQL* my = (MYSQL*)_conGetNLMember(Self, "m_mysql");
   if (my)
   {
      xpp[0]->PutLong((LONG)mysql_errno(my));
   }
   else
   {
      xpp[0]->PutLong(-1);
   }


}
// -------------------------------------------------------------------------------------------------------------

/*{{internal-function_: mysql_xb_last_error_string
   | syntax_: `void mysql_xb_last_error_string( XppParamList pl )` - `( oSelf ) -> cMessage`
   | category: mysql/internals
   | desc: `mysql_error()`; `"Invalid Mysql Object"` without a handle.
     Reached from the methods of {{ilink: <class mysql4xb> mysql4xb}} through `XbFpCall()`.
   | _kw_: mysql_xb_last_error_string, Internal
   }}*/
void __cdecl mysql_xb_last_error_string(XppParamList pl)
{
   TXppParamList xpp(pl, 2);
   ContainerHandle Self = xpp[1]->con();
   MYSQL* my = (MYSQL*)_conGetNLMember(Self, "m_mysql");
   if (my)
   {
      xpp[0]->PutStr( (LPSTR) mysql_error(my));
   }
   else
   {
      xpp[0]->PutStr("Invalid Mysql Object");
   }


}
// -------------------------------------------------------------------------------------------------------------

/*{{internal-function_: mysql_xb_info
   | syntax_: `void mysql_xb_info( XppParamList pl )` - `( oSelf ) -> cInfo`
   | category: mysql/internals
   | desc: `mysql_info()`.
     Reached from the methods of {{ilink: <class mysql4xb> mysql4xb}} through `XbFpCall()`.
   | _kw_: mysql_xb_info, Internal
   }}*/
void __cdecl mysql_xb_info(XppParamList pl)
{
   TXppParamList xpp(pl, 2);
   ContainerHandle Self = xpp[1]->con();
   MYSQL* my = (MYSQL*)_conGetNLMember(Self, "m_mysql");
   if (my)
   {
      xpp[0]->PutStr((LPSTR)mysql_info(my));
   }
   else
   {
      xpp[0]->PutStr("Invalid Mysql Object");
   }


}
// -------------------------------------------------------------------------------------------------------------

/*{{internal-function_: mysql_xb_commit
   | syntax_: `void mysql_xb_commit( XppParamList pl )` - `( oSelf ) -> lOk`
   | category: mysql/internals
   | desc: `mysql_commit()`.
     Reached from the methods of {{ilink: <class mysql4xb> mysql4xb}} through `XbFpCall()`.
   | _kw_: mysql_xb_commit, Internal
   }}*/
void __cdecl mysql_xb_commit(XppParamList pl)
{
   TXppParamList xpp(pl, 2);
   ContainerHandle Self = xpp[1]->con();
   MYSQL* my = (MYSQL*)_conGetNLMember(Self, "m_mysql");
   if (my)
   {
      xpp[0]->PutBool(mysql_commit(my) & 0xFF ? TRUE : FALSE);
   }
   else
   {
      xpp[0]->PutBool(FALSE);
   }


}
// -------------------------------------------------------------------------------------------------------------

/*{{internal-function_: mysql_xb_ping
   | syntax_: `void mysql_xb_ping( XppParamList pl )` - `( oSelf ) -> nResult`
   | category: mysql/internals
   | desc: `mysql_ping()`, -1 without a handle.
     Reached from the methods of {{ilink: <class mysql4xb> mysql4xb}} through `XbFpCall()`.
   | _kw_: mysql_xb_ping, Internal
   }}*/
void __cdecl mysql_xb_ping(XppParamList pl)
{
   TXppParamList xpp(pl, 2);
   ContainerHandle Self = xpp[1]->con();
   MYSQL* my = (MYSQL*)_conGetNLMember(Self, "m_mysql");
   if (my)
   {
      xpp[0]->PutLong(mysql_ping(my));
   }
   else
   {
      xpp[0]->PutLong(-1);
   }


}
// -------------------------------------------------------------------------------------------------------------

/*{{internal-function_: mysql_xb_rollback
   | syntax_: `void mysql_xb_rollback( XppParamList pl )` - `( oSelf ) -> lOk`
   | category: mysql/internals
   | desc: `mysql_rollback()`.
     Reached from the methods of {{ilink: <class mysql4xb> mysql4xb}} through `XbFpCall()`.
   | _kw_: mysql_xb_rollback, Internal
   }}*/
void __cdecl mysql_xb_rollback(XppParamList pl)
{
   TXppParamList xpp(pl, 2);
   ContainerHandle Self = xpp[1]->con();
   MYSQL* my = (MYSQL*)_conGetNLMember(Self, "m_mysql");
   if (my)
   {
      xpp[0]->PutBool(mysql_rollback(my) & 0xFF ? TRUE : FALSE);
   }
   else
   {
      xpp[0]->PutBool(FALSE);
   }


}
// -------------------------------------------------------------------------------------------------------------
/*{{internal-function_: mysql_xb_affected_rows
   | syntax_: `void mysql_xb_affected_rows( XppParamList pl )` - `( oSelf ) -> nRows`
   | category: mysql/internals
   | desc: `mysql_affected_rows()`, a 64-bit count returned as a number; -1 without a handle.
     Reached from the methods of {{ilink: <class mysql4xb> mysql4xb}} through `XbFpCall()`.
   | _kw_: mysql_xb_affected_rows, Internal
   }}*/
void __cdecl mysql_xb_affected_rows(XppParamList pl)
{
   TXppParamList xpp(pl, 2);
   ContainerHandle Self = xpp[1]->con();
   MYSQL* my = (MYSQL*)_conGetNLMember(Self, "m_mysql");
   if (my)
   {
      xpp[0]->PutQWordAsNumeric((LONGLONG)mysql_affected_rows(my));
   }
   else
   {
      xpp[0]->PutLong(-1);
   }


}
// -------------------------------------------------------------------------------------------------------------
/*{{internal-function_: mysql_xb_last_inserted_id
   | syntax_: `void mysql_xb_last_inserted_id( XppParamList pl )` - `( oSelf ) -> nId`
   | category: mysql/internals
   | desc: `mysql_insert_id()`, 64-bit, returned as a number; -1 without a handle.
     Reached from the methods of {{ilink: <class mysql4xb> mysql4xb}} through `XbFpCall()`.
   | _kw_: mysql_xb_last_inserted_id, Internal
   }}*/
void __cdecl mysql_xb_last_inserted_id(XppParamList pl)
{
   TXppParamList xpp(pl, 2);
   ContainerHandle Self = xpp[1]->con();
   MYSQL* my = (MYSQL*)_conGetNLMember(Self, "m_mysql");
   if (my)
   {
      xpp[0]->PutQWordAsNumeric((LONGLONG)mysql_insert_id(my));
   }
   else
   {
      xpp[0]->PutLong(-1);
   }


}
// -------------------------------------------------------------------------------------------------------------
/*{{internal-function_: mysql_xb_field_count
   | syntax_: `void mysql_xb_field_count( XppParamList pl )` - `( oSelf ) -> nFields`
   | category: mysql/internals
   | desc: `mysql_field_count()`; 0 without a handle.
     Reached from the methods of {{ilink: <class mysql4xb> mysql4xb}} through `XbFpCall()`.
   | _kw_: mysql_xb_field_count, Internal
   }}*/
void __cdecl mysql_xb_field_count(XppParamList pl)
{
   TXppParamList xpp(pl, 2);
   ContainerHandle Self = xpp[1]->con();
   MYSQL* my = (MYSQL*)_conGetNLMember(Self, "m_mysql");
   if (my)
   {
      xpp[0]->PutLong((LONG) mysql_field_count(my));
   }
   else
   {
      xpp[0]->PutLong(0);
   }


}
// -------------------------------------------------------------------------------------------------------------