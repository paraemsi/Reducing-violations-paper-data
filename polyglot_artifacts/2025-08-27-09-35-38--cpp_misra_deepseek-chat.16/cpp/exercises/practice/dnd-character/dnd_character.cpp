#include "dnd_character.h"
#include <random>
#include <algorithm>
#include <functional>
#include <array>

namespace dnd_character {

AbilityScore ability() {
    // Generate 4 random numbers between 1 and 6
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 6);
    
    std::array<int, 4> rolls;
    for (int i = 0; i < 4; ++i) {
        rolls[i] = dis(gen);
    }
    
    // Sort in descending order to easily discard the smallest
    std::sort(rolls.begin(), rolls.end(), std::greater<int>());
    
    // Sum the largest three
    int sum = 0;
    for (int i = 0; i < 3; ++i) {
        sum += rolls[i];
    }
    return AbilityScore(sum);
}

AbilityScore modifier(AbilityScore constitution) {
    int diff = static_cast<int>(constitution) - 10;
    if (diff >= 0) {
        return AbilityScore(diff / 2);
    } else {
        // Adjust for negative numbers to always round down
        return AbilityScore((diff - 1) / 2);
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
    
    // Calculate hitpoints
    AbilityScore constitution_modifier = modifier(character.constitution);
    character.hitpoints = Hitpoints(10 + static_cast<int>(constitution_modifier));
    
    return character;
}

}  // namespace dnd_character
