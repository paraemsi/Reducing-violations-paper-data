#pragma once
#include <cstdint>

namespace dnd_character {

std::int32_t ability();
std::int32_t modifier(std::int32_t score);

class Character {
public:
    Character();
    // Make member variables public to match test expectations
    std::int32_t strength;
    std::int32_t dexterity;
    std::int32_t constitution;
    std::int32_t intelligence;
    std::int32_t wisdom;
    std::int32_t charisma;
    std::int32_t hitpoints;
};

}  // namespace dnd_character
