#include "dnd_character.h"

#include <random>

namespace dnd_character {

namespace {
    // Roll a single six-sided die.
    inline score_t roll_die_6()
    {
        // Thread-safe PRNG initialization
        static thread_local std::mt19937 engine([]() {
            std::random_device rd;
            return std::mt19937(static_cast<std::mt19937::result_type>(rd()));
        }());
        static thread_local std::uniform_int_distribution<score_t> dist(static_cast<score_t>(1), static_cast<score_t>(6));
        return dist(engine);
    }
}  // namespace

score_t ability()
{
    constexpr score_t dice_to_roll = static_cast<score_t>(4);
    score_t total = static_cast<score_t>(0);
    score_t smallest = static_cast<score_t>(7);

    for (score_t i = static_cast<score_t>(0); (i < dice_to_roll); ++i) {
        const score_t roll = roll_die_6();
        total = (total + roll);
        if ((roll < smallest)) {
            smallest = roll;
        }
    }

    return (total - smallest);
}

score_t modifier(score_t score)
{
    const score_t delta = (score - static_cast<score_t>(10));
    if ((delta >= static_cast<score_t>(0))) {
        return (delta / static_cast<score_t>(2));
    } else {
        if (((delta % static_cast<score_t>(2)) == static_cast<score_t>(0))) {
            return (delta / static_cast<score_t>(2));
        } else {
            return ((delta - static_cast<score_t>(1)) / static_cast<score_t>(2));
        }
    }
}

Character::Character()
    : strength(ability())
    , dexterity(ability())
    , constitution(ability())
    , intelligence(ability())
    , wisdom(ability())
    , charisma(ability())
    , hitpoints((static_cast<score_t>(10)) + modifier(constitution))
{
}


}  // namespace dnd_character
