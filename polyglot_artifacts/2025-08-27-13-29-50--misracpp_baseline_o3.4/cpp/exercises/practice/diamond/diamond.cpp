#include "diamond.h"
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace diamond {

std::string make(char letter) {
    if (letter < 'A' || letter > 'Z') {
        throw std::invalid_argument("letter must be between 'A' and 'Z'");
    }

    const int n = letter - 'A';

    std::ostringstream oss;

    auto build_row = [&](int i) {
        const char row_letter = static_cast<char>('A' + i);
        const int leading_spaces = n - i;
        const int internal_spaces = (i == 0) ? 0 : 2 * i - 1;

        oss << std::string(leading_spaces, ' ');
        oss << row_letter;
        if (internal_spaces > 0) {
            oss << std::string(internal_spaces, ' ');
            oss << row_letter;
        }
        oss << std::string(leading_spaces, ' ');
        oss << '\n';
    };

    // Top half including the middle row
    for (int i = 0; i <= n; ++i) {
        build_row(i);
    }
    // Bottom half
    for (int i = n - 1; i >= 0; --i) {
        build_row(i);
    }

    std::string result = oss.str();
    if (!result.empty() && result.back() == '\n') {
        result.pop_back();  // remove trailing newline so width == height
    }
    return result;
}

std::vector<std::string> rows(char letter) {
    if (letter < 'A' || letter > 'Z') {
        throw std::invalid_argument("letter must be between 'A' and 'Z'");
    }

    const int n = letter - 'A';
    std::vector<std::string> result;
    const int width = 2 * n + 1;

    auto build_row_str = [&](int i) -> std::string {
        const char row_letter = static_cast<char>('A' + i);
        const int leading = n - i;
        const int internal = (i == 0) ? 0 : 2 * i - 1;

        std::string row;
        row.reserve(width);

        row.append(std::string(leading, ' '));
        row.push_back(row_letter);
        if (internal > 0) {
            row.append(std::string(internal, ' '));
            row.push_back(row_letter);
        }
        row.append(std::string(leading, ' '));
        return row;
    };

    // Top half including the middle row
    for (int i = 0; i <= n; ++i) {
        result.push_back(build_row_str(i));
    }
    // Bottom half
    for (int i = n - 1; i >= 0; --i) {
        result.push_back(build_row_str(i));
    }

    return result;
}

}  // namespace diamond
