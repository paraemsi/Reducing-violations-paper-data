#pragma once

#include <string>
#include <vector>

namespace diamond {

/*  Generate a diamond where the supplied character appears at the widest point.
    The returned std::string contains newline-separated rows. */
[[nodiscard]] auto rows(char letter) -> std::vector<std::string>;
[[nodiscard]] auto generate(char letter) -> std::string;

}  // namespace diamond
