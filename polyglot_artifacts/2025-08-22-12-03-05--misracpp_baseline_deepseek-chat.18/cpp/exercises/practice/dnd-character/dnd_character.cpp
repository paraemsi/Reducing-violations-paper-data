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
    // To always floor the division
    if (value >= 0) {
        return value / 2;
    } else {
        return (value - 1) / 2;
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
