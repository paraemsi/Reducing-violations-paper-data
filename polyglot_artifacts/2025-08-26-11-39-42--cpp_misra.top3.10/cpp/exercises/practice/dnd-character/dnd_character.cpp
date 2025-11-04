#include "dnd_character.h"
#include <random>
#include <algorithm>
#include <numeric>
#include <array>
#include <cstdint>

namespace dnd_character {

ability_t modifier(ability_t score)
{
    // ((score - 10) / 2), rounded down
    return static_cast<ability_t>(((score - 10) / 2));
}

ability_t ability()
{
    static thread_local std::random_device rd;
    static thread_local std::mt19937 rng(rd());
    std::uniform_int_distribution<std::int32_t> dist(1, 6);
    std::array<ability_t, 4U> rolls{};
    for(std::size_t i = 0U; i < 4U; ++i)
    {
        rolls[i] = dist(rng);
    }
    std::sort(rolls.begin(), rolls.end());
    // sum the highest 3 dice
    return (rolls[1U] + rolls[2U] + rolls[3U]);
}

Character generate()
{
    Character character{};
    for(std::size_t i = 0U; i < 6U; ++i)
    {
        character.abilities[i] = ability();
    }
    character.hitpoints = (10 + modifier(character.constitution()));
    return character;
}

}  // namespace dnd_character
