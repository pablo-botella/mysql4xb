#include <mysql4xb_api.h>


/*{{begin-class}}*/
/*{{class-name_: mysql4xb_resultset_t
   | _slug_: mysql4xb_resultset_t
   | category: mysql/resultset
   | desc: What `query()` returns for a statement with rows: a result set with the API of an Xbase++ workarea - `DbGoTop()`,
     `DbSkip()`, `eof()`, `FieldGet()`, `FieldPut()`, `DbAppend()`, `DbDelete()` - and the columns as virtual instance
     variables, so `rs:name` reads the `name` column of the current row and `rs:name := "x"` writes it. The rows
     themselves live in a {{ilink: <class mysql4xb_result_rows_t> mysql4xb_result_rows_t}} (`rowset()`), which also keeps the column descriptors and, per row, the change
     flags, the new-row mark and the deleted mark that a `save()` needs. The object is a facade: every method is one
     line over the rowset.
   | note: The class object used for the results of a connection is `m_resultset_class_object` of {{ilink: <class mysql4xb> mysql4xb}}: a class
     derived from this one, set there, gives the results of every `query()` its own methods - filters, saving,
     dumping to expandos - as {{ilink: <example mysql-recordset> mysql-recordset}} does.
   | note: Two properties travel with every result: `sql`, the statement, and `mysql`, the connection object; both are
     stored in the rowset's `props` by `new()`.
   | _kw_: mysql4xb_resultset_t, resultset, recordset, rows, Class
   }}*/
_XPP_REG_FUN_(MYSQL4XB_RESULTSET_T)
{

   ContainerHandle conco = _conClsObj("MYSQL4XB_RESULTSET_T");
   if (conco == NULLCONTAINER)
   {
      TXbClass* pc = new TXbClass; pc->ClassName("MYSQL4XB_RESULTSET_T");
      /*{{|:**BEGIN CLASS  mysql4xb_resultset_t** }}*/
      pc->EXPORTED();
      /*{{|ivar_: - VAR __m__rowset__
         | desc_: The {{ilink: <class mysql4xb_result_rows_t> mysql4xb_result_rows_t}} holding the data; `rowset()` is the way to read it.
         }}*/
      pc->Var("__m__rowset__");

      // -------------------
      /*{{|method_: - `METHOD new( oRowSet, oMysql, cSql )`
         | return: Self
         | desc_: Called by `query()` with the rowset it filled, the connection and the statement; the last two go into the rowset's
           `props` as `mysql` and `sql`.
         }}*/
      pc->MethodCB("init", "{|s,rowset_object,mysql,sql| rowset_object:set_prop( 'sql' , sql ), rowset_object:set_prop( 'mysql' , mysql) , s:__m__rowset__ := rowset_object ,  s }");
      /*{{|method_: - `METHOD rowset()`
         | return: oRowSet
         | desc_: The {{ilink: <class mysql4xb_result_rows_t> mysql4xb_result_rows_t}} underneath, for what the facade does not expose: `add_colname_alias()`, `set_cell()` with its
           error flags, `row_set` itself.
         }}*/
      pc->MethodCB("rowset", "{|s| s:__m__rowset__  }");
      // -------------------
      /*{{|method_: - `METHOD DbGoTop()`
         | return: NIL
         | desc_: Row 1 (or 0 when the result is empty).
         }}*/
      pc->MethodCB("DbGoTop", "{|s|  s:__m__rowset__:go_top() }" );
      /*{{|method_: - `METHOD DbGoBottom()`
         | return: NIL
         | desc_: The last row.
         }}*/
      pc->MethodCB("DbGoBottom", "{|s|  s:__m__rowset__:go_bottom() }");
      /*{{|method_: - `METHOD DbSkip( [nRows] )`
         | return: NIL
         | desc_: Moves `nRows` (default 1, negative goes back); past the last row `eof()` is true, before the first `bof()` is.
         }}*/
      pc->MethodCB("DbSkip", "{|s,n|  s:__m__rowset__:skip(n) }");
      /*{{|method_: - `METHOD Pos( [nRow] )`
         | return: nRow
         | desc_: The current row number; with a parameter, moves there and returns it (clamped to 0 or `LastRow() + 1`).
         }}*/
      pc->MethodCB("Pos", "{|s,pos| iif( pos == NIL, s:__m__rowset__:get_row_pos() , s:__m__rowset__:set_row_pos(pos) ) }");
      /*{{|method_: - `METHOD LastRow()`
         | return: nRows
         | desc_: The number of rows.
         }}*/
      pc->MethodCB("LastRow", "{|s|  s:__m__rowset__:get_row_count() }");
      /*{{|method_: - `METHOD eof()`
         | return: lEof
         | desc_: True when the position is past the last row or before the first: on a ghost row. Reading a cell there gives
           the blank value of the column, writing is ignored.
         }}*/
      pc->MethodCB("eof", "{|s|  s:__m__rowset__:eof() }");
      /*{{|method_: - `METHOD bof()`
         | return: lBof
         | desc_: True when the position is before the first row (0).
         }}*/
      pc->MethodCB("bof", "{|s|  s:__m__rowset__:bof() }");
      /*{{|method_: - `METHOD FCount()`
         | return: nColumns
         | desc_: The number of columns.
         }}*/
      pc->MethodCB("fcount", "{|s|  s:__m__rowset__:get_col_count() }");
      /*{{|method_: - `METHOD FieldPos( cName )`
         | return: nColumn
         | desc_: The position of a column by name (or alias added with `add_colname_alias()`), 0 when there is none; a number
           is returned as it is when it is a valid position.
         }}*/
      pc->MethodCB("fieldpos", "{|s,n|  s:__m__rowset__:get_col_pos(n) }");
      /*{{|method_: - `METHOD FieldName( nColumn )`
         | return: cName
         | desc_: The name of a column by position, NIL when out of range.
         }}*/
      pc->MethodCB("fieldname", "{|s,n|  s:__m__rowset__:get_col_name(n) }");
      /*{{|method_: - `METHOD FieldGet( xColumn )`
         | return: xValue
         | desc_: The value of a column - by position or name - in the current row; the blank value on a ghost row, NIL for an
           unknown column.
         }}*/
      pc->MethodCB("fieldget", "{|s,n|  s:__m__rowset__:get_cell(n) }");
      /*{{|method_: - `METHOD GetNoIVar( cName )`
         | return: xValue
         | desc_: What makes the columns virtual instance variables: `rs:name` ends here when `name` is not a real member, and
           `rs:name := v` in `SetNoIVar( cName, xValue )`. A column named like a method or variable of the class is not
           reachable this way; use `FieldGet()`.
         }}*/
      pc->MethodCB("GetNoIVar", "{|s,n|  s:__m__rowset__:get_cell(n) }");
      pc->MethodCB("SetNoIVar", "{|s,n,v|  s:__m__rowset__:set_cell(n,v) }");
      /*{{|method_: - `METHOD FieldPut( xColumn, xValue )`
         | return: NIL
         | desc_: Writes a column of the current row and marks it changed. The value must have the Xbase++ type of the column
           (`xbase_type` of its {{ilink: <class mysql4xb_result_field_t> mysql4xb_result_field_t}}) unless the rowset's `throw_type_error` is off; a JSON column takes anything.
         }}*/
      pc->MethodCB("fieldput", "{|s,n,v|  s:__m__rowset__:set_cell(n,v) }");
      /*{{|method_: - `METHOD changed( [xColumn] )`
         | return: lChanged
         | desc_: Whether a column of the current row was written since the row was read - or, with no parameter, whether any was.
         }}*/
      pc->MethodCB("changed", "{|s,n|  s:__m__rowset__:row_changed(n) }");
      /*{{|method_: - `METHOD row_metadata()`
         | return: aMeta
         | desc_: The metadata array of the current row: `{ cChangedFlags, lNewRow, lDeleted, NIL }`, where the flags string has one
           `'0'`/`'1'` per column after a leading one for the whole row. The examples reset it after saving.
         }}*/
      pc->MethodCB("row_metadata", "{|s|  s:__m__rowset__:row_metadata() }");
      // ------
      /*{{|method_: - `METHOD DbAppend()`
         | return: NIL
         | desc_: Adds a row at the end, filled with the blank values of the columns, marked as new, and moves to it.
         }}*/
      pc->MethodCB("DbAppend", "{|s|  s:__m__rowset__:add_blank_row() }");
      /*{{|method_: - `METHOD DbDelete()`
         | return: NIL
         | desc_: Marks the current row as deleted; nothing leaves the rowset until the application decides (the examples turn the
           mark into a `DELETE` statement, then drop the row).
         }}*/
      pc->MethodCB("DbDelete", "{|s|  s:__m__rowset__:mark_row_to_delete() }");
      /*{{|method_: - `METHOD DbRecall()`
         | return: NIL
         | desc_: Removes the deleted mark.
         }}*/
      pc->MethodCB("DbRecall", "{|s|  s:__m__rowset__:unmark_row_to_delete() }");
      // ------
      /*{{|method_: - `METHOD get_field_info( [xColumn] )`
         | return: oField or aFields
         | desc_: The {{ilink: <class mysql4xb_result_field_t> mysql4xb_result_field_t}} of a column, or the array of all of them with no parameter.
         }}*/
      pc->MethodCB("get_field_info", "{|s,k|  s:__m__rowset__:get_col_info(k) }");
      // ------
      /*{{|method_: - `METHOD IsNewRow()`
         | return: lNew
         | desc_: Whether the current row was added with `DbAppend()`.
         }}*/
      pc->MethodCB("IsNewRow", "{|s|  s:__m__rowset__:is_new_row() }");
      /*{{|method_: - `METHOD deleted()`
         | return: lDeleted
         | desc_: Whether the current row carries the deleted mark.
         }}*/
      pc->MethodCB("deleted", "{|s|  s:__m__rowset__:is_row_marked_to_delete() }");
      // ------      
      /*{{|method_: - `METHOD get_prop( cKey )`
         | return: xValue
         | desc_: The properties of the result: `sql` and `mysql` from `new()`, plus whatever the application adds with
           `set_prop( cKey, xValue )`; `is_prop( cKey )` tests one.
         }}*/
      pc->MethodCB("get_prop", "{|s,k| s:__m__rowset__:props:get_prop( k) }");
      pc->MethodCB("is_prop", "{|s,k| s:__m__rowset__:is_prop( k) }");
      pc->MethodCB("set_prop", "{|s,k,v| s:__m__rowset__:set_prop( k,v) }");

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
