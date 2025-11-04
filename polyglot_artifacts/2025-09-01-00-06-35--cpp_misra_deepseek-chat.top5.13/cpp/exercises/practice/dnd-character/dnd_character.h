#pragma once
#include <cstdint>

namespace dnd_character {

using ability_score_t = std::int32_t;

ability_score_t ability();
ability_score_t modifier(ability_score_t constitution);

struct Character {
    ability_score_t strength;
    ability_score_t dexterity;
    ability_score_t constitution;
    ability_score_t intelligence;
    ability_score_t wisdom;
    ability_score_t charisma;
    ability_score_t hitpoints;
};

inline Character generate() {
    Character character;
    character.strength = ability();
    character.dexterity = ability();
    character.constitution = ability();
    character.intelligence = ability();
    character.wisdom = ability();
    character.charisma = ability();
    character.hitpoints = 10 + modifier(character.constitution);
    return character;
}

}  // namespace dnd_character
