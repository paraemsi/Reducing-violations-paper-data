#include "dnd_character.h"

#include <algorithm>
#include <numeric>
#include <random>

namespace dnd_character {

namespace {
// single pseudo-random number generator shared by all rolls
inline std::mt19937& rng()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return gen;
}
}  // namespace

ability_t ability()
{
    std::uniform_int_distribution<ability_t> dist(1, 6);
    std::array<ability_t, 4U> rolls{};

    for (std::size_t i{0U}; i < rolls.size(); ++i) {
        rolls[i] = dist(rng());
    }

    const ability_t total{
        static_cast<ability_t>(std::accumulate(
            rolls.cbegin(),
            rolls.cend(),
            static_cast<ability_t>(0)))
    };
    const ability_t min_roll{*std::min_element(rolls.cbegin(), rolls.cend())};

    return (total - min_roll);
}

ability_t modifier(ability_t score)
{
    if (score >= static_cast<ability_t>(10)) {
        return ((score - static_cast<ability_t>(10)) / static_cast<ability_t>(2));
    } else {
        return ((score - static_cast<ability_t>(11)) / static_cast<ability_t>(2));
    }
}

Character::Character()
    : strength{ability()}
    , dexterity{ability()}
    , constitution{ability()}
    , intelligence{ability()}
    , wisdom{ability()}
    , charisma{ability()}
    , hitpoints{static_cast<ability_t>(10) + modifier(constitution)}
{
}








}  // namespace dnd_character
