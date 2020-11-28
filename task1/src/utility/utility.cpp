#include "utility.h"
#include "customGeometry.h"
#include <fstream>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>

using namespace std;
using namespace cv;

namespace utility
{

     // Ease printing of mat objects
     void printMat(string input, Mat image)
     {
          cout << input + " = " << endl
               << format(image, Formatter::FMT_CSV) << endl
               << endl;
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