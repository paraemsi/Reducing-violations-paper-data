#include "dnd_character.h"
#include <random>
#include <algorithm>
#include <numeric>
#include <vector>
#include <functional>
#include <cmath>

namespace dnd_character {

namespace {
    int roll_4d6_drop_lowest(std::mt19937 &rng) {
        std::uniform_int_distribution<int> dist(1, 6);
        std::vector<int> rolls(4);
        for (int &roll : rolls) {
            roll = dist(rng);
        }
        std::sort(rolls.begin(), rolls.end());
        // Drop the lowest (first) roll
        return rolls[1] + rolls[2] + rolls[3];
    }
}

Character::Character() {
    std::random_device rd;
    std::mt19937 rng(rd());
    for (int i = 0; i < 6; ++i) {
        abilities_[i] = roll_4d6_drop_lowest(rng);
    }
    hitpoints_ = 10 + modifier(abilities_[2]);
}


int Character::strength() const {
    return abilities_[0];
}

int Character::dexterity() const {
    return abilities_[1];
}

int Character::constitution() const {
    return abilities_[2];
}

int Character::intelligence() const {
    return abilities_[3];
}

int Character::wisdom() const {
    return abilities_[4];
}

int Character::charisma() const {
    return abilities_[5];
}

int Character::hitpoints() const {
    return hitpoints_;
}

int modifier(int score) {
    return (score - 10) / 2;
}

}  // namespace dnd_character
