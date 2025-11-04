#include "dnd_character.h"
#include <random>
#include <algorithm>
#include <functional>
#include <array>
#include <cstdint>

namespace dnd_character {

std::int32_t ability() {
    // Generate 4 random numbers between 1 and 6
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<std::int32_t> dis(1, 6);
    
    std::array<std::int32_t, 4> rolls;
    for (std::int32_t i = 0; i < 4; ++i) {
        rolls[i] = dis(gen);
    }
    
    // Sort to find the three largest
    std::sort(rolls.begin(), rolls.end());
    
    // Sum the largest three dice
    std::int32_t sum = ((rolls[1] + rolls[2]) + rolls[3]);
    return sum;
}

std::int32_t modifier(std::int32_t constitution) {
    std::int32_t value = (constitution - 10);
    if (value >= 0) {
        return (value / 2);
    } else {
        return (((value) - 1) / 2);
    }
}

Character::Character() :
    strength(ability()),
    dexterity(ability()),
    constitution(ability()),
    intelligence(ability()),
    wisdom(ability()),
    charisma(ability()),
    hitpoints((10 + modifier(constitution))) 
{
}

}  // namespace dnd_character
