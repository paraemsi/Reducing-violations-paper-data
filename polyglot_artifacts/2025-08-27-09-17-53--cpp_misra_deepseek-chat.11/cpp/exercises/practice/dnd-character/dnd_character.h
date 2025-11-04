#pragma once
#include <cstdint>

namespace dnd_character {

std::int32_t ability();
std::int32_t modifier(std::int32_t constitution);

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

}  // namespace dnd_character
