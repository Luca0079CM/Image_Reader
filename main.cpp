#include <iostream>
#include <opencv2/opencv.hpp>
#include <chrono>
#include <filesystem>
#include <fstream>

#include "imageReaderSequential.h"
#include "imageReaderParallel.h"

#define nTest 10
#define subsetDimension 500

using namespace cv;
using namespace std;
namespace fs = std::filesystem;

int main() {
    String imagePath = "images/";
    ofstream logFile("log.txt");
    vector<string> imageStrings = vector<string>();
    int maxThreads = omp_get_max_threads();
    // Trova i nomi delle immagini all'interno della cartella
    for (auto &p: filesystem::directory_iterator(imagePath))
        imageStrings.emplace_back(p.path().string());

    // Si considera un sottoinsieme di dimensione subsetDimension di immagini
    vector<string> imageStringsSubset(
            imageStrings.begin(),imageStrings.begin() + subsetDimension);

    int sequentialTime = 0;
    // Caricamento sequenziale delle immagini
    for (int i = 0; i < nTest; i++) {
        Mat *images;
        auto start = chrono::system_clock::now();
        loadImagesSequential(imageStringsSubset);
        images = getImagesSequential();
        auto end = chrono::system_clock::now();
        auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - start);
        sequentialTime += elapsed.count();
        delete[] images;
    }
    cout << "Tempo medio trascorso per il caricamento delle immagini in modo sequenziale: "
         << sequentialTime / nTest << "\n";
    logFile << "Tempo medio trascorso per il caricamento delle immagini in modo sequenziale:\n"
            << sequentialTime / nTest << "\n";

    logFile << "\nTempo medio trascorso per il caricamento delle immagini in modo parallelo:\n";
    for(int k = 2; k < (4*maxThreads + 1); k++) {
        int parallelTime = 0;
        // Cambia il numero di thread
        omp_set_num_threads(k);
        // Caricamento parallelo delle immagini
        for (int i = 0; i < nTest; i++) {
            Mat *images;
            auto start = chrono::system_clock::now();
            loadImagesParallel(imageStringsSubset);
            images = getImagesParallel();
            auto end = chrono::system_clock::now();
            auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - start);
            parallelTime += elapsed.count();
            delete[] images;
        }
        cout << "Tempo medio trascorso per il caricamento delle immagini in modo parallelo: "
            << parallelTime / nTest << "\n";
        logFile << parallelTime / nTest << "\n";
    }

    // Tests in base all'aumentare del numero di immagini
    ofstream logFile2("log2.txt");

    // Test con il caricamento sequenziale, aumentando ogni volta di 50 immagini l'insieme da caricare
    logFile2 << "Tempi del caricamento sequenziale, aumentando di 50 immagini ogni volta:\n";
    for (int i = (int)imageStrings.size()/2.5; i < imageStrings.size(); i+=50) {
        sequentialTime = 0;
        for (int j = 0; j < nTest; j++) {
            Mat *images;
            vector<string> imageStringsTest(imageStrings.begin(), imageStrings.begin() + i);
            auto start = chrono::system_clock::now();
            loadImagesSequential(imageStringsTest);
            images = getImagesSequential();
            auto end = chrono::system_clock::now();
            auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - start);
            sequentialTime += elapsed.count();
            delete[] images;
        }
        cout << "Tempo trascorso per il caricamento di " << i << " immagini in modo sequenziale: "
             << sequentialTime/nTest << "\n";
        logFile2 << sequentialTime/nTest << "\n";
    }

    // Cambia il numero di thread settandoli al massimo
    omp_set_num_threads(maxThreads);
    logFile2 << "\nTempi del caricamento parallelo, aumentando di 50 immagini ogni volta:\n";
    // Caricamento parallelo delle immagini
    for (int i = (int)imageStrings.size()/2.5; i < imageStrings.size(); i+=50) {
        int parallelTime = 0;
        for (int j = 0; j < nTest; j++) {
            Mat *images;
            vector<string> imageStringsTest(imageStrings.begin(), imageStrings.begin() + i);
            auto start = chrono::system_clock::now();
            loadImagesParallel(imageStringsTest);
            images = getImagesParallel();
            auto end = chrono::system_clock::now();
            auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - start);
            parallelTime += elapsed.count();
            delete[] images;
        }
        cout << "Tempo trascorso per il caricamento di " << i << " immagini in modo parallelo: "
             << parallelTime/nTest << "\n";
        logFile2 << parallelTime/nTest << "\n";
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