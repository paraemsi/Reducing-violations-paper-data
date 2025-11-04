#include "dnd_character.h"

#include <cmath>
#include <random>

namespace dnd_character {

int ability() {
    static thread_local std::mt19937 rng{std::random_device{}()};
    static thread_local std::uniform_int_distribution<int> dist(1, 6);

    int sum = 0;
    int min_roll = 7;
    for (int i = 0; i < 4; ++i) {
        int r = dist(rng);
        sum += r;
        if (r < min_roll) {
            min_roll = r;
        }
    }
    return sum - min_roll;
}

int modifier(int score) {
    return static_cast<int>(std::floor((score - 10) / 2.0));
}


}  // namespace dnd_character
