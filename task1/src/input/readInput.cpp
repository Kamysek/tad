#include "readInput.h"
#include "../global/enum.h"
#include <string>
#include <map>
#include <utility>
#include <opencv2/opencv.hpp>

using namespace global;
using namespace cv;

using std::string, std::map, std::pair;

namespace input {
   
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
        dsc_9748_Corners.insert(pair(ZERO, Point2d(1872, 1354)));
        dsc_9748_Corners.insert(pair(ONE, Point2d(1444, 1116)));
        dsc_9748_Corners.insert(pair(TWO, Point2d(1710, 1060)));
        dsc_9748_Corners.insert(pair(THREE, Point2d(2178, 1280)));
        dsc_9748_Corners.insert(pair(FOUR, Point2d(1993, 1847)));
        dsc_9748_Corners.insert(pair(FIVE, Point2d(1376, 1523)));
        dsc_9748_Corners.insert(pair(SEVEN, Point2d(2169, 1752)));
        
        image2DCoordinates.insert(pair(DSC_9748, dsc_9748_Corners));

        // DSC_9749
        map<TeaBoxCorner, Point2d> dsc_9749_Corners;
        dsc_9749_Corners.insert(pair(ZERO, Point2d(2018, 1550)));
        dsc_9749_Corners.insert(pair(ONE, Point2d(2063, 1274)));
        dsc_9749_Corners.insert(pair(TWO, Point2d(2355, 1274)));
        dsc_9749_Corners.insert(pair(THREE, Point2d(2406, 1552)));
        dsc_9749_Corners.insert(pair(FOUR, Point2d(2029, 2044)));
        dsc_9749_Corners.insert(pair(SEVEN, Point2d(2388, 2041)));
        
        image2DCoordinates.insert(pair(DSC_9749, dsc_9749_Corners));

        // DSC_9750
        map<TeaBoxCorner, Point2d> dsc_9750_Corners;
        dsc_9750_Corners.insert(pair(ZERO, Point2d(1323, 1468)));
        dsc_9750_Corners.insert(pair(ONE, Point2d(1919, 1291)));
        dsc_9750_Corners.insert(pair(TWO, Point2d(2159, 1351)));
        dsc_9750_Corners.insert(pair(THREE, Point2d(1571, 1555)));
        dsc_9750_Corners.insert(pair(FOUR, Point2d(1333, 1932)));
        dsc_9750_Corners.insert(pair(SIX, Point2d(2132, 1770)));
        dsc_9750_Corners.insert(pair(SEVEN, Point2d(1571, 2053)));
        
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

    map<ImageID, string> matlabWriteLocationTask1b() 
    {
        map<ImageID, string> imageLocation;
        
        imageLocation.insert(pair<ImageID, string>(DSC_9743, "../../resources/init_texture/matlab/task1b/DSC_9743_Keypoints.txt"));
        imageLocation.insert(pair<ImageID, string>(DSC_9744, "../../resources/init_texture/matlab/task1b/DSC_9744_Keypoints.txt"));
        imageLocation.insert(pair<ImageID, string>(DSC_9745, "../../resources/init_texture/matlab/task1b/DSC_9745_Keypoints.txt"));
        imageLocation.insert(pair<ImageID, string>(DSC_9746, "../../resources/init_texture/matlab/task1b/DSC_9746_Keypoints.txt"));
        imageLocation.insert(pair<ImageID, string>(DSC_9747, "../../resources/init_texture/matlab/task1b/DSC_9747_Keypoints.txt"));
        imageLocation.insert(pair<ImageID, string>(DSC_9748, "../../resources/init_texture/matlab/task1b/DSC_9748_Keypoints.txt"));
        imageLocation.insert(pair<ImageID, string>(DSC_9749, "../../resources/init_texture/matlab/task1b/DSC_9749_Keypoints.txt"));
        imageLocation.insert(pair<ImageID, string>(DSC_9750, "../../resources/init_texture/matlab/task1b/DSC_9750_Keypoints.txt"));

        return imageLocation;
    } 

} // namespace input
