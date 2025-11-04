#pragma once

#include <array>
#include <cstdint>
#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <string_view>
#include <type_traits>

namespace yacht {

// Scoring categories for Yacht
enum class category : std::uint8_t {
    ones = 0U,
    twos = 1U,
    threes = 2U,
    fours = 3U,
    fives = 4U,
    sixes = 5U,
    full_house = 6U,
    four_of_a_kind = 7U,
    little_straight = 8U,
    big_straight = 9U,
    choice = 10U,
    yacht = 11U
};

// Convert category name used by tests to enum
inline category category_from_name(std::string_view name) noexcept
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
        // Default to choice for any unknown category name
        return category::choice;
    }
}

namespace detail {
// Internal helper implemented in yacht.cpp
std::uint32_t compute_score_from_counts(
    const std::array<std::uint32_t, 7U>& counts,
    category cat,
    std::uint32_t total) noexcept;
}  // namespace detail

// Generic score function accepting any range with at least five dice values.
// Dice values outside [1, 6] are ignored.
template <typename Range>
std::uint32_t score(const Range& dice, category cat) noexcept
{
    std::array<std::uint32_t, 7U> counts{};
    std::uint32_t total = 0U;

    std::size_t processed = 0U;
    for (auto it = std::begin(dice);
         (it != std::end(dice)) && (processed < static_cast<std::size_t>(5U));
         ++it) {
        using T = std::remove_cv_t<std::remove_reference_t<decltype(*it)>>;

        std::uint32_t face = 0U;
        if constexpr (std::is_integral_v<T>) {
            if constexpr (std::is_signed_v<T>) {
                const std::int64_t v = static_cast<std::int64_t>(*it);
                if (v == static_cast<std::int64_t>(1)) {
                    face = 1U;
                } else if (v == static_cast<std::int64_t>(2)) {
                    face = 2U;
                } else if (v == static_cast<std::int64_t>(3)) {
                    face = 3U;
                } else if (v == static_cast<std::int64_t>(4)) {
                    face = 4U;
                } else if (v == static_cast<std::int64_t>(5)) {
                    face = 5U;
                } else if (v == static_cast<std::int64_t>(6)) {
                    face = 6U;
                } else {
                    face = 0U;
                }
            } else {
                const std::uint64_t v = static_cast<std::uint64_t>(*it);
                if (v == static_cast<std::uint64_t>(1U)) {
                    face = 1U;
                } else if (v == static_cast<std::uint64_t>(2U)) {
                    face = 2U;
                } else if (v == static_cast<std::uint64_t>(3U)) {
                    face = 3U;
                } else if (v == static_cast<std::uint64_t>(4U)) {
                    face = 4U;
                } else if (v == static_cast<std::uint64_t>(5U)) {
                    face = 5U;
                } else if (v == static_cast<std::uint64_t>(6U)) {
                    face = 6U;
                } else {
                    face = 0U;
                }
            }
        } else {
            // Non-integral values are treated as out of range and ignored
            face = 0U;
        }

        if (face != 0U) {
            counts[static_cast<std::size_t>(face)] =
                counts[static_cast<std::size_t>(face)] + 1U;
            total = total + face;
        }
        processed = processed + 1U;
    }

    return detail::compute_score_from_counts(counts, cat, total);
}

// Overload: accept category by name (as used in tests)
template <typename Range>
std::uint32_t score(const Range& dice, std::string_view cat_name) noexcept
{
    return score(dice, category_from_name(cat_name));
}

template <typename Range>
inline std::uint32_t score(const Range& dice, const char* cat_name) noexcept
{
    return score(dice, std::string_view{cat_name});
}

// Overload: accept initializer_list for the dice (as used in tests)
inline std::uint32_t score(std::initializer_list<std::uint32_t> dice, category cat) noexcept
{
    return score<std::initializer_list<std::uint32_t>>(dice, cat);
}

// Overload: accept initializer_list and category by name
inline std::uint32_t score(std::initializer_list<std::uint32_t> dice, std::string_view cat_name) noexcept
{
    return score<std::initializer_list<std::uint32_t>>(dice, category_from_name(cat_name));
}

inline std::uint32_t score(std::initializer_list<std::uint32_t> dice, const char* cat_name) noexcept
{
    return score(dice, std::string_view{cat_name});
}

}  // namespace yacht
