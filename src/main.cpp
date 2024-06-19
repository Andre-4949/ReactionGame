//
// Created by andre on 14.06.2024.
//
#include <iostream>
#include <vector>
#include <fstream>
#include "opencv2/opencv.hpp"
#include <opencv2/opencv.hpp>
#include <chrono>
#include "../include/Scene/HelperClasses/Label.h"
//TODO KITTI_PATH environmental variable (data_tracking_image_2, data_tracking_label_2)
int main() {
    std::cout << "openCV version: " << CV_VERSION << std::endl;

    std::string path;
    std::cout << "Enter path to an image: ";
    std::cin >> path;
    cv::Mat image = cv::imread(path);
    if (image.empty()) {
        std::cerr << "Error: Could not open or find the image!" << std::endl;
        return -1;
    }
    cv::imshow("Display Image", image);
    cv::waitKey(0);

}