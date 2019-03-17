#ifndef __NAVIERSTOKESPHYSICS_H__
#define __NAVIERSTOKESPHYSICS_H__

#include <Eigen/Dense>
#include "options.hpp"
#include "NavierStokesState.h"
#include "Grid2d.h"
#include <iostream>
#include <memory>

class NavierStokesPhysics {

 public:

  NavierStokesPhysics(Options& options, NavierStokesState& simulation, Grid2d& grid);
  ~NavierStokesPhysics();
  void solve();
  
 private:
  
  void update_fourier_vorticity_crank_nicolson(Eigen::ArrayXXcd& W_hat,\
					       Eigen::ArrayXXcd& W_hat_new);
  const Options      options_;
  NavierStokesState* simulation_;
  Grid2d*            grid_;
  Eigen::ArrayXXd     laplacian_hat_;
  
  
};


#endif