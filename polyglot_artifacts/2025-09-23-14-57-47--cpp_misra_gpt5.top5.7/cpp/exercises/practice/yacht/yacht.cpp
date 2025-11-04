#include "yacht.h"

#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <numeric>
#include <initializer_list>

namespace yacht {

namespace {
    // Count occurrences of die faces 1..6; index 0 is unused
    auto count_faces(const std::vector<std::int32_t>& dice) -> std::array<std::int32_t, 7U> {
        std::array<std::int32_t, 7U> counts{};
        counts.fill(static_cast<std::int32_t>(0));

        for (const std::int32_t value : dice) {
            if ((value >= static_cast<std::int32_t>(1)) && (value <= static_cast<std::int32_t>(6))) {
                const std::size_t idx = static_cast<std::size_t>(value);
                counts[idx] = (counts[idx] + static_cast<std::int32_t>(1));
            } else {
                // Out-of-range values are ignored by specification guarantees
            }
        }
        return counts;
    }

    auto sum_dice(const std::vector<std::int32_t>& dice) -> std::int32_t {
        return std::accumulate(dice.begin(), dice.end(), static_cast<std::int32_t>(0));
    }
}  // namespace

auto score(const std::vector<std::int32_t>& dice, category cat) -> std::int32_t {
    const std::array<std::int32_t, 7U> counts = count_faces(dice);

    switch (cat) {
        case category::ones: {
            return (counts[1U] * static_cast<std::int32_t>(1));
        }
        case category::twos: {
            return (counts[2U] * static_cast<std::int32_t>(2));
        }
        case category::threes: {
            return (counts[3U] * static_cast<std::int32_t>(3));
        }
        case category::fours: {
            return (counts[4U] * static_cast<std::int32_t>(4));
        }
        case category::fives: {
            return (counts[5U] * static_cast<std::int32_t>(5));
        }
        case category::sixes: {
            return (counts[6U] * static_cast<std::int32_t>(6));
        }
        case category::full_house: {
            bool has_three = false;
            bool has_two = false;
            for (std::int32_t face = 1; face <= 6; ++face) {
                const std::size_t idx = static_cast<std::size_t>(face);
                if (counts[idx] == static_cast<std::int32_t>(3)) {
                    has_three = true;
                } else if (counts[idx] == static_cast<std::int32_t>(2)) {
                    has_two = true;
                } else {
                    // no-op
                }
            }
            if ((has_three) && (has_two)) {
                return sum_dice(dice);
            } else {
                return static_cast<std::int32_t>(0);
            }
        }
        case category::four_of_a_kind: {
            for (std::int32_t face = 1; face <= 6; ++face) {
                const std::size_t idx = static_cast<std::size_t>(face);
                const std::int32_t c = counts[idx];
                if ((c >= static_cast<std::int32_t>(4)) && (c <= static_cast<std::int32_t>(5))) {
                    return (face * static_cast<std::int32_t>(4));
                }
            }
            return static_cast<std::int32_t>(0);
        }
        case category::little_straight: {
            const bool is_little =
                (counts[1U] == static_cast<std::int32_t>(1)) &&
                (counts[2U] == static_cast<std::int32_t>(1)) &&
                (counts[3U] == static_cast<std::int32_t>(1)) &&
                (counts[4U] == static_cast<std::int32_t>(1)) &&
                (counts[5U] == static_cast<std::int32_t>(1)) &&
                (counts[6U] == static_cast<std::int32_t>(0));
            if (is_little) {
                return static_cast<std::int32_t>(30);
            } else {
                return static_cast<std::int32_t>(0);
            }
        }
        case category::big_straight: {
            const bool is_big =
                (counts[1U] == static_cast<std::int32_t>(0)) &&
                (counts[2U] == static_cast<std::int32_t>(1)) &&
                (counts[3U] == static_cast<std::int32_t>(1)) &&
                (counts[4U] == static_cast<std::int32_t>(1)) &&
                (counts[5U] == static_cast<std::int32_t>(1)) &&
                (counts[6U] == static_cast<std::int32_t>(1));
            if (is_big) {
                return static_cast<std::int32_t>(30);
            } else {
                return static_cast<std::int32_t>(0);
            }
        }
        case category::choice: {
            return sum_dice(dice);
        }
        case category::yacht: {
            for (std::int32_t face = 1; face <= 6; ++face) {
                const std::size_t idx = static_cast<std::size_t>(face);
                if (counts[idx] == static_cast<std::int32_t>(5)) {
                    return static_cast<std::int32_t>(50);
                }
            }
            return static_cast<std::int32_t>(0);
        }
        default: {
            return static_cast<std::int32_t>(0);
        }
    }
}

auto score(const std::vector<std::int32_t>& dice, const char* cat) -> std::int32_t {
    if ((cat == nullptr) || (std::strcmp(cat, "") == 0)) {
        return static_cast<std::int32_t>(0);
    }

    category mapped = category::choice;
    bool recognized = false;

    if ((std::strcmp(cat, "ones") == 0)) {
        mapped = category::ones;
        recognized = true;
    } else if ((std::strcmp(cat, "twos") == 0)) {
        mapped = category::twos;
        recognized = true;
    } else if ((std::strcmp(cat, "threes") == 0)) {
        mapped = category::threes;
        recognized = true;
    } else if ((std::strcmp(cat, "fours") == 0)) {
        mapped = category::fours;
        recognized = true;
    } else if ((std::strcmp(cat, "fives") == 0)) {
        mapped = category::fives;
        recognized = true;
    } else if ((std::strcmp(cat, "sixes") == 0)) {
        mapped = category::sixes;
        recognized = true;
    } else if ((std::strcmp(cat, "full house") == 0)) {
        mapped = category::full_house;
        recognized = true;
    } else if ((std::strcmp(cat, "four of a kind") == 0)) {
        mapped = category::four_of_a_kind;
        recognized = true;
    } else if ((std::strcmp(cat, "little straight") == 0)) {
        mapped = category::little_straight;
        recognized = true;
    } else if ((std::strcmp(cat, "big straight") == 0)) {
        mapped = category::big_straight;
        recognized = true;
    } else if ((std::strcmp(cat, "choice") == 0)) {
        mapped = category::choice;
        recognized = true;
    } else if ((std::strcmp(cat, "yacht") == 0)) {
        mapped = category::yacht;
        recognized = true;
    } else {
        // Unrecognized category string
    }

    if ((!recognized)) {
        return static_cast<std::int32_t>(0);
    }

    return score(dice, mapped);
}

auto score(std::initializer_list<std::int32_t> dice, const char* cat) -> std::int32_t {
    const std::vector<std::int32_t> v(dice);
    return score(v, cat);
}

auto score(std::initializer_list<std::int32_t> dice, category cat) -> std::int32_t {
    const std::vector<std::int32_t> v(dice);
    return score(v, cat);
}

}  // namespace yacht
