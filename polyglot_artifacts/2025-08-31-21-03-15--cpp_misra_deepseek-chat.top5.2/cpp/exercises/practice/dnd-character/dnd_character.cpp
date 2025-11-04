#include "dnd_character.h"
#include <random>
#include <algorithm>
#include <functional>
#include <array>
#include <cstdint>
#include <cmath>

namespace dnd_character {

std::int16_t ability() {
    // Use a random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<std::int16_t> dis(1, 6);
    
    // Roll 4 dice
    std::array<std::int16_t, 4> rolls;
    for (std::int32_t i = 0; i < 4; ++i) {
        rolls[i] = dis(gen);
    }
    
    // Sort in descending order to get the highest values first
    std::sort(rolls.begin(), rolls.end(), std::greater<std::int16_t>());
    
    // Sum the first three (largest) values
    std::int16_t sum = 0;
    for (std::int32_t i = 0; i < 3; ++i) {
        sum = static_cast<std::int16_t>(sum + rolls[i]);
    }
    return sum;
}

std::int16_t modifier(std::int16_t constitution) {
    // Always floor the result of (constitution - 10) / 2.0
    // Using floating point division and then floor
    double result = (constitution - 10) / 2.0;
    return static_cast<std::int16_t>(std::floor(result));
}

Character::Character() 
    : strength(ability())
    , dexterity(ability())
    , constitution(ability())
    , intelligence(ability())
    , wisdom(ability())
    , charisma(ability())
    , hitpoints(static_cast<std::int16_t>(10 + modifier(constitution))) {
}

}  // namespace dnd_character
