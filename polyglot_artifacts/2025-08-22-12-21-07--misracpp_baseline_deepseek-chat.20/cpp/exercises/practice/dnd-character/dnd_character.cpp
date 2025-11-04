#include "dnd_character.h"
#include <vector>
#include <algorithm>
#include <functional>
#include <random>

namespace dnd_character {

int ability() {
    // Generate 4 random numbers between 1 and 6
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 6);
    
    std::vector<int> rolls;
    for (int i = 0; i < 4; ++i) {
        rolls.push_back(dis(gen));
    }
    
    // Sort in descending order and sum the largest three
    std::sort(rolls.begin(), rolls.end(), std::greater<int>());
    return rolls[0] + rolls[1] + rolls[2];
}

int modifier(int constitution) {
    int value = constitution - 10;
    if (value >= 0) {
        return value / 2;
    } else {
        // Adjust for integer division truncating towards zero
        return (value - 1) / 2;
    }
}

Character::Character() {
    strength = ability();
    dexterity = ability();
    constitution = ability();
    intelligence = ability();
    wisdom = ability();
    charisma = ability();
    hitpoints = 10 + modifier(constitution);
}

}  // namespace dnd_character
