#include "spiral_matrix.h"

namespace spiral_matrix {

auto generate(std::size_t dimension) -> matrix_t
{
    matrix_t matrix{};

    /*  A zero dimension has no cells to fill */
    if (dimension == static_cast<std::size_t>(0U)) {
        return matrix;
    }

    /*  Pre-allocate the matrix with zeros */
    matrix.assign(
        dimension,
        std::vector<value_t>(dimension, static_cast<value_t>(0U)));

    /*  Boundaries for the current spiral ring                                        */
    std::int64_t top{0};
    std::int64_t bottom{static_cast<std::int64_t>(dimension) - static_cast<std::int64_t>(1)};
    std::int64_t left{0};
    std::int64_t right{static_cast<std::int64_t>(dimension) - static_cast<std::int64_t>(1)};

    value_t value{static_cast<value_t>(1U)};

    while ((left <= right) && (top <= bottom)) {
        /*  Traverse left → right across the current top row                           */
        for (std::int64_t col{left}; col <= right; ++col) {
            matrix[static_cast<std::size_t>(top)]
                  [static_cast<std::size_t>(col)] = value;
            ++value;
        }
        ++top;

        /*  Traverse top → bottom down the current right column                        */
        for (std::int64_t row{top}; row <= bottom; ++row) {
            matrix[static_cast<std::size_t>(row)]
                  [static_cast<std::size_t>(right)] = value;
            ++value;
        }
        --right;

        /*  Traverse right → left across the current bottom row                        */
        if (top <= bottom) {
            for (std::int64_t col{right}; col >= left; --col) {
                matrix[static_cast<std::size_t>(bottom)]
                      [static_cast<std::size_t>(col)] = value;
                ++value;
            }
            --bottom;
        }

        /*  Traverse bottom → top up the current left column                           */
        if (left <= right) {
            for (std::int64_t row{bottom}; row >= top; --row) {
                matrix[static_cast<std::size_t>(row)]
                      [static_cast<std::size_t>(left)] = value;
                ++value;
            }
            ++left;
        }
    }

    return matrix;
}

/*  Wrapper kept for backward-compatibility with existing tests */
auto spiral_matrix(std::size_t dimension) -> matrix_t
{
    /*  Delegate to the primary generate() implementation                */
    return generate(dimension);
}

}  // namespace spiral_matrix
