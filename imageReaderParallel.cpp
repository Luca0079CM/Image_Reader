#include "imageReaderParallel.h"
Mat* images1;

void loadImagesParallel(std::vector<std::string> imageStrings){
    int tid;
    tid = -1;

#pragma omp parallel private(tid)
    {
#ifdef _OPENMP
        /* Obtain thread number */
        tid = omp_get_thread_num();
        printf("Hello World from thread = %d\n", tid);
#endif
    }

    // Parallel loading of images1
    images1 = new Mat[imageStrings.size()];
#pragma omp parallel for
    for(int i=0; i<imageStrings.size(); i++)
        images1[i] = imread(imageStrings[i]);
}

Mat* getImagesParallel(){
    return images1;
}