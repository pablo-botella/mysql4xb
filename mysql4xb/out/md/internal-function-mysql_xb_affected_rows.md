# mysql_xb_affected_rows

`void mysql_xb_affected_rows( XppParamList pl )` - `( oSelf ) -> nRows`

**category:** mysql/internals

**desc:** `mysql_affected_rows()`, a 64-bit count returned as a number; -1 without a handle.
Reached from the methods of [mysql4xb](mysql4xb.md) through `XbFpCall()`.
