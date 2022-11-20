#include "imageReaderSequential.h"

Mat* images = new Mat[10];

void loadImagesSequential(String s){
    images[0] = imread(s);
}

Mat* getImagesSequential(){
    return images;
}