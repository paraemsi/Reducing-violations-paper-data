#pragma once
#include <cstdint>

namespace dnd_character {

std::int16_t ability();
std::int16_t modifier(std::int16_t constitution);

class Character {
public:
    Character();
    std::int16_t strength;
    std::int16_t dexterity;
    std::int16_t constitution;
    std::int16_t intelligence;
    std::int16_t wisdom;
    std::int16_t charisma;
    std::int16_t hitpoints;
};

}  // namespace dnd_character
