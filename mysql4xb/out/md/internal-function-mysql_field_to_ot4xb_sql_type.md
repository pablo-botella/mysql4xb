# mysql_field_to_ot4xb_sql_type

`LONG mysql_field_to_ot4xb_sql_type( MYSQL_FIELD& field )`

**category:** mysql/internals

**desc:** Maps `field.type` (with the `BLOB` flag for the string types) to the `ot4xb_sql_type` enumeration of ot4xb, the value
stored in `ot4xb_sql_type` of the field descriptor and used by `escape_value()`.
