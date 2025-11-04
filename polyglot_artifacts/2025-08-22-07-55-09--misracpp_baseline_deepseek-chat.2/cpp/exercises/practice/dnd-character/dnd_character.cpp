#include "dnd_character.h"
#include <vector>
#include <algorithm>
#include <random>
#include <functional>
#include <cmath>

namespace dnd_character {

int ability() {
    // Create a random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 6);
    
    // Roll 4 dice
    std::vector<int> rolls;
    for (int i = 0; i < 4; ++i) {
        rolls.push_back(dis(gen));
    }
    
    // Sort in descending order to easily pick the top 3
    std::sort(rolls.begin(), rolls.end(), std::greater<int>());
    
    // Sum the top 3
    int sum = 0;
    for (int i = 0; i < 3; ++i) {
        sum += rolls[i];
    }
    return sum;
}

int modifier(int constitution) {
    return std::floor((constitution - 10) / 2.0);
}

int generate_hitpoints(int constitution) {
    return 10 + modifier(constitution);
}

Character generate() {
    Character character;
    character.strength = ability();
    character.dexterity = ability();
    character.constitution = ability();
    character.intelligence = ability();
    character.wisdom = ability();
    character.charisma = ability();
    character.hitpoints = generate_hitpoints(character.constitution);
    return character;
}

}  // namespace dnd_character
