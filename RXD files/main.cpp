#include <opencv2/highgui.hpp>
#include <iostream>
#include <math.h>
#include <chrono>
#include "RXD.h"
#include "CRXD.h"
#include "Support.h"

using namespace std;

//This is the RXD algorithm and shows the various steps in different windows as well as the time it took to run
void testRXD(string imgName, int threshold) {
    String window1Name = "Original Image",
        window2Name = "RXD filter with K",
        window3Name = "CRXD filter",
        window4Name = "RXD filter with R",
        window5Name = "RXD filter with K binary",
        window6Name = "RXD filter with R binary",
        window7Name = "CRXD binary";

    Mat image = imread(imgName, IMREAD_REDUCED_COLOR_2);
    //Mat sample = imread("TestBSam.png");

    namedWindow(window1Name, WINDOW_AUTOSIZE);
    imshow(window1Name, image);
    

    MatrixXi bMatrix = convertImgtoMatrix(image, 0);
    MatrixXi gMatrix = convertImgtoMatrix(image, 1);
    MatrixXi rMatrix = convertImgtoMatrix(image, 2);


    //MatrixXi bSamMat = convertImgtoMatrix(sample, 0);
    //MatrixXi gSamMat = convertImgtoMatrix(sample, 1);
    //MatrixXi rSamMat = convertImgtoMatrix(sample, 2);

    MatrixXi RXDKfilterMat, CRXDfilterMat, RXDRfilterMat;
    int avgC = 0, avgRK = 0, avgRR = 0, ms, numTest = 1;
    for (int i = 1; i < numTest + 1; i++) {
        auto start = chrono::high_resolution_clock::now();
        RXDKfilterMat = RXDK(rMatrix, gMatrix, bMatrix, rMatrix, gMatrix, bMatrix);
        auto end = chrono::high_resolution_clock::now();

        ms = round(chrono::duration_cast<chrono::milliseconds>(end - start).count());
        avgRK += ms;

        start = chrono::high_resolution_clock::now();
        RXDRfilterMat = cRXD(rMatrix, gMatrix, bMatrix);
        end = chrono::high_resolution_clock::now();
        ms = round(chrono::duration_cast<chrono::milliseconds>(end - start).count());
        avgRR += ms;

        start = chrono::high_resolution_clock::now();
        CRXDfilterMat = cRXD(rMatrix, gMatrix, bMatrix);
        end = chrono::high_resolution_clock::now();

        ms = round(chrono::duration_cast<chrono::milliseconds>(end - start).count());
        avgC += ms;
        cout << ((double)i / (double)numTest) * 100 << "%" << endl;
    }
    cout << "Avg time for RXD-K: " << avgRK / numTest <<" ms"<< endl;
    cout << "Avg time for RXD-R: " << avgRR / numTest << " ms" << endl;
    cout << "Avg time for CRXD: " << avgC / numTest << " ms" << endl;

    MatrixXi rxdkAnalysis = anomalyAnalysis(RXDKfilterMat, threshold);
    /*MatrixXi crxdAnalysis = anomalyAnalysis(CRXDfilterMat, threshold);
    MatrixXi rxdrAnalysis = anomalyAnalysis(RXDRfilterMat, threshold);*/
    
    Mat RXDKfilterImgAnalysis = convertMatrixtoImg(rxdkAnalysis);
    /*Mat RXDRfilterImgAnalysis = convertMatrixtoImg(rxdrAnalysis);
    Mat CRXDfilterImgAnalysis = convertMatrixtoImg(crxdAnalysis);*/
    Mat RXDKfilterImg = convertMatrixtoImg(RXDKfilterMat);
    Mat RXDRfilterImg = convertMatrixtoImg(RXDRfilterMat);
    Mat CRXDfilterImg = convertMatrixtoImg(CRXDfilterMat);

    namedWindow(window2Name, WINDOW_AUTOSIZE);
    imshow(window2Name, RXDKfilterImg);
    /*namedWindow(window3Name, WINDOW_AUTOSIZE);
    imshow(window3Name, CRXDfilterImg);
    namedWindow(window4Name, WINDOW_AUTOSIZE);
    imshow(window4Name, RXDRfilterImg);*/

    
    namedWindow(window5Name, WINDOW_AUTOSIZE);
    imshow(window5Name, RXDKfilterImgAnalysis);
    /*namedWindow(window6Name, WINDOW_AUTOSIZE);
    imshow(window6Name, RXDRfilterImgAnalysis);
    namedWindow(window7Name, WINDOW_AUTOSIZE);
    imshow(window7Name, CRXDfilterImgAnalysis);*/
    waitKey(0);
    

    //imwrite("RXD-K result.jpg", RXDKfilterImg);
    //imwrite("RXD-R result.jpg", RXDRfilterImg);
    //imwrite("CRXD result.jpg", CRXDfilterImg);
}


int main() {
    string TEST_A = "TestA_Original.jpg",
        TEST_A1 = "TestA1.jpg",
        TEST_A2 = "TestA2.jpg",
        TEST_A3 = "TestA3.jpg",
        TEST_A4 = "TestA4.jpg",
        TEST_A5 = "TestA5.jpg",
        TEST_A6 = "TestA6.jpg",
        TEST_A7 = "TestA7.jpg",
        TEST_B = "TestB.png",
        TEST_C = "TestC.jpg",
        TEST_D = "TestD.jpg",
        TEST_E = "TestE.jpg",
        TEST_E2 = "TestE2.jpg";
    int THRESHOLD = 30;
    
    testRXD(TEST_A5,THRESHOLD);

    return 0;
}