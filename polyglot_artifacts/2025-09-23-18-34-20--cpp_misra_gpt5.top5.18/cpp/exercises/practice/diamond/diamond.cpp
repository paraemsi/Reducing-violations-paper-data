#include "diamond.h"
#include <cstddef>
#include <string>
#include <vector>

namespace diamond {

std::vector<std::string> rows(char letter) {
    static const std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const std::size_t pos = alphabet.find(letter);
    if (pos == std::string::npos) {
        return std::vector<std::string>();
    }

    const std::size_t height = (pos * static_cast<std::size_t>(2U)) + static_cast<std::size_t>(1U);

    std::vector<std::string> out;
    out.reserve(height);

    for (std::size_t i = static_cast<std::size_t>(0U); (i < height); ++i) {
        std::size_t idx = static_cast<std::size_t>(0U);
        if (i <= pos) {
            idx = i;
        } else {
            idx = ((height - static_cast<std::size_t>(1U)) - i);
        }

        const std::size_t lead = pos - idx;
        const char ch = alphabet[idx];

        std::string line;
        line.reserve(height);

        line.append(lead, ' ');
        line.push_back(ch);

        if (idx != static_cast<std::size_t>(0U)) {
            const std::size_t inner = ((idx * static_cast<std::size_t>(2U)) - static_cast<std::size_t>(1U));
            line.append(inner, ' ');
            line.push_back(ch);
        }

        line.append(lead, ' ');
        out.emplace_back(line);
    }

    return out;
}

std::string make_diamond(char letter) {
    const std::vector<std::string> lines = rows(letter);
    if (lines.empty()) {
        return std::string();
    }

    std::size_t total = static_cast<std::size_t>(0U);
    for (const std::string& line : lines) {
        total = total + line.size();
    }
    if (lines.size() > static_cast<std::size_t>(1U)) {
        total = total + (lines.size() - static_cast<std::size_t>(1U));
    }

    std::string result;
    result.reserve(total);

    for (std::size_t i = static_cast<std::size_t>(0U); (i < lines.size()); ++i) {
        result.append(lines[i]);
        if ((i + static_cast<std::size_t>(1U)) < lines.size()) {
            result.push_back('\n');
        }
    }

    return result;
}

}  // namespace diamond
