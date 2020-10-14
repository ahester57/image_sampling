// sample.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Austin Hester CS542o oct 2020
// g++.exe (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0

#include <vector>
#include <iostream>

#include "./include/cla_parse.hpp"
#include "./include/dir_func.hpp"
#include "./include/img_transform.hpp"
#include "./include/img_struct.hpp"


int
wait_key()
{
    char key_pressed = cv::waitKey(0) & 255;
    // 'q' or  <escape> quits out
    if (key_pressed == 27 || key_pressed == 'q') {
        cv::destroyAllWindows();
        return 0;
    }
    return 1;
}

int
run_spatial_sampling(
    cv::Mat down_image,
    uint depth,
    uint intensity_levels,
    bool grayscale,
    std::string output_dir_path,
    std::string file_prefix,
    std::function<cv::Mat(cv::Mat)> down_function,
    std::function<cv::Mat(cv::Mat)> up_function,
    std::string inter_type
)
{
    cv::Mat up_image;
    std::string grayscale_string = grayscale ? "grayscale_" : "";
    std::string intensity_string = "intensity_" + std::to_string(intensity_levels) + "_";
    for (int i = 0; i < depth; ++i) {
        // run the downsample function
        down_image = down_function(down_image);
        std::cout << "Image size is:\t\t\t" << down_image.cols << "x" << down_image.rows << std::endl;

        std::string down_file_name = file_prefix + "_down_" + grayscale_string + intensity_string + inter_type + "_" + std::to_string(i) + ".png";
        write_img_to_file(down_image, output_dir_path, down_file_name);

        cv::imshow(down_file_name, down_image);
        if (!wait_key()) return 0;

        up_image = down_image;
        for (int j = 0; j <= i; ++j) {
            up_image = up_function(up_image);
            std::cout << "Image size is:\t\t\t" << up_image.cols << "x" << up_image.rows << std::endl;

            std::string up_file_name = file_prefix + "down_" + grayscale_string + intensity_string + inter_type + "_" +  std::to_string(i) + "_up_" + std::to_string(j) + ".png";
            write_img_to_file(up_image, output_dir_path, up_file_name);

            cv::imshow(up_file_name, up_image);
            if (!wait_key()) return 0;
        }
    }
    return 1;
}

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
        &intensity, &grayscale
    );
    if (parse_result != 1) return parse_result;

    // open image
    img_struct_t* og_image = open_image(input_image.c_str(), grayscale);
    cv::Mat down_image = og_image->image;

    if (intensity > 0 && intensity < 8) {
        down_image = intensity_adjust(og_image->image, intensity);
    }

    if (og_image == NULL) {
        std::cerr << "Could not open image :(" << std::endl;
        return -1;
    }

    cv::imshow("original", og_image->image);
    cv::waitKey(0);

    std::function<cv::Mat(cv::Mat)> down_function;
    std::function<cv::Mat(cv::Mat)> up_function;
    std::string inter_type;

    switch (sampling_method) {
        case 1:
            // do deletions/replications
            std::cout << "Using deletion and replication for sampling." << std::endl;
            down_function = downsample_delete;
            up_function = upsample_replicate;
            inter_type = "deletion";
            break;
        case 2:
            // do the averaging/interpolation
            std::cout << "Using averaging and interpolation for sampling." << std::endl;
            down_function = downsample_average;
            up_function = upsample_average;
            inter_type = "average";
            break;
        case 3:
            // do the pyraminds
            std::cout << "Using pyramids for sampling." << std::endl;
            down_function = downsample_pyramid;
            up_function = upsample_pyramid;
            inter_type = "pyramid";
            break;
        default:
            // no
            std::cerr << "You can't do that!" << std::endl;
            return -1;
    }

    return !run_spatial_sampling(
        down_image,
        depth,
        intensity,
        grayscale,
        output_dir_path,
        og_image->file_name,
        down_function,
        up_function,
        inter_type
    );
}
