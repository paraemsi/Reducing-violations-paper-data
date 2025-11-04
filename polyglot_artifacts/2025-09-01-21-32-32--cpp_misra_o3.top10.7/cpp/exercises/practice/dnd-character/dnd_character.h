#pragma once

#include <array>
#include <algorithm>
#include <cstdint>
#include <random>

namespace dnd_character {

// Fixed-width signed type alias used throughout the interface.
using score_t = std::int32_t;

// Generate a single ability score by rolling four six-sided dice and
// keeping the highest three.
score_t ability();

// Calculate the ability modifier as floor((score − 10) / 2).
score_t modifier(score_t score);

class Character {
public:
    Character();

    // ability scores
    score_t strength{};
    score_t dexterity{};
    score_t constitution{};
    score_t intelligence{};
    score_t wisdom{};
    score_t charisma{};

    // Initial hit-points for a first-level character.
    score_t hitpoints{};

private:
    static score_t roll_ability();
};

}  // namespace dnd_character
