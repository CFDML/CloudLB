#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#include <blaze/math/CompressedMatrix.h>
#include <blaze/math/DynamicMatrix.h>
#include <blaze/math/DynamicVector.h>
#include <blaze_tensor/math/DynamicTensor.h>

typedef blaze::DynamicVector<double> Vector;
typedef blaze::DynamicVector<int> VectorI;
typedef blaze::DynamicVector<unsigned> VectorU;
typedef std::vector<blaze::DynamicVector<double>> VectorVector;
typedef std::vector<blaze::DynamicVector<int>> VectorVectorI;
typedef std::vector<blaze::DynamicVector<unsigned>> VectorVectorU;
typedef blaze::DynamicMatrix<double> Matrix;
typedef blaze::DynamicMatrix<blaze::DynamicVector<double>> MatrixVector;
typedef blaze::SymmetricMatrix<blaze::DynamicMatrix<double, blaze::rowMajor>> SymMatrix;
typedef blaze::DiagonalMatrix<blaze::DynamicMatrix<double, blaze::rowMajor>> DiagMatrix;
typedef blaze::CompressedMatrix<double> SparseMatrix;
typedef blaze::DynamicTensor<double> Tensor;

struct Setup{
    int dim;
    double xmin, xmax, ymin, ymax;
    int nx, ny, nq;
    double cfl;
    double Re;
    double uwall;
    double nu;
    double tau;
};

class Solution {
  public:
    Matrix n;
    MatrixVector u, u0;
    MatrixVector f, F;
};

#endif // TYPEDEFS_H