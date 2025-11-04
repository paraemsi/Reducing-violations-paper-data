#pragma once

#include <string>
#include <vector>

namespace diamond {

[[nodiscard]] auto rows(char target) -> std::vector<std::string>;
[[nodiscard]] auto make(char target) -> std::string;

}  // namespace diamond
