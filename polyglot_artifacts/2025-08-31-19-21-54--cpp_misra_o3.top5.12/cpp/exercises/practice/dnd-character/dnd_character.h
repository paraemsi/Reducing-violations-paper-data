#pragma once

#include <cstdint>

namespace dnd_character {

std::uint32_t ability();
std::int32_t modifier(std::uint32_t score);

class Character {
public:
    Character();

    std::uint32_t strength;
    std::uint32_t dexterity;
    std::uint32_t constitution;
    std::uint32_t intelligence;
    std::uint32_t wisdom;
    std::uint32_t charisma;

    std::int32_t hitpoints;
};

}  // namespace dnd_character
