#pragma once

#include <array>
#include <cstdint>

namespace dnd_character {

using ability_t = std::int32_t;

struct Character
{
    std::array<ability_t, 6U> abilities{};
    ability_t hitpoints{};

    // Ability accessors
    ability_t strength() const { return abilities[0U]; }
    ability_t dexterity() const { return abilities[1U]; }
    ability_t constitution() const { return abilities[2U]; }
    ability_t intelligence() const { return abilities[3U]; }
    ability_t wisdom() const { return abilities[4U]; }
    ability_t charisma() const { return abilities[5U]; }
};

// Returns a random ability score (4d6 drop lowest)
ability_t ability();

// Returns the modifier for a given ability score
ability_t modifier(ability_t score);

Character generate();

}  // namespace dnd_character
