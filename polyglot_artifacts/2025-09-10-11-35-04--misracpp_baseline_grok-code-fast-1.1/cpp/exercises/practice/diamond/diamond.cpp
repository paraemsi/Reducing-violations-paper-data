#include "diamond.h"

#include <string>
#include <vector>
#include <algorithm>

namespace diamond {

std::string rows(char letter) {
    if (letter < 'A' || letter > 'Z') return "";
    int size = 2 * (letter - 'A') + 1;
    int center = (size - 1) / 2;
    std::vector<std::string> rows(size, std::string(size, ' '));
    for (int i = 0; i < size; ++i) {
        char ch = 'A' + std::min(i, size - 1 - i);
        int dist = ch - 'A';
        rows[i][center - dist] = ch;
        if (dist > 0) {
            rows[i][center + dist] = ch;
        }
    }
    std::string result;
    for (const auto& row : rows) {
        result += row + "\n";
    }
    return result;
}

}  // namespace diamond
