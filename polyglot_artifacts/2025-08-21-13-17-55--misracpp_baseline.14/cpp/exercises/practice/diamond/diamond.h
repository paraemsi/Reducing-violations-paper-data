#pragma once

#include <string>
#include <vector>

namespace diamond {

/**
 * Returns a vector of strings representing the diamond for the given uppercase letter.
 * Each string is a row of the diamond.
 * This function is provided for backward compatibility.
 */
std::vector<std::string> diamond(char letter);

// Alias for compatibility with tests expecting diamond::rows
std::vector<std::string> rows(char letter);

}  // namespace diamond
