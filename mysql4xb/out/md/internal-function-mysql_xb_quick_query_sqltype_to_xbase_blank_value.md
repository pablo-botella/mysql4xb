# mysql_xb_quick_query_sqltype_to_xbase_blank_value

`ContainerHandle mysql_xb_quick_query_sqltype_to_xbase_blank_value( ContainerHandle con_value, MYSQL_FIELD& field )`

**category:** mysql/internals

**desc:** Puts in `con_value` the blank value of a column - the `blank value` column of the table above - honouring
`tiny_to_bool`; used for `xbase_empty_value` of the descriptor and for `NULL` cells when `null_to_empty` is on.
