#include "yacht.h"

#include <algorithm>
#include <numeric>
#include <string_view>

namespace yacht {

/* ------------------------------------------------------------------------- */
/*  Internal helper: map textual category names used by the tests to the     */
/*  strongly-typed enumeration.                                              */
/* ------------------------------------------------------------------------- */
namespace
{
    [[nodiscard]] static auto to_category(std::string_view name) -> Category
    {
        if(name == "ones")
        {
            return Category::ones;
        }
        else if(name == "twos")
        {
            return Category::twos;
        }
        else if(name == "threes")
        {
            return Category::threes;
        }
        else if(name == "fours")
        {
            return Category::fours;
        }
        else if(name == "fives")
        {
            return Category::fives;
        }
        else if(name == "sixes")
        {
            return Category::sixes;
        }
        else if(name == "full house")
        {
            return Category::full_house;
        }
        else if(name == "four of a kind")
        {
            return Category::four_of_a_kind;
        }
        else if(name == "little straight")
        {
            return Category::little_straight;
        }
        else if(name == "big straight")
        {
            return Category::big_straight;
        }
        else if(name == "choice")
        {
            return Category::choice;
        }
        else if(name == "yacht")
        {
            return Category::yacht;
        }
        /* Undefined input – default to a result that yields 0 score. */
        return Category::choice;
    }
} /* anonymous namespace */

/* Public overload forwarding to the existing implementation. */
[[nodiscard]] auto score(const std::array<std::uint8_t, 5U> & dice,
                         const std::string_view                category) -> std::uint32_t
{
    return score(dice, to_category(category));
}

/* Utility: produce a frequency table of the dice (indices 0-5 represent faces 1-6). */
static auto face_frequencies(const std::array<std::uint8_t, 5U> & dice)
    -> std::array<std::uint8_t, 6U>
{
    std::array<std::uint8_t, 6U> counts {};
    for(const std::uint8_t die : dice)
    {
        /* Each die is guaranteed 1-6 by problem definition. */
        const std::uint8_t index { static_cast<std::uint8_t>(die - 1U) };
        ++counts[index];
    }
    return counts;
}

[[nodiscard]] auto score(const std::array<std::uint8_t, 5U> & dice,
                         const Category                          category) -> std::uint32_t
{
    const std::array<std::uint8_t, 6U> counts { face_frequencies(dice) };

    switch(category)
    {
        case Category::ones:
        case Category::twos:
        case Category::threes:
        case Category::fours:
        case Category::fives:
        case Category::sixes:
        {
            const std::uint8_t face { static_cast<std::uint8_t>(
                                            static_cast<std::uint8_t>(category) +
                                            static_cast<std::uint8_t>(1U)) };
            const std::uint8_t count { counts[face - 1U] };
            return static_cast<std::uint32_t>(face) * static_cast<std::uint32_t>(count);
        }

        case Category::full_house:
        {
            bool has_three { false };
            bool has_two   { false };

            for(const std::uint8_t c : counts)
            {
                if(c == 3U)
                {
                    has_three = true;
                }
                else if(c == 2U)
                {
                    has_two = true;
                }
            }

            if(has_three && has_two)
            {
                return std::accumulate(dice.cbegin(), dice.cend(), std::uint32_t { 0U });
            }
            return 0U;
        }

        case Category::four_of_a_kind:
        {
            for(std::uint8_t face_index { 0U }; face_index < 6U; ++face_index)
            {
                if(counts[face_index] >= 4U)
                {
                    const std::uint32_t face { static_cast<std::uint32_t>(face_index + 1U) };
                    return face * 4U;
                }
            }
            return 0U;
        }

        case Category::little_straight:
        {
            const bool matches { (counts[0U] == 1U) && (counts[1U] == 1U) &&
                                 (counts[2U] == 1U) && (counts[3U] == 1U) &&
                                 (counts[4U] == 1U) && (counts[5U] == 0U) };
            return matches ? 30U : 0U;
        }

        case Category::big_straight:
        {
            const bool matches { (counts[0U] == 0U) && (counts[1U] == 1U) &&
                                 (counts[2U] == 1U) && (counts[3U] == 1U) &&
                                 (counts[4U] == 1U) && (counts[5U] == 1U) };
            return matches ? 30U : 0U;
        }

        case Category::choice:
        {
            return std::accumulate(dice.cbegin(), dice.cend(), std::uint32_t { 0U });
        }

        case Category::yacht:
        {
            for(const std::uint8_t c : counts)
            {
                if(c == 5U)
                {
                    return 50U;
                }
            }
            return 0U;
        }

        /* Defensive default; all enumerators are handled above. */
        default:
        {
            return 0U;
        }
    }
}

} // namespace yacht
