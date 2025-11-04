#include "yacht.h"
#include <cstddef>

namespace yacht {
namespace detail {

category parse_category(const std::string& name) noexcept
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
        return category::choice;
    }
}

std::uint32_t score_from_counts(const std::array<std::uint32_t, 7U>& counts, category cat) noexcept
{
    auto sum_all = [&counts]() -> std::uint32_t {
        std::uint32_t total = static_cast<std::uint32_t>(0U);
        for (std::size_t f = 1U; f <= 6U; ++f) {
            total = (total + (static_cast<std::uint32_t>(f) * counts[f]));
        }
        return total;
    };

    switch (cat) {
        case category::ones:
        case category::twos:
        case category::threes:
        case category::fours:
        case category::fives:
        case category::sixes: {
            // Enum values for ones..sixes are 0..5; add 1 to get face value and index.
            const std::size_t face_index = (static_cast<std::size_t>(static_cast<std::uint8_t>(cat)) + static_cast<std::size_t>(1U));
            const std::uint32_t face_value = (static_cast<std::uint32_t>(static_cast<std::uint8_t>(cat)) + static_cast<std::uint32_t>(1U));
            return (face_value * counts[face_index]);
        }

        case category::full_house: {
            bool has_three = false;
            bool has_two = false;

            for (std::size_t f = 1U; f <= 6U; ++f) {
                if ((counts[f] == static_cast<std::uint32_t>(3U))) {
                    has_three = true;
                } else if ((counts[f] == static_cast<std::uint32_t>(2U))) {
                    has_two = true;
                } else if ((counts[f] == static_cast<std::uint32_t>(5U))) {
                    // A yacht is not a full house.
                    return static_cast<std::uint32_t>(0U);
                } else {
                    // continue checking
                }
            }

            if (has_three && has_two) {
                return sum_all();
            } else {
                return static_cast<std::uint32_t>(0U);
            }
        }

        case category::four_of_a_kind: {
            for (std::size_t f = 1U; f <= 6U; ++f) {
                if ((counts[f] >= static_cast<std::uint32_t>(4U))) {
                    return (static_cast<std::uint32_t>(4U) * static_cast<std::uint32_t>(f));
                } else {
                    // continue checking
                }
            }
            return static_cast<std::uint32_t>(0U);
        }

        case category::little_straight: {
            if ((counts[1U] == static_cast<std::uint32_t>(1U)) &&
                (counts[2U] == static_cast<std::uint32_t>(1U)) &&
                (counts[3U] == static_cast<std::uint32_t>(1U)) &&
                (counts[4U] == static_cast<std::uint32_t>(1U)) &&
                (counts[5U] == static_cast<std::uint32_t>(1U)) &&
                (counts[6U] == static_cast<std::uint32_t>(0U))) {
                return static_cast<std::uint32_t>(30U);
            } else {
                return static_cast<std::uint32_t>(0U);
            }
        }

        case category::big_straight: {
            if ((counts[1U] == static_cast<std::uint32_t>(0U)) &&
                (counts[2U] == static_cast<std::uint32_t>(1U)) &&
                (counts[3U] == static_cast<std::uint32_t>(1U)) &&
                (counts[4U] == static_cast<std::uint32_t>(1U)) &&
                (counts[5U] == static_cast<std::uint32_t>(1U)) &&
                (counts[6U] == static_cast<std::uint32_t>(1U))) {
                return static_cast<std::uint32_t>(30U);
            } else {
                return static_cast<std::uint32_t>(0U);
            }
        }

        case category::choice: {
            return sum_all();
        }

        case category::yacht: {
            for (std::size_t f = 1U; f <= 6U; ++f) {
                if ((counts[f] == static_cast<std::uint32_t>(5U))) {
                    return static_cast<std::uint32_t>(50U);
                } else {
                    // continue checking
                }
            }
            return static_cast<std::uint32_t>(0U);
        }

        default: {
            return static_cast<std::uint32_t>(0U);
        }
    }
}

}  // namespace detail
}  // namespace yacht
