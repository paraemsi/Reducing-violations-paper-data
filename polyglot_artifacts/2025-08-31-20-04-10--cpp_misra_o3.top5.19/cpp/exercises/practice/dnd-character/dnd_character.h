#pragma once

#include <array>
#include <cstdint>
#include <random>

namespace dnd_character {

class Character {
public:
    Character();

    /*  ability scores (3 – 18) */
    std::int32_t strength;
    std::int32_t dexterity;
    std::int32_t constitution;
    std::int32_t intelligence;
    std::int32_t wisdom;
    std::int32_t charisma;

    /*  initial hit-points */
    std::int32_t hitpoints;
};

/*  free-standing helpers expected by the tests */
std::int32_t ability();
std::int32_t modifier(std::int32_t score);

}  // namespace dnd_character
