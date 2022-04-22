#include "Support.h"


//Converts from Opencv Mat to Eigen library matrix
MatrixXi convertImgtoMatrix(Mat oImg, int colorChoice) { //0 is Blue, 1 is Green, 2 is Red
	Matrix<int, Dynamic, Dynamic> ImgtoMat;
	ImgtoMat.resize(oImg.rows, oImg.cols);
	//cout << oImg << endl;

	for (int r = 0; r < oImg.rows; r++) {
		for (int c = 0; c < oImg.cols; c++) {
			//cout << oImg.at<Vec3b>(r, c) << endl;
			Vec3b tmpVec = oImg.at<Vec3b>(r, c);

			//cout << "tmpVec(" << r << "," << c << "): " << tmpVec << endl;

			ImgtoMat(r, c) = (int)tmpVec[colorChoice];
			//cout << "ImgtoMat(" << r << "," << c << "): " << ImgtoMat(r,c) << endl;
		}
	}

	return ImgtoMat;
}

//Converts from Eigen library matrix to opencv Mat
Mat convertMatrixtoImg(MatrixXi oMatrix) {
	Mat showImg(oMatrix.rows(), oMatrix.cols(), CV_8UC1);
	for (int r = 0; r < (int)oMatrix.rows(); r++) {
		for (int c = 0; c < (int)oMatrix.cols(); c++) {
			showImg.at<uchar>(r, c) = (uchar)oMatrix(r, c);
		}
	}

	return showImg;
}

//Calculates the covariance matrix of a given image
Matrix3d calcCovMatrix(MatrixXi rMat, MatrixXi gMat, MatrixXi bMat) {

	int totalPix = rMat.rows() * rMat.cols();
	double rMean = rMat.mean(),gMean = gMat.mean(),bMean = bMat.mean();
	double rgSum = 0, rbSum = 0, gbSum = 0;

	for (int i = 0; i < rMat.rows(); i++) {
		for (int j = 0; j < rMat.cols(); j++) {
			int rVal = rMat(i, j);
			int gVal = gMat(i, j);
			int bVal = bMat(i, j);

			rgSum += (rVal - rMean) * (gVal - gMean);
			rbSum += (rVal - rMean) * (bVal - bMean);
			gbSum += (gVal - gMean) * (bVal - bMean);
		}
	}
	//cout << "R Mean: " << rMean << endl;
	//cout << "G Mean: " << gMean << endl;
	//cout << "B Mean: " << bMean << endl;
	double covRG = rgSum / (totalPix - 1);
	double covRB = rbSum / (totalPix - 1);
	double covGB = gbSum / (totalPix - 1);

	Matrix3d covMatrix{
		{ 1    , covRG, covRB },
		{ covRG, 1    , covGB },
		{ covRB, covGB, 1     }
	};
	return covMatrix;
}