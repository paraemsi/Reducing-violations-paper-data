#include "dnd_character.h"
#include <cstdint>
#include <vector>
#include <algorithm>
#include <functional>
#include <random>

namespace dnd_character {

score_t ability() {
    // Generate 4 random numbers between 1 and 6
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<score_t> dis(1, 6);
    
    std::vector<score_t> rolls;
    for (score_t i = 0; i < 4; ++i) {
        rolls.push_back(dis(gen));
    }
    
    // Sort in descending order to easily pick the top 3
    std::sort(rolls.begin(), rolls.end(), std::greater<score_t>());
    
    // Sum the largest 3
    score_t sum = 0;
    for (score_t i = 0; i < 3; ++i) {
        sum = (sum + rolls[i]);
    }
    return sum;
}

score_t modifier(score_t constitution) {
    score_t diff = (constitution - 10);
    if (diff >= 0) {
        return (diff / 2);
    } else {
        // For negative numbers, adjust to always floor
        return ((diff - 1) / 2);
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
    character.hitpoints = (10 + modifier(character.constitution));
    return character;
}

}  // namespace dnd_character
