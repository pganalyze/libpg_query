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

  _fingerprintString(ctx, "functype");
  _fingerprintString(ctx, _enumToStringTableFuncType(node->functype));

  // Intentionally ignoring node->location for fingerprinting

  {
    int x = -1;
    Bitmapset *bms = bms_copy(node->notnulls);

    _fingerprintString(ctx, "notnulls");

    while ((x = bms_next_member(bms, x)) >= 0) {
      char buffer[50];
      sprintf(buffer, "%d", x);
      _fingerprintString(ctx, buffer);
    }

    bms_free(bms);
  }

  if (node->ns_names != NULL && node->ns_names->length > 0)
    _fingerprintChildList(ctx, node->ns_names, node, "ns_names", depth);

  if (node->ns_uris != NULL && node->ns_uris->length > 0)
    _fingerprintChildList(ctx, node->ns_uris, node, "ns_uris", depth);

  if (node->ordinalitycol != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->ordinalitycol);
    _fingerprintString(ctx, "ordinalitycol");
    _fingerprintString(ctx, buffer);
  }

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
  if (node->accessMethod != NULL) {
    _fingerprintString(ctx, "accessMethod");
    _fingerprintString(ctx, node->accessMethod);
  }

  if (node->colNames != NULL && node->colNames->length > 0)
    _fingerprintChildList(ctx, node->colNames, node, "colNames", depth);

  _fingerprintString(ctx, "onCommit");
  _fingerprintString(ctx, _enumToStringOnCommitAction(node->onCommit));

  if (node->options != NULL && node->options->length > 0)
    _fingerprintChildList(ctx, node->options, node, "options", depth);

  if (node->rel != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "rel");
    _fingerprintRangeVar(ctx, node->rel, node, "rel", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  if (node->skipData) {
    _fingerprintString(ctx, "skipData");
    _fingerprintString(ctx, "true");
  }

  if (node->tableSpaceName != NULL) {
    _fingerprintString(ctx, "tableSpaceName");
    _fingerprintString(ctx, node->tableSpaceName);
  }

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

  if (node->varattno != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->varattno);
    _fingerprintString(ctx, "varattno");
    _fingerprintString(ctx, buffer);
  }

  if (node->varcollid != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->varcollid);
    _fingerprintString(ctx, "varcollid");
    _fingerprintString(ctx, buffer);
  }

  if (node->varlevelsup != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->varlevelsup);
    _fingerprintString(ctx, "varlevelsup");
    _fingerprintString(ctx, buffer);
  }

  if (node->varno != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->varno);
    _fingerprintString(ctx, "varno");
    _fingerprintString(ctx, buffer);
  }

  {
    int x = -1;
    Bitmapset *bms = bms_copy(node->varnullingrels);

    _fingerprintString(ctx, "varnullingrels");

    while ((x = bms_next_member(bms, x)) >= 0) {
      char buffer[50];
      sprintf(buffer, "%d", x);
      _fingerprintString(ctx, buffer);
    }

    bms_free(bms);
  }

  _fingerprintString(ctx, "varreturningtype");
  _fingerprintString(ctx, _enumToStringVarReturningType(node->varreturningtype));

  if (node->vartype != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->vartype);
    _fingerprintString(ctx, "vartype");
    _fingerprintString(ctx, buffer);
  }

  if (node->vartypmod != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->vartypmod);
    _fingerprintString(ctx, "vartypmod");
    _fingerprintString(ctx, buffer);
  }

}

static void
_fingerprintConst(FingerprintContext *ctx, const Const *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->constbyval) {
    _fingerprintString(ctx, "constbyval");
    _fingerprintString(ctx, "true");
  }

  if (node->constcollid != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->constcollid);
    _fingerprintString(ctx, "constcollid");
    _fingerprintString(ctx, buffer);
  }

  if (node->constisnull) {
    _fingerprintString(ctx, "constisnull");
    _fingerprintString(ctx, "true");
  }

  if (node->constlen != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->constlen);
    _fingerprintString(ctx, "constlen");
    _fingerprintString(ctx, buffer);
  }

  if (node->consttype != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->consttype);
    _fingerprintString(ctx, "consttype");
    _fingerprintString(ctx, buffer);
  }

  if (node->consttypmod != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->consttypmod);
    _fingerprintString(ctx, "consttypmod");
    _fingerprintString(ctx, buffer);
  }

  // Intentionally ignoring node->location for fingerprinting

}

static void
_fingerprintParam(FingerprintContext *ctx, const Param *node, const void *parent, const char *field_name, unsigned int depth)
{
  // Intentionally ignoring node->location for fingerprinting

  if (node->paramcollid != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->paramcollid);
    _fingerprintString(ctx, "paramcollid");
    _fingerprintString(ctx, buffer);
  }

  if (node->paramid != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->paramid);
    _fingerprintString(ctx, "paramid");
    _fingerprintString(ctx, buffer);
  }

  _fingerprintString(ctx, "paramkind");
  _fingerprintString(ctx, _enumToStringParamKind(node->paramkind));

  if (node->paramtype != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->paramtype);
    _fingerprintString(ctx, "paramtype");
    _fingerprintString(ctx, buffer);
  }

  if (node->paramtypmod != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->paramtypmod);
    _fingerprintString(ctx, "paramtypmod");
    _fingerprintString(ctx, buffer);
  }

}

static void
_fingerprintAggref(FingerprintContext *ctx, const Aggref *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->aggargtypes != NULL && node->aggargtypes->length > 0)
    _fingerprintChildList(ctx, node->aggargtypes, node, "aggargtypes", depth);

  if (node->aggcollid != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->aggcollid);
    _fingerprintString(ctx, "aggcollid");
    _fingerprintString(ctx, buffer);
  }

  if (node->aggdirectargs != NULL && node->aggdirectargs->length > 0)
    _fingerprintChildList(ctx, node->aggdirectargs, node, "aggdirectargs", depth);

  if (node->aggdistinct != NULL && node->aggdistinct->length > 0)
    _fingerprintChildList(ctx, node->aggdistinct, node, "aggdistinct", depth);

  if (node->aggfilter != NULL)
    _fingerprintChildNode(ctx, node->aggfilter, node, "aggfilter", depth);

  if (node->aggfnoid != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->aggfnoid);
    _fingerprintString(ctx, "aggfnoid");
    _fingerprintString(ctx, buffer);
  }

  if (node->aggkind != 0) {
    char buffer[2] = {node->aggkind, '\0'};
    _fingerprintString(ctx, "aggkind");
    _fingerprintString(ctx, buffer);
  }

  if (node->agglevelsup != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->agglevelsup);
    _fingerprintString(ctx, "agglevelsup");
    _fingerprintString(ctx, buffer);
  }

  if (node->aggno != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->aggno);
    _fingerprintString(ctx, "aggno");
    _fingerprintString(ctx, buffer);
  }

  if (node->aggorder != NULL && node->aggorder->length > 0)
    _fingerprintChildList(ctx, node->aggorder, node, "aggorder", depth);

  _fingerprintString(ctx, "aggsplit");
  _fingerprintString(ctx, _enumToStringAggSplit(node->aggsplit));

  if (node->aggstar) {
    _fingerprintString(ctx, "aggstar");
    _fingerprintString(ctx, "true");
  }

  if (node->aggtransno != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->aggtransno);
    _fingerprintString(ctx, "aggtransno");
    _fingerprintString(ctx, buffer);
  }

  if (node->aggtype != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->aggtype);
    _fingerprintString(ctx, "aggtype");
    _fingerprintString(ctx, buffer);
  }

  if (node->aggvariadic) {
    _fingerprintString(ctx, "aggvariadic");
    _fingerprintString(ctx, "true");
  }

  if (node->args != NULL && node->args->length > 0)
    _fingerprintChildList(ctx, node->args, node, "args", depth);

  if (node->inputcollid != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->inputcollid);
    _fingerprintString(ctx, "inputcollid");
    _fingerprintString(ctx, buffer);
  }

  // Intentionally ignoring node->location for fingerprinting

}

static void
_fingerprintGroupingFunc(FingerprintContext *ctx, const GroupingFunc *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->agglevelsup != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->agglevelsup);
    _fingerprintString(ctx, "agglevelsup");
    _fingerprintString(ctx, buffer);
  }

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

  if (node->inputcollid != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->inputcollid);
    _fingerprintString(ctx, "inputcollid");
    _fingerprintString(ctx, buffer);
  }

  // Intentionally ignoring node->location for fingerprinting

  if (node->runCondition != NULL && node->runCondition->length > 0)
    _fingerprintChildList(ctx, node->runCondition, node, "runCondition", depth);

  if (node->winagg) {
    _fingerprintString(ctx, "winagg");
    _fingerprintString(ctx, "true");
  }

  if (node->wincollid != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->wincollid);
    _fingerprintString(ctx, "wincollid");
    _fingerprintString(ctx, buffer);
  }

  if (node->winfnoid != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->winfnoid);
    _fingerprintString(ctx, "winfnoid");
    _fingerprintString(ctx, buffer);
  }

  if (node->winref != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->winref);
    _fingerprintString(ctx, "winref");
    _fingerprintString(ctx, buffer);
  }

  if (node->winstar) {
    _fingerprintString(ctx, "winstar");
    _fingerprintString(ctx, "true");
  }

  if (node->wintype != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->wintype);
    _fingerprintString(ctx, "wintype");
    _fingerprintString(ctx, buffer);
  }

}

static void
_fingerprintWindowFuncRunCondition(FingerprintContext *ctx, const WindowFuncRunCondition *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->arg != NULL)
    _fingerprintChildNode(ctx, node->arg, node, "arg", depth);

  if (node->inputcollid != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->inputcollid);
    _fingerprintString(ctx, "inputcollid");
    _fingerprintString(ctx, buffer);
  }

  if (node->opno != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->opno);
    _fingerprintString(ctx, "opno");
    _fingerprintString(ctx, buffer);
  }

  if (node->wfunc_left) {
    _fingerprintString(ctx, "wfunc_left");
    _fingerprintString(ctx, "true");
  }

}

static void
_fingerprintMergeSupportFunc(FingerprintContext *ctx, const MergeSupportFunc *node, const void *parent, const char *field_name, unsigned int depth)
{
  // Intentionally ignoring node->location for fingerprinting

  if (node->msfcollid != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->msfcollid);
    _fingerprintString(ctx, "msfcollid");
    _fingerprintString(ctx, buffer);
  }

  if (node->msftype != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->msftype);
    _fingerprintString(ctx, "msftype");
    _fingerprintString(ctx, buffer);
  }

}

static void
_fingerprintSubscriptingRef(FingerprintContext *ctx, const SubscriptingRef *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->refassgnexpr != NULL)
    _fingerprintChildNode(ctx, node->refassgnexpr, node, "refassgnexpr", depth);

  if (node->refcollid != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->refcollid);
    _fingerprintString(ctx, "refcollid");
    _fingerprintString(ctx, buffer);
  }

  if (node->refcontainertype != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->refcontainertype);
    _fingerprintString(ctx, "refcontainertype");
    _fingerprintString(ctx, buffer);
  }

  if (node->refelemtype != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->refelemtype);
    _fingerprintString(ctx, "refelemtype");
    _fingerprintString(ctx, buffer);
  }

  if (node->refexpr != NULL)
    _fingerprintChildNode(ctx, node->refexpr, node, "refexpr", depth);

  if (node->reflowerindexpr != NULL && node->reflowerindexpr->length > 0)
    _fingerprintChildList(ctx, node->reflowerindexpr, node, "reflowerindexpr", depth);

  if (node->refrestype != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->refrestype);
    _fingerprintString(ctx, "refrestype");
    _fingerprintString(ctx, buffer);
  }

  if (node->reftypmod != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->reftypmod);
    _fingerprintString(ctx, "reftypmod");
    _fingerprintString(ctx, buffer);
  }

  if (node->refupperindexpr != NULL && node->refupperindexpr->length > 0)
    _fingerprintChildList(ctx, node->refupperindexpr, node, "refupperindexpr", depth);

}

static void
_fingerprintFuncExpr(FingerprintContext *ctx, const FuncExpr *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->args != NULL && node->args->length > 0)
    _fingerprintChildList(ctx, node->args, node, "args", depth);

  if (node->funccollid != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->funccollid);
    _fingerprintString(ctx, "funccollid");
    _fingerprintString(ctx, buffer);
  }

  _fingerprintString(ctx, "funcformat");
  _fingerprintString(ctx, _enumToStringCoercionForm(node->funcformat));

  if (node->funcid != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->funcid);
    _fingerprintString(ctx, "funcid");
    _fingerprintString(ctx, buffer);
  }

  if (node->funcresulttype != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->funcresulttype);
    _fingerprintString(ctx, "funcresulttype");
    _fingerprintString(ctx, buffer);
  }

  if (node->funcretset) {
    _fingerprintString(ctx, "funcretset");
    _fingerprintString(ctx, "true");
  }

  if (node->funcvariadic) {
    _fingerprintString(ctx, "funcvariadic");
    _fingerprintString(ctx, "true");
  }

  if (node->inputcollid != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->inputcollid);
    _fingerprintString(ctx, "inputcollid");
    _fingerprintString(ctx, buffer);
  }

  // Intentionally ignoring node->location for fingerprinting

}

static void
_fingerprintNamedArgExpr(FingerprintContext *ctx, const NamedArgExpr *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->arg != NULL)
    _fingerprintChildNode(ctx, node->arg, node, "arg", depth);

  if (node->argnumber != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->argnumber);
    _fingerprintString(ctx, "argnumber");
    _fingerprintString(ctx, buffer);
  }

  // Intentionally ignoring node->location for fingerprinting

  if (node->name != NULL) {
    _fingerprintString(ctx, "name");
    _fingerprintString(ctx, node->name);
  }

}

static void
_fingerprintOpExpr(FingerprintContext *ctx, const OpExpr *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->args != NULL && node->args->length > 0)
    _fingerprintChildList(ctx, node->args, node, "args", depth);

  if (node->inputcollid != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->inputcollid);
    _fingerprintString(ctx, "inputcollid");
    _fingerprintString(ctx, buffer);
  }

  // Intentionally ignoring node->location for fingerprinting

  if (node->opcollid != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->opcollid);
    _fingerprintString(ctx, "opcollid");
    _fingerprintString(ctx, buffer);
  }

  if (node->opno != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->opno);
    _fingerprintString(ctx, "opno");
    _fingerprintString(ctx, buffer);
  }

  if (node->opresulttype != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->opresulttype);
    _fingerprintString(ctx, "opresulttype");
    _fingerprintString(ctx, buffer);
  }

  if (node->opretset) {
    _fingerprintString(ctx, "opretset");
    _fingerprintString(ctx, "true");
  }

}

static void
_fingerprintScalarArrayOpExpr(FingerprintContext *ctx, const ScalarArrayOpExpr *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->args != NULL && node->args->length > 0)
    _fingerprintChildList(ctx, node->args, node, "args", depth);

  if (node->inputcollid != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->inputcollid);
    _fingerprintString(ctx, "inputcollid");
    _fingerprintString(ctx, buffer);
  }

  // Intentionally ignoring node->location for fingerprinting

  if (node->opno != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->opno);
    _fingerprintString(ctx, "opno");
    _fingerprintString(ctx, buffer);
  }

  if (node->useOr) {
    _fingerprintString(ctx, "useOr");
    _fingerprintString(ctx, "true");
  }

}

static void
_fingerprintBoolExpr(FingerprintContext *ctx, const BoolExpr *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->args != NULL && node->args->length > 0)
    _fingerprintChildList(ctx, node->args, node, "args", depth);

  _fingerprintString(ctx, "boolop");
  _fingerprintString(ctx, _enumToStringBoolExprType(node->boolop));

  // Intentionally ignoring node->location for fingerprinting

}

static void
_fingerprintSubLink(FingerprintContext *ctx, const SubLink *node, const void *parent, const char *field_name, unsigned int depth)
{
  // Intentionally ignoring node->location for fingerprinting

  if (node->operName != NULL && node->operName->length > 0)
    _fingerprintChildList(ctx, node->operName, node, "operName", depth);

  if (node->subLinkId != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->subLinkId);
    _fingerprintString(ctx, "subLinkId");
    _fingerprintString(ctx, buffer);
  }

  _fingerprintString(ctx, "subLinkType");
  _fingerprintString(ctx, _enumToStringSubLinkType(node->subLinkType));

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

  if (node->firstColCollation != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->firstColCollation);
    _fingerprintString(ctx, "firstColCollation");
    _fingerprintString(ctx, buffer);
  }

  if (node->firstColType != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->firstColType);
    _fingerprintString(ctx, "firstColType");
    _fingerprintString(ctx, buffer);
  }

  if (node->firstColTypmod != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->firstColTypmod);
    _fingerprintString(ctx, "firstColTypmod");
    _fingerprintString(ctx, buffer);
  }

  if (node->parParam != NULL && node->parParam->length > 0)
    _fingerprintChildList(ctx, node->parParam, node, "parParam", depth);

  if (node->parallel_safe) {
    _fingerprintString(ctx, "parallel_safe");
    _fingerprintString(ctx, "true");
  }

  if (node->paramIds != NULL && node->paramIds->length > 0)
    _fingerprintChildList(ctx, node->paramIds, node, "paramIds", depth);

  if (node->per_call_cost != 0) {
    char buffer[50];
    sprintf(buffer, "%f", node->per_call_cost);
    _fingerprintString(ctx, "per_call_cost");
    _fingerprintString(ctx, buffer);
  }

  if (node->plan_id != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->plan_id);
    _fingerprintString(ctx, "plan_id");
    _fingerprintString(ctx, buffer);
  }

  if (node->plan_name != NULL) {
    _fingerprintString(ctx, "plan_name");
    _fingerprintString(ctx, node->plan_name);
  }

  if (node->setParam != NULL && node->setParam->length > 0)
    _fingerprintChildList(ctx, node->setParam, node, "setParam", depth);

  if (node->startup_cost != 0) {
    char buffer[50];
    sprintf(buffer, "%f", node->startup_cost);
    _fingerprintString(ctx, "startup_cost");
    _fingerprintString(ctx, buffer);
  }

  _fingerprintString(ctx, "subLinkType");
  _fingerprintString(ctx, _enumToStringSubLinkType(node->subLinkType));

  if (node->testexpr != NULL)
    _fingerprintChildNode(ctx, node->testexpr, node, "testexpr", depth);

  if (node->unknownEqFalse) {
    _fingerprintString(ctx, "unknownEqFalse");
    _fingerprintString(ctx, "true");
  }

  if (node->useHashTable) {
    _fingerprintString(ctx, "useHashTable");
    _fingerprintString(ctx, "true");
  }

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

  if (node->fieldnum != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->fieldnum);
    _fingerprintString(ctx, "fieldnum");
    _fingerprintString(ctx, buffer);
  }

  if (node->resultcollid != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->resultcollid);
    _fingerprintString(ctx, "resultcollid");
    _fingerprintString(ctx, buffer);
  }

  if (node->resulttype != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->resulttype);
    _fingerprintString(ctx, "resulttype");
    _fingerprintString(ctx, buffer);
  }

  if (node->resulttypmod != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->resulttypmod);
    _fingerprintString(ctx, "resulttypmod");
    _fingerprintString(ctx, buffer);
  }

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

  if (node->resulttype != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->resulttype);
    _fingerprintString(ctx, "resulttype");
    _fingerprintString(ctx, buffer);
  }

}

static void
_fingerprintRelabelType(FingerprintContext *ctx, const RelabelType *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->arg != NULL)
    _fingerprintChildNode(ctx, node->arg, node, "arg", depth);

  // Intentionally ignoring node->location for fingerprinting

  _fingerprintString(ctx, "relabelformat");
  _fingerprintString(ctx, _enumToStringCoercionForm(node->relabelformat));

  if (node->resultcollid != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->resultcollid);
    _fingerprintString(ctx, "resultcollid");
    _fingerprintString(ctx, buffer);
  }

  if (node->resulttype != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->resulttype);
    _fingerprintString(ctx, "resulttype");
    _fingerprintString(ctx, buffer);
  }

  if (node->resulttypmod != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->resulttypmod);
    _fingerprintString(ctx, "resulttypmod");
    _fingerprintString(ctx, buffer);
  }

}

static void
_fingerprintCoerceViaIO(FingerprintContext *ctx, const CoerceViaIO *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->arg != NULL)
    _fingerprintChildNode(ctx, node->arg, node, "arg", depth);

  _fingerprintString(ctx, "coerceformat");
  _fingerprintString(ctx, _enumToStringCoercionForm(node->coerceformat));

  // Intentionally ignoring node->location for fingerprinting

  if (node->resultcollid != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->resultcollid);
    _fingerprintString(ctx, "resultcollid");
    _fingerprintString(ctx, buffer);
  }

  if (node->resulttype != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->resulttype);
    _fingerprintString(ctx, "resulttype");
    _fingerprintString(ctx, buffer);
  }

}

static void
_fingerprintArrayCoerceExpr(FingerprintContext *ctx, const ArrayCoerceExpr *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->arg != NULL)
    _fingerprintChildNode(ctx, node->arg, node, "arg", depth);

  _fingerprintString(ctx, "coerceformat");
  _fingerprintString(ctx, _enumToStringCoercionForm(node->coerceformat));

  if (node->elemexpr != NULL)
    _fingerprintChildNode(ctx, node->elemexpr, node, "elemexpr", depth);

  // Intentionally ignoring node->location for fingerprinting

  if (node->resultcollid != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->resultcollid);
    _fingerprintString(ctx, "resultcollid");
    _fingerprintString(ctx, buffer);
  }

  if (node->resulttype != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->resulttype);
    _fingerprintString(ctx, "resulttype");
    _fingerprintString(ctx, buffer);
  }

  if (node->resulttypmod != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->resulttypmod);
    _fingerprintString(ctx, "resulttypmod");
    _fingerprintString(ctx, buffer);
  }

}

static void
_fingerprintConvertRowtypeExpr(FingerprintContext *ctx, const ConvertRowtypeExpr *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->arg != NULL)
    _fingerprintChildNode(ctx, node->arg, node, "arg", depth);

  _fingerprintString(ctx, "convertformat");
  _fingerprintString(ctx, _enumToStringCoercionForm(node->convertformat));

  // Intentionally ignoring node->location for fingerprinting

  if (node->resulttype != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->resulttype);
    _fingerprintString(ctx, "resulttype");
    _fingerprintString(ctx, buffer);
  }

}

static void
_fingerprintCollateExpr(FingerprintContext *ctx, const CollateExpr *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->arg != NULL)
    _fingerprintChildNode(ctx, node->arg, node, "arg", depth);

  if (node->collOid != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->collOid);
    _fingerprintString(ctx, "collOid");
    _fingerprintString(ctx, buffer);
  }

  // Intentionally ignoring node->location for fingerprinting

}

static void
_fingerprintCaseExpr(FingerprintContext *ctx, const CaseExpr *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->arg != NULL)
    _fingerprintChildNode(ctx, node->arg, node, "arg", depth);

  if (node->args != NULL && node->args->length > 0)
    _fingerprintChildList(ctx, node->args, node, "args", depth);

  if (node->casecollid != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->casecollid);
    _fingerprintString(ctx, "casecollid");
    _fingerprintString(ctx, buffer);
  }

  if (node->casetype != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->casetype);
    _fingerprintString(ctx, "casetype");
    _fingerprintString(ctx, buffer);
  }

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
  if (node->collation != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->collation);
    _fingerprintString(ctx, "collation");
    _fingerprintString(ctx, buffer);
  }

  if (node->typeId != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->typeId);
    _fingerprintString(ctx, "typeId");
    _fingerprintString(ctx, buffer);
  }

  if (node->typeMod != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->typeMod);
    _fingerprintString(ctx, "typeMod");
    _fingerprintString(ctx, buffer);
  }

}

static void
_fingerprintArrayExpr(FingerprintContext *ctx, const ArrayExpr *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->array_collid != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->array_collid);
    _fingerprintString(ctx, "array_collid");
    _fingerprintString(ctx, buffer);
  }

  if (node->array_typeid != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->array_typeid);
    _fingerprintString(ctx, "array_typeid");
    _fingerprintString(ctx, buffer);
  }

  if (node->element_typeid != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->element_typeid);
    _fingerprintString(ctx, "element_typeid");
    _fingerprintString(ctx, buffer);
  }

  if (node->elements != NULL && node->elements->length > 0)
    _fingerprintChildList(ctx, node->elements, node, "elements", depth);

  // Intentionally ignoring node->list_end for fingerprinting

  // Intentionally ignoring node->list_start for fingerprinting

  // Intentionally ignoring node->location for fingerprinting

  if (node->multidims) {
    _fingerprintString(ctx, "multidims");
    _fingerprintString(ctx, "true");
  }

}

static void
_fingerprintRowExpr(FingerprintContext *ctx, const RowExpr *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->args != NULL && node->args->length > 0)
    _fingerprintChildList(ctx, node->args, node, "args", depth);

  if (node->colnames != NULL && node->colnames->length > 0)
    _fingerprintChildList(ctx, node->colnames, node, "colnames", depth);

  // Intentionally ignoring node->location for fingerprinting

  _fingerprintString(ctx, "row_format");
  _fingerprintString(ctx, _enumToStringCoercionForm(node->row_format));

  if (node->row_typeid != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->row_typeid);
    _fingerprintString(ctx, "row_typeid");
    _fingerprintString(ctx, buffer);
  }

}

static void
_fingerprintRowCompareExpr(FingerprintContext *ctx, const RowCompareExpr *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintString(ctx, "cmptype");
  _fingerprintString(ctx, _enumToStringCompareType(node->cmptype));

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

  if (node->coalescecollid != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->coalescecollid);
    _fingerprintString(ctx, "coalescecollid");
    _fingerprintString(ctx, buffer);
  }

  if (node->coalescetype != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->coalescetype);
    _fingerprintString(ctx, "coalescetype");
    _fingerprintString(ctx, buffer);
  }

  // Intentionally ignoring node->location for fingerprinting

}

static void
_fingerprintMinMaxExpr(FingerprintContext *ctx, const MinMaxExpr *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->args != NULL && node->args->length > 0)
    _fingerprintChildList(ctx, node->args, node, "args", depth);

  if (node->inputcollid != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->inputcollid);
    _fingerprintString(ctx, "inputcollid");
    _fingerprintString(ctx, buffer);
  }

  // Intentionally ignoring node->location for fingerprinting

  if (node->minmaxcollid != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->minmaxcollid);
    _fingerprintString(ctx, "minmaxcollid");
    _fingerprintString(ctx, buffer);
  }

  if (node->minmaxtype != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->minmaxtype);
    _fingerprintString(ctx, "minmaxtype");
    _fingerprintString(ctx, buffer);
  }

  _fingerprintString(ctx, "op");
  _fingerprintString(ctx, _enumToStringMinMaxOp(node->op));

}

static void
_fingerprintSQLValueFunction(FingerprintContext *ctx, const SQLValueFunction *node, const void *parent, const char *field_name, unsigned int depth)
{
  // Intentionally ignoring node->location for fingerprinting

  _fingerprintString(ctx, "op");
  _fingerprintString(ctx, _enumToStringSQLValueFunctionOp(node->op));

  if (node->type != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->type);
    _fingerprintString(ctx, "type");
    _fingerprintString(ctx, buffer);
  }

  if (node->typmod != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->typmod);
    _fingerprintString(ctx, "typmod");
    _fingerprintString(ctx, buffer);
  }

}

static void
_fingerprintXmlExpr(FingerprintContext *ctx, const XmlExpr *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->arg_names != NULL && node->arg_names->length > 0)
    _fingerprintChildList(ctx, node->arg_names, node, "arg_names", depth);

  if (node->args != NULL && node->args->length > 0)
    _fingerprintChildList(ctx, node->args, node, "args", depth);

  if (node->indent) {
    _fingerprintString(ctx, "indent");
    _fingerprintString(ctx, "true");
  }

  // Intentionally ignoring node->location for fingerprinting

  if (node->name != NULL) {
    _fingerprintString(ctx, "name");
    _fingerprintString(ctx, node->name);
  }

  if (node->named_args != NULL && node->named_args->length > 0)
    _fingerprintChildList(ctx, node->named_args, node, "named_args", depth);

  _fingerprintString(ctx, "op");
  _fingerprintString(ctx, _enumToStringXmlExprOp(node->op));

  if (node->type != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->type);
    _fingerprintString(ctx, "type");
    _fingerprintString(ctx, buffer);
  }

  if (node->typmod != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->typmod);
    _fingerprintString(ctx, "typmod");
    _fingerprintString(ctx, buffer);
  }

  _fingerprintString(ctx, "xmloption");
  _fingerprintString(ctx, _enumToStringXmlOptionType(node->xmloption));

}

static void
_fingerprintJsonFormat(FingerprintContext *ctx, const JsonFormat *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintString(ctx, "encoding");
  _fingerprintString(ctx, _enumToStringJsonEncoding(node->encoding));

  _fingerprintString(ctx, "format_type");
  _fingerprintString(ctx, _enumToStringJsonFormatType(node->format_type));

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

  if (node->typid != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->typid);
    _fingerprintString(ctx, "typid");
    _fingerprintString(ctx, buffer);
  }

  if (node->typmod != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->typmod);
    _fingerprintString(ctx, "typmod");
    _fingerprintString(ctx, buffer);
  }

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
  if (node->absent_on_null) {
    _fingerprintString(ctx, "absent_on_null");
    _fingerprintString(ctx, "true");
  }

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

  _fingerprintString(ctx, "type");
  _fingerprintString(ctx, _enumToStringJsonConstructorType(node->type));

  if (node->unique) {
    _fingerprintString(ctx, "unique");
    _fingerprintString(ctx, "true");
  }

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

  _fingerprintString(ctx, "item_type");
  _fingerprintString(ctx, _enumToStringJsonValueType(node->item_type));

  // Intentionally ignoring node->location for fingerprinting

  if (node->unique_keys) {
    _fingerprintString(ctx, "unique_keys");
    _fingerprintString(ctx, "true");
  }

}

static void
_fingerprintJsonBehavior(FingerprintContext *ctx, const JsonBehavior *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintString(ctx, "btype");
  _fingerprintString(ctx, _enumToStringJsonBehaviorType(node->btype));

  if (node->coerce) {
    _fingerprintString(ctx, "coerce");
    _fingerprintString(ctx, "true");
  }

  if (node->expr != NULL)
    _fingerprintChildNode(ctx, node->expr, node, "expr", depth);

  // Intentionally ignoring node->location for fingerprinting

}

static void
_fingerprintJsonExpr(FingerprintContext *ctx, const JsonExpr *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->collation != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->collation);
    _fingerprintString(ctx, "collation");
    _fingerprintString(ctx, buffer);
  }

  if (node->column_name != NULL) {
    _fingerprintString(ctx, "column_name");
    _fingerprintString(ctx, node->column_name);
  }

  if (node->format != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "format");
    _fingerprintJsonFormat(ctx, node->format, node, "format", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  if (node->formatted_expr != NULL)
    _fingerprintChildNode(ctx, node->formatted_expr, node, "formatted_expr", depth);

  // Intentionally ignoring node->location for fingerprinting

  if (node->omit_quotes) {
    _fingerprintString(ctx, "omit_quotes");
    _fingerprintString(ctx, "true");
  }

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

  _fingerprintString(ctx, "op");
  _fingerprintString(ctx, _enumToStringJsonExprOp(node->op));

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

  if (node->use_io_coercion) {
    _fingerprintString(ctx, "use_io_coercion");
    _fingerprintString(ctx, "true");
  }

  if (node->use_json_coercion) {
    _fingerprintString(ctx, "use_json_coercion");
    _fingerprintString(ctx, "true");
  }

  _fingerprintString(ctx, "wrapper");
  _fingerprintString(ctx, _enumToStringJsonWrapper(node->wrapper));

}

static void
_fingerprintJsonTablePath(FingerprintContext *ctx, const JsonTablePath *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->name != NULL) {
    _fingerprintString(ctx, "name");
    _fingerprintString(ctx, node->name);
  }

  // Intentionally ignoring node->value for fingerprinting

}

static void
_fingerprintJsonTablePathScan(FingerprintContext *ctx, const JsonTablePathScan *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->child != NULL)
    _fingerprintChildNode(ctx, node->child, node, "child", depth);

  if (node->colMax != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->colMax);
    _fingerprintString(ctx, "colMax");
    _fingerprintString(ctx, buffer);
  }

  if (node->colMin != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->colMin);
    _fingerprintString(ctx, "colMin");
    _fingerprintString(ctx, buffer);
  }

  if (node->errorOnError) {
    _fingerprintString(ctx, "errorOnError");
    _fingerprintString(ctx, "true");
  }

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

  if (node->argisrow) {
    _fingerprintString(ctx, "argisrow");
    _fingerprintString(ctx, "true");
  }

  // Intentionally ignoring node->location for fingerprinting

  _fingerprintString(ctx, "nulltesttype");
  _fingerprintString(ctx, _enumToStringNullTestType(node->nulltesttype));

}

static void
_fingerprintBooleanTest(FingerprintContext *ctx, const BooleanTest *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->arg != NULL)
    _fingerprintChildNode(ctx, node->arg, node, "arg", depth);

  _fingerprintString(ctx, "booltesttype");
  _fingerprintString(ctx, _enumToStringBoolTestType(node->booltesttype));

  // Intentionally ignoring node->location for fingerprinting

}

static void
_fingerprintMergeAction(FingerprintContext *ctx, const MergeAction *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintString(ctx, "commandType");
  _fingerprintString(ctx, _enumToStringCmdType(node->commandType));

  _fingerprintString(ctx, "matchKind");
  _fingerprintString(ctx, _enumToStringMergeMatchKind(node->matchKind));

  _fingerprintString(ctx, "override");
  _fingerprintString(ctx, _enumToStringOverridingKind(node->override));

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

  _fingerprintString(ctx, "coercionformat");
  _fingerprintString(ctx, _enumToStringCoercionForm(node->coercionformat));

  // Intentionally ignoring node->location for fingerprinting

  if (node->resultcollid != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->resultcollid);
    _fingerprintString(ctx, "resultcollid");
    _fingerprintString(ctx, buffer);
  }

  if (node->resulttype != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->resulttype);
    _fingerprintString(ctx, "resulttype");
    _fingerprintString(ctx, buffer);
  }

  if (node->resulttypmod != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->resulttypmod);
    _fingerprintString(ctx, "resulttypmod");
    _fingerprintString(ctx, buffer);
  }

}

static void
_fingerprintCoerceToDomainValue(FingerprintContext *ctx, const CoerceToDomainValue *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->collation != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->collation);
    _fingerprintString(ctx, "collation");
    _fingerprintString(ctx, buffer);
  }

  // Intentionally ignoring node->location for fingerprinting

  if (node->typeId != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->typeId);
    _fingerprintString(ctx, "typeId");
    _fingerprintString(ctx, buffer);
  }

  if (node->typeMod != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->typeMod);
    _fingerprintString(ctx, "typeMod");
    _fingerprintString(ctx, buffer);
  }

}

static void
_fingerprintSetToDefault(FingerprintContext *ctx, const SetToDefault *node, const void *parent, const char *field_name, unsigned int depth)
{
  // Intentionally ignoring all fields for fingerprinting
}

static void
_fingerprintCurrentOfExpr(FingerprintContext *ctx, const CurrentOfExpr *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->cursor_name != NULL) {
    _fingerprintString(ctx, "cursor_name");
    _fingerprintString(ctx, node->cursor_name);
  }

  if (node->cursor_param != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->cursor_param);
    _fingerprintString(ctx, "cursor_param");
    _fingerprintString(ctx, buffer);
  }

  if (node->cvarno != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->cvarno);
    _fingerprintString(ctx, "cvarno");
    _fingerprintString(ctx, buffer);
  }

}

static void
_fingerprintNextValueExpr(FingerprintContext *ctx, const NextValueExpr *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->seqid != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->seqid);
    _fingerprintString(ctx, "seqid");
    _fingerprintString(ctx, buffer);
  }

  if (node->typeId != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->typeId);
    _fingerprintString(ctx, "typeId");
    _fingerprintString(ctx, buffer);
  }

}

static void
_fingerprintInferenceElem(FingerprintContext *ctx, const InferenceElem *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->expr != NULL)
    _fingerprintChildNode(ctx, node->expr, node, "expr", depth);

  if (node->infercollid != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->infercollid);
    _fingerprintString(ctx, "infercollid");
    _fingerprintString(ctx, buffer);
  }

  if (node->inferopclass != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->inferopclass);
    _fingerprintString(ctx, "inferopclass");
    _fingerprintString(ctx, buffer);
  }

}

static void
_fingerprintReturningExpr(FingerprintContext *ctx, const ReturningExpr *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->retexpr != NULL)
    _fingerprintChildNode(ctx, node->retexpr, node, "retexpr", depth);

  if (node->retlevelsup != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->retlevelsup);
    _fingerprintString(ctx, "retlevelsup");
    _fingerprintString(ctx, buffer);
  }

  if (node->retold) {
    _fingerprintString(ctx, "retold");
    _fingerprintString(ctx, "true");
  }

}

static void
_fingerprintTargetEntry(FingerprintContext *ctx, const TargetEntry *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->expr != NULL)
    _fingerprintChildNode(ctx, node->expr, node, "expr", depth);

  if (node->resjunk) {
    _fingerprintString(ctx, "resjunk");
    _fingerprintString(ctx, "true");
  }

  if (node->resname != NULL) {
    _fingerprintString(ctx, "resname");
    _fingerprintString(ctx, node->resname);
  }

  if (node->resno != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->resno);
    _fingerprintString(ctx, "resno");
    _fingerprintString(ctx, buffer);
  }

  if (node->resorigcol != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->resorigcol);
    _fingerprintString(ctx, "resorigcol");
    _fingerprintString(ctx, buffer);
  }

  if (node->resorigtbl != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->resorigtbl);
    _fingerprintString(ctx, "resorigtbl");
    _fingerprintString(ctx, buffer);
  }

  if (node->ressortgroupref != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->ressortgroupref);
    _fingerprintString(ctx, "ressortgroupref");
    _fingerprintString(ctx, buffer);
  }

}

static void
_fingerprintRangeTblRef(FingerprintContext *ctx, const RangeTblRef *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->rtindex != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->rtindex);
    _fingerprintString(ctx, "rtindex");
    _fingerprintString(ctx, buffer);
  }

}

static void
_fingerprintJoinExpr(FingerprintContext *ctx, const JoinExpr *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->alias != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "alias");
    _fingerprintAlias(ctx, node->alias, node, "alias", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  if (node->isNatural) {
    _fingerprintString(ctx, "isNatural");
    _fingerprintString(ctx, "true");
  }

  if (node->join_using_alias != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "join_using_alias");
    _fingerprintAlias(ctx, node->join_using_alias, node, "join_using_alias", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  _fingerprintString(ctx, "jointype");
  _fingerprintString(ctx, _enumToStringJoinType(node->jointype));

  if (node->larg != NULL)
    _fingerprintChildNode(ctx, node->larg, node, "larg", depth);

  if (node->quals != NULL)
    _fingerprintChildNode(ctx, node->quals, node, "quals", depth);

  if (node->rarg != NULL)
    _fingerprintChildNode(ctx, node->rarg, node, "rarg", depth);

  if (node->rtindex != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->rtindex);
    _fingerprintString(ctx, "rtindex");
    _fingerprintString(ctx, buffer);
  }

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
  _fingerprintString(ctx, "action");
  _fingerprintString(ctx, _enumToStringOnConflictAction(node->action));

  if (node->arbiterElems != NULL && node->arbiterElems->length > 0)
    _fingerprintChildList(ctx, node->arbiterElems, node, "arbiterElems", depth);

  if (node->arbiterWhere != NULL)
    _fingerprintChildNode(ctx, node->arbiterWhere, node, "arbiterWhere", depth);

  if (node->constraint != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->constraint);
    _fingerprintString(ctx, "constraint");
    _fingerprintString(ctx, buffer);
  }

  if (node->exclRelIndex != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->exclRelIndex);
    _fingerprintString(ctx, "exclRelIndex");
    _fingerprintString(ctx, buffer);
  }

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
  if (node->canSetTag) {
    _fingerprintString(ctx, "canSetTag");
    _fingerprintString(ctx, "true");
  }

  _fingerprintString(ctx, "commandType");
  _fingerprintString(ctx, _enumToStringCmdType(node->commandType));

  if (node->constraintDeps != NULL && node->constraintDeps->length > 0)
    _fingerprintChildList(ctx, node->constraintDeps, node, "constraintDeps", depth);

  if (node->cteList != NULL && node->cteList->length > 0)
    _fingerprintChildList(ctx, node->cteList, node, "cteList", depth);

  if (node->distinctClause != NULL && node->distinctClause->length > 0)
    _fingerprintChildList(ctx, node->distinctClause, node, "distinctClause", depth);

  if (node->groupClause != NULL && node->groupClause->length > 0)
    _fingerprintChildList(ctx, node->groupClause, node, "groupClause", depth);

  if (node->groupDistinct) {
    _fingerprintString(ctx, "groupDistinct");
    _fingerprintString(ctx, "true");
  }

  if (node->groupingSets != NULL && node->groupingSets->length > 0)
    _fingerprintChildList(ctx, node->groupingSets, node, "groupingSets", depth);

  if (node->hasAggs) {
    _fingerprintString(ctx, "hasAggs");
    _fingerprintString(ctx, "true");
  }

  if (node->hasDistinctOn) {
    _fingerprintString(ctx, "hasDistinctOn");
    _fingerprintString(ctx, "true");
  }

  if (node->hasForUpdate) {
    _fingerprintString(ctx, "hasForUpdate");
    _fingerprintString(ctx, "true");
  }

  if (node->hasGroupRTE) {
    _fingerprintString(ctx, "hasGroupRTE");
    _fingerprintString(ctx, "true");
  }

  if (node->hasModifyingCTE) {
    _fingerprintString(ctx, "hasModifyingCTE");
    _fingerprintString(ctx, "true");
  }

  if (node->hasRecursive) {
    _fingerprintString(ctx, "hasRecursive");
    _fingerprintString(ctx, "true");
  }

  if (node->hasRowSecurity) {
    _fingerprintString(ctx, "hasRowSecurity");
    _fingerprintString(ctx, "true");
  }

  if (node->hasSubLinks) {
    _fingerprintString(ctx, "hasSubLinks");
    _fingerprintString(ctx, "true");
  }

  if (node->hasTargetSRFs) {
    _fingerprintString(ctx, "hasTargetSRFs");
    _fingerprintString(ctx, "true");
  }

  if (node->hasWindowFuncs) {
    _fingerprintString(ctx, "hasWindowFuncs");
    _fingerprintString(ctx, "true");
  }

  if (node->havingQual != NULL)
    _fingerprintChildNode(ctx, node->havingQual, node, "havingQual", depth);

  if (node->isReturn) {
    _fingerprintString(ctx, "isReturn");
    _fingerprintString(ctx, "true");
  }

  if (node->jointree != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "jointree");
    _fingerprintFromExpr(ctx, node->jointree, node, "jointree", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  if (node->limitCount != NULL)
    _fingerprintChildNode(ctx, node->limitCount, node, "limitCount", depth);

  if (node->limitOffset != NULL)
    _fingerprintChildNode(ctx, node->limitOffset, node, "limitOffset", depth);

  _fingerprintString(ctx, "limitOption");
  _fingerprintString(ctx, _enumToStringLimitOption(node->limitOption));

  if (node->mergeActionList != NULL && node->mergeActionList->length > 0)
    _fingerprintChildList(ctx, node->mergeActionList, node, "mergeActionList", depth);

  if (node->mergeJoinCondition != NULL)
    _fingerprintChildNode(ctx, node->mergeJoinCondition, node, "mergeJoinCondition", depth);

  if (node->mergeTargetRelation != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->mergeTargetRelation);
    _fingerprintString(ctx, "mergeTargetRelation");
    _fingerprintString(ctx, buffer);
  }

  if (node->onConflict != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "onConflict");
    _fingerprintOnConflictExpr(ctx, node->onConflict, node, "onConflict", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  _fingerprintString(ctx, "override");
  _fingerprintString(ctx, _enumToStringOverridingKind(node->override));

  _fingerprintString(ctx, "querySource");
  _fingerprintString(ctx, _enumToStringQuerySource(node->querySource));

  if (node->resultRelation != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->resultRelation);
    _fingerprintString(ctx, "resultRelation");
    _fingerprintString(ctx, buffer);
  }

  if (node->returningList != NULL && node->returningList->length > 0)
    _fingerprintChildList(ctx, node->returningList, node, "returningList", depth);

  if (node->returningNewAlias != NULL) {
    _fingerprintString(ctx, "returningNewAlias");
    _fingerprintString(ctx, node->returningNewAlias);
  }

  if (node->returningOldAlias != NULL) {
    _fingerprintString(ctx, "returningOldAlias");
    _fingerprintString(ctx, node->returningOldAlias);
  }

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

  if (node->stmt_len != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->stmt_len);
    _fingerprintString(ctx, "stmt_len");
    _fingerprintString(ctx, buffer);
  }

  if (node->stmt_location != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->stmt_location);
    _fingerprintString(ctx, "stmt_location");
    _fingerprintString(ctx, buffer);
  }

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

  if (node->pct_type) {
    _fingerprintString(ctx, "pct_type");
    _fingerprintString(ctx, "true");
  }

  if (node->setof) {
    _fingerprintString(ctx, "setof");
    _fingerprintString(ctx, "true");
  }

  if (node->typeOid != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->typeOid);
    _fingerprintString(ctx, "typeOid");
    _fingerprintString(ctx, buffer);
  }

  if (node->typemod != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->typemod);
    _fingerprintString(ctx, "typemod");
    _fingerprintString(ctx, buffer);
  }

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

  if (node->rolename != NULL) {
    _fingerprintString(ctx, "rolename");
    _fingerprintString(ctx, node->rolename);
  }

  _fingerprintString(ctx, "roletype");
  _fingerprintString(ctx, _enumToStringRoleSpecType(node->roletype));

}

static void
_fingerprintFuncCall(FingerprintContext *ctx, const FuncCall *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->agg_distinct) {
    _fingerprintString(ctx, "agg_distinct");
    _fingerprintString(ctx, "true");
  }

  if (node->agg_filter != NULL)
    _fingerprintChildNode(ctx, node->agg_filter, node, "agg_filter", depth);

  if (node->agg_order != NULL && node->agg_order->length > 0)
    _fingerprintChildList(ctx, node->agg_order, node, "agg_order", depth);

  if (node->agg_star) {
    _fingerprintString(ctx, "agg_star");
    _fingerprintString(ctx, "true");
  }

  if (node->agg_within_group) {
    _fingerprintString(ctx, "agg_within_group");
    _fingerprintString(ctx, "true");
  }

  if (node->args != NULL && node->args->length > 0)
    _fingerprintChildList(ctx, node->args, node, "args", depth);

  if (node->func_variadic) {
    _fingerprintString(ctx, "func_variadic");
    _fingerprintString(ctx, "true");
  }

  _fingerprintString(ctx, "funcformat");
  _fingerprintString(ctx, _enumToStringCoercionForm(node->funcformat));

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
  if (node->is_slice) {
    _fingerprintString(ctx, "is_slice");
    _fingerprintString(ctx, "true");
  }

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
  if (node->colno != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->colno);
    _fingerprintString(ctx, "colno");
    _fingerprintString(ctx, buffer);
  }

  if (node->ncolumns != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->ncolumns);
    _fingerprintString(ctx, "ncolumns");
    _fingerprintString(ctx, buffer);
  }

  if (node->source != NULL)
    _fingerprintChildNode(ctx, node->source, node, "source", depth);

}

static void
_fingerprintSortBy(FingerprintContext *ctx, const SortBy *node, const void *parent, const char *field_name, unsigned int depth)
{
  // Intentionally ignoring node->location for fingerprinting

  if (node->node != NULL)
    _fingerprintChildNode(ctx, node->node, node, "node", depth);

  _fingerprintString(ctx, "sortby_dir");
  _fingerprintString(ctx, _enumToStringSortByDir(node->sortby_dir));

  _fingerprintString(ctx, "sortby_nulls");
  _fingerprintString(ctx, _enumToStringSortByNulls(node->sortby_nulls));

  if (node->useOp != NULL && node->useOp->length > 0)
    _fingerprintChildList(ctx, node->useOp, node, "useOp", depth);

}

static void
_fingerprintWindowDef(FingerprintContext *ctx, const WindowDef *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->endOffset != NULL)
    _fingerprintChildNode(ctx, node->endOffset, node, "endOffset", depth);

  if (node->frameOptions != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->frameOptions);
    _fingerprintString(ctx, "frameOptions");
    _fingerprintString(ctx, buffer);
  }

  // Intentionally ignoring node->location for fingerprinting

  if (node->name != NULL) {
    _fingerprintString(ctx, "name");
    _fingerprintString(ctx, node->name);
  }

  if (node->orderClause != NULL && node->orderClause->length > 0)
    _fingerprintChildList(ctx, node->orderClause, node, "orderClause", depth);

  if (node->partitionClause != NULL && node->partitionClause->length > 0)
    _fingerprintChildList(ctx, node->partitionClause, node, "partitionClause", depth);

  if (node->refname != NULL) {
    _fingerprintString(ctx, "refname");
    _fingerprintString(ctx, node->refname);
  }

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

  if (node->lateral) {
    _fingerprintString(ctx, "lateral");
    _fingerprintString(ctx, "true");
  }

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

  if (node->is_rowsfrom) {
    _fingerprintString(ctx, "is_rowsfrom");
    _fingerprintString(ctx, "true");
  }

  if (node->lateral) {
    _fingerprintString(ctx, "lateral");
    _fingerprintString(ctx, "true");
  }

  if (node->ordinality) {
    _fingerprintString(ctx, "ordinality");
    _fingerprintString(ctx, "true");
  }

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

  if (node->lateral) {
    _fingerprintString(ctx, "lateral");
    _fingerprintString(ctx, "true");
  }

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

  if (node->colname != NULL) {
    _fingerprintString(ctx, "colname");
    _fingerprintString(ctx, node->colname);
  }

  if (node->for_ordinality) {
    _fingerprintString(ctx, "for_ordinality");
    _fingerprintString(ctx, "true");
  }

  if (node->is_not_null) {
    _fingerprintString(ctx, "is_not_null");
    _fingerprintString(ctx, "true");
  }

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

  if (node->collOid != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->collOid);
    _fingerprintString(ctx, "collOid");
    _fingerprintString(ctx, buffer);
  }

  if (node->colname != NULL) {
    _fingerprintString(ctx, "colname");
    _fingerprintString(ctx, node->colname);
  }

  if (node->compression != NULL) {
    _fingerprintString(ctx, "compression");
    _fingerprintString(ctx, node->compression);
  }

  if (node->constraints != NULL && node->constraints->length > 0)
    _fingerprintChildList(ctx, node->constraints, node, "constraints", depth);

  if (node->cooked_default != NULL)
    _fingerprintChildNode(ctx, node->cooked_default, node, "cooked_default", depth);

  if (node->fdwoptions != NULL && node->fdwoptions->length > 0)
    _fingerprintChildList(ctx, node->fdwoptions, node, "fdwoptions", depth);

  if (node->generated != 0) {
    char buffer[2] = {node->generated, '\0'};
    _fingerprintString(ctx, "generated");
    _fingerprintString(ctx, buffer);
  }

  if (node->identity != 0) {
    char buffer[2] = {node->identity, '\0'};
    _fingerprintString(ctx, "identity");
    _fingerprintString(ctx, buffer);
  }

  if (node->identitySequence != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "identitySequence");
    _fingerprintRangeVar(ctx, node->identitySequence, node, "identitySequence", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  if (node->inhcount != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->inhcount);
    _fingerprintString(ctx, "inhcount");
    _fingerprintString(ctx, buffer);
  }

  if (node->is_from_type) {
    _fingerprintString(ctx, "is_from_type");
    _fingerprintString(ctx, "true");
  }

  if (node->is_local) {
    _fingerprintString(ctx, "is_local");
    _fingerprintString(ctx, "true");
  }

  if (node->is_not_null) {
    _fingerprintString(ctx, "is_not_null");
    _fingerprintString(ctx, "true");
  }

  // Intentionally ignoring node->location for fingerprinting

  if (node->raw_default != NULL)
    _fingerprintChildNode(ctx, node->raw_default, node, "raw_default", depth);

  if (node->storage != 0) {
    char buffer[2] = {node->storage, '\0'};
    _fingerprintString(ctx, "storage");
    _fingerprintString(ctx, buffer);
  }

  if (node->storage_name != NULL) {
    _fingerprintString(ctx, "storage_name");
    _fingerprintString(ctx, node->storage_name);
  }

  if (node->typeName != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "typeName");
    _fingerprintTypeName(ctx, node->typeName, node, "typeName", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

}

static void
_fingerprintTableLikeClause(FingerprintContext *ctx, const TableLikeClause *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->options != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->options);
    _fingerprintString(ctx, "options");
    _fingerprintString(ctx, buffer);
  }

  if (node->relation != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "relation");
    _fingerprintRangeVar(ctx, node->relation, node, "relation", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  if (node->relationOid != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->relationOid);
    _fingerprintString(ctx, "relationOid");
    _fingerprintString(ctx, buffer);
  }

}

static void
_fingerprintIndexElem(FingerprintContext *ctx, const IndexElem *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->collation != NULL && node->collation->length > 0)
    _fingerprintChildList(ctx, node->collation, node, "collation", depth);

  if (node->expr != NULL)
    _fingerprintChildNode(ctx, node->expr, node, "expr", depth);

  if (node->indexcolname != NULL) {
    _fingerprintString(ctx, "indexcolname");
    _fingerprintString(ctx, node->indexcolname);
  }

  if (node->name != NULL) {
    _fingerprintString(ctx, "name");
    _fingerprintString(ctx, node->name);
  }

  _fingerprintString(ctx, "nulls_ordering");
  _fingerprintString(ctx, _enumToStringSortByNulls(node->nulls_ordering));

  if (node->opclass != NULL && node->opclass->length > 0)
    _fingerprintChildList(ctx, node->opclass, node, "opclass", depth);

  if (node->opclassopts != NULL && node->opclassopts->length > 0)
    _fingerprintChildList(ctx, node->opclassopts, node, "opclassopts", depth);

  _fingerprintString(ctx, "ordering");
  _fingerprintString(ctx, _enumToStringSortByDir(node->ordering));

}

static void
_fingerprintDefElem(FingerprintContext *ctx, const DefElem *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->arg != NULL)
    _fingerprintChildNode(ctx, node->arg, node, "arg", depth);

  _fingerprintString(ctx, "defaction");
  _fingerprintString(ctx, _enumToStringDefElemAction(node->defaction));

  if (node->defname != NULL) {
    _fingerprintString(ctx, "defname");
    _fingerprintString(ctx, node->defname);
  }

  if (node->defnamespace != NULL) {
    _fingerprintString(ctx, "defnamespace");
    _fingerprintString(ctx, node->defnamespace);
  }

  // Intentionally ignoring node->location for fingerprinting

}

static void
_fingerprintLockingClause(FingerprintContext *ctx, const LockingClause *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->lockedRels != NULL && node->lockedRels->length > 0)
    _fingerprintChildList(ctx, node->lockedRels, node, "lockedRels", depth);

  _fingerprintString(ctx, "strength");
  _fingerprintString(ctx, _enumToStringLockClauseStrength(node->strength));

  _fingerprintString(ctx, "waitPolicy");
  _fingerprintString(ctx, _enumToStringLockWaitPolicy(node->waitPolicy));

}

static void
_fingerprintXmlSerialize(FingerprintContext *ctx, const XmlSerialize *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->expr != NULL)
    _fingerprintChildNode(ctx, node->expr, node, "expr", depth);

  if (node->indent) {
    _fingerprintString(ctx, "indent");
    _fingerprintString(ctx, "true");
  }

  // Intentionally ignoring node->location for fingerprinting

  if (node->typeName != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "typeName");
    _fingerprintTypeName(ctx, node->typeName, node, "typeName", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  _fingerprintString(ctx, "xmloption");
  _fingerprintString(ctx, _enumToStringXmlOptionType(node->xmloption));

}

static void
_fingerprintPartitionElem(FingerprintContext *ctx, const PartitionElem *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->collation != NULL && node->collation->length > 0)
    _fingerprintChildList(ctx, node->collation, node, "collation", depth);

  if (node->expr != NULL)
    _fingerprintChildNode(ctx, node->expr, node, "expr", depth);

  // Intentionally ignoring node->location for fingerprinting

  if (node->name != NULL) {
    _fingerprintString(ctx, "name");
    _fingerprintString(ctx, node->name);
  }

  if (node->opclass != NULL && node->opclass->length > 0)
    _fingerprintChildList(ctx, node->opclass, node, "opclass", depth);

}

static void
_fingerprintPartitionSpec(FingerprintContext *ctx, const PartitionSpec *node, const void *parent, const char *field_name, unsigned int depth)
{
  // Intentionally ignoring node->location for fingerprinting

  if (node->partParams != NULL && node->partParams->length > 0)
    _fingerprintChildList(ctx, node->partParams, node, "partParams", depth);

  _fingerprintString(ctx, "strategy");
  _fingerprintString(ctx, _enumToStringPartitionStrategy(node->strategy));

}

static void
_fingerprintPartitionBoundSpec(FingerprintContext *ctx, const PartitionBoundSpec *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->is_default) {
    _fingerprintString(ctx, "is_default");
    _fingerprintString(ctx, "true");
  }

  if (node->listdatums != NULL && node->listdatums->length > 0)
    _fingerprintChildList(ctx, node->listdatums, node, "listdatums", depth);

  // Intentionally ignoring node->location for fingerprinting

  if (node->lowerdatums != NULL && node->lowerdatums->length > 0)
    _fingerprintChildList(ctx, node->lowerdatums, node, "lowerdatums", depth);

  if (node->modulus != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->modulus);
    _fingerprintString(ctx, "modulus");
    _fingerprintString(ctx, buffer);
  }

  if (node->remainder != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->remainder);
    _fingerprintString(ctx, "remainder");
    _fingerprintString(ctx, buffer);
  }

  if (node->strategy != 0) {
    char buffer[2] = {node->strategy, '\0'};
    _fingerprintString(ctx, "strategy");
    _fingerprintString(ctx, buffer);
  }

  if (node->upperdatums != NULL && node->upperdatums->length > 0)
    _fingerprintChildList(ctx, node->upperdatums, node, "upperdatums", depth);

}

static void
_fingerprintPartitionRangeDatum(FingerprintContext *ctx, const PartitionRangeDatum *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintString(ctx, "kind");
  _fingerprintString(ctx, _enumToStringPartitionRangeDatumKind(node->kind));

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

  if (node->concurrent) {
    _fingerprintString(ctx, "concurrent");
    _fingerprintString(ctx, "true");
  }

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

  if (node->ctelevelsup != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->ctelevelsup);
    _fingerprintString(ctx, "ctelevelsup");
    _fingerprintString(ctx, buffer);
  }

  if (node->ctename != NULL) {
    _fingerprintString(ctx, "ctename");
    _fingerprintString(ctx, node->ctename);
  }

  if (node->enrname != NULL) {
    _fingerprintString(ctx, "enrname");
    _fingerprintString(ctx, node->enrname);
  }

  if (node->enrtuples != 0) {
    char buffer[50];
    sprintf(buffer, "%f", node->enrtuples);
    _fingerprintString(ctx, "enrtuples");
    _fingerprintString(ctx, buffer);
  }

  if (node->eref != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "eref");
    _fingerprintAlias(ctx, node->eref, node, "eref", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  if (node->funcordinality) {
    _fingerprintString(ctx, "funcordinality");
    _fingerprintString(ctx, "true");
  }

  if (node->functions != NULL && node->functions->length > 0)
    _fingerprintChildList(ctx, node->functions, node, "functions", depth);

  if (node->groupexprs != NULL && node->groupexprs->length > 0)
    _fingerprintChildList(ctx, node->groupexprs, node, "groupexprs", depth);

  if (node->inFromCl) {
    _fingerprintString(ctx, "inFromCl");
    _fingerprintString(ctx, "true");
  }

  if (node->inh) {
    _fingerprintString(ctx, "inh");
    _fingerprintString(ctx, "true");
  }

  if (node->join_using_alias != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "join_using_alias");
    _fingerprintAlias(ctx, node->join_using_alias, node, "join_using_alias", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  if (node->joinaliasvars != NULL && node->joinaliasvars->length > 0)
    _fingerprintChildList(ctx, node->joinaliasvars, node, "joinaliasvars", depth);

  if (node->joinleftcols != NULL && node->joinleftcols->length > 0)
    _fingerprintChildList(ctx, node->joinleftcols, node, "joinleftcols", depth);

  if (node->joinmergedcols != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->joinmergedcols);
    _fingerprintString(ctx, "joinmergedcols");
    _fingerprintString(ctx, buffer);
  }

  if (node->joinrightcols != NULL && node->joinrightcols->length > 0)
    _fingerprintChildList(ctx, node->joinrightcols, node, "joinrightcols", depth);

  _fingerprintString(ctx, "jointype");
  _fingerprintString(ctx, _enumToStringJoinType(node->jointype));

  if (node->lateral) {
    _fingerprintString(ctx, "lateral");
    _fingerprintString(ctx, "true");
  }

  if (node->perminfoindex != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->perminfoindex);
    _fingerprintString(ctx, "perminfoindex");
    _fingerprintString(ctx, buffer);
  }

  if (node->relid != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->relid);
    _fingerprintString(ctx, "relid");
    _fingerprintString(ctx, buffer);
  }

  if (node->relkind != 0) {
    char buffer[2] = {node->relkind, '\0'};
    _fingerprintString(ctx, "relkind");
    _fingerprintString(ctx, buffer);
  }

  if (node->rellockmode != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->rellockmode);
    _fingerprintString(ctx, "rellockmode");
    _fingerprintString(ctx, buffer);
  }

  _fingerprintString(ctx, "rtekind");
  _fingerprintString(ctx, _enumToStringRTEKind(node->rtekind));

  if (node->securityQuals != NULL && node->securityQuals->length > 0)
    _fingerprintChildList(ctx, node->securityQuals, node, "securityQuals", depth);

  if (node->security_barrier) {
    _fingerprintString(ctx, "security_barrier");
    _fingerprintString(ctx, "true");
  }

  if (node->self_reference) {
    _fingerprintString(ctx, "self_reference");
    _fingerprintString(ctx, "true");
  }

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
  if (node->checkAsUser != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->checkAsUser);
    _fingerprintString(ctx, "checkAsUser");
    _fingerprintString(ctx, buffer);
  }

  if (node->inh) {
    _fingerprintString(ctx, "inh");
    _fingerprintString(ctx, "true");
  }

  {
    int x = -1;
    Bitmapset *bms = bms_copy(node->insertedCols);

    _fingerprintString(ctx, "insertedCols");

    while ((x = bms_next_member(bms, x)) >= 0) {
      char buffer[50];
      sprintf(buffer, "%d", x);
      _fingerprintString(ctx, buffer);
    }

    bms_free(bms);
  }

  if (node->relid != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->relid);
    _fingerprintString(ctx, "relid");
    _fingerprintString(ctx, buffer);
  }

  if (node->requiredPerms != 0) {
    char buffer[50];
    sprintf(buffer, UINT64_FORMAT, node->requiredPerms);
    _fingerprintString(ctx, "requiredPerms");
    _fingerprintString(ctx, buffer);
  }

  {
    int x = -1;
    Bitmapset *bms = bms_copy(node->selectedCols);

    _fingerprintString(ctx, "selectedCols");

    while ((x = bms_next_member(bms, x)) >= 0) {
      char buffer[50];
      sprintf(buffer, "%d", x);
      _fingerprintString(ctx, buffer);
    }

    bms_free(bms);
  }

  {
    int x = -1;
    Bitmapset *bms = bms_copy(node->updatedCols);

    _fingerprintString(ctx, "updatedCols");

    while ((x = bms_next_member(bms, x)) >= 0) {
      char buffer[50];
      sprintf(buffer, "%d", x);
      _fingerprintString(ctx, buffer);
    }

    bms_free(bms);
  }

}

static void
_fingerprintRangeTblFunction(FingerprintContext *ctx, const RangeTblFunction *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->funccolcollations != NULL && node->funccolcollations->length > 0)
    _fingerprintChildList(ctx, node->funccolcollations, node, "funccolcollations", depth);

  if (node->funccolcount != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->funccolcount);
    _fingerprintString(ctx, "funccolcount");
    _fingerprintString(ctx, buffer);
  }

  if (node->funccolnames != NULL && node->funccolnames->length > 0)
    _fingerprintChildList(ctx, node->funccolnames, node, "funccolnames", depth);

  if (node->funccoltypes != NULL && node->funccoltypes->length > 0)
    _fingerprintChildList(ctx, node->funccoltypes, node, "funccoltypes", depth);

  if (node->funccoltypmods != NULL && node->funccoltypmods->length > 0)
    _fingerprintChildList(ctx, node->funccoltypmods, node, "funccoltypmods", depth);

  if (node->funcexpr != NULL)
    _fingerprintChildNode(ctx, node->funcexpr, node, "funcexpr", depth);

  {
    int x = -1;
    Bitmapset *bms = bms_copy(node->funcparams);

    _fingerprintString(ctx, "funcparams");

    while ((x = bms_next_member(bms, x)) >= 0) {
      char buffer[50];
      sprintf(buffer, "%d", x);
      _fingerprintString(ctx, buffer);
    }

    bms_free(bms);
  }

}

static void
_fingerprintTableSampleClause(FingerprintContext *ctx, const TableSampleClause *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->args != NULL && node->args->length > 0)
    _fingerprintChildList(ctx, node->args, node, "args", depth);

  if (node->repeatable != NULL)
    _fingerprintChildNode(ctx, node->repeatable, node, "repeatable", depth);

  if (node->tsmhandler != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->tsmhandler);
    _fingerprintString(ctx, "tsmhandler");
    _fingerprintString(ctx, buffer);
  }

}

static void
_fingerprintWithCheckOption(FingerprintContext *ctx, const WithCheckOption *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->cascaded) {
    _fingerprintString(ctx, "cascaded");
    _fingerprintString(ctx, "true");
  }

  _fingerprintString(ctx, "kind");
  _fingerprintString(ctx, _enumToStringWCOKind(node->kind));

  if (node->polname != NULL) {
    _fingerprintString(ctx, "polname");
    _fingerprintString(ctx, node->polname);
  }

  if (node->qual != NULL)
    _fingerprintChildNode(ctx, node->qual, node, "qual", depth);

  if (node->relname != NULL) {
    _fingerprintString(ctx, "relname");
    _fingerprintString(ctx, node->relname);
  }

}

static void
_fingerprintSortGroupClause(FingerprintContext *ctx, const SortGroupClause *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->eqop != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->eqop);
    _fingerprintString(ctx, "eqop");
    _fingerprintString(ctx, buffer);
  }

  if (node->hashable) {
    _fingerprintString(ctx, "hashable");
    _fingerprintString(ctx, "true");
  }

  if (node->nulls_first) {
    _fingerprintString(ctx, "nulls_first");
    _fingerprintString(ctx, "true");
  }

  if (node->reverse_sort) {
    _fingerprintString(ctx, "reverse_sort");
    _fingerprintString(ctx, "true");
  }

  if (node->sortop != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->sortop);
    _fingerprintString(ctx, "sortop");
    _fingerprintString(ctx, buffer);
  }

  if (node->tleSortGroupRef != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->tleSortGroupRef);
    _fingerprintString(ctx, "tleSortGroupRef");
    _fingerprintString(ctx, buffer);
  }

}

static void
_fingerprintGroupingSet(FingerprintContext *ctx, const GroupingSet *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->content != NULL && node->content->length > 0)
    _fingerprintChildList(ctx, node->content, node, "content", depth);

  _fingerprintString(ctx, "kind");
  _fingerprintString(ctx, _enumToStringGroupingSetKind(node->kind));

  // Intentionally ignoring node->location for fingerprinting

}

static void
_fingerprintWindowClause(FingerprintContext *ctx, const WindowClause *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->copiedOrder) {
    _fingerprintString(ctx, "copiedOrder");
    _fingerprintString(ctx, "true");
  }

  if (node->endInRangeFunc != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->endInRangeFunc);
    _fingerprintString(ctx, "endInRangeFunc");
    _fingerprintString(ctx, buffer);
  }

  if (node->endOffset != NULL)
    _fingerprintChildNode(ctx, node->endOffset, node, "endOffset", depth);

  if (node->frameOptions != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->frameOptions);
    _fingerprintString(ctx, "frameOptions");
    _fingerprintString(ctx, buffer);
  }

  if (node->inRangeAsc) {
    _fingerprintString(ctx, "inRangeAsc");
    _fingerprintString(ctx, "true");
  }

  if (node->inRangeColl != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->inRangeColl);
    _fingerprintString(ctx, "inRangeColl");
    _fingerprintString(ctx, buffer);
  }

  if (node->inRangeNullsFirst) {
    _fingerprintString(ctx, "inRangeNullsFirst");
    _fingerprintString(ctx, "true");
  }

  if (node->name != NULL) {
    _fingerprintString(ctx, "name");
    _fingerprintString(ctx, node->name);
  }

  if (node->orderClause != NULL && node->orderClause->length > 0)
    _fingerprintChildList(ctx, node->orderClause, node, "orderClause", depth);

  if (node->partitionClause != NULL && node->partitionClause->length > 0)
    _fingerprintChildList(ctx, node->partitionClause, node, "partitionClause", depth);

  if (node->refname != NULL) {
    _fingerprintString(ctx, "refname");
    _fingerprintString(ctx, node->refname);
  }

  if (node->startInRangeFunc != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->startInRangeFunc);
    _fingerprintString(ctx, "startInRangeFunc");
    _fingerprintString(ctx, buffer);
  }

  if (node->startOffset != NULL)
    _fingerprintChildNode(ctx, node->startOffset, node, "startOffset", depth);

  if (node->winref != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->winref);
    _fingerprintString(ctx, "winref");
    _fingerprintString(ctx, buffer);
  }

}

static void
_fingerprintRowMarkClause(FingerprintContext *ctx, const RowMarkClause *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->pushedDown) {
    _fingerprintString(ctx, "pushedDown");
    _fingerprintString(ctx, "true");
  }

  if (node->rti != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->rti);
    _fingerprintString(ctx, "rti");
    _fingerprintString(ctx, buffer);
  }

  _fingerprintString(ctx, "strength");
  _fingerprintString(ctx, _enumToStringLockClauseStrength(node->strength));

  _fingerprintString(ctx, "waitPolicy");
  _fingerprintString(ctx, _enumToStringLockWaitPolicy(node->waitPolicy));

}

static void
_fingerprintWithClause(FingerprintContext *ctx, const WithClause *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->ctes != NULL && node->ctes->length > 0)
    _fingerprintChildList(ctx, node->ctes, node, "ctes", depth);

  // Intentionally ignoring node->location for fingerprinting

  if (node->recursive) {
    _fingerprintString(ctx, "recursive");
    _fingerprintString(ctx, "true");
  }

}

static void
_fingerprintInferClause(FingerprintContext *ctx, const InferClause *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->conname != NULL) {
    _fingerprintString(ctx, "conname");
    _fingerprintString(ctx, node->conname);
  }

  if (node->indexElems != NULL && node->indexElems->length > 0)
    _fingerprintChildList(ctx, node->indexElems, node, "indexElems", depth);

  // Intentionally ignoring node->location for fingerprinting

  if (node->whereClause != NULL)
    _fingerprintChildNode(ctx, node->whereClause, node, "whereClause", depth);

}

static void
_fingerprintOnConflictClause(FingerprintContext *ctx, const OnConflictClause *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintString(ctx, "action");
  _fingerprintString(ctx, _enumToStringOnConflictAction(node->action));

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

  if (node->search_breadth_first) {
    _fingerprintString(ctx, "search_breadth_first");
    _fingerprintString(ctx, "true");
  }

  if (node->search_col_list != NULL && node->search_col_list->length > 0)
    _fingerprintChildList(ctx, node->search_col_list, node, "search_col_list", depth);

  if (node->search_seq_column != NULL) {
    _fingerprintString(ctx, "search_seq_column");
    _fingerprintString(ctx, node->search_seq_column);
  }

}

static void
_fingerprintCTECycleClause(FingerprintContext *ctx, const CTECycleClause *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->cycle_col_list != NULL && node->cycle_col_list->length > 0)
    _fingerprintChildList(ctx, node->cycle_col_list, node, "cycle_col_list", depth);

  if (node->cycle_mark_collation != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->cycle_mark_collation);
    _fingerprintString(ctx, "cycle_mark_collation");
    _fingerprintString(ctx, buffer);
  }

  if (node->cycle_mark_column != NULL) {
    _fingerprintString(ctx, "cycle_mark_column");
    _fingerprintString(ctx, node->cycle_mark_column);
  }

  if (node->cycle_mark_default != NULL)
    _fingerprintChildNode(ctx, node->cycle_mark_default, node, "cycle_mark_default", depth);

  if (node->cycle_mark_neop != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->cycle_mark_neop);
    _fingerprintString(ctx, "cycle_mark_neop");
    _fingerprintString(ctx, buffer);
  }

  if (node->cycle_mark_type != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->cycle_mark_type);
    _fingerprintString(ctx, "cycle_mark_type");
    _fingerprintString(ctx, buffer);
  }

  if (node->cycle_mark_typmod != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->cycle_mark_typmod);
    _fingerprintString(ctx, "cycle_mark_typmod");
    _fingerprintString(ctx, buffer);
  }

  if (node->cycle_mark_value != NULL)
    _fingerprintChildNode(ctx, node->cycle_mark_value, node, "cycle_mark_value", depth);

  if (node->cycle_path_column != NULL) {
    _fingerprintString(ctx, "cycle_path_column");
    _fingerprintString(ctx, node->cycle_path_column);
  }

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

  _fingerprintString(ctx, "ctematerialized");
  _fingerprintString(ctx, _enumToStringCTEMaterialize(node->ctematerialized));

  if (node->ctename != NULL) {
    _fingerprintString(ctx, "ctename");
    _fingerprintString(ctx, node->ctename);
  }

  if (node->ctequery != NULL)
    _fingerprintChildNode(ctx, node->ctequery, node, "ctequery", depth);

  if (node->cterecursive) {
    _fingerprintString(ctx, "cterecursive");
    _fingerprintString(ctx, "true");
  }

  if (node->cterefcount != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->cterefcount);
    _fingerprintString(ctx, "cterefcount");
    _fingerprintString(ctx, buffer);
  }

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
  _fingerprintString(ctx, "commandType");
  _fingerprintString(ctx, _enumToStringCmdType(node->commandType));

  if (node->condition != NULL)
    _fingerprintChildNode(ctx, node->condition, node, "condition", depth);

  _fingerprintString(ctx, "matchKind");
  _fingerprintString(ctx, _enumToStringMergeMatchKind(node->matchKind));

  _fingerprintString(ctx, "override");
  _fingerprintString(ctx, _enumToStringOverridingKind(node->override));

  if (node->targetList != NULL && node->targetList->length > 0)
    _fingerprintChildList(ctx, node->targetList, node, "targetList", depth);

  if (node->values != NULL && node->values->length > 0)
    _fingerprintChildList(ctx, node->values, node, "values", depth);

}

static void
_fingerprintReturningOption(FingerprintContext *ctx, const ReturningOption *node, const void *parent, const char *field_name, unsigned int depth)
{
  // Intentionally ignoring node->location for fingerprinting

  _fingerprintString(ctx, "option");
  _fingerprintString(ctx, _enumToStringReturningOptionKind(node->option));

  if (node->value != NULL) {
    _fingerprintString(ctx, "value");
    _fingerprintString(ctx, node->value);
  }

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
  if (node->isNew) {
    _fingerprintString(ctx, "isNew");
    _fingerprintString(ctx, "true");
  }

  if (node->isTable) {
    _fingerprintString(ctx, "isTable");
    _fingerprintString(ctx, "true");
  }

  if (node->name != NULL) {
    _fingerprintString(ctx, "name");
    _fingerprintString(ctx, node->name);
  }

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
  if (node->name != NULL) {
    _fingerprintString(ctx, "name");
    _fingerprintString(ctx, node->name);
  }

  if (node->val != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "val");
    _fingerprintJsonValueExpr(ctx, node->val, node, "val", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

}

static void
_fingerprintJsonFuncExpr(FingerprintContext *ctx, const JsonFuncExpr *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->column_name != NULL) {
    _fingerprintString(ctx, "column_name");
    _fingerprintString(ctx, node->column_name);
  }

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

  _fingerprintString(ctx, "op");
  _fingerprintString(ctx, _enumToStringJsonExprOp(node->op));

  if (node->output != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "output");
    _fingerprintJsonOutput(ctx, node->output, node, "output", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  if (node->passing != NULL && node->passing->length > 0)
    _fingerprintChildList(ctx, node->passing, node, "passing", depth);

  if (node->pathspec != NULL)
    _fingerprintChildNode(ctx, node->pathspec, node, "pathspec", depth);

  _fingerprintString(ctx, "quotes");
  _fingerprintString(ctx, _enumToStringJsonQuotes(node->quotes));

  _fingerprintString(ctx, "wrapper");
  _fingerprintString(ctx, _enumToStringJsonWrapper(node->wrapper));

}

static void
_fingerprintJsonTablePathSpec(FingerprintContext *ctx, const JsonTablePathSpec *node, const void *parent, const char *field_name, unsigned int depth)
{
  // Intentionally ignoring node->location for fingerprinting

  if (node->name != NULL) {
    _fingerprintString(ctx, "name");
    _fingerprintString(ctx, node->name);
  }

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

  if (node->lateral) {
    _fingerprintString(ctx, "lateral");
    _fingerprintString(ctx, "true");
  }

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
  _fingerprintString(ctx, "coltype");
  _fingerprintString(ctx, _enumToStringJsonTableColumnType(node->coltype));

  if (node->columns != NULL && node->columns->length > 0)
    _fingerprintChildList(ctx, node->columns, node, "columns", depth);

  if (node->format != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "format");
    _fingerprintJsonFormat(ctx, node->format, node, "format", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  // Intentionally ignoring node->location for fingerprinting

  if (node->name != NULL) {
    _fingerprintString(ctx, "name");
    _fingerprintString(ctx, node->name);
  }

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

  _fingerprintString(ctx, "quotes");
  _fingerprintString(ctx, _enumToStringJsonQuotes(node->quotes));

  if (node->typeName != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "typeName");
    _fingerprintTypeName(ctx, node->typeName, node, "typeName", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  _fingerprintString(ctx, "wrapper");
  _fingerprintString(ctx, _enumToStringJsonWrapper(node->wrapper));

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

  if (node->unique_keys) {
    _fingerprintString(ctx, "unique_keys");
    _fingerprintString(ctx, "true");
  }

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
  if (node->absent_on_null) {
    _fingerprintString(ctx, "absent_on_null");
    _fingerprintString(ctx, "true");
  }

  if (node->exprs != NULL && node->exprs->length > 0)
    _fingerprintChildList(ctx, node->exprs, node, "exprs", depth);

  // Intentionally ignoring node->location for fingerprinting

  if (node->output != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "output");
    _fingerprintJsonOutput(ctx, node->output, node, "output", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  if (node->unique) {
    _fingerprintString(ctx, "unique");
    _fingerprintString(ctx, "true");
  }

}

static void
_fingerprintJsonArrayConstructor(FingerprintContext *ctx, const JsonArrayConstructor *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->absent_on_null) {
    _fingerprintString(ctx, "absent_on_null");
    _fingerprintString(ctx, "true");
  }

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
  if (node->absent_on_null) {
    _fingerprintString(ctx, "absent_on_null");
    _fingerprintString(ctx, "true");
  }

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
  if (node->absent_on_null) {
    _fingerprintString(ctx, "absent_on_null");
    _fingerprintString(ctx, "true");
  }

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

  if (node->unique) {
    _fingerprintString(ctx, "unique");
    _fingerprintString(ctx, "true");
  }

}

static void
_fingerprintJsonArrayAgg(FingerprintContext *ctx, const JsonArrayAgg *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->absent_on_null) {
    _fingerprintString(ctx, "absent_on_null");
    _fingerprintString(ctx, "true");
  }

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

  _fingerprintString(ctx, "override");
  _fingerprintString(ctx, _enumToStringOverridingKind(node->override));

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
  if (node->all) {
    _fingerprintString(ctx, "all");
    _fingerprintString(ctx, "true");
  }

  if (node->distinctClause != NULL && node->distinctClause->length > 0)
    _fingerprintChildList(ctx, node->distinctClause, node, "distinctClause", depth);

  if (node->fromClause != NULL && node->fromClause->length > 0)
    _fingerprintChildList(ctx, node->fromClause, node, "fromClause", depth);

  if (node->groupClause != NULL && node->groupClause->length > 0)
    _fingerprintChildList(ctx, node->groupClause, node, "groupClause", depth);

  if (node->groupDistinct) {
    _fingerprintString(ctx, "groupDistinct");
    _fingerprintString(ctx, "true");
  }

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

  _fingerprintString(ctx, "limitOption");
  _fingerprintString(ctx, _enumToStringLimitOption(node->limitOption));

  if (node->lockingClause != NULL && node->lockingClause->length > 0)
    _fingerprintChildList(ctx, node->lockingClause, node, "lockingClause", depth);

  _fingerprintString(ctx, "op");
  _fingerprintString(ctx, _enumToStringSetOperation(node->op));

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
  if (node->all) {
    _fingerprintString(ctx, "all");
    _fingerprintString(ctx, "true");
  }

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

  _fingerprintString(ctx, "op");
  _fingerprintString(ctx, _enumToStringSetOperation(node->op));

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

  if (node->name != NULL) {
    _fingerprintString(ctx, "name");
    _fingerprintString(ctx, node->name);
  }

  if (node->nnames != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->nnames);
    _fingerprintString(ctx, "nnames");
    _fingerprintString(ctx, buffer);
  }

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

  if (node->if_not_exists) {
    _fingerprintString(ctx, "if_not_exists");
    _fingerprintString(ctx, "true");
  }

  if (node->schemaElts != NULL && node->schemaElts->length > 0)
    _fingerprintChildList(ctx, node->schemaElts, node, "schemaElts", depth);

  if (node->schemaname != NULL) {
    _fingerprintString(ctx, "schemaname");
    _fingerprintString(ctx, node->schemaname);
  }

}

static void
_fingerprintAlterTableStmt(FingerprintContext *ctx, const AlterTableStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->cmds != NULL && node->cmds->length > 0)
    _fingerprintChildList(ctx, node->cmds, node, "cmds", depth);

  if (node->missing_ok) {
    _fingerprintString(ctx, "missing_ok");
    _fingerprintString(ctx, "true");
  }

  _fingerprintString(ctx, "objtype");
  _fingerprintString(ctx, _enumToStringObjectType(node->objtype));

  if (node->relation != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "relation");
    _fingerprintRangeVar(ctx, node->relation, node, "relation", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

}

static void
_fingerprintAlterTableCmd(FingerprintContext *ctx, const AlterTableCmd *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintString(ctx, "behavior");
  _fingerprintString(ctx, _enumToStringDropBehavior(node->behavior));

  if (node->def != NULL)
    _fingerprintChildNode(ctx, node->def, node, "def", depth);

  if (node->missing_ok) {
    _fingerprintString(ctx, "missing_ok");
    _fingerprintString(ctx, "true");
  }

  if (node->name != NULL) {
    _fingerprintString(ctx, "name");
    _fingerprintString(ctx, node->name);
  }

  if (node->newowner != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "newowner");
    _fingerprintRoleSpec(ctx, node->newowner, node, "newowner", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  if (node->num != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->num);
    _fingerprintString(ctx, "num");
    _fingerprintString(ctx, buffer);
  }

  if (node->recurse) {
    _fingerprintString(ctx, "recurse");
    _fingerprintString(ctx, "true");
  }

  _fingerprintString(ctx, "subtype");
  _fingerprintString(ctx, _enumToStringAlterTableType(node->subtype));

}

static void
_fingerprintATAlterConstraint(FingerprintContext *ctx, const ATAlterConstraint *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->alterDeferrability) {
    _fingerprintString(ctx, "alterDeferrability");
    _fingerprintString(ctx, "true");
  }

  if (node->alterEnforceability) {
    _fingerprintString(ctx, "alterEnforceability");
    _fingerprintString(ctx, "true");
  }

  if (node->alterInheritability) {
    _fingerprintString(ctx, "alterInheritability");
    _fingerprintString(ctx, "true");
  }

  if (node->conname != NULL) {
    _fingerprintString(ctx, "conname");
    _fingerprintString(ctx, node->conname);
  }

  if (node->deferrable) {
    _fingerprintString(ctx, "deferrable");
    _fingerprintString(ctx, "true");
  }

  if (node->initdeferred) {
    _fingerprintString(ctx, "initdeferred");
    _fingerprintString(ctx, "true");
  }

  if (node->is_enforced) {
    _fingerprintString(ctx, "is_enforced");
    _fingerprintString(ctx, "true");
  }

  if (node->noinherit) {
    _fingerprintString(ctx, "noinherit");
    _fingerprintString(ctx, "true");
  }

}

static void
_fingerprintReplicaIdentityStmt(FingerprintContext *ctx, const ReplicaIdentityStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->identity_type != 0) {
    char buffer[2] = {node->identity_type, '\0'};
    _fingerprintString(ctx, "identity_type");
    _fingerprintString(ctx, buffer);
  }

  if (node->name != NULL) {
    _fingerprintString(ctx, "name");
    _fingerprintString(ctx, node->name);
  }

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
  _fingerprintString(ctx, "behavior");
  _fingerprintString(ctx, _enumToStringDropBehavior(node->behavior));

  if (node->def != NULL)
    _fingerprintChildNode(ctx, node->def, node, "def", depth);

  if (node->missing_ok) {
    _fingerprintString(ctx, "missing_ok");
    _fingerprintString(ctx, "true");
  }

  if (node->name != NULL) {
    _fingerprintString(ctx, "name");
    _fingerprintString(ctx, node->name);
  }

  if (node->subtype != 0) {
    char buffer[2] = {node->subtype, '\0'};
    _fingerprintString(ctx, "subtype");
    _fingerprintString(ctx, buffer);
  }

  if (node->typeName != NULL && node->typeName->length > 0)
    _fingerprintChildList(ctx, node->typeName, node, "typeName", depth);

}

static void
_fingerprintGrantStmt(FingerprintContext *ctx, const GrantStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintString(ctx, "behavior");
  _fingerprintString(ctx, _enumToStringDropBehavior(node->behavior));

  if (node->grant_option) {
    _fingerprintString(ctx, "grant_option");
    _fingerprintString(ctx, "true");
  }

  if (node->grantees != NULL && node->grantees->length > 0)
    _fingerprintChildList(ctx, node->grantees, node, "grantees", depth);

  if (node->grantor != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "grantor");
    _fingerprintRoleSpec(ctx, node->grantor, node, "grantor", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  if (node->is_grant) {
    _fingerprintString(ctx, "is_grant");
    _fingerprintString(ctx, "true");
  }

  if (node->objects != NULL && node->objects->length > 0)
    _fingerprintChildList(ctx, node->objects, node, "objects", depth);

  _fingerprintString(ctx, "objtype");
  _fingerprintString(ctx, _enumToStringObjectType(node->objtype));

  if (node->privileges != NULL && node->privileges->length > 0)
    _fingerprintChildList(ctx, node->privileges, node, "privileges", depth);

  _fingerprintString(ctx, "targtype");
  _fingerprintString(ctx, _enumToStringGrantTargetType(node->targtype));

}

static void
_fingerprintObjectWithArgs(FingerprintContext *ctx, const ObjectWithArgs *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->args_unspecified) {
    _fingerprintString(ctx, "args_unspecified");
    _fingerprintString(ctx, "true");
  }

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

  if (node->priv_name != NULL) {
    _fingerprintString(ctx, "priv_name");
    _fingerprintString(ctx, node->priv_name);
  }

}

static void
_fingerprintGrantRoleStmt(FingerprintContext *ctx, const GrantRoleStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintString(ctx, "behavior");
  _fingerprintString(ctx, _enumToStringDropBehavior(node->behavior));

  if (node->granted_roles != NULL && node->granted_roles->length > 0)
    _fingerprintChildList(ctx, node->granted_roles, node, "granted_roles", depth);

  if (node->grantee_roles != NULL && node->grantee_roles->length > 0)
    _fingerprintChildList(ctx, node->grantee_roles, node, "grantee_roles", depth);

  if (node->grantor != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "grantor");
    _fingerprintRoleSpec(ctx, node->grantor, node, "grantor", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  if (node->is_grant) {
    _fingerprintString(ctx, "is_grant");
    _fingerprintString(ctx, "true");
  }

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

  if (node->filename != NULL) {
    _fingerprintString(ctx, "filename");
    _fingerprintString(ctx, node->filename);
  }

  if (node->is_from) {
    _fingerprintString(ctx, "is_from");
    _fingerprintString(ctx, "true");
  }

  if (node->is_program) {
    _fingerprintString(ctx, "is_program");
    _fingerprintString(ctx, "true");
  }

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

  if (node->is_local) {
    _fingerprintString(ctx, "is_local");
    _fingerprintString(ctx, "true");
  }

  // Intentionally ignoring node->jumble_args for fingerprinting

  _fingerprintString(ctx, "kind");
  _fingerprintString(ctx, _enumToStringVariableSetKind(node->kind));

  // Intentionally ignoring node->location for fingerprinting

  if (node->name != NULL) {
    _fingerprintString(ctx, "name");
    _fingerprintString(ctx, node->name);
  }

}

static void
_fingerprintVariableShowStmt(FingerprintContext *ctx, const VariableShowStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->name != NULL) {
    _fingerprintString(ctx, "name");
    _fingerprintString(ctx, node->name);
  }

}

static void
_fingerprintCreateStmt(FingerprintContext *ctx, const CreateStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->accessMethod != NULL) {
    _fingerprintString(ctx, "accessMethod");
    _fingerprintString(ctx, node->accessMethod);
  }

  if (node->constraints != NULL && node->constraints->length > 0)
    _fingerprintChildList(ctx, node->constraints, node, "constraints", depth);

  if (node->if_not_exists) {
    _fingerprintString(ctx, "if_not_exists");
    _fingerprintString(ctx, "true");
  }

  if (node->inhRelations != NULL && node->inhRelations->length > 0)
    _fingerprintChildList(ctx, node->inhRelations, node, "inhRelations", depth);

  if (node->nnconstraints != NULL && node->nnconstraints->length > 0)
    _fingerprintChildList(ctx, node->nnconstraints, node, "nnconstraints", depth);

  if (node->ofTypename != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "ofTypename");
    _fingerprintTypeName(ctx, node->ofTypename, node, "ofTypename", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  _fingerprintString(ctx, "oncommit");
  _fingerprintString(ctx, _enumToStringOnCommitAction(node->oncommit));

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

  if (node->tablespacename != NULL) {
    _fingerprintString(ctx, "tablespacename");
    _fingerprintString(ctx, node->tablespacename);
  }

}

static void
_fingerprintConstraint(FingerprintContext *ctx, const Constraint *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->access_method != NULL) {
    _fingerprintString(ctx, "access_method");
    _fingerprintString(ctx, node->access_method);
  }

  if (node->conname != NULL) {
    _fingerprintString(ctx, "conname");
    _fingerprintString(ctx, node->conname);
  }

  _fingerprintString(ctx, "contype");
  _fingerprintString(ctx, _enumToStringConstrType(node->contype));

  if (node->cooked_expr != NULL) {
    _fingerprintString(ctx, "cooked_expr");
    _fingerprintString(ctx, node->cooked_expr);
  }

  if (node->deferrable) {
    _fingerprintString(ctx, "deferrable");
    _fingerprintString(ctx, "true");
  }

  if (node->exclusions != NULL && node->exclusions->length > 0)
    _fingerprintChildList(ctx, node->exclusions, node, "exclusions", depth);

  if (node->fk_attrs != NULL && node->fk_attrs->length > 0)
    _fingerprintChildList(ctx, node->fk_attrs, node, "fk_attrs", depth);

  if (node->fk_del_action != 0) {
    char buffer[2] = {node->fk_del_action, '\0'};
    _fingerprintString(ctx, "fk_del_action");
    _fingerprintString(ctx, buffer);
  }

  if (node->fk_del_set_cols != NULL && node->fk_del_set_cols->length > 0)
    _fingerprintChildList(ctx, node->fk_del_set_cols, node, "fk_del_set_cols", depth);

  if (node->fk_matchtype != 0) {
    char buffer[2] = {node->fk_matchtype, '\0'};
    _fingerprintString(ctx, "fk_matchtype");
    _fingerprintString(ctx, buffer);
  }

  if (node->fk_upd_action != 0) {
    char buffer[2] = {node->fk_upd_action, '\0'};
    _fingerprintString(ctx, "fk_upd_action");
    _fingerprintString(ctx, buffer);
  }

  if (node->fk_with_period) {
    _fingerprintString(ctx, "fk_with_period");
    _fingerprintString(ctx, "true");
  }

  if (node->generated_kind != 0) {
    char buffer[2] = {node->generated_kind, '\0'};
    _fingerprintString(ctx, "generated_kind");
    _fingerprintString(ctx, buffer);
  }

  if (node->generated_when != 0) {
    char buffer[2] = {node->generated_when, '\0'};
    _fingerprintString(ctx, "generated_when");
    _fingerprintString(ctx, buffer);
  }

  if (node->including != NULL && node->including->length > 0)
    _fingerprintChildList(ctx, node->including, node, "including", depth);

  if (node->indexname != NULL) {
    _fingerprintString(ctx, "indexname");
    _fingerprintString(ctx, node->indexname);
  }

  if (node->indexspace != NULL) {
    _fingerprintString(ctx, "indexspace");
    _fingerprintString(ctx, node->indexspace);
  }

  if (node->initdeferred) {
    _fingerprintString(ctx, "initdeferred");
    _fingerprintString(ctx, "true");
  }

  if (node->initially_valid) {
    _fingerprintString(ctx, "initially_valid");
    _fingerprintString(ctx, "true");
  }

  if (node->is_enforced) {
    _fingerprintString(ctx, "is_enforced");
    _fingerprintString(ctx, "true");
  }

  if (node->is_no_inherit) {
    _fingerprintString(ctx, "is_no_inherit");
    _fingerprintString(ctx, "true");
  }

  if (node->keys != NULL && node->keys->length > 0)
    _fingerprintChildList(ctx, node->keys, node, "keys", depth);

  // Intentionally ignoring node->location for fingerprinting

  if (node->nulls_not_distinct) {
    _fingerprintString(ctx, "nulls_not_distinct");
    _fingerprintString(ctx, "true");
  }

  if (node->old_conpfeqop != NULL && node->old_conpfeqop->length > 0)
    _fingerprintChildList(ctx, node->old_conpfeqop, node, "old_conpfeqop", depth);

  if (node->old_pktable_oid != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->old_pktable_oid);
    _fingerprintString(ctx, "old_pktable_oid");
    _fingerprintString(ctx, buffer);
  }

  if (node->options != NULL && node->options->length > 0)
    _fingerprintChildList(ctx, node->options, node, "options", depth);

  if (node->pk_attrs != NULL && node->pk_attrs->length > 0)
    _fingerprintChildList(ctx, node->pk_attrs, node, "pk_attrs", depth);

  if (node->pk_with_period) {
    _fingerprintString(ctx, "pk_with_period");
    _fingerprintString(ctx, "true");
  }

  if (node->pktable != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "pktable");
    _fingerprintRangeVar(ctx, node->pktable, node, "pktable", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  if (node->raw_expr != NULL)
    _fingerprintChildNode(ctx, node->raw_expr, node, "raw_expr", depth);

  if (node->reset_default_tblspc) {
    _fingerprintString(ctx, "reset_default_tblspc");
    _fingerprintString(ctx, "true");
  }

  if (node->skip_validation) {
    _fingerprintString(ctx, "skip_validation");
    _fingerprintString(ctx, "true");
  }

  if (node->where_clause != NULL)
    _fingerprintChildNode(ctx, node->where_clause, node, "where_clause", depth);

  if (node->without_overlaps) {
    _fingerprintString(ctx, "without_overlaps");
    _fingerprintString(ctx, "true");
  }

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

  if (node->tablespacename != NULL) {
    _fingerprintString(ctx, "tablespacename");
    _fingerprintString(ctx, node->tablespacename);
  }

}

static void
_fingerprintDropTableSpaceStmt(FingerprintContext *ctx, const DropTableSpaceStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->missing_ok) {
    _fingerprintString(ctx, "missing_ok");
    _fingerprintString(ctx, "true");
  }

  if (node->tablespacename != NULL) {
    _fingerprintString(ctx, "tablespacename");
    _fingerprintString(ctx, node->tablespacename);
  }

}

static void
_fingerprintAlterTableSpaceOptionsStmt(FingerprintContext *ctx, const AlterTableSpaceOptionsStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->isReset) {
    _fingerprintString(ctx, "isReset");
    _fingerprintString(ctx, "true");
  }

  if (node->options != NULL && node->options->length > 0)
    _fingerprintChildList(ctx, node->options, node, "options", depth);

  if (node->tablespacename != NULL) {
    _fingerprintString(ctx, "tablespacename");
    _fingerprintString(ctx, node->tablespacename);
  }

}

static void
_fingerprintAlterTableMoveAllStmt(FingerprintContext *ctx, const AlterTableMoveAllStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->new_tablespacename != NULL) {
    _fingerprintString(ctx, "new_tablespacename");
    _fingerprintString(ctx, node->new_tablespacename);
  }

  if (node->nowait) {
    _fingerprintString(ctx, "nowait");
    _fingerprintString(ctx, "true");
  }

  _fingerprintString(ctx, "objtype");
  _fingerprintString(ctx, _enumToStringObjectType(node->objtype));

  if (node->orig_tablespacename != NULL) {
    _fingerprintString(ctx, "orig_tablespacename");
    _fingerprintString(ctx, node->orig_tablespacename);
  }

  if (node->roles != NULL && node->roles->length > 0)
    _fingerprintChildList(ctx, node->roles, node, "roles", depth);

}

static void
_fingerprintCreateExtensionStmt(FingerprintContext *ctx, const CreateExtensionStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->extname != NULL) {
    _fingerprintString(ctx, "extname");
    _fingerprintString(ctx, node->extname);
  }

  if (node->if_not_exists) {
    _fingerprintString(ctx, "if_not_exists");
    _fingerprintString(ctx, "true");
  }

  if (node->options != NULL && node->options->length > 0)
    _fingerprintChildList(ctx, node->options, node, "options", depth);

}

static void
_fingerprintAlterExtensionStmt(FingerprintContext *ctx, const AlterExtensionStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->extname != NULL) {
    _fingerprintString(ctx, "extname");
    _fingerprintString(ctx, node->extname);
  }

  if (node->options != NULL && node->options->length > 0)
    _fingerprintChildList(ctx, node->options, node, "options", depth);

}

static void
_fingerprintAlterExtensionContentsStmt(FingerprintContext *ctx, const AlterExtensionContentsStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->action != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->action);
    _fingerprintString(ctx, "action");
    _fingerprintString(ctx, buffer);
  }

  if (node->extname != NULL) {
    _fingerprintString(ctx, "extname");
    _fingerprintString(ctx, node->extname);
  }

  if (node->object != NULL)
    _fingerprintChildNode(ctx, node->object, node, "object", depth);

  _fingerprintString(ctx, "objtype");
  _fingerprintString(ctx, _enumToStringObjectType(node->objtype));

}

static void
_fingerprintCreateFdwStmt(FingerprintContext *ctx, const CreateFdwStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->fdwname != NULL) {
    _fingerprintString(ctx, "fdwname");
    _fingerprintString(ctx, node->fdwname);
  }

  if (node->func_options != NULL && node->func_options->length > 0)
    _fingerprintChildList(ctx, node->func_options, node, "func_options", depth);

  if (node->options != NULL && node->options->length > 0)
    _fingerprintChildList(ctx, node->options, node, "options", depth);

}

static void
_fingerprintAlterFdwStmt(FingerprintContext *ctx, const AlterFdwStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->fdwname != NULL) {
    _fingerprintString(ctx, "fdwname");
    _fingerprintString(ctx, node->fdwname);
  }

  if (node->func_options != NULL && node->func_options->length > 0)
    _fingerprintChildList(ctx, node->func_options, node, "func_options", depth);

  if (node->options != NULL && node->options->length > 0)
    _fingerprintChildList(ctx, node->options, node, "options", depth);

}

static void
_fingerprintCreateForeignServerStmt(FingerprintContext *ctx, const CreateForeignServerStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->fdwname != NULL) {
    _fingerprintString(ctx, "fdwname");
    _fingerprintString(ctx, node->fdwname);
  }

  if (node->if_not_exists) {
    _fingerprintString(ctx, "if_not_exists");
    _fingerprintString(ctx, "true");
  }

  if (node->options != NULL && node->options->length > 0)
    _fingerprintChildList(ctx, node->options, node, "options", depth);

  if (node->servername != NULL) {
    _fingerprintString(ctx, "servername");
    _fingerprintString(ctx, node->servername);
  }

  if (node->servertype != NULL) {
    _fingerprintString(ctx, "servertype");
    _fingerprintString(ctx, node->servertype);
  }

  if (node->version != NULL) {
    _fingerprintString(ctx, "version");
    _fingerprintString(ctx, node->version);
  }

}

static void
_fingerprintAlterForeignServerStmt(FingerprintContext *ctx, const AlterForeignServerStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->has_version) {
    _fingerprintString(ctx, "has_version");
    _fingerprintString(ctx, "true");
  }

  if (node->options != NULL && node->options->length > 0)
    _fingerprintChildList(ctx, node->options, node, "options", depth);

  if (node->servername != NULL) {
    _fingerprintString(ctx, "servername");
    _fingerprintString(ctx, node->servername);
  }

  if (node->version != NULL) {
    _fingerprintString(ctx, "version");
    _fingerprintString(ctx, node->version);
  }

}

static void
_fingerprintCreateForeignTableStmt(FingerprintContext *ctx, const CreateForeignTableStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintString(ctx, "base");
  _fingerprintCreateStmt(ctx, (const CreateStmt*) &node->base, node, "base", depth);
  if (node->options != NULL && node->options->length > 0)
    _fingerprintChildList(ctx, node->options, node, "options", depth);

  if (node->servername != NULL) {
    _fingerprintString(ctx, "servername");
    _fingerprintString(ctx, node->servername);
  }

}

static void
_fingerprintCreateUserMappingStmt(FingerprintContext *ctx, const CreateUserMappingStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->if_not_exists) {
    _fingerprintString(ctx, "if_not_exists");
    _fingerprintString(ctx, "true");
  }

  if (node->options != NULL && node->options->length > 0)
    _fingerprintChildList(ctx, node->options, node, "options", depth);

  if (node->servername != NULL) {
    _fingerprintString(ctx, "servername");
    _fingerprintString(ctx, node->servername);
  }

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

  if (node->servername != NULL) {
    _fingerprintString(ctx, "servername");
    _fingerprintString(ctx, node->servername);
  }

  if (node->user != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "user");
    _fingerprintRoleSpec(ctx, node->user, node, "user", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

}

static void
_fingerprintDropUserMappingStmt(FingerprintContext *ctx, const DropUserMappingStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->missing_ok) {
    _fingerprintString(ctx, "missing_ok");
    _fingerprintString(ctx, "true");
  }

  if (node->servername != NULL) {
    _fingerprintString(ctx, "servername");
    _fingerprintString(ctx, node->servername);
  }

  if (node->user != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "user");
    _fingerprintRoleSpec(ctx, node->user, node, "user", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

}

static void
_fingerprintImportForeignSchemaStmt(FingerprintContext *ctx, const ImportForeignSchemaStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintString(ctx, "list_type");
  _fingerprintString(ctx, _enumToStringImportForeignSchemaType(node->list_type));

  if (node->local_schema != NULL) {
    _fingerprintString(ctx, "local_schema");
    _fingerprintString(ctx, node->local_schema);
  }

  if (node->options != NULL && node->options->length > 0)
    _fingerprintChildList(ctx, node->options, node, "options", depth);

  if (node->remote_schema != NULL) {
    _fingerprintString(ctx, "remote_schema");
    _fingerprintString(ctx, node->remote_schema);
  }

  if (node->server_name != NULL) {
    _fingerprintString(ctx, "server_name");
    _fingerprintString(ctx, node->server_name);
  }

  if (node->table_list != NULL && node->table_list->length > 0)
    _fingerprintChildList(ctx, node->table_list, node, "table_list", depth);

}

static void
_fingerprintCreatePolicyStmt(FingerprintContext *ctx, const CreatePolicyStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->cmd_name != NULL) {
    _fingerprintString(ctx, "cmd_name");
    _fingerprintString(ctx, node->cmd_name);
  }

  if (node->permissive) {
    _fingerprintString(ctx, "permissive");
    _fingerprintString(ctx, "true");
  }

  if (node->policy_name != NULL) {
    _fingerprintString(ctx, "policy_name");
    _fingerprintString(ctx, node->policy_name);
  }

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
  if (node->policy_name != NULL) {
    _fingerprintString(ctx, "policy_name");
    _fingerprintString(ctx, node->policy_name);
  }

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
  if (node->amname != NULL) {
    _fingerprintString(ctx, "amname");
    _fingerprintString(ctx, node->amname);
  }

  if (node->amtype != 0) {
    char buffer[2] = {node->amtype, '\0'};
    _fingerprintString(ctx, "amtype");
    _fingerprintString(ctx, buffer);
  }

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

  if (node->deferrable) {
    _fingerprintString(ctx, "deferrable");
    _fingerprintString(ctx, "true");
  }

  if (node->events != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->events);
    _fingerprintString(ctx, "events");
    _fingerprintString(ctx, buffer);
  }

  if (node->funcname != NULL && node->funcname->length > 0)
    _fingerprintChildList(ctx, node->funcname, node, "funcname", depth);

  if (node->initdeferred) {
    _fingerprintString(ctx, "initdeferred");
    _fingerprintString(ctx, "true");
  }

  if (node->isconstraint) {
    _fingerprintString(ctx, "isconstraint");
    _fingerprintString(ctx, "true");
  }

  if (node->relation != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "relation");
    _fingerprintRangeVar(ctx, node->relation, node, "relation", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  if (node->replace) {
    _fingerprintString(ctx, "replace");
    _fingerprintString(ctx, "true");
  }

  if (node->row) {
    _fingerprintString(ctx, "row");
    _fingerprintString(ctx, "true");
  }

  if (node->timing != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->timing);
    _fingerprintString(ctx, "timing");
    _fingerprintString(ctx, buffer);
  }

  if (node->transitionRels != NULL && node->transitionRels->length > 0)
    _fingerprintChildList(ctx, node->transitionRels, node, "transitionRels", depth);

  if (node->trigname != NULL) {
    _fingerprintString(ctx, "trigname");
    _fingerprintString(ctx, node->trigname);
  }

  if (node->whenClause != NULL)
    _fingerprintChildNode(ctx, node->whenClause, node, "whenClause", depth);

}

static void
_fingerprintCreateEventTrigStmt(FingerprintContext *ctx, const CreateEventTrigStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->eventname != NULL) {
    _fingerprintString(ctx, "eventname");
    _fingerprintString(ctx, node->eventname);
  }

  if (node->funcname != NULL && node->funcname->length > 0)
    _fingerprintChildList(ctx, node->funcname, node, "funcname", depth);

  if (node->trigname != NULL) {
    _fingerprintString(ctx, "trigname");
    _fingerprintString(ctx, node->trigname);
  }

  if (node->whenclause != NULL && node->whenclause->length > 0)
    _fingerprintChildList(ctx, node->whenclause, node, "whenclause", depth);

}

static void
_fingerprintAlterEventTrigStmt(FingerprintContext *ctx, const AlterEventTrigStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->tgenabled != 0) {
    char buffer[2] = {node->tgenabled, '\0'};
    _fingerprintString(ctx, "tgenabled");
    _fingerprintString(ctx, buffer);
  }

  if (node->trigname != NULL) {
    _fingerprintString(ctx, "trigname");
    _fingerprintString(ctx, node->trigname);
  }

}

static void
_fingerprintCreatePLangStmt(FingerprintContext *ctx, const CreatePLangStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->plhandler != NULL && node->plhandler->length > 0)
    _fingerprintChildList(ctx, node->plhandler, node, "plhandler", depth);

  if (node->plinline != NULL && node->plinline->length > 0)
    _fingerprintChildList(ctx, node->plinline, node, "plinline", depth);

  if (node->plname != NULL) {
    _fingerprintString(ctx, "plname");
    _fingerprintString(ctx, node->plname);
  }

  if (node->pltrusted) {
    _fingerprintString(ctx, "pltrusted");
    _fingerprintString(ctx, "true");
  }

  if (node->plvalidator != NULL && node->plvalidator->length > 0)
    _fingerprintChildList(ctx, node->plvalidator, node, "plvalidator", depth);

  if (node->replace) {
    _fingerprintString(ctx, "replace");
    _fingerprintString(ctx, "true");
  }

}

static void
_fingerprintCreateRoleStmt(FingerprintContext *ctx, const CreateRoleStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->options != NULL && node->options->length > 0)
    _fingerprintChildList(ctx, node->options, node, "options", depth);

  if (node->role != NULL) {
    _fingerprintString(ctx, "role");
    _fingerprintString(ctx, node->role);
  }

  _fingerprintString(ctx, "stmt_type");
  _fingerprintString(ctx, _enumToStringRoleStmtType(node->stmt_type));

}

static void
_fingerprintAlterRoleStmt(FingerprintContext *ctx, const AlterRoleStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->action != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->action);
    _fingerprintString(ctx, "action");
    _fingerprintString(ctx, buffer);
  }

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
  if (node->database != NULL) {
    _fingerprintString(ctx, "database");
    _fingerprintString(ctx, node->database);
  }

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
  if (node->missing_ok) {
    _fingerprintString(ctx, "missing_ok");
    _fingerprintString(ctx, "true");
  }

  if (node->roles != NULL && node->roles->length > 0)
    _fingerprintChildList(ctx, node->roles, node, "roles", depth);

}

static void
_fingerprintCreateSeqStmt(FingerprintContext *ctx, const CreateSeqStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->for_identity) {
    _fingerprintString(ctx, "for_identity");
    _fingerprintString(ctx, "true");
  }

  if (node->if_not_exists) {
    _fingerprintString(ctx, "if_not_exists");
    _fingerprintString(ctx, "true");
  }

  if (node->options != NULL && node->options->length > 0)
    _fingerprintChildList(ctx, node->options, node, "options", depth);

  if (node->ownerId != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->ownerId);
    _fingerprintString(ctx, "ownerId");
    _fingerprintString(ctx, buffer);
  }

  if (node->sequence != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "sequence");
    _fingerprintRangeVar(ctx, node->sequence, node, "sequence", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

}

static void
_fingerprintAlterSeqStmt(FingerprintContext *ctx, const AlterSeqStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->for_identity) {
    _fingerprintString(ctx, "for_identity");
    _fingerprintString(ctx, "true");
  }

  if (node->missing_ok) {
    _fingerprintString(ctx, "missing_ok");
    _fingerprintString(ctx, "true");
  }

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

  if (node->if_not_exists) {
    _fingerprintString(ctx, "if_not_exists");
    _fingerprintString(ctx, "true");
  }

  _fingerprintString(ctx, "kind");
  _fingerprintString(ctx, _enumToStringObjectType(node->kind));

  if (node->oldstyle) {
    _fingerprintString(ctx, "oldstyle");
    _fingerprintString(ctx, "true");
  }

  if (node->replace) {
    _fingerprintString(ctx, "replace");
    _fingerprintString(ctx, "true");
  }

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
  if (node->amname != NULL) {
    _fingerprintString(ctx, "amname");
    _fingerprintString(ctx, node->amname);
  }

  if (node->datatype != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "datatype");
    _fingerprintTypeName(ctx, node->datatype, node, "datatype", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  if (node->isDefault) {
    _fingerprintString(ctx, "isDefault");
    _fingerprintString(ctx, "true");
  }

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

  if (node->itemtype != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->itemtype);
    _fingerprintString(ctx, "itemtype");
    _fingerprintString(ctx, buffer);
  }

  if (node->name != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "name");
    _fingerprintObjectWithArgs(ctx, node->name, node, "name", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  if (node->number != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->number);
    _fingerprintString(ctx, "number");
    _fingerprintString(ctx, buffer);
  }

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
  if (node->amname != NULL) {
    _fingerprintString(ctx, "amname");
    _fingerprintString(ctx, node->amname);
  }

  if (node->opfamilyname != NULL && node->opfamilyname->length > 0)
    _fingerprintChildList(ctx, node->opfamilyname, node, "opfamilyname", depth);

}

static void
_fingerprintAlterOpFamilyStmt(FingerprintContext *ctx, const AlterOpFamilyStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->amname != NULL) {
    _fingerprintString(ctx, "amname");
    _fingerprintString(ctx, node->amname);
  }

  if (node->isDrop) {
    _fingerprintString(ctx, "isDrop");
    _fingerprintString(ctx, "true");
  }

  if (node->items != NULL && node->items->length > 0)
    _fingerprintChildList(ctx, node->items, node, "items", depth);

  if (node->opfamilyname != NULL && node->opfamilyname->length > 0)
    _fingerprintChildList(ctx, node->opfamilyname, node, "opfamilyname", depth);

}

static void
_fingerprintDropStmt(FingerprintContext *ctx, const DropStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintString(ctx, "behavior");
  _fingerprintString(ctx, _enumToStringDropBehavior(node->behavior));

  if (node->concurrent) {
    _fingerprintString(ctx, "concurrent");
    _fingerprintString(ctx, "true");
  }

  if (node->missing_ok) {
    _fingerprintString(ctx, "missing_ok");
    _fingerprintString(ctx, "true");
  }

  if (node->objects != NULL && node->objects->length > 0)
    _fingerprintChildList(ctx, node->objects, node, "objects", depth);

  _fingerprintString(ctx, "removeType");
  _fingerprintString(ctx, _enumToStringObjectType(node->removeType));

}

static void
_fingerprintTruncateStmt(FingerprintContext *ctx, const TruncateStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintString(ctx, "behavior");
  _fingerprintString(ctx, _enumToStringDropBehavior(node->behavior));

  if (node->relations != NULL && node->relations->length > 0)
    _fingerprintChildList(ctx, node->relations, node, "relations", depth);

  if (node->restart_seqs) {
    _fingerprintString(ctx, "restart_seqs");
    _fingerprintString(ctx, "true");
  }

}

static void
_fingerprintCommentStmt(FingerprintContext *ctx, const CommentStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->comment != NULL) {
    _fingerprintString(ctx, "comment");
    _fingerprintString(ctx, node->comment);
  }

  if (node->object != NULL)
    _fingerprintChildNode(ctx, node->object, node, "object", depth);

  _fingerprintString(ctx, "objtype");
  _fingerprintString(ctx, _enumToStringObjectType(node->objtype));

}

static void
_fingerprintSecLabelStmt(FingerprintContext *ctx, const SecLabelStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->label != NULL) {
    _fingerprintString(ctx, "label");
    _fingerprintString(ctx, node->label);
  }

  if (node->object != NULL)
    _fingerprintChildNode(ctx, node->object, node, "object", depth);

  _fingerprintString(ctx, "objtype");
  _fingerprintString(ctx, _enumToStringObjectType(node->objtype));

  if (node->provider != NULL) {
    _fingerprintString(ctx, "provider");
    _fingerprintString(ctx, node->provider);
  }

}

static void
_fingerprintDeclareCursorStmt(FingerprintContext *ctx, const DeclareCursorStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->options != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->options);
    _fingerprintString(ctx, "options");
    _fingerprintString(ctx, buffer);
  }

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
  _fingerprintString(ctx, "direction");
  _fingerprintString(ctx, _enumToStringFetchDirection(node->direction));

  if (node->howMany != 0) {
    char buffer[50];
    sprintf(buffer, "%ld", node->howMany);
    _fingerprintString(ctx, "howMany");
    _fingerprintString(ctx, buffer);
  }

  if (node->ismove) {
    _fingerprintString(ctx, "ismove");
    _fingerprintString(ctx, "true");
  }

  // Intentionally ignoring node->portalname for fingerprinting

}

static void
_fingerprintIndexStmt(FingerprintContext *ctx, const IndexStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->accessMethod != NULL) {
    _fingerprintString(ctx, "accessMethod");
    _fingerprintString(ctx, node->accessMethod);
  }

  if (node->concurrent) {
    _fingerprintString(ctx, "concurrent");
    _fingerprintString(ctx, "true");
  }

  if (node->deferrable) {
    _fingerprintString(ctx, "deferrable");
    _fingerprintString(ctx, "true");
  }

  if (node->excludeOpNames != NULL && node->excludeOpNames->length > 0)
    _fingerprintChildList(ctx, node->excludeOpNames, node, "excludeOpNames", depth);

  if (node->idxcomment != NULL) {
    _fingerprintString(ctx, "idxcomment");
    _fingerprintString(ctx, node->idxcomment);
  }

  if (node->idxname != NULL) {
    _fingerprintString(ctx, "idxname");
    _fingerprintString(ctx, node->idxname);
  }

  if (node->if_not_exists) {
    _fingerprintString(ctx, "if_not_exists");
    _fingerprintString(ctx, "true");
  }

  if (node->indexIncludingParams != NULL && node->indexIncludingParams->length > 0)
    _fingerprintChildList(ctx, node->indexIncludingParams, node, "indexIncludingParams", depth);

  if (node->indexOid != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->indexOid);
    _fingerprintString(ctx, "indexOid");
    _fingerprintString(ctx, buffer);
  }

  if (node->indexParams != NULL && node->indexParams->length > 0)
    _fingerprintChildList(ctx, node->indexParams, node, "indexParams", depth);

  if (node->initdeferred) {
    _fingerprintString(ctx, "initdeferred");
    _fingerprintString(ctx, "true");
  }

  if (node->isconstraint) {
    _fingerprintString(ctx, "isconstraint");
    _fingerprintString(ctx, "true");
  }

  if (node->iswithoutoverlaps) {
    _fingerprintString(ctx, "iswithoutoverlaps");
    _fingerprintString(ctx, "true");
  }

  if (node->nulls_not_distinct) {
    _fingerprintString(ctx, "nulls_not_distinct");
    _fingerprintString(ctx, "true");
  }

  if (node->oldCreateSubid != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->oldCreateSubid);
    _fingerprintString(ctx, "oldCreateSubid");
    _fingerprintString(ctx, buffer);
  }

  if (node->oldFirstRelfilelocatorSubid != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->oldFirstRelfilelocatorSubid);
    _fingerprintString(ctx, "oldFirstRelfilelocatorSubid");
    _fingerprintString(ctx, buffer);
  }

  if (node->oldNumber != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->oldNumber);
    _fingerprintString(ctx, "oldNumber");
    _fingerprintString(ctx, buffer);
  }

  if (node->options != NULL && node->options->length > 0)
    _fingerprintChildList(ctx, node->options, node, "options", depth);

  if (node->primary) {
    _fingerprintString(ctx, "primary");
    _fingerprintString(ctx, "true");
  }

  if (node->relation != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "relation");
    _fingerprintRangeVar(ctx, node->relation, node, "relation", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  if (node->reset_default_tblspc) {
    _fingerprintString(ctx, "reset_default_tblspc");
    _fingerprintString(ctx, "true");
  }

  if (node->tableSpace != NULL) {
    _fingerprintString(ctx, "tableSpace");
    _fingerprintString(ctx, node->tableSpace);
  }

  if (node->transformed) {
    _fingerprintString(ctx, "transformed");
    _fingerprintString(ctx, "true");
  }

  if (node->unique) {
    _fingerprintString(ctx, "unique");
    _fingerprintString(ctx, "true");
  }

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

  if (node->if_not_exists) {
    _fingerprintString(ctx, "if_not_exists");
    _fingerprintString(ctx, "true");
  }

  if (node->relations != NULL && node->relations->length > 0)
    _fingerprintChildList(ctx, node->relations, node, "relations", depth);

  if (node->stat_types != NULL && node->stat_types->length > 0)
    _fingerprintChildList(ctx, node->stat_types, node, "stat_types", depth);

  if (node->stxcomment != NULL) {
    _fingerprintString(ctx, "stxcomment");
    _fingerprintString(ctx, node->stxcomment);
  }

  if (node->transformed) {
    _fingerprintString(ctx, "transformed");
    _fingerprintString(ctx, "true");
  }

}

static void
_fingerprintStatsElem(FingerprintContext *ctx, const StatsElem *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->expr != NULL)
    _fingerprintChildNode(ctx, node->expr, node, "expr", depth);

  if (node->name != NULL) {
    _fingerprintString(ctx, "name");
    _fingerprintString(ctx, node->name);
  }

}

static void
_fingerprintAlterStatsStmt(FingerprintContext *ctx, const AlterStatsStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->defnames != NULL && node->defnames->length > 0)
    _fingerprintChildList(ctx, node->defnames, node, "defnames", depth);

  if (node->missing_ok) {
    _fingerprintString(ctx, "missing_ok");
    _fingerprintString(ctx, "true");
  }

  if (node->stxstattarget != NULL)
    _fingerprintChildNode(ctx, node->stxstattarget, node, "stxstattarget", depth);

}

static void
_fingerprintCreateFunctionStmt(FingerprintContext *ctx, const CreateFunctionStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->funcname != NULL && node->funcname->length > 0)
    _fingerprintChildList(ctx, node->funcname, node, "funcname", depth);

  if (node->is_procedure) {
    _fingerprintString(ctx, "is_procedure");
    _fingerprintString(ctx, "true");
  }

  // Intentionally ignoring node->options for fingerprinting

  if (node->parameters != NULL && node->parameters->length > 0)
    _fingerprintChildList(ctx, node->parameters, node, "parameters", depth);

  if (node->replace) {
    _fingerprintString(ctx, "replace");
    _fingerprintString(ctx, "true");
  }

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

  _fingerprintString(ctx, "mode");
  _fingerprintString(ctx, _enumToStringFunctionParameterMode(node->mode));

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

  _fingerprintString(ctx, "objtype");
  _fingerprintString(ctx, _enumToStringObjectType(node->objtype));

}

static void
_fingerprintDoStmt(FingerprintContext *ctx, const DoStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  // Intentionally ignoring node->args for fingerprinting

}

static void
_fingerprintInlineCodeBlock(FingerprintContext *ctx, const InlineCodeBlock *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->atomic) {
    _fingerprintString(ctx, "atomic");
    _fingerprintString(ctx, "true");
  }

  if (node->langIsTrusted) {
    _fingerprintString(ctx, "langIsTrusted");
    _fingerprintString(ctx, "true");
  }

  if (node->langOid != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->langOid);
    _fingerprintString(ctx, "langOid");
    _fingerprintString(ctx, buffer);
  }

  if (node->source_text != NULL) {
    _fingerprintString(ctx, "source_text");
    _fingerprintString(ctx, node->source_text);
  }

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
  if (node->atomic) {
    _fingerprintString(ctx, "atomic");
    _fingerprintString(ctx, "true");
  }

}

static void
_fingerprintRenameStmt(FingerprintContext *ctx, const RenameStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintString(ctx, "behavior");
  _fingerprintString(ctx, _enumToStringDropBehavior(node->behavior));

  if (node->missing_ok) {
    _fingerprintString(ctx, "missing_ok");
    _fingerprintString(ctx, "true");
  }

  if (node->newname != NULL) {
    _fingerprintString(ctx, "newname");
    _fingerprintString(ctx, node->newname);
  }

  if (node->object != NULL)
    _fingerprintChildNode(ctx, node->object, node, "object", depth);

  if (node->relation != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "relation");
    _fingerprintRangeVar(ctx, node->relation, node, "relation", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  _fingerprintString(ctx, "relationType");
  _fingerprintString(ctx, _enumToStringObjectType(node->relationType));

  _fingerprintString(ctx, "renameType");
  _fingerprintString(ctx, _enumToStringObjectType(node->renameType));

  if (node->subname != NULL) {
    _fingerprintString(ctx, "subname");
    _fingerprintString(ctx, node->subname);
  }

}

static void
_fingerprintAlterObjectDependsStmt(FingerprintContext *ctx, const AlterObjectDependsStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (strlen(node->extname->sval) > 0) {
    _fingerprintString(ctx, "extname");
    _fingerprintString(ctx, node->extname->sval);
  }

  if (node->object != NULL)
    _fingerprintChildNode(ctx, node->object, node, "object", depth);

  _fingerprintString(ctx, "objectType");
  _fingerprintString(ctx, _enumToStringObjectType(node->objectType));

  if (node->relation != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "relation");
    _fingerprintRangeVar(ctx, node->relation, node, "relation", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  if (node->remove) {
    _fingerprintString(ctx, "remove");
    _fingerprintString(ctx, "true");
  }

}

static void
_fingerprintAlterObjectSchemaStmt(FingerprintContext *ctx, const AlterObjectSchemaStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->missing_ok) {
    _fingerprintString(ctx, "missing_ok");
    _fingerprintString(ctx, "true");
  }

  if (node->newschema != NULL) {
    _fingerprintString(ctx, "newschema");
    _fingerprintString(ctx, node->newschema);
  }

  if (node->object != NULL)
    _fingerprintChildNode(ctx, node->object, node, "object", depth);

  _fingerprintString(ctx, "objectType");
  _fingerprintString(ctx, _enumToStringObjectType(node->objectType));

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

  _fingerprintString(ctx, "objectType");
  _fingerprintString(ctx, _enumToStringObjectType(node->objectType));

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

  _fingerprintString(ctx, "event");
  _fingerprintString(ctx, _enumToStringCmdType(node->event));

  if (node->instead) {
    _fingerprintString(ctx, "instead");
    _fingerprintString(ctx, "true");
  }

  if (node->relation != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "relation");
    _fingerprintRangeVar(ctx, node->relation, node, "relation", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  if (node->replace) {
    _fingerprintString(ctx, "replace");
    _fingerprintString(ctx, "true");
  }

  if (node->rulename != NULL) {
    _fingerprintString(ctx, "rulename");
    _fingerprintString(ctx, node->rulename);
  }

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
  if (node->chain) {
    _fingerprintString(ctx, "chain");
    _fingerprintString(ctx, "true");
  }

  // Intentionally ignoring node->gid for fingerprinting

  _fingerprintString(ctx, "kind");
  _fingerprintString(ctx, _enumToStringTransactionStmtKind(node->kind));

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
  if (node->newVal != NULL) {
    _fingerprintString(ctx, "newVal");
    _fingerprintString(ctx, node->newVal);
  }

  if (node->newValIsAfter) {
    _fingerprintString(ctx, "newValIsAfter");
    _fingerprintString(ctx, "true");
  }

  if (node->newValNeighbor != NULL) {
    _fingerprintString(ctx, "newValNeighbor");
    _fingerprintString(ctx, node->newValNeighbor);
  }

  if (node->oldVal != NULL) {
    _fingerprintString(ctx, "oldVal");
    _fingerprintString(ctx, node->oldVal);
  }

  if (node->skipIfNewValExists) {
    _fingerprintString(ctx, "skipIfNewValExists");
    _fingerprintString(ctx, "true");
  }

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

  if (node->replace) {
    _fingerprintString(ctx, "replace");
    _fingerprintString(ctx, "true");
  }

  if (node->view != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "view");
    _fingerprintRangeVar(ctx, node->view, node, "view", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  _fingerprintString(ctx, "withCheckOption");
  _fingerprintString(ctx, _enumToStringViewCheckOption(node->withCheckOption));

}

static void
_fingerprintLoadStmt(FingerprintContext *ctx, const LoadStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->filename != NULL) {
    _fingerprintString(ctx, "filename");
    _fingerprintString(ctx, node->filename);
  }

}

static void
_fingerprintCreatedbStmt(FingerprintContext *ctx, const CreatedbStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->dbname != NULL) {
    _fingerprintString(ctx, "dbname");
    _fingerprintString(ctx, node->dbname);
  }

  if (node->options != NULL && node->options->length > 0)
    _fingerprintChildList(ctx, node->options, node, "options", depth);

}

static void
_fingerprintAlterDatabaseStmt(FingerprintContext *ctx, const AlterDatabaseStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->dbname != NULL) {
    _fingerprintString(ctx, "dbname");
    _fingerprintString(ctx, node->dbname);
  }

  if (node->options != NULL && node->options->length > 0)
    _fingerprintChildList(ctx, node->options, node, "options", depth);

}

static void
_fingerprintAlterDatabaseRefreshCollStmt(FingerprintContext *ctx, const AlterDatabaseRefreshCollStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->dbname != NULL) {
    _fingerprintString(ctx, "dbname");
    _fingerprintString(ctx, node->dbname);
  }

}

static void
_fingerprintAlterDatabaseSetStmt(FingerprintContext *ctx, const AlterDatabaseSetStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->dbname != NULL) {
    _fingerprintString(ctx, "dbname");
    _fingerprintString(ctx, node->dbname);
  }

  if (node->setstmt != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "setstmt");
    _fingerprintVariableSetStmt(ctx, node->setstmt, node, "setstmt", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

}

static void
_fingerprintDropdbStmt(FingerprintContext *ctx, const DropdbStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->dbname != NULL) {
    _fingerprintString(ctx, "dbname");
    _fingerprintString(ctx, node->dbname);
  }

  if (node->missing_ok) {
    _fingerprintString(ctx, "missing_ok");
    _fingerprintString(ctx, "true");
  }

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
  if (node->indexname != NULL) {
    _fingerprintString(ctx, "indexname");
    _fingerprintString(ctx, node->indexname);
  }

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
  if (node->is_vacuumcmd) {
    _fingerprintString(ctx, "is_vacuumcmd");
    _fingerprintString(ctx, "true");
  }

  if (node->options != NULL && node->options->length > 0)
    _fingerprintChildList(ctx, node->options, node, "options", depth);

  if (node->rels != NULL && node->rels->length > 0)
    _fingerprintChildList(ctx, node->rels, node, "rels", depth);

}

static void
_fingerprintVacuumRelation(FingerprintContext *ctx, const VacuumRelation *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->oid != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->oid);
    _fingerprintString(ctx, "oid");
    _fingerprintString(ctx, buffer);
  }

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
  if (node->if_not_exists) {
    _fingerprintString(ctx, "if_not_exists");
    _fingerprintString(ctx, "true");
  }

  if (node->into != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "into");
    _fingerprintIntoClause(ctx, node->into, node, "into", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  if (node->is_select_into) {
    _fingerprintString(ctx, "is_select_into");
    _fingerprintString(ctx, "true");
  }

  _fingerprintString(ctx, "objtype");
  _fingerprintString(ctx, _enumToStringObjectType(node->objtype));

  if (node->query != NULL)
    _fingerprintChildNode(ctx, node->query, node, "query", depth);

}

static void
_fingerprintRefreshMatViewStmt(FingerprintContext *ctx, const RefreshMatViewStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->concurrent) {
    _fingerprintString(ctx, "concurrent");
    _fingerprintString(ctx, "true");
  }

  if (node->relation != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "relation");
    _fingerprintRangeVar(ctx, node->relation, node, "relation", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  if (node->skipData) {
    _fingerprintString(ctx, "skipData");
    _fingerprintString(ctx, "true");
  }

}

static void
_fingerprintCheckPointStmt(FingerprintContext *ctx, const CheckPointStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
}

static void
_fingerprintDiscardStmt(FingerprintContext *ctx, const DiscardStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintString(ctx, "target");
  _fingerprintString(ctx, _enumToStringDiscardMode(node->target));

}

static void
_fingerprintLockStmt(FingerprintContext *ctx, const LockStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->mode != 0) {
    char buffer[50];
    sprintf(buffer, "%d", node->mode);
    _fingerprintString(ctx, "mode");
    _fingerprintString(ctx, buffer);
  }

  if (node->nowait) {
    _fingerprintString(ctx, "nowait");
    _fingerprintString(ctx, "true");
  }

  if (node->relations != NULL && node->relations->length > 0)
    _fingerprintChildList(ctx, node->relations, node, "relations", depth);

}

static void
_fingerprintConstraintsSetStmt(FingerprintContext *ctx, const ConstraintsSetStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->constraints != NULL && node->constraints->length > 0)
    _fingerprintChildList(ctx, node->constraints, node, "constraints", depth);

  if (node->deferred) {
    _fingerprintString(ctx, "deferred");
    _fingerprintString(ctx, "true");
  }

}

static void
_fingerprintReindexStmt(FingerprintContext *ctx, const ReindexStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintString(ctx, "kind");
  _fingerprintString(ctx, _enumToStringReindexObjectType(node->kind));

  if (node->name != NULL) {
    _fingerprintString(ctx, "name");
    _fingerprintString(ctx, node->name);
  }

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

  if (node->def) {
    _fingerprintString(ctx, "def");
    _fingerprintString(ctx, "true");
  }

  if (node->for_encoding_name != NULL) {
    _fingerprintString(ctx, "for_encoding_name");
    _fingerprintString(ctx, node->for_encoding_name);
  }

  if (node->func_name != NULL && node->func_name->length > 0)
    _fingerprintChildList(ctx, node->func_name, node, "func_name", depth);

  if (node->to_encoding_name != NULL) {
    _fingerprintString(ctx, "to_encoding_name");
    _fingerprintString(ctx, node->to_encoding_name);
  }

}

static void
_fingerprintCreateCastStmt(FingerprintContext *ctx, const CreateCastStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintString(ctx, "context");
  _fingerprintString(ctx, _enumToStringCoercionContext(node->context));

  if (node->func != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "func");
    _fingerprintObjectWithArgs(ctx, node->func, node, "func", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

  if (node->inout) {
    _fingerprintString(ctx, "inout");
    _fingerprintString(ctx, "true");
  }

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

  if (node->lang != NULL) {
    _fingerprintString(ctx, "lang");
    _fingerprintString(ctx, node->lang);
  }

  if (node->replace) {
    _fingerprintString(ctx, "replace");
    _fingerprintString(ctx, "true");
  }

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
  if (node->isall) {
    _fingerprintString(ctx, "isall");
    _fingerprintString(ctx, "true");
  }

  // Intentionally ignoring node->location for fingerprinting

  // Intentionally ignoring node->name for fingerprinting

}

static void
_fingerprintDropOwnedStmt(FingerprintContext *ctx, const DropOwnedStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintString(ctx, "behavior");
  _fingerprintString(ctx, _enumToStringDropBehavior(node->behavior));

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

  _fingerprintString(ctx, "kind");
  _fingerprintString(ctx, _enumToStringAlterTSConfigType(node->kind));

  if (node->missing_ok) {
    _fingerprintString(ctx, "missing_ok");
    _fingerprintString(ctx, "true");
  }

  if (node->override) {
    _fingerprintString(ctx, "override");
    _fingerprintString(ctx, "true");
  }

  if (node->replace) {
    _fingerprintString(ctx, "replace");
    _fingerprintString(ctx, "true");
  }

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

  if (node->name != NULL) {
    _fingerprintString(ctx, "name");
    _fingerprintString(ctx, node->name);
  }

  _fingerprintString(ctx, "pubobjtype");
  _fingerprintString(ctx, _enumToStringPublicationObjSpecType(node->pubobjtype));

  if (node->pubtable != NULL) {
    FingerprintChildState cs = _fingerprintChildBegin(ctx, "pubtable");
    _fingerprintPublicationTable(ctx, node->pubtable, node, "pubtable", depth + 1);
    _fingerprintChildEnd(ctx, &cs, false);
  }

}

static void
_fingerprintCreatePublicationStmt(FingerprintContext *ctx, const CreatePublicationStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->for_all_tables) {
    _fingerprintString(ctx, "for_all_tables");
    _fingerprintString(ctx, "true");
  }

  if (node->options != NULL && node->options->length > 0)
    _fingerprintChildList(ctx, node->options, node, "options", depth);

  if (node->pubname != NULL) {
    _fingerprintString(ctx, "pubname");
    _fingerprintString(ctx, node->pubname);
  }

  if (node->pubobjects != NULL && node->pubobjects->length > 0)
    _fingerprintChildList(ctx, node->pubobjects, node, "pubobjects", depth);

}

static void
_fingerprintAlterPublicationStmt(FingerprintContext *ctx, const AlterPublicationStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintString(ctx, "action");
  _fingerprintString(ctx, _enumToStringAlterPublicationAction(node->action));

  if (node->for_all_tables) {
    _fingerprintString(ctx, "for_all_tables");
    _fingerprintString(ctx, "true");
  }

  if (node->options != NULL && node->options->length > 0)
    _fingerprintChildList(ctx, node->options, node, "options", depth);

  if (node->pubname != NULL) {
    _fingerprintString(ctx, "pubname");
    _fingerprintString(ctx, node->pubname);
  }

  if (node->pubobjects != NULL && node->pubobjects->length > 0)
    _fingerprintChildList(ctx, node->pubobjects, node, "pubobjects", depth);

}

static void
_fingerprintCreateSubscriptionStmt(FingerprintContext *ctx, const CreateSubscriptionStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->conninfo != NULL) {
    _fingerprintString(ctx, "conninfo");
    _fingerprintString(ctx, node->conninfo);
  }

  if (node->options != NULL && node->options->length > 0)
    _fingerprintChildList(ctx, node->options, node, "options", depth);

  if (node->publication != NULL && node->publication->length > 0)
    _fingerprintChildList(ctx, node->publication, node, "publication", depth);

  if (node->subname != NULL) {
    _fingerprintString(ctx, "subname");
    _fingerprintString(ctx, node->subname);
  }

}

static void
_fingerprintAlterSubscriptionStmt(FingerprintContext *ctx, const AlterSubscriptionStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  if (node->conninfo != NULL) {
    _fingerprintString(ctx, "conninfo");
    _fingerprintString(ctx, node->conninfo);
  }

  _fingerprintString(ctx, "kind");
  _fingerprintString(ctx, _enumToStringAlterSubscriptionType(node->kind));

  if (node->options != NULL && node->options->length > 0)
    _fingerprintChildList(ctx, node->options, node, "options", depth);

  if (node->publication != NULL && node->publication->length > 0)
    _fingerprintChildList(ctx, node->publication, node, "publication", depth);

  if (node->subname != NULL) {
    _fingerprintString(ctx, "subname");
    _fingerprintString(ctx, node->subname);
  }

}

static void
_fingerprintDropSubscriptionStmt(FingerprintContext *ctx, const DropSubscriptionStmt *node, const void *parent, const char *field_name, unsigned int depth)
{
  _fingerprintString(ctx, "behavior");
  _fingerprintString(ctx, _enumToStringDropBehavior(node->behavior));

  if (node->missing_ok) {
    _fingerprintString(ctx, "missing_ok");
    _fingerprintString(ctx, "true");
  }

  if (node->subname != NULL) {
    _fingerprintString(ctx, "subname");
    _fingerprintString(ctx, node->subname);
  }

}

