#include "dnd_character.h"

#include <random>

namespace dnd_character {

namespace {
    // Roll a single 6-sided die.
    score_t roll_d6() {
        static std::random_device rd;
        static std::uniform_int_distribution<score_t> dist(static_cast<score_t>(1), static_cast<score_t>(6));
        return dist(rd);
    }
}

score_t ability() {
    const score_t zero = static_cast<score_t>(0);
    score_t total = zero;
    score_t min_roll = static_cast<score_t>(6);

    for (std::uint32_t i = 0U; i < 4U; ++i) {
        const score_t roll = roll_d6();
        total = (total + roll);
        if (roll < min_roll) {
            min_roll = roll;
        }
    }

    return (total - min_roll);
}

score_t modifier(score_t score) {
    const score_t ten = static_cast<score_t>(10);
    const score_t two = static_cast<score_t>(2);
    const score_t zero = static_cast<score_t>(0);

    const score_t delta = (score - ten);
    if (delta >= zero) {
        return (delta / two);
    } else {
        const score_t pos = (ten - score);
        return -(((pos + static_cast<score_t>(1)) / two));
    }
}

Character::Character()
    : strength(ability()),
      dexterity(ability()),
      constitution(ability()),
      intelligence(ability()),
      wisdom(ability()),
      charisma(ability()),
      hitpoints(static_cast<score_t>(10)) {
    hitpoints = (hitpoints + modifier(constitution));
}

}  // namespace dnd_character
