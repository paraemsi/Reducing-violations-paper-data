#include "dnd_character.h"
#include <algorithm>
#include <random>
#include <vector>

namespace dnd_character {

// Random number generator - static to maintain state between calls
static std::random_device rd;
static std::mt19937 gen(rd());
static std::uniform_int_distribution<> d6(1, 6);

int ability() {
    // Roll 4d6, drop the lowest, sum the highest 3
    std::vector<int> rolls;
    for (int i = 0; i < 4; ++i) {
        rolls.push_back(d6(gen));
    }
    
    // Sort to easily find the lowest
    std::sort(rolls.begin(), rolls.end());
    
    // Sum the highest 3 (skip the first/lowest)
    int sum = 0;
    for (int i = 1; i < 4; ++i) {
        sum += rolls[i];
    }
    
    return sum;
}

int modifier(int score) {
    // Calculate modifier: (score - 10) / 2, rounded down
    // Integer division in C++ rounds toward zero, which works for positive results
    // For negative results, we need to handle rounding down properly
    int diff = score - 10;
    if (diff >= 0) {
        return diff / 2;
    } else {
        // For negative numbers, we need to round down (more negative)
        return (diff - 1) / 2;
    }
}

Character::Character() {
    // Generate the six ability scores
    strength = ability();
    dexterity = ability();
    constitution = ability();
    intelligence = ability();
    wisdom = ability();
    charisma = ability();
    
    // Calculate hitpoints: 10 + constitution modifier
    hitpoints = 10 + modifier(constitution);
}

}  // namespace dnd_character
