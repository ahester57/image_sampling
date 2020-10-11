// cla_parse.hpp : Parse given command line arguments.
// Austin Hester CS542o sept 2020
// g++.exe (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0

#ifndef _H_CLA_PARSE
#define _H_CLA_PARSE

#include <opencv2/core/core.hpp>
#include <iostream>

int parse_arguments(
    const int argc,
    const char** argv,
    std::string* input_dir_path,
    std::string* output_dir_path,
    uint* rows,
    uint* cols,
    bool* preserve_aspect,
    bool* grayscale,
    std::string* file_type
);

#endif
