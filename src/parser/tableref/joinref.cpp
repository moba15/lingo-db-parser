#include "parser/tableref/joinref.h"

#include "parser/query_node.h"
namespace lingodb::ast {
 JoinRef::JoinRef(JoinType type, JoinCondType refType): TableRef(TYPE), type(type), refType(refType) {
}
std::string JoinRef::toAsciiAST(uint32_t depth){
    toAsciiASTPrefix
    ast.append("JoinRef $1 on $2 \n");
    if (left) {
       ast.append(left->toAsciiAST(depth + 1));
    }
    if (right) {
       ast.append(right->toAsciiAST(depth + 1));
    }

    return ast;
}
} // namespace lingodb::ast