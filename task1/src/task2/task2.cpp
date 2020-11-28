#include "../input/readInput.h"
#include "../utility/utility.h"
#include "customGeometry.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <opencv2/opencv.hpp>
#include <string>
#include <vector>

using namespace utility;
using namespace input;
using namespace cv;
using std::string, std::map, std::pair, std::cout, std::endl, std::vector, std::filesystem::current_path, std::to_string;

namespace task2
{

     Mat intrinsicCameraMatrix = (Mat_<double>(3, 3) << 2960.37845, 0, 1841.68855, 0, 2960.37845, 1235.23369, 0, 0, 1);

    void task2(Storage storage)
    {
        // Load image locations
        map<ImageIDTask2, string> imgLocation = imageLocationTask2();
        // Load locations where images should be written
        map<ImageIDTask2, string> imgWriteLocation = imageWriteLocationTask2();
        // Load teabox 3D coordinates
        map<TeaBoxCorner, Point3d> tb3DCoordinates = teabox3DCoordinates();

        // Setup descriptor matcher
        Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create(DescriptorMatcher::BRUTEFORCE);

        matcher->add(storage.descriptors);
        matcher->train();

        // Cycle through images
        for (int iidInt = DSC_9751; iidInt != LASTIIDTASK2; iidInt++)
        {
            ImageIDTask2 iid = static_cast<ImageIDTask2>(iidInt);
            cout << "Calculate information for image" + to_string(iid) << endl;

            // Load image
            Mat img = imread(imgLocation[iid], IMREAD_GRAYSCALE);
            if (img.empty())
            {
                cout << "Could not load image " + to_string(iid) + " from path: " + current_path().generic_string() << endl;
                throw "Could not load image " + to_string(iid) + " from path: " + current_path().generic_string();
            }

            // Detect the keypoints of "new image" using SIFT Detector
            Ptr<SIFT> detector = SIFT::create();
            vector<KeyPoint> keypoints;
            Mat descriptors;
            detector->detectAndCompute(img, noArray(), keypoints, descriptors);

            vector<DMatch> matches;
            matcher->match(descriptors, matches);

            // Put teabox points into vector
            vector<Point3d> tbc3DVect;

            // Cycle through tea box corners
            for (int tbcInt = ZERO; tbcInt != LASTTBC; tbcInt++)
            {
                TeaBoxCorner tbc = static_cast<TeaBoxCorner>(tbcInt);

                tbc3DVect.push_back(tb3DCoordinates[tbc]);                
            }

            // Find out 2D / 3D correspondences
            vector<Point3f> list_points3d_model_match;    // container for the model 3D coordinates found in the scene
            vector<Point2f> list_points2d_scene_match;    // container for the model 2D coordinates found in the scene
            for(unsigned int match_index = 0; match_index < matches.size(); ++match_index)
            {
                Point3f point3d_model = tbc3DVect[ matches[match_index].trainIdx ];   // 3D point from model
                Point2f point2d_scene = keypoints[ matches[match_index].queryIdx ].pt;    // 2D point from the scene
                list_points3d_model_match.push_back(point3d_model);                                      // add 3D point
                list_points2d_scene_match.push_back(point2d_scene);                                      // add 2D point
            }

            Mat distCoeffs = Mat::zeros(4, 1, CV_64FC1);  // vector of distortion coefficients
            Mat rvec = Mat::zeros(3, 1, CV_64FC1);        // output rotation vector
            Mat tvec = Mat::zeros(3, 1, CV_64FC1);    // output translation vector

            bool useExtrinsicGuess = false;   // if true the function uses the provided rvec and tvec values as
            // initial approximations of the rotation and translation vectors

            solvePnPRansac(list_points3d_model_match, list_points2d_scene_match, intrinsicCameraMatrix, distCoeffs, rvec, tvec, useExtrinsicGuess, 100, 5);

            // Obtrain rotation matrix through rodrigues
            Mat rotationMatrix;
            Rodrigues(rvec, rotationMatrix);

            cout << rvec << endl;

            printMat("Rotation", rotationMatrix);

            cout << tvec << endl;

            //Calculate camera position
            tvec = -rotationMatrix.t() * tvec;
            vector<Point2d> outputPoints;
            projectPoints(tbc3DVect, rvec, tvec, intrinsicCameraMatrix, distCoeffs, outputPoints);

            cout << outputPoints << endl;


           
            // Draw matches
            // Mat img_matches;
            // Mat test = imread("../../resources/init_texture/DSC_9743.JPG");
            // drawMatches(img, keypoints, test, storage.keypoints, matches, img_matches);
            // // Show detected matches
            // imshow("Matches", img_matches);

            //waitKey(0);
        }
    }
} // namespace task2