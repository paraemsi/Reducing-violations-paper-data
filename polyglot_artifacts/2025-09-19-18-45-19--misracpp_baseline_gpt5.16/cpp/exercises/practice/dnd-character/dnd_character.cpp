#include "dnd_character.h"

#include <algorithm>
#include <array>
#include <numeric>
#include <random>

namespace {
    // Single PRNG for the module
    std::mt19937& rng() {
        static std::mt19937 engine(std::random_device{}());
        return engine;
    }

    std::uniform_int_distribution<int>& d6() {
        static std::uniform_int_distribution<int> dist(1, 6);
        return dist;
    }

    int roll_d6() {
        return d6()(rng());
    }
}

namespace dnd_character {

int ability() {
    std::array<int, 4> rolls{ roll_d6(), roll_d6(), roll_d6(), roll_d6() };
    int total = std::accumulate(rolls.begin(), rolls.end(), 0);
    int min_roll = *std::min_element(rolls.begin(), rolls.end());
    return total - min_roll;
}

int modifier(int score) {
    // Compute floor((score - 10) / 2) using integer arithmetic
    // Note: integer division in C++ truncates toward zero, so adjust negatives.
    int x = score - 10;
    return x >= 0 ? x / 2 : (x - 1) / 2;
}

Character::Character() {
    strength = ability();
    dexterity = ability();
    constitution = ability();
    intelligence = ability();
    wisdom = ability();
    charisma = ability();
    hitpoints = 10 + modifier(constitution);
}

}  // namespace dnd_character
