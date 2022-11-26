#include <iostream>
#include <opencv2/opencv.hpp>
#include <chrono>
#include <filesystem>
#include <fstream>

#include "imageReaderSequential.h"
#include "imageReaderParallel.h"

#define nTest 1

using namespace cv;
using namespace std;
namespace fs = std::filesystem;

int main() {
    String imagePath = "/home/luca/CLionProjects/Image_Reader/images/";
    ofstream logFile("log.txt");
    std::vector<std::string> imageStrings = std::vector<std::string>();
    int maxThreads = omp_get_max_threads();
    // Trova i nomi delle immagini all'interno della cartella
    for (auto &p: std::filesystem::directory_iterator(imagePath))
        imageStrings.emplace_back(p.path().string());

    Mat *images;
    int sequentialTime = 0;

    // Caricamento sequenziale delle immagini
    for (int i = 0; i < nTest; i++) {
        auto start = std::chrono::system_clock::now();
        loadImagesSequential(imageStrings);
        images = getImagesSequential();
        auto end = std::chrono::system_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        sequentialTime += elapsed.count();
    }
    cout << "Tempo medio trascorso per il caricamento delle immagini in modo sequenziale: "
         << sequentialTime / nTest << "\n";
    logFile << sequentialTime / nTest << "\n";

    for(int k = 2; k < (maxThreads + 1); k++) {
        int parallelTime = 0;
        // Cambia il numero di thread
        omp_set_num_threads(k);

        // Caricamento parallelo delle immagini
        for (int i = 0; i < nTest; i++) {
            auto start = std::chrono::system_clock::now();
            loadImagesParallel(imageStrings);
            images = getImagesSequential();
            auto end = std::chrono::system_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
            parallelTime += elapsed.count();
        }
        cout << "Tempo medio trascorso per il caricamento delle immagini in modo parallelo: "
            << parallelTime / nTest << "\n";
        logFile << parallelTime / nTest << "\n";
    }
    logFile.close();
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