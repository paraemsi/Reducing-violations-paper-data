#include "diamond.h"
#include <cctype>
#include <cstddef>

namespace diamond {

std::vector<std::string> rows(char letter) {
    char upper = static_cast<char>(std::toupper(static_cast<unsigned char>(letter)));
    if (upper < 'A' || upper > 'Z') {
        return {};
    }

    std::size_t n = static_cast<std::size_t>(upper - 'A' + 1);
    std::size_t width = 2 * n - 1;

    std::vector<std::string> result;
    result.reserve(2 * n - 1);

    auto make_row = [n, width](std::size_t r) {
        std::string row(width, ' ');
        char ch = static_cast<char>('A' + r);
        std::size_t left = (n - 1) - r;
        std::size_t right = (n - 1) + r;
        row[left] = ch;
        if (left != right) {
            row[right] = ch;
        }
        return row;
    };

    for (std::size_t r = 0; r < n; ++r) {
        result.push_back(make_row(r));
    }
    for (std::size_t r = n - 1; r-- > 0; ) {
        result.push_back(make_row(r));
    }

    return result;
}

}  // namespace diamond
