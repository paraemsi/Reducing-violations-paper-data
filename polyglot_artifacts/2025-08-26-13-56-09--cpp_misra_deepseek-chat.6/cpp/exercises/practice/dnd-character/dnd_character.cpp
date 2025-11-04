#include "dnd_character.h"
#include <cstdint>
#include <vector>
#include <algorithm>
#include <functional>
#include <random>

namespace dnd_character {

ability_score_t ability() {
    // Generate 4 random numbers between 1 and 6
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<ability_score_t> dis(1, 6);
    
    std::vector<ability_score_t> rolls;
    for (int i = 0; i < 4; ++i) {
        rolls.push_back(dis(gen));
    }
    
    // Sort in descending order and sum the largest three
    std::sort(rolls.begin(), rolls.end(), std::greater<ability_score_t>());
    return ((rolls[0] + rolls[1]) + rolls[2]);
}

ability_score_t modifier(ability_score_t constitution) {
    // Calculate modifier: (constitution - 10) / 2, always rounded down
    ability_score_t value = (constitution - 10);
    // For integer division that always floors, we can use this approach
    if (value >= 0) {
        return (value / 2);
    } else {
        // For negative numbers, this ensures proper flooring
        return ((value - 1) / 2);
    }
}

Character generate_character() {
    Character character;
    // Generate all six abilities
    character.strength = ability();
    character.dexterity = ability();
    character.constitution = ability();
    character.intelligence = ability();
    character.wisdom = ability();
    character.charisma = ability();
    
    // Calculate hitpoints
    character.hitpoints = (10 + modifier(character.constitution));
    return character;
}

}  // namespace dnd_character
