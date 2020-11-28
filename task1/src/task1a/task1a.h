#ifndef __TASK1A_H__
#define __TASK1A_H__

#include "../utility/utility.h"
#include <map>
#include <opencv2/opencv.hpp>
#include <string>

using namespace utility;
using namespace std;
using namespace cv;

namespace task1a
{

    map<ImageID, map<string, Mat>> task1a();

}

#endif
