#pragma once
#include "parser/parsed_expression.h"

#include <memory>
namespace lingodb::ast {
//! ComparisonExpression represents a boolean comparison (e.g. =, >=, <>). Always returns a boolean
//! and has two children.
class ComparisonExpression : public ParsedExpression {

  public:
  static constexpr const ExpressionClass TYPE = ExpressionClass::COMPARISON;

  explicit ComparisonExpression(ExpressionType type);
  ComparisonExpression(ExpressionType type, std::shared_ptr<ParsedExpression> left, std::shared_ptr<ParsedExpression> right);

  std::shared_ptr<ParsedExpression> left;
  std::shared_ptr<ParsedExpression> right;


   std::string toAsciiAST(uint32_t depth ) override;

   private:
   std::string typeToAscii(ExpressionType type) const;
};
}
