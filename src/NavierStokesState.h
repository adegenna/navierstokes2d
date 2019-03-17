#ifndef __NAVIERSTOKESSTATE_H__
#define __NAVIERSTOKESSTATE_H__

#include <Eigen/Dense>
#include "options.hpp"

class NavierStokesState {

 public:

  NavierStokesState(const Eigen::ArrayXXd& initialstate);
  ~NavierStokesState();
  void set_vorticity(const Eigen::ArrayXXd& omega) { W_ = omega; }
  const Eigen::ArrayXXd& get_vorticity() const { return W_; }
  void write_vorticity(const std::string& filename) const;
  
 private:

  Eigen::ArrayXXd W_;
  
};


#endif
