#include "dnd_character.h"

#include <array>
#include <algorithm>
#include <numeric>
#include <random>

namespace dnd_character {

namespace {

// Translation-unit-local random number generator.
std::random_device rd;
std::mt19937 engine(rd());
std::uniform_int_distribution<score_t> distribution(static_cast<score_t>(1), static_cast<score_t>(6));

}  // namespace

score_t ability()
{
    std::array<score_t, 4> rolls {};
    for (auto & value : rolls) {
        value = distribution(engine);
    }

    std::sort(rolls.begin(), rolls.end());
    const score_t total { std::accumulate(rolls.begin() + 1, rolls.end(), static_cast<score_t>(0)) };

    return total;
}


Character::Character()
    : strength(ability())
    , dexterity(ability())
    , constitution(ability())
    , intelligence(ability())
    , wisdom(ability())
    , charisma(ability())
    , hitpoints(static_cast<score_t>(10) + modifier(constitution))
{
}

}  // namespace dnd_character
