#include "dnd_character.h"

namespace dnd_character {

// ---------------------------------------------------------------------------
//  Internal helpers
// ---------------------------------------------------------------------------

namespace {
/**
 * Thread-local RNG so that each thread gets an independent generator.
 * Using Mersenne Twister for good statistical properties.
 */
inline auto rng_engine() -> std::mt19937& {
    thread_local std::random_device rd{};
    thread_local std::mt19937 engine{ rd() };
    return engine;
}

/**
 * Distribution for a single 6-sided die roll (1-6 inclusive).
 */
inline auto d6() -> std::uniform_int_distribution<score_t>& {
    thread_local std::uniform_int_distribution<score_t> dist{ static_cast<score_t>(1),
                                                              static_cast<score_t>(6) };
    return dist;
}
}  // namespace

// ---------------------------------------------------------------------------
//  Public free functions
// ---------------------------------------------------------------------------

auto ability() -> score_t {
    std::array<score_t, 4U> rolls{};

    for (score_t& value : rolls) {
        value = d6()(rng_engine());
    }

    std::sort(rolls.begin(),
              rolls.end(),
              [](score_t a, score_t b) noexcept { return (a > b); });

    return (rolls[0] + (rolls[1] + rolls[2]));
}

auto modifier(score_t score) -> score_t {
    if (score >= static_cast<score_t>(10)) {
        return (score - static_cast<score_t>(10)) / static_cast<score_t>(2);
    } else {
        return (score - static_cast<score_t>(11)) / static_cast<score_t>(2);
    }
}

// ---------------------------------------------------------------------------
//  Character implementation
// ---------------------------------------------------------------------------

Character::Character() {
    strength     = ability();
    dexterity    = ability();
    constitution = ability();
    intelligence = ability();
    wisdom       = ability();
    charisma     = ability();

    hitpoints = static_cast<score_t>(10) + modifier(constitution);
}


}  // namespace dnd_character
