# mysql4xb Reference

[mysql4xb](index.md)

## Articles

- [mysql4xb-overview](mysql4xb-overview.md) - mysql4xb is a wrapper over libmysql.dll, the client library of MySQL, for Xbase++ programs, built on [ot4xb](https://www.xbwin.com/ot4xb/doc/). (kw: mysql4xb, overview, libmysql, MySQL, Xbase++, Topic)
- [mysql4xb-type-mapping](mysql4xb-type-mapping.md) - How query() of mysql4xb turns what libmysql returns into Xbase++ values. (kw: type mapping, MYSQL_TYPE, conversion, NULL, JSON, BIGINT, Topic)

## Classes

- [mysql4xb](mysql4xb.md) - The connection object of mysql4xb: a thin Xbase++ class over the MYSQL handle of libmysql, created with mysql4xb():new(). (kw: mysql4xb, mysql, connection, libmysql, Class)
- [mysql4xb_result_field_t](mysql4xb_result_field_t.md) - The descriptor of one column of a result set: what libmysql reports in its MYSQL_FIELD (names, table, lengths, flags, decimals, character set, type) plus what... (kw: mysql4xb_result_field_t, field, column, MYSQL_FIELD, Class)
- [mysql4xb_result_rows_t](mysql4xb_result_rows_t.md) - The row store of a result: the values of every row already converted to Xbase++, the descriptors of the columns, a name-to-position map, the current position... (kw: mysql4xb_result_rows_t, rowset, rows, metadata, Class)
- [mysql4xb_resultset_t](mysql4xb_resultset_t.md) - What query() returns for a statement with rows: a result set with the API of an Xbase++ workarea - DbGoTop(), DbSkip(), eof(), FieldGet(), FieldPut()... (kw: mysql4xb_resultset_t, resultset, recordset, rows, Class)

## Internals

- [mysql_field_to_ot4xb_sql_type](internal-function-mysql_field_to_ot4xb_sql_type.md) - Maps field.type (with the BLOB flag for the string types) to the ot4xb_sql_type enumeration of ot4xb, the value stored in ot4xb_sql_type of the field... (kw: mysql_field_to_ot4xb_sql_type, Internal)
- [mysql_xb_affected_rows](internal-function-mysql_xb_affected_rows.md) - mysql_affected_rows(), a 64-bit count returned as a number; -1 without a handle. (kw: mysql_xb_affected_rows, Internal)
- [mysql_xb_close](internal-function-mysql_xb_close.md) - mysql_close() and m_mysql := 0. Reached from the methods of mysql4xb through XbFpCall(). (kw: mysql_xb_close, Internal)
- [mysql_xb_commit](internal-function-mysql_xb_commit.md) - mysql_commit(). (kw: mysql_xb_commit, Internal)
- [mysql_xb_field_count](internal-function-mysql_xb_field_count.md) - mysql_field_count(); 0 without a handle. (kw: mysql_xb_field_count, Internal)
- [mysql_xb_info](internal-function-mysql_xb_info.md) - mysql_info(). (kw: mysql_xb_info, Internal)
- [mysql_xb_init](internal-function-mysql_xb_init.md) - mysql_init(): creates the handle stored in m_mysql, closing a previous one, and stores nFlags (default 1) in m_mysql4xb_flags. (kw: mysql_xb_init, Internal)
- [mysql_xb_last_error](internal-function-mysql_xb_last_error.md) - mysql_errno(), -1 without a handle. (kw: mysql_xb_last_error, Internal)
- [mysql_xb_last_error_string](internal-function-mysql_xb_last_error_string.md) - mysql_error(); "Invalid Mysql Object" without a handle. (kw: mysql_xb_last_error_string, Internal)
- [mysql_xb_last_inserted_id](internal-function-mysql_xb_last_inserted_id.md) - mysql_insert_id(), 64-bit, returned as a number; -1 without a handle. (kw: mysql_xb_last_inserted_id, Internal)
- [mysql_xb_ping](internal-function-mysql_xb_ping.md) - mysql_ping(), -1 without a handle. (kw: mysql_xb_ping, Internal)
- [mysql_xb_quick_query](internal-function-mysql_xb_quick_query.md) - The C side of query(): ( pMysql, cSql, oResultSetClass, oRowsClass, oFieldClass, oSelf, nFlags ). Runs the statement with mysql_real_query() and, for each... (kw: mysql_xb_quick_query, Internal)
- [mysql_xb_quick_query_create_field_object_container_handle](internal-function-mysql_xb_quick_query_create_field_object_container_handle.md) - Instantiates the field class (class_object, a mysql4xb_result_field_t or a class derived from it) and fills its instance variables from the MYSQL_FIELD, plus... (kw: mysql_xb_quick_query_create_field_object_container_handle, Internal)
- [mysql_xb_quick_query_sqltype_to_xbase_blank_value](internal-function-mysql_xb_quick_query_sqltype_to_xbase_blank_value.md) - Puts in con_value the blank value of a column - the blank value column of the table above - honouring tiny_to_bool; used for xbase_empty_value of the... (kw: mysql_xb_quick_query_sqltype_to_xbase_blank_value, Internal)
- [mysql_xb_quick_query_sqltype_to_xbase_type_letter](internal-function-mysql_xb_quick_query_sqltype_to_xbase_type_letter.md) - The Xbase++ type letter of a column type: L/N for TINYINT by tiny_to_bool, N, D, J, C. (kw: mysql_xb_quick_query_sqltype_to_xbase_type_letter, Internal)
- [mysql_xb_real_connect](internal-function-mysql_xb_real_connect.md) - mysql_real_connect(); a NIL string parameter is passed as a null pointer, which is how libmysql takes its defaults. (kw: mysql_xb_real_connect, Internal)
- [mysql_xb_rollback](internal-function-mysql_xb_rollback.md) - mysql_rollback(). (kw: mysql_xb_rollback, Internal)
- [mysql_xb_set_option_bool](internal-function-mysql_xb_set_option_bool.md) - mysql_options() with a boolean (an int 0/1); the C side of set_option_bool() and of the named methods that take a logical. (kw: mysql_xb_set_option_bool, Internal)
- [mysql_xb_set_option_dword](internal-function-mysql_xb_set_option_dword.md) - mysql_options() with an unsigned int value; the C side of set_option_dword() and of the named methods that take a number. (kw: mysql_xb_set_option_dword, Internal)
- [mysql_xb_set_option_string](internal-function-mysql_xb_set_option_string.md) - mysql_options() with a string; the C side of set_option_string() and of the named methods that take one. (kw: mysql_xb_set_option_string, Internal)
