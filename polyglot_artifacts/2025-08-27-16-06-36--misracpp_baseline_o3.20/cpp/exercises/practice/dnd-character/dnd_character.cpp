#include "dnd_character.h"

#include <algorithm>
#include <array>
#include <numeric>
#include <cmath>

namespace dnd_character {

namespace {
// Obtain a reference to a static random number generator, seeded once.
std::mt19937& rng()
{
    static std::random_device rd;
    static std::mt19937 gen{rd()};
    return gen;
}
}  // namespace

int ability()
{
    std::uniform_int_distribution<int> dist(1, 6);

    // Roll four dice.
    std::array<int, 4> rolls{};
    for (int& v : rolls) {
        v = dist(rng());
    }

    // Sum the highest three rolls.
    const int total = std::accumulate(rolls.begin(), rolls.end(), 0);
    const int lowest = *std::min_element(rolls.begin(), rolls.end());
    return total - lowest;
}

int modifier(int score)
{
    // Use floating-point division and std::floor to ensure negative
    // modifiers are rounded down (toward −∞) instead of toward zero.
    return static_cast<int>(std::floor((score - 10) / 2.0));
}

Character::Character()
    : strength{ability()}
    , dexterity{ability()}
    , constitution{ability()}
    , intelligence{ability()}
    , wisdom{ability()}
    , charisma{ability()}
    , hitpoints{10 + modifier(constitution)}
{
}

}  // namespace dnd_character
