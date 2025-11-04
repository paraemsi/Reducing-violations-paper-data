#pragma once

#include <string>
#include <vector>

namespace diamond {

/**
 * Generate a diamond shape for the supplied uppercase letter.
 *
 * The returned string is a square (width == height) whose rows are separated
 * by newline characters (`'\n'`).  Only standard ASCII uppercase letters
 * ('A'‥'Z') are accepted; any other input results in
 * `std::invalid_argument`.
 *
 * Example for letter 'C':
 *
 *   "··A··\n·B·B·\nC···C\n·B·B·\n··A··"
 */
std::vector<std::string> rows(char letter);

}  // namespace diamond
