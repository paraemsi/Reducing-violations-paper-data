#include "diamond.h"
#include <sstream>
#include <stdexcept>
#include <vector>
#include <cctype>

namespace diamond {

std::string make_diamond(char letter) {
    if (!std::isupper(static_cast<unsigned char>(letter)) || letter < 'A' || letter > 'Z') {
        throw std::invalid_argument("letter must be between 'A' and 'Z'");
    }

    const std::size_t size = static_cast<std::size_t>(letter - 'A');

    auto build_line = [size](std::size_t idx) {
        const char ch = static_cast<char>('A' + idx);
        const std::size_t leading = size - idx;
        const std::size_t inner = idx == 0 ? 0 : idx * 2 - 1;

        std::string line;
        line.reserve(size * 2 + 1);
        line.append(leading, ' ');
        line.push_back(ch);
        if (inner > 0) {
            line.append(inner, ' ');
            line.push_back(ch);
        }
        line.append(leading, ' ');
        return line;
    };

    std::vector<std::string> result;
    result.reserve(size * 2 + 1);

    for (std::size_t i = 0; i <= size; ++i) {
        result.emplace_back(build_line(i));
    }
    for (std::size_t i = size; i-- > 0;) {
        result.emplace_back(build_line(i));
    }

    std::ostringstream oss;
    for (std::size_t i = 0; i < result.size(); ++i) {
        oss << result[i];
        if (i + 1 < result.size()) {
            oss << '\n';
        }
    }
    return oss.str();
}

std::vector<std::string> rows(char letter) {
    if (!std::isupper(static_cast<unsigned char>(letter)) || letter < 'A' || letter > 'Z') {
        throw std::invalid_argument("letter must be between 'A' and 'Z'");
    }

    const std::size_t size = static_cast<std::size_t>(letter - 'A');

    auto build_line = [size](std::size_t idx) {
        const char ch = static_cast<char>('A' + idx);
        const std::size_t leading = size - idx;
        const std::size_t inner = idx == 0 ? 0 : idx * 2 - 1;

        std::string line;
        line.reserve(size * 2 + 1);
        line.append(leading, ' ');
        line.push_back(ch);
        if (inner > 0) {
            line.append(inner, ' ');
            line.push_back(ch);
        }
        line.append(leading, ' ');
        return line;
    };

    std::vector<std::string> result;
    result.reserve(size * 2 + 1);

    for (std::size_t i = 0; i <= size; ++i) {
        result.emplace_back(build_line(i));
    }
    for (std::size_t i = size; i-- > 0;) {
        result.emplace_back(build_line(i));
    }
    return result;
}

}  // namespace diamond
