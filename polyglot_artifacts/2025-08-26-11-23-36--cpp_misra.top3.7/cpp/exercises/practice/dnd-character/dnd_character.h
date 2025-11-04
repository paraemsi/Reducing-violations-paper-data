#pragma once

#include <array>
#include <cstdint>

namespace dnd_character {

using ability_t = std::int32_t;

struct Character
{
    std::array<ability_t, 6U> abilities;
    ability_t hitpoints;

    ability_t strength() const { return abilities[0]; }
    ability_t dexterity() const { return abilities[1]; }
    ability_t constitution() const { return abilities[2]; }
    ability_t intelligence() const { return abilities[3]; }
    ability_t wisdom() const { return abilities[4]; }
    ability_t charisma() const { return abilities[5]; }
};

Character generate();
ability_t modifier(ability_t score);
ability_t ability();

}  // namespace dnd_character
