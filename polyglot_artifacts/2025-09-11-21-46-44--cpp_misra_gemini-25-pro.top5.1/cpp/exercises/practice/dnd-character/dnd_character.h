#pragma once

#include <cstdint>

namespace dnd_character {

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

constexpr std::int32_t modifier(std::int32_t score) {
    return (score < 10) ? (((score - 10) - 1) / 2) : ((score - 10) / 2);
}
std::int32_t ability();

}  // namespace dnd_character
