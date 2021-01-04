case T_Integer:
  OUT_NODE(Integer, Integer, integer, Value, integer);
  break;
case T_Float:
  OUT_NODE(Float, Float, float, Value, float_);
  break;
case T_String:
  OUT_NODE(String, String, string, Value, string);
  break;
case T_BitString:
  OUT_NODE(BitString, BitString, bit_string, Value, bit_string);
  break;
case T_Null:
  OUT_NODE(Null, Null, null, Value, null);
  break;
case T_List:
  OUT_NODE(List, List, list, List, list);
  break;
case T_IntList:
  OUT_NODE(IntList, IntList, int_list, List, int_list);
  break;
case T_OidList:
  OUT_NODE(OidList, OidList, oid_list, List, oid_list);
  break;
case T_Alias:
  OUT_NODE(Alias, Alias, alias, Alias, alias);
  break;
case T_RangeVar:
  OUT_NODE(RangeVar, RangeVar, range_var, RangeVar, range_var);
  break;
case T_TableFunc:
  OUT_NODE(TableFunc, TableFunc, table_func, TableFunc, table_func);
  break;
case T_Expr:
  OUT_NODE(Expr, Expr, expr, Expr, expr);
  break;
case T_Var:
  OUT_NODE(Var, Var, var, Var, var);
  break;
case T_Param:
  OUT_NODE(Param, Param, param, Param, param);
  break;
case T_Aggref:
  OUT_NODE(Aggref, Aggref, aggref, Aggref, aggref);
  break;
case T_GroupingFunc:
  OUT_NODE(GroupingFunc, GroupingFunc, grouping_func, GroupingFunc, grouping_func);
  break;
case T_WindowFunc:
  OUT_NODE(WindowFunc, WindowFunc, window_func, WindowFunc, window_func);
  break;
case T_SubscriptingRef:
  OUT_NODE(SubscriptingRef, SubscriptingRef, subscripting_ref, SubscriptingRef, subscripting_ref);
  break;
case T_FuncExpr:
  OUT_NODE(FuncExpr, FuncExpr, func_expr, FuncExpr, func_expr);
  break;
case T_NamedArgExpr:
  OUT_NODE(NamedArgExpr, NamedArgExpr, named_arg_expr, NamedArgExpr, named_arg_expr);
  break;
case T_OpExpr:
  OUT_NODE(OpExpr, OpExpr, op_expr, OpExpr, op_expr);
  break;
case T_DistinctExpr:
  OUT_NODE(DistinctExpr, DistinctExpr, distinct_expr, DistinctExpr, distinct_expr);
  break;
case T_NullIfExpr:
  OUT_NODE(NullIfExpr, NullIfExpr, null_if_expr, NullIfExpr, null_if_expr);
  break;
case T_ScalarArrayOpExpr:
  OUT_NODE(ScalarArrayOpExpr, ScalarArrayOpExpr, scalar_array_op_expr, ScalarArrayOpExpr, scalar_array_op_expr);
  break;
case T_BoolExpr:
  OUT_NODE(BoolExpr, BoolExpr, bool_expr, BoolExpr, bool_expr);
  break;
case T_SubLink:
  OUT_NODE(SubLink, SubLink, sub_link, SubLink, sub_link);
  break;
case T_SubPlan:
  OUT_NODE(SubPlan, SubPlan, sub_plan, SubPlan, sub_plan);
  break;
case T_AlternativeSubPlan:
  OUT_NODE(AlternativeSubPlan, AlternativeSubPlan, alternative_sub_plan, AlternativeSubPlan, alternative_sub_plan);
  break;
case T_FieldSelect:
  OUT_NODE(FieldSelect, FieldSelect, field_select, FieldSelect, field_select);
  break;
case T_FieldStore:
  OUT_NODE(FieldStore, FieldStore, field_store, FieldStore, field_store);
  break;
case T_RelabelType:
  OUT_NODE(RelabelType, RelabelType, relabel_type, RelabelType, relabel_type);
  break;
case T_CoerceViaIO:
  OUT_NODE(CoerceViaIO, CoerceViaIO, coerce_via_io, CoerceViaIO, coerce_via_io);
  break;
case T_ArrayCoerceExpr:
  OUT_NODE(ArrayCoerceExpr, ArrayCoerceExpr, array_coerce_expr, ArrayCoerceExpr, array_coerce_expr);
  break;
case T_ConvertRowtypeExpr:
  OUT_NODE(ConvertRowtypeExpr, ConvertRowtypeExpr, convert_rowtype_expr, ConvertRowtypeExpr, convert_rowtype_expr);
  break;
case T_CollateExpr:
  OUT_NODE(CollateExpr, CollateExpr, collate_expr, CollateExpr, collate_expr);
  break;
case T_CaseExpr:
  OUT_NODE(CaseExpr, CaseExpr, case_expr, CaseExpr, case_expr);
  break;
case T_CaseWhen:
  OUT_NODE(CaseWhen, CaseWhen, case_when, CaseWhen, case_when);
  break;
case T_CaseTestExpr:
  OUT_NODE(CaseTestExpr, CaseTestExpr, case_test_expr, CaseTestExpr, case_test_expr);
  break;
case T_ArrayExpr:
  OUT_NODE(ArrayExpr, ArrayExpr, array_expr, ArrayExpr, array_expr);
  break;
case T_RowExpr:
  OUT_NODE(RowExpr, RowExpr, row_expr, RowExpr, row_expr);
  break;
case T_RowCompareExpr:
  OUT_NODE(RowCompareExpr, RowCompareExpr, row_compare_expr, RowCompareExpr, row_compare_expr);
  break;
case T_CoalesceExpr:
  OUT_NODE(CoalesceExpr, CoalesceExpr, coalesce_expr, CoalesceExpr, coalesce_expr);
  break;
case T_MinMaxExpr:
  OUT_NODE(MinMaxExpr, MinMaxExpr, min_max_expr, MinMaxExpr, min_max_expr);
  break;
case T_SQLValueFunction:
  OUT_NODE(SQLValueFunction, SQLValueFunction, sqlvalue_function, SQLValueFunction, sqlvalue_function);
  break;
case T_XmlExpr:
  OUT_NODE(XmlExpr, XmlExpr, xml_expr, XmlExpr, xml_expr);
  break;
case T_NullTest:
  OUT_NODE(NullTest, NullTest, null_test, NullTest, null_test);
  break;
case T_BooleanTest:
  OUT_NODE(BooleanTest, BooleanTest, boolean_test, BooleanTest, boolean_test);
  break;
case T_CoerceToDomain:
  OUT_NODE(CoerceToDomain, CoerceToDomain, coerce_to_domain, CoerceToDomain, coerce_to_domain);
  break;
case T_CoerceToDomainValue:
  OUT_NODE(CoerceToDomainValue, CoerceToDomainValue, coerce_to_domain_value, CoerceToDomainValue, coerce_to_domain_value);
  break;
case T_SetToDefault:
  OUT_NODE(SetToDefault, SetToDefault, set_to_default, SetToDefault, set_to_default);
  break;
case T_CurrentOfExpr:
  OUT_NODE(CurrentOfExpr, CurrentOfExpr, current_of_expr, CurrentOfExpr, current_of_expr);
  break;
case T_NextValueExpr:
  OUT_NODE(NextValueExpr, NextValueExpr, next_value_expr, NextValueExpr, next_value_expr);
  break;
case T_InferenceElem:
  OUT_NODE(InferenceElem, InferenceElem, inference_elem, InferenceElem, inference_elem);
  break;
case T_TargetEntry:
  OUT_NODE(TargetEntry, TargetEntry, target_entry, TargetEntry, target_entry);
  break;
case T_RangeTblRef:
  OUT_NODE(RangeTblRef, RangeTblRef, range_tbl_ref, RangeTblRef, range_tbl_ref);
  break;
case T_JoinExpr:
  OUT_NODE(JoinExpr, JoinExpr, join_expr, JoinExpr, join_expr);
  break;
case T_FromExpr:
  OUT_NODE(FromExpr, FromExpr, from_expr, FromExpr, from_expr);
  break;
case T_OnConflictExpr:
  OUT_NODE(OnConflictExpr, OnConflictExpr, on_conflict_expr, OnConflictExpr, on_conflict_expr);
  break;
case T_IntoClause:
  OUT_NODE(IntoClause, IntoClause, into_clause, IntoClause, into_clause);
  break;
case T_RawStmt:
  OUT_NODE(RawStmt, RawStmt, raw_stmt, RawStmt, raw_stmt);
  break;
case T_Query:
  OUT_NODE(Query, Query, query, Query, query);
  break;
case T_InsertStmt:
  OUT_NODE(InsertStmt, InsertStmt, insert_stmt, InsertStmt, insert_stmt);
  break;
case T_DeleteStmt:
  OUT_NODE(DeleteStmt, DeleteStmt, delete_stmt, DeleteStmt, delete_stmt);
  break;
case T_UpdateStmt:
  OUT_NODE(UpdateStmt, UpdateStmt, update_stmt, UpdateStmt, update_stmt);
  break;
case T_SelectStmt:
  OUT_NODE(SelectStmt, SelectStmt, select_stmt, SelectStmt, select_stmt);
  break;
case T_AlterTableStmt:
  OUT_NODE(AlterTableStmt, AlterTableStmt, alter_table_stmt, AlterTableStmt, alter_table_stmt);
  break;
case T_AlterTableCmd:
  OUT_NODE(AlterTableCmd, AlterTableCmd, alter_table_cmd, AlterTableCmd, alter_table_cmd);
  break;
case T_AlterDomainStmt:
  OUT_NODE(AlterDomainStmt, AlterDomainStmt, alter_domain_stmt, AlterDomainStmt, alter_domain_stmt);
  break;
case T_SetOperationStmt:
  OUT_NODE(SetOperationStmt, SetOperationStmt, set_operation_stmt, SetOperationStmt, set_operation_stmt);
  break;
case T_GrantStmt:
  OUT_NODE(GrantStmt, GrantStmt, grant_stmt, GrantStmt, grant_stmt);
  break;
case T_GrantRoleStmt:
  OUT_NODE(GrantRoleStmt, GrantRoleStmt, grant_role_stmt, GrantRoleStmt, grant_role_stmt);
  break;
case T_AlterDefaultPrivilegesStmt:
  OUT_NODE(AlterDefaultPrivilegesStmt, AlterDefaultPrivilegesStmt, alter_default_privileges_stmt, AlterDefaultPrivilegesStmt, alter_default_privileges_stmt);
  break;
case T_ClosePortalStmt:
  OUT_NODE(ClosePortalStmt, ClosePortalStmt, close_portal_stmt, ClosePortalStmt, close_portal_stmt);
  break;
case T_ClusterStmt:
  OUT_NODE(ClusterStmt, ClusterStmt, cluster_stmt, ClusterStmt, cluster_stmt);
  break;
case T_CopyStmt:
  OUT_NODE(CopyStmt, CopyStmt, copy_stmt, CopyStmt, copy_stmt);
  break;
case T_CreateStmt:
  OUT_NODE(CreateStmt, CreateStmt, create_stmt, CreateStmt, create_stmt);
  break;
case T_DefineStmt:
  OUT_NODE(DefineStmt, DefineStmt, define_stmt, DefineStmt, define_stmt);
  break;
case T_DropStmt:
  OUT_NODE(DropStmt, DropStmt, drop_stmt, DropStmt, drop_stmt);
  break;
case T_TruncateStmt:
  OUT_NODE(TruncateStmt, TruncateStmt, truncate_stmt, TruncateStmt, truncate_stmt);
  break;
case T_CommentStmt:
  OUT_NODE(CommentStmt, CommentStmt, comment_stmt, CommentStmt, comment_stmt);
  break;
case T_FetchStmt:
  OUT_NODE(FetchStmt, FetchStmt, fetch_stmt, FetchStmt, fetch_stmt);
  break;
case T_IndexStmt:
  OUT_NODE(IndexStmt, IndexStmt, index_stmt, IndexStmt, index_stmt);
  break;
case T_CreateFunctionStmt:
  OUT_NODE(CreateFunctionStmt, CreateFunctionStmt, create_function_stmt, CreateFunctionStmt, create_function_stmt);
  break;
case T_AlterFunctionStmt:
  OUT_NODE(AlterFunctionStmt, AlterFunctionStmt, alter_function_stmt, AlterFunctionStmt, alter_function_stmt);
  break;
case T_DoStmt:
  OUT_NODE(DoStmt, DoStmt, do_stmt, DoStmt, do_stmt);
  break;
case T_RenameStmt:
  OUT_NODE(RenameStmt, RenameStmt, rename_stmt, RenameStmt, rename_stmt);
  break;
case T_RuleStmt:
  OUT_NODE(RuleStmt, RuleStmt, rule_stmt, RuleStmt, rule_stmt);
  break;
case T_NotifyStmt:
  OUT_NODE(NotifyStmt, NotifyStmt, notify_stmt, NotifyStmt, notify_stmt);
  break;
case T_ListenStmt:
  OUT_NODE(ListenStmt, ListenStmt, listen_stmt, ListenStmt, listen_stmt);
  break;
case T_UnlistenStmt:
  OUT_NODE(UnlistenStmt, UnlistenStmt, unlisten_stmt, UnlistenStmt, unlisten_stmt);
  break;
case T_TransactionStmt:
  OUT_NODE(TransactionStmt, TransactionStmt, transaction_stmt, TransactionStmt, transaction_stmt);
  break;
case T_ViewStmt:
  OUT_NODE(ViewStmt, ViewStmt, view_stmt, ViewStmt, view_stmt);
  break;
case T_LoadStmt:
  OUT_NODE(LoadStmt, LoadStmt, load_stmt, LoadStmt, load_stmt);
  break;
case T_CreateDomainStmt:
  OUT_NODE(CreateDomainStmt, CreateDomainStmt, create_domain_stmt, CreateDomainStmt, create_domain_stmt);
  break;
case T_CreatedbStmt:
  OUT_NODE(CreatedbStmt, CreatedbStmt, createdb_stmt, CreatedbStmt, createdb_stmt);
  break;
case T_DropdbStmt:
  OUT_NODE(DropdbStmt, DropdbStmt, dropdb_stmt, DropdbStmt, dropdb_stmt);
  break;
case T_VacuumStmt:
  OUT_NODE(VacuumStmt, VacuumStmt, vacuum_stmt, VacuumStmt, vacuum_stmt);
  break;
case T_ExplainStmt:
  OUT_NODE(ExplainStmt, ExplainStmt, explain_stmt, ExplainStmt, explain_stmt);
  break;
case T_CreateTableAsStmt:
  OUT_NODE(CreateTableAsStmt, CreateTableAsStmt, create_table_as_stmt, CreateTableAsStmt, create_table_as_stmt);
  break;
case T_CreateSeqStmt:
  OUT_NODE(CreateSeqStmt, CreateSeqStmt, create_seq_stmt, CreateSeqStmt, create_seq_stmt);
  break;
case T_AlterSeqStmt:
  OUT_NODE(AlterSeqStmt, AlterSeqStmt, alter_seq_stmt, AlterSeqStmt, alter_seq_stmt);
  break;
case T_VariableSetStmt:
  OUT_NODE(VariableSetStmt, VariableSetStmt, variable_set_stmt, VariableSetStmt, variable_set_stmt);
  break;
case T_VariableShowStmt:
  OUT_NODE(VariableShowStmt, VariableShowStmt, variable_show_stmt, VariableShowStmt, variable_show_stmt);
  break;
case T_DiscardStmt:
  OUT_NODE(DiscardStmt, DiscardStmt, discard_stmt, DiscardStmt, discard_stmt);
  break;
case T_CreateTrigStmt:
  OUT_NODE(CreateTrigStmt, CreateTrigStmt, create_trig_stmt, CreateTrigStmt, create_trig_stmt);
  break;
case T_CreatePLangStmt:
  OUT_NODE(CreatePLangStmt, CreatePLangStmt, create_plang_stmt, CreatePLangStmt, create_plang_stmt);
  break;
case T_CreateRoleStmt:
  OUT_NODE(CreateRoleStmt, CreateRoleStmt, create_role_stmt, CreateRoleStmt, create_role_stmt);
  break;
case T_AlterRoleStmt:
  OUT_NODE(AlterRoleStmt, AlterRoleStmt, alter_role_stmt, AlterRoleStmt, alter_role_stmt);
  break;
case T_DropRoleStmt:
  OUT_NODE(DropRoleStmt, DropRoleStmt, drop_role_stmt, DropRoleStmt, drop_role_stmt);
  break;
case T_LockStmt:
  OUT_NODE(LockStmt, LockStmt, lock_stmt, LockStmt, lock_stmt);
  break;
case T_ConstraintsSetStmt:
  OUT_NODE(ConstraintsSetStmt, ConstraintsSetStmt, constraints_set_stmt, ConstraintsSetStmt, constraints_set_stmt);
  break;
case T_ReindexStmt:
  OUT_NODE(ReindexStmt, ReindexStmt, reindex_stmt, ReindexStmt, reindex_stmt);
  break;
case T_CheckPointStmt:
  OUT_NODE(CheckPointStmt, CheckPointStmt, check_point_stmt, CheckPointStmt, check_point_stmt);
  break;
case T_CreateSchemaStmt:
  OUT_NODE(CreateSchemaStmt, CreateSchemaStmt, create_schema_stmt, CreateSchemaStmt, create_schema_stmt);
  break;
case T_AlterDatabaseStmt:
  OUT_NODE(AlterDatabaseStmt, AlterDatabaseStmt, alter_database_stmt, AlterDatabaseStmt, alter_database_stmt);
  break;
case T_AlterDatabaseSetStmt:
  OUT_NODE(AlterDatabaseSetStmt, AlterDatabaseSetStmt, alter_database_set_stmt, AlterDatabaseSetStmt, alter_database_set_stmt);
  break;
case T_AlterRoleSetStmt:
  OUT_NODE(AlterRoleSetStmt, AlterRoleSetStmt, alter_role_set_stmt, AlterRoleSetStmt, alter_role_set_stmt);
  break;
case T_CreateConversionStmt:
  OUT_NODE(CreateConversionStmt, CreateConversionStmt, create_conversion_stmt, CreateConversionStmt, create_conversion_stmt);
  break;
case T_CreateCastStmt:
  OUT_NODE(CreateCastStmt, CreateCastStmt, create_cast_stmt, CreateCastStmt, create_cast_stmt);
  break;
case T_CreateOpClassStmt:
  OUT_NODE(CreateOpClassStmt, CreateOpClassStmt, create_op_class_stmt, CreateOpClassStmt, create_op_class_stmt);
  break;
case T_CreateOpFamilyStmt:
  OUT_NODE(CreateOpFamilyStmt, CreateOpFamilyStmt, create_op_family_stmt, CreateOpFamilyStmt, create_op_family_stmt);
  break;
case T_AlterOpFamilyStmt:
  OUT_NODE(AlterOpFamilyStmt, AlterOpFamilyStmt, alter_op_family_stmt, AlterOpFamilyStmt, alter_op_family_stmt);
  break;
case T_PrepareStmt:
  OUT_NODE(PrepareStmt, PrepareStmt, prepare_stmt, PrepareStmt, prepare_stmt);
  break;
case T_ExecuteStmt:
  OUT_NODE(ExecuteStmt, ExecuteStmt, execute_stmt, ExecuteStmt, execute_stmt);
  break;
case T_DeallocateStmt:
  OUT_NODE(DeallocateStmt, DeallocateStmt, deallocate_stmt, DeallocateStmt, deallocate_stmt);
  break;
case T_DeclareCursorStmt:
  OUT_NODE(DeclareCursorStmt, DeclareCursorStmt, declare_cursor_stmt, DeclareCursorStmt, declare_cursor_stmt);
  break;
case T_CreateTableSpaceStmt:
  OUT_NODE(CreateTableSpaceStmt, CreateTableSpaceStmt, create_table_space_stmt, CreateTableSpaceStmt, create_table_space_stmt);
  break;
case T_DropTableSpaceStmt:
  OUT_NODE(DropTableSpaceStmt, DropTableSpaceStmt, drop_table_space_stmt, DropTableSpaceStmt, drop_table_space_stmt);
  break;
case T_AlterObjectDependsStmt:
  OUT_NODE(AlterObjectDependsStmt, AlterObjectDependsStmt, alter_object_depends_stmt, AlterObjectDependsStmt, alter_object_depends_stmt);
  break;
case T_AlterObjectSchemaStmt:
  OUT_NODE(AlterObjectSchemaStmt, AlterObjectSchemaStmt, alter_object_schema_stmt, AlterObjectSchemaStmt, alter_object_schema_stmt);
  break;
case T_AlterOwnerStmt:
  OUT_NODE(AlterOwnerStmt, AlterOwnerStmt, alter_owner_stmt, AlterOwnerStmt, alter_owner_stmt);
  break;
case T_AlterOperatorStmt:
  OUT_NODE(AlterOperatorStmt, AlterOperatorStmt, alter_operator_stmt, AlterOperatorStmt, alter_operator_stmt);
  break;
case T_AlterTypeStmt:
  OUT_NODE(AlterTypeStmt, AlterTypeStmt, alter_type_stmt, AlterTypeStmt, alter_type_stmt);
  break;
case T_DropOwnedStmt:
  OUT_NODE(DropOwnedStmt, DropOwnedStmt, drop_owned_stmt, DropOwnedStmt, drop_owned_stmt);
  break;
case T_ReassignOwnedStmt:
  OUT_NODE(ReassignOwnedStmt, ReassignOwnedStmt, reassign_owned_stmt, ReassignOwnedStmt, reassign_owned_stmt);
  break;
case T_CompositeTypeStmt:
  OUT_NODE(CompositeTypeStmt, CompositeTypeStmt, composite_type_stmt, CompositeTypeStmt, composite_type_stmt);
  break;
case T_CreateEnumStmt:
  OUT_NODE(CreateEnumStmt, CreateEnumStmt, create_enum_stmt, CreateEnumStmt, create_enum_stmt);
  break;
case T_CreateRangeStmt:
  OUT_NODE(CreateRangeStmt, CreateRangeStmt, create_range_stmt, CreateRangeStmt, create_range_stmt);
  break;
case T_AlterEnumStmt:
  OUT_NODE(AlterEnumStmt, AlterEnumStmt, alter_enum_stmt, AlterEnumStmt, alter_enum_stmt);
  break;
case T_AlterTSDictionaryStmt:
  OUT_NODE(AlterTSDictionaryStmt, AlterTSDictionaryStmt, alter_tsdictionary_stmt, AlterTSDictionaryStmt, alter_tsdictionary_stmt);
  break;
case T_AlterTSConfigurationStmt:
  OUT_NODE(AlterTSConfigurationStmt, AlterTSConfigurationStmt, alter_tsconfiguration_stmt, AlterTSConfigurationStmt, alter_tsconfiguration_stmt);
  break;
case T_CreateFdwStmt:
  OUT_NODE(CreateFdwStmt, CreateFdwStmt, create_fdw_stmt, CreateFdwStmt, create_fdw_stmt);
  break;
case T_AlterFdwStmt:
  OUT_NODE(AlterFdwStmt, AlterFdwStmt, alter_fdw_stmt, AlterFdwStmt, alter_fdw_stmt);
  break;
case T_CreateForeignServerStmt:
  OUT_NODE(CreateForeignServerStmt, CreateForeignServerStmt, create_foreign_server_stmt, CreateForeignServerStmt, create_foreign_server_stmt);
  break;
case T_AlterForeignServerStmt:
  OUT_NODE(AlterForeignServerStmt, AlterForeignServerStmt, alter_foreign_server_stmt, AlterForeignServerStmt, alter_foreign_server_stmt);
  break;
case T_CreateUserMappingStmt:
  OUT_NODE(CreateUserMappingStmt, CreateUserMappingStmt, create_user_mapping_stmt, CreateUserMappingStmt, create_user_mapping_stmt);
  break;
case T_AlterUserMappingStmt:
  OUT_NODE(AlterUserMappingStmt, AlterUserMappingStmt, alter_user_mapping_stmt, AlterUserMappingStmt, alter_user_mapping_stmt);
  break;
case T_DropUserMappingStmt:
  OUT_NODE(DropUserMappingStmt, DropUserMappingStmt, drop_user_mapping_stmt, DropUserMappingStmt, drop_user_mapping_stmt);
  break;
case T_AlterTableSpaceOptionsStmt:
  OUT_NODE(AlterTableSpaceOptionsStmt, AlterTableSpaceOptionsStmt, alter_table_space_options_stmt, AlterTableSpaceOptionsStmt, alter_table_space_options_stmt);
  break;
case T_AlterTableMoveAllStmt:
  OUT_NODE(AlterTableMoveAllStmt, AlterTableMoveAllStmt, alter_table_move_all_stmt, AlterTableMoveAllStmt, alter_table_move_all_stmt);
  break;
case T_SecLabelStmt:
  OUT_NODE(SecLabelStmt, SecLabelStmt, sec_label_stmt, SecLabelStmt, sec_label_stmt);
  break;
case T_CreateForeignTableStmt:
  OUT_NODE(CreateForeignTableStmt, CreateForeignTableStmt, create_foreign_table_stmt, CreateForeignTableStmt, create_foreign_table_stmt);
  break;
case T_ImportForeignSchemaStmt:
  OUT_NODE(ImportForeignSchemaStmt, ImportForeignSchemaStmt, import_foreign_schema_stmt, ImportForeignSchemaStmt, import_foreign_schema_stmt);
  break;
case T_CreateExtensionStmt:
  OUT_NODE(CreateExtensionStmt, CreateExtensionStmt, create_extension_stmt, CreateExtensionStmt, create_extension_stmt);
  break;
case T_AlterExtensionStmt:
  OUT_NODE(AlterExtensionStmt, AlterExtensionStmt, alter_extension_stmt, AlterExtensionStmt, alter_extension_stmt);
  break;
case T_AlterExtensionContentsStmt:
  OUT_NODE(AlterExtensionContentsStmt, AlterExtensionContentsStmt, alter_extension_contents_stmt, AlterExtensionContentsStmt, alter_extension_contents_stmt);
  break;
case T_CreateEventTrigStmt:
  OUT_NODE(CreateEventTrigStmt, CreateEventTrigStmt, create_event_trig_stmt, CreateEventTrigStmt, create_event_trig_stmt);
  break;
case T_AlterEventTrigStmt:
  OUT_NODE(AlterEventTrigStmt, AlterEventTrigStmt, alter_event_trig_stmt, AlterEventTrigStmt, alter_event_trig_stmt);
  break;
case T_RefreshMatViewStmt:
  OUT_NODE(RefreshMatViewStmt, RefreshMatViewStmt, refresh_mat_view_stmt, RefreshMatViewStmt, refresh_mat_view_stmt);
  break;
case T_ReplicaIdentityStmt:
  OUT_NODE(ReplicaIdentityStmt, ReplicaIdentityStmt, replica_identity_stmt, ReplicaIdentityStmt, replica_identity_stmt);
  break;
case T_AlterSystemStmt:
  OUT_NODE(AlterSystemStmt, AlterSystemStmt, alter_system_stmt, AlterSystemStmt, alter_system_stmt);
  break;
case T_CreatePolicyStmt:
  OUT_NODE(CreatePolicyStmt, CreatePolicyStmt, create_policy_stmt, CreatePolicyStmt, create_policy_stmt);
  break;
case T_AlterPolicyStmt:
  OUT_NODE(AlterPolicyStmt, AlterPolicyStmt, alter_policy_stmt, AlterPolicyStmt, alter_policy_stmt);
  break;
case T_CreateTransformStmt:
  OUT_NODE(CreateTransformStmt, CreateTransformStmt, create_transform_stmt, CreateTransformStmt, create_transform_stmt);
  break;
case T_CreateAmStmt:
  OUT_NODE(CreateAmStmt, CreateAmStmt, create_am_stmt, CreateAmStmt, create_am_stmt);
  break;
case T_CreatePublicationStmt:
  OUT_NODE(CreatePublicationStmt, CreatePublicationStmt, create_publication_stmt, CreatePublicationStmt, create_publication_stmt);
  break;
case T_AlterPublicationStmt:
  OUT_NODE(AlterPublicationStmt, AlterPublicationStmt, alter_publication_stmt, AlterPublicationStmt, alter_publication_stmt);
  break;
case T_CreateSubscriptionStmt:
  OUT_NODE(CreateSubscriptionStmt, CreateSubscriptionStmt, create_subscription_stmt, CreateSubscriptionStmt, create_subscription_stmt);
  break;
case T_AlterSubscriptionStmt:
  OUT_NODE(AlterSubscriptionStmt, AlterSubscriptionStmt, alter_subscription_stmt, AlterSubscriptionStmt, alter_subscription_stmt);
  break;
case T_DropSubscriptionStmt:
  OUT_NODE(DropSubscriptionStmt, DropSubscriptionStmt, drop_subscription_stmt, DropSubscriptionStmt, drop_subscription_stmt);
  break;
case T_CreateStatsStmt:
  OUT_NODE(CreateStatsStmt, CreateStatsStmt, create_stats_stmt, CreateStatsStmt, create_stats_stmt);
  break;
case T_AlterCollationStmt:
  OUT_NODE(AlterCollationStmt, AlterCollationStmt, alter_collation_stmt, AlterCollationStmt, alter_collation_stmt);
  break;
case T_CallStmt:
  OUT_NODE(CallStmt, CallStmt, call_stmt, CallStmt, call_stmt);
  break;
case T_AlterStatsStmt:
  OUT_NODE(AlterStatsStmt, AlterStatsStmt, alter_stats_stmt, AlterStatsStmt, alter_stats_stmt);
  break;
case T_A_Expr:
  OUT_NODE(A_Expr, AExpr, a__expr, A_Expr, a_expr);
  break;
case T_ColumnRef:
  OUT_NODE(ColumnRef, ColumnRef, column_ref, ColumnRef, column_ref);
  break;
case T_ParamRef:
  OUT_NODE(ParamRef, ParamRef, param_ref, ParamRef, param_ref);
  break;
case T_A_Const:
  OUT_NODE(A_Const, AConst, a__const, A_Const, a_const);
  break;
case T_FuncCall:
  OUT_NODE(FuncCall, FuncCall, func_call, FuncCall, func_call);
  break;
case T_A_Star:
  OUT_NODE(A_Star, AStar, a__star, A_Star, a_star);
  break;
case T_A_Indices:
  OUT_NODE(A_Indices, AIndices, a__indices, A_Indices, a_indices);
  break;
case T_A_Indirection:
  OUT_NODE(A_Indirection, AIndirection, a__indirection, A_Indirection, a_indirection);
  break;
case T_A_ArrayExpr:
  OUT_NODE(A_ArrayExpr, AArrayExpr, a__array_expr, A_ArrayExpr, a_array_expr);
  break;
case T_ResTarget:
  OUT_NODE(ResTarget, ResTarget, res_target, ResTarget, res_target);
  break;
case T_MultiAssignRef:
  OUT_NODE(MultiAssignRef, MultiAssignRef, multi_assign_ref, MultiAssignRef, multi_assign_ref);
  break;
case T_TypeCast:
  OUT_NODE(TypeCast, TypeCast, type_cast, TypeCast, type_cast);
  break;
case T_CollateClause:
  OUT_NODE(CollateClause, CollateClause, collate_clause, CollateClause, collate_clause);
  break;
case T_SortBy:
  OUT_NODE(SortBy, SortBy, sort_by, SortBy, sort_by);
  break;
case T_WindowDef:
  OUT_NODE(WindowDef, WindowDef, window_def, WindowDef, window_def);
  break;
case T_RangeSubselect:
  OUT_NODE(RangeSubselect, RangeSubselect, range_subselect, RangeSubselect, range_subselect);
  break;
case T_RangeFunction:
  OUT_NODE(RangeFunction, RangeFunction, range_function, RangeFunction, range_function);
  break;
case T_RangeTableSample:
  OUT_NODE(RangeTableSample, RangeTableSample, range_table_sample, RangeTableSample, range_table_sample);
  break;
case T_RangeTableFunc:
  OUT_NODE(RangeTableFunc, RangeTableFunc, range_table_func, RangeTableFunc, range_table_func);
  break;
case T_RangeTableFuncCol:
  OUT_NODE(RangeTableFuncCol, RangeTableFuncCol, range_table_func_col, RangeTableFuncCol, range_table_func_col);
  break;
case T_TypeName:
  OUT_NODE(TypeName, TypeName, type_name, TypeName, type_name);
  break;
case T_ColumnDef:
  OUT_NODE(ColumnDef, ColumnDef, column_def, ColumnDef, column_def);
  break;
case T_IndexElem:
  OUT_NODE(IndexElem, IndexElem, index_elem, IndexElem, index_elem);
  break;
case T_Constraint:
  OUT_NODE(Constraint, Constraint, constraint, Constraint, constraint);
  break;
case T_DefElem:
  OUT_NODE(DefElem, DefElem, def_elem, DefElem, def_elem);
  break;
case T_RangeTblEntry:
  OUT_NODE(RangeTblEntry, RangeTblEntry, range_tbl_entry, RangeTblEntry, range_tbl_entry);
  break;
case T_RangeTblFunction:
  OUT_NODE(RangeTblFunction, RangeTblFunction, range_tbl_function, RangeTblFunction, range_tbl_function);
  break;
case T_TableSampleClause:
  OUT_NODE(TableSampleClause, TableSampleClause, table_sample_clause, TableSampleClause, table_sample_clause);
  break;
case T_WithCheckOption:
  OUT_NODE(WithCheckOption, WithCheckOption, with_check_option, WithCheckOption, with_check_option);
  break;
case T_SortGroupClause:
  OUT_NODE(SortGroupClause, SortGroupClause, sort_group_clause, SortGroupClause, sort_group_clause);
  break;
case T_GroupingSet:
  OUT_NODE(GroupingSet, GroupingSet, grouping_set, GroupingSet, grouping_set);
  break;
case T_WindowClause:
  OUT_NODE(WindowClause, WindowClause, window_clause, WindowClause, window_clause);
  break;
case T_ObjectWithArgs:
  OUT_NODE(ObjectWithArgs, ObjectWithArgs, object_with_args, ObjectWithArgs, object_with_args);
  break;
case T_AccessPriv:
  OUT_NODE(AccessPriv, AccessPriv, access_priv, AccessPriv, access_priv);
  break;
case T_CreateOpClassItem:
  OUT_NODE(CreateOpClassItem, CreateOpClassItem, create_op_class_item, CreateOpClassItem, create_op_class_item);
  break;
case T_TableLikeClause:
  OUT_NODE(TableLikeClause, TableLikeClause, table_like_clause, TableLikeClause, table_like_clause);
  break;
case T_FunctionParameter:
  OUT_NODE(FunctionParameter, FunctionParameter, function_parameter, FunctionParameter, function_parameter);
  break;
case T_LockingClause:
  OUT_NODE(LockingClause, LockingClause, locking_clause, LockingClause, locking_clause);
  break;
case T_RowMarkClause:
  OUT_NODE(RowMarkClause, RowMarkClause, row_mark_clause, RowMarkClause, row_mark_clause);
  break;
case T_XmlSerialize:
  OUT_NODE(XmlSerialize, XmlSerialize, xml_serialize, XmlSerialize, xml_serialize);
  break;
case T_WithClause:
  OUT_NODE(WithClause, WithClause, with_clause, WithClause, with_clause);
  break;
case T_InferClause:
  OUT_NODE(InferClause, InferClause, infer_clause, InferClause, infer_clause);
  break;
case T_OnConflictClause:
  OUT_NODE(OnConflictClause, OnConflictClause, on_conflict_clause, OnConflictClause, on_conflict_clause);
  break;
case T_CommonTableExpr:
  OUT_NODE(CommonTableExpr, CommonTableExpr, common_table_expr, CommonTableExpr, common_table_expr);
  break;
case T_RoleSpec:
  OUT_NODE(RoleSpec, RoleSpec, role_spec, RoleSpec, role_spec);
  break;
case T_TriggerTransition:
  OUT_NODE(TriggerTransition, TriggerTransition, trigger_transition, TriggerTransition, trigger_transition);
  break;
case T_PartitionElem:
  OUT_NODE(PartitionElem, PartitionElem, partition_elem, PartitionElem, partition_elem);
  break;
case T_PartitionSpec:
  OUT_NODE(PartitionSpec, PartitionSpec, partition_spec, PartitionSpec, partition_spec);
  break;
case T_PartitionBoundSpec:
  OUT_NODE(PartitionBoundSpec, PartitionBoundSpec, partition_bound_spec, PartitionBoundSpec, partition_bound_spec);
  break;
case T_PartitionRangeDatum:
  OUT_NODE(PartitionRangeDatum, PartitionRangeDatum, partition_range_datum, PartitionRangeDatum, partition_range_datum);
  break;
case T_PartitionCmd:
  OUT_NODE(PartitionCmd, PartitionCmd, partition_cmd, PartitionCmd, partition_cmd);
  break;
case T_VacuumRelation:
  OUT_NODE(VacuumRelation, VacuumRelation, vacuum_relation, VacuumRelation, vacuum_relation);
  break;
case T_InlineCodeBlock:
  OUT_NODE(InlineCodeBlock, InlineCodeBlock, inline_code_block, InlineCodeBlock, inline_code_block);
  break;
case T_CallContext:
  OUT_NODE(CallContext, CallContext, call_context, CallContext, call_context);
  break;