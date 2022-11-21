#include <iostream>
#include <opencv2/opencv.hpp>
#include <chrono>
#include <filesystem>

#include "imageReaderSequential.h"
#include "imageReaderParallel.h"

using namespace cv;
using namespace std;
namespace fs = std::filesystem;

int main() {
    String imagePath = "/home/luca/CLionProjects/Image_Reader/images/";
    std::vector<std::string> imageStrings = std::vector<std::string>();
    // Trova i nomi delle immagini all'interno della cartella
    for (auto &p: std::filesystem::directory_iterator(imagePath))
        imageStrings.emplace_back(p.path().string());

    Mat *images;
    int nTest = 2;
    int sequentialTime = 0;
    int parallelTime = 0;

    // Caricamento sequenziale delle immagini
    for (int i = 0; i < nTest; i++) {
        auto start = std::chrono::system_clock::now();
        loadImagesSequential(imageStrings);
        images = getImagesSequential();
        auto end = std::chrono::system_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        sequentialTime += elapsed.count();
    }
    cout << "Tempo medio trascorso per il caricamento delle immagini in modo sequenziale: "<<sequentialTime/nTest<<"\n";

    // Caricamento parallelo delle immagini
    for (int i = 0; i < nTest; i++) {
        auto start = std::chrono::system_clock::now();
        loadImagesParallel(imageStrings);
        images = getImagesSequential();
        auto end = std::chrono::system_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        parallelTime += elapsed.count();
    }
    cout << "Tempo medio trascorso per il caricamento delle immagini in modo parallelo: " << parallelTime / nTest;


    // Test per visualizzare immagini
    /*
    String windowName = "Display window";
    imshow(windowName, images2[30]);
    waitKey(0);
    destroyWindow(windowName);
    imshow(windowName, images2[45]);
    waitKey(0);
    destroyWindow(windowName);
    imshow(windowName, images2[77]);
    waitKey(0);
    destroyWindow(windowName);
     */
    return 0;
}