case T_Alias:
  _fingerprintAlias(ctx, obj, field_name);
  break;
case T_RangeVar:
  _fingerprintRangeVar(ctx, obj, field_name);
  break;
case T_Expr:
  _fingerprintExpr(ctx, obj, field_name);
  break;
case T_Var:
  _fingerprintVar(ctx, obj, field_name);
  break;
case T_Const:
  _fingerprintConst(ctx, obj, field_name);
  break;
case T_Param:
  _fingerprintParam(ctx, obj, field_name);
  break;
case T_Aggref:
  _fingerprintAggref(ctx, obj, field_name);
  break;
case T_GroupingFunc:
  _fingerprintGroupingFunc(ctx, obj, field_name);
  break;
case T_WindowFunc:
  _fingerprintWindowFunc(ctx, obj, field_name);
  break;
case T_ArrayRef:
  _fingerprintArrayRef(ctx, obj, field_name);
  break;
case T_FuncExpr:
  _fingerprintFuncExpr(ctx, obj, field_name);
  break;
case T_NamedArgExpr:
  _fingerprintNamedArgExpr(ctx, obj, field_name);
  break;
case T_OpExpr:
  _fingerprintOpExpr(ctx, obj, field_name);
  break;
case T_ScalarArrayOpExpr:
  _fingerprintScalarArrayOpExpr(ctx, obj, field_name);
  break;
case T_BoolExpr:
  _fingerprintBoolExpr(ctx, obj, field_name);
  break;
case T_SubLink:
  _fingerprintSubLink(ctx, obj, field_name);
  break;
case T_SubPlan:
  _fingerprintSubPlan(ctx, obj, field_name);
  break;
case T_AlternativeSubPlan:
  _fingerprintAlternativeSubPlan(ctx, obj, field_name);
  break;
case T_FieldSelect:
  _fingerprintFieldSelect(ctx, obj, field_name);
  break;
case T_FieldStore:
  _fingerprintFieldStore(ctx, obj, field_name);
  break;
case T_RelabelType:
  _fingerprintRelabelType(ctx, obj, field_name);
  break;
case T_CoerceViaIO:
  _fingerprintCoerceViaIO(ctx, obj, field_name);
  break;
case T_ArrayCoerceExpr:
  _fingerprintArrayCoerceExpr(ctx, obj, field_name);
  break;
case T_ConvertRowtypeExpr:
  _fingerprintConvertRowtypeExpr(ctx, obj, field_name);
  break;
case T_CollateExpr:
  _fingerprintCollateExpr(ctx, obj, field_name);
  break;
case T_CaseExpr:
  _fingerprintCaseExpr(ctx, obj, field_name);
  break;
case T_CaseWhen:
  _fingerprintCaseWhen(ctx, obj, field_name);
  break;
case T_CaseTestExpr:
  _fingerprintCaseTestExpr(ctx, obj, field_name);
  break;
case T_ArrayExpr:
  _fingerprintArrayExpr(ctx, obj, field_name);
  break;
case T_RowExpr:
  _fingerprintRowExpr(ctx, obj, field_name);
  break;
case T_RowCompareExpr:
  _fingerprintRowCompareExpr(ctx, obj, field_name);
  break;
case T_CoalesceExpr:
  _fingerprintCoalesceExpr(ctx, obj, field_name);
  break;
case T_MinMaxExpr:
  _fingerprintMinMaxExpr(ctx, obj, field_name);
  break;
case T_XmlExpr:
  _fingerprintXmlExpr(ctx, obj, field_name);
  break;
case T_NullTest:
  _fingerprintNullTest(ctx, obj, field_name);
  break;
case T_BooleanTest:
  _fingerprintBooleanTest(ctx, obj, field_name);
  break;
case T_CoerceToDomain:
  _fingerprintCoerceToDomain(ctx, obj, field_name);
  break;
case T_CoerceToDomainValue:
  _fingerprintCoerceToDomainValue(ctx, obj, field_name);
  break;
case T_SetToDefault:
  _fingerprintSetToDefault(ctx, obj, field_name);
  break;
case T_CurrentOfExpr:
  _fingerprintCurrentOfExpr(ctx, obj, field_name);
  break;
case T_InferenceElem:
  _fingerprintInferenceElem(ctx, obj, field_name);
  break;
case T_TargetEntry:
  _fingerprintTargetEntry(ctx, obj, field_name);
  break;
case T_RangeTblRef:
  _fingerprintRangeTblRef(ctx, obj, field_name);
  break;
case T_JoinExpr:
  _fingerprintJoinExpr(ctx, obj, field_name);
  break;
case T_FromExpr:
  _fingerprintFromExpr(ctx, obj, field_name);
  break;
case T_OnConflictExpr:
  _fingerprintOnConflictExpr(ctx, obj, field_name);
  break;
case T_IntoClause:
  _fingerprintIntoClause(ctx, obj, field_name);
  break;
case T_Query:
  _fingerprintQuery(ctx, obj, field_name);
  break;
case T_InsertStmt:
  _fingerprintInsertStmt(ctx, obj, field_name);
  break;
case T_DeleteStmt:
  _fingerprintDeleteStmt(ctx, obj, field_name);
  break;
case T_UpdateStmt:
  _fingerprintUpdateStmt(ctx, obj, field_name);
  break;
case T_SelectStmt:
  _fingerprintSelectStmt(ctx, obj, field_name);
  break;
case T_AlterTableStmt:
  _fingerprintAlterTableStmt(ctx, obj, field_name);
  break;
case T_AlterTableCmd:
  _fingerprintAlterTableCmd(ctx, obj, field_name);
  break;
case T_AlterDomainStmt:
  _fingerprintAlterDomainStmt(ctx, obj, field_name);
  break;
case T_SetOperationStmt:
  _fingerprintSetOperationStmt(ctx, obj, field_name);
  break;
case T_GrantStmt:
  _fingerprintGrantStmt(ctx, obj, field_name);
  break;
case T_GrantRoleStmt:
  _fingerprintGrantRoleStmt(ctx, obj, field_name);
  break;
case T_AlterDefaultPrivilegesStmt:
  _fingerprintAlterDefaultPrivilegesStmt(ctx, obj, field_name);
  break;
case T_ClosePortalStmt:
  _fingerprintClosePortalStmt(ctx, obj, field_name);
  break;
case T_ClusterStmt:
  _fingerprintClusterStmt(ctx, obj, field_name);
  break;
case T_CopyStmt:
  _fingerprintCopyStmt(ctx, obj, field_name);
  break;
case T_CreateStmt:
  _fingerprintCreateStmt(ctx, obj, field_name);
  break;
case T_DefineStmt:
  _fingerprintDefineStmt(ctx, obj, field_name);
  break;
case T_DropStmt:
  _fingerprintDropStmt(ctx, obj, field_name);
  break;
case T_TruncateStmt:
  _fingerprintTruncateStmt(ctx, obj, field_name);
  break;
case T_CommentStmt:
  _fingerprintCommentStmt(ctx, obj, field_name);
  break;
case T_FetchStmt:
  _fingerprintFetchStmt(ctx, obj, field_name);
  break;
case T_IndexStmt:
  _fingerprintIndexStmt(ctx, obj, field_name);
  break;
case T_CreateFunctionStmt:
  _fingerprintCreateFunctionStmt(ctx, obj, field_name);
  break;
case T_AlterFunctionStmt:
  _fingerprintAlterFunctionStmt(ctx, obj, field_name);
  break;
case T_DoStmt:
  _fingerprintDoStmt(ctx, obj, field_name);
  break;
case T_RenameStmt:
  _fingerprintRenameStmt(ctx, obj, field_name);
  break;
case T_RuleStmt:
  _fingerprintRuleStmt(ctx, obj, field_name);
  break;
case T_NotifyStmt:
  _fingerprintNotifyStmt(ctx, obj, field_name);
  break;
case T_ListenStmt:
  _fingerprintListenStmt(ctx, obj, field_name);
  break;
case T_UnlistenStmt:
  _fingerprintUnlistenStmt(ctx, obj, field_name);
  break;
case T_TransactionStmt:
  _fingerprintTransactionStmt(ctx, obj, field_name);
  break;
case T_ViewStmt:
  _fingerprintViewStmt(ctx, obj, field_name);
  break;
case T_LoadStmt:
  _fingerprintLoadStmt(ctx, obj, field_name);
  break;
case T_CreateDomainStmt:
  _fingerprintCreateDomainStmt(ctx, obj, field_name);
  break;
case T_CreatedbStmt:
  _fingerprintCreatedbStmt(ctx, obj, field_name);
  break;
case T_DropdbStmt:
  _fingerprintDropdbStmt(ctx, obj, field_name);
  break;
case T_VacuumStmt:
  _fingerprintVacuumStmt(ctx, obj, field_name);
  break;
case T_ExplainStmt:
  _fingerprintExplainStmt(ctx, obj, field_name);
  break;
case T_CreateTableAsStmt:
  _fingerprintCreateTableAsStmt(ctx, obj, field_name);
  break;
case T_CreateSeqStmt:
  _fingerprintCreateSeqStmt(ctx, obj, field_name);
  break;
case T_AlterSeqStmt:
  _fingerprintAlterSeqStmt(ctx, obj, field_name);
  break;
case T_VariableSetStmt:
  _fingerprintVariableSetStmt(ctx, obj, field_name);
  break;
case T_VariableShowStmt:
  _fingerprintVariableShowStmt(ctx, obj, field_name);
  break;
case T_DiscardStmt:
  _fingerprintDiscardStmt(ctx, obj, field_name);
  break;
case T_CreateTrigStmt:
  _fingerprintCreateTrigStmt(ctx, obj, field_name);
  break;
case T_CreatePLangStmt:
  _fingerprintCreatePLangStmt(ctx, obj, field_name);
  break;
case T_CreateRoleStmt:
  _fingerprintCreateRoleStmt(ctx, obj, field_name);
  break;
case T_AlterRoleStmt:
  _fingerprintAlterRoleStmt(ctx, obj, field_name);
  break;
case T_DropRoleStmt:
  _fingerprintDropRoleStmt(ctx, obj, field_name);
  break;
case T_LockStmt:
  _fingerprintLockStmt(ctx, obj, field_name);
  break;
case T_ConstraintsSetStmt:
  _fingerprintConstraintsSetStmt(ctx, obj, field_name);
  break;
case T_ReindexStmt:
  _fingerprintReindexStmt(ctx, obj, field_name);
  break;
case T_CheckPointStmt:
  _fingerprintCheckPointStmt(ctx, obj, field_name);
  break;
case T_CreateSchemaStmt:
  _fingerprintCreateSchemaStmt(ctx, obj, field_name);
  break;
case T_AlterDatabaseStmt:
  _fingerprintAlterDatabaseStmt(ctx, obj, field_name);
  break;
case T_AlterDatabaseSetStmt:
  _fingerprintAlterDatabaseSetStmt(ctx, obj, field_name);
  break;
case T_AlterRoleSetStmt:
  _fingerprintAlterRoleSetStmt(ctx, obj, field_name);
  break;
case T_CreateConversionStmt:
  _fingerprintCreateConversionStmt(ctx, obj, field_name);
  break;
case T_CreateCastStmt:
  _fingerprintCreateCastStmt(ctx, obj, field_name);
  break;
case T_CreateOpClassStmt:
  _fingerprintCreateOpClassStmt(ctx, obj, field_name);
  break;
case T_CreateOpFamilyStmt:
  _fingerprintCreateOpFamilyStmt(ctx, obj, field_name);
  break;
case T_AlterOpFamilyStmt:
  _fingerprintAlterOpFamilyStmt(ctx, obj, field_name);
  break;
case T_PrepareStmt:
  _fingerprintPrepareStmt(ctx, obj, field_name);
  break;
case T_ExecuteStmt:
  _fingerprintExecuteStmt(ctx, obj, field_name);
  break;
case T_DeallocateStmt:
  _fingerprintDeallocateStmt(ctx, obj, field_name);
  break;
case T_DeclareCursorStmt:
  _fingerprintDeclareCursorStmt(ctx, obj, field_name);
  break;
case T_CreateTableSpaceStmt:
  _fingerprintCreateTableSpaceStmt(ctx, obj, field_name);
  break;
case T_DropTableSpaceStmt:
  _fingerprintDropTableSpaceStmt(ctx, obj, field_name);
  break;
case T_AlterObjectSchemaStmt:
  _fingerprintAlterObjectSchemaStmt(ctx, obj, field_name);
  break;
case T_AlterOwnerStmt:
  _fingerprintAlterOwnerStmt(ctx, obj, field_name);
  break;
case T_DropOwnedStmt:
  _fingerprintDropOwnedStmt(ctx, obj, field_name);
  break;
case T_ReassignOwnedStmt:
  _fingerprintReassignOwnedStmt(ctx, obj, field_name);
  break;
case T_CompositeTypeStmt:
  _fingerprintCompositeTypeStmt(ctx, obj, field_name);
  break;
case T_CreateEnumStmt:
  _fingerprintCreateEnumStmt(ctx, obj, field_name);
  break;
case T_CreateRangeStmt:
  _fingerprintCreateRangeStmt(ctx, obj, field_name);
  break;
case T_AlterEnumStmt:
  _fingerprintAlterEnumStmt(ctx, obj, field_name);
  break;
case T_AlterTSDictionaryStmt:
  _fingerprintAlterTSDictionaryStmt(ctx, obj, field_name);
  break;
case T_AlterTSConfigurationStmt:
  _fingerprintAlterTSConfigurationStmt(ctx, obj, field_name);
  break;
case T_CreateFdwStmt:
  _fingerprintCreateFdwStmt(ctx, obj, field_name);
  break;
case T_AlterFdwStmt:
  _fingerprintAlterFdwStmt(ctx, obj, field_name);
  break;
case T_CreateForeignServerStmt:
  _fingerprintCreateForeignServerStmt(ctx, obj, field_name);
  break;
case T_AlterForeignServerStmt:
  _fingerprintAlterForeignServerStmt(ctx, obj, field_name);
  break;
case T_CreateUserMappingStmt:
  _fingerprintCreateUserMappingStmt(ctx, obj, field_name);
  break;
case T_AlterUserMappingStmt:
  _fingerprintAlterUserMappingStmt(ctx, obj, field_name);
  break;
case T_DropUserMappingStmt:
  _fingerprintDropUserMappingStmt(ctx, obj, field_name);
  break;
case T_AlterTableSpaceOptionsStmt:
  _fingerprintAlterTableSpaceOptionsStmt(ctx, obj, field_name);
  break;
case T_AlterTableMoveAllStmt:
  _fingerprintAlterTableMoveAllStmt(ctx, obj, field_name);
  break;
case T_SecLabelStmt:
  _fingerprintSecLabelStmt(ctx, obj, field_name);
  break;
case T_CreateForeignTableStmt:
  _fingerprintCreateForeignTableStmt(ctx, obj, field_name);
  break;
case T_ImportForeignSchemaStmt:
  _fingerprintImportForeignSchemaStmt(ctx, obj, field_name);
  break;
case T_CreateExtensionStmt:
  _fingerprintCreateExtensionStmt(ctx, obj, field_name);
  break;
case T_AlterExtensionStmt:
  _fingerprintAlterExtensionStmt(ctx, obj, field_name);
  break;
case T_AlterExtensionContentsStmt:
  _fingerprintAlterExtensionContentsStmt(ctx, obj, field_name);
  break;
case T_CreateEventTrigStmt:
  _fingerprintCreateEventTrigStmt(ctx, obj, field_name);
  break;
case T_AlterEventTrigStmt:
  _fingerprintAlterEventTrigStmt(ctx, obj, field_name);
  break;
case T_RefreshMatViewStmt:
  _fingerprintRefreshMatViewStmt(ctx, obj, field_name);
  break;
case T_ReplicaIdentityStmt:
  _fingerprintReplicaIdentityStmt(ctx, obj, field_name);
  break;
case T_AlterSystemStmt:
  _fingerprintAlterSystemStmt(ctx, obj, field_name);
  break;
case T_CreatePolicyStmt:
  _fingerprintCreatePolicyStmt(ctx, obj, field_name);
  break;
case T_AlterPolicyStmt:
  _fingerprintAlterPolicyStmt(ctx, obj, field_name);
  break;
case T_CreateTransformStmt:
  _fingerprintCreateTransformStmt(ctx, obj, field_name);
  break;
case T_A_Expr:
  _fingerprintA_Expr(ctx, obj, field_name);
  break;
case T_ColumnRef:
  _fingerprintColumnRef(ctx, obj, field_name);
  break;
case T_ParamRef:
  _fingerprintParamRef(ctx, obj, field_name);
  break;
case T_A_Const:
  _fingerprintA_Const(ctx, obj, field_name);
  break;
case T_FuncCall:
  _fingerprintFuncCall(ctx, obj, field_name);
  break;
case T_A_Star:
  _fingerprintA_Star(ctx, obj, field_name);
  break;
case T_A_Indices:
  _fingerprintA_Indices(ctx, obj, field_name);
  break;
case T_A_Indirection:
  _fingerprintA_Indirection(ctx, obj, field_name);
  break;
case T_A_ArrayExpr:
  _fingerprintA_ArrayExpr(ctx, obj, field_name);
  break;
case T_ResTarget:
  _fingerprintResTarget(ctx, obj, field_name);
  break;
case T_MultiAssignRef:
  _fingerprintMultiAssignRef(ctx, obj, field_name);
  break;
case T_TypeCast:
  _fingerprintTypeCast(ctx, obj, field_name);
  break;
case T_CollateClause:
  _fingerprintCollateClause(ctx, obj, field_name);
  break;
case T_SortBy:
  _fingerprintSortBy(ctx, obj, field_name);
  break;
case T_WindowDef:
  _fingerprintWindowDef(ctx, obj, field_name);
  break;
case T_RangeSubselect:
  _fingerprintRangeSubselect(ctx, obj, field_name);
  break;
case T_RangeFunction:
  _fingerprintRangeFunction(ctx, obj, field_name);
  break;
case T_RangeTableSample:
  _fingerprintRangeTableSample(ctx, obj, field_name);
  break;
case T_TypeName:
  _fingerprintTypeName(ctx, obj, field_name);
  break;
case T_ColumnDef:
  _fingerprintColumnDef(ctx, obj, field_name);
  break;
case T_IndexElem:
  _fingerprintIndexElem(ctx, obj, field_name);
  break;
case T_Constraint:
  _fingerprintConstraint(ctx, obj, field_name);
  break;
case T_DefElem:
  _fingerprintDefElem(ctx, obj, field_name);
  break;
case T_RangeTblEntry:
  _fingerprintRangeTblEntry(ctx, obj, field_name);
  break;
case T_RangeTblFunction:
  _fingerprintRangeTblFunction(ctx, obj, field_name);
  break;
case T_TableSampleClause:
  _fingerprintTableSampleClause(ctx, obj, field_name);
  break;
case T_WithCheckOption:
  _fingerprintWithCheckOption(ctx, obj, field_name);
  break;
case T_SortGroupClause:
  _fingerprintSortGroupClause(ctx, obj, field_name);
  break;
case T_GroupingSet:
  _fingerprintGroupingSet(ctx, obj, field_name);
  break;
case T_WindowClause:
  _fingerprintWindowClause(ctx, obj, field_name);
  break;
case T_FuncWithArgs:
  _fingerprintFuncWithArgs(ctx, obj, field_name);
  break;
case T_AccessPriv:
  _fingerprintAccessPriv(ctx, obj, field_name);
  break;
case T_CreateOpClassItem:
  _fingerprintCreateOpClassItem(ctx, obj, field_name);
  break;
case T_TableLikeClause:
  _fingerprintTableLikeClause(ctx, obj, field_name);
  break;
case T_FunctionParameter:
  _fingerprintFunctionParameter(ctx, obj, field_name);
  break;
case T_LockingClause:
  _fingerprintLockingClause(ctx, obj, field_name);
  break;
case T_RowMarkClause:
  _fingerprintRowMarkClause(ctx, obj, field_name);
  break;
case T_XmlSerialize:
  _fingerprintXmlSerialize(ctx, obj, field_name);
  break;
case T_WithClause:
  _fingerprintWithClause(ctx, obj, field_name);
  break;
case T_InferClause:
  _fingerprintInferClause(ctx, obj, field_name);
  break;
case T_OnConflictClause:
  _fingerprintOnConflictClause(ctx, obj, field_name);
  break;
case T_CommonTableExpr:
  _fingerprintCommonTableExpr(ctx, obj, field_name);
  break;
case T_RoleSpec:
  _fingerprintRoleSpec(ctx, obj, field_name);
  break;
case T_InlineCodeBlock:
  _fingerprintInlineCodeBlock(ctx, obj, field_name);
  break;
