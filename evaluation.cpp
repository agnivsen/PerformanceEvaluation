#include <iostream>
#include <Eigen/Dense>
#include <Eigen/Core>
#include <vector>
#include <chrono>
#include <unistd.h>
using namespace std;
using namespace Eigen;
using namespace std::chrono;

#define DIM 1000
#define NUM_CORES 4
#define ENABLE_PARALLEL

float get_time()
{
    return (float)duration_cast< milliseconds >(system_clock::now().time_since_epoch()).count();
}

void init_A(MatrixXd &A)
{
    for(int i = 0; i < DIM; i++)
    {
        for(int j = 0; j < DIM; j++)
        {
            A(i,j) = static_cast <float> (rand());
        }
    }
}

void init_b(VectorXd &b)
{
    for(int i = 0; i < DIM; i++)
    {
        b[i] = static_cast <float> (rand());
    }
}

void test_QRpseudoInv(MatrixXd &A, VectorXd &b)
{
    A.colPivHouseholderQr().solve(b);
}

void test_QR(MatrixXd &A, VectorXd &b)
{
    A.householderQr().solve(b);
}

void test_CompleteOrtho(MatrixXd &A, VectorXd &b)
{
    A.completeOrthogonalDecomposition().solve(b);
}

void test_LDLT(MatrixXd &A, VectorXd &b)
{
    A.ldlt().solve(b);
}


int main()
{
    /**********Declaration & Initialization**********/
    MatrixXd A(DIM,DIM);
    VectorXd b(DIM);
    init_A(A);
    init_b(b);
    /**********Declaration & Initialization**********/

#ifdef ENABLE_PARALLEL
    Eigen::initParallel();
    Eigen::setNbThreads(NUM_CORES);
#endif


    auto start_ = chrono::steady_clock::now();
    test_QRpseudoInv(A,b);
    auto end_ = chrono::steady_clock::now();
    cout << "colPivHouseholderQr : " 
        << chrono::duration_cast<chrono::nanoseconds>(end_ - start_).count()
        << " ns" << endl;

    start_ = chrono::steady_clock::now();
    test_QR(A,b);
    end_ = chrono::steady_clock::now();
    cout << "householderQr : " 
        << chrono::duration_cast<chrono::nanoseconds>(end_ - start_).count()
        << " ns" << endl;


    start_ = chrono::steady_clock::now();
    test_CompleteOrtho(A,b);
    end_ = chrono::steady_clock::now();
    cout << "completeOrthogonalDecomposition : " 
        << chrono::duration_cast<chrono::nanoseconds>(end_ - start_).count()
        << " ns" << endl;


    start_ = chrono::steady_clock::now();
    test_LDLT(A,b);
    end_ = chrono::steady_clock::now();
    cout << "LDLT: " 
        << chrono::duration_cast<chrono::nanoseconds>(end_ - start_).count()
        << " ns" << endl;


}