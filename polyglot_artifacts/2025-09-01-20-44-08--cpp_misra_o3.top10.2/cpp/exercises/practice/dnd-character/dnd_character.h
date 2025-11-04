#pragma once

#include <array>
#include <cstdint>

namespace dnd_character {

/* Fixed-width aliases to satisfy MISRA C++ rules */
using ability_t  = std::uint16_t;  /* 3-18 fits, avoids unsigned-char arithmetic */
using hp_t       = std::int32_t;   /* use 32-bit signed – avoids narrowing in constructor */
using modifier_t = std::int32_t;   /* keep signed 32-bit for arithmetic in modifier() */

/* Roll one ability score (4d6, drop lowest) */
ability_t ability();

/* Calculate the ability modifier per D&D rules */
modifier_t modifier(ability_t score);

class Character
{
public:
    Character();

    /* ability scores and hitpoints are exposed as public
       data members because the unit tests access them directly */
    ability_t strength;
    ability_t dexterity;
    ability_t constitution;
    ability_t intelligence;
    ability_t wisdom;
    ability_t charisma;

    hp_t hitpoints;
};

}  // namespace dnd_character
