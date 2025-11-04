#include "dnd_character.h"
#include <random>
#include <algorithm>
#include <numeric>
#include <vector>
#include <functional>
#include <cmath>

namespace dnd_character {

namespace {
    int roll_die(std::mt19937& rng) {
        std::uniform_int_distribution<int> dist(1, 6);
        return dist(rng);
    }
}

// Generate a single ability score by rolling 4d6, dropping the lowest, summing the rest
int ability() {
    static std::random_device rd;
    static std::mt19937 rng(rd());

    std::vector<int> rolls(4);
    for (int& roll : rolls) {
        roll = roll_die(rng);
    }
    std::sort(rolls.begin(), rolls.end());
    // sum the highest 3
    return std::accumulate(rolls.begin() + 1, rolls.end(), 0);
}

Character::Character() {
    // Generate all six abilities
    for (int& ab : abilities_) {
        ab = ability();
    }
    hitpoints_ = 10 + modifier(abilities_[2]); // constitution is the 3rd ability
}

int Character::ability() const {
    // Return the first ability (for compatibility)
    return abilities_[0];
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

int Character::modifier(int ability_score) {
    return (ability_score - 10) / 2;
}

int modifier(int ability_score) {
    return (ability_score - 10) / 2;
}

}  // namespace dnd_character
