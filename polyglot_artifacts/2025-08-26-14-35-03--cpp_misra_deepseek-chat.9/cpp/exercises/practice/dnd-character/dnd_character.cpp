#include "dnd_character.h"
#include <random>
#include <algorithm>
#include <functional>
#include <array>
#include <cstdint>

namespace dnd_character {

Character::Character() :
    strength(ability()),
    dexterity(ability()),
    constitution(ability()),
    intelligence(ability()),
    wisdom(ability()),
    charisma(ability()),
    hitpoints((10 + modifier(constitution))) {
}

std::int32_t ability() {
    // Generate 4 random numbers between 1 and 6
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<std::int32_t> dis(1, 6);
    
    std::array<std::int32_t, 4> rolls;
    for (std::int32_t i = 0; i < 4; ++i) {
        rolls[i] = dis(gen);
    }
    
    // Sort in descending order to easily discard the smallest
    std::sort(rolls.begin(), rolls.end(), std::greater<std::int32_t>());
    
    // Sum the largest three
    return (rolls[0] + rolls[1] + rolls[2]);
}

std::int32_t modifier(std::int32_t constitution) {
    // Calculate (constitution - 10) / 2, rounded down
    std::int32_t result = (constitution - 10);
    if (result < 0) {
        // For negative numbers, subtracting 1 before dividing to get floor division
        return (((result) - 1) / 2);
    } else {
        return ((result) / 2);
    }
}

}  // namespace dnd_character
