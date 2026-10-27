# mysql4xb_resultset_t

**category:** mysql/resultset

**desc:** What `query()` returns for a statement with rows: a result set with the API of an Xbase++ workarea - `DbGoTop()`,
`DbSkip()`, `eof()`, `FieldGet()`, `FieldPut()`, `DbAppend()`, `DbDelete()` - and the columns as virtual instance
variables, so `rs:name` reads the `name` column of the current row and `rs:name := "x"` writes it. The rows
themselves live in a [mysql4xb_result_rows_t](mysql4xb_result_rows_t.md) (`rowset()`), which also keeps the column descriptors and, per row, the change
flags, the new-row mark and the deleted mark that a `save()` needs. The object is a facade: every method is one
line over the rowset.

**note:** The class object used for the results of a connection is `m_resultset_class_object` of [mysql4xb](mysql4xb.md): a class
derived from this one, set there, gives the results of every `query()` its own methods - filters, saving,
dumping to expandos - as [mysql-recordset](mysql-recordset.md) does.

**note:** Two properties travel with every result: `sql`, the statement, and `mysql`, the connection object; both are
stored in the rowset's `props` by `new()`.

**BEGIN CLASS  mysql4xb_resultset_t**

- VAR __m__rowset__ - The [mysql4xb_result_rows_t](mysql4xb_result_rows_t.md) holding the data; `rowset()` is the way to read it.
- `METHOD new( oRowSet, oMysql, cSql )` **return:** Self - Called by `query()` with the rowset it filled, the connection and the statement; the last two go into the rowset's
  `props` as `mysql` and `sql`.
- `METHOD rowset()` **return:** oRowSet - The [mysql4xb_result_rows_t](mysql4xb_result_rows_t.md) underneath, for what the facade does not expose: `add_colname_alias()`, `set_cell()` with its
  error flags, `row_set` itself.
- `METHOD DbGoTop()` **return:** NIL - Row 1 (or 0 when the result is empty).
- `METHOD DbGoBottom()` **return:** NIL - The last row.
- `METHOD DbSkip( [nRows] )` **return:** NIL - Moves `nRows` (default 1, negative goes back); past the last row `eof()` is true, before the first `bof()` is.
- `METHOD Pos( [nRow] )` **return:** nRow - The current row number; with a parameter, moves there and returns it (clamped to 0 or `LastRow() + 1`).
- `METHOD LastRow()` **return:** nRows - The number of rows.
- `METHOD eof()` **return:** lEof - True when the position is past the last row or before the first: on a ghost row. Reading a cell there gives
  the blank value of the column, writing is ignored.
- `METHOD bof()` **return:** lBof - True when the position is before the first row (0).
- `METHOD FCount()` **return:** nColumns - The number of columns.
- `METHOD FieldPos( cName )` **return:** nColumn - The position of a column by name (or alias added with `add_colname_alias()`), 0 when there is none; a number
  is returned as it is when it is a valid position.
- `METHOD FieldName( nColumn )` **return:** cName - The name of a column by position, NIL when out of range.
- `METHOD FieldGet( xColumn )` **return:** xValue - The value of a column - by position or name - in the current row; the blank value on a ghost row, NIL for an
  unknown column.
- `METHOD GetNoIVar( cName )` **return:** xValue - What makes the columns virtual instance variables: `rs:name` ends here when `name` is not a real member, and
  `rs:name := v` in `SetNoIVar( cName, xValue )`. A column named like a method or variable of the class is not
  reachable this way; use `FieldGet()`.
- `METHOD FieldPut( xColumn, xValue )` **return:** NIL - Writes a column of the current row and marks it changed. The value must have the Xbase++ type of the column
  (`xbase_type` of its [mysql4xb_result_field_t](mysql4xb_result_field_t.md)) unless the rowset's `throw_type_error` is off; a JSON column takes anything.
- `METHOD changed( [xColumn] )` **return:** lChanged - Whether a column of the current row was written since the row was read - or, with no parameter, whether any was.
- `METHOD row_metadata()` **return:** aMeta - The metadata array of the current row: `{ cChangedFlags, lNewRow, lDeleted, NIL }`, where the flags string has one
  `'0'`/`'1'` per column after a leading one for the whole row. The examples reset it after saving.
- `METHOD DbAppend()` **return:** NIL - Adds a row at the end, filled with the blank values of the columns, marked as new, and moves to it.
- `METHOD DbDelete()` **return:** NIL - Marks the current row as deleted; nothing leaves the rowset until the application decides (the examples turn the
  mark into a `DELETE` statement, then drop the row).
- `METHOD DbRecall()` **return:** NIL - Removes the deleted mark.
- `METHOD get_field_info( [xColumn] )` **return:** oField or aFields - The [mysql4xb_result_field_t](mysql4xb_result_field_t.md) of a column, or the array of all of them with no parameter.
- `METHOD IsNewRow()` **return:** lNew - Whether the current row was added with `DbAppend()`.
- `METHOD deleted()` **return:** lDeleted - Whether the current row carries the deleted mark.
- `METHOD get_prop( cKey )` **return:** xValue - The properties of the result: `sql` and `mysql` from `new()`, plus whatever the application adds with
  `set_prop( cKey, xValue )`; `is_prop( cKey )` tests one.

**END CLASS**
