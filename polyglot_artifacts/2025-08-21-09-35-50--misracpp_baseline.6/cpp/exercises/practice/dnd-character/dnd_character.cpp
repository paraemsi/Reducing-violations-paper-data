#include "dnd_character.h"
#include <random>
#include <algorithm>
#include <numeric>
#include <vector>
#include <functional>
#include <cmath>

namespace dnd_character {

namespace {
    int roll_4d6_drop_lowest() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<> dis(1, 6);

        std::vector<int> rolls(4);
        for (int& roll : rolls) {
            roll = dis(gen);
        }
        std::sort(rolls.begin(), rolls.end());
        // Drop the lowest (first) roll
        return std::accumulate(rolls.begin() + 1, rolls.end(), 0);
    }
}

Character::Character() {
    for (int i = 0; i < 6; ++i) {
        abilities_[i] = roll_4d6_drop_lowest();
    }
    hitpoints_ = 10 + ability_modifier(abilities_[2]);
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

int modifier(int ability_score) {
    return static_cast<int>(std::floor((ability_score - 10) / 2.0));
}

int ability() {
    return roll_4d6_drop_lowest();
}

}  // namespace dnd_character
