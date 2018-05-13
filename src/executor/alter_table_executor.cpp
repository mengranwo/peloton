//===----------------------------------------------------------------------===//
//
//                         Peloton
//
// alter_table_executor.cpp
//
// Identification: src/executor/alter_table_executor.cpp
//
// Copyright (c) 2015-2018, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#include "executor/alter_table_executor.h"

#include "catalog/catalog.h"
#include "common/logger.h"
#include "executor/executor_context.h"

namespace peloton {
namespace executor {

// Constructor for alter table executor
AlterTableExecutor::AlterTableExecutor(const planner::AbstractPlan *node,
                                       ExecutorContext *executor_context)
    : AbstractExecutor(node, executor_context) {
  context_ = executor_context;
}

// Initialize executor
// Nothing to initialize for now
bool AlterTableExecutor::DInit() {
  LOG_TRACE("Initializing Alter Executer...");
  LOG_TRACE("Alter Executor initialized!");
  return true;
}

bool AlterTableExecutor::DExecute() {
  LOG_TRACE("Executing Alter Table ...");
  bool result = false;
  const planner::AlterTablePlan &node = GetPlanNode<planner::AlterTablePlan>();

  AlterType type = node.GetAlterTableType();
  switch (type) {
    case AlterType::RENAME_COLUMN:
      result = RenameColumn(node);
      break;
    case AlterType::DROP_COLUMN:
      result = DropColumns(node);
      break;
    default:
      throw NotImplementedException(
          StringUtil::Format("Alter Type not supported in executor, %s",
                             AlterTypeToString(type).c_str()));
  }
  return result;
}

bool AlterTableExecutor::RenameColumn(
    const peloton::planner::AlterTablePlan &node) {
  auto txn = context_->GetTransaction();
  auto database_name = node.GetDatabaseName();
  auto schema_name = node.GetSchemaName();
  auto table_name = node.GetTableName();
  auto new_column_name = node.GetNewName();
  auto old_column_name = node.GetOldName();

  ResultType result = catalog::Catalog::GetInstance()->RenameColumn(
      database_name, schema_name, table_name, old_column_name, new_column_name,
      txn);
  txn->SetResult(result);

  LOG_TRACE("Alter table(rename column) result is: %s",
            ResultTypeToString(txn->GetResult()).c_str());
  return false;
}

bool AlterTableExecutor::DropColumns(
    const peloton::planner::AlterTablePlan &node) {
  auto txn = context_->GetTransaction();
  auto database_name = node.GetDatabaseName();
  auto schema_name = node.GetSchemaName();
  auto table_name = node.GetTableName();
  auto dropped_columns = node.GetDroppedColumns();

  ResultType result = catalog::Catalog::GetInstance()->DropColumns(
      database_name, schema_name, table_name, dropped_columns, txn);
  txn->SetResult(result);

  LOG_TRACE("Alter table(drop columns) result is: %s",
            ResultTypeToString(txn->GetResult()).c_str());
  return false;
}

}  // namespace executor
}  // namespace peloton
