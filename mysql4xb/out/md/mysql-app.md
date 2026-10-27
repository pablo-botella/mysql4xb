# mysql-app

**category:** mysql

**short:** The application object around the connection: configuration from an .ini and the environment, one connection per thread, errors as Xbase++ errors.

**desc:** The glue the other two examples rely on: `app()` is a singleton that reads the MySQL parameters from an `.ini`
next to a configuration folder named by an environment variable, with the environment as fallback, and hands out
a connected connection per thread - `get_connected_mysql()` creates it in thread-local storage the first time,
and afterwards pings it and reconnects when the ping fails. `query()` and `try_query()` go through that
connection, `get_empty_recordset()` returns a result set with the columns of a table and no rows
(a `SELECT ... LIMIT 0`), the starting point to insert. `throw()` raises an Xbase++ error from a code and a message, or
re-raises an error object.

**note:** This file is an extract of a real application: the class is `ao_app_t` and the connection it creates is
`ao_mysql()`, while `app()` instantiates `app_t()` - the names of the application it came from. Read it for the
pattern; to run it, make the three names agree (`app_t` and `ao_app_t`, `ao_mysql` and the `mysql` class of
[mysql-class](mysql-class.md)).

**note:** `tls()` is the thread-local expando of ot4xb: a property set on it in one thread is not seen by another,
which is exactly what a libmysql connection needs.



## Source code

```xbase
#include "ot4xb.ch"
#include "types.ch"
//----------------------------------------------------------------------------------------------------------------------
static ini_file_name := NIL
static config_folder_env_name := NIL 
static data_folder_env_name := NIL  
//----------------------------------------------------------------------------------------------------------------------
#xcommand __assert(<exp>) => ;
if empty(<exp>) ;
;   __throw( -1 , "Assertion Failed: " + <(exp)> ) ;
;end
//----------------------------------------------------------------------------------------------------------------------
#xcommand __assert(<exp> , <params,...> ) => ;
if empty(<exp>) ;
;   __throw(<params>) ;
;end
//----------------------------------------------------------------------------------------------------------------------
```

The singleton: created once, initialised once, and the version of the DLL checked once - `mysql4xb():version` is a
string built to compare as one. `__assert()` above turns a false expression into an error with `__throw()`.

```xbase
function app()     // singleton
   static app := NIL
   if app == NIL
      app := app_t():new()
      app:init_instance()  
      __assert( (mysql4xb():version >= "001.000.010.000" ) , "mysql4xb Version 1.0.10.0 or newer required" ) 
   end
   return app

//----------------------------------------------------------------------------------------------------------------------
static CLASS  ao_app_t
   EXPORTED:
      // ---------------------------------------------------------------------------------
      VAR ini                   READONLY
      VAR env                   READONLY
      VAR config_folder
      VAR data_folder
      VAR m_mysql_host
      VAR m_mysql_port
      VAR m_mysql_db
      VAR m_mysql_user
      VAR m_mysql_pwd

      // ---------------------------------------------------------------------------------
      INLINE METHOD init   
         return Self
```

Configuration: an [_ot4xb_expando_](https://www.xbwin.com/ot4xb/doc/search?k=_ot4xb_expando_) loaded with the environment (`add_env_strings()`) and another with the
`.ini` (`add_ini_string()`), the file named after the executable ([cPathChangeExt()](https://www.xbwin.com/ot4xb/doc/search?k=cpathchangeext),
[cPathGetFileName()](https://www.xbwin.com/ot4xb/doc/search?k=cpathgetfilename), [AppName()](https://www.xbwin.com/ot4xb/doc/search?k=appname)) in the folder the `<app>_CONFIG_FOLDER` variable
points to. Each MySQL parameter is the `.ini` value, or the environment one, or a default - [__vstr()](https://www.xbwin.com/ot4xb/doc/search?k=__vstr)
returns the first string among its parameters - and a missing one is an error before anything else runs.

```xbase
      INLINE METHOD init_instance()
         local cIniFile
         if ::ini == NIL
            ::ini := _ot4xb_expando_():New()
         end
         if ::env == NIL
            ::env := _ot4xb_expando_():New()
            ::env:add_env_strings()
         end                                          
         
         DEFAULT ini_file_name := cPathChangeExt( cPathGetFileName( AppName() ) , ".ini" )
         DEFAULT config_folder_env_name := cPathRemoveExt( cPathGetFileName( AppName() )) + "_CONFIG_FOLDER"
         DEFAULT data_folder_env_name := cPathRemoveExt( cPathGetFileName( AppName() )) + "_DATA_FOLDER"
         
         
         
         __assert( ::env:get_val( data_folder_env_name)   , -1 , "Missing environment variable: " + data_folder_env_name )
         __assert( ::env:get_val( config_folder_env_name) , -1 , "Missing environment variable: " + config_folder_env_name )
         ::config_folder := cPathAddBackSlash( ::env:get_val( config_folder_env_name) )
         cIniFile := cPathCombine( ::config_folder ,ini_file_name )
         __assert( lIsFile( cIniFile ) , -1 , cPrintf("Missing %s file", cIniFile ) )
         ::ini:add_ini_string( cMemoReadEx(cIniFile , 2 ) )
         ::data_folder   := __vstr( ::ini:DATA_FOLDER , ::env:get_val( data_folder_env_name)  )
         __assert( lMakePath(::data_folder) )



         ::m_mysql_host  := __vstr( ::ini:mysql_host , ::env:ally_mysql_host , "127.0.0.1" )
         ::m_mysql_port  := ot4xb_parse_int( __vstr(::ini:mysql_port, ::env:ally_mysql_port ) , 3306 )
         ::m_mysql_user  := ::ini:mysql_user  
         ::m_mysql_db    := ::ini:mysql_db    
         ::m_mysql_pwd   := ::ini:mysql_pwd   

          __assert( ::m_mysql_host , -1 , "Missing mysql_host  in ao.ini and env:ally_mysql_host" )
          __assert( ::m_mysql_port , -1 , "Missing mysql_port  in ao.ini and env:ally_mysql_port" )
          __assert( ::m_mysql_db   , -1 , "Missing mysql_db    in ao.ini and env:ally_mysql_db  " )
          __assert( ::m_mysql_user , -1 , "Missing mysql_user  in ao.ini and env:ally_mysql_user" )
          __assert( ::m_mysql_pwd  , -1 , "Missing mysql_pwd   in ao.ini and env:ally_mysql_pwd " )



         return Self
      // ---------------------------------------------------------------------------------

      INLINE ACCESS ASSIGN METHOD cConfigFolder( v )
         if v != NIL
            return ::config_folder  := v
         end
          return ::config_folder
      // ---------------------------------------------------------------------------------
      INLINE ACCESS ASSIGN METHOD cDataFolder( v )
         if v != NIL
            return ::data_folder  := v
         end
         return ::data_folder
      // ---------------------------------------------------------------------------------
      INLINE METHOD argv(n)
         return __apeek( GetProccessArgv() , n + iif( IsDebug(),1,0) )
      // ---------------------------------------------------------------------------------
      INLINE METHOD argc()
         static n := NIL
         DEFAULT n := ( Len( GetProccessArgv() ) - iif( IsDebug(),1,0) )
         return n
      // ---------------------------------------------------------------------------------
```

Errors the Xbase++ way: an `Error()` object built from a code and a message - or the object passed in - and
evaluated with the current `ErrorBlock()`, so `BEGIN SEQUENCE` and the error handler of the application see it
like any other. [__vmask()](https://www.xbwin.com/ot4xb/doc/search?k=__vmask) picks a parameter by type.

```xbase
      INLINE METHOD throw(error,cDescription)
         local b := __vmask( XPP_BLOCK , errorblock() ,  {|_e| break(_e) } )
         local e := NIL
         if __vmask( 0xC0 , error ) != NIL // array or object
            e := error
            return eval(b,e)
         end
         e := error():new()
         e:severity     := 2
         e:gencode      := __vmask( XPP_NUMERIC   , error , -1 )
         e:description  := __vmask( XPP_CHARACTER , cDescription , error  , cPrintf("error: %i",e:gencode) )
         return eval(b,e)
      // ---------------------------------------------------------------------------------
      INLINE METHOD _check_flag_str( cValue , lYesIfEmptyString )
         if !empty(lYesIfEmptyString)
            return left(alltrim(__vlower( cValue , "no*" )) + "yes",3) == "yes"
         end
         return  alltrim(__vlower(cValue,"no")) == "yes"
      // ---------------------------------------------------------------------------------
```

One connection per thread: `tls():mysql` holds it; the first call creates it with SSL required and connects with the
parameters read at start, the following ones ping it - [lAnd()](https://www.xbwin.com/ot4xb/doc/search?k=land) of the ping result is true when it
failed - and reconnect if needed. `release_mysql()` closes and forgets it.

```xbase
      INLINE METHOD get_connected_mysql()
         local mysql := tls():mysql

         if mysql == NIL
            mysql := tls():mysql := ao_mysql():new()
            mysql:set_option_ssl_mode( 3  ) // SSL_MODE_REQUIRED
            if !mysql:connect( ::m_mysql_host ,::m_mysql_user,::m_mysql_pwd ,::m_mysql_db,::m_mysql_port,0,0 )
               ::throw(mysql:last_error(),mysql:last_error_string() )
            end
            return mysql
         end          
         if lAnd( mysql:ping() )                               
            mysql:set_option_ssl_mode( 3  ) // SSL_MODE_REQUIRED
            if !mysql:connect( ::m_mysql_host ,::m_mysql_user,::m_mysql_pwd ,::m_mysql_db,::m_mysql_port,0,0 )
               ::throw(mysql:last_error(),mysql:last_error_string() )
            end
         end
         return mysql
      // ------------------------------------------------------------------------------------------------------------------
      INLINE METHOD release_mysql()
         local mysql := tls():mysql
         tls():mysql := NIL
         if mysql != NIL
            mysql:close()
         end
         return NIL
      // ------------------------------------------------------------------------------------------------------------------
      INLINE METHOD query(sql,rs_co,flags)
         return ::get_connected_mysql():query( sql , rs_co , flags )
      // ------------------------------------------------------------------------------------------------------------------
      INLINE METHOD try_query(sql,nError , cError,rs_co)
         return ::get_connected_mysql():try_query( sql , @nError , @cError ,rs_co )
      // ------------------------------------------------------------------------------------------------------------------      
```

A result set of a table with no rows: `SELECT * FROM `table` LIMIT 0` brings the column descriptors and nothing
else, so `DbAppend()`, the fields and `save()` work as on any other; the way to insert into a table without
reading it.

```xbase
      INLINE METHOD get_empty_recordset( table , fields ,rs_co)
         local sql := "SELECT "
         if empty(table)
            return NIL
         end
         if empty( fields )    
            sql += ' * ' 
         else
            sql += ' ' + fields + ' '
         end
         sql += ' FROM  `' + table + '`  LIMIT 0;'
         return ::query( sql ,rs_co)          
      //--------------------------------------------------------------------------------------------------------------------


ENDCLASS
//----------------------------------------------------------------------------------------------------------------------
static function __throw(error,cDescription)
	local b := __vmask( XPP_BLOCK , errorblock() ,  {|_e| break(_e) } )
	local e := NIL
	if __vmask( 0xC0 , error ) != NIL // array or object
	   e := error
	   return eval(b,e)
	end
	e := error():new()
	e:severity     := 2
	e:gencode      := __vmask( XPP_NUMERIC   , error , -1 )
	e:description  := __vmask( XPP_CHARACTER , cDescription , error  , cPrintf("error: %i",e:gencode) )
	return eval(b,e)
```
