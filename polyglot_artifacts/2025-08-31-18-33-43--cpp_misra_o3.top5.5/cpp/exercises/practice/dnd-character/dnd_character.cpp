#include "dnd_character.h"

#include <algorithm>
#include <array>
#include <random>

namespace dnd_character {
namespace {

// roll a single die with the requested number of sides
score_t roll_die(const std::uint32_t sides)
{
    static std::random_device random_source;
    static std::mt19937 engine(random_source());
    std::uniform_int_distribution<score_t> dist(
        static_cast<score_t>(1), static_cast<score_t>(sides));
    return dist(engine);
}

} // unnamed namespace

// ---------- Character static helpers ----------------------------------------------------------

score_t Character::ability()
{
    std::array<score_t, 4U> rolls{};
    for (auto & value : rolls)
    {
        value = roll_die(6U);
    }

    std::sort(rolls.begin(), rolls.end());

    // drop the lowest roll (rolls[0]) and sum the remaining three
    const score_t score = (rolls[1] + rolls[2]) + rolls[3];
    return score;
}

score_t Character::modifier(const score_t ability_score)
{
    const score_t delta = ability_score - static_cast<score_t>(10);

    if (delta >= static_cast<score_t>(0))
    {
        return delta / static_cast<score_t>(2);
    }
    else
    {
        // ensure rounding toward -∞ for negative values
        return (delta - static_cast<score_t>(1)) / static_cast<score_t>(2);
    }
}

// ---------- construction ----------------------------------------------------------------------

Character::Character()
{
    strength     = ability();
    dexterity    = ability();
    constitution = ability();
    intelligence = ability();
    wisdom       = ability();
    charisma     = ability();
    hitpoints    = static_cast<score_t>(10) + modifier(constitution);
}

// ---------- accessors -------------------------------------------------------------------------



// ---------- free helper -----------------------------------------------------------------------

score_t ability()
{
    return Character::ability();
}

score_t modifier(const score_t ability_score)
{
    return Character::modifier(ability_score);
}

}  // namespace dnd_character
