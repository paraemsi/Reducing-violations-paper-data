#pragma once

#include <string>
#include <vector>

namespace diamond {

// Generates a diamond string for the supplied uppercase letter.
//
// Preconditions:
//   • 'letter' must be an uppercase English alphabet letter in the range 'A'..'Z'.
// Returns:
//   • A string that contains the complete diamond (rows separated by '\n').
//   • An empty string if the precondition is violated.
[[nodiscard]] auto rows(char letter) -> std::vector<std::string>;
[[nodiscard]] auto make_diamond(char letter) -> std::string;

}  // namespace diamond
