#ifndef IMAGE_READER_IMAGEREADERPARALLEL_H
#define IMAGE_READER_IMAGEREADERPARALLEL_H

#include <opencv2/opencv.hpp>
#include <omp.h>

using namespace cv;

void loadImagesParallel(std::vector<std::string> imageStrings);
Mat* getImagesParallel();

#endif //IMAGE_READER_IMAGEREADERPARALLEL_H
