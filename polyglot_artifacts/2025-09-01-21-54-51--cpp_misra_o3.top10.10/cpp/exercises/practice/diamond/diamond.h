#pragma once

#include <string>
#include <vector>

namespace diamond {

[[nodiscard]] auto make_diamond(char letter) -> std::string;
[[nodiscard]] auto rows(char letter) -> std::vector<std::string>;

}  // namespace diamond
