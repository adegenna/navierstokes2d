#ifndef __FOURIER2D_H__
#define __FOURIER2D_H__

#include <Eigen/Dense>
#include <stdlib.h>
#include <iostream>
#include <memory>

std::shared_ptr< Eigen::MatrixXcd > fft2( std::shared_ptr< Eigen::MatrixXd >  matIn);
std::shared_ptr< Eigen::MatrixXcd > ifft2(std::shared_ptr< Eigen::MatrixXcd > matIn);

#endif
