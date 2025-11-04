#include "dnd_character.h"
#include <algorithm>
#include <array>
#include <random>

namespace dnd_character {

int modifier(int score) {
    int adjusted = score - 10;
    // Integer division rounds toward zero, which is what we want for negative numbers
    int result = adjusted / 2;
    return result;
}

int ability() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<int> dis(1, 6);
    
    std::array<int, 4> rolls;
    for (int i = 0; i < 4; ++i) {
        rolls[static_cast<std::size_t>(i)] = dis(gen);
    }
    
    std::sort(rolls.begin(), rolls.end());
    
    // Sum the largest three dice (indices 1, 2, 3 after sorting)
    int sum = (rolls[1] + rolls[2]) + rolls[3];
    return sum;
}

Character::Character() {
    strength = ability();
    dexterity = ability();
    constitution = ability();
    intelligence = ability();
    wisdom = ability();
    charisma = ability();
    
    // Calculate hitpoints: 10 + constitution modifier
    int constitution_mod = modifier(constitution);
    hitpoints = 10 + constitution_mod;
}

}  // namespace dnd_character
