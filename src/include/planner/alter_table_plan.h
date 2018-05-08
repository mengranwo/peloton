//===----------------------------------------------------------------------===//
//
//                         Peloton
//
// alter_table_plan.h
//
// Identification: src/include/planner/alter_table_plan.h
//
// Copyright (c) 2015-18, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#pragma once
#include "parser/alter_table_statement.h"
#include "planner/abstract_plan.h"

namespace peloton {

namespace parser {
class AlterTableStatement;
}  // namespace parser
namespace catalog {
class Schema;
}
namespace storage {
class DataTable;
}

namespace planner {
/** @brief The plan used for altering
 */
class AlterTablePlan : public AbstractPlan {
 public:
  AlterTablePlan() = delete;

  explicit AlterTablePlan(AlterType type, const std::string &table_name,
                          const std::string &schema_name,
                          const std::string &database_name,
                          const std::string &old_name,
                          const std::string &new_name);

  explicit AlterTablePlan(parser::AlterTableStatement *parse_tree);

  virtual ~AlterTablePlan() {}

  std::unique_ptr<AbstractPlan> Copy() const {
    // TODO: Implement copy() function
    return nullptr;
  }

  virtual PlanNodeType GetPlanNodeType() const { return PlanNodeType::ALTER; }

  const std::string GetInfo() const;

  std::string GetTableName() const { return table_name_; }

  std::string GetSchemaName() const { return schema_name_; }

  std::string GetDatabaseName() const { return database_name_; }

  AlterType GetAlterTableType() const { return type_; }

  // function used for rename statement
  std::string GetOldName() const { return old_name_; }

  // function used for rename statement
  std::string GetNewName() const { return new_name_; }

 private:
  AlterType type_;
  // Table Name
  std::string table_name_;

  // Schema Name
  std::string schema_name_;

  // Database Name
  std::string database_name_;

  // used for store rename function data
  // NOTE: postreSQL only supports change one column name at time
  std::string old_name_ = "";
  std::string new_name_ = "";
};

}  // namespace planner
}  // namespace peloton
