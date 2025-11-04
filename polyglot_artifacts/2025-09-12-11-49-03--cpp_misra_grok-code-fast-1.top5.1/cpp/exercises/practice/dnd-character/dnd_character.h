#pragma once

#include <cstdint>

namespace dnd_character {

struct Character {
    std::uint32_t strength;
    std::uint32_t dexterity;
    std::uint32_t constitution;
    std::uint32_t intelligence;
    std::uint32_t wisdom;
    std::uint32_t charisma;
    std::uint32_t hitpoints;
};

std::uint32_t ability();
std::int32_t modifier(std::uint32_t score);
Character generate_character();

}  // namespace dnd_character
