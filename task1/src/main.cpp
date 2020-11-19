#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <opencv2/opencv.hpp>
#include "global/enum.h"
#include "input/readInput.h"
#include <stdio.h>
#include <stdlib.h>
#include <filesystem>

using namespace global;
using namespace cv;
using std::string, std::map, std::pair, std::cout, std::endl, std::vector;

void printMat(string input, Mat image)
{
     cout << input + " = " << endl << format(image, Formatter::FMT_CSV) << endl << endl;
}

int main()
{
    // Intrinsic camera positons
    double f_x = 2960.37845;
    double f_y = 2960.37845;
    double c_x = 1841.68855;
    double c_y = 1235.23369;

    // Load 3D teabox coordinates, image location and provided 2D image coordinates
    map<TeaBoxCorner, Point3d> tb3DCoordinates = input::teabox3DCoordinates();
    map<ImageID, string> imgLocation = input::imageLocation();
    map<ImageID, map<TeaBoxCorner, Point2d>> img2DCoordinates = input::image2DCoordinates();
    
    // Cycle through images
    for ( int iidInt = DSC_9743; iidInt != LASTIID; iidInt++ )
    {
        ImageID iid = static_cast<ImageID>(iidInt);

        map<TeaBoxCorner, Point2d> img2DCords = img2DCoordinates[iid];
        
        // Not possible to load 2D coordinates
        if(img2DCoordinates.empty())
        {
            cout << "Could not load 2D coordinates of image!" << endl;
            return 1;
        }

        // Load image
        Mat img = imread(imgLocation[iid], IMREAD_COLOR);

        // Not possible to load image
        if(img.empty())
        {
            cout << std::filesystem::current_path() << endl;
            return 1;
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

        cout << "Img2DVector  = " << endl << format(img2DVect, Formatter::FMT_NUMPY) << endl << endl;
        cout << "Img3DVector  = " << endl << format(tbc3DVect, Formatter::FMT_NUMPY) << endl << endl;

        // Output vector
        Mat rotationVect; 
        Mat translationVect;        

        // Input camera matrix
        Mat cameraMatrix = (cv::Mat_<double>(3,3) << f_x, 0, c_x, 0 , f_y, c_y, 0, 0, 1);
        printMat("CameraMatrix", cameraMatrix);

        Mat distCoeffs = cv::Mat::zeros(4,1,cv::DataType<double>::type); 
        printMat("DistCoeffs", distCoeffs);

        // SolvePnP to get rotation vector and translation vector
        solvePnP(tbc3DVect, img2DVect, cameraMatrix, distCoeffs, rotationVect, translationVect);

        // Obtrain rotation matrix through rodrigues
        Mat rotationMatrix;
        Rodrigues(rotationVect, rotationMatrix);
        printMat("RotationMatrix", rotationMatrix);

        // Transpose rotation matrix
        rotationMatrix = rotationMatrix.t();
        printMat("TransposedRotationMatrix", rotationMatrix);

        // Calculate camera position
        translationVect = -rotationMatrix * translationVect;
        printMat("TranslationVector",translationVect);
    }
}