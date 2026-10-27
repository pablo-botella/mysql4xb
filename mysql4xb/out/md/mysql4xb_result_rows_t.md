# mysql4xb_result_rows_t

**category:** mysql/resultset

**desc:** The row store of a result: the values of every row already converted to Xbase++, the descriptors of the
columns, a name-to-position map, the current position and, per row, the metadata a later save needs. The
methods are implemented in C++ over the ot4xb container API and reached by the [mysql4xb_resultset_t](mysql4xb_resultset_t.md) facade; an
application normally talks to the facade and comes here for `add_colname_alias()`, for `set_cell()` with its
flags by reference, or to read `row_set` directly.

**note:** `row_set` is an array with one element per row, each `{ aMeta, aValues }`: `aValues` holds one value per column
in column order, `aMeta` is `{ cChangedFlags, lNewRow, lDeleted, NIL }` - the flags string has `col_count + 1`
characters, `'1'` where a cell was written, the first one for the row as a whole. `blank_row` holds the blank
value of every column and is what a new row starts with.

**note:** The ghost row: a position outside `1..row_count` (0, or `row_count + 1` after skipping past the end) is where
`eof()` is true. Reading a cell there returns the blank value of the column and sets the `lGhost` flag of the
call; writing does nothing. It is what lets a browse or a form read past the end without checking first.

**BEGIN CLASS  mysql4xb_result_rows_t**

- VAR row_set - The rows: `{ { aMeta, aValues }, ... }`, see the note above. Filled by `query()` through `__init_empty_row()`,
  grown by `add_blank_row()`, shrunk by `remove_row_from_rowset()`.
- VAR fields - One [mysql4xb_result_field_t](mysql4xb_result_field_t.md) per column, by position.
- VAR field_map - An [_ot4xb_expando_](https://www.xbwin.com/ot4xb/doc/search?k=_ot4xb_expando_) mapping every column name - and every alias - to its position, so a column can be
  named in any call. Names are matched the way the expando matches properties: case does not matter.
- VAR row_pos - The current row, 1-based; 0 or `row_count + 1` is the ghost row.
- VAR blank_row - The blank value of each column, in column order: what a `NULL` becomes when `null_to_empty` is on, what a new
  row starts with, what a read on the ghost row returns.
- VAR xbase_row_types - The Xbase++ type letter of each column, what `set_cell()` checks a value against.
- VAR row_count - The number of rows.
- VAR col_count - The number of columns.
- VAR throw_type_error - `.T.` by default: `set_cell()` refuses a value whose type is not the column's and reports it in `lTypeError`.
  With `.F.` the value is stored anyway (the examples switch it off while loading a row from an expando).
- VAR props - An [_ot4xb_expando_](https://www.xbwin.com/ot4xb/doc/search?k=_ot4xb_expando_) with the properties of the result: `sql`, `mysql`, and whatever the application adds.
- `METHOD truncate()` **return:** Self - Drops every row: `row_set` empty, `row_count` and `row_pos` 0. The columns stay.
- `METHOD new( nColumns, nRows )` **return:** Self - Creates the empty store for a result of that size - the arrays, the map, the property bag - with the position
  at 1 and `throw_type_error` on. `query()` then adds the column descriptors and the rows.
- `METHOD add_colname_alias( cColumn, cAlias )` **return:** NIL - Registers a second name for an existing column, so `cAlias` can be used wherever a column name is accepted -
  including the virtual instance variables of the facade. The alias must not exist yet.
- `METHOD __set_field_definition( oField )` **return:** NIL - Internal, called by `query()` once per column: stores the descriptor in `fields`, its name in `field_map`, its
  blank value in `blank_row` and its type letter in `xbase_row_types`.
- `METHOD __init_empty_row( nRow, aValues )` **return:** NIL - Internal, called by `query()` once per row: stores the values and a fresh metadata array (nothing changed, not
  new, not deleted).
- `METHOD add_blank_row( [nFlags] )` **return:** NIL - Appends a row and moves to it, marked as new: filled with the blank values of the columns, or left as NILs when
  `nFlags` has bit 1.
- `METHOD get_col_pos( xColumn )` **return:** nColumn - The position of a column given by name, alias or position; 0 when it does not exist.
- `METHOD get_col_name( xColumn )` **return:** cName - The name of a column given by position, name or alias; NIL when it does not exist.
- `METHOD get_col_info( [xColumn] )` **return:** oField or aFields - The [mysql4xb_result_field_t](mysql4xb_result_field_t.md) of a column, or the whole `fields` array when the parameter is 0 or omitted.
- `METHOD go_top()` **return:** NIL - Row 1, or 0 when there are no rows.
- `METHOD go_bottom()` **return:** NIL - The last row.
- `METHOD skip( [nRows] )` **return:** NIL - Moves `nRows` (default 1); the position stops at 0 going up and at `row_count + 1` going down, the two ghost
  positions.
- `METHOD set_row_pos( nRow )` **return:** NIL - Moves to a row, clamped to the same two ghost positions.
- `METHOD get_row_pos()` **return:** nRow - The current position.
- `METHOD get_row_count()` **return:** nRows - The number of rows.
- `METHOD eof()` **return:** lEof - True on either ghost position.
- `METHOD bof()` **return:** lBof - True at position 0.
- `METHOD get_col_count()` **return:** nColumns - The number of columns.
- `METHOD escape_cell_value( xColumn, [@lError], [@lGhost] )` **return:** cSqlLiteral - The value of a cell of the current row as the SQL literal for its column, through `escape_value()` of the
  column's [mysql4xb_result_field_t](mysql4xb_result_field_t.md). `lError` comes back true for an unknown column, `lGhost` when the position is a ghost row (the
  blank value is escaped then).
- `METHOD get_cell( xColumn, [@lError], [@lGhost] )` **return:** xValue - The value of a cell of the current row, by column name, alias or position; the blank value on a ghost row.
  `lError` true means the column does not exist and NIL was returned.
- `METHOD set_cell( xColumn, xValue, [@lError], [@lTypeError], [@lChanged], [@lGhost] )` **return:** NIL - Writes a cell of the current row and marks the cell and the row as changed. Nothing is written on a ghost row
  (`lGhost`), for an unknown column (`lError`), or when the type of the value is not the column's and
  `throw_type_error` is on (`lTypeError`); a JSON column accepts any type. `lChanged` reports whether the write
  happened.
- `METHOD row_metadata( [@lGhost] )` **return:** aMeta - The metadata array of the current row, `{ cChangedFlags, lNewRow, lDeleted, NIL }`, the array itself: what is
  changed in it changes the row.
- `METHOD row_changed( [xColumn], [@lError], [@lGhost] )` **return:** lChanged - Whether a column of the current row was written - or any column, with no parameter or 0 - since the row was
  read or last reset.
- `METHOD mark_row_to_delete( [@lGhost] )` **return:** NIL - Sets the deleted mark of the current row.
- `METHOD unmark_row_to_delete( [@lGhost] )` **return:** NIL - Clears it.
- `METHOD is_row_marked_to_delete( [@lGhost] )` **return:** lDeleted - Reads it; false on a ghost row.
- `METHOD is_new_row( [@lGhost] )` **return:** lNew - Whether the current row came from `add_blank_row()`; false on a ghost row.
- `METHOD remove_row_from_rowset( [@lGhost] )` **return:** NIL - Deletes the current row from `row_set` for good - the way to drop a row once its `DELETE` ran, or to discard a
  new one - and adjusts the position when it was the last.
- `METHOD get_prop( cKey )` **return:** xValue - `get_prop()`, `is_prop( cKey )` and `set_prop( cKey, xValue )` over `props`.

**END CLASS**
