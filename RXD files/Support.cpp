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
	for (int r = 0; r < oMatrix.rows(); r++) {
		for (int c = 0; c < oMatrix.cols(); c++) {
			showImg.at<uchar>(r, c) = (uchar)oMatrix(r, c);
		}
	}

	return showImg;
}

//Calculates the correlation matrix of a given image
Matrix3d calcCorrMatrix(MatrixXi rMat, MatrixXi gMat, MatrixXi bMat) {
	int sumR = 0, sumG = 0, sumB = 0;
	double sumRG = 0, sumGB = 0, sumRB = 0,
		sumRR = 0, sumGG = 0, sumBB = 0;
	int totalPixels = rMat.rows() * rMat.cols();

	//Getting the sums
	for (int i = 0; i < rMat.rows(); i++) {
		for (int j = 0; j < rMat.cols(); j++) {
			//intinilizing new variables to save time on calls still need to test
			int rVal = rMat(i, j);
			int gVal = gMat(i, j);
			int bVal = bMat(i, j);

			sumR += rVal;
			sumG += gVal;
			sumB += bVal;

			sumRG += rVal * gVal;
			sumGB += gVal * bVal;
			sumRB += rVal * bVal;

			sumRR += rVal * rVal;
			sumGG += gVal * gVal;
			sumBB += bVal * bVal;

		}
	}
	/*cout << "sumR: " << sumR << endl;
	cout << "sumB: " << sumB << endl;
	cout << "sumG: " << sumG << endl;

	cout << "sumRG: " << sumRG << endl;
	cout << "sumGB: " << sumGB << endl;
	cout << "sumRB: " << sumRB << endl;

	cout << "sumRR: " << sumRR << endl;
	cout << "sumBB: " << sumBB << endl;
	cout << "sumGG: " << sumGG << endl;
	cout << "total: " << totalPixels << endl;*/
	//calculating corrlation coefficients
	double corrRG = (totalPixels * sumRG - (sumR * sumG)) /
		sqrt((totalPixels * sumRR - (sumR * sumR)) * (totalPixels * sumGG - (sumG * sumG)));


	double corrRB = (totalPixels * sumRB - (sumR * sumB)) /
		sqrt((totalPixels * sumRR - (sumR * sumR)) * (totalPixels * sumBB - (sumB * sumB)));


	double corrGB = (totalPixels * sumGB - (sumG * sumB)) /
		sqrt((totalPixels * sumGG - (sumG * sumG)) * (totalPixels * sumBB - (sumB * sumB)));
	//cout << "R Mean: " << sumR / totalPixels << endl;
	//cout << "G Mean: " << sumG / totalPixels << endl;
	//cout << "B Mean: " << sumB / totalPixels << endl;
	/*cout << "corrRG: " << corrRG << endl;
	cout << "corrRB: " << corrRB << endl;
	cout << "corrGB: " << corrGB << endl;*/
	Matrix3d corrMatrix{
		{ 1     , corrRG, corrRB},
		{ corrRG, 1     , corrGB},
		{ corrRB, corrGB, 1     }
	};
	/*cout << corrMatrix << endl;*/
	return corrMatrix;
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

//Analyzes the matrix repesentation of the image and uses a threshold to determine anomlies
MatrixXi anomalyAnalysis(MatrixXi input,int threshold) {
	int min = 255, max = -255;
	for (int i = 0; i < input.rows(); i++) {
		for (int j = 0; j < input.cols(); j++) {

			if (i == 200 && j == 205) {
				cout << "Final: " << input(i, j) << endl;
			}
			
			if (input(i, j) > threshold) {
				input(i, j) = 255;
			}
			else {
				input(i, j) = 0;
			}
			if (input(i, j) > max) {
				max = input(i, j);
			}
			if (input(i, j) < min) {
				min = input(i, j);
			}
			
		}
	}
	cout << "Min: " << min << endl;
	cout << "Max: " << max << endl;
	return input;
}
