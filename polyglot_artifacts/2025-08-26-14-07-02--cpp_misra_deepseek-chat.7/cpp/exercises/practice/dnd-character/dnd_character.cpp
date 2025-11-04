#include "dnd_character.h"
#include <random>
#include <algorithm>
#include <functional>
#include <array>

namespace dnd_character {

std::int32_t modifier(std::int32_t ability) {
    if (ability < 10) {
        return (ability - 11) / 2;
    } else {
        return (ability - 10) / 2;
    }
}

std::int32_t ability() {
    // Create a random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<std::int32_t> dis(1, 6);
    
    // Roll 4 dice
    std::array<std::int32_t, 4> rolls;
    for (int i = 0; i < 4; ++i) {
        rolls[i] = dis(gen);
    }
    
    // Sort in descending order to easily discard the lowest
    std::sort(rolls.begin(), rolls.end(), std::greater<std::int32_t>());
    
    // Sum the top 3
    return (rolls[0] + rolls[1] + rolls[2]);
}

Character::Character() :
    strength(generateAbilityScore()),
    dexterity(generateAbilityScore()),
    constitution(generateAbilityScore()),
    intelligence(generateAbilityScore()),
    wisdom(generateAbilityScore()),
    charisma(generateAbilityScore()),
    hitpoints(10 + modifier(constitution)) {
}

std::int32_t Character::generateAbilityScore() {
    return ability();
}

}  // namespace dnd_character
