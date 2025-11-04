#include "dnd_character.h"

#include <algorithm>
#include <array>
#include <random>

namespace {

// Roll a single 6-sided die.
dnd_character::score_t roll_d6()
{
    static thread_local std::mt19937 generator{ std::random_device{}() };
    static thread_local std::uniform_int_distribution<dnd_character::score_t> distribution(static_cast<dnd_character::score_t>(1),
                                                                                           static_cast<dnd_character::score_t>(6));
    return distribution(generator);
}

}  // unnamed namespace

namespace dnd_character {

score_t ability()
{
    const std::array<score_t, 4> rolls{ roll_d6(), roll_d6(), roll_d6(), roll_d6() };

    score_t total = (rolls[0] + rolls[1]);
    total = (total + rolls[2]);
    total = (total + rolls[3]);

    const auto min_it = std::min_element(rolls.begin(), rolls.end());
    const score_t min_val = *min_it;

    return (total - min_val);
}

score_t modifier(score_t score)
{
    const score_t delta = (score - static_cast<score_t>(10));
    if (delta >= static_cast<score_t>(0))
    {
        return (delta / static_cast<score_t>(2));
    }
    else
    {
        const score_t abs_delta = static_cast<score_t>(-delta);
        return static_cast<score_t>(-((abs_delta + static_cast<score_t>(1)) / static_cast<score_t>(2)));
    }
}

Character::Character()
    : strength{ ability() }
    , dexterity{ ability() }
    , constitution{ ability() }
    , intelligence{ ability() }
    , wisdom{ ability() }
    , charisma{ ability() }
    , hitpoints{}
{
    hitpoints = (static_cast<score_t>(10) + modifier(constitution));
}








}  // namespace dnd_character
