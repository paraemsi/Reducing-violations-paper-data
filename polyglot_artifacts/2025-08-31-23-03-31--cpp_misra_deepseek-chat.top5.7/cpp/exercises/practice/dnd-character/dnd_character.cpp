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
    for (std::int16_t i = 0; i < 4; ++i) {
        rolls.push_back(dis(gen));
    }
    
    // Sort in descending order to easily discard the lowest
    std::sort(rolls.begin(), rolls.end(), std::greater<std::int16_t>());
    
    // Sum the largest three
    std::int16_t sum = 0;
    for (std::int16_t i = 0; i < 3; ++i) {
        sum = static_cast<std::int16_t>(sum + rolls[i]);
    }
    return sum;
}

} // namespace

std::int16_t modifier(std::int16_t score) {
    // Calculate the difference first
    std::int16_t diff = static_cast<std::int16_t>(score - 10);
    // Calculate modifier with floor division
    std::int16_t modifier_value = static_cast<std::int16_t>(diff / 2);
    // Ensure proper floor division for negative numbers
    if ((diff < 0) && ((diff % 2) != 0)) {
        modifier_value = static_cast<std::int16_t>(modifier_value - 1);
    }
    return modifier_value;
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
    
    // Calculate hitpoints
    std::int16_t constitution_mod = modifier(character.constitution);
    character.hitpoints = static_cast<std::int16_t>(10 + constitution_mod);
    
    return character;
}

}  // namespace dnd_character
