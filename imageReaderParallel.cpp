#include "imageReaderParallel.h"
Mat* images1;

void loadImagesParallel(std::vector<std::string> imageStrings) {
    int nthreads, tid;
    tid = -1;

#pragma omp parallel private(nthreads, tid)
    {
        // Parallel loading of images1
        images1 = new Mat[imageStrings.size()];
#pragma omp for
        for (int i = 0; i < imageStrings.size(); i++)
            images1[i] = imread(imageStrings[i]);
    }
}

Mat* getImagesParallel(){
    return images1;
}