#include "diamond.h"

#include <cctype>
#include <stdexcept>
#include <string>
#include <vector>

namespace diamond {

std::vector<std::string> rows(char letter) {
    // Normalize to uppercase to simplify computation.
    char upper = static_cast<char>(std::toupper(static_cast<unsigned char>(letter)));
    if (upper < 'A' || upper > 'Z') {
        throw std::invalid_argument("letter must be in range A-Z or a-z");
    }

    int n = upper - 'A';
    int width = 2 * n + 1;

    std::vector<std::string> result;
    result.reserve(static_cast<std::size_t>(width));

    // Build the top half (including middle line)
    for (int i = 0; i <= n; ++i) {
        std::string line(static_cast<std::size_t>(width), ' ');
        char ch = static_cast<char>('A' + i);
        int left = n - i;
        int right = n + i;
        line[static_cast<std::size_t>(left)] = ch;
        if (left != right) {
            line[static_cast<std::size_t>(right)] = ch;
        }
        result.push_back(std::move(line));
    }

    // Mirror to get the bottom half (excluding middle line)
    for (int i = n - 1; i >= 0; --i) {
        result.push_back(result[static_cast<std::size_t>(i)]);
    }

    return result;
}

}  // namespace diamond
