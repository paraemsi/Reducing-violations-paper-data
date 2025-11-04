#include "diamond.h"

#include <cctype>
#include <cstdlib>   // for std::abs
#include <stdexcept>

namespace diamond {

std::vector<std::string> rows(char letter) {
    if (!std::isalpha(static_cast<unsigned char>(letter))) {
        throw std::invalid_argument("letter must be alphabetic");
    }

    // Work with uppercase only.
    char upper = static_cast<char>(std::toupper(static_cast<unsigned char>(letter)));
    if (upper < 'A' || upper > 'Z') {
        throw std::invalid_argument("letter must be in the range A-Z");
    }

    int n = upper - 'A';            // distance from 'A'
    int side = 2 * n + 1;           // width == height
    std::vector<std::string> result(side, std::string(side, ' '));

    for (int row = 0; row < side; ++row) {
        int lead = std::abs(n - row);            // leading (and trailing) spaces
        char ch  = static_cast<char>('A' + (n - lead));

        result[row][lead]               = ch;    // left character
        result[row][side - lead - 1]    = ch;    // right character (same pos for 'A')
    }

    return result;
}

}  // namespace diamond
