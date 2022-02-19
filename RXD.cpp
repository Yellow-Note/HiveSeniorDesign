#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <Eigen/Dense>
#include <iostream>
#include <math.h>
#include <chrono>

using namespace std;
using namespace cv;
using namespace Eigen;

Matrix3d calcCovMatrix(MatrixXi redSam, MatrixXi greenSam, MatrixXi blueSam) {
    int k = 0,size = redSam.cols() * redSam.rows();
    double sum;
    MatrixXi orgPixels;
    orgPixels.resize(size, 3);
    double sampleMeans[3]={0,0,0};

    //reorder image into pixel by spectral band array
    for (int i = 0; i < redSam.rows(); i++) {
        for (int j = 0; j < redSam.cols(); j++) {
            orgPixels.row(k) << redSam(i, j), greenSam(i, j), blueSam(i, j);
            k++;
        }
    }


    //calc sample means
    for (int i = 0; i < 3 ;i++) {
        for (int j = 0; j < size ;j++) {
            sampleMeans[i] += orgPixels(j,i);
        }
        
        sampleMeans[i] /= size;
    }

    //calc each COV
    Matrix3d total;

    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            sum = 0;
            for (int pix = 0; pix < size; pix++) {
                //(x-x^-)(y-y^-)
                sum += (orgPixels(pix, c) - sampleMeans[c]) * (orgPixels(pix, r) - sampleMeans[r]);
            }
            total(r, c) = sum / size;
        }
    }

    //cout << endl << "total\n" << total << endl;

    return total;
}

MatrixXi rxD(MatrixXi redImg, MatrixXi blueImg, MatrixXi greenImg, MatrixXi redSam, MatrixXi greenSam, MatrixXi blueSam) {
    Vector3d u,tmpU;
    Matrix3d K;
    double total;
    Matrix<int, Dynamic, Dynamic> final;
    final.resize(redImg.rows(), redImg.cols());
    double redImgSize = redImg.rows() * redImg.cols();

    int red = 0, green = 0, blue = 0;
    //Calculate the sample mean
    for (int i = 0; i < redSam.rows(); i++) {
        for (int c = 0; c < redSam.cols(); c++) {
            red += redSam(i, c);
            green += greenSam(i, c);
            blue += blueSam(i, c);
        }
    }

    u << red / redImgSize, green / redImgSize, blue / redImgSize;

    //Calculate sample covariance matrix
    K = calcCovMatrix(redSam, greenSam, blueSam).inverse();
    //equation RXD(r) = (r-u)^T K^-1 (r-u)
    Vector<double,3> r, tmp;
    int max = 0;
    int min = 255;
    for (int i = 0; i < redImg.rows(); i++) {
        for (int c = 0; c < redImg.cols(); c++) {
            
            r << redImg(i,c), greenImg(i,c), blueImg(i,c);
            
            tmp = r - u;
            total = tmp.transpose() * K * tmp;

            final(i, c) = round(total);

        }
    }
    
    return final;
}
