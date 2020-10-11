// cla_parse.cpp : Parse given command line arguments.
// Austin Hester CS542o sept 2020
// g++.exe (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0

#include <opencv2/core/core.hpp>
#include <iostream>

#include "./include/cla_parse.hpp"


// parse command line arguments
int
parse_arguments(
    int argc,
    const char** argv,
    std::string* input_dir_path,
    std::string* output_dir_path,
    uint* rows,
    uint* cols,
    bool* preserve_aspect,
    bool* grayscale,
    std::string* file_type
) {
    cv::String keys =
        "{@indir      |<none>| input directory}"             // input directory is the first argument (positional)
        "{@outdir     |./out | output directory}"
        "{rows r      |1080  | --rows=1080}"                 // optional, default value 1080
        "{cols c      |1920  | --cols=1920}"                 // optional, default value 1920
        "{help h      |      | show help message}"           // optional, show help optional
        "{aspect a    |      | preserve aspect ratio}"
        "{grayscale g |      | output grayscale}"
        "{type t      |jpg   | output filetype jpg, tif, bmp, or png}";

    cv::CommandLineParser parser(argc, argv, keys);

    if (parser.has("h")) {
        parser.printMessage();
        return 0;
    }

    try {
        *input_dir_path = (std::string) parser.get<std::string>(0).c_str();
    } catch (...) {
        std::cerr << "Failed to parse input directory argument!:" << std::endl;
        return -1;
    }

    try {
        *output_dir_path = (std::string) parser.get<std::string>(1).c_str();
    } catch (...) {
        std::cerr << "Failed to parse output directory argument!:" << std::endl;
        return -1;
    }

    try {
        *rows = (uint) parser.get<uint>("r") ? parser.get<uint>("r") : 1080;
        *cols = (uint) parser.get<uint>("c") ? parser.get<uint>("c") : 1920;
    } catch (...) {
        std::cerr << "Failed to parse size argument." << std::endl;
        return -1;
    }

    try {
        *preserve_aspect = (bool) parser.has("a") ? true : false;
    } catch (...) {
        std::cerr << "Failed to parse preserve_aspect argument." << std::endl;
        return -1;
    }

    try {
        *grayscale = (bool) parser.has("g") ? true : false;
    } catch (...) {
        std::cerr << "Failed to parse grayscale argument." << std::endl;
        return -1;
    }

    try {
        *file_type = (std::string) parser.get<std::string>("t").c_str();
    } catch (...) {
        std::cerr << "Failed to parse file type argument!:" << std::endl;
        return -1;
    }

    if (*rows == 0 || *cols == 0) {
        std::cerr << "Dimensions cannot be zero." << std::endl;
        return -1;
    }
    if (*rows > 1080 || *cols > 1920) {
        std::cerr << "Dimensions too large. Max 1920x1080" << std::endl;
        return -1;
    }

    if (!parser.check()) {
        parser.printErrors();
        parser.printMessage();
        return -1;
    }

    return 1;
}
