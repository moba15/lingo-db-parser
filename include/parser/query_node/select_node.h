#pragma once
#include "parser/parsed_expression.h"
#include "parser/query_node.h"
#include "parser/tableref.h"

#include <memory>
#include <vector>
namespace lingodb::ast {
class SelectNode : public QueryNode {
public:
  SelectNode();
   ~SelectNode() override;
  static constexpr QueryNodeType TYPE = QueryNodeType::SELECT_NODE;
  //! The projection list
  std::vector<std::shared_ptr<ParsedExpression>> select_list;
  //! The FROM clause
  std::shared_ptr<TableRef> from_clause;
  //! The WHERE clause
  std::shared_ptr<ParsedExpression> where_clause;
  //TODO add missing parameters
   std::string toString(uint32_t depth) override;

   std::string toAsciiAST(uint32_t depth) override;
};
} // namespace lingodb::ast
