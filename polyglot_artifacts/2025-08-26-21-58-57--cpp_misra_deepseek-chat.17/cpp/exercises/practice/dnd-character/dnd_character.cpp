#include "dnd_character.h"
#include <cstdint>
#include <algorithm>
#include <vector>
#include <random>
#include <functional>

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
    
    // Sort in descending order to easily access the largest three
    std::sort(rolls.begin(), rolls.end(), std::greater<std::int32_t>());
    
    // Sum the first three elements
    std::int32_t sum = 0;
    for (std::int32_t i = 0; i < 3; ++i) {
        sum += rolls[i];
    }
    return sum;
}

std::int32_t modifier(std::int32_t constitution) {
    // Calculate (constitution - 10) / 2, rounded down using integer math
    // This correctly handles floor division for both positive and negative numbers
    std::int32_t diff = (constitution - 10);
    if (diff >= 0) {
        return (diff / 2);
    } else {
        // For negative numbers, this gives us floor division
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
