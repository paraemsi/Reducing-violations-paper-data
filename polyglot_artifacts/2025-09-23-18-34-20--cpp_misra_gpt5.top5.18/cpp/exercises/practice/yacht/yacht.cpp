#include "yacht.h"

#include <array>
#include <vector>
#include <cstdint>
#include <cstddef>
#include <string_view>
#include <initializer_list>

namespace yacht {

namespace {

// Convert a vector of uint32_t to a fixed-size array of 5 dice, validating range [1,6].
auto to_fixed_array(std::vector<std::uint32_t> const& dice) -> std::array<std::uint8_t, 5U> {
    std::array<std::uint8_t, 5U> out{{0U, 0U, 0U, 0U, 0U}};
    for (std::size_t i = 0U; (i < 5U) && (i < dice.size()); ++i) {
        std::uint32_t const v = dice[i];
        if ((v >= 1U) && (v <= 6U)) {
            out[i] = static_cast<std::uint8_t>(v);
        } else {
            out[i] = static_cast<std::uint8_t>(0U);
        }
    }
    return out;
}

// Convert a vector of uint8_t to a fixed-size array of 5 dice, validating range [1,6].
auto to_fixed_array(std::vector<std::uint8_t> const& dice) -> std::array<std::uint8_t, 5U> {
    std::array<std::uint8_t, 5U> out{{0U, 0U, 0U, 0U, 0U}};
    for (std::size_t i = 0U; (i < 5U) && (i < dice.size()); ++i) {
        std::uint8_t const v = dice[i];
        if ((v >= static_cast<std::uint8_t>(1U)) && (v <= static_cast<std::uint8_t>(6U))) {
            out[i] = v;
        } else {
            out[i] = static_cast<std::uint8_t>(0U);
        }
    }
    return out;
}

auto make_counts(std::array<std::uint8_t, 5U> const& dice) -> std::array<std::uint32_t, 7U> {
    std::array<std::uint32_t, 7U> counts{{0U, 0U, 0U, 0U, 0U, 0U, 0U}};
    for (std::uint8_t const d : dice) {
        if ((d >= static_cast<std::uint8_t>(1U)) && (d <= static_cast<std::uint8_t>(6U))) {
            std::uint32_t const idx = static_cast<std::uint32_t>(d);
            counts[idx] = (counts[idx] + 1U);
        } else {
            // Ignore out-of-range values (should not occur per problem statement)
        }
    }
    return counts;
}

auto sum_dice(std::array<std::uint8_t, 5U> const& dice) -> std::uint32_t {
    std::uint32_t s = 0U;
    for (std::uint8_t const d : dice) {
        s = s + static_cast<std::uint32_t>(d);
    }
    return s;
}

auto from_string(std::string_view const name) -> category {
    if (name == std::string_view{"ones"}) {
        return category::ones;
    } else if (name == std::string_view{"twos"}) {
        return category::twos;
    } else if (name == std::string_view{"threes"}) {
        return category::threes;
    } else if (name == std::string_view{"fours"}) {
        return category::fours;
    } else if (name == std::string_view{"fives"}) {
        return category::fives;
    } else if (name == std::string_view{"sixes"}) {
        return category::sixes;
    } else if (name == std::string_view{"full house"}) {
        return category::full_house;
    } else if (name == std::string_view{"four of a kind"}) {
        return category::four_of_a_kind;
    } else if (name == std::string_view{"little straight"}) {
        return category::little_straight;
    } else if (name == std::string_view{"big straight"}) {
        return category::big_straight;
    } else if (name == std::string_view{"choice"}) {
        return category::choice;
    } else if (name == std::string_view{"yacht"}) {
        return category::yacht;
    } else {
        return category::choice;
    }
}

}  // namespace

auto score(std::array<std::uint8_t, 5U> const& dice, category const cat) -> std::uint32_t {
    std::array<std::uint32_t, 7U> const counts = make_counts(dice);

    switch (cat) {
        case category::ones: {
            return (1U * counts[1U]);
        }
        case category::twos: {
            return (2U * counts[2U]);
        }
        case category::threes: {
            return (3U * counts[3U]);
        }
        case category::fours: {
            return (4U * counts[4U]);
        }
        case category::fives: {
            return (5U * counts[5U]);
        }
        case category::sixes: {
            return (6U * counts[6U]);
        }
        case category::full_house: {
            bool has_three = false;
            bool has_two = false;
            for (std::uint32_t face = 1U; face <= 6U; face = face + 1U) {
                if (counts[face] == 3U) {
                    has_three = true;
                } else if (counts[face] == 2U) {
                    has_two = true;
                }
            }
            if (has_three && has_two) {
                return sum_dice(dice);
            } else {
                return 0U;
            }
        }
        case category::four_of_a_kind: {
            for (std::uint32_t face = 1U; face <= 6U; face = face + 1U) {
                if (counts[face] >= 4U) {
                    return (4U * face);
                }
            }
            return 0U;
        }
        case category::little_straight: {
            bool const ok =
                (counts[1U] == 1U) &&
                (counts[2U] == 1U) &&
                (counts[3U] == 1U) &&
                (counts[4U] == 1U) &&
                (counts[5U] == 1U) &&
                (counts[6U] == 0U);
            if (ok) {
                return 30U;
            } else {
                return 0U;
            }
        }
        case category::big_straight: {
            bool const ok =
                (counts[1U] == 0U) &&
                (counts[2U] == 1U) &&
                (counts[3U] == 1U) &&
                (counts[4U] == 1U) &&
                (counts[5U] == 1U) &&
                (counts[6U] == 1U);
            if (ok) {
                return 30U;
            } else {
                return 0U;
            }
        }
        case category::choice: {
            return sum_dice(dice);
        }
        case category::yacht: {
            for (std::uint32_t face = 1U; face <= 6U; face = face + 1U) {
                if (counts[face] == 5U) {
                    return 50U;
                }
            }
            return 0U;
        }
        default: {
            return 0U;
        }
    }
}

auto score(std::vector<std::uint32_t> const& dice, category const cat) -> std::uint32_t {
    std::array<std::uint8_t, 5U> const fixed = to_fixed_array(dice);
    return score(fixed, cat);
}

auto score(std::vector<std::uint8_t> const& dice, category const cat) -> std::uint32_t {
    std::array<std::uint8_t, 5U> const fixed = to_fixed_array(dice);
    return score(fixed, cat);
}

auto score(std::vector<std::uint32_t> const& dice, char const* cat) -> std::uint32_t {
    std::string_view const name{cat};
    category const c = from_string(name);
    return score(dice, c);
}

auto score(std::array<std::uint8_t, 5U> const& dice, char const* cat) -> std::uint32_t {
    std::string_view const name{cat};
    category const c = from_string(name);
    return score(dice, c);
}

auto score(std::initializer_list<std::uint32_t> dice, char const* cat) -> std::uint32_t {
    std::vector<std::uint32_t> v{dice};
    return score(v, cat);
}


}  // namespace yacht
