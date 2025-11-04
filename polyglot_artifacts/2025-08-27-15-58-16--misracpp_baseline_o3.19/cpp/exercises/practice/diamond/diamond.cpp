#include "diamond.h"

#include <sstream>
#include <stdexcept>
#include <vector>

namespace diamond {

static void validate_letter(char letter) {
    if (letter < 'A' || letter > 'Z') {
        throw std::invalid_argument("letter must be an uppercase character from 'A' to 'Z'");
    }
}

std::string make_diamond(char letter) {
    validate_letter(letter);

    const int n = letter - 'A';           // distance from 'A'
    const int size = 2 * n + 1;           // width == height
    std::ostringstream out;

    for (int row = 0; row < size; ++row) {
        const int idx = row <= n ? row : 2 * n - row;  // index of current letter
        const char c = static_cast<char>('A' + idx);
        const int leading_spaces = n - idx;

        // left padding
        out << std::string(leading_spaces, ' ');

        // first letter
        out << c;

        if (idx > 0) {
            // inner spacing between the two identical letters
            const int inner_spaces = 2 * idx - 1;
            out << std::string(inner_spaces, ' ') << c;
        }

        // right padding (mirrors leading_spaces)
        out << std::string(leading_spaces, ' ');

        if (row != size - 1) {
            out << '\n';
        }
    }

    return out.str();
}

std::vector<std::string> rows(char letter) {
    std::vector<std::string> result;
    std::istringstream ss(make_diamond(letter));
    std::string line;
    while (std::getline(ss, line)) {
        result.push_back(line);
    }
    return result;
}

}  // namespace diamond
