#pragma once

#include <cstdint>

namespace dnd_character {

using Score = std::int32_t;
using HitPoints = std::int32_t;

Score ability();
Score modifier(Score score);

class Character {
public:
    Character();

    Score strength;
    Score dexterity;
    Score constitution;
    Score intelligence;
    Score wisdom;
    Score charisma;
    HitPoints hitpoints;
};

}  // namespace dnd_character
