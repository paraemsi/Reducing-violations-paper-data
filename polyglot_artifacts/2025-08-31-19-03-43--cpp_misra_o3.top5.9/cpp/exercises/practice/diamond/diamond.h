#pragma once

#include <string>
#include <vector>
#include <cstdint>

namespace diamond {

/*  Build the diamond for the supplied uppercase letter.
 *  Throws std::invalid_argument if the letter is not in ['A' .. 'Z'].
 */
auto make_diamond(char letter) -> std::vector<std::string>;
auto rows(char letter) -> std::vector<std::string>;

}  // namespace diamond
