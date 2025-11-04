#include "dnd_character.h"
#include <vector>
#include <algorithm>
#include <functional>
#include <random>
#include <cmath>

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
    
    // Sort in descending order and sum the top 3
    std::sort(rolls.begin(), rolls.end(), std::greater<int>());
    return rolls[0] + rolls[1] + rolls[2];
}

int modifier(int constitution) {
    return static_cast<int>(std::floor((constitution - 10) / 2.0));
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
