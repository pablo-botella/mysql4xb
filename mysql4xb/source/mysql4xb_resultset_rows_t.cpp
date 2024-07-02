#include <mysql4xb_api.h>
// ------------------------------------------------------------------------------------------------------------------------------------------------------------------
_XPP_REG_FUN_(MYSQL4XB_RESULT_ROWS_T)
{

   ContainerHandle conco = _conClsObj("MYSQL4XB_RESULT_ROWS_T");
   if (conco == NULLCONTAINER)
   {
      TXbClass* pc = new TXbClass; pc->ClassName("MYSQL4XB_RESULT_ROWS_T");
      pc->EXPORTED();
      pc->Var("row_set"); // { changedflags,newrecord,to_delete,reserved} , { col , col, ... } }
      pc->Var("fields");
      pc->Var("field_map");
      pc->Var("row_pos");
      pc->Var("blank_row");
      pc->Var("xbase_row_types");
      pc->Var("row_count");
      pc->Var("col_count");
      pc->Var("throw_type_error");
      pc->Var("props");
      // -------------------
      pc->Var("row_map");
      pc->Var("row_map_pos");
      // ------------------



      // -------------------
      pc->MethodCB("truncate", "{|s |s:row_map := NIL , s:row_set := Array(0) , s:row_pos := 0 , s:row_count := 0 , s}");
      // -------------------
      pc->Method_cbbs("init", "{|s,col_count , row_count | XbFpCall( %i ,s,col_count , row_count ) }", result_rows_ns::init);
      // -------------------
      pc->Method_cbbs("add_colname_alias", "{|s,col_name , col_alias | XbFpCall( %i ,s,col_name , col_alias)}", result_rows_ns::add_colname_alias);
      // -------------------
      pc->Method_cbbs("__set_field_definition", "{|s,fld| XbFpCall(%i , s , fld ) }", result_rows_ns::__set_field_definition);
      // -------------------
      pc->Method_cbbs("__init_empty_row", "{|s,row_pos,col_array| XbFpCall( %i,s,row_pos,col_array ) }", result_rows_ns::__init_empty_row);
      // -------------------
      pc->Method_cbbs("add_blank_row", "{|s,flags|  XbFpCall( %i, s , flags ) }", result_rows_ns::add_blank_row);
      // -------------------
      pc->Method_cbbs("get_col_pos", "{|s,k| XbFpCall(%i,s,k) }", result_rows_ns::get_col_position);
      pc->Method_cbbs("get_col_name", "{|s,k| XbFpCall(%i,s,k) }", result_rows_ns::get_col_name);
      // -------------------
      pc->Method_cbbs("get_col_info", "{|s,k| XbFpCall(%i,s,k) }", result_rows_ns::get_col_info);
      pc->Method_cbbs("peek_col_info", "{|s,col,k,def| __vpeek(XbFpCall(%i,s,col),k,def) }", result_rows_ns::get_col_info);
      // -------------------
      pc->Method_cbbs("go_top", "{|s| XbFpCall(%i,s) }", result_rows_ns::go_top);
      pc->Method_cbbs("go_bottom", "{|s| XbFpCall(%i,s) }", result_rows_ns::go_bottom);
      // -------------------
      pc->Method_cbbs("skip", "{|s,n| XbFpCall(%i,s,n) }", result_rows_ns::skip);
      // -------------------
      pc->Method_cbbs("set_map_pos", "{|s,n| XbFpCall(%i,s,n) }", result_rows_ns::set_map_pos);
      pc->Method_cbbs("set_row_pos", "{|s,n| XbFpCall(%i,s,n) }", result_rows_ns::set_row_pos);
      // -------------------
      pc->MethodCB("get_row_pos", "{|s| s:row_pos }");
      pc->MethodCB("get_row_count", "{|s,n| s:row_count }");
      // -------------------
      pc->MethodCB("get_map_pos", "{|s| s:row_map_pos }");
      pc->MethodCB("get_map_count", "{|s,n| nRShift(len(__vstr(s:row_map,''),2)  }");
      // -------------------
      pc->MethodCB("eof", "{|s|  s:row_pos > s:row_count .or. s:row_pos < 1 }");
      pc->MethodCB("bof", "{|s|  s:row_pos < 1 }");
      pc->MethodCB("get_col_count", "{|s| s:col_count }");
      // -------------------
      pc->Method_cbbs("escape_cell_value", "{|s,n,lError,lGhost|  XbFpCall(%i,s,n,@lError,@lGhost) }", result_rows_ns::escape_cell_value);
      // -------------------
      pc->Method_cbbs("get_cell", "{|s,n,lError,lGhost|  XbFpCall(%i,s,n,@lError,@lGhost) }", result_rows_ns::get_cell);
      // -------------------
      pc->Method_cbbs("set_cell", "{|s,kn,v,lError,lTypeError,lChanged,lGhost|  XbFpCall(%i,s,kn,v,@lError,@lTypeError,@lChanged,@lGhost) }", result_rows_ns::set_cell);
      // ------------------
      pc->Method_cbbs("row_metadata", "{|s,lGhost|   XbFpCall(%i,s,@lGhost) }", result_rows_ns::row_metadata);
      // ------------------
      pc->Method_cbbs("row_changed", "{|s,lGhost|   XbFpCall(%i,s,@lGhost) }", result_rows_ns::row_changed);
      // ------------------
      pc->Method_cbbs("mark_row_to_delete", "{|s,lGhost|   XbFpCall(%i,s,@lGhost) }", result_rows_ns::mark_row_to_delete);
      // ------------------
      pc->Method_cbbs("unmark_row_to_delete", "{|s,lGhost|   XbFpCall(%i,s,@lGhost) }", result_rows_ns::unmark_row_to_delete);
      // ------------------
      pc->Method_cbbs("is_row_marked_to_delete", "{|s,lGhost|   XbFpCall(%i,s,@lGhost) }", result_rows_ns::is_row_marked_to_delete);
      // ------------------
      pc->Method_cbbs("is_new_row", "{|s,lGhost|   XbFpCall(%i,s,@lGhost) }", result_rows_ns::is_new_row);
      // ------------------
      pc->Method_cbbs("remove_row_from_rowset", "{|s,lGhost|   XbFpCall(%i,s,@lGhost) }", result_rows_ns::remove_row_from_rowset);
      // ------------------
      pc->MethodCB("get_prop", "{|s,k| s:props:get_prop( k) }");
      pc->MethodCB("is_prop", "{|s,k| s:props:is_prop( k) }");
      pc->MethodCB("set_prop", "{|s,k,v| s:props:set_prop( k,v) }");


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

// ----------------------------------------------------------------------------------------------------------------------------------
namespace result_rows_ns
{
   // --------------------------------------------------------------------------------------------------------------------
   // xpp{|s,n,@lError,@lGhost|
   ContainerHandle _get_current_or_ghost_cell(TXppParamList& xpp, ContainerHandle& con_field_object)
   {
      ContainerHandle Self = xpp[1]->con();
      LONG row_pos = _conGetNLMember(Self, "row_pos");
      LONG row_count = _conGetNLMember(Self, "row_count");
      DWORD col_count = (DWORD)_conGetNLMember(Self, "col_count");
      DWORD col_pos;
      BOOL lGhost = (row_count > 0 && row_pos <= row_count) ? FALSE : TRUE;
      ContainerHandle con_value = NULLCONTAINER;
      con_field_object = _get_field_object(Self, xpp[2]->con(), col_count, col_pos, con_field_object);

      xpp[3]->PutBool(con_field_object ? 0 : 1);
      xpp[4]->PutBool(lGhost);
      if (con_field_object)
      {
         con_value = _conNew(NULLCONTAINER);
         if (lGhost)
         {
            ContainerHandle cona_blank_row = _conNew(NULLCONTAINER);
            _conGetMember(Self, "blank_row", cona_blank_row);
            _conArrayGet(cona_blank_row, con_value, col_pos, 0);
            _conRelease(cona_blank_row); cona_blank_row = NULLCONTAINER;
         }
         else
         {
            ContainerHandle cona_row_set = _conNew(NULLCONTAINER);
            _conGetMember(Self, "row_set", cona_row_set);
            _conArrayGet(cona_row_set, con_value, row_pos, 2, col_pos, 0);
            _conRelease(cona_row_set); cona_row_set = NULLCONTAINER;
         }
      }
      return con_value;


   }
   // --------------------------------------------------------------------------------------------------------------------
   char _xbase_numeric_type_to_xbase_char_valtype(DWORD xbase_numeric_type)
   {
      switch (xbase_numeric_type & 0xFF)
      {
         case XPP_CHARACTER: return 'C';
         case XPP_NUMERIC: return 'N';
         case XPP_DATE: return 'D';
         case XPP_LOGICAL: return 'L';
         case XPP_ARRAY: return 'A';
         case XPP_OBJECT: return 'O';
         default: return 'U';
      }
   }
   // -----------------------------------------------------------------------------------------------------------------------------
   BOOL _get_row_count_pos_ghost(ContainerHandle Self, LONG& row_pos, LONG& row_count) // -> lGhostRecord 
   {
      row_pos = _conGetNLMember(Self, "row_pos");
      row_count = _conGetNLMember(Self, "row_count");
      return (row_count < 1 || row_count < row_pos) ? TRUE : FALSE;
   }
   // ------------------------------------------------------------------------------------------------------------------------------
   ContainerHandle _get_field_object(ContainerHandle Self, ContainerHandle con_k, DWORD col_count, ContainerHandle con_field_object)
   {
      DWORD col_pos = 0;
      return _get_field_object(Self, con_k, col_count, col_pos, con_field_object);
   }
   ContainerHandle _get_field_object(ContainerHandle Self, ContainerHandle con_k, DWORD col_count, DWORD& col_pos, ContainerHandle con_field_object)
   {
      col_pos = _get_col_position(Self, con_k, col_count);

      if (col_pos)
      {
         ContainerHandle cona_fields = _conNew(NULLCONTAINER);
         if (!con_field_object)
         {
            con_field_object = _conNew(NULLCONTAINER);
         }
         _conGetMember(Self, "fields", cona_fields);
         _conArrayGet(cona_fields, con_field_object, col_pos, 0);
         _conRelease(cona_fields); cona_fields = NULLCONTAINER;
         return con_field_object;
      }
      return NULLCONTAINER;
   }
   // ----------
   DWORD _get_col_position(ContainerHandle Self, ContainerHandle con_k, DWORD col_count)
   {
      DWORD position = 0;
      if (con_k)
      {
         DWORD type = 0;
         _conType(con_k, &type);
         switch (type & 0xFF)
         {
            case XPP_CHARACTER:
            {
               char name[128] = { 0 };
               DWORD dw = 0;
               _conGetCL(con_k, &dw, name, sizeof(name) - 1);
               if (dw)
               {
                  ContainerHandle con_field_map = _conNew(NULLCONTAINER);
                  _conGetMember(Self, "field_map", con_field_map);
                  if (_conCheckType(con_field_map, XPP_OBJECT))
                  {
                     position = (DWORD)_conMCallLong(con_field_map, "get_prop", name);
                  }
                  _conRelease(con_field_map); con_field_map = NULLCONTAINER;
               }
               break;
            }
            case XPP_NUMERIC:
            {
               _conGetNL(con_k, (LONG*)&position);
               break;
            }
         }
      }
      if (position > col_count)
      {
         position = 0;
      }
      return position;
   }
   // ------------------------------------------------------------------------------------------------------------------------------------------
   void __set_get_row_flags(TXppParamList& xpp, BOOL lOnOff, meta_pos_e meta_pos, meta_action_e meta_action, BOOL& lGhost, DWORD col_pos)
   {
      ContainerHandle Self = xpp[1]->con();
      LONG row_pos, row_count;
      lGhost = _get_row_count_pos_ghost(Self, row_pos, row_count);

      if (lGhost)
      {
         if (meta_action == meta_action_e::get)
         {
            xpp[0]->PutBool(FALSE);
         }
      }
      else
      {
         ContainerHandle cona_row_set = _conNew(NULLCONTAINER);
         _conGetMember(Self, "row_set", cona_row_set);
         switch ((int)meta_pos)
         {
            case (int)meta_pos_e::changed:
            {
               if (meta_action == meta_action_e::get) // will support only get operation here
               {
                  ContainerHandle con_change_flags = _conNew(NULLCONTAINER);
                  _conArrayGet(cona_row_set, con_change_flags, row_pos, 1, 1, 0);

                  DWORD cb_flags = 0;
                  LPSTR ps_flags = 0;
                  if (_conRLockC(con_change_flags, &ps_flags, &cb_flags) == 0)
                  {
                     if (col_pos < cb_flags)
                     {
                        xpp[0]->PutBool(ps_flags[col_pos] == '1' ? TRUE : FALSE);
                     }
                     _conUnlockC(con_change_flags);
                  }
                  ps_flags = 0;
                  _conRelease(con_change_flags); con_change_flags = NULLCONTAINER;
               }
               break;
            }
            case (int)meta_pos_e::new_row:
            case (int)meta_pos_e::deleted:
            {
               if (meta_action == meta_action_e::set)
               {
                  _conArrayPutL(cona_row_set, lOnOff, row_pos, 1, meta_pos, 0);
               }
               else
               {
                  _conArrayGet(cona_row_set, xpp[0]->con(), row_pos, 1, meta_pos, 0);
               }
               break;
            }

         }
         _conRelease(cona_row_set); cona_row_set = NULLCONTAINER;
      }
   }


   // ------------------------------------------------------------------------------------------------------------------------------------------
   void init(XppParamList pl) // init( self, col_count , row_count ) -> Self
   {
      TXppParamList xpp(pl, 3);
      ContainerHandle Self = xpp[1]->con();
      DWORD col_count = xpp[2]->GetDWord();
      DWORD row_count = xpp[3]->GetDWord();

      // --- ::row_set := array(   row_count , 2 )
      {
         ContainerHandle con_row_set = _conNewArray(2, row_count, 2);
         _conSetMember(Self, "row_set", con_row_set);
         _conRelease(con_row_set);  con_row_set = NULLCONTAINER;
      }
      // --- ::fields := Array( col_count ) 
      {
         ContainerHandle cona_fields = _conNewArray(1, col_count);
         _conSetMember(Self, "fields", cona_fields);
         _conRelease(cona_fields); cona_fields = NULLCONTAINER;
      }
      // ::field_map := _ot4xb_expando_():new
      {
         ContainerHandle cono_field_map = _conNewObj("_ot4xb_expando_", NULLCONTAINER);
         _conSetMember(Self, "field_map", cono_field_map);
         _conRelease(cono_field_map); cono_field_map = NULLCONTAINER;
      }

      // ---  ::row_pos           := 1
      {
         _conSetNLMember(Self, "row_pos", 1);
      }

      // ---  ::blank_row         := Array( col_count )
      {
         ContainerHandle cona_blank_row = _conNewArray(1, col_count);
         _conSetMember(Self, "blank_row", cona_blank_row);
         _conRelease(cona_blank_row); cona_blank_row = NULLCONTAINER;
      }
      // ---  ::xbase_row_types   := Array( col_count )
      {
         ContainerHandle cona_row_types = _conNewArray(1, col_count);
         _conSetMember(Self, "xbase_row_types", cona_row_types);
         _conRelease(cona_row_types); cona_row_types = NULLCONTAINER;
      }

      // ---  ::row_count         := row_count
      {
         _conSetNLMember(Self, "row_count", (LONG)row_count);
      }
      // ---  ::col_count         := col_count
      {
         _conSetNLMember(Self, "col_count", (LONG)col_count);
      }
      // ---  ::throw_type_error  := .T.
      {
         _conSetLMember(Self, "throw_type_error", TRUE);
      }

      // ---  ::props         := _ot4xb_expando_():new()
      {
         ContainerHandle cono_props = _conNewObj("_ot4xb_expando_", NULLCONTAINER);
         _conSetMember(Self, "props", cono_props);
         _conRelease(cono_props); cono_props = NULLCONTAINER;
      }

      // ---


      _conSetNILMember(Self, "row_map");
      _conSetNLMember(Self, "row_map_pos", 0);



      xpp[0]->Put(Self);
   }
   // ------------------------------------------------------------------------------------------------------------------------------------------
   void add_colname_alias(XppParamList pl)  // add_colname_alias( 1 Self,2 col_name,3 col_alias )
   {
      TXppParamList xpp(pl, 3);
      ContainerHandle Self = xpp[1]->con();
      BOOL result = FALSE;
      LPSTR psz_col_name = xpp[2]->LockStr();
      LPSTR psz_alias_name = xpp[3]->LockStr();
      if (psz_col_name && psz_alias_name)
      {
         ContainerHandle con_field_map = _conNew(NULLCONTAINER);
         _conGetMember(Self, "field_map", con_field_map);
         if (_conCheckType(con_field_map, XPP_OBJECT))
         {
            if (_conMCallLong(con_field_map, "get_prop", psz_alias_name) == 0) // alias_name must not already exist
            {
               DWORD position = (DWORD)_conMCallLong(con_field_map, "get_prop", psz_col_name);
               if (position) // col_name found
               {
                  _conMCallVoid(con_field_map, "set_prop", psz_alias_name, (LONG)position);
                  result = TRUE;
               }

            }
         }
         _conRelease(con_field_map); con_field_map = NULLCONTAINER;
      }
   }
   // ------------------------------------------------------------------------------------------------------------------------------------------
   void __set_field_definition(XppParamList pl)  // __set_field_definition(1 Self,2 field_object)
   {
      TXppParamList xpp(pl, 2);
      ContainerHandle Self = xpp[1]->con();
      ContainerHandle field_object = xpp[2]->con();

      if (_conCheckType(field_object, XPP_OBJECT))
      {
         LONG position = _conGetNLMember(field_object, "field_pos");
         // ------ ::field_map:set_prop(fld:name, fld:field_pos)
         if (position > 0)
         {

            ContainerHandle con_field_map = _conNew(NULLCONTAINER);
            _conGetMember(Self, "field_map", con_field_map);
            if (_conCheckType(con_field_map, XPP_OBJECT))
            {
               char name[128] = { 0 };
               _conGetCLMember(field_object, "name", name, sizeof(name) - 1);
               _conMCallVoid(con_field_map, "set_prop", name, position);
            }
            _conRelease(con_field_map); con_field_map = NULLCONTAINER;
         }
         // -------  ::fields[fld:field_pos] : = fld
         {
            ContainerHandle cona_fields = _conNew(NULLCONTAINER);
            _conGetMember(Self, "fields", cona_fields);
            _conArrayPut(cona_fields, field_object, position, 0);
            _conRelease(cona_fields); cona_fields = NULLCONTAINER;
         }
         // ------- ::blank_row[fld:field_pos] : = fld : xbase_empty_value
         {
            ContainerHandle cona_blank_row = _conNew(NULLCONTAINER);
            ContainerHandle con_empty_value = _conNew(NULLCONTAINER);
            _conGetMember(field_object, "xbase_empty_value", con_empty_value);
            _conGetMember(Self, "blank_row", cona_blank_row);
            _conArrayPut(cona_blank_row, con_empty_value, position, 0);
            _conRelease(cona_blank_row); cona_blank_row = NULLCONTAINER;
            _conRelease(con_empty_value); con_empty_value = NULLCONTAINER;
         }
         // -------  ::xbase_row_types[fld:field_pos] : = fld:xbase_type
         {
            ContainerHandle cona_xbase_row_types = _conNew(NULLCONTAINER);
            _conGetMember(Self, "xbase_row_types", cona_xbase_row_types);
            ContainerHandle con_xbase_type = _conNew(NULLCONTAINER);
            _conGetMember(field_object, "xbase_type", con_xbase_type);
            _conArrayPut(cona_xbase_row_types, con_xbase_type, position, 0);
            _conRelease(cona_xbase_row_types); cona_xbase_row_types = NULLCONTAINER;
            _conRelease(con_xbase_type); con_xbase_type = NULLCONTAINER;
         }
         // ----------
      }
   }
   // ------------------------------------------------------------------------------------------------------------------------------------------
   void __init_empty_row(XppParamList pl)  // __init_empty_row( Self ,row_pos,col_array_values  )
   {
      TXppParamList xpp(pl, 3);
      ContainerHandle Self = xpp[1]->con();
      DWORD row_pos = (DWORD)xpp[2]->GetLong();
      DWORD col_count = (DWORD)_conGetNLMember(Self, "col_count");
      ContainerHandle cona_array_values = xpp[3]->con();

      ContainerHandle cona_row_set = _conNew(NULLCONTAINER);
      _conGetMember(Self, "row_set", cona_row_set);

      // --- s:row_set[row_pos][2] := col_array_values
      _conArrayPut(cona_row_set, cona_array_values, row_pos, 2, 0);

      ContainerHandle cona_metadata = _conNewArray(1, result_rows_ns::meta_pos_e::meta_array_length);

      // -----  metadata[1] := ChrR(48,s:col_count+1)
      {
         LPSTR buffer = (LPSTR)_xgrab(col_count + 2);
         for (DWORD dw = 0; dw <= col_count; dw++) { buffer[dw] = '0'; }
         ContainerHandle con_changed_flag_string = _conPutCL(NULLCONTAINER, buffer, col_count + 1);
         _xfree((void*)buffer); buffer = 0;
         _conArrayPut(cona_metadata, con_changed_flag_string, result_rows_ns::meta_pos_e::changed, 0);
         _conRelease(con_changed_flag_string);
      }
      // -----  metadata[2] := .F. ; metadata[2] := .F. ; 
      {
         ContainerHandle con_false = _conPutL(NULLCONTAINER, FALSE);
         _conArrayPut(cona_metadata, con_false, result_rows_ns::meta_pos_e::new_row, 0);
         _conArrayPut(cona_metadata, con_false, result_rows_ns::meta_pos_e::deleted, 0);
         _conRelease(con_false); con_false = NULLCONTAINER;
      }
      // s:row_set[row_pos][1] : = __anew(ChrR(48, s:col_count + 1), .F., .F., NIL) "
      _conArrayPut(cona_row_set, cona_metadata, row_pos, 1, 0);
      _conRelease(cona_metadata); cona_metadata = NULLCONTAINER;
      _conRelease(cona_row_set); cona_row_set = NULLCONTAINER;

   }

   // ------------------------------------------------------------------------------------------------------------------------------------------
   void add_blank_row(XppParamList pl)  // add_blank_row( Self , flags)  // flags == 1 do not copy the ghost record
   {
      TXppParamList xpp(pl, 2);
      ContainerHandle Self = xpp[1]->con();
      DWORD col_count = (DWORD)_conGetNLMember(Self, "col_count");
      DWORD row_count = (DWORD)_conGetNLMember(Self, "row_count");
      DWORD flags = xpp[2]->GetDWord();

      ContainerHandle cona_row_set = _conNew(NULLCONTAINER);
      _conGetMember(Self, "row_set", cona_row_set);

      // ---- ::row_count++ ; asize( ::row_set , ::row_count ) ; ::row_set[::row_count) := Array(2)
      {
         row_count++;
         _conSetNLMember(Self, "row_count", (LONG)row_count);
         _conSetNLMember(Self, "row_pos", (LONG)row_count);
         _conResizeA(cona_row_set, row_count);
         ContainerHandle cona_pair = _conNewArray(1, 2);
         _conArrayPut(cona_row_set, cona_pair, row_count, 0);
         _conRelease(cona_pair); cona_pair = NULLCONTAINER;
      }

      // --- s:row_set[row_pos][2] := Array( col_count) 
      {
         ContainerHandle cona_array_values = _conNewArray(1, col_count);

         if (!(flags & 1))
         {
            ContainerHandle con_tmp = _conNew(NULLCONTAINER);
            ContainerHandle con_ghost = _conNew(NULLCONTAINER);
            _conGetMember(Self, "blank_row", con_ghost);
            for (DWORD fp = 1; fp <= col_count; fp++)
            {
               if (_conArrayGet(con_ghost, con_tmp, fp, 0))
               {
                  _conArrayPut(cona_array_values, con_tmp, fp, 0);
               }
            }
            _conRelease(con_ghost); con_ghost = NULLCONTAINER;
            _conRelease(con_tmp); con_tmp = NULLCONTAINER;
         }
         _conArrayPut(cona_row_set, cona_array_values, row_count, 2, 0);
         _conRelease(cona_array_values);

      }

      ContainerHandle cona_metadata = _conNewArray(1, 4);


      // -----  metadata[1] := ChrR(48,s:col_count+1)
      {
         LPSTR buffer = (LPSTR)_xgrab(col_count + 2);
         for (DWORD dw = 0; dw <= col_count; dw++) { buffer[dw] = '0'; }
         ContainerHandle con_changed_flag_string = _conPutCL(NULLCONTAINER, buffer, col_count + 1);
         _xfree((void*)buffer); buffer = 0;
         _conArrayPut(cona_metadata, con_changed_flag_string, 1, 0);
         _conRelease(con_changed_flag_string);
      }
      // -----  metadata[2] := .F. ; metadata[2] := .F. ; 
      {
         ContainerHandle con_bool = _conPutL(NULLCONTAINER, FALSE);
         _conArrayPut(cona_metadata, con_bool, meta_pos_e::deleted, 0);
         _conPutL(con_bool, TRUE);
         _conArrayPut(cona_metadata, con_bool, meta_pos_e::new_row, 0);
         _conRelease(con_bool); con_bool = NULLCONTAINER;
      }
      // s:row_set[row_pos][1] : = __anew(ChrR(48, s:col_count + 1), .F., .F., NIL) "
      _conArrayPut(cona_row_set, cona_metadata, row_count, 1, 0);
      _conRelease(cona_metadata); cona_metadata = NULLCONTAINER;

      _conRelease(cona_row_set); cona_row_set = NULLCONTAINER;
   }
   // ------------------------------------------------------------------------------------------------------------------------------------------
   void get_col_name(XppParamList pl)  // get_col_name(1 s , 2 k ) -> col_name | NIL // k = fieldpos or colum name (can be an alias ) 
   {
      TXppParamList xpp(pl, 2);
      ContainerHandle Self = xpp[1]->con();
      DWORD col_count = (DWORD)_conGetNLMember(Self, "col_count");
      ContainerHandle con_field_object = _get_field_object(Self, xpp[2]->con(), col_count);
      if (con_field_object)
      {
         _conGetMember(con_field_object, "name", xpp[0]->con());
         _conRelease(con_field_object); con_field_object = NULLCONTAINER;
      }
   }
   // ------------------------------------------------------------------------------------------------------------------------------------------
   void get_col_position(XppParamList pl)  // get_col_position(1 s , 2 k ) -> col_pos | NIL // k = fieldpos or colum name (can be an alias also ) 
   {
      TXppParamList xpp(pl, 2);
      ContainerHandle Self = xpp[1]->con();
      DWORD col_count = (DWORD)_conGetNLMember(Self, "col_count");
      DWORD col_pos = _get_col_position(Self, xpp[2]->con(), col_count);
      xpp[0]->PutDWord(col_pos);
   }
   // -----------------------------------------------------------------------------------------------------------------------------------------
   // get_col_info( s,k) ->field_object | NIL
   void get_col_info(XppParamList pl)
   {
      TXppParamList xpp(pl, 2);
      ContainerHandle Self = xpp[1]->con();

      if (xpp[2]->CheckType(XPP_NUMERIC | XPP_UNDEF) && (xpp[2]->GetLong() == 0))
      {
         _conGetMember(Self, "fields", xpp[0]->con());
      }
      else
      {
         DWORD col_count = (DWORD)_conGetNLMember(Self, "col_count");
         _get_field_object(Self, xpp[2]->con(), col_count, xpp[0]->con());
      }
   }
   // -----------------------------------------------------------------------------------------------------------------------------------------
   static void __set_pos_by_map(ContainerHandle Self, LONG & map_pos, LONG map_count, LONG* map)
   {
      LONG row_pos = 0;

      map_pos = (map_pos > map_count) ? map_pos = map_count + 1 : (map_pos < 1 ? 0 : map_pos);
      _conSetNLMember(Self, "row_map_pos", (LONG)map_pos);
      if (map_pos > 0)
      {
         LONG  row_count = _conGetNLMember(Self, "row_count");
         if (map_pos > map_count)
         {
            row_pos = row_count + 1;
         }
         else
         {
            row_pos = map[map_pos - 1];
            row_pos = (row_pos > row_count) ? row_pos = row_count + 1 : (row_pos < 1 ? 0 : row_pos);
         }
      }
      _conSetNLMember(Self, "row_pos", (LONG)row_pos);
   }

   // -----------------------------------------------------------------------------------------------------------------------------------------
   static void __go_top_or_bottom_with_map(ContainerHandle Self, ContainerHandle con_map , BOOL bTop)
   {
      DWORD cb = 0;
      LONG* map;
      if (!_conRLockC(con_map, (LPSTR*)((void*)&map), &cb))
      {
         LONG map_count = (LONG)(cb >> 2);
         LONG map_pos = ( bTop ? 1 : map_count) ;
         __set_pos_by_map(Self, map_pos, map_count, map);
         _conUnlockC(con_map); map = 0;
      }
      _conRelease(con_map);
      con_map = NULLCONTAINER;
   }

   // -----------------------------------------------------------------------------------------------------------------------------------------
   // go_top() -> NIL
   void go_top(XppParamList pl)
   {
      TXppParamList xpp(pl, 1);
      ContainerHandle Self = xpp[1]->con();
      ContainerHandle con_map = _conTMember(Self, "row_map", XPP_CHARACTER);
      if (con_map)
      {
         return __go_top_or_bottom_with_map(Self, con_map, TRUE);
      }
      else
      {
         DWORD row_count = (DWORD)_conGetNLMember(Self, "row_count");
         DWORD row_pos = (DWORD)(row_count > 0 ? 1 : 0);
         _conSetNLMember(Self, "row_pos", (LONG)row_pos);
      }
   }
   // -----------------------------------------------------------------------------------------------------------------------------------------
   // go_bottom() -> NIL
   void go_bottom(XppParamList pl)
   {
      TXppParamList xpp(pl, 1);
      ContainerHandle Self = xpp[1]->con();
      ContainerHandle con_map = _conTMember(Self, "row_map", XPP_CHARACTER);
      if (con_map)
      {
         return __go_top_or_bottom_with_map(Self, con_map, FALSE);
      }
      else
      {


         DWORD row_count = (DWORD)_conGetNLMember(Self, "row_count");
         DWORD row_pos = row_count;
         _conSetNLMember(Self, "row_pos", (LONG)row_pos);
      }
   }
   // -----------------------------------------------------------------------------------------------------------------------------------------
   static void __skip_with_map(ContainerHandle Self, LONG rows_to_skip, ContainerHandle con_map)
   {
      DWORD cb = 0;
      LONG * map;
      if (!_conRLockC(con_map, (LPSTR*)((void*)&map), &cb))
      {
         LONG map_pos = _conGetNLMember(Self, "row_map_pos");
         LONG map_count = (LONG) (cb >> 2); 
         map_pos += rows_to_skip;
         __set_pos_by_map(Self, map_pos, map_count, map);
         _conUnlockC(con_map); map = 0;
      }
      _conRelease(con_map);
      con_map = NULLCONTAINER;
   }

   // -----------------------------------------------------------------------------------------------------------------------------------------
   //  skip( rows_to_skip ) 
   void skip(XppParamList pl)
   {
      TXppParamList xpp(pl, 2);
      ContainerHandle Self = xpp[1]->con();
      LONG rows_to_skip = (xpp[2]->CheckType(XPP_NUMERIC) ? xpp[2]->GetLong() : 1);
      ContainerHandle con_map = _conTMember(Self, "row_map", XPP_CHARACTER);
      if( con_map )
      {
         return __skip_with_map(Self, rows_to_skip, con_map);
      }
      else
      {
         LONG row_count = _conGetNLMember(Self, "row_count");
         LONG row_pos = _conGetNLMember(Self, "row_pos");
         row_pos += rows_to_skip;
         row_pos = (row_pos > row_count) ? row_pos = row_count + 1 : (row_pos < 1 ? 0 : row_pos);

         _conSetNLMember(Self, "row_pos", (LONG)row_pos);
      }
   }
   // -----------------------------------------------------------------------------------------------------------------------------------------
   // set_row_pos(row_pos)
   void set_row_pos(XppParamList pl)
   {

      TXppParamList xpp(pl, 2);
      ContainerHandle Self = xpp[1]->con();
      LONG row_pos = xpp[2]->GetLong();
      LONG row_count = _conGetNLMember(Self, "row_count");
      row_pos = (row_pos > row_count) ? row_pos = row_count + 1 : (row_pos < 1 ? 0 : row_pos);
      _conSetNLMember(Self, "row_pos", (LONG)row_pos);
   }
   // -----------------------------------------------------------------------------------------------------------------------------------------
   void set_map_pos(XppParamList pl)
   {
      TXppParamList xpp(pl, 2);
      ContainerHandle Self = xpp[1]->con();
      if (xpp[2]->CheckType(XPP_NUMERIC))
      {
         LONG map_pos = xpp[2]->GetLong();
         ContainerHandle con_map = _conTMember(Self, "row_map", XPP_CHARACTER);
         if (con_map)
         {
            DWORD cb = 0;
            LONG* map = NULL;
            if (!_conRLockC(con_map, (LPSTR*)((void*)&map), &cb))
            {
               LONG map_count = (LONG)(cb >> 2);
               __set_pos_by_map(Self, map_pos, map_count, map);
               _conUnlockC(con_map); map = 0;
            }
            _conRelease(con_map);
            con_map = NULLCONTAINER;
         }
      }
   }
   // -----------------------------------------------------------------------------------------------------------------------------------------
   // escape_cell_value( s,k,@lError,@lGhost| 
   void escape_cell_value(XppParamList pl)
   {
      TXppParamList xpp(pl, 4);
      ContainerHandle con_field_object = NULLCONTAINER;
      ContainerHandle con_value = _get_current_or_ghost_cell(xpp, con_field_object);
      if (con_field_object && con_value)
      {
         ContainerHandle pcon_params[2] = { con_field_object , con_value };
         _conCallMethodPa(xpp[0]->con(), "escape_value", 2, pcon_params);
      }
      if (con_field_object)
      {
         _conRelease(con_field_object); con_field_object = NULLCONTAINER;
      }
      if (con_value)
      {
         _conRelease(con_value); con_value = NULLCONTAINER;
      }
   }
   // -----------------------------------------------------------------------------------------------------------------------------------------
   // get_cell( s,k,@lError,@lGhost| 
   void get_cell(XppParamList pl)
   {
      TXppParamList xpp(pl, 4);
      ContainerHandle con_field_object = NULLCONTAINER;
      ContainerHandle con_value = _get_current_or_ghost_cell(xpp, con_field_object);
      if (con_field_object && con_value)
      {
         ContainerHandle pcon_params[2] = { con_field_object , };
         xpp[0]->Put(con_value);
      }
      if (con_field_object)
      {
         _conRelease(con_field_object); con_field_object = NULLCONTAINER;
      }
      if (con_value)
      {
         _conRelease(con_value); con_value = NULLCONTAINER;
      }
   }
   // -----------------------------------------------------------------------------------------------------------------------------------------
   void set_cell(XppParamList pl)  // set_cell(1 s ,2 k,3 v,4 @lError,5 @lTypeError,6 @lChanged, 7@ lGhost ) -> NIL
   {
      TXppParamList xpp(pl, 7);
      ContainerHandle Self = xpp[1]->con();
      DWORD col_count = (DWORD)_conGetNLMember(Self, "col_count");
      DWORD col_pos = _get_col_position(Self, xpp[2]->con(), col_count);
      ContainerHandle con_value = xpp[3]->con();
      char ch_value_type = _xbase_numeric_type_to_xbase_char_valtype(xpp[3]->GetType());
      LONG row_pos, row_count;
      BOOL lGhost = _get_row_count_pos_ghost(Self, row_pos, row_count);
      BOOL lChanged = FALSE;

      // ---  lError := ( col_pos > s:col_count .or. col_pos < 1) 
      xpp[4]->PutBool(col_pos ? FALSE : TRUE);
      // lGhost 
      xpp[7]->PutBool(lGhost);

      if (col_pos && !lGhost) // if( (!lError) .and. ( !lGhost ) 
      {
         BOOL lStopBecauseTypeError = FALSE;
         BOOL lTypeError = FALSE;
         // -------  lTypeError !( s:xbase_row_types[n] == valtype(k))  ) "
         {
            ContainerHandle cona_xbase_row_types = _conNew(NULLCONTAINER);
            _conGetMember(Self, "xbase_row_types", cona_xbase_row_types);
            char expected_type[2] = { 0 };
            _conArrayGetCL(cona_xbase_row_types, expected_type, sizeof(expected_type), col_pos, 0);
            _conRelease(cona_xbase_row_types); cona_xbase_row_types = NULLCONTAINER;
            lTypeError = (ch_value_type == expected_type[0]) ? FALSE : TRUE;
            if (lTypeError)
            {
               lStopBecauseTypeError = _conGetLMember(Self, "throw_type_error");
            }
            xpp[5]->PutBool(lTypeError);
         }
         if (!lStopBecauseTypeError)
         {
            // ::row_set[::row_pos][2][n] : = v
            ContainerHandle cona_row_set = _conNew(NULLCONTAINER);
            _conGetMember(Self, "row_set", cona_row_set);
            _conArrayPut(cona_row_set, con_value, row_pos, 2, col_pos, 0);
            {
               ContainerHandle con_change_flags = _conNew(NULLCONTAINER);
               _conArrayGet(cona_row_set, con_change_flags, row_pos, 1, 1, 0);
               DWORD cb_flags = 0;
               LPSTR ps_flags = 0;
               if (_conWLockC(con_change_flags, &ps_flags, &cb_flags) == 0)
               {
                  if (cb_flags > col_count) // must be col_count+1
                  {
                     ps_flags[0] = ps_flags[col_pos] = '1';
                  }
                  _conUnlockC(con_change_flags);
                  _conArrayPut(cona_row_set, con_change_flags, row_pos, 1, 1, 0);
               }
               ps_flags = 0;
               _conRelease(con_change_flags); con_change_flags = NULLCONTAINER;
            }
            _conRelease(cona_row_set); cona_row_set = NULLCONTAINER;
            lChanged = TRUE;
         }
      }
   }
   // ---------------------------------------------------------------------------------------------------------------------
   // row_metadata( Self ,@lGhost )
   void row_metadata(XppParamList pl)
   {
      TXppParamList xpp(pl, 2);
      ContainerHandle Self = xpp[1]->con();
      LONG row_pos, row_count;
      BOOL lGhost = _get_row_count_pos_ghost(Self, row_pos, row_count);
      xpp[2]->PutBool(lGhost);
      if (!lGhost)
      {
         ContainerHandle cona_row_set = _conNew(NULLCONTAINER);
         _conGetMember(Self, "row_set", cona_row_set);
         _conArrayGet(cona_row_set, xpp[0]->con(), row_pos, 1, 0);
         _conRelease(cona_row_set); cona_row_set = NULLCONTAINER;
      }

   }
   // ------------------------------------------------------------------------------------------------------------------------------------------
   // row_changed( s,21k,3@lError,4@lGhost) 
   void row_changed(XppParamList pl)
   {
      TXppParamList xpp(pl, 4);
      ContainerHandle Self = xpp[1]->con();
      DWORD col_count = (DWORD)_conGetNLMember(Self, "col_count");
      DWORD col_pos = _get_col_position(Self, xpp[2]->con(), col_count);
      BOOL  lError = (col_pos || xpp[2]->CheckType(XPP_UNDEF)) ? FALSE : !(xpp[2]->CheckType(XPP_NUMERIC) && xpp[2]->GetLong() == 0);
      BOOL lGhost = 0;
      xpp[3]->PutBool(lError);
      if (!lError)
      {
         __set_get_row_flags(xpp, 0, meta_pos_e::changed, meta_action_e::get, lGhost, col_pos);
      }
      xpp[4]->PutBool(lGhost);
   }
   // ------------------------------------------------------------------------------------------------------------------------------------------
   // mark_row_to_delete( s , @lGhost ) 
   void mark_row_to_delete(XppParamList pl)
   {
      TXppParamList xpp(pl, 2);
      BOOL lGhost = 0;
      __set_get_row_flags(xpp, TRUE, meta_pos_e::deleted, meta_action_e::set, lGhost);
      xpp[2]->PutBool(lGhost);
   }
   // ------------------------------------------------------------------------------------------------------------------------------------------
   // unmark_row_to_delete( s , @lGhost ) 
   void unmark_row_to_delete(XppParamList pl)
   {
      TXppParamList xpp(pl, 2);
      BOOL lGhost = 0;
      __set_get_row_flags(xpp, FALSE, meta_pos_e::deleted, meta_action_e::set, lGhost);
      xpp[2]->PutBool(lGhost);
   }
   // ------------------------------------------------------------------------------------------------------------------------------------------
   // is_row_marked_to_delete( s , @lGhost ) 
   void is_row_marked_to_delete(XppParamList pl)
   {
      TXppParamList xpp(pl, 2);
      BOOL lGhost = 0;
      __set_get_row_flags(xpp, 0, meta_pos_e::deleted, meta_action_e::get, lGhost);
      xpp[2]->PutBool(lGhost);
   }
   // ------------------------------------------------------------------------------------------------------------------------------------------
   // is_new_row( s , @lGhost ) 
   void is_new_row(XppParamList pl)
   {
      TXppParamList xpp(pl, 2);
      BOOL lGhost = 0;
      __set_get_row_flags(xpp, 0, meta_pos_e::new_row, meta_action_e::get, lGhost);
      xpp[2]->PutBool(lGhost);
   }
   // ------------------------------------------------------------------------------------------------------------------------------------------
   // remove_row_from_rowset( s , @lGhost ) 
   void remove_row_from_rowset(XppParamList pl)
   {
      TXppParamList xpp(pl, 2);
      ContainerHandle Self = xpp[1]->con();
      LONG row_pos, row_count;
      BOOL lGhost = _get_row_count_pos_ghost(Self, row_pos, row_count);
      xpp[2]->PutBool(lGhost);
      if (!lGhost)
      {
         ContainerHandle cona_row_set = _conNew(NULLCONTAINER);
         _conGetMember(Self, "row_set", cona_row_set);
         _conArrayDelA(cona_row_set, (ULONG)row_pos);
         row_count--;
         _conSetNLMember(Self, "row_count", (LONG)row_count);
         if (row_pos > row_count)
         {
            _conSetNLMember(Self, "row_pos", (LONG)row_count);
         }
         _conRelease(cona_row_set); cona_row_set = NULLCONTAINER;
      }
   }
   // ------------------------------------------------------------------------------------------------------------------------------------------

} // end namespace 
// ------------------------------------------------------------------------------------------------------------------------------------------------------------------

