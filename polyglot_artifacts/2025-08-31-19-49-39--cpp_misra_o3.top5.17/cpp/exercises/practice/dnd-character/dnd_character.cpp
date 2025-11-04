#include "dnd_character.h"

#include <algorithm>
#include <array>
#include <random>

namespace dnd_character {

namespace {

// PRNG objects are kept in an anonymous namespace so that each
// translation unit has one shared instance.
std::random_device rd;
std::mt19937 rng(rd());
std::uniform_int_distribution<ability_score_t> dist(
    static_cast<ability_score_t>(1),
    static_cast<ability_score_t>(6));

// Roll a single die (1 – 6).
static ability_score_t roll_die()
{
    return dist(rng);
}

// Roll four dice and return the sum of the largest three.
static ability_score_t roll_ability()
{
    std::array<ability_score_t, 4U> dice{
        roll_die(), roll_die(), roll_die(), roll_die()
    };

    std::sort(dice.begin(), dice.end());
    // Dice are now ascending; skip index 0 (the smallest).
    return static_cast<ability_score_t>(
        dice[1] + dice[2] + dice[3]);
}

}  // namespace

ability_score_t ability()
{
    return roll_ability();
}

// Calculate ability-score modifier according to D&D rules.
ability_score_t modifier(ability_score_t score)
{
    const ability_score_t diff{
        (score - static_cast<ability_score_t>(10))
    };

    return (diff >= static_cast<ability_score_t>(0))
               ? (diff / static_cast<ability_score_t>(2))
               : ((diff - static_cast<ability_score_t>(1)) / static_cast<ability_score_t>(2));
}

Character::Character()
    : strength(roll_ability()),
      dexterity(roll_ability()),
      constitution(roll_ability()),
      intelligence(roll_ability()),
      wisdom(roll_ability()),
      charisma(roll_ability()),
      hitpoints(static_cast<ability_score_t>(10) + modifier(constitution))
{
}


}  // namespace dnd_character
