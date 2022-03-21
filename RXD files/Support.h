#ifndef SUPPORT_H
#define SUPPORT_H

#include <Eigen/Dense>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>

using namespace std;
using namespace Eigen;
using namespace cv;



MatrixXi convertImgtoMatrix(Mat oImg, int colorChoice);

Mat convertMatrixtoImg(MatrixXi oMatrix);

Matrix3d calcCorrMatrix(MatrixXi rMat, MatrixXi gMat, MatrixXi bMat);

Matrix3d calcCovMatrix(MatrixXi redSam, MatrixXi greenSam, MatrixXi blueSam);

MatrixXi anomalyAnalysis(MatrixXi input, int threshold);

#endif