#pragma once

#include "parser/parser.hpp"
#include "parser/ast/nodes/select.h"
#include "parser/node_factory.h"
# define YY_DECL \
lingodb::parser::symbol_type yylex (driver& drv)
// ... and declare it for the parser's sake.
YY_DECL;



class driver {

public:
	driver();
	~driver()  {//TODO cleanUP
		};
	//TODO result
	std::shared_ptr<lingodb::ast::QueryNode> result;
	int parse (const std::string& f);
	void scan_begin ();
	void scan_end ();
	lingodb::location location;
	std::string file;
	bool trace_scanning;
	bool trace_parsing;
	lingodb::ast::NodeFactory nf;
};