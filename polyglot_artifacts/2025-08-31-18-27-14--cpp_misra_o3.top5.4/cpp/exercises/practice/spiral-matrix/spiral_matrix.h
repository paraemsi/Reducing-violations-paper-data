#if !defined(SPIRAL_MATRIX_H)
#define SPIRAL_MATRIX_H

#include <vector>
#include <cstdint>
#include <cstddef>
#include <utility>

namespace spiral_matrix {

// Type alias representing the square matrix.
struct matrix
{
    using value_type   = std::int32_t;
    using storage_type = std::vector<std::vector<value_type>>;
    using native_int   = int; /* Alias allowed – raw type appears only inside this alias. */

    storage_type data {};

    matrix() = default;
    explicit matrix(storage_type d) : data(std::move(d)) {}

    auto operator[](std::size_t idx) -> std::vector<value_type>&
    {
        return data[idx];
    }

    auto operator[](std::size_t idx) const -> const std::vector<value_type>&
    {
        return data[idx];
    }

    auto size() const noexcept -> std::size_t
    {
        return data.size();
    }

    /* Implicit conversion so the test-suite’s std::vector<std::vector<int>>
     * can be compared directly with a matrix instance.
     */
    operator std::vector<std::vector<native_int>>() const
    {
        std::vector<std::vector<native_int>> out;
        out.reserve(data.size());

        for(const auto& row : data)
        {
            std::vector<native_int> out_row;
            out_row.reserve(row.size());

            for(const auto element : row)
            {
                out_row.push_back(static_cast<native_int>(element));
            }

            out.push_back(std::move(out_row));
        }

        return out;
    }
};

// Generate a clockwise spiral matrix of the requested size.
// Example for size == 3:
// 1 2 3
// 8 9 4
// 7 6 5
auto spiral_matrix(std::uint32_t size) -> matrix;

/* Convenience wrapper that preserves the previous API name.
 * Delegates to the required spiral_matrix(...) implementation.
 */
inline auto spiral(std::uint32_t size) -> matrix
{
    return spiral_matrix(size);
}

}  // namespace spiral_matrix

#endif  // SPIRAL_MATRIX_H
