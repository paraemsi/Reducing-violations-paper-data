#pragma once
#include <cstddef>
#include <string>
#include <vector>

namespace diamond {

std::vector<std::string> make(char letter);
std::vector<std::string> rows(char letter);   // alias kept for legacy tests

}  // namespace diamond
