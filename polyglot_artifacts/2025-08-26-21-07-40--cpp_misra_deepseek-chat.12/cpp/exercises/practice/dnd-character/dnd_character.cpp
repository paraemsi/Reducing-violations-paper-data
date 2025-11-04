#include "dnd_character.h"
#include <random>
#include <algorithm>
#include <functional>
#include <array>
#include <cstdint>

namespace dnd_character {

namespace {

std::int32_t generate_ability_score() {
    // Roll 4 six-sided dice
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<std::int32_t> dis(1, 6);
    
    std::array<std::int32_t, 4> rolls;
    for (std::int32_t i = 0; i < 4; ++i) {
        rolls[i] = dis(gen);
    }
    
    // Sort in descending order to easily discard the lowest
    std::sort(rolls.begin(), rolls.end(), std::greater<std::int32_t>());
    
    // Sum the largest three
    return (rolls[0] + rolls[1] + rolls[2]);
}

} // namespace

std::int32_t ability() {
    return generate_ability_score();
}

std::int32_t modifier(std::int32_t score) {
    std::int32_t value = (score - 10);
    std::int32_t modifier_value = (value / 2);
    // Adjust for negative odd numbers to always round down
    if ((value < 0) && ((value % 2) != 0)) {
        modifier_value -= 1;
    }
    return modifier_value;
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
