#include "dnd_character.h"
#include <random>
#include <algorithm>
#include <functional>
#include <array>
#include <cstdint>

namespace dnd_character {

ability_score_t ability() {
    // Use a static random number generator to avoid reinitialization
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<ability_score_t> dis(1, 6);
    
    // Roll 4 dice
    std::array<ability_score_t, 4> rolls;
    for (ability_score_t i = 0; i < 4; ++i) {
        rolls[i] = dis(gen);
    }
    
    // Sort in ascending order to easily discard the smallest
    std::sort(rolls.begin(), rolls.end());
    
    // Sum the largest three (last three elements)
    return (rolls[1] + rolls[2] + rolls[3]);
}

modifier_t modifier(ability_score_t constitution) {
    // Calculate (constitution - 10), then divide by 2 with flooring
    // For integer division that always floors, we can use:
    ability_score_t diff = constitution - 10;
    // If diff is non-negative, normal integer division works (truncation towards zero is same as floor)
    // If diff is negative, we need to adjust to always floor
    return (diff >= 0) ? (diff / 2) : ((diff - 1) / 2);
}

Character::Character() :
    strength(ability()),
    dexterity(ability()),
    constitution(ability()),
    intelligence(ability()),
    wisdom(ability()),
    charisma(ability()),
    hitpoints(static_cast<hitpoints_t>(10 + modifier(constitution))) {
}

}  // namespace dnd_character
