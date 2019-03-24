#include "Fourier2d.h"
#include <stdio.h>
#include <fstream>
#include <istream>
#include <omp.h>
#include <eigen3/unsupported/Eigen/FFT>

using namespace std;
using namespace Eigen;

shared_ptr< MatrixXcd > fft2(shared_ptr< MatrixXd > matIn) {

  const int nRows = matIn->rows();
  const int nCols = matIn->cols();
  FFT< double > fft;
  shared_ptr< MatrixXcd > matOut = make_shared< MatrixXcd > (nRows, nCols);
  
  for (int k = 0; k < nRows; ++k) {
    VectorXcd tmpOut(nCols);
    fft.fwd(tmpOut, matIn->row(k));
    matOut->row(k) = tmpOut;
  }

  for (int k = 0; k < matOut->cols(); ++k) {
    VectorXcd tmpOut(nRows);
    fft.fwd(tmpOut, matOut->col(k));
    matOut->col(k) = tmpOut;
  }
  
  return matOut;
}

shared_ptr< MatrixXcd > ifft2(shared_ptr< MatrixXcd > matIn) {

  const int nRows = matIn->rows();
  const int nCols = matIn->cols();
  FFT< double > ifft;
  shared_ptr< MatrixXcd > matOut = make_shared< MatrixXcd > (nRows, nCols);
  
  for (int k = 0; k < nRows; ++k) {
    VectorXcd tmpOut(nCols);
    ifft.inv(tmpOut, matIn->row(k));
    matOut->row(k) = tmpOut;
  }

  for (int k = 0; k < matOut->cols(); ++k) {
    VectorXcd tmpOut(nRows);
    ifft.inv(tmpOut, matOut->col(k));
    matOut->col(k) = tmpOut;
  }
  
  return matOut;
}
