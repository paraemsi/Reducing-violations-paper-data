#include "yacht.h"

#include <array>
#include <cstdint>
#include <cstddef>
#include <string_view>

namespace yacht {

namespace {

auto build_counts(const std::array<std::uint8_t, 5U>& dice) -> std::array<std::uint32_t, 7U>
{
    std::array<std::uint32_t, 7U> counts{};
    for (std::size_t i = 0U; i < dice.size(); ++i) {
        const std::size_t idx = static_cast<std::size_t>(dice[i]);
        counts[idx] = (counts[idx] + 1U);
    }
    return counts;
}

auto sum_dice(const std::array<std::uint8_t, 5U>& dice) -> std::uint32_t
{
    std::uint32_t sum = 0U;
    for (std::size_t i = 0U; i < dice.size(); ++i) {
        sum = (sum + static_cast<std::uint32_t>(dice[i]));
    }
    return sum;
}

auto has_n_of_a_kind(const std::array<std::uint32_t, 7U>& counts, std::uint32_t n) -> bool
{
    for (std::size_t face = 1U; face <= 6U; ++face) {
        if ((counts[face] >= n)) {
            return true;
        } else {
            // continue
        }
    }
    return false;
}

auto parse_category(std::string_view name) -> category
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

}  // unnamed namespace

auto score(const std::array<std::uint8_t, 5U>& dice, std::string_view cat) -> std::uint32_t
{
    const auto counts = build_counts(dice);
    const category cat_enum = parse_category(cat);

    switch (cat_enum) {
        case category::ones:
        case category::twos:
        case category::threes:
        case category::fours:
        case category::fives:
        case category::sixes: {
            std::uint32_t face_val = 0U;
            if ((cat_enum == category::ones)) {
                face_val = 1U;
            } else if ((cat_enum == category::twos)) {
                face_val = 2U;
            } else if ((cat_enum == category::threes)) {
                face_val = 3U;
            } else if ((cat_enum == category::fours)) {
                face_val = 4U;
            } else if ((cat_enum == category::fives)) {
                face_val = 5U;
            } else {
                face_val = 6U;
            }
            const std::size_t idx = static_cast<std::size_t>(face_val);
            return ((counts[idx]) * face_val);
        }

        case category::full_house: {
            bool has_three = false;
            bool has_two = false;

            for (std::size_t face = 1U; face <= 6U; ++face) {
                if ((counts[face] == 3U)) {
                    has_three = true;
                } else if ((counts[face] == 2U)) {
                    has_two = true;
                } else if ((counts[face] == 5U)) {
                    // A yacht is not a full house
                    has_three = false;
                    has_two = false;
                } else {
                    // no-op
                }
            }

            if ((has_three && has_two)) {
                return sum_dice(dice);
            } else {
                return 0U;
            }
        }

        case category::four_of_a_kind: {
            for (std::size_t face = 1U; face <= 6U; ++face) {
                if ((counts[face] >= 4U)) {
                    const std::uint32_t fv = static_cast<std::uint32_t>(face);
                    return (4U * fv);
                } else {
                    // continue
                }
            }
            return 0U;
        }

        case category::little_straight: {
            bool ok = true;
            for (std::size_t face = 1U; face <= 5U; ++face) {
                if (!(counts[face] == 1U)) {
                    ok = false;
                } else {
                    // continue
                }
            }
            if ((ok && (counts[6U] == 0U))) {
                return 30U;
            } else {
                return 0U;
            }
        }

        case category::big_straight: {
            bool ok = true;
            for (std::size_t face = 2U; face <= 6U; ++face) {
                if (!(counts[face] == 1U)) {
                    ok = false;
                } else {
                    // continue
                }
            }
            if ((ok && (counts[1U] == 0U))) {
                return 30U;
            } else {
                return 0U;
            }
        }

        case category::choice: {
            return sum_dice(dice);
        }

        case category::yacht: {
            if ((has_n_of_a_kind(counts, 5U))) {
                return 50U;
            } else {
                return 0U;
            }
        }

        default: {
            return 0U;
        }
    }
}

}  // namespace yacht
