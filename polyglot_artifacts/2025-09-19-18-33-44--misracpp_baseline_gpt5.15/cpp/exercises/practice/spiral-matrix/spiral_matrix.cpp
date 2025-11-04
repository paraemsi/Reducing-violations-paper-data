#include "spiral_matrix.h"

namespace spiral_matrix {

namespace {
std::vector<std::vector<int>> make_spiral(std::size_t size) {
    std::vector<std::vector<int>> m(size, std::vector<int>(size, 0));
    int n = static_cast<int>(size);
    if (n == 0) {
        return m;
    }

    int top = 0;
    int left = 0;
    int bottom = n - 1;
    int right = n - 1;
    int val = 1;

    while (left <= right && top <= bottom) {
        for (int j = left; j <= right; ++j) {
            m[static_cast<std::size_t>(top)][static_cast<std::size_t>(j)] = val++;
        }
        ++top;

        for (int i = top; i <= bottom; ++i) {
            m[static_cast<std::size_t>(i)][static_cast<std::size_t>(right)] = val++;
        }
        --right;

        if (top <= bottom) {
            for (int j = right; j >= left; --j) {
                m[static_cast<std::size_t>(bottom)][static_cast<std::size_t>(j)] = val++;
            }
            --bottom;
        }

        if (left <= right) {
            for (int i = bottom; i >= top; --i) {
                m[static_cast<std::size_t>(i)][static_cast<std::size_t>(left)] = val++;
            }
            ++left;
        }
    }

    return m;
}
}  // namespace


std::vector<std::vector<int>> spiral_matrix(std::size_t size) {
    return make_spiral(size);
}

}  // namespace spiral_matrix
