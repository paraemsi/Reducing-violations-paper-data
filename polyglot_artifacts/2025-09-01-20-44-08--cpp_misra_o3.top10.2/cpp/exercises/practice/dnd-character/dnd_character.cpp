#include "dnd_character.h"

#include <algorithm>
#include <array>
#include <cstddef>
#include <random>

namespace dnd_character {

/* ---------- helpers ----------------------------------------------------- */
namespace {

/* Roll a single six-sided die */
ability_t roll_die()
{
    static std::random_device rd;
    static std::mt19937       engine{rd()};
    static std::uniform_int_distribution<std::int32_t> dist(1, 6);

    /* The distribution returns a signed int; cast explicitly to comply with MISRA */
    return static_cast<ability_t>(dist(engine));   /* explicit cast – assured 1-6 fits in ability_t */
}

/* Roll 4d6 and drop the lowest result */
ability_t roll_four_drop_lowest()
{
    std::array<ability_t, 4U> rolls{};

    for (ability_t & r : rolls)
    {
        r = roll_die();
    }

    std::sort(rolls.begin(), rolls.end());

    modifier_t sum{0};
    for (std::size_t idx{1U}; idx < rolls.size(); ++idx)
    {
        sum += static_cast<modifier_t>(rolls[idx]);
    }

    return static_cast<ability_t>(sum);
}

} /* unnamed namespace */

/* ---------- public free functions --------------------------------------- */

ability_t ability()
{
    return roll_four_drop_lowest();
}

modifier_t modifier(ability_t score)
{
    const modifier_t signed_score{static_cast<modifier_t>(score)};

    if (signed_score >= 10)
    {
        return (signed_score - 10) / 2;
    }
    else
    {
        /* Adjust by one to achieve floor() semantics for negative values */
        return (signed_score - 11) / 2;
    }
}

/* ---------- Character implementation ------------------------------------ */

Character::Character() :
    strength{ability()},
    dexterity{ability()},
    constitution{ability()},
    intelligence{ability()},
    wisdom{ability()},
    charisma{ability()},
    hitpoints{10 + modifier(constitution)}
{
}


}  // namespace dnd_character
