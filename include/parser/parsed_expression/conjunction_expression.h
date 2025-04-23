#pragma once
#include "parser/parsed_expression.h"

#include <memory>
#include <vector>

namespace lingodb::ast {
class ConjunctionExpression : public  ParsedExpression {
   public:
   static constexpr const ExpressionClass TYPE = ExpressionClass::CONJUNCTION;
   explicit ConjunctionExpression(ExpressionType type);
   ConjunctionExpression(ExpressionType type, std::shared_ptr<lingodb::ast::ParsedExpression> left, std::shared_ptr<lingodb::ast::ParsedExpression> right);
   ConjunctionExpression(ExpressionType type, std::vector<std::shared_ptr<ParsedExpression>> children);

   std::vector<std::shared_ptr<ParsedExpression>> children;


   std::string toAsciiAST(uint32_t depth ) override;

   private:
   std::string typeToAscii(ExpressionType type) const;


};
}