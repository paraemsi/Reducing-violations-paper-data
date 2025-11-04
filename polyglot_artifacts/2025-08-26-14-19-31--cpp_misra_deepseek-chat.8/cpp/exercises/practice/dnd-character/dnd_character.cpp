#include "dnd_character.h"
#include <random>
#include <algorithm>
#include <functional>
#include <array>
#include <cstdint>

namespace dnd_character {

std::int16_t ability() {
    // Use a static random number generator to avoid reinitialization
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<std::int16_t> dis(1, 6);
    
    std::array<std::int16_t, 4> rolls;
    for (int i = 0; i < 4; ++i) {
        rolls[i] = dis(gen);
    }
    
    // Sort in descending order to easily pick the top 3
    std::sort(rolls.begin(), rolls.end(), std::greater<std::int16_t>());
    
    // Sum the first 3 elements
    std::int16_t sum = 0;
    for (int i = 0; i < 3; ++i) {
        sum = static_cast<std::int16_t>(sum + rolls[i]);
    }
    return sum;
}

std::int16_t modifier(std::int16_t score) {
    // Calculate modifier with flooring division to always round down
    std::int16_t base = static_cast<std::int16_t>(score - 10);
    if (base >= 0) {
        return static_cast<std::int16_t>(base / 2);
    } else {
        // For negative numbers, we need to adjust to always floor
        // (x // 2) for negative x can be done as -((-x) // 2) but that's not always correct
        // Instead, we can use (x - 1) / 2 for negative numbers to always floor
        return static_cast<std::int16_t>((base - 1) / 2);
    }
}

Character::Character() :
    strength(ability()),
    dexterity(ability()),
    constitution(ability()),
    intelligence(ability()),
    wisdom(ability()),
    charisma(ability()),
    hitpoints(static_cast<std::int16_t>(10 + modifier(constitution))) {
}

}  // namespace dnd_character
