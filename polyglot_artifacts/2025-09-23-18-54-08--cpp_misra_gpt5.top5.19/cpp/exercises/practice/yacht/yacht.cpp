#include "yacht.h"

#include <array>
#include <cstddef>
#include <cstdint>
#include <string_view>

namespace yacht {

static constexpr score_t straight_score = 30U;
static constexpr score_t yacht_score = 50U;

auto score(const std::array<die_t, num_dice>& dice, const char* cat) -> score_t
{
    if (cat == nullptr) {
        return 0U;
    }

    const std::string_view sv{cat};

    if ((sv == std::string_view("yacht"))) {
        return score(dice, category::yacht);
    } else if ((sv == std::string_view("ones"))) {
        return score(dice, category::ones);
    } else if ((sv == std::string_view("twos"))) {
        return score(dice, category::twos);
    } else if ((sv == std::string_view("threes"))) {
        return score(dice, category::threes);
    } else if ((sv == std::string_view("fours"))) {
        return score(dice, category::fours);
    } else if ((sv == std::string_view("fives"))) {
        return score(dice, category::fives);
    } else if ((sv == std::string_view("sixes"))) {
        return score(dice, category::sixes);
    } else if ((sv == std::string_view("full house"))) {
        return score(dice, category::full_house);
    } else if ((sv == std::string_view("four of a kind"))) {
        return score(dice, category::four_of_a_kind);
    } else if ((sv == std::string_view("little straight"))) {
        return score(dice, category::little_straight);
    } else if ((sv == std::string_view("big straight"))) {
        return score(dice, category::big_straight);
    } else if ((sv == std::string_view("choice"))) {
        return score(dice, category::choice);
    } else {
        return 0U;
    }
}

auto score(const std::array<die_t, num_dice>& dice, category cat) -> score_t
{
    // Count occurrences of each face value (1..6)
    std::array<std::uint8_t, 7U> counts{};  // index 0 unused
    for (std::size_t i = 0U; i < num_dice; ++i) {
        const die_t d = dice[i];
        // Assuming input is valid (1..6) per problem statement
        counts[static_cast<std::size_t>(d)] =
            static_cast<std::uint8_t>(static_cast<std::uint32_t>(counts[static_cast<std::size_t>(d)]) + 1U);
    }

    // Sum of all dice
    score_t total = 0U;
    for (std::size_t i = 0U; i < num_dice; ++i) {
        total = static_cast<score_t>(total + static_cast<score_t>(dice[i]));
    }

    switch (cat) {
        case category::ones: {
            return static_cast<score_t>(static_cast<score_t>(counts[1U]) * static_cast<score_t>(1U));
        }
        case category::twos: {
            return static_cast<score_t>(static_cast<score_t>(counts[2U]) * static_cast<score_t>(2U));
        }
        case category::threes: {
            return static_cast<score_t>(static_cast<score_t>(counts[3U]) * static_cast<score_t>(3U));
        }
        case category::fours: {
            return static_cast<score_t>(static_cast<score_t>(counts[4U]) * static_cast<score_t>(4U));
        }
        case category::fives: {
            return static_cast<score_t>(static_cast<score_t>(counts[5U]) * static_cast<score_t>(5U));
        }
        case category::sixes: {
            return static_cast<score_t>(static_cast<score_t>(counts[6U]) * static_cast<score_t>(6U));
        }
        case category::full_house: {
            bool has_three = false;
            bool has_two = false;
            for (std::size_t face = 1U; face <= 6U; ++face) {
                if ((counts[face] == 3U)) {
                    has_three = true;
                }
                if ((counts[face] == 2U)) {
                    has_two = true;
                }
            }
            if ((has_three) && (has_two)) {
                return total;
            } else {
                return 0U;
            }
        }
        case category::four_of_a_kind: {
            for (std::size_t face = 1U; face <= 6U; ++face) {
                if ((counts[face] >= 4U)) {
                    return static_cast<score_t>(static_cast<score_t>(4U) * static_cast<score_t>(face));
                }
            }
            return 0U;
        }
        case category::little_straight: {
            if (((counts[1U] == 1U) && (counts[2U] == 1U) && (counts[3U] == 1U) && (counts[4U] == 1U) && (counts[5U] == 1U)) && (counts[6U] == 0U)) {
                return straight_score;
            } else {
                return 0U;
            }
        }
        case category::big_straight: {
            if (((counts[2U] == 1U) && (counts[3U] == 1U) && (counts[4U] == 1U) && (counts[5U] == 1U) && (counts[6U] == 1U)) && (counts[1U] == 0U)) {
                return straight_score;
            } else {
                return 0U;
            }
        }
        case category::choice: {
            return total;
        }
        case category::yacht: {
            for (std::size_t face = 1U; face <= 6U; ++face) {
                if ((counts[face] == 5U)) {
                    return yacht_score;
                }
            }
            return 0U;
        }
        default: {
            // Unreachable with defined enum values
            return 0U;
        }
    }
}

}  // namespace yacht
