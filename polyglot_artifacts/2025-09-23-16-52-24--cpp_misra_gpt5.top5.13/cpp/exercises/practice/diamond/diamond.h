#pragma once

#include <string>
#include <vector>

namespace diamond {

 // Build a diamond of uppercase letters from 'A' to the provided letter.
// Throws std::invalid_argument if letter is not an uppercase ASCII A-Z.
auto make(char letter) -> std::vector<std::string>;
auto rows(char letter) -> std::vector<std::string>;

}  // namespace diamond
