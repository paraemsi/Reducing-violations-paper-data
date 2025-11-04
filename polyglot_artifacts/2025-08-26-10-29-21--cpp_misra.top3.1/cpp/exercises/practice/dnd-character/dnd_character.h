#pragma once

#include <array>
#include <cstdint>

namespace dnd_character {

using ability_score_t = std::int32_t;

class Character {
public:
    Character();

    ability_score_t ability(const char* ability_name) const;
    ability_score_t strength() const;
    ability_score_t dexterity() const;
    ability_score_t constitution() const;
    ability_score_t intelligence() const;
    ability_score_t wisdom() const;
    ability_score_t charisma() const;

    ability_score_t hitpoints() const;
    static ability_score_t modifier(ability_score_t score);

private:
    std::array<ability_score_t, 6> abilities_;
    ability_score_t hitpoints_;
    static ability_score_t roll_ability();
};

ability_score_t ability();

}  // namespace dnd_character
