#pragma once

#include <array>
#include <cstdint>
#include <string>

namespace yacht {

enum class category : std::uint8_t {
  ones = 0U,
  twos = 1U,
  threes = 2U,
  fours = 3U,
  fives = 4U,
  sixes = 5U,
  full_house = 6U,
  four_of_a_kind = 7U,
  little_straight = 8U,
  big_straight = 9U,
  choice = 10U,
  yacht = 11U
};

auto score(const std::array<std::uint8_t, 5U>& dice, const std::string& cat) -> std::uint32_t;

}  // namespace yacht
