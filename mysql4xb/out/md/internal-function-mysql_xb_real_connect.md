# mysql_xb_real_connect

`void mysql_xb_real_connect( XppParamList pl )` - `( pMysql, cHost, cUser, cPassword, cDb, nPort, cUnixSocket, nFlags ) -> lOk`

**category:** mysql/internals

**desc:** `mysql_real_connect()`; a NIL string parameter is passed as a null pointer, which is how libmysql takes its defaults.
Reached from the methods of [mysql4xb](mysql4xb.md) through `XbFpCall()`.
