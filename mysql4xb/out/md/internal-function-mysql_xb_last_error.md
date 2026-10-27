# mysql_xb_last_error

`void mysql_xb_last_error( XppParamList pl )` - `( oSelf ) -> nErrno`

**category:** mysql/internals

**desc:** `mysql_errno()`, -1 without a handle.
Reached from the methods of [mysql4xb](mysql4xb.md) through `XbFpCall()`.
