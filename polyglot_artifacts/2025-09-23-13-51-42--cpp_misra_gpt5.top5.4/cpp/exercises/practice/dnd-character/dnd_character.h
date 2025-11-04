#pragma once

#include <cstdint>

namespace dnd_character {

using score_t = int;

class Character {
public:
    Character();

    score_t strength;
    score_t dexterity;
    score_t constitution;
    score_t intelligence;
    score_t wisdom;
    score_t charisma;

    score_t hitpoints;

};

score_t ability();
score_t modifier(score_t score);

}  // namespace dnd_character
