//===----------------------------------------------------------------------===//
//
//                         Peloton
//
// alter_table_statement.h
//
// Identification: src/include/parser/alter_table_statement.h
//
// Copyright (c) 2015-18, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#pragma once

#include "parser/create_statement.h"

namespace peloton {
namespace parser {
/**
 * @class AlterTableStatement
 * @brief Represents "ALTER TABLE add column COLUMN_NAME COLUMN_TYPE"
 * @ and "ALTER TABLE xx RENAME COLUMN old TO new"
 */
class AlterTableStatement : public TableRefStatement {
 public:
  enum class AlterType {
    INVALID = 0,
    ADD_COLUMN = 1,
    DROP_COLUMN = 2,
    RENAME_COLUMN = 3
  };
  // Defualt constructor
  AlterTableStatement()
      : TableRefStatement(StatementType::ALTER), type_(AlterType::INVALID) {}

  AlterTableStatement(AlterType type)
      : TableRefStatement(StatementType::ALTER), type_(type) {}

  virtual ~AlterTableStatement() {}

  virtual void Accept(SqlNodeVisitor *v) override { v->Visit(this); }

  AlterType type_;
  // Dropped columns
  std::vector<std::string> dropped_names_;
  // Added columns
  std::vector<std::unique_ptr<ColumnDefinition>> added_columns_;
  // changed columns(change type)
  std::vector<std::unique_ptr<ColumnDefinition>> changed_type_columns_;
  // the name that needs to be changed
  std::string oldName = "";
  std::string newName = "";
};

}  // namespace parser
}  // namespace peloton
