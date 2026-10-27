# mysql-class

**category:** mysql

**short:** A connection class derived from mysql4xb: remembers its parameters, reconnects when the server is gone, throws on error.

**desc:** The smallest useful extension of [mysql4xb](mysql4xb.md): `CLASS mysql FROM mysql4xb`. It ORs its own client flags into
the ones given to `new()`, swaps the result class for the `mysql_recordset` of
[mysql-recordset](mysql-recordset.md), keeps the connection parameters so `connect()` can be called
again with none, and wraps `query()`: when libmysql answers `CR_SERVER_GONE_ERROR` (2006) or `CR_SERVER_LOST`
(2013) it reconnects and retries once, and any error left becomes an Xbase++ error through `ErrorBlock()`.
`try_query()` is the same without the throw: the error code and message come back by reference.

**note:** `initclass` is required in every class derived from the mysql4xb classes, even when it does nothing.



## Source code

```xbase
#include "ot4xb.ch"
#define CR_SERVER_GONE_ERROR 2006
#define CR_SERVER_LOST       2013
//----------------------------------------------------------------------------------------------------------------------
CLASS mysql FROM  mysql4xb
   EXPORTED:
      VAR m_host
      VAR m_port
      VAR m_db
      VAR m_user
      VAR m_pwd
      VAR m_sk
      VAR m_flags

   // ------------------------------------------------------------------------------------------------------------------
   INLINE CLASS METHOD initclass() // required even if nothing to do
      
      return Self
   // ------------------------------------------------------------------------------------------------------------------
```

`new()` of the parent takes the flags: `CLIENT_REMEMBER_OPTIONS` so a reconnect keeps the options, `CLIENT_SSL`,
`CLIENT_MULTI_RESULTS` so one `query()` can run several statements. Then the result class is replaced - every
`query()` of this connection will return a `mysql_recordset` - and a property the recordset reads later, the
default name of the primary key.

```xbase
   INLINE METHOD init(flags)
      flags :=  nOr( flags , ::flag_CLIENT_REMEMBER_OPTIONS , ::flag_CLIENT_SSL , ::flag_CLIENT_MULTI_RESULTS   )
      ::mysql4xb:init(flags)
      ::m_resultset_class_object := mysql_recordset()
      ::set_prop( "default_primary_key_name" , "id" )             
      
      return Self
   //-------------------------------------------------------------------------------------------------------------------
```

Each parameter is kept in an instance variable with [__vdef()](https://www.xbwin.com/ot4xb/doc/search?k=__vdef) - the value given, or the one kept - so the
method can be called again without parameters to reconnect. The session time zone is set right after connecting.

```xbase
   INLINE METHOD  connect(host,user,pwd,db,port,sk,flags)    
       local result 
       ::m_host  := __vdef( host   , ::m_host  )
       ::m_port  := __vdef( port   , ::m_port  )
       ::m_db    := __vdef( db     , ::m_db    )
       ::m_user  := __vdef( user   , ::m_user  )
       ::m_pwd   := __vdef( pwd    , ::m_pwd   )
       ::m_sk    := __vdef( sk     , ::m_sk    )
       ::m_flags := __vdef( flags  , ::m_flags )
       result := ::mysql4xb:connect(::m_host,::m_user,::m_pwd,::m_db,::m_port,::m_sk,::m_flags)
       if result 
          ::query( "SET  @@SESSION.time_zone  = 'US/Eastern';") 
       end
       return result
   // ------------------------------------------------------------------------------------------------------------------
```

The retry: a lost or gone server is one connect and one more try; whatever error remains, `__throw()` raises it with
the code and the message of libmysql. `try_query()` below reports instead of raising.

```xbase
   INLINE METHOD query( q ,rs_co,flags)
      local rs := ::mysql4xb:query(q,rs_co,flags)
      local nError := ::last_error()
      if (nError == CR_SERVER_LOST) .or. (nError == CR_SERVER_GONE_ERROR) 
         if ::connect()
            rs := ::mysql4xb:query(q,rs_co,flags)
         end
      end       
      nError := ::last_error()
      if lAnd( nError )
        __throw(nError,::last_error_string() )
      end
      return rs
   // ------------------------------------------------------------------------------------------------------------------
INLINE METHOD try_query( q , nError,cError,rs_co)
      local rs := ::mysql4xb:query(q,rs_co)
      nError := ::last_error()
      if (nError == CR_SERVER_LOST) .or. (nError == CR_SERVER_GONE_ERROR) 
         if ::connect()
            rs := ::mysql4xb:query(q,rs_co)
         end
         nError := ::last_error()
      end              
      if lAnd( nError )
        cError  := ::last_error_string()
      end 
      return rs
   // ------------------------------------------------------------------------------------------------------------------   
ENDCLASS
```
