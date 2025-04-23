#include "parser/parsed_expression/star_expression.h"

#include "parser/query_node.h"
namespace lingodb::ast {
StarExpression::StarExpression(std::string relationName)
    : ParsedExpression(ExpressionType::STAR, ExpressionClass::STAR), relationName(std::move(relationName)) {
}

std::string StarExpression::toAsciiAST(uint32_t depth ) {
   toAsciiASTPrefix
   return "";
}
} // namespace lingodb::ast