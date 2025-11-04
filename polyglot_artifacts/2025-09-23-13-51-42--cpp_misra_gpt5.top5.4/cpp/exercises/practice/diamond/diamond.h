#pragma once

#include <string>
#include <vector>

namespace diamond {

/* Generate a diamond string with the supplied uppercase letter at the widest point.
 * The output has equal width and height, includes trailing spaces for square shape,
 * and uses '\n' between rows without a trailing newline on the last row.
 */
auto make_diamond(char letter) -> std::string;
auto rows(char letter) -> std::vector<std::string>;

}  // namespace diamond
