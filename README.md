# PerformanceEvaluation
A small utility for testing the time required by CPU to perform medium sized matrix inversion using Eigen.

It assigns random values to a matrix (A) and a column vector (b) and tries to solve an equation of the form: x = A^{-1}b
This is done using Eigen, for a sufficiently large array (change the size if needed), and the time required is logged in the console.

## Dependencies
[Eigen 3.3](http://eigen.tuxfamily.org/index.php?title=Main_Page#Download)

## How to install
Go to the root directory and do this:

    mkdir build
    cd build
    cmake ..
    make
    ./evaluation
    
## Options

All options are maintained in the macro. There are no command-line options.

The macros are:

1. DIM: the size of the matrix that is being inverted (and solved)
2. NUM_CORES: the number of cores in the CPU
3. ENABLE_PARALLEL: toggle this macro to enable/disable Eigen's parallelization
