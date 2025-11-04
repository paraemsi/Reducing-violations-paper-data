#include "dnd_character.h"

#include <random>
#include <algorithm>

namespace dnd_character {

int modifier(int score) {
    return (score - 10) / 2;
}

int ability() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 6);
    std::vector<int> rolls;
    for (int i = 0; i < 4; ++i) {
        rolls.push_back(dis(gen));
    }
    std::sort(rolls.begin(), rolls.end());
    return rolls[1] + rolls[2] + rolls[3];  // Discard the lowest, sum the top three
}

Character::Character() {
    strength = ability();
    dexterity = ability();
    constitution = ability();
    intelligence = ability();
    wisdom = ability();
    charisma = ability();
    hitpoints = 10 + modifier(constitution);
}

}  // namespace dnd_character
