#pragma once

#include <cstdint>

#include "config.h"

namespace kplutl {
#ifdef ENABLE_ISPC
namespace ispc {
extern "C" {
#endif
/* basic */

extern void AddForeach(float* out, const float* in_lhs, const float* in_rhs, const std::uint8_t len);
extern void SubForeach(float* out, const float* in_lhs, const float* in_rhs, const std::uint8_t len);
extern void MulForeach(float* out, const float* in_lhs, const float* in_rhs, const std::uint8_t len);
extern void DivForeach(float* out, const float* in_lhs, const float* in_rhs, const std::uint8_t len);
extern void PowForeach(float* out, const float* in_lhs, const float* in_rhs, const std::uint8_t len);
extern void AbsForeach(float* out, const float* in_arg, const std::uint8_t len);
extern void SqrtForeach(float* out, const float* in_arg, const std::uint8_t len);

/* linear algebra */

extern void VectorDotProd(float* out, const float* vec_lhs, const float* vec_rhs, std::uint8_t len);
extern void VectorCrossProdV3(float vec_out[3], const float vec_lhs[3], const float vec_rhs[3]);
extern void VectorTransformV4(const float mat_lhs[16], float vec_rhs[4]);
extern void BuildIdentity(float* mat_arg, const std::uint8_t dim);
extern void MatrixTranspose(float* mat_out, const float* mat_arg, const std::uint8_t row, const std::uint8_t col);

#ifdef ENABLE_ISPC
}
}  // namespace ispc
#endif
}  // namespace kplutl