#ifndef __TASK1B_H__
#define __TASK1B_H__

#include "../utility/utility.h"
#include <map>
#include <opencv2/opencv.hpp>
#include <string>

using namespace utility;
using namespace std;
using namespace cv;

namespace task1b
{

   extern Storage task1b(map<ImageID, map<string, Mat>> rotationTranslationDirectionInformation);

}

#endif