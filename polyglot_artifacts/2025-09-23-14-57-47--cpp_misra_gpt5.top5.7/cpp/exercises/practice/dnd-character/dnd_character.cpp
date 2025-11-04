#include "dnd_character.h"

#include <algorithm>
#include <array>
#include <numeric>
#include <random>

namespace dnd_character {

namespace {
// PRNG accessor with static storage duration
std::mt19937& rng()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return gen;
}

ability_score_t roll_d6()
{
    static std::uniform_int_distribution<ability_score_t> dist(static_cast<ability_score_t>(1), static_cast<ability_score_t>(6));
    return dist(rng());
}
}  // namespace

ability_score_t ability()
{
    std::array<ability_score_t, 4> dice{{roll_d6(), roll_d6(), roll_d6(), roll_d6()}};
    std::sort(dice.begin(), dice.end());
    const ability_score_t sum = std::accumulate(dice.begin(), dice.end(), static_cast<ability_score_t>(0));
    return (sum - dice[0]);
}

ability_modifier_t modifier(ability_score_t score)
{
    const ability_score_t n = (score - static_cast<ability_score_t>(10));
    const bool is_negative = (n < static_cast<ability_score_t>(0));
    ability_modifier_t q = static_cast<ability_modifier_t>(n / static_cast<ability_score_t>(2));
    const bool is_odd = ((n % static_cast<ability_score_t>(2)) != static_cast<ability_score_t>(0));

    if (is_negative) {
        if (is_odd) {
            q = (q - static_cast<ability_modifier_t>(1));
        } else {
            // No adjustment needed for even negative numbers
        }
    } else {
        // No adjustment needed for non-negative numbers
    }

    return q;
}

Character::Character()
    : strength{ability()}
    , dexterity{ability()}
    , constitution{ability()}
    , intelligence{ability()}
    , wisdom{ability()}
    , charisma{ability()}
    , hitpoints{(static_cast<hitpoints_t>(10) + modifier(constitution))}
{
}








}  // namespace dnd_character
