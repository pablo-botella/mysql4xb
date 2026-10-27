# mysql4xb

**category:** mysql/connection

**desc:** The connection object of mysql4xb: a thin Xbase++ class over the `MYSQL` handle of libmysql, created with
`mysql4xb():new()`. It keeps the class objects the queries use to build their results, the connection flags, the
result of the last `connect()` and a property bag. `connect()` opens the session, `query()` runs one statement
or several and returns the result as a [mysql4xb_resultset_t](mysql4xb_resultset_t.md) - or the number of affected rows, or an array of
both when the multi-result flag is on - the `set_option_*()` methods map `mysql_options()` one option each, and
the class-level `mysql4xb_global_flags_*()` methods switch the three conversion flags that apply to every
connection of the process.

**note:** The class is built from C++ with `TXbClass` when the DLL loads; every method is a code block that calls into
the C side with `XbFpCall()`. Deriving from it works as with any Xbase++ class - the examples do it - with one
rule: the derived class needs an `initclass` class method, even an empty one.

**note:** libmysql is initialised once per process and once per thread (`mysql_thread_init()` from `DllMain`). Each
thread creates its own `mysql4xb` object; a connection is never shared between threads.

**see-also:** [mysql4xb_resultset_t](mysql4xb_resultset_t.md) - what `query()` returns, and the recordset API over it.

**see-also:** [overview](mysql4xb-overview.md) - the four classes and how they fit together.

**example:** ```
local my := mysql4xb():new()
local rs
my:set_option_connect_timeout( 5 )
if my:connect( "127.0.0.1", "user", "secret", "test", 3306, NIL, 0 )
   rs := my:query( "SELECT id, name FROM customers ORDER BY name;" )
   while !rs:eof()
      ? rs:id, rs:name      // the columns are virtual instance variables
      rs:DbSkip()
   end
   my:close()
else
   ? my:last_error(), my:last_error_string()
end
```

**BEGIN CLASS  mysql4xb**

- VAR m_mysql - The `MYSQL*` of libmysql as a number: 0 until `new()`, back to 0 after `close()`. The C side reads it from here.
- VAR m_mysql4xb_flags - The client flags given to `new()`; `connect()` ORs them with its own `flags` parameter.
- VAR m_resultset_class_object - The class object `query()` instantiates for each result set: [mysql4xb_resultset_t](mysql4xb_resultset_t.md) by default.
  A derived class replaces it to get its own result objects (the examples do).
- VAR m_result_field_class_object - The class object of the field descriptors: [mysql4xb_result_field_t](mysql4xb_result_field_t.md).
- VAR m_result_rows_class_object - The class object of the row store: [mysql4xb_result_rows_t](mysql4xb_result_rows_t.md).
- VAR m_last_connect_result - The logical returned by the last `connect()`; NIL before the first one.
- VAR m_props - An [_ot4xb_expando_](https://www.xbwin.com/ot4xb/doc/search?k=_ot4xb_expando_) for whatever the application wants to hang on the connection; `get_prop()`,
  `is_prop()` and `set_prop()` go through it.
- `METHOD get_prop( cKey )` **return:** xValue or NIL - Reads a property of `m_props`; `is_prop( cKey )` tells whether it exists and `set_prop( cKey, xValue )` writes it.
  The three are the same calls of [_ot4xb_expando_](https://www.xbwin.com/ot4xb/doc/search?k=_ot4xb_expando_).
- `CLASS PROPERTY version` **return:** cVersion - The version of the DLL as `"maj.min.build.rev"` with three digits per part, so versions compare as strings:
  `mysql4xb():version >= "001.000.021.000"`.
- `METHOD new( [nFlags] )` **return:** Self - Creates the three class objects, the property bag and the `MYSQL` handle (`mysql_init()`); a handle from a
  previous `new()` on the same object is closed first. `nFlags` are the client flags stored in `m_mysql4xb_flags`
  (default 1, `CLIENT_LONG_PASSWORD`); see the `flag_CLIENT_*` class properties.
- `METHOD close()` **return:** NIL - Closes the connection (`mysql_close()`) and sets `m_mysql` to 0. The object can be reused with `new()`.
- `METHOD last_error()` **return:** nErrno - The error code of the last libmysql call (`mysql_errno()`): 0 when there was none, -1 without a handle.
  The `CR_*` client errors (2006 `CR_SERVER_GONE_ERROR`, 2013 `CR_SERVER_LOST`) are the ones worth a reconnect.
- `METHOD last_error_string()` **return:** cMessage - The message of the last error (`mysql_error()`), empty when there was none.
- `METHOD info()` **return:** cInfo - The information string of the last statement (`mysql_info()`): rows matched, changed, warnings, for the
  statements that produce one.
- `METHOD commit()` **return:** lOk - Commits the current transaction (`mysql_commit()`).
- `METHOD ping()` **return:** nResult - Checks the connection (`mysql_ping()`): 0 when alive, an error code otherwise, -1 without a handle. With
  `set_option_reconnect( .T. )` the ping itself reconnects.
- `METHOD rollback()` **return:** lOk - Rolls back the current transaction (`mysql_rollback()`).
- `CLASS PROPERTY flag_CLIENT_*` - The client flags of libmysql (`CLIENT_*` in `mysql.h`), one read-only class property each, to compose the
  `nFlags` of `new()` and `connect()` with `nOr()`. The ones the examples use: `flag_CLIENT_REMEMBER_OPTIONS`,
  `flag_CLIENT_SSL`, `flag_CLIENT_MULTI_RESULTS` (needed for `query()` to run several statements in one call).
- `CLASS PROPERTY flag_CLIENT_LONG_PASSWORD`
- `CLASS PROPERTY flag_CLIENT_FOUND_ROWS`
- `CLASS PROPERTY flag_CLIENT_LONG_FLAG`
- `CLASS PROPERTY flag_CLIENT_CONNECT_WITH_DB`
- `CLASS PROPERTY flag_CLIENT_NO_SCHEMA`
- `CLASS PROPERTY flag_CLIENT_COMPRESS`
- `CLASS PROPERTY flag_CLIENT_LOCAL_FILES`
- `CLASS PROPERTY flag_CLIENT_IGNORE_SPACE`
- `CLASS PROPERTY flag_CLIENT_PROTOCOL_41`
- `CLASS PROPERTY flag_CLIENT_INTERACTIVE`
- `CLASS PROPERTY flag_CLIENT_SSL`
- `CLASS PROPERTY flag_CLIENT_IGNORE_SIGPIPE`
- `CLASS PROPERTY flag_CLIENT_TRANSACTIONS`
- `CLASS PROPERTY flag_CLIENT_RESERVED`
- `CLASS PROPERTY flag_CLIENT_RESERVED2`
- `CLASS PROPERTY flag_CLIENT_MULTI_STATEMENTS`
- `CLASS PROPERTY flag_CLIENT_MULTI_RESULTS`
- `CLASS PROPERTY flag_CLIENT_PS_MULTI_RESULTS`
- `CLASS PROPERTY flag_CLIENT_PLUGIN_AUTH`
- `CLASS PROPERTY flag_CLIENT_CONNECT_ATTRS`
- `CLASS PROPERTY flag_CLIENT_PLUGIN_AUTH_LENENC_CLIENT_DATA`
- `CLASS PROPERTY flag_CLIENT_CAN_HANDLE_EXPIRED_PASSWORDS`
- `CLASS PROPERTY flag_CLIENT_SESSION_TRACK`
- `CLASS PROPERTY flag_CLIENT_DEPRECATE_EOF`
- `CLASS PROPERTY flag_CLIENT_SSL_VERIFY_SERVER_CERT`
- `CLASS PROPERTY flag_CLIENT_REMEMBER_OPTIONS`
- `CLASS METHOD mysql4xb_global_flags_set_get( nPos, [xValue] )` **return:** nValue or NIL - Reads (one parameter) or writes (two) one of the global conversion flags of the DLL, by position; the three
  methods below are the named forms. They are global: they apply to every connection of the process, and the
  three start at 1 (on). See the [type mapping](mysql4xb-type-mapping.md).
- `CLASS METHOD mysql4xb_global_flags_tiny_to_bool( [lOnOff] )` **return:** nValue - `TINYINT` columns come out as logical (`.T.`/`.F.`) when on, as numbers when off. Also decides the
  Xbase++ type the field descriptor reports for them.
- `CLASS METHOD mysql4xb_global_flags_null_to_empty( [lOnOff] )` **return:** nValue - A `NULL` cell comes out as the blank value of its type when on (empty string, 0, empty date, `.F.`), as
  NIL when off.
- `CLASS METHOD mysql4xb_global_flags_auto_truncate_values( [lOnOff] )` **return:** nValue - When on, `escape_value()` of a field truncates a character value longer than the column before quoting
  it; when off the value is passed as it is and the server decides.
- `METHOD set_option_string( nOption, cValue )` - The generic form of `mysql_options()`: `nOption` is a `mysql_option` value of `mysql.h` and the value a string;
  `set_option_dword( nOption, nValue )` and `set_option_bool( nOption, lValue )` are the same for an unsigned
  int and a boolean. The named methods below pick the option and the type for you. Options are set before
  `connect()`.
- `METHOD set_option_*( xValue )` - One method per option of `mysql_options()`, named after it, with the value type the option wants:
  `set_option_connect_timeout( 5 )`, `set_option_reconnect( .T. )`, `set_option_ssl_mode( 3 )`
  (`SSL_MODE_REQUIRED`), `set_option_set_charset_name( "utf8mb4" )`. The option each one sets:
- `METHOD set_option_connect_timeout( nValue )` - `MYSQL_OPT_CONNECT_TIMEOUT`
- `METHOD set_option_init_command( cValue )` - `MYSQL_INIT_COMMAND`
- `METHOD set_option_read_default_file( cValue )` - `MYSQL_READ_DEFAULT_FILE`
- `METHOD set_option_read_default_group( cValue )` - `MYSQL_READ_DEFAULT_GROUP`
- `METHOD set_option_set_charset_dir( cValue )` - `MYSQL_SET_CHARSET_DIR`
- `METHOD set_option_set_charset_name( cValue )` - `MYSQL_SET_CHARSET_NAME`
- `METHOD set_option_local_infile( nValue )` - `MYSQL_OPT_LOCAL_INFILE`
- `METHOD set_option_protocol( nValue )` - `MYSQL_OPT_PROTOCOL`
- `METHOD set_option_shared_memory_base_name( cValue )` - `MYSQL_SHARED_MEMORY_BASE_NAME`
- `METHOD set_option_read_timeout( nValue )` - `MYSQL_OPT_READ_TIMEOUT`
- `METHOD set_option_write_timeout( nValue )` - `MYSQL_OPT_WRITE_TIMEOUT`
- `METHOD set_option_client_ip( cValue )` - `MYSQL_SET_CLIENT_IP`
- `METHOD set_option_secure_auth( lValue )` - `MYSQL_SECURE_AUTH`
- `METHOD set_option_report_data_truncation( lValue )` - `MYSQL_REPORT_DATA_TRUNCATION`
- `METHOD set_option_reconnect( lValue )` - `MYSQL_OPT_RECONNECT`
- `METHOD set_option_ssl_verify_server_cert( lValue )` - `MYSQL_OPT_SSL_VERIFY_SERVER_CERT`
- `METHOD set_option_plugin_dir( cValue )` - `MYSQL_PLUGIN_DIR`
- `METHOD set_option_default_auth( cValue )` - `MYSQL_DEFAULT_AUTH`
- `METHOD set_option_bind( cValue )` - `MYSQL_OPT_BIND`
- `METHOD set_option_ssl_key( cValue )` - `MYSQL_OPT_SSL_KEY`
- `METHOD set_option_ssl_cert( cValue )` - `MYSQL_OPT_SSL_CERT`
- `METHOD set_option_ssl_ca( cValue )` - `MYSQL_OPT_SSL_CA`
- `METHOD set_option_ssl_capath( cValue )` - `MYSQL_OPT_SSL_CAPATH`
- `METHOD set_option_ssl_cipher( cValue )` - `MYSQL_OPT_SSL_CIPHER`
- `METHOD set_option_ssl_crl( cValue )` - `MYSQL_OPT_SSL_CRL`
- `METHOD set_option_ssl_crlpath( cValue )` - `MYSQL_OPT_SSL_CRLPATH`
- `METHOD set_option_connect_attr_delete( cValue )` - `MYSQL_OPT_CONNECT_ATTR_DELETE`
- `METHOD set_option_server_public_key( cValue )` - `MYSQL_SERVER_PUBLIC_KEY`
- `METHOD set_option_enable_cleartext_plugin( lValue )` - `MYSQL_ENABLE_CLEARTEXT_PLUGIN`
- `METHOD set_option_can_handle_expired_passwords( lValue )` - `MYSQL_OPT_CAN_HANDLE_EXPIRED_PASSWORDS`
- `METHOD set_option_ssl_enforce( lValue )` - `MYSQL_OPT_SSL_ENFORCE`
- `METHOD set_option_max_allowed_packet( nValue )` - `MYSQL_OPT_MAX_ALLOWED_PACKET`
- `METHOD set_option_net_buffer_length( nValue )` - `MYSQL_OPT_NET_BUFFER_LENGTH`
- `METHOD set_option_tls_version( cValue )` - `MYSQL_OPT_TLS_VERSION`
- `METHOD set_option_ssl_mode( nValue )` - `MYSQL_OPT_SSL_MODE`
- `METHOD set_option_get_server_public_key( lValue )` - `MYSQL_OPT_GET_SERVER_PUBLIC_KEY`
- `METHOD connect( cHost, cUser, cPassword, cDb, nPort, cUnixSocket, nFlags )` **return:** lConnected - Opens the session (`mysql_real_connect()`) with the options set so far; `nPort` 0 and `cUnixSocket` NIL take
  the defaults of libmysql, `nFlags` is ORed with the flags given to `new()`. The result is also kept in
  `m_last_connect_result`; on failure `last_error()` and `last_error_string()` say why.
- `METHOD query( cSql, [oResultSetClass], [nFlags] )` **return:** oResultSet, nAffectedRows, aResults or NIL - Runs `cSql` (`mysql_real_query()`) and stores the whole result set in memory (`mysql_store_result()`),
  converted to Xbase++ values as the [type mapping](mysql4xb-type-mapping.md) says. A statement that returns rows gives an object of
  `oResultSetClass` - `m_resultset_class_object` when omitted - built over a [mysql4xb_result_rows_t](mysql4xb_result_rows_t.md); one that returns
  none gives the affected rows as a number. With `nFlags` 0x1000 the return is an array with one entry per
  result of the call, which is how several statements in one string (`CLIENT_MULTI_RESULTS`) or a stored
  procedure with several selects come back. NIL when there is no handle or the statement failed: check
  `last_error()`.
- `METHOD field_count()` **return:** nFields - The number of columns of the last statement (`mysql_field_count()`); 0 for a statement without result set.
- `METHOD last_insert_id()` **return:** nId - The `AUTO_INCREMENT` value generated by the last `INSERT` (`mysql_insert_id()`), -1 without a handle.
- `METHOD affected_rows()` **return:** nRows - The rows changed, deleted or inserted by the last statement (`mysql_affected_rows()`), -1 without a handle.

**END CLASS**
