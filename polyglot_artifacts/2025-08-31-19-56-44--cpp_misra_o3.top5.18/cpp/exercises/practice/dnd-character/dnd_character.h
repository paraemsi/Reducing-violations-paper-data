#pragma once

#include <array>
#include <cstdint>

namespace dnd_character {

//--------------------------------------------------------------------------
// Fixed-width aliases to avoid direct use of banned fundamental types
//--------------------------------------------------------------------------
using ability_t   = std::int32_t;
using hitpoint_t  = std::int32_t;

 //--------------------------------------------------------------------------
// Roll a single ability score (3–18) using 4d6 drop-lowest
//--------------------------------------------------------------------------
ability_t ability();

//--------------------------------------------------------------------------
// Calculate an ability modifier – floor((score − 10) / 2)
//--------------------------------------------------------------------------
ability_t modifier(ability_t score);

//--------------------------------------------------------------------------
// Character – generates six ability scores and derived hit-points
//--------------------------------------------------------------------------
class Character {
public:
    Character();

    // ability scores (3‒18)
    ability_t strength{};
    ability_t dexterity{};
    ability_t constitution{};
    ability_t intelligence{};
    ability_t wisdom{};
    ability_t charisma{};

    // derived value
    hitpoint_t hitpoints{};
};

}  // namespace dnd_character
