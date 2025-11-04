#pragma once

#include <string>
#include <vector>

namespace diamond {

// Return the diamond rows for the supplied uppercase letter.
// Each element in the returned vector represents one row and does
// not include a trailing newline. Behaviour is undefined for
// characters outside the range 'A'-'Z'.
std::vector<std::string> rows(char letter);

}  // namespace diamond
