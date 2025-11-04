#pragma once

#include <array>
#include <cstdint>

namespace dnd_character {

using ability_t = ::std::int32_t;

// Standalone modifier function as required by tests
ability_t modifier(ability_t score);

ability_t ability();

class Character {
public:
    Character();

    ability_t ability_strength() const;
    ability_t ability_dexterity() const;
    ability_t ability_constitution() const;
    ability_t ability_intelligence() const;
    ability_t ability_wisdom() const;
    ability_t ability_charisma() const;

    ability_t ability_modifier(ability_t score) const;
    ability_t hitpoints() const;

    // Expose fields as required by tests
    ability_t strength;
    ability_t dexterity;
    ability_t constitution;
    ability_t intelligence;
    ability_t wisdom;
    ability_t charisma;
    ability_t hitpoints;
};

}  // namespace dnd_character
