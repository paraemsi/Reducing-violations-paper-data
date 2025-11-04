#include "dnd_character.h"
#include <random>
#include <algorithm>
#include <numeric>
#include <vector>
#include <cmath>

namespace dnd_character {

namespace
{
    // Use a single random engine for all rolls
    std::random_device rd;
    std::mt19937 engine(rd());
    std::uniform_int_distribution<std::int32_t> dist(1, 6);

    // Roll a single 6-sided die
    std::int32_t roll_die()
    {
        return dist(engine);
    }
}

ability_t ability()
{
    std::array<std::int32_t, 4> rolls;
    for(std::size_t i = 0U; i < 4U; ++i)
    {
        rolls[i] = roll_die();
    }
    std::sort(rolls.begin(), rolls.end());
    // Drop the lowest roll (rolls[0])
    ability_t sum = static_cast<ability_t>((rolls[1] + rolls[2]) + rolls[3]);
    return sum;
}

ability_t modifier(ability_t score)
{
    // Constitution modifier: floor((score - 10) / 2)
    // Use static_cast to ensure correct type and avoid narrowing
    ability_t mod = static_cast<ability_t>(std::floor(static_cast<double>(score - 10) / 2.0));
    return mod;
}

Character generate()
{
    Character c;
    c.strength = ability();
    c.dexterity = ability();
    c.constitution = ability();
    c.intelligence = ability();
    c.wisdom = ability();
    c.charisma = ability();
    ability_t con_mod = modifier(c.constitution);
    c.hitpoints = static_cast<ability_t>(10 + con_mod);
    return c;
}

}  // namespace dnd_character
