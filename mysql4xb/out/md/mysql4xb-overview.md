# mysql4xb-overview

**category:** mysql/reference

**desc:** mysql4xb is a wrapper over `libmysql.dll`, the client library of MySQL, for Xbase++ programs, built on
[ot4xb](https://www.xbwin.com/ot4xb/doc/). It is one DLL, `mysql4xb.dll`, that registers four Xbase++ classes
when it loads and needs nothing else from the program: no `.ch`, no `.lib` beyond the import library, the
connection, the query and the rows are objects.

## The four classes
- [mysql4xb](mysql4xb.md) - the connection: options, `connect()`, `query()`, transactions, errors.
- [mysql4xb_resultset_t](mysql4xb_resultset_t.md) - what a query returns: a result set with the API of a workarea (`DbGoTop()`, `DbSkip()`, `eof()`,
  `FieldGet()`, `DbAppend()`, `DbDelete()`) and the columns as virtual instance variables (`rs:name`).
- [mysql4xb_result_rows_t](mysql4xb_result_rows_t.md) - the rows behind the result set: the values, the column descriptors, the position and, per row,
  the change flags and the new/deleted marks a save needs.
- [mysql4xb_result_field_t](mysql4xb_result_field_t.md) - the descriptor of a column: names, table, type, flags, and the SQL escaping of a value for it.

A query is one call: `my:query( cSql )` stores the whole result in memory, already converted to Xbase++ values
([type mapping](mysql4xb-type-mapping.md)), and returns the object; the rows are walked as a table. Writing goes back the other way: the
application composes the `INSERT`, `UPDATE` and `DELETE` statements from the rows that changed - `changed()`,
`IsNewRow()`, `deleted()` and `escape_value()` give everything needed - and runs them with `query()`. The examples
show a complete version of that.

## Global flags
Three flags of the DLL, read and written with the class methods `mysql4xb_global_flags_*()` of [mysql4xb](mysql4xb.md), apply to
every connection of the process and start on: `tiny_to_bool` (`TINYINT` as logical), `null_to_empty` (`NULL` as the
blank value of the column instead of NIL) and `auto_truncate_values` (character values cut to the column width when
escaped).

## Threads
libmysql is initialised once per process and per thread from `DllMain`, so any thread can use the library; a
connection object belongs to the thread that created it. The [mysql-app](mysql-app.md) example keeps one connection per thread
in thread-local storage.

## Extending the classes
The classes are ordinary Xbase++ classes as far as `CLASS x FROM mysql4xb` is concerned. Two things to know: the
derived class needs an `initclass` class method (an empty one will do), and the result class of a connection is
pluggable - `m_resultset_class_object` - so a derived result set gets used by every `query()` without touching the
calls. [mysql-class](mysql-class.md) and [mysql-recordset](mysql-recordset.md) do exactly that: a connection that reconnects and throws, a result set that
filters, saves and dumps to expandos.

## Building the DLL
Visual Studio, the solution `mysql4xb.sln`; `Directory.Build.props` takes the two dependencies, the MySQL client
(`MYSQL_CLI_DIR`, headers and `libmysql.lib`) and ot4xb (`OT4XB_DIR`), from environment variables, `msbuild`
properties or a git-ignored `local.props`. The Xbase++ exports are declared in `mysql4xb.xbmac` and generated into
the `.def` and `.hpp` files by ot4xb-tool before the build (`mysql4xb.ot4xb-tool`), which also produces the
`.lib` for Xbase++ and the release zips afterwards. `mysql4xb_version.h` carries the version the `version` class
property reports.
