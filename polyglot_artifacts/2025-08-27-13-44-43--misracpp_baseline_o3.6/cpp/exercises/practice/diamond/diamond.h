#pragma once
#include <string>
#include <vector>
#include <stdexcept>

namespace diamond {

// Return the diamond as a vector of rows, each row being a string.
// Throws std::invalid_argument if `letter` is not an uppercase 'A'-'Z'.
// Canonical API name expected by the unit tests.
std::vector<std::string> rows(char letter);

// Alias kept for internal/alternative naming.
std::vector<std::string> generate(char letter);

// Convenience helper that joins the rows with '\n' and returns a single string.
std::string generate_string(char letter);

}  // namespace diamond
