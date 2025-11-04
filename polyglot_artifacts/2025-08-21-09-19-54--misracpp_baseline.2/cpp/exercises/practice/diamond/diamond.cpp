#include "diamond.h"
#include <string>
#include <vector>
#include <stdexcept>
#include <cctype>

namespace diamond {

std::vector<std::string> rows(char letter) {
    if (!std::isupper(letter)) {
        throw std::invalid_argument("Input letter must be uppercase A-Z");
    }
    int n = letter - 'A';
    int size = 2 * n + 1;
    std::vector<std::string> result;

    for (int i = 0; i <= n; ++i) {
        std::string row(size, ' ');
        char ch = 'A' + i;
        row[n - i] = ch;
        row[n + i] = ch;
        result.push_back(row);
    }
    for (int i = n - 1; i >= 0; --i) {
        result.push_back(result[i]);
    }
    return result;
}

}  // namespace diamond
