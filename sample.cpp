// sample.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Austin Hester CS542o oct 2020
// g++.exe (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0

#include <vector>
#include <iostream>

#include "./include/cla_parse.hpp"
#include "./include/dir_func.hpp"
// #include "./include/img_display.hpp"
#include "./include/img_transform.hpp"
#include "./include/img_struct.hpp"


int
main(int argc, const char** argv)
{
    // CLA variables
    uint sampling_method;
    uint depth;
    uint intensity;
    bool grayscale;
    std::string input_image;
    std::string output_dir_path;

    // parse and save command line args
    int parse_result = parse_arguments(
        argc, argv,
        &input_image, &output_dir_path,
        &sampling_method, &depth,
        &intensity
    );
    if (parse_result != 1) return parse_result;

    // open input directory and return list of relative file paths
    // std::vector<std::string> file_paths = open_dir(input_dir_path.c_str());

    // create list of images using provided file paths
    // std::vector<img_struct_t> src_image_vector = get_images_from_path_vector(file_paths);
    std::vector<img_struct_t> dst_image_vector;

    // for (img_struct_t image_struct : src_image_vector) {
        // cv::Mat new_img = scale_image(image_struct.image, rows, cols, preserve_aspect, cv::INTER_LANCZOS4);
    //     if (grayscale) {
    //         new_img = apply_grayscale(new_img);
    //     }
    //     dst_image_vector.push_back({new_img, image_struct.metadata});
    //     image_struct.image.release();
    //     // cv::imshow("hi", new_img);
    //     // cv::waitKey(0);
    // }
    // write_to_dir(dst_image_vector, output_dir_path, file_type);
	return 0;
}
