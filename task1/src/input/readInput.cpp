#include <string>
#include <map>
#include <utility>
#include <opencv2/opencv.hpp>
#include "readInput.h"
#include "../global/enum.h"

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

        //TODO add additional images

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

        //TODO add additional images

        return imageLocation;
    } 

} // namespace input
