#include "../input/readInput.h"
#include "../utility/utility.h"
#include "customGeometry.h"
#include "math.h"
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
            vector<KeyPoint> keypointsNewImage;
            Mat descriptorsNewImage;
            detector->detectAndCompute(img, noArray(), keypointsNewImage, descriptorsNewImage);

            //-- Step 2: Matching descriptor vectors with a FLANN based matcher
            //Since SURF is a floating-point descriptor NORM_L2 is used
            Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create(DescriptorMatcher::FLANNBASED);
            std::vector< std::vector<DMatch> > knn_matches;
            matcher->knnMatch( descriptorsNewImage, storage.descriptors, knn_matches, 2 );
            //-- Filter matches using the Lowe's ratio test
            const float ratio_thresh = 0.7f;
            std::vector<DMatch> good_matches;
            for (size_t i = 0; i < knn_matches.size(); i++)
            {
                if (knn_matches[i][0].distance < ratio_thresh * knn_matches[i][1].distance)
                {
                    good_matches.push_back(knn_matches[i][0]);
                }
            }

            //BFMatcher matcher(NORM_L2, true);
            //Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create(DescriptorMatcher::FLANNBASED);
            //std::vector< std::vector<DMatch> > knn_matches;


            // vector containing all descriptors from training images
            vector<DMatch> matches;

            Mat newDescriptor;
            for (unsigned int i = 0; i < storage.descriptors.size(); ++i)
            {
                vconcat(storage.descriptors.at(i), newDescriptor);
            }

            newDescriptor.convertTo(newDescriptor, CV_32F);

            //matcher -> knnMatch(descriptorsNewImage, newDescriptor, knn_matches, 2);
            //matcher.match(descriptorsNewImage, newDescriptor, matches);

            // const int GOOD_PTS_MAX = 50;
            // const float GOOD_PORTION = 0.2f;

            // std::sort(matches.begin(), matches.end());
            // std::vector< DMatch > good_matches;
            // double minDist = matches.front().distance;
            // double maxDist = matches.back().distance;

            // const int ptsPairs = std::min(GOOD_PTS_MAX, (int)(matches.size() * GOOD_PORTION));
            // for( int i = 0; i < ptsPairs; i++ )
            // {
            //     good_matches.push_back( matches[i] );
            // }

            // const float ratio_thresh = 0.75f;
            // std::vector<DMatch> good_matches;
            // for (size_t i = 0; i < knn_matches.size(); i++)
            // {
            //     if (knn_matches[i][0].distance < ratio_thresh * knn_matches[i][1].distance)
            //     {
            //         good_matches.push_back(knn_matches[i][0]);
            //     }
            // }

            Mat img_matches;
            Mat im2 = imread("../../resources/init_texture/DSC_9743.JPG");
            drawMatches( img, keypointsNewImage, im2, storage.keypoints, good_matches, img_matches, Scalar::all(-1), Scalar::all(-1), std::vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );
            //-- Show detected matches
            imshow("Good Matches", img_matches );
            waitKey();

            // Find out 2D / 3D correspondences
            vector<Point3f> matches3Dmodel;
            vector<Point2f> matches2Dimage;
            for (unsigned int i = 0; i < good_matches.size(); ++i)
            {
                // vector containing all 3d intersection points from training images
                intersection::Vec3f vectorWith3DPoint = storage.intersectionPoints[good_matches[i].trainIdx];
                Point2f point2d = keypointsNewImage[good_matches[i].queryIdx].pt;
                matches3Dmodel.push_back(Point3f(vectorWith3DPoint.x, vectorWith3DPoint.y, vectorWith3DPoint.z));
                matches2Dimage.push_back(point2d);
            }

            // Prepare for solve pnp
            Mat distortionCoefficient = Mat::zeros(4, 1, CV_64FC1);
            Mat rotationVector = Mat::zeros(3, 1, CV_64FC1);
            Mat translationVector = Mat::zeros(3, 1, CV_64FC1);
            

            // How I calculated the optimal values
            // double error = 100000;
            // int finali;
            // int finalj;

            // // calculate lowest distance
            // for (unsigned int j = 10; j < 400; ++j)
            // {
            //     for (unsigned int i = 5; i < 100; ++i)
            //     {
            //         cout << j << endl;
            //         cout << i << endl;
            //         // solvePnPRansac(matches3Dmodel, matches2Dimage, intrinsicCameraMatrix, distortionCoefficient, rotationVector, translationVector, true, j, i, 0.99, noArray(), SOLVEPNP_P3P);

            //         // // Obtrain rotation matrix through rodrigues
            //         // Mat rotationMatrix;
            //         // Rodrigues(rotationVector, rotationMatrix);

            //         // // Get correct order of image points
            //         // vector<Point2d> imagePoints;
            //         // for (unsigned int i = 0; i < tbc3DVect.size(); ++i)
            //         // {
            //         //     vector<Point2d> outputPoint;
            //         //     vector<Point3d> inputPoint;
            //         //     inputPoint.push_back(tbc3DVect.at(i));

            //         //     // Project 3d teabox coordinates to 2d image coordinates
            //         //     projectPoints(inputPoint, rotationVector, translationVector, intrinsicCameraMatrix, distortionCoefficient, outputPoint);

            //         //     imagePoints.push_back(outputPoint.at(0));
            //         // }

            //         // cout << "ImagePoints" << endl;
            //         // cout << imagePoints << endl;

            //         // //Draw lines
            //         // line(img, imagePoints.at(0), imagePoints.at(1), Scalar(255, 0, 0), 3);
            //         // line(img, imagePoints.at(0), imagePoints.at(3), Scalar(255, 0, 0), 3);
            //         // line(img, imagePoints.at(0), imagePoints.at(4), Scalar(255, 0, 0), 3);

            //         // line(img, imagePoints.at(1), imagePoints.at(2), Scalar(255, 0, 0), 3);
            //         // line(img, imagePoints.at(1), imagePoints.at(5), Scalar(255, 0, 0), 3);

            //         // line(img, imagePoints.at(2), imagePoints.at(3), Scalar(255, 0, 0), 3);
            //         // line(img, imagePoints.at(2), imagePoints.at(6), Scalar(255, 0, 0), 3);

            //         // line(img, imagePoints.at(3), imagePoints.at(7), Scalar(255, 0, 0), 3);

            //         // line(img, imagePoints.at(4), imagePoints.at(5), Scalar(255, 0, 0), 3);
            //         // line(img, imagePoints.at(4), imagePoints.at(7), Scalar(255, 0, 0), 3);

            //         // line(img, imagePoints.at(5), imagePoints.at(6), Scalar(255, 0, 0), 3);

            //         // line(img, imagePoints.at(6), imagePoints.at(7), Scalar(255, 0, 0), 3);

            //         // imshow("Show corners", img);

            //         // waitKey();
                    
            //         solvePnPRansac(matches3Dmodel, matches2Dimage, intrinsicCameraMatrix, distortionCoefficient, rotationVector, translationVector, true, j, i, 0.99, noArray(), SOLVEPNP_P3P);

            //         // Obtrain rotation matrix through rodrigues
            //         Mat rotationMatrix;
            //         Rodrigues(rotationVector, rotationMatrix);

            //         // Get correct order of image points
            //         vector<Point2d> imagePoints;
            //         for (unsigned int i = 0; i < tbc3DVect.size(); ++i)
            //         {
            //             vector<Point2d> outputPoint;
            //             vector<Point3d> inputPoint;
            //             inputPoint.push_back(tbc3DVect.at(i));

            //             // Project 3d teabox coordinates to 2d image coordinates
            //             projectPoints(inputPoint, rotationVector, translationVector, intrinsicCameraMatrix, distortionCoefficient, outputPoint);

            //             imagePoints.push_back(outputPoint.at(0));
            //         }

            //         // calculate error
            //         double tmpError = sqrt( pow(abs(1484.0 - imagePoints.at(0).x) + abs(1015.0 - imagePoints.at(0).y), 2) +
            //                     pow(abs(2239.0 - imagePoints.at(1).x) + abs(1154.0 - imagePoints.at(1).y), 2) +
            //                     pow(abs(2132.0 - imagePoints.at(2).x) + abs(1264.0 - imagePoints.at(2).y), 2) +
            //                     pow(abs(1333.0 - imagePoints.at(3).x) + abs(1104.0 - imagePoints.at(3).y), 2) +
            //                     pow(abs(2211.0 - imagePoints.at(5).x) + abs(1555.0 - imagePoints.at(5).y), 2) +
            //                     pow(abs(2105.0 - imagePoints.at(6).x) + abs(1718.0 - imagePoints.at(6).y), 2) +
            //                     pow(abs(1347.0 - imagePoints.at(7).x) + abs(1520.0 - imagePoints.at(7).y), 2));

            //         if (tmpError < error){
            //             error = tmpError;
            //             finali = i;
            //             finalj = j;
            //         }
            //     }
            // }
     
            // cout << finalj << endl;
            // cout << finali << endl;
            solvePnPRansac(matches3Dmodel, matches2Dimage, intrinsicCameraMatrix, distortionCoefficient, rotationVector, translationVector, true, 67, 10, 0.99, noArray(), SOLVEPNP_P3P);

            // Obtrain rotation matrix through rodrigues
            Mat rotationMatrix;
            Rodrigues(rotationVector, rotationMatrix);

            // Get correct order of image points
            vector<Point2d> imagePoints;
            for (unsigned int i = 0; i < tbc3DVect.size(); ++i)
            {
                vector<Point2d> outputPoint;
                vector<Point3d> inputPoint;
                inputPoint.push_back(tbc3DVect.at(i));

                // Project 3d teabox coordinates to 2d image coordinates
                projectPoints(inputPoint, rotationVector, translationVector, intrinsicCameraMatrix, distortionCoefficient, outputPoint);

                imagePoints.push_back(outputPoint.at(0));
            }

            cout << "ImagePoints" << endl;
            cout << imagePoints << endl;

            //Draw lines
            line(img, imagePoints.at(0), imagePoints.at(1), Scalar(255, 0, 0), 3);
            line(img, imagePoints.at(0), imagePoints.at(3), Scalar(255, 0, 0), 3);
            line(img, imagePoints.at(0), imagePoints.at(4), Scalar(255, 0, 0), 3);

            line(img, imagePoints.at(1), imagePoints.at(2), Scalar(255, 0, 0), 3);
            line(img, imagePoints.at(1), imagePoints.at(5), Scalar(255, 0, 0), 3);

            line(img, imagePoints.at(2), imagePoints.at(3), Scalar(255, 0, 0), 3);
            line(img, imagePoints.at(2), imagePoints.at(6), Scalar(255, 0, 0), 3);

            line(img, imagePoints.at(3), imagePoints.at(7), Scalar(255, 0, 0), 3);

            line(img, imagePoints.at(4), imagePoints.at(5), Scalar(255, 0, 0), 3);
            line(img, imagePoints.at(4), imagePoints.at(7), Scalar(255, 0, 0), 3);

            line(img, imagePoints.at(5), imagePoints.at(6), Scalar(255, 0, 0), 3);

            line(img, imagePoints.at(6), imagePoints.at(7), Scalar(255, 0, 0), 3);

            imshow("Show corners", img);

            waitKey();
        }
    }
} // namespace task2