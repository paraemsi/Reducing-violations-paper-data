#include "dnd_character.h"
#include <random>
#include <algorithm>
#include <numeric>
#include <vector>
#include <cmath>

namespace dnd_character {

namespace {
    // Helper function to roll 4d6 and sum the highest 3
    int roll_ability() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<> dis(1, 6);

        std::vector<int> rolls(4);
        for (int& roll : rolls) {
            roll = dis(gen);
        }
        std::sort(rolls.begin(), rolls.end(), std::greater<int>());
        return rolls[0] + rolls[1] + rolls[2];
    }
}

int ability() {
    return roll_ability();
}

int Character::ability() {
    return roll_ability();
}

Character::Character() {
    for (int i = 0; i < 6; ++i) {
        abilities_[i] = roll_ability();
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
    return dnd_character::modifier(ability_score);
}

int modifier(int ability_score) {
    return static_cast<int>(std::floor((ability_score - 10) / 2.0));
}

}  // namespace dnd_character
