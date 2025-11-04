#pragma once
#include <string>
#include <vector>

namespace diamond {

// Generate a diamond string for the given letter.
// Accepts 'A'..'Z' or 'a'..'z'. Returns an empty string for invalid input.
// The returned string contains spaces, including trailing spaces on each line,
// and uses '\n' as the line separator. There is no trailing newline at the end.
std::vector<std::string> rows(char letter);
std::string make(char letter);

}  // namespace diamond
