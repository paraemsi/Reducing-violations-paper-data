#pragma once

#include <vector>
#include <cstdint>
#include <string_view>

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

auto score(const std::vector<std::uint8_t> & dice, category cat) -> std::uint32_t;

/* Convenience overload – accepts the category name as text and
 * forwards to the strongly-typed version used internally. */
auto score(const std::vector<std::uint8_t> & dice, std::string_view cat_name) -> std::uint32_t;

}  // namespace yacht
