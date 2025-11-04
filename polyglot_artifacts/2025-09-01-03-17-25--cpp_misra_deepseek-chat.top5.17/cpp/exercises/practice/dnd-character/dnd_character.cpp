#include "dnd_character.h"
#include <random>
#include <algorithm>
#include <functional>
#include <array>
#include <cstdint>

namespace dnd_character {

namespace {

std::int16_t generateAbilityScore() {
    // Generate 4 random numbers between 1 and 6
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<std::int16_t> dis(1, 6);
    
    std::array<std::int16_t, 4> rolls;
    for (int i = 0; i < 4; ++i) {
        rolls[i] = dis(gen);
    }
    
    // Sort in descending order to easily pick the top 3
    std::sort(rolls.begin(), rolls.end(), std::greater<std::int16_t>());
    
    // Sum the largest three
    std::int16_t sum = 0;
    for (int i = 0; i < 3; ++i) {
        sum += rolls[i];
    }
    return sum;
}

} // namespace

std::int16_t ability() {
    return generateAbilityScore();
}

std::int16_t modifier(std::int16_t score) {
    std::int16_t diff = score - 10;
    // To always round down, we need to adjust for negative numbers
    if (diff >= 0) {
        return diff / 2;
    } else {
        // For negative numbers, this ensures proper flooring
        return (diff - 1) / 2;
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
