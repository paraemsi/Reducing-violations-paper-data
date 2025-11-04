#include "dnd_character.h"

#include <algorithm>
#include <cmath>
#include <numeric>
#include <random>
#include <vector>

namespace dnd_character {

int modifier(int constitution) {
    return static_cast<int>(std::floor((constitution - 10) / 2.0));
}

int ability() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> distrib(1, 6);

    std::vector<int> rolls;
    for (int i = 0; i < 4; ++i) {
        rolls.push_back(distrib(gen));
    }
    std::sort(rolls.begin(), rolls.end());
    return std::accumulate(rolls.begin() + 1, rolls.end(), 0);
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
