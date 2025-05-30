%{ /* -*- C++ -*- */
# include <cerrno>
# include <climits>
# include <cstdlib>
# include <cstring> // strerror
# include <string>
# include "parser/driver.h"
# include "parser.hpp"
%}

%{
#if defined __clang__
# define CLANG_VERSION (__clang_major__ * 100 + __clang_minor__)
#endif

// Clang and ICC like to pretend they are GCC.
#if defined __GNUC__ && !defined __clang__ && !defined __ICC
# define GCC_VERSION (__GNUC__ * 100 + __GNUC_MINOR__)
#endif

// Pacify warnings in yy_init_buffer (observed with Flex 2.6.4)
// and GCC 6.4.0, 7.3.0 with -O3.
#if defined GCC_VERSION && 600 <= GCC_VERSION
# pragma GCC diagnostic ignored "-Wnull-dereference"
#endif

// This example uses Flex's C back end, yet compiles it as C++.
// So expect warnings about C style casts and NULL.
#if defined CLANG_VERSION && 500 <= CLANG_VERSION
# pragma clang diagnostic ignored "-Wold-style-cast"
# pragma clang diagnostic ignored "-Wzero-as-null-pointer-constant"
#elif defined GCC_VERSION && 407 <= GCC_VERSION
# pragma GCC diagnostic ignored "-Wold-style-cast"
# pragma GCC diagnostic ignored "-Wzero-as-null-pointer-constant"
#endif

#define FLEX_VERSION (YY_FLEX_MAJOR_VERSION * 100 + YY_FLEX_MINOR_VERSION)

// Old versions of Flex (2.5.35) generate an incomplete documentation comment.
//
//  In file included from src/scan-code-c.c:3:
//  src/scan-code.c:2198:21: error: empty paragraph passed to '@param' command
//        [-Werror,-Wdocumentation]
//   * @param line_number
//     ~~~~~~~~~~~~~~~~~^
//  1 error generated.
#if FLEX_VERSION < 206 && defined CLANG_VERSION
# pragma clang diagnostic ignored "-Wdocumentation"
#endif

// Old versions of Flex (2.5.35) use 'register'.  Warnings introduced in
// GCC 7 and Clang 6.
#if FLEX_VERSION < 206
# if defined CLANG_VERSION && 600 <= CLANG_VERSION
#  pragma clang diagnostic ignored "-Wdeprecated-register"
# elif defined GCC_VERSION && 700 <= GCC_VERSION
#  pragma GCC diagnostic ignored "-Wregister"
# endif
#endif

#if FLEX_VERSION < 206
# if defined CLANG_VERSION
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wdocumentation"
#  pragma clang diagnostic ignored "-Wshorten-64-to-32"
#  pragma clang diagnostic ignored "-Wsign-conversion"
# elif defined GCC_VERSION
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wsign-conversion"
# endif
#endif

// Flex 2.6.4, GCC 9
// warning: useless cast to type 'int' [-Wuseless-cast]
// 1361 |   YY_CURRENT_BUFFER_LVALUE->yy_buf_size = (int) (new_size - 2);
//      |                                                 ^
#if defined GCC_VERSION && 900 <= GCC_VERSION
# pragma GCC diagnostic ignored "-Wuseless-cast"
#endif


%}

%option noyywrap nounput noinput batch debug

%{
  // A number symbol corresponding to the value in S.

  
%}


space			[ \t\r\f]

decdigit        [0-9]
decinteger		{decdigit}+

numeric         ({decinteger}\.{decinteger}?)|(\.{decinteger})

ident_start     [a-zA-Z]
ident_cont      [a-zA-Z0-9]
identifier      {ident_start}{ident_cont}*

%{
  // Code run each time a pattern is matched.
  # define YY_USER_ACTION  loc.columns (yyleng);
%}
%%
%{
  // A handy shortcut to the location held by the driver.
  lingodb::location& loc = drv.location;
  // Code run each time yylex is called.
  loc.step ();
%}
"("             { return lingodb::parser::make_LP(loc); }
")"             { return lingodb::parser::make_RP(loc); }
"["             { return lingodb::parser::make_LB(loc); }
"]"             { return lingodb::parser::make_RB(loc); }
"."             { return lingodb::parser::make_DOT(loc); }
","             { return lingodb::parser::make_COMMA(loc); }
";"             { return lingodb::parser::make_SEMICOLON(loc); }
"+"             { return lingodb::parser::make_PLUS(loc); }
"-"             { return lingodb::parser::make_MINUS(loc); }
"/"             { return lingodb::parser::make_SLASH(loc); }
"*"             { return lingodb::parser::make_STAR(loc); }
"="             { return lingodb::parser::make_EQUAL(loc); }
"<>"            { return lingodb::parser::make_NOT_EQUAL(loc); }
"<="            { return lingodb::parser::make_LESS_EQUAL(loc); }
"<"             { return lingodb::parser::make_LESS(loc); }
">="            { return lingodb::parser::make_GREATER_EQUAL(loc); }
">"             { return lingodb::parser::make_GREATER(loc); }
"||"            { return lingodb::parser::make_CONCAT(loc); }
"#"             { return lingodb::parser::make_YYEOF(loc);}
all             { return lingodb::parser::make_ALL(loc); }
and             { return lingodb::parser::make_AND(loc);}
as              { return lingodb::parser::make_AS(loc);}

from            { return lingodb::parser::make_FROM(loc); }
full            { return lingodb::parser::make_FULL(loc); }
inner            { return lingodb::parser::make_INNER_P(loc); }

left             { return lingodb::parser::make_LEFT(loc); }

not             { return lingodb::parser::make_NOT(loc); }

where           { return lingodb::parser::make_WHERE(loc); }

join            { return lingodb::parser::make_JOIN(loc); }

right           { return lingodb::parser::make_RIGHT(loc); }

on              { return lingodb::parser::make_ON(loc); }
or              { return lingodb::parser::make_OR(loc); }
outer           { return lingodb::parser::make_OUTER_P(loc); }

select          { return lingodb::parser::make_SELECT(loc); }

<<EOF>>    return lingodb::parser::make_YYEOF (loc);
{identifier}    {
                    std::string ident(yytext);
                    std::transform(ident.begin(), ident.end(), ident.begin(),
                        [](unsigned char c){ return std::tolower(c); });
                    return lingodb::parser::make_IDENTIFIER(std::move(ident), loc);
                }
{decinteger}	{
				    return lingodb::parser::make_ICONST(std::stoul(yytext), loc);
			    }
%%



void
driver::scan_begin ()
{
  yy_flex_debug = trace_scanning;
  if (file.empty () || file == "-")
    yyin = stdin;
  else if (!(yyin = fopen (file.c_str (), "r")))
    {
      std::cerr << "cannot open " << file << ": " << strerror (errno) << '\n';
      exit (EXIT_FAILURE);
    }
}

void
driver::scan_end ()
{
  fclose (yyin);
}
