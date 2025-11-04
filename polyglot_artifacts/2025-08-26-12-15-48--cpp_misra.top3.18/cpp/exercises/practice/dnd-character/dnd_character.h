#pragma once

#include <array>
#include <cstdint>

namespace dnd_character {

using ability_t = std::int32_t;

class Character {
public:
    Character();

    ability_t ability(std::size_t index) const;
    ability_t strength() const;
    ability_t dexterity() const;
    ability_t constitution() const;
    ability_t intelligence() const;
    ability_t wisdom() const;
    ability_t charisma() const;

    ability_t hitpoints() const;
    ability_t ability_modifier(ability_t score) const;

private:
    std::array<ability_t, 6U> abilities_;
    ability_t hitpoints_;
};

ability_t modifier(ability_t score);

}  // namespace dnd_character
