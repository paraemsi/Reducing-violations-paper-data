#pragma once

#include <cstdint>

namespace dnd_character {

/* Fixed-width aliases per MISRA guidance: avoid plain 'int' family keywords */
using ability_score_t = std::int32_t;
using ability_modifier_t = std::int32_t;
using hitpoints_t = std::int32_t;

class Character {
public:
    Character();

    ability_score_t strength;
    ability_score_t dexterity;
    ability_score_t constitution;
    ability_score_t intelligence;
    ability_score_t wisdom;
    ability_score_t charisma;
    hitpoints_t hitpoints;
};

ability_score_t ability();
ability_modifier_t modifier(ability_score_t score);

}  // namespace dnd_character
