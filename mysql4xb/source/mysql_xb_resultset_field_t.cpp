#include <mysql4xb_api.h>

//----------------------------------------------------------------------------------------------------------------------
_XPP_REG_FUN_(MYSQL4XB_RESULT_FIELD_T)
{

   ContainerHandle conco = _conClsObj("MYSQL4XB_RESULT_FIELD_T");
   if (conco == NULLCONTAINER)
   {
      TXbClass* pc = new TXbClass; pc->ClassName("MYSQL4XB_RESULT_FIELD_T");
      pc->EXPORTED();
      pc->Var("field_pos");
      pc->Var("name");
      pc->Var("org_name");
      pc->Var("table");
      pc->Var("db");
      pc->Var("catalog");
      pc->Var("length");
      pc->Var("max_length");
      pc->Var("flags");
      pc->Var("decimals");
      pc->Var("charsetnr");
      pc->Var("type");
      pc->Var("ot4xb_sql_type");
      pc->Var("xbase_type");
      pc->Var("xbase_empty_value");
      pc->Var("escape_flags");

      pc->Property_cbbs("is_NOT_NULL", "{|s| lAnd(s:flags , %i) }", NOT_NULL_FLAG);
      pc->Property_cbbs("is_PRI_KEY", "{|s| lAnd(s:flags , %i) }", PRI_KEY_FLAG);
      pc->Property_cbbs("is_UNIQUE_KEY", "{|s| lAnd(s:flags , %i) }", UNIQUE_KEY_FLAG);
      pc->Property_cbbs("is_MULTIPLE_KEY", "{|s| lAnd(s:flags , %i) }", MULTIPLE_KEY_FLAG);
      pc->Property_cbbs("is_BLOB", "{|s| lAnd(s:flags , %i) }", BLOB_FLAG);
      pc->Property_cbbs("is_UNSIGNED", "{|s| lAnd(s:flags , %i) }", UNSIGNED_FLAG);
      pc->Property_cbbs("is_ZEROFILL", "{|s| lAnd(s:flags , %i) }", ZEROFILL_FLAG);
      pc->Property_cbbs("is_BINARY", "{|s| lAnd(s:flags , %i) }", BINARY_FLAG);
      pc->Property_cbbs("is_ENUM", "{|s| lAnd(s:flags , %i) }", ENUM_FLAG);
      pc->Property_cbbs("is_AUTO_INCREMENT", "{|s| lAnd(s:flags , %i) }", AUTO_INCREMENT_FLAG);
      pc->Property_cbbs("is_TIMESTAMP", "{|s| lAnd(s:flags , %i) }", TIMESTAMP_FLAG);
      pc->Property_cbbs("is_SET", "{|s| lAnd(s:flags , %i) }", SET_FLAG);
      pc->Property_cbbs("is_NO_DEFAULT_VALUE", "{|s| lAnd(s:flags , %i) }", NO_DEFAULT_VALUE_FLAG);

      // -------------------
      pc->MethodCB("escape_value", "{|s,v| ot4xb_sql_dump_value_ansi(v,s:ot4xb_sql_type,s:length,s:decimals,s:escape_flags ) }");
      // -------------------
      pc->MethodCB("init", "{|s| s }");
      // -------------------
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
// ----------------------------------------------------------------------------------------------------------------------------------------
