#if !defined(SPIRAL_MATRIX_H)
#define SPIRAL_MATRIX_H

#include <vector>
#include <cstdint>

namespace spiral_matrix {
namespace impl {

std::vector<std::vector<std::uint32_t>> generate_spiral(std::uint32_t size);

}  // namespace impl

inline std::vector<std::vector<std::uint32_t>> spiral_matrix(std::uint32_t size) {
    return impl::generate_spiral(size);
}

}  // namespace spiral_matrix

#endif  // SPIRAL_MATRIX_H
