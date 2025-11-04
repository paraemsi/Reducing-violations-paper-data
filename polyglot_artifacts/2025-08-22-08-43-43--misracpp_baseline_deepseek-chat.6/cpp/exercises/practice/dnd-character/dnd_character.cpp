#include "dnd_character.h"
#include <vector>
#include <algorithm>
#include <functional>
#include <random>

namespace dnd_character {

int ability() {
    // Create a random number generator
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(1, 6);
    
    // Roll four dice
    std::vector<int> rolls;
    for (int i = 0; i < 4; ++i) {
        rolls.push_back(dis(gen));
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
    int value = constitution - 10;
    if (value >= 0) {
        return value / 2;
    } else {
        // For negative values, this ensures floor division
        return (value - 1) / 2;
    }
}

Character create() {
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
