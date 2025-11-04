#include "diamond.h"

namespace diamond {

std::vector<std::string> rows(char letter) {
    std::vector<std::string> result;
    if (letter < 'A' || letter > 'Z') {
        return result;
    }
    int n = letter - 'A';
    int size = 2 * n + 1;

    // Top half and middle
    for (int i = 0; i <= n; ++i) {
        int outer_spaces = n - i;
        int inner_spaces = i == 0 ? 0 : 2 * i - 1;
        std::string row;
        row.append(outer_spaces, ' ');
        row += ('A' + i);
        if (i > 0) {
            row.append(inner_spaces, ' ');
            row += ('A' + i);
        }
        row.append(outer_spaces, ' ');
        result.push_back(row);
    }
    // Bottom half
    for (int i = n - 1; i >= 0; --i) {
        int outer_spaces = n - i;
        int inner_spaces = i == 0 ? 0 : 2 * i - 1;
        std::string row;
        row.append(outer_spaces, ' ');
        row += ('A' + i);
        if (i > 0) {
            row.append(inner_spaces, ' ');
            row += ('A' + i);
        }
        row.append(outer_spaces, ' ');
        result.push_back(row);
    }
    return result;
}

std::string make_diamond(char letter) {
    auto lines = rows(letter);
    std::string result;
    for (size_t i = 0; i < lines.size(); ++i) {
        result += lines[i];
        if (i + 1 != lines.size()) {
            result += '\n';
        }
    }
    return result;
}

}  // namespace diamond
