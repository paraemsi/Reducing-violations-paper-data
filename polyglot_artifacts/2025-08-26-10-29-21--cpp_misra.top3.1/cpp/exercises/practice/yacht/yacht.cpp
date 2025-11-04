#include "yacht.h"
#include <algorithm>
#include <array>
#include <cstdint>
#include <cstring>

namespace yacht {

// Helper: Map string to category_t
bool category_from_string(const char* str, category_t& out_category)
{
    // Compare against all valid category names
    struct category_map_entry {
        const char* name;
        category_t cat;
    };
    static const category_map_entry mapping[] = {
        {"ones", category_t::ones},
        {"twos", category_t::twos},
        {"threes", category_t::threes},
        {"fours", category_t::fours},
        {"fives", category_t::fives},
        {"sixes", category_t::sixes},
        {"full house", category_t::full_house},
        {"four of a kind", category_t::four_of_a_kind},
        {"little straight", category_t::little_straight},
        {"big straight", category_t::big_straight},
        {"choice", category_t::choice},
        {"yacht", category_t::yacht}
    };
    for(std::size_t i = 0U; i < (sizeof(mapping)/sizeof(mapping[0])); ++i)
    {
        if(std::strcmp(str, mapping[i].name) == 0)
        {
            out_category = mapping[i].cat;
            return true;
        }
    }
    return false;
}

// Overload: Accept string category
score_t score(const std::array<dice_value_t, YACHT_NUM_DICE>& dice, const char* category_name)
{
    category_t cat;
    if(category_from_string(category_name, cat))
    {
        return score(dice, cat);
    }
    // If invalid string, return 0
    return 0U;
}

score_t score(const std::array<dice_value_t, YACHT_NUM_DICE>& dice, category_t category)
{
    // Count occurrences of each dice value (1-6)
    std::array<std::uint8_t, 6U> counts = {0U, 0U, 0U, 0U, 0U, 0U};
    for(std::size_t i = 0U; i < YACHT_NUM_DICE; ++i)
    {
        // dice values are 1-6, so subtract 1 for index
        ++(counts[static_cast<std::size_t>(dice[i]) - 1U]);
    }

    switch(category)
    {
        case category_t::ones:
        case category_t::twos:
        case category_t::threes:
        case category_t::fours:
        case category_t::fives:
        case category_t::sixes:
        {
            // Category index matches dice value minus 1
            std::size_t idx = static_cast<std::size_t>(category);
            return static_cast<score_t>((idx + 1U) * counts[idx]);
        }
        case category_t::full_house:
        {
            bool has_three = false;
            bool has_two = false;
            score_t total = 0U;
            for(std::size_t i = 0U; i < counts.size(); ++i)
            {
                if(counts[i] == 3U)
                {
                    has_three = true;
                }
                else if(counts[i] == 2U)
                {
                    has_two = true;
                }
                total = static_cast<score_t>(total + ((i + 1U) * counts[i]));
            }
            if(has_three && has_two)
            {
                return total;
            }
            return 0U;
        }
        case category_t::four_of_a_kind:
        {
            for(std::size_t i = 0U; i < counts.size(); ++i)
            {
                if(counts[i] >= 4U)
                {
                    return static_cast<score_t>((i + 1U) * 4U);
                }
            }
            return 0U;
        }
        case category_t::little_straight:
        {
            // 1-2-3-4-5
            for(std::size_t i = 0U; i < 5U; ++i)
            {
                if(counts[i] != 1U)
                {
                    return 0U;
                }
            }
            if(counts[5U] == 0U)
            {
                return 30U;
            }
            return 0U;
        }
        case category_t::big_straight:
        {
            // 2-3-4-5-6
            if(counts[0U] == 0U)
            {
                for(std::size_t i = 1U; i < 6U; ++i)
                {
                    if(counts[i] != 1U)
                    {
                        return 0U;
                    }
                }
                return 30U;
            }
            return 0U;
        }
        case category_t::choice:
        {
            score_t total = 0U;
            for(std::size_t i = 0U; i < counts.size(); ++i)
            {
                total = static_cast<score_t>(total + ((i + 1U) * counts[i]));
            }
            return total;
        }
        case category_t::yacht:
        {
            for(std::size_t i = 0U; i < counts.size(); ++i)
            {
                if(counts[i] == 5U)
                {
                    return 50U;
                }
            }
            return 0U;
        }
        default:
        {
            // Should not reach here
            return 0U;
        }
    }
}

}  // namespace yacht
