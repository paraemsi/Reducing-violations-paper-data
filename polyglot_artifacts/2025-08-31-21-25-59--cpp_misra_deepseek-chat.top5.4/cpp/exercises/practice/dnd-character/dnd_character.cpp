#include "dnd_character.h"
#include <cstdint>
#include <algorithm>
#include <random>
#include <vector>

namespace dnd_character {

std::int32_t ability() {
    // Generate 4 random numbers between 1 and 6
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<std::int32_t> dis(1, 6);
    
    std::vector<std::int32_t> rolls;
    for (std::int32_t i = 0; i < 4; ++i) {
        rolls.push_back(dis(gen));
    }
    
    // Sort in non-decreasing order
    std::sort(rolls.begin(), rolls.end());
    
    // Sum the largest three
    std::int32_t sum = 0;
    for (std::int32_t i = 1; i < 4; ++i) {
        sum = (sum + rolls[i]);
    }
    return sum;
}

std::int32_t modifier(std::int32_t constitution) {
    // Calculate floor((constitution - 10) / 2)
    // This can be done using integer math
    std::int32_t diff = (constitution - 10);
    if (diff >= 0) {
        return (diff / 2);
    } else {
        // For negative numbers, integer division truncates towards zero, but we need to floor
        // So (diff - 1) / 2 will work for negative odd numbers
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
