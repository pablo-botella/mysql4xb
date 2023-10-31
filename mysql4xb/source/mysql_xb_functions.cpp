#include <mysql4xb_api.h>
// ------------------------------------------------------------------------------------------------------------
void __cdecl mysql_xb_set_option_dword(XppParamList pl) // ( MYSQL* pMysql , nOption , value ) -> NIL
{
   TXppParamList xpp(pl,3);
   MYSQL* my = (MYSQL*)xpp[1]->GetDWord();
   if (my)
   {
      DWORD value = xpp[3]->GetDWord();

      mysql_options(my, (mysql_option) xpp[2]->GetLong(), (void*) &value);
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

      mysql_options(my, (mysql_option)xpp[2]->GetLong(), (void*) &value);
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
      mysql_options(my, (mysql_option)xpp[2]->GetLong(), (void*) value);
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



