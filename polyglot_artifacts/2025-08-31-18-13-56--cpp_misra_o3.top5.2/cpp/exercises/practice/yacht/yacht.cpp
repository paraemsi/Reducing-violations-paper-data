#include "yacht.h"
#include <algorithm>
#include <numeric>
#include <cstddef>
#include <vector>
#include <string>

namespace yacht {

/*---------------------------------------------------------------------------*/
/* Calculate score                                                           */
/*---------------------------------------------------------------------------*/
auto score(dice_vector const& dice, category cat) -> std::uint32_t
{
    /* Count occurrences of each face (indices 1-6 used, 0 unused) */
    std::array<std::uint8_t, 7U> counts { { 0U, 0U, 0U, 0U, 0U, 0U, 0U } };

    for (std::uint8_t value : dice)
    {
        ++counts[static_cast<std::size_t>(value)];
    }

    switch (cat)
    {
        case category::ones:
        case category::twos:
        case category::threes:
        case category::fours:
        case category::fives:
        case category::sixes:
        {
            /* Map enum value 0-5 → face 1-6 */
            std::uint8_t const face =
                static_cast<std::uint8_t>(static_cast<std::uint32_t>(cat) + 1U);

            return static_cast<std::uint32_t>(face) *
                   static_cast<std::uint32_t>(counts[face]);
        }

        case category::full_house:
        {
            bool const has_three =
                (std::find(counts.begin(), counts.end(), 3U) != counts.end());
            bool const has_two =
                (std::find(counts.begin(), counts.end(), 2U) != counts.end());

            if ((has_three) && (has_two))
            {
                std::uint32_t total { 0U };
                for (std::uint8_t v : dice)
                {
                    total += static_cast<std::uint32_t>(v);
                }
                return total;
            }
            else
            {
                return 0;
            }
        }

        case category::four_of_a_kind:
        {
            for (std::uint8_t face = 1U; face <= 6U; ++face)
            {
                if (counts[face] >= 4U)
                {
                    return static_cast<std::uint32_t>(face) * 4U;
                }
            }
            return 0;
        }

        case category::little_straight:
        {
            bool const is_straight =
                (counts[1U] == 1U) && (counts[2U] == 1U) && (counts[3U] == 1U) &&
                (counts[4U] == 1U) && (counts[5U] == 1U) && (counts[6U] == 0U);

            return (is_straight) ? 30U : 0U;
        }

        case category::big_straight:
        {
            bool const is_straight =
                (counts[1U] == 0U) && (counts[2U] == 1U) && (counts[3U] == 1U) &&
                (counts[4U] == 1U) && (counts[5U] == 1U) && (counts[6U] == 1U);

            return (is_straight) ? 30U : 0U;
        }

        case category::choice:
        {
            std::uint32_t total { 0U };
            for (std::uint8_t v : dice)
            {
                total += static_cast<std::uint32_t>(v);
            }
            return total;
        }

        case category::yacht:
        {
            bool const is_yacht =
                (std::find(counts.begin(), counts.end(), 5U) != counts.end());

            return (is_yacht) ? 50 : 0;
        }

        default:
        {
            return 0;
        }
    }
}

/*---------------------------------------------------------------------------*/
/* String overload                                                            */
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
/* C-string overload                                                         */
/*---------------------------------------------------------------------------*/
auto score(dice_vector const& dice, char const* category_name) -> std::uint32_t
{
    return (category_name == nullptr)
               ? 0
               : score(dice, std::string { category_name });
}

/*---------------------------------------------------------------------------*/
/* std::string overload                                                      */
/*---------------------------------------------------------------------------*/
auto score(dice_vector const& dice, std::string const& category_name) -> std::uint32_t
{
    if (category_name == "ones")
    {
        return score(dice, category::ones);
    }
    else if (category_name == "twos")
    {
        return score(dice, category::twos);
    }
    else if (category_name == "threes")
    {
        return score(dice, category::threes);
    }
    else if (category_name == "fours")
    {
        return score(dice, category::fours);
    }
    else if (category_name == "fives")
    {
        return score(dice, category::fives);
    }
    else if (category_name == "sixes")
    {
        return score(dice, category::sixes);
    }
    else if (category_name == "full house")
    {
        return score(dice, category::full_house);
    }
    else if (category_name == "four of a kind")
    {
        return score(dice, category::four_of_a_kind);
    }
    else if (category_name == "little straight")
    {
        return score(dice, category::little_straight);
    }
    else if (category_name == "big straight")
    {
        return score(dice, category::big_straight);
    }
    else if (category_name == "choice")
    {
        return score(dice, category::choice);
    }
    else if (category_name == "yacht")
    {
        return score(dice, category::yacht);
    }
    else
    {
        return 0;
    }
}

}  // namespace yacht
