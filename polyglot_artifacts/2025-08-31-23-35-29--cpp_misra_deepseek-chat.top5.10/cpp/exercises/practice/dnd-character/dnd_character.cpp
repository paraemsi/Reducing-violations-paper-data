#include "dnd_character.h"
#include <random>
#include <algorithm>
#include <array>
#include <cstdint>
#include <utility>

namespace dnd_character {

std::int32_t ability() {
    // Use a static random number generator to avoid reinitialization
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<std::int32_t> dis(1, 6);
    
    std::array<std::int32_t, 4> rolls;
    for (std::int32_t i = 0; i < 4; ++i) {
        rolls[i] = dis(gen);
    }
    
    // Sort in ascending order
    for (std::int32_t i = 0; i < 4; ++i) {
        for (std::int32_t j = i + 1; j < 4; ++j) {
            if (rolls[i] > rolls[j]) {
                std::swap(rolls[i], rolls[j]);
            }
        }
    }
    
    // Sum the last three elements (largest ones)
    return ((rolls[1] + rolls[2]) + rolls[3]);
}

std::int32_t modifier(std::int32_t constitution) {
    std::int32_t value = (constitution - 10);
    if (value >= 0) {
        return (value / 2);
    } else {
        // For negative values, we need to always floor
        // Since integer division truncates towards zero, we need to adjust
        // (value - 1) / 2 would work for integers to always floor
        // Let's test: (-7 -1)/2 = -8/2 = -4 which matches
        return ((value - 1) / 2);
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
