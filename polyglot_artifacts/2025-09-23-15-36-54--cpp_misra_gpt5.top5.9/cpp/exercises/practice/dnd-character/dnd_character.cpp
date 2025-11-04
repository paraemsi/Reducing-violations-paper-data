#include "dnd_character.h"

#include <random>
#include <cstdint>

namespace dnd_character {

namespace {
// Pseudo-random number generator, seeded once.
auto rng() -> std::mt19937& {
    static std::random_device rd;
    static std::mt19937 gen{ static_cast<std::mt19937::result_type>(rd()) };
    return gen;
}

auto roll_d6() -> score_t {
    static std::uniform_int_distribution<score_t> dist(static_cast<score_t>(1), static_cast<score_t>(6));
    return dist(rng());
}
}  // unnamed namespace

auto ability() -> score_t {
    score_t sum = static_cast<score_t>(0);
    score_t min_roll = static_cast<score_t>(6);

    for (std::uint32_t i = 0U; i < 4U; ++i) {
        const score_t r = roll_d6();
        sum = static_cast<score_t>(sum + r);
        if (r < min_roll) {
            min_roll = r;
        }
    }

    return static_cast<score_t>(sum - min_roll);
}

auto modifier(score_t score) noexcept -> score_t {
    const score_t a = static_cast<score_t>(score - static_cast<score_t>(10));
    score_t q = static_cast<score_t>(a / static_cast<score_t>(2));

    if ((a < static_cast<score_t>(0)) && ((a % static_cast<score_t>(2)) != static_cast<score_t>(0))) {
        q = static_cast<score_t>(q - static_cast<score_t>(1));
    }

    return q;
}

Character::Character()
    : strength{ ability() }
    , dexterity{ ability() }
    , constitution{ ability() }
    , intelligence{ ability() }
    , wisdom{ ability() }
    , charisma{ ability() }
    , hitpoints{ static_cast<score_t>(static_cast<score_t>(10) + modifier(constitution)) } {}








}  // namespace dnd_character
