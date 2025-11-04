#include "diamond.h"

#include <sstream>
#include <cctype>
#include <stdexcept>
#include <vector>
#include <algorithm>

namespace diamond {

std::vector<std::string> rows(char letter) {
    if (!std::isupper(letter)) {
        throw std::invalid_argument("Input must be an uppercase letter A-Z");
    }

    int n = letter - 'A';
    int size = 2 * n + 1;
    std::vector<std::string> result(size);

    for (int i = 0; i <= n; ++i) {
        int outer_spaces = n - i;
        int inner_spaces = (i == 0) ? 0 : 2 * i - 1;
        std::string row;

        row.append(outer_spaces, ' ');
        row += ('A' + i);
        if (i > 0) {
            row.append(inner_spaces, ' ');
            row += ('A' + i);
        }
        row.append(outer_spaces, ' ');
        result[i] = row;
        result[size - 1 - i] = row; // vertical symmetry
    }
    return result;
}

std::string make(char letter) {
    std::vector<std::string> r = rows(letter);
    std::ostringstream oss;
    for (size_t i = 0; i < r.size(); ++i) {
        oss << r[i];
        if (i + 1 < r.size()) {
            oss << '\n';
        }
    }
    return oss.str();
}

}  // namespace diamond
