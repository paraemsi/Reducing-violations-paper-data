#include "dnd_character.h"
#include <cstdint>
#include <algorithm>
#include <vector>
#include <random>
#include <functional>

namespace dnd_character {

std::int32_t ability() {
    // Generate 4 random numbers between 1 and 6
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<std::int32_t> dis(1, 6);
    
    std::vector<std::int32_t> rolls;
    for (std::int32_t i = 0; i < 4; ++i) {
        rolls.push_back(dis(gen));
    }
    
    // Sort in descending order to easily discard the smallest
    std::sort(rolls.begin(), rolls.end(), std::greater<std::int32_t>());
    
    // Sum the largest three with explicit parentheses
    std::int32_t sum = ((rolls[0] + rolls[1]) + rolls[2]);
    return sum;
}

std::int32_t modifier(std::int32_t constitution) {
    // Calculate floor((constitution - 10) / 2)
    // We can use integer division which truncates towards zero, but we need to adjust for negative numbers
    std::int32_t diff = (constitution - 10);
    if (diff >= 0) {
        return (diff / 2);
    } else {
        // For negative numbers, integer division truncates towards zero, but we want floor which is more negative
        // So (diff - 1) / 2 will give the correct result
        return ((diff - 1) / 2);
    }
}

Character generate() {
    Character character;
    character.strength = ability();
    character.dexterity = ability();
    character.constitution = ability();
    character.intelligence = ability();
    character.wisdom = ability();
    character.charisma = ability();
    character.hitpoints = (10 + modifier(character.constitution));
    return character;
}

}  // namespace dnd_character
