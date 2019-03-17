#ifndef __NAVIERSTOKESSTATE_H__
#define __NAVIERSTOKESSTATE_H__

#include <Eigen/Dense>
#include "options.hpp"

class NavierStokesState {

 public:

  NavierStokesState(const Eigen::ArrayXd& initialstate);
  ~NavierStokesState();
  void set_vorticity(const Eigen::ArrayXd& omega) { W_ = omega; }
  const Eigen::ArrayXd& get_vorticity() const { return W_; }
  void write_vorticity(const std::string& filename) const;
  
 private:

  Eigen::ArrayXd W_;
  
};


#endif
