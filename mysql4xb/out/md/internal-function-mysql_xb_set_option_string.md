# mysql_xb_set_option_string

`void mysql_xb_set_option_string( XppParamList pl )` - `( pMysql, nOption, cValue )`

**category:** mysql/internals

**desc:** `mysql_options()` with a string; the C side of `set_option_string()` and of the named methods that take one.
Reached from the methods of [mysql4xb](mysql4xb.md) through `XbFpCall()`.
