#ifndef RXD_H
#define RXD_H

#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

MatrixXi RXDK(MatrixXi redImg, MatrixXi blueImg, MatrixXi greenImg,int threshold);

MatrixXi RXDR(MatrixXi redImg, MatrixXi blueImg, MatrixXi greenImg);

#endif