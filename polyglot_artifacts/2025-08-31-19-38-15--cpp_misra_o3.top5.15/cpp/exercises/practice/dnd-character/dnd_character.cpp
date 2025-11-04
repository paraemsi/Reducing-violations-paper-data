#include "dnd_character.h"

#include <algorithm>
#include <array>
#include <random>

namespace {

// Internal type alias for all numeric values.
using value_t = std::int32_t;

// Constants for a standard six-sided die.
constexpr value_t min_die_value = static_cast<value_t>(1);
constexpr value_t max_die_value = static_cast<value_t>(6);

// Roll one six-sided die.
value_t roll_die(std::mt19937& engine)
{
    std::uniform_int_distribution<value_t> dist(min_die_value, max_die_value);
    return dist(engine);
}

}  // namespace

namespace dnd_character {

std::int32_t ability()
{
    static std::random_device rd;
    static std::mt19937 rng(rd());

    std::array<value_t, static_cast<std::size_t>(4)> rolls{};

    for (std::size_t i = static_cast<std::size_t>(0); i < rolls.size(); ++i) {
        rolls[i] = roll_die(rng);
    }

    std::sort(rolls.begin(), rolls.end());  // Ascending
    // Sum of the highest three rolls (indices 1, 2, 3 after sorting)
    return (rolls[1] + rolls[2]) + rolls[3];
}

std::int32_t modifier(std::int32_t score)
{
    const std::int32_t diff = score - static_cast<std::int32_t>(10);
    if (diff >= static_cast<std::int32_t>(0)) {
        return diff / static_cast<std::int32_t>(2);
    } else {
        // For negative values, ensure arithmetic rounds toward minus infinity
        return (diff - static_cast<std::int32_t>(1)) / static_cast<std::int32_t>(2);
    }
}

// ---- Character ----------------------------------------------------------------

Character::Character()
    : strength(ability())
    , dexterity(ability())
    , constitution(ability())
    , intelligence(ability())
    , wisdom(ability())
    , charisma(ability())
    , hitpoints(static_cast<std::int32_t>(10) + modifier(constitution))
{
}

}  // namespace dnd_character
