#include "dnd_character.h"
#include <random>
#include <algorithm>
#include <numeric>
#include <vector>
#include <cmath>

namespace dnd_character {

namespace {
    int roll_die(std::mt19937& rng) {
        std::uniform_int_distribution<int> dist(1, 6);
        return dist(rng);
    }

    int roll_ability(std::mt19937& rng) {
        std::vector<int> rolls;
        for (int i = 0; i < 4; ++i) {
            rolls.push_back(roll_die(rng));
        }
        std::sort(rolls.begin(), rolls.end(), std::greater<int>());
        return rolls[0] + rolls[1] + rolls[2];
    }
}

Character::Character() {
    std::random_device rd;
    std::mt19937 rng(rd());
    for (int i = 0; i < 6; ++i) {
        abilities_[i] = roll_ability(rng);
    }
    hitpoints_ = 10 + modifier(abilities_[2]);
}

int Character::ability() {
    std::random_device rd;
    std::mt19937 rng(rd());
    return roll_ability(rng);
}

int Character::modifier(int ability_score) {
    return (ability_score - 10) / 2;
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

}  // namespace dnd_character
