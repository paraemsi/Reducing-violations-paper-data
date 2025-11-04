#include "dnd_character.h"
#include <cstddef>

namespace {

// Type alias pulled in to keep the anonymous namespace self-contained.
using score_t = dnd_character::score_t;

// Roll a single six-sided die.
score_t roll_die(std::mt19937 & engine)
{
    std::uniform_int_distribution<score_t> dist(static_cast<score_t>(1), static_cast<score_t>(6));
    return dist(engine);
}

}  // unnamed namespace

namespace dnd_character {

score_t ability()
{
    static thread_local std::mt19937 engine{std::random_device{}()};

    std::array<score_t, 4U> rolls{};
    for (std::size_t i{0U}; i < rolls.size(); ++i)
    {
        rolls[i] = ::roll_die(engine);
    }

    // Sort ascending so the first element is the smallest.
    std::sort(rolls.begin(), rolls.end());

    // Discard the smallest roll and sum the remaining three.
    score_t total{(rolls[1] + rolls[2]) + rolls[3]};

    return total;
}

score_t modifier(score_t score)
{
    score_t diff{score - static_cast<score_t>(10)};
    if (diff >= static_cast<score_t>(0))
    {
        return diff / static_cast<score_t>(2);
    }
    /* For negative values ensure mathematical floor division. */
    return (diff - static_cast<score_t>(1)) / static_cast<score_t>(2);
}

Character::Character()
{
    strength     = roll_ability();
    dexterity    = roll_ability();
    constitution = roll_ability();
    intelligence = roll_ability();
    wisdom       = roll_ability();
    charisma     = roll_ability();

    hitpoints = static_cast<score_t>(10) + modifier(constitution);
}


score_t Character::roll_ability()
{
    return ability();
}


}  // namespace dnd_character
