#pragma once
#include <cstdint>

namespace dnd_character {

class Character {
public:
    std::int32_t strength;
    std::int32_t dexterity;
    std::int32_t constitution;
    std::int32_t intelligence;
    std::int32_t wisdom;
    std::int32_t charisma;
    std::int32_t hitpoints;
    
    Character();
};

std::int32_t ability();
std::int32_t modifier(std::int32_t constitution);

}  // namespace dnd_character
