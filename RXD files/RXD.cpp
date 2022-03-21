#include "Support.h"
#include "CRXD.h"

//This is the RXD method using a correlation matrix
MatrixXi RXDR(MatrixXi redImg, MatrixXi blueImg, MatrixXi greenImg, MatrixXi redSam, MatrixXi greenSam, MatrixXi blueSam) {
    Vector3d u, tmpU;
    Matrix3d R;
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
    R = calcCorrMatrix(redSam, greenSam, blueSam).inverse();
    //cout << "R: \n" << R << endl;
    //equation RXD(r) = (r-u)^T K^-1 (r-u)
    Vector<double, 3> r, tmp;
    int max = 0;
    int min = 255;
    for (int i = 0; i < redImg.rows(); i++) {
        for (int c = 0; c < redImg.cols(); c++) {

            r << redImg(i, c), greenImg(i, c), blueImg(i, c);

            tmp = r - u;
            total = tmp.cwiseAbs().transpose() * R * tmp.cwiseAbs();

            final(i, c) = round(total);
            /*if (i == 5 && c == 5) {
                cout << "[" << redImg(i, c) << "," << greenImg(i, c) << blueImg(i, c) << "]" << endl;
                cout << "r: " << r << endl;
                cout << "u: " << u << endl;
                cout << "tmp: " << tmp << endl;
                cout << "tmp.Trans" << tmp.transpose() << endl;
                cout << "total: " << total << endl;
            }
            if (total > max){
                max = total;
            }
            if (total < min) {
                min = total;
            }*/
        }
    }
    return final;
}

//This is the RXD method using a covariance matrix
MatrixXi RXDK(MatrixXi redImg, MatrixXi blueImg, MatrixXi greenImg, MatrixXi redSam, MatrixXi greenSam, MatrixXi blueSam) {
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