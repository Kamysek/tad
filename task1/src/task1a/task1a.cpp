#include "../input/readInput.h"
#include "../utility/utility.h"
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

namespace task1a
{

    Mat intrinsicCameraMatrix = (Mat_<double>(3, 3) << 2960.37845, 0, 1841.68855, 0, 2960.37845, 1235.23369, 0, 0, 1);

    map<ImageID, map<string, Mat>> task1a()
    {
        // Load teabox 3D coordinates
        map<TeaBoxCorner, Point3d> tb3DCoordinates = teabox3DCoordinates();

        // Load image locations
        map<ImageID, string> imgLocation = imageLocation();

        // Load 2D coordinates of images
        map<ImageID, map<TeaBoxCorner, Point2d>> img2DCoordinates = image2DCoordinates();

        // Rotation and translation
        map<ImageID, map<string, Mat>> rotationTranslationDirection;

        // Load locations where matlab code gets stored
        map<ImageID, string> writeMatlabLocationTask1a = matlabWriteLocationTask1a();

        // Cycle through images
        for (int iidInt = DSC_9743; iidInt != LASTIID; iidInt++)
        {
            ImageID iid = static_cast<ImageID>(iidInt);
            cout << "Calculate information for image" + to_string(iid) << endl;

            // Load 2D coordinates for given image
            map<TeaBoxCorner, Point2d> img2DCords = img2DCoordinates[iid];

            // Load image
            Mat img = readImage(imgLocation[iid], iid);

            // Vector containing the 3D teabox coordinates and the corresponding 2D image coordinates
            vector<Point2d> img2DVect;
            vector<Point3d> tbc3DVect;

            // Cycle through tea box corners
            for (int tbcInt = ZERO; tbcInt != LASTTBC; tbcInt++)
            {
                TeaBoxCorner tbc = static_cast<TeaBoxCorner>(tbcInt);

                // Get values for vector
                if (img2DCords.count(tbc) > 0)
                {
                    img2DVect.push_back(img2DCords[tbc]);
                    tbc3DVect.push_back(tb3DCoordinates[tbc]);
                }
            }

            // Output of solvePnP
            Mat rotationVector;
            Mat translationVector;

            // Distortion coefficients
            Mat distortionCoefficients = cv::Mat::zeros(4, 1, cv::DataType<double>::type);

            // SolvePnP to get rotation vector and translation vector
            solvePnP(tbc3DVect, img2DVect, intrinsicCameraMatrix, distortionCoefficients, rotationVector, translationVector);

            // Obtrain rotation matrix through rodrigues
            Mat rotationMatrix;
            Rodrigues(rotationVector, rotationMatrix);

            // Calculate camera position
            translationVector = -rotationMatrix.t() * translationVector;

            // Calculate camera direction
            Mat vector = (Mat_<double>(3, 1) << 0, 0, 1);
            Mat cameraDirection = rotationMatrix.t() * vector;

            // Store rotation matrix, translation (camera position), camera direction
            map<string, Mat> storeMatTransDir;
            storeMatTransDir.insert(pair("rotation", rotationMatrix));
            storeMatTransDir.insert(pair("translation", translationVector));
            storeMatTransDir.insert(pair("direction", cameraDirection));

            rotationTranslationDirection.insert(pair(iid, storeMatTransDir));

            // Create output file for matlab code
            std::ofstream file;
            file.open(writeMatlabLocationTask1a[iid]);
            if (!file.is_open())
            {
                cout << "No file has been created!" << endl;
                throw "No file has been created!";
            }

            file << "%dsc_" + to_string(iid) << endl;
            file << "%rotation" << endl;
            file << "R" + to_string(iid) + " = [" << format(rotationMatrix, Formatter::FMT_CSV) << "];" << endl;

            file << "%translation" << endl;
            file << "t" + to_string(iid) + " = [" + to_string(translationVector.at<double>(0, 0)) +
                        ", " + to_string(translationVector.at<double>(0, 1)) +
                        ", " + to_string(translationVector.at<double>(0, 2)) + "];"
                 << endl;

            file << "pose" + to_string(iid) + " = rigid3d(R" + to_string(iid) + ", t" + to_string(iid) + ");" << endl;
            file << "vSet = addView(vSet," + to_string(iid) + ", pose" + to_string(iid) + ");" << endl;

            file << "% direction" << endl;
            file << "d" + to_string(iid) + " = [" + to_string(cameraDirection.at<double>(0, 0)) +
                        ", " + to_string(cameraDirection.at<double>(0, 1)) +
                        ", " + to_string(cameraDirection.at<double>(0, 2)) + "];"
                 << endl;

            file << "dsc" + to_string(iid) + " = [" + "t" + to_string(iid) + "; d" + to_string(iid) + "];" << endl;
            file << "line(dsc" + to_string(iid) + "(:,1), dsc" + to_string(iid) + "(:,2), dsc" + to_string(iid) + "(:,3))" << endl;
            file << "hold on" << endl;
            file << "\n"
                 << endl;
            file.close();

        }

        // Create final matlab file for task 1
        createMatlabFile(false, "task1a.m", writeMatlabLocationTask1a);

        return rotationTranslationDirection;
    }
} // namespace task1a