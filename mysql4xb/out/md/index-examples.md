# mysql4xb Examples

[mysql4xb](index.md)

## Examples

- [mysql-app](mysql-app.md) - The application object around the connection: configuration from an .ini and the environment, one connection per thread, errors as Xbase++ errors. (kw: app, singleton, configuration, ini, environment, thread, tls, Example)
- [mysql-class](mysql-class.md) - A connection class derived from mysql4xb: remembers its parameters, reconnects when the server is gone, throws on error. (kw: mysql, connection, reconnect, CR_SERVER_GONE_ERROR, derived class, Example)
- [mysql-recordset](mysql-recordset.md) - A result set derived from mysql4xb_resultset_t that filters, skips deleted rows, saves its changes as SQL and dumps rows to expandos. (kw: mysql_recordset, recordset, save, INSERT, UPDATE, DELETE, filter, expando, Example)
