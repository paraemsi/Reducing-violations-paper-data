#include "diamond.h"

#include <stdexcept>
#include <string>
#include <vector>

namespace diamond {

std::vector<std::string> rows(char letter) {
    if (letter < 'A' || letter > 'Z') {
        throw std::invalid_argument("Letter must be between 'A' and 'Z'");
    }

    const int n = letter - 'A';
    const int total_rows = 2 * n + 1;
    std::vector<std::string> result;
    result.reserve(total_rows);

    for (int row = 0; row < total_rows; ++row) {
        const int idx = row <= n ? row : 2 * n - row;
        const char ch = static_cast<char>('A' + idx);

        const int leading_spaces = n - idx;
        const int inner_spaces = idx == 0 ? 0 : 2 * idx - 1;

        std::string line;
        line.reserve(n + inner_spaces + 2);  // rough estimate

        line.append(leading_spaces, ' ');
        line.push_back(ch);

        if (inner_spaces > 0) {
            line.append(inner_spaces, ' ');
            line.push_back(ch);
        }

        line.append(leading_spaces, ' ');

        result.push_back(std::move(line));
    }

    return result;
}

std::string make(char letter) {
    if (letter < 'A' || letter > 'Z') {
        throw std::invalid_argument("Letter must be between 'A' and 'Z'");
    }

    const int n = letter - 'A';
    const int total_rows = 2 * n + 1;
    std::string diamond;
    diamond.reserve(total_rows * (total_rows + 1));  // rough estimate incl. '\n'

    for (int row = 0; row < total_rows; ++row) {
        const int idx = row <= n ? row : 2 * n - row;
        const char ch = static_cast<char>('A' + idx);

        const int leading_spaces = n - idx;
        const int inner_spaces = idx == 0 ? 0 : 2 * idx - 1;

        diamond.append(leading_spaces, ' ');
        diamond.push_back(ch);

        if (inner_spaces > 0) {
            diamond.append(inner_spaces, ' ');
            diamond.push_back(ch);
        }

        diamond.append(leading_spaces, ' ');

        if (row < total_rows - 1) {
            diamond.push_back('\n');
        }
    }

    return diamond;
}

}  // namespace diamond
