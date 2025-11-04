#include "dnd_character.h"
#include <random>
#include <algorithm>
#include <numeric>
#include <vector>
#include <functional>
#include <cmath>

namespace dnd_character {

namespace {
    // Helper function to roll a single ability score (sum of highest 3 of 4d6)
    int roll_ability(std::mt19937 &rng) {
        std::uniform_int_distribution<int> dist(1, 6);
        std::vector<int> rolls(4);
        for (int &roll : rolls) {
            roll = dist(rng);
        }
        std::sort(rolls.begin(), rolls.end(), std::greater<int>());
        return rolls[0] + rolls[1] + rolls[2];
    }
}

// Standalone function to roll a random ability score
int ability() {
    static std::random_device rd;
    static std::mt19937 rng(rd());
    return roll_ability(rng);
}

// Standalone function to calculate modifier
int modifier(int ability_score) {
    return (ability_score - 10) / 2;
}

// Character class implementation

Character::Character() {
    static std::random_device rd;
    static std::mt19937 rng(rd());
    for (int &score : abilities_) {
        score = roll_ability(rng);
    }
    hitpoints_ = 10 + modifier(abilities_[2]); // Constitution is the third ability
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

int Character::modifier(int ability_score) const {
    return (ability_score - 10) / 2;
}

}  // namespace dnd_character
