#include "dnd_character.h"

#include <algorithm>
#include <array>
#include <random>

namespace dnd_character {

//--------------------------------------------------------------------------
// PRNG helpers – one engine shared for all rolls
//--------------------------------------------------------------------------
namespace {
    std::random_device                          seeder;
    std::mt19937                                engine{ seeder() };
    std::uniform_int_distribution<ability_t>    d6{ static_cast<ability_t>(1),
                                                    static_cast<ability_t>(6) };

    //----------------------------------------------------------------------
    // Compute the ability modifier as floor((score − 10) / 2)
    //----------------------------------------------------------------------
    ability_t ability_modifier(const ability_t score)
    {
        const ability_t raw  = (score - static_cast<ability_t>(10));
        const bool       neg = (raw < static_cast<ability_t>(0));

        ability_t mod = raw / static_cast<ability_t>(2);

        if ((neg) && ((raw % static_cast<ability_t>(2)) != static_cast<ability_t>(0))) {
            /* round toward negative infinity */
            mod = mod - static_cast<ability_t>(1);
        }

        return mod;
    }
//--------------------------------------------------------------------------
// Public wrapper so that unit tests can access the calculation
//--------------------------------------------------------------------------
ability_t modifier(ability_t score)
{
    return ability_modifier(score);
}
}  // unnamed namespace

//--------------------------------------------------------------------------
// Roll 4d6, drop the lowest die, sum the rest
//--------------------------------------------------------------------------
ability_t ability()
{
    std::array<ability_t, 4U> rolls{};

    for (ability_t& r : rolls) {
        r = d6(engine);
    }

    std::sort(rolls.begin(), rolls.end());

    ability_t total = static_cast<ability_t>(0);

    for (std::size_t i = 1U; i < rolls.size(); ++i) { /* keep top three */
        total = total + rolls[i];
    }

    return total;
}

//--------------------------------------------------------------------------
// Character implementation
//--------------------------------------------------------------------------
Character::Character()
    : strength{ ability() }
    , dexterity{ ability() }
    , constitution{ ability() }
    , intelligence{ ability() }
    , wisdom{ ability() }
    , charisma{ ability() }
{
    const ability_t mod = modifier(constitution);
    hitpoints = static_cast<hitpoint_t>(10) + mod;
}


}  // namespace dnd_character
