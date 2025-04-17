#include "parser/ast/nodes/expr.h"
std::string nodes::relExpressionToString(RelExpression relExpression,size_t depth) {
  std::string str = "";
  if (std::holds_alternative<std::shared_ptr<TableName>> (relExpression)) {
    auto tmp = std::get<std::shared_ptr<TableName>> (relExpression);
    str.append(tmp->toString(depth));
  } else if (std::holds_alternative<std::shared_ptr<SelectExpr>> (relExpression)) {
    auto tmp = std::get<std::shared_ptr<SelectExpr>> (relExpression);
    str.append(tmp->toString(depth));
  } else if (std::holds_alternative<std::shared_ptr<Query>> (relExpression)) {
    auto tmp = std::get<std::shared_ptr<Query>> (relExpression);
    str.append(tmp->toString(depth));
  }
  return str;
}