//: protobuf_ast.cpp

#include "protobuf_ast.hpp"

struct message_to_stream
{
  std::ostream& os;

  void operator()(protobuf_ast::attr a) const
  {
    switch(a)
    {
      case protobuf_ast::attr::Optional: os << "optional"; break;
      case protobuf_ast::attr::Required: os << "required"; break;
      case protobuf_ast::attr::Repeated: os << "repeated"; break;
    }
  }

  void operator()(protobuf_ast::type t) const
  {
    if(t.index() == 0)
    {
      switch(std::get<0>(t))
      {
        case protobuf_ast::builtin_type::String: os << "string"; break;
        case protobuf_ast::builtin_type::Boolean: os << "bool"; break;
        case protobuf_ast::builtin_type::Bytes: os << "bytes"; break;
        case protobuf_ast::builtin_type::Float: os << "float"; break;
        case protobuf_ast::builtin_type::Double: os << "double"; break;
        case protobuf_ast::builtin_type::UInt32: os << "uint32"; break;
        case protobuf_ast::builtin_type::UInt64: os << "uint64"; break;
        case protobuf_ast::builtin_type::SInt32: os << "sint32"; break;
        case protobuf_ast::builtin_type::SInt64: os << "sint64"; break;
        case protobuf_ast::builtin_type::Int32: os << "int32"; break;
        case protobuf_ast::builtin_type::Int64: os << "int64"; break;
        case protobuf_ast::builtin_type::Fixed32: os << "fixed32"; break;
        case protobuf_ast::builtin_type::Fixed64: os << "fixed64"; break;
        case protobuf_ast::builtin_type::SFixed32: os << "sfixed32"; break;
        case protobuf_ast::builtin_type::SFixed64: os << "sfixed64"; break;
      }
    }
    else
    {
      os << std::get<1>(t);
    }
  }

  void operator()(std::string const& d) const
  {
    os << d;
  }

  void operator()(int i) const
  {
    os << i;
  }
};

std::ostream& operator<<(std::ostream& os, protobuf_ast::message const& ast)
{
  os << "message " << std::get<0>(ast) << " {\n";

  for(auto& el : std::get<1>(ast))
  {
    message_to_stream m2s{os};

    os << "  ";   m2s(std::get<0>(el));
    os << " ";    m2s(std::get<1>(el));
    os << " ";    m2s(std::get<2>(el));
    os << " = ";  m2s(std::get<3>(el));
    os << ";\n";
  }

  os << "}\n";

  return os;
}
