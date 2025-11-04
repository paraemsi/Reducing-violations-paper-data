#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace diamond {

 // Build a diamond for the given uppercase letter (e.g., 'A'..'Z').
 // Returns an empty vector if the letter is not supported.
[[nodiscard]] std::vector<std::string> rows(char letter);

}  // namespace diamond
