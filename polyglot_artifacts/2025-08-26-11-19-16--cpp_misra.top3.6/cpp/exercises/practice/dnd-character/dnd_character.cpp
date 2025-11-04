#include "dnd_character.h"
#include <random>
#include <algorithm>
#include <numeric>
#include <cmath>

namespace dnd_character {

namespace
{
    // Helper to roll a single 6-sided die
    dnd_character::ability_t roll_die(std::mt19937& rng)
    {
        std::uniform_int_distribution<dnd_character::ability_t> dist(1, 6);
        return dist(rng);
    }

    // Helper to roll 4d6 and sum the largest 3
    dnd_character::ability_t roll_4d6_drop_lowest(std::mt19937& rng)
    {
        std::array<dnd_character::ability_t, 4U> rolls{};
        for(std::size_t i = 0U; i < 4U; ++i)
        {
            rolls[i] = roll_die(rng);
        }
        std::sort(rolls.begin(), rolls.end());
        // sum the largest 3
        return (rolls[1] + rolls[2] + rolls[3]);
    }
}

dnd_character::ability_t dnd_character::ability()
{
    static thread_local std::random_device rd;
    static thread_local std::mt19937 rng(rd());
    return roll_4d6_drop_lowest(rng);
}

dnd_character::ability_t dnd_character::modifier(dnd_character::ability_t score)
{
    // ((score - 10) / 2) rounded down
    return static_cast<dnd_character::ability_t>(std::floor(static_cast<double>(score - 10) / 2.0));
}

dnd_character::Character dnd_character::generate()
{
    Character c{};

    for(std::size_t i = 0U; i < 6U; ++i)
    {
        c.abilities[i] = ability();
    }

    c.hitpoints = (10 + modifier(c.constitution()));

    return c;
}

}  // namespace dnd_character
