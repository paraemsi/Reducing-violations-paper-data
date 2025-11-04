#pragma once

#include <array>
#include <cstdint>

namespace dnd_character {

using ability_score_t = int32_t;
using hitpoint_t = int32_t;

class Character {
public:
    Character();

    ability_score_t ability(const char* ability_name) const;
    hitpoint_t hitpoints() const;
    static ability_score_t modifier(ability_score_t score);

    ability_score_t strength;
    ability_score_t dexterity;
    ability_score_t constitution;
    ability_score_t intelligence;
    ability_score_t wisdom;
    ability_score_t charisma;
    hitpoint_t hitpoints;

private:
    std::array<ability_score_t, 6> abilities_;
    hitpoint_t hitpoints_;
};

ability_score_t ability();

ability_score_t modifier(ability_score_t score);

}  // namespace dnd_character
