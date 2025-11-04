#include "diamond.h"

#include <sstream>
#include <cctype>
#include <algorithm>
#include <vector>

namespace diamond {

std::vector<std::string> rows(char letter) {
    letter = std::toupper(letter);
    if (letter < 'A' || letter > 'Z') {
        return {};
    }
    int n = letter - 'A';
    int size = 2 * n + 1;
    std::vector<std::string> result;

    for (int i = 0; i <= n; ++i) {
        int outer_spaces = n - i;
        int inner_spaces = i == 0 ? 0 : 2 * i - 1;
        std::string row(size, ' ');
        row[outer_spaces] = 'A' + i;
        if (i != 0) {
            row[size - outer_spaces - 1] = 'A' + i;
        }
        result.push_back(row);
    }
    for (int i = n - 1; i >= 0; --i) {
        int outer_spaces = n - i;
        int inner_spaces = i == 0 ? 0 : 2 * i - 1;
        std::string row(size, ' ');
        row[outer_spaces] = 'A' + i;
        if (i != 0) {
            row[size - outer_spaces - 1] = 'A' + i;
        }
        result.push_back(row);
    }
    return result;
}

std::string make_diamond(char letter) {
    auto lines = rows(letter);
    std::ostringstream oss;
    for (size_t i = 0; i < lines.size(); ++i) {
        oss << lines[i];
        if (i + 1 != lines.size()) {
            oss << '\n';
        }
    }
    return oss.str();
}

}  // namespace diamond
