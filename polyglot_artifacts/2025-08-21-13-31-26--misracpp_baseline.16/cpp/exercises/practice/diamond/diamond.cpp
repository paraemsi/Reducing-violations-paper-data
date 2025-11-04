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
        int inner_spaces = (i == 0) ? 0 : 2 * i - 1;
        std::string row;
        row += std::string(outer_spaces, ' ');
        row += static_cast<char>('A' + i);
        if (inner_spaces > 0) {
            row += std::string(inner_spaces, ' ');
            row += static_cast<char>('A' + i);
        }
        row += std::string(outer_spaces, ' ');
        result.push_back(row);
    }
    for (int i = n - 1; i >= 0; --i) {
        int outer_spaces = n - i;
        int inner_spaces = (i == 0) ? 0 : 2 * i - 1;
        std::string row;
        row += std::string(outer_spaces, ' ');
        row += static_cast<char>('A' + i);
        if (inner_spaces > 0) {
            row += std::string(inner_spaces, ' ');
            row += static_cast<char>('A' + i);
        }
        row += std::string(outer_spaces, ' ');
        result.push_back(row);
    }
    // Remove the duplicate middle row
    if (n > 0) {
        result.erase(result.begin() + n + 1);
    }
    return result;
}

std::string make_diamond(char letter) {
    auto lines = rows(letter);
    std::ostringstream oss;
    for (size_t i = 0; i < lines.size(); ++i) {
        oss << lines[i];
        if (i + 1 != lines.size())
            oss << '\n';
    }
    return oss.str();
}

}  // namespace diamond
