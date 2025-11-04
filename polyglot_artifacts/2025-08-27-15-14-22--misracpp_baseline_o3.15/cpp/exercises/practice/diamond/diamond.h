#pragma once
#include <string>
#include <vector>

namespace diamond {

// Create a diamond for the supplied uppercase letter.
//
// Example (`make('C')`):
//   "··A··\n"
//   "·B·B·\n"
//   "C···C\n"
//   "·B·B·\n"
//   "··A··"
//
// The function keeps leading and trailing spaces intact to satisfy
// the kata rules. No trailing newline is appended to the returned string.
std::string make(char letter);
std::vector<std::string> rows(char letter);

}  // namespace diamond
