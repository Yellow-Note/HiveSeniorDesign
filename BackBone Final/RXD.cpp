#include "RXD.h"

//Converts from Opencv Mat to Eigen library matrix
MatrixXi convertImgtoMatrix(Mat oImg, int colorChoice) { //0 is Blue, 1 is Green, 2 is Red
	Matrix<int, Dynamic, Dynamic> ImgtoMat;
	ImgtoMat.resize(oImg.rows, oImg.cols);

	for (int r = 0; r < oImg.rows; r++) {
		for (int c = 0; c < oImg.cols; c++) {
			Vec3b tmpVec = oImg.at<Vec3b>(r, c);
			ImgtoMat(r, c) = (int)tmpVec[colorChoice];
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
	//int min = 255, max = -255;
	for (int i = 0; i < input.rows(); i++) {
		for (int j = 0; j < input.cols(); j++) {
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
	//cout << "Min: " << min << endl;
	//cout << "Max: " << max << endl;
	return input;
}

MatrixXi RXDK(MatrixXi redImg, MatrixXi blueImg, MatrixXi greenImg) {
    Vector3d u, tmpU;
    Matrix3d K;
    double total;
    Matrix<int, Dynamic, Dynamic> final;
    final.resize(redImg.rows(), redImg.cols());
    double redImgSize = redImg.rows() * redImg.cols();
    int red = 0, green = 0, blue = 0;

    //Calculate the sample mean
    for (int i = 0; i < redImg.rows(); i++) {
        for (int c = 0; c < redImg.cols(); c++) {
            red += redImg(i, c);
            green += greenImg(i, c);
            blue += blueImg(i, c);
        }
    }

    u << red / redImgSize, green / redImgSize, blue / redImgSize;

    //Calculate sample covariance matrix
    K = calcCovMatrix(redImg, greenImg, blueImg).inverse();
    //equation RXD(r) = (r-u)^T K^-1 (r-u)
    Vector<double, 3> r, tmp;
    int max = 0;
    int min = 255;
    for (int i = 0; i < redImg.rows(); i++) {
        for (int c = 0; c < redImg.cols(); c++) {

            r << redImg(i, c), greenImg(i, c), blueImg(i, c);

            tmp = r - u;
            total = tmp.cwiseAbs().transpose() * K * tmp.cwiseAbs();
            
            final(i, c) = round(abs(total));
        }
    }
    return final;
}

void runRXD(string imgName, int threshold) {

    Mat image = imread(imgName);
    
    MatrixXi bMatrix = convertImgtoMatrix(image, 0);
    MatrixXi gMatrix = convertImgtoMatrix(image, 1);
    MatrixXi rMatrix = convertImgtoMatrix(image, 2);

    MatrixXi RXDKfilterMat, CRXDfilterMat, RXDRfilterMat;
    int avgC = 0, avgRK = 0, avgRR = 0, ms, numTest = 1;
    for (int i = 1; i < numTest + 1; i++) {
        //auto start = chrono::high_resolution_clock::now();
        RXDKfilterMat = RXDK(rMatrix, gMatrix, bMatrix, rMatrix, gMatrix, bMatrix);
        //auto end = chrono::high_resolution_clock::now();
        //ms = round(chrono::duration_cast<chrono::milliseconds>(end - start).count());
        //avgRK += ms;
        //cout << ((double)i / (double)numTest) * 100 << "%" << endl;
    }

    MatrixXi rxdkAnalysis = anomalyAnalysis(RXDKfilterMat, threshold);
    
    Mat RXDKfilterImgAnalysis = convertMatrixtoImg(rxdkAnalysis);

    Mat RXDKfilterImg = convertMatrixtoImg(RXDKfilterMat);

    imwrite("Result.jpg", RXDKfilterImg);
}