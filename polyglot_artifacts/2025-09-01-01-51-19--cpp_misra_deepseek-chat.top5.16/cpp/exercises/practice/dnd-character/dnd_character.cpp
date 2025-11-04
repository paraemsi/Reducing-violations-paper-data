#include "dnd_character.h"
#include <random>
#include <vector>
#include <algorithm>
#include <functional>
#include <cstdint>

namespace dnd_character {

ability_score_t ability() {
    // Generate 4 random numbers between 1 and 6
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<ability_score_t> dis(1, 6);
    
    std::vector<ability_score_t> rolls;
    for (ability_score_t i = 0; i < 4; ++i) {
        rolls.push_back(dis(gen));
    }
    
    // Sort in descending order and sum the largest three
    std::sort(rolls.begin(), rolls.end(), std::greater<ability_score_t>());
    return ((rolls[0] + rolls[1]) + rolls[2]);
}

ability_score_t modifier(ability_score_t constitution) {
    // Calculate modifier using floor division
    ability_score_t diff = (constitution - 10);
    if (diff < 0) {
        // For negative numbers, adjust to get floor division
        { 
            return ((diff - ((((diff % 2) != 0) ? 1 : 0))) / 2); 
        }
    } else {
        { 
            return (diff / 2); 
        }
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
    character.hitpoints = 10 + modifier(character.constitution);
    return character;
}

}  // namespace dnd_character
