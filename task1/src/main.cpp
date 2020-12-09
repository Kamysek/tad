#include "task1a/task1a.h"
#include "task1b/task1b.h"
#include "task2/task2.h"
#include "task21/task21.h"
#include "task3/task3.h"
#include <opencv2/opencv.hpp>
#include <string>

using namespace utility;
using namespace cv;
using std::string, std::map, std::cout, std::endl;

int main()
{
        // Images are only loaded correct if the program is exectuted from /build/src!
        // Make sure that the folders where the images are stored to exist!

        // Solution for task3
        // Uncomment it to run it!
        // Images must be stored in the cooresponding folder otherwise the program will not run! 
        // Store the images of the detection data set in resources/detection, 
        // the images from the init_texture in resources/init_texture and the tracking images in resources/tracking
    

        map<ImageID, map<string, Mat>> RotationAndTranslation = task1a::task1a();
        Storage keypointsDescriptorsAndIntersection = task1b::task1b(RotationAndTranslation);
        task2::task2(keypointsDescriptorsAndIntersection);

        // Solution for task3
        // Uncomment it to run it!
        // Images must be stored in the cooresponding folder otherwise the program will not run! 
        // Store the images of the detection data set in resources/detection, 
        // the images from the init_texture in resources/init_texture and the tracking images in resources/tracking
        
        pair<Mat, Mat> rotationTranslation = task21::task21(keypointsDescriptorsAndIntersection);
        task3::task3(rotationTranslation);
}