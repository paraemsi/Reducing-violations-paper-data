#include "dnd_character.h"
#include <vector>
#include <algorithm>
#include <functional>
#include <random>
#include <numeric>
#include <cmath>

namespace dnd_character {

// Helper function to roll a single die
int roll_die() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(1, 6);
    return dis(gen);
}

int ability() {
    // Roll 4 dice
    std::vector<int> rolls;
    for (int i = 0; i < 4; ++i) {
        rolls.push_back(roll_die());
    }
    
    // Sort in descending order to easily discard the smallest
    std::sort(rolls.begin(), rolls.end(), std::greater<int>());
    
    // Sum the largest three
    int sum = 0;
    for (int i = 0; i < 3; ++i) {
        sum += rolls[i];
    }
    return sum;
}

int modifier(int constitution) {
    return static_cast<int>(std::floor((constitution - 10) / 2.0));
}

// Character constructor implementation
Character::Character() :
    strength(ability()),
    dexterity(ability()),
    constitution(ability()),
    intelligence(ability()),
    wisdom(ability()),
    charisma(ability()),
    hitpoints(10 + modifier(constitution)) {
}

}  // namespace dnd_character
