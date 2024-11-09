#include <mysql4xb_api.h>
#include <stdio.h>
LONG mysql_field_to_ot4xb_sql_type( MYSQL_FIELD& field )
{
   switch( field.type )
   {
      case MYSQL_TYPE_DECIMAL:  return  (LONG) ot4xb_sql_type::Decimal;
      case MYSQL_TYPE_TINY:  return  (LONG) ot4xb_sql_type::TinyInt;
      case MYSQL_TYPE_SHORT:  return  (LONG) ot4xb_sql_type::SmallInt;
      case MYSQL_TYPE_LONG:  return  (LONG) ot4xb_sql_type::Int;
      case MYSQL_TYPE_FLOAT:  return  (LONG) ot4xb_sql_type::Float;
      case MYSQL_TYPE_DOUBLE:  return  (LONG) ot4xb_sql_type::Double;
      case MYSQL_TYPE_NULL:  return  (LONG) ot4xb_sql_type::Invalid;
      case MYSQL_TYPE_TIMESTAMP:  return  (LONG) ot4xb_sql_type::TimeStamp;
      case MYSQL_TYPE_LONGLONG:  return  (LONG) ot4xb_sql_type::BigInt;
      case MYSQL_TYPE_INT24:  return  (LONG) ot4xb_sql_type::MediumInt;
      case MYSQL_TYPE_DATE:  return  (LONG) ot4xb_sql_type::Date;
      case MYSQL_TYPE_TIME:  return  (LONG) ot4xb_sql_type::Time;
      case MYSQL_TYPE_DATETIME:  return  (LONG) ot4xb_sql_type::DateTime;
      case MYSQL_TYPE_YEAR:  return  (LONG) ot4xb_sql_type::Year;
      case MYSQL_TYPE_NEWDATE:  return  (LONG) ot4xb_sql_type::Date;
      case MYSQL_TYPE_VARCHAR:  return  (LONG) ot4xb_sql_type::VarChar;
      case MYSQL_TYPE_BIT:  return  (LONG) ot4xb_sql_type::Bit;
      case MYSQL_TYPE_TIMESTAMP2:  return  (LONG) ot4xb_sql_type::TimeStamp;
      case MYSQL_TYPE_DATETIME2:  return  (LONG) ot4xb_sql_type::DateTime;
      case MYSQL_TYPE_TIME2:  return  (LONG) ot4xb_sql_type::Time;
      case MYSQL_TYPE_JSON:  return  (LONG) ot4xb_sql_type::Json;
      case MYSQL_TYPE_NEWDECIMAL:  return  (LONG) ot4xb_sql_type::Decimal;
      case MYSQL_TYPE_ENUM:  return  (LONG) ot4xb_sql_type::Enum;
      case MYSQL_TYPE_SET:  return  (LONG) ot4xb_sql_type::Set;
      case MYSQL_TYPE_TINY_BLOB:  return  (LONG) ot4xb_sql_type::TinyBlob;
      case MYSQL_TYPE_MEDIUM_BLOB:  return  (LONG) ot4xb_sql_type::MediumBlob;
      case MYSQL_TYPE_LONG_BLOB:  return  (LONG) ot4xb_sql_type::LongBlob;
      case MYSQL_TYPE_BLOB:  return  (LONG) ot4xb_sql_type::Blob;
      case MYSQL_TYPE_VAR_STRING:  return  IS_BLOB( field.flags ) ? (LONG) ot4xb_sql_type::VarBinary : (LONG) ot4xb_sql_type::VarChar;
      case MYSQL_TYPE_STRING:  return  IS_BLOB( field.flags ) ? (LONG) ot4xb_sql_type::Blob : (LONG) ot4xb_sql_type::Char;
      case MYSQL_TYPE_GEOMETRY:  return  (LONG) ot4xb_sql_type::Char;
      default:  return (LONG) ot4xb_sql_type::Char;
   }

}
// ------------------------------------------------------------------------------------------------------------
ContainerHandle mysql_xb_quick_query_sqltype_to_xbase_blank_value( ContainerHandle con_value, MYSQL_FIELD& field )
{
   con_value = _conPut( con_value, NULLCONTAINER );

   switch( field.type )
   {
      case MYSQL_TYPE_TINY:
      {
         if( mysqlxb_global_flags[ (DWORD) mysqlxb_global_flags_enum::tiny_to_bool ] & 0xFF )
         {
            return _conPutL( con_value, 0 );
         }
         else
         {
            return _conPutNL( con_value, 0 );
         }
         break;
      }
      case MYSQL_TYPE_NEWDECIMAL: case MYSQL_TYPE_DECIMAL:
      {
         return _conPutNDF( con_value, 0.00, (LONG) field.max_length, (LONG) field.decimals );

      }
      case MYSQL_TYPE_LONGLONG: case MYSQL_TYPE_INT24: case MYSQL_TYPE_LONG: case MYSQL_TYPE_SHORT:
      {
         return _conPutNL( con_value, 0 );
      }

      case MYSQL_TYPE_FLOAT: case MYSQL_TYPE_DOUBLE:
      {
         return _conPutND( con_value, 0.00 );
      }
      case MYSQL_TYPE_DATE:
      {
         return _conPutDS( con_value, "        " );
      }
      case MYSQL_TYPE_VAR_STRING:
      {
         char buffer[ 256 ] = { 0 };
         DWORD cb = min( sizeof( buffer ) - 1, field.length );
         for( DWORD dw = 0; dw < cb; dw++ )
         {
            buffer[ dw ] = 0x20;
         }
         return _conPutC( con_value, buffer );
      }
      case MYSQL_TYPE_NULL:
      case MYSQL_TYPE_TIMESTAMP: case MYSQL_TYPE_TIME: case MYSQL_TYPE_DATETIME: case MYSQL_TYPE_YEAR: case MYSQL_TYPE_NEWDATE:
      case MYSQL_TYPE_TIMESTAMP2: case MYSQL_TYPE_DATETIME2: case MYSQL_TYPE_TIME2:
      case MYSQL_TYPE_VARCHAR: case MYSQL_TYPE_BIT: case MYSQL_TYPE_JSON: case MYSQL_TYPE_ENUM: case MYSQL_TYPE_SET:
      case MYSQL_TYPE_TINY_BLOB: case MYSQL_TYPE_MEDIUM_BLOB: case MYSQL_TYPE_LONG_BLOB: case MYSQL_TYPE_BLOB:
      case MYSQL_TYPE_STRING: case MYSQL_TYPE_GEOMETRY:
      default: // character as is
      {
         return _conPutC( con_value, "" );
      }
   }

}
// ------------------------------------------------------------------------------------------------------------
char __cdecl mysql_xb_quick_query_sqltype_to_xbase_type_letter( enum_field_types mytype )
{
   switch( mytype )
   {
      case MYSQL_TYPE_TINY:
      {
         return ( mysqlxb_global_flags[ (DWORD) mysqlxb_global_flags_enum::tiny_to_bool ] & 0xFF ) ? 'L' : 'N';
      }
      case MYSQL_TYPE_NEWDECIMAL: case MYSQL_TYPE_DECIMAL:
      {
         return 'N';
      }
      case MYSQL_TYPE_LONGLONG: case MYSQL_TYPE_INT24: case MYSQL_TYPE_LONG: case MYSQL_TYPE_SHORT:
      {
         return 'N';
      }
      case MYSQL_TYPE_FLOAT: case MYSQL_TYPE_DOUBLE:
      {
         return 'N';
      }
      case MYSQL_TYPE_DATE:
      {
         return 'D';
      }
      case MYSQL_TYPE_JSON:
      {
         return 'J';
      }
      case MYSQL_TYPE_NULL:
      case MYSQL_TYPE_TIMESTAMP: case MYSQL_TYPE_TIME: case MYSQL_TYPE_DATETIME: case MYSQL_TYPE_YEAR: case MYSQL_TYPE_NEWDATE:
      case MYSQL_TYPE_TIMESTAMP2: case MYSQL_TYPE_DATETIME2: case MYSQL_TYPE_TIME2:
      case MYSQL_TYPE_VARCHAR: case MYSQL_TYPE_BIT:  case MYSQL_TYPE_ENUM: case MYSQL_TYPE_SET:
      case MYSQL_TYPE_TINY_BLOB: case MYSQL_TYPE_MEDIUM_BLOB: case MYSQL_TYPE_LONG_BLOB: case MYSQL_TYPE_BLOB: case MYSQL_TYPE_VAR_STRING:
      case MYSQL_TYPE_STRING: case MYSQL_TYPE_GEOMETRY:
      default: // character as is
      {
         return 'C';
      }
   }
}
// -------------------------------------------------------------------------------------------------------------
ContainerHandle mysql_xb_quick_query_create_field_object_container_handle( MYSQL_FIELD& field, DWORD field_pos, ContainerHandle class_object )
{
   ContainerHandle con_value = NULLCONTAINER;

   ContainerHandle con_field_object = _conNew( NULLCONTAINER );

   _conCallMethodPa( con_field_object, "new", 1, &class_object );

   con_value = _conPutNL( con_value, (LONG) ( field_pos + 1 ) );
   _conSetMember( con_field_object, "field_pos", con_value );

   con_value = _conPutCL( con_value, field.name, field.name_length );
   _conSetMember( con_field_object, "name", con_value );

   con_value = _conPutCL( con_value, field.org_name, field.org_name_length );
   _conSetMember( con_field_object, "org_name", con_value );

   con_value = _conPutCL( con_value, field.table, field.table_length );
   _conSetMember( con_field_object, "table", con_value );

   con_value = _conPutCL( con_value, field.db, field.db_length );
   _conSetMember( con_field_object, "db", con_value );

   con_value = _conPutCL( con_value, field.catalog, field.catalog_length );
   _conSetMember( con_field_object, "catalog", con_value );

   con_value = _conPutNL( con_value, (LONG) field.length );
   _conSetMember( con_field_object, "length", con_value );

   con_value = _conPutNL( con_value, (LONG) field.max_length );
   _conSetMember( con_field_object, "max_length", con_value );

   con_value = _conPutNL( con_value, (LONG) field.flags );
   _conSetMember( con_field_object, "flags", con_value );

   con_value = _conPutNL( con_value, (LONG) field.decimals );
   _conSetMember( con_field_object, "decimals", con_value );

   con_value = _conPutNL( con_value, (LONG) field.charsetnr );
   _conSetMember( con_field_object, "charsetnr", con_value );

   con_value = _conPutNL( con_value, field.type );
   _conSetMember( con_field_object, "type", con_value );


   con_value = _conPutNL( con_value, mysql_field_to_ot4xb_sql_type( field ) );
   _conSetMember( con_field_object, "ot4xb_sql_type", con_value );

   char xbase_type[ ] = { mysql_xb_quick_query_sqltype_to_xbase_type_letter( field.type ), 0 };
   con_value = _conPutC( con_value, xbase_type );
   _conSetMember( con_field_object, "xbase_type", con_value );

   con_value = mysql_xb_quick_query_sqltype_to_xbase_blank_value( con_value, field );
   _conSetMember( con_field_object, "xbase_empty_value", con_value );

   DWORD escape_flags = ( mysqlxb_global_flags[ (DWORD) mysqlxb_global_flags_enum::auto_truncate_values ] & 0xFF ? (DWORD) ot4xb_sql_type_flag::Truncate : 0 );
   if( field.flags & NOT_NULL_FLAG )
   {
      escape_flags |= (DWORD) ot4xb_sql_type_flag::NotNull;
   }
   con_value = _conPutNL( con_value, (LONG) escape_flags );
   _conSetMember( con_field_object, "escape_flags", con_value );

   _conRelease( con_value );
   con_value = NULLCONTAINER;
   return con_field_object;
}

// -------------------------------------------------------------------------------------------------------------
// mysql_xb_quick_query(1pMysql,2sql,3rs_co,4 rows_co , 5 fld_co , 6 self , 7 flags)
void __cdecl mysql_xb_quick_query( XppParamList pl )
{
   TXppParamList xpp( pl, 7 );
   MYSQL* my = (MYSQL*) xpp[ 1 ]->GetDWord();
   DWORD flags = xpp[ 7 ]->GetDWord();
   DWORD result_count = 0;
   if( flags & 0x1000 )
   {
      xpp[ 0 ]->PutNewArray( 1, 0 );
   }



   if( my )
   {
      DWORD sql_cb = 0;
      LPSTR sql = xpp[ 2 ]->LockStr( &sql_cb );

      if( sql && sql_cb )
      {

         int status = mysql_real_query( my, sql, sql_cb );
         xpp[ 2 ]->UnlockStr();

         for( ; status == 0; status = mysql_next_result( my ) )
         {

            result_count++;
            if( flags & 0x1000 )
            {
               xpp[ 0 ]->resize( result_count );
            }

            MYSQL_RES* result = mysql_store_result( my );
            if( result )
            {

               int field_count = (int) mysql_num_fields( result );
               int row_count = (int) ( mysql_num_rows( result ) & 0xFFFFFFFF );
               int field_pos;
               int row_pos;


               MYSQL_FIELD* fields = mysql_fetch_fields( result );
               ContainerHandle con_result_class_object = xpp[ 3 ]->con();
               ContainerHandle con_rows_class_object = xpp[ 4 ]->con();
               ContainerHandle con_fld_class_object = xpp[ 5 ]->con();
               ContainerHandle con_rows_object = NULLCONTAINER;
               ContainerHandle con_result_object = NULLCONTAINER;
               if( con_rows_class_object && con_result_class_object )
               {
                  ContainerHandle con_params[ ] = { con_rows_class_object , _conPutNL( NULLCONTAINER,field_count ) , _conPutNL( NULLCONTAINER , row_count ) };
                  con_rows_object = _conNew( NULLCONTAINER );
                  if( _conCallMethodPa( con_rows_object, "new", 3, con_params ) )
                  {
                     _conRelease( con_rows_object ); con_rows_object = NULLCONTAINER;
                  }
                  _conRelease( con_params[ 1 ] ); con_params[ 1 ] = NULLCONTAINER;
                  _conRelease( con_params[ 2 ] ); con_params[ 1 ] = NULLCONTAINER;
               }
               if( con_rows_object )
               {
                  ContainerHandle con_params[ ] = { con_result_class_object , con_rows_object , xpp[ 6 ]->con() , xpp[ 2 ]->con() };
                  con_result_object = _conNew( NULLCONTAINER );
                  if( _conCallMethodPa( con_result_object, "new", 4, con_params ) )
                  {
                     _conRelease( con_rows_object );
                     con_rows_object = NULLCONTAINER;
                     _conRelease( con_result_object );
                     con_result_object = NULLCONTAINER;
                  }
               }
               if( con_rows_object )
               {
                  for( field_pos = 0; field_pos < field_count; field_pos++ )
                  {
                     ContainerHandle con_field_object = mysql_xb_quick_query_create_field_object_container_handle( fields[ field_pos ], (DWORD) field_pos, con_fld_class_object );
                     ContainerHandle con_result = _conNew( NULLCONTAINER );
                     ContainerHandle con_params[ ] = { con_rows_object , con_field_object };
                     _conCallMethodPa( con_result, "__set_field_definition", 2, con_params );
                     _conRelease( con_field_object ); con_field_object = NULLCONTAINER;
                     _conRelease( con_result ); con_result = NULLCONTAINER;
                  }

                  for( row_pos = 0; row_pos < row_count; row_pos++ )
                  {

                     MYSQL_ROW row = mysql_fetch_row( result );
                     if( row )
                     {
                        DWORD* row_lengths = mysql_fetch_lengths( result );
                        ContainerHandle cona_row = _conNewArray( 1, (ULONG) field_count );


                        for( field_pos = 0; field_pos < field_count; field_pos++ )
                        {
                           ContainerHandle con_value = NULLCONTAINER;
                           if( row[ field_pos ] )
                           {
                              switch( fields[ field_pos ].type )
                              {
                                 case MYSQL_TYPE_TINY:
                                 {
                                    char buffer[ 0xFF + 1 ] = { 0 };
                                    memcpy_s( (LPBYTE) buffer, sizeof( buffer ) - 1, (LPBYTE) row[ field_pos ], row_lengths[ field_pos ] );
                                    int value = atoi( buffer );
                                    if( mysqlxb_global_flags[ (DWORD) mysqlxb_global_flags_enum::tiny_to_bool ] & 0xFF )
                                    {
                                       con_value = _conPutL( con_value, value ? 1 : 0 );
                                    }
                                    else
                                    {
                                       con_value = _conPutNL( con_value, value );
                                    }
                                    break;
                                 }
                                 case MYSQL_TYPE_DECIMAL: case MYSQL_TYPE_NEWDECIMAL:
                                 {
                                    char buffer[ 0xFF + 1 ] = { 0 };
                                    memcpy_s( (LPBYTE) buffer, sizeof( buffer ) - 1, (LPBYTE) row[ field_pos ], row_lengths[ field_pos ] );
                                    double value = atof( buffer );
                                    con_value = _conPutNDF( con_value, value, (LONG) fields[ field_pos ].max_length, (LONG) fields[ field_pos ].decimals );





                                    break;
                                 }

                                 case MYSQL_TYPE_SHORT: case MYSQL_TYPE_LONG: case MYSQL_TYPE_INT24:
                                 {
                                    char buffer[ 0xFF + 1 ] = { 0 };
                                    memcpy_s( (LPBYTE) buffer, sizeof( buffer ) - 1, (LPBYTE) row[ field_pos ], row_lengths[ field_pos ] );
                                    LONG value = atoi( buffer );
                                    con_value = _conPutNL( con_value, value );
                                    break;
                                 }
                                 case MYSQL_TYPE_LONGLONG:
                                 {
                                    char buffer[ 0xFF + 1 ] = { 0 };
                                    memcpy_s( (LPBYTE) buffer, sizeof( buffer ) - 1, (LPBYTE) row[ field_pos ], row_lengths[ field_pos ] );
                                    __int64 v64 = _atoi64( buffer );
                                    if( ( v64 & 0xFFFFFFFF00000000ll ) == 0ll || ( v64 & 0xFFFFFFFF00000000ll ) == 0xFFFFFFFF00000000ll )
                                    {
                                       con_value = _conPutNL( con_value, (LONG) v64 );
                                    }
                                    else
                                    {
                                       con_value = _conPutND( con_value, (double) v64 );
                                    }
                                    break;
                                 }

                                 case MYSQL_TYPE_FLOAT:  case MYSQL_TYPE_DOUBLE:
                                 {
                                    char buffer[ 0xFF + 1 ] = { 0 };
                                    memcpy_s( (LPBYTE) buffer, sizeof( buffer ) - 1, (LPBYTE) row[ field_pos ], row_lengths[ field_pos ] );
                                    double value = atof( buffer );
                                    con_value = _conPutND( con_value, value );
                                    break;
                                 }
                                 case MYSQL_TYPE_DATE:
                                 {
                                    char buffer[ 0xFF + 1 ] = { 0 };
                                    LPSTR p = buffer;
                                    DWORD cb = min( row_lengths[ field_pos ], 0xFF );
                                    for( DWORD i = 0; i < cb; i++ )
                                    {
                                       if( (BYTE) row[ field_pos ][ i ] >= '0' && (BYTE) row[ field_pos ][ i ] <= '9' )
                                       {
                                          *p = row[ field_pos ][ i ]; p++;
                                       }
                                    }
                                    con_value = _conPutDS( con_value, buffer );
                                    break;
                                 }
                                 case MYSQL_TYPE_JSON:
                                 {
                                    int utf8_cb = 0;
                                    LPSTR uft8_str = mb2mb( row[ field_pos ], (int) row_lengths[ field_pos ], &utf8_cb, 0, 65001, 0, 0 );
                                    ContainerHandle jso = json_ns::parse_string_utf8( uft8_str, 0, 0 );
                                    _xfree( (void*) uft8_str ); uft8_str = 0;
                                    con_value = _conPut( con_value, jso );
                                    if( jso )
                                    {
                                       _conRelease( jso );
                                       jso = NULLCONTAINER;
                                    }
                                    break;

                                 }

                                 case MYSQL_TYPE_NULL:
                                 case MYSQL_TYPE_TIMESTAMP:
                                 case MYSQL_TYPE_TIME:
                                 case MYSQL_TYPE_DATETIME:
                                 case MYSQL_TYPE_YEAR:
                                 case MYSQL_TYPE_NEWDATE:
                                 case MYSQL_TYPE_VARCHAR:
                                 case MYSQL_TYPE_BIT:
                                 case MYSQL_TYPE_TIMESTAMP2:
                                 case MYSQL_TYPE_DATETIME2:
                                 case MYSQL_TYPE_TIME2:


                                 case MYSQL_TYPE_ENUM:
                                 case MYSQL_TYPE_SET:
                                 case MYSQL_TYPE_TINY_BLOB:
                                 case MYSQL_TYPE_MEDIUM_BLOB:
                                 case MYSQL_TYPE_LONG_BLOB:
                                 case MYSQL_TYPE_BLOB:
                                 case MYSQL_TYPE_VAR_STRING:
                                 case MYSQL_TYPE_STRING:
                                 case MYSQL_TYPE_GEOMETRY:

                                 default: // character as is
                                 {
                                    con_value = _conPutCL( con_value, row[ field_pos ], row_lengths[ field_pos ] );
                                    break;
                                 }
                              }
                           }
                           else
                           {
                              if( mysqlxb_global_flags[ (DWORD) mysqlxb_global_flags_enum::null_to_empty ] && 0xFF )
                              {
                                 con_value = mysql_xb_quick_query_sqltype_to_xbase_blank_value( con_value, fields[ field_pos ] );
                              }
                           }
                           if( con_value )
                           {

                              _conArrayPut( cona_row, con_value, field_pos + 1, 0 );
                              _conRelease( con_value );  con_value = NULLCONTAINER;
                           }
                        }

                        if( cona_row )
                        {
                           ContainerHandle con_result = _conNew( NULLCONTAINER );
                           ContainerHandle con_row_pos = _conPutNL( NULLCONTAINER, row_pos + 1 );
                           ContainerHandle con_params[ ] = { con_rows_object , con_row_pos, cona_row };
                           _conCallMethodPa( con_result, "__init_empty_row", 3, con_params );
                           _conRelease( con_row_pos ); con_row_pos = NULLCONTAINER;
                           _conRelease( cona_row ); cona_row = NULLCONTAINER;
                           _conRelease( con_result ); con_result = NULLCONTAINER;
                        }


                     }
                  }

                  _conRelease( con_rows_object ); con_rows_object = NULLCONTAINER;
               }


               if( flags & 0x1000 )
               {
                  _conArrayPut( xpp[ 0 ]->con(), con_result_object, result_count, 0 );
               }
               else
               {
                  xpp[ 0 ]->Put( con_result_object );

               }
               if( con_result_object )
               {
                  _conRelease( con_result_object ); con_result_object = NULLCONTAINER;
               }
               mysql_free_result( result );
            }
            else
            {
               if( mysql_field_count( my ) == 0 )
               {
                  if( flags & 0x1000 )
                  {
                     LONGLONG qw = (LONGLONG) mysql_affected_rows( my );
                     ContainerHandle con = NULLCONTAINER;
                     if( qw & 0xFFFFFFFF80000000ll ) { con = _conPutND( con, (double) qw ); }
                     else { con = _conPutNL( con, (LONG) ( qw & 0xFFFFFFFFll ) ); }
                     _conArrayPut( xpp[ 0 ]->con(), con, result_count, 0 );
                     _conRelease( con );
                     con = NULLCONTAINER;
                  }
                  else
                  {
                     xpp[ 0 ]->PutQWordAsNumeric( (LONGLONG) mysql_affected_rows( my ) );
                  }
               }
            }

         }


      }
   }



}