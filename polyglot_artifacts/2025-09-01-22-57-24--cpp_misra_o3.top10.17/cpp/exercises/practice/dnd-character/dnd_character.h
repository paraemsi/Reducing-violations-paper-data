#pragma once

#include <array>
#include <cstdint>

namespace dnd_character {

//  Fixed-width signed integer used for every ability‐related value
using ability_score_t = std::int32_t;

//  Roll a single ability score: roll four 6-sided dice, drop the lowest,
//  and return the sum of the remaining three.
auto ability() -> ability_score_t;

//  Generate a full set of six ability scores in the usual order
//  (strength, dexterity, constitution, intelligence, wisdom, charisma).
auto abilities() -> std::array<ability_score_t, 6U>;

 //  Compute the ability modifier specified by the D&D rules.
auto ability_modifier(ability_score_t score) -> ability_score_t;

//  Wrapper expected by the tests – forwards to ability_modifier.
auto modifier(ability_score_t score) -> ability_score_t;

//  A complete D&D character with the six abilities and derived hit-points.
class Character {
public:
    Character();

    //  Public ability scores – the reference tests access them directly.
    ability_score_t strength{};
    ability_score_t dexterity{};
    ability_score_t constitution{};
    ability_score_t intelligence{};
    ability_score_t wisdom{};
    ability_score_t charisma{};

    //  Derived statistic – also accessed directly by the tests.
    ability_score_t hitpoints{};
};

}   // namespace dnd_character
