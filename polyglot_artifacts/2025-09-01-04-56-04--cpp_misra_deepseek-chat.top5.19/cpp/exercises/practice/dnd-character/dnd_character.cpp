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
    
    // Sort in descending order to easily discard the smallest
    std::sort(rolls.begin(), rolls.end(), std::greater<std::int32_t>());
    
    // Sum the largest three
    std::int32_t sum = 0;
    for (std::int32_t i = 0; i < 3; ++i) {
        sum += rolls[i];
    }
    return sum;
}

std::int32_t modifier(std::int32_t constitution) {
    std::int32_t base = constitution - 10;
    if (base >= 0) {
        return base / 2;
    } else {
        // For negative numbers, adjust to get floor division
        return (base - 1) / 2;
    }
}

Character::Character() 
    : strength(ability()), 
      dexterity(ability()), 
      constitution(ability()), 
      intelligence(ability()), 
      wisdom(ability()), 
      charisma(ability()),
      hitpoints(10 + modifier(constitution)) {
}

}  // namespace dnd_character
