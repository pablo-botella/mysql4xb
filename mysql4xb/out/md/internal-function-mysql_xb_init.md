# mysql_xb_init

`void mysql_xb_init( XppParamList pl )` - `( oSelf, [nFlags] ) -> oSelf`

**category:** mysql/internals

**desc:** `mysql_init()`: creates the handle stored in `m_mysql`, closing a previous one, and stores `nFlags` (default 1) in
`m_mysql4xb_flags`. The C side of `new()`.
Reached from the methods of [mysql4xb](mysql4xb.md) through `XbFpCall()`.
