#include "dnd_character.h"
#include <random>
#include <algorithm>
#include <functional>
#include <array>

namespace dnd_character {

namespace {

std::int16_t generate_ability_score() {
    // Generate 4 random numbers between 1 and 6
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<std::int16_t> dis(1, 6);
    
    std::array<std::int16_t, 4> rolls;
    for (int i = 0; i < 4; ++i) {
        rolls[i] = dis(gen);
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

} // namespace

std::int16_t modifier(std::int16_t constitution) {
    std::int16_t base = constitution - 10;
    // To always round down, we can use integer division which truncates towards zero
    // But for negative numbers, we need to adjust
    if (base >= 0) {
        return base / 2;
    } else {
        // For negative numbers, this ensures flooring behavior
        // Example: -7 / 2 would truncate to -3, but we want -4
        return (base - 1) / 2;
    }
}

std::int16_t ability() {
    return generate_ability_score();
}

Character::Character() :
    strength(ability()),
    dexterity(ability()),
    constitution(ability()),
    intelligence(ability()),
    wisdom(ability()),
    charisma(ability()) {
    hitpoints = 10 + modifier(constitution);
}

}  // namespace dnd_character
