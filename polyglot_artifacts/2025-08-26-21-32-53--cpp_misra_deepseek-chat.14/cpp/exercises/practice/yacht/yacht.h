#pragma once
#include <array>
#include <cstdint>
#include <string>

namespace yacht {

std::int32_t score(std::array<std::int8_t, 5> dice, const std::string& category);

}  // namespace yacht
