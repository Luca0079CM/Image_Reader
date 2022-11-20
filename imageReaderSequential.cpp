#include "imageReaderSequential.h"

Mat* images = new Mat[10];

void loadImagesSequential(std::vector<std::string> imageStrings){
    images = new Mat[imageStrings.size()];
    for(int i=0; i<imageStrings.size(); i++)
        images[i] = imread(imageStrings[i]);
}

Mat* getImagesSequential(){
    return images;
}