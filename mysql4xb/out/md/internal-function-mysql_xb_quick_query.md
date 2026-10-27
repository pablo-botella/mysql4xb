# mysql_xb_quick_query

`void mysql_xb_quick_query( XppParamList pl )`

**category:** mysql/internals

**desc:** The C side of `query()`: `( pMysql, cSql, oResultSetClass, oRowsClass, oFieldClass, oSelf, nFlags )`. Runs the
statement with `mysql_real_query()` and, for each result of the call, stores it with `mysql_store_result()`, creates
the [mysql4xb_result_rows_t](mysql4xb_result_rows_t.md) (`new( nColumns, nRows )`) and the result object (`new( oRows, oSelf, cSql )`), feeds one field
descriptor per column through `__set_field_definition()`, converts every cell of every row as the table above says
and hands each row to `__init_empty_row()`. A result without rows becomes the affected rows count. With 0x1000 in
`nFlags` the results are collected in an array, otherwise the first one is returned.
