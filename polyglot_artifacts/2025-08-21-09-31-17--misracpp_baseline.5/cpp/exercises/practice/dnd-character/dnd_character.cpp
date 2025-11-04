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

    int roll_ability(std::mt19937& rng) {
        std::vector<int> rolls(4);
        for (int& roll : rolls) {
            roll = roll_die(rng);
        }
        std::sort(rolls.begin(), rolls.end());
        // sum the largest three
        return rolls[1] + rolls[2] + rolls[3];
    }
}

int ability() {
    static thread_local std::random_device rd;
    static thread_local std::mt19937 rng(rd());
    return roll_ability(rng);
}

int modifier(int ability_score) {
    return (ability_score - 10) / 2;
}

Character::Character() {
    static thread_local std::random_device rd;
    static thread_local std::mt19937 rng(rd());
    strength = roll_ability(rng);
    dexterity = roll_ability(rng);
    constitution = roll_ability(rng);
    intelligence = roll_ability(rng);
    wisdom = roll_ability(rng);
    charisma = roll_ability(rng);
    hitpoints = 10 + modifier(constitution);
}

int Character::modifier(int ability_score) const {
    return (ability_score - 10) / 2;
}

}  // namespace dnd_character
