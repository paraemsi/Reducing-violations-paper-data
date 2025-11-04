#include "diamond.h"

#include <cstddef>
#include <string>
#include <vector>

namespace diamond {

namespace {
    // Returns true if c is one of 'A'..'Z'
    bool is_valid_upper_letter(const char c) {
        const std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        const std::size_t pos = alphabet.find(c);
        return (pos != std::string::npos);
    }
}  // namespace

std::vector<std::string> make_diamond(const char letter) {
    const std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::vector<std::string> output;

    if (!is_valid_upper_letter(letter)) {
        return output;
    }

    const std::size_t pos = alphabet.find(letter);
    const std::size_t height = ((pos * static_cast<std::size_t>(2)) + static_cast<std::size_t>(1));
    const std::size_t width = height;

    output.reserve(height);

    for (std::size_t row = static_cast<std::size_t>(0); row < height; ++row) {
        std::string line(width, ' ');
        std::size_t idx = static_cast<std::size_t>(0);

        if (row <= pos) {
            idx = row;
        } else {
            idx = ((height - static_cast<std::size_t>(1)) - row);
        }

        const char ch = alphabet[idx];
        const std::size_t left = (pos - idx);
        const std::size_t right = (pos + idx);

        line[left] = ch;
        line[right] = ch;

        output.push_back(line);
    }

    return output;
}

std::vector<std::string> rows(const char letter) {
    return make_diamond(letter);
}

std::string make_diamond_string(const char letter) {
    const std::vector<std::string> lines = make_diamond(letter);
    if (lines.empty()) {
        return std::string();
    }

    const std::size_t height = lines.size();
    const std::size_t width = lines[static_cast<std::size_t>(0)].size();
    const std::size_t total_capacity =
        ((width * height) + (height - static_cast<std::size_t>(1)));

    std::string result;
    result.reserve(total_capacity);

    for (std::size_t i = static_cast<std::size_t>(0); i < height; ++i) {
        result += lines[i];
        if (((i + static_cast<std::size_t>(1)) < height)) {
            result.push_back('\n');
        }
    }

    return result;
}

}  // namespace diamond
