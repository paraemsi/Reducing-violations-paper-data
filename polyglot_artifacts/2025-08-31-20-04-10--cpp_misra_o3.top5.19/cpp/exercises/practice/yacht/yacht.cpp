#include "yacht.h"

#include <array>
#include <algorithm>
#include <cstddef>
#include <string_view>

namespace yacht {

auto score(const std::array<std::uint8_t, 5U>& dice, category cat) -> std::uint32_t
{
    /* Count occurrences of each face (1-6) */
    std::array<std::uint8_t, 6U> counts {};
    for(const std::uint8_t die : dice)
    {
        counts[static_cast<std::size_t>(die) - 1U] =
            static_cast<std::uint8_t>(counts[static_cast<std::size_t>(die) - 1U] + 1U);
    }

    switch(cat)
    {
        case category::ones:
        case category::twos:
        case category::threes:
        case category::fours:
        case category::fives:
        case category::sixes:
        {
            const std::uint8_t face =
                static_cast<std::uint8_t>(static_cast<std::uint8_t>(cat) + 1U);
            const std::uint32_t count =
                static_cast<std::uint32_t>(counts[static_cast<std::size_t>(face) - 1U]);
            return (count * static_cast<std::uint32_t>(face));
        }

        case category::full_house:
        {
            bool has_three {false};
            bool has_two {false};
            std::uint32_t total {0U};
            for(const std::uint8_t die : dice)
            {
                total = static_cast<std::uint32_t>(total + static_cast<std::uint32_t>(die));
            }
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
            if((has_three) && (has_two))
            {
                return total;
            }
            return 0U;
        }

        case category::four_of_a_kind:
        {
            for(std::size_t i {0U}; i < counts.size(); ++i)
            {
                if(counts[i] >= 4U)
                {
                    const std::uint32_t face =
                        static_cast<std::uint32_t>(i + 1U);
                    return (face * 4U);
                }
            }
            return 0U;
        }

        case category::little_straight:
        {
            std::array<std::uint8_t, 5U> target {1U, 2U, 3U, 4U, 5U};
            std::array<std::uint8_t, 5U> sorted {};
            std::copy(dice.begin(), dice.end(), sorted.begin());
            std::sort(sorted.begin(), sorted.end());
            if(sorted == target)
            {
                return 30U;
            }
            return 0U;
        }

        case category::big_straight:
        {
            std::array<std::uint8_t, 5U> target {2U, 3U, 4U, 5U, 6U};
            std::array<std::uint8_t, 5U> sorted {};
            std::copy(dice.begin(), dice.end(), sorted.begin());
            std::sort(sorted.begin(), sorted.end());
            if(sorted == target)
            {
                return 30U;
            }
            return 0U;
        }

        case category::choice:
        {
            std::uint32_t total {0U};
            for(const std::uint8_t die : dice)
            {
                total = static_cast<std::uint32_t>(total + static_cast<std::uint32_t>(die));
            }
            return total;
        }

        case category::yacht:
        {
            if(counts[static_cast<std::size_t>(dice[0U]) - 1U] == 5U)
            {
                return 50U;
            }
            return 0U;
        }

        default:
        {
            return 0U;
        }
    }
}

auto to_category(std::string_view name) -> category
{
    if(name == "ones")
    {
        return category::ones;
    }
    else if(name == "twos")
    {
        return category::twos;
    }
    else if(name == "threes")
    {
        return category::threes;
    }
    else if(name == "fours")
    {
        return category::fours;
    }
    else if(name == "fives")
    {
        return category::fives;
    }
    else if(name == "sixes")
    {
        return category::sixes;
    }
    else if(name == "full house")
    {
        return category::full_house;
    }
    else if(name == "four of a kind")
    {
        return category::four_of_a_kind;
    }
    else if(name == "little straight")
    {
        return category::little_straight;
    }
    else if(name == "big straight")
    {
        return category::big_straight;
    }
    else if(name == "choice")
    {
        return category::choice;
    }
    else
    {
        return category::yacht;
    }
}

auto score(const std::array<std::uint8_t, 5U>& dice, std::string_view cat) -> std::uint32_t
{
    return score(dice, to_category(cat));
}

}  // namespace yacht
