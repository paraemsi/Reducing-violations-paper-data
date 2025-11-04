#pragma once

#include <cstdint>

namespace dnd_character {

using ability_score_t = std::int32_t;

ability_score_t ability();

ability_score_t modifier(const ability_score_t score) noexcept;

struct Character {
    ability_score_t strength;
    ability_score_t dexterity;
    ability_score_t constitution;
    ability_score_t intelligence;
    ability_score_t wisdom;
    ability_score_t charisma;
    ability_score_t hitpoints;

    Character() noexcept;
};

}  // namespace dnd_character
