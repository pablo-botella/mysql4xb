# mysql_xb_quick_query_create_field_object_container_handle

`ContainerHandle mysql_xb_quick_query_create_field_object_container_handle( MYSQL_FIELD& field, DWORD field_pos, ContainerHandle class_object )`

**category:** mysql/internals

**desc:** Instantiates the field class (`class_object`, a [mysql4xb_result_field_t](mysql4xb_result_field_t.md) or a class derived from it) and fills its instance
variables from the `MYSQL_FIELD`, plus the four derived ones: `ot4xb_sql_type`, `xbase_type`, `xbase_empty_value`,
`escape_flags` (`Truncate` when `auto_truncate_values` is on, `NotNull` when the column is).
