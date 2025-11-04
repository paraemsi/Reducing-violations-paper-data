#pragma once

#include <array>
#include <cstdint>
#include <vector>
#include <initializer_list>
#include <string>

namespace yacht {

enum class category : std::uint8_t {
    ones,
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

namespace detail {
// Internal helper that evaluates the score from face counts.
// counts[i] holds the count of face 'i' (0 is unused).
std::uint32_t score_from_counts(const std::array<std::uint32_t, 7U>& counts, category cat) noexcept;
category parse_category(const std::string& name) noexcept;
}  // namespace detail

// Templated interface to avoid naming specific integer types in the public API.
// Accepts any integral element type that can represent dice values 1..6.
template <typename IntT>
std::uint32_t score(const std::vector<IntT>& dice, category cat)
{
    std::array<std::uint32_t, 7U> counts{};
    for (const auto& d : dice) {
        if ((d == static_cast<IntT>(1))) {
            ++counts[1U];
        } else if ((d == static_cast<IntT>(2))) {
            ++counts[2U];
        } else if ((d == static_cast<IntT>(3))) {
            ++counts[3U];
        } else if ((d == static_cast<IntT>(4))) {
            ++counts[4U];
        } else if ((d == static_cast<IntT>(5))) {
            ++counts[5U];
        } else if ((d == static_cast<IntT>(6))) {
            ++counts[6U];
        } else {
            // Out-of-range dice value (should not occur per problem statement); ignore it.
        }
    }

    return detail::score_from_counts(counts, cat);
}

inline std::uint32_t score(std::initializer_list<std::uint32_t> dice, const std::string& cat_name)
{
    std::array<std::uint32_t, 7U> counts{};
    for (const auto d : dice) {
        if ((d == static_cast<std::uint32_t>(1U))) {
            ++counts[1U];
        } else if ((d == static_cast<std::uint32_t>(2U))) {
            ++counts[2U];
        } else if ((d == static_cast<std::uint32_t>(3U))) {
            ++counts[3U];
        } else if ((d == static_cast<std::uint32_t>(4U))) {
            ++counts[4U];
        } else if ((d == static_cast<std::uint32_t>(5U))) {
            ++counts[5U];
        } else if ((d == static_cast<std::uint32_t>(6U))) {
            ++counts[6U];
        } else {
            // Out-of-range dice value (should not occur per problem statement); ignore it.
        }
    }

    return detail::score_from_counts(counts, detail::parse_category(cat_name));
}

inline std::uint32_t score(std::initializer_list<std::uint32_t> dice, const char* cat_name)
{
    // Delegate to the std::string overload to avoid duplicating logic.
    return score(dice, std::string(cat_name));
}

template <typename IntT>
inline std::uint32_t score(const std::vector<IntT>& dice, const std::string& cat_name)
{
    return score(dice, detail::parse_category(cat_name));
}

template <typename IntT>
inline std::uint32_t score(const std::vector<IntT>& dice, const char* cat_name)
{
    return score(dice, std::string(cat_name));
}

}  // namespace yacht
