//: protobuf_ast.hpp

#pragma once

#include <boost/spirit/home/x3/support/ast/variant.hpp>

#include <tuple>
#include <vector>
#include <variant>

namespace protobuf_ast {

enum class builtin_type
{
  String,
  Boolean,
  Bytes,
  Float,
  Double,
  Int32,
  Int64,
  UInt32,
  UInt64,
  SInt32,
  SInt64,
  Fixed32,
  Fixed64,
  SFixed32,
  SFixed64
};

using type = std::variant<builtin_type, std::string>;

enum attr
{
  Repeated,
  Optional,
  Required
};

using msg_field = std::tuple<protobuf_ast::attr, protobuf_ast::type, std::string, int>;
using message = std::tuple<std::string, std::vector<msg_field>>;

} // namespace protobuf_ast

std::ostream& operator<<(std::ostream&, protobuf_ast::message const&);
