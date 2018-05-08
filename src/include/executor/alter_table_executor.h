//===----------------------------------------------------------------------===//
//
//                         Peloton
//
// alter_table_executor.h
//
// Identification: src/include/executor/alter_table_executor.h
//
// Copyright (c) 2015-2018, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#pragma once

#include "concurrency/transaction_context.h"
#include "executor/abstract_executor.h"
#include "planner/alter_table_plan.h"

namespace peloton {

namespace planner {
class AbstractPlan;
}

namespace executor {

class AlterTableExecutor : public AbstractExecutor {
 public:
  AlterTableExecutor(const AlterTableExecutor &) = delete;
  AlterTableExecutor &operator=(const AlterTableExecutor &) = delete;
  AlterTableExecutor(AlterTableExecutor &&) = delete;
  AlterTableExecutor &operator=(AlterTableExecutor &&) = delete;

  AlterTableExecutor(const planner::AbstractPlan *node,
                     ExecutorContext *executor_context);

  ~AlterTableExecutor() {}

 protected:
  bool DInit();

  bool DExecute();

  bool RenameColumn(const planner::AlterTablePlan &node,
                    concurrency::TransactionContext *txn);

 private:
  ExecutorContext *context_;
};

}  // namespace executor
}  // namespace peloton
