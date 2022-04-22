#include "Support.h"

//This is the RXD method using a covariance matrix
MatrixXi RXDK(MatrixXi redImg, MatrixXi blueImg, MatrixXi greenImg, int threshold) {
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
    int max = -5000;
    int min = 5000;
    for (int i = 0; i < redImg.rows(); i++) {
        for (int c = 0; c < redImg.cols(); c++) {

            r << redImg(i, c), greenImg(i, c), blueImg(i, c);

            tmp = r - u;
            total = tmp.cwiseAbs().transpose() * K * tmp.cwiseAbs();
            //cout << round(abs(total)) << endl;
            if (round(abs(total)) < threshold) {
                final(i, c) = 0;
            }
            else {
                final(i, c) = 255;
            }
        }
    }
    return final;
}