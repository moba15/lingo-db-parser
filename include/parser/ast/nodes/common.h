#pragma once
#include "parser/ast/ast.h"

#include <memory>
#include <utility>
#include <vector>

namespace nodes {
class QualifiedName : Node {
public:
    explicit QualifiedName(std::string name) : name(std::move(name)) {};
    std::string name;
    std::vector<std::string> qualifier;
     std::string toString(size_t depth)  {
       std::string str = "QualifiedName: ";
       str += this->name;
       str += " (";
       for (auto qualifier : this->qualifier) {
         str += qualifier + ",";
       }
       str += ")";
       return str;
    }
};
}