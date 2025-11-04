#include "dnd_character.h"
#include <random>
#include <algorithm>
#include <functional>
#include <array>
#include <cstdint>

namespace dnd_character {

ability_score_t ability() {
    // Generate 4 random numbers between 1 and 6
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<std::int32_t> dis(1, 6);
    
    std::array<std::int32_t, 4> rolls;
    for (std::int32_t i = 0; i < 4; ++i) {
        rolls[i] = dis(gen);
    }
    
    // Sort in descending order to easily pick the top 3
    std::sort(rolls.begin(), rolls.end(), std::greater<std::int32_t>());
    
    // Sum the largest 3 with proper parentheses
    ability_score_t sum = static_cast<ability_score_t>((rolls[0] + rolls[1]) + rolls[2]);
    return sum;
}

ability_score_t modifier(ability_score_t constitution) {
    std::int32_t value = (static_cast<std::int32_t>(constitution) - 10);
    if (value >= 0) {
        return (static_cast<ability_score_t>(value / 2));
    } else {
        // For negative values, adjust to always floor
        return (static_cast<ability_score_t>((value - 1) / 2));
    }
}

Character generate() {
    Character character;
    character.strength = ability();
    character.dexterity = ability();
    character.constitution = ability();
    character.intelligence = ability();
    character.wisdom = ability();
    character.charisma = ability();
    character.hitpoints = static_cast<ability_score_t>(10 + modifier(character.constitution));
    return character;
}

}  // namespace dnd_character
