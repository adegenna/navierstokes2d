#include <omp.h>
#include <sys/time.h>
#include <Eigen/Dense>
#include "Grid2d.h"

using namespace std;
using namespace Eigen;

Grid2d::Grid2d() {
  
}

Grid2d::Grid2d(double xmin, double xmax, double ymin, double ymax, \
				   int nx, int ny) {
  this->generate_uniform_grid(xmin,xmax,ymin,ymax,nx,ny);
}

Grid2d::~Grid2d() {

}

void Grid2d::generate_uniform_grid(double xmin, double xmax, double ymin, double ymax, \
				   int nx, int ny) {
  XX_.resize(nx,ny);
  YY_.resize(nx,ny);
  double dx = (xmax-xmin)/float(nx-1);
  double dy = (ymax-ymin)/float(ny-1);
  for (int j=0; j<ny; j++) {
    for (int i=0; i<nx; i++) {
      XX_[i,j] = dx*j;
      YY_[i,j] = dy*i;
    }
  }
}

void Grid2d::generate_fourier_grid(int nx, int ny) {
  kx_.resize(nx,ny);
  ky_.resize(nx,ny);
  alias_correction_.resize(nx,ny);

  // Generate x-frequency grid
  for (int j=0; j<nx/2+1; j++)
    kx_.col(j) = j;
  int start_j;
  if ((nx % 2) == 0)
    start_j = -(nx/2 - 1);
  else
    start_j = -nx/2;
  for (int j=nx/2+1; j<nx; j++)
    kx_.col(j) = start_j + j;

  // Generate y-frequency grid
  for (int i=0; i<ny/2+1; i++)
    ky_.row(i) = i;
  int start_i;
  if ((ny % 2) == 0)
    start_i = -(ny/2 - 1);
  else
    start_i = -ny/2;
  for (int i=ny/2+1; i<ny; i++)
    ky_.row(i) = start_i + i;

  // Generate aliasing-correction mask
  this->generate_alias_correction(nx,ny);
}

void Grid2d::generate_alias_correction(int nx, int ny) {
  double frequency_cutoff_x = 1. * nx / 3.;
  double frequency_cutoff_y = 1. * ny / 3.;
  alias_correction_.resize(nx,ny);
  for (int j=0; j<ny; j++) {
    for (int i=0; i<nx; i++) {
      if ((std::abs(kx_[i,j]) < frequency_cutoff_x) & \
	  (std::abs(ky_[i,j]) < frequency_cutoff_y))
	alias_correction_[i,j] = 0;
      else
	alias_correction_[i,j] = 1;
    }
  }

}
