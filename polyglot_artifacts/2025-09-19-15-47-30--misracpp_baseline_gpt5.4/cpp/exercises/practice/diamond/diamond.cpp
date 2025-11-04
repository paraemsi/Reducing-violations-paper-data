#include "diamond.h"

#include <cctype>
#include <cstddef>
#include <stdexcept>

namespace diamond {

std::vector<std::string> rows(char letter) {
    unsigned char uc = static_cast<unsigned char>(letter);
    char upper = static_cast<char>(std::toupper(uc));
    if (upper < 'A' || upper > 'Z') {
        throw std::invalid_argument("letter must be an alphabetic character A-Z");
    }

    std::size_t n = static_cast<std::size_t>(upper - 'A');
    std::size_t width = 2 * n + 1;

    std::vector<std::string> result;
    result.reserve(width);

    for (std::size_t k = 0; k <= n; ++k) {
        std::size_t lead = n - k;
        std::size_t inner = (k == 0) ? 0 : (2 * k - 1);

        std::string line;
        line.reserve(width);

        line.append(lead, ' ');
        line.push_back(static_cast<char>('A' + k));
        if (k > 0) {
            line.append(inner, ' ');
            line.push_back(static_cast<char>('A' + k));
        }
        line.append(lead, ' ');

        result.push_back(std::move(line));
    }

    for (std::ptrdiff_t k = static_cast<std::ptrdiff_t>(n) - 1; k >= 0; --k) {
        result.push_back(result[static_cast<std::size_t>(k)]);
    }

    return result;
}

}  // namespace diamond
