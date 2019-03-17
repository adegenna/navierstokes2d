#include "NavierStokesPhysics.h"
#include "NavierStokesState.h"
#include "Grid2d.h"
#include "Inputfile.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <istream>
#include <random>
#include <cmath>
#include <boost/program_options.hpp>
#include <iostream>
#include <iterator>
#include <omp.h>
#include <sys/time.h>
#include <eigen3/unsupported/Eigen/FFT>

using namespace std;
using namespace Eigen;
namespace po = boost::program_options;

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

NavierStokesPhysics::NavierStokesPhysics(Options& options, \
					 NavierStokesState& simulation, \
					 Grid2d& grid)
  : options_(options), simulation_(&simulation), grid_(&grid)
{
}

NavierStokesPhysics::~NavierStokesPhysics() {

}

void NavierStokesPhysics::update_fourier_vorticity_crank_nicolson(ArrayXXcd& W_hat, \
								  ArrayXXcd& W_hat_new) {
  ArrayXXcd psi_hat,u_grad_W_hat;
  ArrayXXd u,v,W_x,W_y,u_grad_W,a,b;
  ArrayXXcd kx               = grid_->get_fourier_frequencies_x();
  ArrayXXcd ky               = grid_->get_fourier_frequencies_y();
  ArrayXXd alias_correction  = (grid_->get_fourier_alias_correction()).cast <double> ();
  double mu                 = options_.mu;
  double dt                 = options_.dt;
  
  psi_hat        = -W_hat / laplacian_hat_;
  MatrixXcd tmp1 = (ky * psi_hat).matrix();
  shared_ptr< MatrixXcd > tmpptr1 = make_shared< MatrixXcd > (tmp1);
  u            = ifft2( tmpptr1 )->real();
  MatrixXcd tmp2 = (-kx * psi_hat).matrix();
  shared_ptr< MatrixXcd > tmpptr2 = make_shared< MatrixXcd > (tmp2);
  v            = ifft2(tmpptr2 )->real();
  MatrixXcd tmp3 = (kx * W_hat).matrix();
  shared_ptr< MatrixXcd > tmpptr3 = make_shared< MatrixXcd > (tmp3);
  W_x          = ifft2( tmpptr3 )->real();
  MatrixXcd tmp4 = (ky * W_hat).matrix();
  shared_ptr< MatrixXcd > tmpptr4 = make_shared< MatrixXcd > (tmp4);
  W_y          = ifft2( tmpptr4 )->real();
  u_grad_W     = u * W_x + v * W_y;
  MatrixXd tmp5 = u_grad_W.matrix();
  shared_ptr< MatrixXd > tmpptr5 = make_shared< MatrixXd > (tmp5);
  u_grad_W_hat = *fft2( tmpptr5 );
  u_grad_W_hat = alias_correction * u_grad_W_hat;
  a            = 1./(1./dt - 0.5 * mu * laplacian_hat_);
  b            =    (1./dt + 0.5 * mu * laplacian_hat_);
  W_hat_new    = a * ( b * W_hat - u_grad_W );
  cout << W_hat_new.abs().maxCoeff() << " " << W_hat_new.abs().minCoeff() << endl;

}

void NavierStokesPhysics::solve() {

  ArrayXXcd kx               = grid_->get_fourier_frequencies_x();
  ArrayXXcd ky               = grid_->get_fourier_frequencies_y();
  ArrayXXi alias_correction  = grid_->get_fourier_alias_correction();
  laplacian_hat_            = (kx * kx + ky * ky).real();
  laplacian_hat_(0,0)       = 1;
  ArrayXXd W                 = simulation_->get_vorticity();
  int sampling_period       = options_.tsave;
  MatrixXd tmp              = W.matrix();
  shared_ptr< MatrixXd > tmpptr = make_shared< MatrixXd > (tmp);
  ArrayXXcd W_hat            = *fft2(tmpptr);
  ArrayXXcd W_hat_new;
  
  for (int i=0; i<options_.tsteps; i++) { 
    if ((i % sampling_period) == 0) {
      MatrixXcd tmp2 = W_hat.matrix();
      shared_ptr< MatrixXcd > tmpptr2 = make_shared< MatrixXcd > (tmp2);
      W = ifft2( tmpptr2 )->real();
      simulation_->set_vorticity(W);
      simulation_->write_vorticity(options_.outputfile + "_" + std::to_string(i) + ".csv");
    }
    this->update_fourier_vorticity_crank_nicolson(W_hat,W_hat_new);
    W_hat = W_hat_new;
  }

}
