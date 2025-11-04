#include "yacht.h"

#include <array>
#include <cstdint>
#include <cstddef>
#include <string_view>

namespace yacht {

[[nodiscard]] auto score(std::array<die_value_t, 5U> const& dice, category cat) -> score_t
{
    /*  Frequency table for faces 1‒6; index 0 is unused to keep the code
     *  clearer. Using std::uint8_t is sufficient because a die appears
     *  at most five times.
     */
    std::array<std::uint8_t, 7U> counts{};     // NOLINT(cppcoreguidelines-avoid-magic-numbers)
    score_t                      sum = 0U;

    for(die_value_t const d : dice)
    {
        ++counts[static_cast<std::size_t>(d)];
        sum += static_cast<score_t>(d);
    }

    switch(cat)
    {
        case category::ones:
        {
            return static_cast<score_t>(counts[1U]) * 1U;
        }
        case category::twos:
        {
            return static_cast<score_t>(counts[2U]) * 2U;
        }
        case category::threes:
        {
            return static_cast<score_t>(counts[3U]) * 3U;
        }
        case category::fours:
        {
            return static_cast<score_t>(counts[4U]) * 4U;
        }
        case category::fives:
        {
            return static_cast<score_t>(counts[5U]) * 5U;
        }
        case category::sixes:
        {
            return static_cast<score_t>(counts[6U]) * 6U;
        }
        case category::full_house:
        {
            bool has_three = false;
            bool has_two   = false;

            for(std::size_t face = 1U; face <= 6U; ++face)
            {
                if(counts[face] == 3U)
                {
                    has_three = true;
                }
                else if(counts[face] == 2U)
                {
                    has_two = true;
                }
            }

            if(has_three && has_two)
            {
                return sum;
            }

            return 0U;
        }
        case category::four_of_a_kind:
        {
            for(std::size_t face = 1U; face <= 6U; ++face)
            {
                if(counts[face] >= 4U)
                {
                    return static_cast<score_t>(face) * 4U;
                }
            }

            return 0U;
        }
        case category::little_straight:
        {
            if((counts[1U] == 1U) && (counts[2U] == 1U) && (counts[3U] == 1U) &&
               (counts[4U] == 1U) && (counts[5U] == 1U) && (counts[6U] == 0U))
            {
                return 30U;
            }

            return 0U;
        }
        case category::big_straight:
        {
            if((counts[1U] == 0U) && (counts[2U] == 1U) && (counts[3U] == 1U) &&
               (counts[4U] == 1U) && (counts[5U] == 1U) && (counts[6U] == 1U))
            {
                return 30U;
            }

            return 0U;
        }
        case category::choice:
        {
            return sum;
        }
        case category::yacht:
        {
            for(std::size_t face = 1U; face <= 6U; ++face)
            {
                if(counts[face] == 5U)
                {
                    return 50U;
                }
            }

            return 0U;
        }
        default:
        {
            /*  Unreachable in correct use, but required to satisfy all
             *  control paths returning a value.
             */
            return 0U;
        }
    }
}

/*
 * Overload that accepts the category as a textual identifier used by the
 * exercise’s unit-tests.  The text is mapped to the strongly-typed enum and
 * the existing implementation is reused.
 */
[[nodiscard]] auto score(std::array<die_value_t, 5U> const& dice, std::string_view cat_name) -> score_t
{
    if(cat_name == "ones")
    {
        return score(dice, category::ones);
    }
    else if(cat_name == "twos")
    {
        return score(dice, category::twos);
    }
    else if(cat_name == "threes")
    {
        return score(dice, category::threes);
    }
    else if(cat_name == "fours")
    {
        return score(dice, category::fours);
    }
    else if(cat_name == "fives")
    {
        return score(dice, category::fives);
    }
    else if(cat_name == "sixes")
    {
        return score(dice, category::sixes);
    }
    else if(cat_name == "full house")
    {
        return score(dice, category::full_house);
    }
    else if(cat_name == "four of a kind")
    {
        return score(dice, category::four_of_a_kind);
    }
    else if(cat_name == "little straight")
    {
        return score(dice, category::little_straight);
    }
    else if(cat_name == "big straight")
    {
        return score(dice, category::big_straight);
    }
    else if(cat_name == "choice")
    {
        return score(dice, category::choice);
    }
    else if(cat_name == "yacht")
    {
        return score(dice, category::yacht);
    }

    /*  Unknown category string – score zero per the game rules. */
    return 0U;
}

}  // namespace yacht
