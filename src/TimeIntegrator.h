#ifndef __TIMEINTEGRATOR_H__
#define __TIMEINTEGRATOR_H__

#include <Eigen/Dense>
#include "options.hpp"
#include "NavierStokesState.h"
#include "NavierStokesPhysics.h"

class TimeIntegrator {

 public:
  TimeIntegrator(Options& options, NavierStokesPhysics& physics, NavierStokesState& state);
  ~TimeIntegrator();
  void rk4(Eigen::ArrayXXcd& W_hat);
  void euler(Eigen::ArrayXXcd& W_hat);
  
 private:
  const Options        options_;
  NavierStokesPhysics* physics_;
  NavierStokesState*   state_;
  void compute_ifft_and_save_current_state(Eigen::ArrayXXcd& W_hat, int i);

};


#endif
