#include "NavierStokesState.h"
#include "Inputfile.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <istream>
#include <random>
#include <cmath>
#include <iostream>
#include <iterator>
#include <omp.h>
#include <sys/time.h>

using namespace std;
using namespace Eigen;

NavierStokesState::NavierStokesState(const ArrayXXd& initialstate) 
  : W_(initialstate)
{
}

NavierStokesState::~NavierStokesState() {

}

void NavierStokesState::write_vorticity(const std::string& filename) const {
  const static IOFormat CSVFormat(StreamPrecision, DontAlignCols, ", ", "\n");
  ofstream xyout(filename);
  xyout << W_.format(CSVFormat);
  xyout.close();
  
}
