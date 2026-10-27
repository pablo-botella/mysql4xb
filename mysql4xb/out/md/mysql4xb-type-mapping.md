# mysql4xb-type-mapping

**category:** mysql/reference

**desc:** How `query()` of [mysql4xb](mysql4xb.md) turns what libmysql returns into Xbase++ values. Every cell arrives from the
server as text; the column type (`MYSQL_TYPE_*`) decides what it becomes, and the three global flags of the DLL
(`mysql4xb_global_flags_*`) bend three of the rules. The same table decides the `xbase_type` letter and the
`xbase_empty_value` of the column's [mysql4xb_result_field_t](mysql4xb_result_field_t.md).


| MySQL type | Xbase++ value | type letter | blank value |
|---|---|---|---|
| `TINYINT` | logical, `.T.` when not 0; a number when `tiny_to_bool` is off | `L` (`N` when off) | `.F.` (0) |
| `DECIMAL`, `NEWDECIMAL` | number with the width and decimals of the column | `N` | 0 |
| `SMALLINT`, `INT`, `MEDIUMINT` | number | `N` | 0 |
| `BIGINT` | number: an integer when it fits in 32 bits with sign, a double otherwise | `N` | 0 |
| `FLOAT`, `DOUBLE` | double | `N` | 0 |
| `DATE` | date (the digits of `YYYY-MM-DD`) | `D` | empty date |
| `JSON` | the document parsed: an `_ot4xb_expando_` for an object, an array, a scalar | `J` | `""` |
| everything else | the text as received | `C` | `""` (spaces to the width for `VAR_STRING`) |


**note:** Everything else means `DATETIME`, `TIMESTAMP`, `TIME`, `YEAR`, `CHAR`, `VARCHAR`, `TEXT` and the `BLOB`s,
`ENUM`, `SET`, `BIT`, `GEOMETRY`: character strings, byte for byte as the server sent them (a `BLOB` is
binary-safe). A `DATETIME` is `"YYYY-MM-DD hh:mm:ss"` as text; the application converts it if it needs a value.

**note:** `NULL`: the blank value of the column when `null_to_empty` is on (the default), NIL when it is off. A JSON
column is decoded with the UTF-8 parser of ot4xb ([ot4xb_json_parse()](https://www.xbwin.com/ot4xb/doc/search?k=ot4xb_json_parse)), so its strings come out converted.

**note:** Multi-result: with 0x1000 in the `nFlags` of `query()` the call walks `mysql_next_result()` and returns an array
with one entry per result - a [mysql4xb_resultset_t](mysql4xb_resultset_t.md) for a result with rows, the affected rows for a statement without -
which is how a stored procedure with several `SELECT`s, or several statements in one string with
`CLIENT_MULTI_RESULTS`, come back. Without the flag only the first result is returned; the following ones,
if any, are dropped by libmysql when the next statement runs.

**note:** The value types decide what `set_cell()` accepts later: a value must have the type letter of its column, except in
a `J` column, which takes anything.
