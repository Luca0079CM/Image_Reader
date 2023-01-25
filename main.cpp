#include <iostream>
#include <opencv2/opencv.hpp>
#include <chrono>
#include <filesystem>
#include <fstream>

#include "imageReaderSequential.h"
#include "imageReaderParallel.h"

#define nTest 10
#define subsetDimension 200

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

    // Si considera un sottoinsieme di dimensione subsetDimension di immagini
    std::vector<std::string> imageStringsSubset(
            imageStrings.begin(),imageStrings.begin() + subsetDimension);

    int sequentialTime = 0;

    // Caricamento sequenziale delle immagini
    for (int i = 0; i < nTest; i++) {
        Mat *images;
        auto start = std::chrono::system_clock::now();
        loadImagesSequential(imageStringsSubset);
        images = getImagesSequential();
        auto end = std::chrono::system_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        sequentialTime += elapsed.count();
        delete[] images;
    }
    cout << "Tempo medio trascorso per il caricamento delle immagini in modo sequenziale: "
         << sequentialTime / nTest << "\n";
    logFile << "Tempo medio trascorso per il caricamento delle immagini in modo sequenziale:\n"
            << sequentialTime / nTest << "\n";

    logFile << "\nTempo medio trascorso per il caricamento delle immagini in modo parallelo:\n";
    for(int k = 2; k < (maxThreads + 1); k++) {
        int parallelTime = 0;
        // Cambia il numero di thread
        omp_set_num_threads(k);
        // Caricamento parallelo delle immagini
        for (int i = 0; i < nTest; i++) {
            Mat *images;
            auto start = std::chrono::system_clock::now();
            loadImagesParallel(imageStringsSubset);
            images = getImagesParallel();
            auto end = std::chrono::system_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
            parallelTime += elapsed.count();
            delete[] images;
        }
        cout << "Tempo medio trascorso per il caricamento delle immagini in modo parallelo: "
            << parallelTime / nTest << "\n";
        logFile << parallelTime / nTest << "\n";
    }

    // Tests in base all'aumentare del numero di immagini
    ofstream logFile2("log2.txt");

    // Test con il caricamento sequenziale, aumentando ogni volta di 25 immagini l'insieme da caricare
    logFile2 << "Tempi del caricamento sequenziale, aumentando di 25 immagini ogni volta:\n";
    for (int i = (int)imageStrings.size()/10; i < imageStrings.size(); i+=25) {
        Mat *images;
        sequentialTime = 0;
        std::vector<std::string> imageStringsTest(imageStrings.begin(),imageStrings.begin() + i);
        auto start = std::chrono::system_clock::now();
        loadImagesSequential(imageStringsTest);
        images = getImagesSequential();
        auto end = std::chrono::system_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        sequentialTime += elapsed.count();
        delete[] images;
        cout << "Tempo trascorso per il caricamento di " << i << " immagini in modo sequenziale: "
             << sequentialTime << "\n";
        logFile2 << sequentialTime << "\n";
    }

    // Cambia il numero di thread settandoli al massimo
    omp_set_num_threads(maxThreads);
    logFile2 << "\nTempi del caricamento parallelo, aumentando di 25 immagini ogni volta:\n";
    // Caricamento parallelo delle immagini
    for (int i = (int)imageStrings.size()/10; i < imageStrings.size(); i+=25) {
        int parallelTime = 0;
        Mat *images;
        std::vector<std::string> imageStringsTest(imageStrings.begin(),imageStrings.begin() + i);
        auto start = std::chrono::system_clock::now();
        loadImagesParallel(imageStringsTest);
        images = getImagesParallel();
        auto end = std::chrono::system_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        parallelTime += elapsed.count();
        delete[] images;
        cout << "Tempo trascorso per il caricamento di " << i << " immagini in modo parallelo: "
             << parallelTime << "\n";
        logFile2 << parallelTime<< "\n";
    }


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

    logFile.close();
    logFile2.close();
    return 0;
}