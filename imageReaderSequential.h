#ifndef IMAGE_READER_IMAGEREADERSEQUENTIAL_H
#define IMAGE_READER_IMAGEREADERSEQUENTIAL_H

#include <opencv2/opencv.hpp>
using namespace cv;

void loadImagesSequential(std::vector<std::string> imageStrings);
Mat* getImagesSequential();

#endif //IMAGE_READER_IMAGEREADERSEQUENTIAL_H
