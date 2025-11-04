#pragma once

#ifdef __cplusplus
#include <string>
#include <vector>

namespace diamond {

// Build a diamond of capital letters from 'A' up to the given letter.
// Returns a vector of strings with preserved leading/trailing spaces.
// Accepts letters 'A'-'Z' or 'a'-'z'; throws std::invalid_argument otherwise.
std::vector<std::string> rows(char letter);

}  // namespace diamond
#endif  // __cplusplus
