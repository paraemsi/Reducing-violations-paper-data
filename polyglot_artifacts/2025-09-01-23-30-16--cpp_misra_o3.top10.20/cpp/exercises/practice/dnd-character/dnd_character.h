#pragma once
#include <cstdint>

namespace dnd_character {

std::int32_t ability();

std::int32_t modifier(std::int32_t score);

class Character {
public:
    Character();

    const std::int32_t strength;
    const std::int32_t dexterity;
    const std::int32_t constitution;
    const std::int32_t intelligence;
    const std::int32_t wisdom;
    const std::int32_t charisma;
    const std::int32_t hitpoints;
};

}  // namespace dnd_character
