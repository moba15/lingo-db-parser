#pragma once
#include "parser/tableref.h"

#include <memory>
namespace lingodb::ast {
enum class JoinCondType : uint8_t;
enum class JoinType : uint8_t ;

class JoinRef : public TableRef {
   static constexpr TableReferenceType TYPE = TableReferenceType::JOIN;
   public:
   JoinRef(JoinType type, JoinCondType refType);


   //! The left hand side of the join
   std::shared_ptr<TableRef> left;
   //! The right hand side of the join
   std::shared_ptr<TableRef> right;
   //! The join type
   JoinType type;
   //! Join condition type
   JoinCondType refType;

   //TODO Add missing vriable
   /*vector<string> using_columns;
   //! Duplicate eliminated columns (if any)
   vector<unique_ptr<ParsedExpression>> duplicate_eliminated_columns;*/


   std::string toAsciiAST(uint32_t depth) override;

};

enum class JoinCondType : uint8_t {
   REGULAR,    // Explicit conditions
   NATURAL,    // Implied conditions
   CROSS,      // No condition
   POSITIONAL, // Positional condition
   ASOF,       // AsOf conditions
   DEPENDENT,  // Dependent join conditions
};

enum class JoinType : uint8_t {
   INVALID = 0, // invalid join type
   LEFT = 1,    // left
   RIGHT = 2,   // right
   INNER = 3,   // inner
   OUTER = 4,   // outer
   SEMI = 5,    // LEFT SEMI join returns left side row ONLY if it has a join partner, no duplicates.
   ANTI = 6,    // LEFT ANTI join returns left side row ONLY if it has NO join partner, no duplicates
   MARK = 7,    // MARK join returns marker indicating whether or not there is a join partner (true), there is no join
                // partner (false)
   SINGLE = 8,  // SINGLE join is like LEFT OUTER JOIN, BUT returns at most one join partner per entry on the LEFT side
                // (and NULL if no partner is found)
   RIGHT_SEMI = 9, // RIGHT SEMI join is created by the optimizer when the children of a semi join need to be switched
                   // so that the build side can be the smaller table
   RIGHT_ANTI = 10 // RIGHT ANTI join is created by the optimizer when the children of an anti join need to be
                   // switched so that the build side can be the smaller table
};
} // namespace lingodb::ast
