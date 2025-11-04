#pragma once

#include <array>
#include <cstdint>

namespace dnd_character {

using ability_t = std::int32_t;

class Character {
public:
    Character();

    [[nodiscard]] ability_t strength() const;
    [[nodiscard]] ability_t dexterity() const;
    [[nodiscard]] ability_t constitution() const;
    [[nodiscard]] ability_t intelligence() const;
    [[nodiscard]] ability_t wisdom() const;
    [[nodiscard]] ability_t charisma() const;
    [[nodiscard]] ability_t hitpoints() const;

private:
    std::array<ability_t, 6U> abilities_;
    ability_t hitpoints_;

    static ability_t ability();
    static ability_t modifier(ability_t score);
};

ability_t ability();

}  // namespace dnd_character
