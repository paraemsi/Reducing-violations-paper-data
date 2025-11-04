#pragma once

#include <cstddef>
#include <cctype>
#include <stdexcept>
#include <string>
#include <vector>

namespace diamond {

 // Build a diamond up to the given letter (case-insensitive).
// Returns a vector of strings, each string being one row of the diamond.
// Throws std::invalid_argument if the input is not an alphabetic character.
namespace detail {
inline std::string make_line(char current, char max_letter) {
    const int n = static_cast<int>(max_letter - 'A');
    const int idx = static_cast<int>(current - 'A');
    const std::size_t width = static_cast<std::size_t>(n * 2 + 1);

    std::string line(width, ' ');
    const std::size_t left = static_cast<std::size_t>(n - idx);
    const std::size_t right = static_cast<std::size_t>(n + idx);

    line[left] = current;
    if (left != right) {
        line[right] = current;
    }
    return line;
}
}  // namespace detail

inline std::vector<std::string> rows(char letter) {
    if (!std::isalpha(static_cast<unsigned char>(letter))) {
        throw std::invalid_argument("diamond::rows expects an alphabetic character");
    }
    const char max_letter = static_cast<char>(std::toupper(static_cast<unsigned char>(letter)));

    std::vector<std::string> result;
    result.reserve(static_cast<std::size_t>((max_letter - 'A') * 2 + 1));

    for (int c = 'A'; c <= max_letter; ++c) {
        result.push_back(detail::make_line(static_cast<char>(c), max_letter));
    }
    for (int c = max_letter - 1; c >= 'A'; --c) {
        result.push_back(detail::make_line(static_cast<char>(c), max_letter));
    }

    return result;
}

}  // namespace diamond
