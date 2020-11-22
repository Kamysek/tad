#include "utility/utility.h"
#include "task1a/task1a.h"
#include "task1b/task1b.h"
#include <map>
#include <string>
#include <opencv2/opencv.hpp>

using namespace utility;
using namespace cv;
using std::string, std::map, std::cout, std::endl;

int main()
{

    cout << "Solution for task1a \n \n" 
            "NOTE: \n"
            "Images are only loaded correct if the program is exectuted from /build/src! \n"
    << endl;

    map<ImageID, map<string, Mat>> RotationAndTranslation = task1a::task1a();
    
    cout << "Solution for task1b \n \n" 
            "NOTE: \n"
            "Images are only loaded correct if the program is exectuted from /build/src! \n"
    << endl;

    task1b::task1b(RotationAndTranslation);

}