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
    
    // Roll 4 dice
    std::int32_t dice1 = dis(gen);
    std::int32_t dice2 = dis(gen);
    std::int32_t dice3 = dis(gen);
    std::int32_t dice4 = dis(gen);
    
    // Find the smallest die to discard
    std::int32_t min_die = dice1;
    if ((dice2 < min_die)) { 
        min_die = dice2; 
    }
    if ((dice3 < min_die)) { 
        min_die = dice3; 
    }
    if ((dice4 < min_die)) { 
        min_die = dice4; 
    }
    
    // Sum all dice and subtract the smallest
    std::int32_t total = ((dice1 + dice2) + (dice3 + dice4));
    return (total - min_die);
}

std::int32_t modifier(std::int32_t constitution) {
    // Calculate (constitution - 10) / 2, always rounding down
    std::int32_t base = (constitution - 10);
    if (base >= 0) {
        return (base / 2);
    } else {
        // For negative numbers, subtracting 1 before division always rounds down
        return ((base - 1) / 2);
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
