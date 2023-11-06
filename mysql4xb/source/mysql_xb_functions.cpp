#include <mysql4xb_api.h>
// ------------------------------------------------------------------------------------------------------------
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

void __cdecl mysql_xb_init(XppParamList pl)
{
   TXppParamList xpp(pl, 2);
   ContainerHandle Self = xpp[1]->con();
   LONG flags = xpp[2]->CheckType(XPP_NUMERIC) ? xpp[2]->GetLong() : 1;
   MYSQL* my = (MYSQL*)_conGetNLMember(Self, "m_mysql");
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