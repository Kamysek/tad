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
        dsc_9743_Corners.insert(pair(ZERO, Point2d(1373, 1020)));
        dsc_9743_Corners.insert(pair(ONE, Point2d(2239, 1005)));
        dsc_9743_Corners.insert(pair(TWO, Point2d(2311, 1114)));
        dsc_9743_Corners.insert(pair(THREE, Point2d(1342, 1134)));
        dsc_9743_Corners.insert(pair(SIX, Point2d(2279, 1589)));
        dsc_9743_Corners.insert(pair(SEVEN, Point2d(1372, 1619)));

        image2DCoordinates.insert(pair(DSC_9743, dsc_9743_Corners));

        // DSC_9744
        map<TeaBoxCorner, Point2d> dsc_9744_Corners;
        dsc_9744_Corners.insert(pair(ZERO, Point2d(1660, 934)));
        dsc_9744_Corners.insert(pair(ONE, Point2d(2204, 1152)));
        dsc_9744_Corners.insert(pair(TWO, Point2d(1923, 1231)));
        dsc_9744_Corners.insert(pair(THREE, Point2d(1400, 987)));
        dsc_9744_Corners.insert(pair(FIVE, Point2d(2175, 1618)));
        dsc_9744_Corners.insert(pair(SIX, Point2d(1912, 1734)));
        dsc_9744_Corners.insert(pair(SEVEN, Point2d(1419, 1408)));

        image2DCoordinates.insert(pair(DSC_9744, dsc_9744_Corners));

        // DSC_9745
        map<TeaBoxCorner, Point2d> dsc_9745_Corners;
        dsc_9745_Corners.insert(pair(ZERO, Point2d(1837, 992)));
        dsc_9745_Corners.insert(pair(ONE, Point2d(1890, 1283)));
        dsc_9745_Corners.insert(pair(TWO, Point2d(1487, 1278)));
        dsc_9745_Corners.insert(pair(THREE, Point2d(1534, 991)));
        dsc_9745_Corners.insert(pair(FIVE, Point2d(1872, 1782)));
        dsc_9745_Corners.insert(pair(SIX, Point2d(1500, 1791)));

        image2DCoordinates.insert(pair(DSC_9745, dsc_9745_Corners));

        // DSC_9746
        map<TeaBoxCorner, Point2d> dsc_9746_Corners;
        dsc_9746_Corners.insert(pair(ZERO, Point2d(2115, 1055)));
        dsc_9746_Corners.insert(pair(ONE, Point2d(1505, 1274)));
        dsc_9746_Corners.insert(pair(TWO, Point2d(1258, 1175)));
        dsc_9746_Corners.insert(pair(THREE, Point2d(1874, 987)));
        dsc_9746_Corners.insert(pair(FOUR, Point2d(2086, 1471)));
        dsc_9746_Corners.insert(pair(FIVE, Point2d(1512, 1764)));
        dsc_9746_Corners.insert(pair(SIX, Point2d(1274, 1643)));

        image2DCoordinates.insert(pair(DSC_9746, dsc_9746_Corners));

        // DSC_9747
        map<TeaBoxCorner, Point2d> dsc_9747_Corners;
        dsc_9747_Corners.insert(pair(ZERO, Point2d(2330, 1173)));
        dsc_9747_Corners.insert(pair(ONE, Point2d(1345, 1170)));
        dsc_9747_Corners.insert(pair(TWO, Point2d(1395, 1047)));
        dsc_9747_Corners.insert(pair(THREE, Point2d(2281, 1054)));
        dsc_9747_Corners.insert(pair(FOUR, Point2d(2296, 1652)));
        dsc_9747_Corners.insert(pair(FIVE, Point2d(1377, 1644)));

        image2DCoordinates.insert(pair(DSC_9747, dsc_9747_Corners));

        // DSC_9748
        map<TeaBoxCorner, Point2d> dsc_9748_Corners;
        dsc_9748_Corners.insert(pair(ZERO, Point2d(1748, 1180)));
        dsc_9748_Corners.insert(pair(ONE, Point2d(1317, 942)));
        dsc_9748_Corners.insert(pair(TWO, Point2d(1587, 885)));
        dsc_9748_Corners.insert(pair(THREE, Point2d(2056, 1106)));
        dsc_9748_Corners.insert(pair(FOUR, Point2d(1761, 1666)));
        dsc_9748_Corners.insert(pair(FIVE, Point2d(1351, 1349)));
        dsc_9748_Corners.insert(pair(SEVEN, Point2d(2048, 1575)));

        image2DCoordinates.insert(pair(DSC_9748, dsc_9748_Corners));

        // DSC_9749
        map<TeaBoxCorner, Point2d> dsc_9749_Corners;
        dsc_9749_Corners.insert(pair(ZERO, Point2d(1597, 1189)));
        dsc_9749_Corners.insert(pair(ONE, Point2d(1645, 915)));
        dsc_9749_Corners.insert(pair(TWO, Point2d(1938, 909)));
        dsc_9749_Corners.insert(pair(THREE, Point2d(1981, 1189)));
        dsc_9749_Corners.insert(pair(FOUR, Point2d(1616, 1678)));
        dsc_9749_Corners.insert(pair(SEVEN, Point2d(1974, 1681)));

        image2DCoordinates.insert(pair(DSC_9749, dsc_9749_Corners));

        // DSC_9750
        map<TeaBoxCorner, Point2d> dsc_9750_Corners;
        dsc_9750_Corners.insert(pair(ZERO, Point2d(1458, 1141)));
        dsc_9750_Corners.insert(pair(ONE, Point2d(2054, 970)));
        dsc_9750_Corners.insert(pair(TWO, Point2d(2300, 1031)));
        dsc_9750_Corners.insert(pair(THREE, Point2d(1710, 1234)));
        dsc_9750_Corners.insert(pair(FOUR, Point2d(1470, 1608)));
        dsc_9750_Corners.insert(pair(SIX, Point2d(2271, 1449)));
        dsc_9750_Corners.insert(pair(SEVEN, Point2d(1703, 1732)));

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

        imageLocation.insert(pair<ImageIDTask2, string>(DSC_9751, "../../resources/detection/DSC_9751_Keypoints.JPG"));
        imageLocation.insert(pair<ImageIDTask2, string>(DSC_9752, "../../resources/detection/DSC_9752_Keypoints.JPG"));
        imageLocation.insert(pair<ImageIDTask2, string>(DSC_9753, "../../resources/detection/DSC_9753_Keypoints.JPG"));
        imageLocation.insert(pair<ImageIDTask2, string>(DSC_9754, "../../resources/detection/DSC_9754_Keypoints.JPG"));
        imageLocation.insert(pair<ImageIDTask2, string>(DSC_9755, "../../resources/detection/DSC_9755_Keypoints.JPG"));
        imageLocation.insert(pair<ImageIDTask2, string>(DSC_9756, "../../resources/detection/DSC_9756_Keypoints.JPG"));
        imageLocation.insert(pair<ImageIDTask2, string>(DSC_9757, "../../resources/detection/DSC_9757_Keypoints.JPG"));
        imageLocation.insert(pair<ImageIDTask2, string>(DSC_9758, "../../resources/detection/DSC_9758_Keypoints.JPG"));
        imageLocation.insert(pair<ImageIDTask2, string>(DSC_9759, "../../resources/detection/DSC_9759_Keypoints.JPG"));
        imageLocation.insert(pair<ImageIDTask2, string>(DSC_9760, "../../resources/detection/DSC_9760_Keypoints.JPG"));
        imageLocation.insert(pair<ImageIDTask2, string>(DSC_9761, "../../resources/detection/DSC_9761_Keypoints.JPG"));
        imageLocation.insert(pair<ImageIDTask2, string>(DSC_9762, "../../resources/detection/DSC_9762_Keypoints.JPG"));
        imageLocation.insert(pair<ImageIDTask2, string>(DSC_9763, "../../resources/detection/DSC_9763_Keypoints.JPG"));
        imageLocation.insert(pair<ImageIDTask2, string>(DSC_9764, "../../resources/detection/DSC_9764_Keypoints.JPG"));
        imageLocation.insert(pair<ImageIDTask2, string>(DSC_9765, "../../resources/detection/DSC_9765_Keypoints.JPG"));
        imageLocation.insert(pair<ImageIDTask2, string>(DSC_9766, "../../resources/detection/DSC_9766_Keypoints.JPG"));
        imageLocation.insert(pair<ImageIDTask2, string>(DSC_9767, "../../resources/detection/DSC_9767_Keypoints.JPG"));
        imageLocation.insert(pair<ImageIDTask2, string>(DSC_9768, "../../resources/detection/DSC_9768_Keypoints.JPG"));
        imageLocation.insert(pair<ImageIDTask2, string>(DSC_9769, "../../resources/detection/DSC_9769_Keypoints.JPG"));
        imageLocation.insert(pair<ImageIDTask2, string>(DSC_9770, "../../resources/detection/DSC_9770_Keypoints.JPG"));
        imageLocation.insert(pair<ImageIDTask2, string>(DSC_9771, "../../resources/detection/DSC_9771_Keypoints.JPG"));
        imageLocation.insert(pair<ImageIDTask2, string>(DSC_9772, "../../resources/detection/DSC_9772_Keypoints.JPG"));
        imageLocation.insert(pair<ImageIDTask2, string>(DSC_9773, "../../resources/detection/DSC_9773_Keypoints.JPG"));
        imageLocation.insert(pair<ImageIDTask2, string>(DSC_9774, "../../resources/detection/DSC_9774_Keypoints.JPG"));

        return imageLocation;
    }

} // namespace input
