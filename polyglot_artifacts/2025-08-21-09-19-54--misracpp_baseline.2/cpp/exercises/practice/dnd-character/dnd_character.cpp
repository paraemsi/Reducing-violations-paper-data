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

int ability() {
    static std::random_device rd;
    static std::mt19937 rng(rd());
    return roll_ability(rng);
}

int modifier(int ability_score) {
    return (ability_score - 10) / 2;
}

Character::Character() {
    static std::random_device rd;
    static std::mt19937 rng(rd());
    for (int i = 0; i < 6; ++i) {
        abilities_[i] = roll_ability(rng);
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

int Character::modifier(int ability_score) const {
    return (ability_score - 10) / 2;
}

// Define static member indices
const int Character::strength_idx = 0;
const int Character::dexterity_idx = 1;
const int Character::constitution_idx = 2;
const int Character::intelligence_idx = 3;
const int Character::wisdom_idx = 4;
const int Character::charisma_idx = 5;

// Define member variable-like references
const int& Character::strength = reinterpret_cast<const int&>(
    reinterpret_cast<const char&>(reinterpret_cast<const Character*>(0)->abilities_[strength_idx])
);
const int& Character::dexterity = reinterpret_cast<const int&>(
    reinterpret_cast<const char&>(reinterpret_cast<const Character*>(0)->abilities_[dexterity_idx])
);
const int& Character::constitution = reinterpret_cast<const int&>(
    reinterpret_cast<const char&>(reinterpret_cast<const Character*>(0)->abilities_[constitution_idx])
);
const int& Character::intelligence = reinterpret_cast<const int&>(
    reinterpret_cast<const char&>(reinterpret_cast<const Character*>(0)->abilities_[intelligence_idx])
);
const int& Character::wisdom = reinterpret_cast<const int&>(
    reinterpret_cast<const char&>(reinterpret_cast<const Character*>(0)->abilities_[wisdom_idx])
);
const int& Character::charisma = reinterpret_cast<const int&>(
    reinterpret_cast<const char&>(reinterpret_cast<const Character*>(0)->abilities_[charisma_idx])
);
const int& Character::hitpoints = reinterpret_cast<const int&>(
    reinterpret_cast<const char&>(reinterpret_cast<const Character*>(0)->hitpoints_)
);

}  // namespace dnd_character
