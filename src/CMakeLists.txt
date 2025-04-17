
add_subdirectory(parser)

add_executable(lingo_db_parser_main main.cpp)
target_link_libraries(lingo_db_parser_main lingo_db_parser)
