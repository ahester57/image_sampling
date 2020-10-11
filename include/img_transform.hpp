// img_transform.hpp : Transformation functions
// Austin Hester CS542o sept 2020
// g++.exe (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0

#ifndef _H_IMG_TRANSFORM
#define _H_IMG_TRANSFORM

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>

cv::Mat scale_image(cv::Mat src, uint rows, uint cols, bool preserve_aspect, cv::InterpolationFlags inter_mode);
cv::Size get_size_aspect(cv::Mat src, uint rows, uint cols);
cv::Mat apply_grayscale(cv::Mat src);

#endif
