#include "dnd_character.h"

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
    // Roll four 6-sided dice
    std::array<std::int32_t, 4U> rolls{};
    for(std::size_t i = 0U; i < 4U; ++i)
    {
        rolls[i] = roll_die();
    }

    // Find the smallest roll
    std::size_t min_index = 0U;
    for(std::size_t i = 1U; i < 4U; ++i)
    {
        if(rolls[i] < rolls[min_index])
        {
            min_index = i;
        }
    }

    // Sum the largest three dice
    std::int32_t sum = 0;
    for(std::size_t i = 0U; i < 4U; ++i)
    {
        if(i != min_index)
        {
            sum = (sum + rolls[i]);
        }
    }
    return sum;
}

ability_t modifier(ability_t score)
{
    // ((score - 10) / 2), rounded down
    return static_cast<ability_t>(((score - 10) / 2));
}

character generate()
{
    character c{};
    c.strength = ability();
    c.dexterity = ability();
    c.constitution = ability();
    c.intelligence = ability();
    c.wisdom = ability();
    c.charisma = ability();
    c.hitpoints = (10 + modifier(c.constitution));
    return c;
}

}  // namespace dnd_character
