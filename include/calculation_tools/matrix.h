#pragma once

#include <iostream>
#include <initializer_list>

#include "utils.h"
#include "vector.h"

namespace kplutl {
template <typename T, size_t ROWS, size_t COLS>
struct MatrixCT {
  VectorCT<T, COLS> data_[ROWS];

  MatrixCT<T, ROWS, COLS>() = default;
  MatrixCT<T, ROWS, COLS>(MatrixCT<T, ROWS, COLS>& matrixCT) = default;
  MatrixCT<T, ROWS, COLS>& operator=(MatrixCT<T, ROWS, COLS>& matrixCT) = default;
  MatrixCT<T, ROWS, COLS>(MatrixCT<T, ROWS, COLS>&& matrixCT) = default;
  MatrixCT<T, ROWS, COLS>& operator=(MatrixCT<T, ROWS, COLS>&& matrixCT) = default;

  MatrixCT<T, ROWS, COLS>(T value) {
    for (size_t r = 0; r < ROWS; ++r) {
      for (size_t c = 0; c < COLS; ++c) {
        data_[r][c] = value;
      }
    }
  }
  MatrixCT<T, ROWS, COLS>(std::initializer_list<std::initializer_list<const T>> list) {
    assert(list.size() == ROWS);
    size_t i = 0;
    for (auto sub_list : list) {
      assert(sub_list.size() <= COLS);
      size_t j = 0;
      for (auto value : sub_list) {
        data_[i][j++] = value;
      }
      i++;
    }
  }

  template <typename It>
  MatrixCT<T, ROWS, COLS>(It first, It last) {
    auto size = std::distance(first, last);
    assert(size == ROWS * COLS);
    auto it = first;
    for (size_t r = 0; r < ROWS; ++r) {
      for (size_t c = 0; c < COLS; ++c) {
        data_[r][c] = *it;
        ++it;
      }
    }
  }

  template <typename S>
  explicit MatrixCT<T, ROWS, COLS>(const S* source) {
    for (size_t r = 0; r < ROWS; ++r) {
      for (size_t c = 0; c < COLS; ++c) {
        data_[r][c] = (T)source[r][c];
      }
    }
  }
  template <typename S>
  explicit MatrixCT<T, ROWS, COLS>(const MatrixCT<S, ROWS, COLS>& source) {
    for (size_t r = 0; r < ROWS; ++r) {
      for (size_t c = 0; c < COLS; ++c) {
        data_[r][c] = (T)source[r][c];
      }
    }
  }

  VectorCT<T, COLS>& operator[](int row_index) { return data_[row_index]; }

  operator T*() { return &data_[0][0]; };

  operator const T*() const { return static_cast<const T*>(&data_[0][0]); };
};

/* type defines */

using Matrix3X3f = MatrixCT<float, 3, 3>;
using Matrix4X4f = MatrixCT<float, 4, 4>;

/* inline functions */

template <typename T, size_t ROWS, size_t COLS>
inline void matrixAdd_(
    MatrixCT<T, ROWS, COLS>& out, const MatrixCT<T, ROWS, COLS>& in_lhs,
    const MatrixCT<T, ROWS, COLS>& in_rhs) {
#ifdef ENABLE_ISPC
  ispc::AddForeach(out, in_lhs, in_rhs, ROWS * COLS);
#else
  AddForeach(out, in_lhs, in_rhs, ROWS * COLS);
#endif
}

template <typename T, size_t ROWS, size_t COLS>
inline void matrixSub_(
    MatrixCT<T, ROWS, COLS>& out, const MatrixCT<T, ROWS, COLS>& in_lhs,
    const MatrixCT<T, ROWS, COLS>& in_rhs) {
#ifdef ENABLE_ISPC
  ispc::SubForeach(out, in_lhs, in_rhs, ROWS * COLS);
#else
  SubForeach(out, in_lhs, in_rhs, ROWS * COLS);
#endif
}

template <typename T, size_t ROWS, size_t COLS>
inline void matrixMul_(
    MatrixCT<T, ROWS, COLS>& out, const MatrixCT<T, ROWS, COLS>& in_lhs,
    const MatrixCT<T, ROWS, COLS>& in_rhs) {
#ifdef ENABLE_ISPC
  ispc::MulForeach(out, in_lhs, in_rhs, ROWS * COLS);
#else
  MulForeach(out, in_lhs, in_rhs, ROWS * COLS);
#endif
}

template <typename T, size_t ROWS, size_t COLS>
inline void matrixDiv_(
    MatrixCT<T, ROWS, COLS>& out, const MatrixCT<T, ROWS, COLS>& in_lhs,
    const MatrixCT<T, ROWS, COLS>& in_rhs) {
#ifdef ENABLE_ISPC
  ispc::DivForeach(out, in_lhs, in_rhs, ROWS * COLS);
#else
  DivForeach(out, in_lhs, in_rhs, ROWS * COLS);
#endif
}

template <typename T, size_t ROWS, size_t COLS>
inline void matrixAbs_(MatrixCT<T, ROWS, COLS>& out, const MatrixCT<T, ROWS, COLS>& in_arg) {
#ifdef ENABLE_ISPC
  ispc::AbsForeach(out, in_arg, ROWS * COLS);
#else
  AbsForeach(out, in_arg, ROWS * COLS);
#endif
}

template <typename T, size_t ROWS, size_t COLS>
inline void matrixSqrt_(MatrixCT<T, ROWS, COLS>& out, const MatrixCT<T, ROWS, COLS>& in_arg) {
#ifdef ENABLE_ISPC
  ispc::SqrtForeach(out, in_arg, ROWS * COLS);
#else
  SqrtForeach(out, in_arg, ROWS * COLS);
#endif
}

/* operators */

/* + */

template <typename T, size_t ROWS, size_t COLS>
MatrixCT<T, ROWS, COLS> operator+(
    const MatrixCT<T, ROWS, COLS>& lhs, const MatrixCT<T, ROWS, COLS>& rhs) {
  MatrixCT<T, ROWS, COLS> res;
  matrixAdd_(res, lhs, rhs);
  return res;
}

template <typename T, size_t ROWS, size_t COLS>
MatrixCT<T, ROWS, COLS> operator+(const MatrixCT<T, ROWS, COLS>& lhs, const T scalar) {
  MatrixCT<T, ROWS, COLS> res{scalar};
  matrixAdd_(res, lhs, res);
  return res;
}

template <typename T, size_t ROWS, size_t COLS>
MatrixCT<T, ROWS, COLS> operator+(const T scalar, const MatrixCT<T, ROWS, COLS>& rhs) {
  MatrixCT<T, ROWS, COLS> res{scalar};
  matrixAdd_(res, res, rhs);
  return res;
}

/* - */

template <typename T, size_t ROWS, size_t COLS>
MatrixCT<T, ROWS, COLS> operator-(
    const MatrixCT<T, ROWS, COLS>& lhs, const MatrixCT<T, ROWS, COLS>& rhs) {
  MatrixCT<T, ROWS, COLS> res;
  matrixSub_(res, lhs, rhs);
  return res;
}

template <typename T, size_t ROWS, size_t COLS>
MatrixCT<T, ROWS, COLS> operator-(const MatrixCT<T, ROWS, COLS>& lhs, const T scalar) {
  MatrixCT<T, ROWS, COLS> res{scalar};
  matrixSub_(res, lhs, res);
  return res;
}

template <typename T, size_t ROWS, size_t COLS>
MatrixCT<T, ROWS, COLS> operator-(const T scalar, const MatrixCT<T, ROWS, COLS>& rhs) {
  MatrixCT<T, ROWS, COLS> res{scalar};
  matrixSub_(res, res, rhs);
  return res;
}

/* * */

template <typename T, size_t ROWS, size_t COLS>
MatrixCT<T, ROWS, COLS> operator*(
    const MatrixCT<T, ROWS, COLS>& lhs, const MatrixCT<T, ROWS, COLS>& rhs) {
  MatrixCT<T, ROWS, COLS> res;
  matrixMul_(res, lhs, rhs);
  return res;
}

template <typename T, size_t ROWS, size_t COLS>
MatrixCT<T, ROWS, COLS> operator*(const MatrixCT<T, ROWS, COLS>& lhs, const T scalar) {
  MatrixCT<T, ROWS, COLS> res{scalar};
  matrixMul_(res, lhs, res);
  return res;
}

template <typename T, size_t ROWS, size_t COLS>
MatrixCT<T, ROWS, COLS> operator*(const T scalar, const MatrixCT<T, ROWS, COLS>& rhs) {
  MatrixCT<T, ROWS, COLS> res{scalar};
  matrixMul_(res, res, rhs);
  return res;
}

/* / */

template <typename T, size_t ROWS, size_t COLS>
MatrixCT<T, ROWS, COLS> operator/(
    const MatrixCT<T, ROWS, COLS>& lhs, const MatrixCT<T, ROWS, COLS>& rhs) {
  MatrixCT<T, ROWS, COLS> res;
  matrixDiv_(res, lhs, rhs);
  return res;
}

template <typename T, size_t ROWS, size_t COLS>
MatrixCT<T, ROWS, COLS> operator/(const MatrixCT<T, ROWS, COLS>& lhs, const T scalar) {
  MatrixCT<T, ROWS, COLS> res{scalar};
  matrixDiv_(res, lhs, res);
  return res;
}

template <typename T, size_t ROWS, size_t COLS>
MatrixCT<T, ROWS, COLS> operator/(const T scalar, const MatrixCT<T, ROWS, COLS>& rhs) {
  MatrixCT<T, ROWS, COLS> res{scalar};
  matrixDiv_(res, res, rhs);
  return res;
}

/* free functions */

template <typename T, size_t ROWS, size_t COLS>
MatrixCT<T, ROWS, COLS> Abs(const MatrixCT<T, ROWS, COLS>& mat) {
  MatrixCT<T, ROWS, COLS> res;
  matrixAbs_(res, mat);
  return res;
}

template <typename T, size_t ROWS, size_t COLS>
MatrixCT<T, ROWS, COLS> Sqrt(const MatrixCT<T, ROWS, COLS>& mat) {
  MatrixCT<T, ROWS, COLS> res;
  matrixSqrt_(res, mat);
  return res;
}

/* stream */

template <typename T, size_t ROWS, size_t COLS>
std::istream& operator>>(std::istream& in, MatrixCT<T, ROWS, COLS>& mat) {
  for (size_t r = 0; r < ROWS; ++r) in >> mat[r];
  return in;
}

template <typename T, size_t ROWS, size_t COLS>
std::ostream& operator<<(std::ostream& out, MatrixCT<T, ROWS, COLS>& mat) {
  out << std::endl;
  for (size_t r = 0; r < ROWS; ++r) out << mat[r] << std::endl;
  return out;
}

template <typename T, size_t ROWS, size_t COLS>
std::ostream& operator<<(std::ostream& out, MatrixCT<T, ROWS, COLS>&& mat) {
  out << std::endl;
  for (size_t r = 0; r < ROWS; ++r) out << mat[r] << std::endl;
  return out;
}

}  // namespace kplutl