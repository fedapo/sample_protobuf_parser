//: protobuf_parser.hpp

#pragma once

#include "protobuf_ast.hpp"

#include <boost/fusion/include/std_pair.hpp>
#include <boost/fusion/include/std_tuple.hpp>
#include <boost/spirit/home/x3.hpp>

#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

struct protobuf_parse_exception : std::exception {};

namespace protobuf_grammar
{
  namespace x3 = boost::spirit::x3;

  namespace kw // keywords
  {
    auto const message = x3::lit("message");

    // message field attributes
    auto const repeated = x3::lit("repeated");
    auto const optional = x3::lit("optional");
    auto const required = x3::lit("required");

    // data types
    auto const string   = x3::lit("string")   >> x3::attr(protobuf_ast::builtin_type::String);
    auto const bytes    = x3::lit("bytes")    >> x3::attr(protobuf_ast::builtin_type::Bytes);
    auto const float_   = x3::lit("float")    >> x3::attr(protobuf_ast::builtin_type::Float);
    auto const double_  = x3::lit("double")   >> x3::attr(protobuf_ast::builtin_type::Double);
    auto const uint32   = x3::lit("uint32")   >> x3::attr(protobuf_ast::builtin_type::UInt32);
    auto const uint64   = x3::lit("uint64")   >> x3::attr(protobuf_ast::builtin_type::UInt64);
    auto const int32    = x3::lit("int32")    >> x3::attr(protobuf_ast::builtin_type::Int32);
    auto const int64    = x3::lit("int64")    >> x3::attr(protobuf_ast::builtin_type::Int64);
    auto const sint32   = x3::lit("sint32")   >> x3::attr(protobuf_ast::builtin_type::SInt32);
    auto const sint64   = x3::lit("sint64")   >> x3::attr(protobuf_ast::builtin_type::SInt64);
    auto const fixed32  = x3::lit("fixed32")  >> x3::attr(protobuf_ast::builtin_type::Fixed32);
    auto const fixed64  = x3::lit("fixed64")  >> x3::attr(protobuf_ast::builtin_type::Fixed64);
    auto const sfixed32 = x3::lit("sfixed32") >> x3::attr(protobuf_ast::builtin_type::SFixed32);
    auto const sfixed64 = x3::lit("sfixed64") >> x3::attr(protobuf_ast::builtin_type::SFixed64);
    auto const boolean  = x3::lit("bool")     >> x3::attr(protobuf_ast::builtin_type::Boolean);
  }

  auto const builtin_type = x3::rule<class builtin_type, protobuf_ast::builtin_type>()
                          = kw::string | kw::bytes | kw::boolean
                          | kw::float_ | kw::double_
                          | kw::int32 | kw::int64
                          | kw::uint32 | kw::uint64
                          | kw::sint32 | kw::sint64
                          | kw::fixed32 | kw::fixed64
                          | kw::sfixed32 | kw::sfixed64;
  auto const reserved = builtin_type
                      | kw::message | kw::repeated | kw::optional | kw::required;
  auto const type_attribute = x3::rule<class type_attribute, protobuf_ast::attr>()
                            = kw::repeated >> x3::attr(protobuf_ast::attr::Repeated)
                            | kw::optional >> x3::attr(protobuf_ast::attr::Optional)
                            | kw::required >> x3::attr(protobuf_ast::attr::Required);
  auto const identifier = x3::rule<class identifier, std::string>()
                        = x3::lexeme[ x3::alpha >> *x3::alnum ] - reserved;
  //auto const char_literal =  x3::no_skip['"' >> *(~x3::char_('"')) >> '"'];
  auto const char_literal = x3::rule<class char_literal, std::string>()
                          =  x3::no_skip['"' >> *(x3::char_ - '"') >> '"'];
  auto const type = x3::rule<class type, protobuf_ast::type>()
                  = builtin_type | identifier;
  auto const msg_field = x3::rule<class msg_field, protobuf_ast::msg_field>()
                       = type_attribute >> type >> identifier >> '=' >> x3::int_ >> ';';
  auto const msg_fields = *msg_field;
  auto const func_param = type;
  auto const enum_item = x3::rule<class enum_item>()
                       = identifier >> '=' >> x3::int_ >> ';';
  auto const message = x3::rule<class message, protobuf_ast::message>()
                     = kw::message >> identifier >> '{' >> msg_fields >> '}';
}

template <class IT>
bool protobuf_parse(IT it1, IT it2, protobuf_ast::message& ast)
{
  namespace x3 = boost::spirit::x3;

  bool res = x3::phrase_parse(it1, it2, protobuf_grammar::message, x3::space, ast);

  if(!res)
    throw protobuf_parse_exception();

  return res;
}
