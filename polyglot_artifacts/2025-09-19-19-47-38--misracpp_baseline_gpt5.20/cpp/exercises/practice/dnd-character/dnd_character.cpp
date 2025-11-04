#include "dnd_character.h"

#include <algorithm>
#include <cmath>
#include <random>

namespace {
// Random number generator setup for rolling a 6-sided die.
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<int> d6(1, 6);

inline int roll_die() {
    return d6(gen);
}
}  // namespace

namespace dnd_character {

int ability() {
    int d1 = roll_die();
    int d2 = roll_die();
    int d3 = roll_die();
    int d4 = roll_die();

    int sum = d1 + d2 + d3 + d4;
    int lowest = std::min(std::min(d1, d2), std::min(d3, d4));
    return sum - lowest;
}

int modifier(int score) {
    // Floor((score - 10) / 2.0) to handle negatives correctly.
    return static_cast<int>(std::floor((score - 10) / 2.0));
}


}  // namespace dnd_character
