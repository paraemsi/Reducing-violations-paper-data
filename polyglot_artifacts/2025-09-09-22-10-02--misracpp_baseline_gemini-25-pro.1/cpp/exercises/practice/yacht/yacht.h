#pragma once

#include <array>
#include <string_view>

namespace yacht {

constexpr int score(const std::array<int, 5>& dice, std::string_view category);

}  // namespace yacht
