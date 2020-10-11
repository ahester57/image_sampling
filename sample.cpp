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

    // open image
    img_struct_t* og_image = open_image(input_image.c_str());

    if (og_image == NULL) {
        std::cerr << "Could not open image :(" << std::endl;
        return -1;
    }

    cv::Mat down_image = og_image->image, up_image;
    cv::imshow("original", og_image->image);
    cv::waitKey(0);

    switch (sampling_method) {
        case 1:
            // do deletions/replications
            std::cout << "Using deletion and replication for sampling." << std::endl;
            for (int i = 0; i < depth; ++i) {
                down_image = downsample_delete(down_image);
                std::cout << "Image size is:\t\t\t" << down_image.cols << "x" << down_image.rows << std::endl;
                cv::imshow("down", down_image);
                cv::waitKey(0);
                up_image = down_image;
                for (int j = 0; j <= i; ++j) {
                    up_image = upsample_replicate(up_image);
                    std::cout << "Image size is:\t\t\t" << up_image.cols << "x" << up_image.rows << std::endl;
                    cv::imshow("up", up_image);
                    cv::waitKey(0);
                }
            }
            break;
        case 2:
            // do the averaging/interpolation
            std::cout << "Using averaging and interpolation for sampling." << std::endl;
            break;
        default:
            // no
            std::cerr << "You can't do that!" << std::endl;
            return -1;
    }

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
