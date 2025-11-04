#pragma once

#include <string>
#include <vector>

namespace diamond {

/**
 * Generate a diamond string whose widest point is the supplied letter.
 *
 * Example for letter 'C':
 *   "··A··\n·B·B·\nC···C\n·B·B·\n··A··\n"
 * (Spaces shown with · for clarity.)
 *
 * The returned string always ends with a single '\n' newline.
 *
 * @param letter An uppercase letter from 'A' to 'Z'.
 * @return A square diamond as a std::string.
 * @throws std::invalid_argument if letter is outside ['A','Z'].
 */
std::string make_diamond(char letter);
std::vector<std::string> rows(char letter);

}  // namespace diamond
