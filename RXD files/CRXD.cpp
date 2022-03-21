#include "CRXD.h"
#include "Support.h"

//This is the casual RXD method //NOT FULLY FUCTIONTING YET//
MatrixXi cRXD(MatrixXi rMat, MatrixXi gMat, MatrixXi bMat) {
	Matrix <int, Dynamic, Dynamic> final;
	final.resize(rMat.rows(), rMat.cols());
	Vector<double, 3> r;
	double total;

	//Calculate correlation matrix
	Matrix3d R = calcCorrMatrix(rMat, gMat, bMat).inverse();
	//cout << "R: \n" << R << endl;
	for (int i = 0; i < rMat.rows(); i++) {
		for (int j = 0; j < rMat.cols(); j++) {
			r << rMat(i, j), gMat(i, j), bMat(i, j);
			total = r.transpose() * R * r;

			final(i, j) = round(total);
		}
	}
	return final;
}