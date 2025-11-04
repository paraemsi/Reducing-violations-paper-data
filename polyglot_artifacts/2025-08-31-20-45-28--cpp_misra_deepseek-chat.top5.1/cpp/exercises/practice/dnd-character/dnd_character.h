#pragma once
#include <cstdint>

namespace dnd_character {

// Define an alias for the integer type
using ability_score_t = std::int32_t;

ability_score_t ability();
ability_score_t modifier(ability_score_t constitution);

class Character {
public:
    ability_score_t strength;
    ability_score_t dexterity;
    ability_score_t constitution;
    ability_score_t intelligence;
    ability_score_t wisdom;
    ability_score_t charisma;
    ability_score_t hitpoints;
    
    Character();
};

}  // namespace dnd_character
