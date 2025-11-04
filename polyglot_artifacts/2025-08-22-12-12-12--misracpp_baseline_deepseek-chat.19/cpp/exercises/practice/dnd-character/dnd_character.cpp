#include "dnd_character.h"
#include <vector>
#include <algorithm>
#include <functional>
#include <random>

namespace dnd_character {

Character::Character() :
    strength(ability()),
    dexterity(ability()),
    constitution(ability()),
    intelligence(ability()),
    wisdom(ability()),
    charisma(ability()),
    hitpoints(10 + modifier(constitution)) {
}

int ability() {
    // Generate 4 random numbers between 1 and 6
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 6);
    
    std::vector<int> rolls;
    for (int i = 0; i < 4; ++i) {
        rolls.push_back(dis(gen));
    }
    
    // Sort in descending order to easily pick the top 3
    std::sort(rolls.begin(), rolls.end(), std::greater<int>());
    
    // Sum the first 3 elements
    int sum = 0;
    for (int i = 0; i < 3; ++i) {
        sum += rolls[i];
    }
    return sum;
}

int modifier(int constitution) {
    int value = constitution - 10;
    if (value >= 0) {
        return value / 2;
    } else {
        // For negative values, we need to handle rounding towards negative infinity
        // This can be done by (value - 1) / 2 to adjust the integer division which truncates towards zero
        return (value - 1) / 2;
    }
}

}  // namespace dnd_character
