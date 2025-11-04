#include "dnd_character.h"

#include <algorithm>
#include <array>
#include <random>

namespace dnd_character {

namespace {
    // Thread-local PRNG
    auto rng() -> std::mt19937& {
        static thread_local std::mt19937 gen(static_cast<std::mt19937::result_type>(std::random_device{}()));
        return gen;
    }
}  // namespace

auto ability() -> score_t {
    std::array<score_t, 4U> rolls{};

    // Distribution for a 6-sided die
    static thread_local std::uniform_int_distribution<score_t> dist(
        static_cast<score_t>(1), static_cast<score_t>(6));

    for (score_t& r : rolls) {
        r = dist(rng());
    }

    std::sort(rolls.begin(), rolls.end());
    const score_t sum_top_three = ((rolls[1] + rolls[2]) + rolls[3]);
    return sum_top_three;
}

auto modifier(score_t score) -> score_t {
    const score_t diff = (score - static_cast<score_t>(10));
    const bool is_negative = (diff < static_cast<score_t>(0));
    const bool is_odd = ((diff % static_cast<score_t>(2)) != static_cast<score_t>(0));

    if ((!is_negative) || (!is_odd)) {
        return (diff / static_cast<score_t>(2));
    } else {
        return ((diff / static_cast<score_t>(2)) - static_cast<score_t>(1));
    }
}

Character::Character()
    : strength(ability())
    , dexterity(ability())
    , constitution(ability())
    , intelligence(ability())
    , wisdom(ability())
    , charisma(ability())
    , hitpoints(static_cast<hp_t>(0)) {
    hitpoints = static_cast<hp_t>((static_cast<score_t>(10) + modifier(constitution)));
}

}  // namespace dnd_character
