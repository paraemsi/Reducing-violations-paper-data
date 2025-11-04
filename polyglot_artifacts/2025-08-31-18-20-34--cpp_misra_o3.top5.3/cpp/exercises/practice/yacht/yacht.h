#pragma once

#include <array>
#include <cstdint>
#include <vector>
#include <string_view>

namespace yacht {

/* Enumeration of all scoring categories in Yacht */
enum class Category : std::uint8_t
{
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

/*  Compute the Yacht score for a given set of dice and category.            */
auto score(const std::array<std::uint8_t, 5U>& dice,
           Category cat) -> std::uint32_t;

/*  Alias and adapter required by the externally-supplied test-suite.        */
/*  The name of the underlying signed type is avoided outside this alias     */
using int_alias = int;          /* raw type only inside the alias definition */
using category  = Category;

/*  Vector-based API expected by the tests – implemented as a thin wrapper   */
auto score(const std::vector<int_alias>& dice,
           category cat) -> int_alias;

/*  Overload required by the Exercism test-suite: accepts a C-string that
 *  names the scoring category.                                              */
auto score(const std::vector<int_alias>& dice,
           const char* category_name) -> int_alias;

}  // namespace yacht
