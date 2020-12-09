#include "../input/readInput.h"
#include "../utility/utility.h"
#include "customGeometry.h"
// #include "../intersection/raybox.h"
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
    ReprojectionError(Eigen::Vector3d& M, Eigen::Vector2d& m, Eigen::Matrix3d& intrinsics)
            : M_(M), m_(m), intrinsics_(intrinsics) {}

    template<typename T>
    bool operator()(const T* const R, const T* const t, T* residual) const {
        
        // Project point x = R*M + t
        T x[3];
        T X[3];
        X[0] = T(M_.x());
        X[1] = T(M_.y());
        X[2] = T(M_.z());
        ceres::AngleAxisRotatePoint(R, X, x);
        //ceres::AngleAxisRotatePoint(R, M_, x);
        x[0] += t[0];
        x[1] += t[1];
        x[2] += t[2];   

        // Normalize x, y
        T normalized_x = x[0] / x[2];
        T normalized_y = x[1] / x[2];
       
        // Extract infromation from intrinsics matrix
        T focal_length_x = T(intrinsics_(0,0));
        T focal_length_y = T(intrinsics_(1,1));
        T principal_point_x = T(intrinsics_(0,2));
        T principal_point_y = T(intrinsics_(1,2));

        T predicted_x, predicted_y;

        // Apply focal length and principal point
        predicted_x = focal_length_x * normalized_x + principal_point_x;
        predicted_y = focal_length_y * normalized_y + principal_point_y;

        residual[0] = predicted_x - m_.x();
        residual[1] = predicted_y - m_.y();
        return true;
    }

private:
    Eigen::Vector3d M_;
    Eigen::Vector2d m_;
    Eigen::Matrix3d intrinsics_;
};

namespace task3
{
    void task3(Storage2 storage)
    {
        // Load image locations
        map<ImageIDTask2, string> imgLocation = imageLocationTask2();

        // Rotation Matrix
        Mat R; // = storage.rotationMatrix;

        // Declare what you need
        cv::FileStorage file1("../../resources/R.ext", cv::FileStorage::READ);
        // Write to file!
        //file1 << "R" << R;
        file1["R"] >> R;
        file1.release();

        // Translation Vector
        Mat t;// = storage.translationVect;

        // Declare what you need
        cv::FileStorage file2("../../resources/t.ext", cv::FileStorage::READ);
        // Write to file!
        //file2 << "t" << t;
        file2["t"] >> t;
        file2.release();

        // Keypoints and descriptors previous frame
        vector<KeyPoint> keypointsPreviousImage; // = storage.keypoints;
        // FileStorage fs("../../resources/keypoints.yml", FileStorage::WRITE);
        // write( fs , "aNameYouLike", keypointsPreviousImage );
        // fs.release();

        FileStorage fs2("../../resources/keypoints.yml", FileStorage::READ);
        FileNode kptFileNode = fs2["aNameYouLike"];
        read( kptFileNode, keypointsPreviousImage);
        fs2.release();

        Mat descriptorsPreviousImage; // = storage.descriptors;
        cv::FileStorage file3("../../resources/descriptors.ext", cv::FileStorage::READ);
        //file3 << "descriptors" << descriptorsPreviousImage;
        file3["descriptors"] >> descriptorsPreviousImage;
        file3.release();

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

            // Extract keypoints and descriptors of current frame using SIFT Detector
            Ptr<SIFT> detector = SIFT::create();
            vector<KeyPoint> keypointsCurrentImage;
            Mat descriptorsCurrentImage;
            detector->detectAndCompute(img, noArray(), keypointsCurrentImage, descriptorsCurrentImage);

            // Calculate intersection with object given its keypoints, descriptors
            map<string, Mat> rotationTranslation;
            rotationTranslation.insert(pair("rotation", R));
            
            // Retrieve camera position
            Mat translationVector = -R.t() * t;
            rotationTranslation.insert(pair("translation", translationVector));

            // Returns keypoints, descriptors for intersection points
            IntersectionData intersectionData = checkIntersection(keypointsPreviousImage, rotationTranslation, descriptorsPreviousImage);

            // Find matches between SIFT Features of previous frame and SIFT Features of the current frame
            Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create(DescriptorMatcher::BRUTEFORCE);
            vector<DMatch> matches;
            matcher->match(descriptorsCurrentImage, intersectionData.tmpDescriptor, matches);

            // Get all 3d points from previous frame and 2d points from current frame of matches
            vector<Eigen::Vector3d> MPoints3D;
            vector<Eigen::Vector2d> mPoints2D;
            for (unsigned int i = 0; i < matches.size(); ++i)
            {
                // vector containing all 3d intersection points from training images
                intersection::Vec3f intersectionPoint = intersectionData.intersectionPoints[matches[i].trainIdx];
                MPoints3D.push_back(Eigen::Vector3d(intersectionPoint.x, intersectionPoint.y, intersectionPoint.z));

                Point2f point2d = keypointsCurrentImage[matches[i].queryIdx].pt;
                mPoints2D.push_back(Eigen::Vector2d(point2d.x, point2d.y));
            }

            // Intrinsics for ceres
            Eigen::Matrix3d intrinsics;
            intrinsics << 2960.37845, 0, 1841.68855, 0, 2960.37845, 1235.23369, 0, 0, 1;

            // Create rotation vector
            Mat rotationVector;
            Rodrigues(R, rotationVector);
            

            printMat("Translation", translationVector);

            printMat("Rotation Matrix", R);

            printMat("Rotation Vector", rotationVector);

            // Transform rotation vector and translation vector to eigen
            // Eigen::Vector3d Rotation;
            // Rotation << rotationVector.at<double>(0,0), rotationVector.at<double>(1,0), rotationVector.at<double>(2,0);
        
            // Eigen::Vector3d Translation;
            // Translation << t.at<double>(0,0), t.at<double>(1,0), t.at<double>(2,0);

            // Create problem
            Problem problem;
            for (int i = 0; i < matches.size(); ++i) {
                problem.AddResidualBlock(new AutoDiffCostFunction<ReprojectionError, 2, 3, 3>(
                    new ReprojectionError(MPoints3D.at(i), mPoints2D.at(i), intrinsics)), new ceres::TukeyLoss(4.685), rotationVector.ptr<double>(0), translationVector.ptr<double>(0));
            }

            Solver::Options options;
            options.linear_solver_type = ceres::ITERATIVE_SCHUR;
            options.use_nonmonotonic_steps = true;
            options.preconditioner_type = ceres::SCHUR_JACOBI;
            //options.minimizer_progress_to_stdout = true;
            //options.check_gradients = true;
            Solver::Summary summary;
            Solve(options, &problem, &summary);

            // Convert rotation and translation back to cv
            // Eigen::Vector3d optimized_rvec;
            // optimized_rvec << rot[0], rot[1], rot[2];
            // Eigen::Vector3d optimized_tvec;
            // optimized_tvec << trans[0], trans[1], trans[2];

            // Mat optR = (Mat_<double>(3, 1) << optimized_rvec(0), optimized_rvec(1), optimized_rvec(2));
            // Mat optT = (Mat_<double>(3, 1) << optimized_tvec(0), optimized_tvec(1), optimized_tvec(2));

            printMat("Optimized Rotation", rotationVector);
            printMat("Optimized Translation", translationVector);

            Mat optRotMat;
            Rodrigues(rotationVector, optRotMat);

            printMat("Optimized Rotation Matrix", optRotMat);
            
            R = optRotMat;
            t = translationVector;
        }
    }

} // namespace task3


/*

int t = 0; 
            double lambda = 0.001;
            double u = tau + 1;
        
            // Perform for loop
            do {

                // STEP 1:
                    // Calculate keypoints and descriptors of current frame
                    // Get SIFT Features of previous frame and calculate intersections with object
                    
                    // Project 3D intersection points of previous frame to current frame using the previous camera position
                    // Find matches between between projected points and SIFT features of current frame (Get 2D / 3D correspondences by matching between the current and the previous frame)

                // Extract keypoints and descriptors of current frame using SIFT Detector
                Ptr<SIFT> detector = SIFT::create();
                vector<KeyPoint> keypointsCurrentImage;
                Mat descriptorsCurrentImage;
                detector->detectAndCompute(img, noArray(), keypointsCurrentImage, descriptorsCurrentImage);

                // Calculate intersection with object given its keypoints, descriptors
                // Store box keypoints and intersection Points
                vector<KeyPoint> tmpKeypoints;
                Mat tmpDescriptors;
                vector<Point3d> intersectionPoints;

                map<string, Mat> rotationTranslation;
                Mat rotationMatrix = theta(Rect(0,0,3,3));
                Mat translationVector = theta(Rect(3,0,1,3));
                rotationTranslation.insert(pair("rotation",  rotationMatrix));
                rotationTranslation.insert(pair("translation",  translationVector));

                // Cycle through all keypoints to check if they intersect with the box
                // for (vector<KeyPoint>::iterator iter = keypointsPreviousImage.begin(); iter != keypointsPreviousImage.end(); ++iter)
                // {
                //     // Map 2D points to 3D rays
                //     Point2d pointOnTeabox = Point2d((*iter).pt.x, (*iter).pt.y);
                //     pair<intersection::Vec3f, intersection::Vec3f> calculatedRay = convert2DPointTo3DRay(rotationTranslation, pointOnTeabox);

                //     // Calculate intersection with box
                //     intersection::Ray ray(calculatedRay.first, calculatedRay.second.normalize());
                //     float t;
                //     if (box.intersect(ray, t))
                //     {
                //         // Store intersection keypoint
                //         tmpKeypoints.push_back(*iter);

                //         // Extract descriptor for intersection point
                //         int iteratorIndex = iter - keypointsPreviousImage.begin();
                //         Mat intersectionDescriptors = descriptorsPreviousImage.row(iteratorIndex);
                //         tmpDescriptors.push_back(intersectionDescriptors);

                //         // Get intersection point
                //         intersection::Vec3f tmpIntersection = ray.orig + ray.dir * t;
                //         Point3d intersection = Point3d(tmpIntersection.x, tmpIntersection.y, tmpIntersection.z);
                //         intersectionPoints.push_back(intersection);
                //     }
                // }

                IntersectionData intersectionData = checkIntersection(keypointsPreviousImage, rotationTranslation, descriptorsPreviousImage);

                // Point3d intersection = Point3d(tmpIntersection.x, tmpIntersection.y, tmpIntersection.z);
                // intersectionPoints.push_back(intersection);

                // Find matches between SIFT Features of previous frame and SIFT Features of the current frame
                Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create(DescriptorMatcher::BRUTEFORCE);
                vector<DMatch> matches;
                matcher->match(descriptorsCurrentImage, tmpDescriptors, matches);

                // Cycle through matches and calculate discrepancies between the x, y coordinates
                vector<double> x_discrepancy;
                vector<double> y_discrepancy;

                for (size_t i = 0; i < matches.size(); i++)
                {
                    // Extract x, y coordinates
                    Point2d currentImagePoint = keypointsCurrentImage[matches[i].queryIdx].pt;
                    Point2d tmpImagePoint = tmpKeypoints[matches[i].trainIdx].pt;

                    // Calculate discrepancy
                    x_discrepancy.push_back(abs(currentImagePoint.x - tmpImagePoint.x));
                    y_discrepancy.push_back(abs(currentImagePoint.y - tmpImagePoint.y));
                }

                vector<double> e;
                e.insert(e.end(), x_discrepancy.begin(), x_discrepancy.end());
                e.insert(e.end(), y_discrepancy.begin(), y_discrepancy.end());

                double arr[e.size()];
                copy(e.begin(), e.end(), arr);
                
                double sigma = 1.48257968 * meanAbsoluteDeviation(arr, sizeof(arr) / sizeof(arr[0]));
                
                vector<double> tmpDiagonalVector = e;

                transform(tmpDiagonalVector.begin(), tmpDiagonalVector.end(), tmpDiagonalVector.begin(), [](double elem){return elem / 2; });


                // Step 2: Calculate Error
                    
                    // Calculate discrepancies between matching points 
                        // e2N×1 ← [du(x,θ) dv(x,θ)]T

                    // Apply MAD

                // Step 3: Compute weight and construct diagonal matrix 
                
                    // Ceres apply tukeyloss with c = 4.685


                // Step 4: Update parameter or step size



        //         // The variable to solve for with its initial value.
        //         double initial_x = 5.0;
        //         double x = initial_x;

        //         // Build the ceres problem
        //         Problem problem;

        //         // Set up the only cost function (also known as residual). This uses
        //         // auto-differentiation to obtain the derivative (jacobian).
        //         CostFunction* cost_function =
        //             new AutoDiffCostFunction<CostFunctor, 1, 1>(new CostFunctor);
        //         problem.AddResidualBlock(cost_function, nullptr, &x);

        //          // Run the solver!
        //         Solver::Options options;
        //         options.linear_solver_type = ceres::DENSE_QR;
        //         options.minimizer_progress_to_stdout = true;
        //         Solver::Summary summary;
        //         Solve(options, &problem, &summary);

        //         std::cout << summary.BriefReport() << "\n";
        //         std::cout << "x : " << initial_x
        //                     << " -> " << x << "\n";




            }
            while (t < T && u > tau);

*/

// // Project intersection points from previous camera position to current frame
// Mat distortionCoefficient = Mat::zeros(4, 1, CV_64FC1);

// // Obtrain rotation vector through rodrigues
// Mat rotationVector;
// Rodrigues(rotationMatrix, rotationVector);

// vector<Point2d> outputPoints;
// // Project 3d intersection coordinates to 2d image coordinates
// projectPoints(intersectionPoints, rotationVector, translationVector, A, distortionCoefficient, outputPoints);