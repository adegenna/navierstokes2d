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
  std::shared_ptr< Eigen::ArrayXXcd > rhs_fourier_vorticity( const Eigen::ArrayXXcd& W_hat );
  Eigen::ArrayXXcd& get_current_fourier_vorticity() { return W_hat_; }
  void solve();
  
 private:

  std::shared_ptr< Eigen::ArrayXXcd > update_fourier_vorticity_crank_nicolson( Eigen::ArrayXXcd& W_hat );
  const Options      options_;
  NavierStokesState* simulation_;
  Grid2d*            grid_;
  Eigen::ArrayXXcd   laplacian_hat_;
  Eigen::ArrayXXcd   W_hat_;
  
};


#endif
