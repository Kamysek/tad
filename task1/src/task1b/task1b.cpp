#include "../input/readInput.h"
#include "../intersection/customGeometry.h"
#include "../utility/utility.h"
#include "math.h"
// #include "../intersection/raybox.h"
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
            Mat img = readImage(imgLocation[iid], iid);

            // Detect the keypoints using SIFT Detector
            Ptr<SIFT> detector = SIFT::create();
            vector<KeyPoint> keypoints;
            Mat descriptors;
            detector->detectAndCompute(img, noArray(), keypoints, descriptors);

            // Calculate Intersection
            IntersectionData intersectionData = checkIntersection(keypoints, rotationTranslationDirection, descriptors);

            // Create output file for matlab code
            ofstream file;
            file.open(writeMatlabLocationTask1b[iid]);
            if (!file.is_open())
            {
                cout << "No file has been created!" << endl;
                throw "No file has been created!";
            }

            // Write matlab code to file
            for (size_t i = 0; i < intersectionData.intersectionPoints.size(); i++)
            {
                file << "scatter3(" + to_string(intersectionData.intersectionPoints[i].x) + ", " + to_string(intersectionData.intersectionPoints[i].y) + ", " + to_string(intersectionData.intersectionPoints[i].z) + ", 1);" << endl;
            }

            // Close file
            file << "hold all" << endl;
            file.close();

            // copy intersected points, keypoints and descriptors to storage
            all3DModelPoints.insert(pair(ImageID(iidInt), intersectionData.intersectionPoints));
            allKeypoints.insert(pair(ImageID(iidInt), intersectionData.tmpKeypoints));
            allDescriptors.insert(pair(ImageID(iidInt), intersectionData.tmpDescriptor));

            // Draw keypoints on picture and write detected keypoints to image
            Mat output;
            drawKeypoints(img, intersectionData.tmpKeypoints, output);
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