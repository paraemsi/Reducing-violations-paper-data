#include "dnd_character.h"

#include <algorithm>
#include <array>
#include <cstdint>
#include <random>

namespace {

std::mt19937& rng_engine() {
    static std::mt19937 engine{std::random_device{}()};
    return engine;
}

dnd_character::Score roll_d6() {
    static thread_local std::uniform_int_distribution<dnd_character::Score> dist(1, 6);
    return dist(rng_engine());
}

}  // unnamed namespace

namespace dnd_character {

constexpr Score kBaseHP = static_cast<Score>(10);

Score ability() {
    std::array<Score, 4U> rolls{{
        roll_d6(),
        roll_d6(),
        roll_d6(),
        roll_d6()
    }};

    std::sort(rolls.begin(), rolls.end(), [](Score a, Score b) { return (a > b); });

    const Score sum_top_three = ((rolls[0] + rolls[1]) + rolls[2]);
    return sum_top_three;
}

Score modifier(Score score) {
    const Score a = (score - 10);
    Score div = (a / 2);
    const Score rem = (a % 2);

    if ((a < 0) && (rem != 0)) {
        div = (div - 1);
    }

    return div;
}

Character::Character()
    : strength{ability()}
    , dexterity{ability()}
    , constitution{ability()}
    , intelligence{ability()}
    , wisdom{ability()}
    , charisma{ability()}
    , hitpoints{(static_cast<HitPoints>(kBaseHP) + static_cast<HitPoints>(modifier(constitution)))} {
}








}  // namespace dnd_character
