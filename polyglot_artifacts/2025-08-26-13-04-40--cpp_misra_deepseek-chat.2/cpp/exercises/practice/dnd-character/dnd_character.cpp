#include "dnd_character.h"
#include <random>
#include <algorithm>
#include <array>
#include <cstdint>

namespace dnd_character {

std::int32_t ability() {
    // Generate 4 random numbers between 1 and 6
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<std::int32_t> dis(1, 6);
    
    std::array<std::int32_t, 4> rolls;
    for (std::int32_t i = 0; i < 4; ++i) {
        rolls[i] = dis(gen);
    }
    
    // Sort to easily discard the lowest
    std::sort(rolls.begin(), rolls.end());
    
    // Sum the largest three
    std::int32_t sum = 0;
    sum = (sum + rolls[3]);
    sum = (sum + rolls[2]);
    sum = (sum + rolls[1]);
    return sum;
}

std::int32_t modifier(std::int32_t constitution) {
    // Calculate floor((constitution - 10) / 2)
    std::int32_t base = (constitution - 10);
    // For integer division in C++, when base is negative, we need to adjust to get floor division
    if (base < 0) {
        return ((base - 1) / 2);
    } else {
        return (base / 2);
    }
}

Character::Character() :
    strength(ability()),
    dexterity(ability()),
    constitution(ability()),
    intelligence(ability()),
    wisdom(ability()),
    charisma(ability()),
    hitpoints(10 + modifier(constitution)) {
}

}  // namespace dnd_character
