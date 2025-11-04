#include "diamond.h"
#include <string>
#include <vector>
#include <cctype>
#include <stdexcept>

namespace diamond {

std::vector<std::string> rows(char letter) {
    if (!std::isalpha(letter) || !std::isupper(letter)) {
        throw std::invalid_argument("Input must be an uppercase letter A-Z");
    }

    int n = letter - 'A';
    int size = 2 * n + 1;
    std::vector<std::string> result(size);

    for (int i = 0; i <= n; ++i) {
        int outer_spaces = n - i;
        char ch = 'A' + i;
        std::string row(size, ' ');

        row[outer_spaces] = ch;
        row[size - outer_spaces - 1] = ch;

        result[i] = row;
        result[size - i - 1] = row;
    }
    return result;
}

std::string make_diamond(char letter) {
    std::vector<std::string> lines = rows(letter);
    std::string result;
    for (size_t i = 0; i < lines.size(); ++i) {
        result += lines[i];
        if (i + 1 < lines.size()) {
            result += '\n';
        }
    }
    return result;
}

}  // namespace diamond
