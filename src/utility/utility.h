#ifndef __UTILITY_H__
#define __UTILITY_H__

#include "../../libs/intersection/customGeometry.h"
#include <opencv2/opencv.hpp>
#include <string>
#include <map>

using namespace std;
using namespace cv;

namespace utility
{

    // Enum for teabox corners
    enum TeaBoxCorner
    {
        ZERO = 0,
        ONE = 1,
        TWO = 2,
        THREE = 3,
        FOUR = 4,
        FIVE = 5,
        SIX = 6,
        SEVEN = 7,
        LASTTBC
    };

    // Enum for image ids
    enum ImageID
    {
        DSC_9743 = 9743,
        DSC_9744 = 9744,
        DSC_9745 = 9745,
        DSC_9746 = 9746,
        DSC_9747 = 9747,
        DSC_9748 = 9748,
        DSC_9749 = 9749,
        DSC_9750 = 9750,
        LASTIID
    };

    enum ImageIDTask2
    {
        DSC_9751 = 9751,
        DSC_9752 = 9752,
        DSC_9753 = 9753,
        DSC_9754 = 9754,
        DSC_9755 = 9755,
        DSC_9756 = 9756,
        DSC_9757 = 9757,
        DSC_9758 = 9758,
        DSC_9759 = 9759,
        DSC_9760 = 9760,
        DSC_9761 = 9761,
        DSC_9762 = 9762,
        DSC_9763 = 9763,
        DSC_9764 = 9764,
        DSC_9765 = 9765,
        DSC_9766 = 9766,
        DSC_9767 = 9767,
        DSC_9768 = 9768,
        DSC_9769 = 9769,
        DSC_9770 = 9770,
        DSC_9771 = 9771,
        DSC_9772 = 9772,
        DSC_9773 = 9773,
        DSC_9774 = 9774,
        LASTIIDTASK2
    };

    enum ImageIDTask3
    {
        DSC_6 = 6,
        DSC_7 = 7,
        DSC_8 = 8,
        DSC_9 = 9,
        DSC_10 = 10,
        DSC_11 = 11,
        DSC_12 = 12,
        DSC_13 = 13,
        DSC_14 = 14,
        DSC_15 = 15,
        DSC_16 = 16,
        DSC_17 = 17,
        DSC_18 = 18,
        DSC_19 = 19,
        DSC_20 = 20,
        DSC_21 = 21,
        DSC_22 = 22,
        DSC_23 = 23,
        DSC_24 = 24,
        DSC_25 = 25,
        DSC_26 = 26,
        DSC_27 = 27,
        DSC_28 = 28,
        DSC_29 = 29,
        DSC_30 = 30,
        LASTIIDTASK3
    };

    extern void printMat(string input, Mat image);

    extern void createMatlabFile(bool points, string output, map<ImageID, string> fileLocations);

    extern void createMatlabFileTask3(string output, map<ImageIDTask3, string> fileLocations);

    struct Storage
    {
        map<ImageID, vector<KeyPoint>> keypoints;
        map<ImageID, Mat> descriptors;
        map<ImageID, vector<intersection::Vec3f>> intersectionPoints;
    };

    struct Storage2
    {
        vector<Point3f> matches3Dmodel;
        vector<Point2f> matches2Dimage;
        Mat descriptors;
        vector<KeyPoint> keypoints;
        Mat rotationMatrix;
        Mat translationVect;
    };

    struct IntersectionData
    {
        vector<KeyPoint> tmpKeypoints;
        Mat tmpDescriptor;
        vector<intersection::Vec3f> intersectionPoints;
    };

    IntersectionData checkIntersection(vector<KeyPoint> keypoints, map<string, Mat> rotationTranslationDirection, Mat descriptors);

    Mat readImage(string imageLocation, int iid);

} // namespace utility

#endif