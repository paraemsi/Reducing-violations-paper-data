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
    return static_cast<ability_t>((score - 10) / 2);
}

ability_t ability()
{
    static thread_local std::random_device rd;
    static thread_local std::mt19937 rng(rd());
    std::array<ability_t, 4U> rolls{};
    for(std::size_t i = 0U; i < 4U; ++i)
    {
        std::uniform_int_distribution<ability_t> dist(1, 6);
        rolls[i] = dist(rng);
    }
    std::sort(rolls.begin(), rolls.end());
    return (rolls[1] + rolls[2] + rolls[3]);
}

Character::Character()
    : abilities{}
    , hitpoints{}
    , strength{}
    , dexterity{}
    , constitution{}
    , intelligence{}
    , wisdom{}
    , charisma{}
{
    for(std::size_t i = 0U; i < 6U; ++i)
    {
        abilities[i] = ability();
    }
    strength = abilities[0];
    dexterity = abilities[1];
    constitution = abilities[2];
    intelligence = abilities[3];
    wisdom = abilities[4];
    charisma = abilities[5];
    hitpoints = (10 + modifier(constitution));
}

Character generate()
{
    return Character();
}

}  // namespace dnd_character
