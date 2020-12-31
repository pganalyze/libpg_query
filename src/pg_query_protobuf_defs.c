static void _outAlias(PgQuery__Alias * out_node, const Alias *node);
static void _outRangeVar(PgQuery__RangeVar * out_node, const RangeVar *node);
static void _outTableFunc(PgQuery__TableFunc * out_node, const TableFunc *node);
static void _outExpr(PgQuery__Expr * out_node, const Expr *node);
static void _outVar(PgQuery__Var * out_node, const Var *node);
static void _outParam(PgQuery__Param * out_node, const Param *node);
static void _outAggref(PgQuery__Aggref * out_node, const Aggref *node);
static void _outGroupingFunc(PgQuery__GroupingFunc * out_node, const GroupingFunc *node);
static void _outWindowFunc(PgQuery__WindowFunc * out_node, const WindowFunc *node);
static void _outSubscriptingRef(PgQuery__SubscriptingRef * out_node, const SubscriptingRef *node);
static void _outFuncExpr(PgQuery__FuncExpr * out_node, const FuncExpr *node);
static void _outNamedArgExpr(PgQuery__NamedArgExpr * out_node, const NamedArgExpr *node);
static void _outOpExpr(PgQuery__OpExpr * out_node, const OpExpr *node);
static void _outDistinctExpr(PgQuery__DistinctExpr * out_node, const DistinctExpr *node);
static void _outNullIfExpr(PgQuery__NullIfExpr * out_node, const NullIfExpr *node);
static void _outScalarArrayOpExpr(PgQuery__ScalarArrayOpExpr * out_node, const ScalarArrayOpExpr *node);
static void _outBoolExpr(PgQuery__BoolExpr * out_node, const BoolExpr *node);
static void _outSubLink(PgQuery__SubLink * out_node, const SubLink *node);
static void _outSubPlan(PgQuery__SubPlan * out_node, const SubPlan *node);
static void _outAlternativeSubPlan(PgQuery__AlternativeSubPlan * out_node, const AlternativeSubPlan *node);
static void _outFieldSelect(PgQuery__FieldSelect * out_node, const FieldSelect *node);
static void _outFieldStore(PgQuery__FieldStore * out_node, const FieldStore *node);
static void _outRelabelType(PgQuery__RelabelType * out_node, const RelabelType *node);
static void _outCoerceViaIO(PgQuery__CoerceViaIO * out_node, const CoerceViaIO *node);
static void _outArrayCoerceExpr(PgQuery__ArrayCoerceExpr * out_node, const ArrayCoerceExpr *node);
static void _outConvertRowtypeExpr(PgQuery__ConvertRowtypeExpr * out_node, const ConvertRowtypeExpr *node);
static void _outCollateExpr(PgQuery__CollateExpr * out_node, const CollateExpr *node);
static void _outCaseExpr(PgQuery__CaseExpr * out_node, const CaseExpr *node);
static void _outCaseWhen(PgQuery__CaseWhen * out_node, const CaseWhen *node);
static void _outCaseTestExpr(PgQuery__CaseTestExpr * out_node, const CaseTestExpr *node);
static void _outArrayExpr(PgQuery__ArrayExpr * out_node, const ArrayExpr *node);
static void _outRowExpr(PgQuery__RowExpr * out_node, const RowExpr *node);
static void _outRowCompareExpr(PgQuery__RowCompareExpr * out_node, const RowCompareExpr *node);
static void _outCoalesceExpr(PgQuery__CoalesceExpr * out_node, const CoalesceExpr *node);
static void _outMinMaxExpr(PgQuery__MinMaxExpr * out_node, const MinMaxExpr *node);
static void _outSQLValueFunction(PgQuery__SQLValueFunction * out_node, const SQLValueFunction *node);
static void _outXmlExpr(PgQuery__XmlExpr * out_node, const XmlExpr *node);
static void _outNullTest(PgQuery__NullTest * out_node, const NullTest *node);
static void _outBooleanTest(PgQuery__BooleanTest * out_node, const BooleanTest *node);
static void _outCoerceToDomain(PgQuery__CoerceToDomain * out_node, const CoerceToDomain *node);
static void _outCoerceToDomainValue(PgQuery__CoerceToDomainValue * out_node, const CoerceToDomainValue *node);
static void _outSetToDefault(PgQuery__SetToDefault * out_node, const SetToDefault *node);
static void _outCurrentOfExpr(PgQuery__CurrentOfExpr * out_node, const CurrentOfExpr *node);
static void _outNextValueExpr(PgQuery__NextValueExpr * out_node, const NextValueExpr *node);
static void _outInferenceElem(PgQuery__InferenceElem * out_node, const InferenceElem *node);
static void _outTargetEntry(PgQuery__TargetEntry * out_node, const TargetEntry *node);
static void _outRangeTblRef(PgQuery__RangeTblRef * out_node, const RangeTblRef *node);
static void _outJoinExpr(PgQuery__JoinExpr * out_node, const JoinExpr *node);
static void _outFromExpr(PgQuery__FromExpr * out_node, const FromExpr *node);
static void _outOnConflictExpr(PgQuery__OnConflictExpr * out_node, const OnConflictExpr *node);
static void _outIntoClause(PgQuery__IntoClause * out_node, const IntoClause *node);
static void _outRawStmt(PgQuery__RawStmt * out_node, const RawStmt *node);
static void _outQuery(PgQuery__Query * out_node, const Query *node);
static void _outInsertStmt(PgQuery__InsertStmt * out_node, const InsertStmt *node);
static void _outDeleteStmt(PgQuery__DeleteStmt * out_node, const DeleteStmt *node);
static void _outUpdateStmt(PgQuery__UpdateStmt * out_node, const UpdateStmt *node);
static void _outSelectStmt(PgQuery__SelectStmt * out_node, const SelectStmt *node);
static void _outAlterTableStmt(PgQuery__AlterTableStmt * out_node, const AlterTableStmt *node);
static void _outAlterTableCmd(PgQuery__AlterTableCmd * out_node, const AlterTableCmd *node);
static void _outAlterDomainStmt(PgQuery__AlterDomainStmt * out_node, const AlterDomainStmt *node);
static void _outSetOperationStmt(PgQuery__SetOperationStmt * out_node, const SetOperationStmt *node);
static void _outGrantStmt(PgQuery__GrantStmt * out_node, const GrantStmt *node);
static void _outGrantRoleStmt(PgQuery__GrantRoleStmt * out_node, const GrantRoleStmt *node);
static void _outAlterDefaultPrivilegesStmt(PgQuery__AlterDefaultPrivilegesStmt * out_node, const AlterDefaultPrivilegesStmt *node);
static void _outClosePortalStmt(PgQuery__ClosePortalStmt * out_node, const ClosePortalStmt *node);
static void _outClusterStmt(PgQuery__ClusterStmt * out_node, const ClusterStmt *node);
static void _outCopyStmt(PgQuery__CopyStmt * out_node, const CopyStmt *node);
static void _outCreateStmt(PgQuery__CreateStmt * out_node, const CreateStmt *node);
static void _outDefineStmt(PgQuery__DefineStmt * out_node, const DefineStmt *node);
static void _outDropStmt(PgQuery__DropStmt * out_node, const DropStmt *node);
static void _outTruncateStmt(PgQuery__TruncateStmt * out_node, const TruncateStmt *node);
static void _outCommentStmt(PgQuery__CommentStmt * out_node, const CommentStmt *node);
static void _outFetchStmt(PgQuery__FetchStmt * out_node, const FetchStmt *node);
static void _outIndexStmt(PgQuery__IndexStmt * out_node, const IndexStmt *node);
static void _outCreateFunctionStmt(PgQuery__CreateFunctionStmt * out_node, const CreateFunctionStmt *node);
static void _outAlterFunctionStmt(PgQuery__AlterFunctionStmt * out_node, const AlterFunctionStmt *node);
static void _outDoStmt(PgQuery__DoStmt * out_node, const DoStmt *node);
static void _outRenameStmt(PgQuery__RenameStmt * out_node, const RenameStmt *node);
static void _outRuleStmt(PgQuery__RuleStmt * out_node, const RuleStmt *node);
static void _outNotifyStmt(PgQuery__NotifyStmt * out_node, const NotifyStmt *node);
static void _outListenStmt(PgQuery__ListenStmt * out_node, const ListenStmt *node);
static void _outUnlistenStmt(PgQuery__UnlistenStmt * out_node, const UnlistenStmt *node);
static void _outTransactionStmt(PgQuery__TransactionStmt * out_node, const TransactionStmt *node);
static void _outViewStmt(PgQuery__ViewStmt * out_node, const ViewStmt *node);
static void _outLoadStmt(PgQuery__LoadStmt * out_node, const LoadStmt *node);
static void _outCreateDomainStmt(PgQuery__CreateDomainStmt * out_node, const CreateDomainStmt *node);
static void _outCreatedbStmt(PgQuery__CreatedbStmt * out_node, const CreatedbStmt *node);
static void _outDropdbStmt(PgQuery__DropdbStmt * out_node, const DropdbStmt *node);
static void _outVacuumStmt(PgQuery__VacuumStmt * out_node, const VacuumStmt *node);
static void _outExplainStmt(PgQuery__ExplainStmt * out_node, const ExplainStmt *node);
static void _outCreateTableAsStmt(PgQuery__CreateTableAsStmt * out_node, const CreateTableAsStmt *node);
static void _outCreateSeqStmt(PgQuery__CreateSeqStmt * out_node, const CreateSeqStmt *node);
static void _outAlterSeqStmt(PgQuery__AlterSeqStmt * out_node, const AlterSeqStmt *node);
static void _outVariableSetStmt(PgQuery__VariableSetStmt * out_node, const VariableSetStmt *node);
static void _outVariableShowStmt(PgQuery__VariableShowStmt * out_node, const VariableShowStmt *node);
static void _outDiscardStmt(PgQuery__DiscardStmt * out_node, const DiscardStmt *node);
static void _outCreateTrigStmt(PgQuery__CreateTrigStmt * out_node, const CreateTrigStmt *node);
static void _outCreatePLangStmt(PgQuery__CreatePLangStmt * out_node, const CreatePLangStmt *node);
static void _outCreateRoleStmt(PgQuery__CreateRoleStmt * out_node, const CreateRoleStmt *node);
static void _outAlterRoleStmt(PgQuery__AlterRoleStmt * out_node, const AlterRoleStmt *node);
static void _outDropRoleStmt(PgQuery__DropRoleStmt * out_node, const DropRoleStmt *node);
static void _outLockStmt(PgQuery__LockStmt * out_node, const LockStmt *node);
static void _outConstraintsSetStmt(PgQuery__ConstraintsSetStmt * out_node, const ConstraintsSetStmt *node);
static void _outReindexStmt(PgQuery__ReindexStmt * out_node, const ReindexStmt *node);
static void _outCheckPointStmt(PgQuery__CheckPointStmt * out_node, const CheckPointStmt *node);
static void _outCreateSchemaStmt(PgQuery__CreateSchemaStmt * out_node, const CreateSchemaStmt *node);
static void _outAlterDatabaseStmt(PgQuery__AlterDatabaseStmt * out_node, const AlterDatabaseStmt *node);
static void _outAlterDatabaseSetStmt(PgQuery__AlterDatabaseSetStmt * out_node, const AlterDatabaseSetStmt *node);
static void _outAlterRoleSetStmt(PgQuery__AlterRoleSetStmt * out_node, const AlterRoleSetStmt *node);
static void _outCreateConversionStmt(PgQuery__CreateConversionStmt * out_node, const CreateConversionStmt *node);
static void _outCreateCastStmt(PgQuery__CreateCastStmt * out_node, const CreateCastStmt *node);
static void _outCreateOpClassStmt(PgQuery__CreateOpClassStmt * out_node, const CreateOpClassStmt *node);
static void _outCreateOpFamilyStmt(PgQuery__CreateOpFamilyStmt * out_node, const CreateOpFamilyStmt *node);
static void _outAlterOpFamilyStmt(PgQuery__AlterOpFamilyStmt * out_node, const AlterOpFamilyStmt *node);
static void _outPrepareStmt(PgQuery__PrepareStmt * out_node, const PrepareStmt *node);
static void _outExecuteStmt(PgQuery__ExecuteStmt * out_node, const ExecuteStmt *node);
static void _outDeallocateStmt(PgQuery__DeallocateStmt * out_node, const DeallocateStmt *node);
static void _outDeclareCursorStmt(PgQuery__DeclareCursorStmt * out_node, const DeclareCursorStmt *node);
static void _outCreateTableSpaceStmt(PgQuery__CreateTableSpaceStmt * out_node, const CreateTableSpaceStmt *node);
static void _outDropTableSpaceStmt(PgQuery__DropTableSpaceStmt * out_node, const DropTableSpaceStmt *node);
static void _outAlterObjectDependsStmt(PgQuery__AlterObjectDependsStmt * out_node, const AlterObjectDependsStmt *node);
static void _outAlterObjectSchemaStmt(PgQuery__AlterObjectSchemaStmt * out_node, const AlterObjectSchemaStmt *node);
static void _outAlterOwnerStmt(PgQuery__AlterOwnerStmt * out_node, const AlterOwnerStmt *node);
static void _outAlterOperatorStmt(PgQuery__AlterOperatorStmt * out_node, const AlterOperatorStmt *node);
static void _outAlterTypeStmt(PgQuery__AlterTypeStmt * out_node, const AlterTypeStmt *node);
static void _outDropOwnedStmt(PgQuery__DropOwnedStmt * out_node, const DropOwnedStmt *node);
static void _outReassignOwnedStmt(PgQuery__ReassignOwnedStmt * out_node, const ReassignOwnedStmt *node);
static void _outCompositeTypeStmt(PgQuery__CompositeTypeStmt * out_node, const CompositeTypeStmt *node);
static void _outCreateEnumStmt(PgQuery__CreateEnumStmt * out_node, const CreateEnumStmt *node);
static void _outCreateRangeStmt(PgQuery__CreateRangeStmt * out_node, const CreateRangeStmt *node);
static void _outAlterEnumStmt(PgQuery__AlterEnumStmt * out_node, const AlterEnumStmt *node);
static void _outAlterTSDictionaryStmt(PgQuery__AlterTSDictionaryStmt * out_node, const AlterTSDictionaryStmt *node);
static void _outAlterTSConfigurationStmt(PgQuery__AlterTSConfigurationStmt * out_node, const AlterTSConfigurationStmt *node);
static void _outCreateFdwStmt(PgQuery__CreateFdwStmt * out_node, const CreateFdwStmt *node);
static void _outAlterFdwStmt(PgQuery__AlterFdwStmt * out_node, const AlterFdwStmt *node);
static void _outCreateForeignServerStmt(PgQuery__CreateForeignServerStmt * out_node, const CreateForeignServerStmt *node);
static void _outAlterForeignServerStmt(PgQuery__AlterForeignServerStmt * out_node, const AlterForeignServerStmt *node);
static void _outCreateUserMappingStmt(PgQuery__CreateUserMappingStmt * out_node, const CreateUserMappingStmt *node);
static void _outAlterUserMappingStmt(PgQuery__AlterUserMappingStmt * out_node, const AlterUserMappingStmt *node);
static void _outDropUserMappingStmt(PgQuery__DropUserMappingStmt * out_node, const DropUserMappingStmt *node);
static void _outAlterTableSpaceOptionsStmt(PgQuery__AlterTableSpaceOptionsStmt * out_node, const AlterTableSpaceOptionsStmt *node);
static void _outAlterTableMoveAllStmt(PgQuery__AlterTableMoveAllStmt * out_node, const AlterTableMoveAllStmt *node);
static void _outSecLabelStmt(PgQuery__SecLabelStmt * out_node, const SecLabelStmt *node);
static void _outCreateForeignTableStmt(PgQuery__CreateForeignTableStmt * out_node, const CreateForeignTableStmt *node);
static void _outImportForeignSchemaStmt(PgQuery__ImportForeignSchemaStmt * out_node, const ImportForeignSchemaStmt *node);
static void _outCreateExtensionStmt(PgQuery__CreateExtensionStmt * out_node, const CreateExtensionStmt *node);
static void _outAlterExtensionStmt(PgQuery__AlterExtensionStmt * out_node, const AlterExtensionStmt *node);
static void _outAlterExtensionContentsStmt(PgQuery__AlterExtensionContentsStmt * out_node, const AlterExtensionContentsStmt *node);
static void _outCreateEventTrigStmt(PgQuery__CreateEventTrigStmt * out_node, const CreateEventTrigStmt *node);
static void _outAlterEventTrigStmt(PgQuery__AlterEventTrigStmt * out_node, const AlterEventTrigStmt *node);
static void _outRefreshMatViewStmt(PgQuery__RefreshMatViewStmt * out_node, const RefreshMatViewStmt *node);
static void _outReplicaIdentityStmt(PgQuery__ReplicaIdentityStmt * out_node, const ReplicaIdentityStmt *node);
static void _outAlterSystemStmt(PgQuery__AlterSystemStmt * out_node, const AlterSystemStmt *node);
static void _outCreatePolicyStmt(PgQuery__CreatePolicyStmt * out_node, const CreatePolicyStmt *node);
static void _outAlterPolicyStmt(PgQuery__AlterPolicyStmt * out_node, const AlterPolicyStmt *node);
static void _outCreateTransformStmt(PgQuery__CreateTransformStmt * out_node, const CreateTransformStmt *node);
static void _outCreateAmStmt(PgQuery__CreateAmStmt * out_node, const CreateAmStmt *node);
static void _outCreatePublicationStmt(PgQuery__CreatePublicationStmt * out_node, const CreatePublicationStmt *node);
static void _outAlterPublicationStmt(PgQuery__AlterPublicationStmt * out_node, const AlterPublicationStmt *node);
static void _outCreateSubscriptionStmt(PgQuery__CreateSubscriptionStmt * out_node, const CreateSubscriptionStmt *node);
static void _outAlterSubscriptionStmt(PgQuery__AlterSubscriptionStmt * out_node, const AlterSubscriptionStmt *node);
static void _outDropSubscriptionStmt(PgQuery__DropSubscriptionStmt * out_node, const DropSubscriptionStmt *node);
static void _outCreateStatsStmt(PgQuery__CreateStatsStmt * out_node, const CreateStatsStmt *node);
static void _outAlterCollationStmt(PgQuery__AlterCollationStmt * out_node, const AlterCollationStmt *node);
static void _outCallStmt(PgQuery__CallStmt * out_node, const CallStmt *node);
static void _outAlterStatsStmt(PgQuery__AlterStatsStmt * out_node, const AlterStatsStmt *node);
static void _outAExpr(PgQuery__AExpr * out_node, const A_Expr *node);
static void _outColumnRef(PgQuery__ColumnRef * out_node, const ColumnRef *node);
static void _outParamRef(PgQuery__ParamRef * out_node, const ParamRef *node);
static void _outAConst(PgQuery__AConst * out_node, const A_Const *node);
static void _outFuncCall(PgQuery__FuncCall * out_node, const FuncCall *node);
static void _outAStar(PgQuery__AStar * out_node, const A_Star *node);
static void _outAIndices(PgQuery__AIndices * out_node, const A_Indices *node);
static void _outAIndirection(PgQuery__AIndirection * out_node, const A_Indirection *node);
static void _outAArrayExpr(PgQuery__AArrayExpr * out_node, const A_ArrayExpr *node);
static void _outResTarget(PgQuery__ResTarget * out_node, const ResTarget *node);
static void _outMultiAssignRef(PgQuery__MultiAssignRef * out_node, const MultiAssignRef *node);
static void _outTypeCast(PgQuery__TypeCast * out_node, const TypeCast *node);
static void _outCollateClause(PgQuery__CollateClause * out_node, const CollateClause *node);
static void _outSortBy(PgQuery__SortBy * out_node, const SortBy *node);
static void _outWindowDef(PgQuery__WindowDef * out_node, const WindowDef *node);
static void _outRangeSubselect(PgQuery__RangeSubselect * out_node, const RangeSubselect *node);
static void _outRangeFunction(PgQuery__RangeFunction * out_node, const RangeFunction *node);
static void _outRangeTableSample(PgQuery__RangeTableSample * out_node, const RangeTableSample *node);
static void _outRangeTableFunc(PgQuery__RangeTableFunc * out_node, const RangeTableFunc *node);
static void _outRangeTableFuncCol(PgQuery__RangeTableFuncCol * out_node, const RangeTableFuncCol *node);
static void _outTypeName(PgQuery__TypeName * out_node, const TypeName *node);
static void _outColumnDef(PgQuery__ColumnDef * out_node, const ColumnDef *node);
static void _outIndexElem(PgQuery__IndexElem * out_node, const IndexElem *node);
static void _outConstraint(PgQuery__Constraint * out_node, const Constraint *node);
static void _outDefElem(PgQuery__DefElem * out_node, const DefElem *node);
static void _outRangeTblEntry(PgQuery__RangeTblEntry * out_node, const RangeTblEntry *node);
static void _outRangeTblFunction(PgQuery__RangeTblFunction * out_node, const RangeTblFunction *node);
static void _outTableSampleClause(PgQuery__TableSampleClause * out_node, const TableSampleClause *node);
static void _outWithCheckOption(PgQuery__WithCheckOption * out_node, const WithCheckOption *node);
static void _outSortGroupClause(PgQuery__SortGroupClause * out_node, const SortGroupClause *node);
static void _outGroupingSet(PgQuery__GroupingSet * out_node, const GroupingSet *node);
static void _outWindowClause(PgQuery__WindowClause * out_node, const WindowClause *node);
static void _outObjectWithArgs(PgQuery__ObjectWithArgs * out_node, const ObjectWithArgs *node);
static void _outAccessPriv(PgQuery__AccessPriv * out_node, const AccessPriv *node);
static void _outCreateOpClassItem(PgQuery__CreateOpClassItem * out_node, const CreateOpClassItem *node);
static void _outTableLikeClause(PgQuery__TableLikeClause * out_node, const TableLikeClause *node);
static void _outFunctionParameter(PgQuery__FunctionParameter * out_node, const FunctionParameter *node);
static void _outLockingClause(PgQuery__LockingClause * out_node, const LockingClause *node);
static void _outRowMarkClause(PgQuery__RowMarkClause * out_node, const RowMarkClause *node);
static void _outXmlSerialize(PgQuery__XmlSerialize * out_node, const XmlSerialize *node);
static void _outWithClause(PgQuery__WithClause * out_node, const WithClause *node);
static void _outInferClause(PgQuery__InferClause * out_node, const InferClause *node);
static void _outOnConflictClause(PgQuery__OnConflictClause * out_node, const OnConflictClause *node);
static void _outCommonTableExpr(PgQuery__CommonTableExpr * out_node, const CommonTableExpr *node);
static void _outRoleSpec(PgQuery__RoleSpec * out_node, const RoleSpec *node);
static void _outTriggerTransition(PgQuery__TriggerTransition * out_node, const TriggerTransition *node);
static void _outPartitionElem(PgQuery__PartitionElem * out_node, const PartitionElem *node);
static void _outPartitionSpec(PgQuery__PartitionSpec * out_node, const PartitionSpec *node);
static void _outPartitionBoundSpec(PgQuery__PartitionBoundSpec * out_node, const PartitionBoundSpec *node);
static void _outPartitionRangeDatum(PgQuery__PartitionRangeDatum * out_node, const PartitionRangeDatum *node);
static void _outPartitionCmd(PgQuery__PartitionCmd * out_node, const PartitionCmd *node);
static void _outVacuumRelation(PgQuery__VacuumRelation * out_node, const VacuumRelation *node);
static void _outInlineCodeBlock(PgQuery__InlineCodeBlock * out_node, const InlineCodeBlock *node);
static void _outCallContext(PgQuery__CallContext * out_node, const CallContext *node);
static void
_outAlias(PgQuery__Alias * out_node, const Alias *node)
{
  WRITE_STRING_FIELD(aliasname, aliasname);
  WRITE_LIST_FIELD(colnames, colnames);
}

static void
_outRangeVar(PgQuery__RangeVar * out_node, const RangeVar *node)
{
  WRITE_STRING_FIELD(catalogname, catalogname);
  WRITE_STRING_FIELD(schemaname, schemaname);
  WRITE_STRING_FIELD(relname, relname);
  WRITE_BOOL_FIELD(inh, inh);
  WRITE_CHAR_FIELD(relpersistence, relpersistence);
  WRITE_SPECIFIC_NODE_PTR_FIELD(Alias, alias, alias, alias);
  WRITE_INT_FIELD(location, location);
}

static void
_outTableFunc(PgQuery__TableFunc * out_node, const TableFunc *node)
{
  WRITE_LIST_FIELD(ns_uris, ns_uris);
  WRITE_LIST_FIELD(ns_names, ns_names);
  WRITE_NODE_PTR_FIELD(docexpr, docexpr);
  WRITE_NODE_PTR_FIELD(rowexpr, rowexpr);
  WRITE_LIST_FIELD(colnames, colnames);
  WRITE_LIST_FIELD(coltypes, coltypes);
  WRITE_LIST_FIELD(coltypmods, coltypmods);
  WRITE_LIST_FIELD(colcollations, colcollations);
  WRITE_LIST_FIELD(colexprs, colexprs);
  WRITE_LIST_FIELD(coldefexprs, coldefexprs);
  WRITE_BITMAPSET_FIELD(notnulls, notnulls);
  WRITE_INT_FIELD(ordinalitycol, ordinalitycol);
  WRITE_INT_FIELD(location, location);
}

static void
_outExpr(PgQuery__Expr * out_node, const Expr *node)
{
}

static void
_outVar(PgQuery__Var * out_node, const Var *node)
{
  WRITE_UINT_FIELD(varno, varno);
  WRITE_INT_FIELD(varattno, varattno);
  WRITE_UINT_FIELD(vartype, vartype);
  WRITE_INT_FIELD(vartypmod, vartypmod);
  WRITE_UINT_FIELD(varcollid, varcollid);
  WRITE_UINT_FIELD(varlevelsup, varlevelsup);
  WRITE_UINT_FIELD(varnosyn, varnosyn);
  WRITE_INT_FIELD(varattnosyn, varattnosyn);
  WRITE_INT_FIELD(location, location);
}

static void
_outParam(PgQuery__Param * out_node, const Param *node)
{
  WRITE_ENUM_FIELD(ParamKind, paramkind, paramkind);
  WRITE_INT_FIELD(paramid, paramid);
  WRITE_UINT_FIELD(paramtype, paramtype);
  WRITE_INT_FIELD(paramtypmod, paramtypmod);
  WRITE_UINT_FIELD(paramcollid, paramcollid);
  WRITE_INT_FIELD(location, location);
}

static void
_outAggref(PgQuery__Aggref * out_node, const Aggref *node)
{
  WRITE_UINT_FIELD(aggfnoid, aggfnoid);
  WRITE_UINT_FIELD(aggtype, aggtype);
  WRITE_UINT_FIELD(aggcollid, aggcollid);
  WRITE_UINT_FIELD(inputcollid, inputcollid);
  WRITE_UINT_FIELD(aggtranstype, aggtranstype);
  WRITE_LIST_FIELD(aggargtypes, aggargtypes);
  WRITE_LIST_FIELD(aggdirectargs, aggdirectargs);
  WRITE_LIST_FIELD(args, args);
  WRITE_LIST_FIELD(aggorder, aggorder);
  WRITE_LIST_FIELD(aggdistinct, aggdistinct);
  WRITE_NODE_PTR_FIELD(aggfilter, aggfilter);
  WRITE_BOOL_FIELD(aggstar, aggstar);
  WRITE_BOOL_FIELD(aggvariadic, aggvariadic);
  WRITE_CHAR_FIELD(aggkind, aggkind);
  WRITE_UINT_FIELD(agglevelsup, agglevelsup);
  WRITE_ENUM_FIELD(AggSplit, aggsplit, aggsplit);
  WRITE_INT_FIELD(location, location);
}

static void
_outGroupingFunc(PgQuery__GroupingFunc * out_node, const GroupingFunc *node)
{
  WRITE_LIST_FIELD(args, args);
  WRITE_LIST_FIELD(refs, refs);
  WRITE_LIST_FIELD(cols, cols);
  WRITE_UINT_FIELD(agglevelsup, agglevelsup);
  WRITE_INT_FIELD(location, location);
}

static void
_outWindowFunc(PgQuery__WindowFunc * out_node, const WindowFunc *node)
{
  WRITE_UINT_FIELD(winfnoid, winfnoid);
  WRITE_UINT_FIELD(wintype, wintype);
  WRITE_UINT_FIELD(wincollid, wincollid);
  WRITE_UINT_FIELD(inputcollid, inputcollid);
  WRITE_LIST_FIELD(args, args);
  WRITE_NODE_PTR_FIELD(aggfilter, aggfilter);
  WRITE_UINT_FIELD(winref, winref);
  WRITE_BOOL_FIELD(winstar, winstar);
  WRITE_BOOL_FIELD(winagg, winagg);
  WRITE_INT_FIELD(location, location);
}

static void
_outSubscriptingRef(PgQuery__SubscriptingRef * out_node, const SubscriptingRef *node)
{
  WRITE_UINT_FIELD(refcontainertype, refcontainertype);
  WRITE_UINT_FIELD(refelemtype, refelemtype);
  WRITE_INT_FIELD(reftypmod, reftypmod);
  WRITE_UINT_FIELD(refcollid, refcollid);
  WRITE_LIST_FIELD(refupperindexpr, refupperindexpr);
  WRITE_LIST_FIELD(reflowerindexpr, reflowerindexpr);
  WRITE_NODE_PTR_FIELD(refexpr, refexpr);
  WRITE_NODE_PTR_FIELD(refassgnexpr, refassgnexpr);
}

static void
_outFuncExpr(PgQuery__FuncExpr * out_node, const FuncExpr *node)
{
  WRITE_UINT_FIELD(funcid, funcid);
  WRITE_UINT_FIELD(funcresulttype, funcresulttype);
  WRITE_BOOL_FIELD(funcretset, funcretset);
  WRITE_BOOL_FIELD(funcvariadic, funcvariadic);
  WRITE_ENUM_FIELD(CoercionForm, funcformat, funcformat);
  WRITE_UINT_FIELD(funccollid, funccollid);
  WRITE_UINT_FIELD(inputcollid, inputcollid);
  WRITE_LIST_FIELD(args, args);
  WRITE_INT_FIELD(location, location);
}

static void
_outNamedArgExpr(PgQuery__NamedArgExpr * out_node, const NamedArgExpr *node)
{
  WRITE_NODE_PTR_FIELD(arg, arg);
  WRITE_STRING_FIELD(name, name);
  WRITE_INT_FIELD(argnumber, argnumber);
  WRITE_INT_FIELD(location, location);
}

static void
_outOpExpr(PgQuery__OpExpr * out_node, const OpExpr *node)
{
  WRITE_UINT_FIELD(opno, opno);
  WRITE_UINT_FIELD(opfuncid, opfuncid);
  WRITE_UINT_FIELD(opresulttype, opresulttype);
  WRITE_BOOL_FIELD(opretset, opretset);
  WRITE_UINT_FIELD(opcollid, opcollid);
  WRITE_UINT_FIELD(inputcollid, inputcollid);
  WRITE_LIST_FIELD(args, args);
  WRITE_INT_FIELD(location, location);
}

static void
_outDistinctExpr(PgQuery__DistinctExpr * out_node, const DistinctExpr *node)
{
  WRITE_UINT_FIELD(opno, opno);
  WRITE_UINT_FIELD(opfuncid, opfuncid);
  WRITE_UINT_FIELD(opresulttype, opresulttype);
  WRITE_BOOL_FIELD(opretset, opretset);
  WRITE_UINT_FIELD(opcollid, opcollid);
  WRITE_UINT_FIELD(inputcollid, inputcollid);
  WRITE_LIST_FIELD(args, args);
  WRITE_INT_FIELD(location, location);
}

static void
_outNullIfExpr(PgQuery__NullIfExpr * out_node, const NullIfExpr *node)
{
  WRITE_UINT_FIELD(opno, opno);
  WRITE_UINT_FIELD(opfuncid, opfuncid);
  WRITE_UINT_FIELD(opresulttype, opresulttype);
  WRITE_BOOL_FIELD(opretset, opretset);
  WRITE_UINT_FIELD(opcollid, opcollid);
  WRITE_UINT_FIELD(inputcollid, inputcollid);
  WRITE_LIST_FIELD(args, args);
  WRITE_INT_FIELD(location, location);
}

static void
_outScalarArrayOpExpr(PgQuery__ScalarArrayOpExpr * out_node, const ScalarArrayOpExpr *node)
{
  WRITE_UINT_FIELD(opno, opno);
  WRITE_UINT_FIELD(opfuncid, opfuncid);
  WRITE_BOOL_FIELD(use_or, useOr);
  WRITE_UINT_FIELD(inputcollid, inputcollid);
  WRITE_LIST_FIELD(args, args);
  WRITE_INT_FIELD(location, location);
}

static void
_outBoolExpr(PgQuery__BoolExpr * out_node, const BoolExpr *node)
{
  WRITE_ENUM_FIELD(BoolExprType, boolop, boolop);
  WRITE_LIST_FIELD(args, args);
  WRITE_INT_FIELD(location, location);
}

static void
_outSubLink(PgQuery__SubLink * out_node, const SubLink *node)
{
  WRITE_ENUM_FIELD(SubLinkType, sub_link_type, subLinkType);
  WRITE_INT_FIELD(sub_link_id, subLinkId);
  WRITE_NODE_PTR_FIELD(testexpr, testexpr);
  WRITE_LIST_FIELD(oper_name, operName);
  WRITE_NODE_PTR_FIELD(subselect, subselect);
  WRITE_INT_FIELD(location, location);
}

static void
_outSubPlan(PgQuery__SubPlan * out_node, const SubPlan *node)
{
  WRITE_ENUM_FIELD(SubLinkType, sub_link_type, subLinkType);
  WRITE_NODE_PTR_FIELD(testexpr, testexpr);
  WRITE_LIST_FIELD(param_ids, paramIds);
  WRITE_INT_FIELD(plan_id, plan_id);
  WRITE_STRING_FIELD(plan_name, plan_name);
  WRITE_UINT_FIELD(first_col_type, firstColType);
  WRITE_INT_FIELD(first_col_typmod, firstColTypmod);
  WRITE_UINT_FIELD(first_col_collation, firstColCollation);
  WRITE_BOOL_FIELD(use_hash_table, useHashTable);
  WRITE_BOOL_FIELD(unknown_eq_false, unknownEqFalse);
  WRITE_BOOL_FIELD(parallel_safe, parallel_safe);
  WRITE_LIST_FIELD(set_param, setParam);
  WRITE_LIST_FIELD(par_param, parParam);
  WRITE_LIST_FIELD(args, args);
  WRITE_FLOAT_FIELD(startup_cost, startup_cost);
  WRITE_FLOAT_FIELD(per_call_cost, per_call_cost);
}

static void
_outAlternativeSubPlan(PgQuery__AlternativeSubPlan * out_node, const AlternativeSubPlan *node)
{
  WRITE_LIST_FIELD(subplans, subplans);
}

static void
_outFieldSelect(PgQuery__FieldSelect * out_node, const FieldSelect *node)
{
  WRITE_NODE_PTR_FIELD(arg, arg);
  WRITE_INT_FIELD(fieldnum, fieldnum);
  WRITE_UINT_FIELD(resulttype, resulttype);
  WRITE_INT_FIELD(resulttypmod, resulttypmod);
  WRITE_UINT_FIELD(resultcollid, resultcollid);
}

static void
_outFieldStore(PgQuery__FieldStore * out_node, const FieldStore *node)
{
  WRITE_NODE_PTR_FIELD(arg, arg);
  WRITE_LIST_FIELD(newvals, newvals);
  WRITE_LIST_FIELD(fieldnums, fieldnums);
  WRITE_UINT_FIELD(resulttype, resulttype);
}

static void
_outRelabelType(PgQuery__RelabelType * out_node, const RelabelType *node)
{
  WRITE_NODE_PTR_FIELD(arg, arg);
  WRITE_UINT_FIELD(resulttype, resulttype);
  WRITE_INT_FIELD(resulttypmod, resulttypmod);
  WRITE_UINT_FIELD(resultcollid, resultcollid);
  WRITE_ENUM_FIELD(CoercionForm, relabelformat, relabelformat);
  WRITE_INT_FIELD(location, location);
}

static void
_outCoerceViaIO(PgQuery__CoerceViaIO * out_node, const CoerceViaIO *node)
{
  WRITE_NODE_PTR_FIELD(arg, arg);
  WRITE_UINT_FIELD(resulttype, resulttype);
  WRITE_UINT_FIELD(resultcollid, resultcollid);
  WRITE_ENUM_FIELD(CoercionForm, coerceformat, coerceformat);
  WRITE_INT_FIELD(location, location);
}

static void
_outArrayCoerceExpr(PgQuery__ArrayCoerceExpr * out_node, const ArrayCoerceExpr *node)
{
  WRITE_NODE_PTR_FIELD(arg, arg);
  WRITE_NODE_PTR_FIELD(elemexpr, elemexpr);
  WRITE_UINT_FIELD(resulttype, resulttype);
  WRITE_INT_FIELD(resulttypmod, resulttypmod);
  WRITE_UINT_FIELD(resultcollid, resultcollid);
  WRITE_ENUM_FIELD(CoercionForm, coerceformat, coerceformat);
  WRITE_INT_FIELD(location, location);
}

static void
_outConvertRowtypeExpr(PgQuery__ConvertRowtypeExpr * out_node, const ConvertRowtypeExpr *node)
{
  WRITE_NODE_PTR_FIELD(arg, arg);
  WRITE_UINT_FIELD(resulttype, resulttype);
  WRITE_ENUM_FIELD(CoercionForm, convertformat, convertformat);
  WRITE_INT_FIELD(location, location);
}

static void
_outCollateExpr(PgQuery__CollateExpr * out_node, const CollateExpr *node)
{
  WRITE_NODE_PTR_FIELD(arg, arg);
  WRITE_UINT_FIELD(coll_oid, collOid);
  WRITE_INT_FIELD(location, location);
}

static void
_outCaseExpr(PgQuery__CaseExpr * out_node, const CaseExpr *node)
{
  WRITE_UINT_FIELD(casetype, casetype);
  WRITE_UINT_FIELD(casecollid, casecollid);
  WRITE_NODE_PTR_FIELD(arg, arg);
  WRITE_LIST_FIELD(args, args);
  WRITE_NODE_PTR_FIELD(defresult, defresult);
  WRITE_INT_FIELD(location, location);
}

static void
_outCaseWhen(PgQuery__CaseWhen * out_node, const CaseWhen *node)
{
  WRITE_NODE_PTR_FIELD(expr, expr);
  WRITE_NODE_PTR_FIELD(result, result);
  WRITE_INT_FIELD(location, location);
}

static void
_outCaseTestExpr(PgQuery__CaseTestExpr * out_node, const CaseTestExpr *node)
{
  WRITE_UINT_FIELD(type_id, typeId);
  WRITE_INT_FIELD(type_mod, typeMod);
  WRITE_UINT_FIELD(collation, collation);
}

static void
_outArrayExpr(PgQuery__ArrayExpr * out_node, const ArrayExpr *node)
{
  WRITE_UINT_FIELD(array_typeid, array_typeid);
  WRITE_UINT_FIELD(array_collid, array_collid);
  WRITE_UINT_FIELD(element_typeid, element_typeid);
  WRITE_LIST_FIELD(elements, elements);
  WRITE_BOOL_FIELD(multidims, multidims);
  WRITE_INT_FIELD(location, location);
}

static void
_outRowExpr(PgQuery__RowExpr * out_node, const RowExpr *node)
{
  WRITE_LIST_FIELD(args, args);
  WRITE_UINT_FIELD(row_typeid, row_typeid);
  WRITE_ENUM_FIELD(CoercionForm, row_format, row_format);
  WRITE_LIST_FIELD(colnames, colnames);
  WRITE_INT_FIELD(location, location);
}

static void
_outRowCompareExpr(PgQuery__RowCompareExpr * out_node, const RowCompareExpr *node)
{
  WRITE_ENUM_FIELD(RowCompareType, rctype, rctype);
  WRITE_LIST_FIELD(opnos, opnos);
  WRITE_LIST_FIELD(opfamilies, opfamilies);
  WRITE_LIST_FIELD(inputcollids, inputcollids);
  WRITE_LIST_FIELD(largs, largs);
  WRITE_LIST_FIELD(rargs, rargs);
}

static void
_outCoalesceExpr(PgQuery__CoalesceExpr * out_node, const CoalesceExpr *node)
{
  WRITE_UINT_FIELD(coalescetype, coalescetype);
  WRITE_UINT_FIELD(coalescecollid, coalescecollid);
  WRITE_LIST_FIELD(args, args);
  WRITE_INT_FIELD(location, location);
}

static void
_outMinMaxExpr(PgQuery__MinMaxExpr * out_node, const MinMaxExpr *node)
{
  WRITE_UINT_FIELD(minmaxtype, minmaxtype);
  WRITE_UINT_FIELD(minmaxcollid, minmaxcollid);
  WRITE_UINT_FIELD(inputcollid, inputcollid);
  WRITE_ENUM_FIELD(MinMaxOp, op, op);
  WRITE_LIST_FIELD(args, args);
  WRITE_INT_FIELD(location, location);
}

static void
_outSQLValueFunction(PgQuery__SQLValueFunction * out_node, const SQLValueFunction *node)
{
  WRITE_ENUM_FIELD(SQLValueFunctionOp, op, op);
  WRITE_UINT_FIELD(type, type);
  WRITE_INT_FIELD(typmod, typmod);
  WRITE_INT_FIELD(location, location);
}

static void
_outXmlExpr(PgQuery__XmlExpr * out_node, const XmlExpr *node)
{
  WRITE_ENUM_FIELD(XmlExprOp, op, op);
  WRITE_STRING_FIELD(name, name);
  WRITE_LIST_FIELD(named_args, named_args);
  WRITE_LIST_FIELD(arg_names, arg_names);
  WRITE_LIST_FIELD(args, args);
  WRITE_ENUM_FIELD(XmlOptionType, xmloption, xmloption);
  WRITE_UINT_FIELD(type, type);
  WRITE_INT_FIELD(typmod, typmod);
  WRITE_INT_FIELD(location, location);
}

static void
_outNullTest(PgQuery__NullTest * out_node, const NullTest *node)
{
  WRITE_NODE_PTR_FIELD(arg, arg);
  WRITE_ENUM_FIELD(NullTestType, nulltesttype, nulltesttype);
  WRITE_BOOL_FIELD(argisrow, argisrow);
  WRITE_INT_FIELD(location, location);
}

static void
_outBooleanTest(PgQuery__BooleanTest * out_node, const BooleanTest *node)
{
  WRITE_NODE_PTR_FIELD(arg, arg);
  WRITE_ENUM_FIELD(BoolTestType, booltesttype, booltesttype);
  WRITE_INT_FIELD(location, location);
}

static void
_outCoerceToDomain(PgQuery__CoerceToDomain * out_node, const CoerceToDomain *node)
{
  WRITE_NODE_PTR_FIELD(arg, arg);
  WRITE_UINT_FIELD(resulttype, resulttype);
  WRITE_INT_FIELD(resulttypmod, resulttypmod);
  WRITE_UINT_FIELD(resultcollid, resultcollid);
  WRITE_ENUM_FIELD(CoercionForm, coercionformat, coercionformat);
  WRITE_INT_FIELD(location, location);
}

static void
_outCoerceToDomainValue(PgQuery__CoerceToDomainValue * out_node, const CoerceToDomainValue *node)
{
  WRITE_UINT_FIELD(type_id, typeId);
  WRITE_INT_FIELD(type_mod, typeMod);
  WRITE_UINT_FIELD(collation, collation);
  WRITE_INT_FIELD(location, location);
}

static void
_outSetToDefault(PgQuery__SetToDefault * out_node, const SetToDefault *node)
{
  WRITE_UINT_FIELD(type_id, typeId);
  WRITE_INT_FIELD(type_mod, typeMod);
  WRITE_UINT_FIELD(collation, collation);
  WRITE_INT_FIELD(location, location);
}

static void
_outCurrentOfExpr(PgQuery__CurrentOfExpr * out_node, const CurrentOfExpr *node)
{
  WRITE_UINT_FIELD(cvarno, cvarno);
  WRITE_STRING_FIELD(cursor_name, cursor_name);
  WRITE_INT_FIELD(cursor_param, cursor_param);
}

static void
_outNextValueExpr(PgQuery__NextValueExpr * out_node, const NextValueExpr *node)
{
  WRITE_UINT_FIELD(seqid, seqid);
  WRITE_UINT_FIELD(type_id, typeId);
}

static void
_outInferenceElem(PgQuery__InferenceElem * out_node, const InferenceElem *node)
{
  WRITE_NODE_PTR_FIELD(expr, expr);
  WRITE_UINT_FIELD(infercollid, infercollid);
  WRITE_UINT_FIELD(inferopclass, inferopclass);
}

static void
_outTargetEntry(PgQuery__TargetEntry * out_node, const TargetEntry *node)
{
  WRITE_NODE_PTR_FIELD(expr, expr);
  WRITE_INT_FIELD(resno, resno);
  WRITE_STRING_FIELD(resname, resname);
  WRITE_UINT_FIELD(ressortgroupref, ressortgroupref);
  WRITE_UINT_FIELD(resorigtbl, resorigtbl);
  WRITE_INT_FIELD(resorigcol, resorigcol);
  WRITE_BOOL_FIELD(resjunk, resjunk);
}

static void
_outRangeTblRef(PgQuery__RangeTblRef * out_node, const RangeTblRef *node)
{
  WRITE_INT_FIELD(rtindex, rtindex);
}

static void
_outJoinExpr(PgQuery__JoinExpr * out_node, const JoinExpr *node)
{
  WRITE_ENUM_FIELD(JoinType, jointype, jointype);
  WRITE_BOOL_FIELD(is_natural, isNatural);
  WRITE_NODE_PTR_FIELD(larg, larg);
  WRITE_NODE_PTR_FIELD(rarg, rarg);
  WRITE_LIST_FIELD(using_clause, usingClause);
  WRITE_NODE_PTR_FIELD(quals, quals);
  WRITE_SPECIFIC_NODE_PTR_FIELD(Alias, alias, alias, alias);
  WRITE_INT_FIELD(rtindex, rtindex);
}

static void
_outFromExpr(PgQuery__FromExpr * out_node, const FromExpr *node)
{
  WRITE_LIST_FIELD(fromlist, fromlist);
  WRITE_NODE_PTR_FIELD(quals, quals);
}

static void
_outOnConflictExpr(PgQuery__OnConflictExpr * out_node, const OnConflictExpr *node)
{
  WRITE_ENUM_FIELD(OnConflictAction, action, action);
  WRITE_LIST_FIELD(arbiter_elems, arbiterElems);
  WRITE_NODE_PTR_FIELD(arbiter_where, arbiterWhere);
  WRITE_UINT_FIELD(constraint, constraint);
  WRITE_LIST_FIELD(on_conflict_set, onConflictSet);
  WRITE_NODE_PTR_FIELD(on_conflict_where, onConflictWhere);
  WRITE_INT_FIELD(excl_rel_index, exclRelIndex);
  WRITE_LIST_FIELD(excl_rel_tlist, exclRelTlist);
}

static void
_outIntoClause(PgQuery__IntoClause * out_node, const IntoClause *node)
{
  WRITE_SPECIFIC_NODE_PTR_FIELD(RangeVar, range_var, rel, rel);
  WRITE_LIST_FIELD(col_names, colNames);
  WRITE_STRING_FIELD(access_method, accessMethod);
  WRITE_LIST_FIELD(options, options);
  WRITE_ENUM_FIELD(OnCommitAction, on_commit, onCommit);
  WRITE_STRING_FIELD(table_space_name, tableSpaceName);
  WRITE_NODE_PTR_FIELD(view_query, viewQuery);
  WRITE_BOOL_FIELD(skip_data, skipData);
}

static void
_outRawStmt(PgQuery__RawStmt * out_node, const RawStmt *node)
{
  WRITE_NODE_PTR_FIELD(stmt, stmt);
  WRITE_INT_FIELD(stmt_location, stmt_location);
  WRITE_INT_FIELD(stmt_len, stmt_len);
}

static void
_outQuery(PgQuery__Query * out_node, const Query *node)
{
  WRITE_ENUM_FIELD(CmdType, command_type, commandType);
  WRITE_ENUM_FIELD(QuerySource, query_source, querySource);
  WRITE_BOOL_FIELD(can_set_tag, canSetTag);
  WRITE_NODE_PTR_FIELD(utility_stmt, utilityStmt);
  WRITE_INT_FIELD(result_relation, resultRelation);
  WRITE_BOOL_FIELD(has_aggs, hasAggs);
  WRITE_BOOL_FIELD(has_window_funcs, hasWindowFuncs);
  WRITE_BOOL_FIELD(has_target_srfs, hasTargetSRFs);
  WRITE_BOOL_FIELD(has_sub_links, hasSubLinks);
  WRITE_BOOL_FIELD(has_distinct_on, hasDistinctOn);
  WRITE_BOOL_FIELD(has_recursive, hasRecursive);
  WRITE_BOOL_FIELD(has_modifying_cte, hasModifyingCTE);
  WRITE_BOOL_FIELD(has_for_update, hasForUpdate);
  WRITE_BOOL_FIELD(has_row_security, hasRowSecurity);
  WRITE_LIST_FIELD(cte_list, cteList);
  WRITE_LIST_FIELD(rtable, rtable);
  WRITE_SPECIFIC_NODE_PTR_FIELD(FromExpr, from_expr, jointree, jointree);
  WRITE_LIST_FIELD(target_list, targetList);
  WRITE_ENUM_FIELD(OverridingKind, override, override);
  WRITE_SPECIFIC_NODE_PTR_FIELD(OnConflictExpr, on_conflict_expr, on_conflict, onConflict);
  WRITE_LIST_FIELD(returning_list, returningList);
  WRITE_LIST_FIELD(group_clause, groupClause);
  WRITE_LIST_FIELD(grouping_sets, groupingSets);
  WRITE_NODE_PTR_FIELD(having_qual, havingQual);
  WRITE_LIST_FIELD(window_clause, windowClause);
  WRITE_LIST_FIELD(distinct_clause, distinctClause);
  WRITE_LIST_FIELD(sort_clause, sortClause);
  WRITE_NODE_PTR_FIELD(limit_offset, limitOffset);
  WRITE_NODE_PTR_FIELD(limit_count, limitCount);
  WRITE_ENUM_FIELD(LimitOption, limit_option, limitOption);
  WRITE_LIST_FIELD(row_marks, rowMarks);
  WRITE_NODE_PTR_FIELD(set_operations, setOperations);
  WRITE_LIST_FIELD(constraint_deps, constraintDeps);
  WRITE_LIST_FIELD(with_check_options, withCheckOptions);
  WRITE_INT_FIELD(stmt_location, stmt_location);
  WRITE_INT_FIELD(stmt_len, stmt_len);
}

static void
_outInsertStmt(PgQuery__InsertStmt * out_node, const InsertStmt *node)
{
  WRITE_SPECIFIC_NODE_PTR_FIELD(RangeVar, range_var, relation, relation);
  WRITE_LIST_FIELD(cols, cols);
  WRITE_NODE_PTR_FIELD(select_stmt, selectStmt);
  WRITE_SPECIFIC_NODE_PTR_FIELD(OnConflictClause, on_conflict_clause, on_conflict_clause, onConflictClause);
  WRITE_LIST_FIELD(returning_list, returningList);
  WRITE_SPECIFIC_NODE_PTR_FIELD(WithClause, with_clause, with_clause, withClause);
  WRITE_ENUM_FIELD(OverridingKind, override, override);
}

static void
_outDeleteStmt(PgQuery__DeleteStmt * out_node, const DeleteStmt *node)
{
  WRITE_SPECIFIC_NODE_PTR_FIELD(RangeVar, range_var, relation, relation);
  WRITE_LIST_FIELD(using_clause, usingClause);
  WRITE_NODE_PTR_FIELD(where_clause, whereClause);
  WRITE_LIST_FIELD(returning_list, returningList);
  WRITE_SPECIFIC_NODE_PTR_FIELD(WithClause, with_clause, with_clause, withClause);
}

static void
_outUpdateStmt(PgQuery__UpdateStmt * out_node, const UpdateStmt *node)
{
  WRITE_SPECIFIC_NODE_PTR_FIELD(RangeVar, range_var, relation, relation);
  WRITE_LIST_FIELD(target_list, targetList);
  WRITE_NODE_PTR_FIELD(where_clause, whereClause);
  WRITE_LIST_FIELD(from_clause, fromClause);
  WRITE_LIST_FIELD(returning_list, returningList);
  WRITE_SPECIFIC_NODE_PTR_FIELD(WithClause, with_clause, with_clause, withClause);
}

static void
_outSelectStmt(PgQuery__SelectStmt * out_node, const SelectStmt *node)
{
  WRITE_LIST_FIELD(distinct_clause, distinctClause);
  WRITE_SPECIFIC_NODE_PTR_FIELD(IntoClause, into_clause, into_clause, intoClause);
  WRITE_LIST_FIELD(target_list, targetList);
  WRITE_LIST_FIELD(from_clause, fromClause);
  WRITE_NODE_PTR_FIELD(where_clause, whereClause);
  WRITE_LIST_FIELD(group_clause, groupClause);
  WRITE_NODE_PTR_FIELD(having_clause, havingClause);
  WRITE_LIST_FIELD(window_clause, windowClause);
  WRITE_LIST_FIELD(values_lists, valuesLists);
  WRITE_LIST_FIELD(sort_clause, sortClause);
  WRITE_NODE_PTR_FIELD(limit_offset, limitOffset);
  WRITE_NODE_PTR_FIELD(limit_count, limitCount);
  WRITE_ENUM_FIELD(LimitOption, limit_option, limitOption);
  WRITE_LIST_FIELD(locking_clause, lockingClause);
  WRITE_SPECIFIC_NODE_PTR_FIELD(WithClause, with_clause, with_clause, withClause);
  WRITE_ENUM_FIELD(SetOperation, op, op);
  WRITE_BOOL_FIELD(all, all);
  WRITE_SPECIFIC_NODE_PTR_FIELD(SelectStmt, select_stmt, larg, larg);
  WRITE_SPECIFIC_NODE_PTR_FIELD(SelectStmt, select_stmt, rarg, rarg);
}

static void
_outAlterTableStmt(PgQuery__AlterTableStmt * out_node, const AlterTableStmt *node)
{
  WRITE_SPECIFIC_NODE_PTR_FIELD(RangeVar, range_var, relation, relation);
  WRITE_LIST_FIELD(cmds, cmds);
  WRITE_ENUM_FIELD(ObjectType, relkind, relkind);
  WRITE_BOOL_FIELD(missing_ok, missing_ok);
}

static void
_outAlterTableCmd(PgQuery__AlterTableCmd * out_node, const AlterTableCmd *node)
{
  WRITE_ENUM_FIELD(AlterTableType, subtype, subtype);
  WRITE_STRING_FIELD(name, name);
  WRITE_INT_FIELD(num, num);
  WRITE_SPECIFIC_NODE_PTR_FIELD(RoleSpec, role_spec, newowner, newowner);
  WRITE_NODE_PTR_FIELD(def, def);
  WRITE_ENUM_FIELD(DropBehavior, behavior, behavior);
  WRITE_BOOL_FIELD(missing_ok, missing_ok);
}

static void
_outAlterDomainStmt(PgQuery__AlterDomainStmt * out_node, const AlterDomainStmt *node)
{
  WRITE_CHAR_FIELD(subtype, subtype);
  WRITE_LIST_FIELD(type_name, typeName);
  WRITE_STRING_FIELD(name, name);
  WRITE_NODE_PTR_FIELD(def, def);
  WRITE_ENUM_FIELD(DropBehavior, behavior, behavior);
  WRITE_BOOL_FIELD(missing_ok, missing_ok);
}

static void
_outSetOperationStmt(PgQuery__SetOperationStmt * out_node, const SetOperationStmt *node)
{
  WRITE_ENUM_FIELD(SetOperation, op, op);
  WRITE_BOOL_FIELD(all, all);
  WRITE_NODE_PTR_FIELD(larg, larg);
  WRITE_NODE_PTR_FIELD(rarg, rarg);
  WRITE_LIST_FIELD(col_types, colTypes);
  WRITE_LIST_FIELD(col_typmods, colTypmods);
  WRITE_LIST_FIELD(col_collations, colCollations);
  WRITE_LIST_FIELD(group_clauses, groupClauses);
}

static void
_outGrantStmt(PgQuery__GrantStmt * out_node, const GrantStmt *node)
{
  WRITE_BOOL_FIELD(is_grant, is_grant);
  WRITE_ENUM_FIELD(GrantTargetType, targtype, targtype);
  WRITE_ENUM_FIELD(ObjectType, objtype, objtype);
  WRITE_LIST_FIELD(objects, objects);
  WRITE_LIST_FIELD(privileges, privileges);
  WRITE_LIST_FIELD(grantees, grantees);
  WRITE_BOOL_FIELD(grant_option, grant_option);
  WRITE_ENUM_FIELD(DropBehavior, behavior, behavior);
}

static void
_outGrantRoleStmt(PgQuery__GrantRoleStmt * out_node, const GrantRoleStmt *node)
{
  WRITE_LIST_FIELD(granted_roles, granted_roles);
  WRITE_LIST_FIELD(grantee_roles, grantee_roles);
  WRITE_BOOL_FIELD(is_grant, is_grant);
  WRITE_BOOL_FIELD(admin_opt, admin_opt);
  WRITE_SPECIFIC_NODE_PTR_FIELD(RoleSpec, role_spec, grantor, grantor);
  WRITE_ENUM_FIELD(DropBehavior, behavior, behavior);
}

static void
_outAlterDefaultPrivilegesStmt(PgQuery__AlterDefaultPrivilegesStmt * out_node, const AlterDefaultPrivilegesStmt *node)
{
  WRITE_LIST_FIELD(options, options);
  WRITE_SPECIFIC_NODE_PTR_FIELD(GrantStmt, grant_stmt, action, action);
}

static void
_outClosePortalStmt(PgQuery__ClosePortalStmt * out_node, const ClosePortalStmt *node)
{
  WRITE_STRING_FIELD(portalname, portalname);
}

static void
_outClusterStmt(PgQuery__ClusterStmt * out_node, const ClusterStmt *node)
{
  WRITE_SPECIFIC_NODE_PTR_FIELD(RangeVar, range_var, relation, relation);
  WRITE_STRING_FIELD(indexname, indexname);
  WRITE_INT_FIELD(options, options);
}

static void
_outCopyStmt(PgQuery__CopyStmt * out_node, const CopyStmt *node)
{
  WRITE_SPECIFIC_NODE_PTR_FIELD(RangeVar, range_var, relation, relation);
  WRITE_NODE_PTR_FIELD(query, query);
  WRITE_LIST_FIELD(attlist, attlist);
  WRITE_BOOL_FIELD(is_from, is_from);
  WRITE_BOOL_FIELD(is_program, is_program);
  WRITE_STRING_FIELD(filename, filename);
  WRITE_LIST_FIELD(options, options);
  WRITE_NODE_PTR_FIELD(where_clause, whereClause);
}

static void
_outCreateStmt(PgQuery__CreateStmt * out_node, const CreateStmt *node)
{
  WRITE_SPECIFIC_NODE_PTR_FIELD(RangeVar, range_var, relation, relation);
  WRITE_LIST_FIELD(table_elts, tableElts);
  WRITE_LIST_FIELD(inh_relations, inhRelations);
  WRITE_SPECIFIC_NODE_PTR_FIELD(PartitionBoundSpec, partition_bound_spec, partbound, partbound);
  WRITE_SPECIFIC_NODE_PTR_FIELD(PartitionSpec, partition_spec, partspec, partspec);
  WRITE_SPECIFIC_NODE_PTR_FIELD(TypeName, type_name, of_typename, ofTypename);
  WRITE_LIST_FIELD(constraints, constraints);
  WRITE_LIST_FIELD(options, options);
  WRITE_ENUM_FIELD(OnCommitAction, oncommit, oncommit);
  WRITE_STRING_FIELD(tablespacename, tablespacename);
  WRITE_STRING_FIELD(access_method, accessMethod);
  WRITE_BOOL_FIELD(if_not_exists, if_not_exists);
}

static void
_outDefineStmt(PgQuery__DefineStmt * out_node, const DefineStmt *node)
{
  WRITE_ENUM_FIELD(ObjectType, kind, kind);
  WRITE_BOOL_FIELD(oldstyle, oldstyle);
  WRITE_LIST_FIELD(defnames, defnames);
  WRITE_LIST_FIELD(args, args);
  WRITE_LIST_FIELD(definition, definition);
  WRITE_BOOL_FIELD(if_not_exists, if_not_exists);
  WRITE_BOOL_FIELD(replace, replace);
}

static void
_outDropStmt(PgQuery__DropStmt * out_node, const DropStmt *node)
{
  WRITE_LIST_FIELD(objects, objects);
  WRITE_ENUM_FIELD(ObjectType, remove_type, removeType);
  WRITE_ENUM_FIELD(DropBehavior, behavior, behavior);
  WRITE_BOOL_FIELD(missing_ok, missing_ok);
  WRITE_BOOL_FIELD(concurrent, concurrent);
}

static void
_outTruncateStmt(PgQuery__TruncateStmt * out_node, const TruncateStmt *node)
{
  WRITE_LIST_FIELD(relations, relations);
  WRITE_BOOL_FIELD(restart_seqs, restart_seqs);
  WRITE_ENUM_FIELD(DropBehavior, behavior, behavior);
}

static void
_outCommentStmt(PgQuery__CommentStmt * out_node, const CommentStmt *node)
{
  WRITE_ENUM_FIELD(ObjectType, objtype, objtype);
  WRITE_NODE_PTR_FIELD(object, object);
  WRITE_STRING_FIELD(comment, comment);
}

static void
_outFetchStmt(PgQuery__FetchStmt * out_node, const FetchStmt *node)
{
  WRITE_ENUM_FIELD(FetchDirection, direction, direction);
  WRITE_LONG_FIELD(how_many, howMany);
  WRITE_STRING_FIELD(portalname, portalname);
  WRITE_BOOL_FIELD(ismove, ismove);
}

static void
_outIndexStmt(PgQuery__IndexStmt * out_node, const IndexStmt *node)
{
  WRITE_STRING_FIELD(idxname, idxname);
  WRITE_SPECIFIC_NODE_PTR_FIELD(RangeVar, range_var, relation, relation);
  WRITE_STRING_FIELD(access_method, accessMethod);
  WRITE_STRING_FIELD(table_space, tableSpace);
  WRITE_LIST_FIELD(index_params, indexParams);
  WRITE_LIST_FIELD(index_including_params, indexIncludingParams);
  WRITE_LIST_FIELD(options, options);
  WRITE_NODE_PTR_FIELD(where_clause, whereClause);
  WRITE_LIST_FIELD(exclude_op_names, excludeOpNames);
  WRITE_STRING_FIELD(idxcomment, idxcomment);
  WRITE_UINT_FIELD(index_oid, indexOid);
  WRITE_UINT_FIELD(old_node, oldNode);
  WRITE_UINT_FIELD(old_create_subid, oldCreateSubid);
  WRITE_UINT_FIELD(old_first_relfilenode_subid, oldFirstRelfilenodeSubid);
  WRITE_BOOL_FIELD(unique, unique);
  WRITE_BOOL_FIELD(primary, primary);
  WRITE_BOOL_FIELD(isconstraint, isconstraint);
  WRITE_BOOL_FIELD(deferrable, deferrable);
  WRITE_BOOL_FIELD(initdeferred, initdeferred);
  WRITE_BOOL_FIELD(transformed, transformed);
  WRITE_BOOL_FIELD(concurrent, concurrent);
  WRITE_BOOL_FIELD(if_not_exists, if_not_exists);
  WRITE_BOOL_FIELD(reset_default_tblspc, reset_default_tblspc);
}

static void
_outCreateFunctionStmt(PgQuery__CreateFunctionStmt * out_node, const CreateFunctionStmt *node)
{
  WRITE_BOOL_FIELD(is_procedure, is_procedure);
  WRITE_BOOL_FIELD(replace, replace);
  WRITE_LIST_FIELD(funcname, funcname);
  WRITE_LIST_FIELD(parameters, parameters);
  WRITE_SPECIFIC_NODE_PTR_FIELD(TypeName, type_name, return_type, returnType);
  WRITE_LIST_FIELD(options, options);
}

static void
_outAlterFunctionStmt(PgQuery__AlterFunctionStmt * out_node, const AlterFunctionStmt *node)
{
  WRITE_ENUM_FIELD(ObjectType, objtype, objtype);
  WRITE_SPECIFIC_NODE_PTR_FIELD(ObjectWithArgs, object_with_args, func, func);
  WRITE_LIST_FIELD(actions, actions);
}

static void
_outDoStmt(PgQuery__DoStmt * out_node, const DoStmt *node)
{
  WRITE_LIST_FIELD(args, args);
}

static void
_outRenameStmt(PgQuery__RenameStmt * out_node, const RenameStmt *node)
{
  WRITE_ENUM_FIELD(ObjectType, rename_type, renameType);
  WRITE_ENUM_FIELD(ObjectType, relation_type, relationType);
  WRITE_SPECIFIC_NODE_PTR_FIELD(RangeVar, range_var, relation, relation);
  WRITE_NODE_PTR_FIELD(object, object);
  WRITE_STRING_FIELD(subname, subname);
  WRITE_STRING_FIELD(newname, newname);
  WRITE_ENUM_FIELD(DropBehavior, behavior, behavior);
  WRITE_BOOL_FIELD(missing_ok, missing_ok);
}

static void
_outRuleStmt(PgQuery__RuleStmt * out_node, const RuleStmt *node)
{
  WRITE_SPECIFIC_NODE_PTR_FIELD(RangeVar, range_var, relation, relation);
  WRITE_STRING_FIELD(rulename, rulename);
  WRITE_NODE_PTR_FIELD(where_clause, whereClause);
  WRITE_ENUM_FIELD(CmdType, event, event);
  WRITE_BOOL_FIELD(instead, instead);
  WRITE_LIST_FIELD(actions, actions);
  WRITE_BOOL_FIELD(replace, replace);
}

static void
_outNotifyStmt(PgQuery__NotifyStmt * out_node, const NotifyStmt *node)
{
  WRITE_STRING_FIELD(conditionname, conditionname);
  WRITE_STRING_FIELD(payload, payload);
}

static void
_outListenStmt(PgQuery__ListenStmt * out_node, const ListenStmt *node)
{
  WRITE_STRING_FIELD(conditionname, conditionname);
}

static void
_outUnlistenStmt(PgQuery__UnlistenStmt * out_node, const UnlistenStmt *node)
{
  WRITE_STRING_FIELD(conditionname, conditionname);
}

static void
_outTransactionStmt(PgQuery__TransactionStmt * out_node, const TransactionStmt *node)
{
  WRITE_ENUM_FIELD(TransactionStmtKind, kind, kind);
  WRITE_LIST_FIELD(options, options);
  WRITE_STRING_FIELD(savepoint_name, savepoint_name);
  WRITE_STRING_FIELD(gid, gid);
  WRITE_BOOL_FIELD(chain, chain);
}

static void
_outViewStmt(PgQuery__ViewStmt * out_node, const ViewStmt *node)
{
  WRITE_SPECIFIC_NODE_PTR_FIELD(RangeVar, range_var, view, view);
  WRITE_LIST_FIELD(aliases, aliases);
  WRITE_NODE_PTR_FIELD(query, query);
  WRITE_BOOL_FIELD(replace, replace);
  WRITE_LIST_FIELD(options, options);
  WRITE_ENUM_FIELD(ViewCheckOption, with_check_option, withCheckOption);
}

static void
_outLoadStmt(PgQuery__LoadStmt * out_node, const LoadStmt *node)
{
  WRITE_STRING_FIELD(filename, filename);
}

static void
_outCreateDomainStmt(PgQuery__CreateDomainStmt * out_node, const CreateDomainStmt *node)
{
  WRITE_LIST_FIELD(domainname, domainname);
  WRITE_SPECIFIC_NODE_PTR_FIELD(TypeName, type_name, type_name, typeName);
  WRITE_SPECIFIC_NODE_PTR_FIELD(CollateClause, collate_clause, coll_clause, collClause);
  WRITE_LIST_FIELD(constraints, constraints);
}

static void
_outCreatedbStmt(PgQuery__CreatedbStmt * out_node, const CreatedbStmt *node)
{
  WRITE_STRING_FIELD(dbname, dbname);
  WRITE_LIST_FIELD(options, options);
}

static void
_outDropdbStmt(PgQuery__DropdbStmt * out_node, const DropdbStmt *node)
{
  WRITE_STRING_FIELD(dbname, dbname);
  WRITE_BOOL_FIELD(missing_ok, missing_ok);
  WRITE_LIST_FIELD(options, options);
}

static void
_outVacuumStmt(PgQuery__VacuumStmt * out_node, const VacuumStmt *node)
{
  WRITE_LIST_FIELD(options, options);
  WRITE_LIST_FIELD(rels, rels);
  WRITE_BOOL_FIELD(is_vacuumcmd, is_vacuumcmd);
}

static void
_outExplainStmt(PgQuery__ExplainStmt * out_node, const ExplainStmt *node)
{
  WRITE_NODE_PTR_FIELD(query, query);
  WRITE_LIST_FIELD(options, options);
}

static void
_outCreateTableAsStmt(PgQuery__CreateTableAsStmt * out_node, const CreateTableAsStmt *node)
{
  WRITE_NODE_PTR_FIELD(query, query);
  WRITE_SPECIFIC_NODE_PTR_FIELD(IntoClause, into_clause, into, into);
  WRITE_ENUM_FIELD(ObjectType, relkind, relkind);
  WRITE_BOOL_FIELD(is_select_into, is_select_into);
  WRITE_BOOL_FIELD(if_not_exists, if_not_exists);
}

static void
_outCreateSeqStmt(PgQuery__CreateSeqStmt * out_node, const CreateSeqStmt *node)
{
  WRITE_SPECIFIC_NODE_PTR_FIELD(RangeVar, range_var, sequence, sequence);
  WRITE_LIST_FIELD(options, options);
  WRITE_UINT_FIELD(owner_id, ownerId);
  WRITE_BOOL_FIELD(for_identity, for_identity);
  WRITE_BOOL_FIELD(if_not_exists, if_not_exists);
}

static void
_outAlterSeqStmt(PgQuery__AlterSeqStmt * out_node, const AlterSeqStmt *node)
{
  WRITE_SPECIFIC_NODE_PTR_FIELD(RangeVar, range_var, sequence, sequence);
  WRITE_LIST_FIELD(options, options);
  WRITE_BOOL_FIELD(for_identity, for_identity);
  WRITE_BOOL_FIELD(missing_ok, missing_ok);
}

static void
_outVariableSetStmt(PgQuery__VariableSetStmt * out_node, const VariableSetStmt *node)
{
  WRITE_ENUM_FIELD(VariableSetKind, kind, kind);
  WRITE_STRING_FIELD(name, name);
  WRITE_LIST_FIELD(args, args);
  WRITE_BOOL_FIELD(is_local, is_local);
}

static void
_outVariableShowStmt(PgQuery__VariableShowStmt * out_node, const VariableShowStmt *node)
{
  WRITE_STRING_FIELD(name, name);
}

static void
_outDiscardStmt(PgQuery__DiscardStmt * out_node, const DiscardStmt *node)
{
  WRITE_ENUM_FIELD(DiscardMode, target, target);
}

static void
_outCreateTrigStmt(PgQuery__CreateTrigStmt * out_node, const CreateTrigStmt *node)
{
  WRITE_STRING_FIELD(trigname, trigname);
  WRITE_SPECIFIC_NODE_PTR_FIELD(RangeVar, range_var, relation, relation);
  WRITE_LIST_FIELD(funcname, funcname);
  WRITE_LIST_FIELD(args, args);
  WRITE_BOOL_FIELD(row, row);
  WRITE_INT_FIELD(timing, timing);
  WRITE_INT_FIELD(events, events);
  WRITE_LIST_FIELD(columns, columns);
  WRITE_NODE_PTR_FIELD(when_clause, whenClause);
  WRITE_BOOL_FIELD(isconstraint, isconstraint);
  WRITE_LIST_FIELD(transition_rels, transitionRels);
  WRITE_BOOL_FIELD(deferrable, deferrable);
  WRITE_BOOL_FIELD(initdeferred, initdeferred);
  WRITE_SPECIFIC_NODE_PTR_FIELD(RangeVar, range_var, constrrel, constrrel);
}

static void
_outCreatePLangStmt(PgQuery__CreatePLangStmt * out_node, const CreatePLangStmt *node)
{
  WRITE_BOOL_FIELD(replace, replace);
  WRITE_STRING_FIELD(plname, plname);
  WRITE_LIST_FIELD(plhandler, plhandler);
  WRITE_LIST_FIELD(plinline, plinline);
  WRITE_LIST_FIELD(plvalidator, plvalidator);
  WRITE_BOOL_FIELD(pltrusted, pltrusted);
}

static void
_outCreateRoleStmt(PgQuery__CreateRoleStmt * out_node, const CreateRoleStmt *node)
{
  WRITE_ENUM_FIELD(RoleStmtType, stmt_type, stmt_type);
  WRITE_STRING_FIELD(role, role);
  WRITE_LIST_FIELD(options, options);
}

static void
_outAlterRoleStmt(PgQuery__AlterRoleStmt * out_node, const AlterRoleStmt *node)
{
  WRITE_SPECIFIC_NODE_PTR_FIELD(RoleSpec, role_spec, role, role);
  WRITE_LIST_FIELD(options, options);
  WRITE_INT_FIELD(action, action);
}

static void
_outDropRoleStmt(PgQuery__DropRoleStmt * out_node, const DropRoleStmt *node)
{
  WRITE_LIST_FIELD(roles, roles);
  WRITE_BOOL_FIELD(missing_ok, missing_ok);
}

static void
_outLockStmt(PgQuery__LockStmt * out_node, const LockStmt *node)
{
  WRITE_LIST_FIELD(relations, relations);
  WRITE_INT_FIELD(mode, mode);
  WRITE_BOOL_FIELD(nowait, nowait);
}

static void
_outConstraintsSetStmt(PgQuery__ConstraintsSetStmt * out_node, const ConstraintsSetStmt *node)
{
  WRITE_LIST_FIELD(constraints, constraints);
  WRITE_BOOL_FIELD(deferred, deferred);
}

static void
_outReindexStmt(PgQuery__ReindexStmt * out_node, const ReindexStmt *node)
{
  WRITE_ENUM_FIELD(ReindexObjectType, kind, kind);
  WRITE_SPECIFIC_NODE_PTR_FIELD(RangeVar, range_var, relation, relation);
  WRITE_STRING_FIELD(name, name);
  WRITE_INT_FIELD(options, options);
  WRITE_BOOL_FIELD(concurrent, concurrent);
}

static void
_outCheckPointStmt(PgQuery__CheckPointStmt * out_node, const CheckPointStmt *node)
{
}

static void
_outCreateSchemaStmt(PgQuery__CreateSchemaStmt * out_node, const CreateSchemaStmt *node)
{
  WRITE_STRING_FIELD(schemaname, schemaname);
  WRITE_SPECIFIC_NODE_PTR_FIELD(RoleSpec, role_spec, authrole, authrole);
  WRITE_LIST_FIELD(schema_elts, schemaElts);
  WRITE_BOOL_FIELD(if_not_exists, if_not_exists);
}

static void
_outAlterDatabaseStmt(PgQuery__AlterDatabaseStmt * out_node, const AlterDatabaseStmt *node)
{
  WRITE_STRING_FIELD(dbname, dbname);
  WRITE_LIST_FIELD(options, options);
}

static void
_outAlterDatabaseSetStmt(PgQuery__AlterDatabaseSetStmt * out_node, const AlterDatabaseSetStmt *node)
{
  WRITE_STRING_FIELD(dbname, dbname);
  WRITE_SPECIFIC_NODE_PTR_FIELD(VariableSetStmt, variable_set_stmt, setstmt, setstmt);
}

static void
_outAlterRoleSetStmt(PgQuery__AlterRoleSetStmt * out_node, const AlterRoleSetStmt *node)
{
  WRITE_SPECIFIC_NODE_PTR_FIELD(RoleSpec, role_spec, role, role);
  WRITE_STRING_FIELD(database, database);
  WRITE_SPECIFIC_NODE_PTR_FIELD(VariableSetStmt, variable_set_stmt, setstmt, setstmt);
}

static void
_outCreateConversionStmt(PgQuery__CreateConversionStmt * out_node, const CreateConversionStmt *node)
{
  WRITE_LIST_FIELD(conversion_name, conversion_name);
  WRITE_STRING_FIELD(for_encoding_name, for_encoding_name);
  WRITE_STRING_FIELD(to_encoding_name, to_encoding_name);
  WRITE_LIST_FIELD(func_name, func_name);
  WRITE_BOOL_FIELD(def, def);
}

static void
_outCreateCastStmt(PgQuery__CreateCastStmt * out_node, const CreateCastStmt *node)
{
  WRITE_SPECIFIC_NODE_PTR_FIELD(TypeName, type_name, sourcetype, sourcetype);
  WRITE_SPECIFIC_NODE_PTR_FIELD(TypeName, type_name, targettype, targettype);
  WRITE_SPECIFIC_NODE_PTR_FIELD(ObjectWithArgs, object_with_args, func, func);
  WRITE_ENUM_FIELD(CoercionContext, context, context);
  WRITE_BOOL_FIELD(inout, inout);
}

static void
_outCreateOpClassStmt(PgQuery__CreateOpClassStmt * out_node, const CreateOpClassStmt *node)
{
  WRITE_LIST_FIELD(opclassname, opclassname);
  WRITE_LIST_FIELD(opfamilyname, opfamilyname);
  WRITE_STRING_FIELD(amname, amname);
  WRITE_SPECIFIC_NODE_PTR_FIELD(TypeName, type_name, datatype, datatype);
  WRITE_LIST_FIELD(items, items);
  WRITE_BOOL_FIELD(is_default, isDefault);
}

static void
_outCreateOpFamilyStmt(PgQuery__CreateOpFamilyStmt * out_node, const CreateOpFamilyStmt *node)
{
  WRITE_LIST_FIELD(opfamilyname, opfamilyname);
  WRITE_STRING_FIELD(amname, amname);
}

static void
_outAlterOpFamilyStmt(PgQuery__AlterOpFamilyStmt * out_node, const AlterOpFamilyStmt *node)
{
  WRITE_LIST_FIELD(opfamilyname, opfamilyname);
  WRITE_STRING_FIELD(amname, amname);
  WRITE_BOOL_FIELD(is_drop, isDrop);
  WRITE_LIST_FIELD(items, items);
}

static void
_outPrepareStmt(PgQuery__PrepareStmt * out_node, const PrepareStmt *node)
{
  WRITE_STRING_FIELD(name, name);
  WRITE_LIST_FIELD(argtypes, argtypes);
  WRITE_NODE_PTR_FIELD(query, query);
}

static void
_outExecuteStmt(PgQuery__ExecuteStmt * out_node, const ExecuteStmt *node)
{
  WRITE_STRING_FIELD(name, name);
  WRITE_LIST_FIELD(params, params);
}

static void
_outDeallocateStmt(PgQuery__DeallocateStmt * out_node, const DeallocateStmt *node)
{
  WRITE_STRING_FIELD(name, name);
}

static void
_outDeclareCursorStmt(PgQuery__DeclareCursorStmt * out_node, const DeclareCursorStmt *node)
{
  WRITE_STRING_FIELD(portalname, portalname);
  WRITE_INT_FIELD(options, options);
  WRITE_NODE_PTR_FIELD(query, query);
}

static void
_outCreateTableSpaceStmt(PgQuery__CreateTableSpaceStmt * out_node, const CreateTableSpaceStmt *node)
{
  WRITE_STRING_FIELD(tablespacename, tablespacename);
  WRITE_SPECIFIC_NODE_PTR_FIELD(RoleSpec, role_spec, owner, owner);
  WRITE_STRING_FIELD(location, location);
  WRITE_LIST_FIELD(options, options);
}

static void
_outDropTableSpaceStmt(PgQuery__DropTableSpaceStmt * out_node, const DropTableSpaceStmt *node)
{
  WRITE_STRING_FIELD(tablespacename, tablespacename);
  WRITE_BOOL_FIELD(missing_ok, missing_ok);
}

static void
_outAlterObjectDependsStmt(PgQuery__AlterObjectDependsStmt * out_node, const AlterObjectDependsStmt *node)
{
  WRITE_ENUM_FIELD(ObjectType, object_type, objectType);
  WRITE_SPECIFIC_NODE_PTR_FIELD(RangeVar, range_var, relation, relation);
  WRITE_NODE_PTR_FIELD(object, object);
  WRITE_NODE_PTR_FIELD(extname, extname);
  WRITE_BOOL_FIELD(remove, remove);
}

static void
_outAlterObjectSchemaStmt(PgQuery__AlterObjectSchemaStmt * out_node, const AlterObjectSchemaStmt *node)
{
  WRITE_ENUM_FIELD(ObjectType, object_type, objectType);
  WRITE_SPECIFIC_NODE_PTR_FIELD(RangeVar, range_var, relation, relation);
  WRITE_NODE_PTR_FIELD(object, object);
  WRITE_STRING_FIELD(newschema, newschema);
  WRITE_BOOL_FIELD(missing_ok, missing_ok);
}

static void
_outAlterOwnerStmt(PgQuery__AlterOwnerStmt * out_node, const AlterOwnerStmt *node)
{
  WRITE_ENUM_FIELD(ObjectType, object_type, objectType);
  WRITE_SPECIFIC_NODE_PTR_FIELD(RangeVar, range_var, relation, relation);
  WRITE_NODE_PTR_FIELD(object, object);
  WRITE_SPECIFIC_NODE_PTR_FIELD(RoleSpec, role_spec, newowner, newowner);
}

static void
_outAlterOperatorStmt(PgQuery__AlterOperatorStmt * out_node, const AlterOperatorStmt *node)
{
  WRITE_SPECIFIC_NODE_PTR_FIELD(ObjectWithArgs, object_with_args, opername, opername);
  WRITE_LIST_FIELD(options, options);
}

static void
_outAlterTypeStmt(PgQuery__AlterTypeStmt * out_node, const AlterTypeStmt *node)
{
  WRITE_LIST_FIELD(type_name, typeName);
  WRITE_LIST_FIELD(options, options);
}

static void
_outDropOwnedStmt(PgQuery__DropOwnedStmt * out_node, const DropOwnedStmt *node)
{
  WRITE_LIST_FIELD(roles, roles);
  WRITE_ENUM_FIELD(DropBehavior, behavior, behavior);
}

static void
_outReassignOwnedStmt(PgQuery__ReassignOwnedStmt * out_node, const ReassignOwnedStmt *node)
{
  WRITE_LIST_FIELD(roles, roles);
  WRITE_SPECIFIC_NODE_PTR_FIELD(RoleSpec, role_spec, newrole, newrole);
}

static void
_outCompositeTypeStmt(PgQuery__CompositeTypeStmt * out_node, const CompositeTypeStmt *node)
{
  WRITE_SPECIFIC_NODE_PTR_FIELD(RangeVar, range_var, typevar, typevar);
  WRITE_LIST_FIELD(coldeflist, coldeflist);
}

static void
_outCreateEnumStmt(PgQuery__CreateEnumStmt * out_node, const CreateEnumStmt *node)
{
  WRITE_LIST_FIELD(type_name, typeName);
  WRITE_LIST_FIELD(vals, vals);
}

static void
_outCreateRangeStmt(PgQuery__CreateRangeStmt * out_node, const CreateRangeStmt *node)
{
  WRITE_LIST_FIELD(type_name, typeName);
  WRITE_LIST_FIELD(params, params);
}

static void
_outAlterEnumStmt(PgQuery__AlterEnumStmt * out_node, const AlterEnumStmt *node)
{
  WRITE_LIST_FIELD(type_name, typeName);
  WRITE_STRING_FIELD(old_val, oldVal);
  WRITE_STRING_FIELD(new_val, newVal);
  WRITE_STRING_FIELD(new_val_neighbor, newValNeighbor);
  WRITE_BOOL_FIELD(new_val_is_after, newValIsAfter);
  WRITE_BOOL_FIELD(skip_if_new_val_exists, skipIfNewValExists);
}

static void
_outAlterTSDictionaryStmt(PgQuery__AlterTSDictionaryStmt * out_node, const AlterTSDictionaryStmt *node)
{
  WRITE_LIST_FIELD(dictname, dictname);
  WRITE_LIST_FIELD(options, options);
}

static void
_outAlterTSConfigurationStmt(PgQuery__AlterTSConfigurationStmt * out_node, const AlterTSConfigurationStmt *node)
{
  WRITE_ENUM_FIELD(AlterTSConfigType, kind, kind);
  WRITE_LIST_FIELD(cfgname, cfgname);
  WRITE_LIST_FIELD(tokentype, tokentype);
  WRITE_LIST_FIELD(dicts, dicts);
  WRITE_BOOL_FIELD(override, override);
  WRITE_BOOL_FIELD(replace, replace);
  WRITE_BOOL_FIELD(missing_ok, missing_ok);
}

static void
_outCreateFdwStmt(PgQuery__CreateFdwStmt * out_node, const CreateFdwStmt *node)
{
  WRITE_STRING_FIELD(fdwname, fdwname);
  WRITE_LIST_FIELD(func_options, func_options);
  WRITE_LIST_FIELD(options, options);
}

static void
_outAlterFdwStmt(PgQuery__AlterFdwStmt * out_node, const AlterFdwStmt *node)
{
  WRITE_STRING_FIELD(fdwname, fdwname);
  WRITE_LIST_FIELD(func_options, func_options);
  WRITE_LIST_FIELD(options, options);
}

static void
_outCreateForeignServerStmt(PgQuery__CreateForeignServerStmt * out_node, const CreateForeignServerStmt *node)
{
  WRITE_STRING_FIELD(servername, servername);
  WRITE_STRING_FIELD(servertype, servertype);
  WRITE_STRING_FIELD(version, version);
  WRITE_STRING_FIELD(fdwname, fdwname);
  WRITE_BOOL_FIELD(if_not_exists, if_not_exists);
  WRITE_LIST_FIELD(options, options);
}

static void
_outAlterForeignServerStmt(PgQuery__AlterForeignServerStmt * out_node, const AlterForeignServerStmt *node)
{
  WRITE_STRING_FIELD(servername, servername);
  WRITE_STRING_FIELD(version, version);
  WRITE_LIST_FIELD(options, options);
  WRITE_BOOL_FIELD(has_version, has_version);
}

static void
_outCreateUserMappingStmt(PgQuery__CreateUserMappingStmt * out_node, const CreateUserMappingStmt *node)
{
  WRITE_SPECIFIC_NODE_PTR_FIELD(RoleSpec, role_spec, user, user);
  WRITE_STRING_FIELD(servername, servername);
  WRITE_BOOL_FIELD(if_not_exists, if_not_exists);
  WRITE_LIST_FIELD(options, options);
}

static void
_outAlterUserMappingStmt(PgQuery__AlterUserMappingStmt * out_node, const AlterUserMappingStmt *node)
{
  WRITE_SPECIFIC_NODE_PTR_FIELD(RoleSpec, role_spec, user, user);
  WRITE_STRING_FIELD(servername, servername);
  WRITE_LIST_FIELD(options, options);
}

static void
_outDropUserMappingStmt(PgQuery__DropUserMappingStmt * out_node, const DropUserMappingStmt *node)
{
  WRITE_SPECIFIC_NODE_PTR_FIELD(RoleSpec, role_spec, user, user);
  WRITE_STRING_FIELD(servername, servername);
  WRITE_BOOL_FIELD(missing_ok, missing_ok);
}

static void
_outAlterTableSpaceOptionsStmt(PgQuery__AlterTableSpaceOptionsStmt * out_node, const AlterTableSpaceOptionsStmt *node)
{
  WRITE_STRING_FIELD(tablespacename, tablespacename);
  WRITE_LIST_FIELD(options, options);
  WRITE_BOOL_FIELD(is_reset, isReset);
}

static void
_outAlterTableMoveAllStmt(PgQuery__AlterTableMoveAllStmt * out_node, const AlterTableMoveAllStmt *node)
{
  WRITE_STRING_FIELD(orig_tablespacename, orig_tablespacename);
  WRITE_ENUM_FIELD(ObjectType, objtype, objtype);
  WRITE_LIST_FIELD(roles, roles);
  WRITE_STRING_FIELD(new_tablespacename, new_tablespacename);
  WRITE_BOOL_FIELD(nowait, nowait);
}

static void
_outSecLabelStmt(PgQuery__SecLabelStmt * out_node, const SecLabelStmt *node)
{
  WRITE_ENUM_FIELD(ObjectType, objtype, objtype);
  WRITE_NODE_PTR_FIELD(object, object);
  WRITE_STRING_FIELD(provider, provider);
  WRITE_STRING_FIELD(label, label);
}

static void
_outCreateForeignTableStmt(PgQuery__CreateForeignTableStmt * out_node, const CreateForeignTableStmt *node)
{
  WRITE_SPECIFIC_NODE_FIELD(CreateStmt, create_stmt, base_stmt, base);
  WRITE_STRING_FIELD(servername, servername);
  WRITE_LIST_FIELD(options, options);
}

static void
_outImportForeignSchemaStmt(PgQuery__ImportForeignSchemaStmt * out_node, const ImportForeignSchemaStmt *node)
{
  WRITE_STRING_FIELD(server_name, server_name);
  WRITE_STRING_FIELD(remote_schema, remote_schema);
  WRITE_STRING_FIELD(local_schema, local_schema);
  WRITE_ENUM_FIELD(ImportForeignSchemaType, list_type, list_type);
  WRITE_LIST_FIELD(table_list, table_list);
  WRITE_LIST_FIELD(options, options);
}

static void
_outCreateExtensionStmt(PgQuery__CreateExtensionStmt * out_node, const CreateExtensionStmt *node)
{
  WRITE_STRING_FIELD(extname, extname);
  WRITE_BOOL_FIELD(if_not_exists, if_not_exists);
  WRITE_LIST_FIELD(options, options);
}

static void
_outAlterExtensionStmt(PgQuery__AlterExtensionStmt * out_node, const AlterExtensionStmt *node)
{
  WRITE_STRING_FIELD(extname, extname);
  WRITE_LIST_FIELD(options, options);
}

static void
_outAlterExtensionContentsStmt(PgQuery__AlterExtensionContentsStmt * out_node, const AlterExtensionContentsStmt *node)
{
  WRITE_STRING_FIELD(extname, extname);
  WRITE_INT_FIELD(action, action);
  WRITE_ENUM_FIELD(ObjectType, objtype, objtype);
  WRITE_NODE_PTR_FIELD(object, object);
}

static void
_outCreateEventTrigStmt(PgQuery__CreateEventTrigStmt * out_node, const CreateEventTrigStmt *node)
{
  WRITE_STRING_FIELD(trigname, trigname);
  WRITE_STRING_FIELD(eventname, eventname);
  WRITE_LIST_FIELD(whenclause, whenclause);
  WRITE_LIST_FIELD(funcname, funcname);
}

static void
_outAlterEventTrigStmt(PgQuery__AlterEventTrigStmt * out_node, const AlterEventTrigStmt *node)
{
  WRITE_STRING_FIELD(trigname, trigname);
  WRITE_CHAR_FIELD(tgenabled, tgenabled);
}

static void
_outRefreshMatViewStmt(PgQuery__RefreshMatViewStmt * out_node, const RefreshMatViewStmt *node)
{
  WRITE_BOOL_FIELD(concurrent, concurrent);
  WRITE_BOOL_FIELD(skip_data, skipData);
  WRITE_SPECIFIC_NODE_PTR_FIELD(RangeVar, range_var, relation, relation);
}

static void
_outReplicaIdentityStmt(PgQuery__ReplicaIdentityStmt * out_node, const ReplicaIdentityStmt *node)
{
  WRITE_CHAR_FIELD(identity_type, identity_type);
  WRITE_STRING_FIELD(name, name);
}

static void
_outAlterSystemStmt(PgQuery__AlterSystemStmt * out_node, const AlterSystemStmt *node)
{
  WRITE_SPECIFIC_NODE_PTR_FIELD(VariableSetStmt, variable_set_stmt, setstmt, setstmt);
}

static void
_outCreatePolicyStmt(PgQuery__CreatePolicyStmt * out_node, const CreatePolicyStmt *node)
{
  WRITE_STRING_FIELD(policy_name, policy_name);
  WRITE_SPECIFIC_NODE_PTR_FIELD(RangeVar, range_var, table, table);
  WRITE_STRING_FIELD(cmd_name, cmd_name);
  WRITE_BOOL_FIELD(permissive, permissive);
  WRITE_LIST_FIELD(roles, roles);
  WRITE_NODE_PTR_FIELD(qual, qual);
  WRITE_NODE_PTR_FIELD(with_check, with_check);
}

static void
_outAlterPolicyStmt(PgQuery__AlterPolicyStmt * out_node, const AlterPolicyStmt *node)
{
  WRITE_STRING_FIELD(policy_name, policy_name);
  WRITE_SPECIFIC_NODE_PTR_FIELD(RangeVar, range_var, table, table);
  WRITE_LIST_FIELD(roles, roles);
  WRITE_NODE_PTR_FIELD(qual, qual);
  WRITE_NODE_PTR_FIELD(with_check, with_check);
}

static void
_outCreateTransformStmt(PgQuery__CreateTransformStmt * out_node, const CreateTransformStmt *node)
{
  WRITE_BOOL_FIELD(replace, replace);
  WRITE_SPECIFIC_NODE_PTR_FIELD(TypeName, type_name, type_name, type_name);
  WRITE_STRING_FIELD(lang, lang);
  WRITE_SPECIFIC_NODE_PTR_FIELD(ObjectWithArgs, object_with_args, fromsql, fromsql);
  WRITE_SPECIFIC_NODE_PTR_FIELD(ObjectWithArgs, object_with_args, tosql, tosql);
}

static void
_outCreateAmStmt(PgQuery__CreateAmStmt * out_node, const CreateAmStmt *node)
{
  WRITE_STRING_FIELD(amname, amname);
  WRITE_LIST_FIELD(handler_name, handler_name);
  WRITE_CHAR_FIELD(amtype, amtype);
}

static void
_outCreatePublicationStmt(PgQuery__CreatePublicationStmt * out_node, const CreatePublicationStmt *node)
{
  WRITE_STRING_FIELD(pubname, pubname);
  WRITE_LIST_FIELD(options, options);
  WRITE_LIST_FIELD(tables, tables);
  WRITE_BOOL_FIELD(for_all_tables, for_all_tables);
}

static void
_outAlterPublicationStmt(PgQuery__AlterPublicationStmt * out_node, const AlterPublicationStmt *node)
{
  WRITE_STRING_FIELD(pubname, pubname);
  WRITE_LIST_FIELD(options, options);
  WRITE_LIST_FIELD(tables, tables);
  WRITE_BOOL_FIELD(for_all_tables, for_all_tables);
  WRITE_ENUM_FIELD(DefElemAction, table_action, tableAction);
}

static void
_outCreateSubscriptionStmt(PgQuery__CreateSubscriptionStmt * out_node, const CreateSubscriptionStmt *node)
{
  WRITE_STRING_FIELD(subname, subname);
  WRITE_STRING_FIELD(conninfo, conninfo);
  WRITE_LIST_FIELD(publication, publication);
  WRITE_LIST_FIELD(options, options);
}

static void
_outAlterSubscriptionStmt(PgQuery__AlterSubscriptionStmt * out_node, const AlterSubscriptionStmt *node)
{
  WRITE_ENUM_FIELD(AlterSubscriptionType, kind, kind);
  WRITE_STRING_FIELD(subname, subname);
  WRITE_STRING_FIELD(conninfo, conninfo);
  WRITE_LIST_FIELD(publication, publication);
  WRITE_LIST_FIELD(options, options);
}

static void
_outDropSubscriptionStmt(PgQuery__DropSubscriptionStmt * out_node, const DropSubscriptionStmt *node)
{
  WRITE_STRING_FIELD(subname, subname);
  WRITE_BOOL_FIELD(missing_ok, missing_ok);
  WRITE_ENUM_FIELD(DropBehavior, behavior, behavior);
}

static void
_outCreateStatsStmt(PgQuery__CreateStatsStmt * out_node, const CreateStatsStmt *node)
{
  WRITE_LIST_FIELD(defnames, defnames);
  WRITE_LIST_FIELD(stat_types, stat_types);
  WRITE_LIST_FIELD(exprs, exprs);
  WRITE_LIST_FIELD(relations, relations);
  WRITE_STRING_FIELD(stxcomment, stxcomment);
  WRITE_BOOL_FIELD(if_not_exists, if_not_exists);
}

static void
_outAlterCollationStmt(PgQuery__AlterCollationStmt * out_node, const AlterCollationStmt *node)
{
  WRITE_LIST_FIELD(collname, collname);
}

static void
_outCallStmt(PgQuery__CallStmt * out_node, const CallStmt *node)
{
  WRITE_SPECIFIC_NODE_PTR_FIELD(FuncCall, func_call, funccall, funccall);
  WRITE_SPECIFIC_NODE_PTR_FIELD(FuncExpr, func_expr, funcexpr, funcexpr);
}

static void
_outAlterStatsStmt(PgQuery__AlterStatsStmt * out_node, const AlterStatsStmt *node)
{
  WRITE_LIST_FIELD(defnames, defnames);
  WRITE_INT_FIELD(stxstattarget, stxstattarget);
  WRITE_BOOL_FIELD(missing_ok, missing_ok);
}

static void
_outAExpr(PgQuery__AExpr * out_node, const A_Expr *node)
{
  WRITE_ENUM_FIELD(A_Expr_Kind, kind, kind);
  WRITE_LIST_FIELD(name, name);
  WRITE_NODE_PTR_FIELD(lexpr, lexpr);
  WRITE_NODE_PTR_FIELD(rexpr, rexpr);
  WRITE_INT_FIELD(location, location);
}

static void
_outColumnRef(PgQuery__ColumnRef * out_node, const ColumnRef *node)
{
  WRITE_LIST_FIELD(fields, fields);
  WRITE_INT_FIELD(location, location);
}

static void
_outParamRef(PgQuery__ParamRef * out_node, const ParamRef *node)
{
  WRITE_INT_FIELD(number, number);
  WRITE_INT_FIELD(location, location);
}

static void
_outAConst(PgQuery__AConst * out_node, const A_Const *node)
{
  WRITE_NODE_FIELD(val, val);
  WRITE_INT_FIELD(location, location);
}

static void
_outFuncCall(PgQuery__FuncCall * out_node, const FuncCall *node)
{
  WRITE_LIST_FIELD(funcname, funcname);
  WRITE_LIST_FIELD(args, args);
  WRITE_LIST_FIELD(agg_order, agg_order);
  WRITE_NODE_PTR_FIELD(agg_filter, agg_filter);
  WRITE_BOOL_FIELD(agg_within_group, agg_within_group);
  WRITE_BOOL_FIELD(agg_star, agg_star);
  WRITE_BOOL_FIELD(agg_distinct, agg_distinct);
  WRITE_BOOL_FIELD(func_variadic, func_variadic);
  WRITE_SPECIFIC_NODE_PTR_FIELD(WindowDef, window_def, over, over);
  WRITE_INT_FIELD(location, location);
}

static void
_outAStar(PgQuery__AStar * out_node, const A_Star *node)
{
}

static void
_outAIndices(PgQuery__AIndices * out_node, const A_Indices *node)
{
  WRITE_BOOL_FIELD(is_slice, is_slice);
  WRITE_NODE_PTR_FIELD(lidx, lidx);
  WRITE_NODE_PTR_FIELD(uidx, uidx);
}

static void
_outAIndirection(PgQuery__AIndirection * out_node, const A_Indirection *node)
{
  WRITE_NODE_PTR_FIELD(arg, arg);
  WRITE_LIST_FIELD(indirection, indirection);
}

static void
_outAArrayExpr(PgQuery__AArrayExpr * out_node, const A_ArrayExpr *node)
{
  WRITE_LIST_FIELD(elements, elements);
  WRITE_INT_FIELD(location, location);
}

static void
_outResTarget(PgQuery__ResTarget * out_node, const ResTarget *node)
{
  WRITE_STRING_FIELD(name, name);
  WRITE_LIST_FIELD(indirection, indirection);
  WRITE_NODE_PTR_FIELD(val, val);
  WRITE_INT_FIELD(location, location);
}

static void
_outMultiAssignRef(PgQuery__MultiAssignRef * out_node, const MultiAssignRef *node)
{
  WRITE_NODE_PTR_FIELD(source, source);
  WRITE_INT_FIELD(colno, colno);
  WRITE_INT_FIELD(ncolumns, ncolumns);
}

static void
_outTypeCast(PgQuery__TypeCast * out_node, const TypeCast *node)
{
  WRITE_NODE_PTR_FIELD(arg, arg);
  WRITE_SPECIFIC_NODE_PTR_FIELD(TypeName, type_name, type_name, typeName);
  WRITE_INT_FIELD(location, location);
}

static void
_outCollateClause(PgQuery__CollateClause * out_node, const CollateClause *node)
{
  WRITE_NODE_PTR_FIELD(arg, arg);
  WRITE_LIST_FIELD(collname, collname);
  WRITE_INT_FIELD(location, location);
}

static void
_outSortBy(PgQuery__SortBy * out_node, const SortBy *node)
{
  WRITE_NODE_PTR_FIELD(node, node);
  WRITE_ENUM_FIELD(SortByDir, sortby_dir, sortby_dir);
  WRITE_ENUM_FIELD(SortByNulls, sortby_nulls, sortby_nulls);
  WRITE_LIST_FIELD(use_op, useOp);
  WRITE_INT_FIELD(location, location);
}

static void
_outWindowDef(PgQuery__WindowDef * out_node, const WindowDef *node)
{
  WRITE_STRING_FIELD(name, name);
  WRITE_STRING_FIELD(refname, refname);
  WRITE_LIST_FIELD(partition_clause, partitionClause);
  WRITE_LIST_FIELD(order_clause, orderClause);
  WRITE_INT_FIELD(frame_options, frameOptions);
  WRITE_NODE_PTR_FIELD(start_offset, startOffset);
  WRITE_NODE_PTR_FIELD(end_offset, endOffset);
  WRITE_INT_FIELD(location, location);
}

static void
_outRangeSubselect(PgQuery__RangeSubselect * out_node, const RangeSubselect *node)
{
  WRITE_BOOL_FIELD(lateral, lateral);
  WRITE_NODE_PTR_FIELD(subquery, subquery);
  WRITE_SPECIFIC_NODE_PTR_FIELD(Alias, alias, alias, alias);
}

static void
_outRangeFunction(PgQuery__RangeFunction * out_node, const RangeFunction *node)
{
  WRITE_BOOL_FIELD(lateral, lateral);
  WRITE_BOOL_FIELD(ordinality, ordinality);
  WRITE_BOOL_FIELD(is_rowsfrom, is_rowsfrom);
  WRITE_LIST_FIELD(functions, functions);
  WRITE_SPECIFIC_NODE_PTR_FIELD(Alias, alias, alias, alias);
  WRITE_LIST_FIELD(coldeflist, coldeflist);
}

static void
_outRangeTableSample(PgQuery__RangeTableSample * out_node, const RangeTableSample *node)
{
  WRITE_NODE_PTR_FIELD(relation, relation);
  WRITE_LIST_FIELD(method, method);
  WRITE_LIST_FIELD(args, args);
  WRITE_NODE_PTR_FIELD(repeatable, repeatable);
  WRITE_INT_FIELD(location, location);
}

static void
_outRangeTableFunc(PgQuery__RangeTableFunc * out_node, const RangeTableFunc *node)
{
  WRITE_BOOL_FIELD(lateral, lateral);
  WRITE_NODE_PTR_FIELD(docexpr, docexpr);
  WRITE_NODE_PTR_FIELD(rowexpr, rowexpr);
  WRITE_LIST_FIELD(namespaces, namespaces);
  WRITE_LIST_FIELD(columns, columns);
  WRITE_SPECIFIC_NODE_PTR_FIELD(Alias, alias, alias, alias);
  WRITE_INT_FIELD(location, location);
}

static void
_outRangeTableFuncCol(PgQuery__RangeTableFuncCol * out_node, const RangeTableFuncCol *node)
{
  WRITE_STRING_FIELD(colname, colname);
  WRITE_SPECIFIC_NODE_PTR_FIELD(TypeName, type_name, type_name, typeName);
  WRITE_BOOL_FIELD(for_ordinality, for_ordinality);
  WRITE_BOOL_FIELD(is_not_null, is_not_null);
  WRITE_NODE_PTR_FIELD(colexpr, colexpr);
  WRITE_NODE_PTR_FIELD(coldefexpr, coldefexpr);
  WRITE_INT_FIELD(location, location);
}

static void
_outTypeName(PgQuery__TypeName * out_node, const TypeName *node)
{
  WRITE_LIST_FIELD(names, names);
  WRITE_UINT_FIELD(type_oid, typeOid);
  WRITE_BOOL_FIELD(setof, setof);
  WRITE_BOOL_FIELD(pct_type, pct_type);
  WRITE_LIST_FIELD(typmods, typmods);
  WRITE_INT_FIELD(typemod, typemod);
  WRITE_LIST_FIELD(array_bounds, arrayBounds);
  WRITE_INT_FIELD(location, location);
}

static void
_outColumnDef(PgQuery__ColumnDef * out_node, const ColumnDef *node)
{
  WRITE_STRING_FIELD(colname, colname);
  WRITE_SPECIFIC_NODE_PTR_FIELD(TypeName, type_name, type_name, typeName);
  WRITE_INT_FIELD(inhcount, inhcount);
  WRITE_BOOL_FIELD(is_local, is_local);
  WRITE_BOOL_FIELD(is_not_null, is_not_null);
  WRITE_BOOL_FIELD(is_from_type, is_from_type);
  WRITE_CHAR_FIELD(storage, storage);
  WRITE_NODE_PTR_FIELD(raw_default, raw_default);
  WRITE_NODE_PTR_FIELD(cooked_default, cooked_default);
  WRITE_CHAR_FIELD(identity, identity);
  WRITE_SPECIFIC_NODE_PTR_FIELD(RangeVar, range_var, identity_sequence, identitySequence);
  WRITE_CHAR_FIELD(generated, generated);
  WRITE_SPECIFIC_NODE_PTR_FIELD(CollateClause, collate_clause, coll_clause, collClause);
  WRITE_UINT_FIELD(coll_oid, collOid);
  WRITE_LIST_FIELD(constraints, constraints);
  WRITE_LIST_FIELD(fdwoptions, fdwoptions);
  WRITE_INT_FIELD(location, location);
}

static void
_outIndexElem(PgQuery__IndexElem * out_node, const IndexElem *node)
{
  WRITE_STRING_FIELD(name, name);
  WRITE_NODE_PTR_FIELD(expr, expr);
  WRITE_STRING_FIELD(indexcolname, indexcolname);
  WRITE_LIST_FIELD(collation, collation);
  WRITE_LIST_FIELD(opclass, opclass);
  WRITE_LIST_FIELD(opclassopts, opclassopts);
  WRITE_ENUM_FIELD(SortByDir, ordering, ordering);
  WRITE_ENUM_FIELD(SortByNulls, nulls_ordering, nulls_ordering);
}

static void
_outConstraint(PgQuery__Constraint * out_node, const Constraint *node)
{
  WRITE_ENUM_FIELD(ConstrType, contype, contype);
  WRITE_STRING_FIELD(conname, conname);
  WRITE_BOOL_FIELD(deferrable, deferrable);
  WRITE_BOOL_FIELD(initdeferred, initdeferred);
  WRITE_INT_FIELD(location, location);
  WRITE_BOOL_FIELD(is_no_inherit, is_no_inherit);
  WRITE_NODE_PTR_FIELD(raw_expr, raw_expr);
  WRITE_STRING_FIELD(cooked_expr, cooked_expr);
  WRITE_CHAR_FIELD(generated_when, generated_when);
  WRITE_LIST_FIELD(keys, keys);
  WRITE_LIST_FIELD(including, including);
  WRITE_LIST_FIELD(exclusions, exclusions);
  WRITE_LIST_FIELD(options, options);
  WRITE_STRING_FIELD(indexname, indexname);
  WRITE_STRING_FIELD(indexspace, indexspace);
  WRITE_BOOL_FIELD(reset_default_tblspc, reset_default_tblspc);
  WRITE_STRING_FIELD(access_method, access_method);
  WRITE_NODE_PTR_FIELD(where_clause, where_clause);
  WRITE_SPECIFIC_NODE_PTR_FIELD(RangeVar, range_var, pktable, pktable);
  WRITE_LIST_FIELD(fk_attrs, fk_attrs);
  WRITE_LIST_FIELD(pk_attrs, pk_attrs);
  WRITE_CHAR_FIELD(fk_matchtype, fk_matchtype);
  WRITE_CHAR_FIELD(fk_upd_action, fk_upd_action);
  WRITE_CHAR_FIELD(fk_del_action, fk_del_action);
  WRITE_LIST_FIELD(old_conpfeqop, old_conpfeqop);
  WRITE_UINT_FIELD(old_pktable_oid, old_pktable_oid);
  WRITE_BOOL_FIELD(skip_validation, skip_validation);
  WRITE_BOOL_FIELD(initially_valid, initially_valid);
}

static void
_outDefElem(PgQuery__DefElem * out_node, const DefElem *node)
{
  WRITE_STRING_FIELD(defnamespace, defnamespace);
  WRITE_STRING_FIELD(defname, defname);
  WRITE_NODE_PTR_FIELD(arg, arg);
  WRITE_ENUM_FIELD(DefElemAction, defaction, defaction);
  WRITE_INT_FIELD(location, location);
}

static void
_outRangeTblEntry(PgQuery__RangeTblEntry * out_node, const RangeTblEntry *node)
{
  WRITE_ENUM_FIELD(RTEKind, rtekind, rtekind);
  WRITE_UINT_FIELD(relid, relid);
  WRITE_CHAR_FIELD(relkind, relkind);
  WRITE_INT_FIELD(rellockmode, rellockmode);
  WRITE_SPECIFIC_NODE_PTR_FIELD(TableSampleClause, table_sample_clause, tablesample, tablesample);
  WRITE_SPECIFIC_NODE_PTR_FIELD(Query, query, subquery, subquery);
  WRITE_BOOL_FIELD(security_barrier, security_barrier);
  WRITE_ENUM_FIELD(JoinType, jointype, jointype);
  WRITE_INT_FIELD(joinmergedcols, joinmergedcols);
  WRITE_LIST_FIELD(joinaliasvars, joinaliasvars);
  WRITE_LIST_FIELD(joinleftcols, joinleftcols);
  WRITE_LIST_FIELD(joinrightcols, joinrightcols);
  WRITE_LIST_FIELD(functions, functions);
  WRITE_BOOL_FIELD(funcordinality, funcordinality);
  WRITE_SPECIFIC_NODE_PTR_FIELD(TableFunc, table_func, tablefunc, tablefunc);
  WRITE_LIST_FIELD(values_lists, values_lists);
  WRITE_STRING_FIELD(ctename, ctename);
  WRITE_UINT_FIELD(ctelevelsup, ctelevelsup);
  WRITE_BOOL_FIELD(self_reference, self_reference);
  WRITE_LIST_FIELD(coltypes, coltypes);
  WRITE_LIST_FIELD(coltypmods, coltypmods);
  WRITE_LIST_FIELD(colcollations, colcollations);
  WRITE_STRING_FIELD(enrname, enrname);
  WRITE_FLOAT_FIELD(enrtuples, enrtuples);
  WRITE_SPECIFIC_NODE_PTR_FIELD(Alias, alias, alias, alias);
  WRITE_SPECIFIC_NODE_PTR_FIELD(Alias, alias, eref, eref);
  WRITE_BOOL_FIELD(lateral, lateral);
  WRITE_BOOL_FIELD(inh, inh);
  WRITE_BOOL_FIELD(in_from_cl, inFromCl);
  WRITE_UINT_FIELD(required_perms, requiredPerms);
  WRITE_UINT_FIELD(check_as_user, checkAsUser);
  WRITE_BITMAPSET_FIELD(selected_cols, selectedCols);
  WRITE_BITMAPSET_FIELD(inserted_cols, insertedCols);
  WRITE_BITMAPSET_FIELD(updated_cols, updatedCols);
  WRITE_BITMAPSET_FIELD(extra_updated_cols, extraUpdatedCols);
  WRITE_LIST_FIELD(security_quals, securityQuals);
}

static void
_outRangeTblFunction(PgQuery__RangeTblFunction * out_node, const RangeTblFunction *node)
{
  WRITE_NODE_PTR_FIELD(funcexpr, funcexpr);
  WRITE_INT_FIELD(funccolcount, funccolcount);
  WRITE_LIST_FIELD(funccolnames, funccolnames);
  WRITE_LIST_FIELD(funccoltypes, funccoltypes);
  WRITE_LIST_FIELD(funccoltypmods, funccoltypmods);
  WRITE_LIST_FIELD(funccolcollations, funccolcollations);
  WRITE_BITMAPSET_FIELD(funcparams, funcparams);
}

static void
_outTableSampleClause(PgQuery__TableSampleClause * out_node, const TableSampleClause *node)
{
  WRITE_UINT_FIELD(tsmhandler, tsmhandler);
  WRITE_LIST_FIELD(args, args);
  WRITE_NODE_PTR_FIELD(repeatable, repeatable);
}

static void
_outWithCheckOption(PgQuery__WithCheckOption * out_node, const WithCheckOption *node)
{
  WRITE_ENUM_FIELD(WCOKind, kind, kind);
  WRITE_STRING_FIELD(relname, relname);
  WRITE_STRING_FIELD(polname, polname);
  WRITE_NODE_PTR_FIELD(qual, qual);
  WRITE_BOOL_FIELD(cascaded, cascaded);
}

static void
_outSortGroupClause(PgQuery__SortGroupClause * out_node, const SortGroupClause *node)
{
  WRITE_UINT_FIELD(tle_sort_group_ref, tleSortGroupRef);
  WRITE_UINT_FIELD(eqop, eqop);
  WRITE_UINT_FIELD(sortop, sortop);
  WRITE_BOOL_FIELD(nulls_first, nulls_first);
  WRITE_BOOL_FIELD(hashable, hashable);
}

static void
_outGroupingSet(PgQuery__GroupingSet * out_node, const GroupingSet *node)
{
  WRITE_ENUM_FIELD(GroupingSetKind, kind, kind);
  WRITE_LIST_FIELD(content, content);
  WRITE_INT_FIELD(location, location);
}

static void
_outWindowClause(PgQuery__WindowClause * out_node, const WindowClause *node)
{
  WRITE_STRING_FIELD(name, name);
  WRITE_STRING_FIELD(refname, refname);
  WRITE_LIST_FIELD(partition_clause, partitionClause);
  WRITE_LIST_FIELD(order_clause, orderClause);
  WRITE_INT_FIELD(frame_options, frameOptions);
  WRITE_NODE_PTR_FIELD(start_offset, startOffset);
  WRITE_NODE_PTR_FIELD(end_offset, endOffset);
  WRITE_UINT_FIELD(start_in_range_func, startInRangeFunc);
  WRITE_UINT_FIELD(end_in_range_func, endInRangeFunc);
  WRITE_UINT_FIELD(in_range_coll, inRangeColl);
  WRITE_BOOL_FIELD(in_range_asc, inRangeAsc);
  WRITE_BOOL_FIELD(in_range_nulls_first, inRangeNullsFirst);
  WRITE_UINT_FIELD(winref, winref);
  WRITE_BOOL_FIELD(copied_order, copiedOrder);
}

static void
_outObjectWithArgs(PgQuery__ObjectWithArgs * out_node, const ObjectWithArgs *node)
{
  WRITE_LIST_FIELD(objname, objname);
  WRITE_LIST_FIELD(objargs, objargs);
  WRITE_BOOL_FIELD(args_unspecified, args_unspecified);
}

static void
_outAccessPriv(PgQuery__AccessPriv * out_node, const AccessPriv *node)
{
  WRITE_STRING_FIELD(priv_name, priv_name);
  WRITE_LIST_FIELD(cols, cols);
}

static void
_outCreateOpClassItem(PgQuery__CreateOpClassItem * out_node, const CreateOpClassItem *node)
{
  WRITE_INT_FIELD(itemtype, itemtype);
  WRITE_SPECIFIC_NODE_PTR_FIELD(ObjectWithArgs, object_with_args, name, name);
  WRITE_INT_FIELD(number, number);
  WRITE_LIST_FIELD(order_family, order_family);
  WRITE_LIST_FIELD(class_args, class_args);
  WRITE_SPECIFIC_NODE_PTR_FIELD(TypeName, type_name, storedtype, storedtype);
}

static void
_outTableLikeClause(PgQuery__TableLikeClause * out_node, const TableLikeClause *node)
{
  WRITE_SPECIFIC_NODE_PTR_FIELD(RangeVar, range_var, relation, relation);
  WRITE_UINT_FIELD(options, options);
}

static void
_outFunctionParameter(PgQuery__FunctionParameter * out_node, const FunctionParameter *node)
{
  WRITE_STRING_FIELD(name, name);
  WRITE_SPECIFIC_NODE_PTR_FIELD(TypeName, type_name, arg_type, argType);
  WRITE_ENUM_FIELD(FunctionParameterMode, mode, mode);
  WRITE_NODE_PTR_FIELD(defexpr, defexpr);
}

static void
_outLockingClause(PgQuery__LockingClause * out_node, const LockingClause *node)
{
  WRITE_LIST_FIELD(locked_rels, lockedRels);
  WRITE_ENUM_FIELD(LockClauseStrength, strength, strength);
  WRITE_ENUM_FIELD(LockWaitPolicy, wait_policy, waitPolicy);
}

static void
_outRowMarkClause(PgQuery__RowMarkClause * out_node, const RowMarkClause *node)
{
  WRITE_UINT_FIELD(rti, rti);
  WRITE_ENUM_FIELD(LockClauseStrength, strength, strength);
  WRITE_ENUM_FIELD(LockWaitPolicy, wait_policy, waitPolicy);
  WRITE_BOOL_FIELD(pushed_down, pushedDown);
}

static void
_outXmlSerialize(PgQuery__XmlSerialize * out_node, const XmlSerialize *node)
{
  WRITE_ENUM_FIELD(XmlOptionType, xmloption, xmloption);
  WRITE_NODE_PTR_FIELD(expr, expr);
  WRITE_SPECIFIC_NODE_PTR_FIELD(TypeName, type_name, type_name, typeName);
  WRITE_INT_FIELD(location, location);
}

static void
_outWithClause(PgQuery__WithClause * out_node, const WithClause *node)
{
  WRITE_LIST_FIELD(ctes, ctes);
  WRITE_BOOL_FIELD(recursive, recursive);
  WRITE_INT_FIELD(location, location);
}

static void
_outInferClause(PgQuery__InferClause * out_node, const InferClause *node)
{
  WRITE_LIST_FIELD(index_elems, indexElems);
  WRITE_NODE_PTR_FIELD(where_clause, whereClause);
  WRITE_STRING_FIELD(conname, conname);
  WRITE_INT_FIELD(location, location);
}

static void
_outOnConflictClause(PgQuery__OnConflictClause * out_node, const OnConflictClause *node)
{
  WRITE_ENUM_FIELD(OnConflictAction, action, action);
  WRITE_SPECIFIC_NODE_PTR_FIELD(InferClause, infer_clause, infer, infer);
  WRITE_LIST_FIELD(target_list, targetList);
  WRITE_NODE_PTR_FIELD(where_clause, whereClause);
  WRITE_INT_FIELD(location, location);
}

static void
_outCommonTableExpr(PgQuery__CommonTableExpr * out_node, const CommonTableExpr *node)
{
  WRITE_STRING_FIELD(ctename, ctename);
  WRITE_LIST_FIELD(aliascolnames, aliascolnames);
  WRITE_ENUM_FIELD(CTEMaterialize, ctematerialized, ctematerialized);
  WRITE_NODE_PTR_FIELD(ctequery, ctequery);
  WRITE_INT_FIELD(location, location);
  WRITE_BOOL_FIELD(cterecursive, cterecursive);
  WRITE_INT_FIELD(cterefcount, cterefcount);
  WRITE_LIST_FIELD(ctecolnames, ctecolnames);
  WRITE_LIST_FIELD(ctecoltypes, ctecoltypes);
  WRITE_LIST_FIELD(ctecoltypmods, ctecoltypmods);
  WRITE_LIST_FIELD(ctecolcollations, ctecolcollations);
}

static void
_outRoleSpec(PgQuery__RoleSpec * out_node, const RoleSpec *node)
{
  WRITE_ENUM_FIELD(RoleSpecType, roletype, roletype);
  WRITE_STRING_FIELD(rolename, rolename);
  WRITE_INT_FIELD(location, location);
}

static void
_outTriggerTransition(PgQuery__TriggerTransition * out_node, const TriggerTransition *node)
{
  WRITE_STRING_FIELD(name, name);
  WRITE_BOOL_FIELD(is_new, isNew);
  WRITE_BOOL_FIELD(is_table, isTable);
}

static void
_outPartitionElem(PgQuery__PartitionElem * out_node, const PartitionElem *node)
{
  WRITE_STRING_FIELD(name, name);
  WRITE_NODE_PTR_FIELD(expr, expr);
  WRITE_LIST_FIELD(collation, collation);
  WRITE_LIST_FIELD(opclass, opclass);
  WRITE_INT_FIELD(location, location);
}

static void
_outPartitionSpec(PgQuery__PartitionSpec * out_node, const PartitionSpec *node)
{
  WRITE_STRING_FIELD(strategy, strategy);
  WRITE_LIST_FIELD(part_params, partParams);
  WRITE_INT_FIELD(location, location);
}

static void
_outPartitionBoundSpec(PgQuery__PartitionBoundSpec * out_node, const PartitionBoundSpec *node)
{
  WRITE_CHAR_FIELD(strategy, strategy);
  WRITE_BOOL_FIELD(is_default, is_default);
  WRITE_INT_FIELD(modulus, modulus);
  WRITE_INT_FIELD(remainder, remainder);
  WRITE_LIST_FIELD(listdatums, listdatums);
  WRITE_LIST_FIELD(lowerdatums, lowerdatums);
  WRITE_LIST_FIELD(upperdatums, upperdatums);
  WRITE_INT_FIELD(location, location);
}

static void
_outPartitionRangeDatum(PgQuery__PartitionRangeDatum * out_node, const PartitionRangeDatum *node)
{
  WRITE_ENUM_FIELD(PartitionRangeDatumKind, kind, kind);
  WRITE_NODE_PTR_FIELD(value, value);
  WRITE_INT_FIELD(location, location);
}

static void
_outPartitionCmd(PgQuery__PartitionCmd * out_node, const PartitionCmd *node)
{
  WRITE_SPECIFIC_NODE_PTR_FIELD(RangeVar, range_var, name, name);
  WRITE_SPECIFIC_NODE_PTR_FIELD(PartitionBoundSpec, partition_bound_spec, bound, bound);
}

static void
_outVacuumRelation(PgQuery__VacuumRelation * out_node, const VacuumRelation *node)
{
  WRITE_SPECIFIC_NODE_PTR_FIELD(RangeVar, range_var, relation, relation);
  WRITE_UINT_FIELD(oid, oid);
  WRITE_LIST_FIELD(va_cols, va_cols);
}

static void
_outInlineCodeBlock(PgQuery__InlineCodeBlock * out_node, const InlineCodeBlock *node)
{
  WRITE_STRING_FIELD(source_text, source_text);
  WRITE_UINT_FIELD(lang_oid, langOid);
  WRITE_BOOL_FIELD(lang_is_trusted, langIsTrusted);
  WRITE_BOOL_FIELD(atomic, atomic);
}

static void
_outCallContext(PgQuery__CallContext * out_node, const CallContext *node)
{
  WRITE_BOOL_FIELD(atomic, atomic);
}

