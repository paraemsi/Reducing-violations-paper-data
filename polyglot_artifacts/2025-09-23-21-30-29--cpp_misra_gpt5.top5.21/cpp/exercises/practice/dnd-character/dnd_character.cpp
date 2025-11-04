#include "dnd_character.h"

#include <algorithm>
#include <array>
#include <cstddef>
#include <random>

namespace dnd_character {

using dist_type = std::uniform_int_distribution<ability_t>;

static ability_t roll_die_6()
{
    static std::mt19937 engine{std::random_device{}()};
    static dist_type dist(static_cast<ability_t>(1), static_cast<ability_t>(6));
    return dist(engine);
}

ability_t ability()
{
    std::array<ability_t, 4U> rolls{};
    for (ability_t& r : rolls) {
        r = roll_die_6();
    }
    std::sort(rolls.begin(), rolls.end());
    constexpr std::size_t i1 = 1U;
    constexpr std::size_t i2 = 2U;
    constexpr std::size_t i3 = 3U;
    ability_t sum = ((rolls[i1] + rolls[i2]) + rolls[i3]);
    return sum;
}

ability_t modifier(ability_t score)
{
    ability_t diff = score - static_cast<ability_t>(10);
    ability_t mod = diff / static_cast<ability_t>(2);
    if ((diff < static_cast<ability_t>(0)) && ((diff % static_cast<ability_t>(2)) != static_cast<ability_t>(0))) {
        mod = mod - static_cast<ability_t>(1);
    }
    return mod;
}

Character::Character()
    : strength(ability())
    , dexterity(ability())
    , constitution(ability())
    , intelligence(ability())
    , wisdom(ability())
    , charisma(ability())
    , hitpoints((static_cast<ability_t>(10) + modifier(constitution)))
{
}


}  // namespace dnd_character
