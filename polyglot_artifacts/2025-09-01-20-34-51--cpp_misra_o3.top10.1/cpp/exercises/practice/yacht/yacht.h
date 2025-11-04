#pragma once

#include <cstdint>
#include <vector>
#include <string_view>

namespace yacht {

/* Enumeration of all possible Yacht scoring categories */
enum class category : std::uint16_t {
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

using die_t = std::uint16_t;

/*  Calculate the Yacht score for a given set of dice in the chosen category.      */
/*  `dice` must contain exactly five elements with values in the range [1, 6].     */
/*  The function is `[[nodiscard]]` to enforce use of the returned score.          */
[[nodiscard]] auto score(const std::vector<die_t>& dice,
                         category                      cat) -> std::uint32_t;

/*  Compatibility overload for callers that supply `int` dice values           */
/*  (e.g. the Exercism unit tests). Explicitly converts each value to          */
/*  std::uint8_t after checking it is within the valid [1, 6] range.           */
[[nodiscard]] auto score(const std::vector<int>& dice,
                         category              cat) -> std::uint32_t;

/*  Overloads accepting the category as a textual value (needed by tests)    */
[[nodiscard]] auto score(const std::vector<die_t>& dice,
                         std::string_view          cat_name) -> std::uint32_t;

[[nodiscard]] auto score(const std::vector<int>& dice,
                         std::string_view cat_name) -> std::uint32_t;

}  // namespace yacht
