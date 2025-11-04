#include "yacht.h"

#include <array>
#include <cstddef>
#include <cstdint>
#include <initializer_list>
#include <string_view>
#include <vector>

namespace {
auto parse_category(std::string_view sv) -> yacht::category
{
    using std::string_view;
    if ((sv == string_view("ones"))) {
        return yacht::category::ones;
    } else if ((sv == string_view("twos"))) {
        return yacht::category::twos;
    } else if ((sv == string_view("threes"))) {
        return yacht::category::threes;
    } else if ((sv == string_view("fours"))) {
        return yacht::category::fours;
    } else if ((sv == string_view("fives"))) {
        return yacht::category::fives;
    } else if ((sv == string_view("sixes"))) {
        return yacht::category::sixes;
    } else if ((sv == string_view("full house"))) {
        return yacht::category::full_house;
    } else if ((sv == string_view("four of a kind"))) {
        return yacht::category::four_of_a_kind;
    } else if ((sv == string_view("little straight"))) {
        return yacht::category::little_straight;
    } else if ((sv == string_view("big straight"))) {
        return yacht::category::big_straight;
    } else if ((sv == string_view("choice"))) {
        return yacht::category::choice;
    } else if ((sv == string_view("yacht"))) {
        return yacht::category::yacht;
    } else {
        // Default to choice for unknown strings.
        return yacht::category::choice;
    }
}

auto parse_category(const char* cat) -> yacht::category
{
    using std::string_view;
    const string_view sv{(cat != nullptr) ? string_view(cat) : string_view()};
    return parse_category(sv);
}
}  // unnamed namespace

namespace yacht {

auto score(const std::vector<std::int32_t>& dice, const char* cat) -> std::int32_t
{
    return score(dice, ::parse_category(cat));
}

auto score(std::initializer_list<std::int32_t> dice, category cat) -> std::int32_t
{
    return score(std::vector<std::int32_t>(dice), cat);
}

auto score(std::initializer_list<std::int32_t> dice, const char* cat) -> std::int32_t
{
    return score(std::vector<std::int32_t>(dice), ::parse_category(cat));
}

auto score(const std::vector<std::int32_t>& dice, std::string_view cat) -> std::int32_t
{
    return score(dice, ::parse_category(cat));
}

auto score(std::initializer_list<std::int32_t> dice, std::string_view cat) -> std::int32_t
{
    return score(std::vector<std::int32_t>(dice), ::parse_category(cat));
}

auto score(const std::vector<std::int32_t>& dice, category cat) -> std::int32_t
{
    // Frequency of faces 1..6 (index 0 unused)
    std::array<std::uint8_t, 7U> freq{};  // zero-initialized

    // Sum of all dice (for "choice" and "full_house")
    std::int32_t sum{0};

    for (const auto& v : dice) {
        if ((v >= static_cast<std::int32_t>(1)) && (v <= static_cast<std::int32_t>(6))) {
            const std::size_t idx = static_cast<std::size_t>(static_cast<std::uint32_t>(v));
            // Increment with widened intermediate to avoid overflow on uint8_t arithmetic
            freq[idx] = static_cast<std::uint8_t>(
                static_cast<std::uint16_t>(freq[idx]) + static_cast<std::uint16_t>(1U));
            sum = (sum + static_cast<std::int32_t>(v));
        } else {
            // Values are expected to be 1..6 per problem statement; ignore otherwise.
            // No change to freq or sum.
        }
    }

    const auto face_score = [&freq](std::uint8_t face) -> std::int32_t {
        const std::uint8_t count = freq[static_cast<std::size_t>(face)];
        return static_cast<std::int32_t>(
            static_cast<std::int32_t>(face) * static_cast<std::int32_t>(count));
    };

    const auto has_n_of_a_kind = [&freq](std::uint8_t n, std::uint8_t& face_out) -> bool {
        for (std::uint8_t face = static_cast<std::uint8_t>(1U);
             face <= static_cast<std::uint8_t>(6U);
             face = static_cast<std::uint8_t>(face + static_cast<std::uint8_t>(1U))) {
            if (freq[static_cast<std::size_t>(face)] >= n) {
                face_out = face;
                return true;
            }
        }
        return false;
    };

    switch (cat) {
        case category::ones: {
            return face_score(static_cast<std::uint8_t>(1U));
        }
        case category::twos: {
            return face_score(static_cast<std::uint8_t>(2U));
        }
        case category::threes: {
            return face_score(static_cast<std::uint8_t>(3U));
        }
        case category::fours: {
            return face_score(static_cast<std::uint8_t>(4U));
        }
        case category::fives: {
            return face_score(static_cast<std::uint8_t>(5U));
        }
        case category::sixes: {
            return face_score(static_cast<std::uint8_t>(6U));
        }
        case category::choice: {
            return sum;
        }
        case category::yacht: {
            for (std::uint8_t face = static_cast<std::uint8_t>(1U);
                 face <= static_cast<std::uint8_t>(6U);
                 face = static_cast<std::uint8_t>(face + static_cast<std::uint8_t>(1U))) {
                if (freq[static_cast<std::size_t>(face)] == static_cast<std::uint8_t>(5U)) {
                    return static_cast<std::int32_t>(50);
                }
            }
            return static_cast<std::int32_t>(0);
        }
        case category::four_of_a_kind: {
            std::uint8_t face{0U};
            if (has_n_of_a_kind(static_cast<std::uint8_t>(4U), face)) {
                return static_cast<std::int32_t>(
                    static_cast<std::int32_t>(face) * static_cast<std::int32_t>(4));
            }
            return static_cast<std::int32_t>(0);
        }
        case category::full_house: {
            bool has_three{false};
            bool has_pair{false};

            for (std::uint8_t face = static_cast<std::uint8_t>(1U);
                 face <= static_cast<std::uint8_t>(6U);
                 face = static_cast<std::uint8_t>(face + static_cast<std::uint8_t>(1U))) {
                const std::uint8_t count = freq[static_cast<std::size_t>(face)];
                if (count == static_cast<std::uint8_t>(3U)) {
                    has_three = true;
                } else if (count == static_cast<std::uint8_t>(2U)) {
                    has_pair = true;
                }
            }

            if ((has_three) && (has_pair)) {
                return sum;
            }

            return static_cast<std::int32_t>(0);
        }
        case category::little_straight: {
            const bool is_ls =
                (freq[static_cast<std::size_t>(1U)] == static_cast<std::uint8_t>(1U)) &&
                (freq[static_cast<std::size_t>(2U)] == static_cast<std::uint8_t>(1U)) &&
                (freq[static_cast<std::size_t>(3U)] == static_cast<std::uint8_t>(1U)) &&
                (freq[static_cast<std::size_t>(4U)] == static_cast<std::uint8_t>(1U)) &&
                (freq[static_cast<std::size_t>(5U)] == static_cast<std::uint8_t>(1U)) &&
                (freq[static_cast<std::size_t>(6U)] == static_cast<std::uint8_t>(0U));

            if (is_ls) {
                return static_cast<std::int32_t>(30);
            }
            return static_cast<std::int32_t>(0);
        }
        case category::big_straight: {
            const bool is_bs =
                (freq[static_cast<std::size_t>(1U)] == static_cast<std::uint8_t>(0U)) &&
                (freq[static_cast<std::size_t>(2U)] == static_cast<std::uint8_t>(1U)) &&
                (freq[static_cast<std::size_t>(3U)] == static_cast<std::uint8_t>(1U)) &&
                (freq[static_cast<std::size_t>(4U)] == static_cast<std::uint8_t>(1U)) &&
                (freq[static_cast<std::size_t>(5U)] == static_cast<std::uint8_t>(1U)) &&
                (freq[static_cast<std::size_t>(6U)] == static_cast<std::uint8_t>(1U));

            if (is_bs) {
                return static_cast<std::int32_t>(30);
            }
            return static_cast<std::int32_t>(0);
        }
        default: {
            // Should not be reachable; return zero score if it happens.
            return static_cast<std::int32_t>(0);
        }
    }
}

}  // namespace yacht
