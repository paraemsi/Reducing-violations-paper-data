#include "yacht.h"

#include <array>
#include <cstddef>
#include <cstdint>
#include <cstring>

namespace yacht {

namespace
{
    constexpr std::uint8_t min_face{1U};
    constexpr std::uint8_t max_face{6U};
    constexpr score_t straight_score{30U};
    constexpr score_t yacht_score{50U};

    auto sum_dice(const std::array<die_t, 5U>& dice) noexcept -> score_t
    {
        score_t total{0U};
        for (const die_t d : dice)
        {
            total = static_cast<score_t>(total + static_cast<score_t>(d));
        }
        return (total);
    }

    auto make_counts(const std::array<die_t, 5U>& dice) noexcept -> std::array<std::uint8_t, 7U>
    {
        std::array<std::uint8_t, 7U> counts{};  // indices 0..6, we ignore 0
        for (const die_t d : dice)
        {
            if ((d >= min_face) && (d <= max_face))
            {
                const std::size_t idx = static_cast<std::size_t>(d);
                counts[idx] = static_cast<std::uint8_t>(counts[idx] + static_cast<std::uint8_t>(1U));
            }
            else
            {
                // Out-of-range die values are ignored as inputs are specified to be valid.
                // Keeping branch to avoid undefined behavior if violated.
            }
        }
        return (counts);
    }

    auto face_score(const std::array<std::uint8_t, 7U>& counts, std::uint8_t face) noexcept -> score_t
    {
        const score_t f = static_cast<score_t>(face);
        const score_t c = static_cast<score_t>(counts[static_cast<std::size_t>(face)]);
        return (static_cast<score_t>(f * c));
    }

    auto is_yacht(const std::array<std::uint8_t, 7U>& counts) noexcept -> bool
    {
        for (std::uint8_t face = min_face; face <= max_face; face = static_cast<std::uint8_t>(face + static_cast<std::uint8_t>(1U)))
        {
            if (counts[static_cast<std::size_t>(face)] == static_cast<std::uint8_t>(5U))
            {
                return (true);
            }
        }
        return (false);
    }

    auto full_house_score(const std::array<std::uint8_t, 7U>& counts, const std::array<die_t, 5U>& dice) noexcept -> score_t
    {
        bool has_three{false};
        bool has_two{false};
        for (std::uint8_t face = min_face; face <= max_face; face = static_cast<std::uint8_t>(face + static_cast<std::uint8_t>(1U)))
        {
            const std::uint8_t c = counts[static_cast<std::size_t>(face)];
            if (c == static_cast<std::uint8_t>(3U))
            {
                has_three = true;
            }
            else if (c == static_cast<std::uint8_t>(2U))
            {
                has_two = true;
            }
        }

        if ((has_three) && (has_two))
        {
            return (sum_dice(dice));
        }

        return (static_cast<score_t>(0U));
    }

    auto four_of_a_kind_score(const std::array<std::uint8_t, 7U>& counts) noexcept -> score_t
    {
        for (std::uint8_t face = min_face; face <= max_face; face = static_cast<std::uint8_t>(face + static_cast<std::uint8_t>(1U)))
        {
            const std::uint8_t c = counts[static_cast<std::size_t>(face)];
            if (c >= static_cast<std::uint8_t>(4U))
            {
                return (static_cast<score_t>(static_cast<score_t>(4U) * static_cast<score_t>(face)));
            }
        }
        return (static_cast<score_t>(0U));
    }

    auto is_little_straight(const std::array<std::uint8_t, 7U>& counts) noexcept -> bool
    {
        for (std::uint8_t face = min_face; face <= static_cast<std::uint8_t>(5U); face = static_cast<std::uint8_t>(face + static_cast<std::uint8_t>(1U)))
        {
            if (counts[static_cast<std::size_t>(face)] != static_cast<std::uint8_t>(1U))
            {
                return (false);
            }
        }
        if (counts[static_cast<std::size_t>(6U)] != static_cast<std::uint8_t>(0U))
        {
            return (false);
        }
        return (true);
    }

    auto is_big_straight(const std::array<std::uint8_t, 7U>& counts) noexcept -> bool
    {
        for (std::uint8_t face = static_cast<std::uint8_t>(2U); face <= max_face; face = static_cast<std::uint8_t>(face + static_cast<std::uint8_t>(1U)))
        {
            if (counts[static_cast<std::size_t>(face)] != static_cast<std::uint8_t>(1U))
            {
                return (false);
            }
        }
        if (counts[static_cast<std::size_t>(1U)] != static_cast<std::uint8_t>(0U))
        {
            return (false);
        }
        return (true);
    }
}  // namespace

auto score(const std::array<die_t, 5U>& dice, category cat) noexcept -> score_t
{
    const std::array<std::uint8_t, 7U> counts = make_counts(dice);

    switch (cat)
    {
        case category::ones:
        {
            return (face_score(counts, static_cast<std::uint8_t>(1U)));
        }
        case category::twos:
        {
            return (face_score(counts, static_cast<std::uint8_t>(2U)));
        }
        case category::threes:
        {
            return (face_score(counts, static_cast<std::uint8_t>(3U)));
        }
        case category::fours:
        {
            return (face_score(counts, static_cast<std::uint8_t>(4U)));
        }
        case category::fives:
        {
            return (face_score(counts, static_cast<std::uint8_t>(5U)));
        }
        case category::sixes:
        {
            return (face_score(counts, static_cast<std::uint8_t>(6U)));
        }
        case category::full_house:
        {
            if (is_yacht(counts))
            {
                return (static_cast<score_t>(0U));
            }
            return (full_house_score(counts, dice));
        }
        case category::four_of_a_kind:
        {
            return (four_of_a_kind_score(counts));
        }
        case category::little_straight:
        {
            if (is_little_straight(counts))
            {
                return (straight_score);
            }
            return (static_cast<score_t>(0U));
        }
        case category::big_straight:
        {
            if (is_big_straight(counts))
            {
                return (straight_score);
            }
            return (static_cast<score_t>(0U));
        }
        case category::choice:
        {
            return (sum_dice(dice));
        }
        case category::yacht:
        {
            if (is_yacht(counts))
            {
                return (yacht_score);
            }
            return (static_cast<score_t>(0U));
        }
        default:
        {
            // Unreachable with current enum, but keeps switch exhaustive if extended.
            return (static_cast<score_t>(0U));
        }
    }
}

auto score(const std::array<die_t, 5U>& dice, const char* cat) noexcept -> score_t
{
    if ((cat != nullptr) && (std::strcmp(cat, "ones") == 0))
    {
        return (score(dice, category::ones));
    }
    else if ((cat != nullptr) && (std::strcmp(cat, "twos") == 0))
    {
        return (score(dice, category::twos));
    }
    else if ((cat != nullptr) && (std::strcmp(cat, "threes") == 0))
    {
        return (score(dice, category::threes));
    }
    else if ((cat != nullptr) && (std::strcmp(cat, "fours") == 0))
    {
        return (score(dice, category::fours));
    }
    else if ((cat != nullptr) && (std::strcmp(cat, "fives") == 0))
    {
        return (score(dice, category::fives));
    }
    else if ((cat != nullptr) && (std::strcmp(cat, "sixes") == 0))
    {
        return (score(dice, category::sixes));
    }
    else if ((cat != nullptr) && (std::strcmp(cat, "full house") == 0))
    {
        return (score(dice, category::full_house));
    }
    else if ((cat != nullptr) && (std::strcmp(cat, "four of a kind") == 0))
    {
        return (score(dice, category::four_of_a_kind));
    }
    else if ((cat != nullptr) && (std::strcmp(cat, "little straight") == 0))
    {
        return (score(dice, category::little_straight));
    }
    else if ((cat != nullptr) && (std::strcmp(cat, "big straight") == 0))
    {
        return (score(dice, category::big_straight));
    }
    else if ((cat != nullptr) && (std::strcmp(cat, "choice") == 0))
    {
        return (score(dice, category::choice));
    }
    else if ((cat != nullptr) && (std::strcmp(cat, "yacht") == 0))
    {
        return (score(dice, category::yacht));
    }

    return (static_cast<score_t>(0U));
}

}  // namespace yacht
