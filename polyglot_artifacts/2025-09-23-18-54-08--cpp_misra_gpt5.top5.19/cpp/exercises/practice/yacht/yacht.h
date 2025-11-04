#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

namespace yacht {

using die_t = std::uint8_t;
using score_t = std::uint32_t;
constexpr std::size_t num_dice = 5U;

enum class category : std::uint8_t {
  ones = 0U,
  twos,
  threes,
  fours,
  fives,
  sixes,
  full_house,
  four_of_a_kind,
  little_straight,
  big_straight,
  choice,
  yacht
};

auto score(const std::array<die_t, num_dice>& dice, category cat) -> score_t;
auto score(const std::array<die_t, num_dice>& dice, const char* cat) -> score_t;

}  // namespace yacht
