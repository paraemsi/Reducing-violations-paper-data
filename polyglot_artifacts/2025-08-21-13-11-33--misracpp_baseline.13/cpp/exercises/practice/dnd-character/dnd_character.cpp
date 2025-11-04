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

    int ability_score(std::mt19937& rng) {
        std::vector<int> rolls(4);
        for (int& roll : rolls) {
            roll = roll_die(rng);
        }
        std::sort(rolls.begin(), rolls.end(), std::greater<int>());
        return rolls[0] + rolls[1] + rolls[2];
    }
}

Character::Character() {
    std::random_device rd;
    std::mt19937 rng(rd());
    for (int& ability : abilities_) {
        ability = ability_score(rng);
    }
    hitpoints_ = 10 + dnd_character::modifier(constitution());
}

int Character::ability() {
    // Generate a random ability score (for testing, not used in construction)
    std::random_device rd;
    std::mt19937 rng(rd());
    return ability_score(rng);
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

}  // namespace

int modifier(int score) {
    return static_cast<int>(std::floor((score - 10) / 2.0));
}

}  // namespace dnd_character
