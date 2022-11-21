#include "imageReaderParallel.h"

Mat* images1;

void loadImagesParallel(std::vector<std::string> imageStrings){
    int nthreads, tid;
    tid = -1;

#ifdef _OPENMP
    std::cout << "_OPENMP defined" << std::endl;
    std::cout << "Num processors (Phys+HT): " << omp_get_num_procs() << std::endl;
#endif

    printf("Global copy of tid before threads execution = %d\n\n", tid);

/* Fork a team of threads giving them their own copies of variables */
#pragma omp parallel private(nthreads, tid)
    {

#ifdef _OPENMP
        /* Obtain thread number */
        tid = omp_get_thread_num();
        printf("Hello World from thread = %d\n", tid);

        /* Only master thread does this */
        if (tid == 0) {
            nthreads = omp_get_num_threads();
            printf("Master thread - Number of threads = %d\n", nthreads);
        }
#endif

        tid += 100;
        printf("Local copy of tid = %d\n", tid);

    }
    /* All threads join master thread and are destroyed */
    printf("\nGlobal copy of tid after threads execution = %d\n", tid);

    // Parallel loading of images2
    images1 = new Mat[imageStrings.size()];
#pragma omp parallel for
    for(int i=0; i<imageStrings.size(); i++)
        images1[i] = imread(imageStrings[i]);
}

Mat* getImagesParallel(){
    return images1;
}