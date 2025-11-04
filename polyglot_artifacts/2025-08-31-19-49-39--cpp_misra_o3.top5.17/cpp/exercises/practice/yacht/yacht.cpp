#include "yacht.h"

#include <algorithm>
#include <array>
#include <numeric>
#include <string_view>
#include <initializer_list>

namespace yacht {

auto score(const std::array<std::uint8_t, 5U>& dice, category cat) -> std::uint32_t
{
    std::uint32_t result {0U};

    std::array<std::uint8_t, 6U> counts {};
    for(const auto value : dice) {
        ++counts[static_cast<std::size_t>(value) - 1U];
    }

    switch (cat) {
    case category::ones:
    case category::twos:
    case category::threes:
    case category::fours:
    case category::fives:
    case category::sixes:
    {
        const std::uint8_t face { static_cast<std::uint8_t>(static_cast<std::uint8_t>(cat) + 1U) };
        result = static_cast<std::uint32_t>(face) * static_cast<std::uint32_t>(counts[face - 1U]);
        break;
    }
    case category::full_house:
    {
        bool has_three { false };
        bool has_two { false };
        std::uint32_t sum {0U};
        for(std::uint8_t idx = 0U; idx < 6U; ++idx) {
            if(counts[idx] == 3U) { has_three = true; }
            if(counts[idx] == 2U) { has_two = true; }
            sum += static_cast<std::uint32_t>((static_cast<std::uint32_t>(idx) + 1U) * counts[idx]);
        }
        if((has_three) && (has_two)) {
            result = sum;
        } else {
            result = 0U;
        }
        break;
    }
    case category::four_of_a_kind:
    {
        for(std::uint8_t idx = 0U; idx < 6U; ++idx) {
            if(counts[idx] >= 4U) {
                result = static_cast<std::uint32_t>((static_cast<std::uint32_t>(idx) + 1U) * 4U);
                break;
            }
        }
        break;
    }
    case category::little_straight:
    {
        if((counts[0U] == 1U) && (counts[1U] == 1U) && (counts[2U] == 1U) && (counts[3U] == 1U) && (counts[4U] == 1U)) {
            result = 30U;
        }
        break;
    }
    case category::big_straight:
    {
        if((counts[1U] == 1U) && (counts[2U] == 1U) && (counts[3U] == 1U) && (counts[4U] == 1U) && (counts[5U] == 1U)) {
            result = 30U;
        }
        break;
    }
    case category::choice:
    {
        result = std::accumulate(dice.cbegin(), dice.cend(), 0U);
        break;
    }
    case category::yacht:
    {
        for(const auto count : counts) {
            if(count == 5U) {
                result = 50U;
            }
        }
        break;
    }
    default:
    {
        result = 0U;
        break;
    }
    }

    return result;
}

auto score(const std::array<std::uint8_t, 5U>& dice, std::string_view cat) -> std::uint32_t
{
    category mapped {};

    if(cat == "ones") {
        mapped = category::ones;
    } else if(cat == "twos") {
        mapped = category::twos;
    } else if(cat == "threes") {
        mapped = category::threes;
    } else if(cat == "fours") {
        mapped = category::fours;
    } else if(cat == "fives") {
        mapped = category::fives;
    } else if(cat == "sixes") {
        mapped = category::sixes;
    } else if(cat == "full house") {
        mapped = category::full_house;
    } else if(cat == "four of a kind") {
        mapped = category::four_of_a_kind;
    } else if(cat == "little straight") {
        mapped = category::little_straight;
    } else if(cat == "big straight") {
        mapped = category::big_straight;
    } else if(cat == "choice") {
        mapped = category::choice;
    } else if(cat == "yacht") {
        mapped = category::yacht;
    } else {
        return 0U;
    }

    return score(dice, mapped);
}

auto score(std::initializer_list<int_dice_t> dice_init, std::string_view cat) -> std::uint32_t
{
    if(dice_init.size() != 5U) {
        return 0U;
    }

    std::array<std::uint8_t, 5U> dice_array {};
    std::size_t idx {0U};
    for(const int_dice_t value : dice_init) {
        dice_array[idx] = static_cast<std::uint8_t>(value);
        ++idx;
    }

    return score(dice_array, cat);
}

}  // namespace yacht
