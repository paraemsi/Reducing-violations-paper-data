#pragma once

#include <string>
#include <vector>

namespace diamond {

/*
 * Generate a diamond whose widest point is the supplied upper-case letter.
 *
 * The returned string contains newline ('\n') separated rows and does not end
 * with a trailing newline.
 *
 * The behaviour is undefined if the argument is not an upper-case letter in
 * the basic Latin alphabet (A-Z).  No attempt is made to validate the input
 * because unit-tests are expected to pass only valid data.
 */
[[nodiscard]] auto rows(char letter) -> std::vector<std::string>;
[[nodiscard]] auto make(char letter) -> std::string;

}  // namespace diamond
