#pragma once

#include <string>
#include <vector>

namespace diamond {

/*
 * Build a textual diamond for the supplied uppercase letter.
 * The returned vector contains one string per row; each string
 * has identical width and trailing spaces so that the diamond
 * can be printed with `'\n'` joins.
 *
 * The function returns an empty vector if the input letter is
 * not found in the English alphabet.
 */
[[nodiscard]] auto rows(char letter) -> std::vector<std::string>;

}  // namespace diamond
