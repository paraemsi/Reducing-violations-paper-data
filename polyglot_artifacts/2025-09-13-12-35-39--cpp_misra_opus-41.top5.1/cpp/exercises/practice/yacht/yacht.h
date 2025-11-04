#pragma once

#include <cstdint>
#include <vector>
#include <string>

namespace yacht {

// Calculate the score for a given set of dice and category
std::uint32_t score(std::vector<std::uint8_t> dice, const std::string& category);

}  // namespace yacht
