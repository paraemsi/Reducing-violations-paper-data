#include "dnd_character.h"
#include <random>
#include <algorithm>
#include <numeric>
#include <array>
#include <cstdint>

namespace dnd_character {

namespace
{
    // Helper function to roll a single 6-sided die
    dnd_character::ability_t roll_die(std::mt19937& rng)
    {
        std::uniform_int_distribution<dnd_character::ability_t> dist(1, 6);
        return dist(rng);
    }
}

// Returns a random ability score (4d6 drop lowest)
dnd_character::ability_t dnd_character::ability()
{
    static thread_local std::random_device rd;
    static thread_local std::mt19937 rng(rd());

    std::array<ability_t, 4U> rolls{};
    for(std::size_t i = 0U; i < 4U; ++i)
    {
        rolls[i] = roll_die(rng);
    }
    std::sort(rolls.begin(), rolls.end());
    // Drop the lowest (rolls[0]), sum the rest
    return (rolls[1] + rolls[2] + rolls[3]);
}

// Returns the modifier for a given ability score
dnd_character::ability_t dnd_character::modifier(ability_t score)
{
    // ((score - 10) / 2), rounded down
    return static_cast<ability_t>((score - 10) / 2);
}

dnd_character::Character dnd_character::generate()
{
    Character character{};
    for(std::size_t i = 0U; i < 6U; ++i)
    {
        character.abilities[i] = ability();
    }
    character.hitpoints = (10 + modifier(character.constitution()));
    return character;
}
