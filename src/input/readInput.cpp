#include "readInput.h"
#include "../utility/utility.h"
#include <map>
#include <opencv2/opencv.hpp>
#include <string>

using namespace utility;
using namespace std;
using namespace cv;

namespace input
{

    // Stores all the provided coordinates of a corner for each imageid
    map<ImageID, map<TeaBoxCorner, Point2d>> image2DCoordinates()
    {
        map<ImageID, map<TeaBoxCorner, Point2d>> image2DCoordinates;

        // DSC_9743
        map<TeaBoxCorner, Point2d> dsc_9743_Corners;
        dsc_9743_Corners.insert(pair(ZERO, Point2d(1375, 1024)));
        dsc_9743_Corners.insert(pair(ONE, Point2d(2237, 1009)));
        dsc_9743_Corners.insert(pair(TWO, Point2d(2310, 1116)));
        dsc_9743_Corners.insert(pair(THREE, Point2d(1347, 1138)));
        dsc_9743_Corners.insert(pair(SIX, Point2d(2280, 1589)));
        dsc_9743_Corners.insert(pair(SEVEN, Point2d(1380, 1616)));

        image2DCoordinates.insert(pair(DSC_9743, dsc_9743_Corners));

        // DSC_9744
        map<TeaBoxCorner, Point2d> dsc_9744_Corners;
        dsc_9744_Corners.insert(pair(ZERO, Point2d(1660, 938)));
        dsc_9744_Corners.insert(pair(ONE, Point2d(2204, 1154)));
        dsc_9744_Corners.insert(pair(TWO, Point2d(1928, 1233)));
        dsc_9744_Corners.insert(pair(THREE, Point2d(1404, 990)));
        dsc_9744_Corners.insert(pair(FIVE, Point2d(2177, 1620)));
        dsc_9744_Corners.insert(pair(SIX, Point2d(1916, 1736)));
        dsc_9744_Corners.insert(pair(SEVEN, Point2d(1422, 1410)));

        image2DCoordinates.insert(pair(DSC_9744, dsc_9744_Corners));

        // DSC_9745
        map<TeaBoxCorner, Point2d> dsc_9745_Corners;
        dsc_9745_Corners.insert(pair(ZERO, Point2d(1886, 859)));
        dsc_9745_Corners.insert(pair(ONE, Point2d(1936, 1148)));
        dsc_9745_Corners.insert(pair(TWO, Point2d(1539, 1144)));
        dsc_9745_Corners.insert(pair(THREE, Point2d(1585, 858)));
        dsc_9745_Corners.insert(pair(FIVE, Point2d(1920, 1650)));
        dsc_9745_Corners.insert(pair(SIX, Point2d(1551, 1658)));

        image2DCoordinates.insert(pair(DSC_9745, dsc_9745_Corners));

        // DSC_9746
        map<TeaBoxCorner, Point2d> dsc_9746_Corners;
        dsc_9746_Corners.insert(pair(ZERO, Point2d(2316, 979)));
        dsc_9746_Corners.insert(pair(ONE, Point2d(1710, 1196)));
        dsc_9746_Corners.insert(pair(TWO, Point2d(1461, 1101)));
        dsc_9746_Corners.insert(pair(THREE, Point2d(2074, 911)));
        dsc_9746_Corners.insert(pair(FOUR, Point2d(2287, 1395)));
        dsc_9746_Corners.insert(pair(FIVE, Point2d(1716, 1686)));
        dsc_9746_Corners.insert(pair(SIX, Point2d(1476, 1568)));

        image2DCoordinates.insert(pair(DSC_9746, dsc_9746_Corners));

        // DSC_9747
        map<TeaBoxCorner, Point2d> dsc_9747_Corners;
        dsc_9747_Corners.insert(pair(ZERO, Point2d(2296, 1129)));
        dsc_9747_Corners.insert(pair(ONE, Point2d(1308, 1123)));
        dsc_9747_Corners.insert(pair(TWO, Point2d(1359, 1002)));
        dsc_9747_Corners.insert(pair(THREE, Point2d(2244, 1011)));
        dsc_9747_Corners.insert(pair(FOUR, Point2d(2262, 1607)));
        dsc_9747_Corners.insert(pair(FIVE, Point2d(1343, 1600)));

        image2DCoordinates.insert(pair(DSC_9747, dsc_9747_Corners));

        // DSC_9748
        map<TeaBoxCorner, Point2d> dsc_9748_Corners;
        dsc_9748_Corners.insert(pair(ZERO, Point2d(1749, 1179)));
        dsc_9748_Corners.insert(pair(ONE, Point2d(1322, 942)));
        dsc_9748_Corners.insert(pair(TWO, Point2d(1587, 887)));
        dsc_9748_Corners.insert(pair(THREE, Point2d(2057, 1106)));
        dsc_9748_Corners.insert(pair(FOUR, Point2d(1761, 1670)));
        dsc_9748_Corners.insert(pair(FIVE, Point2d(1353, 1351)));
        dsc_9748_Corners.insert(pair(SEVEN, Point2d(2048, 1576)));

        image2DCoordinates.insert(pair(DSC_9748, dsc_9748_Corners));

        // DSC_9749
        map<TeaBoxCorner, Point2d> dsc_9749_Corners;
        dsc_9749_Corners.insert(pair(ZERO, Point2d(1601, 1189)));
        dsc_9749_Corners.insert(pair(ONE, Point2d(1649, 915)));
        dsc_9749_Corners.insert(pair(TWO, Point2d(1938, 909)));
        dsc_9749_Corners.insert(pair(THREE, Point2d(1983, 1189)));
        dsc_9749_Corners.insert(pair(FOUR, Point2d(1616, 1683)));
        dsc_9749_Corners.insert(pair(SEVEN, Point2d(1976, 1681)));

        image2DCoordinates.insert(pair(DSC_9749, dsc_9749_Corners));

        // DSC_9750
        map<TeaBoxCorner, Point2d> dsc_9750_Corners;
        dsc_9750_Corners.insert(pair(ZERO, Point2d(1461, 1146)));
        dsc_9750_Corners.insert(pair(ONE, Point2d(2054, 970)));
        dsc_9750_Corners.insert(pair(TWO, Point2d(2295, 1031)));
        dsc_9750_Corners.insert(pair(THREE, Point2d(1711, 1236)));
        dsc_9750_Corners.insert(pair(FOUR, Point2d(1472, 1611)));
        dsc_9750_Corners.insert(pair(SIX, Point2d(2271, 1449)));
        dsc_9750_Corners.insert(pair(SEVEN, Point2d(1708, 1750)));

        image2DCoordinates.insert(pair(DSC_9750, dsc_9750_Corners));

        return image2DCoordinates;
    }

    // Stores all the coordinates of a corner from the teabox.ply
    map<TeaBoxCorner, Point3d> teabox3DCoordinates()
    {
        map<TeaBoxCorner, Point3d> teabox3DCoordinates;
        teabox3DCoordinates.insert(pair(ZERO, Point3d(0, 0.063, 0.093)));
        teabox3DCoordinates.insert(pair(ONE, Point3d(0.165, 0.063, 0.093)));
        teabox3DCoordinates.insert(pair(TWO, Point3d(0.165, 0, 0.093)));
        teabox3DCoordinates.insert(pair(THREE, Point3d(0, 0, 0.093)));
        teabox3DCoordinates.insert(pair(FOUR, Point3d(0, 0.063, 0)));
        teabox3DCoordinates.insert(pair(FIVE, Point3d(0.165, 0.063, 0)));
        teabox3DCoordinates.insert(pair(SIX, Point3d(0.165, 0, 0)));
        teabox3DCoordinates.insert(pair(SEVEN, Point3d(0, 0, 0)));

        return teabox3DCoordinates;
    }

    map<ImageID, string> imageLocation()
    {
        map<ImageID, string> imageLocation;

        imageLocation.insert(pair<ImageID, string>(DSC_9743, "../../resources/init_texture/DSC_9743.JPG"));
        imageLocation.insert(pair<ImageID, string>(DSC_9744, "../../resources/init_texture/DSC_9744.JPG"));
        imageLocation.insert(pair<ImageID, string>(DSC_9745, "../../resources/init_texture/DSC_9745.JPG"));
        imageLocation.insert(pair<ImageID, string>(DSC_9746, "../../resources/init_texture/DSC_9746.JPG"));
        imageLocation.insert(pair<ImageID, string>(DSC_9747, "../../resources/init_texture/DSC_9747.JPG"));
        imageLocation.insert(pair<ImageID, string>(DSC_9748, "../../resources/init_texture/DSC_9748.JPG"));
        imageLocation.insert(pair<ImageID, string>(DSC_9749, "../../resources/init_texture/DSC_9749.JPG"));
        imageLocation.insert(pair<ImageID, string>(DSC_9750, "../../resources/init_texture/DSC_9750.JPG"));

        return imageLocation;
    }

    map<ImageID, string> imageWriteLocation()
    {
        map<ImageID, string> imageLocation;

        imageLocation.insert(pair<ImageID, string>(DSC_9743, "../../resources/init_texture/DSC_9743_Keypoints.JPG"));
        imageLocation.insert(pair<ImageID, string>(DSC_9744, "../../resources/init_texture/DSC_9744_Keypoints.JPG"));
        imageLocation.insert(pair<ImageID, string>(DSC_9745, "../../resources/init_texture/DSC_9745_Keypoints.JPG"));
        imageLocation.insert(pair<ImageID, string>(DSC_9746, "../../resources/init_texture/DSC_9746_Keypoints.JPG"));
        imageLocation.insert(pair<ImageID, string>(DSC_9747, "../../resources/init_texture/DSC_9747_Keypoints.JPG"));
        imageLocation.insert(pair<ImageID, string>(DSC_9748, "../../resources/init_texture/DSC_9748_Keypoints.JPG"));
        imageLocation.insert(pair<ImageID, string>(DSC_9749, "../../resources/init_texture/DSC_9749_Keypoints.JPG"));
        imageLocation.insert(pair<ImageID, string>(DSC_9750, "../../resources/init_texture/DSC_9750_Keypoints.JPG"));

        return imageLocation;
    }

    map<ImageID, string> matlabWriteLocationTask1a()
    {
        map<ImageID, string> matlabWriteLocation;

        matlabWriteLocation.insert(pair<ImageID, string>(DSC_9743, "../../resources/matlab/task1a/DSC_9743_Keypoints.m"));
        matlabWriteLocation.insert(pair<ImageID, string>(DSC_9744, "../../resources/matlab/task1a/DSC_9744_Keypoints.m"));
        matlabWriteLocation.insert(pair<ImageID, string>(DSC_9745, "../../resources/matlab/task1a/DSC_9745_Keypoints.m"));
        matlabWriteLocation.insert(pair<ImageID, string>(DSC_9746, "../../resources/matlab/task1a/DSC_9746_Keypoints.m"));
        matlabWriteLocation.insert(pair<ImageID, string>(DSC_9747, "../../resources/matlab/task1a/DSC_9747_Keypoints.m"));
        matlabWriteLocation.insert(pair<ImageID, string>(DSC_9748, "../../resources/matlab/task1a/DSC_9748_Keypoints.m"));
        matlabWriteLocation.insert(pair<ImageID, string>(DSC_9749, "../../resources/matlab/task1a/DSC_9749_Keypoints.m"));
        matlabWriteLocation.insert(pair<ImageID, string>(DSC_9750, "../../resources/matlab/task1a/DSC_9750_Keypoints.m"));

        return matlabWriteLocation;
    }

    map<ImageID, string> matlabWriteLocationTask1b()
    {
        map<ImageID, string> matlabWriteLocation;

        matlabWriteLocation.insert(pair<ImageID, string>(DSC_9743, "../../resources/matlab/task1b/DSC_9743_Keypoints.m"));
        matlabWriteLocation.insert(pair<ImageID, string>(DSC_9744, "../../resources/matlab/task1b/DSC_9744_Keypoints.m"));
        matlabWriteLocation.insert(pair<ImageID, string>(DSC_9745, "../../resources/matlab/task1b/DSC_9745_Keypoints.m"));
        matlabWriteLocation.insert(pair<ImageID, string>(DSC_9746, "../../resources/matlab/task1b/DSC_9746_Keypoints.m"));
        matlabWriteLocation.insert(pair<ImageID, string>(DSC_9747, "../../resources/matlab/task1b/DSC_9747_Keypoints.m"));
        matlabWriteLocation.insert(pair<ImageID, string>(DSC_9748, "../../resources/matlab/task1b/DSC_9748_Keypoints.m"));
        matlabWriteLocation.insert(pair<ImageID, string>(DSC_9749, "../../resources/matlab/task1b/DSC_9749_Keypoints.m"));
        matlabWriteLocation.insert(pair<ImageID, string>(DSC_9750, "../../resources/matlab/task1b/DSC_9750_Keypoints.m"));

        return matlabWriteLocation;
    }

    map<ImageIDTask2, string> imageLocationTask2()
    {
        map<ImageIDTask2, string> imageLocation;

        imageLocation.insert(pair<ImageIDTask2, string>(DSC_9751, "../../resources/detection/DSC_9751.JPG"));
        imageLocation.insert(pair<ImageIDTask2, string>(DSC_9752, "../../resources/detection/DSC_9752.JPG"));
        imageLocation.insert(pair<ImageIDTask2, string>(DSC_9753, "../../resources/detection/DSC_9753.JPG"));
        imageLocation.insert(pair<ImageIDTask2, string>(DSC_9754, "../../resources/detection/DSC_9754.JPG"));
        imageLocation.insert(pair<ImageIDTask2, string>(DSC_9755, "../../resources/detection/DSC_9755.JPG"));
        imageLocation.insert(pair<ImageIDTask2, string>(DSC_9756, "../../resources/detection/DSC_9756.JPG"));
        imageLocation.insert(pair<ImageIDTask2, string>(DSC_9757, "../../resources/detection/DSC_9757.JPG"));
        imageLocation.insert(pair<ImageIDTask2, string>(DSC_9758, "../../resources/detection/DSC_9758.JPG"));
        imageLocation.insert(pair<ImageIDTask2, string>(DSC_9759, "../../resources/detection/DSC_9759.JPG"));
        imageLocation.insert(pair<ImageIDTask2, string>(DSC_9760, "../../resources/detection/DSC_9760.JPG"));
        imageLocation.insert(pair<ImageIDTask2, string>(DSC_9761, "../../resources/detection/DSC_9761.JPG"));
        imageLocation.insert(pair<ImageIDTask2, string>(DSC_9762, "../../resources/detection/DSC_9762.JPG"));
        imageLocation.insert(pair<ImageIDTask2, string>(DSC_9763, "../../resources/detection/DSC_9763.JPG"));
        imageLocation.insert(pair<ImageIDTask2, string>(DSC_9764, "../../resources/detection/DSC_9764.JPG"));
        imageLocation.insert(pair<ImageIDTask2, string>(DSC_9765, "../../resources/detection/DSC_9765.JPG"));
        imageLocation.insert(pair<ImageIDTask2, string>(DSC_9766, "../../resources/detection/DSC_9766.JPG"));
        imageLocation.insert(pair<ImageIDTask2, string>(DSC_9767, "../../resources/detection/DSC_9767.JPG"));
        imageLocation.insert(pair<ImageIDTask2, string>(DSC_9768, "../../resources/detection/DSC_9768.JPG"));
        imageLocation.insert(pair<ImageIDTask2, string>(DSC_9769, "../../resources/detection/DSC_9769.JPG"));
        imageLocation.insert(pair<ImageIDTask2, string>(DSC_9770, "../../resources/detection/DSC_9770.JPG"));
        imageLocation.insert(pair<ImageIDTask2, string>(DSC_9771, "../../resources/detection/DSC_9771.JPG"));
        imageLocation.insert(pair<ImageIDTask2, string>(DSC_9772, "../../resources/detection/DSC_9772.JPG"));
        imageLocation.insert(pair<ImageIDTask2, string>(DSC_9773, "../../resources/detection/DSC_9773.JPG"));
        imageLocation.insert(pair<ImageIDTask2, string>(DSC_9774, "../../resources/detection/DSC_9774.JPG"));

        return imageLocation;
    }

    map<ImageIDTask2, string> imageWriteLocationTask2()
    {
        map<ImageIDTask2, string> imageLocation;

        imageLocation.insert(pair<ImageIDTask2, string>(DSC_9751, "../../resources/detection/DSC_9751_Box.JPG"));
        imageLocation.insert(pair<ImageIDTask2, string>(DSC_9752, "../../resources/detection/DSC_9752_Box.JPG"));
        imageLocation.insert(pair<ImageIDTask2, string>(DSC_9753, "../../resources/detection/DSC_9753_Box.JPG"));
        imageLocation.insert(pair<ImageIDTask2, string>(DSC_9754, "../../resources/detection/DSC_9754_Box.JPG"));
        imageLocation.insert(pair<ImageIDTask2, string>(DSC_9755, "../../resources/detection/DSC_9755_Box.JPG"));
        imageLocation.insert(pair<ImageIDTask2, string>(DSC_9756, "../../resources/detection/DSC_9756_Box.JPG"));
        imageLocation.insert(pair<ImageIDTask2, string>(DSC_9757, "../../resources/detection/DSC_9757_Box.JPG"));
        imageLocation.insert(pair<ImageIDTask2, string>(DSC_9758, "../../resources/detection/DSC_9758_Box.JPG"));
        imageLocation.insert(pair<ImageIDTask2, string>(DSC_9759, "../../resources/detection/DSC_9759_Box.JPG"));
        imageLocation.insert(pair<ImageIDTask2, string>(DSC_9760, "../../resources/detection/DSC_9760_Box.JPG"));
        imageLocation.insert(pair<ImageIDTask2, string>(DSC_9761, "../../resources/detection/DSC_9761_Box.JPG"));
        imageLocation.insert(pair<ImageIDTask2, string>(DSC_9762, "../../resources/detection/DSC_9762_Box.JPG"));
        imageLocation.insert(pair<ImageIDTask2, string>(DSC_9763, "../../resources/detection/DSC_9763_Box.JPG"));
        imageLocation.insert(pair<ImageIDTask2, string>(DSC_9764, "../../resources/detection/DSC_9764_Box.JPG"));
        imageLocation.insert(pair<ImageIDTask2, string>(DSC_9765, "../../resources/detection/DSC_9765_Box.JPG"));
        imageLocation.insert(pair<ImageIDTask2, string>(DSC_9766, "../../resources/detection/DSC_9766_Box.JPG"));
        imageLocation.insert(pair<ImageIDTask2, string>(DSC_9767, "../../resources/detection/DSC_9767_Box.JPG"));
        imageLocation.insert(pair<ImageIDTask2, string>(DSC_9768, "../../resources/detection/DSC_9768_Box.JPG"));
        imageLocation.insert(pair<ImageIDTask2, string>(DSC_9769, "../../resources/detection/DSC_9769_Box.JPG"));
        imageLocation.insert(pair<ImageIDTask2, string>(DSC_9770, "../../resources/detection/DSC_9770_Box.JPG"));
        imageLocation.insert(pair<ImageIDTask2, string>(DSC_9771, "../../resources/detection/DSC_9771_Box.JPG"));
        imageLocation.insert(pair<ImageIDTask2, string>(DSC_9772, "../../resources/detection/DSC_9772_Box.JPG"));
        imageLocation.insert(pair<ImageIDTask2, string>(DSC_9773, "../../resources/detection/DSC_9773_Box.JPG"));
        imageLocation.insert(pair<ImageIDTask2, string>(DSC_9774, "../../resources/detection/DSC_9774_Box.JPG"));

        return imageLocation;
    }

 map<ImageIDTask3, string> imageLocationTask3()
    {
        map<ImageIDTask3, string> imageLocation;

        imageLocation.insert(pair<ImageIDTask3, string>(DSC_6, "../../resources/tracking/color_000006.JPG"));
        imageLocation.insert(pair<ImageIDTask3, string>(DSC_7, "../../resources/tracking/color_000007.JPG"));
        imageLocation.insert(pair<ImageIDTask3, string>(DSC_8, "../../resources/tracking/color_000008.JPG"));
        imageLocation.insert(pair<ImageIDTask3, string>(DSC_9, "../../resources/tracking/color_000009.JPG"));
        imageLocation.insert(pair<ImageIDTask3, string>(DSC_10, "../../resources/tracking/color_000010.JPG"));
        imageLocation.insert(pair<ImageIDTask3, string>(DSC_11, "../../resources/tracking/color_000011.JPG"));
        imageLocation.insert(pair<ImageIDTask3, string>(DSC_12, "../../resources/tracking/color_000012.JPG"));
        imageLocation.insert(pair<ImageIDTask3, string>(DSC_13, "../../resources/tracking/color_000013.JPG"));
        imageLocation.insert(pair<ImageIDTask3, string>(DSC_14, "../../resources/tracking/color_000014.JPG"));
        imageLocation.insert(pair<ImageIDTask3, string>(DSC_15, "../../resources/tracking/color_000015.JPG"));
        imageLocation.insert(pair<ImageIDTask3, string>(DSC_16, "../../resources/tracking/color_000016.JPG"));
        imageLocation.insert(pair<ImageIDTask3, string>(DSC_17, "../../resources/tracking/color_000017.JPG"));
        imageLocation.insert(pair<ImageIDTask3, string>(DSC_18, "../../resources/tracking/color_000018.JPG"));
        imageLocation.insert(pair<ImageIDTask3, string>(DSC_19, "../../resources/tracking/color_000019.JPG"));
        imageLocation.insert(pair<ImageIDTask3, string>(DSC_20, "../../resources/tracking/color_000020.JPG"));
        imageLocation.insert(pair<ImageIDTask3, string>(DSC_21, "../../resources/tracking/color_000021.JPG"));
        imageLocation.insert(pair<ImageIDTask3, string>(DSC_22, "../../resources/tracking/color_000022.JPG"));
        imageLocation.insert(pair<ImageIDTask3, string>(DSC_23, "../../resources/tracking/color_000023.JPG"));
        imageLocation.insert(pair<ImageIDTask3, string>(DSC_24, "../../resources/tracking/color_000024.JPG"));
        imageLocation.insert(pair<ImageIDTask3, string>(DSC_25, "../../resources/tracking/color_000025.JPG"));
        imageLocation.insert(pair<ImageIDTask3, string>(DSC_26, "../../resources/tracking/color_000026.JPG"));
        imageLocation.insert(pair<ImageIDTask3, string>(DSC_27, "../../resources/tracking/color_000027.JPG"));
        imageLocation.insert(pair<ImageIDTask3, string>(DSC_28, "../../resources/tracking/color_000028.JPG"));
        imageLocation.insert(pair<ImageIDTask3, string>(DSC_29, "../../resources/tracking/color_000029.JPG"));
        imageLocation.insert(pair<ImageIDTask3, string>(DSC_30, "../../resources/tracking/color_000030.JPG"));

        return imageLocation;
    }
    
     map<ImageIDTask3, string> matlabWriteLocationTask3()
    {
        map<ImageIDTask3, string> imageLocation;

        imageLocation.insert(pair<ImageIDTask3, string>(DSC_6, "../../resources/matlab/task3/color_000006_Rt.m"));
        imageLocation.insert(pair<ImageIDTask3, string>(DSC_7, "../../resources/matlab/task3/color_000007_Rt.m"));
        imageLocation.insert(pair<ImageIDTask3, string>(DSC_8, "../../resources/matlab/task3/color_000008_Rt.m"));
        imageLocation.insert(pair<ImageIDTask3, string>(DSC_9, "../../resources/matlab/task3/color_000009_Rt.m"));
        imageLocation.insert(pair<ImageIDTask3, string>(DSC_10, "../../resources/matlab/task3/color_000010_Rt.m"));
        imageLocation.insert(pair<ImageIDTask3, string>(DSC_11, "../../resources/matlab/task3/color_000011_Rt.m"));
        imageLocation.insert(pair<ImageIDTask3, string>(DSC_12, "../../resources/matlab/task3/color_000012_Rt.m"));
        imageLocation.insert(pair<ImageIDTask3, string>(DSC_13, "../../resources/matlab/task3/color_000013_Rt.m"));
        imageLocation.insert(pair<ImageIDTask3, string>(DSC_14, "../../resources/matlab/task3/color_000014_Rt.m"));
        imageLocation.insert(pair<ImageIDTask3, string>(DSC_15, "../../resources/matlab/task3/color_000015_Rt.m"));
        imageLocation.insert(pair<ImageIDTask3, string>(DSC_16, "../../resources/matlab/task3/color_000016_Rt.m"));
        imageLocation.insert(pair<ImageIDTask3, string>(DSC_17, "../../resources/matlab/task3/color_000017_Rt.m"));
        imageLocation.insert(pair<ImageIDTask3, string>(DSC_18, "../../resources/matlab/task3/color_000018_Rt.m"));
        imageLocation.insert(pair<ImageIDTask3, string>(DSC_19, "../../resources/matlab/task3/color_000019_Rt.m"));
        imageLocation.insert(pair<ImageIDTask3, string>(DSC_20, "../../resources/matlab/task3/color_000020_Rt.m"));
        imageLocation.insert(pair<ImageIDTask3, string>(DSC_21, "../../resources/matlab/task3/color_000021_Rt.m"));
        imageLocation.insert(pair<ImageIDTask3, string>(DSC_22, "../../resources/matlab/task3/color_000022_Rt.m"));
        imageLocation.insert(pair<ImageIDTask3, string>(DSC_23, "../../resources/matlab/task3/color_000023_Rt.m"));
        imageLocation.insert(pair<ImageIDTask3, string>(DSC_24, "../../resources/matlab/task3/color_000024_Rt.m"));
        imageLocation.insert(pair<ImageIDTask3, string>(DSC_25, "../../resources/matlab/task3/color_000025_Rt.m"));
        imageLocation.insert(pair<ImageIDTask3, string>(DSC_26, "../../resources/matlab/task3/color_000026_Rt.m"));
        imageLocation.insert(pair<ImageIDTask3, string>(DSC_27, "../../resources/matlab/task3/color_000027_Rt.m"));
        imageLocation.insert(pair<ImageIDTask3, string>(DSC_28, "../../resources/matlab/task3/color_000028_Rt.m"));
        imageLocation.insert(pair<ImageIDTask3, string>(DSC_29, "../../resources/matlab/task3/color_000029_Rt.m"));
        imageLocation.insert(pair<ImageIDTask3, string>(DSC_30, "../../resources/matlab/task3/color_000030_Rt.m"));

        return imageLocation;
    }

} // namespace input
