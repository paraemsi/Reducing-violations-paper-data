#include "diamond.h"
#include <cctype>
#include <stdexcept>

namespace diamond {

std::vector<std::string> rows(char letter) {
    // Normalize to uppercase and validate
    if (letter >= 'a' && letter <= 'z') {
        letter = static_cast<char>(std::toupper(static_cast<unsigned char>(letter)));
    }
    if (letter < 'A' || letter > 'Z') {
        throw std::invalid_argument("letter must be in range A-Z or a-z");
    }

    const int n = letter - 'A' + 1;
    const int width = 2 * n - 1;

    std::vector<std::string> result;
    result.reserve(static_cast<size_t>(2 * n - 1));

    // Top half including middle row
    for (int i = 0; i < n; ++i) {
        const char ch = static_cast<char>('A' + i);
        std::string line(static_cast<size_t>(width), ' ');
        const int left = (n - 1) - i;
        const int right = width - left - 1;
        line[static_cast<size_t>(left)] = ch;
        line[static_cast<size_t>(right)] = ch;
        result.push_back(std::move(line));
    }

    // Bottom half (mirror of top half without the middle row)
    for (int i = n - 2; i >= 0; --i) {
        result.push_back(result[static_cast<size_t>(i)]);
    }

    return result;
}

}  // namespace diamond
