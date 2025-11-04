#include "spiral_matrix.h"

namespace spiral_matrix {

auto generate(std::uint32_t size) -> matrix
{
    if (size == static_cast<std::uint32_t>(0)) {
        return {};
    }

    matrix result(
        size,
        std::vector<std::uint32_t>(
            size,
            static_cast<std::uint32_t>(0)));

    std::uint32_t current { static_cast<std::uint32_t>(1) };

    std::int32_t top { static_cast<std::int32_t>(0) };
    std::int32_t bottom {
        static_cast<std::int32_t>(size) - static_cast<std::int32_t>(1) };
    std::int32_t left { static_cast<std::int32_t>(0) };
    std::int32_t right {
        static_cast<std::int32_t>(size) - static_cast<std::int32_t>(1) };

    while ((top <= bottom) && (left <= right)) {
        for (std::int32_t col { left }; col <= right; ++col) {
            result[static_cast<std::size_t>(top)]
                  [static_cast<std::size_t>(col)] = current;
            ++current;
        }
        ++top;

        for (std::int32_t row { top }; row <= bottom; ++row) {
            result[static_cast<std::size_t>(row)]
                  [static_cast<std::size_t>(right)] = current;
            ++current;
        }
        --right;

        if (top <= bottom) {
            for (std::int32_t col { right }; col >= left; --col) {
                result[static_cast<std::size_t>(bottom)]
                      [static_cast<std::size_t>(col)] = current;
                ++current;
            }
            --bottom;
        }

        if (left <= right) {
            for (std::int32_t row { bottom }; row >= top; --row) {
                result[static_cast<std::size_t>(row)]
                      [static_cast<std::size_t>(left)] = current;
                ++current;
            }
            ++left;
        }
    }

    return result;
}

auto spiral_matrix(std::uint32_t size) -> matrix
{
    return generate(size);
}

}  // namespace spiral_matrix
