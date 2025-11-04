#pragma once

#include <cstdint>

namespace dnd_character {

using Score = std::int32_t;

/*  Roll four six-sided dice, discard the lowest roll,
    and return the sum of the remaining three. */
Score ability();

/*  Calculate the ability modifier, i.e.
    floor((score - 10) / 2). */
Score modifier(Score score);

class Character {
public:
    Character();

    /*  Public ability scores and hit-points, as required by the tests. */
    Score strength;
    Score dexterity;
    Score constitution;
    Score intelligence;
    Score wisdom;
    Score charisma;
    Score hitpoints;
};

}  // namespace dnd_character
