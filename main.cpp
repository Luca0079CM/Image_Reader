#include <iostream>
#include <opencv2/opencv.hpp>
#include <chrono>
#include <unistd.h>
#include <filesystem>

#include "imageReaderSequential.h"
#include "imageReaderParallel.h"

using namespace cv;
using namespace std;
namespace fs = std::filesystem;

int main() {
    String imagePath = "/home/luca/CLionProjects/Image_Reader/images/";
    std::vector<std::string> imgNames = std::vector<std::string>();

    std::cout << "Current path is " << fs::current_path() << '\n';

    Mat* images;
    loadImagesSequential(imagePath);
    images = getImagesSequential();
    //imshow("Display window", images[0]);


    return 0;
}