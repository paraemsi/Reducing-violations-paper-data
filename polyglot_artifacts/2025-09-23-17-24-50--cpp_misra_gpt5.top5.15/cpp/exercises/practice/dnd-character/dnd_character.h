#pragma once

#include <cstdint>

namespace dnd_character {

using score_t = std::int32_t;

// Generate an ability score by rolling four 6-sided dice and summing the highest three.
score_t ability();

// Compute the ability modifier: floor((score - 10) / 2).
score_t modifier(score_t score);

class Character {
public:
    Character();

    score_t strength{};
    score_t dexterity{};
    score_t constitution{};
    score_t intelligence{};
    score_t wisdom{};
    score_t charisma{};
    score_t hitpoints{};
};

}  // namespace dnd_character
