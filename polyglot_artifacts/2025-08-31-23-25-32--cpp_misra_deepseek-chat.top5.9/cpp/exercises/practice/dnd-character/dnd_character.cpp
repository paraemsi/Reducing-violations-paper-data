#include "dnd_character.h"
#include <cstdint>
#include <algorithm>
#include <vector>
#include <random>
#include <functional>

namespace dnd_character {

namespace {

std::int16_t generate_ability() {
    // Roll 4 dice
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<std::int16_t> dis(1, 6);
    
    std::vector<std::int16_t> rolls;
    for (int i = 0; i < 4; ++i) {
        rolls.push_back(dis(gen));
    }
    
    // Sort to easily discard the lowest
    std::sort(rolls.begin(), rolls.end(), std::greater<std::int16_t>());
    
    // Sum the top three
    std::int16_t sum = 0;
    for (int i = 0; i < 3; ++i) {
        sum += rolls[i];
    }
    return sum;
}

} // namespace

std::int16_t modifier(std::int16_t score) {
    std::int16_t diff = (score - 10);
    if (diff < 0) {
        // For negative differences, we need to always floor
        // Adjust for odd negative numbers
        if ((diff % 2) != 0) {
            return ((diff - 1) / 2);
        } else {
            return (diff / 2);
        }
    } else {
        return (diff / 2);
    }
}

std::int16_t ability() {
    return generate_ability();
}

Character generate() {
    Character character;
    character.strength = ability();
    character.dexterity = ability();
    character.constitution = ability();
    character.intelligence = ability();
    character.wisdom = ability();
    character.charisma = ability();
    
    // Calculate hitpoints using the modifier function
    character.hitpoints = 10 + modifier(character.constitution);
    
    return character;
}

}  // namespace dnd_character
