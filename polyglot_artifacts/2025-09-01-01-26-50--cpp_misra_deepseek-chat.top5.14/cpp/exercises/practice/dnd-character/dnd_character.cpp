#include "dnd_character.h"
#include <cstdint>
#include <random>
#include <algorithm>
#include <functional>
#include <vector>

namespace dnd_character {

std::int16_t ability() {
    // Generate 4 random numbers between 1 and 6
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<std::int16_t> dis(1, 6);
    
    std::vector<std::int16_t> rolls(4);
    for (std::int32_t i = 0; i < 4; i++) {
        rolls[i] = dis(gen);
    }
    
    // Sort in descending order to easily discard the smallest
    std::sort(rolls.begin(), rolls.end(), std::greater<std::int16_t>());
    
    // Sum the largest three
    std::int16_t sum = 0;
    for (std::int32_t i = 0; i < 3; i++) {
        sum = static_cast<std::int16_t>(sum + rolls[i]);
    }
    return sum;
}

std::int16_t modifier(std::int16_t constitution) {
    // Calculate modifier: floor((constitution - 10) / 2)
    // Use integer division which truncates towards zero, but we need floor
    std::int16_t diff = static_cast<std::int16_t>((constitution - 10));
    if (diff < 0) {
        // For negative numbers, adjust to always round down
        return static_cast<std::int16_t>(((diff) - 1) / 2);
    } else {
        return static_cast<std::int16_t>((diff) / 2);
    }
}

Character generate_character() {
    Character character;
    character.strength = ability();
    character.dexterity = ability();
    character.constitution = ability();
    character.intelligence = ability();
    character.wisdom = ability();
    character.charisma = ability();
    
    // Calculate hitpoints
    character.hitpoints = static_cast<std::int16_t>(10 + modifier(character.constitution));
    return character;
}

}  // namespace dnd_character
