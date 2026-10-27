# mysql4xb_result_field_t

**category:** mysql/resultset

**desc:** The descriptor of one column of a result set: what libmysql reports in its `MYSQL_FIELD` (names, table,
lengths, flags, decimals, character set, type) plus what mysql4xb derives from it - the ot4xb SQL type, the
Xbase++ type letter, the blank value of the column and the escape flags. `query()` builds one per column and
hands it to the [mysql4xb_result_rows_t](mysql4xb_result_rows_t.md), which keeps them in `fields` and returns them from `get_col_info()`.

**note:** The `is_*` properties read the bits of `flags` (`NOT_NULL_FLAG`, `PRI_KEY_FLAG`, ... of `mysql.h`); the
examples use `is_AUTO_INCREMENT` and `is_NO_DEFAULT_VALUE` to decide what an `INSERT` must carry.

**see-also:** [type mapping](mysql4xb-type-mapping.md) - how `type` becomes `xbase_type` and `xbase_empty_value`.

**BEGIN CLASS  mysql4xb_result_field_t**

- VAR field_pos - Position of the column in the result, 1-based.
- VAR name - Name of the column as the result shows it: the alias when the statement gave one.
- VAR org_name - Original name of the column in its table.
- VAR table - Name of the table the column belongs to (the alias of the table when the statement gave one); empty for a
  computed column. The examples require every column of a result to come from the same table to save it.
- VAR db - Database of the table.
- VAR catalog - Catalog of the table (always `def` in MySQL).
- VAR length - Width of the column as defined in the table, in bytes.
- VAR max_length - Widest value present in this result.
- VAR flags - The `*_FLAG` bits of `mysql.h`; the `is_*` properties read them one by one.
- VAR decimals - Number of decimals of a numeric column.
- VAR charsetnr - Character set number of the column.
- VAR type - The `enum_field_types` value of libmysql (`MYSQL_TYPE_LONG`, `MYSQL_TYPE_VARCHAR`, ...).
- VAR ot4xb_sql_type - The type translated to the `ot4xb_sql_type` enumeration of ot4xb ([ot4xb_get_sql_type_enum()](https://www.xbwin.com/ot4xb/doc/search?k=ot4xb_get_sql_type_enum)), which is what `escape_value()` needs.
- VAR xbase_type - The Xbase++ type the cells of this column carry, as a letter: `C`, `N`, `D`, `L`, or `J` for a JSON column,
  whose cells hold whatever the document parsed to. `set_cell()` checks a new value against it.
- VAR xbase_empty_value - The blank value of the column in Xbase++ terms: the empty string, 0, an empty date, `.F.`; a `NULL` cell gets
  it when `mysql4xb_global_flags_null_to_empty` is on, and a new row starts with it in every column.
- VAR escape_flags - The `ot4xb_sql_type_flag` bits `escape_value()` passes on: `Truncate` when the global flag
  `auto_truncate_values` is on, `NotNull` when the column is `NOT NULL`.
- `PROPERTY is_*` **return:** lSet - One read-only logical per flag bit of the column:
- `PROPERTY is_NOT_NULL` - `NOT_NULL_FLAG`
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
- `METHOD escape_value( xValue )` **return:** cSqlLiteral - Turns an Xbase++ value into the SQL literal for this column - quoted and escaped for a string, formatted with
  the decimals of the column for a number, `NULL` when allowed - through [ot4xb_sql_dump_value_ansi()](https://www.xbwin.com/ot4xb/doc/search?k=ot4xb_sql_dump_value_ansi) of ot4xb, with
  `ot4xb_sql_type`, `length`, `decimals` and `escape_flags` as the rules. It is what the examples use to compose
  their `INSERT` and `UPDATE` statements.
- `METHOD new()` **return:** Self - Does nothing: `query()` fills the instance variables right after creating the object.

**END CLASS**
