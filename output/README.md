# Introduction
Fourier spectral solver for the 2D incompressible Navier Stokes equations.
Periodic boundary conditions, rectangular domain.

# Build
mkdir navierstokes2d/build/
cd navierstokes2d/build/
cmake ../
make

# Preprocessing
To generate initial conditions for the solver, edit/run the simple python script in preprocessing/.

# Solver
First, edit the filepaths in src/input.dat to reflect what is on your machine. Then:

cd build/
./solver --config=../src/input.dat

# Visualization
First, edit the filepaths in the output/plot.py script to reflect what is on your machine. Then, run:

python plot.py