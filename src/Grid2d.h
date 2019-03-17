#ifndef __GRID2D_H__
#define __GRID2D_H__

#include <Eigen/Dense>
#include "options.hpp"

class Grid2d {

 public:

  Grid2d();
  Grid2d(double xmin, double xmax, double ymin, double ymax, int nx, int ny);
  ~Grid2d();
  const Eigen::ArrayXcd& get_fourier_frequencies_x() const {return kx_;}
  const Eigen::ArrayXcd& get_fourier_frequencies_y() const {return ky_;}
  const Eigen::ArrayXi& get_fourier_alias_correction() const {return alias_correction_;}
  const Eigen::ArrayXd& get_grid_xx() const {return XX_;}
  const Eigen::ArrayXd& get_grid_yy() const {return YY_;}
  
 private:

  void generate_uniform_grid(double xmin, double xmax, double ymin, double ymax, int nx, int ny);
  void generate_fourier_grid(int nx, int ny);
  void generate_alias_correction(int nx, int ny);
  Eigen::ArrayXd  XX_;
  Eigen::ArrayXd  YY_;
  Eigen::ArrayXcd kx_;
  Eigen::ArrayXcd ky_;
  Eigen::ArrayXi alias_correction_;

};

#endif
