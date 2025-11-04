#pragma once
#include <cstdint>

namespace dnd_character {

// Define an alias for a fixed-width integer type
using ability_score_t = std::int16_t;

struct Character {
    ability_score_t strength;
    ability_score_t dexterity;
    ability_score_t constitution;
    ability_score_t intelligence;
    ability_score_t wisdom;
    ability_score_t charisma;
    ability_score_t hitpoints;
};

ability_score_t ability();
ability_score_t modifier(ability_score_t constitution);
Character generate_character();

}  // namespace dnd_character
