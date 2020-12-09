#ifndef __INPUT_H__
#define __INPUT_H__

#include "../utility/utility.h"
#include <map>
#include <opencv2/opencv.hpp>
#include <string>

using namespace std;
using namespace cv;

namespace input
{
    map<utility::ImageID, map<utility::TeaBoxCorner, Point2d>> image2DCoordinates();

    map<utility::TeaBoxCorner, Point3d> teabox3DCoordinates();

    map<utility::ImageID, string> imageLocation();

    map<utility::ImageID, string> imageWriteLocation();

    map<utility::ImageID, string> matlabWriteLocationTask1a();

    map<utility::ImageID, string> matlabWriteLocationTask1b();

    map<utility::ImageIDTask2, string> imageLocationTask2();

    map<utility::ImageIDTask2, string> imageWriteLocationTask2();

    map<utility::ImageIDTask3, string> imageLocationTask3();

    map<utility::ImageIDTask3, string> matlabWriteLocationTask3();

} // namespace input

#endif