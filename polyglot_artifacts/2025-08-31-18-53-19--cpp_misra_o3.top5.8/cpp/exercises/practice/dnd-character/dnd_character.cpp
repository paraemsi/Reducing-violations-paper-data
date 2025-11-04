#include "dnd_character.h"
#include <algorithm>  /* for std::sort */

namespace dnd_character {

namespace {
/* Lazily-initialised shared RNG – one per translation unit is enough. */
std::mt19937& rng() {
    static std::random_device rd;
    static std::mt19937 engine(rd());
    return engine;
}
}  // anonymous namespace

/* -------- Character static helpers ------------------------------------ */

std::int32_t ability() {
    static std::uniform_int_distribution<std::int32_t> dist(static_cast<std::int32_t>(1),
                                                            static_cast<std::int32_t>(6));

    std::array<std::int32_t, 4U> rolls{};
    for(std::int32_t& r : rolls) {
        r = dist(rng());
    }

    /* sort ascending to drop the first (smallest) element */
    std::sort(rolls.begin(), rolls.end());

    /* sum the three highest dice */
    const std::int32_t total =
        (rolls[1] + rolls[2]) + rolls[3];  /* parentheses emphasise precedence */

    return total;
}

std::int32_t modifier(const std::int32_t score) {
    /* floor((score - 10) / 2) without using floating point */
    if(score >= static_cast<std::int32_t>(10)) {
        return (score - static_cast<std::int32_t>(10)) / static_cast<std::int32_t>(2);
    }
    /* for negative offset subtract one extra before dividing to round down */
    return (score - static_cast<std::int32_t>(11)) / static_cast<std::int32_t>(2);
}

/* -------- Character construction & accessors -------------------------- */

Character::Character() {
    strength      = ability();
    dexterity     = ability();
    constitution  = ability();
    intelligence  = ability();
    wisdom        = ability();
    charisma      = ability();
    hitpoints     = static_cast<std::int32_t>(10) + modifier(constitution);
}


}  // namespace dnd_character
