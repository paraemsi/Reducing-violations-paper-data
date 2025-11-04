#include "dnd_character.h"

namespace dnd_character
{

namespace
{
    //  Random number infrastructure – one engine & distribution reused
    std::random_device                               rd;
    std::mt19937                                     gen(rd());
    std::uniform_int_distribution<score_t>           dist(static_cast<score_t>(1), static_cast<score_t>(6));

    //  Roll a single six-sided die
    score_t roll_die()
    {
        return dist(gen);
    }
} // unnamed namespace

Character::Character() :
    strength(ability()),
    dexterity(ability()),
    constitution(ability()),
    intelligence(ability()),
    wisdom(ability()),
    charisma(ability()),
    hitpoints(static_cast<score_t>(10) + modifier(constitution))
{
}

score_t Character::ability()
{
    std::array<score_t, 4U> rolls{ roll_die(), roll_die(), roll_die(), roll_die() };

    std::sort(rolls.begin(), rolls.end());                    // ascending
    const score_t sum = (rolls[1] + rolls[2]) + rolls[3];     // highest three
    return sum;
}

score_t Character::modifier(score_t score)
{
    //  An equivalent, but simpler, formulation of
    //  floor((score - 10) / 2) that avoids implementation-defined
    //  behaviour for negative signed division.
    return ((score / static_cast<score_t>(2)) - static_cast<score_t>(5));
}

//  Free-standing helpers expected by the unit-tests
score_t ability()
{
    return Character::ability();
}

score_t modifier(score_t score)
{
    return Character::modifier(score);
}

} // namespace dnd_character
