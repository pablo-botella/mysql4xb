# mysql_xb_last_inserted_id

`void mysql_xb_last_inserted_id( XppParamList pl )` - `( oSelf ) -> nId`

**category:** mysql/internals

**desc:** `mysql_insert_id()`, 64-bit, returned as a number; -1 without a handle.
Reached from the methods of [mysql4xb](mysql4xb.md) through `XbFpCall()`.
