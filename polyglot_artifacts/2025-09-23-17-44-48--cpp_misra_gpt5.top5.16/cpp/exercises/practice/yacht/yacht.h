#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <string_view>
#include <initializer_list>

namespace yacht {

enum class category : std::uint8_t {
  ones,
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

using die_t = std::uint8_t;
constexpr std::size_t dice_count = static_cast<std::size_t>(5U);
using dice_roll = std::array<die_t, dice_count>;
using score_t = std::uint32_t;

[[nodiscard]] auto score(const dice_roll& dice, std::string_view cat) noexcept -> score_t;
[[nodiscard]] auto score(std::initializer_list<std::uint32_t> dice, std::string_view cat) noexcept -> score_t;

}  // namespace yacht
