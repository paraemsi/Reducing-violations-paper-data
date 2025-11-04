#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace diamond {

 // Build a diamond string for the given letter.
 // Returns an empty string if the input is not an ASCII alphabetic letter.
[[nodiscard]] std::string make(char letter);
[[nodiscard]] std::vector<std::string> rows(char letter);

}  // namespace diamond
