#pragma once

#include <cstdint>

namespace dnd_character {

using score_type = std::int32_t;

score_type ability();
score_type modifier(score_type score);

class Character {
public:
    Character();

    score_type strength;
    score_type dexterity;
    score_type constitution;
    score_type intelligence;
    score_type wisdom;
    score_type charisma;
    score_type hitpoints;
};

}  // namespace dnd_character
