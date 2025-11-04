#include "dnd_character.h"

#include <algorithm>
#include <numeric>
#include <random>

namespace dnd_character {

namespace {

/* Helper: roll four six-sided dice, drop the lowest, sum the rest. */
ability_t roll_ability()
{
    static std::random_device rd{};
    static std::mt19937 gen{rd()};
    static std::uniform_int_distribution<ability_t> dist{
        static_cast<ability_t>(1),
        static_cast<ability_t>(6)};

    std::array<ability_t, 4U> rolls{};

    for (ability_t &die : rolls) {
        die = dist(gen);
    }

    std::sort(rolls.begin(), rolls.end());

    /* Sum the highest three dice (skip the first – lowest – element). */
    return static_cast<ability_t>(
        std::accumulate(rolls.begin() + 1U,
                        rolls.end(),
                        static_cast<ability_t>(0)));
}

}  // unnamed namespace

ability_t ability()
{
    return roll_ability();
}

ability_t modifier(ability_t score)
{
    const ability_t diff = (score - static_cast<ability_t>(10));

    if (diff >= static_cast<ability_t>(0)) {
        return (diff / static_cast<ability_t>(2));
    } else {
        return -(((static_cast<ability_t>(-diff) + static_cast<ability_t>(1)) /
                  static_cast<ability_t>(2)));
    }
}

Character::Character()
    : strength{roll_ability()},
      dexterity{roll_ability()},
      constitution{roll_ability()},
      intelligence{roll_ability()},
      wisdom{roll_ability()},
      charisma{roll_ability()},
      hitpoints{static_cast<ability_t>(10) + modifier(constitution)}
{
}


}  // namespace dnd_character

