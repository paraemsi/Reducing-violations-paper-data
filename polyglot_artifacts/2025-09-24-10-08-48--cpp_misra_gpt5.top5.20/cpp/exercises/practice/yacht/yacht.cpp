#include "yacht.h"

#include <array>
#include <cstdint>
#include <cstddef>
#include <string_view>
#include <initializer_list>

namespace yacht {

namespace {
    constexpr auto kLittleStraightScore = static_cast<std::uint16_t>(30U);
    constexpr auto kBigStraightScore = static_cast<std::uint16_t>(30U);
    constexpr auto kYachtScore = static_cast<std::uint16_t>(50U);

    inline auto to_index(std::uint8_t v) -> std::size_t {
        return static_cast<std::size_t>(v);
    }

    auto make_counts(const std::array<std::uint8_t, 5U>& dice) -> std::array<std::uint8_t, 7U> {
        std::array<std::uint8_t, 7U> counts{};
        for (std::uint8_t d : dice) {
            counts[to_index(d)] = static_cast<std::uint8_t>(static_cast<std::uint16_t>(counts[to_index(d)]) + static_cast<std::uint16_t>(1U));
        }
        return counts;
    }

    auto sum_dice(const std::array<std::uint8_t, 5U>& dice) -> std::uint16_t {
        std::uint16_t sum = static_cast<std::uint16_t>(0U);
        for (std::uint8_t d : dice) {
            sum = static_cast<std::uint16_t>(sum + static_cast<std::uint16_t>(d));
        }
        return sum;
    }

    auto face_score(const std::array<std::uint8_t, 7U>& counts, std::uint8_t face) -> std::uint16_t {
        const std::uint16_t c = static_cast<std::uint16_t>(counts[to_index(face)]);
        return static_cast<std::uint16_t>(static_cast<std::uint16_t>(face) * c);
    }

    inline auto parse_category(std::string_view name) -> category {
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


    inline auto pack_to_u8(std::initializer_list<std::int32_t> src) -> std::array<std::uint8_t, 5U> {
        std::array<std::uint8_t, 5U> out{};
        std::size_t i = 0U;
        for (std::int32_t v : src) {
            if ((i >= 5U)) {
                break;
            }
            if ((v < 0)) {
                v = 0;
            }
            if ((v > 6)) {
                v = 6;
            }
            out[i] = static_cast<std::uint8_t>(v);
            i = static_cast<std::size_t>(i + 1U);
        }
        return out;
    }
}

auto score(const std::array<std::uint8_t, 5U>& dice, category cat) -> std::uint16_t {
    const auto counts = make_counts(dice);

    switch (cat) {
        case category::ones: {
            return face_score(counts, static_cast<std::uint8_t>(1U));
        }
        case category::twos: {
            return face_score(counts, static_cast<std::uint8_t>(2U));
        }
        case category::threes: {
            return face_score(counts, static_cast<std::uint8_t>(3U));
        }
        case category::fours: {
            return face_score(counts, static_cast<std::uint8_t>(4U));
        }
        case category::fives: {
            return face_score(counts, static_cast<std::uint8_t>(5U));
        }
        case category::sixes: {
            return face_score(counts, static_cast<std::uint8_t>(6U));
        }
        case category::full_house: {
            bool has_three = false;
            bool has_two = false;
            for (std::uint8_t face = static_cast<std::uint8_t>(1U); face <= static_cast<std::uint8_t>(6U); face = static_cast<std::uint8_t>(face + static_cast<std::uint8_t>(1U))) {
                const std::uint8_t cnt = counts[to_index(face)];
                if ((cnt == static_cast<std::uint8_t>(3U))) {
                    has_three = true;
                } else if ((cnt == static_cast<std::uint8_t>(2U))) {
                    has_two = true;
                }
            }
            if ((has_three) && (has_two)) {
                return sum_dice(dice);
            } else {
                return static_cast<std::uint16_t>(0U);
            }
        }
        case category::four_of_a_kind: {
            for (std::uint8_t face = static_cast<std::uint8_t>(1U); face <= static_cast<std::uint8_t>(6U); face = static_cast<std::uint8_t>(face + static_cast<std::uint8_t>(1U))) {
                const std::uint8_t cnt = counts[to_index(face)];
                if ((cnt >= static_cast<std::uint8_t>(4U))) {
                    return static_cast<std::uint16_t>(static_cast<std::uint16_t>(face) * static_cast<std::uint16_t>(4U));
                }
            }
            return static_cast<std::uint16_t>(0U);
        }
        case category::little_straight: {
            const bool ok = (counts[to_index(static_cast<std::uint8_t>(1U))] == static_cast<std::uint8_t>(1U))
                         && (counts[to_index(static_cast<std::uint8_t>(2U))] == static_cast<std::uint8_t>(1U))
                         && (counts[to_index(static_cast<std::uint8_t>(3U))] == static_cast<std::uint8_t>(1U))
                         && (counts[to_index(static_cast<std::uint8_t>(4U))] == static_cast<std::uint8_t>(1U))
                         && (counts[to_index(static_cast<std::uint8_t>(5U))] == static_cast<std::uint8_t>(1U))
                         && (counts[to_index(static_cast<std::uint8_t>(6U))] == static_cast<std::uint8_t>(0U));
            if (ok) {
                return kLittleStraightScore;
            } else {
                return static_cast<std::uint16_t>(0U);
            }
        }
        case category::big_straight: {
            const bool ok = (counts[to_index(static_cast<std::uint8_t>(1U))] == static_cast<std::uint8_t>(0U))
                         && (counts[to_index(static_cast<std::uint8_t>(2U))] == static_cast<std::uint8_t>(1U))
                         && (counts[to_index(static_cast<std::uint8_t>(3U))] == static_cast<std::uint8_t>(1U))
                         && (counts[to_index(static_cast<std::uint8_t>(4U))] == static_cast<std::uint8_t>(1U))
                         && (counts[to_index(static_cast<std::uint8_t>(5U))] == static_cast<std::uint8_t>(1U))
                         && (counts[to_index(static_cast<std::uint8_t>(6U))] == static_cast<std::uint8_t>(1U));
            if (ok) {
                return kBigStraightScore;
            } else {
                return static_cast<std::uint16_t>(0U);
            }
        }
        case category::choice: {
            return sum_dice(dice);
        }
        case category::yacht: {
            for (std::uint8_t face = static_cast<std::uint8_t>(1U); face <= static_cast<std::uint8_t>(6U); face = static_cast<std::uint8_t>(face + static_cast<std::uint8_t>(1U))) {
                if ((counts[to_index(face)] == static_cast<std::uint8_t>(5U))) {
                    return kYachtScore;
                }
            }
            return static_cast<std::uint16_t>(0U);
        }
        default: {
            return static_cast<std::uint16_t>(0U);
        }
    }
}

auto score(const std::array<std::uint8_t, 5U>& dice, std::string_view cat) -> std::uint16_t {
    return score(dice, parse_category(cat));
}

auto score(const std::array<std::uint8_t, 5U>& dice, const char* cat) -> std::uint16_t {
    return score(dice, std::string_view{cat});
}




auto score(std::initializer_list<std::int32_t> dice, std::string_view cat) -> std::uint16_t {
    return score(pack_to_u8(dice), cat);
}

auto score(std::initializer_list<std::int32_t> dice, const char* cat) -> std::uint16_t {
    return score(pack_to_u8(dice), std::string_view{cat});
}

}  // namespace yacht
