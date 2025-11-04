#include "dnd_character.h"
#include <random>
#include <algorithm>
#include <array>
#include <functional>
#include <cstdint>

namespace dnd_character {

namespace {

// Generate a single ability score by rolling 4 six-sided dice and summing the largest three
std::int16_t generate_ability_score() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<std::int16_t> dis(1, 6);
    
    std::array<std::int16_t, 4> rolls;
    for (std::int16_t& roll : rolls) {
        roll = dis(gen);
    }
    
    // Sort in ascending order
    std::sort(rolls.begin(), rolls.end());
    
    // Sum the last three (largest) rolls
    return (rolls[1] + rolls[2] + rolls[3]);
}

} // namespace

std::int16_t ability() {
    return generate_ability_score();
}

std::int16_t modifier(std::int16_t constitution) {
    // Calculate the difference
    std::int16_t diff = constitution - 10;
    // Always floor the division
    if (diff >= 0) {
        return diff / 2;
    } else {
        // For negative numbers, this ensures proper flooring
        return (diff - 1) / 2;
    }
}

Character::Character() :
    strength(generate_ability_score()),
    dexterity(generate_ability_score()),
    constitution(generate_ability_score()),
    intelligence(generate_ability_score()),
    wisdom(generate_ability_score()),
    charisma(generate_ability_score()),
    hitpoints(10 + modifier(constitution)) {
}

}  // namespace dnd_character
