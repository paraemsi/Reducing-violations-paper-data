#include "dnd_character.h"
#include <cstdint>
#include <algorithm>
#include <vector>
#include <random>
#include <functional>

namespace dnd_character {

namespace {
    std::int16_t roll_die() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<std::int16_t> dis(1, 6);
        return dis(gen);
    }
}

std::int16_t ability() {
    std::vector<std::int16_t> rolls;
    for (std::int16_t i = 0; i < 4; ++i) {
        rolls.push_back(roll_die());
    }
    // Sort in descending order to easily discard the smallest
    std::sort(rolls.begin(), rolls.end(), std::greater<std::int16_t>());
    return ((rolls[0] + rolls[1]) + rolls[2]);
}

std::int16_t modifier(std::int16_t constitution) {
    std::int16_t value = (constitution - 10);
    if (value >= 0) {
        return (value / 2);
    } else {
        return (((value - 1)) / 2);
    }
}

Character::Character() 
    : strength(ability())
    , dexterity(ability())
    , constitution(ability())
    , intelligence(ability())
    , wisdom(ability())
    , charisma(ability())
    , hitpoints((10 + modifier(constitution))) {
}

}  // namespace dnd_character
