#include "dnd_character.h"
#include <cstdint>
#include <algorithm>
#include <vector>
#include <random>

namespace dnd_character {

std::int32_t ability() {
    // Generate 4 random dice rolls
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<std::int32_t> dis(1, 6);
    
    std::vector<std::int32_t> rolls;
    for (std::int32_t i = 0; i < 4; ++i) {
        rolls.push_back(dis(gen));
    }
    
    // Sort in descending order
    std::sort(rolls.begin(), rolls.end(), std::greater<std::int32_t>());
    
    // Sum the top three with proper parentheses
    return ((rolls[0] + rolls[1]) + rolls[2]);
}

std::int32_t modifier(std::int32_t constitution) {
    // Calculate modifier using flooring division
    // This works because integer division truncates towards zero, and we want to always floor
    // So for negative numbers, we need to adjust
    std::int32_t diff = (constitution - 10);
    if (diff >= 0) {
        return (diff / 2);
    } else {
        // For negative numbers, subtract 1 before dividing to always floor
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
