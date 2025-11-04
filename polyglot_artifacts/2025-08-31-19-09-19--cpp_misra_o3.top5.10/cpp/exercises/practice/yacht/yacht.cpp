#include "yacht.h"

#include <algorithm>
#include <array>
#include <numeric>
#include <vector>
#include <string_view>
#include <cstddef>

namespace yacht {

namespace {

/* Convert textual category name used by tests to enumeration value */
auto to_category(std::string_view name) -> category
{
    if ((name == "ones")) {
        return category::ones;
    } else if ((name == "twos")) {
        return category::twos;
    } else if ((name == "threes")) {
        return category::threes;
    } else if ((name == "fours")) {
        return category::fours;
    } else if ((name == "fives")) {
        return category::fives;
    } else if ((name == "sixes")) {
        return category::sixes;
    } else if ((name == "full house")) {
        return category::full_house;
    } else if ((name == "four of a kind")) {
        return category::four_of_a_kind;
    } else if ((name == "little straight")) {
        return category::little_straight;
    } else if ((name == "big straight")) {
        return category::big_straight;
    } else if ((name == "choice")) {
        return category::choice;
    } else if ((name == "yacht")) {
        return category::yacht;
    } else {
        return category::choice; /* fallback, should not occur in tests */
    }
}

}  // unnamed namespace

auto score(const std::vector<die_value_t>& dice, category cat) -> score_t
{
    /* tally occurrences of each face (index 0 unused) */
    std::array<std::uint8_t, 7U> counts{};
    for (const auto value : dice) {
        ++counts[static_cast<std::size_t>(value)];
    }

    const score_t total = std::accumulate(
        dice.begin(),
        dice.end(),
        static_cast<score_t>(0U),
        [](score_t acc, die_value_t v) { return (acc + static_cast<score_t>(v)); });

    switch (cat) {
        case category::ones: {
            return (static_cast<score_t>(counts[1U]) * 1U);
        }
        case category::twos: {
            return (static_cast<score_t>(counts[2U]) * 2U);
        }
        case category::threes: {
            return (static_cast<score_t>(counts[3U]) * 3U);
        }
        case category::fours: {
            return (static_cast<score_t>(counts[4U]) * 4U);
        }
        case category::fives: {
            return (static_cast<score_t>(counts[5U]) * 5U);
        }
        case category::sixes: {
            return (static_cast<score_t>(counts[6U]) * 6U);
        }
        case category::full_house: {
            bool has_three {false};
            bool has_two   {false};
            for (std::size_t face = 1U; face <= 6U; ++face) {
                if (counts[face] == 3U) {
                    has_three = true;
                }
                if (counts[face] == 2U) {
                    has_two = true;
                }
            }
            if (has_three && has_two) {
                return total;
            } else {
                return 0U;
            }
        }
        case category::four_of_a_kind: {
            for (std::size_t face = 1U; face <= 6U; ++face) {
                if (counts[face] >= 4U) {
                    return (static_cast<score_t>(face) * 4U);
                }
            }
            return 0U;
        }
        case category::little_straight: {
            if ((counts[1U] == 1U) && (counts[2U] == 1U) && (counts[3U] == 1U) &&
                (counts[4U] == 1U) && (counts[5U] == 1U) && (counts[6U] == 0U)) {
                return 30U;
            } else {
                return 0U;
            }
        }
        case category::big_straight: {
            if ((counts[1U] == 0U) && (counts[2U] == 1U) && (counts[3U] == 1U) &&
                (counts[4U] == 1U) && (counts[5U] == 1U) && (counts[6U] == 1U)) {
                return 30U;
            } else {
                return 0U;
            }
        }
        case category::choice: {
            return total;
        }
        case category::yacht: {
            for (std::size_t face = 1U; face <= 6U; ++face) {
                if (counts[face] == 5U) {
                    return 50U;
                }
            }
            return 0U;
        }
        default: {
            return 0U;  /* should be unreachable */
        }
    }
}

auto score(const std::vector<die_value_t>& dice, std::string_view cat) -> score_t
{
    return score(dice, to_category(cat));
}

}  // namespace yacht
