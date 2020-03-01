#pragma once
#include <ostream>
#include <string>

struct Options {
  std::string initialvorticityfile;
  std::string outputfile;
  std::string integrator;
  double dt;
  int tsteps;
  int tsave;
  double mu;
  double xmin;
  double xmax;
  double ymin;
  double ymax;
  double nx;
  double ny;
  
};

inline std::ostream& operator <<(std::ostream& os, const Options& o){
 os << "initialvorticityfile  = " << o.initialvorticityfile << std::endl
    << "outputfile = " << o.outputfile << std::endl
    << "integrator = " << o.integrator << std::endl
    << "dt         = " << o.dt        << std::endl
    << "tsteps     = " << o.tsteps     << std::endl
    << "tsave      = " << o.tsave      << std::endl
    << "mu         = " << o.mu         << std::endl
    << "xmin       = " << o.xmin       << std::endl
    << "xmax       = " << o.xmax       << std::endl
    << "ymin       = " << o.ymin       << std::endl
    << "ymax       = " << o.ymax       << std::endl
    << "nx         = " << o.nx         << std::endl
    << "ny         = " << o.ny         << std::endl;
   
   return os;
}
