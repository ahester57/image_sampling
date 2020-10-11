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
    std::string* input_image,
    std::string* output_dir_path,
    uint* sampling_method,
    uint* depth,
    uint* intensity
) {
    cv::String keys =
        "{@image       |<none>| input image}"             // input image is the first argument (positional)
        "{@outdir      |./out | output directory}"
        "{sampling s   |1     | 1 = deletion/duplication \n\t\t2 = averaging/interpolation}"
        "{depth d      |1     | layers of downsampling}"                 // optional, 
        "{intensity i  |1     | number of intensity levels}"                 // optional, 
        "{help h       |      | show help message}";           // optional

    cv::CommandLineParser parser(argc, argv, keys);

    if (parser.has("h")) {
        parser.printMessage();
        return 0;
    }

    if (!parser.check()) {
        parser.printErrors();
        parser.printMessage();
        return -1;
    }

    try {
        *input_image = (std::string) parser.get<std::string>(0).c_str();
    } catch (...) {
        std::cerr << "Failed to parse input image argument!:" << std::endl;
        return -1;
    }

    try {
        *output_dir_path = (std::string) parser.get<std::string>(1).c_str();
    } catch (...) {
        std::cerr << "Failed to parse output directory argument!:" << std::endl;
        return -1;
    }

    try {
        *sampling_method = (uint) parser.get<uint>("s") ? parser.get<uint>("s") : 1;
        if (*sampling_method != 1 && *sampling_method != 2) {
            std::cerr << "Sampling method can only be 1 or 2." << std::endl;
            return -1;
        }
    } catch (...) {
        std::cerr << "Failed to parse sampling_method argument." << std::endl;
        return -1;
    }

    try {
        *depth = (uint) parser.get<uint>("d") ? parser.get<uint>("d") : 1;
        if (*depth > 10) std::cout << "You're wasting your time." << std::endl;
    } catch (...) {
        std::cerr << "Failed to parse depth argument." << std::endl;
        return -1;
    }

    try {
        *intensity = (uint) parser.get<uint>("i") ? parser.get<uint>("i") : 1;
        if (*intensity < 1 || *intensity > 7) {
            std::cerr << "Intensity can only be from 1 to 7." << std::endl;
            return -1;
        }
    } catch (...) {
        std::cerr << "Failed to parse intensity argument." << std::endl;
        return -1;
    }


    return 1;
}
