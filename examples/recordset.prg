/*{{begin-example}}*/
/*{{example: mysql-recordset
   | _slug_: mysql-recordset
   | category: mysql
   | short: A result set derived from mysql4xb_resultset_t that filters, skips deleted rows, saves its changes as SQL and dumps rows to expandos.
   | desc: The part of a data layer that mysql4xb leaves to the application, written once:
     `CLASS mysql_recordset FROM mysql4xb_resultset_t`. It adds a filter code block and a `skip_deleted` switch that the navigation methods honour,
     `findById()`, and above all `save()`: it walks the rows, reads the metadata of each one - changed flags, new
     mark, deleted mark - and composes the `INSERT`, `UPDATE` or `DELETE` statement of that row with the column
     descriptors and `escape_cell_value()`, then runs them through the connection. Around it, the helpers a form
     needs: the current row as an array or an [_ot4xb_expando_](https://www.xbwin.com/ot4xb/doc/search?k=_ot4xb_expando_), all rows at once, a row loaded back
     from an expando, the metadata reset for the whole set, and an iterator driven by code blocks.
   | note: The statements are composed for one table: every column of the result must come from the same table, the
     primary key column must be present (`id` by default, or the `primary_key_name` property), and a changed primary
     key or auto-increment column is refused. Those are the errors `prepare_save_changes_current_row_sql()` returns.
   | note: The rows and their metadata are read straight from `row_set` of the {{ilink: <class mysql4xb_result_rows_t> mysql4xb_result_rows_t}} through the `rowset_info_pos_e`
     and `meta_pos_e` translations at the top: `{ aMeta, aValues }` per row, `aMeta` being
     `{ cChangedFlags, lNewRow, lDeleted, NIL }`.
   | _kw_: mysql_recordset, recordset, save, INSERT, UPDATE, DELETE, filter, expando, Example
   |: 
   }}*/
/*{{|: ## Source code }}*/
/*{{begin-code: xbase}}*/
#include "ot4xb.ch"
#include "types.ch"
#xtranslate rowset_info_pos_e.metadata =>  1
#xtranslate rowset_info_pos_e.data =>  2
#xtranslate meta_pos_e.changed =>  1
#xtranslate meta_pos_e.new_row =>  2
#xtranslate meta_pos_e.deleted =>  3
#xtranslate meta_pos_e.meta_array_length => 4

//----------------------------------------------------------------------------------------------------------------------
CLASS mysql_recordset FROM  mysql4xb_resultset_t
   EXPORTED:
   // ------------------------------------------------------------------------------------------------------------------
   INLINE CLASS METHOD initclass() // required even if nothing to do
      return Self
   // ------------------------------------------------------------------------------------------------------------------
   /*{{end-code}}*/
   /*{{|: `new()` of the parent stores the rowset, the connection and the statement; two properties are added on the
          rowset: `skip_deleted`, off, and `primary_key_name`, taken from the connection's `default_primary_key_name`. }}*/
   /*{{begin-code: xbase}}*/
   INLINE METHOD init(rowset_object,mysql_object,sql_cmd)
      ::mysql4xb_resultset_t:init(rowset_object,mysql_object,sql_cmd)
      ::set_prop( "skip_deleted" , .F. )
      ::set_prop( "primary_key_name"  , __vstr( mysql_object:get_prop( "default_primary_key_name" ) ,  "id" ) )
      return Self
   // ------------------------------------------------------------------------------------------------------------------
   /*{{end-code}}*/
   /*{{|: After a `save()` with refresh, the same object is re-initialised over the rowset of a fresh query, keeping its
          properties, so the references the application holds stay valid. }}*/
   /*{{begin-code: xbase}}*/
   INLINE METHOD rebuild_object(new_object)
      local rowset := new_object:rowset()
      local props  := ::rowset():props
      local sql    := new_object:get_prop("sql")
      local mysql  := new_object:get_prop("mysql")
      ::mysql4xb_resultset_t:init(rowset,mysql,sql)
      ::rowset():props := props
      return Self
   // ------------------------------------------------------------------------------------------------------------------
   /*{{end-code}}*/
   /*{{|: The filter is a code block evaluated with the recordset (`{|rs| rs:amount > 0 }`); `set_deleted( .T. )` hides the
          rows marked for deletion. `test_filter_condition()` applies both to the current row and
          `skip_to_next_valid_filter_record()` moves on, in either direction, until a row passes or the set ends; the
          three navigation methods below call it after moving, which is all a filter needs. }}*/
   /*{{begin-code: xbase}}*/
   INLINE METHOD set_filter( bFilter )
      if pcount() > 0
         ::set_prop( "filter" ,  __vblock( bFilter , NIL ) )
      end
      return ::get_prop("filter")
   // ------------------------------------------------------------------------------------------------------------------
   INLINE METHOD set_deleted( lOnOff )
      if pcount() > 0
         ::set_prop( "skip_deleted" , lAnd( lOnOff ) )
      end
      return ::get_prop( "skip_deleted" )
   // ------------------------------------------------------------------------------------------------------------------
   INLINE METHOD test_filter_condition(lSetDeleted , filter)
      DEFAULT lSetDeleted := ::get_prop( "skip_deleted" )
      DEFAULT filter  := ::get_prop("filter")

      if ::rowset():eof()
         return .F.
      end
      if lSetDeleted
         if ::rowset():is_row_marked_to_delete()
            return .F.
         end
      end
      if ::__m__filter__codeblock  != NIL
         return eval( ::__m__filter__codeblock  , Self )
      end
      return .T.
   // ------------------------------------------------------------------------------------------------------------------
   INLINE METHOD skip_to_next_valid_filter_record( lGoUp )
      local lSetDeleted := ::get_prop( "skip_deleted" )
      local filter      := ::get_prop("filter")
      local nSkip :=  iif( lAnd(lGoUp) , -1 , 1 )
      local rowset := ::rowset()
      while !rowset:eof()
         if ::test_filter_condition(lSetDeleted , filter)
            return NIL
         end
         rowset:skip(nSkip)
      end
      return NIL
   // ------------------------------------------------------------------------------------------------------------------
   INLINE METHOD DbGoTop()
       ::rowset():go_top()
       ::skip_to_next_valid_filter_record( .T. )
       return NIL
   // ------------------------------------------------------------------------------------------------------------------
   INLINE METHOD DbGoBottom()
       ::rowset():go_bottom()
       ::skip_to_next_valid_filter_record( .F. )
       return NIL
   // ------------------------------------------------------------------------------------------------------------------
   INLINE METHOD DbSkip(n)
       ::rowset():skip( n )
       ::skip_to_next_valid_filter_record( lAnd(n,0x80000000) )
       return NIL
   // ------------------------------------------------------------------------------------------------------------------
   INLINE METHOD findById(id)
       local pos := 0
       ::rowset():go_top()
       while !::rowset():eof()
         ++pos
         if (::id == id)
            return pos
         endif
         ::rowset():skip(1)
       end
       return 0
   // ------------------------------------------------------------------------------------------------------------------
   /*{{end-code}}*/
   /*{{|: `save()` runs every statement `prepare_save_changes_all_rows_sql()` composed, through the connection of the
          application (`app():get_connected_mysql()`, see {{ilink: <example mysql-app> mysql-app}}), and throws on the first
          error. With `lRefreshRowSetWithNewQuery` the original statement is run again and the object rebuilt over the new
          rows. `save_current_row()` does the same for one row and then resets its metadata: a deleted row leaves the
          rowset, a new one receives its `id` from `last_insert_id()`, the change flags go back to zeros. }}*/
   /*{{begin-code: xbase}}*/
   INLINE METHOD save( lRefreshRowSetWithNewQuery  )
      local error := NIL
      local row_pos := NIL
      local sql_array := ::prepare_save_changes_all_rows_sql(@error,@row_pos)
      local mysql, results, new_object
      local n,nn
      if error != NIL
         app():throw( error )
         return NIL
      end
      nn := len ( sql_array)
      results := array(nn,2)
      mysql := app():get_connected_mysql()

      for n := 1 to nn
         results[n][1] := sql_array[n]
         results[n][2] := mysql:query( sql_array[n] )
         if lAnd( mysql:last_error()  )
            app():throw( mysql:last_error() ,mysql:last_error_string() )
         end

      next
      if lAnd( lRefreshRowSetWithNewQuery )
         new_object := mysql:query( ::get_prop( "sql" ) )
         ::rebuild_object( new_object )
         if lAnd( mysql:last_error()  )
            app():throw( mysql:last_error() ,mysql:last_error_string() )
         end
      end
      return results
   // ------------------------------------------------------------------------------------------------------------------
   INLINE METHOD save_current_row(lResetMetaData)
      local error := NIL
      local rs,mysql, result
      local sql,meta

      sql := ::prepare_save_changes_current_row_sql(,@error)
      if error != NIL
         app():throw( error )
         return NIL
      end
      if sql == NIL
      	return NIL
      end

      DEFAULT lResetMetaData := .T.
      result := NIL
      mysql := app():get_connected_mysql()
      result := mysql:query( sql )
      if lAnd( mysql:last_error()  )
         app():throw( mysql:last_error() ,mysql:last_error_string() )
      end
      if lResetMetaData
      	rs := ::rowset()
      	if rs:is_row_marked_to_delete()
      	   rs:remove_row_from_rowset()
      	   return result
      	end
      	if rs:is_new_row()
      		rs:set_cell( "id" , mysql:query( "SELECT last_insert_id() AS id ;"):id  )
      	end
      	meta := rs:row_metadata()
      	meta[meta_pos_e.changed]  := Replicate( '0' , rs:get_col_count() + 1 )
			meta[meta_pos_e.new_row] := .F.
			meta[meta_pos_e.deleted] := .F.
      end
      return result
   // ------------------------------------------------------------------------------------------------------------------
   INLINE METHOD prepare_save_changes_all_rows_sql(error,row_pos)
      local rs := ::rowset()
      local rp := ::pos()
      local sql_array := Array(0)
      local primary_key_name := __vstr( ::get_prop( "primary_key_name" ) , "id" )
      local cc

      error := NIL
      rs:go_top()
      while !rs:eof()
          cc := ::prepare_save_changes_current_row_sql(primary_key_name,@error)
          if error != NIL
             row_pos := ::pos()
             return sql_array
          end
          if cc != NIL
             aadd( sql_array , cc )
          end
         rs:skip(1)
      end
      ::pos(rp)
      return sql_array
   // ------------------------------------------------------------------------------------------------------------------
   /*{{end-code}}*/
   /*{{|: Helpers for forms and grids: a copy of the current row appended as a new one (without its `id`), the current row
          as an array (`get_current_tuple()`, the blank row on eof), all rows as arrays, the current row dumped to an
          expando by column name and every row to an array of them, and the reverse: `set_record_from_expando()` writes
          the properties whose names are columns, all of them or only the ones that differ, with the type check of the
          rowset switched off while it does. }}*/
   /*{{begin-code: xbase}}*/
   INLINE METHOD duplicate_current_row()
   	local tuple := aclone( ::get_current_tuple() )
   	local id_pos := ::fieldpos("id")
   	if lAnd( id_pos) 
   		tuple[ id_pos ] := NIL
   	end
   	::DbAppend()
   	::rowset():row_set[ ::pos() ][ rowset_info_pos_e.data ] := tuple
   	return NIL
   // ------------------------------------------------------------------------------------------------------------------   	
   INLINE METHOD get_current_tuple()
      if ::eof()
        return ::rowset():blank_row
      end
      return __apeek( ::rowset():row_set , ::pos() , rowset_info_pos_e.data )
	//----------------------------------------------------------------------------------------------------------------------
   INLINE METHOD get_all_tuples()
   	local aa := array( len( ::rowset():row_set ) )
   	aeval( ::rowset():row_set , {|v,p| aa[p] := v[ rowset_info_pos_e.data ] } )
   	return aa
	//----------------------------------------------------------------------------------------------------------------------
   INLINE METHOD dump_record_to_expando( expando  )
      local row := ::get_current_tuple()
      DEFAULT expando := _ot4xb_expando_():new()
      aeval( row , {|v,pos| expando:set_prop( ::fieldname(pos) , v)} )
      return expando                               
      
   // ---------------------------------------------------------------------------------
   INLINE METHOD dump_all_records( expando_class  )
      local pos := ::pos()
      local result := Array(0)
      DEFAULT expando_class := _ot4xb_expando_()        
      ::DbGoTop()
      while !::eof()
      	aadd( result ,  ::dump_record_to_expando( expando_class:new()  ) )
      	::DbSkip()
      end
      ::pos(pos)
      return result

   // ------------------------------------------------------------------------------------------------------------------
   INLINE METHOD set_record_from_expando( expando  , lOnlyChanged)
      local rs := ::rowset()
      local nn := rs:get_col_count()
      local k,n,t,v,vv

      lOnlyChanged := lAnd( lOnlyChanged )

      if ::eof()
         return .F.
      end
      t := rs:throw_type_error
      rs:throw_type_error := .F.

      if lOnlyChanged
         for n := 1 to nn
            k := ::fieldname(n)
            vv := expando:get_prop( k )
            if vv != NIL
               v  := ::fieldget( n )
               if valtype(vv) == valtype(v)
                  if !(vv == v)
                     rs:set_cell(n, vv )
                  end
               else
                  rs:set_cell(n, vv )
               end
            end
         next
      else

         for n := 1 to nn
            k := ::fieldname(n)
            if expando:is_prop( k )
               rs:set_cell(n, expando:get_prop( k ) )
            end
         next
      end
      rs:throw_type_error := t
      return .T.
   // ------------------------------------------------------------------------------------------------------------------
   /*{{end-code}}*/
   /*{{|: Rewrites the metadata of every row at once, by keywords in `flags` (`"new"`, `"changed"`, `"unchanged"`,
          `"delete"`, `"undelete"`, matched with [lStrWildCmpEx()](https://www.xbwin.com/ot4xb/doc/search?k=lstrwildcmpex)) and optionally sets one or more columns
          to NIL: the way to turn a result set into a batch of inserts for another table, for instance. }}*/
   /*{{begin-code: xbase}}*/
   INLINE METHOD reset_metadata_for_entire_rowset( flags , key_to_null )
      local lDelete    := lStrWildCmpEx( "*.delete.*", flags , 1 )
      local lUnDelete    := lStrWildCmpEx( "*.undelete.*", flags , 1 )
      local lNewRecord := lStrWildCmpEx( "*.new.*", flags , 1 )
      local lChanged     := lStrWildCmpEx( "*.changed.*", flags , 1 )
      local lUnChanged   := lStrWildCmpEx( "*.unchanged.*", flags , 1 )
      local rs := ::rowset():row_set
      local change_str  := NIL
      local nn := len( rs )
      local n
      local null_array := NIL

      if nn < 1
         return .T. // no rows so nothing to do
      end


      if lNewRecord .or. lUnchanged
         change_str := Replicate( '0' , ::FCount() + 1 )
      elseif lChanged
         change_str := Replicate( '0' , ::FCount() + 1 )
      end
      if change_str != NIL
         for n := 1 to nn
            rs[n][ rowset_info_pos_e.metadata ][meta_pos_e.changed] := change_str
         next
      end

      if !empty( key_to_null )
         null_array := array(0)
         if valtype( key_to_null ) == "A"
            aeval( key_to_null , {|k,pos| pos := ::fieldpos(k) , iif( lAnd(pos) , aadd( null_array , pos ) ,) } )
         elseif valtype( key_to_null ) == "C"
            n := ::fieldpos( key_to_null )
            if lAnd(n)
               aadd( null_array , n )
            end
            if len( null_array ) > 0
               for n := 1 to nn
                  aeval( null_array , {|pos| rs[n][rowset_info_pos_e.data ][pos] := NIL } )
               next
            end
         end
      end

      if lDelete
         for n := 1 to nn
            rs[n][rowset_info_pos_e.metadata ][meta_pos_e.deleted] := .T.
         next
      end
      if lUndelete
         for n := 1 to nn
            rs[n][rowset_info_pos_e.metadata ][meta_pos_e.deleted] := .F.
         next
      end
      if lNewRecord
         for n := 1 to nn
            rs[n][rowset_info_pos_e.metadata ][meta_pos_e.new_row] := .T.
         next
      end
      return .T.
      // ---------------------------------------------------------------------------------
   /*{{end-code}}*/
   /*{{|: The heart of it. The metadata of the current row decides the statement: new and not deleted is an `INSERT` with the
          changed columns (a column with no default value must be there); deleted and not new is a `DELETE` by primary
          key; changed otherwise is an `UPDATE` of the changed columns by primary key; nothing to do returns NIL. The
          column descriptors (`get_col_info()`, one {{ilink: <class mysql4xb_result_field_t> mysql4xb_result_field_t}} each) give the table, `is_NO_DEFAULT_VALUE` and
          `is_AUTO_INCREMENT`; `escape_cell_value()` gives every value already quoted for its column. Table names go in
          backticks. }}*/
   /*{{begin-code: xbase}}*/
   INLINE METHOD prepare_save_changes_current_row_sql(primary_key_name,error)
      local rs := ::rowset()
      local primary_key  := NIL
      local fields
      local table  := NIL
      local lNewRow   := rs:is_new_row()
      local lToDelete := rs:is_row_marked_to_delete()
      local changed_flags,changed
      local fs,n,nn,fd,tb, cc
      primary_key_name  := __vstr(primary_key_name)
      DEFAULT primary_key_name := __vstr( ::get_prop( "primary_key_name" ) , "id" )

      error := NIL
      if rs:eof()
         error := "EOF"
         return NIL
      end
      changed_flags  := rs:row_metadata()[meta_pos_e.changed]
      if lNewRow .and. !lToDelete
         fields := rs:get_col_info()
         fs := Array(0)
         nn := len(fields)
         for n := 1 to nn
            fd := fields[n]
            tb := lower( fd:table )  
            if !empty(tb) 
               DEFAULT table := tb
               if !table == tb
                  error := "multiple tables not suported"
                  return NIL
               end
               changed := ( changed_flags[n+1] == '1' )
               if changed  .or. !fd:is_NO_DEFAULT_VALUE
                  if changed .and. lStrWildCmpEx( primary_key_name , fd:name , 1 )
                     error := "change primary key not supported"
                     return NIL
                  elseif fd:is_AUTO_INCREMENT .and. changed
                     error := "changed autoincrement fields not supported"
                     return NIL
                  end
                  if changed
                     aadd( fs , __anew( fd:name , rs:escape_cell_value(n) ) )
                  end
               end
            end
         next
         if empty( table )
            error := "no table"
            return NIL
         end
         cc := "INSERT INTO " + "`" + table + "` ("
         nn := len( fs )
         for n := 1 to nn
            cc += fs[n][1]  + iif( n < nn , ",","")
         next
         cc += ") VALUES ("
         for n := 1 to nn
            cc += fs[n][2]  + iif( n < nn , ",","")
         next
         cc += ");"
         return cc
      elseif lToDelete .and. !lNewRow
         fields := rs:get_col_info()
         fs := Array(0)
         nn := len(fields)
         for n := 1 to nn
            fd := fields[n]
            tb := lower( fd:table )    
            if !empty(tb) 
               DEFAULT table := tb
               if !table == tb
                  error := "multiple tables not suported"
                  return NIL
               end
            end
         next
         if empty( table )
            error := "no table"
            return NIL
         end
         primary_key  := rs:get_cell( primary_key_name )
         if primary_key == NIL
            error := "primary key is required to delete a record"
            return NIL
         end

         cc := "DELETE FROM  " + "`" + table + "` WHERE `" + primary_key_name + "`=" + rs:escape_cell_value(primary_key_name) + ";"
         return cc
      elseif changed_flags[1] == '1'
         primary_key := rs:get_cell( primary_key_name )
         if primary_key == NIL
            error := "primary key  is required to update  a record"
            return NIL
         end

         fields := rs:get_col_info()
         fs := Array(0)
         nn := len(fields)
         for n := 1 to nn
            fd := fields[n]
            tb := lower( fd:table )
            if !empty(tb) 
               DEFAULT table := tb
               if !table == tb
                  error := "multiple tables not suported"
                  return NIL
               end
               changed := ( changed_flags[n+1] == '1' )
               if changed  .or. !fd:is_NO_DEFAULT_VALUE
                  if changed .and. lStrWildCmpEx( primary_key_name , fd:name , 1 )
                     error := "change primary key  not supported"
                     return NIL
                  elseif fd:is_AUTO_INCREMENT .and. changed
                     error := "changed autoincrement fields not supported"
                     return NIL
                  end
                  if changed
                     aadd( fs , __anew( fd:name , rs:escape_cell_value(n) ) )
                  end
               end
            end
         next
         if empty( table )
            error := "no table"
            return NIL
         end
         cc := "UPDATE " + "`" + table + "` SET "
         nn := len( fs )
         for n := 1 to nn
            cc += ' ' + fs[n][1] + ' = ' + fs[n][2]
            cc += iif( n < nn , ",","")
         next
         cc += " WHERE `" + primary_key_name + "`=" + rs:escape_cell_value(primary_key_name) + ";"
         return cc
      end
      return NIL
   // ------------------------------------------------------------------------------------------------------------------
   /*{{end-code}}*/
   /*{{|: An iterator: `cb` is evaluated for every row that passes `ctx:bFor` while `ctx:bWhile` holds, with the recordset, the
          cargo by reference and a context expando the `settings` block can prepare; `nStep` rows at a time. }}*/
   /*{{begin-code: xbase}}*/
   INLINE METHOD iterate_cb(cb,cargo,settings)
   	local ctx := _ot4xb_expando_():new()
   	local bFor,bWhile,nStep
   	ctx:bWhile := {|rs| !rs:eof() }
   	if valtype(settings) == "B"
   		eval( settings , Self , ctx )
   	end
   	cb     := __vmask( XPP_BLOCK , cb , {|| NIL } )
   	bFor   := __vmask( XPP_BLOCK , ctx:bFor , {|| .T. } )
   	bWhile := __vmask( XPP_BLOCK , ctx:bWhile , {|| !::eof() } )
   	nStep  := nOr( __vmask( XPP_NUMERIC , 1 ) )
   	if !lAnd(nStep)
   		nStep := 1
   	end
   	while eval( bWhile , Self, @cargo , ctx)
   		if eval( bFor , Self, @cargo , ctx)
   			eval( cb , Self, @cargo , ctx )
   		end
   		::DbSkip( nStep )
   	end
   	return ctx
	//----------------------------------------------------------------------------------------------------------------------
ENDCLASS     
/*{{end-code}}*/
/*{{end-example}}*/
