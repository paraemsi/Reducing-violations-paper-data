#pragma once

#include <cstdint>
#include <cstddef>

namespace dnd_character
{
    // Fixed-width aliases complying with MISRA C++
    using ability_score_t = std::uint8_t;   // 0 – 18
    using modifier_t      = std::int8_t;    // −5 – +5
    using hit_point_t     = std::int16_t;   // sufficient for hit points

    // Generate a single ability score: roll 4d6 and drop the lowest
    ability_score_t ability();

    // Calculate the corresponding ability modifier (floor((score-10)/2))
    modifier_t modifier(ability_score_t score);

    class Character
    {
    public:
        Character();

        ability_score_t strength{};
        ability_score_t dexterity{};
        ability_score_t constitution{};
        ability_score_t intelligence{};
        ability_score_t wisdom{};
        ability_score_t charisma{};

        hit_point_t     hitpoints{};

    };
} // namespace dnd_character
