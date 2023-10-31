#include <mysql4xb_api.h>


_XPP_REG_FUN_(MYSQL4XB_RESULTSET_T)
{

   ContainerHandle conco = _conClsObj("MYSQL4XB_RESULTSET_T");
   if (conco == NULLCONTAINER)
   {
      TXbClass* pc = new TXbClass; pc->ClassName("MYSQL4XB_RESULTSET_T");
      pc->EXPORTED();
      pc->Var("__m__rowset__");

      // -------------------
      pc->MethodCB("init", "{|s,rowset_object,mysql,sql| rowset_object:set_prop( 'sql' , sql ), rowset_object:set_prop( 'mysql' , mysql) , s:__m__rowset__ := rowset_object ,  s }");
      pc->MethodCB("rowset", "{|s| s:__m__rowset__  }");
      // -------------------
      pc->MethodCB("DbGoTop", "{|s|  s:__m__rowset__:go_top() }" );
      pc->MethodCB("DbGoBottom", "{|s|  s:__m__rowset__:go_bottom() }");
      pc->MethodCB("DbSkip", "{|s,n|  s:__m__rowset__:skip(n) }");
      pc->MethodCB("Pos", "{|s,pos| iif( pos == NIL, s:__m__rowset__:get_row_pos() , s:__m__rowset__:set_row_pos(pos) ) }");
      pc->MethodCB("LastRow", "{|s|  s:__m__rowset__:get_row_count() }");
      pc->MethodCB("eof", "{|s|  s:__m__rowset__:eof() }");
      pc->MethodCB("bof", "{|s|  s:__m__rowset__:bof() }");
      pc->MethodCB("fcount", "{|s|  s:__m__rowset__:get_col_count() }");
      pc->MethodCB("fieldpos", "{|s,n|  s:__m__rowset__:get_col_pos(n) }");
      pc->MethodCB("fieldname", "{|s,n|  s:__m__rowset__:get_col_name(n) }");
      pc->MethodCB("fieldget", "{|s,n|  s:__m__rowset__:get_cell(n) }");
      pc->MethodCB("GetNoIVar", "{|s,n|  s:__m__rowset__:get_cell(n) }");
      pc->MethodCB("SetNoIVar", "{|s,n,v|  s:__m__rowset__:set_cell(n,v) }");
      pc->MethodCB("fieldput", "{|s,n,v|  s:__m__rowset__:set_cell(n,v) }");
      pc->MethodCB("changed", "{|s,n|  s:__m__rowset__:row_changed(n) }");
      pc->MethodCB("row_metadata", "{|s|  s:__m__rowset__:row_metadata() }");
      // ------
      pc->MethodCB("DbAppend", "{|s|  s:__m__rowset__:add_blank_row() }");
      pc->MethodCB("DbDelete", "{|s|  s:__m__rowset__:mark_row_to_delete() }");
      pc->MethodCB("DbRecall", "{|s|  s:__m__rowset__:unmark_row_to_delete() }");
      // ------
      pc->MethodCB("get_field_info", "{|s,k|  s:__m__rowset__:get_col_info(k) }");
      // ------
      pc->MethodCB("IsNewRow", "{|s|  s:__m__rowset__:is_new_row() }");
      pc->MethodCB("deleted", "{|s|  s:__m__rowset__:is_row_marked_to_delete() }");
      // ------      
      pc->MethodCB("get_prop", "{|s,k| s:__m__rowset__:props:get_prop( k) }");
      pc->MethodCB("is_prop", "{|s,k| s:__m__rowset__:is_prop( k) }");
      pc->MethodCB("set_prop", "{|s,k,v| s:__m__rowset__:set_prop( k,v) }");

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
