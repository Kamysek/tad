#include <iostream>
#include <opencv2/opencv.hpp>
#include <test.h>

using namespace cv;

int main()
{

    // Corners of provided teabox.ply 
    // A corner has the following structure (x,y,z)
    double tbCorners[8][3] = {{0, 0.063, 0.093},        // 0
                                {0.165, 0.063, 0.093},  // 1
                                {0.165, 0, 0.093},      // 2
                                {0, 0, 0.093},          // 3
                                {0, 0.063, 0},          // 4
                                {0.165, 0.063, 0},      // 5
                                {0.165, 0, 0},          // 6
                                {0, 0, 0}};             // 7 (lower left corner)
    
    // Intrinsic camera positons
    double f_x = 2960.37845;
    double f_y = 2960.37845;
    double c_x = 1841.68855;
    double c_y = 1235.23369;

    // 2D image coordinates
    // DSC_9743
    double tb_DSC_9743[6][2] = {{1373 ,1020},       // 0
                                {2239, 1005},       // 1
                                {2311, 1114},       // 2
                                {1342, 1134},       // 3
                                {2279, 1589},       // 6
                                {1372, 1619}};      // 7

    // Cycle through coordinates
    for (int i = 0; i < (sizeof(tbCorners)/sizeof(*tbCorners)); i++) 
    { 
        for (int j = 0; j < (sizeof(tbCorners[i])/sizeof(*tbCorners[i])); j++) 
        { 
            std::cout << "Element at x[" << i 
                 << "][" << j << "]: "; 
            std::cout << tbCorners[i][j]<<std::endl; 
        } 
    } 

    // Load input image
    Mat img = imread("./resources/init_texture/DSC_9743.JPG", IMREAD_COLOR);
    if(img.empty())
    {
        std::cout << "Could not read the image" << std::endl;
        return 1;
    }

    imshow("Display window", img);

    int k = waitKey(0);
    return 0;
}