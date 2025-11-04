#include "dnd_character.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <random>

namespace {

// Roll one six-sided die.
int roll_die() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<int> dist(1, 6);
    return dist(gen);
}

// Roll 4d6 and drop the lowest die.
int roll_4d6_drop_lowest() {
    std::array<int, 4> rolls{roll_die(), roll_die(), roll_die(), roll_die()};
    std::sort(rolls.begin(), rolls.end(), std::greater<int>());
    return rolls[0] + rolls[1] + rolls[2];
}

}  // namespace

namespace dnd_character {

int ability() {
    return roll_4d6_drop_lowest();
}

int modifier(int score) {
    return static_cast<int>(std::floor((score - 10) / 2.0));
}

Character::Character()
    : strength(ability())
    , dexterity(ability())
    , constitution(ability())
    , intelligence(ability())
    , wisdom(ability())
    , charisma(ability()) {
    hitpoints = 10 + modifier(constitution);
}


}  // namespace dnd_character
