#include "imageReaderSequential.h"

Mat* images;

void loadImagesSequential(std::vector<std::string> imageStrings){
    images = new Mat[imageStrings.size()];
    for(int i=0; i<imageStrings.size(); i++)
        images[i] = imread(imageStrings[i]);
}

Mat* getImagesSequential(){
    return images;
}