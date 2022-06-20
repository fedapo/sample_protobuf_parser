//: main.cpp

#include "protobuf_ast.hpp"
#include "protobuf_parser.hpp"

#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
  //cout << "SPIRIT_X3_VERSION: " << showbase << hex << SPIRIT_X3_VERSION << dec << '\n';

  if(argc != 2)
  {
    cerr << "Usage: protobuf_parser <sample_file>\n";
    return 1;
  }

  string fname = argv[1];
  ifstream is(fname, ios::binary | ios::ate);

  if(!is)
  {
    cerr << "Cannot open file " << fname << '\n';
    return 2;
  }

  // load file to be parser in a string
  auto size = is.tellg();
  is.seekg(0);
  string text(size, '\0');
  is.read(text.data(), text.length());

  cout << "Parsing the following text:\n" << text << '\n';

  try
  {
    protobuf_ast::message ast;
    bool res = protobuf_parse(text.begin(), text.end(), ast);

    cout << "Parsed. Echoing the result:\n" << ast << '\n';
  }
  catch(protobuf_parse_exception const& e)
  {
    cerr << "Error: " << e.what() << '\n';
  }
}
