static void _fingerprintAlias(FingerprintContext *ctx, const Alias *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintRangeVar(FingerprintContext *ctx, const RangeVar *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintTableFunc(FingerprintContext *ctx, const TableFunc *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintIntoClause(FingerprintContext *ctx, const IntoClause *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintVar(FingerprintContext *ctx, const Var *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintConst(FingerprintContext *ctx, const Const *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintParam(FingerprintContext *ctx, const Param *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintAggref(FingerprintContext *ctx, const Aggref *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintGroupingFunc(FingerprintContext *ctx, const GroupingFunc *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintWindowFunc(FingerprintContext *ctx, const WindowFunc *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintWindowFuncRunCondition(FingerprintContext *ctx, const WindowFuncRunCondition *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintMergeSupportFunc(FingerprintContext *ctx, const MergeSupportFunc *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintSubscriptingRef(FingerprintContext *ctx, const SubscriptingRef *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintFuncExpr(FingerprintContext *ctx, const FuncExpr *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintNamedArgExpr(FingerprintContext *ctx, const NamedArgExpr *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintOpExpr(FingerprintContext *ctx, const OpExpr *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintScalarArrayOpExpr(FingerprintContext *ctx, const ScalarArrayOpExpr *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintBoolExpr(FingerprintContext *ctx, const BoolExpr *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintSubLink(FingerprintContext *ctx, const SubLink *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintSubPlan(FingerprintContext *ctx, const SubPlan *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintAlternativeSubPlan(FingerprintContext *ctx, const AlternativeSubPlan *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintFieldSelect(FingerprintContext *ctx, const FieldSelect *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintFieldStore(FingerprintContext *ctx, const FieldStore *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintRelabelType(FingerprintContext *ctx, const RelabelType *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintCoerceViaIO(FingerprintContext *ctx, const CoerceViaIO *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintArrayCoerceExpr(FingerprintContext *ctx, const ArrayCoerceExpr *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintConvertRowtypeExpr(FingerprintContext *ctx, const ConvertRowtypeExpr *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintCollateExpr(FingerprintContext *ctx, const CollateExpr *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintCaseExpr(FingerprintContext *ctx, const CaseExpr *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintCaseWhen(FingerprintContext *ctx, const CaseWhen *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintCaseTestExpr(FingerprintContext *ctx, const CaseTestExpr *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintArrayExpr(FingerprintContext *ctx, const ArrayExpr *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintRowExpr(FingerprintContext *ctx, const RowExpr *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintRowCompareExpr(FingerprintContext *ctx, const RowCompareExpr *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintCoalesceExpr(FingerprintContext *ctx, const CoalesceExpr *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintMinMaxExpr(FingerprintContext *ctx, const MinMaxExpr *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintSQLValueFunction(FingerprintContext *ctx, const SQLValueFunction *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintXmlExpr(FingerprintContext *ctx, const XmlExpr *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintJsonFormat(FingerprintContext *ctx, const JsonFormat *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintJsonReturning(FingerprintContext *ctx, const JsonReturning *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintJsonValueExpr(FingerprintContext *ctx, const JsonValueExpr *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintJsonConstructorExpr(FingerprintContext *ctx, const JsonConstructorExpr *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintJsonIsPredicate(FingerprintContext *ctx, const JsonIsPredicate *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintJsonBehavior(FingerprintContext *ctx, const JsonBehavior *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintJsonExpr(FingerprintContext *ctx, const JsonExpr *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintJsonTablePath(FingerprintContext *ctx, const JsonTablePath *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintJsonTablePathScan(FingerprintContext *ctx, const JsonTablePathScan *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintJsonTableSiblingJoin(FingerprintContext *ctx, const JsonTableSiblingJoin *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintNullTest(FingerprintContext *ctx, const NullTest *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintBooleanTest(FingerprintContext *ctx, const BooleanTest *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintMergeAction(FingerprintContext *ctx, const MergeAction *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintCoerceToDomain(FingerprintContext *ctx, const CoerceToDomain *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintCoerceToDomainValue(FingerprintContext *ctx, const CoerceToDomainValue *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintSetToDefault(FingerprintContext *ctx, const SetToDefault *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintCurrentOfExpr(FingerprintContext *ctx, const CurrentOfExpr *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintNextValueExpr(FingerprintContext *ctx, const NextValueExpr *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintInferenceElem(FingerprintContext *ctx, const InferenceElem *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintReturningExpr(FingerprintContext *ctx, const ReturningExpr *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintTargetEntry(FingerprintContext *ctx, const TargetEntry *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintRangeTblRef(FingerprintContext *ctx, const RangeTblRef *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintJoinExpr(FingerprintContext *ctx, const JoinExpr *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintFromExpr(FingerprintContext *ctx, const FromExpr *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintOnConflictExpr(FingerprintContext *ctx, const OnConflictExpr *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintQuery(FingerprintContext *ctx, const Query *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintTypeName(FingerprintContext *ctx, const TypeName *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintColumnRef(FingerprintContext *ctx, const ColumnRef *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintParamRef(FingerprintContext *ctx, const ParamRef *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintA_Expr(FingerprintContext *ctx, const A_Expr *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintTypeCast(FingerprintContext *ctx, const TypeCast *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintCollateClause(FingerprintContext *ctx, const CollateClause *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintRoleSpec(FingerprintContext *ctx, const RoleSpec *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintFuncCall(FingerprintContext *ctx, const FuncCall *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintA_Star(FingerprintContext *ctx, const A_Star *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintA_Indices(FingerprintContext *ctx, const A_Indices *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintA_Indirection(FingerprintContext *ctx, const A_Indirection *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintA_ArrayExpr(FingerprintContext *ctx, const A_ArrayExpr *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintResTarget(FingerprintContext *ctx, const ResTarget *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintMultiAssignRef(FingerprintContext *ctx, const MultiAssignRef *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintSortBy(FingerprintContext *ctx, const SortBy *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintWindowDef(FingerprintContext *ctx, const WindowDef *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintRangeSubselect(FingerprintContext *ctx, const RangeSubselect *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintRangeFunction(FingerprintContext *ctx, const RangeFunction *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintRangeTableFunc(FingerprintContext *ctx, const RangeTableFunc *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintRangeTableFuncCol(FingerprintContext *ctx, const RangeTableFuncCol *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintRangeTableSample(FingerprintContext *ctx, const RangeTableSample *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintColumnDef(FingerprintContext *ctx, const ColumnDef *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintTableLikeClause(FingerprintContext *ctx, const TableLikeClause *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintIndexElem(FingerprintContext *ctx, const IndexElem *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintDefElem(FingerprintContext *ctx, const DefElem *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintLockingClause(FingerprintContext *ctx, const LockingClause *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintXmlSerialize(FingerprintContext *ctx, const XmlSerialize *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintPartitionElem(FingerprintContext *ctx, const PartitionElem *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintPartitionSpec(FingerprintContext *ctx, const PartitionSpec *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintPartitionBoundSpec(FingerprintContext *ctx, const PartitionBoundSpec *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintPartitionRangeDatum(FingerprintContext *ctx, const PartitionRangeDatum *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintPartitionCmd(FingerprintContext *ctx, const PartitionCmd *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintRangeTblEntry(FingerprintContext *ctx, const RangeTblEntry *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintRTEPermissionInfo(FingerprintContext *ctx, const RTEPermissionInfo *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintRangeTblFunction(FingerprintContext *ctx, const RangeTblFunction *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintTableSampleClause(FingerprintContext *ctx, const TableSampleClause *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintWithCheckOption(FingerprintContext *ctx, const WithCheckOption *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintSortGroupClause(FingerprintContext *ctx, const SortGroupClause *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintGroupingSet(FingerprintContext *ctx, const GroupingSet *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintWindowClause(FingerprintContext *ctx, const WindowClause *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintRowMarkClause(FingerprintContext *ctx, const RowMarkClause *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintWithClause(FingerprintContext *ctx, const WithClause *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintInferClause(FingerprintContext *ctx, const InferClause *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintOnConflictClause(FingerprintContext *ctx, const OnConflictClause *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintCTESearchClause(FingerprintContext *ctx, const CTESearchClause *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintCTECycleClause(FingerprintContext *ctx, const CTECycleClause *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintCommonTableExpr(FingerprintContext *ctx, const CommonTableExpr *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintMergeWhenClause(FingerprintContext *ctx, const MergeWhenClause *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintReturningOption(FingerprintContext *ctx, const ReturningOption *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintReturningClause(FingerprintContext *ctx, const ReturningClause *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintTriggerTransition(FingerprintContext *ctx, const TriggerTransition *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintJsonOutput(FingerprintContext *ctx, const JsonOutput *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintJsonArgument(FingerprintContext *ctx, const JsonArgument *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintJsonFuncExpr(FingerprintContext *ctx, const JsonFuncExpr *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintJsonTablePathSpec(FingerprintContext *ctx, const JsonTablePathSpec *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintJsonTable(FingerprintContext *ctx, const JsonTable *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintJsonTableColumn(FingerprintContext *ctx, const JsonTableColumn *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintJsonKeyValue(FingerprintContext *ctx, const JsonKeyValue *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintJsonParseExpr(FingerprintContext *ctx, const JsonParseExpr *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintJsonScalarExpr(FingerprintContext *ctx, const JsonScalarExpr *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintJsonSerializeExpr(FingerprintContext *ctx, const JsonSerializeExpr *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintJsonObjectConstructor(FingerprintContext *ctx, const JsonObjectConstructor *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintJsonArrayConstructor(FingerprintContext *ctx, const JsonArrayConstructor *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintJsonArrayQueryConstructor(FingerprintContext *ctx, const JsonArrayQueryConstructor *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintJsonAggConstructor(FingerprintContext *ctx, const JsonAggConstructor *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintJsonObjectAgg(FingerprintContext *ctx, const JsonObjectAgg *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintJsonArrayAgg(FingerprintContext *ctx, const JsonArrayAgg *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintRawStmt(FingerprintContext *ctx, const RawStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintInsertStmt(FingerprintContext *ctx, const InsertStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintDeleteStmt(FingerprintContext *ctx, const DeleteStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintUpdateStmt(FingerprintContext *ctx, const UpdateStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintMergeStmt(FingerprintContext *ctx, const MergeStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintSelectStmt(FingerprintContext *ctx, const SelectStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintSetOperationStmt(FingerprintContext *ctx, const SetOperationStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintReturnStmt(FingerprintContext *ctx, const ReturnStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintPLAssignStmt(FingerprintContext *ctx, const PLAssignStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintCreateSchemaStmt(FingerprintContext *ctx, const CreateSchemaStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintAlterTableStmt(FingerprintContext *ctx, const AlterTableStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintAlterTableCmd(FingerprintContext *ctx, const AlterTableCmd *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintATAlterConstraint(FingerprintContext *ctx, const ATAlterConstraint *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintReplicaIdentityStmt(FingerprintContext *ctx, const ReplicaIdentityStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintAlterCollationStmt(FingerprintContext *ctx, const AlterCollationStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintAlterDomainStmt(FingerprintContext *ctx, const AlterDomainStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintGrantStmt(FingerprintContext *ctx, const GrantStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintObjectWithArgs(FingerprintContext *ctx, const ObjectWithArgs *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintAccessPriv(FingerprintContext *ctx, const AccessPriv *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintGrantRoleStmt(FingerprintContext *ctx, const GrantRoleStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintAlterDefaultPrivilegesStmt(FingerprintContext *ctx, const AlterDefaultPrivilegesStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintCopyStmt(FingerprintContext *ctx, const CopyStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintVariableSetStmt(FingerprintContext *ctx, const VariableSetStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintVariableShowStmt(FingerprintContext *ctx, const VariableShowStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintCreateStmt(FingerprintContext *ctx, const CreateStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintConstraint(FingerprintContext *ctx, const Constraint *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintCreateTableSpaceStmt(FingerprintContext *ctx, const CreateTableSpaceStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintDropTableSpaceStmt(FingerprintContext *ctx, const DropTableSpaceStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintAlterTableSpaceOptionsStmt(FingerprintContext *ctx, const AlterTableSpaceOptionsStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintAlterTableMoveAllStmt(FingerprintContext *ctx, const AlterTableMoveAllStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintCreateExtensionStmt(FingerprintContext *ctx, const CreateExtensionStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintAlterExtensionStmt(FingerprintContext *ctx, const AlterExtensionStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintAlterExtensionContentsStmt(FingerprintContext *ctx, const AlterExtensionContentsStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintCreateFdwStmt(FingerprintContext *ctx, const CreateFdwStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintAlterFdwStmt(FingerprintContext *ctx, const AlterFdwStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintCreateForeignServerStmt(FingerprintContext *ctx, const CreateForeignServerStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintAlterForeignServerStmt(FingerprintContext *ctx, const AlterForeignServerStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintCreateForeignTableStmt(FingerprintContext *ctx, const CreateForeignTableStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintCreateUserMappingStmt(FingerprintContext *ctx, const CreateUserMappingStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintAlterUserMappingStmt(FingerprintContext *ctx, const AlterUserMappingStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintDropUserMappingStmt(FingerprintContext *ctx, const DropUserMappingStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintImportForeignSchemaStmt(FingerprintContext *ctx, const ImportForeignSchemaStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintCreatePolicyStmt(FingerprintContext *ctx, const CreatePolicyStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintAlterPolicyStmt(FingerprintContext *ctx, const AlterPolicyStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintCreateAmStmt(FingerprintContext *ctx, const CreateAmStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintCreateTrigStmt(FingerprintContext *ctx, const CreateTrigStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintCreateEventTrigStmt(FingerprintContext *ctx, const CreateEventTrigStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintAlterEventTrigStmt(FingerprintContext *ctx, const AlterEventTrigStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintCreatePLangStmt(FingerprintContext *ctx, const CreatePLangStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintCreateRoleStmt(FingerprintContext *ctx, const CreateRoleStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintAlterRoleStmt(FingerprintContext *ctx, const AlterRoleStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintAlterRoleSetStmt(FingerprintContext *ctx, const AlterRoleSetStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintDropRoleStmt(FingerprintContext *ctx, const DropRoleStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintCreateSeqStmt(FingerprintContext *ctx, const CreateSeqStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintAlterSeqStmt(FingerprintContext *ctx, const AlterSeqStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintDefineStmt(FingerprintContext *ctx, const DefineStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintCreateDomainStmt(FingerprintContext *ctx, const CreateDomainStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintCreateOpClassStmt(FingerprintContext *ctx, const CreateOpClassStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintCreateOpClassItem(FingerprintContext *ctx, const CreateOpClassItem *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintCreateOpFamilyStmt(FingerprintContext *ctx, const CreateOpFamilyStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintAlterOpFamilyStmt(FingerprintContext *ctx, const AlterOpFamilyStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintDropStmt(FingerprintContext *ctx, const DropStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintTruncateStmt(FingerprintContext *ctx, const TruncateStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintCommentStmt(FingerprintContext *ctx, const CommentStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintSecLabelStmt(FingerprintContext *ctx, const SecLabelStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintDeclareCursorStmt(FingerprintContext *ctx, const DeclareCursorStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintClosePortalStmt(FingerprintContext *ctx, const ClosePortalStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintFetchStmt(FingerprintContext *ctx, const FetchStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintIndexStmt(FingerprintContext *ctx, const IndexStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintCreateStatsStmt(FingerprintContext *ctx, const CreateStatsStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintStatsElem(FingerprintContext *ctx, const StatsElem *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintAlterStatsStmt(FingerprintContext *ctx, const AlterStatsStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintCreateFunctionStmt(FingerprintContext *ctx, const CreateFunctionStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintFunctionParameter(FingerprintContext *ctx, const FunctionParameter *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintAlterFunctionStmt(FingerprintContext *ctx, const AlterFunctionStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintDoStmt(FingerprintContext *ctx, const DoStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintInlineCodeBlock(FingerprintContext *ctx, const InlineCodeBlock *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintCallStmt(FingerprintContext *ctx, const CallStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintCallContext(FingerprintContext *ctx, const CallContext *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintRenameStmt(FingerprintContext *ctx, const RenameStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintAlterObjectDependsStmt(FingerprintContext *ctx, const AlterObjectDependsStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintAlterObjectSchemaStmt(FingerprintContext *ctx, const AlterObjectSchemaStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintAlterOwnerStmt(FingerprintContext *ctx, const AlterOwnerStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintAlterOperatorStmt(FingerprintContext *ctx, const AlterOperatorStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintAlterTypeStmt(FingerprintContext *ctx, const AlterTypeStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintRuleStmt(FingerprintContext *ctx, const RuleStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintNotifyStmt(FingerprintContext *ctx, const NotifyStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintListenStmt(FingerprintContext *ctx, const ListenStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintUnlistenStmt(FingerprintContext *ctx, const UnlistenStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintTransactionStmt(FingerprintContext *ctx, const TransactionStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintCompositeTypeStmt(FingerprintContext *ctx, const CompositeTypeStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintCreateEnumStmt(FingerprintContext *ctx, const CreateEnumStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintCreateRangeStmt(FingerprintContext *ctx, const CreateRangeStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintAlterEnumStmt(FingerprintContext *ctx, const AlterEnumStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintViewStmt(FingerprintContext *ctx, const ViewStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintLoadStmt(FingerprintContext *ctx, const LoadStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintCreatedbStmt(FingerprintContext *ctx, const CreatedbStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintAlterDatabaseStmt(FingerprintContext *ctx, const AlterDatabaseStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintAlterDatabaseRefreshCollStmt(FingerprintContext *ctx, const AlterDatabaseRefreshCollStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintAlterDatabaseSetStmt(FingerprintContext *ctx, const AlterDatabaseSetStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintDropdbStmt(FingerprintContext *ctx, const DropdbStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintAlterSystemStmt(FingerprintContext *ctx, const AlterSystemStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintClusterStmt(FingerprintContext *ctx, const ClusterStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintVacuumStmt(FingerprintContext *ctx, const VacuumStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintVacuumRelation(FingerprintContext *ctx, const VacuumRelation *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintExplainStmt(FingerprintContext *ctx, const ExplainStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintCreateTableAsStmt(FingerprintContext *ctx, const CreateTableAsStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintRefreshMatViewStmt(FingerprintContext *ctx, const RefreshMatViewStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintCheckPointStmt(FingerprintContext *ctx, const CheckPointStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintDiscardStmt(FingerprintContext *ctx, const DiscardStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintLockStmt(FingerprintContext *ctx, const LockStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintConstraintsSetStmt(FingerprintContext *ctx, const ConstraintsSetStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintReindexStmt(FingerprintContext *ctx, const ReindexStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintCreateConversionStmt(FingerprintContext *ctx, const CreateConversionStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintCreateCastStmt(FingerprintContext *ctx, const CreateCastStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintCreateTransformStmt(FingerprintContext *ctx, const CreateTransformStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintPrepareStmt(FingerprintContext *ctx, const PrepareStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintExecuteStmt(FingerprintContext *ctx, const ExecuteStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintDeallocateStmt(FingerprintContext *ctx, const DeallocateStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintDropOwnedStmt(FingerprintContext *ctx, const DropOwnedStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintReassignOwnedStmt(FingerprintContext *ctx, const ReassignOwnedStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintAlterTSDictionaryStmt(FingerprintContext *ctx, const AlterTSDictionaryStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintAlterTSConfigurationStmt(FingerprintContext *ctx, const AlterTSConfigurationStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintPublicationTable(FingerprintContext *ctx, const PublicationTable *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintPublicationObjSpec(FingerprintContext *ctx, const PublicationObjSpec *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintCreatePublicationStmt(FingerprintContext *ctx, const CreatePublicationStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintAlterPublicationStmt(FingerprintContext *ctx, const AlterPublicationStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintCreateSubscriptionStmt(FingerprintContext *ctx, const CreateSubscriptionStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintAlterSubscriptionStmt(FingerprintContext *ctx, const AlterSubscriptionStmt *node, const void *parent, const char *field_name, unsigned int depth);
static void _fingerprintDropSubscriptionStmt(FingerprintContext *ctx, const DropSubscriptionStmt *node, const void *parent, const char *field_name, unsigned int depth);


static void
_fingerprintAlias(FingerprintContext *ctx, const Alias *node, const void *parent, const char *field_name, unsigned int depth)
{
  // Intentionally ignoring all fields for fingerprinting
}

// _fingerprintRangeVar has a custom implementation, see pg_query_fingerprint.c

static void
_fingerprintTableFunc(FingerprintContext *ctx, const TableFunc *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->colcollations != NULL && node->colcollations->length > 0)
    _fingerprintChildList(ctx, node->colcollations, node, "colcollations", depth);

  if (node->coldefexprs != NULL && node->coldefexprs->length > 0)
    _fingerprintChildList(ctx, node->coldefexprs, node, "coldefexprs", depth);

  if (node->colexprs != NULL && node->colexprs->length > 0)
    _fingerprintChildList(ctx, node->colexprs, node, "colexprs", depth);

  if (node->colnames != NULL && node->colnames->length > 0)
    _fingerprintChildList(ctx, node->colnames, node, "colnames", depth);

  if (node->coltypes != NULL && node->coltypes->length > 0)
    _fingerprintChildList(ctx, node->coltypes, node, "coltypes", depth);

  if (node->coltypmods != NULL && node->coltypmods->length > 0)
    _fingerprintChildList(ctx, node->coltypmods, node, "coltypmods", depth);

  if (node->colvalexprs != NULL && node->colvalexprs->length > 0)
    _fingerprintChildList(ctx, node->colvalexprs, node, "colvalexprs", depth);

  if (node->docexpr != NULL)
    _fingerprintChildNode(ctx, node->docexpr, node, "docexpr", depth);

  _fingerprintEnumField(ctx, "functype", _enumToStringTableFuncType(node->functype));

  // Intentionally ignoring node->location for fingerprinting

  _fingerprintBitmapsetField(ctx, "notnulls", node->notnulls);

  if (node->ns_names != NULL && node->ns_names->length > 0)
    _fingerprintChildList(ctx, node->ns_names, node, "ns_names", depth);

  if (node->ns_uris != NULL && node->ns_uris->length > 0)
    _fingerprintChildList(ctx, node->ns_uris, node, "ns_uris", depth);

  _fingerprintIntField(ctx, "ordinalitycol", node->ordinalitycol);

  if (node->passingvalexprs != NULL && node->passingvalexprs->length > 0)
    _fingerprintChildList(ctx, node->passingvalexprs, node, "passingvalexprs", depth);

  if (node->plan != NULL)
    _fingerprintChildNode(ctx, node->plan, node, "plan", depth);

  if (node->rowexpr != NULL)
    _fingerprintChildNode(ctx, node->rowexpr, node, "rowexpr", depth);

}

static void
_fingerprintIntoClause(FingerprintContext *ctx, const IntoClause *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintStringField(ctx, "accessMethod", node->accessMethod);

  if (node->colNames != NULL && node->colNames->length > 0)
    _fingerprintChildList(ctx, node->colNames, node, "colNames", depth);

  _fingerprintEnumField(ctx, "onCommit", _enumToStringOnCommitAction(node->onCommit));

  if (node->options != NULL && node->options->length > 0)
    _fingerprintChildList(ctx, node->options, node, "options", depth);

  if (node->rel != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "rel");
    _fingerprintRangeVar(ctx, node->rel, node, "rel", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  _fingerprintBoolField(ctx, "skipData", node->skipData);

  _fingerprintStringField(ctx, "tableSpaceName", node->tableSpaceName);

  if (node->viewQuery != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "viewQuery");
    _fingerprintQuery(ctx, node->viewQuery, node, "viewQuery", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

}

static void
_fingerprintVar(FingerprintContext *ctx, const Var *node, const void *parent, const char *field_name, unsigned int depth)
{
  // Intentionally ignoring node->location for fingerprinting

  _fingerprintIntField(ctx, "varattno", node->varattno);

  _fingerprintIntField(ctx, "varcollid", node->varcollid);

  _fingerprintIntField(ctx, "varlevelsup", node->varlevelsup);

  _fingerprintIntField(ctx, "varno", node->varno);

  _fingerprintBitmapsetField(ctx, "varnullingrels", node->varnullingrels);

  _fingerprintEnumField(ctx, "varreturningtype", _enumToStringVarReturningType(node->varreturningtype));

  _fingerprintIntField(ctx, "vartype", node->vartype);

  _fingerprintIntField(ctx, "vartypmod", node->vartypmod);

}

static void
_fingerprintConst(FingerprintContext *ctx, const Const *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintBoolField(ctx, "constbyval", node->constbyval);

  _fingerprintIntField(ctx, "constcollid", node->constcollid);

  _fingerprintBoolField(ctx, "constisnull", node->constisnull);

  _fingerprintIntField(ctx, "constlen", node->constlen);

  _fingerprintIntField(ctx, "consttype", node->consttype);

  _fingerprintIntField(ctx, "consttypmod", node->consttypmod);

  // Intentionally ignoring node->location for fingerprinting

}

static void
_fingerprintParam(FingerprintContext *ctx, const Param *node, const void *parent, const char *field_name, unsigned int depth)
{
  // Intentionally ignoring node->location for fingerprinting

  _fingerprintIntField(ctx, "paramcollid", node->paramcollid);

  _fingerprintIntField(ctx, "paramid", node->paramid);

  _fingerprintEnumField(ctx, "paramkind", _enumToStringParamKind(node->paramkind));

  _fingerprintIntField(ctx, "paramtype", node->paramtype);

  _fingerprintIntField(ctx, "paramtypmod", node->paramtypmod);

}

static void
_fingerprintAggref(FingerprintContext *ctx, const Aggref *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->aggargtypes != NULL && node->aggargtypes->length > 0)
    _fingerprintChildList(ctx, node->aggargtypes, node, "aggargtypes", depth);

  _fingerprintIntField(ctx, "aggcollid", node->aggcollid);

  if (node->aggdirectargs != NULL && node->aggdirectargs->length > 0)
    _fingerprintChildList(ctx, node->aggdirectargs, node, "aggdirectargs", depth);

  if (node->aggdistinct != NULL && node->aggdistinct->length > 0)
    _fingerprintChildList(ctx, node->aggdistinct, node, "aggdistinct", depth);

  if (node->aggfilter != NULL)
    _fingerprintChildNode(ctx, node->aggfilter, node, "aggfilter", depth);

  _fingerprintIntField(ctx, "aggfnoid", node->aggfnoid);

  _fingerprintCharField(ctx, "aggkind", node->aggkind);

  _fingerprintIntField(ctx, "agglevelsup", node->agglevelsup);

  _fingerprintIntField(ctx, "aggno", node->aggno);

  if (node->aggorder != NULL && node->aggorder->length > 0)
    _fingerprintChildList(ctx, node->aggorder, node, "aggorder", depth);

  _fingerprintEnumField(ctx, "aggsplit", _enumToStringAggSplit(node->aggsplit));

  _fingerprintBoolField(ctx, "aggstar", node->aggstar);

  _fingerprintIntField(ctx, "aggtransno", node->aggtransno);

  _fingerprintIntField(ctx, "aggtype", node->aggtype);

  _fingerprintBoolField(ctx, "aggvariadic", node->aggvariadic);

  if (node->args != NULL && node->args->length > 0)
    _fingerprintChildList(ctx, node->args, node, "args", depth);

  _fingerprintIntField(ctx, "inputcollid", node->inputcollid);

  // Intentionally ignoring node->location for fingerprinting

}

static void
_fingerprintGroupingFunc(FingerprintContext *ctx, const GroupingFunc *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintIntField(ctx, "agglevelsup", node->agglevelsup);

  if (node->args != NULL && node->args->length > 0)
    _fingerprintChildList(ctx, node->args, node, "args", depth);

  // Intentionally ignoring node->location for fingerprinting

  if (node->refs != NULL && node->refs->length > 0)
    _fingerprintChildList(ctx, node->refs, node, "refs", depth);

}

static void
_fingerprintWindowFunc(FingerprintContext *ctx, const WindowFunc *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->aggfilter != NULL)
    _fingerprintChildNode(ctx, node->aggfilter, node, "aggfilter", depth);

  if (node->args != NULL && node->args->length > 0)
    _fingerprintChildList(ctx, node->args, node, "args", depth);

  _fingerprintIntField(ctx, "inputcollid", node->inputcollid);

  // Intentionally ignoring node->location for fingerprinting

  if (node->runCondition != NULL && node->runCondition->length > 0)
    _fingerprintChildList(ctx, node->runCondition, node, "runCondition", depth);

  _fingerprintBoolField(ctx, "winagg", node->winagg);

  _fingerprintIntField(ctx, "wincollid", node->wincollid);

  _fingerprintIntField(ctx, "winfnoid", node->winfnoid);

  _fingerprintIntField(ctx, "winref", node->winref);

  _fingerprintBoolField(ctx, "winstar", node->winstar);

  _fingerprintIntField(ctx, "wintype", node->wintype);

}

static void
_fingerprintWindowFuncRunCondition(FingerprintContext *ctx, const WindowFuncRunCondition *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->arg != NULL)
    _fingerprintChildNode(ctx, node->arg, node, "arg", depth);

  _fingerprintIntField(ctx, "inputcollid", node->inputcollid);

  _fingerprintIntField(ctx, "opno", node->opno);

  _fingerprintBoolField(ctx, "wfunc_left", node->wfunc_left);

}

static void
_fingerprintMergeSupportFunc(FingerprintContext *ctx, const MergeSupportFunc *node, const void *parent, const char *field_name, unsigned int depth)
{
  // Intentionally ignoring node->location for fingerprinting

  _fingerprintIntField(ctx, "msfcollid", node->msfcollid);

  _fingerprintIntField(ctx, "msftype", node->msftype);

}

static void
_fingerprintSubscriptingRef(FingerprintContext *ctx, const SubscriptingRef *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->refassgnexpr != NULL)
    _fingerprintChildNode(ctx, node->refassgnexpr, node, "refassgnexpr", depth);

  _fingerprintIntField(ctx, "refcollid", node->refcollid);

  _fingerprintIntField(ctx, "refcontainertype", node->refcontainertype);

  _fingerprintIntField(ctx, "refelemtype", node->refelemtype);

  if (node->refexpr != NULL)
    _fingerprintChildNode(ctx, node->refexpr, node, "refexpr", depth);

  if (node->reflowerindexpr != NULL && node->reflowerindexpr->length > 0)
    _fingerprintChildList(ctx, node->reflowerindexpr, node, "reflowerindexpr", depth);

  _fingerprintIntField(ctx, "refrestype", node->refrestype);

  _fingerprintIntField(ctx, "reftypmod", node->reftypmod);

  if (node->refupperindexpr != NULL && node->refupperindexpr->length > 0)
    _fingerprintChildList(ctx, node->refupperindexpr, node, "refupperindexpr", depth);

}

static void
_fingerprintFuncExpr(FingerprintContext *ctx, const FuncExpr *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->args != NULL && node->args->length > 0)
    _fingerprintChildList(ctx, node->args, node, "args", depth);

  _fingerprintIntField(ctx, "funccollid", node->funccollid);

  _fingerprintEnumField(ctx, "funcformat", _enumToStringCoercionForm(node->funcformat));

  _fingerprintIntField(ctx, "funcid", node->funcid);

  _fingerprintIntField(ctx, "funcresulttype", node->funcresulttype);

  _fingerprintBoolField(ctx, "funcretset", node->funcretset);

  _fingerprintBoolField(ctx, "funcvariadic", node->funcvariadic);

  _fingerprintIntField(ctx, "inputcollid", node->inputcollid);

  // Intentionally ignoring node->location for fingerprinting

}

static void
_fingerprintNamedArgExpr(FingerprintContext *ctx, const NamedArgExpr *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->arg != NULL)
    _fingerprintChildNode(ctx, node->arg, node, "arg", depth);

  _fingerprintIntField(ctx, "argnumber", node->argnumber);

  // Intentionally ignoring node->location for fingerprinting

  _fingerprintStringField(ctx, "name", node->name);

}

static void
_fingerprintOpExpr(FingerprintContext *ctx, const OpExpr *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->args != NULL && node->args->length > 0)
    _fingerprintChildList(ctx, node->args, node, "args", depth);

  _fingerprintIntField(ctx, "inputcollid", node->inputcollid);

  // Intentionally ignoring node->location for fingerprinting

  _fingerprintIntField(ctx, "opcollid", node->opcollid);

  _fingerprintIntField(ctx, "opno", node->opno);

  _fingerprintIntField(ctx, "opresulttype", node->opresulttype);

  _fingerprintBoolField(ctx, "opretset", node->opretset);

}

static void
_fingerprintScalarArrayOpExpr(FingerprintContext *ctx, const ScalarArrayOpExpr *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->args != NULL && node->args->length > 0)
    _fingerprintChildList(ctx, node->args, node, "args", depth);

  _fingerprintIntField(ctx, "inputcollid", node->inputcollid);

  // Intentionally ignoring node->location for fingerprinting

  _fingerprintIntField(ctx, "opno", node->opno);

  _fingerprintBoolField(ctx, "useOr", node->useOr);

}

static void
_fingerprintBoolExpr(FingerprintContext *ctx, const BoolExpr *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->args != NULL && node->args->length > 0)
    _fingerprintChildList(ctx, node->args, node, "args", depth);

  _fingerprintEnumField(ctx, "boolop", _enumToStringBoolExprType(node->boolop));

  // Intentionally ignoring node->location for fingerprinting

}

static void
_fingerprintSubLink(FingerprintContext *ctx, const SubLink *node, const void *parent, const char *field_name, unsigned int depth)
{
  // Intentionally ignoring node->location for fingerprinting

  if (node->operName != NULL && node->operName->length > 0)
    _fingerprintChildList(ctx, node->operName, node, "operName", depth);

  _fingerprintIntField(ctx, "subLinkId", node->subLinkId);

  _fingerprintEnumField(ctx, "subLinkType", _enumToStringSubLinkType(node->subLinkType));

  if (node->subselect != NULL)
    _fingerprintChildNode(ctx, node->subselect, node, "subselect", depth);

  if (node->testexpr != NULL)
    _fingerprintChildNode(ctx, node->testexpr, node, "testexpr", depth);

}

static void
_fingerprintSubPlan(FingerprintContext *ctx, const SubPlan *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->args != NULL && node->args->length > 0)
    _fingerprintChildList(ctx, node->args, node, "args", depth);

  _fingerprintIntField(ctx, "firstColCollation", node->firstColCollation);

  _fingerprintIntField(ctx, "firstColType", node->firstColType);

  _fingerprintIntField(ctx, "firstColTypmod", node->firstColTypmod);

  if (node->parParam != NULL && node->parParam->length > 0)
    _fingerprintChildList(ctx, node->parParam, node, "parParam", depth);

  _fingerprintBoolField(ctx, "parallel_safe", node->parallel_safe);

  if (node->paramIds != NULL && node->paramIds->length > 0)
    _fingerprintChildList(ctx, node->paramIds, node, "paramIds", depth);

  _fingerprintFloatField(ctx, "per_call_cost", node->per_call_cost);

  _fingerprintIntField(ctx, "plan_id", node->plan_id);

  _fingerprintStringField(ctx, "plan_name", node->plan_name);

  if (node->setParam != NULL && node->setParam->length > 0)
    _fingerprintChildList(ctx, node->setParam, node, "setParam", depth);

  _fingerprintFloatField(ctx, "startup_cost", node->startup_cost);

  _fingerprintEnumField(ctx, "subLinkType", _enumToStringSubLinkType(node->subLinkType));

  if (node->testexpr != NULL)
    _fingerprintChildNode(ctx, node->testexpr, node, "testexpr", depth);

  _fingerprintBoolField(ctx, "unknownEqFalse", node->unknownEqFalse);

  _fingerprintBoolField(ctx, "useHashTable", node->useHashTable);

}

static void
_fingerprintAlternativeSubPlan(FingerprintContext *ctx, const AlternativeSubPlan *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->subplans != NULL && node->subplans->length > 0)
    _fingerprintChildList(ctx, node->subplans, node, "subplans", depth);

}

static void
_fingerprintFieldSelect(FingerprintContext *ctx, const FieldSelect *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->arg != NULL)
    _fingerprintChildNode(ctx, node->arg, node, "arg", depth);

  _fingerprintIntField(ctx, "fieldnum", node->fieldnum);

  _fingerprintIntField(ctx, "resultcollid", node->resultcollid);

  _fingerprintIntField(ctx, "resulttype", node->resulttype);

  _fingerprintIntField(ctx, "resulttypmod", node->resulttypmod);

}

static void
_fingerprintFieldStore(FingerprintContext *ctx, const FieldStore *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->arg != NULL)
    _fingerprintChildNode(ctx, node->arg, node, "arg", depth);

  if (node->fieldnums != NULL && node->fieldnums->length > 0)
    _fingerprintChildList(ctx, node->fieldnums, node, "fieldnums", depth);

  if (node->newvals != NULL && node->newvals->length > 0)
    _fingerprintChildList(ctx, node->newvals, node, "newvals", depth);

  _fingerprintIntField(ctx, "resulttype", node->resulttype);

}

static void
_fingerprintRelabelType(FingerprintContext *ctx, const RelabelType *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->arg != NULL)
    _fingerprintChildNode(ctx, node->arg, node, "arg", depth);

  // Intentionally ignoring node->location for fingerprinting

  _fingerprintEnumField(ctx, "relabelformat", _enumToStringCoercionForm(node->relabelformat));

  _fingerprintIntField(ctx, "resultcollid", node->resultcollid);

  _fingerprintIntField(ctx, "resulttype", node->resulttype);

  _fingerprintIntField(ctx, "resulttypmod", node->resulttypmod);

}

static void
_fingerprintCoerceViaIO(FingerprintContext *ctx, const CoerceViaIO *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->arg != NULL)
    _fingerprintChildNode(ctx, node->arg, node, "arg", depth);

  _fingerprintEnumField(ctx, "coerceformat", _enumToStringCoercionForm(node->coerceformat));

  // Intentionally ignoring node->location for fingerprinting

  _fingerprintIntField(ctx, "resultcollid", node->resultcollid);

  _fingerprintIntField(ctx, "resulttype", node->resulttype);

}

static void
_fingerprintArrayCoerceExpr(FingerprintContext *ctx, const ArrayCoerceExpr *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->arg != NULL)
    _fingerprintChildNode(ctx, node->arg, node, "arg", depth);

  _fingerprintEnumField(ctx, "coerceformat", _enumToStringCoercionForm(node->coerceformat));

  if (node->elemexpr != NULL)
    _fingerprintChildNode(ctx, node->elemexpr, node, "elemexpr", depth);

  // Intentionally ignoring node->location for fingerprinting

  _fingerprintIntField(ctx, "resultcollid", node->resultcollid);

  _fingerprintIntField(ctx, "resulttype", node->resulttype);

  _fingerprintIntField(ctx, "resulttypmod", node->resulttypmod);

}

static void
_fingerprintConvertRowtypeExpr(FingerprintContext *ctx, const ConvertRowtypeExpr *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->arg != NULL)
    _fingerprintChildNode(ctx, node->arg, node, "arg", depth);

  _fingerprintEnumField(ctx, "convertformat", _enumToStringCoercionForm(node->convertformat));

  // Intentionally ignoring node->location for fingerprinting

  _fingerprintIntField(ctx, "resulttype", node->resulttype);

}

static void
_fingerprintCollateExpr(FingerprintContext *ctx, const CollateExpr *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->arg != NULL)
    _fingerprintChildNode(ctx, node->arg, node, "arg", depth);

  _fingerprintIntField(ctx, "collOid", node->collOid);

  // Intentionally ignoring node->location for fingerprinting

}

static void
_fingerprintCaseExpr(FingerprintContext *ctx, const CaseExpr *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->arg != NULL)
    _fingerprintChildNode(ctx, node->arg, node, "arg", depth);

  if (node->args != NULL && node->args->length > 0)
    _fingerprintChildList(ctx, node->args, node, "args", depth);

  _fingerprintIntField(ctx, "casecollid", node->casecollid);

  _fingerprintIntField(ctx, "casetype", node->casetype);

  if (node->defresult != NULL)
    _fingerprintChildNode(ctx, node->defresult, node, "defresult", depth);

  // Intentionally ignoring node->location for fingerprinting

}

static void
_fingerprintCaseWhen(FingerprintContext *ctx, const CaseWhen *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->expr != NULL)
    _fingerprintChildNode(ctx, node->expr, node, "expr", depth);

  // Intentionally ignoring node->location for fingerprinting

  if (node->result != NULL)
    _fingerprintChildNode(ctx, node->result, node, "result", depth);

}

static void
_fingerprintCaseTestExpr(FingerprintContext *ctx, const CaseTestExpr *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintIntField(ctx, "collation", node->collation);

  _fingerprintIntField(ctx, "typeId", node->typeId);

  _fingerprintIntField(ctx, "typeMod", node->typeMod);

}

static void
_fingerprintArrayExpr(FingerprintContext *ctx, const ArrayExpr *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintIntField(ctx, "array_collid", node->array_collid);

  _fingerprintIntField(ctx, "array_typeid", node->array_typeid);

  _fingerprintIntField(ctx, "element_typeid", node->element_typeid);

  if (node->elements != NULL && node->elements->length > 0)
    _fingerprintChildList(ctx, node->elements, node, "elements", depth);

  // Intentionally ignoring node->list_end for fingerprinting

  // Intentionally ignoring node->list_start for fingerprinting

  // Intentionally ignoring node->location for fingerprinting

  _fingerprintBoolField(ctx, "multidims", node->multidims);

}

static void
_fingerprintRowExpr(FingerprintContext *ctx, const RowExpr *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->args != NULL && node->args->length > 0)
    _fingerprintChildList(ctx, node->args, node, "args", depth);

  if (node->colnames != NULL && node->colnames->length > 0)
    _fingerprintChildList(ctx, node->colnames, node, "colnames", depth);

  // Intentionally ignoring node->location for fingerprinting

  _fingerprintEnumField(ctx, "row_format", _enumToStringCoercionForm(node->row_format));

  _fingerprintIntField(ctx, "row_typeid", node->row_typeid);

}

static void
_fingerprintRowCompareExpr(FingerprintContext *ctx, const RowCompareExpr *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintEnumField(ctx, "cmptype", _enumToStringCompareType(node->cmptype));

  if (node->inputcollids != NULL && node->inputcollids->length > 0)
    _fingerprintChildList(ctx, node->inputcollids, node, "inputcollids", depth);

  if (node->largs != NULL && node->largs->length > 0)
    _fingerprintChildList(ctx, node->largs, node, "largs", depth);

  if (node->opfamilies != NULL && node->opfamilies->length > 0)
    _fingerprintChildList(ctx, node->opfamilies, node, "opfamilies", depth);

  if (node->opnos != NULL && node->opnos->length > 0)
    _fingerprintChildList(ctx, node->opnos, node, "opnos", depth);

  if (node->rargs != NULL && node->rargs->length > 0)
    _fingerprintChildList(ctx, node->rargs, node, "rargs", depth);

}

static void
_fingerprintCoalesceExpr(FingerprintContext *ctx, const CoalesceExpr *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->args != NULL && node->args->length > 0)
    _fingerprintChildList(ctx, node->args, node, "args", depth);

  _fingerprintIntField(ctx, "coalescecollid", node->coalescecollid);

  _fingerprintIntField(ctx, "coalescetype", node->coalescetype);

  // Intentionally ignoring node->location for fingerprinting

}

static void
_fingerprintMinMaxExpr(FingerprintContext *ctx, const MinMaxExpr *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->args != NULL && node->args->length > 0)
    _fingerprintChildList(ctx, node->args, node, "args", depth);

  _fingerprintIntField(ctx, "inputcollid", node->inputcollid);

  // Intentionally ignoring node->location for fingerprinting

  _fingerprintIntField(ctx, "minmaxcollid", node->minmaxcollid);

  _fingerprintIntField(ctx, "minmaxtype", node->minmaxtype);

  _fingerprintEnumField(ctx, "op", _enumToStringMinMaxOp(node->op));

}

static void
_fingerprintSQLValueFunction(FingerprintContext *ctx, const SQLValueFunction *node, const void *parent, const char *field_name, unsigned int depth)
{
  // Intentionally ignoring node->location for fingerprinting

  _fingerprintEnumField(ctx, "op", _enumToStringSQLValueFunctionOp(node->op));

  _fingerprintIntField(ctx, "type", node->type);

  _fingerprintIntField(ctx, "typmod", node->typmod);

}

static void
_fingerprintXmlExpr(FingerprintContext *ctx, const XmlExpr *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->arg_names != NULL && node->arg_names->length > 0)
    _fingerprintChildList(ctx, node->arg_names, node, "arg_names", depth);

  if (node->args != NULL && node->args->length > 0)
    _fingerprintChildList(ctx, node->args, node, "args", depth);

  _fingerprintBoolField(ctx, "indent", node->indent);

  // Intentionally ignoring node->location for fingerprinting

  _fingerprintStringField(ctx, "name", node->name);

  if (node->named_args != NULL && node->named_args->length > 0)
    _fingerprintChildList(ctx, node->named_args, node, "named_args", depth);

  _fingerprintEnumField(ctx, "op", _enumToStringXmlExprOp(node->op));

  _fingerprintIntField(ctx, "type", node->type);

  _fingerprintIntField(ctx, "typmod", node->typmod);

  _fingerprintEnumField(ctx, "xmloption", _enumToStringXmlOptionType(node->xmloption));

}

static void
_fingerprintJsonFormat(FingerprintContext *ctx, const JsonFormat *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintEnumField(ctx, "encoding", _enumToStringJsonEncoding(node->encoding));

  _fingerprintEnumField(ctx, "format_type", _enumToStringJsonFormatType(node->format_type));

  // Intentionally ignoring node->location for fingerprinting

}

static void
_fingerprintJsonReturning(FingerprintContext *ctx, const JsonReturning *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->format != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "format");
    _fingerprintJsonFormat(ctx, node->format, node, "format", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  _fingerprintIntField(ctx, "typid", node->typid);

  _fingerprintIntField(ctx, "typmod", node->typmod);

}

static void
_fingerprintJsonValueExpr(FingerprintContext *ctx, const JsonValueExpr *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->format != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "format");
    _fingerprintJsonFormat(ctx, node->format, node, "format", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  if (node->formatted_expr != NULL)
    _fingerprintChildNode(ctx, node->formatted_expr, node, "formatted_expr", depth);

  if (node->raw_expr != NULL)
    _fingerprintChildNode(ctx, node->raw_expr, node, "raw_expr", depth);

}

static void
_fingerprintJsonConstructorExpr(FingerprintContext *ctx, const JsonConstructorExpr *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintBoolField(ctx, "absent_on_null", node->absent_on_null);

  if (node->args != NULL && node->args->length > 0)
    _fingerprintChildList(ctx, node->args, node, "args", depth);

  if (node->coercion != NULL)
    _fingerprintChildNode(ctx, node->coercion, node, "coercion", depth);

  if (node->func != NULL)
    _fingerprintChildNode(ctx, node->func, node, "func", depth);

  // Intentionally ignoring node->location for fingerprinting

  if (node->returning != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "returning");
    _fingerprintJsonReturning(ctx, node->returning, node, "returning", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  _fingerprintEnumField(ctx, "type", _enumToStringJsonConstructorType(node->type));

  _fingerprintBoolField(ctx, "unique", node->unique);

}

static void
_fingerprintJsonIsPredicate(FingerprintContext *ctx, const JsonIsPredicate *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->expr != NULL)
    _fingerprintChildNode(ctx, node->expr, node, "expr", depth);

  if (node->format != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "format");
    _fingerprintJsonFormat(ctx, node->format, node, "format", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  _fingerprintEnumField(ctx, "item_type", _enumToStringJsonValueType(node->item_type));

  // Intentionally ignoring node->location for fingerprinting

  _fingerprintBoolField(ctx, "unique_keys", node->unique_keys);

}

static void
_fingerprintJsonBehavior(FingerprintContext *ctx, const JsonBehavior *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintEnumField(ctx, "btype", _enumToStringJsonBehaviorType(node->btype));

  _fingerprintBoolField(ctx, "coerce", node->coerce);

  if (node->expr != NULL)
    _fingerprintChildNode(ctx, node->expr, node, "expr", depth);

  // Intentionally ignoring node->location for fingerprinting

}

static void
_fingerprintJsonExpr(FingerprintContext *ctx, const JsonExpr *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintIntField(ctx, "collation", node->collation);

  _fingerprintStringField(ctx, "column_name", node->column_name);

  if (node->format != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "format");
    _fingerprintJsonFormat(ctx, node->format, node, "format", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  if (node->formatted_expr != NULL)
    _fingerprintChildNode(ctx, node->formatted_expr, node, "formatted_expr", depth);

  // Intentionally ignoring node->location for fingerprinting

  _fingerprintBoolField(ctx, "omit_quotes", node->omit_quotes);

  if (node->on_empty != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "on_empty");
    _fingerprintJsonBehavior(ctx, node->on_empty, node, "on_empty", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  if (node->on_error != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "on_error");
    _fingerprintJsonBehavior(ctx, node->on_error, node, "on_error", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  _fingerprintEnumField(ctx, "op", _enumToStringJsonExprOp(node->op));

  if (node->passing_names != NULL && node->passing_names->length > 0)
    _fingerprintChildList(ctx, node->passing_names, node, "passing_names", depth);

  if (node->passing_values != NULL && node->passing_values->length > 0)
    _fingerprintChildList(ctx, node->passing_values, node, "passing_values", depth);

  if (node->path_spec != NULL)
    _fingerprintChildNode(ctx, node->path_spec, node, "path_spec", depth);

  if (node->returning != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "returning");
    _fingerprintJsonReturning(ctx, node->returning, node, "returning", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  _fingerprintBoolField(ctx, "use_io_coercion", node->use_io_coercion);

  _fingerprintBoolField(ctx, "use_json_coercion", node->use_json_coercion);

  _fingerprintEnumField(ctx, "wrapper", _enumToStringJsonWrapper(node->wrapper));

}

static void
_fingerprintJsonTablePath(FingerprintContext *ctx, const JsonTablePath *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintStringField(ctx, "name", node->name);

  // Intentionally ignoring node->value for fingerprinting

}

static void
_fingerprintJsonTablePathScan(FingerprintContext *ctx, const JsonTablePathScan *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->child != NULL)
    _fingerprintChildNode(ctx, node->child, node, "child", depth);

  _fingerprintIntField(ctx, "colMax", node->colMax);

  _fingerprintIntField(ctx, "colMin", node->colMin);

  _fingerprintBoolField(ctx, "errorOnError", node->errorOnError);

  if (node->path != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "path");
    _fingerprintJsonTablePath(ctx, node->path, node, "path", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  _fingerprintChildNode(ctx, &node->plan, node, "plan", depth);

}

static void
_fingerprintJsonTableSiblingJoin(FingerprintContext *ctx, const JsonTableSiblingJoin *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->lplan != NULL)
    _fingerprintChildNode(ctx, node->lplan, node, "lplan", depth);

  _fingerprintChildNode(ctx, &node->plan, node, "plan", depth);

  if (node->rplan != NULL)
    _fingerprintChildNode(ctx, node->rplan, node, "rplan", depth);

}

static void
_fingerprintNullTest(FingerprintContext *ctx, const NullTest *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->arg != NULL)
    _fingerprintChildNode(ctx, node->arg, node, "arg", depth);

  _fingerprintBoolField(ctx, "argisrow", node->argisrow);

  // Intentionally ignoring node->location for fingerprinting

  _fingerprintEnumField(ctx, "nulltesttype", _enumToStringNullTestType(node->nulltesttype));

}

static void
_fingerprintBooleanTest(FingerprintContext *ctx, const BooleanTest *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->arg != NULL)
    _fingerprintChildNode(ctx, node->arg, node, "arg", depth);

  _fingerprintEnumField(ctx, "booltesttype", _enumToStringBoolTestType(node->booltesttype));

  // Intentionally ignoring node->location for fingerprinting

}

static void
_fingerprintMergeAction(FingerprintContext *ctx, const MergeAction *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintEnumField(ctx, "commandType", _enumToStringCmdType(node->commandType));

  _fingerprintEnumField(ctx, "matchKind", _enumToStringMergeMatchKind(node->matchKind));

  _fingerprintEnumField(ctx, "override", _enumToStringOverridingKind(node->override));

  if (node->qual != NULL)
    _fingerprintChildNode(ctx, node->qual, node, "qual", depth);

  if (node->targetList != NULL && node->targetList->length > 0)
    _fingerprintChildList(ctx, node->targetList, node, "targetList", depth);

  if (node->updateColnos != NULL && node->updateColnos->length > 0)
    _fingerprintChildList(ctx, node->updateColnos, node, "updateColnos", depth);

}

static void
_fingerprintCoerceToDomain(FingerprintContext *ctx, const CoerceToDomain *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->arg != NULL)
    _fingerprintChildNode(ctx, node->arg, node, "arg", depth);

  _fingerprintEnumField(ctx, "coercionformat", _enumToStringCoercionForm(node->coercionformat));

  // Intentionally ignoring node->location for fingerprinting

  _fingerprintIntField(ctx, "resultcollid", node->resultcollid);

  _fingerprintIntField(ctx, "resulttype", node->resulttype);

  _fingerprintIntField(ctx, "resulttypmod", node->resulttypmod);

}

static void
_fingerprintCoerceToDomainValue(FingerprintContext *ctx, const CoerceToDomainValue *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintIntField(ctx, "collation", node->collation);

  // Intentionally ignoring node->location for fingerprinting

  _fingerprintIntField(ctx, "typeId", node->typeId);

  _fingerprintIntField(ctx, "typeMod", node->typeMod);

}

static void
_fingerprintSetToDefault(FingerprintContext *ctx, const SetToDefault *node, const void *parent, const char *field_name, unsigned int depth)
{
  // Intentionally ignoring all fields for fingerprinting
}

static void
_fingerprintCurrentOfExpr(FingerprintContext *ctx, const CurrentOfExpr *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintStringField(ctx, "cursor_name", node->cursor_name);

  _fingerprintIntField(ctx, "cursor_param", node->cursor_param);

  _fingerprintIntField(ctx, "cvarno", node->cvarno);

}

static void
_fingerprintNextValueExpr(FingerprintContext *ctx, const NextValueExpr *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintIntField(ctx, "seqid", node->seqid);

  _fingerprintIntField(ctx, "typeId", node->typeId);

}

static void
_fingerprintInferenceElem(FingerprintContext *ctx, const InferenceElem *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->expr != NULL)
    _fingerprintChildNode(ctx, node->expr, node, "expr", depth);

  _fingerprintIntField(ctx, "infercollid", node->infercollid);

  _fingerprintIntField(ctx, "inferopclass", node->inferopclass);

}

static void
_fingerprintReturningExpr(FingerprintContext *ctx, const ReturningExpr *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->retexpr != NULL)
    _fingerprintChildNode(ctx, node->retexpr, node, "retexpr", depth);

  _fingerprintIntField(ctx, "retlevelsup", node->retlevelsup);

  _fingerprintBoolField(ctx, "retold", node->retold);

}

static void
_fingerprintTargetEntry(FingerprintContext *ctx, const TargetEntry *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->expr != NULL)
    _fingerprintChildNode(ctx, node->expr, node, "expr", depth);

  _fingerprintBoolField(ctx, "resjunk", node->resjunk);

  _fingerprintStringField(ctx, "resname", node->resname);

  _fingerprintIntField(ctx, "resno", node->resno);

  _fingerprintIntField(ctx, "resorigcol", node->resorigcol);

  _fingerprintIntField(ctx, "resorigtbl", node->resorigtbl);

  _fingerprintIntField(ctx, "ressortgroupref", node->ressortgroupref);

}

static void
_fingerprintRangeTblRef(FingerprintContext *ctx, const RangeTblRef *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintIntField(ctx, "rtindex", node->rtindex);

}

static void
_fingerprintJoinExpr(FingerprintContext *ctx, const JoinExpr *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->alias != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "alias");
    _fingerprintAlias(ctx, node->alias, node, "alias", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  _fingerprintBoolField(ctx, "isNatural", node->isNatural);

  if (node->join_using_alias != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "join_using_alias");
    _fingerprintAlias(ctx, node->join_using_alias, node, "join_using_alias", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  _fingerprintEnumField(ctx, "jointype", _enumToStringJoinType(node->jointype));

  if (node->larg != NULL)
    _fingerprintChildNode(ctx, node->larg, node, "larg", depth);

  if (node->quals != NULL)
    _fingerprintChildNode(ctx, node->quals, node, "quals", depth);

  if (node->rarg != NULL)
    _fingerprintChildNode(ctx, node->rarg, node, "rarg", depth);

  _fingerprintIntField(ctx, "rtindex", node->rtindex);

  if (node->usingClause != NULL && node->usingClause->length > 0)
    _fingerprintChildList(ctx, node->usingClause, node, "usingClause", depth);

}

static void
_fingerprintFromExpr(FingerprintContext *ctx, const FromExpr *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->fromlist != NULL && node->fromlist->length > 0)
    _fingerprintChildList(ctx, node->fromlist, node, "fromlist", depth);

  if (node->quals != NULL)
    _fingerprintChildNode(ctx, node->quals, node, "quals", depth);

}

static void
_fingerprintOnConflictExpr(FingerprintContext *ctx, const OnConflictExpr *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintEnumField(ctx, "action", _enumToStringOnConflictAction(node->action));

  if (node->arbiterElems != NULL && node->arbiterElems->length > 0)
    _fingerprintChildList(ctx, node->arbiterElems, node, "arbiterElems", depth);

  if (node->arbiterWhere != NULL)
    _fingerprintChildNode(ctx, node->arbiterWhere, node, "arbiterWhere", depth);

  _fingerprintIntField(ctx, "constraint", node->constraint);

  _fingerprintIntField(ctx, "exclRelIndex", node->exclRelIndex);

  if (node->exclRelTlist != NULL && node->exclRelTlist->length > 0)
    _fingerprintChildList(ctx, node->exclRelTlist, node, "exclRelTlist", depth);

  if (node->onConflictSet != NULL && node->onConflictSet->length > 0)
    _fingerprintChildList(ctx, node->onConflictSet, node, "onConflictSet", depth);

  if (node->onConflictWhere != NULL)
    _fingerprintChildNode(ctx, node->onConflictWhere, node, "onConflictWhere", depth);

}

static void
_fingerprintQuery(FingerprintContext *ctx, const Query *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintBoolField(ctx, "canSetTag", node->canSetTag);

  _fingerprintEnumField(ctx, "commandType", _enumToStringCmdType(node->commandType));

  if (node->constraintDeps != NULL && node->constraintDeps->length > 0)
    _fingerprintChildList(ctx, node->constraintDeps, node, "constraintDeps", depth);

  if (node->cteList != NULL && node->cteList->length > 0)
    _fingerprintChildList(ctx, node->cteList, node, "cteList", depth);

  if (node->distinctClause != NULL && node->distinctClause->length > 0)
    _fingerprintChildList(ctx, node->distinctClause, node, "distinctClause", depth);

  if (node->groupClause != NULL && node->groupClause->length > 0)
    _fingerprintChildList(ctx, node->groupClause, node, "groupClause", depth);

  _fingerprintBoolField(ctx, "groupDistinct", node->groupDistinct);

  if (node->groupingSets != NULL && node->groupingSets->length > 0)
    _fingerprintChildList(ctx, node->groupingSets, node, "groupingSets", depth);

  _fingerprintBoolField(ctx, "hasAggs", node->hasAggs);

  _fingerprintBoolField(ctx, "hasDistinctOn", node->hasDistinctOn);

  _fingerprintBoolField(ctx, "hasForUpdate", node->hasForUpdate);

  _fingerprintBoolField(ctx, "hasGroupRTE", node->hasGroupRTE);

  _fingerprintBoolField(ctx, "hasModifyingCTE", node->hasModifyingCTE);

  _fingerprintBoolField(ctx, "hasRecursive", node->hasRecursive);

  _fingerprintBoolField(ctx, "hasRowSecurity", node->hasRowSecurity);

  _fingerprintBoolField(ctx, "hasSubLinks", node->hasSubLinks);

  _fingerprintBoolField(ctx, "hasTargetSRFs", node->hasTargetSRFs);

  _fingerprintBoolField(ctx, "hasWindowFuncs", node->hasWindowFuncs);

  if (node->havingQual != NULL)
    _fingerprintChildNode(ctx, node->havingQual, node, "havingQual", depth);

  _fingerprintBoolField(ctx, "isReturn", node->isReturn);

  if (node->jointree != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "jointree");
    _fingerprintFromExpr(ctx, node->jointree, node, "jointree", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  if (node->limitCount != NULL)
    _fingerprintChildNode(ctx, node->limitCount, node, "limitCount", depth);

  if (node->limitOffset != NULL)
    _fingerprintChildNode(ctx, node->limitOffset, node, "limitOffset", depth);

  _fingerprintEnumField(ctx, "limitOption", _enumToStringLimitOption(node->limitOption));

  if (node->mergeActionList != NULL && node->mergeActionList->length > 0)
    _fingerprintChildList(ctx, node->mergeActionList, node, "mergeActionList", depth);

  if (node->mergeJoinCondition != NULL)
    _fingerprintChildNode(ctx, node->mergeJoinCondition, node, "mergeJoinCondition", depth);

  _fingerprintIntField(ctx, "mergeTargetRelation", node->mergeTargetRelation);

  if (node->onConflict != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "onConflict");
    _fingerprintOnConflictExpr(ctx, node->onConflict, node, "onConflict", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  _fingerprintEnumField(ctx, "override", _enumToStringOverridingKind(node->override));

  _fingerprintEnumField(ctx, "querySource", _enumToStringQuerySource(node->querySource));

  _fingerprintIntField(ctx, "resultRelation", node->resultRelation);

  if (node->returningList != NULL && node->returningList->length > 0)
    _fingerprintChildList(ctx, node->returningList, node, "returningList", depth);

  _fingerprintStringField(ctx, "returningNewAlias", node->returningNewAlias);

  _fingerprintStringField(ctx, "returningOldAlias", node->returningOldAlias);

  if (node->rowMarks != NULL && node->rowMarks->length > 0)
    _fingerprintChildList(ctx, node->rowMarks, node, "rowMarks", depth);

  if (node->rtable != NULL && node->rtable->length > 0)
    _fingerprintChildList(ctx, node->rtable, node, "rtable", depth);

  if (node->rteperminfos != NULL && node->rteperminfos->length > 0)
    _fingerprintChildList(ctx, node->rteperminfos, node, "rteperminfos", depth);

  if (node->setOperations != NULL)
    _fingerprintChildNode(ctx, node->setOperations, node, "setOperations", depth);

  if (node->sortClause != NULL && node->sortClause->length > 0)
    _fingerprintChildList(ctx, node->sortClause, node, "sortClause", depth);

  _fingerprintIntField(ctx, "stmt_len", node->stmt_len);

  _fingerprintIntField(ctx, "stmt_location", node->stmt_location);

  if (node->targetList != NULL && node->targetList->length > 0)
    _fingerprintChildList(ctx, node->targetList, node, "targetList", depth);

  if (node->utilityStmt != NULL)
    _fingerprintChildNode(ctx, node->utilityStmt, node, "utilityStmt", depth);

  if (node->windowClause != NULL && node->windowClause->length > 0)
    _fingerprintChildList(ctx, node->windowClause, node, "windowClause", depth);

  if (node->withCheckOptions != NULL && node->withCheckOptions->length > 0)
    _fingerprintChildList(ctx, node->withCheckOptions, node, "withCheckOptions", depth);

}

static void
_fingerprintTypeName(FingerprintContext *ctx, const TypeName *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->arrayBounds != NULL && node->arrayBounds->length > 0)
    _fingerprintChildList(ctx, node->arrayBounds, node, "arrayBounds", depth);

  // Intentionally ignoring node->location for fingerprinting

  if (node->names != NULL && node->names->length > 0)
    _fingerprintChildList(ctx, node->names, node, "names", depth);

  _fingerprintBoolField(ctx, "pct_type", node->pct_type);

  _fingerprintBoolField(ctx, "setof", node->setof);

  _fingerprintIntField(ctx, "typeOid", node->typeOid);

  _fingerprintIntField(ctx, "typemod", node->typemod);

  if (node->typmods != NULL && node->typmods->length > 0)
    _fingerprintChildList(ctx, node->typmods, node, "typmods", depth);

}

static void
_fingerprintColumnRef(FingerprintContext *ctx, const ColumnRef *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->fields != NULL && node->fields->length > 0)
    _fingerprintChildList(ctx, node->fields, node, "fields", depth);

  // Intentionally ignoring node->location for fingerprinting

}

static void
_fingerprintParamRef(FingerprintContext *ctx, const ParamRef *node, const void *parent, const char *field_name, unsigned int depth)
{
  // Intentionally ignoring all fields for fingerprinting
}

static void
_fingerprintA_Expr(FingerprintContext *ctx, const A_Expr *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (true) {
    _fingerprintString(ctx, "kind");
    if (node->kind == AEXPR_OP_ANY || node->kind == AEXPR_IN)
      _fingerprintString(ctx, "AEXPR_OP");
    else
      _fingerprintString(ctx, _enumToStringA_Expr_Kind(node->kind));
  }

  if (node->lexpr != NULL)
    _fingerprintChildNode(ctx, node->lexpr, node, "lexpr", depth);

  // Intentionally ignoring node->location for fingerprinting

  if (node->name != NULL && node->name->length > 0)
    _fingerprintChildList(ctx, node->name, node, "name", depth);

  if (node->rexpr != NULL)
    _fingerprintChildNode(ctx, node->rexpr, node, "rexpr", depth);

  // Intentionally ignoring node->rexpr_list_end for fingerprinting

  // Intentionally ignoring node->rexpr_list_start for fingerprinting

}

static void
_fingerprintTypeCast(FingerprintContext *ctx, const TypeCast *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->arg != NULL)
    _fingerprintChildNode(ctx, node->arg, node, "arg", depth);

  // Intentionally ignoring node->location for fingerprinting

  if (node->typeName != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "typeName");
    _fingerprintTypeName(ctx, node->typeName, node, "typeName", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

}

static void
_fingerprintCollateClause(FingerprintContext *ctx, const CollateClause *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->arg != NULL)
    _fingerprintChildNode(ctx, node->arg, node, "arg", depth);

  if (node->collname != NULL && node->collname->length > 0)
    _fingerprintChildList(ctx, node->collname, node, "collname", depth);

  // Intentionally ignoring node->location for fingerprinting

}

static void
_fingerprintRoleSpec(FingerprintContext *ctx, const RoleSpec *node, const void *parent, const char *field_name, unsigned int depth)
{
  // Intentionally ignoring node->location for fingerprinting

  _fingerprintStringField(ctx, "rolename", node->rolename);

  _fingerprintEnumField(ctx, "roletype", _enumToStringRoleSpecType(node->roletype));

}

static void
_fingerprintFuncCall(FingerprintContext *ctx, const FuncCall *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintBoolField(ctx, "agg_distinct", node->agg_distinct);

  if (node->agg_filter != NULL)
    _fingerprintChildNode(ctx, node->agg_filter, node, "agg_filter", depth);

  if (node->agg_order != NULL && node->agg_order->length > 0)
    _fingerprintChildList(ctx, node->agg_order, node, "agg_order", depth);

  _fingerprintBoolField(ctx, "agg_star", node->agg_star);

  _fingerprintBoolField(ctx, "agg_within_group", node->agg_within_group);

  if (node->args != NULL && node->args->length > 0)
    _fingerprintChildList(ctx, node->args, node, "args", depth);

  _fingerprintBoolField(ctx, "func_variadic", node->func_variadic);

  _fingerprintEnumField(ctx, "funcformat", _enumToStringCoercionForm(node->funcformat));

  if (node->funcname != NULL && node->funcname->length > 0)
    _fingerprintChildList(ctx, node->funcname, node, "funcname", depth);

  // Intentionally ignoring node->location for fingerprinting

  if (node->over != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "over");
    _fingerprintWindowDef(ctx, node->over, node, "over", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

}

static void
_fingerprintA_Star(FingerprintContext *ctx, const A_Star *node, const void *parent, const char *field_name, unsigned int depth)
{
}

static void
_fingerprintA_Indices(FingerprintContext *ctx, const A_Indices *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintBoolField(ctx, "is_slice", node->is_slice);

  if (node->lidx != NULL)
    _fingerprintChildNode(ctx, node->lidx, node, "lidx", depth);

  if (node->uidx != NULL)
    _fingerprintChildNode(ctx, node->uidx, node, "uidx", depth);

}

static void
_fingerprintA_Indirection(FingerprintContext *ctx, const A_Indirection *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->arg != NULL)
    _fingerprintChildNode(ctx, node->arg, node, "arg", depth);

  if (node->indirection != NULL && node->indirection->length > 0)
    _fingerprintChildList(ctx, node->indirection, node, "indirection", depth);

}

static void
_fingerprintA_ArrayExpr(FingerprintContext *ctx, const A_ArrayExpr *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->elements != NULL && node->elements->length > 0)
    _fingerprintChildList(ctx, node->elements, node, "elements", depth);

  // Intentionally ignoring node->list_end for fingerprinting

  // Intentionally ignoring node->list_start for fingerprinting

  // Intentionally ignoring node->location for fingerprinting

}

static void
_fingerprintResTarget(FingerprintContext *ctx, const ResTarget *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->indirection != NULL && node->indirection->length > 0)
    _fingerprintChildList(ctx, node->indirection, node, "indirection", depth);

  // Intentionally ignoring node->location for fingerprinting

  if (node->name != NULL && (field_name == NULL || parent == NULL || !IsA(parent, SelectStmt) || strcmp(field_name, "targetList") != 0)) {
    _fingerprintString(ctx, "name");
    _fingerprintString(ctx, node->name);
  }

  if (node->val != NULL)
    _fingerprintChildNode(ctx, node->val, node, "val", depth);

}

static void
_fingerprintMultiAssignRef(FingerprintContext *ctx, const MultiAssignRef *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintIntField(ctx, "colno", node->colno);

  _fingerprintIntField(ctx, "ncolumns", node->ncolumns);

  if (node->source != NULL)
    _fingerprintChildNode(ctx, node->source, node, "source", depth);

}

static void
_fingerprintSortBy(FingerprintContext *ctx, const SortBy *node, const void *parent, const char *field_name, unsigned int depth)
{
  // Intentionally ignoring node->location for fingerprinting

  if (node->node != NULL)
    _fingerprintChildNode(ctx, node->node, node, "node", depth);

  _fingerprintEnumField(ctx, "sortby_dir", _enumToStringSortByDir(node->sortby_dir));

  _fingerprintEnumField(ctx, "sortby_nulls", _enumToStringSortByNulls(node->sortby_nulls));

  if (node->useOp != NULL && node->useOp->length > 0)
    _fingerprintChildList(ctx, node->useOp, node, "useOp", depth);

}

static void
_fingerprintWindowDef(FingerprintContext *ctx, const WindowDef *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->endOffset != NULL)
    _fingerprintChildNode(ctx, node->endOffset, node, "endOffset", depth);

  _fingerprintIntField(ctx, "frameOptions", node->frameOptions);

  // Intentionally ignoring node->location for fingerprinting

  _fingerprintStringField(ctx, "name", node->name);

  if (node->orderClause != NULL && node->orderClause->length > 0)
    _fingerprintChildList(ctx, node->orderClause, node, "orderClause", depth);

  if (node->partitionClause != NULL && node->partitionClause->length > 0)
    _fingerprintChildList(ctx, node->partitionClause, node, "partitionClause", depth);

  _fingerprintStringField(ctx, "refname", node->refname);

  if (node->startOffset != NULL)
    _fingerprintChildNode(ctx, node->startOffset, node, "startOffset", depth);

}

static void
_fingerprintRangeSubselect(FingerprintContext *ctx, const RangeSubselect *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->alias != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "alias");
    _fingerprintAlias(ctx, node->alias, node, "alias", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  _fingerprintBoolField(ctx, "lateral", node->lateral);

  if (node->subquery != NULL)
    _fingerprintChildNode(ctx, node->subquery, node, "subquery", depth);

}

static void
_fingerprintRangeFunction(FingerprintContext *ctx, const RangeFunction *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->alias != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "alias");
    _fingerprintAlias(ctx, node->alias, node, "alias", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  if (node->coldeflist != NULL && node->coldeflist->length > 0)
    _fingerprintChildList(ctx, node->coldeflist, node, "coldeflist", depth);

  if (node->functions != NULL && node->functions->length > 0)
    _fingerprintChildList(ctx, node->functions, node, "functions", depth);

  _fingerprintBoolField(ctx, "is_rowsfrom", node->is_rowsfrom);

  _fingerprintBoolField(ctx, "lateral", node->lateral);

  _fingerprintBoolField(ctx, "ordinality", node->ordinality);

}

static void
_fingerprintRangeTableFunc(FingerprintContext *ctx, const RangeTableFunc *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->alias != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "alias");
    _fingerprintAlias(ctx, node->alias, node, "alias", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  if (node->columns != NULL && node->columns->length > 0)
    _fingerprintChildList(ctx, node->columns, node, "columns", depth);

  if (node->docexpr != NULL)
    _fingerprintChildNode(ctx, node->docexpr, node, "docexpr", depth);

  _fingerprintBoolField(ctx, "lateral", node->lateral);

  // Intentionally ignoring node->location for fingerprinting

  if (node->namespaces != NULL && node->namespaces->length > 0)
    _fingerprintChildList(ctx, node->namespaces, node, "namespaces", depth);

  if (node->rowexpr != NULL)
    _fingerprintChildNode(ctx, node->rowexpr, node, "rowexpr", depth);

}

static void
_fingerprintRangeTableFuncCol(FingerprintContext *ctx, const RangeTableFuncCol *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->coldefexpr != NULL)
    _fingerprintChildNode(ctx, node->coldefexpr, node, "coldefexpr", depth);

  if (node->colexpr != NULL)
    _fingerprintChildNode(ctx, node->colexpr, node, "colexpr", depth);

  _fingerprintStringField(ctx, "colname", node->colname);

  _fingerprintBoolField(ctx, "for_ordinality", node->for_ordinality);

  _fingerprintBoolField(ctx, "is_not_null", node->is_not_null);

  // Intentionally ignoring node->location for fingerprinting

  if (node->typeName != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "typeName");
    _fingerprintTypeName(ctx, node->typeName, node, "typeName", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

}

static void
_fingerprintRangeTableSample(FingerprintContext *ctx, const RangeTableSample *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->args != NULL && node->args->length > 0)
    _fingerprintChildList(ctx, node->args, node, "args", depth);

  // Intentionally ignoring node->location for fingerprinting

  if (node->method != NULL && node->method->length > 0)
    _fingerprintChildList(ctx, node->method, node, "method", depth);

  if (node->relation != NULL)
    _fingerprintChildNode(ctx, node->relation, node, "relation", depth);

  if (node->repeatable != NULL)
    _fingerprintChildNode(ctx, node->repeatable, node, "repeatable", depth);

}

static void
_fingerprintColumnDef(FingerprintContext *ctx, const ColumnDef *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->collClause != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "collClause");
    _fingerprintCollateClause(ctx, node->collClause, node, "collClause", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  _fingerprintIntField(ctx, "collOid", node->collOid);

  _fingerprintStringField(ctx, "colname", node->colname);

  _fingerprintStringField(ctx, "compression", node->compression);

  if (node->constraints != NULL && node->constraints->length > 0)
    _fingerprintChildList(ctx, node->constraints, node, "constraints", depth);

  if (node->cooked_default != NULL)
    _fingerprintChildNode(ctx, node->cooked_default, node, "cooked_default", depth);

  if (node->fdwoptions != NULL && node->fdwoptions->length > 0)
    _fingerprintChildList(ctx, node->fdwoptions, node, "fdwoptions", depth);

  _fingerprintCharField(ctx, "generated", node->generated);

  _fingerprintCharField(ctx, "identity", node->identity);

  if (node->identitySequence != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "identitySequence");
    _fingerprintRangeVar(ctx, node->identitySequence, node, "identitySequence", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  _fingerprintIntField(ctx, "inhcount", node->inhcount);

  _fingerprintBoolField(ctx, "is_from_type", node->is_from_type);

  _fingerprintBoolField(ctx, "is_local", node->is_local);

  _fingerprintBoolField(ctx, "is_not_null", node->is_not_null);

  // Intentionally ignoring node->location for fingerprinting

  if (node->raw_default != NULL)
    _fingerprintChildNode(ctx, node->raw_default, node, "raw_default", depth);

  _fingerprintCharField(ctx, "storage", node->storage);

  _fingerprintStringField(ctx, "storage_name", node->storage_name);

  if (node->typeName != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "typeName");
    _fingerprintTypeName(ctx, node->typeName, node, "typeName", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

}

static void
_fingerprintTableLikeClause(FingerprintContext *ctx, const TableLikeClause *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintIntField(ctx, "options", node->options);

  if (node->relation != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "relation");
    _fingerprintRangeVar(ctx, node->relation, node, "relation", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  _fingerprintIntField(ctx, "relationOid", node->relationOid);

}

static void
_fingerprintIndexElem(FingerprintContext *ctx, const IndexElem *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->collation != NULL && node->collation->length > 0)
    _fingerprintChildList(ctx, node->collation, node, "collation", depth);

  if (node->expr != NULL)
    _fingerprintChildNode(ctx, node->expr, node, "expr", depth);

  _fingerprintStringField(ctx, "indexcolname", node->indexcolname);

  _fingerprintStringField(ctx, "name", node->name);

  _fingerprintEnumField(ctx, "nulls_ordering", _enumToStringSortByNulls(node->nulls_ordering));

  if (node->opclass != NULL && node->opclass->length > 0)
    _fingerprintChildList(ctx, node->opclass, node, "opclass", depth);

  if (node->opclassopts != NULL && node->opclassopts->length > 0)
    _fingerprintChildList(ctx, node->opclassopts, node, "opclassopts", depth);

  _fingerprintEnumField(ctx, "ordering", _enumToStringSortByDir(node->ordering));

}

static void
_fingerprintDefElem(FingerprintContext *ctx, const DefElem *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->arg != NULL)
    _fingerprintChildNode(ctx, node->arg, node, "arg", depth);

  _fingerprintEnumField(ctx, "defaction", _enumToStringDefElemAction(node->defaction));

  _fingerprintStringField(ctx, "defname", node->defname);

  _fingerprintStringField(ctx, "defnamespace", node->defnamespace);

  // Intentionally ignoring node->location for fingerprinting

}

static void
_fingerprintLockingClause(FingerprintContext *ctx, const LockingClause *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->lockedRels != NULL && node->lockedRels->length > 0)
    _fingerprintChildList(ctx, node->lockedRels, node, "lockedRels", depth);

  _fingerprintEnumField(ctx, "strength", _enumToStringLockClauseStrength(node->strength));

  _fingerprintEnumField(ctx, "waitPolicy", _enumToStringLockWaitPolicy(node->waitPolicy));

}

static void
_fingerprintXmlSerialize(FingerprintContext *ctx, const XmlSerialize *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->expr != NULL)
    _fingerprintChildNode(ctx, node->expr, node, "expr", depth);

  _fingerprintBoolField(ctx, "indent", node->indent);

  // Intentionally ignoring node->location for fingerprinting

  if (node->typeName != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "typeName");
    _fingerprintTypeName(ctx, node->typeName, node, "typeName", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  _fingerprintEnumField(ctx, "xmloption", _enumToStringXmlOptionType(node->xmloption));

}

static void
_fingerprintPartitionElem(FingerprintContext *ctx, const PartitionElem *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->collation != NULL && node->collation->length > 0)
    _fingerprintChildList(ctx, node->collation, node, "collation", depth);

  if (node->expr != NULL)
    _fingerprintChildNode(ctx, node->expr, node, "expr", depth);

  // Intentionally ignoring node->location for fingerprinting

  _fingerprintStringField(ctx, "name", node->name);

  if (node->opclass != NULL && node->opclass->length > 0)
    _fingerprintChildList(ctx, node->opclass, node, "opclass", depth);

}

static void
_fingerprintPartitionSpec(FingerprintContext *ctx, const PartitionSpec *node, const void *parent, const char *field_name, unsigned int depth)
{
  // Intentionally ignoring node->location for fingerprinting

  if (node->partParams != NULL && node->partParams->length > 0)
    _fingerprintChildList(ctx, node->partParams, node, "partParams", depth);

  _fingerprintEnumField(ctx, "strategy", _enumToStringPartitionStrategy(node->strategy));

}

static void
_fingerprintPartitionBoundSpec(FingerprintContext *ctx, const PartitionBoundSpec *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintBoolField(ctx, "is_default", node->is_default);

  if (node->listdatums != NULL && node->listdatums->length > 0)
    _fingerprintChildList(ctx, node->listdatums, node, "listdatums", depth);

  // Intentionally ignoring node->location for fingerprinting

  if (node->lowerdatums != NULL && node->lowerdatums->length > 0)
    _fingerprintChildList(ctx, node->lowerdatums, node, "lowerdatums", depth);

  _fingerprintIntField(ctx, "modulus", node->modulus);

  _fingerprintIntField(ctx, "remainder", node->remainder);

  _fingerprintCharField(ctx, "strategy", node->strategy);

  if (node->upperdatums != NULL && node->upperdatums->length > 0)
    _fingerprintChildList(ctx, node->upperdatums, node, "upperdatums", depth);

}

static void
_fingerprintPartitionRangeDatum(FingerprintContext *ctx, const PartitionRangeDatum *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintEnumField(ctx, "kind", _enumToStringPartitionRangeDatumKind(node->kind));

  // Intentionally ignoring node->location for fingerprinting

  if (node->value != NULL)
    _fingerprintChildNode(ctx, node->value, node, "value", depth);

}

static void
_fingerprintPartitionCmd(FingerprintContext *ctx, const PartitionCmd *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->bound != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "bound");
    _fingerprintPartitionBoundSpec(ctx, node->bound, node, "bound", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  _fingerprintBoolField(ctx, "concurrent", node->concurrent);

  if (node->name != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "name");
    _fingerprintRangeVar(ctx, node->name, node, "name", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

}

static void
_fingerprintRangeTblEntry(FingerprintContext *ctx, const RangeTblEntry *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->alias != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "alias");
    _fingerprintAlias(ctx, node->alias, node, "alias", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  if (node->colcollations != NULL && node->colcollations->length > 0)
    _fingerprintChildList(ctx, node->colcollations, node, "colcollations", depth);

  if (node->coltypes != NULL && node->coltypes->length > 0)
    _fingerprintChildList(ctx, node->coltypes, node, "coltypes", depth);

  if (node->coltypmods != NULL && node->coltypmods->length > 0)
    _fingerprintChildList(ctx, node->coltypmods, node, "coltypmods", depth);

  _fingerprintIntField(ctx, "ctelevelsup", node->ctelevelsup);

  _fingerprintStringField(ctx, "ctename", node->ctename);

  _fingerprintStringField(ctx, "enrname", node->enrname);

  _fingerprintFloatField(ctx, "enrtuples", node->enrtuples);

  if (node->eref != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "eref");
    _fingerprintAlias(ctx, node->eref, node, "eref", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  _fingerprintBoolField(ctx, "funcordinality", node->funcordinality);

  if (node->functions != NULL && node->functions->length > 0)
    _fingerprintChildList(ctx, node->functions, node, "functions", depth);

  if (node->groupexprs != NULL && node->groupexprs->length > 0)
    _fingerprintChildList(ctx, node->groupexprs, node, "groupexprs", depth);

  _fingerprintBoolField(ctx, "inFromCl", node->inFromCl);

  _fingerprintBoolField(ctx, "inh", node->inh);

  if (node->join_using_alias != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "join_using_alias");
    _fingerprintAlias(ctx, node->join_using_alias, node, "join_using_alias", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  if (node->joinaliasvars != NULL && node->joinaliasvars->length > 0)
    _fingerprintChildList(ctx, node->joinaliasvars, node, "joinaliasvars", depth);

  if (node->joinleftcols != NULL && node->joinleftcols->length > 0)
    _fingerprintChildList(ctx, node->joinleftcols, node, "joinleftcols", depth);

  _fingerprintIntField(ctx, "joinmergedcols", node->joinmergedcols);

  if (node->joinrightcols != NULL && node->joinrightcols->length > 0)
    _fingerprintChildList(ctx, node->joinrightcols, node, "joinrightcols", depth);

  _fingerprintEnumField(ctx, "jointype", _enumToStringJoinType(node->jointype));

  _fingerprintBoolField(ctx, "lateral", node->lateral);

  _fingerprintIntField(ctx, "perminfoindex", node->perminfoindex);

  _fingerprintIntField(ctx, "relid", node->relid);

  _fingerprintCharField(ctx, "relkind", node->relkind);

  _fingerprintIntField(ctx, "rellockmode", node->rellockmode);

  _fingerprintEnumField(ctx, "rtekind", _enumToStringRTEKind(node->rtekind));

  if (node->securityQuals != NULL && node->securityQuals->length > 0)
    _fingerprintChildList(ctx, node->securityQuals, node, "securityQuals", depth);

  _fingerprintBoolField(ctx, "security_barrier", node->security_barrier);

  _fingerprintBoolField(ctx, "self_reference", node->self_reference);

  if (node->subquery != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "subquery");
    _fingerprintQuery(ctx, node->subquery, node, "subquery", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  if (node->tablefunc != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "tablefunc");
    _fingerprintTableFunc(ctx, node->tablefunc, node, "tablefunc", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  if (node->tablesample != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "tablesample");
    _fingerprintTableSampleClause(ctx, node->tablesample, node, "tablesample", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  if (node->values_lists != NULL && node->values_lists->length > 0)
    _fingerprintChildList(ctx, node->values_lists, node, "values_lists", depth);

}

static void
_fingerprintRTEPermissionInfo(FingerprintContext *ctx, const RTEPermissionInfo *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintIntField(ctx, "checkAsUser", node->checkAsUser);

  _fingerprintBoolField(ctx, "inh", node->inh);

  _fingerprintBitmapsetField(ctx, "insertedCols", node->insertedCols);

  _fingerprintIntField(ctx, "relid", node->relid);

  _fingerprintUInt64Field(ctx, "requiredPerms", node->requiredPerms);

  _fingerprintBitmapsetField(ctx, "selectedCols", node->selectedCols);

  _fingerprintBitmapsetField(ctx, "updatedCols", node->updatedCols);

}

static void
_fingerprintRangeTblFunction(FingerprintContext *ctx, const RangeTblFunction *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->funccolcollations != NULL && node->funccolcollations->length > 0)
    _fingerprintChildList(ctx, node->funccolcollations, node, "funccolcollations", depth);

  _fingerprintIntField(ctx, "funccolcount", node->funccolcount);

  if (node->funccolnames != NULL && node->funccolnames->length > 0)
    _fingerprintChildList(ctx, node->funccolnames, node, "funccolnames", depth);

  if (node->funccoltypes != NULL && node->funccoltypes->length > 0)
    _fingerprintChildList(ctx, node->funccoltypes, node, "funccoltypes", depth);

  if (node->funccoltypmods != NULL && node->funccoltypmods->length > 0)
    _fingerprintChildList(ctx, node->funccoltypmods, node, "funccoltypmods", depth);

  if (node->funcexpr != NULL)
    _fingerprintChildNode(ctx, node->funcexpr, node, "funcexpr", depth);

  _fingerprintBitmapsetField(ctx, "funcparams", node->funcparams);

}

static void
_fingerprintTableSampleClause(FingerprintContext *ctx, const TableSampleClause *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->args != NULL && node->args->length > 0)
    _fingerprintChildList(ctx, node->args, node, "args", depth);

  if (node->repeatable != NULL)
    _fingerprintChildNode(ctx, node->repeatable, node, "repeatable", depth);

  _fingerprintIntField(ctx, "tsmhandler", node->tsmhandler);

}

static void
_fingerprintWithCheckOption(FingerprintContext *ctx, const WithCheckOption *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintBoolField(ctx, "cascaded", node->cascaded);

  _fingerprintEnumField(ctx, "kind", _enumToStringWCOKind(node->kind));

  _fingerprintStringField(ctx, "polname", node->polname);

  if (node->qual != NULL)
    _fingerprintChildNode(ctx, node->qual, node, "qual", depth);

  _fingerprintStringField(ctx, "relname", node->relname);

}

static void
_fingerprintSortGroupClause(FingerprintContext *ctx, const SortGroupClause *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintIntField(ctx, "eqop", node->eqop);

  _fingerprintBoolField(ctx, "hashable", node->hashable);

  _fingerprintBoolField(ctx, "nulls_first", node->nulls_first);

  _fingerprintBoolField(ctx, "reverse_sort", node->reverse_sort);

  _fingerprintIntField(ctx, "sortop", node->sortop);

  _fingerprintIntField(ctx, "tleSortGroupRef", node->tleSortGroupRef);

}

static void
_fingerprintGroupingSet(FingerprintContext *ctx, const GroupingSet *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->content != NULL && node->content->length > 0)
    _fingerprintChildList(ctx, node->content, node, "content", depth);

  _fingerprintEnumField(ctx, "kind", _enumToStringGroupingSetKind(node->kind));

  // Intentionally ignoring node->location for fingerprinting

}

static void
_fingerprintWindowClause(FingerprintContext *ctx, const WindowClause *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintBoolField(ctx, "copiedOrder", node->copiedOrder);

  _fingerprintIntField(ctx, "endInRangeFunc", node->endInRangeFunc);

  if (node->endOffset != NULL)
    _fingerprintChildNode(ctx, node->endOffset, node, "endOffset", depth);

  _fingerprintIntField(ctx, "frameOptions", node->frameOptions);

  _fingerprintBoolField(ctx, "inRangeAsc", node->inRangeAsc);

  _fingerprintIntField(ctx, "inRangeColl", node->inRangeColl);

  _fingerprintBoolField(ctx, "inRangeNullsFirst", node->inRangeNullsFirst);

  _fingerprintStringField(ctx, "name", node->name);

  if (node->orderClause != NULL && node->orderClause->length > 0)
    _fingerprintChildList(ctx, node->orderClause, node, "orderClause", depth);

  if (node->partitionClause != NULL && node->partitionClause->length > 0)
    _fingerprintChildList(ctx, node->partitionClause, node, "partitionClause", depth);

  _fingerprintStringField(ctx, "refname", node->refname);

  _fingerprintIntField(ctx, "startInRangeFunc", node->startInRangeFunc);

  if (node->startOffset != NULL)
    _fingerprintChildNode(ctx, node->startOffset, node, "startOffset", depth);

  _fingerprintIntField(ctx, "winref", node->winref);

}

static void
_fingerprintRowMarkClause(FingerprintContext *ctx, const RowMarkClause *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintBoolField(ctx, "pushedDown", node->pushedDown);

  _fingerprintIntField(ctx, "rti", node->rti);

  _fingerprintEnumField(ctx, "strength", _enumToStringLockClauseStrength(node->strength));

  _fingerprintEnumField(ctx, "waitPolicy", _enumToStringLockWaitPolicy(node->waitPolicy));

}

static void
_fingerprintWithClause(FingerprintContext *ctx, const WithClause *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->ctes != NULL && node->ctes->length > 0)
    _fingerprintChildList(ctx, node->ctes, node, "ctes", depth);

  // Intentionally ignoring node->location for fingerprinting

  _fingerprintBoolField(ctx, "recursive", node->recursive);

}

static void
_fingerprintInferClause(FingerprintContext *ctx, const InferClause *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintStringField(ctx, "conname", node->conname);

  if (node->indexElems != NULL && node->indexElems->length > 0)
    _fingerprintChildList(ctx, node->indexElems, node, "indexElems", depth);

  // Intentionally ignoring node->location for fingerprinting

  if (node->whereClause != NULL)
    _fingerprintChildNode(ctx, node->whereClause, node, "whereClause", depth);

}

static void
_fingerprintOnConflictClause(FingerprintContext *ctx, const OnConflictClause *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintEnumField(ctx, "action", _enumToStringOnConflictAction(node->action));

  if (node->infer != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "infer");
    _fingerprintInferClause(ctx, node->infer, node, "infer", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  // Intentionally ignoring node->location for fingerprinting

  if (node->targetList != NULL && node->targetList->length > 0)
    _fingerprintChildList(ctx, node->targetList, node, "targetList", depth);

  if (node->whereClause != NULL)
    _fingerprintChildNode(ctx, node->whereClause, node, "whereClause", depth);

}

static void
_fingerprintCTESearchClause(FingerprintContext *ctx, const CTESearchClause *node, const void *parent, const char *field_name, unsigned int depth)
{
  // Intentionally ignoring node->location for fingerprinting

  _fingerprintBoolField(ctx, "search_breadth_first", node->search_breadth_first);

  if (node->search_col_list != NULL && node->search_col_list->length > 0)
    _fingerprintChildList(ctx, node->search_col_list, node, "search_col_list", depth);

  _fingerprintStringField(ctx, "search_seq_column", node->search_seq_column);

}

static void
_fingerprintCTECycleClause(FingerprintContext *ctx, const CTECycleClause *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->cycle_col_list != NULL && node->cycle_col_list->length > 0)
    _fingerprintChildList(ctx, node->cycle_col_list, node, "cycle_col_list", depth);

  _fingerprintIntField(ctx, "cycle_mark_collation", node->cycle_mark_collation);

  _fingerprintStringField(ctx, "cycle_mark_column", node->cycle_mark_column);

  if (node->cycle_mark_default != NULL)
    _fingerprintChildNode(ctx, node->cycle_mark_default, node, "cycle_mark_default", depth);

  _fingerprintIntField(ctx, "cycle_mark_neop", node->cycle_mark_neop);

  _fingerprintIntField(ctx, "cycle_mark_type", node->cycle_mark_type);

  _fingerprintIntField(ctx, "cycle_mark_typmod", node->cycle_mark_typmod);

  if (node->cycle_mark_value != NULL)
    _fingerprintChildNode(ctx, node->cycle_mark_value, node, "cycle_mark_value", depth);

  _fingerprintStringField(ctx, "cycle_path_column", node->cycle_path_column);

  // Intentionally ignoring node->location for fingerprinting

}

static void
_fingerprintCommonTableExpr(FingerprintContext *ctx, const CommonTableExpr *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->aliascolnames != NULL && node->aliascolnames->length > 0)
    _fingerprintChildList(ctx, node->aliascolnames, node, "aliascolnames", depth);

  if (node->ctecolcollations != NULL && node->ctecolcollations->length > 0)
    _fingerprintChildList(ctx, node->ctecolcollations, node, "ctecolcollations", depth);

  if (node->ctecolnames != NULL && node->ctecolnames->length > 0)
    _fingerprintChildList(ctx, node->ctecolnames, node, "ctecolnames", depth);

  if (node->ctecoltypes != NULL && node->ctecoltypes->length > 0)
    _fingerprintChildList(ctx, node->ctecoltypes, node, "ctecoltypes", depth);

  if (node->ctecoltypmods != NULL && node->ctecoltypmods->length > 0)
    _fingerprintChildList(ctx, node->ctecoltypmods, node, "ctecoltypmods", depth);

  _fingerprintEnumField(ctx, "ctematerialized", _enumToStringCTEMaterialize(node->ctematerialized));

  _fingerprintStringField(ctx, "ctename", node->ctename);

  if (node->ctequery != NULL)
    _fingerprintChildNode(ctx, node->ctequery, node, "ctequery", depth);

  _fingerprintBoolField(ctx, "cterecursive", node->cterecursive);

  _fingerprintIntField(ctx, "cterefcount", node->cterefcount);

  if (node->cycle_clause != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "cycle_clause");
    _fingerprintCTECycleClause(ctx, node->cycle_clause, node, "cycle_clause", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  // Intentionally ignoring node->location for fingerprinting

  if (node->search_clause != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "search_clause");
    _fingerprintCTESearchClause(ctx, node->search_clause, node, "search_clause", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

}

static void
_fingerprintMergeWhenClause(FingerprintContext *ctx, const MergeWhenClause *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintEnumField(ctx, "commandType", _enumToStringCmdType(node->commandType));

  if (node->condition != NULL)
    _fingerprintChildNode(ctx, node->condition, node, "condition", depth);

  _fingerprintEnumField(ctx, "matchKind", _enumToStringMergeMatchKind(node->matchKind));

  _fingerprintEnumField(ctx, "override", _enumToStringOverridingKind(node->override));

  if (node->targetList != NULL && node->targetList->length > 0)
    _fingerprintChildList(ctx, node->targetList, node, "targetList", depth);

  if (node->values != NULL && node->values->length > 0)
    _fingerprintChildList(ctx, node->values, node, "values", depth);

}

static void
_fingerprintReturningOption(FingerprintContext *ctx, const ReturningOption *node, const void *parent, const char *field_name, unsigned int depth)
{
  // Intentionally ignoring node->location for fingerprinting

  _fingerprintEnumField(ctx, "option", _enumToStringReturningOptionKind(node->option));

  _fingerprintStringField(ctx, "value", node->value);

}

static void
_fingerprintReturningClause(FingerprintContext *ctx, const ReturningClause *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->exprs != NULL && node->exprs->length > 0)
    _fingerprintChildList(ctx, node->exprs, node, "exprs", depth);

  if (node->options != NULL && node->options->length > 0)
    _fingerprintChildList(ctx, node->options, node, "options", depth);

}

static void
_fingerprintTriggerTransition(FingerprintContext *ctx, const TriggerTransition *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintBoolField(ctx, "isNew", node->isNew);

  _fingerprintBoolField(ctx, "isTable", node->isTable);

  _fingerprintStringField(ctx, "name", node->name);

}

static void
_fingerprintJsonOutput(FingerprintContext *ctx, const JsonOutput *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->returning != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "returning");
    _fingerprintJsonReturning(ctx, node->returning, node, "returning", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  if (node->typeName != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "typeName");
    _fingerprintTypeName(ctx, node->typeName, node, "typeName", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

}

static void
_fingerprintJsonArgument(FingerprintContext *ctx, const JsonArgument *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintStringField(ctx, "name", node->name);

  if (node->val != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "val");
    _fingerprintJsonValueExpr(ctx, node->val, node, "val", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

}

static void
_fingerprintJsonFuncExpr(FingerprintContext *ctx, const JsonFuncExpr *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintStringField(ctx, "column_name", node->column_name);

  if (node->context_item != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "context_item");
    _fingerprintJsonValueExpr(ctx, node->context_item, node, "context_item", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  // Intentionally ignoring node->location for fingerprinting

  if (node->on_empty != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "on_empty");
    _fingerprintJsonBehavior(ctx, node->on_empty, node, "on_empty", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  if (node->on_error != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "on_error");
    _fingerprintJsonBehavior(ctx, node->on_error, node, "on_error", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  _fingerprintEnumField(ctx, "op", _enumToStringJsonExprOp(node->op));

  if (node->output != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "output");
    _fingerprintJsonOutput(ctx, node->output, node, "output", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  if (node->passing != NULL && node->passing->length > 0)
    _fingerprintChildList(ctx, node->passing, node, "passing", depth);

  if (node->pathspec != NULL)
    _fingerprintChildNode(ctx, node->pathspec, node, "pathspec", depth);

  _fingerprintEnumField(ctx, "quotes", _enumToStringJsonQuotes(node->quotes));

  _fingerprintEnumField(ctx, "wrapper", _enumToStringJsonWrapper(node->wrapper));

}

static void
_fingerprintJsonTablePathSpec(FingerprintContext *ctx, const JsonTablePathSpec *node, const void *parent, const char *field_name, unsigned int depth)
{
  // Intentionally ignoring node->location for fingerprinting

  _fingerprintStringField(ctx, "name", node->name);

  // Intentionally ignoring node->name_location for fingerprinting

  if (node->string != NULL)
    _fingerprintChildNode(ctx, node->string, node, "string", depth);

}

static void
_fingerprintJsonTable(FingerprintContext *ctx, const JsonTable *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->alias != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "alias");
    _fingerprintAlias(ctx, node->alias, node, "alias", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  if (node->columns != NULL && node->columns->length > 0)
    _fingerprintChildList(ctx, node->columns, node, "columns", depth);

  if (node->context_item != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "context_item");
    _fingerprintJsonValueExpr(ctx, node->context_item, node, "context_item", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  _fingerprintBoolField(ctx, "lateral", node->lateral);

  // Intentionally ignoring node->location for fingerprinting

  if (node->on_error != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "on_error");
    _fingerprintJsonBehavior(ctx, node->on_error, node, "on_error", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  if (node->passing != NULL && node->passing->length > 0)
    _fingerprintChildList(ctx, node->passing, node, "passing", depth);

  if (node->pathspec != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "pathspec");
    _fingerprintJsonTablePathSpec(ctx, node->pathspec, node, "pathspec", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

}

static void
_fingerprintJsonTableColumn(FingerprintContext *ctx, const JsonTableColumn *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintEnumField(ctx, "coltype", _enumToStringJsonTableColumnType(node->coltype));

  if (node->columns != NULL && node->columns->length > 0)
    _fingerprintChildList(ctx, node->columns, node, "columns", depth);

  if (node->format != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "format");
    _fingerprintJsonFormat(ctx, node->format, node, "format", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  // Intentionally ignoring node->location for fingerprinting

  _fingerprintStringField(ctx, "name", node->name);

  if (node->on_empty != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "on_empty");
    _fingerprintJsonBehavior(ctx, node->on_empty, node, "on_empty", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  if (node->on_error != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "on_error");
    _fingerprintJsonBehavior(ctx, node->on_error, node, "on_error", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  if (node->pathspec != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "pathspec");
    _fingerprintJsonTablePathSpec(ctx, node->pathspec, node, "pathspec", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  _fingerprintEnumField(ctx, "quotes", _enumToStringJsonQuotes(node->quotes));

  if (node->typeName != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "typeName");
    _fingerprintTypeName(ctx, node->typeName, node, "typeName", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  _fingerprintEnumField(ctx, "wrapper", _enumToStringJsonWrapper(node->wrapper));

}

static void
_fingerprintJsonKeyValue(FingerprintContext *ctx, const JsonKeyValue *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->key != NULL)
    _fingerprintChildNode(ctx, node->key, node, "key", depth);

  if (node->value != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "value");
    _fingerprintJsonValueExpr(ctx, node->value, node, "value", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

}

static void
_fingerprintJsonParseExpr(FingerprintContext *ctx, const JsonParseExpr *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->expr != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "expr");
    _fingerprintJsonValueExpr(ctx, node->expr, node, "expr", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  // Intentionally ignoring node->location for fingerprinting

  if (node->output != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "output");
    _fingerprintJsonOutput(ctx, node->output, node, "output", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  _fingerprintBoolField(ctx, "unique_keys", node->unique_keys);

}

static void
_fingerprintJsonScalarExpr(FingerprintContext *ctx, const JsonScalarExpr *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->expr != NULL)
    _fingerprintChildNode(ctx, node->expr, node, "expr", depth);

  // Intentionally ignoring node->location for fingerprinting

  if (node->output != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "output");
    _fingerprintJsonOutput(ctx, node->output, node, "output", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

}

static void
_fingerprintJsonSerializeExpr(FingerprintContext *ctx, const JsonSerializeExpr *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->expr != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "expr");
    _fingerprintJsonValueExpr(ctx, node->expr, node, "expr", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  // Intentionally ignoring node->location for fingerprinting

  if (node->output != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "output");
    _fingerprintJsonOutput(ctx, node->output, node, "output", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

}

static void
_fingerprintJsonObjectConstructor(FingerprintContext *ctx, const JsonObjectConstructor *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintBoolField(ctx, "absent_on_null", node->absent_on_null);

  if (node->exprs != NULL && node->exprs->length > 0)
    _fingerprintChildList(ctx, node->exprs, node, "exprs", depth);

  // Intentionally ignoring node->location for fingerprinting

  if (node->output != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "output");
    _fingerprintJsonOutput(ctx, node->output, node, "output", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  _fingerprintBoolField(ctx, "unique", node->unique);

}

static void
_fingerprintJsonArrayConstructor(FingerprintContext *ctx, const JsonArrayConstructor *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintBoolField(ctx, "absent_on_null", node->absent_on_null);

  if (node->exprs != NULL && node->exprs->length > 0)
    _fingerprintChildList(ctx, node->exprs, node, "exprs", depth);

  // Intentionally ignoring node->location for fingerprinting

  if (node->output != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "output");
    _fingerprintJsonOutput(ctx, node->output, node, "output", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

}

static void
_fingerprintJsonArrayQueryConstructor(FingerprintContext *ctx, const JsonArrayQueryConstructor *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintBoolField(ctx, "absent_on_null", node->absent_on_null);

  if (node->format != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "format");
    _fingerprintJsonFormat(ctx, node->format, node, "format", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  // Intentionally ignoring node->location for fingerprinting

  if (node->output != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "output");
    _fingerprintJsonOutput(ctx, node->output, node, "output", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  if (node->query != NULL)
    _fingerprintChildNode(ctx, node->query, node, "query", depth);

}

static void
_fingerprintJsonAggConstructor(FingerprintContext *ctx, const JsonAggConstructor *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->agg_filter != NULL)
    _fingerprintChildNode(ctx, node->agg_filter, node, "agg_filter", depth);

  if (node->agg_order != NULL && node->agg_order->length > 0)
    _fingerprintChildList(ctx, node->agg_order, node, "agg_order", depth);

  // Intentionally ignoring node->location for fingerprinting

  if (node->output != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "output");
    _fingerprintJsonOutput(ctx, node->output, node, "output", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  if (node->over != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "over");
    _fingerprintWindowDef(ctx, node->over, node, "over", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

}

static void
_fingerprintJsonObjectAgg(FingerprintContext *ctx, const JsonObjectAgg *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintBoolField(ctx, "absent_on_null", node->absent_on_null);

  if (node->arg != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "arg");
    _fingerprintJsonKeyValue(ctx, node->arg, node, "arg", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  if (node->constructor != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "constructor");
    _fingerprintJsonAggConstructor(ctx, node->constructor, node, "constructor", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  _fingerprintBoolField(ctx, "unique", node->unique);

}

static void
_fingerprintJsonArrayAgg(FingerprintContext *ctx, const JsonArrayAgg *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintBoolField(ctx, "absent_on_null", node->absent_on_null);

  if (node->arg != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "arg");
    _fingerprintJsonValueExpr(ctx, node->arg, node, "arg", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  if (node->constructor != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "constructor");
    _fingerprintJsonAggConstructor(ctx, node->constructor, node, "constructor", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

}

static void
_fingerprintRawStmt(FingerprintContext *ctx, const RawStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->stmt != NULL)
    _fingerprintChildNode(ctx, node->stmt, node, "stmt", depth);

  // Intentionally ignoring node->stmt_len for fingerprinting

  // Intentionally ignoring node->stmt_location for fingerprinting

}

static void
_fingerprintInsertStmt(FingerprintContext *ctx, const InsertStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->cols != NULL && node->cols->length > 0)
    _fingerprintChildList(ctx, node->cols, node, "cols", depth);

  if (node->onConflictClause != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "onConflictClause");
    _fingerprintOnConflictClause(ctx, node->onConflictClause, node, "onConflictClause", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  _fingerprintEnumField(ctx, "override", _enumToStringOverridingKind(node->override));

  if (node->relation != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "relation");
    _fingerprintRangeVar(ctx, node->relation, node, "relation", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  if (node->returningClause != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "returningClause");
    _fingerprintReturningClause(ctx, node->returningClause, node, "returningClause", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  if (node->selectStmt != NULL)
    _fingerprintChildNode(ctx, node->selectStmt, node, "selectStmt", depth);

  if (node->withClause != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "withClause");
    _fingerprintWithClause(ctx, node->withClause, node, "withClause", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

}

static void
_fingerprintDeleteStmt(FingerprintContext *ctx, const DeleteStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->relation != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "relation");
    _fingerprintRangeVar(ctx, node->relation, node, "relation", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  if (node->returningClause != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "returningClause");
    _fingerprintReturningClause(ctx, node->returningClause, node, "returningClause", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  if (node->usingClause != NULL && node->usingClause->length > 0)
    _fingerprintChildList(ctx, node->usingClause, node, "usingClause", depth);

  if (node->whereClause != NULL)
    _fingerprintChildNode(ctx, node->whereClause, node, "whereClause", depth);

  if (node->withClause != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "withClause");
    _fingerprintWithClause(ctx, node->withClause, node, "withClause", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

}

static void
_fingerprintUpdateStmt(FingerprintContext *ctx, const UpdateStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->fromClause != NULL && node->fromClause->length > 0)
    _fingerprintChildList(ctx, node->fromClause, node, "fromClause", depth);

  if (node->relation != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "relation");
    _fingerprintRangeVar(ctx, node->relation, node, "relation", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  if (node->returningClause != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "returningClause");
    _fingerprintReturningClause(ctx, node->returningClause, node, "returningClause", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  if (node->targetList != NULL && node->targetList->length > 0)
    _fingerprintChildList(ctx, node->targetList, node, "targetList", depth);

  if (node->whereClause != NULL)
    _fingerprintChildNode(ctx, node->whereClause, node, "whereClause", depth);

  if (node->withClause != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "withClause");
    _fingerprintWithClause(ctx, node->withClause, node, "withClause", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

}

static void
_fingerprintMergeStmt(FingerprintContext *ctx, const MergeStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->joinCondition != NULL)
    _fingerprintChildNode(ctx, node->joinCondition, node, "joinCondition", depth);

  if (node->mergeWhenClauses != NULL && node->mergeWhenClauses->length > 0)
    _fingerprintChildList(ctx, node->mergeWhenClauses, node, "mergeWhenClauses", depth);

  if (node->relation != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "relation");
    _fingerprintRangeVar(ctx, node->relation, node, "relation", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  if (node->returningClause != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "returningClause");
    _fingerprintReturningClause(ctx, node->returningClause, node, "returningClause", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  if (node->sourceRelation != NULL)
    _fingerprintChildNode(ctx, node->sourceRelation, node, "sourceRelation", depth);

  if (node->withClause != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "withClause");
    _fingerprintWithClause(ctx, node->withClause, node, "withClause", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

}

static void
_fingerprintSelectStmt(FingerprintContext *ctx, const SelectStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintBoolField(ctx, "all", node->all);

  if (node->distinctClause != NULL && node->distinctClause->length > 0)
    _fingerprintChildList(ctx, node->distinctClause, node, "distinctClause", depth);

  if (node->fromClause != NULL && node->fromClause->length > 0)
    _fingerprintChildList(ctx, node->fromClause, node, "fromClause", depth);

  if (node->groupClause != NULL && node->groupClause->length > 0)
    _fingerprintChildList(ctx, node->groupClause, node, "groupClause", depth);

  _fingerprintBoolField(ctx, "groupDistinct", node->groupDistinct);

  if (node->havingClause != NULL)
    _fingerprintChildNode(ctx, node->havingClause, node, "havingClause", depth);

  if (node->intoClause != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "intoClause");
    _fingerprintIntoClause(ctx, node->intoClause, node, "intoClause", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  if (node->larg != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "larg");
    _fingerprintSelectStmt(ctx, node->larg, node, "larg", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  if (node->limitCount != NULL)
    _fingerprintChildNode(ctx, node->limitCount, node, "limitCount", depth);

  if (node->limitOffset != NULL)
    _fingerprintChildNode(ctx, node->limitOffset, node, "limitOffset", depth);

  _fingerprintEnumField(ctx, "limitOption", _enumToStringLimitOption(node->limitOption));

  if (node->lockingClause != NULL && node->lockingClause->length > 0)
    _fingerprintChildList(ctx, node->lockingClause, node, "lockingClause", depth);

  _fingerprintEnumField(ctx, "op", _enumToStringSetOperation(node->op));

  if (node->rarg != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "rarg");
    _fingerprintSelectStmt(ctx, node->rarg, node, "rarg", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  if (node->sortClause != NULL && node->sortClause->length > 0)
    _fingerprintChildList(ctx, node->sortClause, node, "sortClause", depth);

  if (node->targetList != NULL && node->targetList->length > 0)
    _fingerprintChildList(ctx, node->targetList, node, "targetList", depth);

  if (node->valuesLists != NULL && node->valuesLists->length > 0)
    _fingerprintChildList(ctx, node->valuesLists, node, "valuesLists", depth);

  if (node->whereClause != NULL)
    _fingerprintChildNode(ctx, node->whereClause, node, "whereClause", depth);

  if (node->windowClause != NULL && node->windowClause->length > 0)
    _fingerprintChildList(ctx, node->windowClause, node, "windowClause", depth);

  if (node->withClause != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "withClause");
    _fingerprintWithClause(ctx, node->withClause, node, "withClause", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

}

static void
_fingerprintSetOperationStmt(FingerprintContext *ctx, const SetOperationStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintBoolField(ctx, "all", node->all);

  if (node->colCollations != NULL && node->colCollations->length > 0)
    _fingerprintChildList(ctx, node->colCollations, node, "colCollations", depth);

  if (node->colTypes != NULL && node->colTypes->length > 0)
    _fingerprintChildList(ctx, node->colTypes, node, "colTypes", depth);

  if (node->colTypmods != NULL && node->colTypmods->length > 0)
    _fingerprintChildList(ctx, node->colTypmods, node, "colTypmods", depth);

  if (node->groupClauses != NULL && node->groupClauses->length > 0)
    _fingerprintChildList(ctx, node->groupClauses, node, "groupClauses", depth);

  if (node->larg != NULL)
    _fingerprintChildNode(ctx, node->larg, node, "larg", depth);

  _fingerprintEnumField(ctx, "op", _enumToStringSetOperation(node->op));

  if (node->rarg != NULL)
    _fingerprintChildNode(ctx, node->rarg, node, "rarg", depth);

}

static void
_fingerprintReturnStmt(FingerprintContext *ctx, const ReturnStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->returnval != NULL)
    _fingerprintChildNode(ctx, node->returnval, node, "returnval", depth);

}

static void
_fingerprintPLAssignStmt(FingerprintContext *ctx, const PLAssignStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->indirection != NULL && node->indirection->length > 0)
    _fingerprintChildList(ctx, node->indirection, node, "indirection", depth);

  // Intentionally ignoring node->location for fingerprinting

  _fingerprintStringField(ctx, "name", node->name);

  _fingerprintIntField(ctx, "nnames", node->nnames);

  if (node->val != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "val");
    _fingerprintSelectStmt(ctx, node->val, node, "val", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

}

static void
_fingerprintCreateSchemaStmt(FingerprintContext *ctx, const CreateSchemaStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->authrole != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "authrole");
    _fingerprintRoleSpec(ctx, node->authrole, node, "authrole", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  _fingerprintBoolField(ctx, "if_not_exists", node->if_not_exists);

  if (node->schemaElts != NULL && node->schemaElts->length > 0)
    _fingerprintChildList(ctx, node->schemaElts, node, "schemaElts", depth);

  _fingerprintStringField(ctx, "schemaname", node->schemaname);

}

static void
_fingerprintAlterTableStmt(FingerprintContext *ctx, const AlterTableStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->cmds != NULL && node->cmds->length > 0)
    _fingerprintChildList(ctx, node->cmds, node, "cmds", depth);

  _fingerprintBoolField(ctx, "missing_ok", node->missing_ok);

  _fingerprintEnumField(ctx, "objtype", _enumToStringObjectType(node->objtype));

  if (node->relation != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "relation");
    _fingerprintRangeVar(ctx, node->relation, node, "relation", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

}

static void
_fingerprintAlterTableCmd(FingerprintContext *ctx, const AlterTableCmd *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintEnumField(ctx, "behavior", _enumToStringDropBehavior(node->behavior));

  if (node->def != NULL)
    _fingerprintChildNode(ctx, node->def, node, "def", depth);

  _fingerprintBoolField(ctx, "missing_ok", node->missing_ok);

  _fingerprintStringField(ctx, "name", node->name);

  if (node->newowner != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "newowner");
    _fingerprintRoleSpec(ctx, node->newowner, node, "newowner", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  _fingerprintIntField(ctx, "num", node->num);

  _fingerprintBoolField(ctx, "recurse", node->recurse);

  _fingerprintEnumField(ctx, "subtype", _enumToStringAlterTableType(node->subtype));

}

static void
_fingerprintATAlterConstraint(FingerprintContext *ctx, const ATAlterConstraint *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintBoolField(ctx, "alterDeferrability", node->alterDeferrability);

  _fingerprintBoolField(ctx, "alterEnforceability", node->alterEnforceability);

  _fingerprintBoolField(ctx, "alterInheritability", node->alterInheritability);

  _fingerprintStringField(ctx, "conname", node->conname);

  _fingerprintBoolField(ctx, "deferrable", node->deferrable);

  _fingerprintBoolField(ctx, "initdeferred", node->initdeferred);

  _fingerprintBoolField(ctx, "is_enforced", node->is_enforced);

  _fingerprintBoolField(ctx, "noinherit", node->noinherit);

}

static void
_fingerprintReplicaIdentityStmt(FingerprintContext *ctx, const ReplicaIdentityStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintCharField(ctx, "identity_type", node->identity_type);

  _fingerprintStringField(ctx, "name", node->name);

}

static void
_fingerprintAlterCollationStmt(FingerprintContext *ctx, const AlterCollationStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->collname != NULL && node->collname->length > 0)
    _fingerprintChildList(ctx, node->collname, node, "collname", depth);

}

static void
_fingerprintAlterDomainStmt(FingerprintContext *ctx, const AlterDomainStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintEnumField(ctx, "behavior", _enumToStringDropBehavior(node->behavior));

  if (node->def != NULL)
    _fingerprintChildNode(ctx, node->def, node, "def", depth);

  _fingerprintBoolField(ctx, "missing_ok", node->missing_ok);

  _fingerprintStringField(ctx, "name", node->name);

  _fingerprintCharField(ctx, "subtype", node->subtype);

  if (node->typeName != NULL && node->typeName->length > 0)
    _fingerprintChildList(ctx, node->typeName, node, "typeName", depth);

}

static void
_fingerprintGrantStmt(FingerprintContext *ctx, const GrantStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintEnumField(ctx, "behavior", _enumToStringDropBehavior(node->behavior));

  _fingerprintBoolField(ctx, "grant_option", node->grant_option);

  if (node->grantees != NULL && node->grantees->length > 0)
    _fingerprintChildList(ctx, node->grantees, node, "grantees", depth);

  if (node->grantor != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "grantor");
    _fingerprintRoleSpec(ctx, node->grantor, node, "grantor", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  _fingerprintBoolField(ctx, "is_grant", node->is_grant);

  if (node->objects != NULL && node->objects->length > 0)
    _fingerprintChildList(ctx, node->objects, node, "objects", depth);

  _fingerprintEnumField(ctx, "objtype", _enumToStringObjectType(node->objtype));

  if (node->privileges != NULL && node->privileges->length > 0)
    _fingerprintChildList(ctx, node->privileges, node, "privileges", depth);

  _fingerprintEnumField(ctx, "targtype", _enumToStringGrantTargetType(node->targtype));

}

static void
_fingerprintObjectWithArgs(FingerprintContext *ctx, const ObjectWithArgs *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintBoolField(ctx, "args_unspecified", node->args_unspecified);

  if (node->objargs != NULL && node->objargs->length > 0)
    _fingerprintChildList(ctx, node->objargs, node, "objargs", depth);

  if (node->objfuncargs != NULL && node->objfuncargs->length > 0)
    _fingerprintChildList(ctx, node->objfuncargs, node, "objfuncargs", depth);

  if (node->objname != NULL && node->objname->length > 0)
    _fingerprintChildList(ctx, node->objname, node, "objname", depth);

}

static void
_fingerprintAccessPriv(FingerprintContext *ctx, const AccessPriv *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->cols != NULL && node->cols->length > 0)
    _fingerprintChildList(ctx, node->cols, node, "cols", depth);

  _fingerprintStringField(ctx, "priv_name", node->priv_name);

}

static void
_fingerprintGrantRoleStmt(FingerprintContext *ctx, const GrantRoleStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintEnumField(ctx, "behavior", _enumToStringDropBehavior(node->behavior));

  if (node->granted_roles != NULL && node->granted_roles->length > 0)
    _fingerprintChildList(ctx, node->granted_roles, node, "granted_roles", depth);

  if (node->grantee_roles != NULL && node->grantee_roles->length > 0)
    _fingerprintChildList(ctx, node->grantee_roles, node, "grantee_roles", depth);

  if (node->grantor != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "grantor");
    _fingerprintRoleSpec(ctx, node->grantor, node, "grantor", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  _fingerprintBoolField(ctx, "is_grant", node->is_grant);

  if (node->opt != NULL && node->opt->length > 0)
    _fingerprintChildList(ctx, node->opt, node, "opt", depth);

}

static void
_fingerprintAlterDefaultPrivilegesStmt(FingerprintContext *ctx, const AlterDefaultPrivilegesStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->action != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "action");
    _fingerprintGrantStmt(ctx, node->action, node, "action", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  if (node->options != NULL && node->options->length > 0)
    _fingerprintChildList(ctx, node->options, node, "options", depth);

}

static void
_fingerprintCopyStmt(FingerprintContext *ctx, const CopyStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->attlist != NULL && node->attlist->length > 0)
    _fingerprintChildList(ctx, node->attlist, node, "attlist", depth);

  _fingerprintStringField(ctx, "filename", node->filename);

  _fingerprintBoolField(ctx, "is_from", node->is_from);

  _fingerprintBoolField(ctx, "is_program", node->is_program);

  if (node->options != NULL && node->options->length > 0)
    _fingerprintChildList(ctx, node->options, node, "options", depth);

  if (node->query != NULL)
    _fingerprintChildNode(ctx, node->query, node, "query", depth);

  if (node->relation != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "relation");
    _fingerprintRangeVar(ctx, node->relation, node, "relation", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  if (node->whereClause != NULL)
    _fingerprintChildNode(ctx, node->whereClause, node, "whereClause", depth);

}

static void
_fingerprintVariableSetStmt(FingerprintContext *ctx, const VariableSetStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->args != NULL && node->args->length > 0)
    _fingerprintChildList(ctx, node->args, node, "args", depth);

  _fingerprintBoolField(ctx, "is_local", node->is_local);

  // Intentionally ignoring node->jumble_args for fingerprinting

  _fingerprintEnumField(ctx, "kind", _enumToStringVariableSetKind(node->kind));

  // Intentionally ignoring node->location for fingerprinting

  _fingerprintStringField(ctx, "name", node->name);

}

static void
_fingerprintVariableShowStmt(FingerprintContext *ctx, const VariableShowStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintStringField(ctx, "name", node->name);

}

static void
_fingerprintCreateStmt(FingerprintContext *ctx, const CreateStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintStringField(ctx, "accessMethod", node->accessMethod);

  if (node->constraints != NULL && node->constraints->length > 0)
    _fingerprintChildList(ctx, node->constraints, node, "constraints", depth);

  _fingerprintBoolField(ctx, "if_not_exists", node->if_not_exists);

  if (node->inhRelations != NULL && node->inhRelations->length > 0)
    _fingerprintChildList(ctx, node->inhRelations, node, "inhRelations", depth);

  if (node->nnconstraints != NULL && node->nnconstraints->length > 0)
    _fingerprintChildList(ctx, node->nnconstraints, node, "nnconstraints", depth);

  if (node->ofTypename != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "ofTypename");
    _fingerprintTypeName(ctx, node->ofTypename, node, "ofTypename", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  _fingerprintEnumField(ctx, "oncommit", _enumToStringOnCommitAction(node->oncommit));

  if (node->options != NULL && node->options->length > 0)
    _fingerprintChildList(ctx, node->options, node, "options", depth);

  if (node->partbound != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "partbound");
    _fingerprintPartitionBoundSpec(ctx, node->partbound, node, "partbound", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  if (node->partspec != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "partspec");
    _fingerprintPartitionSpec(ctx, node->partspec, node, "partspec", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  if (node->relation != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "relation");
    _fingerprintRangeVar(ctx, node->relation, node, "relation", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  if (node->tableElts != NULL && node->tableElts->length > 0)
    _fingerprintChildList(ctx, node->tableElts, node, "tableElts", depth);

  _fingerprintStringField(ctx, "tablespacename", node->tablespacename);

}

static void
_fingerprintConstraint(FingerprintContext *ctx, const Constraint *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintStringField(ctx, "access_method", node->access_method);

  _fingerprintStringField(ctx, "conname", node->conname);

  _fingerprintEnumField(ctx, "contype", _enumToStringConstrType(node->contype));

  _fingerprintStringField(ctx, "cooked_expr", node->cooked_expr);

  _fingerprintBoolField(ctx, "deferrable", node->deferrable);

  if (node->exclusions != NULL && node->exclusions->length > 0)
    _fingerprintChildList(ctx, node->exclusions, node, "exclusions", depth);

  if (node->fk_attrs != NULL && node->fk_attrs->length > 0)
    _fingerprintChildList(ctx, node->fk_attrs, node, "fk_attrs", depth);

  _fingerprintCharField(ctx, "fk_del_action", node->fk_del_action);

  if (node->fk_del_set_cols != NULL && node->fk_del_set_cols->length > 0)
    _fingerprintChildList(ctx, node->fk_del_set_cols, node, "fk_del_set_cols", depth);

  _fingerprintCharField(ctx, "fk_matchtype", node->fk_matchtype);

  _fingerprintCharField(ctx, "fk_upd_action", node->fk_upd_action);

  _fingerprintBoolField(ctx, "fk_with_period", node->fk_with_period);

  _fingerprintCharField(ctx, "generated_kind", node->generated_kind);

  _fingerprintCharField(ctx, "generated_when", node->generated_when);

  if (node->including != NULL && node->including->length > 0)
    _fingerprintChildList(ctx, node->including, node, "including", depth);

  _fingerprintStringField(ctx, "indexname", node->indexname);

  _fingerprintStringField(ctx, "indexspace", node->indexspace);

  _fingerprintBoolField(ctx, "initdeferred", node->initdeferred);

  _fingerprintBoolField(ctx, "initially_valid", node->initially_valid);

  _fingerprintBoolField(ctx, "is_enforced", node->is_enforced);

  _fingerprintBoolField(ctx, "is_no_inherit", node->is_no_inherit);

  if (node->keys != NULL && node->keys->length > 0)
    _fingerprintChildList(ctx, node->keys, node, "keys", depth);

  // Intentionally ignoring node->location for fingerprinting

  _fingerprintBoolField(ctx, "nulls_not_distinct", node->nulls_not_distinct);

  if (node->old_conpfeqop != NULL && node->old_conpfeqop->length > 0)
    _fingerprintChildList(ctx, node->old_conpfeqop, node, "old_conpfeqop", depth);

  _fingerprintIntField(ctx, "old_pktable_oid", node->old_pktable_oid);

  if (node->options != NULL && node->options->length > 0)
    _fingerprintChildList(ctx, node->options, node, "options", depth);

  if (node->pk_attrs != NULL && node->pk_attrs->length > 0)
    _fingerprintChildList(ctx, node->pk_attrs, node, "pk_attrs", depth);

  _fingerprintBoolField(ctx, "pk_with_period", node->pk_with_period);

  if (node->pktable != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "pktable");
    _fingerprintRangeVar(ctx, node->pktable, node, "pktable", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  if (node->raw_expr != NULL)
    _fingerprintChildNode(ctx, node->raw_expr, node, "raw_expr", depth);

  _fingerprintBoolField(ctx, "reset_default_tblspc", node->reset_default_tblspc);

  _fingerprintBoolField(ctx, "skip_validation", node->skip_validation);

  if (node->where_clause != NULL)
    _fingerprintChildNode(ctx, node->where_clause, node, "where_clause", depth);

  _fingerprintBoolField(ctx, "without_overlaps", node->without_overlaps);

}

static void
_fingerprintCreateTableSpaceStmt(FingerprintContext *ctx, const CreateTableSpaceStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  // Intentionally ignoring node->location for fingerprinting

  if (node->options != NULL && node->options->length > 0)
    _fingerprintChildList(ctx, node->options, node, "options", depth);

  if (node->owner != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "owner");
    _fingerprintRoleSpec(ctx, node->owner, node, "owner", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  _fingerprintStringField(ctx, "tablespacename", node->tablespacename);

}

static void
_fingerprintDropTableSpaceStmt(FingerprintContext *ctx, const DropTableSpaceStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintBoolField(ctx, "missing_ok", node->missing_ok);

  _fingerprintStringField(ctx, "tablespacename", node->tablespacename);

}

static void
_fingerprintAlterTableSpaceOptionsStmt(FingerprintContext *ctx, const AlterTableSpaceOptionsStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintBoolField(ctx, "isReset", node->isReset);

  if (node->options != NULL && node->options->length > 0)
    _fingerprintChildList(ctx, node->options, node, "options", depth);

  _fingerprintStringField(ctx, "tablespacename", node->tablespacename);

}

static void
_fingerprintAlterTableMoveAllStmt(FingerprintContext *ctx, const AlterTableMoveAllStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintStringField(ctx, "new_tablespacename", node->new_tablespacename);

  _fingerprintBoolField(ctx, "nowait", node->nowait);

  _fingerprintEnumField(ctx, "objtype", _enumToStringObjectType(node->objtype));

  _fingerprintStringField(ctx, "orig_tablespacename", node->orig_tablespacename);

  if (node->roles != NULL && node->roles->length > 0)
    _fingerprintChildList(ctx, node->roles, node, "roles", depth);

}

static void
_fingerprintCreateExtensionStmt(FingerprintContext *ctx, const CreateExtensionStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintStringField(ctx, "extname", node->extname);

  _fingerprintBoolField(ctx, "if_not_exists", node->if_not_exists);

  if (node->options != NULL && node->options->length > 0)
    _fingerprintChildList(ctx, node->options, node, "options", depth);

}

static void
_fingerprintAlterExtensionStmt(FingerprintContext *ctx, const AlterExtensionStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintStringField(ctx, "extname", node->extname);

  if (node->options != NULL && node->options->length > 0)
    _fingerprintChildList(ctx, node->options, node, "options", depth);

}

static void
_fingerprintAlterExtensionContentsStmt(FingerprintContext *ctx, const AlterExtensionContentsStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintIntField(ctx, "action", node->action);

  _fingerprintStringField(ctx, "extname", node->extname);

  if (node->object != NULL)
    _fingerprintChildNode(ctx, node->object, node, "object", depth);

  _fingerprintEnumField(ctx, "objtype", _enumToStringObjectType(node->objtype));

}

static void
_fingerprintCreateFdwStmt(FingerprintContext *ctx, const CreateFdwStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintStringField(ctx, "fdwname", node->fdwname);

  if (node->func_options != NULL && node->func_options->length > 0)
    _fingerprintChildList(ctx, node->func_options, node, "func_options", depth);

  if (node->options != NULL && node->options->length > 0)
    _fingerprintChildList(ctx, node->options, node, "options", depth);

}

static void
_fingerprintAlterFdwStmt(FingerprintContext *ctx, const AlterFdwStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintStringField(ctx, "fdwname", node->fdwname);

  if (node->func_options != NULL && node->func_options->length > 0)
    _fingerprintChildList(ctx, node->func_options, node, "func_options", depth);

  if (node->options != NULL && node->options->length > 0)
    _fingerprintChildList(ctx, node->options, node, "options", depth);

}

static void
_fingerprintCreateForeignServerStmt(FingerprintContext *ctx, const CreateForeignServerStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintStringField(ctx, "fdwname", node->fdwname);

  _fingerprintBoolField(ctx, "if_not_exists", node->if_not_exists);

  if (node->options != NULL && node->options->length > 0)
    _fingerprintChildList(ctx, node->options, node, "options", depth);

  _fingerprintStringField(ctx, "servername", node->servername);

  _fingerprintStringField(ctx, "servertype", node->servertype);

  _fingerprintStringField(ctx, "version", node->version);

}

static void
_fingerprintAlterForeignServerStmt(FingerprintContext *ctx, const AlterForeignServerStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintBoolField(ctx, "has_version", node->has_version);

  if (node->options != NULL && node->options->length > 0)
    _fingerprintChildList(ctx, node->options, node, "options", depth);

  _fingerprintStringField(ctx, "servername", node->servername);

  _fingerprintStringField(ctx, "version", node->version);

}

static void
_fingerprintCreateForeignTableStmt(FingerprintContext *ctx, const CreateForeignTableStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintString(ctx, "base");
  _fingerprintCreateStmt(ctx, (const CreateStmt*) &node->base, node, "base", depth);
  if (node->options != NULL && node->options->length > 0)
    _fingerprintChildList(ctx, node->options, node, "options", depth);

  _fingerprintStringField(ctx, "servername", node->servername);

}

static void
_fingerprintCreateUserMappingStmt(FingerprintContext *ctx, const CreateUserMappingStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintBoolField(ctx, "if_not_exists", node->if_not_exists);

  if (node->options != NULL && node->options->length > 0)
    _fingerprintChildList(ctx, node->options, node, "options", depth);

  _fingerprintStringField(ctx, "servername", node->servername);

  if (node->user != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "user");
    _fingerprintRoleSpec(ctx, node->user, node, "user", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

}

static void
_fingerprintAlterUserMappingStmt(FingerprintContext *ctx, const AlterUserMappingStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->options != NULL && node->options->length > 0)
    _fingerprintChildList(ctx, node->options, node, "options", depth);

  _fingerprintStringField(ctx, "servername", node->servername);

  if (node->user != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "user");
    _fingerprintRoleSpec(ctx, node->user, node, "user", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

}

static void
_fingerprintDropUserMappingStmt(FingerprintContext *ctx, const DropUserMappingStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintBoolField(ctx, "missing_ok", node->missing_ok);

  _fingerprintStringField(ctx, "servername", node->servername);

  if (node->user != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "user");
    _fingerprintRoleSpec(ctx, node->user, node, "user", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

}

static void
_fingerprintImportForeignSchemaStmt(FingerprintContext *ctx, const ImportForeignSchemaStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintEnumField(ctx, "list_type", _enumToStringImportForeignSchemaType(node->list_type));

  _fingerprintStringField(ctx, "local_schema", node->local_schema);

  if (node->options != NULL && node->options->length > 0)
    _fingerprintChildList(ctx, node->options, node, "options", depth);

  _fingerprintStringField(ctx, "remote_schema", node->remote_schema);

  _fingerprintStringField(ctx, "server_name", node->server_name);

  if (node->table_list != NULL && node->table_list->length > 0)
    _fingerprintChildList(ctx, node->table_list, node, "table_list", depth);

}

static void
_fingerprintCreatePolicyStmt(FingerprintContext *ctx, const CreatePolicyStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintStringField(ctx, "cmd_name", node->cmd_name);

  _fingerprintBoolField(ctx, "permissive", node->permissive);

  _fingerprintStringField(ctx, "policy_name", node->policy_name);

  if (node->qual != NULL)
    _fingerprintChildNode(ctx, node->qual, node, "qual", depth);

  if (node->roles != NULL && node->roles->length > 0)
    _fingerprintChildList(ctx, node->roles, node, "roles", depth);

  if (node->table != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "table");
    _fingerprintRangeVar(ctx, node->table, node, "table", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  if (node->with_check != NULL)
    _fingerprintChildNode(ctx, node->with_check, node, "with_check", depth);

}

static void
_fingerprintAlterPolicyStmt(FingerprintContext *ctx, const AlterPolicyStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintStringField(ctx, "policy_name", node->policy_name);

  if (node->qual != NULL)
    _fingerprintChildNode(ctx, node->qual, node, "qual", depth);

  if (node->roles != NULL && node->roles->length > 0)
    _fingerprintChildList(ctx, node->roles, node, "roles", depth);

  if (node->table != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "table");
    _fingerprintRangeVar(ctx, node->table, node, "table", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  if (node->with_check != NULL)
    _fingerprintChildNode(ctx, node->with_check, node, "with_check", depth);

}

static void
_fingerprintCreateAmStmt(FingerprintContext *ctx, const CreateAmStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintStringField(ctx, "amname", node->amname);

  _fingerprintCharField(ctx, "amtype", node->amtype);

  if (node->handler_name != NULL && node->handler_name->length > 0)
    _fingerprintChildList(ctx, node->handler_name, node, "handler_name", depth);

}

static void
_fingerprintCreateTrigStmt(FingerprintContext *ctx, const CreateTrigStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->args != NULL && node->args->length > 0)
    _fingerprintChildList(ctx, node->args, node, "args", depth);

  if (node->columns != NULL && node->columns->length > 0)
    _fingerprintChildList(ctx, node->columns, node, "columns", depth);

  if (node->constrrel != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "constrrel");
    _fingerprintRangeVar(ctx, node->constrrel, node, "constrrel", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  _fingerprintBoolField(ctx, "deferrable", node->deferrable);

  _fingerprintIntField(ctx, "events", node->events);

  if (node->funcname != NULL && node->funcname->length > 0)
    _fingerprintChildList(ctx, node->funcname, node, "funcname", depth);

  _fingerprintBoolField(ctx, "initdeferred", node->initdeferred);

  _fingerprintBoolField(ctx, "isconstraint", node->isconstraint);

  if (node->relation != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "relation");
    _fingerprintRangeVar(ctx, node->relation, node, "relation", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  _fingerprintBoolField(ctx, "replace", node->replace);

  _fingerprintBoolField(ctx, "row", node->row);

  _fingerprintIntField(ctx, "timing", node->timing);

  if (node->transitionRels != NULL && node->transitionRels->length > 0)
    _fingerprintChildList(ctx, node->transitionRels, node, "transitionRels", depth);

  _fingerprintStringField(ctx, "trigname", node->trigname);

  if (node->whenClause != NULL)
    _fingerprintChildNode(ctx, node->whenClause, node, "whenClause", depth);

}

static void
_fingerprintCreateEventTrigStmt(FingerprintContext *ctx, const CreateEventTrigStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintStringField(ctx, "eventname", node->eventname);

  if (node->funcname != NULL && node->funcname->length > 0)
    _fingerprintChildList(ctx, node->funcname, node, "funcname", depth);

  _fingerprintStringField(ctx, "trigname", node->trigname);

  if (node->whenclause != NULL && node->whenclause->length > 0)
    _fingerprintChildList(ctx, node->whenclause, node, "whenclause", depth);

}

static void
_fingerprintAlterEventTrigStmt(FingerprintContext *ctx, const AlterEventTrigStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintCharField(ctx, "tgenabled", node->tgenabled);

  _fingerprintStringField(ctx, "trigname", node->trigname);

}

static void
_fingerprintCreatePLangStmt(FingerprintContext *ctx, const CreatePLangStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->plhandler != NULL && node->plhandler->length > 0)
    _fingerprintChildList(ctx, node->plhandler, node, "plhandler", depth);

  if (node->plinline != NULL && node->plinline->length > 0)
    _fingerprintChildList(ctx, node->plinline, node, "plinline", depth);

  _fingerprintStringField(ctx, "plname", node->plname);

  _fingerprintBoolField(ctx, "pltrusted", node->pltrusted);

  if (node->plvalidator != NULL && node->plvalidator->length > 0)
    _fingerprintChildList(ctx, node->plvalidator, node, "plvalidator", depth);

  _fingerprintBoolField(ctx, "replace", node->replace);

}

static void
_fingerprintCreateRoleStmt(FingerprintContext *ctx, const CreateRoleStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->options != NULL && node->options->length > 0)
    _fingerprintChildList(ctx, node->options, node, "options", depth);

  _fingerprintStringField(ctx, "role", node->role);

  _fingerprintEnumField(ctx, "stmt_type", _enumToStringRoleStmtType(node->stmt_type));

}

static void
_fingerprintAlterRoleStmt(FingerprintContext *ctx, const AlterRoleStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintIntField(ctx, "action", node->action);

  if (node->options != NULL && node->options->length > 0)
    _fingerprintChildList(ctx, node->options, node, "options", depth);

  if (node->role != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "role");
    _fingerprintRoleSpec(ctx, node->role, node, "role", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

}

static void
_fingerprintAlterRoleSetStmt(FingerprintContext *ctx, const AlterRoleSetStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintStringField(ctx, "database", node->database);

  if (node->role != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "role");
    _fingerprintRoleSpec(ctx, node->role, node, "role", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  if (node->setstmt != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "setstmt");
    _fingerprintVariableSetStmt(ctx, node->setstmt, node, "setstmt", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

}

static void
_fingerprintDropRoleStmt(FingerprintContext *ctx, const DropRoleStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintBoolField(ctx, "missing_ok", node->missing_ok);

  if (node->roles != NULL && node->roles->length > 0)
    _fingerprintChildList(ctx, node->roles, node, "roles", depth);

}

static void
_fingerprintCreateSeqStmt(FingerprintContext *ctx, const CreateSeqStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintBoolField(ctx, "for_identity", node->for_identity);

  _fingerprintBoolField(ctx, "if_not_exists", node->if_not_exists);

  if (node->options != NULL && node->options->length > 0)
    _fingerprintChildList(ctx, node->options, node, "options", depth);

  _fingerprintIntField(ctx, "ownerId", node->ownerId);

  if (node->sequence != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "sequence");
    _fingerprintRangeVar(ctx, node->sequence, node, "sequence", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

}

static void
_fingerprintAlterSeqStmt(FingerprintContext *ctx, const AlterSeqStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintBoolField(ctx, "for_identity", node->for_identity);

  _fingerprintBoolField(ctx, "missing_ok", node->missing_ok);

  if (node->options != NULL && node->options->length > 0)
    _fingerprintChildList(ctx, node->options, node, "options", depth);

  if (node->sequence != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "sequence");
    _fingerprintRangeVar(ctx, node->sequence, node, "sequence", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

}

static void
_fingerprintDefineStmt(FingerprintContext *ctx, const DefineStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->args != NULL && node->args->length > 0)
    _fingerprintChildList(ctx, node->args, node, "args", depth);

  if (node->definition != NULL && node->definition->length > 0)
    _fingerprintChildList(ctx, node->definition, node, "definition", depth);

  if (node->defnames != NULL && node->defnames->length > 0)
    _fingerprintChildList(ctx, node->defnames, node, "defnames", depth);

  _fingerprintBoolField(ctx, "if_not_exists", node->if_not_exists);

  _fingerprintEnumField(ctx, "kind", _enumToStringObjectType(node->kind));

  _fingerprintBoolField(ctx, "oldstyle", node->oldstyle);

  _fingerprintBoolField(ctx, "replace", node->replace);

}

static void
_fingerprintCreateDomainStmt(FingerprintContext *ctx, const CreateDomainStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->collClause != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "collClause");
    _fingerprintCollateClause(ctx, node->collClause, node, "collClause", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  if (node->constraints != NULL && node->constraints->length > 0)
    _fingerprintChildList(ctx, node->constraints, node, "constraints", depth);

  if (node->domainname != NULL && node->domainname->length > 0)
    _fingerprintChildList(ctx, node->domainname, node, "domainname", depth);

  if (node->typeName != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "typeName");
    _fingerprintTypeName(ctx, node->typeName, node, "typeName", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

}

static void
_fingerprintCreateOpClassStmt(FingerprintContext *ctx, const CreateOpClassStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintStringField(ctx, "amname", node->amname);

  if (node->datatype != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "datatype");
    _fingerprintTypeName(ctx, node->datatype, node, "datatype", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  _fingerprintBoolField(ctx, "isDefault", node->isDefault);

  if (node->items != NULL && node->items->length > 0)
    _fingerprintChildList(ctx, node->items, node, "items", depth);

  if (node->opclassname != NULL && node->opclassname->length > 0)
    _fingerprintChildList(ctx, node->opclassname, node, "opclassname", depth);

  if (node->opfamilyname != NULL && node->opfamilyname->length > 0)
    _fingerprintChildList(ctx, node->opfamilyname, node, "opfamilyname", depth);

}

static void
_fingerprintCreateOpClassItem(FingerprintContext *ctx, const CreateOpClassItem *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->class_args != NULL && node->class_args->length > 0)
    _fingerprintChildList(ctx, node->class_args, node, "class_args", depth);

  _fingerprintIntField(ctx, "itemtype", node->itemtype);

  if (node->name != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "name");
    _fingerprintObjectWithArgs(ctx, node->name, node, "name", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  _fingerprintIntField(ctx, "number", node->number);

  if (node->order_family != NULL && node->order_family->length > 0)
    _fingerprintChildList(ctx, node->order_family, node, "order_family", depth);

  if (node->storedtype != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "storedtype");
    _fingerprintTypeName(ctx, node->storedtype, node, "storedtype", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

}

static void
_fingerprintCreateOpFamilyStmt(FingerprintContext *ctx, const CreateOpFamilyStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintStringField(ctx, "amname", node->amname);

  if (node->opfamilyname != NULL && node->opfamilyname->length > 0)
    _fingerprintChildList(ctx, node->opfamilyname, node, "opfamilyname", depth);

}

static void
_fingerprintAlterOpFamilyStmt(FingerprintContext *ctx, const AlterOpFamilyStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintStringField(ctx, "amname", node->amname);

  _fingerprintBoolField(ctx, "isDrop", node->isDrop);

  if (node->items != NULL && node->items->length > 0)
    _fingerprintChildList(ctx, node->items, node, "items", depth);

  if (node->opfamilyname != NULL && node->opfamilyname->length > 0)
    _fingerprintChildList(ctx, node->opfamilyname, node, "opfamilyname", depth);

}

static void
_fingerprintDropStmt(FingerprintContext *ctx, const DropStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintEnumField(ctx, "behavior", _enumToStringDropBehavior(node->behavior));

  _fingerprintBoolField(ctx, "concurrent", node->concurrent);

  _fingerprintBoolField(ctx, "missing_ok", node->missing_ok);

  if (node->objects != NULL && node->objects->length > 0)
    _fingerprintChildList(ctx, node->objects, node, "objects", depth);

  _fingerprintEnumField(ctx, "removeType", _enumToStringObjectType(node->removeType));

}

static void
_fingerprintTruncateStmt(FingerprintContext *ctx, const TruncateStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintEnumField(ctx, "behavior", _enumToStringDropBehavior(node->behavior));

  if (node->relations != NULL && node->relations->length > 0)
    _fingerprintChildList(ctx, node->relations, node, "relations", depth);

  _fingerprintBoolField(ctx, "restart_seqs", node->restart_seqs);

}

static void
_fingerprintCommentStmt(FingerprintContext *ctx, const CommentStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintStringField(ctx, "comment", node->comment);

  if (node->object != NULL)
    _fingerprintChildNode(ctx, node->object, node, "object", depth);

  _fingerprintEnumField(ctx, "objtype", _enumToStringObjectType(node->objtype));

}

static void
_fingerprintSecLabelStmt(FingerprintContext *ctx, const SecLabelStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintStringField(ctx, "label", node->label);

  if (node->object != NULL)
    _fingerprintChildNode(ctx, node->object, node, "object", depth);

  _fingerprintEnumField(ctx, "objtype", _enumToStringObjectType(node->objtype));

  _fingerprintStringField(ctx, "provider", node->provider);

}

static void
_fingerprintDeclareCursorStmt(FingerprintContext *ctx, const DeclareCursorStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintIntField(ctx, "options", node->options);

  // Intentionally ignoring node->portalname for fingerprinting

  if (node->query != NULL)
    _fingerprintChildNode(ctx, node->query, node, "query", depth);

}

static void
_fingerprintClosePortalStmt(FingerprintContext *ctx, const ClosePortalStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  // Intentionally ignoring node->portalname for fingerprinting

}

static void
_fingerprintFetchStmt(FingerprintContext *ctx, const FetchStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintEnumField(ctx, "direction", _enumToStringFetchDirection(node->direction));

  _fingerprintLongField(ctx, "howMany", node->howMany);

  _fingerprintBoolField(ctx, "ismove", node->ismove);

  // Intentionally ignoring node->portalname for fingerprinting

}

static void
_fingerprintIndexStmt(FingerprintContext *ctx, const IndexStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintStringField(ctx, "accessMethod", node->accessMethod);

  _fingerprintBoolField(ctx, "concurrent", node->concurrent);

  _fingerprintBoolField(ctx, "deferrable", node->deferrable);

  if (node->excludeOpNames != NULL && node->excludeOpNames->length > 0)
    _fingerprintChildList(ctx, node->excludeOpNames, node, "excludeOpNames", depth);

  _fingerprintStringField(ctx, "idxcomment", node->idxcomment);

  _fingerprintStringField(ctx, "idxname", node->idxname);

  _fingerprintBoolField(ctx, "if_not_exists", node->if_not_exists);

  if (node->indexIncludingParams != NULL && node->indexIncludingParams->length > 0)
    _fingerprintChildList(ctx, node->indexIncludingParams, node, "indexIncludingParams", depth);

  _fingerprintIntField(ctx, "indexOid", node->indexOid);

  if (node->indexParams != NULL && node->indexParams->length > 0)
    _fingerprintChildList(ctx, node->indexParams, node, "indexParams", depth);

  _fingerprintBoolField(ctx, "initdeferred", node->initdeferred);

  _fingerprintBoolField(ctx, "isconstraint", node->isconstraint);

  _fingerprintBoolField(ctx, "iswithoutoverlaps", node->iswithoutoverlaps);

  _fingerprintBoolField(ctx, "nulls_not_distinct", node->nulls_not_distinct);

  _fingerprintIntField(ctx, "oldCreateSubid", node->oldCreateSubid);

  _fingerprintIntField(ctx, "oldFirstRelfilelocatorSubid", node->oldFirstRelfilelocatorSubid);

  _fingerprintIntField(ctx, "oldNumber", node->oldNumber);

  if (node->options != NULL && node->options->length > 0)
    _fingerprintChildList(ctx, node->options, node, "options", depth);

  _fingerprintBoolField(ctx, "primary", node->primary);

  if (node->relation != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "relation");
    _fingerprintRangeVar(ctx, node->relation, node, "relation", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  _fingerprintBoolField(ctx, "reset_default_tblspc", node->reset_default_tblspc);

  _fingerprintStringField(ctx, "tableSpace", node->tableSpace);

  _fingerprintBoolField(ctx, "transformed", node->transformed);

  _fingerprintBoolField(ctx, "unique", node->unique);

  if (node->whereClause != NULL)
    _fingerprintChildNode(ctx, node->whereClause, node, "whereClause", depth);

}

static void
_fingerprintCreateStatsStmt(FingerprintContext *ctx, const CreateStatsStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->defnames != NULL && node->defnames->length > 0)
    _fingerprintChildList(ctx, node->defnames, node, "defnames", depth);

  if (node->exprs != NULL && node->exprs->length > 0)
    _fingerprintChildList(ctx, node->exprs, node, "exprs", depth);

  _fingerprintBoolField(ctx, "if_not_exists", node->if_not_exists);

  if (node->relations != NULL && node->relations->length > 0)
    _fingerprintChildList(ctx, node->relations, node, "relations", depth);

  if (node->stat_types != NULL && node->stat_types->length > 0)
    _fingerprintChildList(ctx, node->stat_types, node, "stat_types", depth);

  _fingerprintStringField(ctx, "stxcomment", node->stxcomment);

  _fingerprintBoolField(ctx, "transformed", node->transformed);

}

static void
_fingerprintStatsElem(FingerprintContext *ctx, const StatsElem *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->expr != NULL)
    _fingerprintChildNode(ctx, node->expr, node, "expr", depth);

  _fingerprintStringField(ctx, "name", node->name);

}

static void
_fingerprintAlterStatsStmt(FingerprintContext *ctx, const AlterStatsStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->defnames != NULL && node->defnames->length > 0)
    _fingerprintChildList(ctx, node->defnames, node, "defnames", depth);

  _fingerprintBoolField(ctx, "missing_ok", node->missing_ok);

  if (node->stxstattarget != NULL)
    _fingerprintChildNode(ctx, node->stxstattarget, node, "stxstattarget", depth);

}

static void
_fingerprintCreateFunctionStmt(FingerprintContext *ctx, const CreateFunctionStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->funcname != NULL && node->funcname->length > 0)
    _fingerprintChildList(ctx, node->funcname, node, "funcname", depth);

  _fingerprintBoolField(ctx, "is_procedure", node->is_procedure);

  // Intentionally ignoring node->options for fingerprinting

  if (node->parameters != NULL && node->parameters->length > 0)
    _fingerprintChildList(ctx, node->parameters, node, "parameters", depth);

  _fingerprintBoolField(ctx, "replace", node->replace);

  if (node->returnType != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "returnType");
    _fingerprintTypeName(ctx, node->returnType, node, "returnType", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  if (node->sql_body != NULL)
    _fingerprintChildNode(ctx, node->sql_body, node, "sql_body", depth);

}

static void
_fingerprintFunctionParameter(FingerprintContext *ctx, const FunctionParameter *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->argType != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "argType");
    _fingerprintTypeName(ctx, node->argType, node, "argType", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  if (node->defexpr != NULL)
    _fingerprintChildNode(ctx, node->defexpr, node, "defexpr", depth);

  // Intentionally ignoring node->location for fingerprinting

  _fingerprintEnumField(ctx, "mode", _enumToStringFunctionParameterMode(node->mode));

  // Intentionally ignoring node->name for fingerprinting

}

static void
_fingerprintAlterFunctionStmt(FingerprintContext *ctx, const AlterFunctionStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->actions != NULL && node->actions->length > 0)
    _fingerprintChildList(ctx, node->actions, node, "actions", depth);

  if (node->func != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "func");
    _fingerprintObjectWithArgs(ctx, node->func, node, "func", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  _fingerprintEnumField(ctx, "objtype", _enumToStringObjectType(node->objtype));

}

static void
_fingerprintDoStmt(FingerprintContext *ctx, const DoStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  // Intentionally ignoring node->args for fingerprinting

}

static void
_fingerprintInlineCodeBlock(FingerprintContext *ctx, const InlineCodeBlock *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintBoolField(ctx, "atomic", node->atomic);

  _fingerprintBoolField(ctx, "langIsTrusted", node->langIsTrusted);

  _fingerprintIntField(ctx, "langOid", node->langOid);

  _fingerprintStringField(ctx, "source_text", node->source_text);

}

static void
_fingerprintCallStmt(FingerprintContext *ctx, const CallStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->funccall != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "funccall");
    _fingerprintFuncCall(ctx, node->funccall, node, "funccall", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  if (node->funcexpr != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "funcexpr");
    _fingerprintFuncExpr(ctx, node->funcexpr, node, "funcexpr", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  if (node->outargs != NULL && node->outargs->length > 0)
    _fingerprintChildList(ctx, node->outargs, node, "outargs", depth);

}

static void
_fingerprintCallContext(FingerprintContext *ctx, const CallContext *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintBoolField(ctx, "atomic", node->atomic);

}

static void
_fingerprintRenameStmt(FingerprintContext *ctx, const RenameStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintEnumField(ctx, "behavior", _enumToStringDropBehavior(node->behavior));

  _fingerprintBoolField(ctx, "missing_ok", node->missing_ok);

  _fingerprintStringField(ctx, "newname", node->newname);

  if (node->object != NULL)
    _fingerprintChildNode(ctx, node->object, node, "object", depth);

  if (node->relation != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "relation");
    _fingerprintRangeVar(ctx, node->relation, node, "relation", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  _fingerprintEnumField(ctx, "relationType", _enumToStringObjectType(node->relationType));

  _fingerprintEnumField(ctx, "renameType", _enumToStringObjectType(node->renameType));

  _fingerprintStringField(ctx, "subname", node->subname);

}

static void
_fingerprintAlterObjectDependsStmt(FingerprintContext *ctx, const AlterObjectDependsStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintStringNodeField(ctx, "extname", node->extname);

  if (node->object != NULL)
    _fingerprintChildNode(ctx, node->object, node, "object", depth);

  _fingerprintEnumField(ctx, "objectType", _enumToStringObjectType(node->objectType));

  if (node->relation != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "relation");
    _fingerprintRangeVar(ctx, node->relation, node, "relation", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  _fingerprintBoolField(ctx, "remove", node->remove);

}

static void
_fingerprintAlterObjectSchemaStmt(FingerprintContext *ctx, const AlterObjectSchemaStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintBoolField(ctx, "missing_ok", node->missing_ok);

  _fingerprintStringField(ctx, "newschema", node->newschema);

  if (node->object != NULL)
    _fingerprintChildNode(ctx, node->object, node, "object", depth);

  _fingerprintEnumField(ctx, "objectType", _enumToStringObjectType(node->objectType));

  if (node->relation != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "relation");
    _fingerprintRangeVar(ctx, node->relation, node, "relation", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

}

static void
_fingerprintAlterOwnerStmt(FingerprintContext *ctx, const AlterOwnerStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->newowner != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "newowner");
    _fingerprintRoleSpec(ctx, node->newowner, node, "newowner", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  if (node->object != NULL)
    _fingerprintChildNode(ctx, node->object, node, "object", depth);

  _fingerprintEnumField(ctx, "objectType", _enumToStringObjectType(node->objectType));

  if (node->relation != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "relation");
    _fingerprintRangeVar(ctx, node->relation, node, "relation", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

}

static void
_fingerprintAlterOperatorStmt(FingerprintContext *ctx, const AlterOperatorStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->opername != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "opername");
    _fingerprintObjectWithArgs(ctx, node->opername, node, "opername", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  if (node->options != NULL && node->options->length > 0)
    _fingerprintChildList(ctx, node->options, node, "options", depth);

}

static void
_fingerprintAlterTypeStmt(FingerprintContext *ctx, const AlterTypeStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->options != NULL && node->options->length > 0)
    _fingerprintChildList(ctx, node->options, node, "options", depth);

  if (node->typeName != NULL && node->typeName->length > 0)
    _fingerprintChildList(ctx, node->typeName, node, "typeName", depth);

}

static void
_fingerprintRuleStmt(FingerprintContext *ctx, const RuleStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->actions != NULL && node->actions->length > 0)
    _fingerprintChildList(ctx, node->actions, node, "actions", depth);

  _fingerprintEnumField(ctx, "event", _enumToStringCmdType(node->event));

  _fingerprintBoolField(ctx, "instead", node->instead);

  if (node->relation != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "relation");
    _fingerprintRangeVar(ctx, node->relation, node, "relation", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  _fingerprintBoolField(ctx, "replace", node->replace);

  _fingerprintStringField(ctx, "rulename", node->rulename);

  if (node->whereClause != NULL)
    _fingerprintChildNode(ctx, node->whereClause, node, "whereClause", depth);

}

static void
_fingerprintNotifyStmt(FingerprintContext *ctx, const NotifyStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  // Intentionally ignoring node->conditionname for fingerprinting

  // Intentionally ignoring node->payload for fingerprinting

}

static void
_fingerprintListenStmt(FingerprintContext *ctx, const ListenStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  // Intentionally ignoring node->conditionname for fingerprinting

}

static void
_fingerprintUnlistenStmt(FingerprintContext *ctx, const UnlistenStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  // Intentionally ignoring node->conditionname for fingerprinting

}

static void
_fingerprintTransactionStmt(FingerprintContext *ctx, const TransactionStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintBoolField(ctx, "chain", node->chain);

  // Intentionally ignoring node->gid for fingerprinting

  _fingerprintEnumField(ctx, "kind", _enumToStringTransactionStmtKind(node->kind));

  // Intentionally ignoring node->location for fingerprinting

  // Intentionally ignoring node->options for fingerprinting

  // Intentionally ignoring node->savepoint_name for fingerprinting

}

static void
_fingerprintCompositeTypeStmt(FingerprintContext *ctx, const CompositeTypeStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->coldeflist != NULL && node->coldeflist->length > 0)
    _fingerprintChildList(ctx, node->coldeflist, node, "coldeflist", depth);

  if (node->typevar != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "typevar");
    _fingerprintRangeVar(ctx, node->typevar, node, "typevar", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

}

static void
_fingerprintCreateEnumStmt(FingerprintContext *ctx, const CreateEnumStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->typeName != NULL && node->typeName->length > 0)
    _fingerprintChildList(ctx, node->typeName, node, "typeName", depth);

  if (node->vals != NULL && node->vals->length > 0)
    _fingerprintChildList(ctx, node->vals, node, "vals", depth);

}

static void
_fingerprintCreateRangeStmt(FingerprintContext *ctx, const CreateRangeStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->params != NULL && node->params->length > 0)
    _fingerprintChildList(ctx, node->params, node, "params", depth);

  if (node->typeName != NULL && node->typeName->length > 0)
    _fingerprintChildList(ctx, node->typeName, node, "typeName", depth);

}

static void
_fingerprintAlterEnumStmt(FingerprintContext *ctx, const AlterEnumStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintStringField(ctx, "newVal", node->newVal);

  _fingerprintBoolField(ctx, "newValIsAfter", node->newValIsAfter);

  _fingerprintStringField(ctx, "newValNeighbor", node->newValNeighbor);

  _fingerprintStringField(ctx, "oldVal", node->oldVal);

  _fingerprintBoolField(ctx, "skipIfNewValExists", node->skipIfNewValExists);

  if (node->typeName != NULL && node->typeName->length > 0)
    _fingerprintChildList(ctx, node->typeName, node, "typeName", depth);

}

static void
_fingerprintViewStmt(FingerprintContext *ctx, const ViewStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->aliases != NULL && node->aliases->length > 0)
    _fingerprintChildList(ctx, node->aliases, node, "aliases", depth);

  if (node->options != NULL && node->options->length > 0)
    _fingerprintChildList(ctx, node->options, node, "options", depth);

  if (node->query != NULL)
    _fingerprintChildNode(ctx, node->query, node, "query", depth);

  _fingerprintBoolField(ctx, "replace", node->replace);

  if (node->view != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "view");
    _fingerprintRangeVar(ctx, node->view, node, "view", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  _fingerprintEnumField(ctx, "withCheckOption", _enumToStringViewCheckOption(node->withCheckOption));

}

static void
_fingerprintLoadStmt(FingerprintContext *ctx, const LoadStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintStringField(ctx, "filename", node->filename);

}

static void
_fingerprintCreatedbStmt(FingerprintContext *ctx, const CreatedbStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintStringField(ctx, "dbname", node->dbname);

  if (node->options != NULL && node->options->length > 0)
    _fingerprintChildList(ctx, node->options, node, "options", depth);

}

static void
_fingerprintAlterDatabaseStmt(FingerprintContext *ctx, const AlterDatabaseStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintStringField(ctx, "dbname", node->dbname);

  if (node->options != NULL && node->options->length > 0)
    _fingerprintChildList(ctx, node->options, node, "options", depth);

}

static void
_fingerprintAlterDatabaseRefreshCollStmt(FingerprintContext *ctx, const AlterDatabaseRefreshCollStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintStringField(ctx, "dbname", node->dbname);

}

static void
_fingerprintAlterDatabaseSetStmt(FingerprintContext *ctx, const AlterDatabaseSetStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintStringField(ctx, "dbname", node->dbname);

  if (node->setstmt != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "setstmt");
    _fingerprintVariableSetStmt(ctx, node->setstmt, node, "setstmt", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

}

static void
_fingerprintDropdbStmt(FingerprintContext *ctx, const DropdbStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintStringField(ctx, "dbname", node->dbname);

  _fingerprintBoolField(ctx, "missing_ok", node->missing_ok);

  if (node->options != NULL && node->options->length > 0)
    _fingerprintChildList(ctx, node->options, node, "options", depth);

}

static void
_fingerprintAlterSystemStmt(FingerprintContext *ctx, const AlterSystemStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->setstmt != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "setstmt");
    _fingerprintVariableSetStmt(ctx, node->setstmt, node, "setstmt", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

}

static void
_fingerprintClusterStmt(FingerprintContext *ctx, const ClusterStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintStringField(ctx, "indexname", node->indexname);

  if (node->params != NULL && node->params->length > 0)
    _fingerprintChildList(ctx, node->params, node, "params", depth);

  if (node->relation != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "relation");
    _fingerprintRangeVar(ctx, node->relation, node, "relation", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

}

static void
_fingerprintVacuumStmt(FingerprintContext *ctx, const VacuumStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintBoolField(ctx, "is_vacuumcmd", node->is_vacuumcmd);

  if (node->options != NULL && node->options->length > 0)
    _fingerprintChildList(ctx, node->options, node, "options", depth);

  if (node->rels != NULL && node->rels->length > 0)
    _fingerprintChildList(ctx, node->rels, node, "rels", depth);

}

static void
_fingerprintVacuumRelation(FingerprintContext *ctx, const VacuumRelation *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintIntField(ctx, "oid", node->oid);

  if (node->relation != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "relation");
    _fingerprintRangeVar(ctx, node->relation, node, "relation", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  if (node->va_cols != NULL && node->va_cols->length > 0)
    _fingerprintChildList(ctx, node->va_cols, node, "va_cols", depth);

}

static void
_fingerprintExplainStmt(FingerprintContext *ctx, const ExplainStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->options != NULL && node->options->length > 0)
    _fingerprintChildList(ctx, node->options, node, "options", depth);

  if (node->query != NULL)
    _fingerprintChildNode(ctx, node->query, node, "query", depth);

}

static void
_fingerprintCreateTableAsStmt(FingerprintContext *ctx, const CreateTableAsStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintBoolField(ctx, "if_not_exists", node->if_not_exists);

  if (node->into != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "into");
    _fingerprintIntoClause(ctx, node->into, node, "into", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  _fingerprintBoolField(ctx, "is_select_into", node->is_select_into);

  _fingerprintEnumField(ctx, "objtype", _enumToStringObjectType(node->objtype));

  if (node->query != NULL)
    _fingerprintChildNode(ctx, node->query, node, "query", depth);

}

static void
_fingerprintRefreshMatViewStmt(FingerprintContext *ctx, const RefreshMatViewStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintBoolField(ctx, "concurrent", node->concurrent);

  if (node->relation != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "relation");
    _fingerprintRangeVar(ctx, node->relation, node, "relation", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  _fingerprintBoolField(ctx, "skipData", node->skipData);

}

static void
_fingerprintCheckPointStmt(FingerprintContext *ctx, const CheckPointStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
}

static void
_fingerprintDiscardStmt(FingerprintContext *ctx, const DiscardStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintEnumField(ctx, "target", _enumToStringDiscardMode(node->target));

}

static void
_fingerprintLockStmt(FingerprintContext *ctx, const LockStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintIntField(ctx, "mode", node->mode);

  _fingerprintBoolField(ctx, "nowait", node->nowait);

  if (node->relations != NULL && node->relations->length > 0)
    _fingerprintChildList(ctx, node->relations, node, "relations", depth);

}

static void
_fingerprintConstraintsSetStmt(FingerprintContext *ctx, const ConstraintsSetStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->constraints != NULL && node->constraints->length > 0)
    _fingerprintChildList(ctx, node->constraints, node, "constraints", depth);

  _fingerprintBoolField(ctx, "deferred", node->deferred);

}

static void
_fingerprintReindexStmt(FingerprintContext *ctx, const ReindexStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintEnumField(ctx, "kind", _enumToStringReindexObjectType(node->kind));

  _fingerprintStringField(ctx, "name", node->name);

  if (node->params != NULL && node->params->length > 0)
    _fingerprintChildList(ctx, node->params, node, "params", depth);

  if (node->relation != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "relation");
    _fingerprintRangeVar(ctx, node->relation, node, "relation", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

}

static void
_fingerprintCreateConversionStmt(FingerprintContext *ctx, const CreateConversionStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->conversion_name != NULL && node->conversion_name->length > 0)
    _fingerprintChildList(ctx, node->conversion_name, node, "conversion_name", depth);

  _fingerprintBoolField(ctx, "def", node->def);

  _fingerprintStringField(ctx, "for_encoding_name", node->for_encoding_name);

  if (node->func_name != NULL && node->func_name->length > 0)
    _fingerprintChildList(ctx, node->func_name, node, "func_name", depth);

  _fingerprintStringField(ctx, "to_encoding_name", node->to_encoding_name);

}

static void
_fingerprintCreateCastStmt(FingerprintContext *ctx, const CreateCastStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintEnumField(ctx, "context", _enumToStringCoercionContext(node->context));

  if (node->func != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "func");
    _fingerprintObjectWithArgs(ctx, node->func, node, "func", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  _fingerprintBoolField(ctx, "inout", node->inout);

  if (node->sourcetype != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "sourcetype");
    _fingerprintTypeName(ctx, node->sourcetype, node, "sourcetype", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  if (node->targettype != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "targettype");
    _fingerprintTypeName(ctx, node->targettype, node, "targettype", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

}

static void
_fingerprintCreateTransformStmt(FingerprintContext *ctx, const CreateTransformStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->fromsql != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "fromsql");
    _fingerprintObjectWithArgs(ctx, node->fromsql, node, "fromsql", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  _fingerprintStringField(ctx, "lang", node->lang);

  _fingerprintBoolField(ctx, "replace", node->replace);

  if (node->tosql != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "tosql");
    _fingerprintObjectWithArgs(ctx, node->tosql, node, "tosql", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  if (node->type_name != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "type_name");
    _fingerprintTypeName(ctx, node->type_name, node, "type_name", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

}

static void
_fingerprintPrepareStmt(FingerprintContext *ctx, const PrepareStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->argtypes != NULL && node->argtypes->length > 0)
    _fingerprintChildList(ctx, node->argtypes, node, "argtypes", depth);

  // Intentionally ignoring node->name for fingerprinting

  if (node->query != NULL)
    _fingerprintChildNode(ctx, node->query, node, "query", depth);

}

static void
_fingerprintExecuteStmt(FingerprintContext *ctx, const ExecuteStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  // Intentionally ignoring node->name for fingerprinting

  if (node->params != NULL && node->params->length > 0)
    _fingerprintChildList(ctx, node->params, node, "params", depth);

}

static void
_fingerprintDeallocateStmt(FingerprintContext *ctx, const DeallocateStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintBoolField(ctx, "isall", node->isall);

  // Intentionally ignoring node->location for fingerprinting

  // Intentionally ignoring node->name for fingerprinting

}

static void
_fingerprintDropOwnedStmt(FingerprintContext *ctx, const DropOwnedStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintEnumField(ctx, "behavior", _enumToStringDropBehavior(node->behavior));

  if (node->roles != NULL && node->roles->length > 0)
    _fingerprintChildList(ctx, node->roles, node, "roles", depth);

}

static void
_fingerprintReassignOwnedStmt(FingerprintContext *ctx, const ReassignOwnedStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->newrole != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "newrole");
    _fingerprintRoleSpec(ctx, node->newrole, node, "newrole", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  if (node->roles != NULL && node->roles->length > 0)
    _fingerprintChildList(ctx, node->roles, node, "roles", depth);

}

static void
_fingerprintAlterTSDictionaryStmt(FingerprintContext *ctx, const AlterTSDictionaryStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->dictname != NULL && node->dictname->length > 0)
    _fingerprintChildList(ctx, node->dictname, node, "dictname", depth);

  if (node->options != NULL && node->options->length > 0)
    _fingerprintChildList(ctx, node->options, node, "options", depth);

}

static void
_fingerprintAlterTSConfigurationStmt(FingerprintContext *ctx, const AlterTSConfigurationStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->cfgname != NULL && node->cfgname->length > 0)
    _fingerprintChildList(ctx, node->cfgname, node, "cfgname", depth);

  if (node->dicts != NULL && node->dicts->length > 0)
    _fingerprintChildList(ctx, node->dicts, node, "dicts", depth);

  _fingerprintEnumField(ctx, "kind", _enumToStringAlterTSConfigType(node->kind));

  _fingerprintBoolField(ctx, "missing_ok", node->missing_ok);

  _fingerprintBoolField(ctx, "override", node->override);

  _fingerprintBoolField(ctx, "replace", node->replace);

  if (node->tokentype != NULL && node->tokentype->length > 0)
    _fingerprintChildList(ctx, node->tokentype, node, "tokentype", depth);

}

static void
_fingerprintPublicationTable(FingerprintContext *ctx, const PublicationTable *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->columns != NULL && node->columns->length > 0)
    _fingerprintChildList(ctx, node->columns, node, "columns", depth);

  if (node->relation != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "relation");
    _fingerprintRangeVar(ctx, node->relation, node, "relation", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  if (node->whereClause != NULL)
    _fingerprintChildNode(ctx, node->whereClause, node, "whereClause", depth);

}

static void
_fingerprintPublicationObjSpec(FingerprintContext *ctx, const PublicationObjSpec *node, const void *parent, const char *field_name, unsigned int depth)
{
  // Intentionally ignoring node->location for fingerprinting

  _fingerprintStringField(ctx, "name", node->name);

  _fingerprintEnumField(ctx, "pubobjtype", _enumToStringPublicationObjSpecType(node->pubobjtype));

  if (node->pubtable != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "pubtable");
    _fingerprintPublicationTable(ctx, node->pubtable, node, "pubtable", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

}

static void
_fingerprintCreatePublicationStmt(FingerprintContext *ctx, const CreatePublicationStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintBoolField(ctx, "for_all_tables", node->for_all_tables);

  if (node->options != NULL && node->options->length > 0)
    _fingerprintChildList(ctx, node->options, node, "options", depth);

  _fingerprintStringField(ctx, "pubname", node->pubname);

  if (node->pubobjects != NULL && node->pubobjects->length > 0)
    _fingerprintChildList(ctx, node->pubobjects, node, "pubobjects", depth);

}

static void
_fingerprintAlterPublicationStmt(FingerprintContext *ctx, const AlterPublicationStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintEnumField(ctx, "action", _enumToStringAlterPublicationAction(node->action));

  _fingerprintBoolField(ctx, "for_all_tables", node->for_all_tables);

  if (node->options != NULL && node->options->length > 0)
    _fingerprintChildList(ctx, node->options, node, "options", depth);

  _fingerprintStringField(ctx, "pubname", node->pubname);

  if (node->pubobjects != NULL && node->pubobjects->length > 0)
    _fingerprintChildList(ctx, node->pubobjects, node, "pubobjects", depth);

}

static void
_fingerprintCreateSubscriptionStmt(FingerprintContext *ctx, const CreateSubscriptionStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintStringField(ctx, "conninfo", node->conninfo);

  if (node->options != NULL && node->options->length > 0)
    _fingerprintChildList(ctx, node->options, node, "options", depth);

  if (node->publication != NULL && node->publication->length > 0)
    _fingerprintChildList(ctx, node->publication, node, "publication", depth);

  _fingerprintStringField(ctx, "subname", node->subname);

}

static void
_fingerprintAlterSubscriptionStmt(FingerprintContext *ctx, const AlterSubscriptionStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintStringField(ctx, "conninfo", node->conninfo);

  _fingerprintEnumField(ctx, "kind", _enumToStringAlterSubscriptionType(node->kind));

  if (node->options != NULL && node->options->length > 0)
    _fingerprintChildList(ctx, node->options, node, "options", depth);

  if (node->publication != NULL && node->publication->length > 0)
    _fingerprintChildList(ctx, node->publication, node, "publication", depth);

  _fingerprintStringField(ctx, "subname", node->subname);

}

static void
_fingerprintDropSubscriptionStmt(FingerprintContext *ctx, const DropSubscriptionStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintEnumField(ctx, "behavior", _enumToStringDropBehavior(node->behavior));

  _fingerprintBoolField(ctx, "missing_ok", node->missing_ok);

  _fingerprintStringField(ctx, "subname", node->subname);

}

