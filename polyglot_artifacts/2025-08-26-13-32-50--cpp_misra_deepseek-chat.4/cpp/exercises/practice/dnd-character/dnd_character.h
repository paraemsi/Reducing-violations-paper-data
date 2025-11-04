#pragma once
#include <cstdint>

namespace dnd_character {

struct Character {
    std::int32_t strength;
    std::int32_t dexterity;
    std::int32_t constitution;
    std::int32_t intelligence;
    std::int32_t wisdom;
    std::int32_t charisma;
    std::int32_t hitpoints;
};

std::int32_t ability();
std::int32_t modifier(std::int32_t constitution);
std::int32_t generate_hitpoints(std::int32_t constitution);
Character generate();

}  // namespace dnd_character
