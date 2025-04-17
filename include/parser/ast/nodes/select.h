#pragma once
#include "parser/ast/nodes/expr.h"
namespace nodes {
class SelectStatement : Node {
public:
  explicit  SelectStatement(std::shared_ptr<Query> query) : query(std::move(query)) {};
  std::shared_ptr<Query> query;
  std::string toString() {
    std::string string = "SelectStatement\n";
    string.append(std::string(0, ' '));
    string.append(query->toString(1));
    string.append("\n");
    return string;
  }
};
}