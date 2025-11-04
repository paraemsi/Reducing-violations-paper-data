#include "dnd_character.h"
#include <algorithm>
#include <numeric>
#include <vector>
#include <random>
#include <functional>
#include <cmath>

namespace dnd_character {

namespace {
    // Helper function to get a random number generator
    std::mt19937& rng() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        return gen;
    }
}

Character::Character() {
    // Generate six ability scores
    for (int i = 0; i < 6; ++i) {
        abilities_[i] = ability();
    }
    hitpoints_ = 10 + modifier(abilities_[2]); // constitution is index 2
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

int Character::ability() const {
    return ability();
}

int Character::ability() {
    std::uniform_int_distribution<int> dist(1, 6);
    std::vector<int> rolls(4);
    for (int& roll : rolls) {
        roll = dist(rng());
    }
    std::sort(rolls.begin(), rolls.end());
    // Drop the lowest roll
    return std::accumulate(rolls.begin() + 1, rolls.end(), 0);
}

int Character::modifier(int score) {
    return static_cast<int>(std::floor((score - 10) / 2.0));
}

// Provide a free function for dnd_character::modifier
int modifier(int score) {
    return Character::modifier(score);
}

// Provide a free function for dnd_character::ability
int ability() {
    return Character::ability();
}

}  // namespace dnd_character
