#include "../input/readInput.h"
#include "../utility/utility.h"
#include "customGeometry.h"
#include "math.h"
#include "raybox.h"
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

namespace task1b
{

    Mat intrinsicCameraMatrix = (Mat_<double>(3, 3) << 2960.37845, 0, 1841.68855, 0, 2960.37845, 1235.23369, 0, 0, 1);

    pair<intersection::Vec3f, intersection::Vec3f> convert2DPointTo3DRay(map<string, Mat> rotationTranslationDirection, Point2d m)
    {
        // extract rotation matrix and camera position
        Mat rotationMatrix = rotationTranslationDirection["rotation"];
        Mat cameraPosition = rotationTranslationDirection["translation"];

        // Create homogeneous point
        Mat homogeneousPoint = (Mat_<double>(3, 1) << m.x, m.y, 1);

        // Get world coordinates
        homogeneousPoint = (intrinsicCameraMatrix * rotationMatrix).inv() * homogeneousPoint;

        // Add camera origin and direction
        intersection::Vec3f origin = intersection::Vec3f(cameraPosition.at<double>(0, 0), cameraPosition.at<double>(0, 1), cameraPosition.at<double>(0, 2));
        intersection::Vec3f direction = intersection::Vec3f(homogeneousPoint.at<double>(0, 0), homogeneousPoint.at<double>(0, 1), homogeneousPoint.at<double>(0, 2));

        return pair(origin, direction);
    }

    Storage task1b(map<ImageID, map<string, Mat>> rotationTranslationDirectionInformation)
    {

        // Load teabox 3D coordinates
        map<TeaBoxCorner, Point3d> tb3DCoordinates = teabox3DCoordinates();

        // Load image locations
        map<ImageID, string> imgLocation = imageLocation();

        // Load locations where images should be written
        map<ImageID, string> imgWriteLocation = imageWriteLocation();

        // Load locations where matlab code gets stored
        map<ImageID, string> writeMatlabLocationTask1b = matlabWriteLocationTask1b();

        // store all siftkey points
        map<ImageID, vector<KeyPoint>> allKeypoints;

        // store all descriptors
        map<ImageID, Mat> allDescriptors;

        // store all 3d model points
        map<ImageID, vector<intersection::Vec3f>> all3DModelPoints;

        // Cycle through images
        for (int iidInt = DSC_9743; iidInt != LASTIID; iidInt++)
        {
            ImageID iid = static_cast<ImageID>(iidInt);
            cout << "Calculate information for image" + to_string(iid) << endl;

            // Extract rotation position translation information
            map<string, Mat> rotationTranslationDirection = rotationTranslationDirectionInformation[iid];

            // Load image
            Mat img = imread(imgLocation[iid], IMREAD_COLOR);
            if (img.empty())
            {
                cout << "Could not load image " + to_string(iid) + " from path: " + current_path().generic_string() << endl;
                throw "Could not load image " + to_string(iid) + " from path: " + current_path().generic_string();
            }

            // Detect the keypoints using SIFT Detector
            Ptr<SIFT> detector = SIFT::create();
            vector<KeyPoint> keypoints;
            Mat descriptors;
            detector->detectAndCompute(img, noArray(), keypoints, descriptors);

            // Create boundary box
            intersection::AABBox box(intersection::Vec3f(0, 0, 0), intersection::Vec3f(0.165, 0.063, 0.093));

            // Store box keypoints and intersection Points
            vector<KeyPoint> tmpKeypoints;
            Mat tmpDescriptor;
            vector<intersection::Vec3f> intersectionPoints;

            // Create output file for matlab code
            ofstream file;
            file.open(writeMatlabLocationTask1b[iid]);
            if (!file.is_open())
            {
                cout << "No file has been created!" << endl;
                throw "No file has been created!";
            }

            // Cycle through all keypoints to check if they intersect with the box
            for (vector<KeyPoint>::iterator iter = keypoints.begin(); iter != keypoints.end(); ++iter)
            {
                // Map 2D points to 3D rays
                Point2d pointOnTeabox = Point2d((*iter).pt.x, (*iter).pt.y);
                pair<intersection::Vec3f, intersection::Vec3f> calculatedRay = convert2DPointTo3DRay(rotationTranslationDirection, pointOnTeabox);

                // Calculate intersection with box
                intersection::Ray ray(calculatedRay.first, calculatedRay.second.normalize());
                float t;
                if (box.intersect(ray, t))
                {
                    // Store intersection keypoint
                    tmpKeypoints.push_back(*iter);

                    // Extract descriptor for intersection point
                    int iteratorIndex = iter - keypoints.begin();
                    Mat intersectionDescriptor = descriptors.row(iteratorIndex);
                    tmpDescriptor.push_back(intersectionDescriptor);

                    // Get intersection point
                    intersection::Vec3f intersection = ray.orig + ray.dir * t;
                    intersectionPoints.push_back(intersection);

                    // Write matlab code to file
                    file << "scatter3(" + to_string(intersection.x) + ", " + to_string(intersection.y) + ", " + to_string(intersection.z) + ", 1);" << endl;
                }
            }

            // Close file
            file << "hold all" << endl;
            file.close();

            // copy intersected points, keypoints and descriptors to storage
            all3DModelPoints.insert(pair(ImageID(iidInt), intersectionPoints));
            allKeypoints.insert(pair(ImageID(iidInt), tmpKeypoints));
            allDescriptors.insert(pair(ImageID(iidInt), tmpDescriptor));
           
            // Draw keypoints on picture and write detected keypoints to image
            Mat output;
            drawKeypoints(img, tmpKeypoints, output);            
            imwrite(imgWriteLocation[iid], output);

        }

        // Create final matlab file for task 1b
        createMatlabFile(true, "task1b.m", writeMatlabLocationTask1b);

        Storage storage;
        storage.descriptors = allDescriptors;
        storage.keypoints = allKeypoints;
        storage.intersectionPoints = all3DModelPoints;

        return storage;
    }
} // namespace task1b