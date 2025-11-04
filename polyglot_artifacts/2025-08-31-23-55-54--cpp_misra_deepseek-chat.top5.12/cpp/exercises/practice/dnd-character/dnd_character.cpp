#include "dnd_character.h"
#include <random>
#include <algorithm>
#include <array>
#include <functional>

namespace dnd_character {

std::int16_t ability() {
    // Generate 4 random numbers between 1 and 6
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<std::int16_t> dis(1, 6);
    
    std::array<std::int16_t, 4> rolls;
    for (int i = 0; i < 4; ++i) {
        rolls[i] = dis(gen);
    }
    
    // Sort to find the three largest
    std::sort(rolls.begin(), rolls.end());
    
    // Sum the last three (largest) values
    return ((rolls[1] + rolls[2]) + rolls[3]);
}

std::int16_t modifier(std::int16_t score) {
    // Calculate modifier using integer division which truncates towards zero
    // Since we need to round down, and (score - 10) can be negative, we need to be careful
    // For integers, division truncates towards zero, but we need floor division
    // So for negative values, we need to adjust
    std::int16_t diff = (score - 10);
    if (diff >= 0) {
        return (diff / 2);
    } else {
        // For negative numbers, we need to adjust to always round down
        // Example: -1 / 2 would be 0 in integer division, but we want -1
        return ((diff - 1) / 2);
    }
}

Character::Character() 
    : strength(ability())
    , dexterity(ability())
    , constitution(ability())
    , intelligence(ability())
    , wisdom(ability())
    , charisma(ability()) 
    , hitpoints((10 + modifier(constitution))) {
}

}  // namespace dnd_character
