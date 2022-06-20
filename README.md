# Protobuf Parser

federico.aponte@gmail.com

## Description

This is a sample implementation of a Protobuf parser using the Boost.Spirit X3 parsing library.

At the moment the parser is very limited, it only parses a single Protobuf `message` object. This is a sample of the structure:

```proto
message Object
{
  required uint32 id = 0;
  required ObjType type = 1;
  optional string name = 2;
  repeated string tags = 3;
  optional double length = 4;
}
```

The result of a successful parsing is an C++ `std::tuple` object - aliased as `message` - with the following structure.

```c++
using msg_field = std::tuple
                  <
                      protobuf_ast::attr,
                      protobuf_ast::type,
                      std::string,
                      int
                  >;

using message = std::tuple
                <
                    std::string,
                    std::vector<msg_field>
                >;
```

One could define similar `struct`s with the advantage over `std::tuple` of having named fields, but it would require some "glueing" code (based on Boost:Fusion) between the structures and the parser. Simplicity was preferred for this simple example.

The sample application accepts a file name, containing the text to parse, from the command line. Then, the following actions are carried on.

1. The file is read in memory.
2. The content of the file is echoed.
3. The text is parsed.
4. If parsing is successful, data synthesized by the parser is echoed again.

## Building

The sample application is based on Boost.Spirit library, this is a prerequisite. The library can be obtained in several ways.

### Installing Boost.Spirit from a Debian Linux distro.

```sh
> sudo apt install libboost-dev
```

### Installing Boost.Spirit from a Fedora Linux distro.

```sh
> sudo dnf install boost-devel
```

### Installing Boost.Spirit using microsoft Vcpkg

Vcpkg is an interesting package manager that allows to easily manage a large number of libraries both under Windows and Linux.
Here's a quick list of commands to install vcpkg and Boost within.

```sh
> git clone https://github.com/microsoft/vcpkg.git
> cd vcpkg
> ./bootstrap-vcpkg.sh
> ./vcpkg install boost
```

### Building the sample code

Once Boost.Spirit is installed. The example can be built with the following commands.

```ch
> git clone https://github.com/fedapo/sample_protobuf_parser.git
> cd sample_protobuf_parser
> cmake -B build build -DCMAKE_TOOLCHAIN_FILE=$VCPKG_ROOT/vcpkg/scripts/buildsystems/vcpkg.cmake .
> cmake --build build
```

A prerequisite is having an environment variable pointing at the directory where vcpkg is installed.

### Running the sample code

The sample application is minimalist. This is all that is required after the steps above.

```sh
> ./build/protobuf_parser sample1.proto
```
