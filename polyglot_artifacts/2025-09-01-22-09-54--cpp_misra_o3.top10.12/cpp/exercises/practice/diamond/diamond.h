#pragma once

#include <string>
#include <vector>

#if (__cplusplus >= 201703L)
#define DIAMOND_NODISCARD [[nodiscard]]
#else
#define DIAMOND_NODISCARD
#endif

namespace diamond {

/*
 * Generate a diamond string whose widest point is the supplied
 * uppercase letter.  The returned string contains embedded '\n'
 * characters but no trailing newline.
 */
[[nodiscard]] auto make(char const letter) -> std::string;
[[nodiscard]] auto rows(char const letter) -> std::vector<std::string>;

}  // namespace diamond
