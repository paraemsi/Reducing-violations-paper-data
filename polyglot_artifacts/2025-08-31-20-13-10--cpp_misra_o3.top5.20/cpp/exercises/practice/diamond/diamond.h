#pragma once

#include <string>
#include <vector>

namespace diamond {

auto generate(char letter) -> std::string;
auto rows(char letter) -> std::vector<std::string>;

}  // namespace diamond
