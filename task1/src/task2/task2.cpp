#include "../input/readInput.h"
#include "math.h"
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
using namespace intersection;
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

        // Put teabox points into vector
        vector<Point3d> tbc3DVect;
        for (int tbcInt = ZERO; tbcInt != LASTTBC; tbcInt++)
        {
            TeaBoxCorner tbc = static_cast<TeaBoxCorner>(tbcInt);

            tbc3DVect.push_back(tb3DCoordinates[tbc]);
        }

        // Cycle through images
        for (int iidInt = DSC_9751; iidInt != LASTIIDTASK2; iidInt++)
        {
            ImageIDTask2 iid = static_cast<ImageIDTask2>(iidInt);
            cout << "Calculate information for image" + to_string(iid) << endl;

            // Load image
            Mat img = imread(imgLocation[iid], IMREAD_COLOR);
            if (img.empty())
            {
                cout << "Could not load image " + to_string(iid) + " from path: " + current_path().generic_string() << endl;
                throw "Could not load image " + to_string(iid) + " from path: " + current_path().generic_string();
            }

            // Extract keypoints and descriptors of "new image" using SIFT Detector
            Ptr<SIFT> detector = SIFT::create();
            vector<KeyPoint> keypoints;
            Mat descriptors;
            detector->detectAndCompute(img, noArray(), keypoints, descriptors);

            // Setup descriptor matcher
            Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create(DescriptorMatcher::BRUTEFORCE);

            matcher->add(storage.descriptors);
            matcher->train();

            // match new descriptors with descriptors from original images
            vector<DMatch> matches;
            matcher->match(descriptors, matches);

            // Find out 2D / 3D correspondences
            vector<Point3f> matches3Dmodel;
            vector<Point2f> matches2Dimage;
            for (unsigned int i = 0; i < matches.size(); ++i)
            {
                intersection::Vec3f vectorWith3DPoint = storage.intersectionPoints[matches[i].trainIdx];
                //Point3f point3d intersection:: = storage.intersectionPoints[matches[i].trainIdx];
                Point2f point2d = keypoints[matches[i].queryIdx].pt;
                matches3Dmodel.push_back(Point3f(vectorWith3DPoint.x, vectorWith3DPoint.y, vectorWith3DPoint.z));
                matches2Dimage.push_back(point2d);
            }

            // // Draw matches
            // Mat drawImg;
            // Mat loadimage = imread("../../resources/init_texture/DSC_9743.JPG");
            // drawMatches(img, keypoints, loadimage, storage.keypoints, matches, drawImg);
            // imshow("Show corners", drawImg);

            // waitKey(0);

            // Prepare for solve pnp
            Mat distortionCoefficient = Mat::zeros(4, 1, CV_64FC1);
            Mat rotationVector = Mat::zeros(3, 1, CV_64FC1);
            Mat translationVector = Mat::zeros(3, 1, CV_64FC1);

            double error = 1000000;
            int finali;
            int finalj;

            // calculate lowest distance
            // for (unsigned int j = 10; j < 200; ++j)
            // {
            //     for (unsigned int i = 5; i < 150; ++i)
            //     { 
            //         solvePnPRansac(matches3Dmodel, matches2Dimage, intrinsicCameraMatrix, distortionCoefficient, rotationVector, translationVector, false, j, i);

            //         // Obtrain rotation matrix through rodrigues
            //         Mat rotationMatrix;
            //         Rodrigues(rotationVector, rotationMatrix);

            //         printMat("RotationVector", rotationVector);

            //         printMat("RotationMatrix", rotationMatrix);

            //         // Calculate camera position
            //         //translationVector = -rotationMatrix.t() * translationVector;
            //         printMat("TranslationVector", translationVector);

            //         vector<Point2d> imagePoints;
            //         for (unsigned int i = 0; i < tbc3DVect.size(); ++i)
            //         {    
            //             vector<Point2d> outputPoint;
            //             vector<Point3d> inputPoint; 
            //             inputPoint.push_back(tbc3DVect.at(i));

            //             projectPoints(inputPoint, rotationVector, translationVector, intrinsicCameraMatrix, distortionCoefficient, outputPoint);

            //             imagePoints.push_back(outputPoint.at(0));
            //         }

            //         // calculate error
            //         double tmpError = sqrt( pow(abs(1484.0 - imagePoints.at(0).x) + abs(1015.0 - imagePoints.at(0).y), 2) + 
            //                     pow(abs(2239.0 - imagePoints.at(1).x) + abs(1154.0 - imagePoints.at(1).y), 2) +
            //                     pow(abs(2132.0 - imagePoints.at(2).x) + abs(1264.0 - imagePoints.at(2).y), 2) +
            //                     pow(abs(1333.0 - imagePoints.at(3).x) + abs(1104.0 - imagePoints.at(3).y), 2) );

            //         if (tmpError < error){
            //             error = tmpError;
            //             finali = i;
            //             finalj = j;
            //         }
            //     }
            // }

            solvePnPRansac(matches3Dmodel, matches2Dimage, intrinsicCameraMatrix, distortionCoefficient, rotationVector, translationVector, false, 68, 0.5);

            // Obtrain rotation matrix through rodrigues
            Mat rotationMatrix;
            Rodrigues(rotationVector, rotationMatrix);

            printMat("RotationVector", rotationVector);

            printMat("RotationMatrix", rotationMatrix);

            // Calculate camera position
            translationVector = -rotationMatrix.t() * translationVector;
            printMat("TranslationVector", translationVector);

            vector<Point2d> imagePoints;
            for (unsigned int i = 0; i < tbc3DVect.size(); ++i)
            {    
                vector<Point2d> outputPoint;
                vector<Point3d> inputPoint; 
                inputPoint.push_back(tbc3DVect.at(i));

                projectPoints(inputPoint, rotationVector, translationVector, intrinsicCameraMatrix, distortionCoefficient, outputPoint);

                imagePoints.push_back(outputPoint.at(0));
            }

            cout << "ImagePoints" << endl;
            cout << imagePoints << endl;

            line(img, imagePoints.at(0), imagePoints.at(1), Scalar( 255, 0, 0 ), 3);
            line(img, imagePoints.at(0), imagePoints.at(3), Scalar( 255, 0, 0 ), 3);
            line(img, imagePoints.at(0), imagePoints.at(4), Scalar( 255, 0, 0 ), 3);

            line(img, imagePoints.at(1), imagePoints.at(2), Scalar( 255, 0, 0 ), 3);
            line(img, imagePoints.at(1), imagePoints.at(5), Scalar( 255, 0, 0 ), 3);

            line(img, imagePoints.at(2), imagePoints.at(3), Scalar( 255, 0, 0 ), 3);
            line(img, imagePoints.at(2), imagePoints.at(6), Scalar( 255, 0, 0 ), 3);

            line(img, imagePoints.at(3), imagePoints.at(7), Scalar( 255, 0, 0 ), 3);

            line(img, imagePoints.at(4), imagePoints.at(5), Scalar( 255, 0, 0 ), 3);
            line(img, imagePoints.at(4), imagePoints.at(7), Scalar( 255, 0, 0 ), 3);

            line(img, imagePoints.at(5), imagePoints.at(6), Scalar( 255, 0, 0 ), 3);

            line(img, imagePoints.at(6), imagePoints.at(7), Scalar (255, 0, 0 ), 3);

            imshow("Show corners", img);

            waitKey(0);
        }
    }
} // namespace task2