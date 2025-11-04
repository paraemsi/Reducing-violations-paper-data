#include "dnd_character.h"
#include <random>
#include <algorithm>
#include <functional>
#include <array>

namespace dnd_character {

std::int32_t ability() {
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
    
    // Sum the first 3 elements with proper parentheses
    return ((rolls[0] + rolls[1]) + rolls[2]);
}

std::int32_t modifier(std::int32_t constitution) {
    // Calculate modifier: (constitution - 10) / 2, rounded down
    std::int32_t diff = (constitution - 10);
    if ((diff < 0)) {
        return ((((diff) - 1)) / 2);
    } else {
        return ((diff) / 2);
    }
}

Character::Character() :
    strength(ability()),
    dexterity(ability()),
    constitution(ability()),
    intelligence(ability()),
    wisdom(ability()),
    charisma(ability()),
    hitpoints(((10) + (modifier(constitution)))) {
}

}  // namespace dnd_character
