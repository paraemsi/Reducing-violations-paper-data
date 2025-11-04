#pragma once
#include <cstddef>
#include <string>
#include <vector>

namespace diamond {

// Build the diamond as a vector of strings; returns empty if input is not 'A'..'Z'
[[nodiscard]] std::vector<std::string> make_diamond(const char letter);

// Compatibility for tests: rows() is an alias of make_diamond
[[nodiscard]] std::vector<std::string> rows(const char letter);

// Build the diamond as a single string joined by '\n'; returns empty if input is not 'A'..'Z'
[[nodiscard]] std::string make_diamond_string(const char letter);

}  // namespace diamond
