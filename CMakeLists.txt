cmake_minimum_required (VERSION 3.0)
project (TinyPython)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Run FA2LEXER to generate the lexer
add_custom_command (
  OUTPUT ProjectLexer.cpp
  COMMAND fa2lexer --src ProjectLexer.cpp --tpl ${PROJECT_SOURCE_DIR}/fa/project.fa2l
  MAIN_DEPENDENCY ${PROJECT_SOURCE_DIR}/fa/project.fa2l
  DEPENDS ${PROJECT_SOURCE_DIR}/fa/start.jff

  )

INCLUDE_DIRECTORIES(${CMAKE_BINARY_DIR})
include_directories(${PROJECT_SOURCE_DIR})

add_executable(${PROJECT_NAME} main.cpp ProjectLexer.cpp)

