#include "dnd_character.h"

#include <algorithm>
#include <array>
#include <cstddef>
#include <random>

namespace dnd_character {

namespace {
    // PRNG accessor with static storage duration
    auto prng() -> std::mt19937& {
        static std::mt19937 gen{ std::random_device{}() };
        return gen;
    }
}  // namespace

auto ability() -> score_t {
    std::uniform_int_distribution<score_t> dist(static_cast<score_t>(1), static_cast<score_t>(6));

    std::array<score_t, 4U> rolls{};
    for (std::size_t i = 0U; i < static_cast<std::size_t>(4); ++i) {
        rolls[i] = static_cast<score_t>(dist(prng()));
    }

    std::sort(rolls.begin(), rolls.end());

    score_t sum = static_cast<score_t>(0);
    for (std::size_t i = static_cast<std::size_t>(1); i < static_cast<std::size_t>(4); ++i) {
        sum = (sum + rolls[i]);
    }

    return sum;
}

auto modifier(score_t score) -> score_t {
    const score_t ten = static_cast<score_t>(10);
    const score_t two = static_cast<score_t>(2);
    const score_t zero = static_cast<score_t>(0);

    const score_t delta = static_cast<score_t>(score - ten);
    score_t mod = static_cast<score_t>(delta / two);

    if ((delta < zero) && ((delta % two) != zero)) {
        mod = static_cast<score_t>(mod - static_cast<score_t>(1));
    }

    return mod;
}

Character::Character() {
    strength = ability();
    dexterity = ability();
    constitution = ability();
    intelligence = ability();
    wisdom = ability();
    charisma = ability();

    hitpoints = (static_cast<score_t>(10) + modifier(constitution));
}

}  // namespace dnd_character
