#pragma once

#include <array>
#include <cstdint>

namespace dnd_character {

using ability_t = std::int32_t;  // fixed-width signed type for all ability scores

/*  Roll a single ability score (4d6, drop the lowest). */
auto ability() -> ability_t;

/*  Compute the D&D ability modifier for a given score. */
auto modifier(ability_t score) -> ability_t;

/*  Generate all six ability scores in the canonical order. */
auto abilities() -> std::array<ability_t, 6U>;

class Character {
public:
    Character();

    /*  Ability scores – rolled at construction time. */
    ability_t strength;
    ability_t dexterity;
    ability_t constitution;
    ability_t intelligence;
    ability_t wisdom;
    ability_t charisma;

    /*  Derived stat. */
    ability_t hitpoints;
};

}  // namespace dnd_character
