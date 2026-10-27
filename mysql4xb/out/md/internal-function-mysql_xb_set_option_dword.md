# mysql_xb_set_option_dword

`void mysql_xb_set_option_dword( XppParamList pl )` - `( pMysql, nOption, nValue )`

**category:** mysql/internals

**desc:** `mysql_options()` with an unsigned int value; the C side of `set_option_dword()` and of the named methods that take a number.
Reached from the methods of [mysql4xb](mysql4xb.md) through `XbFpCall()`.
