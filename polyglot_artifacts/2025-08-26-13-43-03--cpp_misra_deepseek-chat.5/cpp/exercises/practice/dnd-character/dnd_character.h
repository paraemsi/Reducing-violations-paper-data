#pragma once
#include <cstdint>

namespace dnd_character {

using ability_score_t = std::int16_t;
using modifier_t = std::int16_t;
using hitpoints_t = std::int16_t;

ability_score_t ability();
modifier_t modifier(ability_score_t constitution);

class Character {
public:
    ability_score_t strength;
    ability_score_t dexterity;
    ability_score_t constitution;
    ability_score_t intelligence;
    ability_score_t wisdom;
    ability_score_t charisma;
    hitpoints_t hitpoints;
    
    Character();
};

}  // namespace dnd_character
