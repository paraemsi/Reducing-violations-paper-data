#pragma once

#include <cstdint>

namespace dnd_character {

using score_t = std::int32_t;  // fixed-width signed type mandated by MISRA

score_t ability() noexcept;          // roll 4d6, keep highest three
score_t modifier(score_t ability_score) noexcept;  // ability modifier helper

class Character final {
public:
    Character();

    score_t strength;
    score_t dexterity;
    score_t constitution;
    score_t intelligence;
    score_t wisdom;
    score_t charisma;

    score_t hitpoints;
};

}  // namespace dnd_character
