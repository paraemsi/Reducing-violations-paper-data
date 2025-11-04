#pragma once

#include <cstdint>

namespace dnd_character {

// Roll four 6-sided dice, discard the lowest, sum the rest.
std::int32_t ability();

// Calculate the ability modifier as floor((score − 10) / 2)
std::int32_t modifier(std::int32_t score);

class Character {
public:
    Character();

    std::int32_t strength{};
    std::int32_t dexterity{};
    std::int32_t constitution{};
    std::int32_t intelligence{};
    std::int32_t wisdom{};
    std::int32_t charisma{};
    std::int32_t hitpoints{};

};

}  // namespace dnd_character
