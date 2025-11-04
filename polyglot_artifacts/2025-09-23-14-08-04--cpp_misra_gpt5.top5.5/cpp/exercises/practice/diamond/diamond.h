#pragma once

#include <string>
#include <vector>


namespace diamond {

// Generate a diamond string for the given uppercase letter ('A'..'Z').
// Returns an empty string if the input is outside 'A'..'Z'.
// The result preserves trailing spaces on each line and has no trailing newline.
std::vector<std::string> rows(char letter);
std::string make(char letter);

}  // namespace diamond
