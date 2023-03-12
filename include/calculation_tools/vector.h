#pragma once

#include <cassert>

#include <array>
#include <iterator>
#include <iostream>
#include <initializer_list>

#include "utils.h"

namespace kplutl {
template <typename T, size_t N>
struct VectorCT {
  std::array<T, N> data_{};

  VectorCT<T, N>() = default;
  VectorCT<T, N>(VectorCT<T, N>& vectorCT) = default;
  VectorCT<T, N>& operator=(VectorCT<T, N>& matrixCT) = default;
  VectorCT<T, N>(VectorCT<T, N>&& vectorCT) = default;
  VectorCT<T, N>& operator=(VectorCT<T, N>&& matrixCT) = default;

  VectorCT<T, N>(T value) {
    for (size_t i = 0; i < N; ++i) data_[i] = value;
  }
  VectorCT<T, N>(std::initializer_list<const T> list) {
    assert(list.size() == N);
    size_t i = 0;
    for (auto value : list) data_[i++] = value;
  }

  template <typename It>
  VectorCT<T, N>(It first, It last) {
    auto size = std::distance(first, last);
    assert(size == N);
    auto it = first;
    for (size_t i = 0; i < size; ++i) {
      data_[i] = *it;
      ++it;
    }
  }

  template <typename S>
  explicit VectorCT<T, N>(const S* source) {
    for (size_t i = 0; i < N; ++i) data_[i] = (T)source[i];
  }
  template <typename S>
  explicit VectorCT<T, N>(const VectorCT<S, N>& source) {
    for (size_t i = 0; i < N; ++i) data_[i] = (T)source[i];
  }

  T& operator[](size_t index) { return data_[index]; }

  operator T*() { return &data_[0]; };

  operator const T*() const { return reinterpret_cast<const T*>(&data_[0]); }

  VectorCT<T, N>& operator+=(const VectorCT<T, N>& lhs) {
    *this = *this + lhs;
    return *this;
  }

  VectorCT<T, N>& operator+=(const T scalar) {
    *this = *this + scalar;
    return *this;
  }

  VectorCT<T, N>& operator-=(const VectorCT<T, N>& lhs) {
    *this = *this - lhs;
    return *this;
  }

  VectorCT<T, N>& operator-=(const T scalar) {
    *this = *this - scalar;
    return *this;
  }

  VectorCT<T, N>& operator*=(const VectorCT<T, N>& lhs) {
    *this = *this * lhs;
    return *this;
  }

  VectorCT<T, N>& operator*=(const T scalar) {
    *this = *this * scalar;
    return *this;
  }

  VectorCT<T, N>& operator/=(const VectorCT<T, N>& lhs) {
    *this = *this / lhs;
    return *this;
  }

  VectorCT<T, N>& operator/=(const T scalar) {
    *this = *this / scalar;
    return *this;
  }
};

/* type defines */

using Vector2f = VectorCT<float, 2>;
using Vector3f = VectorCT<float, 3>;
using Vector4f = VectorCT<float, 4>;

/* inline functions */

template <typename T, size_t N>
inline void vectorAdd_(
    VectorCT<T, N>& out, const VectorCT<T, N>& in_lhs, const VectorCT<T, N>& in_rhs) {
#ifdef ENABLE_ISPC
  ispc::AddForeach(out, in_lhs, in_rhs, N);
#else
  AddForeach(out, in_lhs, in_rhs, N);
#endif
}

template <typename T, size_t N>
inline void vectorSub_(
    VectorCT<T, N>& out, const VectorCT<T, N>& in_lhs, const VectorCT<T, N>& in_rhs) {
#ifdef ENABLE_ISPC
  ispc::SubForeach(out, in_lhs, in_rhs, N);
#else
  SubForeach(out, in_lhs, in_rhs, N);
#endif
}

template <typename T, size_t N>
inline void vectorMul_(
    VectorCT<T, N>& out, const VectorCT<T, N>& in_lhs, const VectorCT<T, N>& in_rhs) {
#ifdef ENABLE_ISPC
  ispc::MulForeach(out, in_lhs, in_rhs, N);
#else
  MulForeach(in_lhs, in_rhs, out, N);
#endif
}

template <typename T, size_t N>
inline void vectorDiv_(
    VectorCT<T, N>& out, const VectorCT<T, N>& in_lhs, const VectorCT<T, N>& in_rhs) {
#ifdef ENABLE_ISPC
  ispc::DivForeach(out, in_lhs, in_rhs, N);
#else
  DivForeach(out, in_lhs, in_rhs, N);
#endif
}

template <typename T, size_t N>
inline void vectorAbs_(VectorCT<T, N>& out, const VectorCT<T, N>& in_arg) {
#ifdef ENABLE_ISPC
  ispc::AbsForeach(out, in_arg, N);
#else
  AbsForeach(out, in_arg, N);
#endif
}

template <typename T, size_t N>
inline void vectorSqrt_(VectorCT<T, N>& out, const VectorCT<T, N>& in_arg) {
#ifdef ENABLE_ISPC
  ispc::SqrtForeach(out, in_arg, N);
#else
  SqrtForeach(out, in_arg, N);
#endif
}

/* operators */

/* + */

template <typename T, size_t N>
VectorCT<T, N> operator+(const VectorCT<T, N>& lhs, const VectorCT<T, N>& rhs) {
  VectorCT<T, N> res;
  vectorAdd_(res, lhs, rhs);
  return res;
}

template <typename T, size_t N>
VectorCT<T, N> operator+(const VectorCT<T, N>& lhs, const T scalar) {
  VectorCT<T, N> res(scalar);
  vectorAdd_(res, lhs, res);
  return res;
}

template <typename T, size_t N>
VectorCT<T, N> operator+(const T scalar, const VectorCT<T, N>& rhs) {
  VectorCT<T, N> res(scalar);
  vectorAdd_(res, res, rhs);
  return res;
}

/* - */

template <typename T, size_t N>
VectorCT<T, N> operator-(const VectorCT<T, N>& lhs, const VectorCT<T, N>& rhs) {
  VectorCT<T, N> res;
  vectorSub_(res, lhs, rhs);
  return res;
}

template <typename T, size_t N>
VectorCT<T, N> operator-(const VectorCT<T, N>& lhs, const T scalar) {
  VectorCT<T, N> res(scalar);
  vectorSub_(res, lhs, res);
  return res;
}

template <typename T, size_t N>
VectorCT<T, N> operator-(const T scalar, const VectorCT<T, N>& rhs) {
  VectorCT<T, N> res(scalar);
  vectorSub_(res, res, rhs);
  return res;
}

/* * */

template <typename T, size_t N>
VectorCT<T, N> operator*(const VectorCT<T, N>& lhs, const VectorCT<T, N>& rhs) {
  VectorCT<T, N> res;
  vectorMul_(res, lhs, rhs);
  return res;
}

template <typename T, size_t N>
VectorCT<T, N> operator*(const VectorCT<T, N>& lhs, const T scalar) {
  VectorCT<T, N> res(scalar);
  vectorMul_(res, lhs, res);
  return res;
}

template <typename T, size_t N>
VectorCT<T, N> operator*(const T scalar, const VectorCT<T, N>& rhs) {
  VectorCT<T, N> res(scalar);
  vectorMul_(res, res, rhs);
  return res;
}

/* / */

template <typename T, size_t N>
VectorCT<T, N> operator/(const VectorCT<T, N>& lhs, const VectorCT<T, N>& rhs) {
  VectorCT<T, N> res;
  vectorDiv_(res, lhs, rhs);
  return res;
}

template <typename T, size_t N>
VectorCT<T, N> operator/(const VectorCT<T, N>& lhs, const T scalar) {
  VectorCT<T, N> res(scalar);
  vectorDiv_(res, lhs, res);
  return res;
}

template <typename T, size_t N>
VectorCT<T, N> operator/(const T scalar, const VectorCT<T, N>& rhs) {
  VectorCT<T, N> res(scalar);
  vectorDiv_(res, res, rhs);
  return res;
}

/* free functions */

template <typename T, size_t N>
VectorCT<T, N> Abs(const VectorCT<T, N>& vec) {
  VectorCT<T, N> res;
  vectorAbs_(res, vec);
  return res;
}

template <typename T, size_t N>
VectorCT<T, N> Sqrt(const VectorCT<T, N>& vec) {
  VectorCT<T, N> res;
  vectorSqrt_(res, vec);
  return res;
}

/* stream */

template <typename T, size_t N>
std::istream& operator>>(std::istream& in, VectorCT<T, N>& vec) {
  for (size_t i = 0; i < N; ++i) in >> vec.data_[i];
  return in;
}

template <typename T, size_t N>
std::ostream& operator<<(std::ostream& out, const VectorCT<T, N>& vec) {
  out << "( ";
  for (size_t i = 0; i < N; ++i) out << vec.data_[i] << (i != N - 1 ? ", " : "");
  out << " )";
  return out;
}

}  // namespace kplutl