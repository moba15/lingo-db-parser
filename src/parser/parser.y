%skeleton "lalr1.cc" // -*- C++ -*-
%require "3.8.2"
%header

%define api.token.raw

%define api.token.constructor
%define api.value.type variant
%define parse.assert



%code requires {
  # include <string>
  #include <iostream>
  #include "parser/ast/ast.h"
  #include <memory>
  #include "parser/ast/nodes/select.h"
  #include "parser/ast/nodes/expr.h"
  #include "parser/ast/nodes/common.h"
  class driver;
}

// The parsing context.
%param { driver& drv }



%define parse.trace
%define parse.error detailed
%define parse.lac full
%locations
%code {
  #include "parser/driver.h"
  #include <iostream>
  #include "parser/ast/ast.h"
  #include "parser/ast/nodes/select.h"
  #include "parser/ast/nodes/expr.h"
  #include "parser/ast/nodes/common.h"
  #include <memory>
  #define mkNode drv.nf.node
  #define mkList drv.nf.list
  #define mkNotNode drv.nf.notNode


}

%define api.token.prefix {TOK_}

%token <uint64_t>	INTEGER_VALUE	"integer_value"
%token <double>		FLOAT_VALUE	"float_value"
%token <std::string>	IDENTIFIER	"identifier"
%token <std::string>	STRING_VALUE	"string"
%token <std::string>	BIT_VALUE	"bit_string"
%token <std::string>	HEX_VALUE	"hex_string"
%token <std::string>	NATIONAL_VALUE	"nat_string"
%token 			LP		"("
%token 			RP		")"
%token 			LB		"["
%token 			RB		"]"
%token 			DOT		"."
%token 			COMMA		","
%token 			SEMICOLON	";"
%token 			PLUS		"+"
%token 			SLASH		"/"
%token 			STAR		"*"
%token 			MINUS		"-"
%token 			EQUAL		"="
%token 			NOT_EQUAL	"<>"
%token 			LESS_EQUAL	"<="
%token 			LESS		"<"
%token 			GREATER_EQUAL	">="
%token 			GREATER		">"
%token 			QUOTE		"'"
%token 			CONCAT		"||"
%token SELECT WHERE FROM



%type <nodes::RelExpression>		simple_select
%type <std::shared_ptr<nodes::Query>> select_no_parens
%type <std::shared_ptr<nodes::SelectStatement>> SelectStatement
%type <std::vector<nodes::RelExpression>>	from_clause
%type <std::vector<nodes::RelExpression>>	from_list
%type <nodes::RelExpression>						table_ref
%type <std::shared_ptr<nodes::QualifiedName>>					qualified_name
%type <std::vector<std::string>>					qualifier_list
%type <std::shared_ptr<nodes::RowExpr>>					target_list
%type <std::shared_ptr<nodes::QualifiedName>>					target_element
//%token <int> NUMBER "number"
//%nterm <int> exp



%printer { std::cout << ""; } <*>;

%%
%start stmt;
//unit: exp  { drv.result = $1; };
stmt:
    SelectStatement
    {
        drv.result = $SelectStatement;
    }
 ;
SelectStatement:
    select_no_parens
    {
        $$ = mkNode<nodes::SelectStatement>(@$, $select_no_parens);
    }
     ;
select_no_parens:
    simple_select
    {
        $$ = mkNode<nodes::Query>(@$, $simple_select);
    }
;
simple_select:
    SELECT target_list from_clause
    {
        auto expr = mkNode<nodes::SelectExpr>(@$);
        expr->from_clause = $from_clause;
        expr->target_list = $target_list;
        $$ = expr;
    }
;

target_list:
   target_element {$$ = mkNode<nodes::RowExpr>(@$, $target_element);}
 | target_list[list] COMMA target_element {}
 ;
target_element:
    qualified_name { $$ = $qualified_name;}
  | STAR {}
 ;

from_clause:
    FROM from_list { $$ = $from_list;}

  | %empty {}
;

from_list:
    table_ref {$$ = mkList<nodes::RelExpression>(@$); $$.emplace_back($table_ref); }
   | from_list[list] COMMA table_ref {$list.emplace_back($table_ref); $$=$list;}
 ;
table_ref:
    qualified_name[table_name]
    {
        auto node = mkNode<nodes::TableName>(@$, $table_name);
        $$ = node;
    }
;
qualified_name:
    qualifier_list[list]
	{
	    auto last = std::move($list.back());
        $list.pop_back();
        $$ = mkNode<nodes::QualifiedName>(@$, std::move(last));
        $$->qualifier = $list;
	}
 ;

 qualifier_list:
     IDENTIFIER[name]						{  auto l = mkList<std::string>(@$); l.emplace_back($name); $$ = l;}
  |  qualifier_list[qn] DOT IDENTIFIER[name]			{ $qn.push_back($name); $$ = $qn;  }
  ;

where_clause:
    WHERE bool_value_expr {}
;
bool_value_expr:
    bool_predicand {}
;
bool_predicand:
    common_value_expr {}
;
common_value_expr:
    IDENTIFIER
%%
void
yy::parser::error (const location_type& l, const std::string& m)
{
  std::cerr << l << ": " << m << '\n';
}
