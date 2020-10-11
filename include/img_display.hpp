// img_display.hpp : This file contains the 'display_images' function. Program execution begins and ends there.
// Austin Hester CS542o sept 2020
// g++.exe (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0

#ifndef _H_IMG_DISPLAY
#define _H_IMG_DISPLAY

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>

void display_images(std::vector<std::string> file_paths, uint rows, uint cols);

#endif
