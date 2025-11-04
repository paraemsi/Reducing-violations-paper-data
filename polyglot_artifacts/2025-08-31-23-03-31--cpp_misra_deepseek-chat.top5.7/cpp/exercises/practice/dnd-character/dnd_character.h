#pragma once

#include <cstdint>

namespace dnd_character {

struct Character {
    std::int16_t strength;
    std::int16_t dexterity;
    std::int16_t constitution;
    std::int16_t intelligence;
    std::int16_t wisdom;
    std::int16_t charisma;
    std::int16_t hitpoints;
};

std::int16_t modifier(std::int16_t score);
std::int16_t ability();
Character generate();

}  // namespace dnd_character
