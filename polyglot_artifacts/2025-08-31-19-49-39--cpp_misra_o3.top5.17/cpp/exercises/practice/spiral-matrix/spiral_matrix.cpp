#include "spiral_matrix.h"

#include <vector>
#include <cstdint>

namespace spiral_matrix {

auto spiral_matrix(std::size_t size) -> std::vector<std::vector<std::uint32_t>> 
{
    using Matrix = std::vector<std::vector<std::uint32_t>>;

    Matrix result{};
    if(size == static_cast<std::size_t>(0U)) {
        return result;
    }

    result.assign(size, std::vector<std::uint32_t>(size, static_cast<std::uint32_t>(0U)));

    std::uint32_t value{ static_cast<std::uint32_t>(1U) };

    std::int32_t top{ 0 };
    std::int32_t bottom{ static_cast<std::int32_t>(size) - 1 };
    std::int32_t left{ 0 };
    std::int32_t right{ static_cast<std::int32_t>(size) - 1 };

    while((top <= bottom) && (left <= right)) {

        for(std::int32_t col{ left }; col <= right; ++col) {
            result[static_cast<std::size_t>(top)][static_cast<std::size_t>(col)] = value;
            ++value;
        }
        ++top;

        for(std::int32_t row{ top }; row <= bottom; ++row) {
            result[static_cast<std::size_t>(row)][static_cast<std::size_t>(right)] = value;
            ++value;
        }
        --right;

        if(top <= bottom) {
            for(std::int32_t col{ right }; col >= left; --col) {
                result[static_cast<std::size_t>(bottom)][static_cast<std::size_t>(col)] = value;
                ++value;
            }
            --bottom;
        }

        if(left <= right) {
            for(std::int32_t row{ bottom }; row >= top; --row) {
                result[static_cast<std::size_t>(row)][static_cast<std::size_t>(left)] = value;
                ++value;
            }
            ++left;
        }
    }

    return result;
}

}  // namespace spiral_matrix
