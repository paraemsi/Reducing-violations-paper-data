#include "diamond.h"
#include <stdexcept>
#include <string>
#include <vector>
#include <cstddef>
#include <utility>      // for std::move

namespace diamond {

std::vector<std::string> make(char letter) {
    if (letter < 'A' || letter > 'Z') {
        throw std::invalid_argument("letter must be between 'A' and 'Z'");
    }

    const std::size_t n = static_cast<std::size_t>(letter - 'A');
    const std::size_t size = 2 * n + 1;
    std::vector<std::string> result;
    result.reserve(size);

    // Top half including middle line
    for (std::size_t i = 0; i <= n; ++i) {
        const char ch = static_cast<char>('A' + i);
        const std::size_t leading = n - i;
        const std::size_t between = i == 0 ? 0 : 2 * i - 1;

        std::string line;
        line.append(leading, ' ');
        line.push_back(ch);
        if (between > 0) {
            line.append(between, ' ');
            line.push_back(ch);
        }
        line.append(leading, ' ');
        result.push_back(std::move(line));
    }

    // Bottom half (mirror of the top half excluding center)
    for (std::size_t i = n; i-- > 0; ) {
        result.push_back(result[i]);
    }

    return result;
}

std::vector<std::string> rows(char letter) {
    // Delegates to make() to keep single point of logic
    return make(letter);
}

}  // namespace diamond
