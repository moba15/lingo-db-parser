#pragma once
#include "parser/ast/ast.h"

#include <memory>
#include <utility>
#include "parser/ast/nodes/common.h"
namespace nodes {
class  SelectExpr;
class Query;
class TableName;
class RowExpr;
using RelExpression = std::variant<
    //box<JoinExpr>,
    std::shared_ptr<TableName>,
          //box<TableAlias>,
    std::shared_ptr<SelectExpr>,
    //box<ValuesExpr>,
    //box<SetOp>,
    std::shared_ptr<Query>>;

std::string relExpressionToString(RelExpression relExpression,  size_t depth);
class RowExpr : Node {
public:
  std::shared_ptr<QualifiedName> name;
  RowExpr(std::shared_ptr<QualifiedName> name) : name(name) {};
  std::string toString(size_t depth) {
    std::string str = "RowExpr\n";
    str.append(std::string(depth, ' '));
    str.append(name->toString(depth+1));
    str.append("\n");
    return str;

  }
};

class SelectExpr : Node  {
public:

  SelectExpr() = default;
  std::string toString(size_t depth)  {
    std::string str = "SelectExpr\n";
    str.append(std::string(depth, ' '));
    str.append(target_list->toString(depth+1));
    for (auto& from : from_clause) {


      str.append(std::string(depth, ' '));
      str.append(relExpressionToString(from, depth+1));

    }

    return str;
  }
  std::vector<RelExpression> from_clause;
  std::shared_ptr<RowExpr> target_list;

};

class Query : Node {
public:
  explicit  Query(RelExpression relExpr) : relExpr(std::move(relExpr)) {};
  RelExpression relExpr;
  std::string toString(size_t depth)  {
    std::string str = "Query\n";
    str.append(std::string(depth, ' '));
    str.append(relExpressionToString(relExpr,  depth+1));

    return str;
  }
};

class TableName : Node {
public:
  explicit TableName(std::shared_ptr<QualifiedName> name) : name(std::move(name)) {};

  std::shared_ptr<QualifiedName> name;
  std::string toString(size_t depth)  {
    std::string str = "TableName\n";
    str.append(std::string(depth, ' '));
    str.append(name->toString(depth+1));
    str.append("\n");
    return str;
  }

};

}

