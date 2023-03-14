#pragma once
#include "vector.h"
#include "matrix.h"
#include "linear_algebra.h"

/*
    Y-up
*/

namespace kplutl {
template <class T>
class Quaternion : public VectorCT<T, 4> {
 public:
  using VectorCT<T, 4>::VectorCT;

  const T x() const { return this->data_[0]; }
  const T y() const { return this->data_[1]; }
  const T z() const { return this->data_[2]; }
  const T w() const { return this->data_[3]; }
};

template <typename T>
MatrixCT<T, 4, 4> BuildTranslationMatrix(const T xAxis, const T yAxis, const T zAxis) {
  return MatrixCT<T, 4, 4>{
      {1, 0, 0, xAxis},
      {0, 1, 0, yAxis},
      {0, 0, 1, zAxis},
      {0, 0, 0, 1    }
  };
}

template <typename T>
MatrixCT<T, 4, 4> BuildScaleMatrix(const T xAxis, const T yAxis, const T zAxis) {
  return MatrixCT<T, 4, 4>{
      {xAxis, 0,     0,     0},
      {0,     yAxis, 0,     0},
      {0,     0,     zAxis, 0},
      {0,     0,     0,     1}
  };
}

template <typename T>
MatrixCT<T, 4, 4> BuildRotationMatrixX(const T angel) {
  T sinAngel = std::sin(angel);
  T cosAngel = std::cos(angel);

  return MatrixCT<T, 4, 4>{
      {1, 0,        0,         0},
      {0, cosAngel, -sinAngel, 0},
      {0, sinAngel, cosAngel,  0},
      {0, 0,        0,         1}
  };
}

template <typename T>
MatrixCT<T, 4, 4> BuildRotationMatrixY(const T angel) {
  T sinAngel = std::sin(angel);
  T cosAngel = std::cos(angel);

  return MatrixCT<T, 4, 4>{
      {cosAngel,  0, sinAngel, 0},
      {0,         1, 0,        0},
      {-sinAngel, 0, cosAngel, 0},
      {0,         0, 0,        1}
  };
}

template <typename T>
MatrixCT<T, 4, 4> BuildRotationMatrixZ(const T angel) {
  T sinAngel = std::sin(angel);
  T cosAngel = std::cos(angel);

  return MatrixCT<T, 4, 4>{
      {cosAngel, -sinAngel, 0, 0},
      {sinAngel, cosAngel,  0, 0},
      {0,        0,         1, 0},
      {0,        0,         0, 1}
  };
}

// template <typename T>
// MatrixCT<T, 4, 4> BuildRotationMatrix(const T x, const T y, const T z) {
//   T sinRoll = std::sin(x);
//   T sinPitch = std::sin(y);
//   T sinYaw = std::sin(z);
//
//   T cRoll = std::cos(x);
//   T cPitch = std::cos(y);
//   T cYaw = std::cos(z);
//
//   T r00 = cYaw * cPitch;
//   T r01 = cYaw * sinPitch * sinRoll - sinYaw * cRoll;
//   T r02 = cYaw * sinPitch * cRoll + sinYaw * sinRoll;
//
//   T r10 = sinYaw * cPitch;
//   T r11 = sinYaw * sinPitch * sinRoll + cYaw * cRoll;
//   T r12 = sinYaw * sinPitch * cRoll - cYaw * sinRoll;
//
//   T r20 = -sinPitch;
//   T r21 = cPitch * sinRoll;
//   T r22 = cPitch * cRoll;
//
//   return MatrixCT<T, 4, 4>{
//   {r00, r01, r02, 0},
//   {r10, r11, r12, 0},
//   {r20, r21, r22, 0},
//   {0,   0,   0,   1}
//   };
// }

template <typename T>
MatrixCT<T, 4, 4> BuildRotationMatrix(const Quaternion<T> quaternion) {
  T r00 = 2.0 * (quaternion.w * quaternion.w + quaternion.x * quaternion.x) - 1.0;
  T r01 = 2.0 * (quaternion.x * quaternion.y - quaternion.w * quaternion.z);
  T r02 = 2.0 * (quaternion.x * quaternion.z + quaternion.w * quaternion.y);

  T r10 = 2.0 * (quaternion.x * quaternion.y + quaternion.w * quaternion.z);
  T r11 = 2.0 * (quaternion.w * quaternion.w + quaternion.y * quaternion.y) - 1.0;
  T r12 = 2.0 * (quaternion.y * quaternion.z - quaternion.w * quaternion.x);

  T r20 = 2.0 * (quaternion.x * quaternion.z - quaternion.w * quaternion.y);
  T r21 = 2.0 * (quaternion.y * quaternion.z + quaternion.w * quaternion.x);
  T r22 = 2.0 * (quaternion.w * quaternion.w + quaternion.z * quaternion.z) - 1.0;

  return MatrixCT<T, 4, 4>{
      {r00, r01, r02, 0},
      {r10, r11, r12, 0},
      {r20, r21, r22, 0},
      {0,   0,   0,   1}
  };
}

template <typename T>
MatrixCT<T, 4, 4> BuildViewMatrixRH(
    const VectorCT<T, 3> eye, const VectorCT<T, 3> target, const VectorCT<T, 3> up) {
  VectorCT<T, 3> xAxis, yAxis, zAxis;

  zAxis = Normalize(eye - target);
  xAxis = Normalize(CrossProd(up, zAxis));
  yAxis = CrossProd(zAxis, xAxis);

  return MatrixCT<T, 4, 4>{
      {xAxis[0], xAxis[1], xAxis[2], -eye[0]},
      {yAxis[0], yAxis[1], yAxis[2], -eye[1]},
      {zAxis[0], zAxis[1], zAxis[2], -eye[2]},
      {0,        0,        0,        1      }
  };
}

template <typename T>
MatrixCT<T, 4, 4> BuildViewMatrixLH(
    const VectorCT<T, 3> eye, const VectorCT<T, 3> target, const VectorCT<T, 3> up) {
  VectorCT<T, 3> xAxis, yAxis, zAxis;

  zAxis = Normalize(target - eye);
  xAxis = Normalize(CrossProd(up, zAxis));
  yAxis = CrossProd(zAxis, xAxis);

  return MatrixCT<T, 4, 4>{
      {xAxis[0], xAxis[1], xAxis[2], -eye[0]},
      {yAxis[0], yAxis[1], yAxis[2], -eye[1]},
      {zAxis[0], zAxis[1], zAxis[2], -eye[2]},
      {0,        0,        0,        1      }
  };
}

template <typename T>
MatrixCT<T, 4, 4> BuildOrthographicProjectionMatrixRH(
    const T rightPlane, const T leftPlane, const T topPlane, const T bottomPlane, const T nearPlane,
    const T farPlane) {
  T width = rightPlane - leftPlane;
  T height = topPlane - bottomPlane;
  T depth = nearPlane - farPlane;

  return MatrixCT<T, 4, 4>{
      {2 / width, 0,          0,         -(rightPlane + leftPlane) / width },
      {0,         2 / height, 0,         -(topPlane + bottomPlane) / height},
      {0,         0,          2 / depth, -(nearPlane + farPlane) / depth   },
      {0,         0,          0,         1                                 }
  };
}

template <typename T>
MatrixCT<T, 4, 4> BuildPerspectiveProjectionMatrixRH(
    const T rightPlane, const T leftPlane, const T topPlane, const T bottomPlane, const T nearPlane,
    const T farPlane) {
  T width = rightPlane - leftPlane;
  T height = topPlane - bottomPlane;
  T depth = nearPlane - farPlane;

  return MatrixCT<T, 4, 4>{
      {2 * nearPlane / width, 0,                      rightPlane + leftPlane / -width,
       -(rightPlane + leftPlane) / width                                                                                 },
      {0,                     2 * nearPlane / height, topPlane + bottomPlane / -height,
       -(topPlane + bottomPlane) / height                                                                                },
      {0,                     0,                      nearPlane + farPlane / depth,     2 * nearPlane * farPlane / -depth},
      {0,                     0,                      1,                                0                                }
  };
}

}  // namespace kplutl