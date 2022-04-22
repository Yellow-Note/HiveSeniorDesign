#ifndef SUPPORT_H
#define SUPPORT_H

#include <Eigen/Dense>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <list>

using namespace std;
using namespace Eigen;
using namespace cv;

struct target
{
	int High[2] = {0,0};//[i,j] or [row,col]
	int Low[2] = {0,0};//[i,j] or [row,col]
	int center[2] = { -1,-1 };
};
struct pix {
	int row =0;
	int col = 0;
};

#define MIN_TAR_SIZE 10
#define BOARD_THICK 3
#define TAR_SPACE 5

MatrixXi convertImgtoMatrix(Mat oImg, int colorChoice);

Mat convertMatrixtoImg(MatrixXi oMatrix);


Matrix3d calcCovMatrix(MatrixXi redSam, MatrixXi greenSam, MatrixXi blueSam);


#endif