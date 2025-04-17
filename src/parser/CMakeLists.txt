set(BISON_INPUT_FILE ${CMAKE_SOURCE_DIR}/src/parser/parser.y)
set(FLEX_INPUT_FILE ${CMAKE_SOURCE_DIR}/src/parser/lexer.l)
BISON_TARGET(parser ${BISON_INPUT_FILE} ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp)
FLEX_TARGET(lexer ${FLEX_INPUT_FILE} ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp)

add_library(lingo_db_parser
        driver.cpp
        ast/nodes/expr.cpp
        ${BISON_parser_OUTPUTS}
        ${FLEX_lexer_OUTPUTS}
    )