#pragma once

#include <array>
#include <algorithm>
#include <cstdint>
#include <random>

namespace dnd_character {

//  Fixed-width signed integer type used throughout this module
using score_t = std::int32_t;

//  Free-standing helpers expected by the unit-tests
score_t ability();                 // roll 4d6, keep highest 3
score_t modifier(score_t score);   // floor((score - 10) / 2)

class Character {
public:
    Character();

    //  Ability score helpers remain available here, but wrappers
    //  are also provided at namespace scope.
    static score_t ability();                 // roll 4d6, keep highest 3
    static score_t modifier(score_t score);   // floor((score - 10) / 2)

    //  Public constant data members as required by the unit-tests
    const score_t strength;
    const score_t dexterity;
    const score_t constitution;
    const score_t intelligence;
    const score_t wisdom;
    const score_t charisma;

    const score_t hitpoints;
};

}  // namespace dnd_character
