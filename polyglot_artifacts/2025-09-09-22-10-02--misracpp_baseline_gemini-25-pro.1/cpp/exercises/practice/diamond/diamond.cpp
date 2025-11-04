#include "diamond.h"

#include <stdexcept>

namespace diamond {

std::vector<std::string> rows(const char letter) {
    if (letter < 'A' || letter > 'Z') {
        throw std::invalid_argument("letter must be an uppercase letter");
    }
    int max_index = letter - 'A';
    std::vector<std::string> top_half;

    for (int i = 0; i <= max_index; ++i) {
        char current_char = 'A' + i;
        int outer_spaces = max_index - i;
        std::string row = std::string(outer_spaces, ' ');
        row += current_char;

        if (i > 0) {
            int inner_spaces = 2 * i - 1;
            row += std::string(inner_spaces, ' ');
            row += current_char;
        }

        row += std::string(outer_spaces, ' ');
        top_half.push_back(row);
    }

    std::vector<std::string> result = top_half;
    for (int i = max_index - 1; i >= 0; --i) {
        result.push_back(top_half[i]);
    }

    return result;
}

}  // namespace diamond
