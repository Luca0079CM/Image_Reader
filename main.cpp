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
    std::vector<std::string> imageStrings = std::vector<std::string>();

    std::cout << "Current path is " << fs::current_path() << '\n';

    for (auto &p: std::filesystem::directory_iterator(imagePath))
        imageStrings.emplace_back(p.path().string());

    Mat* images;
    loadImagesSequential(imageStrings);
    images = getImagesSequential();
    imshow("Display window", images[0]);
    imshow("Display window", images[1]);
    imshow("Display window", images[2]);

    return 0;
}