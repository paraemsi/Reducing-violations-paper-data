#pragma once

#include <string>
#include <vector>

namespace diamond {

[[nodiscard]] std::vector<std::string> make_diamond(char letter);

// Alias for test compatibility
[[nodiscard]] inline std::vector<std::string> rows(char letter) {
    return make_diamond(letter);
}

}  // namespace diamond
