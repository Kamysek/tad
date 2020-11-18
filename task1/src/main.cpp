#include <iostream>
#include <opencv2/opencv.hpp>

using std::string, std::map, std::pair, std::cout, std::endl, std::vector;
using namespace cv;

enum TeaBoxCorner {ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, LASTTBC};
enum ImageID {DSC_9743, DSC_9744, DSC_9745, DSC_9746, DSC_9747, DSC_9748, DSC_9749, DSC_9750, LASTIID};

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

map<ImageID, string> imageLocation() 
{
    map<ImageID, string> imageLocation;
    
    imageLocation.insert(pair<ImageID, string>(DSC_9743, "./resources/init_texture/DSC_9743.JPG"));

    //TODO add additional images

    return imageLocation;
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

int main()
{
    // Intrinsic camera positons
    double f_x = 2960.37845;
    double f_y = 2960.37845;
    double c_x = 1841.68855;
    double c_y = 1235.23369;

    // Load 3D teabox coordinates, image location and provided 2D image coordinates
    map<TeaBoxCorner, Point3d> tb3DCoordinates = teabox3DCoordinates();
    map<ImageID, string> imgLocation = imageLocation();
    map<ImageID, map<TeaBoxCorner, Point2d>> img2DCoordinates = image2DCoordinates();
    
    // Cycle through images
    for ( int iidInt = DSC_9743; iidInt != LASTIID; iidInt++ )
    {
        ImageID iid = static_cast<ImageID>(iidInt);

        map<TeaBoxCorner, Point2d> img2DCords = img2DCoordinates[iid];
        
        // Not possible to load 2D coordinates
        if(img2DCoordinates.empty())
        {
            cout << "Could not load 2D coordinates of image!" << endl;
            return 1;
        }

        // Load image
        // imgLocation[iid]
        Mat img = imread( "../../../resources/init_texture/DSC_9743.JPG", IMREAD_COLOR);

        // Not possible to load image
        if(img.empty())
        {
            cout << "Could not load the image!" << endl;
            return 1;
        }

        // Create two vector one containing the 3D teabox coordinates and the second the corresponding 2D image coordinates
        vector<Point2d> img2DVect;
        vector<Point3d> tbc3DVect;

        // Cycle through tea box corners
        for ( int tbcInt = ZERO; tbcInt != LASTTBC; tbcInt++ )
        {
            TeaBoxCorner tbc = static_cast<TeaBoxCorner>(tbcInt);
            
            // Get values for vector
            img2DVect.push_back(img2DCords[tbc]);
            tbc3DVect.push_back(tb3DCoordinates[tbc]);

        }

        // Output vector
        Mat rotationVect; 
        Mat translationVect;        

        // Input camera matrix
        Mat cameraMatrix = (cv::Mat_<double>(3,3) << f_x, 0, c_x, 0 , f_y, c_y, 0, 0, 1);
        Mat distCoeffs = cv::Mat::zeros(4,1,cv::DataType<double>::type); 

        solvePnP(tbc3DVect, img2DVect, cameraMatrix, distCoeffs, rotationVect, translationVect);

        imshow("Display window", rotationVect);
        imshow("Display window", translationVect);
        int k = waitKey(0);

    }
}
    // Cycle through coordinates
    // for (int i = 0; i < (sizeof(tbCorners)/sizeof(*tbCorners)); i++) 
    // { 
    //     for (int j = 0; j < (sizeof(tbCorners[i])/sizeof(*tbCorners[i])); j++) 
    //     { 
    //         std::cout << "Element at x[" << i 
    //              << "][" << j << "]: "; 
    //         std::cout << tbCorners[i][j]<<std::endl; 
    //     } 
    // } 