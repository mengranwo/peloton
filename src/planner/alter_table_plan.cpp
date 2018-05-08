//===----------------------------------------------------------------------===//
//
//                         Peloton
//
// alter_table_plan.cpp
//
// Identification: src/planner/alter_table_plan.cpp
//
// Copyright (c) 2015-16, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#include <iostream>
#include <sstream>

#include "planner/alter_table_plan.h"

namespace peloton {
namespace planner {

AlterTablePlan::AlterTablePlan(AlterType type, const std::string &table_name,
                               const std::string &schema_name,
                               const std::string &database_name,
                               const std::string &old_name,
                               const std::string &new_name)
    : type_(type),
      table_name_(table_name),
      schema_name_(schema_name),
      database_name_(database_name),
      old_name_(old_name),
      new_name_(new_name) {}

AlterTablePlan::AlterTablePlan(parser::AlterTableStatement *parse_tree) {
  table_name_ = parse_tree->GetTableName();
  schema_name_ = parse_tree->GetSchemaName();
  database_name_ = parse_tree->GetDatabaseName();

  switch (parse_tree->type_) {
    case parser::AlterTableStatement::AlterType::RENAME_COLUMN: {
      old_name_ = parse_tree->oldName;
      new_name_ = parse_tree->newName;
      type_ = AlterType::RENAME_COLUMN;
      break;
    }

    default:
      LOG_ERROR("Not Implemented the plan type %d in alter table!", (int)type_);
      type_ = AlterType::INVALID;
  }
}

const std::string AlterTablePlan::GetInfo() const {
  std::ostringstream os;

  os << "Alter table plan["
     << "type:" << type_ << ", "
     << "table::" << table_name_ << ", "
     << "schema:" << schema_name_ << ", "
     << "database:" << database_name_ << "]";

  return os.str();
}

}  // namespace planner
}  // namespace peloton
