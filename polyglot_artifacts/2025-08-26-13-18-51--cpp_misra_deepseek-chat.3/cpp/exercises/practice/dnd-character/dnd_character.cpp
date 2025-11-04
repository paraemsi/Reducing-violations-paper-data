#include "dnd_character.h"
#include <random>
#include <algorithm>
#include <functional>
#include <array>
#include <cstdint>

namespace dnd_character {

std::int32_t ability() {
    // Generate 4 random numbers between 1 and 6
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<std::int32_t> dis(1, 6);
    
    std::array<std::int32_t, 4> rolls;
    for (int i = 0; i < 4; ++i) {
        rolls[i] = dis(gen);
    }
    
    // Sort to find the three largest
    std::sort(rolls.begin(), rolls.end(), std::greater<std::int32_t>());
    
    // Sum the first three
    return (rolls[0] + rolls[1] + rolls[2]);
}

std::int32_t modifier(std::int32_t constitution) {
    std::int32_t base = constitution - 10;
    // To always floor, we can use integer division which truncates towards zero for positive numbers
    // For negative numbers, we need to adjust
    if (base >= 0) {
        return base / 2;
    } else {
        // For negative numbers, this ensures proper flooring
        // Example: (base - 1) / 2 when base is negative
        // base = -1: (-1 -1)/2 = -2/2 = -1 which matches floor(-0.5) = -1
        // base = -2: (-2 -1)/2 = -3/2 = -1 which matches floor(-1) = -1
        // base = -3: (-3 -1)/2 = -4/2 = -2 which matches floor(-1.5) = -2
        // base = -4: (-4 -1)/2 = -5/2 = -2 which matches floor(-2) = -2
        return (base - 1) / 2;
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
