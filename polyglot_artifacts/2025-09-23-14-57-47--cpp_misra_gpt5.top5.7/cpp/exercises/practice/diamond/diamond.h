#pragma once
#include <string>
#include <vector>

namespace diamond {

using letter_t = char;

/**
 * Build a diamond of uppercase letters up to the given letter.
 * If the input is not an alphabetic ASCII letter [A-Za-z], returns an empty vector.
 */
std::vector<std::string> make_diamond(letter_t letter);
std::vector<std::string> rows(letter_t letter);

}  // namespace diamond
