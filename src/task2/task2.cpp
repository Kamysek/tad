#include "../input/readInput.h"
#include "../intersection/customGeometry.h"
#include "../utility/utility.h"
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

        // Store information for task3
        Storage2 storage2;

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

            // Extract keypoints and descriptors of image using SIFT Detector
            Ptr<SIFT> detector = SIFT::create();
            vector<KeyPoint> keypointsNewImage;
            Mat descriptorsNewImage;
            detector->detectAndCompute(img, noArray(), keypointsNewImage, descriptorsNewImage);

            // Create Matcher
            Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create(DescriptorMatcher::FLANNBASED);

            // Find two best matching image
            Mat bestDescriptorsImage1;
            vector<KeyPoint> bestKeypointsImage1;
            vector<intersection::Vec3f> bestIntersectionPointsImage1;

            Mat bestDescriptorsImage2;
            vector<KeyPoint> bestKeypointsImage2;
            vector<intersection::Vec3f> bestIntersectionPointsImage2;

            double distance = INFINITY;
            for (int iidInt2 = DSC_9743; iidInt2 != LASTIID; iidInt2++)
            {
                ImageID iid2 = static_cast<ImageID>(iidInt2);

                // Load keypoints, descriptors and intersections of current image
                vector<KeyPoint> tmpKeypoints = storage.keypoints[iid2];
                Mat tmpDescriptors = storage.descriptors[iid2];
                vector<intersection::Vec3f> tmpIntersectionPoints = storage.intersectionPoints[iid2];

                // Perform matching
                vector<vector<DMatch>> knn_matches;
                matcher->knnMatch(descriptorsNewImage, tmpDescriptors, knn_matches, 2);

                // Apply lowe ratio test
                const float ratio_thresh = 0.80f;
                std::vector<DMatch> good_matches;
                for (size_t i = 0; i < knn_matches.size(); i++)
                {
                    if (knn_matches[i][0].distance < ratio_thresh * knn_matches[i][1].distance)
                    {
                        good_matches.push_back(knn_matches[i][0]);
                    }
                }

                // Calculate media to select best fitting images
                double median;
                size_t size = good_matches.size();

                sort(good_matches.begin(), good_matches.end());
                if (size % 2 == 0)
                {
                    median = (good_matches[size / 2 - 1].distance + good_matches[size / 2].distance) / 2;
                }
                else
                {
                    median = good_matches[size / 2].distance;
                }

                if (median < distance)
                {
                    // Update information
                    distance = median;
                    bestDescriptorsImage1 = tmpDescriptors;
                    bestKeypointsImage1 = tmpKeypoints;
                    bestIntersectionPointsImage1 = tmpIntersectionPoints;
                    bestDescriptorsImage2 = bestDescriptorsImage1;
                    bestKeypointsImage1 = bestKeypointsImage1;
                    bestIntersectionPointsImage2 = bestIntersectionPointsImage1;
                }
            }

            // Combine best matching pictures
            Mat allD;
            vector<KeyPoint> allK;
            vector<intersection::Vec3f> allInt;
            vconcat(bestDescriptorsImage1, allD);
            vconcat(bestDescriptorsImage2, allD);
            allK.insert(allK.end(), bestKeypointsImage1.begin(), bestKeypointsImage1.end());
            allK.insert(allK.end(), bestKeypointsImage2.begin(), bestKeypointsImage2.end());
            allInt.insert(allInt.end(), bestIntersectionPointsImage1.begin(), bestIntersectionPointsImage1.end());
            allInt.insert(allInt.end(), bestIntersectionPointsImage2.begin(), bestIntersectionPointsImage2.end());

            // Perform matching for two best matching images
            vector<vector<DMatch>> knn_matches;
            matcher->knnMatch(descriptorsNewImage, allD, knn_matches, 2);

            // Apply lowe ratio test
            const float ratio_thresh = 0.80f;
            std::vector<DMatch> good_matches;
            for (size_t i = 0; i < knn_matches.size(); i++)
            {
                if (knn_matches[i][0].distance < ratio_thresh * knn_matches[i][1].distance)
                {
                    good_matches.push_back(knn_matches[i][0]);
                }
            }

            // Find out 2D / 3D correspondences
            vector<Point3f> matches3Dmodel;
            vector<Point2f> matches2Dimage;
            for (unsigned int i = 0; i < good_matches.size(); ++i)
            {
                // vector containing all 3d intersection points from training images
                intersection::Vec3f vectorWith3DPoint = allInt[good_matches[i].trainIdx];
                Point2f point2d = keypointsNewImage[good_matches[i].queryIdx].pt;
                matches3Dmodel.push_back(Point3f(vectorWith3DPoint.x, vectorWith3DPoint.y, vectorWith3DPoint.z));
                matches2Dimage.push_back(point2d);
            }

            // Prepare for solve pnp ransac
            Mat distortionCoefficient = Mat::zeros(4, 1, CV_64FC1);
            Mat rotationVector = Mat::zeros(3, 1, CV_64FC1);
            Mat translationVector = Mat::zeros(3, 1, CV_64FC1);

            solvePnPRansac(matches3Dmodel, matches2Dimage, intrinsicCameraMatrix, distortionCoefficient, rotationVector, translationVector, true, 59, 25, 0.99, noArray(), SOLVEPNP_P3P);

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

            imwrite(imgWriteLocation[iid], img);
        }

    }
} // namespace task2

// How I searched for good ransac parameters

// double error = INFINITY;
// int finali;
// int finalj;
// vector<pair<int,int>> nums;
// //calculate lowest distance
// for (unsigned int i = 20; i < 200; ++i)
// {
//     for (unsigned int j = 6; j < 100; ++j)
//     {
//         solvePnPRansac(matches3Dmodel, matches2Dimage, intrinsicCameraMatrix, distortionCoefficient, rotationVector, translationVector, true, i, j, 0.99, noArray(), SOLVEPNP_P3P);

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

//         // // 51
//         // double tmpError = sqrt( pow(abs(1492.0 - imagePoints.at(0).x) + abs(1011.0 - imagePoints.at(0).y), 2) +
//         //                         pow(abs(2235.0 - imagePoints.at(1).x) + abs(1147.0 - imagePoints.at(1).y), 2) +
//         //                         pow(abs(2135.0 - imagePoints.at(2).x) + abs(1261.0 - imagePoints.at(2).y), 2) +
//         //                         pow(abs(1330.0 - imagePoints.at(3).x) + abs(1106.0 - imagePoints.at(3).y), 2) +
//         //                         pow(abs(2204.0 - imagePoints.at(5).x) + abs(1560.0 - imagePoints.at(5).y), 2) +
//         //                         pow(abs(2102.0 - imagePoints.at(6).x) + abs(1714.0 - imagePoints.at(6).y), 2) +
//         //                         pow(abs(1344.0 - imagePoints.at(7).x) + abs(1520.0 - imagePoints.at(7).y), 2));

//         // //74
//         // double tmpError = sqrt( pow(abs(2204.0 - imagePoints.at(0).x) + abs(1154.0 - imagePoints.at(0).y), 2) +
//         //                         pow(abs(1810.0 - imagePoints.at(1).x) + abs(964.0 - imagePoints.at(1).y), 2) +
//         //                         pow(abs(1487.0 - imagePoints.at(2).x) + abs(879.0 - imagePoints.at(2).y), 2) +
//         //                         pow(abs(1944.0 - imagePoints.at(3).x) + abs(656.0 - imagePoints.at(3).y), 2) +
//         //                         pow(abs(1797.0 - imagePoints.at(5).x) + abs(1450.0 - imagePoints.at(5).y), 2) +
//         //                         pow(abs(1496.0 - imagePoints.at(6).x) + abs(1362.0 - imagePoints.at(6).y), 2));

//          //70
//         // double tmpError = sqrt( pow(abs(1099.0 - imagePoints.at(0).x) + abs(1089.0 - imagePoints.at(0).y), 2) +
//         //                         pow(abs(1769.0 - imagePoints.at(1).x) + abs(1001.0 - imagePoints.at(1).y), 2) +
//         //                         pow(abs(1830.0 - imagePoints.at(2).x) + abs(1161.0 - imagePoints.at(2).y), 2) +
//         //                         pow(abs(1118.0 - imagePoints.at(3).x) + abs(1262.0 - imagePoints.at(3).y), 2) +
//         //                         pow(abs(1819.0 - imagePoints.at(6).x) + abs(1431.0 - imagePoints.at(6).y), 2) +
//         //                         pow(abs(1169.0 - imagePoints.at(7).x) + abs(1535.0 - imagePoints.at(7).y), 2));
//         // // 69
//         // double tmpError = sqrt( pow(abs(1265.0 - imagePoints.at(0).x) + abs(879.0 - imagePoints.at(0).y), 2) +
//         //                         pow(abs(1901.0 - imagePoints.at(1).x) + abs(1020.0 - imagePoints.at(1).y), 2) +
//         //                         pow(abs(1841.0 - imagePoints.at(2).x) + abs(1156.0 - imagePoints.at(2).y), 2) +
//         //                         pow(abs(1159.0 - imagePoints.at(3).x) + abs(1002.0 - imagePoints.at(3).y), 2) +
//         //                         pow(abs(1868.0 - imagePoints.at(5).x) + abs(1297.0 - imagePoints.at(5).y), 2) +
//         //                         pow(abs(1864.0 - imagePoints.at(6).x) + abs(1468.0 - imagePoints.at(6).y), 2) +
//         //                         pow(abs(1174.0 - imagePoints.at(7).x) + abs(1312.0 - imagePoints.at(7).y), 2));

//         // 67
//         // double tmpError = sqrt( pow(abs(2303.0 - imagePoints.at(1).x) + abs(1305.0 - imagePoints.at(1).y), 2) +
//         //                         pow(abs(2115.0 - imagePoints.at(2).x) + abs(1308.0 - imagePoints.at(2).y), 2) +
//         //                         pow(abs(1391.0 - imagePoints.at(3).x) + abs(1281.0 - imagePoints.at(3).y), 2) +
//         //                         pow(abs(2294.0 - imagePoints.at(5).x) + abs(1824.0 - imagePoints.at(5).y), 2) +
//         //                         pow(abs(2103.0 - imagePoints.at(6).x) + abs(1887.0 - imagePoints.at(6).y), 2) +
//         //                         pow(abs(1385.0 - imagePoints.at(7).x) + abs(1758.0 - imagePoints.at(7).y), 2));

//         // 71
//         double tmpError = sqrt( pow(abs(1233.0 - imagePoints.at(0).x) + abs(1208.0 - imagePoints.at(0).y), 2) +
//                                 pow(abs(1715.0 - imagePoints.at(1).x) + abs(940.0 - imagePoints.at(1).y), 2) +
//                                 pow(abs(1884.0 - imagePoints.at(2).x) + abs(1048.0 - imagePoints.at(2).y), 2) +
//                                 pow(abs(1400.0 - imagePoints.at(3).x) + abs(1345.0 - imagePoints.at(3).y), 2) +
//                                 pow(abs(1856.0 - imagePoints.at(6).x) + abs(1300.0 - imagePoints.at(6).y), 2) +
//                                 pow(abs(1408.0 - imagePoints.at(7).x) + abs(1598.0 - imagePoints.at(7).y), 2) +
//                                 pow(abs(1253.0 - imagePoints.at(4).x) + abs(1457.0 - imagePoints.at(4).y), 2));

//         if (tmpError < error){
//             error = tmpError;
//             finali = i;
//             finalj = j;

//             nums.push_back(pair(i, j));
//         }
//     }
// }

// cout << "best values" << endl;
// cout << finali << endl;
// cout << finalj << endl;