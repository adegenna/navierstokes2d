#include <boost/program_options.hpp>
#include "../src/Fourier2d.h"
#include "fft_test.h"
#include "../src/NavierStokesPhysics.h"
#include "../src/Inputfile.hpp"
#include <sys/time.h>

using namespace std;
using namespace Eigen;

TEST(FFTTest, testFFT2d) {
  
  std::string inputfile  = std::string(SRCDIR)+"tests/omega0_3.csv";
  
  // Setup
  ArrayXXd omega0 = load_csv<ArrayXXd>(inputfile);
  
  // FFT/IFFT
  ArrayXXcd omega_hat = *fft2( make_shared< MatrixXd > ( omega0.matrix() ) );
  ArrayXXcd omega     = ifft2( make_shared< MatrixXcd > ( omega_hat.matrix() ) )->real();
  
  ASSERT_TRUE(omega0.isApprox(omega));
  
}

