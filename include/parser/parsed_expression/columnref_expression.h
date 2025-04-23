#pragma once
#include "parser/parsed_expression.h"
#include <vector>
#include <string>
namespace lingodb::ast {
class ColumnRefExpression : public ParsedExpression {
  public:
  static constexpr ExpressionClass TYPE = ExpressionClass::COLUMN_REF;

  //! Specify both the column and table name
  ColumnRefExpression(std::string column_name, std::string table_name);
  //! Specify both the column and table alias
  //TODO ColumnRefExpression(std::string column_name, const BindingAlias &alias);
  //! Only specify the column name, the table name will be derived later
  explicit ColumnRefExpression(std::string column_name);
  //! Specify a set of names
  explicit ColumnRefExpression(std::vector<std::string> column_names);


  //! The stack of names in order of which they appear (column_names[0].column_names[1].column_names[2]....)
  std::vector<std::string> column_names;


   std::string toAsciiAST(uint32_t depth ) override;

};
}
