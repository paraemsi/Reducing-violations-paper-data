#pragma once
#include <cstdint>

namespace dnd_character {

std::int32_t modifier(std::int32_t ability);
std::int32_t ability();

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
private:
    static std::int32_t generateAbilityScore();
};

}  // namespace dnd_character
