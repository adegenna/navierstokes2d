#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <string>
#include <fstream>
#include <istream>
#include <random>
#include <cmath>
#include <Eigen/Dense>
#include <boost/program_options.hpp>
#include "options.hpp"
#include "options_parser.hpp"
#include "Inputfile.hpp"
#include "Grid2d.h"
#include "NavierStokesState.h"
#include "NavierStokesPhysics.h"

using namespace std;
using namespace Eigen;

int main(int argc, char* argv[]) {
  printf("*********** DRIVER PROGRAM FOR 2D NAVIER-STOKES SPECTRAL SOLVER ***********\n\n");

  // Parse input file options
  Options options;
  if (!parseOptions(argc,argv,options)){
   return 0;
  }
  cout << options << endl;

  // Load state
  MatrixXd omega0 = load_csv<MatrixXd>(options.initialvorticityfile);
  
  // Pass parsed program options to simulation
  Grid2d grid(options.xmin,options.xmax,options.ymin,options.ymax,\
			     options.nx,options.ny);
  NavierStokesState state(omega0.array());
  NavierStokesPhysics physics(options, state, grid);
  physics.solve();
  
  return 0;
}
