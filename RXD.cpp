Mat rxD(Mat oImg, Mat sample) {
    Vector3d u,tmpU;
    Matrix3d K;
    double total;
    Matrix<int, Dynamic, Dynamic, RowMajor> final;
    final.resize(oImg.rows, oImg.cols);
    double oImgSize = oImg.rows * oImg.cols;

    Map<Matrix<char, Dynamic, Dynamic, RowMajor>, Unaligned, Stride<3, 1>> redImg(oImg.ptr<char>(), oImg.rows, oImg.cols);
    Map<Matrix<char, Dynamic, Dynamic, RowMajor>, Unaligned, Stride<3, 1>> greenImg(oImg.ptr<char>() + 1, oImg.rows, oImg.cols);
    Map<Matrix<char, Dynamic, Dynamic, RowMajor>, Unaligned, Stride<3, 1>> blueImg(oImg.ptr<char>() + 2, oImg.rows, oImg.cols);

    Map<Matrix<char, Dynamic, Dynamic, RowMajor>, Unaligned, Stride<3, 1>> redImgSam(sample.ptr<char>(), oImg.rows, oImg.cols);
    Map<Matrix<char, Dynamic, Dynamic, RowMajor>, Unaligned, Stride<3, 1>> greenImgSam(sample.ptr<char>() + 1, oImg.rows, oImg.cols);
    Map<Matrix<char, Dynamic, Dynamic, RowMajor>, Unaligned, Stride<3, 1>> blueImgSam(sample.ptr<char>() + 2, oImg.rows, oImg.cols);

    int red = 0, green = 0, blue = 0;
    //Calculate the sample mean
    for (int i = 0; i < sample.rows; i++) {
        for (int c = 0; c < sample.cols; c++) {
            red += redImgSam(i, c);
            green += greenImgSam(i, c);
            blue += blueImgSam(i, c);
        }
    }

    u << red / oImgSize, green / oImgSize, blue / oImgSize;

    //Calculate sample covariance matrix
    K = calcCovMatrix(sample);// .inverse();
    cout << "K: \n" << K << endl;
    //equation RXD(r) = (r-u)^T K^-1 (r-u)
    Vector<double,3> r, tmp;
    int max = 0;
    int min = 255;
    for (int i = 0; i < oImg.rows; i++) {
        for (int c = 0; c < oImg.cols; c++) {
            
            r << redImg(i,c), greenImg(i,c), blueImg(i,c);
            
            tmp = r - u;
            total = tmp.transpose() * K * tmp;

            final(i, c) = round(total);
        }
    }
    Mat tmpImg(final.rows(), final.cols(), CV_32SC1, final.data());
    return tmpImg;
}