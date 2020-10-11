// img_display.cpp : This file contains the 'display_images' function.
// Displays images given vector of file paths.
// Austin Hester CS542o sept 2020
// g++.exe (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0

#include "./include/img_display.hpp"
#include "./include/img_struct.hpp"


// display the images
void
display_images(std::vector<std::string> file_paths, uint rows, uint cols)
{
    if (file_paths.size() == 0) return;
    std::vector<std::string>::iterator it = file_paths.begin();

    while (true) { // loop until exit condition

        std::cout << std::endl << "File info:" << std::endl;
        std::cout << ' ' << *it << std::endl;

        try {
            // attempt to read the image
            cv::Mat src = cv::imread(*it);
            if (src.empty()) {
                std::cerr << "Cannot open input image: " + *it << std::endl;
                it = file_paths.erase(it);
                continue;
            }
            std::cout << "Image size is:\t\t\t" << src.cols << "x" << src.rows << std::endl;

            // calculate scaling
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

            // Resize and show the image
            std::cout << "Displayed image size is:\t" << d_cols << "x" << d_rows << std::endl;
            cv::namedWindow(*it, cv::WINDOW_NORMAL);
            cv::resizeWindow(*it, d_cols, d_rows);
            cv::imshow(*it, src);

            // Wait for input
            while (char key_pressed = cv::waitKey(0) & 255) {
                // 'q' or  <escape> quits out
                if (key_pressed == 27 || key_pressed == 'q') {
                    cv::destroyAllWindows();
                    return;
                }
                // 'n' or <space> -> next image
                if (key_pressed == 'n' || key_pressed == ' ') {
                    cv::destroyWindow(*it);
                    if (++it == file_paths.end()) --it;
                    break;
                }
                // 'p' -> previous image
                if (key_pressed == 'p') {
                    cv::destroyWindow(*it);
                    if (it != file_paths.begin()) --it;
                    break;
                }
            }
        } catch (std::string &str) {
            std::cerr << "Error: " << *it << ": " << str << std::endl;
            return;
        } catch (cv::Exception &e) {
            std::cerr << "Error: " << *it << ": " << e.msg << std::endl;
            return;
        }
    }
}
