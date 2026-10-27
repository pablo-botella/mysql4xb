# mysql_xb_set_option_bool

`void mysql_xb_set_option_bool( XppParamList pl )` - `( pMysql, nOption, lValue )`

**category:** mysql/internals

**desc:** `mysql_options()` with a boolean (an int 0/1); the C side of `set_option_bool()` and of the named methods that take a logical.
Reached from the methods of [mysql4xb](mysql4xb.md) through `XbFpCall()`.
