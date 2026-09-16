#include <mysql4xb_api.h>

//----------------------------------------------------------------------------------------------------------------------
/*{{begin-class}}*/
/*{{class-name_: mysql4xb_result_field_t
   | _slug_: mysql4xb_result_field_t
   | category: mysql/resultset
   | desc: The descriptor of one column of a result set: what libmysql reports in its `MYSQL_FIELD` (names, table,
     lengths, flags, decimals, character set, type) plus what mysql4xb derives from it - the ot4xb SQL type, the
     Xbase++ type letter, the blank value of the column and the escape flags. `query()` builds one per column and
     hands it to the {{ilink: <class mysql4xb_result_rows_t> mysql4xb_result_rows_t}}, which keeps them in `fields` and returns them from `get_col_info()`.
   | note: The `is_*` properties read the bits of `flags` (`NOT_NULL_FLAG`, `PRI_KEY_FLAG`, ... of `mysql.h`); the
     examples use `is_AUTO_INCREMENT` and `is_NO_DEFAULT_VALUE` to decide what an `INSERT` must carry.
   | see-also: {{ilink: <topic mysql4xb-type-mapping> type mapping}} - how `type` becomes `xbase_type` and `xbase_empty_value`.
   | _kw_: mysql4xb_result_field_t, field, column, MYSQL_FIELD, Class
   }}*/
_XPP_REG_FUN_(MYSQL4XB_RESULT_FIELD_T)
{

   ContainerHandle conco = _conClsObj("MYSQL4XB_RESULT_FIELD_T");
   if (conco == NULLCONTAINER)
   {
      TXbClass* pc = new TXbClass; pc->ClassName("MYSQL4XB_RESULT_FIELD_T");
      /*{{|:**BEGIN CLASS  mysql4xb_result_field_t** }}*/
      pc->EXPORTED();
      /*{{|ivar_: - VAR field_pos
         | desc_: Position of the column in the result, 1-based.
         }}*/
      pc->Var("field_pos");
      /*{{|ivar_: - VAR name
         | desc_: Name of the column as the result shows it: the alias when the statement gave one.
         }}*/
      pc->Var("name");
      /*{{|ivar_: - VAR org_name
         | desc_: Original name of the column in its table.
         }}*/
      pc->Var("org_name");
      /*{{|ivar_: - VAR table
         | desc_: Name of the table the column belongs to (the alias of the table when the statement gave one); empty for a
           computed column. The examples require every column of a result to come from the same table to save it.
         }}*/
      pc->Var("table");
      /*{{|ivar_: - VAR db
         | desc_: Database of the table.
         }}*/
      pc->Var("db");
      /*{{|ivar_: - VAR catalog
         | desc_: Catalog of the table (always `def` in MySQL).
         }}*/
      pc->Var("catalog");
      /*{{|ivar_: - VAR length
         | desc_: Width of the column as defined in the table, in bytes.
         }}*/
      pc->Var("length");
      /*{{|ivar_: - VAR max_length
         | desc_: Widest value present in this result.
         }}*/
      pc->Var("max_length");
      /*{{|ivar_: - VAR flags
         | desc_: The `*_FLAG` bits of `mysql.h`; the `is_*` properties read them one by one.
         }}*/
      pc->Var("flags");
      /*{{|ivar_: - VAR decimals
         | desc_: Number of decimals of a numeric column.
         }}*/
      pc->Var("decimals");
      /*{{|ivar_: - VAR charsetnr
         | desc_: Character set number of the column.
         }}*/
      pc->Var("charsetnr");
      /*{{|ivar_: - VAR type
         | desc_: The `enum_field_types` value of libmysql (`MYSQL_TYPE_LONG`, `MYSQL_TYPE_VARCHAR`, ...).
         }}*/
      pc->Var("type");
      /*{{|ivar_: - VAR ot4xb_sql_type
         | desc_: The type translated to the `ot4xb_sql_type` enumeration of ot4xb ([ot4xb_get_sql_type_enum()](https://www.xbwin.com/ot4xb/doc/search?k=ot4xb_get_sql_type_enum)), which is what `escape_value()` needs.
         }}*/
      pc->Var("ot4xb_sql_type");
      /*{{|ivar_: - VAR xbase_type
         | desc_: The Xbase++ type the cells of this column carry, as a letter: `C`, `N`, `D`, `L`, or `J` for a JSON column,
           whose cells hold whatever the document parsed to. `set_cell()` checks a new value against it.
         }}*/
      pc->Var("xbase_type");
      /*{{|ivar_: - VAR xbase_empty_value
         | desc_: The blank value of the column in Xbase++ terms: the empty string, 0, an empty date, `.F.`; a `NULL` cell gets
           it when `mysql4xb_global_flags_null_to_empty` is on, and a new row starts with it in every column.
         }}*/
      pc->Var("xbase_empty_value");
      /*{{|ivar_: - VAR escape_flags
         | desc_: The `ot4xb_sql_type_flag` bits `escape_value()` passes on: `Truncate` when the global flag
           `auto_truncate_values` is on, `NotNull` when the column is `NOT NULL`.
         }}*/
      pc->Var("escape_flags");

      /*{{|property_: - `PROPERTY is_*`
         | return: lSet
         | desc_: One read-only logical per flag bit of the column:
         | list_: - `PROPERTY is_NOT_NULL` - `NOT_NULL_FLAG`
           - `PROPERTY is_PRI_KEY` - `PRI_KEY_FLAG`
           - `PROPERTY is_UNIQUE_KEY` - `UNIQUE_KEY_FLAG`
           - `PROPERTY is_MULTIPLE_KEY` - `MULTIPLE_KEY_FLAG`
           - `PROPERTY is_BLOB` - `BLOB_FLAG`
           - `PROPERTY is_UNSIGNED` - `UNSIGNED_FLAG`
           - `PROPERTY is_ZEROFILL` - `ZEROFILL_FLAG`
           - `PROPERTY is_BINARY` - `BINARY_FLAG`
           - `PROPERTY is_ENUM` - `ENUM_FLAG`
           - `PROPERTY is_AUTO_INCREMENT` - `AUTO_INCREMENT_FLAG`
           - `PROPERTY is_TIMESTAMP` - `TIMESTAMP_FLAG`
           - `PROPERTY is_SET` - `SET_FLAG`
           - `PROPERTY is_NO_DEFAULT_VALUE` - `NO_DEFAULT_VALUE_FLAG`
         }}*/
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
      /*{{|method_: - `METHOD escape_value( xValue )`
         | return: cSqlLiteral
         | desc_: Turns an Xbase++ value into the SQL literal for this column - quoted and escaped for a string, formatted with
           the decimals of the column for a number, `NULL` when allowed - through [ot4xb_sql_dump_value_ansi()](https://www.xbwin.com/ot4xb/doc/search?k=ot4xb_sql_dump_value_ansi) of ot4xb, with
           `ot4xb_sql_type`, `length`, `decimals` and `escape_flags` as the rules. It is what the examples use to compose
           their `INSERT` and `UPDATE` statements.
         }}*/
      pc->MethodCB("escape_value", "{|s,v| ot4xb_sql_dump_value_ansi(v,s:ot4xb_sql_type,s:length,s:decimals,s:escape_flags ) }");
      // -------------------
      /*{{|method_: - `METHOD new()`
         | return: Self
         | desc_: Does nothing: `query()` fills the instance variables right after creating the object.
         }}*/
      pc->MethodCB("init", "{|s| s }");
      // -------------------
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
// ----------------------------------------------------------------------------------------------------------------------------------------
