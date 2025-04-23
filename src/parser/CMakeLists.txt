set(BISON_INPUT_FILE ${CMAKE_SOURCE_DIR}/src/parser/parser.y)
set(FLEX_INPUT_FILE ${CMAKE_SOURCE_DIR}/src/parser/lexer.l)
BISON_TARGET(parser ${BISON_INPUT_FILE} ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp)
FLEX_TARGET(lexer ${FLEX_INPUT_FILE} ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp)

add_library(lingo_db_parser
        driver.cpp
        ast/nodes/expr.cpp

        node_factory.cpp
        base_expression.cpp
        parsed_expression.cpp
        query_node.cpp
        tableref.cpp

        query_node/select_node.cpp


        parsed_expression/comparison_expression.cpp
        parsed_expression/columnref_expression.cpp
        parsed_expression/star_expression.cpp
        parsed_expression/constant_expression.cpp
        parsed_expression/conjunction_expression.cpp

        tableref/basetableref.cpp

        ${BISON_parser_OUTPUTS}
        ${FLEX_lexer_OUTPUTS}
    )