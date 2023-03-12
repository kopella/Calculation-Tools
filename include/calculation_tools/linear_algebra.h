#pragma once

#include "vector.h"
#include "matrix.h"


namespace kplutl {
/* inline functions */

template <typename T>
inline void vectorCross_(
    VectorCT<T, 3>& vec_out, const VectorCT<T, 3>& vec_lhs, const VectorCT<T, 3>& vec_rhs) {
#ifdef ENABLE_ISPC
  ispc::VectorCrossV3(vec_out, vec_lhs, vec_rhs);
#else
  VectorCrossV3(vec_out, vec_lhs, vec_rhs);
#endif
}

template <typename T>
inline void vertexTransform_(const MatrixCT<T, 4, 4>& mat_lhs, VectorCT<T, 4>& vec_rhs) {
#ifdef ENABLE_ISPC
  ispc::VectorTransformV4(mat_lhs, vec_rhs);
#else
  VectorTransformV4(mat_lhs, vec_rhs);
#endif
}

template <typename T, size_t D>
inline void buildIdentity_(MatrixCT<T, D, D>& mat, const size_t n) {
#ifdef ENABLE_ISPC
  ispc::BuildIdentity(mat, n);
#else
  BuildIdentity(mat, n);
#endif
}

template <typename T, size_t ROWS, size_t COLS>
inline void matrixTranspose_(MatrixCT<T, COLS, ROWS>& out, const MatrixCT<T, ROWS, COLS>& mat) {
#ifdef ENABLE_ISPC
  ispc::MatrixTranspose(out, mat, ROWS, COLS);
#else
  MatrixTranspose(out, mat, ROWS, COLS);
#endif
}

/* free functions */

template <typename T, size_t N>
T DotProd(const VectorCT<T, N>& lhs, const VectorCT<T, N>& rhs) {
  VectorCT<T, N> tmp = lhs * rhs;
  T res = tmp[0];
  for (size_t i = 1; i < N; ++i) {
    res += tmp[i];
  }
  return res;
}

template <typename T>
T CrossProd(const VectorCT<T, 2>& lhs, const VectorCT<T, 2>& rhs) {
  return lhs.v[0] * rhs.v[1] - lhs.v[1] * rhs.v[0];
}

template <typename T>
VectorCT<T, 3> CrossProd(const VectorCT<T, 3>& lhs, const VectorCT<T, 3>& rhs) {
  VectorCT<T, 3> res;
  vectorCross_(res, lhs, rhs);
  return res;
}

template <typename T, size_t N>
T Length(const VectorCT<T, N>& vec) {
  return (T)std::sqrt(Dot(vec, vec));
}

template <typename T, size_t N>
VectorCT<T, N> Normalize(const VectorCT<T, N>& vec) {
  return vec / Length(vec);
}

template <typename T, size_t D>
void BuildIdentity(MatrixCT<T, D, D>& mat) {
  buildIdentity_(mat, D);
}

template <typename T>
VectorCT<T, 4> Transform(const MatrixCT<T, 4, 4>& mat, const VectorCT<T, 4>& vec) {
  VectorCT<T, 4> res{vec};
  vertexTransform_(mat, res);
  return res;
}

template <typename T, size_t ROWS, size_t COLS>
MatrixCT<T, COLS, ROWS> Transpose(const MatrixCT<T, ROWS, COLS>& mat) {
  MatrixCT<T, COLS, ROWS> res;
  matrixTranspose_(res, mat);
  return res;
}

template <typename T, size_t Da, size_t Db, size_t Dc>
MatrixCT<T, Da, Dc> MatrixProd(const MatrixCT<T, Da, Db>& lhs, const MatrixCT<T, Db, Dc>& rhs) {
  MatrixCT<T, Da, Dc> res;
  MatrixCT<T, Dc, Db> rhs_t{Transpose(rhs)};
  for (size_t r = 0; r < Da; ++r) {
    for (size_t c = 0; c < Dc; ++c) {
      res.data_[r][c] = DotProd(lhs.data_[r], rhs_t.data_[c]);
    }
  }
  return res;
}

}  // namespace kplutl
