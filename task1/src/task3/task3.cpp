#include "../input/readInput.h"
#include "../utility/utility.h"
#include "customGeometry.h"
#include "ceres/ceres.h"
#include "ceres/rotation.h"
#include "math.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <opencv2/core/eigen.hpp>
#include <opencv2/opencv.hpp>
#include <string>
#include <vector>

using namespace utility;
using namespace input;
using namespace cv;
using namespace intersection;
using ceres::AutoDiffCostFunction;
using ceres::CostFunction;
using ceres::Problem;
using ceres::Solve;
using ceres::Solver;
using std::string, std::map, std::pair, std::cout, std::endl, std::vector, std::to_string, std::filesystem::current_path;

class ReprojectionError {
public:
    ReprojectionError(Eigen::Vector3d &M, Eigen::Vector2d &m, Eigen::Matrix3d &intrinsics)
            : M_(M), m_(m), intrinsics_(intrinsics) {}

    template<typename T>
    bool operator()(const T* const Rt, T* residual) const {
        
        // Project point x = R*M + t
        T x[3];
        T X[3];
        X[0] = T(M_.x());
        X[1] = T(M_.y());
        X[2] = T(M_.z());
        ceres::AngleAxisRotatePoint(Rt, X, x);
        x[0] += T(Rt[3]);
        x[1] += T(Rt[4]);
        x[2] += T(Rt[5]);

        // Extract infromation from intrinsics matrix
        T focal_length_x = T(intrinsics_(0,0));
        T focal_length_y = T(intrinsics_(1,1));
        T principal_point_x = T(intrinsics_(0,2));
        T principal_point_y = T(intrinsics_(1,2));

        T predicted_x, predicted_y;

        // Apply focal length and principal point
        predicted_x = focal_length_x * x[0] + principal_point_x * x[2];
        predicted_y = focal_length_y * x[1] + principal_point_y * x[2];

        // Normalize x, y
        T normalized_x = predicted_x / x[2];
        T normalized_y = predicted_y / x[2];
       


        // // Extract infromation from intrinsics matrix
        // T focal_length_x = T(intrinsics_(0,0));
        // T focal_length_y = T(intrinsics_(1,1));
        // T principal_point_x = T(intrinsics_(0,2));
        // T principal_point_y = T(intrinsics_(1,2));

        // T predicted_x, predicted_y;

        // // Apply focal length and principal point
        // predicted_x = focal_length_x * normalized_x + principal_point_x;
        // predicted_y = focal_length_y * normalized_y + principal_point_y;

        // // Normalize x, y
        // T normalized_x = x[0] / x[2];
        // T normalized_y = x[1] / x[2];
       

        residual[0] = normalized_x - T(m_.x());
        residual[1] = normalized_y - T(m_.y());
        return true;
    }

private:
    Eigen::Vector3d M_;
    Eigen::Vector2d m_;
    Eigen::Matrix3d intrinsics_;
};

namespace task3
{
    void task3(pair<Mat,Mat> rotationTranslation)
    {
    
        // Load image locations
        map<ImageIDTask3, string> imgLocation = imageLocationTask3();

        // Load locations where to save matlab code
        map<ImageIDTask3, string> matlabLocation = matlabWriteLocationTask3();

        // Rotation Matrix
        Mat R = rotationTranslation.first;

        Mat t = rotationTranslation.second;

        // Cycle through images
        for (int iidInt = DSC_7; iidInt != LASTIIDTASK3; iidInt++)
        {
            ImageIDTask3 iid = static_cast<ImageIDTask3>(iidInt);
            cout << "Calculate information for image" + to_string(iid) << endl;

            // Load current frame
            Mat img = imread(imgLocation[iid], IMREAD_COLOR);
            if (img.empty())
            {
                cout << "Could not load image " + to_string(iid) + " from path: " + current_path().generic_string() << endl;
                throw "Could not load image " + to_string(iid) + " from path: " + current_path().generic_string();
            }

            // Load previous frame
            Mat imgPrevious = imread(imgLocation[ImageIDTask3(iid-1)], IMREAD_COLOR);
            if (imgPrevious.empty())
            {
                cout << "Could not load image " + to_string(iid-1) + " from path: " + current_path().generic_string() << endl;
                throw "Could not load image " + to_string(iid-1) + " from path: " + current_path().generic_string();
            }

            // Calculate intersection with object given keypoints, descriptors, rotation matrix and camera position
            map<string, Mat> rotationTranslation;
            rotationTranslation.insert(pair("rotation", R));
           
            Mat camera_position = -R.t() * t;
            rotationTranslation.insert(pair("translation", camera_position));

            // Extract keypoints and descriptors of previous frame using SIFT Detector
            Ptr<SIFT> detector = SIFT::create();
            vector<KeyPoint> keypointsPreviousFrame;
            Mat descriptorsPreviousFrame;
            detector->detectAndCompute(imgPrevious, noArray(), keypointsPreviousFrame, descriptorsPreviousFrame);

            // Returns keypoints, descriptors for intersection points
            IntersectionData intersectionDataPreviousFrame = checkIntersection(keypointsPreviousFrame, rotationTranslation, descriptorsPreviousFrame);
        
            // Extract keypoints and descriptors of current frame using SIFT Detector
            vector<KeyPoint> keypointsCurrentFrame;
            Mat descriptorsCurrentFrame;
            detector->detectAndCompute(img, noArray(), keypointsCurrentFrame, descriptorsCurrentFrame);

            // Returns keypoints, descriptors for intersection points
            IntersectionData intersectionDataCurrentFrame = checkIntersection(keypointsCurrentFrame, rotationTranslation, descriptorsCurrentFrame);

            // Perform matching for two best matching images
            Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create(DescriptorMatcher::FLANNBASED);
            vector<vector<DMatch>> knn_matches;
            matcher->knnMatch(intersectionDataPreviousFrame.tmpDescriptor, intersectionDataCurrentFrame.tmpDescriptor, knn_matches, 2);

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

            vector<Eigen::Vector3d> MPoints3D;
            vector<Eigen::Vector2d> mPoints2D;
            for (unsigned int i = 0; i < good_matches.size(); ++i)
            {
                // Get 3D points of previous frame
                intersection::Vec3f intersectionPoint = intersectionDataPreviousFrame.intersectionPoints[good_matches[i].queryIdx];
                MPoints3D.push_back(Eigen::Vector3d(intersectionPoint.x, intersectionPoint.y, intersectionPoint.z));
                // Get 2D points of current frame
                Point2f imagePoint = intersectionDataCurrentFrame.tmpKeypoints[good_matches[i].trainIdx].pt;
                mPoints2D.push_back(Eigen::Vector2d(imagePoint.x, imagePoint.y));
            }

            // Convert rotation and translation to 
            Eigen::Matrix<double, 3, 3> rotationMatrix;
            cv2eigen(R, rotationMatrix);
            
            Eigen::Vector3d translationVector;
            cv2eigen(t, translationVector);

            // Put rotation vector and translation together
            Eigen::Matrix<double, 6, 1>  Rt;
            ceres::RotationMatrixToAngleAxis(&rotationMatrix(0, 0), &Rt(0));
            Rt.tail<3>() = translationVector;
           
            // Intrinsics for ceres
            Eigen::Matrix3d intrinsics;
            intrinsics << 2960.37845, 0, 1841.68855, 0, 2960.37845, 1235.23369, 0, 0, 1;

            // Build the problem.
            Problem problem;

            for (size_t i = 0; i < MPoints3D.size(); ++i) {
                // Add residual block for matching 3D and 2D points
                problem.AddResidualBlock(new AutoDiffCostFunction<ReprojectionError, 2, 6>(
                        new ReprojectionError(MPoints3D.at(i), mPoints2D.at(i), intrinsics)), new ceres::TukeyLoss(4.685) , &Rt(0));
            }

            // Ceres options
            Solver::Options options;
            options.linear_solver_type = ceres::DENSE_QR;
            options.use_nonmonotonic_steps = true;
            //options.preconditioner_type = ceres::SCHUR_JACOBI;
           
            // Solve and report ceres outcome
            Solver::Summary summary;
            Solve(options, &problem, &summary);
            std::cout << summary.BriefReport() << "\n";

            // Extract optimized rotation and translation
            Eigen::Matrix<double, 3, 3> optRotationMatrix;
            ceres::AngleAxisToRotationMatrix(&Rt(0), &optRotationMatrix(0, 0));
            Eigen::Vector3d optimizedTranslation = Rt.tail<3>();
            
            // Convert back and store for next iteration
            eigen2cv(optRotationMatrix, R);
            printMat("OptR", R);
            eigen2cv(optimizedTranslation, t);
            printMat("Optt", t);

            // Calculate Camera Pose
            Eigen::Vector3d camera_pose = -optRotationMatrix.transpose() * optimizedTranslation;
            cout << "Camera position" << endl;
            cout << camera_pose << endl;

            // Create output file for matlab code
            std::ofstream file;
            file.open(matlabLocation[iid]);
            if (!file.is_open())
            {
                cout << "No file has been created!" << endl;
                throw "No file has been created!";
            }

            file << "%dsc_" + to_string(iid) << endl;
            file << "%rotation" << endl;
            file << "R" + to_string(iid) + " = [" << format(R, Formatter::FMT_CSV) << "];" << endl;

            file << "%translation" << endl;
            file << "t" + to_string(iid) + " = [" + to_string(camera_pose.x()) +
                        ", " + to_string(camera_pose.y()) +
                        ", " + to_string(camera_pose.z()) + "];"
                 << endl;

            file << "pose" + to_string(iid) + " = rigid3d(R" + to_string(iid) + ", t" + to_string(iid) + ");" << endl;
            file << "vSet = addView(vSet," + to_string(iid) + ", pose" + to_string(iid) + ");" << endl;

            file << "\n"
                 << endl;
            file.close();

        }

        // Create final matlab file for task 1b
        createMatlabFileTask3("task3.m", matlabLocation);

    }

} // namespace task3
