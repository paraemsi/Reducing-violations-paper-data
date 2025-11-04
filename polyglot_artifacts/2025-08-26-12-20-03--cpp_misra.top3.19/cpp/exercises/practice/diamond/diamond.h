#pragma once

#include <string>
#include <vector>

namespace diamond {

[[nodiscard]] std::vector<std::string> make_diamond(char letter);

// Alias for test compatibility: rows is the required function name in tests
[[nodiscard]] std::vector<std::string> rows(char letter);

}  // namespace diamond
