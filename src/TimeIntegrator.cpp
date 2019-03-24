#include "TimeIntegrator.h"
#include "NavierStokesPhysics.h"
#include "Fourier2d.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <istream>
#include <cmath>
#include <iostream>
#include <iterator>
#include <omp.h>
#include <sys/time.h>
#include <eigen3/unsupported/Eigen/FFT>
#include <boost/program_options.hpp>

using namespace std;
using namespace Eigen;
namespace po = boost::program_options;

TimeIntegrator::TimeIntegrator(Options& options, \
			       NavierStokesPhysics& physics,	\
			       NavierStokesState&   state)
  : options_(options) , physics_(&physics) , state_(&state)
{
}

TimeIntegrator::~TimeIntegrator() {

}

void TimeIntegrator::compute_ifft_and_save_current_state(ArrayXXcd& W_hat, int i) {
  MatrixXcd tmp2 = W_hat.matrix();
  auto tmpptr2   = make_shared< MatrixXcd > (tmp2);
  ArrayXXd W     = ifft2( tmpptr2 )->real();
  state_->set_vorticity(W);
  state_->write_vorticity(options_.outputfile + "_" + std::to_string(i) + ".csv");
}

void TimeIntegrator::rk4(ArrayXXcd& W_hat) {

  double dt = options_.dt;
  for (int i=0; i<options_.tsteps; i++) {

    if ((i % options_.tsave) == 0)
      this->compute_ifft_and_save_current_state(W_hat,i);

    ArrayXXcd k1 = *(physics_->rhs_fourier_vorticity(W_hat));
    ArrayXXcd k2 = *(physics_->rhs_fourier_vorticity(W_hat + 0.5*dt*k1));
    ArrayXXcd k3 = *(physics_->rhs_fourier_vorticity(W_hat + 0.5*dt*k2));
    ArrayXXcd k4 = *(physics_->rhs_fourier_vorticity(W_hat +     dt*k3));
    W_hat       += (1./6.) * dt * (k1 + 2*k2 + 2*k3 + k4);

  }

}
