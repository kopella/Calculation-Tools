#include <calculation_tools/linear_algebra.h>
#include "calculation_tools/matrix.h"

using namespace kplutl;

int main() {
  Vector3f vec_1{1, 2, 3};
  Vector3f vec_2{7, 8, 9};

  std::cout << "vec_1: " << vec_1 << std::endl;
  std::cout << "vec_2: " << vec_2 << std::endl;

  std::cout << "DotProd(vec_1, vec_2): " << DotProd(vec_1, vec_2) << std::endl;
  std::cout << "CrossProd(vec_1, vec_2): " << CrossProd(vec_1, vec_2) << std::endl;
  std::cout << "CrossProd(vec_2, vec_1): " << CrossProd(vec_2, vec_1) << std::endl;

  Matrix4X4f mat_transform{
      {2, 0,   0, 1},
      {0, 0.5, 0, 1},
      {0, 0,   1, 1},
      {0, 0,   0, 1}
  };
  Vector4f vec_transform{1, 1, 1, 1};

  std::cout << "mat_transform: " << mat_transform;
  std::cout << "vec_transform: " << vec_transform << std::endl;

  std::cout << "transform(mat_transform, vec_transform): "
            << Transform(mat_transform, vec_transform) << std::endl;

  MatrixCT<float, 3, 2> mat_1{
      {1, 2},
      {3, 4},
      {5, 6}
  };

  std::cout << "mat_1: " << mat_1;
  std::cout << "Transpose(mat_1):" << Transpose(mat_1);

  Matrix3X3f mat_2{
      {1, 2, 3},
      {4, 5, 6},
      {7, 8, 9}
  };

  Matrix3X3f mat_3{
      {9, 8, 7},
      {6, 5, 4},
      {3, 2, 1}
  };

  std::cout << "mat_2: " << mat_2;
  std::cout << "mat_3: " << mat_3;

  std::cout << "MatrixProd(mat_2, mat_3):" << MatrixProd(mat_2, mat_3);
}