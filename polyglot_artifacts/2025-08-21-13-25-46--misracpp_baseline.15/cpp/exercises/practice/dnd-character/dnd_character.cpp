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
        std::vector<int> rolls(4);
        for (int& roll : rolls) {
            roll = roll_die(rng);
        }
        std::sort(rolls.begin(), rolls.end());
        // Discard the lowest roll
        return std::accumulate(rolls.begin() + 1, rolls.end(), 0);
    }
}

int ability_modifier(int ability_score) {
    return (ability_score - 10) / 2;
}

Character::Character() {
    std::random_device rd;
    std::mt19937 rng(rd());
    for (int& ability : abilities_) {
        ability = roll_ability(rng);
    }
    // Assign to public fields for test compatibility
    strength = abilities_[0];
    dexterity = abilities_[1];
    constitution = abilities_[2];
    intelligence = abilities_[3];
    wisdom = abilities_[4];
    charisma = abilities_[5];
    hitpoints = 10 + ability_modifier(constitution);

    hitpoints_ = hitpoints; // keep private field in sync
}

int Character::ability_strength() const {
    return abilities_[0];
}

int Character::ability_dexterity() const {
    return abilities_[1];
}

int Character::ability_constitution() const {
    return abilities_[2];
}

int Character::ability_intelligence() const {
    return abilities_[3];
}

int Character::ability_wisdom() const {
    return abilities_[4];
}

int Character::ability_charisma() const {
    return abilities_[5];
}

int Character::hitpoints() const {
    return hitpoints_;
}

int Character::ability_modifier(int ability_score) const {
    return dnd_character::ability_modifier(ability_score);
}

}  // namespace dnd_character
