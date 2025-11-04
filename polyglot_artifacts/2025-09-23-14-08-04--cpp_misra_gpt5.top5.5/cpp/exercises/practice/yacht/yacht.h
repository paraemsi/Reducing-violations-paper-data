#ifndef YACHT_H_INCLUDED
#define YACHT_H_INCLUDED

#include <array>
#include <cstdint>
#include <cstddef>
#include <string>

namespace yacht {

constexpr std::size_t dice_count = static_cast<std::size_t>(5U);

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
using score_t = std::uint32_t;

auto score(const std::array<die_t, dice_count>& dice, category cat) noexcept -> score_t;
auto score(const std::array<die_t, dice_count>& dice, const char* cat) noexcept -> score_t;
auto score(const std::array<die_t, dice_count>& dice, const std::string& cat) noexcept -> score_t;

}  // namespace yacht

#endif  // YACHT_H_INCLUDED
