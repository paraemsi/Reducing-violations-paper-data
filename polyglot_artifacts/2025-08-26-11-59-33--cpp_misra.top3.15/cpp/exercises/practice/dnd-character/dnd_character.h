#pragma once

#include <array>
#include <cstdint>
#include <random>

namespace dnd_character {

using ability_score_t = std::int32_t;
using hitpoint_t = std::int32_t;

struct character
{
    std::array<ability_score_t, 6> abilities;
    hitpoint_t hitpoints;

    ability_score_t strength() const { return abilities[0]; }
    ability_score_t dexterity() const { return abilities[1]; }
    ability_score_t constitution() const { return abilities[2]; }
    ability_score_t intelligence() const { return abilities[3]; }
    ability_score_t wisdom() const { return abilities[4]; }
    ability_score_t charisma() const { return abilities[5]; }
};

character generate_character();
ability_score_t ability();
int modifier(ability_score_t score);

}  // namespace dnd_character
