#include "utility.h"
#include "../intersection/customGeometry.h"
#include "../intersection/raybox.h"
#include <fstream>
#include <iostream>
#include <map>
#include <opencv2/opencv.hpp>
#include <string>

using namespace std;
using namespace cv;
using namespace intersection;
using std::filesystem::current_path;

namespace utility
{

     Mat readImage(string imageLocation, int iid) {
          Mat img = imread(imageLocation, IMREAD_COLOR);
          if (img.empty())
          {
               cout << "Could not load image " + to_string(iid) + " from path: " + current_path().generic_string() << endl;
               throw "Could not load image " + to_string(iid) + " from path: " + current_path().generic_string();
          } 
          return img;
     }

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

     IntersectionData checkIntersection(vector<KeyPoint> keypoints, map<string, Mat> rotationTranslationDirection, Mat descriptors)
     {
          // Create boundary box
          intersection::AABBox box(intersection::Vec3f(0, 0, 0), intersection::Vec3f(0.165, 0.063, 0.093));

          // Store box keypoints and intersection Points
          vector<KeyPoint> tmpKeypoints;
          Mat tmpDescriptor;
          vector<intersection::Vec3f> intersectionPoints;

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

                    //  Get intersection point
                    intersection::Vec3f intersection = ray.orig + ray.dir * t;
                    intersectionPoints.push_back(intersection);
               }
          }

          IntersectionData intersectionData;
          intersectionData.intersectionPoints = intersectionPoints;
          intersectionData.tmpDescriptor = tmpDescriptor;
          intersectionData.tmpKeypoints = tmpKeypoints;

          return intersectionData;
     }

     void printMat(string input, Mat image)
     {
          cout << input + " = " << endl
               << format(image, Formatter::FMT_CSV) << endl
               << endl;
     }

     void createMatlabFileTask3(string output, map<ImageIDTask3, string> fileLocations)
     {
          string line;

          ofstream combined_file("../../matlab/" + output);
          if (!combined_file.is_open())
          {
               cout << "No file has been created!" << endl;
               throw "No file has been created!";
          }

          ifstream start;
          start.open("../../resources/matlab/init/begin.m");
          if (!start.is_open())
          {
               cout << "No file has been created!" << endl;
               throw "No file has been created!";
          }

          while (getline(start, line))
          {
               combined_file << line << "\n";
          }
          start.close();

          for (int iidInt = DSC_7; iidInt != LASTIIDTASK3; iidInt++)
          {
               ImageIDTask3 iid = static_cast<ImageIDTask3>(iidInt);

               ifstream file;
               file.open(fileLocations[iid]);
               if (!file.is_open())
               {
                    cout << "No file has been created!" << endl;
                    throw "No file has been created!";
               }

               while (getline(file, line))
               {
                    combined_file << line << "\n";
               }

               file.close();
          }

          ifstream end;
          end.open("../../resources/matlab/init/end.m");
          if (!end.is_open())
          {
               cout << "No file has been created!" << endl;
               throw "No file has been created!";
          }

          while (getline(end, line))
          {
               combined_file << line << "\n";
          }
          end.close();
          

          combined_file.close();
     }

     void createMatlabFile(bool points, string output, map<ImageID, string> fileLocations)
     {
          string line;

          ofstream combined_file("../../matlab/" + output);
          if (!combined_file.is_open())
          {
               cout << "No file has been created!" << endl;
               throw "No file has been created!";
          }

          if (!points)
          {
               ifstream start;
               start.open("../../resources/matlab/init/begin.m");
               if (!start.is_open())
               {
                    cout << "No file has been created!" << endl;
                    throw "No file has been created!";
               }

               while (getline(start, line))
               {
                    combined_file << line << "\n";
               }
               start.close();

               for (int iidInt = DSC_9743; iidInt != LASTIID; iidInt++)
               {
                    ImageID iid = static_cast<ImageID>(iidInt);

                    ifstream file;
                    file.open(fileLocations[iid]);
                    if (!file.is_open())
                    {
                         cout << "No file has been created!" << endl;
                         throw "No file has been created!";
                    }

                    while (getline(file, line))
                    {
                         combined_file << line << "\n";
                    }

                    file.close();
               }

               ifstream end;
               end.open("../../resources/matlab/init/end.m");
               if (!end.is_open())
               {
                    cout << "No file has been created!" << endl;
                    throw "No file has been created!";
               }

               while (getline(end, line))
               {
                    combined_file << line << "\n";
               }
               end.close();
          }

          if (points)
          {
               ifstream start;
               start.open("../../matlab/task1a.m");
               if (!start.is_open())
               {
                    cout << "No file has been created!" << endl;
                    throw "No file has been created!";
               }

               while (getline(start, line))
               {
                    combined_file << line << "\n";
               }
               start.close();

               for (int iidInt = DSC_9743; iidInt != LASTIID; iidInt++)
               {
                    ImageID iid = static_cast<ImageID>(iidInt);

                    ifstream file;
                    file.open(fileLocations[iid]);
                    if (!file.is_open())
                    {
                         cout << "No file has been created!" << endl;
                         throw "No file has been created!";
                    }

                    while (getline(file, line))
                    {
                         combined_file << line << "\n";
                    }

                    file.close();
               }
          }

          combined_file.close();
     }

} // namespace utility