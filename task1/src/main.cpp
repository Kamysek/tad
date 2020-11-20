#include "math.h"
#include "global/enum.h"
#include "global/helper.h"
#include "input/readInput.h"
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <filesystem>
#include <opencv2/opencv.hpp>

using namespace global;
using namespace cv;
using std::string, std::map, std::pair, std::cout, std::endl, std::vector;

// Intrinsic camera positons
double f_x = 2960.37845;
double f_y = 2960.37845;
double c_x = 1841.68855;
double c_y = 1235.23369;

/*

Solution for task1

NOTE: 
Images are only loaded correct if the program is exectuted from /build/src! 
The values printed in the terminal from task1 are used to plot the camera positions. 
This is done using Matlab (see matlab/plot1a.m and matlab/plot1a.fig)

*/
map<ImageID, pair<Mat, Mat>> task1a()
{

    // Load 3D teabox coordinates, image location and provided 2D image coordinates
    map<TeaBoxCorner, Point3d> tb3DCoordinates = input::teabox3DCoordinates();
    map<ImageID, string> imgLocation = input::imageLocation();
    map<ImageID, map<TeaBoxCorner, Point2d>> img2DCoordinates = input::image2DCoordinates();
    map<ImageID, pair<Mat, Mat>> RotationMatrixAndTranslationVector;

    // Cycle through images
    for ( int iidInt = DSC_9743; iidInt != LASTIID; iidInt++ )
    {
        ImageID iid = static_cast<ImageID>(iidInt);
        cout << "Calculated Information for Image" + std::to_string(iid) << endl;

        // Load 2D coordinates for given image
        map<TeaBoxCorner, Point2d> img2DCords = img2DCoordinates[iid];
        if(img2DCoordinates.empty())
        {
            cout << "Could not load 2D coordinates of image: " + std::to_string(iid) << endl;
            throw "Could not load 2D coordinates of image: " + std::to_string(iid);
        }

        // Load image
        Mat img = imread(imgLocation[iid], IMREAD_COLOR);
        if(img.empty())
        {
            cout << "Could not load image " + std::to_string(iid) + " from path: " + std::filesystem::current_path().generic_string() << endl;
            throw "Could not load image " + std::to_string(iid) + " from path: " + std::filesystem::current_path().generic_string();
        }

        // Create two vector one containing the 3D teabox coordinates and the second the corresponding 2D image coordinates
        vector<Point2d> img2DVect;
        vector<Point3d> tbc3DVect;

        // Cycle through tea box corners
        for (int tbcInt = ZERO; tbcInt != LASTTBC; tbcInt++)
        {
            TeaBoxCorner tbc = static_cast<TeaBoxCorner>(tbcInt);
            
            // Get values for vector
            if (img2DCords.count(tbc) > 0) {
                img2DVect.push_back(img2DCords[tbc]);
                tbc3DVect.push_back(tb3DCoordinates[tbc]);
            }
        }

        // Prepare output Mat objects for solvePnP
        Mat rotationVect; 
        Mat translationVect;        

        // Input camera matrix
        Mat cameraMatrix = (cv::Mat_<double>(3,3) << f_x, 0, c_x, 0 , f_y, c_y, 0, 0, 1);

        // Dist coeffs
        Mat distCoeffs = cv::Mat::zeros(4,1,cv::DataType<double>::type); 

        // SolvePnP to get rotation vector and translation vector
        solvePnP(tbc3DVect, img2DVect, cameraMatrix, distCoeffs, rotationVect, translationVect);

        // Obtrain rotation matrix through rodrigues
        Mat rotationMatrix;
        Rodrigues(rotationVect, rotationMatrix);
        global::printMat("RotationMatrix", rotationMatrix);

        // Calculate camera position
        translationVect = -rotationMatrix.t() * translationVect;
        global::printMat("Camera Position",translationVect);
    
        // Calculate camera direction
        Mat vector = (Mat_<double>(3, 1) << 0, 0, 1);
        cout << vector.size << endl;
        rotationMatrix = rotationMatrix.t() * vector;
        global::printMat("Camera Direction", rotationMatrix);

        RotationMatrixAndTranslationVector.insert(pair(iid, pair(rotationMatrix, translationVect)));
    }
    return RotationMatrixAndTranslationVector;
}

/*

Solution for task1

NOTE: 
Images are only loaded correct if the program is exectuted from /build/src! 
The values printed in the terminal from task1 are used to plot the camera positions. 
This is done using Matlab (see matlab/plot1a.m and matlab/plot1a.fig)

*/

void task1b(){

    // Load 3D teabox coordinates, image location and provided 2D image coordinates
    map<TeaBoxCorner, Point3d> tb3DCoordinates = input::teabox3DCoordinates();
    map<ImageID, string> imgLocation = input::imageLocation();
    map<ImageID, map<TeaBoxCorner, Point2d>> img2DCoordinates = input::image2DCoordinates();
    
    // Cycle through images
    for ( int iidInt = DSC_9743; iidInt != LASTIID; iidInt++ )
    {
        ImageID iid = static_cast<ImageID>(iidInt);
        cout << "Calculated Information for Image" + std::to_string(iid) << endl;

        // Load 2D coordinates for given image
        map<TeaBoxCorner, Point2d> img2DCords = img2DCoordinates[iid];
        if(img2DCoordinates.empty())
        {
            cout << "Could not load 2D coordinates of image: " + std::to_string(iid) << endl;
            return;
        }

        // Map 2D points to 3D rays




        // Load image
        Mat img = imread(imgLocation[iid], IMREAD_GRAYSCALE);
        if(img.empty())
        {
            cout << "Could not load image " + std::to_string(iid) + "from path: " + std::filesystem::current_path().generic_string() << endl;
            return;
        }

        // Detect the keypoints using SIFT Detector
        Ptr<SIFT> detector = SIFT::create();
        std::vector<KeyPoint> keypoints;
        detector->detect(img, keypoints);
        
        // Draw keypoints on picture
        Mat output;
        drawKeypoints(img, keypoints, output);
        
        // Show detected keypoints
        imshow("Keypoints 1", output);
       
        waitKey(0);

    }
}

// Point3d convert2DPointTo3DRay(Point2d m){

//     // Calculate 

//     retunr 
// }

int main()
{

    cout << "Solution for task1 \n \n" 
            "NOTE: \n"
            "Images are only loaded correct if the program is exectuted from /build/src! \n"
            "The values printed in the terminal from task1 are used to plot the camera positions. \n"
            "This is done using Matlab (see matlab/plot1a.m and matlab/plot1a.fig) \n"
    << endl;

    map<ImageID, pair<Mat, Mat>> RotationAndTranslation = task1a();
    
    //task1b();

}