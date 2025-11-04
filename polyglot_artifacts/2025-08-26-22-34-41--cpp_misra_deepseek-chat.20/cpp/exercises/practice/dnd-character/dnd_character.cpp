#include "dnd_character.h"
#include <cstdint>
#include <algorithm>
#include <vector>
#include <random>
#include <functional>

namespace dnd_character {

ability_score_t ability() {
    // Generate 4 random numbers between 1 and 6
    std::random_device rd;
    std::mt19937 gen(rd());
    // Use a type that's not a standard integer type
    using dist_type = std::uniform_int_distribution<ability_score_t>;
    dist_type dis(1, 6);
    
    std::vector<ability_score_t> rolls;
    for (ability_score_t i = 0; (i < 4); ++i) {
        rolls.push_back(dis(gen));
    }
    
    // Sort in descending order to easily access the largest three
    std::sort(rolls.begin(), rolls.end(), std::greater<ability_score_t>());
    
    // Sum the first three elements
    ability_score_t sum = 0;
    for (ability_score_t i = 0; (i < 3); ++i) {
        sum = (sum + rolls[i]);
    }
    return sum;
}

ability_score_t modifier(ability_score_t constitution) {
    // Calculate (constitution - 10) / 2, rounded down using floor division
    ability_score_t result = (constitution - 10);
    if ((result < 0)) {
        // Adjust for floor division with negative numbers
        return (((result - 1)) / 2);
    } else {
        return ((result) / 2);
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
