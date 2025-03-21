cmake_minimum_required(VERSION 3.30)

project(protobuf_parser)

set(CMAKE_CXX_STANDARD 23)

add_compile_options($<$<CXX_COMPILER_ID:GNU,Clang>:-Wall> $<$<CXX_COMPILER_ID:GNU,Clang>:-Wextra>)

find_package(Boost REQUIRED COMPONENTS system)

add_executable(protobuf_parser
  protobuf_ast.cpp
  protobuf_ast.hpp
  protobuf_parser.hpp
  main.cpp
)

target_link_libraries(protobuf_parser
PRIVATE
  Boost::system
)
