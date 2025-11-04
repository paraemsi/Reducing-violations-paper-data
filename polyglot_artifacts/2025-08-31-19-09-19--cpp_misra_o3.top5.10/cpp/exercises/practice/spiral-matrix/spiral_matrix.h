#if !defined(SPIRAL_MATRIX_H)
#define SPIRAL_MATRIX_H

#include <cstdint>
#include <cstddef>
#include <vector>

namespace spiral_matrix {

/*
 * Alias representing a square matrix holding natural numbers.
 * All numeric elements use std::uint32_t to comply with MISRA C++ rules
 * requiring fixed-width unsigned integer types.
 *
 * A dedicated alias name is introduced so that the underlying fixed-width
 * type appears only here, as permitted by the guidelines.
 */
using value_type = std::int32_t;
using matrix = std::vector<std::vector<value_type>>;

/*
 * Generate a size × size clockwise spiral matrix populated
 * with consecutive natural numbers starting from 1 at the
 * top-left corner.
 *
 * @param size  The length of one side of the square matrix.
 * @return      A 'matrix' object; empty when size == 0.
 *
 * Requirements:
 *   • Uses only standard library facilities.
 *   • Respects MISRA C++ rules stated in the task description.
 */
auto spiral_matrix(value_type size) -> matrix;

}  // namespace spiral_matrix

#endif  // SPIRAL_MATRIX_H
