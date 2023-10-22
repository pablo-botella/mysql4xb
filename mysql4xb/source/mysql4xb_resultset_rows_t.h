#pragma once

namespace result_rows_ns
{
   enum class meta_pos_e : ULONG
   {
      changed = 1,
      new_row = 2,
      deleted = 3,
      meta_array_length = 4
   };
   enum class meta_action_e : ULONG
   {
      get,
      set
   };


   ContainerHandle _get_current_or_ghost_cell(TXppParamList& xpp, ContainerHandle& con_field_object);
   char _xbase_numeric_type_to_xbase_char_valtype(DWORD xbase_numeric_type);
   ContainerHandle _get_field_object(ContainerHandle Self, ContainerHandle con_k, DWORD col_count, DWORD& col_pos, ContainerHandle con_field_object = NULLCONTAINER);
   ContainerHandle _get_field_object(ContainerHandle Self, ContainerHandle con_k, DWORD col_count, ContainerHandle con_field_object = NULLCONTAINER);
   DWORD _get_col_position(ContainerHandle Self, ContainerHandle con_k, DWORD col_count);
   void __set_get_row_flags(TXppParamList& xpp, BOOL lOnOff, meta_pos_e meta_pos, meta_action_e meta_action, BOOL& lGhost, DWORD col_pos = 0);

   void init(XppParamList pl);

   void add_colname_alias(XppParamList pl);

   void __set_field_definition(XppParamList pl);

   void __init_empty_row(XppParamList pl);

   void add_blank_row(XppParamList pl);

   void get_col_name(XppParamList pl);

   void get_col_position(XppParamList pl);
   void get_col_info(XppParamList pl);

   void go_top(XppParamList pl);

   void go_bottom(XppParamList pl);

   void skip(XppParamList pl);

   void set_row_pos(XppParamList pl);

   void escape_cell_value(XppParamList pl);

   void get_cell(XppParamList pl);

   void set_cell(XppParamList pl);

   void row_metadata(XppParamList pl);

   void row_changed(XppParamList pl);

   void mark_row_to_delete(XppParamList pl);

   void unmark_row_to_delete(XppParamList pl);

   void is_row_marked_to_delete(XppParamList pl);

   void is_new_row(XppParamList pl);

   void remove_row_from_rowset(XppParamList pl);





}
