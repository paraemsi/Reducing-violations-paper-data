#pragma once

#include <string>
#include <vector>

namespace diamond {

/**
 * Build a diamond shape for the supplied upper-case letter.
 *
 * The returned vector contains one string per line; no trailing new-lines are
 * included so that callers can join/print as they wish.
 *
 * If the input is outside the range 'A'..'Z', an empty vector is returned.
 */
[[nodiscard]] auto make(char letter) -> std::vector<std::string>;

/**
 * Convenience wrapper used by the unit tests.
 * Simply forwards to make().
 */
[[nodiscard]] auto rows(char letter) -> std::vector<std::string>;

}  // namespace diamond
