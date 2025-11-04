#include "diamond.h"
#include <sstream>
#include <cctype>
#include <stdexcept>
#include <vector>

namespace diamond {

std::string make(char letter) {
    char upper = static_cast<char>(std::toupper(static_cast<unsigned char>(letter)));
    if (upper < 'A' || upper > 'Z') {
        throw std::invalid_argument("letter must be between 'A' and 'Z'");
    }

    int n = upper - 'A';
    int size = 2 * n + 1;
    std::ostringstream out;

    for (int i = 0; i < size; ++i) {
        int diff = (i <= n) ? i : size - 1 - i;
        int leading = n - diff;
        char c = static_cast<char>('A' + diff);

        out << std::string(leading, ' ');
        out << c;

        if (c != 'A') {
            int middle = 2 * diff - 1;
            out << std::string(middle, ' ');
            out << c;
        }

        out << std::string(leading, ' ');

        out << '\n';
    }

    std::string result = out.str();
    if (!result.empty() && result.back() == '\n') {
        result.pop_back();
    }
    return result;
}

std::vector<std::string> rows(char letter) {
    std::vector<std::string> lines;
    std::istringstream stream(make(letter));
    std::string line;
    while (std::getline(stream, line)) {
        lines.push_back(line);
    }
    return lines;
}

}  // namespace diamond
