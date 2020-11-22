#pragma once

#include <string>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

namespace utility {

    // Enum for teabox corners
    enum TeaBoxCorner {ZERO = 0, ONE = 1, TWO = 2, THREE = 3, FOUR = 4, FIVE = 5, SIX = 6, SEVEN = 7, LASTTBC};

    // Enum for image ids
    enum ImageID {DSC_9743 = 9743, DSC_9744 = 9744, DSC_9745 = 9745, DSC_9746 = 9746, DSC_9747 = 9747, DSC_9748 = 9748, DSC_9749 = 9749, DSC_9750 = 9750, LASTIID};

    void printMat(string input, Mat image);

    void createMatlabFile(bool points, string output, map<ImageID, string> fileLocations);
    
} // namespace utility
