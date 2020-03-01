#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <boost/program_options.hpp>
#include "options.hpp"

namespace po = boost::program_options;

bool parseOptions(int argc, char *argv[], Options& options){

  std::string input_file;

  // Declare the supported options.
  po::options_description desc("Allowed options");
  desc.add_options()
    ("help", "produce help message")
    ("initialvorticityfile"        , po::value<std::string>(&options.initialvorticityfile) , "Set intial vorticity filename")
    ("outputfile"       , po::value<std::string>(&options.outputfile) , "Set output filename")
    ("integrator"       , po::value<std::string>(&options.integrator) , "Set time integrator type")
    ("dt"               , po::value<double>(&options.dt) , "Set timestep")
    ("tsteps"           , po::value<int>(&options.tsteps)     , "Set number of time steps")
    ("tsave"            , po::value<int>(&options.tsave)      , "Set checkpoint for saving")
    ("mu"               , po::value<double>(&options.mu)      , "Set viscosity")
    ("xmin"            , po::value<double>(&options.xmin)      , "Set xmin")
    ("xmax"            , po::value<double>(&options.xmax)      , "Set xmax")
    ("ymin"            , po::value<double>(&options.ymin)      , "Set ymin")
    ("ymax"            , po::value<double>(&options.ymax)      , "Set ymax")
    ("nx"              , po::value<double>(&options.nx)      , "Set nx")
    ("ny"              , po::value<double>(&options.ny)      , "Set ny")

    ("config_file"      , po::value<std::string>(&input_file), "Configuration input file.")
  ;

  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, desc), vm);
  po::notify(vm);

  if (vm.count("help")) {
      std::cout << desc << "\n";
      return false;
  }

  std::ifstream ifs(input_file.c_str());
  po::store(po::parse_config_file(ifs, desc), vm);
  po::notify(vm);

  return true;
}

