#include "dnd_character.h"
#include <cstdint>
#include <algorithm>
#include <random>
#include <functional>
#include <vector>
#include <cmath>

namespace dnd_character {


std::int16_t ability() {
    // Generate 4 random numbers between 1 and 6
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<std::int16_t> dis(1, 6);
    
    std::vector<std::int16_t> rolls;
    for (int i = 0; i < 4; ++i) {
        rolls.push_back(dis(gen));
    }
    
    // Sort in descending order to easily discard the smallest
    std::sort(rolls.begin(), rolls.end(), std::greater<std::int16_t>());
    
    // Sum the largest three
    std::int16_t sum = 0;
    for (int i = 0; i < 3; ++i) {
        sum += rolls[i];
    }
    return sum;
}

std::int16_t modifier(std::int16_t score) {
    // (score - 10) / 2, rounded down (always floor towards negative infinity)
    // Use floor division to handle both positive and negative correctly
    return static_cast<std::int16_t>(std::floor((score - 10) / 2.0));
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
