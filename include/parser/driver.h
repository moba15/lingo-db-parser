#pragma once

#include "parser/parser.hpp"
#include "parser/ast/nodes/nodes.h"
#include "parser/ast/nodes/select.h"
# define YY_DECL \
yy::parser::symbol_type yylex (driver& drv)
// ... and declare it for the parser's sake.
YY_DECL;



class driver {

public:
	driver();
	~driver()  {//TODO cleanUP
		};
	//TODO result
	std::shared_ptr<nodes::SelectStatement> result;
	int parse (const std::string& f);
	void scan_begin ();
	void scan_end ();
	yy::location location;
	std::string file;
	bool trace_scanning;
	bool trace_parsing;
	nodes::NodeFactory nf;
};