#include "helper.h"
#include <string>
#include <iostream>
#include <opencv2/opencv.hpp>

namespace global {
     void printMat(std::string input, cv::Mat image)
     {
          std::cout << input + " = " << std::endl << format(image, cv::Formatter::FMT_CSV) << std::endl << std::endl;
     }
}