#pragma once

#include "../utility/utility.h"
#include <map>
#include <string>
#include <utility>
#include <opencv2/opencv.hpp>

using namespace utility;
using namespace std;
using namespace cv;

namespace input {
    map<ImageID, map<TeaBoxCorner, Point2d>> image2DCoordinates();

    map<TeaBoxCorner, Point3d> teabox3DCoordinates();

    map<ImageID, string> imageLocation(); 

    map<ImageID, string> imageWriteLocation(); 

    map<ImageID, string> matlabWriteLocationTask1a(); 

    map<ImageID, string> matlabWriteLocationTask1b(); 
    
} // namespace input
