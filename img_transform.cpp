// img_transform.cpp : Transformation functions
// Austin Hester CS542o sept 2020
// g++.exe (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>

#include "./include/img_transform.hpp"

cv::Mat
scale_image(cv::Mat src, uint rows, uint cols, bool preserve_aspect, cv::InterpolationFlags inter_mode)
{
    cv::Size new_size = cv::Size(cols, rows);
    if (preserve_aspect) {
        new_size = get_size_aspect(src, rows, cols);
    }
    std::cout << "New image size is:\t" << new_size.width << "x" << new_size.height << std::endl;
            
    cv::Mat dst = cv::Mat::zeros(new_size, CV_64FC1);
    resize(src, dst, dst.size(), 0, 0, inter_mode);
    src.release();
    return dst;
}

// calculate scaling
cv::Size
get_size_aspect(cv::Mat src, uint rows, uint cols)
{
    uint d_rows = src.rows, d_cols = src.cols;
    float col_scale = (float) cols / src.cols;
    float row_scale = (float) rows / src.rows;

    // decide which way to scale
    if (src.cols * row_scale > cols) {
        // set columns to maximum provided
        d_cols = cols;
        d_rows = (uint) (src.rows * col_scale);
        std::cout << "Scaled up cols:\t" << col_scale << std::endl;
    } else {
        // set rows to maximum provided
        d_rows = rows;
        d_cols = (uint) (src.cols * row_scale);
        std::cout << "Scaled up rows:\t" << row_scale << std::endl;
    }
    return cv::Size(d_cols, d_rows);
}

cv::Mat
apply_grayscale(cv::Mat src)
{
    cv::Mat dst = cv::Mat::zeros(src.size(), CV_8U);
    cv::cvtColor(src, dst, cv::COLOR_BGR2GRAY);
    src.release();
    return dst;
}

cv::Mat
downsample_delete(cv::Mat src)
{
    cv::Mat dst = cv::Mat::zeros(cv::Size(src.cols / 2, src.rows / 2), src.type());
    // resize(src, dst, dst.size(), 0, 0, cv::INTER_NEAREST);
    if (src.channels() == 1) {
        std::cout << "Grayscale Image <uchar>" << std::endl;
    } else if (src.channels() == 3) {
        std::cout << "Color Image <cv::Vec3b>" << std::endl;
    } else {
        std::cout << "Unknown Image. Goodbye." << std::endl;
        return src;
    }
    for (int r = 0; r < src.rows-1; r+=2) {
        for (int c = 0; c < src.cols-1; c+=2) {
            if (src.channels() == 1) {
                dst.at<uchar>(r/2, c/2) = src.at<uchar>(r, c);
            } else if (src.channels() == 3) {
                dst.at<cv::Vec3b>(r/2, c/2) = src.at<cv::Vec3b>(r, c);
            }
        }
    }
    src.release();
    return dst;
}

cv::Mat
upsample_replicate(cv::Mat src)
{
    cv::Mat dst = cv::Mat::zeros(cv::Size(src.cols * 2, src.rows * 2), src.type());
    // resize(src, dst, dst.size(), 0, 0, cv::INTER_NEAREST);
    if (src.channels() == 1) {
        std::cout << "Grayscale Image <uchar>" << std::endl;
    } else if (src.channels() == 3) {
        std::cout << "Color Image <cv::Vec3b>" << std::endl;
    } else {
        std::cout << "Unknown Image. Goodbye." << std::endl;
        return src;
    }
    for (int r = 0; r < src.rows-1; r++) {
        for (int c = 0; c < src.cols-1; c++) {
            if (src.channels() == 1) {
                dst.at<uchar>(r*2, c*2) = src.at<uchar>(r, c);
                dst.at<uchar>(r*2, c*2+1) = src.at<uchar>(r, c);
                dst.at<uchar>(r*2+1, c*2) = src.at<uchar>(r, c);
                dst.at<uchar>(r*2+1, c*2+1) = src.at<uchar>(r, c);
            } else if (src.channels() == 3) {
                dst.at<cv::Vec3b>(r*2, c*2) = src.at<cv::Vec3b>(r, c);
                dst.at<cv::Vec3b>(r*2, c*2+1) = src.at<cv::Vec3b>(r, c);
                dst.at<cv::Vec3b>(r*2+1, c*2) = src.at<cv::Vec3b>(r, c);
                dst.at<cv::Vec3b>(r*2+1, c*2+1) = src.at<cv::Vec3b>(r, c);
            }
        }
    }
    src.release();
    return dst;
}

cv::Mat
downsample_average(cv::Mat src)
{
    cv::Mat dst = cv::Mat::zeros(cv::Size(src.cols / 2, src.rows / 2), src.type());
    resize(src, dst, dst.size(), 0, 0, cv::INTER_LANCZOS4);
    src.release();
    return dst;
}

cv::Mat
upsample_average(cv::Mat src)
{
    cv::Mat dst = cv::Mat::zeros(cv::Size(src.cols * 2, src.rows * 2), src.type());
    resize(src, dst, dst.size(), 0, 0, cv::INTER_LANCZOS4);
    src.release();
    return dst;
}

cv::Mat
downsample_pyramid(cv::Mat src)
{
    cv::Mat dst = src;
    cv::pyrDown(src, dst, cv::Size(src.cols / 2, src.rows / 2));
    src.release();
    return dst;
}

cv::Mat
upsample_pyramid(cv::Mat src)
{
    cv::Mat dst = src;
    cv::pyrUp(src, dst, cv::Size(src.cols * 2, src.rows * 2));
    src.release();
    return dst;
}

cv::Mat
intensity_adjust(cv::Mat src, uint8_t level)
{
    cv::Mat dst = cv::Mat::zeros(cv::Size(src.cols, src.rows), src.type());
    if (src.channels() == 1) {
        std::cout << "Grayscale Image <uchar>" << std::endl;
    } else if (src.channels() == 3) {
        std::cout << "Color Image <cv::Vec3b>" << std::endl;
    } else {
        std::cout << "Unknown Image. Goodbye." << std::endl;
        return src;
    }
    for (int r = 0; r < src.rows; r++) {
        for (int c = 0; c < src.cols; c++) {
            if (src.channels() == 1) {
                uchar pixel = src.at<uchar>(r, c);
                pixel = (pixel >> level) << level;
                dst.at<uchar>(r, c) = pixel;
            } else if (src.channels() == 3) {
                cv::Vec3b pixel = src.at<cv::Vec3b>(r, c);
                pixel[0] = (pixel[0] >> level) << level;
                pixel[1] = (pixel[1] >> level) << level;
                pixel[2] = (pixel[2] >> level) << level;
                dst.at<cv::Vec3b>(r, c) = pixel;
            }
        }
    }
    src.release();
    return dst;
}
