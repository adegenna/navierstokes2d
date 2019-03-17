#ifndef __GRID2D_H__
#define __GRID2D_H__

#include <Eigen/Dense>
#include "options.hpp"

class Grid2d {

 public:

  Grid2d();
  Grid2d(double xmin, double xmax, double ymin, double ymax, int nx, int ny);
  ~Grid2d();
  const Eigen::ArrayXXcd& get_fourier_frequencies_x() const {return kx_;}
  const Eigen::ArrayXXcd& get_fourier_frequencies_y() const {return ky_;}
  const Eigen::ArrayXXi& get_fourier_alias_correction() const {return alias_correction_;}
  const Eigen::ArrayXXd& get_grid_xx() const {return XX_;}
  const Eigen::ArrayXXd& get_grid_yy() const {return YY_;}
  
 private:

  void generate_uniform_grid(double xmin, double xmax, double ymin, double ymax, int nx, int ny);
  void generate_fourier_grid(int nx, int ny);
  void generate_alias_correction(int nx, int ny);
  Eigen::ArrayXXd  XX_;
  Eigen::ArrayXXd  YY_;
  Eigen::ArrayXXcd kx_;
  Eigen::ArrayXXcd ky_;
  Eigen::ArrayXXi alias_correction_;

};

#endif
