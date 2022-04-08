#include "RXD.h"

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

	//calculating corrlation coefficients
	double corrRG = (totalPixels * sumRG - (sumR * sumG)) /
		sqrt((totalPixels * sumRR - (sumR * sumR)) * (totalPixels * sumGG - (sumG * sumG)));


	double corrRB = (totalPixels * sumRB - (sumR * sumB)) /
		sqrt((totalPixels * sumRR - (sumR * sumR)) * (totalPixels * sumBB - (sumB * sumB)));


	double corrGB = (totalPixels * sumGB - (sumG * sumB)) /
		sqrt((totalPixels * sumGG - (sumG * sumG)) * (totalPixels * sumBB - (sumB * sumB)));
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

MatrixXi RXDK(MatrixXi redImg, MatrixXi blueImg, MatrixXi greenImg) {

    Vector3d u, tmpU;
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
    //cout << "K: \n" << K << endl;
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
            if (i == 200 && c == 205) {
               /* cout << "r: " << r << endl;
                cout << "u: " << u << endl;
                cout << "tmp: " << tmp.cwiseAbs() << endl;
                cout << "tmp.Trans: " << tmp.cwiseAbs().transpose() << endl;
                cout << "K: " << K << endl;
                cout << "total: " << abs(total) << endl<<endl;*/
            }
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